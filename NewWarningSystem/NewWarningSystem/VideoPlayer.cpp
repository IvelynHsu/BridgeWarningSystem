// VideoPlayer.cpp : 实现文件
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

// VideoPlayer 对话框

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


// VideoPlayer 消息处理程序



void VideoPlayer::Display(IplImage *img){  
  
    CDC* pDC = GetDlgItem(IDC_Video)->GetDC();  //CDC是一个类  
    //GetDlgItem(ID)获取控件窗口对象,GetDC()由窗口对象得到DC,然后可以用来在控件中画图  
    //上一句等价于CWnd* pWin=GetDlgItem(ID);  CDC* pDC=pWin->GetDC();  
  
    HDC hDC = pDC->GetSafeHdc();//HDC是一个句柄     
    CRect rect;  
    CWnd  *pWnd;  
  
    int picWidth;  
    int picHeight;  
  
    pWnd = GetDlgItem(IDC_Video);  
    pWnd->GetClientRect(&rect);  
  

	
	//CProgressCtrl *myProCtrl2 = (CProgressCtrl *)GetDlgItem(IDC_PROCESS1);


    //求图片控件的宽和高  
    picWidth = rect.Width();  
    picHeight = rect.Height();  
  
    IplImage*dst = cvCreateImage(cvSize(picWidth, picHeight), img->depth, img->nChannels);  
    cvResize(img, dst, CV_INTER_LINEAR);  
  
	
    //在控件里显示图片  
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
  
    pCapture = cvCreateFileCapture("F:\\Ivelyn\\科研\\研究生科研\\防船撞系统\\防船撞\\Mov.avi");  
  



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
	// TODO: 在此添加控件通知处理程序代码
		  
    HANDLE hThreadSend;         //创建独立线程发送数据  
    DWORD ThreadSendID;  
  
    start_event.SetEvent();  
  
    hThreadSend = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)PlayVideo, (LPVOID)this, 0, &ThreadSendID);  
    CloseHandle(hThreadSend);  
}


void VideoPlayer::OnBnClickedStop()
{
	// TODO: 在此添加控件通知处理程序代码
	CString buttonText;  
	CButton *StopButton = (CButton*)GetDlgItem(IDSTOP);
	StopButton->GetWindowTextW(buttonText);
    

	
    if (buttonText.Compare(_T("暂 停"))==0)  
    {  
        start_event.ResetEvent();  
        StopButton->SetWindowTextW(_T("继 续"));  
  
    }  
    else  
    {  
        start_event.SetEvent();  
        StopButton->SetWindowText(_T("暂 停"));  
    }  

}


void VideoPlayer::OnBnClickedEnd()
{
	// TODO: 在此添加控件通知处理程序代码
	flag = -1;
}


void VideoPlayer::OnMenuv()
{
	// TODO: 在此添加命令处理程序代码

	CNewWarningSystemDlg * pDlg;
	pDlg = new CNewWarningSystemDlg();
	pDlg->Create(IDD_Main);
	pDlg->ShowWindow(SW_SHOW);
}


void VideoPlayer::OnMenup()
{
	// TODO: 在此添加命令处理程序代码
	VideoPlayer * pDlg;
	pDlg = new VideoPlayer();
	pDlg->Create(IDD_VideoPlayer);
	pDlg->ShowWindow(SW_SHOW);
}


void VideoPlayer::OnMenur()
{
	// TODO: 在此添加命令处理程序代码
	RiverDlg * pDlg;
	pDlg = new RiverDlg();
	pDlg->Create(IDD_River);
	pDlg->ShowWindow(SW_SHOW);
}


void VideoPlayer::OnMenuw()
{
	// TODO: 在此添加命令处理程序代码
	WarningNoverlDlg * pDlg;
	pDlg = new WarningNoverlDlg();
	pDlg->Create(IDD_Warning);
	pDlg->ShowWindow(SW_SHOW);
}


void VideoPlayer::OnMenuc()
{
	// TODO: 在此添加命令处理程序代码
	CheckDlg * pDlg;
	pDlg = new CheckDlg();
	pDlg->Create(IDD_Check);
	pDlg->ShowWindow(SW_SHOW);
}
