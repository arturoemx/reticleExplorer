#include <opencv2/opencv.hpp>
#include <showDisplay.h>
#include <mFrame.h>
#include <annotateImage.h>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>

using namespace std;
using namespace cv;
using namespace boost::filesystem;
using namespace shDisp;
using namespace imNote;


#ifdef QT
enum KeyCodes {Esc=27, KeyUp=65362, KeyLeft=65361, KeyDown=65364, KeyRight=65363, Key_p=112, Key_P=80};
#endif

struct reticleParams
{
	//Threshold Parameters
	int brightThr;

	//Canny_Parameters
	int lowThr, highThr;
	int CannyAppertureSize;
	bool L2Gradient;

	//Hough Parameters
	double rho;
	double theta;
	int voteThr;

	reticleParams(uint bThr, uint lThr, uint hThr, int CAP, bool L2G, double _rho, double _theta, int _vThr)
	{
		brightThr = bThr;
		lowThr = lThr;
		highThr = hThr;
		CannyAppertureSize = CAP;
		L2Gradient = L2G;
		rho  = _rho;
		theta = _theta;
		voteThr = _vThr;
	}
	
	reticleParams()
	{
		brightThr = 127;
		lowThr = 127;
		highThr = 128;
		CannyAppertureSize = 3;
		L2Gradient = true;
		rho  = 0.25; // one fourth of a pixel.
		theta = M_PI/360; //0.5 degrees
		voteThr = 150;
	}	
};

struct pathTStamp
{
	string path;
	string timeStamp;
};

void processImage(reticleParams &prm, cv::Mat Gray, annotations &Feat)
{
	Mat Binary, Edges;
	vector<Vec4i> lines;

	//Umbraliza
	if (prm.brightThr > 0)
		threshold(Gray, Binary, prm.brightThr, 255, THRESH_BINARY);
	else
		if (prm.brightThr > 0)
			threshold(Gray, Binary, prm.brightThr, 255, THRESH_OTSU);
		else
			adaptiveThreshold 	(Gray, Binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, 0);

	Feat.addLayer("Binary");
	Feat.addImageFeature("Binary", Binary, Scalar_<uchar> (0, 128, 0));
	
	//Encuentra Bordes.
	Canny (Binary, Edges, prm.lowThr, prm.highThr, prm.CannyAppertureSize, prm.L2Gradient);

	Feat.addLayer("Edges");
	Feat.addImageFeature("Edges", Binary, Scalar_<uchar> (0, 128, 128));

	HoughLinesP (Edges, lines, prm.rho, prm.theta, prm.voteThr);
}

void loadParseFileNames(string dirName, vector<pathTStamp> &fNm)
{
	if (is_directory(dirName))
	{
    	for (directory_iterator itr(dirName); itr!=directory_iterator(); ++itr)
    	{
    		if (is_regular_file(itr->status()))
    		{
    			pathTStamp n;
    			string tmp;

    			tmp = n.path = itr->path().string();
				tmp = tmp.substr(tmp.find("-")+1);
				tmp.erase(tmp.find(".jpg"));
				n.timeStamp = tmp;
    			fNm.push_back(n);
      		}
      	}
    }
}

int main(int argc, char **argv)
{
	vector<pathTStamp> fileNames;
	vector<pathTStamp>::iterator itp;
	vector <mFrame> Images;
	string dirName;
	u_int idx, firstImage = 0, lastImage = 0, nImages = 0;
	bool running = true;
	KeyCodes key;
	reticleParams rPrms;
	Mat Gray;

	showDisplay D;
	
	if (argc < 2)
		return -1;
	else
	{
		dirName = argv[1];

		loadParseFileNames(dirName, fileNames);
		lastImage = fileNames.size() - 1;
		
		if (argc == 3)
			lastImage = stoi(string(argv[2]));
		else
			if (argc > 3)
			{
				firstImage = stoi(string(argv[2]));
				lastImage = stoi(string(argv[3]));
			}
	}

	if (lastImage > fileNames.size())
		lastImage = fileNames.size() - 1;

	nImages = lastImage - firstImage + 1;

#ifdef __verbose__
	cout << "loading " << nImages + 1 << " Images" << endl;
#endif
	for (idx = firstImage, itp = fileNames.begin() + firstImage; idx <= lastImage && itp != fileNames.end(); ++itp, ++idx)
	{
		mFrame mF;

#ifdef __verbose__
		cout << "Path[" << idx << "]     :  " << itp->path << endl
             << "timestamp[" << idx << "]:  " << itp->timeStamp << endl << endl;
#endif
        Images.insert(Images.begin(), mFrame(itp->path, stod(itp->timeStamp)));
	}

#ifdef __verbose__	
    cout << endl;
#endif

	
	annotations Features(Images[0].Frame.rows, Images[0].Frame.cols);

	namedWindow("Display", WINDOW_GUI_EXPANDED);
	
	D.testDisplay();
	idx = 0;
    do
    {
    	D.setMain(Images[idx].Frame);
    	imshow("Display", D.Display);
    	key = (KeyCodes)(waitKeyEx(0) & 0x0000FFFF);
    	cout << "Key:" << key << endl;
    	switch (key)
    	{
    		case KeyUp:
    			idx = idx > 0 ? idx-1 : idx;
    			break;
    		case KeyDown:
    			idx = idx < nImages-1 ? idx+1 : idx;
    			break;
    		case Key_p:
    		case Key_P: 
    			//Convierte a tonos de gris.
				cvtColor(Images[idx].Frame, Gray, COLOR_BGR2GRAY);
    			processImage(rPrms, Gray, Features);
    	/*		cout << "Se encontraron " << Lines.size() << " Lineas." << endl;
    			for (long unsigned i=0;i<Lines.size();i++)
    				cout << "Linea[" << i << "]=" << Lines[i] << endl;
    			cout << endl;*/
    			break;
    		case Esc: running = false; break;
    		default:break;
    	}

    } while (running);
	
	return 0;
}