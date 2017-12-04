#include "StdAfx.h"
#include "Camera.h"
#include "YCIni.h"
#include "ImageingSource.h"
#include "KSJCamera.h"
#include "YPtgCamera.h"
#include "GigECamera.h"
//#include "DSCamera.h"

CCamera::CCamera()
{
	m_nDeviceNum = 0;
	
//	pPtgCam = NULL;
	
	for(int i = 0; i < MAX_DEVICE; i++)
	{
		m_pCameraType[i] = NO_CAMERA;
		m_pConnectView[i] = NULL;
		m_pImage[i] = NULL; 
	}
	CameraApiInit(); //KSJ
	InitLibrary();   //IMG
	
	
}

int CCamera::flag=0;
CCamera::~CCamera()
{
	for (int i=0;i<m_nDeviceNum;++i)
	{
		PauseCamera(i,true);
	}	

	++flag;
	CameraApiUninit();
	if(flag>1)
	ExitLibrary();
}

int LookUpCameraTypeIndex(CString cameType)
{
	if(cameType == "KSJ")
		return 1;
	else if(cameType == "IMG")
		return 5;
	else if(cameType == "PTG")
		return 4;
	else if(cameType == "DS")
		return 6;
	else
		return 0;
}

void CCamera::CameraApiInit()
{
	KSJ_Init();
}
void CCamera::CameraApiUninit()
{
	KSJ_UnInit();
}

int CCamera::DetectCamera(MYDEVICEINFO *deviceInfo)
{
	int i;
	int uNo = 0;
	//KSJ
	int nDeviceNum = KSJ_DeviceGetCount();
	for(i = 0; i < nDeviceNum; i++ )
	{
		KSJ_DEVICETYPE deviceType;
		KSJ_DeviceGetInformation( i, &deviceType, &(deviceInfo[uNo].nIndex), &(deviceInfo[uNo].wFirmwareVersion) );//������ֱ���
		KSJ_CaptureGetSize( i, &deviceInfo[uNo].m_nWidth, &deviceInfo[uNo].m_nHeight );
	
		deviceInfo[uNo].m_nCameraType = 1;
		uNo++;
	}
	//PTG
	YPtgCamera *pPtgCam = NULL;
	BusManager   busMgr;
	unsigned int num;
	busMgr.GetNumOfCameras(&num);
	nDeviceNum = num;
	for(i = 0; i < nDeviceNum; i++ )
	{
		if (NULL != pPtgCam)       // Lgy
			delete pPtgCam;		

		pPtgCam = new YPtgCamera;  //
		//pPtgCam->GetDeviceInformation(deviceInfo[uNo].nIndex,deviceInfo[uNo].wFirmwareVersion,deviceInfo[uNo].m_nWidth,deviceInfo[uNo].m_nHeight);
		pPtgCam->GetDeviceInformation(deviceInfo[uNo].Str_index,deviceInfo[uNo].wFirmwareVersion,deviceInfo[uNo].m_nWidth,deviceInfo[uNo].m_nHeight); //Lgy 8 -24
		deviceInfo[uNo].m_nCameraType = 4;
		uNo++;
	}
	
	//IMG
		YImageingSource *imgcamera=new YImageingSource;
		nDeviceNum=imgcamera->GetDeviceNumber();

		LONGLONG temple=0;
		
		for(i=0;i<nDeviceNum;++i)
		{
			//int m=imgcamera->GetDeviceInformation(temple,deviceInfo[uNo].wFirmwareVersion,deviceInfo[uNo].m_nWidth,deviceInfo[uNo].m_nHeight,i);
			int m=imgcamera->GetDeviceInformation(deviceInfo[uNo].Str_index,deviceInfo[uNo].wFirmwareVersion,deviceInfo[uNo].m_nWidth,deviceInfo[uNo].m_nHeight,i);
			if(m==-1)
			{
				AfxMessageBox("δ�����豸��");
				break;
			}
			if (m==-2)
			{
				AfxMessageBox("��ȡ���к�ʧ�ܣ�");
				break;
			}
			if (m==-3)
			{
				AfxMessageBox("�����豸��Ϣʧ��");
				break;
			}
			deviceInfo[uNo].nIndex=int (temple);
			deviceInfo[uNo].m_nCameraType = 5;
			uNo++;
		}		
		//DS
		//CDSCamera *dscamera = new CDSCamera;


	return uNo;
}

