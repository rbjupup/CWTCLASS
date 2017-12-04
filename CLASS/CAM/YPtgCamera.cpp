
#include "StdAfx.h"
#include "YPtgCamera.h"
#include "GigECamera.h"

YPtgCamera::YPtgCamera(void)
{
	m_CameraInfoArry.RemoveAll();
	m_hWaitTimeEvent = CreateEvent(NULL,false,false,NULL);
	m_pCam=NULL;
	m_pConnectView=NULL;
	m_ptrCap=NULL;
	m_ImgW = 808;
	m_ImgH = 608;
	m_nIndex=0;
	m_nExposure = 0.60/*1.1*/;
	m_nGain = 0;
	CString str;
	m_bTrig = false;

}

YPtgCamera::~YPtgCamera(void)
{
	UninitCamera();
	m_CameraInfoArry.RemoveAll();
	if (m_pCam != NULL)
	{
		delete m_pCam;
		m_pCam = NULL;
	}

	if (m_pConnectView!=NULL)
	{
		delete m_pConnectView;
	}
	AfxMessageBox("灰点析构");
}



bool YPtgCamera::InitCamera(XCamerInfo XInfo)
{
	m_serial = XInfo.nserial;
	m_ImgW = XInfo.nResolution.cx;
	m_ImgH = XInfo.nResolution.cy;
	error = m_busMgr.GetCameraFromSerialNumber((unsigned int)m_serial,&guid);
	PrintMessage(error);
	if (error != PGRERROR_OK)
	{
		PrintMessage(error);
		return false;
	}
	// 	m_bufferImage1 = cvCreateImage(cvSize(m_ImgW,m_ImgH),IPL_DEPTH_8U,1);
	// 	m_bufferImage2 = cvCreateImage(cvSize(m_ImgW,m_ImgH),IPL_DEPTH_8U,1);
	// 	m_CaptureImage = m_bufferImage1;
	bufferNumber=1;

	RunSingleCamera(guid);
	return true;

}

void YPtgCamera::UninitCamera()
{
	BOOL judge=m_pCam->IsConnected();
	if (judge)
	{
		ConvertTrigToCon();
		error = m_pCam->StopCapture();
		error = m_pCam->Disconnect();
	}
}

bool YPtgCamera::StartCapure()
{
	error = m_pCam->StartCapture(CameraCaptureCallBack,this);
	PrintMessage(error);
	if (error != PGRERROR_OK)
	{
		return false;
	}
	m_preTime = 0;
	SetExposure(m_nExposure);
	TRACE("%.4f\n",m_nExposure);
	return true;

}

