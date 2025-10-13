#ifndef __GEOM_FEATURES__
#define __GEOM_FEATURES__

#include <ostream>

namespace gfeat
{
	struct vec2D
	{
		float p[3];

		vec2D ();
		
		
		vec2D (float _x, float _y, float _w = 1);
		
		void cross(vec2D &s, vec2D &t);
		
		void norm();
		
	};

	std::ostream &operator<< (std::ostream &s, vec2D &v);
	

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

		void intersect(vec2D &l1, vec2D &l2);
	};

	std::ostream &operator<< (std::ostream &s, point2D &p);


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
		
		line2D(float a, float b, float d, float e);
		
		void join(vec2D &p1, vec2D &p2);
	};

	std::ostream &operator<< (std::ostream &s, line2D &l);

	struct circle
	{
		float h, k, r;

		circle();
	
		circle (float _h, float _k, float _r);
	};


	std::ostream &operator<< (std::ostream &s, circle &l);
}

#endif