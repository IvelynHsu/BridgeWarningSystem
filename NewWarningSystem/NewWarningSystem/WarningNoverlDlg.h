#pragma once


// WarningNoverlDlg �Ի���

class WarningNoverlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(WarningNoverlDlg)

public:
	WarningNoverlDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~WarningNoverlDlg();

// �Ի�������
	enum { IDD = IDD_Warning };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuv();
	afx_msg void OnMenur();
	afx_msg void OnMenuw();
	afx_msg void OnMenuc();
	afx_msg void OnMenua();
	afx_msg void OnMenup();
};
