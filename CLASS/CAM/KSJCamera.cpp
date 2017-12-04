#include "stdafx.h"
#include "KSJCamera.h"

#pragma comment(lib, "KSJApi.lib")

#define IGNORE_TIMES  1 //为减少数据传输影像，张图显示一次
#define USE1 3
#define USE2 254
#define USE3 255
#define USESOMECAM
#define SCAPENOUSECAM  if(!IfSomeNoUse(nCamIndex)) return FALSE;

VOID WINAPI PREVIEWCALLBACK0( unsigned char *pImageData, int nWidth, int nHeight, int nBitCount,  void *lpContext )
{
	CKSJCamera *pCamera = (CKSJCamera *)lpContext;

	if (pCamera->m_pIsPaused[0])
	{
		return;
	}


   if (pCamera->m_pCapturedImageNum[0] < 1000)
	{
		pCamera->m_pCapturedImageNum[0]++;
	}
	else
	{
		//LT
		pCamera->m_pCapturedImageNum[0] = 0;
	}


   if ((pCamera->m_pCapturedImageNum[0]%IGNORE_TIMES)!=0)
   {
      return;
   }

 
 	memcpy(pCamera->m_pImage[0].m_lpDibArray, pImageData, pCamera->m_pImage[0].m_ImageSize);




	if (pCamera->m_pConnectView[0] != NULL && pCamera->m_pConnectView[0] ->GetSafeHwnd() != NULL /*&& pCamera->m_pCapturedImageNum[1]%3 == 0*/) 
	{
		pCamera->m_pConnectView[0]->Invalidate(FALSE);
		//TRACE("0\n");
	}


}

VOID WINAPI PREVIEWCALLBACK1( unsigned char *pImageData, int nWidth, int nHeight, int nBitCount,  void *lpContext )
{
	CKSJCamera *pCamera = (CKSJCamera *)lpContext;
	
	if (pCamera->m_pIsPaused[1])
	{
		return;
	}

    if (pCamera->m_pCapturedImageNum[1] < 1000)
	{
		pCamera->m_pCapturedImageNum[1]++;
	}
	else
	{
		//LT
		pCamera->m_pCapturedImageNum[1] = 0;
	}

	if ((pCamera->m_pCapturedImageNum[1]%IGNORE_TIMES)!=0)
	{
		return;
	}



	memcpy(pCamera->m_pImage[1].m_lpDibArray, pImageData, pCamera->m_pImage[1].m_ImageSize);

	
			if (pCamera->m_pConnectView[1] != NULL && pCamera->m_pConnectView[1] ->GetSafeHwnd() != NULL /*&& pCamera->m_pCapturedImageNum[1]%3 == 0*/) 
			{
				pCamera->m_pConnectView[1]->Invalidate(FALSE);
				//TRACE("0\n");
			}
	
}

VOID WINAPI PREVIEWCALLBACK2( unsigned char *pImageData, int nWidth, int nHeight, int nBitCount,  void *lpContext )
{
	CKSJCamera *pCamera = (CKSJCamera *)lpContext;	
	if (pCamera->m_pIsPaused[2])
	{
		return;
	}



	if (pCamera->m_pCapturedImageNum[2] < 1000)
	{
		pCamera->m_pCapturedImageNum[2]++;
	}
	else
	{
		//LT
		pCamera->m_pCapturedImageNum[2] = 0;
	}
	
	if ((pCamera->m_pCapturedImageNum[2]%IGNORE_TIMES)!=0)
	{
		return;
	}

// 	memcpy(pCamera->m_pImage[2].m_lpDibArray, pImageData, pCamera->m_pImage[2].m_ImageSize);

	memcpy(pCamera->m_pImage[2].m_lpDibArray, pImageData, pCamera->m_pImage[2].m_ImageSize);



			if (pCamera->m_pConnectView[2] != NULL && pCamera->m_pConnectView[2] ->GetSafeHwnd() != NULL /*&& pCamera->m_pCapturedImageNum[1]%3 == 0*/) 
			{
				pCamera->m_pConnectView[2]->Invalidate(FALSE);
				//TRACE("1\n");
			}

}

