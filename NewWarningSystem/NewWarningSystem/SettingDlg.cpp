// SettingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NewWarningSystem.h"
#include "SettingDlg.h"
#include "afxdialogex.h"

#include "NewWarningSystemDlg.h"
#include "RiverDlg.h"
#include "CheckDlg.h"
#include "VideoPlayer.h"
#include "WarningNoverlDlg.h"
#include "RiverDlg.h"
#include "SettingDlg.h"

// SettingDlg �Ի���

IMPLEMENT_DYNAMIC(SettingDlg, CDialogEx)

SettingDlg::SettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(SettingDlg::IDD, pParent)
{

}

SettingDlg::~SettingDlg()
{
}

void SettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SettingDlg, CDialogEx)
END_MESSAGE_MAP()


// SettingDlg ��Ϣ�������
