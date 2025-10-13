#include <drawingFeatures.h>

drawingFeatures::drawingFeatures()
{
	thickness = 1;
	lineType = cv::LINE_8;
}

void drawingFeatures::setThickness(int t)
{
	thickness = t;
}

void drawingFeatures::setLineType(int type)
{
	lineType = type;
}

std::ostream &operator<< (std::ostream &s, dPoint &p)
{
	s << *((gfeat::point2D *)&p);
	return s;
}

std::ostream &operator<< (std::ostream &s, dLine &l)
{
	s << *((gfeat::line2D *)&l);
	return s;
}

std::ostream &operator<< (std::ostream &s, dCircle &c)
{
	s << *((gfeat::circle *)&c);
	return s;
}