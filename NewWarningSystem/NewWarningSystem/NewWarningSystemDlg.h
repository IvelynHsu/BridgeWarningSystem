
// NewWarningSystemDlg.h : ͷ�ļ�
//
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <iostream>
#include <highgui.hpp>
#include "CvvImage.h"
#include <opencv2/opencv.hpp>
#include "Stabilition.h"

#pragma once


// CNewWarningSystemDlg �Ի���
class CNewWarningSystemDlg : public CDialogEx
{
// ����
public:
	CNewWarningSystemDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_NEWWARNINGSYSTEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��


private:
	Stabilition stabilition;


protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void VideoClick();
	afx_msg void OnBnClickedOk4();
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedCancelWarning();
	afx_msg void OnBnClickedAddWarning();
	afx_msg void OnMenuv();
	afx_msg void OnMenur();
	afx_msg void OnMenuw();
	afx_msg void OnMenuc();
	afx_msg void OnMenua();
	afx_msg void OnBnClickedPlayVideo();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedEnd();

	void DisplayFrame(IplImage *img);
	IplImage* CheckForRaidoButton(CvCapture* pCapture);
	void BeginSetting(CvCapture* pCapture);
	void ReleaseSetting(IplImage* pFrame);

	IplImage* BoatPosition(IplImage* pFrame);
	IplImage* VideoStabilization(IplImage* pFrame);
	IplImage* VideoTracking(IplImage* pFrame);

	afx_msg void OnMenup();
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedStop1();
	afx_msg void OnBnClickedEnd2();
	afx_msg void OnBnClickedOpenvideo();


};