int CCamera::DetectCamera(MYDEVICEINFO *deviceInfo,CapturePara *caminfo)
{
	int i;
	int uNo = 0;

	//KSJ
	int nDeviceNum = KSJ_DeviceGetCount();
	for(i = 0; i < nDeviceNum; i++ )
	{
		KSJ_DEVICETYPE deviceType;
		//KSJ_DeviceGetInformation( i, &deviceType, &(deviceInfo[uNo].nIndex), &(deviceInfo[uNo].wFirmwareVersion) );//������ֱ���
		KSJ_DeviceGetInformation( i, &deviceType, &(deviceInfo[uNo].nIndex), &(deviceInfo[uNo].wFirmwareVersion) );//������ֱ��� Lgy 8 -24
		// 8-24
		char tempindex[10]={0};
		itoa(deviceInfo[uNo].nIndex,tempindex,10);    
		deviceInfo[uNo].Str_index = tempindex;
		//
		KSJ_CaptureGetSize( i, &deviceInfo[uNo].m_nWidth, &deviceInfo[uNo].m_nHeight );
		KSJ_PreviewGetFrameRate(i,&caminfo[uNo].m_fFrameRate);     //Lgy
		
		deviceInfo[uNo].m_nCameraType = 1;
		uNo++;
	}
	//PTG
	BusManager   busMgr;
	unsigned int num;
	YPtgCamera *pPtgCam = new YPtgCamera ;
	busMgr.GetNumOfCameras(&num);
	nDeviceNum = num;
	for(i = 0; i < nDeviceNum; i++ )
	{

		//pPtgCam->GetDeviceInformation(deviceInfo[uNo].nIndex,deviceInfo[uNo].wFirmwareVersion,deviceInfo[uNo].m_nWidth,deviceInfo[uNo].m_nHeight);
		pPtgCam->GetDeviceInformation(deviceInfo[uNo].Str_index,deviceInfo[uNo].wFirmwareVersion,
			deviceInfo[uNo].m_nWidth,deviceInfo[uNo].m_nHeight); //Lgy 8-24
		caminfo[uNo].m_fFrameRate = pPtgCam->GetFrameRate();     //Lgy
		deviceInfo[uNo].m_nCameraType = 4;
		uNo++;
	}
	
	//IMG
		YImageingSource *imgcamera = new YImageingSource;
		nDeviceNum = imgcamera->GetDeviceNumber();

	//	LONGLONG temple = 0; //Lgy 8-24
		
		for(i=0;i<nDeviceNum;++i)
		{
			//int m = imgcamera->GetDeviceInformation(temple,deviceInfo[uNo].wFirmwareVersion,deviceInfo[uNo].m_nWidth,deviceInfo[uNo].m_nHeight,i);  //8-24
			int m = imgcamera->GetDeviceInformation(deviceInfo[uNo].Str_index,deviceInfo[uNo].wFirmwareVersion,
				deviceInfo[uNo].m_nWidth,deviceInfo[uNo].m_nHeight,i);  //8-24
			caminfo[uNo].m_fFrameRate = imgcamera->GetFPS();            //Lgy  8-19
			if(m == -1)
			{
				AfxMessageBox("δ�����豸��");
				break;
			}
			if (m == -2)
			{
				AfxMessageBox("��ȡ���к�ʧ�ܣ�");
				break;
			}
			if (m == -3)
			{
				AfxMessageBox("�����豸��Ϣʧ��");
				break;
			}
		//	deviceInfo[uNo].nIndex=int (temple);
			deviceInfo[uNo].m_nCameraType = 5;
			uNo++;
		}		
// 		//DS
// 		CDSCamera *dscamera = new CDSCamera;
// 		nDeviceNum = dscamera->GetDeviceNum();
	//	emDSCameraStatus status;
	//	
// 		for (i = 0;i < nDeviceNum; i++ )
// 		{
// 			dscamera->GetDeviceInformation(deviceInfo[uNo].Str_index,deviceInfo[uNo].wFirmwareVersion,
// 				deviceInfo[uNo].m_nWidth,deviceInfo[uNo].m_nHeight,i);
// 			deviceInfo[uNo].m_nCameraType = 6;
// 			uNo ++;
// 		}
		
	
	return uNo;
}


bool CCamera::OpenFixCamera(int uNo, MYDEVICEINFO deviceInfo, CapturePara para, CWnd *pWnd)
{
	if(uNo >= MAX_DEVICE)
	{
		AfxMessageBox("���õ���������������֧������");
		return false;
	}
	m_Capture[uNo].m_nCameraType = deviceInfo.m_nCameraType;
	m_Capture[uNo].m_nCameraIndex = deviceInfo.nIndex;
	m_Capture[uNo].m_uNo = uNo;
	if(m_Capture[uNo].ConnectCamera())
	{
		m_pImage[uNo] = m_Capture[uNo].m_pCaptureImage;
		SetConnectView(uNo, pWnd);
	}
	else
		return false;
	return true;
}


int CCamera::ConnectCamera(IMGSHOW imgshow[],int maxdevice)
{
	m_nDeviceNum = 0;

	int i,nCamNum;
	YCIni iniFile;
	CFileFind fileFind;
	if (!fileFind.FindFile(m_sCameraInfoPath))
	{
		AfxMessageBox("�ļ�ȱʧ!");
	}

	iniFile.Read(m_sCameraInfoPath);
	bool T = iniFile.GetValue("������Ϣ", "�������", nCamNum);
	if(nCamNum > MAX_DEVICE)
	{
		AfxMessageBox("���õ���������������֧������");
		return FALSE;
	}
	//for(i=0; i<nCamNum; i++)      //Lgy
	for(i = 0; i < MAX_DEVICE; i++)
	{
		CString strNo, strCamType;
		CString uCamNO;
		int     uCamNo;
		int     uGain;
		float   uExpouse;
		strNo.Format("���%d", i+1);
		iniFile.GetValue(strNo, "Ʒ��", strCamType);
		iniFile.GetValue(strNo, "���к�", uCamNO);
		iniFile.GetValue(strNo, "���к�", uCamNo);
		iniFile.GetValue(strNo, "����", uGain);
		iniFile.GetValue(strNo, "�ع�ʱ��",uExpouse);
		m_Capture[i].m_nCameraType = LookUpCameraTypeIndex(strCamType);
		m_Capture[i].m_nCameraIndex = uCamNo;
		m_Capture[i].m_nGain = uGain;
		m_Capture[i].m_nExpouse =uExpouse;
		m_Capture[i].m_uNo = i;
		m_Capture[i].m_TempIndex = i;                // Lgy 
		if(m_Capture[i].ConnectCamera(imgshow,maxdevice,i))  //
		{
			m_nDeviceNum++;
			m_pImage[i] = m_Capture[i].m_pCaptureImage;
		}
	}
	iniFile.Clear();
	return m_nDeviceNum;
}

