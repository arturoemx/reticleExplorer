#include <geomFeatures.h>
#include <math.h>

//*************************************
//*************** VEC2D ***************
//*************************************

gfeat::vec2D::vec2D ()
{
	p[0] = p[1] = 0.;
	p[2] =1.;
}

gfeat::vec2D::vec2D (float _x, float _y, float _w)
{
	p[0] = (float)_x;
	p[1] = (float)_y;
	p[2] = (float)_w; 
}

gfeat::vec2D::vec2D (cv::Vec3f &v)
{
	p[0] = v[0];
	p[1] = v[1];
	p[2] = v[2]; 
}

gfeat::vec2D::vec2D (cv::Vec2f &v)
{
	p[0] = v[0];
	p[1] = v[1];
	p[2] = 1.; 
}

gfeat::vec2D::vec2D (vec2D &v)
{
	*this = v;
}

gfeat::vec2D &gfeat::vec2D::operator= (const gfeat::vec2D &v)
{
	p[0] = v.p[0];
	p[1] = v.p[1];
	p[2] = v.p[2];

	return *this;
}

gfeat::vec2D gfeat::vec2D::operator+ (const gfeat::vec2D &v)
{
	gfeat::vec2D vo(p[0]+v.p[0], p[1]+v.p[1], p[2]+v.p[2]);

	return vo;
}

gfeat::vec2D gfeat::vec2D::operator- (const gfeat::vec2D &v)
{
	gfeat::vec2D r(p[0]-v.p[0], p[1]-v.p[1], p[2]-v.p[2]);

	return r;
}

gfeat::vec2D &gfeat::vec2D::operator += (const gfeat::vec2D &v)
{
	p[0] += v.p[0];
	p[1] += v.p[1];
	p[2] += v.p[2];

	return *this;
}

gfeat::vec2D &gfeat::vec2D::operator -= (const gfeat::vec2D &v)
{
	p[0] -= v.p[0];
	p[1] -= v.p[1];
	p[2] -= v.p[2];

	return *this;
}

float gfeat::vec2D::operator[](int idx)
{
	return p[idx];
}

gfeat::vec2D gfeat::vec2D::cross(vec2D &s, vec2D &t)
{
	gfeat::vec2D c;

	c.p[0] = s.p[1] * t.p[2] - s.p[2] * t.p[1];
	c.p[1] = s.p[2] * t.p[0] - s.p[0] * t.p[2],
	c.p[2] = s.p[0] * t.p[1] - s.p[1] * t.p[0];

	return c;
}

void gfeat::vec2D::cross(vec2D &t)
{
	gfeat::vec2D s;

	s.p[0] = p[1] * t.p[2] - p[2] * t.p[1];
	s.p[1] = p[2] * t.p[0] - p[0] * t.p[2],
	s.p[2] = p[0] * t.p[1] - p[1] * t.p[0];

	*this = s;
}

void gfeat::vec2D::norm()
{
	float mag;

	mag = sqrt(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
	if (mag != 0.)
		mag = 1./mag;
	p[0] *= mag;
	p[1] *= mag;
	p[2] *= mag;
}

std::ostream &gfeat::operator<< (std::ostream &s, gfeat::vec2D v)
{
	s << "[" << v.p[0] << ", " << v.p[1] << ", " << v.p[2] << "]";
	return s;
}

//*************************************
//************** POINT2D **************
//*************************************

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
		iw = 1. / std::numeric_limits<double>::infinity();// if the point is at the infinity.
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
		iw = 1. / std::numeric_limits<double>::infinity();// if the point is at the infinity.
		infinity = true; 
	}

	cx = p[0] * iw;
	cy = p[1] * iw;
}

gfeat::point2D::point2D(cv::Vec2f &v):gfeat::vec2D(v)
{
	infinity = false;

	cx = p[0];
	cy = p[1];
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
	cx = p[0] * iw;
	cy = p[1] * iw;
}

std::ostream &gfeat::operator<< (std::ostream &s, gfeat::point2D p)
{
	s << "(" << p.cx << ", " << p.cy;

	if (p.infinity == true)
		s << ",Infinity)";
	else
		s << ")";

	return s;
}

//*************************************
//*************** LINE2D **************
//*************************************

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

gfeat::line2D::line2D(cv::Vec2f &v):gfeat::vec2D(v)
{
	x1 = y1 = x2 = y2 = 0.;
	unbound = true;
}

gfeat::line2D::line2D(cv::Vec3f &v):gfeat::vec2D(v)
{
	x1 = y1 = x2 = y2 = 0.;
	unbound = true;
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

	x1 = p1.p[0]/p1.p[2];
	y1 = p1.p[1]/p1.p[2];
	x2 = p2.p[0]/p2.p[2];
	y2 = p2.p[1]/p2.p[2];
	unbound = false;
}

std::ostream &gfeat::operator<< (std::ostream &s, gfeat::line2D l)
{
	gfeat::vec2D *pl = (gfeat::vec2D *)&l;

	if (l.unbound == false)
		s << "Pt{(" << l.x1 << "," << l.y1 << ")-(" << l.x2 << "," << l.y2
		  << ")|" << sqrt(pow(l.x1-l.x2,2)+pow(l.y1-l.y2,2)) << ":"
      	  << *pl << "}";
	else
		s << "Pt{" << *pl <<"}";
	return s;
}

//*************************************
//*************** CIRCLE **************
//*************************************

gfeat::circle::circle()
{
	h=k=r=0.;
}

gfeat::circle::circle (float _h, float _k, float _r)
{
	h = (float)_h;
	k = (float)_k;
	r = (float)_r;
}

gfeat::circle::circle (cv::Vec3f &c)
{
	h = c[0];
	k = c[1];
	r = c[2];
}

std::ostream &gfeat::operator<< (std::ostream &s, gfeat::circle c)
{
	s << "Circ{(" << c.h << ",  " << c.k << "):" << c.r << "}";
	return s;
}
