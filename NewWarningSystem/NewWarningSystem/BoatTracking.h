#include "includefortrct.h"

#pragma once
class BoatTracking
{
public:
	CvCapture *capture;
	//IplImage *frame;
	IplImage * pCannyImg;
	IplImage* pFrImg;
	IplImage* pBkImg;
	CvMat* pFrameMat ;
	CvMat* pFrMat ;
	CvMat* pBkMat ;


	int fHeight;
	int fWidth;
	int ncvFindContours;
	int p;//有交集的方框数量


	// --- status variables ---//
	bool onProcess;
	bool tractObject;
	bool drawRect;


	// --- count variables ---//
	int rectCount;
	static const int maxNumberRect = 100;

	CvRect tmpSelection[10];//[]??

public:
	BoatTracking(void);
	~BoatTracking(void);

	void setCapture(CvCapture *tmpCap);
/*	void displayFrames()*/;
	void displaycanny();
	void setProperties();
	//void displayFrames1();
	void initilizelocation(int times, char number);


	void drawRectangles(IplImage* pFrame);
};

