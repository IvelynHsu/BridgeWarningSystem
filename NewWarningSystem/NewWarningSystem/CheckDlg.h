#pragma once


// CheckDlg �Ի���

class CheckDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CheckDlg)

public:
	CheckDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CheckDlg();

// �Ի�������
	enum { IDD = IDD_Check };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuv();
	afx_msg void OnMenur();
	afx_msg void OnMenuw();
	afx_msg void OnMenuc();
	afx_msg void OnMenua();
	afx_msg void OnBnClickedCheck();
	afx_msg void OnMenup();
};
