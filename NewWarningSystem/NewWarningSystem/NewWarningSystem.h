
// NewWarningSystem.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNewWarningSystemApp:
// �йش����ʵ�֣������ NewWarningSystem.cpp
//

class CNewWarningSystemApp : public CWinApp
{
public:
	CNewWarningSystemApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CNewWarningSystemApp theApp;