
// CLASSTEST.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "CLASSTEST.h"
#include "CLASSTESTDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCLASSTESTApp

BEGIN_MESSAGE_MAP(CCLASSTESTApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCLASSTESTApp ����

CCLASSTESTApp::CCLASSTESTApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CCLASSTESTApp ����

CCLASSTESTApp theApp;


// CCLASSTESTApp ��ʼ��

BOOL CCLASSTESTApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
// 	INITCOMMONCONTROLSEX InitCtrls;
// 	InitCtrls.dwSize = sizeof(InitCtrls);
// 	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
// 	// �����ؼ��ࡣ
// 	InitCtrls.dwICC = ICC_WIN95_CLASSES;
// 	InitCommonControlsEx(&InitCtrls);
// 
// 	CWinApp::InitInstance();
// 
// 
// 	AfxEnableControlContainer();
	InitCommonControls();
	CWinApp::InitInstance();
	AfxEnableControlContainer();
#ifdef BCG
	globalData.SetDPIAware ();
	CBCGPVisualManager2010::SetStyle (CBCGPVisualManager2010::VS2010_Black);
	CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2010));
#endif
	GdiplusStartup(&m_pGdiToken,&m_gdiplusStartupInput,NULL);  
	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
//	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
//	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	m_resdlg = new CResDlg();
	m_resdlg->Create(IDD_DIALOG_SHOWRESULT);   
	CCLASSTESTDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
// 	if (pShellManager != NULL)
// 	{
// 		delete pShellManager;
// 	}

#ifdef BCG
	BCGCBProCleanUp ();
#endif

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

CCLASSTESTApp::~CCLASSTESTApp()
{
	delete m_resdlg;
}

