#include "stdafx.h"
#include "AllForTracking.h"

AllForTracking::AllForTracking(CvCapture* pCapture)
{
	//后来添加代码
	largenFrmNum[0] = 1200;
	largenFrmNum[1] = 1450;
	largenFrmNum[2] = 480;
	largenFrmNum[3] = -1;


	numFrames = (int)cvGetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_COUNT);
	fWidth = cvGetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_WIDTH);
	fHeight = cvGetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_HEIGHT);


	finishedLocating = false;
	nFrmNum=0;


	pyr = NULL;
	pHJ = NULL;
	
	memset(charname,0,sizeof(char));
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5f, 0.5f, 0, 1, 8);



	myRect = cvRect(0, 0, 0, 0);


	trackObj.setupImages(fWidth, fHeight);
	trackObj.allfWidth = fWidth;
	trackObj.allfHeight = fHeight;

	for (int k = 0; k < 50; k++){
		trackSet[k].setupImages(fWidth, fHeight);
		trackSet[k].allfWidth = fWidth;
		trackSet[k].allfHeight = fHeight;
	}


}


//AllForTracking::~AllForTracking(void)
//{
//}