void YPtgCamera::ConvertConToTrig()
{
	if (!m_bTrig)
	{
		error = m_pCam->StopCapture();
		const unsigned int k_cameraPower = 0x610;
		const unsigned int k_powerVal = 0x80000000;
		error  = m_pCam->WriteRegister( k_cameraPower, k_powerVal );

		TriggerMode triggerMode;
		error = m_pCam->GetTriggerMode( &triggerMode );
		// Set camera to trigger mode 0
		triggerMode.onOff = true;
		triggerMode.polarity=1;//高电平触发
		triggerMode.mode = 0;
		triggerMode.parameter = 0;

		// A source of 7 means software trigger
		//设置为外触发,触发源为GPIO2
		triggerMode.source = 0;
		error = m_pCam->SetTriggerMode( &triggerMode );

		//新加光源控制
		StrobeControl strobeControl;
		strobeControl.source=1;//输出口为GPIO1
		error = m_pCam->GetStrobe(&strobeControl);
		strobeControl.onOff=true;
		strobeControl.polarity=0;//高电平触发有效
		error = m_pCam->SetStrobe(&strobeControl);

		unsigned int pDirection0,pDirection1;
		error = m_pCam->GetGPIOPinDirection(0,&pDirection0);
		error = m_pCam->GetGPIOPinDirection(1,&pDirection1);
		//pDirection0=0;//设置为输入口
		pDirection1=1;//设置为输出口
		error = m_pCam->SetGPIOPinDirection(0,pDirection0);
		error = m_pCam->SetGPIOPinDirection(1,pDirection1);


		//设置触发延时
		TriggerDelay pTriggerDelay;
		m_pCam->GetTriggerDelay(&pTriggerDelay);
		pTriggerDelay.absValue = 0.01;
		pTriggerDelay.absControl = true;
		m_pCam->SetTriggerDelay(&pTriggerDelay,false);

		error = m_pCam->StartCapture(CameraCaptureCallBack,this);
		m_bTrig = true;
	}

}
void YPtgCamera::ConvertTrigToCon()
{
	//连续采集时关闭频闪输出信号
	StrobeControl strobeControl;
	strobeControl.source=1;//GPIO1口
	error = m_pCam->GetStrobe(&strobeControl);
	strobeControl.onOff=true;
	strobeControl.polarity=1;//低电平有效,但之后会将该频闪信号关闭.之所以这样设置是为了在连续采集的时候让该IO口持续保持高电平输出状态(相机的特性:关闭频闪信号后会保持关闭前的输出状态)
	error = m_pCam->SetStrobe(&strobeControl);
	strobeControl.onOff=false;//关闭频闪信号
	error = m_pCam->SetStrobe(&strobeControl);

	TriggerMode triggerMode;
	error = m_pCam->GetTriggerMode( &triggerMode );
	triggerMode.onOff = false;    
	error = m_pCam->SetTriggerMode( &triggerMode );

	m_bTrig = false;
}