VOID WINAPI PREVIEWCALLBACK3( unsigned char *pImageData, int nWidth, int nHeight, int nBitCount,  void *lpContext )
{
	CKSJCamera *pCamera = (CKSJCamera *)lpContext;	
	if (pCamera->m_pIsPaused[3])
	{
		return;
	}

	if (pCamera->m_pCapturedImageNum[3] < 1000)
	{
		pCamera->m_pCapturedImageNum[3]++;
	}
	else
	{
		//LT
		pCamera->m_pCapturedImageNum[3] = 0;
	}

	if ((pCamera->m_pCapturedImageNum[3]%IGNORE_TIMES)!=0)
	{
		return;
	}

	memcpy(pCamera->m_pImage[3].m_lpDibArray, pImageData, pCamera->m_pImage[3].m_ImageSize);

		if (pCamera->m_pConnectView[3] != NULL && pCamera->m_pConnectView[3] ->GetSafeHwnd() != NULL) 
		{
			pCamera->m_pConnectView[3]->Invalidate(FALSE);
		}

}

VOID WINAPI PREVIEWCALLBACK4( unsigned char *pImageData, int nWidth, int nHeight, int nBitCount,  void *lpContext )
{
	CKSJCamera *pCamera = (CKSJCamera *)lpContext;	
	if (pCamera->m_pIsPaused[4])
	{
		return;
	}

	if (pCamera->m_pCapturedImageNum[4] < 1000)
	{
		pCamera->m_pCapturedImageNum[4]++;
	}
	else
	{
		//LT
		pCamera->m_pCapturedImageNum[4] = 0;
	}

	if ((pCamera->m_pCapturedImageNum[4]%IGNORE_TIMES)!=0)
	{
		return;
	}

	memcpy(pCamera->m_pImage[4].m_lpDibArray, pImageData, pCamera->m_pImage[4].m_ImageSize);

	if (pCamera->m_pConnectView[4] != NULL && pCamera->m_pConnectView[4] ->GetSafeHwnd() != NULL) 
	{
		pCamera->m_pConnectView[4]->Invalidate(FALSE);
	}

}

CKSJCamera::CKSJCamera()
{
	m_nChooseIndex = 0;
	m_nDeviceNum = 0;
	m_bIsConnected = FALSE;
	memset(m_pCapturedImageNum, 0, MAX_DEVICE*sizeof(int));
	for(int i = 0; i < MAX_DEVICE; i++)
	{
		m_pIsPaused[i] = FALSE;
		m_pExposureTime[i] = 10;
		m_pDeviceInfo[i].nIndex = -1;
		m_pIsRGB[i] = FALSE;
		m_pIsTriggerMode[i] = FALSE;
		m_pConnectView[i] = NULL;
	}
	m_pConnectView[4] = NULL;
	m_pConnectView[5] = NULL;
	m_pConnectView[6] = NULL;
}

CKSJCamera::~CKSJCamera()
{
	CloseCamera();
}

