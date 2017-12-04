#include "stdafx.h"
#include "ImageingSource.h"
#include <vector>
#include<iostream>
using namespace DShowLib;
// using namespace _DSHOWLIB_NAMESPACE;
// #include "VCDPropertyID.h"
using namespace std; 
CListener :: CListener()
{
	m_pConnectView	= NULL;
	m_pImageSource	= NULL;
	m_pImage		= NULL;
	m_pIsPaused		= NULL;
	m_pIsTriggerMode= NULL;
	m_pIsSoftFinish	= NULL;
	m_pImageSource	= NULL;
}
CListener :: ~CListener()
{
}

void CListener::frameReady(Grabber& param, smart_ptr<MemBuffer> pBuffer, DWORD FrameNumber)
{
//	TRACE("%d\n",FrameNumber);
	if (*m_pIsPaused)
	{
		return;
	}
 	memcpy(m_pImage->m_lpDibArray, pBuffer->getPtr(), pBuffer->getBufferSize());
 	m_pImage->VerticalFlip();
 	*m_pIsSoftFinish = TRUE;
 	if (m_pImageSource != NULL)
 	{
 		m_pImageSource->m_ptrCap->CamCallBack(m_pImageSource->angle,m_pImageSource->isH,m_pImageSource->isV);
 	}
}
YImageingSource::YImageingSource()
{
	m_nDeviceNum = 0;	
	m_bIsConnected = FALSE;
	m_ptrCap		= NULL;
	
	pListener = new CListener();
	m_nColor = 8;
	m_pIsRGB = FALSE;
	m_pIsPaused = FALSE;
	m_pExposureTime = 0;
	m_pBrightness = 0;
	m_pIsTriggerMode = FALSE;
	m_pIsSoftTriggerMode = FALSE;
	m_pConnectView = NULL;
	m_pDeviceInfo.m_nHeight  = 0;
	m_pDeviceInfo.m_nStartCol = 0;
	m_pDeviceInfo.m_nStartRow = 0;
	m_pDeviceInfo.m_nWidth = 0;
	m_pDeviceInfo.nIndex = -1;
	m_pDeviceInfo.wFirmwareVersion = 0;
	m_pIsSoftFinish = FALSE;

//	pItf = NULL;
	


}
YImageingSource::~YImageingSource()
{
	if(m_bIsConnected==TRUE)
		CloseCamera();
}
BOOL YImageingSource::SoftTrigger()
{
	if(m_pIsSoftTriggerMode)
	{
		m_pIsSoftFinish = FALSE;	
		softtrigger->push();
	}

	return TRUE;
}
BOOL YImageingSource::CloseCamera()
{
	if (m_Grabber.isLive())
	{
		m_Grabber.stopLive();
		m_Grabber.closeDev();
	}
	if (m_Grabber.isListenerRegistered(pListener))
	{
		m_Grabber.removeListener(pListener, GrabberListener::eFRAMEREADY);
	}
	if (pListener==NULL)
	{
		delete pListener;
		pListener = NULL;
	}
		m_pImage.DeleteMe();
	//delete m_Grabber;		
	return TRUE;
}
BOOL YImageingSource::ConnectCamera(int nCameraSerialNo)
{

	Grabber::tVidCapDevListPtr pVidCapDevList = m_Grabber.getAvailableVideoCaptureDevices();
	if(pVidCapDevList->size() == 0 || pVidCapDevList->empty())
	{
		return FALSE;
	}

	if(!m_Grabber.openDev(nCameraSerialNo))
		return	false;

	pProps = m_Grabber.getAvailableVCDProperties();
	
	m_pDeviceInfo.m_nWidth = m_Grabber.getAcqSizeMaxX();

    m_pDeviceInfo.m_nHeight = m_Grabber.getAcqSizeMaxY();
	
	 if( pProps != 0 && ( pItf = pProps->findInterface( VCDID_Gain, VCDElement_Value, VCDInterface_Range ) ) != 0 )
	{
		pItf->QueryInterface(gainRange);
	}
	
	gainRange->setValue(gainRange->getRangeMin()) ;

	m_pImage.CreateEmpty(m_pDeviceInfo.m_nWidth, m_pDeviceInfo.m_nHeight, 8, 0);	

	pListener->m_pImageSource = this;

	pListener->m_pImage = &(m_pImage);
	
	pListener->m_pIsPaused = &(m_pIsPaused);
	
	pListener->m_pIsTriggerMode = &(m_pIsTriggerMode);
 
	pListener->m_pIsSoftFinish = &(m_pIsSoftFinish);
	 
	m_Grabber.addListener(pListener, GrabberListener::eFRAMEREADY);//注册回调	
	
	pSink0 = FrameHandlerSink::create(eY800, 1);
	
	pSink0->setSnapMode(false);
	
	m_Grabber.setSinkType(pSink0);
	
	if (!m_Grabber.isLive())
	{
		m_Grabber.startLive(false);
	}

	if (!SetExposureTime(m_pExposureTime))
	{
		AfxMessageBox("曝光设置错误!");
		return FALSE;
	}

	//PauseCamera(FALSE);
	
	SetFreeMode();
	
	m_bIsConnected = TRUE;
	m_Grabber.setDeviceFrameFilters( pFilter.get());	
	return TRUE;
}

