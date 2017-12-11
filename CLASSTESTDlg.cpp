
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
	: CDialog(CCLASSTESTDlg::IDD, pParent)
	, m_strHelp(_T(""))
	, m_strInput(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_row = 0;
	m_column = 0;

}

void CCLASSTESTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbSupportClass);
	DDX_Control(pDX, IDC_COMBO2, m_cbFunction);
	DDX_Text(pDX, IDC_EDIT1, m_strHelp);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_strInput);
	DDX_Control(pDX, IDC_LIST1, m_ListInput);
	DDX_Control(pDX, IDC_EDIT_TMP, m_edit);
}

BEGIN_MESSAGE_MAP(CCLASSTESTDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CCLASSTESTDlg::OnBnClickedButtonStart)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CCLASSTESTDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON_INPUT, &CCLASSTESTDlg::OnBnClickedButtonInput)
	ON_BN_CLICKED(IDC_BUTTON1, &CCLASSTESTDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CCLASSTESTDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCLASSTESTDlg::OnBnClickedButton2)
	ON_EN_KILLFOCUS(IDC_EDIT_TMP, &CCLASSTESTDlg::OnEnKillfocusEditTmp)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CCLASSTESTDlg::OnNMDblclkList1)
END_MESSAGE_MAP()


// CCLASSTESTDlg ��Ϣ�������

BOOL CCLASSTESTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
#ifdef BCG
	CBCGPVisualManager2010::SetStyle (CBCGPVisualManager2010::VS2010_Blue);
	CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2010));
	EnableVisualManagerStyle();
#endif
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
	}
	m_cbSupportClass.SetCurSel(0);

	vector<CString> supportFunction;
	CString curClassName;
	m_cbSupportClass.GetLBText(m_cbSupportClass.GetCurSel(),curClassName);
	supportFunction = m_boss.GetSupportFunCtion(curClassName);
	for (int  i = 0 ; i < supportFunction.size(); i++)
	{
		m_cbFunction.AddString(supportFunction[i]);
	}
	m_cbFunction.SetCurSel(0);
	OnCbnSelchangeCombo2();

	LONG lStyle;
	lStyle = GetWindowLong(m_ListInput.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(m_ListInput.m_hWnd, GWL_STYLE, lStyle);//����style
	DWORD dwStyle = m_ListInput.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	m_ListInput.SetExtendedStyle(dwStyle); //������չ���
	m_ListInput.InsertColumn(0,"������",0,80);
	m_ListInput.InsertColumn(1,"��������",0,400);

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
		CDialog::OnSysCommand(nID, lParam);
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
		CDialog::OnPaint();
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
		CString strText =  m_ListInput.GetItemText(i,1);
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

	CString numIndex;
	numIndex.Format("%d",ncount);
	m_ListInput.InsertItem(ncount,numIndex);
	m_ListInput.SetItemText(ncount,1,m_strInput);
	m_strInput = CString("");
	UpdateData(FALSE);
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

//ɾ��ѡ��
void CCLASSTESTDlg::OnBnClickedButton2()
{
	POSITION pos = m_ListInput.GetFirstSelectedItemPosition();
	int num =(int)pos - 1;
	vector<CString> param;
	int ncount = m_ListInput.GetItemCount();
	for (int i = 0 ; i < ncount; i++)
	{
		if(i == num)
			continue;
		CString strText =  m_ListInput.GetItemText(i,1);
		param.push_back(strText);
	}
	m_ListInput.DeleteAllItems();
	for (int i = 0; i < param.size(); i++)
	{
		CString numIndex;
		numIndex.Format("%d",i);
		m_ListInput.InsertItem(i,numIndex);
		m_ListInput.SetItemText(i,1,param[i]);
	}
	return;
}


void CCLASSTESTDlg::OnEnKillfocusEditTmp()
{
	CString str;
	m_edit.GetWindowText(str);//ȡ�ñ༭�������
	m_ListInput.SetItemText(m_row,m_column,str);//�������ݸ��µ�CListCtrl��
	m_edit.ShowWindow(SW_HIDE);//���ر༭��
	POSITION pos = m_ListInput.GetFirstSelectedItemPosition();
	int num =m_row;//(int)pos - 1;

	if (m_column == 0||m_row == 0)
	{
		return;
	}

	vector<CString> param;
	int ncount = m_ListInput.GetItemCount();
	for (int i = 0 ; i < ncount; i++)
	{
		CString strText =  m_ListInput.GetItemText(i,1);
		if(i == num)
			param.push_back(str);
		else
			param.push_back(strText);
	}
	m_ListInput.DeleteAllItems();
	for (int i = 0; i < param.size(); i++)
	{
		CString numIndex;
		numIndex.Format("%d",i);
		m_ListInput.InsertItem(i,numIndex);
		m_ListInput.SetItemText(i,1,param[i]);
	}
	return;
}


void CCLASSTESTDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;
	CRect rc,rect;
	if(pNMListView->iItem!=-1)
	{
		m_row=pNMListView->iItem;//m_rowΪ��ѡ���е�����ţ�int���ͳ�Ա������
		m_column=pNMListView->iSubItem;//m_columnΪ��ѡ���е�����ţ�int���ͳ�Ա������
		m_ListInput.GetSubItemRect(pNMListView->iItem, pNMListView->iSubItem,LVIR_LABEL,rc);//ȡ������ľ���
		GetDlgItem(IDC_LIST1)->GetWindowRect(&rect);//��ȡ�ؼ�����Ļ����
		ScreenToClient(&rect);//ת��Ϊ�Ի����ϵĿͻ�����
		rc.left+=3;
		rc.left+=rect.left;
		rc.top+=2;
		rc.top+=rect.top;
		rc.right+=3;
		rc.right+=rect.left;
		rc.bottom+=2;
		rc.bottom+=rect.top;

		char * ch=new char [128];
		m_ListInput.GetItemText(pNMListView->iItem, pNMListView->iSubItem,ch,128);//ȡ�����������
		m_edit.SetWindowText(ch);//�������������ʾ���༭����
		m_edit.ShowWindow(SW_SHOW);//��ʾ�༭��
		m_edit.MoveWindow(&rc);//���༭���ƶ����������棬������������
		m_edit.SetFocus();//ʹ�༭��ȡ�ý���
		m_edit.BringWindowToTop();
		m_edit.CreateSolidCaret(1,rc.Height()-5);//����һ�����
		m_edit.ShowCaret();//��ʾ���
		m_edit.SetSel(-1);//ʹ����Ƶ������
	}
	*pResult = 0;
}
