
// NewWarningSystemDlg.h : 头文件
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


// CNewWarningSystemDlg 对话框
class CNewWarningSystemDlg : public CDialogEx
{
// 构造
public:
	CNewWarningSystemDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_NEWWARNINGSYSTEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现


private:
	Stabilition stabilition;


protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
