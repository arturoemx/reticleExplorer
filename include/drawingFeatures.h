#ifndef __DRAWING_FEATURES__
#define __DRAWING_FEATURES__

#include <geomFeatures.h>
#include <opencv2/opencv.hpp>

enum dFeatureTypes {None=0, image, point, line, circle, marker};

struct drawingFeatures
{
	int thickness;
	int lineType;
	drawingFeatures();
	void setThickness(int t);
	void setLineType(int type);
};

struct dPoint: public gfeat::point2D, public drawingFeatures
{
	dPoint():point2D(){}
	
	dPoint(float _x, float _y, float _w = 1):point2D(_x, _y, _w){}
};

std::ostream &operator<< (std::ostream &s, dPoint &p);

struct dLine: public gfeat::line2D, public drawingFeatures
{
	dLine():line2D(){}
	
	dLine(float _A, float _B, float _C):line2D(_A, _B, _C){}
	
	dLine(float x1, float y1, float x2, float y2):line2D(x1, y1, x2, y2){}
};

std::ostream &operator<< (std::ostream &s, dLine &l);


struct dCircle: public gfeat::circle, public drawingFeatures 
{
	dCircle():circle(){}
	
	dCircle(float _h, float _k, float _r):circle(_h, _k, _r){}
};

std::ostream &operator<< (std::ostream &s, dCircle &c);

#endif