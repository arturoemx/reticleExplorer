/*  
  	mFrame.h - header file that defines a structure to store an image
	           read from a file with a timestamp.
  
    Copyright (C) 2025  Arturo Espinosa-Romero (arturoemx@gmail.com)
    Facultad de Matemáticas, Universidad Autónoma de Yucatán, México.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef __MFRAME__
#define __MFRAME__

#include <opencv2/opencv.hpp>
#include <string>

struct mFrame
{
		cv::Mat Frame;
		double timeStamp;
		std::string path;
		
		mFrame ()
		{
			timeStamp = 0.;
		}

		mFrame(const std::string &pth, double tmsp)
		{
			path = std::string(pth);
			Frame = cv::imread(path);
			timeStamp = tmsp;
		}

		mFrame (const mFrame &mF)
		{
			Frame = mF.Frame.clone();
			timeStamp = mF.timeStamp;
			path = mF.path;
		}

		mFrame & operator = (const mFrame &mF)
		{
			Frame = mF.Frame.clone();
			timeStamp = mF.timeStamp;
			path = mF.path;
			return *this;
		}
};

#endif