bool YPtgCamera::Trigger()
{
	// Fire software trigger
	const unsigned int k_fireVal = 0x80000000;
	const unsigned int k_softwareTrigger = 0x62C;

	if(CheckSoftwareTriggerPresence())
	{
		if(CheckTriggerReady())
		{
			error = m_pCam->WriteRegister( k_softwareTrigger, k_fireVal );
			m_bTrigWin=false;
			if (error != PGRERROR_OK)
			{
				TRACE("相机%d触发失败!!!\n", m_nIndex+1);
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else 
	{
		return false;
	}
	
	return true;
}

void YPtgCamera::SetExposure(float exposure)
{
	Property shutter(SHUTTER);
	error = m_pCam->GetProperty(&shutter);
	PrintMessage(error);
	// 	shutter.valueA = 0.05;
	shutter.absValue = exposure;
	shutter.absControl = true;
	shutter.autoManualMode = false;
	shutter.onOff = true;
	shutter.present = true;
	error = m_pCam->SetProperty(&shutter);
	m_nExposure = exposure;
	PrintMessage(error);
}

void YPtgCamera::StopCapure()
{
	error = m_pCam->StopCapture();
	//PrintMessage(error);
	// 	if (m_bufferImage1 != NULL)
	// 	{
	// 		cvReleaseImage(&m_bufferImage1);
	// 		m_bufferImage1 = NULL;
	// 	}
	// 	if (m_bufferImage2 != NULL)
	// 	{
	// 		cvReleaseImage(&m_bufferImage2);
	// 		m_bufferImage2 = NULL;
	// 	}
}

int YPtgCamera::FindAndGetCameraInfo(CameraInfo& camInfo)
{
	bool bFindAnyCamera = false;
	//PointGray 相机信息获取
	Error error;                                                                                                                                           
	BusManager busMgr;
	error = busMgr.GetNumOfCameras(&numCameras);
	if (error != PGRERROR_OK)
	{
		PrintMessage( error );
		return -1;
	}
	if ( numCameras >0 )
	{
		bFindAnyCamera = true;

		for (int i=0;i<(int)numCameras;i++)
		{
			error = busMgr.GetCameraFromIndex(i, &guid);
			if (error != PGRERROR_OK)
			{
				PrintMessage( error );
				return -1;
			}
			Camera cam;
			// Connect to a camera
			error = cam.Connect(&guid);
			if (error != PGRERROR_OK)
			{
				PrintMessage( error );
				return -1;
			}
			// Power on the camera
			const unsigned int k_cameraPower = 0x610;
			const unsigned int k_powerVal = 0x80000000;
			error  = cam.WriteRegister( k_cameraPower, k_powerVal );
			if (error != PGRERROR_OK)
			{
				PrintMessage( error );
				return -1;
			}
			const unsigned int millisecondsToSleep = 100;
			unsigned int regVal = 0;

			// Wait for camera to complete power-up
			do 
			{
				#if defined(WIN32) || defined(WIN64)
				Sleep(millisecondsToSleep);    
				#else
				usleep(millisecondsToSleep * 1000);
				#endif
				error = cam.ReadRegister(k_cameraPower, &regVal);
				if (error != PGRERROR_OK)
				{
					PrintMessage( error );
					return -1;
				}
			} while ((regVal & k_powerVal) == 0);
			// Get the camera information
			
			error = cam.GetCameraInfo(&camInfo);
			if (error != PGRERROR_OK)
			{
				PrintMessage( error );
				return -1;
			}
			XCamerInfo CInfo;
			CInfo.strCameraModel = camInfo.modelName;
			CInfo.strCameraVendor = camInfo.vendorName;
			CInfo.nserial = camInfo.serialNumber;
			CString strResonlution;
			strResonlution = camInfo.sensorResolution;
			int nPos = strResonlution.Find('x');
			if (nPos>0)
			{
				CInfo.nResolution.cx = _ttoi(strResonlution.Left(nPos));
				CInfo.nResolution.cy = _ttoi(strResonlution.Right(strResonlution.GetLength()-nPos-1));
			}
			
			
			CInfo.bIsColor = camInfo.isColorCamera;
		//	m_CameraInfoArry.Add(CInfo);             、//@Lgy
			// Disconnect the camera
		/*	error = cam.Disconnect();
			if (error != PGRERROR_OK)
			{
				PrintMessage( error );
				return -1;
			}*/
		}
	}
	return 0;
}

void YPtgCamera::PrintMessage(Error MError)
{
	if (MError != PGRERROR_OK)
	{
		CString csMessage;
		csMessage.Format("CameraInfo Failure: %s", MError.GetDescription());
		AfxMessageBox( csMessage, MB_ICONSTOP );
		return;
	}
}

int YPtgCamera::RunSingleCamera( PGRGuid guid )
{
	error = m_pCam->Connect(&guid);
	PrintMessage(error);
	if (error != PGRERROR_OK)
	{
		return -1;
	}
	CameraInfo camInfo;
	error = m_pCam->GetCameraInfo(&camInfo);
	PrintMessage(error);

	//设置图像格式
	// 	VideoMode mode = VIDEOMODE_FORMAT7;
	//	FrameRate rate = FRAMERATE_FORMAT7;
	// 	VideoMode mode = VIDEOMODE_1280x960Y8;
	// 	FrameRate rate = FRAMERATE_60;
	//  	m_pCam->SetVideoModeAndFrameRate(mode, rate);
	//  
	//  	m_pCam->GetVideoModeAndFrameRate(&mode, &rate);

	//Format7Info   pInfo;
	//bool          pSupported;
	//Format7PacketInfo fmt7PacketInfo;
	//error = m_pCam->GetFormat7Info(&pInfo, &pSupported);
	//Format7ImageSettings fmt7ImageSettings;
	//fmt7ImageSettings.mode = MODE_0;
	//fmt7ImageSettings.offsetX = 0;
	//fmt7ImageSettings.offsetY = 0;
	//fmt7ImageSettings.width = pInfo.maxWidth;
	//fmt7ImageSettings.height = pInfo.maxHeight;
	//fmt7ImageSettings.pixelFormat = PIXEL_FORMAT_MONO8;
	//error = m_pCam->ValidateFormat7Settings(&fmt7ImageSettings, &pSupported, &fmt7PacketInfo );
	//error = m_pCam->SetFormat7Configuration(&fmt7ImageSettings, fmt7PacketInfo.recommendedBytesPerPacket );
	//VideoMode mode;
	//FrameRate rate;
	//m_pCam->GetVideoModeAndFrameRate(&mode, &rate);

	GigEImageSettingsInfo imageSettingsInfo;
	error = m_pCam->GetGigEImageSettingsInfo( &imageSettingsInfo );
	if (error != PGRERROR_OK)
	{
		return -1;
	}
	GigEImageSettings imageSettings;
	imageSettings.offsetX = 0;
	imageSettings.offsetY = 0;
	imageSettings.height = imageSettingsInfo.maxHeight;
	imageSettings.width = imageSettingsInfo.maxWidth;
	imageSettings.pixelFormat = PIXEL_FORMAT_MONO8;
	error = m_pCam->SetGigEImageSettings( &imageSettings );
	if (error != PGRERROR_OK)
	{
		return -1;
	}
	////获取分辨率
	//char *c = camInfo.sensorResolution;	
	//CString str = (CString)c;
	//int t = str.Find("x");
	//CString str1,str2;
	//str1 = str.Left(t);
	//str2 = str.Right(t-1);
	//int w = atoi(str.Left(t));
	//int h = atoi(str.Right(t-1));

	//设置曝光
	//set shutter
	Property shutter(SHUTTER);
	error = m_pCam->GetProperty(&shutter);
	PrintMessage(error);
	// 	shutter.valueA = 0.05;
	shutter.absValue = m_nExposure;
	shutter.absControl = true;
	shutter.autoManualMode = false;
	shutter.onOff = true;
	shutter.present = true;
	error = m_pCam->SetProperty(&shutter);
	PrintMessage(error);
	//

	//设置增益
	//set shutter
	Property gain(GAIN);
	error = m_pCam->GetProperty(&gain);
	PrintMessage(error);
	// 	shutter.valueA = 0.05;
	gain.absValue = m_nGain;
	gain.absControl = true;
	gain.autoManualMode = false;
	gain.onOff = true;
	gain.present = true;
	error = m_pCam->SetProperty(&gain);
	//设置帧频
	//set frame rate
	Property framerate;
	framerate.type= FRAME_RATE;
	error = m_pCam->GetProperty(&framerate);
	PrintMessage(error);
	framerate.absValue = 6;
	framerate.absControl = true;
	//Property Fframerate;
	//Fframerate.type= FRAME_RATE;
	//error = m_pCam->GetProperty(&Fframerate);

	framerate.autoManualMode = false;
	framerate.onOff = true;
	framerate.present = true;
	error = m_pCam->SetProperty(&framerate);
	PrintMessage(error);

	// 	//设置触发延时
	// 	TriggerDelay pTriggerDelay;
	// 	m_pCam->GetTriggerDelay(&pTriggerDelay);
	// 	pTriggerDelay.absValue = 0.407;
	// 	pTriggerDelay.absControl = true;
	// 	m_pCam->SetTriggerDelay(&pTriggerDelay,false);

	//设置采集的ROI


	ConvertTrigToCon();
	// 	StartCapure();
	return 0;
}

bool YPtgCamera::CheckTriggerReady()
{
	// Poll the camera to make sure the camera is actually in trigger mode
	// before we start it (avoids timeouts due to the trigger not being armed)
	if (!m_pCam->IsConnected())
	{
		return false;
	}

	const unsigned int k_softwareTrigger = 0x62C;
	Error error;
	unsigned int regVal = 0;

	do 
	{
		error = m_pCam->ReadRegister( k_softwareTrigger, &regVal );
		if (error != PGRERROR_OK)
		{
			return false;
		}

	} while ( (regVal >> 31) != 0 );

	return true;
}

bool  YPtgCamera::CheckSoftwareTriggerPresence()
{
	// Check that the camera actually supports the PGR SOFT_ASYNC_TRIGGER or SOFTWARE_TRIGGER
	// method of software triggering
	if (!m_pCam->IsConnected())
	{
		return false;
	}

	const unsigned int k_triggerInq = 0x530;

	Error error;
	unsigned int regVal = 0;

	error = m_pCam->ReadRegister( k_triggerInq, &regVal );

	if (error != PGRERROR_OK)
	{
		return false;
	}

	if( ( regVal & 0x10000 ) != 0x10000 )
	{
		return false;
	}

	return true;
}
//void PointGreyCamera::LoadCameraPara()
//{
//	CIni CameraParaIni;
//	CString str;
//	str.Format("CameraPara.ini");
//	CameraParaIni.Read(str);
//	CameraParaIni.GetValue("Para","ExpouseTime",m_nExposure);
//}
//void PointGreyCamera::SaveCameraPara()
//{
//	CIni CameraParaIni;
//	CString str;
//	str.Format("CameraPara.ini");
//	CameraParaIni.Read(str);
//	CameraParaIni.SetValue("Para","ExpouseTime",m_nExposure);
//	CameraParaIni.Write(str);
//}
BOOL YPtgCamera::ConnectCamera(int nCameraSerialNo)
{
	
	Error error = m_busMgr.GetCameraFromSerialNumber((unsigned int)nCameraSerialNo,&m_guid);       
	
	if(error == PGRERROR_BUS_MASTER_FAILED)
		return FALSE;
	PrintMessage(error);
	m_pCam = new GigECamera; //2015-8
	error = m_pCam->Connect(&m_guid);         //？？？Lgy
	PrintMessage(error);
	if (error != PGRERROR_OK)
	{
		return FALSE;
	}
	CameraInfo camInfo;
	error = m_pCam->GetCameraInfo(&camInfo);
	PrintMessage(error);
	GigEImageSettingsInfo imageSettingsInfo;
	error = m_pCam->GetGigEImageSettingsInfo( &imageSettingsInfo );
	if (error != PGRERROR_OK)
	{
		return FALSE;
	}
	GigEProperty PacketSize;
	PacketSize.propType=PACKET_SIZE;//设置数据包大小
	m_pCam->GetGigEProperty(&PacketSize);
	PacketSize.value=1400;
	m_pCam->SetGigEProperty(&PacketSize);
	GigEImageSettings imageSettings;
	imageSettings.offsetX = 0;
	imageSettings.offsetY = 0;
	imageSettings.height = imageSettingsInfo.maxHeight;
	imageSettings.width = imageSettingsInfo.maxWidth;
	imageSettings.pixelFormat = PIXEL_FORMAT_MONO8;
	//分配内存
	m_pImage.CreateEmpty(imageSettings.width, imageSettings.height, 8, 0);
	error = m_pCam->SetGigEImageSettings( &imageSettings );
	//m_pCam=this->m_pCam;
	
// 	StartCapure();//@Whq810
// 	SetFreeMode();
	if (error != PGRERROR_OK)
	{
		return FALSE;
	}
	
	return TRUE;
}
BOOL YPtgCamera::SetContrast(float Contrast)
{

	return TRUE;
}

BOOL YPtgCamera::SetExposureTime(float nTime)
{
	//设置曝光
	//set shutter
	Property shutter(SHUTTER);
	Error error = m_pCam->GetProperty(&shutter);
	PrintMessage(error);
	if (error != PGRERROR_OK)
	{
		return FALSE;
	}
	// 	shutter.valueA = 0.05;
	shutter.absValue = nTime;
	shutter.absControl = true;
	shutter.autoManualMode = false;
	shutter.onOff = true;
	shutter.present = true;
	error = m_pCam->SetProperty(&shutter);
	PrintMessage(error);
	if (error != PGRERROR_OK)
	{
		return FALSE;
	}
	return TRUE;
}
bool YPtgCamera::SetGain(float Vgain)
{	
	Property gain(GAIN);
	Error error = m_pCam->GetProperty(&gain);
	PrintMessage(error);
	if (error != PGRERROR_OK)
	{
		return false;
	}
	gain.absValue = Vgain;
	gain.absControl = true;
	gain.autoManualMode = false;
	gain.onOff = true;
	gain.present = true;
	error = m_pCam->SetProperty(&gain);
	PrintMessage(error);
	if (error != PGRERROR_OK)
	{
		return false;
	}
	return true;
}

bool YPtgCamera::SetBrightness(float Brightness)
{
	Property brightness(BRIGHTNESS);
	Error error = m_pCam->GetProperty(&brightness);
	PrintMessage(error);
	if (error != PGRERROR_OK)
	{
		return false;
	}
	brightness.absValue = Brightness;
	brightness.absControl = true;
	brightness.autoManualMode = false;
	brightness.onOff = true;
	brightness.present = true;
	error = m_pCam->SetProperty(&brightness);
	PrintMessage(error);
	if (error != PGRERROR_OK)
	{
		return false;
	}
	return true;
}

ParaRange YPtgCamera::GetParamRange(int nCamIndex,ParaRange para)
{
	//增益
	PropertyInfo Gain(GAIN);
	Error error = m_pCam->GetPropertyInfo(&Gain);
	PrintMessage(error);
	if (error != PGRERROR_OK)
	{
		AfxMessageBox("error");
//		return false;
	}
	para.MaxGain = Gain.absMax;
	para.MinGain = Gain.absMin;
	//亮度
	PropertyInfo Brightness(BRIGHTNESS);
	error = m_pCam->GetPropertyInfo(&Brightness);
	PrintMessage(error);
	if (error != PGRERROR_OK)
	{
		AfxMessageBox("error");
		//		return false;
	}
	para.MinBrightness = Brightness.absMin;
	para.MaxBrightness = Brightness.absMax;
	//曝光
	PropertyInfo Exposure(SHUTTER);
    error = m_pCam->GetPropertyInfo(&Exposure);
	PrintMessage(error);
	if (error != PGRERROR_OK)
	{
		AfxMessageBox("error");
		//		return false;
	}
	para.MinExposure = Exposure.absMin;
	para.MaxExposure = Exposure.absMax;

	//锐化
	PropertyInfo Shapness(SHARPNESS);
	error = m_pCam->GetPropertyInfo(&Shapness);
	PrintMessage(error);
	if (error != PGRERROR_OK)
	{
		AfxMessageBox("error");
		//		return false;
	}
	para.MinContrast = Shapness.min;
	para.MaxContrast = Shapness.max;

	return para;
}

float YPtgCamera::GetFrameRate()    //在修改
{
	
	Property framerate;
	Error error;
	framerate.type = FRAME_RATE;
	
	error =m_pCam->GetProperty(&framerate);
	if (error != PGRERROR_OK)
	{
		PrintMessage(error);
		return -1;
	}
	
	return framerate.absValue;
}

bool YPtgCamera::SetFrameRate(float fraRate)
{
	Property framerate;
	framerate.type= FRAME_RATE;
	Error error = m_pCam->GetProperty(&framerate);
	PrintMessage(error);
	if (error != PGRERROR_OK)
	{
		return false;
	}
	framerate.absValue = fraRate;
	framerate.absControl = true;
	framerate.autoManualMode = false;
	framerate.onOff = true;
	framerate.present = true;
	error = m_pCam->SetProperty(&framerate);
	PrintMessage(error);
	if (error != PGRERROR_OK)
	{
		return false;
	}
	return true;
}

BOOL YPtgCamera::CloseCamera()
{
	if (m_pCam->IsConnected())
	{
		Error error = m_pCam->StopCapture();
		error = m_pCam->Disconnect();
		m_pImage.DeleteMe();
		SetFreeMode();
	}
	return TRUE;
}

BOOL YPtgCamera::PauseCamera(BOOL bIsWorking)
{
	Error error;
	if(!bIsWorking)
	{
		error = m_pCam->StartCapture(CameraCaptureCallBack,this);
		PrintMessage(error);
		SetFreeMode();
	}
	else
	{
		error = m_pCam->StopCapture();
		PrintMessage(error);
		StrobeControl strobeControl;
		strobeControl.source=1;//GPIO1口
		error = m_pCam->GetStrobe(&strobeControl);
		strobeControl.onOff=true;
		strobeControl.polarity=1;//低电平有效,但之后会将该频闪信号关闭.之所以这样设置是为了在连续采集的时候让该IO口持续保持高电平输出状态(相机的特性:关闭频闪信号后会保持关闭前的输出状态)
		error = m_pCam->SetStrobe(&strobeControl);
		strobeControl.onOff=false;//关闭频闪信号
		error = m_pCam->SetStrobe(&strobeControl);
		PrintMessage(error);
	}
	return TRUE;
}

BOOL YPtgCamera::SetPreviewPos(HWND hWnd, CRect sRect)
{
//	int nRet;
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
//	nRet = KSJ_PreviewSetPos(m_uNo, hWnd, sRect.left, sRect.top, sRect.Width(), sRect.Height());
//	return (nRet==RET_SUCCESS);
	return TRUE;
}

BOOL YPtgCamera::CaptureImage()
{
	CTimeCount time;
	time.Start();
	time.End();
	if(m_pIsTriggerMode)
	{
		m_bImageReady = false;
		SoftTrigger();
		while(!m_bImageReady && time.GetUseTime() < 0.4)
		{
			::WaitForSingleObject(m_hWaitTimeEvent, 1);
			time.End();
		}
	}
	else
	{
		m_bImageReady = false;
		while(!m_bImageReady && time.GetUseTime() < 0.4)
		{
			::WaitForSingleObject(m_hWaitTimeEvent, 1);
			time.End();
		}
	}
	time.End();
	if (time.GetUseTime() > 0.4)
	{
		AfxMessageBox("Capture image time out!");
		return FALSE;
	}
	return TRUE;
}

bool YPtgCamera::SoftTrigger()
{
	// Fire software trigger
	const unsigned int k_fireVal = 0x80000000;
	const unsigned int k_softwareTrigger = 0x62C;

	if(CheckSoftwareTriggerReady())
	{
		Error error = m_pCam->WriteRegister( k_softwareTrigger, k_fireVal );
		PrintMessage(error);
		if (error != PGRERROR_OK)
		{
			TRACE("相机%d触发失败!!!\n", m_uNo+1);
			return false;
		}
	}
	else 
	{
		return false;
	}
	return true;
}

bool YPtgCamera::CheckSoftwareTriggerReady()
{
	// Check that the camera actually supports the PGR SOFT_ASYNC_TRIGGER or SOFTWARE_TRIGGER
	// method of software triggering
	if (!m_pCam->IsConnected())
	{
		return false;
	}
	const unsigned int k_triggerInq = 0x530;
	Error error;
	unsigned int regVal = 0;
	error = m_pCam->ReadRegister( k_triggerInq, &regVal );
	if (error != PGRERROR_OK)
	{
		return false;
	}
	if( ( regVal & 0x10000 ) != 0x10000 )
	{
		return false;
	}
	const unsigned int k_softwareTrigger = 0x62C;
	do 
	{
		error = m_pCam->ReadRegister( k_softwareTrigger, &regVal );
		if (error != PGRERROR_OK)
		{
			return false;
		}

	} while ( (regVal >> 31) != 0 );//死循环？？？ 8-26 Lgy

	return true;
}
BOOL YPtgCamera::SetSoftTriggerMode()
{
	if(m_pIsTriggerMode)
		return TRUE;
	//	JudgeCameraIndex(nCamIndex);
	Error error = m_pCam->StopCapture();
	const unsigned int k_cameraPower = 0x610;
	const unsigned int k_powerVal = 0x80000000;
	error  = m_pCam->WriteRegister( k_cameraPower, k_powerVal );

	//频闪控制
	StrobeControl strobeControl;
	strobeControl.source=1;//输出口为GPIO1
	error = m_pCam->GetStrobe(&strobeControl);
	strobeControl.onOff=true;
	strobeControl.polarity=1;//高电平触发有效
	error = m_pCam->SetStrobe(&strobeControl);

	//unsigned int pDirection0;
	unsigned int pDirection1;
	//error = m_pCam->GetGPIOPinDirection(2,&pDirection0);
	//pDirection0=0;//设置为输入口
	//error = m_pCam->SetGPIOPinDirection(2,pDirection0);
	error = m_pCam->GetGPIOPinDirection(1,&pDirection1);
	pDirection1=1;//设置为输出口
	error = m_pCam->SetGPIOPinDirection(1,pDirection1);

	TriggerMode triggerMode;
	error = m_pCam->GetTriggerMode( &triggerMode );
	// Set camera to trigger mode 0
	triggerMode.onOff = true;
	triggerMode.mode = 0;
	triggerMode.parameter = 0;
	// A source of 7 means software trigger
	triggerMode.source = 7;
	error = m_pCam->SetTriggerMode( &triggerMode );
	error = m_pCam->StartCapture(CameraCaptureCallBack,this);
	if (error != PGRERROR_OK)
	{
		return FALSE;
	}
	m_pIsTriggerMode = TRUE;
	return TRUE;
}
BOOL YPtgCamera::SetFreeMode()
{
	//连续采集时关闭频闪输出信号
	StrobeControl strobeControl;
	strobeControl.source=1;//GPIO1口
	Error error = m_pCam->GetStrobe(&strobeControl);
	strobeControl.onOff=true;
	strobeControl.polarity=0;//低电平有效,但之后会将该频闪信号关闭.之所以这样设置是为了在连续采集的时候让该IO口持续保持高电平输出状态(相机的特性:关闭频闪信号后会保持关闭前的输出状态)
	error = m_pCam->SetStrobe(&strobeControl);
	strobeControl.onOff=false;//关闭频闪信号
	error = m_pCam->SetStrobe(&strobeControl);
	TriggerMode triggerMode;
	error = m_pCam->GetTriggerMode( &triggerMode );
	triggerMode.onOff = false;    
	error = m_pCam->SetTriggerMode( &triggerMode );
	if (error != PGRERROR_OK)
	{
		return FALSE;
	}
	m_pIsTriggerMode = false;
	return TRUE;
}

void CameraCaptureCallBack(Image* pImage, const void* pCallbackData)
{
	YPtgCamera *pCamera = (YPtgCamera *)pCallbackData;

 	pCamera->m_bTrigWin=true;
	 
 	Error error;
 	CString str;
 	memcpy(pCamera ->m_pImage.m_lpDibArray,pImage->GetData(),pImage->GetDataSize());/////////////////////@whq
 	pCamera ->m_ptrCap->CamCallBack();

}

void YPtgCamera::JudgeCameraIndex()
{
#if _DEBUG
	return;
#endif
}

BOOL YPtgCamera::GetDeviceInformation(CString& index,WORD& FirmwareVersion,int& m_nWidth,int& m_nHeight )
{   
	unsigned int numCameras;	
	BusManager busMgr;
	busMgr.GetNumOfCameras(&numCameras);
	if(numCameras==0)
		return FALSE;
	CameraInfo camInfo;
	FindAndGetCameraInfo(camInfo);
	//index=camInfo.serialNumber;

	char tempindex[10]={0};
	itoa(camInfo.serialNumber,tempindex,10); //Lgy 8-24
	index = tempindex;

	GigEImageSettingsInfo imageSettingsInfo;
	//m_pCam=new GigECamera;

	int tempIndex = atoi(index);        // Lgy 8-24
	ConnectCamera(tempIndex);
	m_pCam->GetGigEImageSettingsInfo(&imageSettingsInfo);
	m_nHeight=imageSettingsInfo.maxHeight;
	m_nWidth=imageSettingsInfo.maxWidth;
	for(int i=0;camInfo.firmwareVersion[i]!='\0';++i)
	{
		FirmwareVersion=camInfo.firmwareVersion[i]-'0';
		FirmwareVersion=FirmwareVersion*10;
	}
	return TRUE; //Lgy 8-11
	//whq
	//CloseCamera();
	//delete m_pCam; //@Whq 88
}

