
#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <iostream>
#include <vector>
#include <string>
#include <io.h>

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv2\nonfree\nonfree.hpp>

class Display {
public :
	// BGR2Gray Image create
	static IplImage *createBGR2GrayImage  (IplImage *srcImage, IplImage *dstImage) ;
	// Gray2BGR Image Create
	static IplImage *createGray2BGRImage (IplImage *srcImage, IplImage *dstImage) ; 
	// 경로의 모든 이미지 로드
	static std ::vector<IplImage *> loadImages (std ::vector<IplImage *> loadImageVector, std ::string folderPath) ;
	// Windows show
	static void showWindows (std ::string windowName, IplImage *srcImage) ;
} ;

#endif