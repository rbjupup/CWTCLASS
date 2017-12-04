#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "BCGPVisualCtrl.h"
#include "BCGPChartVisualObject.h"


// ABCGDlg �Ի���

#define CDialog CBCGPDialog

#define MAX_SERIES 5
class ABCGDlg : public CDialog
{
	DECLARE_DYNAMIC(ABCGDlg)

public:
	ABCGDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ABCGDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_BCG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

//����ͼ��������
	CBCGPChartCtrl m_wndChart;
	CBCGPChartSeries*	m_arSeries[1];
//����ͼ��������End


	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonStart();
};
