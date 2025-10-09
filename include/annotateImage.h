#ifndef __ANNOTATE_IMAGE__
#define __ANNOTATE_IMAGE__

#include <math.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <drawingFeatures.h>

namespace imNote
{
	struct featureDescriptor
	{
		u_int id;
		dFeatureTypes type;
		cv::Vec3b Color;

		featureDescriptor(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		{
			id = val;
			type = None;
			Color[0] = C[0];
			Color[1] = C[1];
			Color[2] = C[2];
		}
		void setId(u_int _id)
		{
			id = _id;
		}
		void setColor(cv::Scalar_<uchar> C)
		{
			Color[0] = C[0];
			Color[1] = C[1];
			Color[2] = C[2];
		}

	};

	struct imageFeature: public featureDescriptor
	{
		cv::Mat feature;

		imageFeature(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255)):featureDescriptor(val, C)
		{
			type = image;
		}
		void set(cv::Mat &I)
		{
			feature = I;
		}
		void apply(cv::Mat &I)
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
		dPoint ftre; // feature

		pointFeature(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255)):featureDescriptor(val, C)
		{
			type = point;
		}
		void set(dPoint &val)
		{
			ftre = val;
		}
		void apply(cv::Mat &I)
		{
			I.at<cv::Vec3b>((int)rintf(ftre.cy), (int)rintf(ftre.cx)) = Color;
		}
	};

	struct lineFeature: public featureDescriptor
	{
		dLine ftre;

		lineFeature(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255)):featureDescriptor(val, C)
		{
			type = line;
		}
		void set(dLine &val)
		{
			ftre = val;
		}
		void apply(cv::Mat &I)
		{
			if (!ftre.unbound)	
				cv::line(I, cv::Point((int)rintf(ftre.x1),(int)rintf(ftre.y1)),
				            cv::Point((int)rintf(ftre.x2),(int)rintf(ftre.y2)),
				            Color, ftre.thickness, ftre.lineType);
			//else to Be Done Case of unbounded line.
		}
	};

	struct circleFeature: public featureDescriptor
	{
		dCircle ftre;

		circleFeature(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255)):featureDescriptor(val, C)
		{
			type = circle;
		}
		void set(dCircle &val)
		{
			ftre = val;
		}
		void apply(cv::Mat &I)
		{
			cv::circle(I, cv::Point((int)rint(ftre.h), (int)rint(ftre.k)), (int)rint(ftre.r), Color, ftre.thickness, ftre.lineType);
		}
	};

	struct markerFeature: public featureDescriptor
	{
		dPoint ftre; // feature
		cv::MarkerTypes mType;
		int mSize;
		
	
		markerFeature(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255), cv::MarkerTypes mt = cv::MARKER_CROSS):featureDescriptor(val, C)
		{
			mType = mt;
			mSize = 20;
			type = marker;
		}
		void setIdType(u_int _id, cv::MarkerTypes mt = cv::MARKER_CROSS)
		{
			id = _id;
			mType = mt;
		}
		void set(dPoint &val)
		{
			ftre = val;
		}
		void setMarkerType(cv::MarkerTypes mt)
		{
			mType = mt;
		}
		void setMarkerSize(int ms)
		{
			mSize = ms;
		}
		void apply(cv::Mat &I)
		{
			cv::drawMarker(I, cv::Point((int)rint(ftre.cx), (int)rint(ftre.cy)), Color, mType, mSize, ftre.thickness, ftre.lineType);
		}
	};

	struct featureLayer
	{
		std::string name;
		bool active;
		std::vector<std::shared_ptr<featureDescriptor>> L;
		cv::Mat lyImage;

		featureLayer(std::string nme, int _r, int _c)
		{	
			name = nme;
			active = false;
			lyImage = cv::Mat::zeros(_r, _c, CV_8UC3);
		}

		void addImageFeature(cv::Mat &I, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		{
			if (I.rows != lyImage.rows || I.cols != lyImage.cols || I.channels() != 1)
			{
				std::cerr << "Error in addImageFeature" << std::endl;
				std::cerr.flush();
				return;
			}
			std::shared_ptr<imageFeature> ptr(new imageFeature(id, C));
			ptr->set(I);
			L.push_back(ptr);
		}


		void addPointFeature(dPoint &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		{
			std::shared_ptr<pointFeature> ptr(new pointFeature(id, C));
			ptr->set(val);
			L.push_back(ptr);
		}

		void addLineFeature(dLine &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		{
			std::shared_ptr<lineFeature> ptr(new lineFeature(id, C));
			ptr->set(val);
			L.push_back(ptr);
		}
		
		void addCircleFeature(dCircle &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		{
			std::shared_ptr<circleFeature> ptr(new circleFeature(id, C));
			ptr->set(val);
			L.push_back(ptr);
		}

		void addMarkerFeature(dPoint &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255), cv::MarkerTypes mt = cv::MARKER_CROSS)
		{
			std::shared_ptr<markerFeature> ptr(new markerFeature(id, C, mt));
			ptr->set(val);
			L.push_back(ptr);
		}

		void applyFeatures(cv::Mat &I)
		{
			featureDescriptor *ptr;
			std::vector<std::shared_ptr<featureDescriptor>>::iterator it, end;

			it = L.begin();
			end = L.end();
			for (; it != end; ++it)
			{
				ptr = it->get();

				switch(ptr->type)
				{
					case image:
							((imageFeature *)ptr)->apply(I);
						break;
					case point:
							((pointFeature *)ptr)->apply(I);
						break;
					case line:
							((lineFeature *)ptr)->apply(I);
						break;
					case circle:
							((circleFeature *)ptr)->apply(I);
						break;	
					case marker:
							((markerFeature *)ptr)->apply(I);
					default:break;
				}
			}
		}
	};

	struct annotation
	{
		int nLayers;
		int rows, cols;
		std::map<std::string,unsigned int> idxMap; 
		std::vector<featureLayer> Features;

		annotation(int r, int c)
		{
			if (r <=0 || c <= 0)
			{
				std::cerr << "Error in annotation constructor." << std::endl;
				std::cerr.flush();
				return;
			}
			rows = r;
			cols = c;
			nLayers = 0;
		}
		
		void addLayer(std::string name)
		{
			unsigned int idx;
			featureLayer ly(name, rows, cols);

			idx = Features.size();
			idxMap[name] = idx;

			ly.active = true;

			Features.push_back(ly);
		}
		void applyAnnotations(cv::Mat &I)
		{
			unsigned int i, N;

			if (I.rows != rows || I.cols != cols || I.channels() != 3)
			{
				std::cerr <<"Error in annotation::applyAnnotation."
				          << std:: endl << "Differente Image size."
				          << std::endl;
				return;
			}

			N = Features.size();
			for (i = 0;i < N; ++i)
				if (Features[i].active == true)
					Features[i].applyFeatures(I);
		}
		void addImageFeature(std::string name, cv::Mat &I, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		{
			unsigned int idx;

			idx = idxMap[name];
			Features[idx].addImageFeature(I, id, C);

		}
		void addPointFeature(std::string name, dPoint &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		{
			unsigned int idx;

			idx = idxMap[name];
			Features[idx].addPointFeature(val, id, C);
		}
		
		void addLineFeature(std::string name, dLine &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		{
			unsigned int idx;

			idx = idxMap[name];
			Features[idx].addLineFeature(val, id, C);
		}

		void addCircleFeature(std::string name, dCircle &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		{
			unsigned int idx;

			idx = idxMap[name];
			Features[idx].addCircleFeature(val, id, C);
		}

		void addMarkerFeature(std::string name, dPoint &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255), cv::MarkerTypes mt = cv::MARKER_CROSS)
		{
			unsigned int idx;

			idx = idxMap[name];
			Features[idx].addMarkerFeature(val, id, C);
		}
	};
}
#endif