
// NewWarningSystemDlg.cpp : ʵ���ļ�
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
/*********************CAboutDlg �Ի���*******************/
/*********************************************************/


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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
/**************CNewWarningSystemDlg �Ի���*****************/
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


// CNewWarningSystemDlg ��Ϣ�������

BOOL CNewWarningSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	CButton *RadioButton1 = (CButton*)GetDlgItem(IDC_RADIO1);
	RadioButton1->SetCheck(TRUE);


	//RadioButton1.Checked = true;
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CNewWarningSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CNewWarningSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}










/**********************************************************/
/*************************����Ŀ¼����********************/
/*********************************************************/

void CNewWarningSystemDlg::OnMenuv()
{
	// TODO: �ڴ���������������
	//�޷���������
}


void CNewWarningSystemDlg::OnMenur()
{
	// TODO: �ڴ���������������
	RiverDlg * pDlg;
	pDlg = new RiverDlg();
	pDlg->Create(IDD_River);

	pDlg->ShowWindow(SW_SHOW);
	
}



void CNewWarningSystemDlg::OnMenup()
{
	// TODO: �ڴ���������������
	VideoPlayer * pDlg;
	pDlg = new VideoPlayer();
	pDlg->Create(IDD_VideoPlayer);
	pDlg->ShowWindow(SW_SHOW);
}


void CNewWarningSystemDlg::OnMenuw()
{
	// TODO: �ڴ���������������
	WarningNoverlDlg * pDlg;
	pDlg = new WarningNoverlDlg();
	pDlg->Create(IDD_Warning);
	pDlg->ShowWindow(SW_SHOW);
}


void CNewWarningSystemDlg::OnMenuc()
{
	// TODO: �ڴ���������������
	CheckDlg * pDlg;
	pDlg = new CheckDlg();
	pDlg->Create(IDD_Check);
	pDlg->ShowWindow(SW_SHOW);
}


void CNewWarningSystemDlg::OnMenua()
{
	// TODO: �ڴ���������������
	CAboutDlg * pDlg;
	pDlg = new CAboutDlg();
	pDlg->Create(IDD_ABOUTBOX);
	pDlg->ShowWindow(SW_SHOW);
}





















/**********************************************************/
/***********************������Ƶ���Ŵ���******************/
/*********************************************************/

std::shared_ptr<AllForTracking> forTrack;//Ϊ�˸���
char * vPathreal = NULL; //��ƵĿ¼
char number;//�ж���Ƶ�����


void CNewWarningSystemDlg::OnBnClickedOpenvideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//���ô������Ƶ

	vPathreal = NULL;
	CFileDialog dlg(
		TRUE, _T("*.avi"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files (*.avi; *.mp4) |*.avi; *.mp4 | All Files (*.*) |*.*||"), NULL
		);
	// ���ļ��Ի���ı�����
	dlg.m_ofn.lpstrTitle = _T("Open Video");
	// �ж��Ƿ���
	if( dlg.DoModal() != IDOK )	
		return;
	// ��ȡ·��	
	CString vPath = dlg.GetPathName();			
	// ��ȡͼƬ�����浽һ���ֲ����� ipl ��

	
	
	////�ַ�������
	const size_t strsize=(vPath.GetLength()+1)*2; // ���ַ��ĳ���;
	vPathreal= new char[strsize]; //����ռ�;
	size_t sz=0;
	wcstombs_s(&sz,vPathreal,strsize,vPath,_TRUNCATE);

	

	number = vPathreal[vPath.GetLength()-5];


	int n=atoi((const char*)vPathreal);

}



