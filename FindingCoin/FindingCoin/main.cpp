/**********************
비주얼 컴퓨팅
동전 인식하기
20093326 이의재
***********************/


#include "display.h"
#include "filterling.h"
#include "labeling.h"

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv2\nonfree\nonfree.hpp>
#include <iostream>

void symbolSerch (IplImage *, IplImage *) ;

int main() {

	std ::vector<IplImage *> loadImageVector ;
	loadImageVector = Display ::loadImages (loadImageVector, "./coin/") ;
	
	for (int i = 0 ; i < loadImageVector.size () ; i++) {
		IplImage *copyImage = NULL,
			*grayScaleImage = NULL ;
		
		grayScaleImage = Display ::createBGR2GrayImage  (loadImageVector.at (i), grayScaleImage) ;
		// Histogram Stretching
		//Filterling ::contrastStretching (grayScaleImage, grayScaleImage) ;
		// Noise Erase
		Filterling ::noiseEraser (grayScaleImage, grayScaleImage) ;
		// Thresholding
		//cvAdaptiveThreshold (grayScaleImage, grayScaleImage, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV, 7, 3) ;

		// Copy
		copyImage = Display ::createGray2BGRImage (loadImageVector.at (i), copyImage) ;

		// Symbol Serch
		symbolSerch (copyImage, grayScaleImage) ;

		// print
		Display ::showWindows ("result", copyImage) ;

		cvWaitKey (0) ;

		// release
		cvReleaseImage (&loadImageVector.at (i)) ;
		cvReleaseImage (&copyImage) ;
		cvReleaseImage (&grayScaleImage) ;
	}
	loadImageVector.clear () ;
	loadImageVector.~vector () ;
	cvDestroyAllWindows () ;

	return 0 ;
}

void symbolSerch (IplImage *originImage, IplImage *grayScaleImage) {

	// exception 
	if (!Labeling ::drawSymbol (originImage, grayScaleImage)) return ;

	//Labeling ::symbolFindContours (originImage, grayScaleImage, symbolImage) ;
}