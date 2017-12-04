
#include "stdafx.h"
#include "XFunCom.h"


///////////////////////////////////////////////////
// ��ȷ����㷨����ʱ�����(��������)
void LTimeCount::Start() // ��ʱ��ʼ
{
	QueryPerformanceFrequency( &Frequency );
	QueryPerformanceCounter  ( &old );
	UseTime = 0.0;
}
void LTimeCount::End() // ��ʱ����
{
	QueryPerformanceCounter( &Time );
	UseTime = (double) ( Time.QuadPart - old.QuadPart) / (double)Frequency.QuadPart;
// 	TRACE("Use time = %20.10f(s)\n", UseTime );
}

double LTimeCount::GetUseTime() // ����㷨����ʱ��(��λ:��)
{		
	return UseTime;
}
void LTimeCount::WaitTime(double waitTime)
{
	LTimeCount tt;
	tt.Start();
	tt.End();
	while(tt.GetUseTime()*1000 < waitTime)
	{
		tt.End();
	}
}

int GetRand(int min,int max)
{
	int m_nMax;
	m_nMax=RAND_MAX;
	return (int)(rand()*(max-min)/m_nMax+min);
}

/////////////////Ŀ¼��顢�ļ���顢Ŀ¼����
BOOL FolderExist(CString strPath)
{
	WIN32_FIND_DATA   wfd;
	BOOL rValue = FALSE;
	HANDLE hFind = FindFirstFile(strPath, &wfd);
	if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		rValue = TRUE;   
	}
	FindClose(hFind);
	return rValue;
}

BOOL FileExist(CString strFileName)
{
	CFileFind fFind;
	return fFind.FindFile(strFileName); 
}
void GetFileFromDir(CString csDirPath,std::vector<CString> &m_FileList )  
{  
	csDirPath+="\\*";  
	HANDLE file;  
	WIN32_FIND_DATA fileData;  
	char line[1024];  
	char fn[1000];  
	//mbstowcs(fn,csDirPath.GetBuffer(),999);  
	file = FindFirstFile(csDirPath.GetBuffer(), &fileData);  
	if (strstr(fileData.cFileName,".") == NULL)
	{
		m_FileList.push_back(fileData.cFileName);  
	}
	bool bState = false;  
	bState = FindNextFile(file, &fileData);  
	while(bState){  
		//wcstombs(line,(const char*)fileData.cFileName,259);  
		if (strstr(fileData.cFileName,".") == NULL)
		{
			m_FileList.push_back(fileData.cFileName);  
		} 
		bState = FindNextFile(file, &fileData);  
	}  
}  


BOOL CreateAllDirectories(CString strDir)
{
	//remove ending / if exists
	if(strDir.Right(1)=="\\")
		strDir=strDir.Left(strDir.GetLength()-1); 

	// base case . . .if directory exists
	if(GetFileAttributes(strDir)!=-1) 
		return FALSE;

	// recursive call, one less directory
	int nFound = strDir.ReverseFind('\\');
	if (nFound != -1)
		CreateAllDirectories(strDir.Left(nFound)); 

	// actual work
	BOOL bSuccess = FALSE;//�ɹ���־
	// 	CreateDirectory(strDir,NULL); 
	bSuccess = CreateDirectory(strDir, NULL) ? TRUE : FALSE;
	return bSuccess;
}
//�����ļ�����������ͬ��׺���ļ�
CString FindFileSameExtension(CString strPath,CString strExtension)
{
	CFileFind finder; 
	CString FileName;
	CString FilePath;
	bool bExist = finder.FindFile(strPath); 
	if(bExist) 
	{ 
		finder.FindNextFile();
		FileName = finder.GetFileName();
		FilePath = finder.GetFilePath();								//�ļ���ȫ·�� 
		CString Exten;
		Exten = PathFindExtension(FilePath);
		if (strcmp(Exten,strExtension) == 0)		//��ȡ�ļ��ĺ�׺���ж��Ƿ���Ҫ�ҵĺ�׺��ͬ
		{
			finder.Close();
			return finder.GetFileTitle();
		}
	}
	finder.Close();
	return "";
}

BOOL CreateFolder(CString strPath)
{
	// 	SECURITY_ATTRIBUTES attrib;
	// 	attrib.bInheritHandle = FALSE;
	// 	attrib.lpSecurityDescriptor = NULL;
	// 	attrib.nLength =sizeof(SECURITY_ATTRIBUTES);
	//���涨������Կ���ʡ�ԡ� ֱ��return ::CreateDirectory( path, NULL); ����
	return ::CreateDirectory( strPath, NULL/*&attrib*/);
} 