/*********************** �������**************************/
//������Ű�ť
//��Ӧ�߳��¼�
void CNewWarningSystemDlg::OnBnClickedPlay()
{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CDC *pDC = GetDlgItem(IDC_Pic1)->GetDC();//����ID��ô���ָ���ٻ�ȡ��ô��ڹ�����������ָ��
//	HDC hdc= pDC->GetSafeHdc();                      // ��ȡ�豸�����ľ��
//	CRect rect;// ������
//	GetDlgItem(IDC_Pic1)->GetClientRect(&rect); //��ȡbox1�ͻ���
//	CvCapture *capture = cvCreateFileCapture ("F:\\Ivelyn\\����\\�о�������\\����ײϵͳ\\����ײ\\Mov.avi");  //��ȡ��Ƶ
//	if(capture==NULL) {
//		printf("NO capture");    //��ȡ���ɹ������ʶ
//	};
//
//	CDC *pDC2 = GetDlgItem(IDC_Pic2)->GetDC();//����ID��ô���ָ���ٻ�ȡ��ô��ڹ�����������ָ��
//	HDC hdc2= pDC2->GetSafeHdc();                      // ��ȡ�豸�����ľ��
//	CRect rect2;// ������
//	GetDlgItem(IDC_Pic2)->GetClientRect(&rect2); //��ȡbox1�ͻ���
//	CvCapture *capture2 = cvCreateFileCapture ("F:\\Ivelyn\\����\\�о�������\\����ײϵͳ\\����ײ\\Mov.avi");  //��ȡ��Ƶ
//	
//	if(capture2==NULL) {
//		printf("NO capture");    //��ȡ���ɹ������ʶ
//	};
//
//	IplImage *frame,*frame2;
//	while(1){ 
//		frame = cvQueryFrame( capture ); //������ͷ�����ļ���ץȡ������һ֡
//		CvvImage cimg;
//		cimg.CopyOf(frame,frame->nChannels);
//		cimg.DrawToHDC(hdc,&rect);
//
//		frame2 = cvQueryFrame( capture2 ); //������ͷ�����ļ���ץȡ������һ֡
//		CvvImage cimg2;
//		cimg.CopyOf(frame2,frame2->nChannels);
//		cimg.DrawToHDC(hdc2,&rect2);
//	}
//	
//	ReleaseDC( pDC );
//	cvReleaseCapture(&capture);
//	ReleaseDC( pDC2 );
//	cvReleaseCapture(&capture2);


	HANDLE hThreadSend;         //���������̷߳�������  
    DWORD ThreadSendID;  
  
    start_event2.SetEvent();  
  
    hThreadSend = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)NWPlayVideo, (LPVOID)this, 0, &ThreadSendID);  
    CloseHandle(hThreadSend);  

}


//�����߳���Ӧ����
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

		//��������checkforradiobutton�и��ı��� �����Ӱ����һ֡��ѡȡ
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


//���в���Ԥ����
void CNewWarningSystemDlg::BeginSetting(CvCapture* pCapture)
{
	//���ж�λʱ���Ԥ����
	IplImage* pFrame; 

	//ԭ������
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

	//	//ת���ɵ�ͨ��ͼ���ٴ���
	//	cvCvtColor(pFrame, pBkImg, CV_BGR2GRAY);
	//	cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);

	//	cvConvert(pFrImg, pFrameMat);
	//	cvConvert(pFrImg, pFrMat);
	//	cvConvert(pFrImg, pBkMat);
	//}


	if(IsDlgButtonChecked(IDC_RADIO3)==BST_CHECKED)
	{
		forTrack = std::make_shared<AllForTracking>(pCapture);

		//���ж�λʱ���Ԥ����
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
		forTrack->msTrack.initilizelocation(1,number);//ע������@��������������������
	
		for (int j = 0; j < forTrack->msTrack.ncvFindContours; j++)
		{
				forTrack->trackSet[j].isTrackingInitialized = false;
		}
	}
}


//����radiobutton����ѡ��Ĳ�ͬ
//��ȡ��ͬ��Capture
IplImage* CNewWarningSystemDlg::CheckForRaidoButton(CvCapture* pCapture)
{
	//�ж���ѡ����ĸ�radiobutton����
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
			pFrame = VideoTracking(pFrame);//����� �Է�ֹ����
			cvReleaseImage(&Temp);
		}
	}
		return pFrame;

}