ParaRange YImageingSource::GetParamRange(int nCamIndex,ParaRange para)
{
	if( pProps!= 0 && ( pItf = pProps->findInterface( VCDID_Exposure, VCDElement_Value, VCDInterface_AbsoluteValue ) ) != 0 )
	{
		pItf->QueryInterface(ExposureRange);
	}
	para.MinExposure = ExposureRange->getRangeMin();
	para.MaxExposure = ExposureRange->getRangeMax();

	if( pProps!= 0 && ( pItf = pProps->findInterface( VCDID_Gain, VCDElement_Value, VCDInterface_Range ) ) != 0 )
	{
		pItf->QueryInterface(gainRange);
	}
	para.MinGain = gainRange->getRangeMin();
	para.MaxGain = gainRange->getRangeMax();

	if( pProps!= 0 && ( pItf = pProps->findInterface( VCDID_Brightness, VCDElement_Value, VCDInterface_Range ) ) != 0 )
	{
		pItf->QueryInterface(BrightnessRange);
	}
	para.MinBrightness = BrightnessRange->getRangeMin();
	para.MaxBrightness = BrightnessRange->getRangeMax();

	if( pProps!= 0 && ( pItf = pProps->findInterface( VCDID_Contrast, VCDElement_Value, VCDInterface_Range ) ) != 0 )
	{
		pItf->QueryInterface(ContrastRange);
	}
	para.MinContrast = ContrastRange->getRangeMin();
	para.MaxContrast = ContrastRange->getRangeMax();

    return para;
}

BOOL YImageingSource::SetExposureTime(float ExposureTime)
{

    if( pProps!= 0 && ( pItf = pProps->findInterface( VCDID_Exposure, VCDElement_Value, VCDInterface_AbsoluteValue ) ) != 0 )
	{
		pItf->QueryInterface(ExposureRange);
	}

	if (ExposureTime < 10000*ExposureRange->getRangeMin()) 
	{
		ExposureTime = 10000*ExposureRange->getRangeMin();
	}

	if (ExposureTime > 10000*ExposureRange->getRangeMax())
	{
		ExposureTime = 10000*ExposureRange->getRangeMax();
	}

    ExposureRange->setValue(ExposureTime/10000);
	m_pExposureTime = ExposureTime;
	return TRUE;
}

BOOL YImageingSource::SetBrightness(float Brightness)
{
	
	if( pProps != 0 && ( pItf = pProps->findInterface( VCDID_Brightness, VCDElement_Value, VCDInterface_Range ) ) != 0 )
	{
		pItf->QueryInterface(BrightnessRange);
	}

	if (Brightness < BrightnessRange->getRangeMin()) 
	{
		Brightness = BrightnessRange->getRangeMin();
	}

	if (Brightness > BrightnessRange->getRangeMax())
	{
		Brightness = BrightnessRange->getRangeMax();
	}

	BrightnessRange->setValue(Brightness);
	m_pBrightness = Brightness;
	return TRUE;
}

BOOL YImageingSource::SetGain(float Gain)
{
	if( pProps!= 0 && ( pItf = pProps->findInterface( VCDID_Gain, VCDElement_Value, VCDInterface_Range ) ) != 0 )
	{
		pItf->QueryInterface(gainRange);
	}
	
	if (Gain < gainRange->getRangeMin()) 
	{
		Gain = gainRange->getRangeMin();
	}

	if (Gain > gainRange->getRangeMax())
	{
		Gain = gainRange->getRangeMax();
	}
	gainRange->setValue(Gain);
	m_pGain = Gain;
	return TRUE;

}

BOOL YImageingSource::SetContrast(float Contrast)
{
	
	if( pProps!= 0 && ( pItf = pProps->findInterface( VCDID_Contrast, VCDElement_Value, VCDInterface_Range ) ) != 0 )
	{
		pItf->QueryInterface(ContrastRange);
	}

	if (Contrast < ContrastRange->getRangeMin()) 
	{
		Contrast  = ContrastRange->getRangeMin();
	}

	if (Contrast  > ContrastRange->getRangeMax())
	{
		Contrast = ContrastRange->getRangeMax();
	}

	ContrastRange->setValue(Contrast);
	m_pContrast = Contrast;
	return TRUE;

}

