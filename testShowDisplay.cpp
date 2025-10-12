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
	uint i;
	int keyVal;
	uint itNo = 0;
	cv::Mat Base;
	showDisplay D;
	bool runFlag;

	Base = imread("images/JaguarUmbralizado.png", IMREAD_GRAYSCALE);
	
	annotations Notes(Base.rows, Base.cols);

	Notes.addLayer("Imagen");
	Notes.addLayer("Puntos");
	Notes.addLayer("Lineas");
	Notes.addLayer("Circulos");
	Notes.addLayer("Marcadores");

	{
		unsigned int idx;

		idx  = Notes.getLayerIdx("Imagen");
		cout << "La capa 'Image' tiene el índice " << idx << endl;
		idx  = Notes.getLayerIdx("Puntos");
		cout << "La capa 'Puntos' tiene el índice " << idx << endl;
		idx  = Notes.getLayerIdx("Lineas");
		cout << "La capa 'Lineas' tiene el índice " << idx << endl;
		idx  = Notes.getLayerIdx("Circulos");
		cout << "La capa 'Circulos' tiene el índice " << idx << endl;
		idx  = Notes.getLayerIdx("Marcadores");
		cout << "La capa 'Marcadores' tiene el índice " << idx << endl;

		try	{idx  = Notes.getLayerIdx("Cuadrados");}
		catch(out_of_range &e) {idx = Notes.Features.size();};
		cout << "La capa 'Cuadrados' tiene el índice " << idx << endl << endl;
	

		for (idx = 0; idx<Notes.Features.size(); ++idx)
		{
			cout << "Notes.Features[" << idx << "].name = "
			     << Notes.Features[idx].name << endl
			     << "idxMap[" << Notes.Features[idx].name << "] = "
			     << Notes.Features[idx].name << endl << endl;
		}

		Notes.moveLayerUp("Lineas");
		Notes.moveLayerDown("Puntos");

		Notes.moveLayerDown("Astros");

		cout << endl << endl;

		for (idx = 0; idx<Notes.Features.size(); ++idx)
		{
			cout << "Notes.Features[" << idx << "].name = "
			     << Notes.Features[idx].name << endl
			     << "idxMap[" << Notes.Features[idx].name << "] = "
			     << Notes.Features[idx].name << endl << endl;
		}

		cout << endl << endl;
	}


	Notes.addImageFeature("Imagen", Base, Scalar_<uchar> (0, 128, 0));
	
	D.testDisplay();
	Notes.applyAnnotations(D.Main);
	namedWindow("Display", WINDOW_GUI_EXPANDED);
	imshow("Display", D.Display);
	waitKeyEx(0);
	

	runFlag = true;
	while (runFlag)
	{
		imshow("Display", D.Display);
		D.Main=Scalar_<uchar>(0,0,0);
		keyVal = waitKeyEx(30) & 0x000000FF;
		switch(keyVal)
		{
			case 27:
				runFlag = false;
				break;
			case 'i':
			case 'I':
				Notes.toggleLayer("Imagen");
				break;
			case 'p':
			case 'P':
				Notes.toggleLayer("Puntos");
				break;
			case 'l':
			case 'L':
				Notes.toggleLayer("Lineas");
				break;
			case 'c':
			case 'C':
				Notes.toggleLayer("Circulos");
				break;
			case 'm':
			case 'M':
				Notes.toggleLayer("Marcadores");
				break;
			case 'z':
			case 'Z':
				Notes.toggleLayer("Zirconias");
				break;
		};
		if (keyVal == 27)
			break;

		for (i=0;i<100;++i)
		{
			float x, y;

			x = random() % D.mainWidth;
			y = random() % D.mainHeight;

			dPoint p(x, y);
			Notes.addPointFeature("Puntos", p, Scalar_<uchar> (255,128,255));
		}

		for (i=0;i<2;++i)
		{	
			float x1, y1, x2, y2;

			x1 = random() % D.mainWidth;
			y1 = random() % D.mainHeight;
			x2 = random() % D.mainWidth;
			y2 = random() % D.mainHeight;
		
			dLine l(x1, y1, x2, y2);
			Notes.addLineFeature("Lineas", l, cv::Scalar_<uchar> (96,0,128));
		}

		for (i=0;i<1;++i)
		{	
			float x, y, r;

			x = random() % D.mainWidth;
			y = random() % D.mainHeight;
			r = random() % 100;
		
			dCircle c(x, y, r);
			Notes.addCircleFeature("Circulos", c, cv::Scalar_<uchar> (0,150,200));
		}

		for (i=0;i<1;++i)
		{	
			float x, y;

			x = random() % D.mainWidth;
			y = random() % D.mainHeight;

			dPoint p(x, y);
			Notes.addMarkerFeature("Marcadores", p, cv::Scalar_<uchar> (146,114,0), cv::MARKER_TRIANGLE_UP);
		}

		Notes.applyAnnotations(D.Main);
				
		cout << "Iteración #" << itNo << endl;
		cout.flush();
		
		itNo++;
	}

	return 0;
}