BOOL CKSJCamera::ConnectCamera()
{
	int nRet = KSJ_Init();
	// 获取连入主机的设备个数
	m_nDeviceNum = KSJ_DeviceGetCount();
	if( m_nDeviceNum == 0 )    
		return FALSE;
	if( m_nDeviceNum >= MAX_DEVICE )  
		m_nDeviceNum = MAX_DEVICE;

	int i;
	// 获取每个设备信息（类型，序号，固件版本）
	for( i = 0; i < m_nDeviceNum; i++ )
	{
		
		DWORD dst = KSJ_DeviceGetInformation( i, &(m_pDeviceInfo[i].DeviceType), &(m_pDeviceInfo[i].nIndex), &(m_pDeviceInfo[i].wFirmwareVersion) );
		if (dst != RET_SUCCESS)
		{
			continue;
		}
	}
	for( i = 0; i < m_nDeviceNum; i++ )
	{
		if (m_pDeviceInfo[i].nIndex != USE1&&m_pDeviceInfo[i].nIndex != USE2&&m_pDeviceInfo[i].nIndex != USE3)
		{
			KSJ_DeviceClose(i);
			continue;
		}
		BYTE btMajVersion = ( m_pDeviceInfo[i].wFirmwareVersion & 0xFF00 ) >> 8;		// 得到主版本号
		BYTE btMinVersion =	m_pDeviceInfo[i].wFirmwareVersion & 0x00FF;					// 得到副版本号
		switch(m_pDeviceInfo[i].DeviceType) 
		{
		case KSJ_UC320C_MRNN:
			m_pIsRGB[i] = TRUE;
			break;
		case KSJ_UC320C_MRYY:
			m_pIsRGB[i] = TRUE;
			break;
		case KSJ_UC500C_MRYY:
			m_pIsRGB[i] = TRUE;
			break;
		case KSJ_UC500C_MRNN:
			m_pIsRGB[i] = TRUE;
			break;
// 		case KSJ_MU3E130M_EGYY:
// 			m_pIsRGB[i] = TRUE;
// 			break;
		case KSJ_MU3C120M_MGYYO:
			m_pIsRGB[i] = TRUE;
			break;
// 		case KSJ_MU3E200C_EGYYO:
// 			m_pIsRGB[i] = TRUE;
// 			break;
		}


		if(m_pDeviceInfo[i].DeviceType==KSJ_MU3E200C_EGYYO)
		{
			m_pExposureTime[i]=30;
		}


		if (!SetExposureTime(i, m_pExposureTime[i]))
		{
			AfxMessageBox("相机设置错误! Code:Exposure");
			return FALSE;
		}
		//获得gain
		int gain_g;
		if(m_pDeviceInfo[i].DeviceType==KSJ_MU3E200C_EGYYO)
		{
			KSJ_GetParam(i, KSJ_GREEN, &gain_g);
			KSJ_SetParam(i, KSJ_GREEN, 150);
			KSJ_SetParam(i, KSJ_RED, 150);
			KSJ_SetParam(i, KSJ_BLUE, 150);

			int nFlipMode=1;
			KSJ_GetParam(i,KSJ_FLIP,&nFlipMode);

			if (nFlipMode==1)
			{
				KSJ_SetParam(i,KSJ_FLIP,0);
			}
		}
		else
		{
			KSJ_GetParam(i, KSJ_GREEN, &gain_g);
			KSJ_SetParam(i, KSJ_GREEN, 50);
			KSJ_SetParam(i, KSJ_RED, 50);
			KSJ_SetParam(i, KSJ_BLUE, 50);
//			KSJ_SetParam(i, KSJ_CDSGAIN, 100);
		}



		//设置Bayer模式为灰度
		if (m_pIsRGB[i])
			KSJ_BayerSetMode(i, KSJ_BGGR_GRAY8);
		//获得最大分辨率
		int nColumnStart; int nRowStart; int nColumnSize; int nRowSize; KSJ_ADDRESSMODE ColumnAddressMode; KSJ_ADDRESSMODE RowAddressMode; 
		KSJ_CaptureGetDefaultFieldOfView(i,&nColumnStart,&nColumnStart,&m_pDeviceInfo[i].m_nWidth,&m_pDeviceInfo[i].m_nHeight,&ColumnAddressMode,&RowAddressMode);

//		KSJ_CaptureGetSize( i, &m_pDeviceInfo[i].m_nWidth, &m_pDeviceInfo[i].m_nHeight );

// 		if (m_pDeviceInfo[i].nIndex == 1)
// 		{
// 			//设置采集分辨率
// 			KSJ_CaptureSetFieldOfView(i, 200, 0, 664, m_pDeviceInfo[i].m_nHeight, KSJ_SKIPNONE, KSJ_SKIPNONE);
// 			KSJ_PreviewSetFieldOfView(i, 200, 0, 664, 1024, KSJ_SKIPNONE, KSJ_SKIPNONE);
// 			//分配内存
// 			m_pImage[i].CreateEmpty(664, m_pDeviceInfo[i].m_nHeight, 8, 0);
// 			//			continue;
// 		}
// 		else
		{
			//设置采集分辨率
			KSJ_CaptureSetFieldOfView(i, 0, 0, m_pDeviceInfo[i].m_nWidth, m_pDeviceInfo[i].m_nHeight, KSJ_SKIPNONE, KSJ_SKIPNONE);
			KSJ_PreviewSetFieldOfView(i, 0, 0, m_pDeviceInfo[i].m_nWidth, m_pDeviceInfo[i].m_nHeight, KSJ_SKIPNONE, KSJ_SKIPNONE);
			//分配内存

			//m_pColorImage[i].CreateEmpty(m_pDeviceInfo[i].m_nWidth, m_pDeviceInfo[i].m_nHeight, 24, 0);
			m_pImage[i].CreateEmpty(m_pDeviceInfo[i].m_nWidth, m_pDeviceInfo[i].m_nHeight, 24, 0);
		
		}

// 		if (m_pDeviceInfo[i].DeviceType==KSJ_MU3E200C_EGYYO) 
// 		{
// 		//	KSJ_PreviewSetCallback( i, NULL, NULL );
// 			continue;
// 		}

		switch(i)
		{
		case 0:
			KSJ_PreviewSetCallback( i, PREVIEWCALLBACK0, this );
			break;
		case 1:
			KSJ_PreviewSetCallback( i, PREVIEWCALLBACK1, this );
			break;
		case 2:
			KSJ_PreviewSetCallback( i, PREVIEWCALLBACK2, this );
			break;
		case 3:
			KSJ_PreviewSetCallback( i, PREVIEWCALLBACK3, this );
			break;
		case 4:
			KSJ_PreviewSetCallback( i, PREVIEWCALLBACK4, this );
			break;
		}		
		KSJ_PreviewSetPos(i, NULL, 0, 0, 0, 0);
		KSJ_PreviewStart(i, true);
	}		

	
	m_bIsConnected = TRUE;
	return TRUE;
}