BOOL DelFilesOfDir(CString strDir)
{
	SHFILEOPSTRUCT    shFileOp;
	memset(&shFileOp,0,sizeof(shFileOp));

	shFileOp.fFlags = FOF_SILENT | FOF_NOCONFIRMATION ; 
	shFileOp.hNameMappings = NULL; 
	shFileOp.hwnd = NULL; 
	shFileOp.lpszProgressTitle = NULL; 
	shFileOp.pFrom = strDir; 
	shFileOp.pTo = NULL; 
	shFileOp.wFunc = FO_DELETE; 

	return SHFileOperation(&shFileOp)==0;
}
//ɾ���ļ���Ŀ¼(�ǿ�) �����ᵽ��ɾ��Ŀ¼�ķ���ֻ��ɾ����Ŀ¼�����ļ��У������Ŀ¼�����ļ�������Ŀ¼���Ͳ���ɾ���ˣ�VC�����û��ֱ�ӵĺ�����ֻ���ֶ�д��������ɾ���ˣ������ṩһ��ɾ���ǿ�Ŀ¼�ķ����� 

	bool DeleteDirectory(CString strDir)
{
	if(strDir.IsEmpty())   

	{ 

		RemoveDirectory(strDir); 

		return false; 

	} 

	//����ɾ���ļ������ļ��� 

	CFileFind   ff; 

	BOOL bFound = ff.FindFile(strDir+ _T("\\*"),0); 

	while(bFound) 

	{ 

		bFound = ff.FindNextFile(); 

		if(ff.GetFileName()== _T(".")||ff.GetFileName()== _T("..")) 

			continue; 

		//ȥ���ļ�(��)ֻ�������� 

		SetFileAttributes(ff.GetFilePath(),FILE_ATTRIBUTE_NORMAL); 

		if(ff.IsDirectory())  

		{   

			//�ݹ�ɾ�����ļ��� 

			DeleteDirectory(ff.GetFilePath()); 

			RemoveDirectory(ff.GetFilePath()); 

		} 

		else   

		{ 

			DeleteFile(ff.GetFilePath());   //ɾ���ļ� 

		} 

	} 

	ff.Close(); 

	//Ȼ��ɾ�����ļ��� 

	RemoveDirectory(strDir); 
	return true;
}
//����·��
BOOL CopyFolder(CString strFromDir,CString strToDir)
{
	SHFILEOPSTRUCT FileOp; 
	ZeroMemory((void*)&FileOp,sizeof(SHFILEOPSTRUCT));

	FileOp.fFlags = FOF_SILENT | FOF_NOCONFIRMATION ; 
	FileOp.hNameMappings = NULL; 
	FileOp.hwnd = NULL; 
	FileOp.lpszProgressTitle = NULL; 
	FileOp.pFrom = strFromDir; 
	FileOp.pTo = strToDir; 
	FileOp.wFunc = FO_COPY; 

	return SHFileOperation(&FileOp) == 0;
}

