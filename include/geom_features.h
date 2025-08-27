#ifndef __GEOM_FEATURES__
#define __GEOM_FEATURES__

namespace gfeat
{
	enum gFeatureTypes {None=0, image, point, line, circle, marker};

	struct vec2D
	{
		float p[3];

		vec2D ()
		{
			p[0] = p[1] = 0.;
			p[2] =1.;
		}
		template<typename X>
		vec2D (X _x, X _y, X _w = 1)
		{
			p[0] = (float)_x;
			p[1] = (float)_y;
			p[2] = (float)_w; 
		}
		void cross(vec2D &s, vec2D &t)
		{
			p[0] = s.p[1] * t.p[2] - s.p[2] * t.p[1];
			p[1] = s.p[2] * t.p[0] - s.p[0] * t.p[2],
			p[2] = s.p[0] * t.p[1] - s.p[1] * t.p[0];
		}
		void norm()
		{
			float mag;

			mag = sqrt(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
			if (mag != 0.)
				mag = 1./mag;
			p[0] *= mag;
			p[1] *= mag;
			p[2] *= mag;
		}
	};

	/*! struct point2D
	 * 
	 * &\brie stores an homogeneous representation of a 2D point.
	*/
	struct point2D: public vec2D
	{
		float cx, cy;
		point2D():vec2D()
		{
			cx = cy = 0.;
		}
		template<typename X>
		point2D(X _x, X _y, X _w = 1):vec2D(_x, _y, _w)
		{
			float iw = 1./p[2];

			cx = p[0] * iw;
			cy = p[1] * iw;
		}
		void intersect(vec2D &l1, vec2D &l2)
		{
			float iw;

			l1.cross(l1, l2);
			iw = 1./p[2];
			cx = p[0] * iw;
			cy = p[1] * iw;
		}
	};

	/*! struct line2D
	 * 
	 * &\brie stores an homogeneous representation of a 2D point.
	*/
	struct line2D: public vec2D
	{
		float x1, y1, x2, y2; //endpoints
		bool unbound;

		line2D():vec2D()
		{
			x1 = y1 = x2 = y2 = 0.;
			unbound = true;
		}
		template<typename X>
		line2D(X _A, X _B, X _C = 1):vec2D(_A, _B, _C)
		{
			x1 = y1 = x2 = y2 = 0.;
			unbound = true;
		}
		
		template<typename X>
		line2D(X a, X b, X d, X e)
		{
			x1 = (float)a;
			y1 = (float)b;
			x2 = (float)d;
			y2 = (float)e;
			unbound = false;

			p[0] = b - e;
			p[1] = d - a;
			p[2] = a * e - b * d;
			if (p[2] != 0.)
			{
				float s = 1. / p[2];
				p[0] *= s;
				p[1] *= s;
				p[2] = 1;
			}
		}
		
		void join(vec2D &p1, vec2D &p2)
		{
			cross(p1, p2);
			x1 = y1 = x2 = y2 = 0.;
			unbound = true;
		}
	};

	struct circle
	{
		float h, k, r;

		circle()
		{
			h=k=r=0.;
		}
		template <typename X>
		circle (X _h, X _k, X _r)
		{
			h = (float)_h;
			k = (float)_k;
			r = (float)_r;
		}
	};

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

	struct dPoint: public point2D, public drawingFeatures
	{
		dPoint():point2D()
		{
		}
		template <typename X>
		dPoint(X _x, X _y, X _w = 1):point2D(_x, _y, _w)
		{

		}
	};
	struct dLine: public line2D, public drawingFeatures
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
	struct dCircle: public circle, public drawingFeatures 
	{
		dCircle():circle()
		{
		}
		template <typename X>
		dCircle(X _h, X _k, X _r):circle(_h, _k, _r)
		{

		}
	};
}

#endif