BOOL CKSJCamera::SetExposureTime(int nCamIndex, int nTime)
{

	if (nCamIndex < 0 || nCamIndex > m_nDeviceNum)
	{
		return FALSE;
	}
	SCAPENOUSECAM
	int ExposureMin, ExposureMax;
	KSJ_GetParamRange( nCamIndex, KSJ_EXPOSURE, &ExposureMin, &ExposureMax );
	if (nTime < ExposureMin) 
	{
		nTime = ExposureMin;
	}
	if (nTime > ExposureMax)
	{
		nTime = ExposureMax;
	}
	int nRet = KSJ_SetParam(nCamIndex, KSJ_EXPOSURE, nTime);
	if (nRet == RET_SUCCESS)
	{
		m_pExposureTime[nCamIndex] = nTime;
	}
	return (nRet==RET_SUCCESS);
}


BOOL CKSJCamera::SetBright(int nCamIndex,int nBright)
{
	if (nCamIndex < 0 || nCamIndex > m_nDeviceNum)
	{
		return FALSE;
	}
	SCAPENOUSECAM
	int nBrightMin, nBrightMax;
	KSJ_GetParamRange( nCamIndex, KSJ_BRIGHTNESS, &nBrightMin, &nBrightMax );
	if (nBright < nBrightMin) 
	{
		nBright = nBrightMin;
	}
	if (nBright > nBrightMax)
	{
		nBright = nBrightMax;
	}
	int nRet = KSJ_SetParam(nCamIndex, KSJ_BRIGHTNESS, nBright);
// 	if (nRet == RET_SUCCESS)
// 	{
// 		m_pExposureTime[nCamIndex] = nTime;
// 	}
	return (nRet==RET_SUCCESS);
}

BOOL CKSJCamera::SetContrast(int nCamIndex,int nContrast)
{
	if (nCamIndex < 0 || nCamIndex > m_nDeviceNum)
	{
		return FALSE;
	}
	SCAPENOUSECAM
	int nContrastMin, nContrastMax;
	KSJ_GetParamRange( nCamIndex, KSJ_CONTRAST, &nContrastMin, &nContrastMax );
	if (nContrast < nContrastMin) 
	{
		nContrast = nContrastMin;
	}
	if (nContrast > nContrastMax)
	{
		nContrast = nContrastMax;
	}
	int nRet = KSJ_SetParam(nCamIndex, KSJ_CONTRAST, nContrast);
	// 	if (nRet == RET_SUCCESS)
	// 	{
	// 		m_pExposureTime[nCamIndex] = nTime;
	// 	}
	return (nRet==RET_SUCCESS);
}

BOOL CKSJCamera::CloseCamera()
{
	for(int i = 0; i < m_nDeviceNum; i++)
	{
		if (m_pDeviceInfo[i].nIndex != USE1||m_pDeviceInfo[i].nIndex != USE2||
			m_pDeviceInfo[i].nIndex != USE3){
			continue;
		}
		KSJ_PreviewStart(i, FALSE);
		KSJ_PreviewSetCallback( i, NULL, this );
	}
	int nRet = KSJ_UnInit();
	return (nRet==RET_SUCCESS);
}


