#include "BoatTracking.h"
#include "BoatDetecting.h"

#pragma once
class AllForTracking
{
public:
	
	int numFrames;//视频的帧数
	int fWidth;//视频的宽度
	int fHeight;//视频的高度

	CvMemStorage *stor;
	CvSeq *cont;

	bool finishedLocating;
	int nFrmNum;

	IplImage * pyr;
	IplImage * pHJ;
	CvFont font;
	char charname[50];

	BoatDetecting trackObj;    //用来完成相关的对象 最后传值
	BoatDetecting trackSet[50];//用来放置在一帧中有几个框框

	//对应检测的框框
	CvRect myRect ;
	CvRect objectLocations[50];

	BoatTracking msTrack;

	//对应不同的结果的帧数 改变框框
	int largenFrmNum[4];

public:
	AllForTracking(CvCapture* pCapture);
	//~AllForTracking(void);
};
