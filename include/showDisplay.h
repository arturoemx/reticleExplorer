#ifndef __SHOW_DISPLAY__
#define __SHOW_DISPLAY__

#include <opencv2/opencv.hpp>
#include <string>
#include <memory>
#include <vector>
#include <geom_features.h>

namespace shDisp
{
	#define H_SEP_SIZE 6
	#define V_SEP_SIZE 6
	#define WIDTH 2304
	#define HEIGHT 1296
	#define MAIN_WIDTH 1920
	#define MAIN_HEIGTH 1080

	struct featureDescriptor
	{
		u_int id;
		gfeat::gFeatureTypes type;
		cv::Vec3b Color;

		featureDescriptor(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		{
			id = val;
			type = gfeat::None;
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
			type = gfeat::image;
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
		gfeat::dPoint ftre; // feature

		pointFeature(uint val):featureDescriptor(val)
		{
			type = gfeat::point;
		}
		void set(gfeat::dPoint &val)
		{
			ftre = val;
		}
		void apply(cv::Mat_<cv::Vec3b> &I)
		{
			cv::circle(I, cv::Point(ftre.cx, ftre.cy), ftre.thickness, 1, ftre.lineType);
		}
	};

	struct lineFeature: public featureDescriptor
	{
		gfeat::dLine ftre;

		lineFeature(uint val):featureDescriptor(val)
		{
			type = gfeat::line;
		}
		void set(gfeat::dLine &val)
		{
			ftre = val;
		}
		void apply(cv::Mat_<cv::Vec3b> &I)
		{
			if (!ftre.unbound)	
				cv::line(I, cv::Point((int)round(ftre.x1),(int)round(ftre.y1)),
				            cv::Point((int)round(ftre.x2),(int)round(ftre.y2)),
				            Color, ftre.thickness, ftre.lineType);
			//else to Be Done Case of unbounded line.
		}
	};

	struct circleFeature: public featureDescriptor
	{
		gfeat::dCircle ftre;

		circleFeature(uint val):featureDescriptor(val)
		{
			type = gfeat::circle;
		}
		void set(gfeat::dCircle &val)
		{
			ftre = val;
		}
		void apply(cv::Mat_<cv::Vec3b> &I)
		{
			
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
		void addFeature(featureDescriptor &fD, gfeat::gFeatureTypes fT, u_int id)
		{
			switch(fT)
			{
				case gfeat::image:
						L.push_back(std::make_shared<imageFeature>(id));
					break;
				case gfeat::point:
						L.push_back(std::make_shared<pointFeature>(id));
					break;
				case gfeat::line:
						L.push_back(std::make_shared<lineFeature>(id));
					break;
				case gfeat::circle:
						L.push_back(std::make_shared<circleFeature>(id));
					break;	
				default:break;
			}
		}
		void applyFeatures(cv::Mat_<cv::Vec3b> &I, cv::Mat_<cv::Vec3b> &O)
		{
			featureDescriptor *ptr;
			std::vector<std::shared_ptr<featureDescriptor>>::iterator it, end;

			O = I.clone();
			it = L.begin();
			end = L.end();
			for (; it != end; ++it)
			{
				ptr = it->get();

				switch(ptr->type)
				{
					case gfeat::image:
							((imageFeature *)ptr)->apply(O);
						break;
					case gfeat::point:
							((pointFeature *)ptr)->apply(O);
						break;
					case gfeat::line:
							((lineFeature *)ptr)->apply(O);
						break;
					case gfeat::circle:
							((circleFeature *)ptr)->apply(O);
						break;	
					default:break;
				}
			}
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