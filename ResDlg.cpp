// ResDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CLASSTEST.h"
#include "ResDlg.h"
#include "afxdialogex.h"


// CResDlg �Ի���

IMPLEMENT_DYNAMIC(CResDlg, CDialog)

CResDlg::CResDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CResDlg::IDD, pParent)
	, m_strRes(_T(""))
{

}

CResDlg::~CResDlg()
{
}

void CResDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RESSTR, m_strRes);
	DDX_Control(pDX, IDC_SHOW, m_Show);
}


BEGIN_MESSAGE_MAP(CResDlg, CDialog)
END_MESSAGE_MAP()


// CResDlg ��Ϣ�������
