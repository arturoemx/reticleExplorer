#include <circle.h>
#include <math.h>

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

std::ostream &gfeat::operator<< (std::ostream &s, gfeat::circle &l)
{
	s << "Circ{(" << l.h << ",  " << l.k << "):" << l.r << "}";
	return s;
}
