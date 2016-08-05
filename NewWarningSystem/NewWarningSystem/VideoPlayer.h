#pragma once

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <iostream>
#include <highgui.hpp>
#include "CvvImage.h"
#include <opencv2/opencv.hpp>
// VideoPlayer 对话框

class VideoPlayer : public CDialogEx
{
	DECLARE_DYNAMIC(VideoPlayer)

public:
	VideoPlayer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~VideoPlayer();

// 对话框数据
	enum { IDD = IDD_VideoPlayer };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedEnd();
	void Display(IplImage *img);
	afx_msg void OnMenuv();
	afx_msg void OnMenup();
	afx_msg void OnMenur();
	afx_msg void OnMenuw();
	afx_msg void OnMenuc();
};
