#ifndef __DRAWING_FEATURES__
#define __DRAWING_FEATURES__

#include <geom_features.h>
#include <opencv2/opencv.hpp>

enum dFeatureTypes {None=0, image, point, line, circle, marker};

struct drawingFeatures
{
	int thickness;
	int lineType;
	drawingFeatures()
	{
		thickness = 1;
		lineType = cv::LINE_8;
	}
	void setThickness(int t)
	{
		thickness = t;
	}
	void setLineType(int type)
	{
		lineType = type;
	}
};

struct dPoint: public gfeat::point2D, public drawingFeatures
{
	dPoint():point2D()
	{
	}
	template <typename X>
	dPoint(X _x, X _y, X _w = 1):point2D(_x, _y, _w)
	{

	}
};
struct dLine: public gfeat::line2D, public drawingFeatures
{
	dLine():line2D()
	{
	}
	template <typename X>
	dLine(X _A, X _B, X _C):line2D(_A, _B, _C)
	{
	}
	template <typename X>
	dLine(X x1, X y1, X x2, X y2):line2D(x1, y1, x2, y2)
	{
	}
};
struct dCircle: public gfeat::circle, public drawingFeatures 
{
	dCircle():circle()
	{
	}
	template <typename X>
	dCircle(X _h, X _k, X _r):circle(_h, _k, _r)
	{

	}
};

#endif