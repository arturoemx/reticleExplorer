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
		vec2D (int _x, int _y, int _w = 1)
		{
			p[0] = _x;
			p[1] = _y;
			p[2] = _w; 
		}
		vec2D (float _x, float _y, float _w = 1)
		{
			p[0] = _x;
			p[1] = _y;
			p[2] = _w;
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
		point2D(int _x, int _y, int _w = 1):vec2D(_x, _y, _w)
		{
			float iw = 1./p[2];

			cx = p[0] * iw;
			cy = p[1] * iw;
		}
		point2D(float _x, float _y, float _w = 1):vec2D(_x, _y, _w)
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
		line2D(int _A, int _B, int _C = 1):vec2D(_A, _B, _C)
		{
			x1 = y1 = x2 = y2 = 0.;
			unbound = true;
		}
		
		line2D(float _A, float _B, float _C = 1):vec2D(_A, _B, _C)
		{
			x1 = y1 = x2 = y2 = 0.;
			unbound = true;
		}
		
		line2D(float a, float b, float d, float e)
		{
			x1 = a;
			y1 = b;
			x2 = d;
			y2 = e;
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
		circle (float _h, float _k, float _r)
		{
			h = _h;
			k = _k;
			r = _r;
		}
		circle (int _h, int _k, int _r)
		{
			h = _h;
			k = _k;
			r = _r;
		}
	};

	struct drawingFeatures
	{
		int thickness;
		int lineType;
		drawingFeatures()
		{
			thickness = 3;
			lineType = cv::LINE_AA;
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
		dPoint(int _x, int _y, int _w = 1):point2D(_x, _y, _w)
		{

		}
		dPoint(float _x, float _y, float _w = 1.):point2D(_x, _y, _w)
		{

		}

	};
	struct dLine: public line2D, public drawingFeatures
	{
		dLine():line2D()
		{
		}
		dLine(float _A, float _B, float _C):line2D(_A, _B, _C)
		{
		}
		dLine(int _A, int _B, int _C):line2D(_A, _B, _C)
		{
		}
	};
	struct dCircle: public circle, public drawingFeatures 
	{
		dCircle():circle()
		{
		}
		dCircle(float _h, float _k, float _r):circle(_h, _k, _r)
		{

		}
	};
}

#endif