
// NewWarningSystemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NewWarningSystem.h"
#include "NewWarningSystemDlg.h"
#include "afxdialogex.h"
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <iostream>
#include <highgui.hpp>
#include "CvvImage.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <memory>

#include "RiverDlg.h"
#include "CheckDlg.h"
#include "VideoPlayer.h"
#include "WarningNoverlDlg.h"
#include "RiverDlg.h"
#include "SettingDlg.h"
#include "AllForTracking.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace cv;
using namespace std;

CEvent start_event2;
volatile int flag2;

DWORD WINAPI NWPlayVideo(LPVOID lpParam);










/**********************************************************/
/*********************CAboutDlg 对话框*******************/
/*********************************************************/


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddWarning();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()









/**********************************************************/
/**************CNewWarningSystemDlg 对话框*****************/
/*********************************************************/

CNewWarningSystemDlg::CNewWarningSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNewWarningSystemDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNewWarningSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNewWarningSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK3, &CNewWarningSystemDlg::OnBnClickedCancelWarning)
	ON_BN_CLICKED(IDOK2, &CNewWarningSystemDlg::OnBnClickedAddWarning)
	ON_COMMAND(ID_MenuV, &CNewWarningSystemDlg::OnMenuv)
	ON_COMMAND(ID_MenuR, &CNewWarningSystemDlg::OnMenur)
	ON_COMMAND(ID_MenuW, &CNewWarningSystemDlg::OnMenuw)
	ON_COMMAND(ID_MenuC, &CNewWarningSystemDlg::OnMenuc)
	ON_COMMAND(ID_MenuA, &CNewWarningSystemDlg::OnMenua)


	ON_COMMAND(ID_MenuP, &CNewWarningSystemDlg::OnMenup)
	ON_BN_CLICKED(IDC_Play, &CNewWarningSystemDlg::OnBnClickedPlay)
	ON_BN_CLICKED(IDC_Stop, &CNewWarningSystemDlg::OnBnClickedStop1)
	ON_BN_CLICKED(IDC_End, &CNewWarningSystemDlg::OnBnClickedEnd2)
	ON_BN_CLICKED(IDC_OpenVideo, &CNewWarningSystemDlg::OnBnClickedOpenvideo)
END_MESSAGE_MAP()


// CNewWarningSystemDlg 消息处理程序

BOOL CNewWarningSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	CButton *RadioButton1 = (CButton*)GetDlgItem(IDC_RADIO1);
	RadioButton1->SetCheck(TRUE);


	//RadioButton1.Checked = true;
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNewWarningSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNewWarningSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CNewWarningSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}










/**********************************************************/
/*************************建立目录代码********************/
/*********************************************************/

void CNewWarningSystemDlg::OnMenuv()
{
	// TODO: 在此添加命令处理程序代码
	//无法打开自身窗口
}


void CNewWarningSystemDlg::OnMenur()
{
	// TODO: 在此添加命令处理程序代码
	RiverDlg * pDlg;
	pDlg = new RiverDlg();
	pDlg->Create(IDD_River);

	pDlg->ShowWindow(SW_SHOW);
	
}



void CNewWarningSystemDlg::OnMenup()
{
	// TODO: 在此添加命令处理程序代码
	VideoPlayer * pDlg;
	pDlg = new VideoPlayer();
	pDlg->Create(IDD_VideoPlayer);
	pDlg->ShowWindow(SW_SHOW);
}


void CNewWarningSystemDlg::OnMenuw()
{
	// TODO: 在此添加命令处理程序代码
	WarningNoverlDlg * pDlg;
	pDlg = new WarningNoverlDlg();
	pDlg->Create(IDD_Warning);
	pDlg->ShowWindow(SW_SHOW);
}


void CNewWarningSystemDlg::OnMenuc()
{
	// TODO: 在此添加命令处理程序代码
	CheckDlg * pDlg;
	pDlg = new CheckDlg();
	pDlg->Create(IDD_Check);
	pDlg->ShowWindow(SW_SHOW);
}


