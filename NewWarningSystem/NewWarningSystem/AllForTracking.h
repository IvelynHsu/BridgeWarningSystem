#include "BoatTracking.h"
#include "BoatDetecting.h"

#pragma once
class AllForTracking
{
public:
	
	int numFrames;//��Ƶ��֡��
	int fWidth;//��Ƶ�Ŀ��
	int fHeight;//��Ƶ�ĸ߶�

	CvMemStorage *stor;
	CvSeq *cont;

	bool finishedLocating;
	int nFrmNum;

	IplImage * pyr;
	IplImage * pHJ;
	CvFont font;
	char charname[50];

	BoatDetecting trackObj;    //���������صĶ��� ���ֵ
	BoatDetecting trackSet[50];//����������һ֡���м������

	//��Ӧ���Ŀ��
	CvRect myRect ;
	CvRect objectLocations[50];

	BoatTracking msTrack;

	//��Ӧ��ͬ�Ľ����֡�� �ı���
	int largenFrmNum[4];

public:
	AllForTracking(CvCapture* pCapture);
	//~AllForTracking(void);
};
