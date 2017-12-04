#ifndef _CAMERA_H
#define _CAMERA_H

//#include "AcutanceCamera.h"
//#include "basler.h"
//#include "svPTGrab2.h"
/*#include "ImageingSource.h"*/
#include "Image.h"
#define NO_CAMERA 0
#define KSJ 1
#define ACU 2
#define BAS 3
#define PTG 4
#define IMG 5
#define DS  6
#define MAX_DEVICE 1
enum ROTE_IMAGE 
{
	ROTE_0=0,
	ROTE_90=90,
	ROTE_VFLIP,
	ROTE_HFLIP
};


class CKSJCamera;
class YImageingSource;
class YPtgCamera;
//class CDSCamera;

struct IMGSHOW   //DS�����ʼ����Ҫ������ʾ�ؼ�����Ϳ��
{
	HWND ctlhwnd;  //�ؼ����
	int  ctlwidth; //�ؼ���
	int  ctlheight;//�ؼ���
};

struct MYDEVICEINFO
{
	CString             Str_index;       //���к�   Lgy 8-24  �ܶ����кŲ���INT�� �������������Cstring ������
	int 				nIndex;          //���к�   Lgy 8-24
	int                 m_nCameraType;   //���Ʒ��
	WORD				wFirmwareVersion;//�̼��汾 Lgy 8-24
	int					m_nStartCol;
	int					m_nStartRow;
	int					m_nWidth;
	int					m_nHeight;
};

struct CapturePara
{
	bool  m_bValid;
	float m_fExposureTime;
	float m_fGain;
	float m_fFrameRate;
};

struct ParaRange      //�����ȡ������������С�����ṹ��
{
	int MaxBrightness;
	int MinBrightness;
	int MaxGain;
	int MinGain;
	int MaxContrast;
	int MinContrast;
	int MaxExposure;
	int MinExposure;
};

class YCapture
{
public:

    static int   ExIndex;			 //Lgy KSJ���֮����±���������,��Ϊ���������ļ���������������и��±ꡣÿ�õ�һ��KSJ��� ��1
	int    ExCamIndex[MAX_DEVICE];	 /*Lgy �Զ������������0��ʼ�������±� �����ͬ���֮���Ĭ��nChannel,����KSJ������������������3��
	                          ���Ǽ��������ӵ�KSJ�����Ĭ��nChannelΪ0����ExCamIndex[2] = 0;*/
	int	  ExDsIndex;				// ÿ����һ��DS ��� ExDsIndex ��1����ӦDS�����ʼ��֮�����ɵ�iCameraID,�������ExDsCamIndex[]
	int   ExDsCamIndex[MAX_DEVICE];  //����DS����������Զ������������0��ʼ���±�

	int   m_uNo;
	int   m_nCameraIndex;  //���к��м����
	int	  m_nCameraType;
	int   m_nGain;      //Lgy
	int   m_TempIndex;  //��ʱ�����±� ���������±� ExCamIndex[],ExDsCamIndex[] �ȵ�Lgy 
	float m_nExpouse;   //Lgy
	bool  m_bValid;

	CMyImage   *m_pCaptureImage;
	CWnd       *m_pCautureView;
	ROTE_IMAGE angle;


	void CamCallBack();
	void SetConnectView(CWnd *pWnd);
	void CamCallBack(ROTE_IMAGE Orientate,BOOL ish,BOOL isV);

	
	bool CaptureImage();
	bool SoftTrigger();
	bool SetFreeMode();
	bool ConnectCamera();
	bool SetSoftTriggerMode();  
	bool PauseCamera(BOOL bIsWorking);
	bool SetExposureTime(float millSeconds);
	bool ConnectCamera(IMGSHOW imgshow[],int maxdevice,int index);  // Lgy 8-26 1Ϊ�ṹ��������������ؼ������ߵȣ�index����Ycapture[i]���i�±꣬
																	// ������������е�λ��,maxdevice Ϊ�����С

	BOOL		CloseCamera();										    //�رս����˳��Ȳ���֮ǰ�ر����  Lgy	
	BOOL		SetGain(int Gain);										//��������	   Lgy
	BOOL		SetContrast(int Contrast);							    //���öԱȶ�   Lgy
	BOOL		SetBrightness(int Brightness);							//��������     Lgy
	BOOL		JudgeCameraType(int m_nCameraIndex);					//���������� �ж�Type Lgy
	ParaRange	GetParamRange(int nCamIndex,ParaRange para);		
	
//	void RoteImage(ROTE_IMAGE RoteStatue);						//��תͼ��
	int  GetDeviceNumber();
	//void GetDeviceInformation(LONGLONG& index,WORD& version,int& Width,int& Height);
	
