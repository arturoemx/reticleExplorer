#include <line2D.h>
#include <point2D.h>
#include <math.h>

gfeat::line2D::line2D():vec2D()
{
	x1 = y1 = x2 = y2 = 0.;
	unbound = true;
}

gfeat::line2D::line2D(float _A, float _B, float _C ):gfeat::vec2D(_A, _B, _C)
{
	x1 = y1 = x2 = y2 = 0.;
	unbound = true;
}


gfeat::line2D::line2D(cv::Vec3f &v):gfeat::vec2D(v)
{
	x1 = y1 = x2 = y2 = 0.;
	unbound = true;
}

gfeat::line2D::line2D(float _x1, float _y1, float _x2, float _y2)
{
	x1 = (float)_x1;
	y1 = (float)_y1;
	x2 = (float)_x2;
	y2 = (float)_y2;
	unbound = false;

	p[0] = y1 - y2;
	p[1] = x2 - x1;
	p[2] = x1 * y2 - y1 * x2;
	if (p[2] != 0.)
	{
		float s = 1. / p[2];
		p[0] *= s;
		p[1] *= s;
		p[2] = 1;
	}
}

gfeat::line2D::line2D(cv::Vec4f &v)
{
	x1 = v[0];
	y1 = v[1];
	x2 = v[2];
	y2 = v[3];
	unbound = false;

	p[0] = y1 - y2;
	p[1] = x2 - x1;
	p[2] = x1 * y2 - y1 * x2;
	if (p[2] != 0.)
	{
		float s = 1. / p[2];
		p[0] *= s;
		p[1] *= s;
		p[2] = 1;
	}
}

void gfeat::line2D::join(gfeat::vec2D &p1, gfeat::vec2D &p2)
{
	gfeat::vec2D *q = this;

	*q = cross(p1, p2);

	x1 = p1.p[0]/p1[2];
	y1 = p1.p[1]/p1[2];
	x1 = p2.p[0]/p2[2];
	y1 = p2.p[1]/p2[2];
	unbound = false;
}

std::ostream &gfeat::operator<< (std::ostream &s, gfeat::line2D &l)
{
	gfeat::vec2D *pl = (gfeat::vec2D *)&l;

	if (l.unbound == false)
		s << "Pt{(" << l.x1 << "," << l.y1 << ")-(" << l.x2 << "," << l.y2
		  << "|" << sqrt(pow(l.x1-l.x2,2)+pow(l.y1-l.y2,2)) << "):"
      	  << *pl << "}";
	else
		s << "Pt{" << *pl <<"}";
	return s;
}
