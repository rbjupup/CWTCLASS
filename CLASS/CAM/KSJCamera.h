#ifndef _KSJCAMERA_H
#define _KSJCAMERA_H

//#include "KSJApiB.h"
//#include "KSJApiC.h"
//#include "KSJApiD.h"
//#include "ksjapiE.h"
//#include "ksjapiF.h"
#include "KSJApiBase.h"
#include "KSJApiCallback.h"
#include "KSJApiMultiProcess.h"
#include "KSJApiTriggerMode.h"
#include "KSJApiBayer.h"
#include "ksjCode.h"
#include "Image.h"

#define MAX_DEVICE 5

struct DEVICEINFO
{
	KSJ_DEVICETYPE		DeviceType;
	int					nIndex;
	WORD				wFirmwareVersion;
	int					m_nStartCol;
	int					m_nStartRow;
	int					m_nWidth;
	int					m_nHeight;
};

class CKSJCamera
{
public:
	int m_nChooseIndex;//0:��˿��λ��� 1:��Ƭ��λ���  (��˿��λ���IDΪ1����Ƭ��λ���IDΪ2)
	void JudgeCameraIndex(int nCamIndex);
	BOOL SetFreeMode(int nCamIndex);
	BOOL SetSoftTriggerMode(int nCamIndex);
	BOOL CaptureImage(int nCamIndex);
	BOOL m_pIsRGB[MAX_DEVICE];
	BOOL m_pIsPaused[MAX_DEVICE];
	BOOL m_pIsTriggerMode[MAX_DEVICE];
	int m_pCapturedImageNum[MAX_DEVICE];
	int m_nIndex[MAX_DEVICE];
	BOOL m_bIsConnected;
	CWnd  *m_pConnectView[MAX_DEVICE+3];
	BOOL SetPreviewPos(int nCamIndex, HWND hWnd, CRect sRect);

	BOOL PauseCamera(int nCamIndex, BOOL bIsWorking);


	BOOL PauseCameraView(int nCamIndex, BOOL bPause);

	BOOL CloseCamera();
	BOOL SetExposureTime(int nCamIndex, int nTime);

	BOOL SetBright(int nCamIndex,int nBright);
	BOOL SetContrast(int nCamIndex,int nContrast);


	BOOL IsCamaraColor(int nCamIndex); //�Ƿ��ɫ���

	BOOL IfSomeNoUse(int nCamIndex);

	int    m_pExposureTime[MAX_DEVICE];
	CMyImage m_pImage[MAX_DEVICE];

	CMyImage m_pColorImage[MAX_DEVICE];  //��ɫ���ͼƬ

	double m_pShowScale[MAX_DEVICE];
	int m_nDeviceNum;
	DEVICEINFO    m_pDeviceInfo[MAX_DEVICE];
	BOOL ConnectCamera();
	CKSJCamera();
	~CKSJCamera();

};

#endif