void CNewWarningSystemDlg::OnMenua()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg * pDlg;
	pDlg = new CAboutDlg();
	pDlg->Create(IDD_ABOUTBOX);
	pDlg->ShowWindow(SW_SHOW);
}





















/**********************************************************/
/***********************建立视频播放代码******************/
/*********************************************************/

std::shared_ptr<AllForTracking> forTrack;//为了跟踪
char * vPathreal = NULL; //视频目录
char number;//判断视频的序号


void CNewWarningSystemDlg::OnBnClickedOpenvideo()
{
	// TODO: 在此添加控件通知处理程序代码
	//利用代码打开视频

	vPathreal = NULL;
	CFileDialog dlg(
		TRUE, _T("*.avi"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files (*.avi; *.mp4) |*.avi; *.mp4 | All Files (*.*) |*.*||"), NULL
		);
	// 打开文件对话框的标题名
	dlg.m_ofn.lpstrTitle = _T("Open Video");
	// 判断是否获得
	if( dlg.DoModal() != IDOK )	
		return;
	// 获取路径	
	CString vPath = dlg.GetPathName();			
	// 读取图片、缓存到一个局部变量 ipl 中

	
	
	////字符集问题
	const size_t strsize=(vPath.GetLength()+1)*2; // 宽字符的长度;
	vPathreal= new char[strsize]; //分配空间;
	size_t sz=0;
	wcstombs_s(&sz,vPathreal,strsize,vPath,_TRUNCATE);

	

	number = vPathreal[vPath.GetLength()-5];


	int n=atoi((const char*)vPathreal);

}



/*********************** 点击播放**************************/
//点击播放按钮
//相应线程事件
void CNewWarningSystemDlg::OnBnClickedPlay()
{
//	// TODO: 在此添加控件通知处理程序代码
//	CDC *pDC = GetDlgItem(IDC_Pic1)->GetDC();//根据ID获得窗口指针再获取与该窗口关联的上下文指针
//	HDC hdc= pDC->GetSafeHdc();                      // 获取设备上下文句柄
//	CRect rect;// 矩形类
//	GetDlgItem(IDC_Pic1)->GetClientRect(&rect); //获取box1客户区
//	CvCapture *capture = cvCreateFileCapture ("F:\\Ivelyn\\科研\\研究生科研\\防船撞系统\\防船撞\\Mov.avi");  //读取视频
//	if(capture==NULL) {
//		printf("NO capture");    //读取不成功，则标识
//	};
//
//	CDC *pDC2 = GetDlgItem(IDC_Pic2)->GetDC();//根据ID获得窗口指针再获取与该窗口关联的上下文指针
//	HDC hdc2= pDC2->GetSafeHdc();                      // 获取设备上下文句柄
//	CRect rect2;// 矩形类
//	GetDlgItem(IDC_Pic2)->GetClientRect(&rect2); //获取box1客户区
//	CvCapture *capture2 = cvCreateFileCapture ("F:\\Ivelyn\\科研\\研究生科研\\防船撞系统\\防船撞\\Mov.avi");  //读取视频
//	
//	if(capture2==NULL) {
//		printf("NO capture");    //读取不成功，则标识
//	};
//
//	IplImage *frame,*frame2;
//	while(1){ 
//		frame = cvQueryFrame( capture ); //从摄像头或者文件中抓取并返回一帧
//		CvvImage cimg;
//		cimg.CopyOf(frame,frame->nChannels);
//		cimg.DrawToHDC(hdc,&rect);
//
//		frame2 = cvQueryFrame( capture2 ); //从摄像头或者文件中抓取并返回一帧
//		CvvImage cimg2;
//		cimg.CopyOf(frame2,frame2->nChannels);
//		cimg.DrawToHDC(hdc2,&rect2);
//	}
//	
//	ReleaseDC( pDC );
//	cvReleaseCapture(&capture);
//	ReleaseDC( pDC2 );
//	cvReleaseCapture(&capture2);


	HANDLE hThreadSend;         //创建独立线程发送数据  
    DWORD ThreadSendID;  
  
    start_event2.SetEvent();  
  
    hThreadSend = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)NWPlayVideo, (LPVOID)this, 0, &ThreadSendID);  
    CloseHandle(hThreadSend);  

}


