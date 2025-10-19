#ifndef __GEOM_CIRCLE__
#define __GEOM_CIRCLE__

#include <ostream>
#include <opencv2/opencv.hpp>

namespace gfeat
{

	struct circle
	{
		float h, k, r;

		circle();
	
		circle (float _h, float _k, float _r);

		circle (cv::Vec3f &c);
	};


	std::ostream &operator<< (std::ostream &s, circle &l);
}

#endif