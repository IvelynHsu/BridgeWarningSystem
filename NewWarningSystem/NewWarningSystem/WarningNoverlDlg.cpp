// WarningNoverlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NewWarningSystem.h"
#include "WarningNoverlDlg.h"
#include "afxdialogex.h"

#include "NewWarningSystemDlg.h"
#include "RiverDlg.h"
#include "CheckDlg.h"
#include "VideoPlayer.h"
#include "WarningNoverlDlg.h"
#include "RiverDlg.h"
#include "SettingDlg.h"

// WarningNoverlDlg 对话框

IMPLEMENT_DYNAMIC(WarningNoverlDlg, CDialogEx)

WarningNoverlDlg::WarningNoverlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(WarningNoverlDlg::IDD, pParent)
{

}

WarningNoverlDlg::~WarningNoverlDlg()
{
}

void WarningNoverlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WarningNoverlDlg, CDialogEx)
	ON_COMMAND(ID_MenuV, &WarningNoverlDlg::OnMenuv)
	ON_COMMAND(ID_MenuR, &WarningNoverlDlg::OnMenur)
	ON_COMMAND(ID_MenuW, &WarningNoverlDlg::OnMenuw)
	ON_COMMAND(ID_MenuC, &WarningNoverlDlg::OnMenuc)
	ON_COMMAND(ID_MenuA, &WarningNoverlDlg::OnMenua)
	ON_COMMAND(ID_MenuP, &WarningNoverlDlg::OnMenup)
END_MESSAGE_MAP()


// WarningNoverlDlg 消息处理程序


void WarningNoverlDlg::OnMenuv()
{
	// TODO: 在此添加命令处理程序代码
	CNewWarningSystemDlg * pDlg;
	pDlg = new CNewWarningSystemDlg();
	pDlg->Create(IDD_Main);
	pDlg->ShowWindow(SW_SHOW);
}


void WarningNoverlDlg::OnMenur()
{
	// TODO: 在此添加命令处理程序代码
	RiverDlg * pDlg;
	pDlg = new RiverDlg();
	pDlg->Create(IDD_River);
	pDlg->ShowWindow(SW_SHOW);
}


void WarningNoverlDlg::OnMenuw()
{
	// TODO: 在此添加命令处理程序代码
}


void WarningNoverlDlg::OnMenuc()
{
	// TODO: 在此添加命令处理程序代码
	CheckDlg * pDlg;
	pDlg = new CheckDlg();
	pDlg->Create(IDD_Check);
	pDlg->ShowWindow(SW_SHOW);
}


void WarningNoverlDlg::OnMenua()
{
	// TODO: 在此添加命令处理程序代码
	CDialogEx * pDlg;
	pDlg = new CDialogEx();
	pDlg->Create(IDD_ABOUTBOX);
	pDlg->ShowWindow(SW_SHOW);
}


void WarningNoverlDlg::OnMenup()
{
	// TODO: 在此添加命令处理程序代码
	VideoPlayer * pDlg;
	pDlg = new VideoPlayer();
	pDlg->Create(IDD_VideoPlayer);
	pDlg->ShowWindow(SW_SHOW);
}