//建立线程相应机制
DWORD WINAPI NWPlayVideo(LPVOID lpParam){  
  
	CNewWarningSystemDlg* pThis = (CNewWarningSystemDlg*)lpParam;  
  
    CvCapture* pCapture;  
    IplImage* pFrame,*pFrame2;  

	//pCapture = cvCreateFileCapture("D:\\WorkSpace\\WorkSpaceVS\\TRY\\MOV_2.avi");  
    
	 flag2 = 0; 
	if(vPathreal == NULL){
		 return -1;
	}
	
	pCapture = cvCreateFileCapture( vPathreal);


    if (pCapture == NULL)  
    {  
        return -1;  
    }  
  
		//if(number == '1')
	//     return;	
	//else if(number == '2')
	//	return;
	//else if(number == '3')
	//	return;

	pThis->BeginSetting(pCapture);

    while (pFrame = pThis->CheckForRaidoButton(pCapture))  
    {  

		//不可以在checkforradiobutton中更改变量 否则会影响下一帧的选取
		//Mat  frameTemp;
		//frameTemp = cvarrToMat(pFrame,true); 
		//pFrame2 = &IplImage ( frameTemp );

        WaitForSingleObject(start_event2, INFINITE);  
        start_event2.SetEvent();  
        if (flag2 == -1)  
        {  
            flag2 = 0;  
            //_endthreadex(0); 
			break;
        }
		
		
		pThis->DisplayFrame(pFrame);

        Sleep(33);  

		pThis->ReleaseSetting(pFrame);
		//pFrame = pThis->CheckForRaidoButton(pCapture);
    }  
  
    cvReleaseCapture(&pCapture);  
	
	flag2 = -1;
}  


//进行播放预处理
void CNewWarningSystemDlg::BeginSetting(CvCapture* pCapture)
{
	//进行定位时候的预处理
	IplImage* pFrame; 

	//原本代码
	//if(IsDlgButtonChecked(IDC_RADIO3)==BST_CHECKED)
	//{
	//	//pFrame = CNewWarningSystemDlg::DoProcess(pCapture);
	//	pFrame = cvQueryFrame(pCapture);
	//	pBkImg = cvCreateImage(cvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U, 1);
	//	pFrImg = cvCreateImage(cvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U, 1);

	//	pBkImg->origin = 0;
	//	pFrImg->origin = 0;

	//	pCannyImg = cvCreateImage(cvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U, 1);
	//	pCannyImg->origin = 0;

	//	pyr = cvCreateImage(cvSize(pFrame->width / 2, pFrame->height / 2), IPL_DEPTH_8U, 1);

	//	pBkMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
	//	pFrMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
	//	pFrameMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);

	//	//转化成单通道图像再处理
	//	cvCvtColor(pFrame, pBkImg, CV_BGR2GRAY);
	//	cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);

	//	cvConvert(pFrImg, pFrameMat);
	//	cvConvert(pFrImg, pFrMat);
	//	cvConvert(pFrImg, pBkMat);
	//}


	if(IsDlgButtonChecked(IDC_RADIO3)==BST_CHECKED)
	{
		forTrack = std::make_shared<AllForTracking>(pCapture);

		//进行定位时候的预处理
		forTrack->nFrmNum++;
		IplImage* pFrame; 

		pFrame = cvQueryFrame(pCapture);

		forTrack->msTrack.pBkImg = cvCreateImage(cvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U, 1);
		forTrack->msTrack.pFrImg = cvCreateImage(cvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U, 1);

		forTrack->msTrack.pBkImg->origin = 0;
		forTrack->msTrack.pFrImg->origin = 0;
		forTrack->msTrack.pBkMat = cvCreateMat(pFrame->width, pFrame->height, CV_32FC1);
		forTrack->msTrack.pFrMat = cvCreateMat(pFrame->width, pFrame->height, CV_32FC1);
		forTrack->msTrack.pFrameMat = cvCreateMat(pFrame->width, pFrame->height, CV_32FC1);

		cvCvtColor(pFrame, forTrack->msTrack.pBkImg, CV_BGR2GRAY);
		cvCvtColor(pFrame, forTrack->msTrack.pFrImg, CV_BGR2GRAY);

		//cvConvert(forTrack->msTrack.pFrImg, forTrack->msTrack.pFrameMat);
		//cvConvert(forTrack->msTrack.pFrImg, forTrack->msTrack.pFrMat);
		//cvConvert(forTrack->msTrack.pFrImg, forTrack->msTrack.pBkMat);

		forTrack->msTrack.p = 0;
		forTrack->msTrack.ncvFindContours = 0;
		forTrack->msTrack.pCannyImg = cvCreateImage(cvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U, 1);
		forTrack->msTrack.pCannyImg->origin = 0;
		forTrack->msTrack.initilizelocation(1,number);//注意引用@！！！！！！！！！！
	
		for (int j = 0; j < forTrack->msTrack.ncvFindContours; j++)
		{
				forTrack->trackSet[j].isTrackingInitialized = false;
		}
	}
}


