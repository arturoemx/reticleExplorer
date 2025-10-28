#ifndef __DYNAMIC_DISPLAY__
#define __DYNAMIC_DISPLAY__

#include <math.h>
#include <string>
#include <iostream>
#include <vector>
#include <showDisplay.h>
#include <annotateImage.h>

#ifdef QT
enum KeyCodes {Esc=27, KeyUp=65362, KeyLeft=65361, KeyDown=65364, KeyRight=65363, Key_p=112, Key_P=80};
#endif


//Estas sob cosas que dependen del backend.
//No debieran ir aqui.
//Luego lo arreglo.

struct reticleParams
{
	//Threshold Parameters
	int intensityThr;

	//Canny_Parameters
	int  CannyLowThr, CannyHighThr;
	int  CannyAppertureSize;
	bool CannyL2Gradient;

	//Hough Parameters
	double HoughRho;
	double HoughTheta;
	int    HoughVoteThr;
	int    HoughMinLineLength;
	bool *changeFlag;
	std::string windowName;

	reticleParams(const std::string &WN, uint iThr, uint lThr, uint hThr, int CAP, bool L2G, double _rho, double _theta, int _vThr, int minLL, bool *chF)
	{
		intensityThr = iThr;
		CannyLowThr = lThr;
		CannyHighThr = hThr;
		CannyAppertureSize = CAP;
		CannyL2Gradient = L2G;
		HoughRho  = _rho;
		HoughTheta = _theta;
		HoughVoteThr = _vThr;
		HoughMinLineLength = minLL;
		windowName = WN;
		changeFlag = chF;
		*changeFlag = false;
	}
	
	reticleParams(const std::string &WN, bool *chF)
	{
		intensityThr = 219;
		CannyLowThr = 127;
		CannyHighThr = 128;
		CannyAppertureSize = 5;
		CannyL2Gradient = true;
		HoughRho  = 0.25; // one fourth of a pixel.
		HoughTheta = M_PI/360; //0.5 degrees
		HoughVoteThr = 15;
		HoughMinLineLength = 10;
		windowName = WN;
		changeFlag = chF;
		*changeFlag = false;
	}
};

std::ostream &operator<<(std::ostream &s, reticleParams &p)
{
	s << "Intensity Threshold : " << p.intensityThr << std::endl
	  << "Canny Low Threshold : " << p.CannyLowThr << std::endl
	  << "Canny high Threshold: " << p.CannyHighThr << std::endl
	  << "Canny Apperture Size: " << p.CannyAppertureSize << std::endl
	  << "Canny L2 Gradient   : " << p.CannyL2Gradient << std::endl
	  << "Hough Rho           : " << p.HoughRho << std::endl
	  << "Hough Theta         : " << p.HoughTheta << std::endl
	  << "Hough Vote Threshold: " << p.HoughVoteThr << std::endl
	  << "Hough Min LineLength: " << p.HoughMinLineLength << std::endl << std::endl;

	  return s;
}


//**********************************************************************
//**                            Control Panel                         **
//**********************************************************************



void intensityChange(int pos, void *data)
{
	reticleParams *rP = (reticleParams *)data;
	rP->intensityThr = pos;
	*(rP->changeFlag) =  true;
}

void CannyLowThrChange(int pos, void *data)
{
	reticleParams *rP = (reticleParams *)data;
	rP->CannyLowThr = pos;
	*(rP->changeFlag) =  true;
}

void CannyHighThrChange(int pos, void *data)
{
	reticleParams *rP = (reticleParams *)data;
	rP->CannyHighThr = pos;
	*(rP->changeFlag) =  true;
}

void CannyAppertureSizeChange(int pos, void *data)
{
	reticleParams *rP = (reticleParams *)data;
	rP->CannyAppertureSize = 3 + pos * 2;
	*(rP->changeFlag) =  true;
}

