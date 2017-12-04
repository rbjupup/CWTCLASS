// WMFCBtn.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CLASSTEST.h"
#include "WMFCBtn.h"
#include "afxdialogex.h"


// CWMFCBtn �Ի���

IMPLEMENT_DYNAMIC(CWMFCBtn, CDialog)
WCHAR* ToWChar(char *str)  
{  
	//�� GDI���У��й��ַ��Ĳ�������ȫ������ WCHAR ���͵�  
	//�ú����ǽ���ͳ�ַ�������ת��  
	static WCHAR buffer[1024];  
	wcsset(buffer,0);  
	MultiByteToWideChar(CP_ACP,0,str,strlen(str),buffer,1024);  
	return buffer;  
}  

int GetImageCLSID(const WCHAR *format, CLSID *pCLSID)  
{  
	UINT num=0;  
	UINT size=0;  
	ImageCodecInfo* pImageCodecInfo=NULL;  
	GetImageEncodersSize(&num,&size);  
	if(size==0)  
		return FALSE; // ������Ϣ������  
	// �����ڴ�  
	pImageCodecInfo=(ImageCodecInfo*)(malloc(size));  
	if(pImageCodecInfo==NULL)  
		return FALSE; // ����ʧ��  
	// ���ϵͳ�п��õı��뷽ʽ��������Ϣ  
	GetImageEncoders(num,size,pImageCodecInfo);  
	// �ڿ��ñ�����Ϣ�в��� format ��ʽ�Ƿ�֧��  

	for(UINT i=0;i<num;++i)  
	{  
		//MimeType: ���뷽ʽ�ľ�������  
		if (wcscmp(pImageCodecInfo[ i] .MimeType,format)==0)  
		{  
			*pCLSID=pImageCodecInfo[i].Clsid;  
			free(pImageCodecInfo);  
			return TRUE;  
		}  
	}  
	free(pImageCodecInfo);  
	return FALSE;  
}  

CWMFCBtn::CWMFCBtn(CWnd* pParent /*=NULL*/)
	: CDialog(CWMFCBtn::IDD, pParent),
	m_Bg1(ToWChar("bg1.png")),m_Bg2(ToWChar("bg1.png"))
{

}

CWMFCBtn::~CWMFCBtn()
{
//	GdiplusShutdown(m_pGdiToken);  
}

void CWMFCBtn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_UNNORMAL2, m_btnPng);
}


BEGIN_MESSAGE_MAP(CWMFCBtn, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_UNNORMAL2, &CWMFCBtn::OnBnClickedButtonUnnormal2)
END_MESSAGE_MAP()


// CWMFCBtn ��Ϣ�������


BOOL CWMFCBtn::OnInitDialog()
{
	CDialog::OnInitDialog();
//	GdiplusStartup(&m_pGdiToken,&m_gdiplusStartupInput,NULL);  
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CMFCButton *pMfcButton = (CMFCButton *)GetDlgItem(IDC_BUTTON_UNNORMAL2);  

// 	m_Bg1.FromFile(ToWChar("bg1.png"));
// 	m_Bg2.FromFile(ToWChar("bg2.png"));
// 	HBITMAP hBmp, hBmpHot;  
// 	m_Bg1.GetHBITMAP(NULL, &hBmp);  
// 	m_Bg2.GetHBITMAP(NULL, &hBmpHot);  
// 	pMfcButton->SetImage(hBmp, TRUE, hBmpHot);  
// 	OnPaint();
// 	pMfcButton->m_bTransparent = TRUE;    // ���ð�ťΪ͸����  
	m_btnPng.LoadStdImage(IDB_LOGINBTN, _T("PNG")); //����״̬ 
	m_btnPng.LoadAltImage(IDB_LOGINACTIVE, _T("PNG")); //����ʱ 
	CRect rect;
	m_btnPng.GetClientRect(rect);
	m_btnPng.MoveWindow(CRect(rect.left,rect.top,rect.left + 128,rect.top + 128));
	m_btnPng.EnableToggle(TRUE); 
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CWMFCBtn::OnPaint()
{
	CPaintDC dc(this); // device context for painting
// 	Graphics graphics(dc);  
// 	Pen pen(Color(255, 0, 255));  
// 	graphics.DrawLine(&pen, 0, 0, 200, 100); 
// 	//Bitmap image(ToWChar("bg1.png"));  
// 	Rect rect =Rect( 0,0,m_Bg1.GetWidth(),m_Bg1.GetHeight()); 
// 	graphics.DrawImage(&m_Bg1,rect);
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}


void CWMFCBtn::OnBnClickedButtonUnnormal2()
{
	//GetDlgItem(IDC_BUTTON_UNNORMAL2)->PostMessage(WM_KILLFOCUS, 0, 0);
	int a = 0;
}