//根据radiobutton按键选择的不同
//读取不同的Capture
IplImage* CNewWarningSystemDlg::CheckForRaidoButton(CvCapture* pCapture)
{
	//判断是选择的哪个radiobutton按键
	IplImage* pFrame,*pFrame2; 

	pFrame = cvQueryFrame(pCapture);

	if(pFrame){
		if(IsDlgButtonChecked(IDC_RADIO1)==BST_CHECKED)
		
			;
		else if(IsDlgButtonChecked(IDC_RADIO2)==BST_CHECKED)
		{
			//pCapture = cvCreateFileCapture("D:\\WorkSpace\\WorkSpaceVS\\NewWarningSystem\\MOV10677.MPG");
			pFrame=VideoStabilization(pFrame);
		}
		else
		{
			//pFrame = cvQueryFrame(pCapture);
			//pFrame = CNewWarningSystemDlg::BoatPosition(pFrame);

			pFrame = VideoStabilization(pFrame);
			IplImage* Temp = pFrame;
			pFrame = VideoTracking(pFrame);//新添加 以防止出错
			cvReleaseImage(&Temp);
		}
	}
		return pFrame;

}


//显示每帧的视频
void CNewWarningSystemDlg::DisplayFrame(IplImage *img){  
  
    CDC* pDC = GetDlgItem(IDC_Pic1)->GetDC();  //CDC是一个类  
    //GetDlgItem(ID)获取控件窗口对象,GetDC()由窗口对象得到DC,然后可以用来在控件中画图  
    //上一句等价于CWnd* pWin=GetDlgItem(ID);  CDC* pDC=pWin->GetDC();  
  
    HDC hDC = pDC->GetSafeHdc();//HDC是一个句柄     
    CRect rect;  
    CWnd  *pWnd;  
  
    int picWidth;  
    int picHeight;  
  
    pWnd = GetDlgItem(IDC_Pic1);  
    pWnd->GetClientRect(&rect);  
  
    //求图片控件的宽和高  
    picWidth = rect.Width();  
    picHeight = rect.Height();  
  
    IplImage*dst = cvCreateImage(cvSize(picWidth, picHeight), img->depth, img->nChannels);  
    cvResize(img, dst, CV_INTER_LINEAR);  
  
	CDC* pDC2 = GetDlgItem(IDC_Pic2)->GetDC();  //CDC是一个类  
    //GetDlgItem(ID)获取控件窗口对象,GetDC()由窗口对象得到DC,然后可以用来在控件中画图  
    //上一句等价于CWnd* pWin=GetDlgItem(ID);  CDC* pDC=pWin->GetDC();  
  
    HDC hDC2 = pDC2->GetSafeHdc();//HDC是一个句柄     
    CRect rect2;  
    CWnd  *pWnd2;  
  
    int picWidth2;  
    int picHeight2;  
  
    pWnd2 = GetDlgItem(IDC_Pic2);  
    pWnd2->GetClientRect(&rect2);  
  
    //求图片控件的宽和高  
    picWidth2 = rect2.Width();  
    picHeight2 = rect2.Height();  
  
    IplImage*dst2 = cvCreateImage(cvSize(picWidth, picHeight), img->depth, img->nChannels);  
    cvResize(img, dst2, CV_INTER_LINEAR);  
      
    //在控件里显示图片  
    CvvImage cimg;  
    cimg.CopyOf(dst);  
    cimg.DrawToHDC(hDC, &rect);  
    cvReleaseImage(&dst);  
    ReleaseDC(pDC);  
	
	//在控件里显示图片  
    CvvImage cimg2;  
    cimg2.CopyOf(dst2);  
    cimg2.DrawToHDC(hDC2, &rect2);  
    cvReleaseImage(&dst2);  
    ReleaseDC(pDC2);  

}  