//�жϵ��Ƿ���Rect��
bool JudgePointInRect(CPoint pt,CRect JRect)
{
	if (pt.x<JRect.left || pt.x>JRect.right||pt.y<JRect.top||pt.y>JRect.bottom)
	{
		return false;
	}
	else
	{
		return true;
	}
}
/************************************************************************/
/*							�ַ������ò���						        */
/************************************************************************/
/************************************************************************
��������: str_to_hex 
��������: �ַ���ת��Ϊʮ������ 
�������: string �ַ��� cbuf ʮ������ len �ַ����ĳ��ȡ� 
�������: �� 
************************************************************************/   
int str_to_hex(char *string, unsigned char *cbuf, int len)
{
	BYTE high, low;  
	int idx, ii=0;  
	for (idx=0; idx<len; idx+=2)   
	{  
		high = string[idx];  
		low = string[idx+1];  

		if(high>='0' && high<='9')  
			high = high-'0';  
		else if(high>='A' && high<='F')  
			high = high - 'A' + 10;  
		else if(high>='a' && high<='f')  
			high = high - 'a' + 10;  
		else  
			return -1;  

		if(low>='0' && low<='9')  
			low = low-'0';  
		else if(low>='A' && low<='F')  
			low = low - 'A' + 10;  
		else if(low>='a' && low<='f')  
			low = low - 'a' + 10;  
		else  
			return -1;  

		cbuf[ii++] = high<<4 | low;  
	}  
	return 0; 
}
/**************************************************************************** 
��������: hex_to_str 
��������: ʮ������ת�ַ��� 
�������: ptr �ַ��� buf ʮ������ len ʮ�������ַ����ĳ��ȡ� 
�������: �� 
*****************************************************************************/   
void hex_to_str(char *ptr,unsigned char *buf,int len)  
{  
	for(int i = 0; i < len; i++)  
	{  
		sprintf(ptr, "%02x",buf[i]);  
		ptr += 2;  
	}  
}  
/**************************************************************************** 
��������: char_to_wchar 
��������: charתwchar
�������: ptr �����ַ��� buf����ַ����� 
�������: �� 
*****************************************************************************/   
void char_to_wchar(const char *ptr, wchar_t *buf)
{
	size_t len = strlen(ptr);
	size_t wlen = MultiByteToWideChar(CP_ACP, 0, (const char*)ptr, int(len), NULL, 0);
	/*buf = new wchar_t[wlen + 1];*/
	MultiByteToWideChar(CP_ACP, 0, (const char*)ptr, int(len), buf, int(wlen));
}
/************************************************************************
��������: CStringExistSymble 
��������: �ж��ַ������Ƿ��г����֡���ĸ����������ķǷ��ַ� 
�������: str �ַ��� 
�������: �� 
************************************************************************/
int IsCStringExistSymble(CString str)
{
	if (str.GetLength() == 0)
	{
		return 1;
	}
	char *FileN = str.GetBuffer(0);
	for (int i=0;i<str.GetLength();i++)
	{
		if ((FileN[i]>='0'&&FileN[i]<='9')||(FileN[i]>='a'&&FileN[i]<='z')||(FileN[i]>='A'&&FileN[i]<='Z')||FileN[i]>127||FileN[i]<0)
		{
			
		}
		else
		{
			return 2;
		}
	}
	return 0;
}
/************************************************************************/
/*						  �ַ������ò�������						    */
/************************************************************************/

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg dialog
// CProgressDlg::CProgressDlg(UINT nCaptionID)
// {
// 	m_nCaptionID = CG_IDS_PROGRESS_CAPTION;
// 	if (nCaptionID != 0)
// 		m_nCaptionID = nCaptionID;
// 
// 	m_bCancel=FALSE;
// 	m_nLower=0;
// 	m_nUpper=100;
// 	m_nStep=10;
// 	//{{AFX_DATA_INIT(CProgressDlg)
// 	// NOTE: the ClassWizard will add member initialization here
// 	//}}AFX_DATA_INIT
// 	m_bParentDisabled = FALSE;
// }
/************************************************************************/
/*								 ͼ�������ʼ                           */
/************************************************************************/
//���λͼͷ�ļ�
void FillBitmapInfo(BITMAPINFO* bmi, int width, int height, int bpp, int origin)
{
	assert( bmi && width >= 0 && height >= 0 && (bpp == 8 || bpp == 24 || bpp == 32));

	BITMAPINFOHEADER* bmih = &(bmi->bmiHeader);

	memset( bmih, 0, sizeof(*bmih));
	bmih->biSize = sizeof(BITMAPINFOHEADER);
	bmih->biWidth = width;
	bmih->biHeight = origin ? abs(height) : -abs(height);
	bmih->biPlanes = 1;
	bmih->biBitCount = (unsigned short)bpp;
	bmih->biCompression = BI_RGB;

	if( bpp == 8 )
	{
		RGBQUAD* palette = bmi->bmiColors;
		int i;
		for( i = 0; i < 256; i++ )
		{
			palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
			palette[i].rgbReserved = 0;
		}
	}
}
//����ʮ����
// void DrawCrossOnImage(IplImage *Img,CvPoint pt,int nLength,CvScalar rgb)
// {
// 	if (Img == NULL ||pt.x<0||pt.y<0||pt.x>Img->width||pt.y>Img->height)
// 	{
// 		return;
// 	}
// 	CvPoint pt1,pt2,pt3,pt4;
// 	pt1.x = pt.x-nLength<0?0:pt.x-nLength;
// 	pt1.y = pt.y;
// 	pt2.x = pt.x+nLength>Img->width?Img->width:pt.x+nLength;
// 	pt2.y = pt.y;
// 	pt3.x = pt.x;
// 	pt3.y = pt.y-nLength<0?0:pt.y-nLength;
// 	pt4.x = pt.x;
// 	pt4.y = pt.y+nLength>Img->height?Img->height:pt.y+nLength;
// 	cvLine(Img,pt1,pt2,rgb,2);
// 	cvLine(Img,pt3,pt4,rgb,2);
// }
/************************************************************************/
/* �������ܣ���DC�ϻ���			ͼ��                                    */
/************************************************************************/
void DrawGraphOnDC(CDC *pDC,DrawShape DShape)
{
	ASSERT(pDC);
	CPoint pt1,pt2,pt3,pt4;
	CPen pen,pen1,*oldpen;
	CRect rect;
	switch(DShape.Shape)
	{
	case SHAPE_RECTANGLE_R:
		break;
	case SHAPE_RECTANGLE_P:
		pt1.x = DShape.CterPoint.x - DShape.nLength;
		pt1.y = DShape.CterPoint.y - DShape.nLength;
		pt2.x = DShape.CterPoint.x + DShape.nLength;
		pt2.y = DShape.CterPoint.y - DShape.nLength;
		pt3.x = DShape.CterPoint.x + DShape.nLength;
		pt3.y = DShape.CterPoint.y + DShape.nLength;
		pt4.x = DShape.CterPoint.x - DShape.nLength;
		pt4.y = DShape.CterPoint.y + DShape.nLength;
		
		pen.CreatePen(PS_SOLID,1,DShape.rgb);
		oldpen=pDC->SelectObject(&pen);
		//����ֱ��
		pDC->MoveTo(pt1.x,pt1.y);
		pDC->LineTo(pt2.x,pt2.y);
		pDC->LineTo(pt3.x,pt3.y);
		pDC->LineTo(pt4.x,pt4.y);
		pDC->LineTo(pt1.x,pt1.y);
		pDC->SelectObject(oldpen);
		pen.DeleteObject();
		break;
	case SHAPE_CIRCLE:
		pen.CreatePen(PS_SOLID,1,DShape.rgb);
		oldpen=pDC->SelectObject(&pen);
		rect.left = DShape.CterPoint.x - DShape.nLength;
		rect.top = DShape.CterPoint.y - DShape.nLength;
		rect.right = DShape.CterPoint.x + DShape.nLength;
		rect.bottom = DShape.CterPoint.y + DShape.nLength;
		pDC->Arc(rect,CPoint(0,0),CPoint(0,0));
		pDC->SelectObject(oldpen);
		pen.DeleteObject();
		break;
	case SHAPE_CROSS:
		break;
	case SHAPE_RULER:
		break;
	default:
		break;
	}
}
/************************************************************************/
/* �������ܣ���DC�ϻ���ͼ��		                                        */
/*	   ������Img ͼ�� MemDc  Ŀ��DC								        */
/************************************************************************/
// void DrawImageOnMemDc(IplImage *Img,CDC *pMemDC,CBitmap *bmp,float fImageScale)
// {
// 	ASSERT(Img);
// 	ASSERT(pMemDC);
//   	uchar buffer[sizeof(BITMAPINFOHEADER) + 1024];
//   	BITMAPINFO* bmi = (BITMAPINFO*)buffer;
//   	int bmp_w = Img->width;
//   	int bmp_h = Img->height;
//   
//   	int bpp = Img ? (Img->depth & 255)*Img->nChannels : 0;
//   	//����cvvimage��Bpp()����
//   
//   	FillBitmapInfo( bmi, bmp_w, bmp_h, bpp,Img->origin );
//   
//   	HBITMAP hOldBitmap;
//   	CBitmap *pOldBit = NULL;
//   
// 	pOldBit = pMemDC->SelectObject(bmp);									//��λͼѡ����ڴ�DC
// 	pMemDC->FillSolidRect(CRect(0,0,bmp_w,bmp_h),RGB(255,255,255)); //��ԭ���������ͻ�������Ȼ���Ǻ�ɫ
// 	pMemDC->SetStretchBltMode(COLORONCOLOR);
// 
// 	int t = StretchDIBits(
// 		pMemDC->GetSafeHdc(),0,0,int(Img->width * fImageScale+0.5), int(Img->height * fImageScale+0.5),0,0, bmp_w, bmp_h,
// 		Img->imageData, bmi, DIB_RGB_COLORS,SRCCOPY );
//   	pMemDC->SelectObject(&hOldBitmap);
//   	if (hOldBitmap)
//   	{
//   		DeleteObject(hOldBitmap);
//   		hOldBitmap=NULL;
//   	}
// }
/************************************************************************/
/*								ͼ���������                             */
/************************************************************************/
// CProgressDlg::~CProgressDlg()
// {
// 	if(m_hWnd!=NULL)
// 		DestroyWindow();
// }
// 
// BOOL CProgressDlg::DestroyWindow()
// {
// 	ReEnableParent();
// 	return CDialog::DestroyWindow();
// }
// 
// void CProgressDlg::ReEnableParent()
// {
// 	if(m_bParentDisabled && (m_pParentWnd!=NULL))
// 		m_pParentWnd->EnableWindow(TRUE);
// 	m_bParentDisabled=FALSE;
// }
// 
// BOOL CProgressDlg::Create(CWnd *pParent)
// {
// 	// Get the true parent of the dialog
// 	m_pParentWnd = CWnd::GetSafeOwner(pParent);
// 
// 	// m_bParentDisabled is used to re-enable the parent window
// 	// when the dialog is destroyed. So we don't want to set
// 	// it to TRUE unless the parent was already enabled.
// 
// 	if((m_pParentWnd!=NULL) && m_pParentWnd->IsWindowEnabled())
// 	{
// 		m_pParentWnd->EnableWindow(FALSE);
// 		m_bParentDisabled = TRUE;
// 	}
// 
// 	if(!CDialog::Create(CProgressDlg::IDD,pParent))
// 	{
// 		ReEnableParent();
// 		return FALSE;
// 	}
// 
// 	return TRUE;
// }
// 
// void CProgressDlg::DoDataExchange(CDataExchange* pDX)
// {
// 	CDialog::DoDataExchange(pDX);
// 	//{{AFX_DATA_MAP(CProgressDlg)
// 	DDX_Control(pDX, CG_IDC_PROGDLG_PROGRESS, m_Progress);
// 	//}}AFX_DATA_MAP
// }
// 
// BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
// 	//{{AFX_MSG_MAP(CProgressDlg)
// 	//}}AFX_MSG_MAP
// 	ON_BN_CLICKED(IDCANCEL, &CProgressDlg::OnBnClickedCancel)
// END_MESSAGE_MAP()
// 
// void CProgressDlg::SetStatus(LPCTSTR lpszMessage)
// {
// // 	ASSERT(m_hWnd); // Don't call this _before_ the dialog has
// // 	// been created. Can be called from OnInitDialog
// // 	CWnd *pWndStatus = GetDlgItem(CG_IDC_PROGDLG_STATUS);
// // 	// Verify that the static text control exists
// // 	ASSERT(pWndStatus!=NULL);
// // 	pWndStatus->SetWindowText(lpszMessage);
// }
// 
// void CProgressDlg::OnCancel()
// {
// 	m_bCancel=TRUE;
// }
// 
// void CProgressDlg::SetRange(int nLower,int nUpper)
// {
// 	m_nLower = nLower;
// 	m_nUpper = nUpper;
// 	m_Progress.SetRange(nLower,nUpper);
// }
// 
// int CProgressDlg::SetPos(int nPos)
// {
// 	PumpMessages();
// 	int iResult = m_Progress.SetPos(nPos);
// 	UpdatePercent(nPos);
// 	return iResult;
// }
// 
// int CProgressDlg::SetStep(int nStep)
// {
// 	m_nStep = nStep; // Store for later use in calculating percentage
// 	return m_Progress.SetStep(nStep);
// }
// 
// int CProgressDlg::OffsetPos(int nPos)
// {
// 	PumpMessages();
// 	int iResult = m_Progress.OffsetPos(nPos);
// 	UpdatePercent(iResult+nPos);
// 	return iResult;
// }
// 
// int CProgressDlg::StepIt()
// {
// 	PumpMessages();
// 	int iResult = m_Progress.StepIt();
// 	UpdatePercent(iResult+m_nStep);
// 	return iResult;
// }
// 
// void CProgressDlg::PumpMessages()
// {
// 	// Must call Create() before using the dialog
// 	ASSERT(m_hWnd!=NULL);
// 
// 	MSG msg;
// 	// Handle dialog messages
// 	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
// 	{
// 		if(!IsDialogMessage(&msg))
// 		{
// 			TranslateMessage(&msg);
// 			DispatchMessage(&msg);  
// 		}
// 	}
// }
// 
// BOOL CProgressDlg::CheckCancelButton()
// {
// 	// Process all pending messages
// 	PumpMessages();
// 
// 	// Reset m_bCancel to FALSE so that
// 	// CheckCancelButton returns FALSE until the user
// 	// clicks Cancel again. This will allow you to call
// 	// CheckCancelButton and still continue the operation.
// 	// If m_bCancel stayed TRUE, then the next call to
// 	// CheckCancelButton would always return TRUE
// 
// 	BOOL bResult = m_bCancel;
// 	m_bCancel = FALSE;
// 
// 	return bResult;
// }
// 
// void CProgressDlg::UpdatePercent(int nNewPos)
// {
// 	CWnd *pWndPercent = GetDlgItem(CG_IDC_PROGDLG_PERCENT);
// 	int nPercent;
// 
// 	int nDivisor = m_nUpper - m_nLower;
// 	ASSERT(nDivisor>0);  // m_nLower should be smaller than m_nUpper
// 
// 	int nDividend = (nNewPos - m_nLower);
// 	ASSERT(nDividend>=0);   // Current position should be greater than m_nLower
// 
// 	nPercent = nDividend * 100 / nDivisor;
// 
// 	// Since the Progress Control wraps, we will wrap the percentage
// 	// along with it. However, don't reset 100% back to 0%
// 	if(nPercent!=100)
// 		nPercent %= 100;
// 
// 	// Display the percentage
// 	CString strBuf;
// 	strBuf.Format(_T("%d%c"),nPercent,_T('%'));
// 
// 	CString strCur; // get current percentage
// 	pWndPercent->GetWindowText(strCur);
// 
// 	if (strCur != strBuf)
// 		pWndPercent->SetWindowText(strBuf);
// }
// 
// /////////////////////////////////////////////////////////////////////////////
// // CProgressDlg message handlers
// 
// BOOL CProgressDlg::OnInitDialog() 
// {
// 	CDialog::OnInitDialog();
// 	m_Progress.SetRange(m_nLower,m_nUpper);
// 	m_Progress.SetStep(m_nStep);
// 	m_Progress.SetPos(m_nLower);
// 
// 	CString strCaption;
// 	VERIFY(strCaption.LoadString(m_nCaptionID));
// 	SetWindowText(strCaption);
// 
// 	return TRUE;  
// }
// 
// 
// void WaitTimeShowProgressDlg(int waitTime)
// {
// 	CProgressDlg * MsgHandler = new CProgressDlg();
// 	MsgHandler->Create(NULL);
// 	MsgHandler->SetStatus("Start OT");
// 	for(int i=0; i<10; i++)
// 	{
// 		Sleep(waitTime/10);
// 		MsgHandler->SetPos(100 * i/10);
// 	}
// 	MsgHandler->DestroyWindow();
// 	delete  MsgHandler;
// }
// 
// void CProgressDlg::OnBnClickedCancel()
// {
// 	// TODO: �ڴ���ӿؼ�֪ͨ����������
// 	CDialog::OnCancel();
// }

//��ȡ�������е�ǰ·��
CString GetCurRunDir()
{
	CString str = "";
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL,szFilePath,MAX_PATH);
	(_tcsrchr(szFilePath,_T('\\')))[1] = 0;
	return str = szFilePath;
}

CCriticalSection g_filelock;

void CWlog(CString mlog)	{
	g_filelock.Lock();
	CFile test;
	CString ttt;
	SYSTEMTIME time;
	GetLocalTime(&time);
	ttt.Format("%s:%d/%d/%d/ %d:%d:%d\r\n",mlog,time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond);\
	TRACE(ttt);
	test.Open(_T("LOG\\log.txt"),CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
	test.SeekToEnd();
	test.Write(ttt,ttt.GetLength());
	test.Close();
	g_filelock.Unlock();
}

CString GetAppPath()
{
	CString Tmp;
	CHAR filepath[MAX_PATH];
	TCHAR driver[MAX_PATH];
	TCHAR fullPath[MAX_PATH];
	TCHAR namePath[MAX_PATH];
	GetModuleFileName(NULL,filepath,MAX_PATH);
	_tsplitpath(filepath,driver,fullPath,namePath,namePath);
	Tmp.Format("%s%s",driver,fullPath);
	return Tmp;
}

