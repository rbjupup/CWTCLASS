
// CLASSTEST.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once
#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "ResDlg.h"
#include <afxdtctl.h>  
#define ULONG_PTR ULONG  
#include <gdiplus.h>  
using namespace Gdiplus;  
#pragma comment(lib, "gdiplus.lib")  
#ifdef BCG
#include "afxwin.h"
#include "afxcmn.h"
#include "BCGPVisualCtrl.h"
#include "BCGPChartVisualObject.h"
#endif
// CCLASSTESTApp:
// �йش����ʵ�֣������ CLASSTEST.cpp
//

class CCLASSTESTApp : public CWinApp
{
public:
	CCLASSTESTApp();
	~CCLASSTESTApp();
private:  
	GdiplusStartupInput m_gdiplusStartupInput;  
	ULONG_PTR m_pGdiToken;  
// ��д
public:
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance()
	{
		GdiplusShutdown(m_pGdiToken);  
		return TRUE;
	}
	CResDlg* m_resdlg;
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCLASSTESTApp theApp;