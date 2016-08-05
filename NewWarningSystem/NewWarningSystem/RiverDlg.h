#pragma once


// RiverDlg 对话框

class RiverDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RiverDlg)

public:
	RiverDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~RiverDlg();

// 对话框数据
	enum { IDD = IDD_River };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL RiverDlg::OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuv();
	afx_msg void OnMenur();
	afx_msg void OnMenuw();
	afx_msg void OnMenuc();
	afx_msg void OnMenua();
	afx_msg void OnBnClickedOk4();
	afx_msg void OnMenup();
	afx_msg void OnBnClickedtry();
	afx_msg void OnBnClickedWarning();
	afx_msg void OnBnClickedWarningCancelR();
};
