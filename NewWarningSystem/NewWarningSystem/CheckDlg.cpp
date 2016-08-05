// CheckDlg.cpp : ʵ���ļ�

#include "stdafx.h"
#include "NewWarningSystem.h"
#include "CheckDlg.h"
#include "afxdialogex.h"


#include "NewWarningSystemDlg.h"
#include "RiverDlg.h"
#include "CheckDlg.h"
#include "VideoPlayer.h"
#include "WarningNoverlDlg.h"
#include "RiverDlg.h"
#include "SettingDlg.h"

// CheckDlg �Ի���

IMPLEMENT_DYNAMIC(CheckDlg, CDialogEx)

CheckDlg::CheckDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CheckDlg::IDD, pParent)
{

}

CheckDlg::~CheckDlg()
{
}

void CheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CheckDlg, CDialogEx)
	ON_COMMAND(ID_MenuV, &CheckDlg::OnMenuv)
	ON_COMMAND(ID_MenuR, &CheckDlg::OnMenur)
	ON_COMMAND(ID_MenuW, &CheckDlg::OnMenuw)
	ON_COMMAND(ID_MenuC, &CheckDlg::OnMenuc)
	ON_COMMAND(ID_MenuA, &CheckDlg::OnMenua)
	ON_BN_CLICKED(IDOK3, &CheckDlg::OnBnClickedCheck)
	ON_COMMAND(ID_MenuP, &CheckDlg::OnMenup)
END_MESSAGE_MAP()


// CheckDlg ��Ϣ�������


void CheckDlg::OnMenuv()
{
	// TODO: �ڴ���������������
	CNewWarningSystemDlg * pDlg;
	pDlg = new CNewWarningSystemDlg();
	pDlg->Create(IDD_Main);
	pDlg->ShowWindow(SW_SHOW);
}


void CheckDlg::OnMenur()
{
	// TODO: �ڴ���������������
	RiverDlg * pDlg;
	pDlg = new RiverDlg();
	pDlg->Create(IDD_River);
	pDlg->ShowWindow(SW_SHOW);
}


void CheckDlg::OnMenuw()
{
	// TODO: �ڴ���������������
	WarningNoverlDlg * pDlg;
	pDlg = new WarningNoverlDlg();
	pDlg->Create(IDD_Warning);
	pDlg->ShowWindow(SW_SHOW);
}


void CheckDlg::OnMenuc()
{
	// TODO: �ڴ���������������
}


void CheckDlg::OnMenua()
{
	// TODO: �ڴ���������������
	CDialogEx * pDlg;
	pDlg = new CDialogEx();
	pDlg->Create(IDD_ABOUTBOX);
	pDlg->ShowWindow(SW_SHOW);
}


void CheckDlg::OnBnClickedCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CheckDlg::OnMenup()
{
	// TODO: �ڴ���������������
	VideoPlayer * pDlg;
	pDlg = new VideoPlayer();
	pDlg->Create(IDD_VideoPlayer);
	pDlg->ShowWindow(SW_SHOW);
}
