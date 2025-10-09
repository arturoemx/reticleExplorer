#include <reticleExplorer.h>

reticleParams::reticleParams(uint bThr, uint lThr, uint hThr, int CAP, bool L2G, double _rho, double _theta, int _vThr)
{
	brightThr = bThr;
	lowThr = lThr;
	highThr = hThr;
	CannyAppertureSize = CAP;
	L2Gradient = L2G;
	rho  = _rho;
	theta = _theta;
	voteThr = _vThr;
}

reticleParams::reticleParams()
{
	brightThr = 127;
	lowThr = 127;
	highThr = 128;
	CannyAppertureSize = 3;
	L2Gradient = true;
	rho  = 0.25; // one fourth of a pixel.
	theta = M_PI/360; //0.5 degrees
	voteThr = 150;
}

void processImage(reticleParams &prm, cv::Mat I);