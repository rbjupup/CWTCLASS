
// CLASSTESTDlg.h : ͷ�ļ�
//

#pragma once
#include "BOSSCLASS.h"
#include "afxwin.h"
#include "afxcmn.h"

// CCLASSTESTDlg �Ի���
class CCLASSTESTDlg : public CDialogEx
{
// ����
public:
	CCLASSTESTDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLASSTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:

	BOSSCLASS m_boss;								//��Ҫ�࣬�������ȸ���������

	afx_msg void OnBnClickedButtonStart();
	CComboBox m_cbSupportClass;
	CComboBox m_cbFunction;
	afx_msg void OnCbnSelchangeCombo2();
	CString m_strHelp;
	CString m_strInput;
	afx_msg void OnBnClickedButtonInput();
	CListCtrl m_ListInput;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeCombo1();
};
