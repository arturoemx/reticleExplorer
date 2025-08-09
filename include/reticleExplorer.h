#ifndef __RETICLE_EXPLORER__
#define __RETICLE_EXPLORER__

#include <vector>

struct reticleParams
{
	uint brightThr;
	uint lowThr, highThr;
	float gaussStd;
	reticleParams(uint bThr, uint lThr, uint hThr, float gStd)
	{
		brightThr = bThr;
		lowThr = lThr;
		highThr = hThr;
		gaussStd = gStd;
	}
	reticleParams()
	{
		brightThr = 127;
		lowThr = 127;
		highThr = 128;
		gaussStd = 1.0;
	}
};

void processImage(reticleParams &prm, cv::Mat I);

#endif