#include <showDisplay.h>

using namespace shDisp;

showDisplay::showDisplay(uint _w, uint _h, uint _mW, uint _mH, uint _hS, uint _vS)
{
	width = _w;
	height = _h;
	mainWidth = _mW;
	mainHeight = _mH;
	hSep = _hS;
	vSep = _vS;
	consoleWidth = width - 2 * hSep;
	consoleHeight = height - mainHeight - 3 * vSep;
	dataWidth = width - mainWidth - 3 * hSep;
	dataHeight = mainHeight;

	Display = cv::Mat::zeros(height, width, CV_8UC3);
	Main = Display(cv::Rect(hSep, vSep, mainWidth, mainHeight));
	Console = Display(cv::Rect(hSep,vSep*2+mainHeight, consoleWidth, consoleHeight));
	Data = Display(cv::Rect(2*hSep+mainWidth,vSep, dataWidth, dataHeight));
}

void showDisplay::testDisplay()
{
	Display = cv::Scalar_<uchar>(   0,   0,   0 );
	Main    = cv::Scalar_<uchar>(   0,   0,   0 );
	Console = cv::Scalar_<uchar>(  64, 128,   0 );
	Data    = cv::Scalar_<uchar>( 128,  64,   0 );
}

void showDisplay::setMain(cv::Mat &I)
{
	if (I.rows != Main.rows || I.cols != Main.cols)
	{
		std::cerr << "Error in setMain: mismatch size"
	              << std::endl;
	    return;
	}
	//for (int i=0;i<I.rows;++i)
	//	for (int j=0;j<I.cols;++j)
	//		Main.at<cv::Vec3b>(i,j) = I.at<cv::Vec3b>(i,j);
	I.copyTo(Main);//.clone();
}
	