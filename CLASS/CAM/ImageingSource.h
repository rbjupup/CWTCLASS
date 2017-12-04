#ifndef _IMAGEINGSOURCE_H
#define _IMAGEINGSOURCE_H

#include "Image.h"
#include "tisudshl.h"
#include "Camera.h" 

//#include "ProTime.h"	
using namespace DShowLib;
static const GUID VCDElement_SoftTrigger =   	{ 0xFDB4003C, 0x552C, 0x4FAA, { 0xB8, 0x7B, 0x42, 0xE8, 0x88, 0xD5, 0x41, 0x47 } };

class CListener  :public GrabberListener 
{
public:
	virtual void frameReady(Grabber& param, smart_ptr<MemBuffer> pBuffer, DWORD FrameNumber);
	CWnd *m_pConnectView;
	CMyImage *m_pImage;
	BOOL *m_pIsPaused;
	BOOL *m_pIsTriggerMode;
	BOOL *m_pIsSoftFinish;
	YImageingSource *m_pImageSource;
 	CListener();
 	~CListener();
};
class CSimplePropertyAccess;

class YImageingSource
{
public:
	double m_pShowScale;
	tIVCDPropertyItemsPtr pItems;
	YCapture *m_ptrCap;
	smart_com<DShowLib::IFrameFilter> pFilter;
	BOOL  m_pIsSoftFinish;
	BOOL  m_pIsRGB;
	BOOL  m_pIsPaused;
	ROTE_IMAGE angle;//旋转角度
	BOOL isV;        //是否进行了垂直旋转@L
	BOOL isH;        //是否进行了水平旋转@L
	int  count;      //旋转次数@L
	BOOL m_bIsConnected;
	int  m_pExposureTime;
	int  m_pBrightness;  //Lgy
	int  m_pGain;        //Lgy
	int  m_pContrast;    //Lgy

	CWnd *m_pConnectView;
	CMyImage m_pImage;
	BOOL m_pIsTriggerMode;	       //是否进行了触发模式
	int  m_nColor;                 //x相机图片的深度
	MYDEVICEINFO   m_pDeviceInfo;
	BOOL m_pIsSoftTriggerMode;
	int  m_nDeviceNum;
	BOOL ConnectCamera(int nCameraSerialNo);     
	BOOL SoftTrigger();
	BOOL PauseCamera(BOOL bIsWorking);          //bIsWorking为FALSE暂停
	BOOL CloseCamera();
	BOOL SetExposureTime(float ExposureTime);   //曝光时间MS	
	BOOL SetCaptureMode();                      //设置硬件触发采集模式
	BOOL CaptureImage();                        //获取图片
	BOOL SetSoftTriggerMode();                  //设置相机为软件触发模式	
	BOOL SetFreeMode();                         //设置指定相机的触发模式为自由运行模式
//	void RoteImage(ROTE_IMAGE RoteStatue);
	BOOL SetPreviewPos(HWND hwnd, CRect sRect);

	BOOL SetBrightness(float Brightness);       //设置亮度   Lgy 8-19
	BOOL SetGain(float Gain);					//设置增益   Lgy	 8-19
	BOOL SetContrast(float Contrast);           //设置对比度 Lgy  8-19
	int  GetFPS();                              //获取帧频   Lgy  8-19
	ParaRange GetParamRange(int nCamIndex,ParaRange para);	//获取参数范围 Lgy 8-19

public:
	//CProTime  m_time[MAX_DEVICE];
    tIVCDPropertyInterfacePtr	  pItf;
    tIVCDPropertyItemsPtr    	  pProps;		
	tIVCDAbsoluteValuePropertyPtr ExposureRange;
	tIVCDRangePropertyPtr         BrightnessRange; //Lgy  8-19 亮度范围
	tIVCDRangePropertyPtr         ContrastRange;   //Lgy  8-19 对比度范围
	

	tIVCDRangePropertyPtr         gainRange;
	tIVCDSwitchPropertyPtr        triggerswitch;
	tIVCDButtonPropertyPtr        softtrigger;
	tFrameHandlerSinkPtr          pSink0;

	//CSimplePropertyAccess         m_BrightnessRange; //Lgy 8-19

	Grabber    m_Grabber; 
    CListener* pListener;
	__int64    m_nSerialNumber;
		
	YImageingSource();
	~YImageingSource();
    int  GetDeviceNumber();
	//int  GetDeviceInformation(LONGLONG& index,WORD& version,int& Width,int& Height,int i);   
	int  GetDeviceInformation(CString& index,WORD& version,int& Width,int& Height,int i);   //Lgy 8-24 将所有此函数index 参数类型 变为Cstring
};
#endif