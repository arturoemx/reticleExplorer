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

struct pathTStamp
{
	string path;
	string timeStamp;
};

void processImage(reticleParams &prm, cv::Mat I)
{
	
}

void loadParseFileNames(char *dirName, vector<pathTStamp> &fNm)
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
	u_int idx;

	if (argc < 2)
		return -1;
	else
		loadParseFileNames(argv[1], fileNames);

	cout << "loading filenames" << endl;
	for (idx = 0, itp = fileNames.begin(); itp != fileNames.end(); ++itp, ++idx)
	{
		mFrame mF;

		cout << "Path[" << idx << "]     :  " << itp->path << endl
             << "timestamp[" << idx << "]:  " << itp->timeStamp << endl << endl;
        Images.insert(Images.begin(), mFrame(itp->path, stod(itp->timeStamp)));
	}
	
    cout << endl;

	return 0;
}