int CCamera::ConnectCamera()
{
	m_nDeviceNum = 0;
	
	int i,nCamNum;
	YCIni iniFile;
	CFileFind fileFind;
	if (!fileFind.FindFile(m_sCameraInfoPath))
	{
		AfxMessageBox("�ļ�ȱʧ!");
	}

	iniFile.Read(m_sCameraInfoPath);
	bool T = iniFile.GetValue("������Ϣ", "�������", nCamNum);
	if(nCamNum > MAX_DEVICE)
	{
		AfxMessageBox("���õ���������������֧������");
		return FALSE;
	}
	//for(i=0; i<nCamNum; i++)      //Lgy
	for(i = 0; i < MAX_DEVICE; i++)
	{
		CString strNo, strCamType;
		CString uCamNO;
		int     uCamNo;
		int     uGain;
		float   uExpouse;
		strNo.Format("���%d", i+1);
		iniFile.GetValue(strNo, "Ʒ��", strCamType);
		iniFile.GetValue(strNo, "���к�", uCamNO);
		iniFile.GetValue(strNo, "���к�", uCamNo);
		iniFile.GetValue(strNo, "����", uGain);
		iniFile.GetValue(strNo, "�ع�ʱ��",uExpouse);
		m_Capture[i].m_nCameraType = LookUpCameraTypeIndex(strCamType);
		m_Capture[i].m_nCameraIndex = uCamNo;
		m_Capture[i].m_nGain = uGain;
		m_Capture[i].m_nExpouse =uExpouse;
		m_Capture[i].m_uNo = i;
		m_Capture[i].m_TempIndex = i;            // Lgy 
		if(m_Capture[i].ConnectCamera()) 
		{
			m_nDeviceNum++;
			m_pImage[i] = m_Capture[i].m_pCaptureImage;	
		}
	}
	iniFile.Clear();
	return m_nDeviceNum;
}

int  CCamera::ConnectSelCamera(int nCamIndex,int CamType, int uCamNo)
{

	m_Capture[nCamIndex].m_nCameraType = CamType;
	m_Capture[nCamIndex].m_nCameraIndex = uCamNo;
	//int k =m_Capture[nCamIndex].m_uNo ;

	if(m_Capture[nCamIndex].ConnectCamera())
	{
		m_pImage[nCamIndex] = m_Capture[nCamIndex].m_pCaptureImage;
		m_Capture[nCamIndex].m_TempIndex = nCamIndex;
		m_nDeviceNum++;
	}

	return m_nDeviceNum;
}


BOOL CCamera::PauseCamera(int nCamIndex, BOOL bIsWorking)
{
	BOOL bIsOK = FALSE;
	//if (nCamIndex >= m_nDeviceNum)
	if (nCamIndex >= MAX_DEVICE) //Lgy
	{
		AfxMessageBox("������Խ�磬��������豸��������ȷ");
		return FALSE;
	}
	bIsOK = m_Capture[nCamIndex].PauseCamera(bIsWorking);
	return bIsOK;

}

BOOL CCamera::CaptureImage(int nCamIndex)
{
	BOOL bIsOK = FALSE;
	//if (nCamIndex >= m_nDeviceNum)
	if (nCamIndex >= MAX_DEVICE) //Lgy
	{
		AfxMessageBox("������Խ�磬��������豸��������ȷ");
		return FALSE;
	}
	bIsOK = m_Capture[nCamIndex].CaptureImage();
	return bIsOK;
}

BOOL CCamera::SoftTrigger(int nCamIndex)
{
	BOOL bIsOK = FALSE;
	//if (nCamIndex >= m_nDeviceNum)
	if (nCamIndex >= MAX_DEVICE) //Lgy
	{
		AfxMessageBox("������Խ�磬��������豸��������ȷ");
		return FALSE;
	}
	bIsOK = m_Capture[nCamIndex].SoftTrigger();
	return bIsOK;
}

BOOL CCamera::SetExposureTime(int nCamIndex, float nTime)
{
	BOOL bIsOK = FALSE;
	//if (nCamIndex >= m_nDeviceNum)
	if (nCamIndex >= MAX_DEVICE) //Lgy
	{
		AfxMessageBox("������Խ�磬��������豸��������ȷ");
		return FALSE;
	}
	bIsOK = m_Capture[nCamIndex].SetExposureTime(nTime);
	m_pExposureTime[nCamIndex] = nTime;
	return bIsOK;
}

BOOL CCamera::SetFreeMode(int nCamIndex)
{
	BOOL bIsOK = FALSE;
	//if (nCamIndex >= m_nDeviceNum)
	if (nCamIndex >= MAX_DEVICE) //Lgy
	{
		AfxMessageBox("������Խ�磬��������豸��������ȷ");
		return FALSE;
	}
	bIsOK = m_Capture[nCamIndex].SetFreeMode();
	return bIsOK;
}

BOOL CCamera::SetSoftTriggerMode(int nCamIndex)
{
	BOOL bIsOK = FALSE;
	//if (nCamIndex >= m_nDeviceNum)
	if (nCamIndex >= MAX_DEVICE) //Lgy
	{
		AfxMessageBox("������Խ�磬��������豸��������ȷ");
		return FALSE;
	}
	bIsOK = m_Capture[nCamIndex].SetSoftTriggerMode();
	return bIsOK;
}

BOOL CCamera::SetContrast(int nCamIndex,int Contrast)
{
	BOOL bIsOK = FALSE;
	//if (nCamIndex >= m_nDeviceNum)
	if (nCamIndex >= MAX_DEVICE) //Lgy
	{
		AfxMessageBox("������Խ�磬��������豸��������ȷ");
		return FALSE;
	}
	bIsOK = m_Capture[nCamIndex].SetContrast(Contrast);
	
	return bIsOK;
}

BOOL CCamera::CloseCamera(int nCamIndex)
{
	BOOL bIsOk = FALSE;
	bIsOk = m_Capture[nCamIndex].CloseCamera();
	return bIsOk;
}

