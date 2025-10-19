#include <vec2D.h>
#include <math.h>

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