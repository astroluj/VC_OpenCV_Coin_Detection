#ifndef _LABELING_H_
#define _LABELING_H_

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv2\nonfree\nonfree.hpp>

class Labeling {
private :
	 // Quick Sort Compare funcion
	static int compare (const void *A, const void *B) ;
	// Sizes sort
	static void coinSizeSorted (IplImage *orgImage, float **points, int pointSize) ;
public :
	// Symbol Draw
	static bool drawSymbol (IplImage *orgImage, IplImage *grayScalImage) ;
	// Symbol carrie GrayScale
	static void symbolFindContours (IplImage *orgImage, IplImage *grayScaleImage, IplImage *symbolImage) ;
} ;

#endif