BOOL CCamera::SetBrightness(int nCamIndex,int Brightness)
{
	BOOL bIsOK = FALSE;
	//if (nCamIndex >= m_nDeviceNum)
	if (nCamIndex >= MAX_DEVICE) //Lgy
	{
		AfxMessageBox("������Խ�磬��������豸��������ȷ");
		return FALSE;
	}
	bIsOK = m_Capture[nCamIndex].SetBrightness(Brightness);
	return bIsOK;
}


ParaRange CCamera::GetParamRange(int nCamIndex,ParaRange para)
{
	//BOOL bIsOk = false;
	if (nCamIndex >= MAX_DEVICE) //Lgy
	{
		AfxMessageBox("������Խ�磬��������豸��������ȷ");
	//	return FALSE;
	}
	ParaRange nret = m_Capture[nCamIndex].GetParamRange(nCamIndex,para);

	return nret;
}

BOOL CCamera::JudgeCameraType(int m_nCameraIndex)
{
	
	if (m_nCameraIndex >= MAX_DEVICE) //Lgy
	{
		AfxMessageBox("������Խ�磬��������豸��������ȷ");
		return FALSE;
	}
	int nRet = m_Capture[m_nCameraIndex].JudgeCameraType(m_nCameraIndex);
	return nRet;
}

BOOL CCamera::SetGain(int nCamIndex, int Gain)
{
	BOOL bIsOK = FALSE;
	//if (nCamIndex >= m_nDeviceNum)
	if (nCamIndex >= MAX_DEVICE) //Lgy
	{
		AfxMessageBox("������Խ�磬��������豸��������ȷ");
		return FALSE;
	}
	bIsOK = m_Capture[nCamIndex].SetGain(Gain);
	m_Gain[nCamIndex] = Gain;
	return bIsOK;
}

void CCamera::SetConnectView(int nCamIndex, CWnd *pWnd)
{
	if (nCamIndex < 0 || nCamIndex >= MAX_DEVICE)
	{
		return;
	}
	// 		if (m_pConnectView[nCamIndex] != NULL && m_pConnectView[nCamIndex]->GetSafeHwnd() != NULL)
	//  			m_pConnectView[nCamIndex]->Invalidate(FALSE);
	m_pConnectView[nCamIndex] = pWnd;
	m_Capture[nCamIndex].SetConnectView(pWnd);
}

YCapture::YCapture()
{
	//AfxMessageBox("����YCapture");
	m_pCautureView = NULL;
	m_KSJCamera = NULL;
	m_IMGCamera = NULL;
	m_PTGCamera = NULL;
//	m_DSCamera = NULL;
	ExIndex = 0;
	m_TempIndex = -1;
	angle=ROTE_0;
 	for (int i = 0; i < MAX_DEVICE; i++)
 		ExCamIndex[i] = -1;
}

YCapture::~YCapture()
{
	AfxMessageBox("����YCapture");
	if(m_KSJCamera != NULL)
		delete m_KSJCamera;
	if(m_IMGCamera!=NULL)
		delete m_IMGCamera;
	
}

void YCapture::SetConnectView(CWnd *pWnd)//��ʾ
{
	m_pCautureView = pWnd;
	switch(m_nCameraType)
	{
	case KSJ:
		{
			m_KSJCamera->m_pConnectView[0] = pWnd;		
			CRect rect;
			pWnd->GetClientRect(&rect);
			m_KSJCamera->SetPreviewPos(0,pWnd->m_hWnd, rect);	
			break;
		}
	case ACU:
		break;
	case BAS:
		break;
	
	case PTG:
		{
			m_PTGCamera->m_pConnectView=pWnd;
			CRect rect;
			pWnd->GetClientRect(&rect);
			m_PTGCamera->SetPreviewPos(pWnd->m_hWnd,rect);
			break;
		}
		
	case IMG:                                    //Lgy 8-21ԭ���ⲿ��Ϊע��״̬
		{
			m_IMGCamera->m_pConnectView=pWnd;				
			CRect rect;
			pWnd->GetClientRect(&rect);
			m_IMGCamera->SetPreviewPos(pWnd->m_hWnd, rect);
			break;
		}
		
// 	case DS:
// 		{
// 			m_DSCamera->m_pConnectView=pWnd;				
// 			CRect rect;
// 			pWnd->GetClientRect(&rect);
// 			//m_DSCamera->SetPreviewPos(pWnd->m_hWnd, rect);
// 			//	m_DSCamera->Set
// 			break;
// 		}
		
	default:
		break;
	}
}

bool YCapture::SetSoftTriggerMode()
{
	bool bIsOK = false;
	switch(m_nCameraType)
	{
	case KSJ:
		{
			bIsOK = m_KSJCamera->SetSoftTriggerMode(0);
			break;
		}
	case ACU:
		//		bIsOK = m_ACUCamera.PauseCamera(m_pCameraIndex[nCamIndex], bIsWorking);
		break;
	case BAS:
		//		bIsOK = m_BaslerCamera.PauseCamera(m_pCameraIndex[nCamIndex], bIsWorking);
		break;
	case PTG:
		{
			m_PTGCamera->CheckSoftwareTriggerReady();   //Lgy  8-26��ѭ��������
			bIsOK = m_PTGCamera->SetSoftTriggerMode();
			break;
		}
	case IMG:
		{
			bIsOK=m_IMGCamera->SetSoftTriggerMode();
			break;
		}
		//		bIsOK = m_IMGCamera.PauseCamera(m_pCameraIndex[nCamIndex], bIsWorking);
		break;
	default:
		break;
	}
	return bIsOK;
}