BOOL CKSJCamera::PauseCameraView(int nCamIndex, BOOL bPause)
{
	if (nCamIndex < 0 || nCamIndex > m_nDeviceNum)
	{
		return FALSE;
	} 
	SCAPENOUSECAM
	int nRet = RET_SUCCESS; 

    nRet = KSJ_PreviewPause(nCamIndex, bPause);  

	return (nRet == RET_SUCCESS);
}

BOOL CKSJCamera::PauseCamera(int nCamIndex, BOOL bIsWorking)
{
	if (nCamIndex < 0 || nCamIndex > m_nDeviceNum)
	{
		return FALSE;
	} 
	SCAPENOUSECAM
	int nRet = RET_SUCCESS; 


 	m_pIsPaused[nCamIndex] = !bIsWorking;  //WHQ
 	return (nRet == RET_SUCCESS);
// 
// 
// 	JudgeCameraIndex(nCamIndex);

	if (!bIsWorking)
	{
		nRet = KSJ_PreviewPause(nCamIndex, TRUE);  //@whq 2016-6-28 
		//nRet = KSJ_PreviewStart(nCamIndex, FALSE);
// 		int nRet;
// 		if (m_pIsRGB[nCamIndex])
// 			nRet = KSJ_CaptureRgbDataAfterEmptyFrameBuffer(nCamIndex, m_pImage[nCamIndex].m_lpDibArray);
// 		else
// 			nRet = KSJ_CaptureRawDataAfterEmptyFrameBuffer(nCamIndex, m_pImage[nCamIndex].m_lpDibArray);
// 		if (m_pConnectV1iew[nCamIndex] != NULL)
// 			m_pConnectView[nCamIndex]->Invalidate(FALSE);
	}
	else
	{
		nRet = KSJ_PreviewPause(nCamIndex, FALSE);
		//nRet = KSJ_PreviewStart(nCamIndex, TRUE);
		m_pCapturedImageNum[nCamIndex] = 0;
	}

	return (nRet == RET_SUCCESS);
}

BOOL CKSJCamera::SetPreviewPos(int nCamIndex, HWND hWnd, CRect sRect)
{
	if (nCamIndex < 0 || nCamIndex > m_nDeviceNum)
	{
		return FALSE;
	}
	SCAPENOUSECAM
	int nRet;
	double tmpscalex = sRect.Width()/(double)m_pDeviceInfo[nCamIndex].m_nWidth;
	double tmpscaley = sRect.Height()/(double)m_pDeviceInfo[nCamIndex].m_nHeight;
	if(tmpscalex<tmpscaley)
	{
		m_pShowScale[nCamIndex] = tmpscalex;
		sRect.bottom = sRect.top  + int(m_pShowScale[nCamIndex]*m_pDeviceInfo[nCamIndex].m_nHeight + 0.5);
	}
	else
	{
		m_pShowScale[nCamIndex] = tmpscaley;
		sRect.right  = sRect.left + int(m_pShowScale[nCamIndex]*m_pDeviceInfo[nCamIndex].m_nWidth  + 0.5);
	}
	nRet = KSJ_PreviewSetPos(nCamIndex, hWnd, sRect.left, sRect.right, sRect.Width(), sRect.Height());
	return (nRet==RET_SUCCESS);
}

BOOL CKSJCamera::CaptureImage(int nCamIndex)
{
	if (nCamIndex < 0 || nCamIndex > m_nDeviceNum)
	{
		return FALSE;
	}
	SCAPENOUSECAM

	int nRet = RET_SUCCESS;
	JudgeCameraIndex(nCamIndex);



	if (m_pDeviceInfo[nCamIndex].DeviceType==KSJ_MU3E200C_EGYYO)
	{
		nRet = KSJ_CaptureRgbData/*AfterEmptyFrameBuffer*/(nCamIndex, m_pImage[nCamIndex].m_lpDibArray);
	//	memcpy(pCamera->m_pColorImage[0].m_lpDibArray, pImageData, pCamera->m_pColorImage[0].m_ImageSize);   
// 		CMyImage temp(m_pColorImage[nCamIndex]);
// 		temp.ConvertToGrayImage();
// 		memcpy(m_pImage[nCamIndex].m_lpDibArray, temp.m_lpDibArray, m_pImage[nCamIndex].m_ImageSize);
//		m_pImage[nCamIndex].VerticalFlip();
	} 
	else
	{
		if (m_pIsRGB[nCamIndex])
			nRet = KSJ_CaptureRgbData/*AfterEmptyFrameBuffer*/(nCamIndex, m_pImage[nCamIndex].m_lpDibArray);  //@whq 2016-6-25  不等待清除buffer
		else
			nRet = KSJ_CaptureRawData/*AfterEmptyFrameBuffer*/(nCamIndex, m_pImage[nCamIndex].m_lpDibArray);
	}

	
	if (m_pConnectView[nCamIndex] != NULL)
		m_pConnectView[nCamIndex]->Invalidate(FALSE);
	
	return (nRet==RET_SUCCESS);
}

