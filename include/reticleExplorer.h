#ifndef __RETICLE_EXPLORER__
#define __RETICLE_EXPLORER__

#include <math.h>
#include <opencv2/opencv.hpp>

struct reticleParams
{
	//Threshold Parameters
	int brightThr;

	//Canny_Parameters
	int lowThr, highThr;
	int CannyAppertureSize;
	bool L2Gradient;

	//Hough Parameters
	double rho;
	double theta;
	int voteThr;

	reticleParams(uint bThr, uint lThr, uint hThr, int CAP, bool L2G, double _rho, double _theta, int _vThr);
	
	reticleParams();
	
};

void processImage(reticleParams &prm, cv::Mat I);

#endif