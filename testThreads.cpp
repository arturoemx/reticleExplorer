#include <opencv2/opencv.hpp>
#include <drawingFeatures.h>
#include <clipBox.h>
#include <iostream>
#include <bits/stdc++.h>

using namespace cv;
using namespace std;

// Referencia: https://www.geeksforgeeks.org/cpp/multithreading-in-cpp/

// Function to be run by the thread
void func()
{
	int Width = 1024, Height = 768, keyVal;
	Mat D = Mat::zeros(Height, Width, CV_8UC3);
	bool runFlag;

	cout << endl << "Iniciamos el flujo de dibujo." << endl
	     << "Esperamos 4 segundos." << endl;
    cout.flush();
    sleep(4);
    
    namedWindow("Display", WINDOW_GUI_EXPANDED);
	
	imshow("Display", D);
	waitKeyEx(1);
	clipBox cA(0, 0,Width-1,0, Width-1,Height-1,0,Height-1);
	clipBox cB(100,100,500,100,500,500,100,500);

	cv::line(D, Point(100,100), Point(500, 100), Scalar_<uchar> (0,0,255), 3);
	cv::line(D, Point(500,100), Point(500, 500), Scalar_<uchar> (0,0,255), 3);
	cv::line(D, Point(500,500), Point(100, 500), Scalar_<uchar> (0,0,255), 3);
	cv::line(D, Point(100,500), Point(100, 100), Scalar_<uchar> (0,0,255), 3);

	runFlag = true;
	while (runFlag)
	{
		float x1, y1, x2, y2;
		dLine ln;
		gfeat::line2D *gl = &ln;
		dPoint pA1, pA2, pB1, pB2;

		x1 = random() % Width;
		y1 = random() % Height;
		x2 = random() % Width;
		y2 = random() % Height;

		ln = dLine(x1,y1,x2,y2);

		cA.clipLine(*gl, pA1, pA2);
		cB.clipLine(*gl, pB1, pB2);

		cv::line(D, Point((int)rintf(pA1.cx),(int)rintf(pA1.cy)), Point((int)rintf(pA2.cx),(int)rintf(pA2.cy)),
			        Scalar_<uchar> (128,128,0));
		if (cB.clipLine(*gl, pB1, pB2))
			cv::line(D, Point((int)rintf(pB1.cx),(int)rintf(pB1.cy)), Point((int)rintf(pB2.cx),(int)rintf(pB2.cy)),
			        Scalar_<uchar> (255,255,0),2);

		imshow("Display", D);
		
		keyVal = waitKeyEx(30) & 0x000000FF;

		cout.flush();

		if (keyVal == 27)
			runFlag = false;
	}
	cout << endl << "Se terminó el flujo de dibujo."
	     << "Esperamos 4 segundos." << endl;
    cout.flush();
    sleep(4);
}

int main()
{
	// Create a thread that runs 
    // the function func
    thread t(func);
    
    // Main thread waits for 't' to finish
    cout << "waiting for the thread to finish." << endl;
    cout.flush();
    cout << "Antes del Join.";cout.flush();
    t.join();  
    cout << "Despues del Join.";cout.flush();
    cout << "Main thread finished.";
    cout.flush();

	return 0;
}
