#include "stdafx.h"
#include "BoatTracking.h"


BoatTracking::BoatTracking(void)
{
	rectCount = 0;
	onProcess = false;
	tractObject = false;
	drawRect = false;
}


BoatTracking::~BoatTracking(void)
{
}



void BoatTracking::setProperties(){
	fHeight = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
	fWidth = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);

	//frame = cvCreateImage(cvSize(fWidth, fHeight), IPL_DEPTH_8U, 3);

}
void BoatTracking::initilizelocation(int times, char number){

	//需要加上判断 判断是哪个视频以初始化成功
	if(times ==1){
		if (number == '1')
		{
			ncvFindContours = 3;
			tmpSelection[0] = CvRect(270, 177, 56, 72);
			tmpSelection[1] = CvRect(238, 103, 52, 20);
			//msTrack.tmpSelection[2] = CvRect(575, 103, 47, 10);
			tmpSelection[2] = CvRect(325, 78, 44, 31);
		}
		else if(number == '2')
		{
			ncvFindContours = 5;
			tmpSelection[0] = CvRect(146, 95, 31, 16);
			tmpSelection[1] = CvRect(219, 98,38, 16);
			tmpSelection[2] = CvRect(287, 116, 45, 30);
			tmpSelection[3] = CvRect(353, 92, 34, 25);
			tmpSelection[4] = CvRect(542, 115, 67, 18);

		}
		else if(number == '3')
		{
			ncvFindContours = 1;
			tmpSelection[0] = CvRect(218, 122, 90, 55);
		}
		else if(number == '4')
		{
			ncvFindContours = 1;
			tmpSelection[0] = CvRect(188, 119, 67, 40);
		}
	}
	else
	{
		if (number == '1')
		{
			ncvFindContours = 3;
			tmpSelection[0] = CvRect(270, 177, 56, 72);
			tmpSelection[1] = CvRect(238, 103, 52, 20);
			//msTrack.tmpSelection[2] = CvRect(575, 103, 47, 10);
			tmpSelection[2] = CvRect(325, 78, 44, 31);
		}
		else if(number == '2')
		{
			ncvFindContours = 3;
			tmpSelection[0] = CvRect(270, 177, 56, 72);
			tmpSelection[1] = CvRect(238, 103, 52, 20);
			tmpSelection[2] = CvRect(325, 78, 44, 31);
		}
		else if(number == '3')
		{
			ncvFindContours = 2;
			tmpSelection[1] = CvRect(276, 100, 78, 30);
		}
		else if(number == '4')
		{
			ncvFindContours = 2;
			tmpSelection[1] = CvRect(276, 100, 78, 30);
		}
	}

}

//void BoatTracking::displayFrames(){
//	cvShowImage("video", frame);
//}
void BoatTracking::displaycanny(){
	cvShowImage("canny", pCannyImg);
}
//void BoatTracking::displayFrames1(){
//	cvShowImage("video1", frame);
//}



void BoatTracking::drawRectangles(IplImage* pFrame){

	CvPoint p1, p2;
	for (int i = 0; i < ncvFindContours; i++)
	{

		p1.x = tmpSelection[i].x;

		p2.x = tmpSelection[i].x + tmpSelection[i].width;

		p1.y = tmpSelection[i].y;

		p2.y = tmpSelection[i].y + tmpSelection[i].height;

		cvRectangle(pFrame, p1, p2, CV_RGB(255, 0, 0), 1, CV_AA, 0);
	}

}