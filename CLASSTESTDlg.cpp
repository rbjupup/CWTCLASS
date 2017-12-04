
// CLASSTESTDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CLASSTEST.h"
#include "CLASSTESTDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CCLASSTESTDlg 对话框




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


// CCLASSTESTDlg 消息处理程序

BOOL CCLASSTESTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
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
	m_ListInput.InsertColumn(0,"输入内容",0,1200);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCLASSTESTDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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

	// 显示非模态对话框   
	theApp.m_resdlg->ShowWindow(SW_SHOW);   
	m_boss.CallFunction(surClass,surFun,param);
//	m_ListInput.DeleteAllItems();
}


//选择函数改变了
void CCLASSTESTDlg::OnCbnSelchangeCombo2()
{
	//改变帮助函数
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

//选择的测试类改变了
void CCLASSTESTDlg::OnCbnSelchangeCombo1()
{
	//改变帮助函数


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
