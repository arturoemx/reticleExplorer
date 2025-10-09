#include <mFrame.h>
#include <opencv2/opencv.hpp>
#include <string>


mFrame::mFrame ()
{
	timeStamp = 0.;
}

mFrame::mFrame(const std::string &pth, double tmsp)
{
	path = std::string(pth);
	Frame = cv::imread(path);
	timeStamp = tmsp;
}

mFrame::mFrame (const mFrame &mF)
{
	Frame = mF.Frame.clone();
	timeStamp = mF.timeStamp;
	path = mF.path;
}

mFrame & mFrame::operator = (const mFrame &mF)
{
	Frame = mF.Frame.clone();
	timeStamp = mF.timeStamp;
	path = mF.path;
	return *this;
}