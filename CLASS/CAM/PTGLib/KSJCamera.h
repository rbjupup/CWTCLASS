#ifndef _KSJCAMERA_H
#define _KSJCAMERA_H

#include "KSJApiB.h"
#include "KSJApiC.h"
#include "KSJApiD.h"
#include "ksjapiE.h"
#include "ksjapiF.h"
#include "ksjCode.h"
#include "Image.h"
#include "Camera.h"

class CKSJCamera
{
public:
	int m_uNo;						//相机索引号--用于KSJ开发库中的nChannel
	//int m_ContrastSet;			//保存对比度值的大小
	void JudgeCameraIndex();
	BOOL SetFreeMode();
	BOOL SetSoftTriggerMode();
	BOOL CaptureImage();
	bool SoftTrigger();
	
	BOOL isV;
	BOOL isH;
	BOOL m_pIsYY;
	BOOL m_pIsRGB;
	BOOL m_pIsPaused;
	BOOL m_bIsConnected;
	BOOL m_pIsTriggerMode;  
	int  m_pCapturedImageNum;
	
	CWnd     *m_pConnectView;
	YCapture *m_ptrCap;
	
	ROTE_IMAGE   angle;
	MYDEVICEINFO   m_pDeviceInfo;
	
	BOOL SetPreviewPos(HWND hWnd, CRect sRect);
	BOOL PauseCamera(BOOL bIsWorking);
	BOOL CloseCamera();
	void RoteImage(ROTE_IMAGE RoteStatue);			//无效
	BOOL SetExposureTime(float nTime);
	BOOL SetContrast(int Contrast);				    //设置对比度 Lgy
	BOOL SetBrightness(int Brightness);				//设置亮度   Lgy
	BOOL SetGain(int Gain);							//增益设置   Lgy

	BOOL	  ConnectCamera(int nCameraSerialNo);
	ParaRange GetParamRange(int nCamIndex,ParaRange para);				//获取参数范围 Lgy
	
	float     m_pExposureTime;
	int       count;
	int       m_Gain;                //8-12 Lgy
	CMyImage  m_pImage;
	double    m_pShowScale;
	
	
	CKSJCamera();
	~CKSJCamera();
protected:
	KSJ_DEVICETYPE		m_DeviceType;

};


#endif