//释放杂七杂八的变量
void CNewWarningSystemDlg::ReleaseSetting(IplImage* pFrame)
{
	//进行定位时候的释放处理

	if(IsDlgButtonChecked(IDC_RADIO2)==BST_CHECKED)
	{
		//cvReleaseImage(&pFrImg);
		//cvReleaseImage(&pBkImg);
		//cvReleaseImage(&pCannyImg);
		//cvReleaseImage(&pyr);
		//cvReleaseImage(&pHJ);

		//cvReleaseMat(&pFrameMat);
		//cvReleaseMat(&pFrMat);
		//cvReleaseMat(&pBkMat);
		cvReleaseImage(&pFrame);

		//delete[] pPoint;
		//delete forTrack;
	}

}




/***********************不同的功能实现**************************/

//视频稳像
IplImage* CNewWarningSystemDlg::VideoStabilization(IplImage* pFrame)
{
	//视频稳像代码

	pFrame = stabilition.processImage(pFrame,false,false);
	return pFrame;
}


//视频跟踪
IplImage* CNewWarningSystemDlg::VideoTracking(IplImage* pFrame){
	
	forTrack->nFrmNum++;

	CvPoint ptframe = CvPoint(20, 20);

	char framename[50];
	//sprintf_s(framename, "%d", forTrack->nFrmNum);
	//cvPutText(pFrame, framename, ptframe, &forTrack->font, cvScalar(255, 0, 0));
	//cvPutText(pFrame, "#", CvPoint(10,17), &forTrack->font, cvScalar(255, 0, 0));
	forTrack->msTrack.tractObject = true;
	forTrack->trackObj.copyImage(pFrame);

	int intnumber = int(number - '0');
	int a =forTrack-> largenFrmNum[intnumber-1];


	if (forTrack->msTrack.tractObject && forTrack->nFrmNum<= forTrack-> largenFrmNum[intnumber-1]){
		
		
		for (int j = 0; j < forTrack->msTrack.ncvFindContours; j++){
			forTrack->trackSet[j].copyImage(pFrame);//复制整幅图
			forTrack->trackSet[j].setTrackWindow(forTrack->msTrack.tmpSelection[j]);//需要跟踪的原始窗口，赋值给selection
			forTrack->trackSet[j].convertToHSV();//整幅图转到HSV
			forTrack->trackSet[j].startTrackObject(); 
			forTrack->objectLocations[j] = forTrack->trackSet[j].getTrackWindow();
		}

		
		for (int j = 0; j < forTrack->msTrack.ncvFindContours; j++){
			forTrack->trackObj.drawRectangle(forTrack->objectLocations[j]);
		}

		pFrame = forTrack->trackObj.getTrackedFrame();

	}
	if (forTrack->nFrmNum == forTrack-> largenFrmNum[intnumber-1]+1)
	{//------------------------------注20160730---第1451帧的时候对0号窗位置重新初始化，原来0号窗的船走出了，又进来一艘
		forTrack->trackSet[0].isTrackingInitialized = false ;
		if(intnumber == 1)
			forTrack->msTrack.tmpSelection[0] = CvRect(223,102,35,20);
		else if(intnumber == 2)
			forTrack->msTrack.tmpSelection[0] = CvRect(497,97,58,22);
		else if(intnumber == 3)
			forTrack->msTrack.initilizelocation(2,number);
	}
	if (forTrack->msTrack.tractObject&& forTrack->nFrmNum  >  forTrack-> largenFrmNum[intnumber-1] )//-----------注20160730---第1450帧以后，对所有窗口重新进行camshift跟踪初始化，随后操作不变
	{
		for (int j = 0; j < forTrack->msTrack.ncvFindContours; j++){
			forTrack->trackSet[j].copyImage(pFrame);//复制整幅图
			forTrack->trackSet[j].setTrackWindow(forTrack->msTrack.tmpSelection[j]);//需要跟踪的原始窗口，赋值给selection
			forTrack->trackSet[j].convertToHSV();//整幅图转到HSV
			forTrack->trackSet[j].startTrackObject(); 
			forTrack->objectLocations[j] = forTrack->trackSet[j].getTrackWindow();
		}

		
		for (int j = 0; j < forTrack->msTrack.ncvFindContours; j++){
			forTrack->trackObj.drawRectangle(forTrack->objectLocations[j]);
		}

		pFrame = forTrack->trackObj.getTrackedFrame();
	}


	return pFrame;
}

