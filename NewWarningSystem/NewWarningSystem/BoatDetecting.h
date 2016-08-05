#include "includefortrct.h"
#pragma once
class BoatDetecting
{


public:

	CvRect selection;
	CvRect trackWindow;
	CvBox2D trackBox;
	CvConnectedComp trackComp;


	IplImage *image;
	IplImage *hsv;
	IplImage *hue;
	IplImage *mask;
	IplImage *backproject;


	bool isTrackingInitialized;


	CvHistogram *hist;

	int allfWidth;//视频的宽度
	int allfHeight;//视频的高度
	
	int smin;
	int vmin;
	int vmax;

public:
	BoatDetecting(void);
	~BoatDetecting(void);
	int setupImages(int frameWidth, int frameHeight);
	void copyImage(IplImage *srcImg);
	void initilizeTracking();
	void startTrackObject();
	void setTrackWindow(CvRect tmpRect);
	void convertToHSV();
	IplImage* getTrackedFrame();
	CvRect getTrackWindow();
	void drawRectangle(CvRect objectLocation);



};

