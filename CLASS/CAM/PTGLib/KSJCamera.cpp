#include "stdafx.h"
#include "KSJCamera.h"
//#include "YCaptureNew.h"

#pragma comment(lib, "CLASS\\CAM\\KSJApiLib\\KSJApi.lib")

VOID WINAPI KSJCamera_callback(unsigned char *pImageData, int nWidth, int nHeight, int nBitCount,  void *lpContext)
{
	CKSJCamera *pCamera = (CKSJCamera *)lpContext;

	if (pCamera->m_pIsPaused)
	{
		return;
	}
	memcpy(pCamera->m_pImage.m_lpDibArray, pImageData, pCamera->m_pImage.m_ImageSize);
	
	pCamera->m_ptrCap->CamCallBack();
}


CKSJCamera::CKSJCamera()
{
	m_pConnectView = NULL;
	m_bIsConnected = FALSE;
	m_pCapturedImageNum = 0;
	m_pIsPaused = FALSE;
	m_pExposureTime = 10;
	m_pDeviceInfo.nIndex = -1;
	m_pIsRGB = FALSE;
	m_pIsTriggerMode = FALSE;
	m_pIsYY = FALSE;
	AfxMessageBox("构造KSJ");
}

CKSJCamera::~CKSJCamera()
{
	CloseCamera();
	AfxMessageBox("析构KSJ");
}

	BOOL CKSJCamera::ConnectCamera(int nCameraSerialNo)
	{
		int i = nCameraSerialNo;
		// 获取连入主机的设备个数
		int nDeviceNum = KSJ_DeviceGetCount();
		if( nDeviceNum == 0)    
			return FALSE;
	
		// 获取每个设备信息（类型，序号，固件版本）
		for(i = 0; i < nDeviceNum; i++ )
		{
			MYDEVICEINFO tempDevice;
			KSJ_DEVICETYPE deviceType;
			KSJ_DeviceGetInformation( i, &deviceType, &(tempDevice.nIndex), &(tempDevice.wFirmwareVersion));
			if(tempDevice.nIndex == nCameraSerialNo)
			{
				m_uNo = i;
				m_DeviceType = deviceType;
				m_pDeviceInfo.nIndex = tempDevice.nIndex;
				m_pDeviceInfo.wFirmwareVersion = tempDevice.wFirmwareVersion;
				BYTE btMajVersion = ( m_pDeviceInfo.wFirmwareVersion & 0xFF00 ) >> 8;		    // 得到主版本号
				BYTE btMinVersion =	m_pDeviceInfo.wFirmwareVersion & 0x00FF;					// 得到副版本号
				switch(m_DeviceType) 
				{
				case KSJ_UC320C_MRNN:
					m_pIsRGB = TRUE;
					break;
				case KSJ_UC500C_MRYY:
					m_pIsRGB = TRUE;
					break;
				case KSJ_UC500C_MRNN:
					m_pIsRGB = TRUE;
					break;
				case KSJ_UC36M_MGYY:
					m_pIsYY = TRUE;
					break;
	// 			case KSJ_MUC36M_MGYY:
	// 				m_pIsYY = TRUE;
	// 				break;
				case KSJ_MUC36M_MGYFO:
					m_pIsYY = FALSE;
					break;
				}
				//曝光时间
				
				if (!SetExposureTime(m_pExposureTime))
				{
					AfxMessageBox("相机设置错误! Code:Exposure");
					return FALSE;
				}
				//增频
				
				//获得gain
				int gain_g = 20;  
				KSJ_SetParam(m_uNo, KSJ_GREEN, gain_g);
				KSJ_SetParam(m_uNo, KSJ_RED, gain_g);
				KSJ_SetParam(m_uNo, KSJ_BLUE,gain_g);
				//KSJ_GetParam(m_uNo, KSJ_GREEN, &gain_g);
				//KSJ_SetParam(m_uNo, KSJ_GREEN, 20);
				//KSJ_SetParam(m_uNo, KSJ_RED, 20);
				//KSJ_SetParam(m_uNo, KSJ_BLUE,20);
		
				//设置对比度
 				int Contrast;
 				KSJ_ProcessContrastGet(m_uNo,&Contrast);
 				KSJ_ProcessContrastSet(m_uNo,10);
				//设置Bayer模式为灰度
				if (m_pIsRGB)
					KSJ_BayerSetMode(m_uNo, KSJ_BGGR_GRAY8);
				//获得最大分辨率
				KSJ_CaptureGetSize( m_uNo, &m_pDeviceInfo.m_nWidth, &m_pDeviceInfo.m_nHeight );
				//设置采集分辨率
				KSJ_CaptureSetFieldOfView(m_uNo, 0, 0, m_pDeviceInfo.m_nWidth, m_pDeviceInfo.m_nHeight, KSJ_SKIPNONE, KSJ_SKIPNONE);
				KSJ_PreviewSetFieldOfView(m_uNo, 0, 0, m_pDeviceInfo.m_nWidth, m_pDeviceInfo.m_nHeight, KSJ_SKIPNONE, KSJ_SKIPNONE);
				//分配内存
				m_pImage.CreateEmpty(m_pDeviceInfo.m_nWidth, m_pDeviceInfo.m_nHeight, 8, 0);
				KSJ_PreviewSetCallback(m_uNo, KSJCamera_callback, this );
				KSJ_PreviewSetPos(m_uNo, NULL, 0, 0, 0, 0);
				KSJ_PreviewStart(m_uNo, true);
				m_bIsConnected = TRUE;
			}
	// 		else
	// 		{
	// 			KSJ_DeviceClose(i);
	// 		}
		}		
		return TRUE;
	}

	BOOL CKSJCamera::SetPreviewPos(HWND hWnd, CRect sRect)
	{
		int nRet;
		double tmpscalex = sRect.Width()/(double)m_pDeviceInfo.m_nWidth;
		double tmpscaley = sRect.Height()/(double)m_pDeviceInfo.m_nHeight;
		if(tmpscalex<tmpscaley)
		{
			m_pShowScale = tmpscalex;
			sRect.bottom = sRect.top  + int(m_pShowScale*m_pDeviceInfo.m_nHeight + 0.5);
		}
		else
		{
			m_pShowScale = tmpscaley;
			sRect.right  = sRect.left + int(m_pShowScale*m_pDeviceInfo.m_nWidth  + 0.5);
		}
		nRet = KSJ_PreviewSetPos(m_uNo, hWnd, sRect.left, sRect.top, sRect.Width(), sRect.Height());
		return (nRet==RET_SUCCESS);
	}

	BOOL CKSJCamera::SetExposureTime(float nTime)
	{
		int tempTime = int(nTime);
		int ExposureMin, ExposureMax;
		KSJ_GetParamRange( m_uNo, KSJ_EXPOSURE_LINES, &ExposureMin, &ExposureMax );
		if (tempTime < ExposureMin) 
		{
			tempTime = ExposureMin;
		}
		if (tempTime > ExposureMax)
		{
			tempTime = ExposureMax;
		}
		int nRet = KSJ_SetParam(m_uNo, KSJ_EXPOSURE_LINES, tempTime);
		if (nRet == RET_SUCCESS)
		{
			m_pExposureTime = nTime;
		}
		return (nRet==RET_SUCCESS);
	}

	BOOL CKSJCamera::SetContrast(int Contrast)
	{
		int tempContrast = Contrast;
		int nRet = KSJ_ProcessContrastSet(m_uNo,tempContrast);
		return nRet;
	}

	BOOL CKSJCamera::SetBrightness(int Brightness)
	{
		int tempBrightness = Brightness;
		int nRet = KSJ_ProcessBrightnessSet(m_uNo,tempBrightness);
		return nRet;
	}

	BOOL CKSJCamera::SetGain(int Gain)
	{
		int tempGain = Gain;
		int nRet = KSJ_SetParam(m_uNo, KSJ_RED, Gain);
		KSJ_SetParam(m_uNo, KSJ_GREEN, Gain);
		KSJ_SetParam(m_uNo, KSJ_BLUE, Gain);
		return nRet;
	}


	ParaRange CKSJCamera::GetParamRange(int nCamIndex,ParaRange para)
	{
		//int nChan = m_ptrCap->ExCamIndex[nCamIndex];
		
		KSJ_GetParamRange(m_uNo,KSJ_BRIGHTNESS,&para.MinBrightness,&para.MaxBrightness);
		KSJ_GetParamRange(m_uNo,KSJ_GREEN,&para.MinGain,&para.MaxGain);
		KSJ_GetParamRange(m_uNo,KSJ_EXPOSURE_LINES,&para.MinExposure,&para.MaxExposure);
		KSJ_GetParamRange(m_uNo,KSJ_CONTRAST,&para.MinContrast,&para.MaxContrast);

		return para;
	}

	BOOL CKSJCamera::CloseCamera()
	{
		if(m_bIsConnected)
		{
			KSJ_PreviewStart(m_uNo, FALSE);
			KSJ_PreviewSetCallback(m_uNo, NULL, this );
			m_pImage.DeleteMe();
		}
		int nRet = KSJ_UnInit();
		return (nRet==RET_SUCCESS);
	}

	BOOL CKSJCamera::PauseCamera(BOOL bIsWorking)
	{
		int nRet = RET_SUCCESS; 

	//	JudgeCameraIndex(nCamIndex);

		if (!bIsWorking)
		{
			nRet = KSJ_PreviewPause(m_uNo, TRUE);
			int nRet;
			if (m_pIsYY)
			{
				nRet = KSJ_EmptyFrameBuffer(m_uNo);
			}	
			
			if (m_pConnectView != NULL)
				m_pConnectView->Invalidate(FALSE);
		}
		else
		{
			nRet = KSJ_PreviewPause(m_uNo, FALSE);
			m_pCapturedImageNum = 0;
		}
		return (nRet == RET_SUCCESS); 
	}
	BOOL CKSJCamera::CaptureImage()
	{
		int nRet = 0;
		CTimeCount time;
		time.Start();
		time.End();
		while (nRet != RET_SUCCESS && time.GetUseTime() < 0.4)
		{
			if (m_pIsRGB)
			{
			/*	if (m_pIsYY)*/
				/*{*/
					nRet = KSJ_CaptureRgbData(m_uNo, m_pImage.m_lpDibArray);//KSJ_CaptureRgbDataAfterEmptyFrameBuffer(nCamIndex, m_pImage[nCamIndex].m_lpDibArray);
			/*	}	
				else
				{
					nRet = KSJ_CaptureRgbData(m_uNo, m_pImage.m_lpDibArray);
				}*/
			}
			else
			{
				/*if (m_pIsYY)*/
				/*{*/
					nRet = KSJ_CaptureRawData(m_uNo, m_pImage.m_lpDibArray);//KSJ_CaptureRawDataAfterEmptyFrameBuffer(nCamIndex, m_pImage[nCamIndex].m_lpDibArray);
				/*}	
				else
				{
					nRet = KSJ_CaptureRawData(m_uNo, m_pImage.m_lpDibArray);
				}*/
			} 
			time.End();
		}	
		time.End();
		if (time.GetUseTime() > 0.4)
		{
			AfxMessageBox("Capture image time out!");
		}
		
		CString strTime;
		CTime curTime = CTime::GetCurrentTime(); 
		strTime = curTime.Format(_T("%Y_%m_%d_%H_%M_%S")); 
		CString driction("E:\\KSJCamPic");
		driction=driction+strTime+".bmp";
		const char *lpctStr=(LPCTSTR)driction;
		
		 if (nRet != RET_SUCCESS)
		{
			AfxMessageBox("Capture image error!");
			m_pImage.SaveImageToFile(lpctStr);
		}

		m_pImage.SaveImageToFile(lpctStr);
		if (m_pConnectView != NULL)
			m_pConnectView->Invalidate(FALSE);
		return (nRet==RET_SUCCESS);
	/*	return TRUE;*/
	}

	bool CKSJCamera::SoftTrigger()
	{
		return false;
	}

	BOOL CKSJCamera::SetSoftTriggerMode()
	{
	//	JudgeCameraIndex(nCamIndex);

		int nRet = KSJ_TriggerModeSet(m_uNo, KSJ_TRIGGER_SOFTWARE);
		nRet &= KSJ_PreviewSetCallback(m_uNo, NULL, NULL);
		m_pIsTriggerMode = TRUE;
		return (nRet==RET_SUCCESS);
	}

	BOOL CKSJCamera::SetFreeMode()
	{
		int nRet = KSJ_TriggerModeSet(m_uNo, KSJ_TRIGGER_INTERNAL);
		nRet &= KSJ_PreviewSetCallback(m_uNo, KSJCamera_callback, this );
		m_pIsTriggerMode = FALSE;
		return (nRet==RET_SUCCESS);
	}

	void CKSJCamera::JudgeCameraIndex()
	{
	#if _DEBUG
		return;
	#endif
		KSJ_DEVICETYPE DeviceType;
		int nIndex;
		unsigned short wFirmwareVersion;
		KSJ_DeviceGetInformation( m_uNo, &DeviceType, &nIndex, &wFirmwareVersion );
		if (m_pDeviceInfo.nIndex != nIndex)
		{
			CloseCamera();
			ConnectCamera(nIndex);
		}
	}
	/*void CKSJCamera::RoteImage(ROTE_IMAGE RoteStatue=ROTE_0)
	{
		PauseCamera(FALSE);
		INT m=0;
		switch (RoteStatue)
		{
		case ROTE_0:
			break;
		case ROTE_90:
			break;
		case ROTE_270:
			break;
		case ROTE_HFLIP:
			break;
		case ROTE_VFLIP:
			break;
		}
		PauseCamera(TRUE);
		m=515;
	}*/