BOOL CKSJCamera::SetSoftTriggerMode(int nCamIndex)
{
	if (nCamIndex < 0 || nCamIndex > m_nDeviceNum)
	{
		return FALSE;
	}
	SCAPENOUSECAM
	//return PauseCamera(nCamIndex,FALSE);  //@whq 2016-6-28 
	if(m_pIsTriggerMode[nCamIndex])  //@whq 2016-6-25 
		return TRUE;
	JudgeCameraIndex(nCamIndex);

	int nRet = KSJ_TriggerModeSet(nCamIndex, KSJ_TRIGGER_SOFTWARE);
	nRet &= KSJ_PreviewSetCallback(nCamIndex, NULL, NULL);
	m_pIsTriggerMode[nCamIndex] = TRUE;
	return (nRet==RET_SUCCESS);
//	return TRUE;
}

BOOL CKSJCamera::SetFreeMode(int nCamIndex)
{
	if (nCamIndex < 0 || nCamIndex > m_nDeviceNum)
	{
		return FALSE;
	}
	SCAPENOUSECAM
	//return PauseCamera(nCamIndex,TRUE);  //@whq 2016-6-28 


	int nRet = KSJ_TriggerModeSet(nCamIndex, KSJ_TRIGGER_INTERNAL);
	switch(nCamIndex)
	{
	case 0:
		nRet &= KSJ_PreviewSetCallback( nCamIndex, PREVIEWCALLBACK0, this );
		break;
	case 1:
		nRet &= KSJ_PreviewSetCallback( nCamIndex, PREVIEWCALLBACK1, this );
		break;
	case 2:
		nRet &= KSJ_PreviewSetCallback( nCamIndex, PREVIEWCALLBACK2, this );
		break;
	case 3:
		nRet &= KSJ_PreviewSetCallback( nCamIndex, PREVIEWCALLBACK3, this );
		break;
 	case 4:
 		nRet &= KSJ_PreviewSetCallback( nCamIndex, PREVIEWCALLBACK4, this );
 		break;
	}
	m_pIsTriggerMode[nCamIndex] = FALSE;
	return (nRet==RET_SUCCESS);
//	return TRUE;

}

void CKSJCamera::JudgeCameraIndex(int nCamIndex)
{
#if _DEBUG
	return;
#endif
	if(!IfSomeNoUse(nCamIndex)) return;
	KSJ_DEVICETYPE DeviceType;
	int nIndex;
	unsigned short wFirmwareVersion;
	KSJ_DeviceGetInformation( nCamIndex, &DeviceType, &nIndex, &wFirmwareVersion );
	if (m_pDeviceInfo[nCamIndex].nIndex != nIndex)
	{
		CloseCamera();
		ConnectCamera();
	}
}


BOOL CKSJCamera::IsCamaraColor(int nCamIndex) //是否彩色相机
{
	if (nCamIndex < 0 || nCamIndex > m_nDeviceNum)
	{
		return FALSE;
	}
	IfSomeNoUse(nCamIndex);

	JudgeCameraIndex(nCamIndex);

	return m_pDeviceInfo[nCamIndex].DeviceType==KSJ_MU3E200C_EGYYO;
}

BOOL CKSJCamera::IfSomeNoUse(int nCamIndex)
{
#ifdef USESOMECAM
	if (m_pDeviceInfo[nCamIndex].nIndex == USE1||m_pDeviceInfo[nCamIndex].nIndex == USE2||
		m_pDeviceInfo[nCamIndex].nIndex == USE3){
			return TRUE;
	}
#endif
	return FALSE;
}
