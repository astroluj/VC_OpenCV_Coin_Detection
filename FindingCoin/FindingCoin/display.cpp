#include "display.h"

// GrayScale Image create
IplImage *Display ::createBGR2GrayImage  (IplImage *srcImage, IplImage *dstImage) {
	dstImage = cvCreateImage (cvGetSize (srcImage), IPL_DEPTH_8U, 1) ;

	// GrayScaleImage 
	cvCvtColor (srcImage, dstImage, CV_BGR2GRAY) ;
	//cvSmooth (dstImage, dstImage, CV_GAUSSIAN, 7, 7) ;
	//cvCanny (dstImage, dstImage, 10, 30, 3) ;

	return dstImage ;
}

// Symbol Image Create
IplImage *Display ::createGray2BGRImage (IplImage *srcImage, IplImage *dstImage) {
	dstImage = cvCreateImage (cvGetSize (srcImage), IPL_DEPTH_8U, 3) ;

	// SymbolImage
	// Init Black
	cvCopy (srcImage, dstImage) ;

	return dstImage ;
}

// 경로의 모든 이미지 로드
std ::vector<IplImage *> Display ::loadImages (std ::vector<IplImage *> loadImageVector, std ::string folderPath) {
	// Open
	_finddata_t findData ;
	long findHandler = _findfirst ((folderPath + "*.bmp").c_str (), &findData) ;

	// Error
	if (findHandler == EOF) {
		std ::cout << "Thre were no files." << std ::endl ;
		return loadImageVector ;
	}

	// File Name List
	int result = 1 ;
	while (result != EOF) {
		// Load  Images
		loadImageVector.push_back (cvLoadImage ((folderPath + findData.name).c_str ())) ;
		result = _findnext (findHandler, &findData) ;
	}
	// Close
	_findclose (findHandler) ;

	return loadImageVector ;
}

// Windows show
void Display ::showWindows (std ::string windowName, IplImage *srcImage) {
	// print Text
	CvFont font ;
	cvInitFont (&font, CV_FONT_HERSHEY_PLAIN, 1.0f, 1.0f, 1.0f, 2, 8) ;
	cvPutText (srcImage, "Green : 50Won", cvPoint (60, 100), &font, CV_RGB (0, 255, 0)) ;
	cvPutText (srcImage, "Yellow : 10Won", cvPoint (60, 120), &font, CV_RGB (255, 255, 0)) ;
	cvPutText (srcImage, "Purple : 100Won", cvPoint (60, 140), &font, CV_RGB (255, 0, 255,)) ;
	// Show Windows
	cvNamedWindow (windowName.c_str (), CV_WINDOW_AUTOSIZE) ;
	cvShowImage (windowName.c_str (), srcImage) ;
}