bool YCapture::SetFreeMode()
{
	bool bIsOK = false;
	switch(m_nCameraType)
	{
	case KSJ:
		{
			bIsOK = m_KSJCamera->SetFreeMode(0);
			break;
		}
	case ACU:
		//		bIsOK = m_ACUCamera.PauseCamera(m_pCameraIndex[nCamIndex], bIsWorking);
		break;
	case BAS:
		//		bIsOK = m_BaslerCamera.PauseCamera(m_pCameraIndex[nCamIndex], bIsWorking);
		break;
	case PTG:
		{
			bIsOK = m_PTGCamera->SetFreeMode();
			break;
		}
		//		bIsOK = m_PointGreyCamera.PauseCamera(m_pCameraIndex[nCamIndex], bIsWorking);
		break;
	case IMG:
		{
			bIsOK = m_IMGCamera->SetFreeMode();
			break;
		}
		//		bIsOK = m_IMGCamera.PauseCamera(m_pCameraIndex[nCamIndex], bIsWorking);
		break;
	default:
		break;
	}
	return bIsOK;
}

bool YCapture::SetExposureTime(float millSeconds)
{
	bool bIsOK = false;
	switch(m_nCameraType)
	{
	case KSJ:
		{
			bIsOK = m_KSJCamera->SetExposureTime(0,millSeconds);
			break;
		}
	case ACU:
		break;
	case BAS:
		break;
	case PTG:
		{
			bIsOK = m_PTGCamera->SetExposureTime(millSeconds);
			break;
		}
		
	case IMG:
		{
			bIsOK = m_IMGCamera->SetExposureTime(millSeconds);
			break;
		}
		
// 	case DS:
// 		{
// 			bIsOK = m_DSCamera->SetExposureTime(millSeconds,1);//��ʱд��Ϊ1
// 			break;
// 		}
		
	default:
		break;
	}
	return bIsOK;
}

bool YCapture::CaptureImage()
{
	bool bIsOK = false;
	switch(m_nCameraType)
	{
	case KSJ:
		{
			bIsOK = m_KSJCamera->CaptureImage(0);
			break;
		}
	case ACU:
		break;
	case BAS:
		break;
	case PTG:
		{
			bIsOK = m_PTGCamera->CaptureImage();
			break;
		}
		
	case IMG:
		{
			bIsOK = m_IMGCamera->CaptureImage();
			break;
		}
		
// 	case DS:
// 		{
// 			bIsOK = m_DSCamera->CaptureImage(1);//��ʱд�� ʵ�ʲ���ΪiCameraID
// 			break;
// 		}
	default:
		break;
	}
	return bIsOK;
}

bool YCapture::SoftTrigger()
{
	bool bIsOK = false;
	switch(m_nCameraType)
	{
	case KSJ:
		{
//			bIsOK = m_KSJCamera->SoftTrigger();
			break;
		}
	case ACU:
		//		bIsOK = m_ACUCamera.PauseCamera(m_pCameraIndex[nCamIndex], bIsWorking);
		break;
	case BAS:
		//		bIsOK = m_BaslerCamera.PauseCamera(m_pCameraIndex[nCamIndex], bIsWorking);
		break;
	case PTG:
		{
			bIsOK = m_PTGCamera->SoftTrigger();
			break;
		}
		//		bIsOK = m_PointGreyCamera.PauseCamera(m_pCameraIndex[nCamIndex], bIsWorking);
		break;
	case IMG:
		{
			bIsOK = m_IMGCamera->SoftTrigger(); 
			break;
		}
		//		bIsOK = m_IMGCamera.PauseCamera(m_pCameraIndex[nCamIndex], bIsWorking);
		break;
	default:
		break;
	}
	return bIsOK;	
}

BOOL YCapture::JudgeCameraType(int m_nCameraIndex)
{

	bool bIsOk = false;
	switch(m_nCameraType)
	{
	case KSJ:
		return 1;
	//	break;
	case PTG:
		return 4;
	//	break;
	case IMG:
		return 5;
	case DS:
		return 6;
	default:
		return false;
	}
}

BOOL YCapture::SetContrast(int Contrast)
{
	bool bIsOK = false;
	switch(m_nCameraType)
	{
	case KSJ:
		bIsOK = m_KSJCamera->SetContrast(0,Contrast);
		break;
	case PTG:
		//bIsOK = m_PTGCamera->
		break;
	case IMG:
		bIsOK = m_IMGCamera->SetContrast(Contrast);
		break;
// 	case DS:
// 		bIsOK = m_DSCamera->SetContrast(Contrast,1);//��ʱд��Ϊ1
	}
	return bIsOK;
}


ParaRange YCapture::GetParamRange(int nCamIndex,ParaRange para)
{
	ParaRange nret = {0,0,0,0,0,0,0,0};
	switch(m_nCameraType)
	{
	case KSJ:
// 		m_KSJCamera->m_uNo = ExCamIndex[nCamIndex];        //������ʱ���ֵ�nChannel����KSJ��װ,KSJ�����ָ��������ѡ�����ú���
// 		nret = m_KSJCamera->GetParamRange(nCamIndex,para);
		break;
	case PTG:
		nret = m_PTGCamera->GetParamRange(nCamIndex,para);
		break;
	case IMG:
		nret = m_IMGCamera->GetParamRange(nCamIndex,para);
		break;
	default:
		
		break;
	}

	return nret;
}

BOOL YCapture::SetBrightness(int Brightness)
{
	bool bIsOk = false;
	switch(m_nCameraType)
	{
	case KSJ:
//		bIsOk = m_KSJCamera->SetBrightness(Brightness);
		break;
	case PTG:
		bIsOk = m_PTGCamera->SetBrightness(Brightness);
		break;
	case IMG:
		bIsOk = m_IMGCamera->SetBrightness(Brightness);
	case DS:
		//
		break;
	}
	return bIsOk;
}