//��ʾÿ֡����Ƶ
void CNewWarningSystemDlg::DisplayFrame(IplImage *img){  
  
    CDC* pDC = GetDlgItem(IDC_Pic1)->GetDC();  //CDC��һ����  
    //GetDlgItem(ID)��ȡ�ؼ����ڶ���,GetDC()�ɴ��ڶ���õ�DC,Ȼ����������ڿؼ��л�ͼ  
    //��һ��ȼ���CWnd* pWin=GetDlgItem(ID);  CDC* pDC=pWin->GetDC();  
  
    HDC hDC = pDC->GetSafeHdc();//HDC��һ�����     
    CRect rect;  
    CWnd  *pWnd;  
  
    int picWidth;  
    int picHeight;  
  
    pWnd = GetDlgItem(IDC_Pic1);  
    pWnd->GetClientRect(&rect);  
  
    //��ͼƬ�ؼ��Ŀ�͸�  
    picWidth = rect.Width();  
    picHeight = rect.Height();  
  
    IplImage*dst = cvCreateImage(cvSize(picWidth, picHeight), img->depth, img->nChannels);  
    cvResize(img, dst, CV_INTER_LINEAR);  
  
	CDC* pDC2 = GetDlgItem(IDC_Pic2)->GetDC();  //CDC��һ����  
    //GetDlgItem(ID)��ȡ�ؼ����ڶ���,GetDC()�ɴ��ڶ���õ�DC,Ȼ����������ڿؼ��л�ͼ  
    //��һ��ȼ���CWnd* pWin=GetDlgItem(ID);  CDC* pDC=pWin->GetDC();  
  
    HDC hDC2 = pDC2->GetSafeHdc();//HDC��һ�����     
    CRect rect2;  
    CWnd  *pWnd2;  
  
    int picWidth2;  
    int picHeight2;  
  
    pWnd2 = GetDlgItem(IDC_Pic2);  
    pWnd2->GetClientRect(&rect2);  
  
    //��ͼƬ�ؼ��Ŀ�͸�  
    picWidth2 = rect2.Width();  
    picHeight2 = rect2.Height();  
  
    IplImage*dst2 = cvCreateImage(cvSize(picWidth, picHeight), img->depth, img->nChannels);  
    cvResize(img, dst2, CV_INTER_LINEAR);  
      
    //�ڿؼ�����ʾͼƬ  
    CvvImage cimg;  
    cimg.CopyOf(dst);  
    cimg.DrawToHDC(hDC, &rect);  
    cvReleaseImage(&dst);  
    ReleaseDC(pDC);  
	
	//�ڿؼ�����ʾͼƬ  
    CvvImage cimg2;  
    cimg2.CopyOf(dst2);  
    cimg2.DrawToHDC(hDC2, &rect2);  
    cvReleaseImage(&dst2);  
    ReleaseDC(pDC2);  

}  


