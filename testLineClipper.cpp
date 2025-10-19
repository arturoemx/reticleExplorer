#include <opencv2/opencv.hpp>
#include <drawingFeatures.h>
#include <showDisplay.h>
#include <lineSimilarity.h>
#include <string>

using namespace cv;
using namespace std;
using namespace gfeat;
using namespace shDisp;


int main()
{
	int keyVal;
	cv::Mat Base;
	showDisplay D(1024, 768, 800, 600);
	bool runFlag;

	Base = Mat::zeros(600,800,CV_8UC3);
	
	
	D.testDisplay();
	namedWindow("Display", WINDOW_GUI_EXPANDED);
	imshow("Display", D.Display);
	waitKeyEx(1);
	clipBox cA(0, 0,799,0, 799,599,0,599);
	clipBox cB(100,100,500,100,500,500,100,500);

	cv::line(D.Main, Point(100,100), Point(500, 100), Scalar_<uchar> (0,0,255), 3);
	cv::line(D.Main, Point(500,100), Point(500, 500), Scalar_<uchar> (0,0,255), 3);
	cv::line(D.Main, Point(500,500), Point(100, 500), Scalar_<uchar> (0,0,255), 3);
	cv::line(D.Main, Point(100,500), Point(100, 100), Scalar_<uchar> (0,0,255), 3);

	runFlag = true;
	while (runFlag)
	{
		float x1, y1, x2, y2;
		dLine ln;
		line2D *gl = &ln;
		dPoint pA1, pA2, pB1, pB2;

		x1 = random() % D.mainWidth;
		y1 = random() % D.mainHeight;
		x2 = random() % D.mainWidth;
		y2 = random() % D.mainHeight;

		ln = dLine(x1,y1,x2,y2);

		cA.clipLine(*gl, pA1, pA2);
		cB.clipLine(*gl, pB1, pB2);

		cv::line(D.Main, Point((int)rintf(pA1.cx),(int)rintf(pA1.cy)), Point((int)rintf(pA2.cx),(int)rintf(pA2.cy)),
			        Scalar_<uchar> (128,128,0));
		if (cB.clipLine(*gl, pB1, pB2))
			cv::line(D.Main, Point((int)rintf(pB1.cx),(int)rintf(pB1.cy)), Point((int)rintf(pB2.cx),(int)rintf(pB2.cy)),
			        Scalar_<uchar> (255,255,0),2);

		imshow("Display", D.Display);
		
		keyVal = waitKeyEx(30) & 0x000000FF;

		cout.flush();

		if (keyVal == 27)
			runFlag = false;
	}

	return 0;
}