#pragma once
#include "resource.h"
#include "afxwin.h"

// CResDlg �Ի���

class CResDlg : public CDialog
{
	DECLARE_DYNAMIC(CResDlg)

public:
	CResDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CResDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SHOWRESULT };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strRes;
	CStatic m_Show;
};