void lauchControls(reticleParams &prms, const std::string &controlWindowName)
{
	intensityChange(219,&prms);
	CannyLowThrChange(127,&prms);
	CannyHighThrChange(128,&prms);
	CannyAppertureSizeChange(1,&prms);
	cv::createTrackbar("Intensity Thr", controlWindowName, &prms.intensityThr, 255, intensityChange, &prms);
	cv::createTrackbar("Canny Low Thr", controlWindowName, &prms.CannyLowThr, 255, CannyLowThrChange, &prms);
	cv::createTrackbar("Canny Low High", controlWindowName, &prms.CannyHighThr, 255, CannyHighThrChange, &prms);
	cv::createTrackbar("Canny Apperture Size", controlWindowName, nullptr, 2, CannyAppertureSizeChange, &prms);
}

struct dynDisplay
{
	shDisp::showDisplay D;
	std::vector <mFrame> Images;
	std::vector<imNote::annotations> Notes;
	bool running;

	dynDisplay(int width, int height)
	{
		int wWidth, wHeight;

		wWidth  = (int)ceil(width*1.2);
		wHeight = (int)ceil(height*1.2);
		running = true;
		D = shDisp::showDisplay(wWidth, wHeight, width, height);
		cv::namedWindow("Display", cv::WINDOW_GUI_EXPANDED);
		cv::namedWindow("Control", cv::WINDOW_GUI_NORMAL);
		
	}

	void addImage(const mFrame &mFrm, u_int idx)
	{
		Images.insert(Images.begin()+idx, mFrm);
        Notes.insert(Notes.begin()+idx, imNote::annotations(Images[idx].Frame.rows, Images[idx].Frame.cols));
	}

	void mainLoop()
	{
		unsigned int idx, idxOld, nImages;
		bool changeFlag;
		reticleParams rPrms("", &changeFlag);
		KeyCodes key;


		idxOld = idx = 0;
		nImages = Images.size();

		D.testDisplay();
		if (nImages > 0)
			D.setMain(Images[idx].Frame);
    	imshow("Display", D.Display);

    	changeFlag = true;
    	lauchControls(rPrms, "Control");
		cv::waitKeyEx(1);

		running = true;
    	do
    	{
    		key = (KeyCodes)(cv::waitKeyEx(30) & 0x0000FFFF);
    	
    		switch (key)
	    	{
	    		case KeyUp:
	    			std::cout << "Retreat"<< std::endl; std::cout.flush();
	    			idxOld = idx;
	    			idx = idx > 0 ? idx-1 : idx;
	    			if (idxOld != idx)
	    				changeFlag = true;
	    			D.setMain(Images[idx].Frame);
	    			imshow("Display", D.Display);
	    			cv::waitKeyEx(1);
	    			break;
	    		case KeyDown:
	    			std::cout << "Advance"<< std::endl; std::cout.flush();
	    			idxOld = idx;
	    			idx = idx < nImages-1 ? idx+1 : idx;
	    			if (idxOld != idx)
	    				changeFlag = true;
	    			D.setMain(Images[idx].Frame);
	    			imshow("Display", D.Display);
	    			cv::waitKeyEx(1);
	    			break;
	    		case Esc:
	    			running = changeFlag = false;
	    			break;
	    		default:
	    			break;
	    	}

	    	//Convierte a tonos de gris.
	    	if (changeFlag)
	    	{
	    		/* 

	    		Esto lo debiera hacer el backend.

	    		std::cout << "rPrms:" << rPrms << std::endl;
	    		std::cout.flush();

	    		Notes[idx].clear();
				cvtColor(Images[idx].Frame, Gray, COLOR_BGR2GRAY);
				processImage(rPrms, Gray, Notes[idx]);
				cvtColor(Gray,dGray,COLOR_GRAY2RGB);
				imwrite("Gray.png", Gray);
				Notes[idx].applyAnnotations(dGray, true);
				D.setMain(dGray);
				cv::imshow("Display", D.Display);
				cv::waitKeyEx(1);

				std::cout << "Gray.channels = " << Gray.channels() << std::endl;
				std::cout << "dGray.channels = " << dGray.channels() << std::endl;
				for (long unsigned int i = 0; i < Notes[idx].Features.size(); ++i)
					std::cout << "FeatureLayer[" << i << "] = " << Notes[idx].Features[i] << std::endl << std::endl
					     <<  "**************************************************"
				         << std::endl << std::endl;
				changeFlag = false;
				*/
			}
	    } while (running);
	}
};

#endif