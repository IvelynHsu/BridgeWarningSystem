#include "stdafx.h"
#include "BoatDetecting.h"



BoatDetecting::BoatDetecting(void)
{
	smin = 40;//30
	vmin = 10;
	vmax = 256;
	selection = cvRect(0,0,0,0);
	image = 0;
	isTrackingInitialized = false;
}

BoatDetecting::~BoatDetecting(void)
{
	//cvReleaseImage(&image);
	//cvReleaseImage(&hsv);
	//cvReleaseImage(&hue);
	//cvReleaseImage(&mask);
	//cvReleaseImage(&backproject);
}

int BoatDetecting::setupImages(int frameWidth, int frameHeight)
{
	image = cvCreateImage(cvSize(frameWidth, frameHeight), IPL_DEPTH_8U, 3);
	hsv = cvCreateImage(cvSize(frameWidth, frameHeight), IPL_DEPTH_8U, 3);
	hue = cvCreateImage(cvSize(frameWidth, frameHeight), IPL_DEPTH_8U, 1);
	mask = cvCreateImage(cvSize(frameWidth, frameHeight), IPL_DEPTH_8U, 1);
	backproject = cvCreateImage(cvSize(frameWidth, frameHeight), IPL_DEPTH_8U, 1);

	int hdims = 16; float hranges_arr[] = { 0, 180 }; float *hranges = hranges_arr;
	hist = cvCreateHist(1, &hdims, CV_HIST_ARRAY, &hranges, 1);

	return 1;
}


void BoatDetecting::copyImage(IplImage *srcImg)
{
	cvCopy(srcImg, image);
}
void BoatDetecting::initilizeTracking(){
	cvInRangeS(hsv, cvScalar(0, smin, MIN(vmin, vmax), 0), cvScalar(180, 256, MAX(vmin, vmax), 0), mask);
	// 10,256,30
	
	cvSplit(hsv, hue, 0, 0, 0);
	if (!isTrackingInitialized){ // 如果跟踪窗口未初始化
		float max_val = 0.f;		
		cvSetImageROI(hue, selection);
		cvSetImageROI(mask, selection);		
		cvCalcHist(&hue, hist, 0, mask);
		cvGetMinMaxHistValue(hist, 0, &max_val, 0, 0);
		cvConvertScale(hist->bins, hist->bins, max_val ? 255. / max_val : 0., 0);
		cvResetImageROI(hue);
		cvResetImageROI(mask);
		trackWindow = selection;
		isTrackingInitialized = true;

	}

	cvCalcBackProject(&hue, backproject, hist);
	//cvShowImage("Hue Channel",backproject);
	
	cvAnd(backproject, mask, backproject, 0);
	
	cvCamShift(backproject, trackWindow, cvTermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 15, 2), &trackComp, 0);//初始化跟踪窗口以后直接用trackWindow做跟踪，每帧都会更新
	

	//if (trackComp.rect.width<90 && trackComp.rect.y<200){
	//	trackWindow = trackComp.rect;
	//}
	//if (trackComp.rect.y>200)
	//{
	//	trackWindow = trackComp.rect;
	//}
	trackWindow = trackComp.rect;
}
void BoatDetecting::startTrackObject(){
		cvInRangeS(hsv, cvScalar(0, smin, MIN(vmin, vmax), 0), cvScalar(180, 256, MAX(vmin, vmax), 0), mask);
	// 10,256,30
	
	cvSplit(hsv, hue, 0, 0, 0);
	if (!isTrackingInitialized){ // 如果跟踪窗口未初始化
		float max_val = 0.f;		
		cvSetImageROI(hue, selection);
		cvSetImageROI(mask, selection);		
		cvCalcHist(&hue, hist, 0, mask);
		cvGetMinMaxHistValue(hist, 0, &max_val, 0, 0);
		cvConvertScale(hist->bins, hist->bins, max_val ? 255. / max_val : 0., 0);
		cvResetImageROI(hue);
		cvResetImageROI(mask);
		trackWindow = selection;
		isTrackingInitialized = true;

	}

	cvCalcBackProject(&hue, backproject, hist);
	//cvShowImage("Hue Channel",backproject);
	
	cvAnd(backproject, mask, backproject, 0);
	
	//if (trackWindow.x + trackWindow.width/2< allfWidth &&trackWindow.y + trackWindow.height/2< allfHeight &&trackWindow.x>0)
	if (trackWindow.x + trackWindow.width< allfWidth &&trackWindow.y + trackWindow.height< allfHeight &&trackWindow.x>0)
		cvCamShift(backproject, trackWindow, cvTermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 20, 1), &trackComp, 0);//初始化跟踪窗口以后直接用trackWindow做跟踪，每帧都会更新
	

	//if (trackComp.rect.width<90 && trackComp.rect.y<200){
	//	trackWindow = trackComp.rect;
	//}
	//if (trackComp.rect.y>200)
	//{
	//	trackWindow = trackComp.rect;
	//}
	trackWindow = trackComp.rect;
	
}
void BoatDetecting::setTrackWindow(CvRect tmpRect){
	selection = tmpRect;
}
void BoatDetecting::convertToHSV(){
	cvCvtColor(image, hsv, CV_BGR2HSV);
}
IplImage* BoatDetecting::getTrackedFrame(){
	return image;
}
CvRect BoatDetecting::getTrackWindow(){
	return trackWindow;
}
void BoatDetecting::drawRectangle(CvRect objectLocation){
	CvPoint p1, p2;
	
	p1.x = objectLocation.x;
	
	p2.x = objectLocation.x + objectLocation.width;
	
	p1.y = objectLocation.y;
	p2.y = objectLocation.y + objectLocation.height;
	if (objectLocation.x + objectLocation.width<allfWidth&&objectLocation.y + objectLocation.height<allfHeight&&objectLocation.x>0)
		cvRectangle(image, p1, p2, CV_RGB(255, 0, 0), 1, CV_AA, 0);
}