//原本视频检索
IplImage* CNewWarningSystemDlg::BoatPosition(IplImage* pFrame)
{
//
//
//	cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);
//	cvConvert(pFrImg, pFrameMat);
//
//	//Canny边缘
//	cvCanny(pFrImg, pCannyImg, 100, 120, 3);
//	//当前帧跟背景图相减
//	cvAbsDiff(pFrameMat, pBkMat, pFrMat);
//
//	//二值化前景图
//	cvThreshold(pFrMat, pFrImg, 15, 255.0, CV_THRESH_BINARY);
//
//	//更新背景
//	cvRunningAvg(pFrameMat, pBkMat, 0.005, 0);
//	//将背景转化为图像格式，用以显示
//	cvConvert(pBkMat, pBkImg);
//	cvMul(pFrImg, pCannyImg, pFrImg, 1);
//
//	// 向下采样，去掉噪声
//	cvPyrDown(pFrImg, pyr, 7);//高斯金字塔分解向下采样
//	cvDilate(pyr, pyr, 0, 1);  // 做膨胀操作，消除目标的不连续空洞
//	cvPyrUp(pyr, pFrImg, 7);
//
//	// 找到所有轮廓
//	// Create dynamic structure and sequence.
//	stor = cvCreateMemStorage(0);
//	cont = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint), stor);
//
//	cvFindContours(pFrImg, stor, &cont, sizeof(CvContour),
//	CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
//
//	// 直接使用CONTOUR中的矩形来画轮廓
//	for (; cont; cont = cont->h_next)
//	{
//		CvRect r = ((CvContour*)cont)->rect;
//
//		// 人为剔除干扰
//		if ((r.x + r.width < 200 && r.y > 200) ||
//		(r.x + r.width < 120 && r.y > 180))
//			continue;
//
//		if ((r.y + r.height) < FILTER_LINE)   // 感兴趣区域
//			continue;
//
//		cvLine(pFrame,
//		cvPoint(0, FILTER_LINE), cvPoint(351, FILTER_LINE),
//		CV_RGB(0, 255, 0), 1, CV_AA, 0);
//
//		if (r.height * r.width > CONTOUR_MAX_AERA) // 面积小的方形抛弃掉
//		{
//			cvRectangle(pFrame, cvPoint(r.x, r.y),cvPoint(r.x + r.width, r.y + r.height),CV_RGB(255, 0, 0), 1, CV_AA, 0);
//
//			// 记录航迹
//			pPoint[nPoint].x = r.x + r.width / 2;
//			pPoint[nPoint].y = r.y + r.height / 2;
//			nPoint++;
//		}
//	}
//	// free memory
//	cvReleaseMemStorage(&stor);
//
//	//for (int nP = 0; nP < nPoint; nP++)
//	//{
//	//	cvCircle(pHJ, pPoint[nP], 1, CV_RGB(0, 0, 255), 0, CV_AA, 0);
//	//}
//
	return pFrame;
}













