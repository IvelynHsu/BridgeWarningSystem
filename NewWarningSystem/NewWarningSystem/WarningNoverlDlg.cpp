// WarningNoverlDlg.cpp : ʵ���ļ�
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

// WarningNoverlDlg �Ի���

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


// WarningNoverlDlg ��Ϣ�������


void WarningNoverlDlg::OnMenuv()
{
	// TODO: �ڴ���������������
	CNewWarningSystemDlg * pDlg;
	pDlg = new CNewWarningSystemDlg();
	pDlg->Create(IDD_Main);
	pDlg->ShowWindow(SW_SHOW);
}


void WarningNoverlDlg::OnMenur()
{
	// TODO: �ڴ���������������
	RiverDlg * pDlg;
	pDlg = new RiverDlg();
	pDlg->Create(IDD_River);
	pDlg->ShowWindow(SW_SHOW);
}


void WarningNoverlDlg::OnMenuw()
{
	// TODO: �ڴ���������������
}


void WarningNoverlDlg::OnMenuc()
{
	// TODO: �ڴ���������������
	CheckDlg * pDlg;
	pDlg = new CheckDlg();
	pDlg->Create(IDD_Check);
	pDlg->ShowWindow(SW_SHOW);
}


void WarningNoverlDlg::OnMenua()
{
	// TODO: �ڴ���������������
	CDialogEx * pDlg;
	pDlg = new CDialogEx();
	pDlg->Create(IDD_ABOUTBOX);
	pDlg->ShowWindow(SW_SHOW);
}


void WarningNoverlDlg::OnMenup()
{
	// TODO: �ڴ���������������
	VideoPlayer * pDlg;
	pDlg = new VideoPlayer();
	pDlg->Create(IDD_VideoPlayer);
	pDlg->ShowWindow(SW_SHOW);
}