BOOL YCapture::CloseCamera()
{
	BOOL bIsOk = FALSE;
	switch(m_nCameraType)
	{
	case KSJ:
		bIsOk = m_KSJCamera->CloseCamera();
		break;
	case PTG:
		bIsOk = m_PTGCamera->CloseCamera();
		break;
	case IMG:
		bIsOk = m_IMGCamera->CloseCamera();
		break;
// 	case DS:
// 		bIsOk = m_DSCamera->CloseCamera(); //
// 		break;
	default:
		break;
	}
	
	return bIsOk;
}

BOOL YCapture::SetGain(int Gain)
{
	bool bIsOk = false;
	switch(m_nCameraType)
	{
	case KSJ:
//		bIsOk = m_KSJCamera->SetGain(Gain);
		break;
	case PTG:
		bIsOk = m_PTGCamera->SetGain(Gain);
		break;
	case IMG:
		bIsOk = m_IMGCamera->SetGain(Gain);;
		break;
// 	case DS:
// 		bIsOk = m_DSCamera->SetGain(Gain,1);//��ʱд��Ϊ1 ֮��Ҫ�����������ҳ����Ӧ��iCameraID���� 8-27
	default:
		break;
	}
	return bIsOk;
}


bool YCapture::PauseCamera(BOOL bIsWorking)
{
	bool bIsOK = false;
	switch(m_nCameraType)
	{
	case KSJ:
		{
			bIsOK = m_KSJCamera->PauseCamera(0,bIsWorking);
			break;
		}
	case ACU:
		break;
	case BAS:
		break;
	case PTG:
		{
			bIsOK=m_PTGCamera->PauseCamera(bIsWorking);
			break;
		}
	case IMG:
		{
			bIsOK=m_IMGCamera->PauseCamera(bIsWorking);
			break;
		}
		break;
	default:
		break;
	}
	return bIsOK;
}
int YCapture::ExIndex = 0;   //Lgy

bool YCapture::ConnectCamera(IMGSHOW imgshow[],int maxdevice,int index)
{
	bool bIsOK = false;
	switch(m_nCameraType)
	{
	case KSJ:
		{
// 			ExCamIndex[m_TempIndex] = ExIndex++;     //Lgy �����൱�ڰ�KSJ�ڲ�nChannel ���浽һ���������ص����飬����֮�����KSJ�ĺ���
// 			                                         //KSJ��һЩ���������ڲ�nChannelΪ�����ģ��������ⲿ�����Ǹ�������ʱ���ɵ����
// 			if(m_KSJCamera != NULL)
// 				delete m_KSJCamera;
// 
// 			m_KSJCamera = new CKSJCamera;
// 			m_KSJCamera->m_ptrCap = this;
// 			m_KSJCamera->m_pExposureTime = m_nExpouse;// 8-12  Lgy ���ع�ֵ���뵽KSJ��connect����
// 			bIsOK = m_KSJCamera->ConnectCamera(m_nCameraIndex);
// 			m_pCaptureImage = &m_KSJCamera->m_pImage;
			break;
		}
	case ACU:
		//		bIsOK = m_ACUCamera.PauseCamera(m_pCameraIndex[nCamIndex], bIsWorking);
		break;
	case BAS:
		//		bIsOK = m_BaslerCamera.PauseCamera(m_pCameraIndex[nCamIndex], bIsWorking);
		break;
	
	case PTG:
		{
			if(m_PTGCamera != NULL)
				delete m_PTGCamera;
			m_PTGCamera = new YPtgCamera;
			m_PTGCamera->m_ptrCap = this;
			bIsOK = m_PTGCamera->ConnectCamera(m_nCameraIndex);
			m_PTGCamera->StartCapure();//@Whq8-10
			m_PTGCamera->SetFreeMode();
			m_pCaptureImage = &m_PTGCamera->m_pImage;
			break;
		}
		//		bIsOK = m_PointGreyCamera.PauseCamera(m_pCameraIndex[nCamIndex], bIsWorking);
		
	case IMG:
		{
			if(m_IMGCamera != NULL)
				delete m_IMGCamera;
			m_IMGCamera = new YImageingSource;
			m_IMGCamera->m_ptrCap=this;
			bIsOK = m_IMGCamera->ConnectCamera(m_nCameraIndex);
			m_pCaptureImage = &m_IMGCamera->m_pImage;
			break;
		}
// 	case DS:
// 		{
// 			if (m_DSCamera != NULL )
// 				delete m_DSCamera;
// 			m_DSCamera = new CDSCamera;
// 			m_DSCamera->m_ptrCap = this;
// 			bIsOK = m_DSCamera->ConnectCamera(imgshow,maxdevice,index);
// 			//	m_pCaptureImage = &m_DSCamera->m_pImage;
// 		}
		break;
		
	default:
		break;
	}
	m_bValid = bIsOK;
	return bIsOK;
}

