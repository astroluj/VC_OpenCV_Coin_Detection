#include "filterling.h"

// Dilate -> Erode -> Dilate
void Filterling ::noiseEraser (IplImage *srcImage, IplImage *dstImage) {
	int COL =3, ROW = 3, ITERATIONS = 1 ;

	IplConvKernel *elem =cvCreateStructuringElementEx (COL, ROW, 0, 0, CV_SHAPE_RECT, NULL) ;
	//cvMorphologyEx (img, img, NULL, elem, CV_MOP_CLOSE, 1) ; // 닫힘
	cvDilate (srcImage, dstImage, elem, ITERATIONS) ;	// 팽창
	cvErode (dstImage, dstImage, elem, ITERATIONS * 2) ;	//침식
	cvDilate (dstImage, dstImage, elem, ITERATIONS) ;	// 팽창
}

// Histogram Contrast Stretching
void Filterling ::contrastStretching (IplImage *srcImage, IplImage *dstImage) {
	// histogram연산을 위해 사용할 배열메모리를 할당 
	 unsigned int *histogramArray = new unsigned int[256],
		*sumHistogramArray = new unsigned int[256] ;
	memset (histogramArray, 0, sizeof (unsigned int) * 256) ;
	memset (sumHistogramArray, 0, sizeof (unsigned int) * 256) ;

	// 영상의 histogram을 계산 
	for (size_t i = 0 ; i < srcImage ->height ; i++) 
		for (size_t j = 0 ; j < srcImage ->width ; j++) 
			histogramArray[(unsigned int)cvGetReal2D (srcImage, i, j)]++ ;

	// histogram의 정규화된 합을 계산 
	unsigned int sum = 0 ;
	const float SCALE_FACTOR = 128.0f / (float)(srcImage ->height * srcImage ->width) ;

	for (size_t i = 0 ; i < 256 ; i++) {
		sum += histogramArray[i] ;
		sumHistogramArray[i] = (unsigned int)((sum * SCALE_FACTOR) + 0.5) ;
	}

	// LUT로써 sumHistogramArray 배열을 사용하여 영상을 변환 
	for (size_t i = 0 ; i < srcImage ->height ; i++) 
		for (size_t j = 0 ; j < srcImage ->width ; j++) 
			// pixel indexing
			cvSetReal2D (dstImage, i, j, (double) sumHistogramArray[(unsigned int)cvGetReal2D (srcImage, i, j)]) ;

	delete [] (histogramArray) ;
	delete [] (sumHistogramArray) ;
}