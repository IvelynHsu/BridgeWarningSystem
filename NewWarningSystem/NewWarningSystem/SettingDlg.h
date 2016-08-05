#pragma once


// SettingDlg 对话框

class SettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SettingDlg)

public:
	SettingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SettingDlg();

// 对话框数据
	enum { IDD = IDD_Setting };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
