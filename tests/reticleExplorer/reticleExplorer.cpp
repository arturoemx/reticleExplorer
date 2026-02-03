#include <opencv2/opencv.hpp>
#include <showDisplay.h>
#include <mFrame.h>
#include <annotateImage.h>
#include <lineSimilarity.h>
#include <algorithm>
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

struct pathTStamp
{
	string path;
	string timeStamp;
};

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

struct reticleParams
{
	//Threshold Parameters
	int intensityThr;

	//Canny_Parameters
	int  CannyLowThr, CannyHighThr;
	int  CannyAppertureSize;
	bool CannyL2Gradient;

	//Hough Parameters
	double HoughRho;
	double HoughTheta;
	int    HoughVoteThr;
	int    HoughMinLineLength;
	bool *changeFlag;
	string windowName;

	reticleParams(const string &WN, uint iThr, uint lThr, uint hThr, int CAP, bool L2G, double _rho, double _theta, int _vThr, int minLL, bool *chF)
	{
		intensityThr = iThr;
		CannyLowThr = lThr;
		CannyHighThr = hThr;
		CannyAppertureSize = CAP;
		CannyL2Gradient = L2G;
		HoughRho  = _rho;
		HoughTheta = _theta;
		HoughVoteThr = _vThr;
		HoughMinLineLength = minLL;
		windowName = WN;
		changeFlag = chF;
		*changeFlag = false;
	}
	
	reticleParams(const string &WN, bool *chF)
	{
		intensityThr = 219;
		CannyLowThr = 127;
		CannyHighThr = 128;
		CannyAppertureSize = 5;
		CannyL2Gradient = true;
		HoughRho  = 0.25; // one fourth of a pixel.
		HoughTheta = M_PI/360; //0.5 degrees
		HoughVoteThr = 15;
		HoughMinLineLength = 10;
		windowName = WN;
		changeFlag = chF;
		*changeFlag = false;
	}
};

ostream &operator<<(ostream &s, reticleParams &p)
{
	s << "Intensity Threshold : " << p.intensityThr << endl
	  << "Canny Low Threshold : " << p.CannyLowThr << endl
	  << "Canny high Threshold: " << p.CannyHighThr << endl
	  << "Canny Apperture Size: " << p.CannyAppertureSize << endl
	  << "Canny L2 Gradient   : " << p.CannyL2Gradient << endl
	  << "Hough Rho           : " << p.HoughRho << endl
	  << "Hough Theta         : " << p.HoughTheta << endl
	  << "Hough Vote Threshold: " << p.HoughVoteThr << endl
	  << "Hough Min LineLength: " << p.HoughMinLineLength << endl << endl;

	  return s;
}


//**********************************************************************
//**                            Control Panel                         **
//**********************************************************************



void intensityChange(int pos, void *data)
{
	reticleParams *rP = (reticleParams *)data;
	rP->intensityThr = pos;
	*(rP->changeFlag) =  true;
}

void CannyLowThrChange(int pos, void *data)
{
	reticleParams *rP = (reticleParams *)data;
	rP->CannyLowThr = pos;
	*(rP->changeFlag) =  true;
}

void CannyHighThrChange(int pos, void *data)
{
	reticleParams *rP = (reticleParams *)data;
	rP->CannyHighThr = pos;
	*(rP->changeFlag) =  true;
}

void CannyAppertureSizeChange(int pos, void *data)
{
	reticleParams *rP = (reticleParams *)data;
	rP->CannyAppertureSize = 3 + pos * 2;
	*(rP->changeFlag) =  true;
}

void lauchControls(reticleParams &prms, const string &controlWindowName)
{
	intensityChange(219,&prms);
	CannyLowThrChange(127,&prms);
	CannyHighThrChange(128,&prms);
	CannyAppertureSizeChange(1,&prms);
	createTrackbar("Intensity Thr", controlWindowName, &prms.intensityThr, 255, intensityChange, &prms);
	createTrackbar("Canny Low Thr", controlWindowName, &prms.CannyLowThr, 255, CannyLowThrChange, &prms);
	createTrackbar("Canny Low High", controlWindowName, &prms.CannyHighThr, 255, CannyHighThrChange, &prms);
	createTrackbar("Canny Apperture Size", controlWindowName, nullptr, 2, CannyAppertureSizeChange, &prms);
}

struct dists
{
	int idx1, idx2;
	float d;
	bool close;
	dists()
	{
		idx1 = idx2 = 0;
		d = 0.;
		close = false;
	}
	dists(int _idx1, int _idx2, float _d, bool _close)
	{
		idx1 = _idx1;
		idx2 = _idx2;
		d = _d;
		close = _close;
	}
};

ostream &operator<< (ostream &s, dists &d)
{
	s << d.idx1 << ", " << d.idx2 << ", " << d.d << ", " << d.close << endl;
	return s;
}

int checkLines(vector<Vec4f> &l, clipBox &clpB, float threshold, vector<dists> &D)
{
	int tope1, tope2, i, j, k, cont;
	float d = 0;
	bool close;
	vector<Vec4f>::iterator itL1, itL2;
	dLine dL1, dL2;

	tope2 = l.size();
	if (tope2  == 0)
		return 0;
	tope1 = tope2 - 1;
	
	itL1 = l.begin();
	cont = 0;
	for (i=k=0;i<tope1;++i, ++itL1)
	{
		dL1 = dLine((*itL1)[0],(*itL1)[1],(*itL1)[2],(*itL1)[3]);
		itL2 = itL1+1;
		for (j=i+1;j<tope2;++j, ++k, ++itL2)
		{
			dL2 = dLine((*itL2)[0],(*itL2)[1],(*itL2)[2],(*itL2)[3]);

			close = lineSimilarity(dL1, dL2, clpB, d, threshold=2);
			if (close)
				cont++;
			D.push_back(dists(i, j, d, close));
		}
	}
	return cont;
}

