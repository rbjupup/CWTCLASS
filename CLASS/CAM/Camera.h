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

struct IMGSHOW   //DS相机初始化需要传入显示控件句柄和宽高
{
	HWND ctlhwnd;  //控件句柄
	int  ctlwidth; //控件宽
	int  ctlheight;//控件高
};

struct MYDEVICEINFO
{
	CString             Str_index;       //序列号   Lgy 8-24  很多序列号不是INT型 所以在这里添加Cstring 来操作
	int 				nIndex;          //序列号   Lgy 8-24
	int                 m_nCameraType;   //相机品牌
	WORD				wFirmwareVersion;//固件版本 Lgy 8-24
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

struct ParaRange      //保存获取到的最大参数最小参数结构体
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

    static int   ExIndex;			 //Lgy KSJ相机之间的下标增长变量,因为根据配置文件（多种相机）会有个下标。每得到一个KSJ相机 加1
	int    ExCamIndex[MAX_DEVICE];	 /*Lgy 以读入相机数量从0开始做数组下标 存放相同相机之间的默认nChannel,比如KSJ的相机在配置中是相机3，
	                          但是假设在连接的KSJ相机里默认nChannel为0，则ExCamIndex[2] = 0;*/
	int	  ExDsIndex;				// 每连接一个DS 相机 ExDsIndex 加1，对应DS相机初始化之后生成的iCameraID,并存放于ExDsCamIndex[]
	int   ExDsCamIndex[MAX_DEVICE];  //用于DS相机，数组以读入相机数量从0开始做下标

	int   m_uNo;
	int   m_nCameraIndex;  //序列号中间变量
	int	  m_nCameraType;
	int   m_nGain;      //Lgy
	int   m_TempIndex;  //临时保存下标 用作数组下标 ExCamIndex[],ExDsCamIndex[] 等等Lgy 
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
	bool ConnectCamera(IMGSHOW imgshow[],int maxdevice,int index);  // Lgy 8-26 1为结构体数组参数包含控件句柄宽高等，index等于Ycapture[i]里的i下标，
																	// 即相机在配置中的位置,maxdevice 为数组大小

	BOOL		CloseCamera();										    //关闭界面退出等操作之前关闭相机  Lgy	
	BOOL		SetGain(int Gain);										//设置增益	   Lgy
	BOOL		SetContrast(int Contrast);							    //设置对比度   Lgy
	BOOL		SetBrightness(int Brightness);							//设置亮度     Lgy
	BOOL		JudgeCameraType(int m_nCameraIndex);					//根据相机序号 判断Type Lgy
	ParaRange	GetParamRange(int nCamIndex,ParaRange para);		
	
//	void RoteImage(ROTE_IMAGE RoteStatue);						//反转图像
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
	BOOL SetSoftTriggerMode(int nCamIndex);   //设置软触发模式
	BOOL CaptureImage(int nCamIndex);		  //捕获照片
	BOOL SoftTrigger(int nCamIndex);          //触发获取
	BOOL SetFreeMode(int nCamIndex);		  //连续模式
	BOOL SetExposureTime(int nCamIndex, float nTime);
	BOOL PauseCamera(int nCamIndex, BOOL bIsWorking);


	BOOL		SetGain(int nCamIndex,int Gain);						//设置增益	      Lgy
	BOOL		SetContrast(int nCamIndex,int Contrast);				//设置对比度      Lgy
	BOOL		SetBrightness(int nCamIndex,int Brightness);			//设置亮度        Lgy
	BOOL		JudgeCameraType(int m_nCameraIndex);					//根据相机序号判断类型 Lgy                       
	ParaRange	GetParamRange(int nCamIndex,ParaRange para);			//根据相机序号查找相机参数范围 Lgy

	int  DetectCamera();
	int  ConnectCamera();
	int  ConnectCamera(IMGSHOW imgshow[],int maxdevice);			//Lgy 8-26 传入结构体数组参数包含控件句柄 宽高等，DS相机也可以条用
	BOOL CloseCamera(int nCamIndex);								//关闭界面退出等操作之前关闭相机  Lgy
	int  DetectCamera(MYDEVICEINFO *deviceInfo);
	int  DetectCamera(MYDEVICEINFO *deviceInfo,CapturePara *caminfo);	//检测当前连接的相机数量及相机信息 Lgy 添加参数CapturePara	
	int  ConnectSelCamera(int nCamIndex, int CamType, int uCamNo);	//只连接指定相机，列表双击时连接  Lgy
	bool OpenFixCamera(int uNo, MYDEVICEINFO deviceInfo, CapturePara para, CWnd *pWnd);

	//有些相机库需要进行初始化操作，且进行初始化操作以后，所有连接的相机都会受影响，因此把初始化放到Camera类里
	void CameraApiInit();
	void CameraApiUninit();      //分别是KSJ的初始化和反初始化
	//void CameraInit();
	CCamera();
	~CCamera();

protected:
	void JudgeCameraType();
};


// 精确获得算法处理时间的类(毫秒量级)
class CTimeCount
{
private:	
	double			UseTime;				// 算法处理时间(单位:秒)
	LARGE_INTEGER	Time, Frequency, old;	// 计数值

public:	
	void Start() // 计时开始
	{
		QueryPerformanceFrequency( &Frequency );
		QueryPerformanceCounter  ( &old );
		UseTime = 0.0;
	}
	void End() // 计时结束
	{
		QueryPerformanceCounter( &Time );
		UseTime = (double) ( Time.QuadPart - old.QuadPart) / (double)Frequency.QuadPart;
		//		TRACE("Use time = %20.10f(ms)\n", UseTime );
	}
	double GetUseTime() // 获得算法处理时间(单位:秒)
	{		
		return UseTime;
	}
};
//------------------------------------------精确获得算法处理时间的类定义结束

#endif