bool YCapture::ConnectCamera()
{
	bool bIsOK = false;
	switch(m_nCameraType)
	{
	case KSJ:
		{
// 			ExCamIndex[m_TempIndex] = ExIndex++;     //Lgy 
// 			if(m_KSJCamera != NULL)
// 				delete m_KSJCamera;
// 
// 			m_KSJCamera = new CKSJCamera;
//   			m_KSJCamera->m_ptrCap = this;
// 			m_KSJCamera->m_pExposureTime = m_nExpouse;// 8-12  Lgy ���ع�ֵ���뵽KSJ��connect����
// 			bIsOK = m_KSJCamera->ConnectCamera(m_nCameraIndex);
// 			m_pCaptureImage = &m_KSJCamera->m_pImage;
			break;
		}
	case ACU:
		//		bIsOK = m_ACUCamera.PauseCamera(m_pCameraIndex[nCamIndex], bIsWorking);
		break;
	case BAS:
		//		bIsOK = m_BaslerCamera.PauseCamera(m_pCameraIndex[nCamIndex], bIsWorking);
		break;

	case PTG:
		{
			if(m_PTGCamera != NULL)
				delete m_PTGCamera;
			m_PTGCamera = new YPtgCamera;
			m_PTGCamera->m_ptrCap = this;
			bIsOK = m_PTGCamera->ConnectCamera(m_nCameraIndex);
			m_PTGCamera->StartCapure();//@Whq8-10
			m_PTGCamera->SetFreeMode();
			m_pCaptureImage = &m_PTGCamera->m_pImage;
			break;
		}
		//		bIsOK = m_PointGreyCamera.PauseCamera(m_pCameraIndex[nCamIndex], bIsWorking);
		break;
	case IMG:
		{
			if(m_IMGCamera != NULL)
				delete m_IMGCamera;
			m_IMGCamera = new YImageingSource;
			m_IMGCamera->m_ptrCap=this;
			bIsOK = m_IMGCamera->ConnectCamera(m_nCameraIndex);
			m_pCaptureImage = &m_IMGCamera->m_pImage;
			break;
		}

// 	case DS:
// 		{
// 			if (m_DSCamera != NULL )
// 				delete m_DSCamera;
// 			m_DSCamera = new CDSCamera;
// 			m_DSCamera->m_ptrCap = this;
// 			//			bIsOK = m_DSCamera->ConnectCamera(m_nCameraIndex);
// 			//	m_pCaptureImage = &m_DSCamera->m_pImage;
// 			break;
// 		}
		
	default:
		break;
	}
	m_bValid = bIsOK;
	return bIsOK;
}

void YCapture::CamCallBack()
{
	CRect showRect;
	
	if(m_pCautureView != NULL)
	{
		m_pCautureView->GetClientRect(showRect);
		
		CDC *pDc= m_pCautureView->GetDC();
		m_pCaptureImage->ShowCurrentImage(pDc,showRect.left,showRect.top
			,showRect.right,showRect.bottom);
		pDc->DeleteDC();

		TRACE("���%d�ɼ�%d\n", m_nCameraType,m_uNo);
	}
	return;
}

void CCamera::preparerotate(ROTE_IMAGE Oientate,int count)
{
	 for(int i=0;i<=MAX_DEVICE;++i)
	 {
		 if(m_Capture[i].m_nCameraType==IMG)//IMG
		{
			if (count==0)
			{
				m_Capture[i].m_IMGCamera->angle=ROTE_0;//count=0 ʱͼ��������ʾ
			}
			else
			{
				m_Capture[i].m_IMGCamera->count=count;	//�����ת����
				m_Capture[i].m_IMGCamera->angle=ROTE_90;//��ת��ʽΪ90����ת
			}
			if (Oientate==ROTE_HFLIP)
			{
				m_Capture[i].m_IMGCamera->angle=ROTE_HFLIP;  //ˮƽ��ת
				if(m_Capture[i].m_IMGCamera->isH==TRUE)		//�����Ƿ��й�����ˮƽ��ת  //lgy 8-11 true-TRUE
					m_Capture[i].m_IMGCamera->isH=FALSE;
				else
					m_Capture[i].m_IMGCamera->isH=TRUE;     //lgy 8-11 true-TRUE
			}
			if (Oientate==ROTE_VFLIP)						//��ֱ��ת
			{
				m_Capture[i].m_IMGCamera->angle=ROTE_VFLIP;
				if(m_Capture[i].m_IMGCamera->isV==TRUE)		//�����Ƿ��й����д�ֱ��ת  //lgy 8-11 true-TRUE
					m_Capture[i].m_IMGCamera->isV=FALSE;
				else
					m_Capture[i].m_IMGCamera->isV=TRUE;
			}
		 } 
// 		 if(m_Capture[i].m_nCameraType==KSJ)		//KSJ��ת��Ч
// 		 {
// 			 if (count==0)
// 			 {
// 				 m_Capture[i].m_KSJCamera->angle=ROTE_0;
// 			 }
// 			 else
// 			 {
// 				 m_Capture[i].m_KSJCamera->count=count;
// 				 m_Capture[i].m_KSJCamera->angle=ROTE_90;
// 			 }
// 			 if (Oientate==ROTE_HFLIP)
// 			 {
// 				 m_Capture[i].m_KSJCamera->angle=ROTE_HFLIP;
// 				 if(m_Capture[i].m_KSJCamera->isH==TRUE)//lgy 8-11 true-TRUE
// 					 m_Capture[i].m_KSJCamera->isH=FALSE;
// 				 else
// 					 m_Capture[i].m_KSJCamera->isH=TRUE;//lgy 8-11 true-TRUE
// 			 }
// 			 if (Oientate==ROTE_VFLIP)
// 			 {
// 				 m_Capture[i].m_KSJCamera->angle=ROTE_VFLIP;
// 				 if(m_Capture[i].m_KSJCamera->isV==TRUE) //lgy 8-11 true-TRUE
// 					 m_Capture[i].m_KSJCamera->isV=FALSE;
// 				 else
// 					 m_Capture[i].m_KSJCamera->isV=TRUE;
// 			 }
// 		 }

	 }
}

