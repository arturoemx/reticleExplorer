#include <opencv2/opencv.hpp>
#include <drawingFeatures.h>
#include <showDisplay.h>
#include <string>

using namespace cv;
using namespace std;
using namespace shDisp;
using namespace imNote;

int main()
{
	uint idx = 0, i;
	int keyVal;
	uint itNo = 0;
	cv::Mat Base;
	showDisplay D;

	Base = imread("images/JaguarUmbralizado.png", IMREAD_GRAYSCALE);
	
	annotation Notes(Base.rows, Base.cols);

	Notes.addLayer("Imagen");
	Notes.addLayer("Puntos");
	Notes.addLayer("Lineas");
	Notes.addLayer("Circulos");
	Notes.addLayer("Marcadores");
	

	Notes.addImageFeature("Imagen", Base, idx++, Scalar_<uchar> (0, 128, 0));
	
	D.testDisplay();
	Notes.applyAnnotations(D.Main);
	namedWindow("Display", WINDOW_GUI_EXPANDED);
	imshow("Display", D.Display);
	waitKeyEx(0);
	

	while (true)
	{
		imshow("Display", D.Display);
		keyVal = waitKeyEx(30) & 0x000000FF;
		if (keyVal == 27)
			break;

		for (i=0;i<100;++i)
		{
			float x, y;

			x = random() % D.mainWidth;
			y = random() % D.mainHeight;

			dPoint p(x, y);
			Notes.addPointFeature("Puntos", p, idx++, Scalar_<uchar> (255,128,255));
		}

		for (i=0;i<2;++i)
		{	
			float x1, y1, x2, y2;

			x1 = random() % D.mainWidth;
			y1 = random() % D.mainHeight;
			x2 = random() % D.mainWidth;
			y2 = random() % D.mainHeight;
		
			dLine l(x1, y1, x2, y2);
			Notes.addLineFeature("Lineas", l, idx++, cv::Scalar_<uchar> (96,0,128));
		}

		for (i=0;i<1;++i)
		{	
			float x, y, r;

			x = random() % D.mainWidth;
			y = random() % D.mainHeight;
			r = random() % 100;
		
			dCircle c(x, y, r);
			Notes.addCircleFeature("Circulos", c, idx++, cv::Scalar_<uchar> (0,150,200));
		}

		for (i=0;i<1;++i)
		{	
			float x, y;

			x = random() % D.mainWidth;
			y = random() % D.mainHeight;

			dPoint p(x, y);
			Notes.addMarkerFeature("Marcadores", p, idx++, cv::Scalar_<uchar> (146,114,0), cv::MARKER_TRIANGLE_UP);
		}

		Notes.applyAnnotations(D.Main);
				
		cout << "Iteración #" << itNo << endl;
		cout.flush();
		
		itNo++;
	}

	return 0;
}