// VideoPlayer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NewWarningSystem.h"
#include "VideoPlayer.h"
#include "afxdialogex.h"


#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <iostream>
#include <highgui.hpp>
#include "CvvImage.h"
#include <opencv2/opencv.hpp>

#include "NewWarningSystemDlg.h"
#include "RiverDlg.h"
#include "CheckDlg.h"
#include "VideoPlayer.h"
#include "WarningNoverlDlg.h"
#include "RiverDlg.h"
#include "SettingDlg.h"

CEvent start_event;
int flag;

DWORD WINAPI PlayVideo(LPVOID lpParam);

// VideoPlayer �Ի���

IMPLEMENT_DYNAMIC(VideoPlayer, CDialogEx)

VideoPlayer::VideoPlayer(CWnd* pParent /*=NULL*/)
	: CDialogEx(VideoPlayer::IDD, pParent)
{

}

VideoPlayer::~VideoPlayer()
{
}

void VideoPlayer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(VideoPlayer, CDialogEx)
	ON_BN_CLICKED(IDOK, &VideoPlayer::OnBnClickedOk)
	ON_BN_CLICKED(IDSTOP, &VideoPlayer::OnBnClickedStop)
	ON_BN_CLICKED(IDEND, &VideoPlayer::OnBnClickedEnd)
	ON_COMMAND(ID_MenuV, &VideoPlayer::OnMenuv)
	ON_COMMAND(ID_MenuP, &VideoPlayer::OnMenup)
	ON_COMMAND(ID_MenuR, &VideoPlayer::OnMenur)
	ON_COMMAND(ID_MenuW, &VideoPlayer::OnMenuw)
	ON_COMMAND(ID_MenuC, &VideoPlayer::OnMenuc)
END_MESSAGE_MAP()


// VideoPlayer ��Ϣ�������



void VideoPlayer::Display(IplImage *img){  
  
    CDC* pDC = GetDlgItem(IDC_Video)->GetDC();  //CDC��һ����  
    //GetDlgItem(ID)��ȡ�ؼ����ڶ���,GetDC()�ɴ��ڶ���õ�DC,Ȼ����������ڿؼ��л�ͼ  
    //��һ��ȼ���CWnd* pWin=GetDlgItem(ID);  CDC* pDC=pWin->GetDC();  
  
    HDC hDC = pDC->GetSafeHdc();//HDC��һ�����     
    CRect rect;  
    CWnd  *pWnd;  
  
    int picWidth;  
    int picHeight;  
  
    pWnd = GetDlgItem(IDC_Video);  
    pWnd->GetClientRect(&rect);  
  

	
	//CProgressCtrl *myProCtrl2 = (CProgressCtrl *)GetDlgItem(IDC_PROCESS1);


    //��ͼƬ�ؼ��Ŀ�͸�  
    picWidth = rect.Width();  
    picHeight = rect.Height();  
  
    IplImage*dst = cvCreateImage(cvSize(picWidth, picHeight), img->depth, img->nChannels);  
    cvResize(img, dst, CV_INTER_LINEAR);  
  
	
    //�ڿؼ�����ʾͼƬ  
    CvvImage cimg;  
    cimg.CopyOf(dst);  
    cimg.DrawToHDC(hDC, &rect);  
    cvReleaseImage(&dst);  
    ReleaseDC(pDC);  

}  



DWORD WINAPI PlayVideo(LPVOID lpParam){  
  
	VideoPlayer* pThis = (VideoPlayer*)lpParam;  
  
    CvCapture* pCapture;  
    IplImage* pFrame;  
  
    pCapture = cvCreateFileCapture("F:\\Ivelyn\\����\\�о�������\\����ײϵͳ\\����ײ\\Mov.avi");  
  



    if (pCapture == NULL)  
    {  
        return -1;  
    }  
  
    pFrame = cvQueryFrame(pCapture);  
    while (pFrame)  
    {  
        WaitForSingleObject(start_event, INFINITE);  
        start_event.SetEvent();  
        if (flag == -1)  
        {  
            flag = 0;  
            _endthreadex(0);  
        };  

		pThis->Display(pFrame);
	
        Sleep(33);  
        pFrame = cvQueryFrame(pCapture);  
    }  
  
    cvReleaseCapture(&pCapture);  
  
}  

void VideoPlayer::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		  
    HANDLE hThreadSend;         //���������̷߳�������  
    DWORD ThreadSendID;  
  
    start_event.SetEvent();  
  
    hThreadSend = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)PlayVideo, (LPVOID)this, 0, &ThreadSendID);  
    CloseHandle(hThreadSend);  
}


void VideoPlayer::OnBnClickedStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString buttonText;  
	CButton *StopButton = (CButton*)GetDlgItem(IDSTOP);
	StopButton->GetWindowTextW(buttonText);
    

	
    if (buttonText.Compare(_T("�� ͣ"))==0)  
    {  
        start_event.ResetEvent();  
        StopButton->SetWindowTextW(_T("�� ��"));  
  
    }  
    else  
    {  
        start_event.SetEvent();  
        StopButton->SetWindowText(_T("�� ͣ"));  
    }  

}


void VideoPlayer::OnBnClickedEnd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	flag = -1;
}


void VideoPlayer::OnMenuv()
{
	// TODO: �ڴ���������������

	CNewWarningSystemDlg * pDlg;
	pDlg = new CNewWarningSystemDlg();
	pDlg->Create(IDD_Main);
	pDlg->ShowWindow(SW_SHOW);
}


void VideoPlayer::OnMenup()
{
	// TODO: �ڴ���������������
	VideoPlayer * pDlg;
	pDlg = new VideoPlayer();
	pDlg->Create(IDD_VideoPlayer);
	pDlg->ShowWindow(SW_SHOW);
}


void VideoPlayer::OnMenur()
{
	// TODO: �ڴ���������������
	RiverDlg * pDlg;
	pDlg = new RiverDlg();
	pDlg->Create(IDD_River);
	pDlg->ShowWindow(SW_SHOW);
}


void VideoPlayer::OnMenuw()
{
	// TODO: �ڴ���������������
	WarningNoverlDlg * pDlg;
	pDlg = new WarningNoverlDlg();
	pDlg->Create(IDD_Warning);
	pDlg->ShowWindow(SW_SHOW);
}


void VideoPlayer::OnMenuc()
{
	// TODO: �ڴ���������������
	CheckDlg * pDlg;
	pDlg = new CheckDlg();
	pDlg->Create(IDD_Check);
	pDlg->ShowWindow(SW_SHOW);
}
