#ifndef __SHOW_DISPLAY__
#define __SHOW_DISPLAY__

#include <math.h>
#include <opencv2/opencv.hpp>
#include <annotateImage.h>
#include <string>

namespace shDisp
{
	#define H_SEP_SIZE 6
	#define V_SEP_SIZE 6
	#define WIDTH 2304
	#define HEIGHT 1296
	#define MAIN_WIDTH 1920
	#define MAIN_HEIGTH 1080
	
	struct showDisplay
	{
		uint width, height;
		uint hSep, vSep;
		uint mainWidth, mainHeight;
		uint consoleWidth, consoleHeight;
		uint dataWidth, dataHeight;

		cv::Mat Display;
		cv::Mat Main;
		cv::Mat Console;
		cv::Mat Data;

		showDisplay(uint _w=WIDTH, uint _h=HEIGHT,\
		            uint _mW=MAIN_WIDTH, uint _mH=MAIN_HEIGTH,\
		            uint _hS=H_SEP_SIZE, uint _vS=V_SEP_SIZE);
		
		void testDisplay();
		
		void setMain(cv::Mat &I);
	};
}

#endif