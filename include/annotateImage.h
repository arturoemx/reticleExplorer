#ifndef __ANNOTATE_IMAGE__
#define __ANNOTATE_IMAGW__

#include <math.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <memory>
#include <vector>
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

		featureLayer(std::string nme)
		{	
			name = nme;
			active = false;
		}

		void addImageFeature(cv::Mat &I, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255))
		{
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

/*
	struct annotation
	{
		int nLayers;
		vector<Mat_<cv::Vec3b>> annoteLayer;
		vector<featureLayer> Features;
	};
}
#endif