	CKSJCamera      *m_KSJCamera;
	YImageingSource *m_IMGCamera;
	YPtgCamera      *m_PTGCamera;
//	CDSCamera       *m_DSCamera;  //Lgy 8-22

	YCapture();
	~YCapture();
};


class CCamera
{
public:
//	YPtgCamera *pPtgCam;		 //Lgy
	static int flag;
	int        m_nDeviceNum;
	CString	   m_sCameraInfoPath;

	YCapture   m_Capture[MAX_DEVICE];
	MYDEVICEINFO m_pDeviceInfo[MAX_DEVICE];

	UINT       m_pCameraType[MAX_DEVICE];
	UINT       m_pCameraIndex[MAX_DEVICE];
	
	int        m_Gain[MAX_DEVICE];            
	CMyImage   *m_pImage[MAX_DEVICE];
	CWnd       *m_pConnectView[MAX_DEVICE];
	float      m_pExposureTime[MAX_DEVICE];

	//void RoteImage(ROTE_IMAGE RoteStatue);
	void preparerotate(ROTE_IMAGE Oientate,int count);
	void SetConnectView(int nCamIndex, CWnd *pWnd);
	BOOL SetSoftTriggerMode(int nCamIndex);   //��������ģʽ
	BOOL CaptureImage(int nCamIndex);		  //������Ƭ
	BOOL SoftTrigger(int nCamIndex);          //������ȡ
	BOOL SetFreeMode(int nCamIndex);		  //����ģʽ
	BOOL SetExposureTime(int nCamIndex, float nTime);
	BOOL PauseCamera(int nCamIndex, BOOL bIsWorking);


	BOOL		SetGain(int nCamIndex,int Gain);						//��������	      Lgy
	BOOL		SetContrast(int nCamIndex,int Contrast);				//���öԱȶ�      Lgy
	BOOL		SetBrightness(int nCamIndex,int Brightness);			//��������        Lgy
	BOOL		JudgeCameraType(int m_nCameraIndex);					//�����������ж����� Lgy                       
	ParaRange	GetParamRange(int nCamIndex,ParaRange para);			//���������Ų������������Χ Lgy

	int  DetectCamera();
	int  ConnectCamera();
	int  ConnectCamera(IMGSHOW imgshow[],int maxdevice);			//Lgy 8-26 ����ṹ��������������ؼ���� ��ߵȣ�DS���Ҳ��������
	BOOL CloseCamera(int nCamIndex);								//�رս����˳��Ȳ���֮ǰ�ر����  Lgy
	int  DetectCamera(MYDEVICEINFO *deviceInfo);
	int  DetectCamera(MYDEVICEINFO *deviceInfo,CapturePara *caminfo);	//��⵱ǰ���ӵ���������������Ϣ Lgy ��Ӳ���CapturePara	
	int  ConnectSelCamera(int nCamIndex, int CamType, int uCamNo);	//ֻ����ָ��������б�˫��ʱ����  Lgy
	bool OpenFixCamera(int uNo, MYDEVICEINFO deviceInfo, CapturePara para, CWnd *pWnd);

	//��Щ�������Ҫ���г�ʼ���������ҽ��г�ʼ�������Ժ��������ӵ����������Ӱ�죬��˰ѳ�ʼ���ŵ�Camera����
	void CameraApiInit();
	void CameraApiUninit();      //�ֱ���KSJ�ĳ�ʼ���ͷ���ʼ��
	//void CameraInit();
	CCamera();
	~CCamera();

protected:
	void JudgeCameraType();
};


// ��ȷ����㷨����ʱ�����(��������)
class CTimeCount
{
private:	
	double			UseTime;				// �㷨����ʱ��(��λ:��)
	LARGE_INTEGER	Time, Frequency, old;	// ����ֵ

public:	
	void Start() // ��ʱ��ʼ
	{
		QueryPerformanceFrequency( &Frequency );
		QueryPerformanceCounter  ( &old );
		UseTime = 0.0;
	}
	void End() // ��ʱ����
	{
		QueryPerformanceCounter( &Time );
		UseTime = (double) ( Time.QuadPart - old.QuadPart) / (double)Frequency.QuadPart;
		//		TRACE("Use time = %20.10f(ms)\n", UseTime );
	}
	double GetUseTime() // ����㷨����ʱ��(��λ:��)
	{		
		return UseTime;
	}
};
//------------------------------------------��ȷ����㷨����ʱ����ඨ�����

#endif