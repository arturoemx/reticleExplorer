#include <opencv2/opencv.hpp>
#include <showDisplay.h>
#include <string>

using namespace cv;
using namespace std;
using namespace shDisp;

int main()
{
	showDisplay D;
	paintLayer pL("Puntos");
	uint idx = 0, i;

	D.testDisplay();

	for (i=0;i<1000;++i)
	{
		int x, y;
		x = random() % D.mainWidth;
		y = random() % D.mainHeight;

		gfeat::dPoint p(x,y);

		pL.addPointFeature(idx++, p);
		

	}
	namedWindow("Display", WINDOW_GUI_EXPANDED);
	imshow("Display", D.Display);

	waitKeyEx(0);

	return 0;
}