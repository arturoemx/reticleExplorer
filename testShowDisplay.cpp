#include <opencv2/opencv.hpp>
#include <showDisplay.h>

using namespace cv;
using namespace shDisp;

int main()
{
	showDisplay D;

	D.testDisplay();

	namedWindow("Display", WINDOW_GUI_EXPANDED);
	imshow("Display", D.Display);

	waitKeyEx(0);

	return 0;
}