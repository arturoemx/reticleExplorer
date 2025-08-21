#ifndef __SHOW_DISPLAY__
#define __SHOW_DISPLAY__

#include <opencv2/opencv.hpp>
#include <string>
#include <memory>
#include <vector>
#include <geom_features.h>

using namespace feat;

namespace shDisp
{
	#define H_SEP_SIZE 6
	#define V_SEP_SIZE 6
	#define WIDTH 2304
	#define HEIGHT 1296
	#define MAIN_WIDTH 1920
	#define MAIN_HEIGTH 1080

	enum featureTypes {None=0, image, point, line, circle};

	struct featureDescriptor
	{
		u_int id;
		featureTypes type;
		cv::Vec3b Color;

		featureDescriptor(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		{
			id = val;
			type = None;
			Color[0] = C[0];
			Color[1] = C[1];
			Color[2] = C[2];
		}
	};

	struct imageFeature: public featureDescriptor
	{
		cv::Mat feature;

		imageFeature(uint val):featureDescriptor(val)
		{
			type = image;
		}
		void set(cv::Mat &I)
		{
			feature = I;
		}
		void apply(cv::Mat_<cv::Vec3b> &I)
		{
			cv::Vec3b *apuI, *endI;
			uchar *apuF;
			int i;

			for (i=0; i < I.rows; ++i)
			{
				apuF = feature.ptr<uchar>(i);
				apuI  = I.ptr<cv::Vec3b>(i);
				endI  = apuI + I.cols;
				for (;apuI < endI; ++apuI, ++apuF)
					if (*apuF)
						*apuI = Color;
			}
		}
	};

	struct pointFeature: public featureDescriptor
	{
		dPoint feature;

		pointFeature(uint val):featureDescriptor(val)
		{
			type = point;
		}
		void set(dPoint &val)
		{
			feature = val;
		}
		void apply(cv::Mat_<cv::Vec3b> &I)
		{
			cv::Vec3b *apuI, *endI;

		}
	};

	struct lineFeature: public featureDescriptor
	{
		dLine feature;

		lineFeature(uint val):featureDescriptor(val)
		{
			type = line;
		}
		void set(dLine &val)
		{
			feature = val;
		}
		void apply(cv::Mat_<cv::Vec3b> &I)
		{
			cv::Vec3b *apuI, *endI;

		}
	};

	struct circleFeature: public featureDescriptor
	{
		dCircle feature;

		circleFeature(uint val):featureDescriptor(val)
		{
			type = circle;
		}
		void set(dCircle &val)
		{
			feature = val;
		}
		void apply(cv::Mat_<cv::Vec3b> &I)
		{
			cv::Vec3b *apuI, *endI;
		}
	};

	struct paintLayer
	{
		std::string name;
		bool active;
		std::vector<std::shared_ptr<featureDescriptor>> L;

		paintLayer(std::string &nme)
		{	
			name = nme;
			active = false;
		}
		void addFeature(featureDescriptor &fD, featureTypes fT, u_int id)
		{
			switch(fT)
			{
				case image:
						L.push_back(std::make_shared<imageFeature>(id));
					break;
				case point:
						L.push_back(std::make_shared<pointFeature>(id));
					break;
				case line:
						L.push_back(std::make_shared<lineFeature>(id));
					break;
				case circle:
						L.push_back(std::make_shared<circleFeature>(id));
					break;	
				default:break;
			};
			
		}
	};
	
	struct showDisplay
	{
		uint width, height;
		uint hSep, vSep;
		uint mainWidth, mainHeight;
		uint consoleWidth, consoleHeight;
		uint dataWidth, dataHeight;

		std::vector <paintLayer> pLayers;

		cv::Mat Display;
		cv::Mat Main;
		cv::Mat Console;
		cv::Mat Data;

		showDisplay(uint _w=WIDTH, uint _h=HEIGHT,\
		            uint _mW=MAIN_WIDTH, uint _mH=MAIN_HEIGTH,\
		            uint _hS=H_SEP_SIZE, uint _vS=V_SEP_SIZE)
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

		void testDisplay()
		{
			Display = cv::Scalar_<uchar>(255, 0,   0  );
			Main    = cv::Scalar_<uchar>(0,   255, 0  );
			Console = cv::Scalar_<uchar>(0,   0,   0  );
			Data    = cv::Scalar_<uchar>(255, 0,   255);
		}
	};
}

#endif