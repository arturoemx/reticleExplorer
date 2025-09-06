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
		            uint _hS=H_SEP_SIZE, uint _vS=V_SEP_SIZE)
		{
			width = _w;
			height = _h;
			mainWidth = _mW;
			mainHeight = _mH;
			hSep = _hS;
			vSep = _vS;
			consoleWidth = width - 2 * hSep;
			consoleHeight = height - mainHeight - 3 * vSep;
			dataWidth = width - mainWidth - 3 * hSep;
			dataHeight = mainHeight;

			Display = cv::Mat::zeros(height, width, CV_8UC3);
			Main = Display(cv::Rect(hSep, vSep, mainWidth, mainHeight));
			Console = Display(cv::Rect(hSep,vSep*2+mainHeight, consoleWidth, consoleHeight));
			Data = Display(cv::Rect(2*hSep+mainWidth,vSep, dataWidth, dataHeight));
		}

		void testDisplay()
		{
			Display = cv::Scalar_<uchar>( 255, 255, 255 );
			Main    = cv::Scalar_<uchar>(   0,   0,   0 );
			Console = cv::Scalar_<uchar>(   0,   0,   0 );
			Data    = cv::Scalar_<uchar>( 255,   0, 255 );
		}
	};
}

#endif