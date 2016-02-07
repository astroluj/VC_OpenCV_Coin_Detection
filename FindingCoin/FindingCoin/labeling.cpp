#include "labeling.h"

// Symbol Draw
bool Labeling ::drawSymbol (IplImage *orgImage, IplImage *grayScalImage) {
	
	CvMemStorage *symbolStorage = cvCreateMemStorage (0) ;

	try {
		CvSeq *symbolSeq = cvHoughCircles (grayScalImage, symbolStorage, CV_HOUGH_GRADIENT, 2, orgImage ->height / 6, 100, 50, 35, 58) ;

		if (symbolSeq ->total == 0) throw false ;

		// Labell Detection
		// Point Allocation
		float **points = new float*[symbolSeq ->total] ;
		for (size_t i = 0 ; i < symbolSeq ->total ; i++) {
			// round the floats to an int
			points[i] = (float *) cvGetSeqElem (symbolSeq, i) ;
		}
		coinSizeSorted (orgImage, points, symbolSeq ->total) ;

		// Release memory

		delete[] (points) ;
		cvReleaseMemStorage (&symbolStorage) ;

		return true ;
	} catch (const bool exception) {
		cvReleaseMemStorage (&symbolStorage) ;

		return NULL ;
	}
}

int Labeling ::compare (const void *A, const void *B) {
	double *a = (double*)A, *b = (double*)B ;

	return (a[2] > b[2]) ? -1
		: (a[2] == b[2]) ? 0
		: 1 ;
}

// Sizes sort
void Labeling ::coinSizeSorted (IplImage *orgImage, float **points, int pointSize) {

	// quick sorting
	//qsort (points, pointSize, sizeof (points[0]), compare) ;

	for (int i = 0 ; i < pointSize ; i++) {
		for (int j = i + 1 ; j < pointSize ; j++) {
			if (points[i][2] > points[j][2]) {
				float temp[3] ={0,} ;
				// swap
				temp[0] = points[j][0] ;
				temp[1] = points[j][1] ;
				temp[2] = points[j][2] ;

				points[j][0] = points[i][0] ;
				points[j][1] = points[i][1] ;
				points[j][2] = points[i][2] ;

				points[i][0] = temp[0] ;
				points[i][1] = temp[1] ;
				points[i][2] = temp[2] ;
			}
		}
	}
	for (int i = 0 ; i < pointSize ; i++) {
		cv ::Point center (cvRound (points[i][0]), cvRound (points[i][1])) ;
		int radius = cvRound (points[i][2]) ;
		std ::cout << points[i][0] << " "  << points[i][1] << " " << points[i][2] << std ::endl ;
		// Draw the Circle outline
		switch (i) {

		// FIFTY_WON
		case 0 :
			// Circle
			cvCircle (orgImage, center, radius - 1, CV_RGB (0, 255, 0), 3) ;
			// Center
			cvCircle (orgImage, center, 2, CV_RGB (0, 255, 0), 3) ;

			break ;
		// TEN_WON
		case 1:case 2:
			// Circle
			cvCircle (orgImage, center, radius - 1, CV_RGB (255, 255, 0), 3) ;
			// Center
			cvCircle (orgImage, center, 2, CV_RGB (255, 255, 0), 3) ;

			break ;
		// HUNDREDWON
		default :
			// Circle
			cvCircle (orgImage, center, radius - 1, CV_RGB (255, 0, 255), 3) ;
			// Center
			cvCircle (orgImage, center, 2, CV_RGB (255, 0, 255), 3) ;

			break ;
		}
	}
	std ::cout << "===================================\n" ;
	// Coordinate 덮어써짐 방지
	for (int i = 0 ; i < pointSize ; i++) {
		cv ::Point center (cvRound (points[i][0]), cvRound (points[i][1])) ;
		
		CvFont font ;
		cvInitFont (&font, CV_FONT_HERSHEY_PLAIN, 1.0f, 1.0f, 1.0f, 2, 8) ;
		std ::string coordinate = "" ;
		std ::ostringstream convert ;
		// Integer to string
		convert << center.x ;
		coordinate.append (convert.str ()) ;
		coordinate.append (", ") ;
		convert.clear () ;
		convert.str ("") ;
		convert << center.y ;
		coordinate.append (convert.str ()) ;
		
		// print Text
		cvPutText (orgImage, coordinate.c_str (), center, &font, CV_RGB (0, 0, 0)) ;
	}
}

// Symbol carrie GrayScale
void Labeling ::symbolFindContours (IplImage *orgImage, IplImage *grayScaleImage, IplImage *symbolImage) {
	CvMemStorage *symbolStorage = cvCreateMemStorage(0) ;
	CvSeq *symbolSeq = 0 ;

	try {
		// OriginImage Labelling
		//cvCopy (symbolImage, grayScaleImage) ;
		cvCvtColor (symbolImage, grayScaleImage, CV_BGR2GRAY) ;
		if (cvFindContours (
			grayScaleImage,
			symbolStorage,
			&symbolSeq,
			sizeof (CvContour), 
			CV_RETR_LIST,
			CV_CHAIN_APPROX_SIMPLE
			) == 0) throw false ;

		while (symbolSeq != 0) {
			cvDrawContours(
				orgImage,                //외곽선이 그려질 영상
				symbolSeq,              //외곽선 트리의 루트노드
				CV_RGB (rand () & 255, rand () & 255, rand () & 255),      //외부 외곽선의 색상
				CV_RGB (0, 0, 0),      //내부 외곽선의 색상
				-1,                    //외곽선을 그릴때 이동할 깊이
				3					   //선 굵기
			) ; 

			symbolSeq = symbolSeq ->h_next ;
		}

	} catch (const bool exception) {}

	cvReleaseMemStorage (&symbolStorage) ;
}