void processImage(reticleParams &prm, cv::Mat Gray, annotations &Feat)
{
	Mat Binary, Edges;
	vector<Vec4f> lines;
	vector<Vec4f>::iterator itL, endL;
	vector<dists> D;

	//Umbraliza
	if (prm.intensityThr > 0)
		threshold(Gray, Binary, prm.intensityThr, 255, THRESH_BINARY);
	else
		if (prm.intensityThr == 0)
			threshold(Gray, Binary, prm.intensityThr, 255, THRESH_OTSU);
		else
			adaptiveThreshold 	(Gray, Binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 45, 0);

	imwrite("Gray.png", Gray);

	//Feat.addLayer("Binary");
	//Feat.addImageFeature("Binary", Binary, Scalar_<uchar> (0, 128, 0));
	imwrite("Binary.png", Binary);
	
	//Encuentra Bordes.
	Canny (Binary, Edges, prm.CannyLowThr, prm.CannyHighThr, prm.CannyAppertureSize, prm.CannyL2Gradient);
	threshold(Edges, Edges, prm.intensityThr, 255, THRESH_OTSU);

	Feat.addLayer("Edges");
	Feat.addImageFeature("Edges", Edges, Scalar_<uchar> (255, 255, 0));
	imwrite("Edges.png", Edges);

	
	HoughLinesP (Edges, lines, prm.HoughRho, prm.HoughTheta, prm.HoughVoteThr, prm.HoughMinLineLength);

	Feat.addLayer("Lines");

	itL = lines.begin();
	endL = lines.end();
	for (;itL != endL;++itL)
	{
		dLine dL((*itL)[0],(*itL)[1],(*itL)[2],(*itL)[3]);
		dL.setThickness(1);

		Feat.addLineFeature("Lines", dL, Scalar_<uchar> (0, 196, 0));
	}

}

bool compFrames(mFrame &a, mFrame &b)
{
	return a.timeStamp < b.timeStamp;
}

int main(int argc, char **argv)
{
	vector<pathTStamp> fileNames;
	vector<pathTStamp>::iterator itp;
	vector <mFrame> Images;
	vector<annotations> Notes;
	string dirName;
	u_int idx, idxOld, idxName, firstImage = 0, lastImage = 0, nImages = 0;
	bool running = true;
	KeyCodes key;
	
	Mat Gray, dGray;
	bool changeFlag;
	reticleParams rPrms("", &changeFlag);
	

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
	for (idx = 0, idxName = firstImage, itp = fileNames.begin() + firstImage; idxName <= lastImage && itp != fileNames.end(); ++itp, ++idx, ++idxName)
	{
		mFrame mF;

#ifdef __verbose__
		cout << "Path[" << idxName << "]     :  " << itp->path << endl
             << "timestamp[" << idxName << "]:  " << itp->timeStamp << endl << endl;
#endif
        Images.insert(Images.begin()+idx, mFrame(itp->path, stod(itp->timeStamp)));
        Notes.insert(Notes.begin(), annotations(Images[idx].Frame.rows, Images[idx].Frame.cols));
	}

#ifdef __verbose__	
    cout << endl;
#endif

    sort(Images.begin(), Images.end(), compFrames);

	namedWindow("Display", WINDOW_GUI_EXPANDED);
	namedWindow("Control", WINDOW_GUI_NORMAL);
	
	D.testDisplay();
	idxOld = idx = 0;
	D.setMain(Images[idx].Frame);
    imshow("Display", D.Display);

    changeFlag = true;
    lauchControls(rPrms, "Control");
	waitKeyEx(1);

    do
    {
    	key = (KeyCodes)(waitKeyEx(30) & 0x0000FFFF);
    	
    	switch (key)
    	{
    		case KeyUp:
    			cout << "Retreat: "<< idx << endl; cout.flush();
    			idxOld = idx;
    			idx = idx > 0 ? idx-1 : idx;
    			if (idxOld != idx)
    				changeFlag = true;
    			D.setMain(Images[idx].Frame);
    			imshow("Display", D.Display);
    			waitKeyEx(1);
    			break;
    		case KeyDown:
    			cout << "Advance: "<< idx << endl; cout.flush();
    			idxOld = idx;
    			idx = idx < nImages-1 ? idx+1 : idx;
    			if (idxOld != idx)
    				changeFlag = true;
    			D.setMain(Images[idx].Frame);
    			imshow("Display", D.Display);
    			waitKeyEx(1);
    			break;
    		case Esc:
    			running = changeFlag = false;
    			break;
    		default:
    			break;
    	}

    	//Convierte a tonos de gris.
    	if (changeFlag)
    	{
    		cout << "rPrms:" << rPrms << endl;
    		cout.flush();

    		Notes[idx].clear();
			cvtColor(Images[idx].Frame, Gray, COLOR_BGR2GRAY);
			processImage(rPrms, Gray, Notes[idx]);
			cvtColor(Gray,dGray,COLOR_GRAY2RGB);
			imwrite("Gray.png", Gray);
			Notes[idx].applyAnnotations(dGray, true);
			D.setMain(dGray);
			imshow("Display", D.Display);
			waitKeyEx(1);

			changeFlag = false;
		}
    } while (running);
	
	return 0;
}