#include <opencv2/opencv.hpp>
#include <showDisplay.h>
#include <reticleExplorer.h>
#include <mFrame.h>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>

using namespace std;
using namespace cv;
using namespace boost::filesystem;
using namespace shDisp;

struct pathTStamp
{
	string path;
	string timeStamp;
};

void processImage(reticleParams &prm, cv::Mat I)
{
	
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
	u_int idx, firstImage = 0, lastImage = 0, numImages;
	
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

	numImages = lastImage - firstImage + 1;
	cout << "loading " << numImages << " Images" << endl;
	for (idx = firstImage, itp = fileNames.begin() + firstImage; idx <= lastImage && itp != fileNames.end(); ++itp, ++idx)
	{
		mFrame mF;

		cout << "Path[" << idx << "]     :  " << itp->path << endl
             << "timestamp[" << idx << "]:  " << itp->timeStamp << endl << endl;
        Images.insert(Images.begin(), mFrame(itp->path, stod(itp->timeStamp)));
	}
	
    cout << endl;



	D.testDisplay();

	namedWindow("Display", WINDOW_GUI_EXPANDED);
	imshow("Display", D.Display);

	waitKeyEx(0);

	return 0;
}