/*********************** 暂停 停止**************************/
//点击暂停按钮
void CNewWarningSystemDlg::OnBnClickedStop1()
{
	// TODO: 在此添加控件通知处理程序代码

	CString buttonText;  
	CButton *StopButton = (CButton*)GetDlgItem(IDC_Stop);
	StopButton->GetWindowTextW(buttonText);
    

	
    if (buttonText.Compare(_T("暂 停"))==0)  
    {  
        start_event2.ResetEvent();  
        StopButton->SetWindowTextW(_T("继 续"));  
  
    }  
    else  
    {  
        start_event2.SetEvent();  
        StopButton->SetWindowText(_T("暂 停"));  
    }  

}


//点击停止按钮
void CNewWarningSystemDlg::OnBnClickedEnd2()
{
	// TODO: 在此添加控件通知处理程序代码
	flag2 = -1;
}







//#define CONTOUR_MAX_AERA 256
//#define FILTER_LINE 100  // 上左为原点
//
//IplImage* pFrImg;
//IplImage* pBkImg;
//CvMat* pFrameMat;
//CvMat* pFrMat;
//CvMat* pBkMat;
//CvPoint * pPoint = new CvPoint[5000];;
//int nPoint;
//IplImage * pCannyImg;
//IplImage * pyr;
//IplImage * pHJ;
//CvMemStorage *stor;CvSeq *cont;
//

//void CNewWarningSystemDlg::Show(IplImage *pFrame)
//{
//	CDC *pDC = GetDlgItem(IDC_Pic1)->GetDC();//根据ID获得窗口指针再获取与该窗口关联的上下文指针
//	HDC hdc= pDC->GetSafeHdc();                      // 获取设备上下文句柄
//	CRect rect;// 矩形类
//	GetDlgItem(IDC_Pic1)->GetClientRect(&rect); //获取box1客户区
//
//	CvvImage cimg;
//	cimg.CopyOf(pFrame,pFrame->nChannels);
//	cimg.DrawToHDC(hdc,&rect);
//}
























/**********************************************************/
/***********************  建立告警机制  ******************/
/*********************************************************/

void CNewWarningSystemDlg::OnBnClickedCancelWarning()
{
	// TODO: 在此添加控件通知处理程序代码
	
	INT_PTR nRes;   
  
    // 显示消息对话框   
    nRes = MessageBox(_T("您确定要解除告警么吗？"), _T("解除告警"), MB_OKCANCEL | MB_ICONQUESTION);   
    // 判断消息对话框返回值。如果为IDCANCEL就return，否则继续向下执行   
    if (IDCANCEL == nRes)   
        return;   
  
    // 将各控件中的数据保存到相应的变量   
    UpdateData(TRUE);   
  
  
    // 根据各变量的值更新相应的控件。和的编辑框会显示m_editSum的值   
    UpdateData(FALSE);   
    // 设置属性对话框为向导对话框   
    //sheet.SetWizardMode(); 
}


void CNewWarningSystemDlg::OnBnClickedAddWarning()
{

	// TODO: 在此添加控件通知处理程序代码
	
	INT_PTR nRes;   
  
    // 显示消息对话框   
    nRes = MessageBox(_T("您确定要手动告警么吗？"), _T("手动告警"), MB_OKCANCEL | MB_ICONQUESTION);   
    // 判断消息对话框返回值。如果为IDCANCEL就return，否则继续向下执行   
    if (IDCANCEL == nRes)   
        return;   
  
    // 将各控件中的数据保存到相应的变量   
    UpdateData(TRUE);   
  
  
    // 根据各变量的值更新相应的控件。和的编辑框会显示m_editSum的值   
    UpdateData(FALSE);   
    // 设置属性对话框为向导对话框   
    //sheet.SetWizardMode(); 
}


