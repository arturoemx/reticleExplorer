#include <point2D.h>
#include <math.h>

gfeat::point2D::point2D():vec2D()
{
	cx = cy = 0.;
	infinity = false;
}

gfeat::point2D::point2D(float _x, float _y, float _w):gfeat::vec2D(_x, _y, _w)
{
	float iw;

	if (p[2] != 0)
	{
		iw = 1./p[2];
		infinity = true;
	}
	else
	{
		iw = 1e6;// if the point is at the infinity.
		infinity = true; 
	}

	cx = p[0] * iw;
	cy = p[1] * iw;
}

gfeat::point2D::point2D(cv::Vec3f &v):gfeat::vec2D(v)
{
	float iw;

	if (p[2] != 0)
	{
		iw = 1./p[2];
		infinity = true;
	}
	else
	{
		iw = 1e6;// if the point is at the infinity.
		infinity = true; 
	}

	cx = p[0] * iw;
	cy = p[1] * iw;
}

gfeat::point2D::point2D(cv::Vec2f &v):gfeat::vec2D(v)
{
	float iw;

	if (p[2] != 0)
	{
		iw = 1./p[2];
		infinity = true;
	}
	else
	{
		iw = 1./std::numeric_limits<double>::infinity();// if the point is at the infinity.
		infinity = true; 
	}

	cx = p[0] * iw;
	cy = p[1] * iw;
}

void gfeat::point2D::intersect(gfeat::vec2D &l1, gfeat::vec2D &l2)
{
	float iw;
	gfeat::vec2D *q = this;

	*q = cross(l1, l2);
	if (p[2] != 0)
	{
		iw = 1./p[2];
		infinity = false;
	}
	else
	{
		iw = 1./std::numeric_limits<double>::infinity();// if the point is at the infinity.
		infinity = true; 
	}
	cx = p[0]*iw;
	cy = p[1]*iw;
}

std::ostream &gfeat::operator<< (std::ostream &s, gfeat::point2D &p)
{
	s << "(" << p.cx << ", " << p.cy;

	if (p.infinity == true)
		s << ",∞)";
	else
		s << ")";

	return s;
}