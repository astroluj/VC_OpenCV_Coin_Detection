
#ifndef _FILTERLING_H_
#define _FILTERLING_H_

#include <string>

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv2\nonfree\nonfree.hpp>

class Filterling {
public :
	// Dilate -> Erode -> Dilate
	static void noiseEraser (IplImage *srcImage, IplImage *dstImage) ;
	// Histogram Contrast Stretching
	static void contrastStretching (IplImage *srcImage, IplImage *dstImage) ;
} ;

#endif