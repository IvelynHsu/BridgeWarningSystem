// RiverDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NewWarningSystem.h"
#include "RiverDlg.h"
#include "afxdialogex.h"

#include "NewWarningSystemDlg.h"
#include "RiverDlg.h"
#include "CheckDlg.h"
#include "VideoPlayer.h"
#include "WarningNoverlDlg.h"
#include "RiverDlg.h"
#include "SettingDlg.h"

// RiverDlg 对话框

IMPLEMENT_DYNAMIC(RiverDlg, CDialogEx)

RiverDlg::RiverDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(RiverDlg::IDD, pParent)
{

}


RiverDlg::~RiverDlg()
{

}

void RiverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RiverDlg, CDialogEx)
	ON_COMMAND(ID_MenuV, &RiverDlg::OnMenuv)
	ON_COMMAND(ID_MenuR, &RiverDlg::OnMenur)
	ON_COMMAND(ID_MenuW, &RiverDlg::OnMenuw)
	ON_COMMAND(ID_MenuC, &RiverDlg::OnMenuc)
	ON_COMMAND(ID_MenuA, &RiverDlg::OnMenua)
	ON_BN_CLICKED(IDOK4, &RiverDlg::OnBnClickedOk4)
	ON_COMMAND(ID_MenuP, &RiverDlg::OnMenup)
	ON_BN_CLICKED(IDOK2, &RiverDlg::OnBnClickedWarning)
	ON_BN_CLICKED(IDOK3, &RiverDlg::OnBnClickedWarningCancelR)
END_MESSAGE_MAP()


// RiverDlg 消息处理程序


BOOL RiverDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();


	return TRUE;
}







/**********************************************************/
/*************************建立目录代码********************/
/*********************************************************/
void RiverDlg::OnMenuv()
{
	// TODO: 在此添加命令处理程序代码

	CNewWarningSystemDlg * pDlg;
	pDlg = new CNewWarningSystemDlg();
	pDlg->Create(IDD_Main);
	pDlg->ShowWindow(SW_SHOW);


	//！！！！！如果已存在 可以把光标突出
}

void RiverDlg::OnMenur()
{
	// TODO: 在此添加命令处理程序代码
}

void RiverDlg::OnMenuw()
{
	// TODO: 在此添加命令处理程序代码
	WarningNoverlDlg * pDlg;
	pDlg = new WarningNoverlDlg();
	pDlg->Create(IDD_Warning);
	pDlg->ShowWindow(SW_SHOW);
}

void RiverDlg::OnMenuc()
{
	// TODO: 在此添加命令处理程序代码
	CheckDlg * pDlg;
	pDlg = new CheckDlg();
	pDlg->Create(IDD_Check);
	pDlg->ShowWindow(SW_SHOW);
}

void RiverDlg::OnMenua()
{
	// TODO: 在此添加命令处理程序代码
	CDialogEx * pDlg;
	pDlg = new CDialogEx();
	pDlg->Create(IDD_ABOUTBOX);
	pDlg->ShowWindow(SW_SHOW);
}

void RiverDlg::OnMenup()
{
	// TODO: 在此添加命令处理程序代码
	VideoPlayer * pDlg;
	pDlg = new VideoPlayer();
	pDlg->Create(IDD_VideoPlayer);
	pDlg->ShowWindow(SW_SHOW);
}




















void RiverDlg::OnBnClickedOk4()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CDC *pDC = GetDlgItem(IDC_River)->GetDC();//根据ID获得窗口指针再获取与该窗口关联的上下文指针
	HDC hdc= pDC->GetSafeHdc(); // 获取设备上下文句柄
	CRect rect;// 矩形类
	
	GetDlgItem(IDC_River)->GetClientRect(&rect); //获取box1客户区
	CvvImage cimg;
	IplImage *src; // 定义IplImage指针变量src     
    src = cvLoadImage("D:\\WorkSpace\\WorkSpaceVS\\NewWarningSystem\\NewWarningSystem\\res\\River.png",1); // 将src指向当前工程文件目录下的图像
	cimg.CopyOf(src,src->nChannels);
	cimg.DrawToHDC(hdc,&rect);//输出图像
	ReleaseDC(pDC);
	cimg.Destroy();//销毁

	CDialogEx * pDlg;
	pDlg = new CDialogEx();
	pDlg->Create(IDD_Setting);
	pDlg->ShowWindow(SW_SHOW);
}





























/**********************************************************/
/***********************  建立告警机制  ******************/
/*********************************************************/


void RiverDlg::OnBnClickedWarning()
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




void RiverDlg::OnBnClickedWarningCancelR()
{
	// TODO: 在此添加控件通知处理程序代码
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
