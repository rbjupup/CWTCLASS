
// CLASSTESTDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CLASSTEST.h"
#include "CLASSTESTDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCLASSTESTDlg �Ի���




CCLASSTESTDlg::CCLASSTESTDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCLASSTESTDlg::IDD, pParent)
	, m_strHelp(_T(""))
	, m_strInput(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCLASSTESTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbSupportClass);
	DDX_Control(pDX, IDC_COMBO2, m_cbFunction);
	DDX_Text(pDX, IDC_EDIT1, m_strHelp);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_strInput);
	DDX_Control(pDX, IDC_LIST1, m_ListInput);
}

BEGIN_MESSAGE_MAP(CCLASSTESTDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CCLASSTESTDlg::OnBnClickedButtonStart)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CCLASSTESTDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON_INPUT, &CCLASSTESTDlg::OnBnClickedButtonInput)
	ON_BN_CLICKED(IDC_BUTTON1, &CCLASSTESTDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CCLASSTESTDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CCLASSTESTDlg ��Ϣ�������

BOOL CCLASSTESTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_cbSupportClass.ResetContent();
	m_cbFunction.ResetContent();
	vector<CString> supportclass;
	supportclass = m_boss.GetSupportClass();

	for (int  i = 0 ; i < supportclass.size(); i++)
	{
		m_cbSupportClass.AddString(supportclass[i]);
		if (supportclass[i] == CLASSNAME1)
		{
			m_cbSupportClass.SetCurSel(i);
		}
	}

	vector<CString> supportFunction;
	CString curClassName;
	m_cbSupportClass.GetLBText(m_cbSupportClass.GetCurSel(),curClassName);
	supportFunction = m_boss.GetSupportFunCtion(curClassName);

	for (int  i = 0 ; i < supportFunction.size(); i++)
	{
		m_cbFunction.AddString(supportFunction[i]);
		if (supportFunction[i] == "TESTCAMTOBOARD")
		{
			m_cbFunction.SetCurSel(i);
		}
	}
	OnCbnSelchangeCombo2();
	m_ListInput.InsertColumn(0,"��������",0,1200);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCLASSTESTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCLASSTESTDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCLASSTESTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCLASSTESTDlg::OnBnClickedButtonStart()
{
	CString surClass,surFun;
	m_cbSupportClass.GetLBText(m_cbSupportClass.GetCurSel(),surClass);
	m_cbFunction.GetLBText(m_cbFunction.GetCurSel(),surFun);
	theApp.m_resdlg->m_strRes = CString("");
	vector<CString> param;
	int ncount = m_ListInput.GetItemCount();
	for (int i = 0 ; i < ncount; i++)
	{
		CString strText =  m_ListInput.GetItemText(i,0);
		param.push_back(strText);
	}

	// ��ʾ��ģ̬�Ի���   
	theApp.m_resdlg->ShowWindow(SW_SHOW);   
	m_boss.CallFunction(surClass,surFun,param);
//	m_ListInput.DeleteAllItems();
}


//ѡ�����ı���
void CCLASSTESTDlg::OnCbnSelchangeCombo2()
{
	//�ı��������
	CString surClass,surFun;
	m_cbSupportClass.GetLBText(m_cbSupportClass.GetCurSel(),surClass);
	m_cbFunction.GetLBText(m_cbFunction.GetCurSel(),surFun);
	theApp.m_resdlg->m_strRes = CString("");
	m_strHelp.Format("%s",m_boss.GetFunctionHelp(surClass,surFun));
	UpdateData(FALSE);
}


void CCLASSTESTDlg::OnBnClickedButtonInput()
{
	UpdateData(TRUE);
	int ncount = m_ListInput.GetItemCount();
	m_ListInput.InsertItem(ncount,m_strInput);
	m_strInput = CString("");
	UpdateData(TRUE);
}


void CCLASSTESTDlg::OnBnClickedButton1()
{
	m_ListInput.DeleteAllItems();
	UpdateData(FALSE);
}

//ѡ��Ĳ�����ı���
void CCLASSTESTDlg::OnCbnSelchangeCombo1()
{
	//�ı��������


	vector<CString> supportFunction;
	CString curClassName;
	m_cbSupportClass.GetLBText(m_cbSupportClass.GetCurSel(),curClassName);
	supportFunction = m_boss.GetSupportFunCtion(curClassName);
	m_cbFunction.ResetContent();
	for (int  i = 0 ; i < supportFunction.size(); i++)
	{
		m_cbFunction.AddString(supportFunction[i]);
	}
	m_cbFunction.SetCurSel(0);
	OnCbnSelchangeCombo2();
}
