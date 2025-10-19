#ifndef __GEOM_LINE2D__
#define __GEOM_LINE2D__

#include <ostream>
#include <opencv2/opencv.hpp>
#include <vec2D.h>
#include <point2D.h>

namespace gfeat
{
	/*! struct line2D
	 * 
	 * &\brie stores an homogeneous representation of a 2D point.
	*/
	struct line2D: public vec2D
	{
		float x1, y1, x2, y2; //endpoints
		bool unbound;

		line2D();
		
		line2D(float _A, float _B, float _C = 1);

		line2D(float _x1, float _y1, float _x2, float _y2);

		line2D(cv::Vec3f &v);

		line2D(cv::Vec2f &v);

		line2D(cv::Vec4f &v);
		
		void join(gfeat::vec2D &p1, gfeat::vec2D &p2);
	};

	std::ostream &operator<< (std::ostream &s, line2D &l);
}

#endif