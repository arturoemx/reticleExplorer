#include <showDisplay.h>
#include <mFrame.h>
#include <annotateImage.h>
#include <lineSimilarity.h>
#include <dynamicDisplay.h>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;
using namespace boost::filesystem;
using namespace shDisp;
using namespace imNote;


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

int main(int argc, char **argv)
{
	vector<pathTStamp> fileNames;
	vector<pathTStamp>::iterator itp;
	string dirName;
	u_int idx, idxName, firstImage = 0, lastImage = 0;
	Mat Gray, dGray;
	dynDisplay dynD(1920, 1080);
	
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

#ifdef __verbose__
	cout << "loading " << lastImage - firstImage + 2 << " Images" << endl;
#endif
	for (idx = 0, idxName = firstImage, itp = fileNames.begin() + firstImage; idxName <= lastImage && itp != fileNames.end(); ++itp, ++idx, ++idxName)
	{
		mFrame mF;

#ifdef __verbose__
		cout << "Path[" << idxName << "]     :  " << itp->path << endl
             << "timestamp[" << idxName << "]:  " << itp->timeStamp << endl << endl;
#endif
        dynD.addImage(mFrame(itp->path, stod(itp->timeStamp)), idx);
	}

#ifdef __verbose__	
    cout << endl;
#endif

    dynD.mainLoop();

    return 0;
}