BOOL YImageingSource::PauseCamera(BOOL bIsWorking)           
{
	if ((!bIsWorking) && (m_Grabber.isLive()))
	{
		m_pIsPaused = TRUE;
		m_Grabber.stopLive();
		return TRUE;
	}
	else if ((bIsWorking) && (!m_Grabber.isLive()))
	{
		m_pIsPaused = FALSE;
		m_Grabber.startLive(false);
		return TRUE;
	}
	return FALSE;
}	

BOOL YImageingSource::SetFreeMode()
{
	PauseCamera(TRUE);
    if(pProps != 0 && (pItf = pProps->findInterface( VCDID_TriggerMode, VCDElement_Value, VCDInterface_Switch)) != 0)
	{    
		pItf->QueryInterface(triggerswitch);
		triggerswitch->setSwitch(false);	
		m_pIsTriggerMode = FALSE;
		return TRUE;
	}
	return FALSE;
}

BOOL YImageingSource::SetCaptureMode()
{
	PauseCamera(TRUE);
    if( pProps != 0 && (pItf = pProps->findInterface( VCDID_TriggerMode, VCDElement_Value, VCDInterface_Switch ) ) != 0 )
	{    
		pItf->QueryInterface(triggerswitch);
		triggerswitch->setSwitch(true);	
		m_pIsTriggerMode = TRUE;
		return TRUE;
	}
    return FALSE;	
}

BOOL YImageingSource::SetSoftTriggerMode()
{
	PauseCamera(TRUE);
	SetCaptureMode();
	if(pProps != 0 && (pItf=pProps->findInterface( VCDID_TriggerMode, VCDElement_SoftTrigger, VCDInterface_Button )) != 0)
	{    
		pItf->QueryInterface(softtrigger);
		m_pIsSoftTriggerMode = TRUE;
		return TRUE;		
	}	
	softtrigger->push();
	return FALSE;
}

BOOL YImageingSource::CaptureImage()
{
	CString strTime;
	CTime curTime = CTime::GetCurrentTime(); 
	strTime = curTime.Format(_T("%Y_%m_%d_%H_%M_%S")); 
	CString driction("E:\\IMGCamPic");
	driction=driction+strTime+".bmp";
	const char *lpctStr=(LPCTSTR)driction;
	if (!m_pIsSoftTriggerMode)
	{
			m_pImage.SaveImageToFile(lpctStr);
			return TRUE;
	}
	m_pIsSoftFinish = FALSE;	
	softtrigger->push();

	
	pSink0->getLastAcqMemBuffer()->save(lpctStr);
	return TRUE;

}

BOOL YImageingSource::SetPreviewPos(HWND hwnd, CRect sRect)
{
 //	std::vector<FilterInfo> filterInfos = FilterLoader::getAvailableFrameFilters( eFC_ALL );
	//pFilter = FilterLoader::createFilter( filterInfos[4] ); // Module file.
	//pFilter->beginParamTransfer();
	//pFilter->setParameter( "Flip V", TRUE );
	pListener->m_pConnectView = m_pConnectView;
	/*pFilter->setParameter( "Flip V", TRUE );*/
	int q = m_Grabber.showDevicePage(hwnd);
	/*pFilter->setParameter( "Flip V", TRUE );*/
    int T = m_Grabber.setHWND(hwnd);
	//pFilter->setParameter( "Flip V", TRUE );
	HWND pwnd = m_Grabber.getHWND();
	/*pFilter->setParameter( "Flip V", TRUE );*/
	/*pFilter->endParamTransfer();*/
	PauseCamera(TRUE);
	return true;
}

int YImageingSource::GetFPS()
{
	int TempFps = m_Grabber.getFPS();
	return TempFps;
}

int YImageingSource::GetDeviceNumber()
{
	Grabber::tVidCapDevListPtr pVidCapDevList = m_Grabber.getAvailableVideoCaptureDevices();
	return pVidCapDevList->size();
}

int YImageingSource::GetDeviceInformation(CString& index,WORD& version,int& Width,int& Height,int i)
{

	Grabber::tVidCapDevListPtr pVidCapDevList = m_Grabber.getAvailableVideoCaptureDevices();
	Grabber::tVidCapDevList::iterator it = pVidCapDevList->begin();
	
	for(int counter=0;counter<i;++counter)
		++ it;

	m_Grabber.openDev((LPCSTR)it->c_str());

	char tempindex[10];
	LONGLONG tempIndex ;   //获取到序列号保存变量                      Lgy 8-24
	if(m_Grabber.getDev().getSerialNumber(tempIndex) != true)      // Lgy 8-24
		return -2;	

	itoa(tempIndex,tempindex,10);//转换为字符形式
	index = tempindex;			 //赋给参数index  8-24	

	Width = m_Grabber.getAcqSizeMaxX();
	Height = m_Grabber.getAcqSizeMaxY();		
	version = 0;
	return 1;
}

