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
	ROTE_IMAGE angle;//��ת�Ƕ�
	BOOL isV;        //�Ƿ�����˴�ֱ��ת@L
	BOOL isH;        //�Ƿ������ˮƽ��ת@L
	int  count;      //��ת����@L
	BOOL m_bIsConnected;
	int  m_pExposureTime;
	int  m_pBrightness;  //Lgy
	int  m_pGain;        //Lgy
	int  m_pContrast;    //Lgy

	CWnd *m_pConnectView;
	CMyImage m_pImage;
	BOOL m_pIsTriggerMode;	       //�Ƿ�����˴���ģʽ
	int  m_nColor;                 //x���ͼƬ�����
	MYDEVICEINFO   m_pDeviceInfo;
	BOOL m_pIsSoftTriggerMode;
	int  m_nDeviceNum;
	BOOL ConnectCamera(int nCameraSerialNo);     
	BOOL SoftTrigger();
	BOOL PauseCamera(BOOL bIsWorking);          //bIsWorkingΪFALSE��ͣ
	BOOL CloseCamera();
	BOOL SetExposureTime(float ExposureTime);   //�ع�ʱ��MS	
	BOOL SetCaptureMode();                      //����Ӳ�������ɼ�ģʽ
	BOOL CaptureImage();                        //��ȡͼƬ
	BOOL SetSoftTriggerMode();                  //�������Ϊ�������ģʽ	
	BOOL SetFreeMode();                         //����ָ������Ĵ���ģʽΪ��������ģʽ
//	void RoteImage(ROTE_IMAGE RoteStatue);
	BOOL SetPreviewPos(HWND hwnd, CRect sRect);

	BOOL SetBrightness(float Brightness);       //��������   Lgy 8-19
	BOOL SetGain(float Gain);					//��������   Lgy	 8-19
	BOOL SetContrast(float Contrast);           //���öԱȶ� Lgy  8-19
	int  GetFPS();                              //��ȡ֡Ƶ   Lgy  8-19
	ParaRange GetParamRange(int nCamIndex,ParaRange para);	//��ȡ������Χ Lgy 8-19

public:
	//CProTime  m_time[MAX_DEVICE];
    tIVCDPropertyInterfacePtr	  pItf;
    tIVCDPropertyItemsPtr    	  pProps;		
	tIVCDAbsoluteValuePropertyPtr ExposureRange;
	tIVCDRangePropertyPtr         BrightnessRange; //Lgy  8-19 ���ȷ�Χ
	tIVCDRangePropertyPtr         ContrastRange;   //Lgy  8-19 �Աȶȷ�Χ
	

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
	int  GetDeviceInformation(CString& index,WORD& version,int& Width,int& Height,int i);   //Lgy 8-24 �����д˺���index �������� ��ΪCstring
};
#endif