#ifndef __GEOM_VEC2D__
#define __GEOM_VEC2D__

#include <ostream>
#include <opencv2/opencv.hpp>

namespace gfeat
{
	struct vec2D
	{
		float p[3];

		vec2D ();
				
		vec2D (float _x, float _y, float _w = 1);

		vec2D (cv::Vec3f &v);

		vec2D (cv::Vec2f &v);

		vec2D (vec2D &v);

		vec2D &operator= (const vec2D &v);

		vec2D operator + (const vec2D &v);

		vec2D operator - (const vec2D &v);

		template <typename X>
		vec2D operator + (X val)
		{
			vec2D vo(p[0]+val, p[1]+val, p[2]+val);

			return vo;
		}

		template <typename X>
		vec2D operator - (X val)
		{
			vec2D vo(p[0]-val, p[1]-val, p[2]-val);

			return vo;
		}

		template <typename X>
		vec2D operator * (X val)
		{
			vec2D vo(p[0]*val, p[1]*val, p[2]*val);

			return vo;
		}

		template <typename X>
		vec2D operator / (X val)
		{
			vec2D vo(p[0]/val, p[1]/val, p[2]/val);

			return vo;
		}

		vec2D &operator += (const vec2D &v);

		vec2D &operator -= (const vec2D &v);

		template <typename X>
		vec2D operator += (X val)
		{
			p[0] += (float)val;
			p[1] += (float)val;
			p[2] += (float)val;

			return *this;
		}

		template <typename X>
		vec2D operator -= (X val)
		{
			p[0] -= (float)val;
			p[1] -= (float)val;
			p[2] -= (float)val;

			return *this;
		}

		template <typename X>
		vec2D operator *= (X val)
		{
			p[0] *= (float)val;
			p[1] *= (float)val;
			p[2] *= (float)val;

			return *this;
		}

		template <typename X>
		vec2D operator /= (X val)
		{
			p[0] /= (float)val;
			p[1] /= (float)val;
			p[2] /= (float)val;

			return *this;
		}

		float operator[](int idx);
		
		vec2D cross(vec2D &s, vec2D &t);

		void cross(vec2D &t);
		
		void norm();
		
	};

	std::ostream &operator<< (std::ostream &s, vec2D v);
}

#endif