//void YImageingSource::RoteImage(ROTE_IMAGE RoteStatue=ROTE_0)
//{
//	/*if( m_Grabber.isDevValid() )
//		 m_Grabber.openDev( m_tDeviceState.szDevice );*/
//		/*m_tDeviceState.szDevice = m_pGrabber->getDev().c_str();*/
//	//Grabber::tVidCapDevListPtr pVidCapDevList = m_Grabber.getAvailableVideoCaptureDevices();
//
//	//Grabber::tVidCapDevList::iterator it = pVidCapDevList->begin();
//	//bool y=m_Grabber.openDev((LPCSTR)it->c_str());
//	PauseCamera(FALSE);
//	tFilterError n;
//	std::vector<FilterInfo> filterInfos = FilterLoader::getAvailableFrameFilters( eFC_ALL );
//	pFilter = FilterLoader::createFilter( filterInfos[4] ); // Module file.
//		smart_com<IFrameFilter> pFilter = FilterLoader::createFilter( "Rotate Flip" );
//		/*m_Grabber.setDeviceFrameFilters( pFilter.get() );*/
//	pFilter->beginParamTransfer();
//	switch (RoteStatue)
//	{
//		case ROTE_0:
//			{
//				if(eNO_ERROR != pFilter->setParameter( "Rotation Angle", ROTE_0  ))
//					{
//						AfxMessageBox("卧槽，旋转失败");
//						PauseCamera(TRUE);
//						pFilter->endParamTransfer();
//						return;
//					}
//				break;
//			}
//		case ROTE_90:
//			{
//				if(eNO_ERROR != pFilter->setParameter( "Rotation Angle", ROTE_90  ))
//				{
//					AfxMessageBox("卧槽，旋转失败");
//					PauseCamera(TRUE);
//					pFilter->endParamTransfer();
//					return;
//				}
//					break;
//			}
//		case ROTE_180:
//			{
//				if(eNO_ERROR != pFilter->setParameter( "Rotation Angle", ROTE_180  ))
//				{
//					AfxMessageBox("卧槽，旋转失败");
//					PauseCamera(TRUE);
//					pFilter->endParamTransfer();
//					return;
//				}
//				break;
//			}
//		case ROTE_270:
//			{
//				if(eNO_ERROR != pFilter->setParameter( "Rotation Angle", ROTE_270  ))
//				{
//					AfxMessageBox("卧槽，旋转失败");
//					PauseCamera(TRUE);
//					pFilter->endParamTransfer();
//					return;
//				}
//				break;
//			}
//		case ROTE_HFLIP:
//			{
//				if(eNO_ERROR != pFilter->setParameter( "Flip H", TRUE ))
//				{
//					AfxMessageBox("卧槽，旋转失败");
//					PauseCamera(TRUE);
//					pFilter->endParamTransfer();
//					return;
//				}
//				break;
//			}
//		case ROTE_VFLIP:
//			{
//				
//				/*if(eNO_ERROR!=pFilter->setParameter( "Flip V", TRUE ))
//				{
//					AfxMessageBox("卧槽，旋转失败");
//					PauseCamera(TRUE);
//					pFilter->endParamTransfer();
//					return;
//				}*/
//				break;
//			}
//	}
//	pFilter->endParamTransfer();
//	PauseCamera(TRUE);
//	//	pListener->m_pConnectView = m_pConnectView;
//	/*pFilter->setParameter( "Flip H", TRUE );*/
//	//int q = m_Grabber.showDevicePage(*m_pConnectView);
//	//int T = m_Grabber.setHWND(*m_pConnectView);
//	//HWND pwnd = m_Grabber.getHWND();
//	//PauseCamera(TRUE);
//	AfxMessageBox("当你看到成功的这条消息时\n按理说应该已经旋转成功了!!\n（PS：至少我自己是这么觉得的）");
//	AfxMessageBox("但是你发现并没有这样\n你一定很疑惑这TM的是因为个啥？");
//	AfxMessageBox("如果你想知道答案的话\n就请你继续点击确定键\n进入相机对你的深情独白\n(PS1:你不想知道也得知道因为程序是我写的！）\n（PS2:You have no choice！）\n(PS3:哇咔咔咔咔咔咔！)");
//	AfxMessageBox("相机:\n     \"老子就是TM不转！\n      老子就是TM任性！\n      老子就是要气死你！\n      老子奏是这么贱！\n      你能把老子怎么地!\"");
//	AfxMessageBox("想旋转是吧\n要么歪脑袋\n要么自己调整相机角度\n怎么转随你想怎么转就这么转");
//}