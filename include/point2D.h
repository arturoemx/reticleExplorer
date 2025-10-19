#ifndef __GEOM_POINT2D__
#define __GEOM_POINT2D__

#include <ostream>
#include <opencv2/opencv.hpp>
#include <vec2D.h>

namespace gfeat
{
	/*! struct point2D
	 * 
	 * &\brie stores an homogeneous representation of a 2D point.
	*/
	struct point2D: public vec2D
	{
		float cx, cy;
		bool infinity;

		point2D();

		point2D(float _x, float _y, float _w = 1);

		point2D(cv::Vec3f &v);

		point2D(cv::Vec2f &v);

		void intersect(vec2D &l1, vec2D &l2);
	};

	std::ostream &operator<< (std::ostream &s, point2D &p);
}

#endif