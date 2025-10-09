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

		featureDescriptor(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));

		void setId(u_int _id);
		void setColor(cv::Scalar_<uchar> C);

	};

	struct imageFeature: public featureDescriptor
	{
		cv::Mat feature;

		imageFeature(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
		
		void set(cv::Mat &I);
		
		void apply(cv::Mat &I);
	};

	struct pointFeature: public featureDescriptor
	{
		dPoint ftre; // feature

		pointFeature(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
		
		void set(dPoint &val);

		void apply(cv::Mat &I);
	};

	struct lineFeature: public featureDescriptor
	{
		dLine ftre;

		lineFeature(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
		
		void set(dLine &val);

		void apply(cv::Mat &I);
	};

	struct circleFeature: public featureDescriptor
	{
		dCircle ftre;

		circleFeature(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
		
		void set(dCircle &val);

		void apply(cv::Mat &I);
	};

	struct markerFeature: public featureDescriptor
	{
		dPoint ftre; // feature
		cv::MarkerTypes mType;
		int mSize;
		
	
		markerFeature(uint val, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255), cv::MarkerTypes mt = cv::MARKER_CROSS);
		
		void setIdType(u_int _id, cv::MarkerTypes mt = cv::MARKER_CROSS);
		
		void set(dPoint &val);
		
		void setMarkerType(cv::MarkerTypes mt);
		
		void setMarkerSize(int ms);
		
		void apply(cv::Mat &I);
	};

	struct featureLayer
	{
		std::string name;
		bool active;
		std::vector<std::shared_ptr<featureDescriptor>> L;
		cv::Mat lyImage;

		featureLayer(std::string nme, int _r, int _c);
		
		void addImageFeature(cv::Mat &I, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
		
		void addPointFeature(dPoint &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
		
		void addLineFeature(dLine &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
		
		void addCircleFeature(dCircle &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
		
		void addMarkerFeature(dPoint &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255), cv::MarkerTypes mt = cv::MARKER_CROSS);
		
		void applyFeatures(cv::Mat &I);
	};

	struct annotation
	{
		int nLayers;
		int rows, cols;
		std::map<std::string,unsigned int> idxMap; 
		std::vector<featureLayer> Features;

		annotation(int r, int c);
				
		void addLayer(std::string name);
		
		void moveLayerUp(std::string name);
		
		void moveLayerDown(std::string name);
		
		void activateLayer(std::string name);
		
		void deactivateLayer(std::string name);
		
		void applyAnnotations(cv::Mat &I);
		
		void addImageFeature(std::string name, cv::Mat &I, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
		
		void addPointFeature(std::string name, dPoint &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
				
		void addLineFeature(std::string name, dLine &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
		
		void addCircleFeature(std::string name, dCircle &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255));
		
		void addMarkerFeature(std::string name, dPoint &val, u_int id, cv::Scalar_<uchar> C = cv::Scalar_<uchar>(255,255,255), cv::MarkerTypes mt = cv::MARKER_CROSS);
	};
}
#endif