void YCapture::CamCallBack(ROTE_IMAGE Oientate,BOOL isH,BOOL isv)//�Բɼ�ͼ�ν��з�ת@L
{
	//TRACE("���%d�ɼ�%d\n", m_nCameraType,m_uNo);
	if(m_nCameraType == IMG && m_pCautureView != NULL)
	{	
		CRect showRect;
		m_pCautureView->GetClientRect(showRect);
		if(m_pCaptureImage != NULL)
		{	
			switch (Oientate)
			{
				case ROTE_0:
					break;
				case ROTE_90:
					{
						switch(m_IMGCamera->count)
						{
							case 3 :									//��ת270����Ҫת����
								m_IMGCamera->m_pImage.Rotate90(TRUE);
							case 2 :
								m_IMGCamera->m_pImage.Rotate90(TRUE);	//��ת180����Ҫת����
							case 1:
								m_IMGCamera->m_pImage.Rotate90(TRUE);	//��ת90����Ҫתһ��
						}
						break;
					}
				case ROTE_HFLIP:
					{
						m_IMGCamera->m_pImage.HorizontalFlip();		//����ˮƽ��תһ��
						if(m_IMGCamera->isH==FALSE)
							m_IMGCamera->m_pImage.HorizontalFlip();//��תһ�Σ�������ʾ
						break;
					}
				case ROTE_VFLIP:									//ͬˮƽ��ת
					{
						m_IMGCamera->m_pImage.VerticalFlip();
						if(m_IMGCamera->isV==FALSE)
							m_IMGCamera->m_pImage.VerticalFlip();
						break;
					}
			}
			CDC *pDc= m_pCautureView->GetDC();
			m_pCaptureImage->ShowCurrentImage(pDc,showRect.left,showRect.top
				,showRect.right,showRect.bottom);
			pDc->DeleteDC();
		}
	}
	if(m_nCameraType == KSJ)
	{
		TRACE("���KSJ%d�ɼ�%d\n", m_nCameraType,m_uNo);
		CRect showRect;
		m_pCautureView->GetClientRect(showRect);
 		if(m_pCaptureImage != NULL)
 		{	
// 			switch (Oientate)
// 			{
// 			case ROTE_0:
// 				break;
// 			case ROTE_90:
// 				{
// 					switch(m_KSJCamera->count)
// 					{
// 					case 3 :									//��ת270����Ҫת����
// 						m_KSJCamera->m_pImage.Rotate90(TRUE);
// 					case 2 :
// 						m_KSJCamera->m_pImage.Rotate90(TRUE);	//��ת180����Ҫת����
// 					case 1:
// 						m_KSJCamera->m_pImage.Rotate90(TRUE);	//��ת90����Ҫתһ��
// 					}
//  					break;
// 				}
// 			case ROTE_HFLIP:
// 				{
// 					m_KSJCamera->m_pImage.HorizontalFlip();		//����ˮƽ��תһ��
// 					if(m_KSJCamera->isH==FALSE)
// 						m_KSJCamera->m_pImage.HorizontalFlip();//��תһ�Σ�������ʾ
// 					break;
// 				}
// 			case ROTE_VFLIP:									//ͬˮƽ��ת
// 				{
// 					m_KSJCamera->m_pImage.VerticalFlip();
// 					if(m_KSJCamera->isV==FALSE)
// 						m_KSJCamera->m_pImage.VerticalFlip();
// 					break;
// 				}
// 			}
			CDC *pDc= m_pCautureView->GetDC();//@whq
			m_pCaptureImage->ShowCurrentImage(pDc,showRect.left,showRect.top
				,showRect.right,showRect.bottom);
			pDc->DeleteDC();
		}
	}
	
	if(m_nCameraType == PTG)                                  // Lgy
	{
		TRACE("���PTG%d�ɼ�%d\n", m_nCameraType,m_uNo);
		CRect showRect;
		m_pCautureView->GetClientRect(showRect);
		if(m_pCaptureImage != NULL)
		{	
// 			switch (Oientate)
// 			{
// 			case ROTE_0:
// 				break;
// 			case ROTE_90:
// 				{
// 					switch(m_KSJCamera->count)
// 					{
// 					case 3 :									//��ת270����Ҫת����
// 						m_KSJCamera->m_pImage.Rotate90(TRUE);
// 					case 2 :
// 						m_KSJCamera->m_pImage.Rotate90(TRUE);	//��ת180����Ҫת����
// 					case 1:
// 						m_KSJCamera->m_pImage.Rotate90(TRUE);	//��ת90����Ҫתһ��
// 					}
// 					break;
// 				}
// 			case ROTE_HFLIP:
// 				{
// 					m_KSJCamera->m_pImage.HorizontalFlip();		//����ˮƽ��תһ��
// 					if(m_KSJCamera->isH==FALSE)
// 						m_KSJCamera->m_pImage.HorizontalFlip();//��תһ�Σ�������ʾ
// 					break;
// 				}
// 			case ROTE_VFLIP:									//ͬˮƽ��ת
// 				{
// 					m_KSJCamera->m_pImage.VerticalFlip();
// 					if(m_KSJCamera->isV==FALSE)
// 						m_KSJCamera->m_pImage.VerticalFlip();
// 					break;
// 				}
//			}
			CDC *pDc= m_pCautureView->GetDC();
			m_pCaptureImage->ShowCurrentImage(pDc,showRect.left,showRect.top
				,showRect.right,showRect.bottom);
			pDc->DeleteDC();
		}
	}
	return;
}
//void YCapture::RoteImage(ROTE_IMAGE RoteStatue)	
//{
//	switch(m_nCameraType)
//	{
//		
//		case KSJ:
//			m_KSJCamera->RoteImage(RoteStatue);
//			break;
//		case ACU:
//			break;
//		case BAS:
//			break;
//		case PTG:
//			break;
//		case IMG:
//			{
//				m_IMGCamera->RoteImage(RoteStatue);
//				break;
//			}
//	}
//	return ;
//}
//
//void CCamera::RoteImage(ROTE_IMAGE RoteStatue)
//{
//	
//	int nCamNum;
//	CIni iniFile;
//	iniFile.Read(m_sCameraInfoPath);
//}