//�ͷ������Ӱ˵ı���
void CNewWarningSystemDlg::ReleaseSetting(IplImage* pFrame)
{
	//���ж�λʱ����ͷŴ���

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




/***********************��ͬ�Ĺ���ʵ��**************************/

//��Ƶ����
IplImage* CNewWarningSystemDlg::VideoStabilization(IplImage* pFrame)
{
	//��Ƶ�������

	pFrame = stabilition.processImage(pFrame,false,false);
	return pFrame;
}


//��Ƶ����
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
			forTrack->trackSet[j].copyImage(pFrame);//��������ͼ
			forTrack->trackSet[j].setTrackWindow(forTrack->msTrack.tmpSelection[j]);//��Ҫ���ٵ�ԭʼ���ڣ���ֵ��selection
			forTrack->trackSet[j].convertToHSV();//����ͼת��HSV
			forTrack->trackSet[j].startTrackObject(); 
			forTrack->objectLocations[j] = forTrack->trackSet[j].getTrackWindow();
		}

		
		for (int j = 0; j < forTrack->msTrack.ncvFindContours; j++){
			forTrack->trackObj.drawRectangle(forTrack->objectLocations[j]);
		}

		pFrame = forTrack->trackObj.getTrackedFrame();

	}
	if (forTrack->nFrmNum == forTrack-> largenFrmNum[intnumber-1]+1)
	{//------------------------------ע20160730---��1451֡��ʱ���0�Ŵ�λ�����³�ʼ����ԭ��0�Ŵ��Ĵ��߳��ˣ��ֽ���һ��
		forTrack->trackSet[0].isTrackingInitialized = false ;
		if(intnumber == 1)
			forTrack->msTrack.tmpSelection[0] = CvRect(223,102,35,20);
		else if(intnumber == 2)
			forTrack->msTrack.tmpSelection[0] = CvRect(497,97,58,22);
		else if(intnumber == 3)
			forTrack->msTrack.initilizelocation(2,number);
	}
	if (forTrack->msTrack.tractObject&& forTrack->nFrmNum  >  forTrack-> largenFrmNum[intnumber-1] )//-----------ע20160730---��1450֡�Ժ󣬶����д������½���camshift���ٳ�ʼ��������������
	{
		for (int j = 0; j < forTrack->msTrack.ncvFindContours; j++){
			forTrack->trackSet[j].copyImage(pFrame);//��������ͼ
			forTrack->trackSet[j].setTrackWindow(forTrack->msTrack.tmpSelection[j]);//��Ҫ���ٵ�ԭʼ���ڣ���ֵ��selection
			forTrack->trackSet[j].convertToHSV();//����ͼת��HSV
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

//ԭ����Ƶ����
IplImage* CNewWarningSystemDlg::BoatPosition(IplImage* pFrame)
{
//
//
//	cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);
//	cvConvert(pFrImg, pFrameMat);
//
//	//Canny��Ե
//	cvCanny(pFrImg, pCannyImg, 100, 120, 3);
//	//��ǰ֡������ͼ���
//	cvAbsDiff(pFrameMat, pBkMat, pFrMat);
//
//	//��ֵ��ǰ��ͼ
//	cvThreshold(pFrMat, pFrImg, 15, 255.0, CV_THRESH_BINARY);
//
//	//���±���
//	cvRunningAvg(pFrameMat, pBkMat, 0.005, 0);
//	//������ת��Ϊͼ���ʽ��������ʾ
//	cvConvert(pBkMat, pBkImg);
//	cvMul(pFrImg, pCannyImg, pFrImg, 1);
//
//	// ���²�����ȥ������
//	cvPyrDown(pFrImg, pyr, 7);//��˹�������ֽ����²���
//	cvDilate(pyr, pyr, 0, 1);  // �����Ͳ���������Ŀ��Ĳ������ն�
//	cvPyrUp(pyr, pFrImg, 7);
//
//	// �ҵ���������
//	// Create dynamic structure and sequence.
//	stor = cvCreateMemStorage(0);
//	cont = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint), stor);
//
//	cvFindContours(pFrImg, stor, &cont, sizeof(CvContour),
//	CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
//
//	// ֱ��ʹ��CONTOUR�еľ�����������
//	for (; cont; cont = cont->h_next)
//	{
//		CvRect r = ((CvContour*)cont)->rect;
//
//		// ��Ϊ�޳�����
//		if ((r.x + r.width < 200 && r.y > 200) ||
//		(r.x + r.width < 120 && r.y > 180))
//			continue;
//
//		if ((r.y + r.height) < FILTER_LINE)   // ����Ȥ����
//			continue;
//
//		cvLine(pFrame,
//		cvPoint(0, FILTER_LINE), cvPoint(351, FILTER_LINE),
//		CV_RGB(0, 255, 0), 1, CV_AA, 0);
//
//		if (r.height * r.width > CONTOUR_MAX_AERA) // ���С�ķ���������
//		{
//			cvRectangle(pFrame, cvPoint(r.x, r.y),cvPoint(r.x + r.width, r.y + r.height),CV_RGB(255, 0, 0), 1, CV_AA, 0);
//
//			// ��¼����
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













/*********************** ��ͣ ֹͣ**************************/
//�����ͣ��ť
void CNewWarningSystemDlg::OnBnClickedStop1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString buttonText;  
	CButton *StopButton = (CButton*)GetDlgItem(IDC_Stop);
	StopButton->GetWindowTextW(buttonText);
    

	
    if (buttonText.Compare(_T("�� ͣ"))==0)  
    {  
        start_event2.ResetEvent();  
        StopButton->SetWindowTextW(_T("�� ��"));  
  
    }  
    else  
    {  
        start_event2.SetEvent();  
        StopButton->SetWindowText(_T("�� ͣ"));  
    }  

}


//���ֹͣ��ť
void CNewWarningSystemDlg::OnBnClickedEnd2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	flag2 = -1;
}







//#define CONTOUR_MAX_AERA 256
//#define FILTER_LINE 100  // ����Ϊԭ��
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
//	CDC *pDC = GetDlgItem(IDC_Pic1)->GetDC();//����ID��ô���ָ���ٻ�ȡ��ô��ڹ�����������ָ��
//	HDC hdc= pDC->GetSafeHdc();                      // ��ȡ�豸�����ľ��
//	CRect rect;// ������
//	GetDlgItem(IDC_Pic1)->GetClientRect(&rect); //��ȡbox1�ͻ���
//
//	CvvImage cimg;
//	cimg.CopyOf(pFrame,pFrame->nChannels);
//	cimg.DrawToHDC(hdc,&rect);
//}
























/**********************************************************/
/***********************  �����澯����  ******************/
/*********************************************************/

void CNewWarningSystemDlg::OnBnClickedCancelWarning()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	INT_PTR nRes;   
  
    // ��ʾ��Ϣ�Ի���   
    nRes = MessageBox(_T("��ȷ��Ҫ����澯ô��"), _T("����澯"), MB_OKCANCEL | MB_ICONQUESTION);   
    // �ж���Ϣ�Ի��򷵻�ֵ�����ΪIDCANCEL��return�������������ִ��   
    if (IDCANCEL == nRes)   
        return;   
  
    // �����ؼ��е����ݱ��浽��Ӧ�ı���   
    UpdateData(TRUE);   
  
  
    // ���ݸ�������ֵ������Ӧ�Ŀؼ����͵ı༭�����ʾm_editSum��ֵ   
    UpdateData(FALSE);   
    // �������ԶԻ���Ϊ�򵼶Ի���   
    //sheet.SetWizardMode(); 
}


void CNewWarningSystemDlg::OnBnClickedAddWarning()
{

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	INT_PTR nRes;   
  
    // ��ʾ��Ϣ�Ի���   
    nRes = MessageBox(_T("��ȷ��Ҫ�ֶ��澯ô��"), _T("�ֶ��澯"), MB_OKCANCEL | MB_ICONQUESTION);   
    // �ж���Ϣ�Ի��򷵻�ֵ�����ΪIDCANCEL��return�������������ִ��   
    if (IDCANCEL == nRes)   
        return;   
  
    // �����ؼ��е����ݱ��浽��Ӧ�ı���   
    UpdateData(TRUE);   
  
  
    // ���ݸ�������ֵ������Ӧ�Ŀؼ����͵ı༭�����ʾm_editSum��ֵ   
    UpdateData(FALSE);   
    // �������ԶԻ���Ϊ�򵼶Ի���   
    //sheet.SetWizardMode(); 
}


