#pragma once	

#include "FlyCapture2.h"
#include "FlyCapture2Gui.h"
#include "camera.h"

using namespace FlyCapture2;

#pragma  comment(lib,"FlyCapture2_v100.lib")
#pragma  comment(lib,"FlyCapture2GUI_v100.lib")

struct XCamerInfo
{
	CString strCameraModel;						//相机类型
	CString strCameraVendor;					//相机供应商
	bool	bIsColor;							//是否是彩色相机
	__int64 nserial;							//相机编号
	CSize	nResolution;						//相机分辨率
};

typedef CArray<XCamerInfo,XCamerInfo>XCamerInfoArry;

class YPtgCamera
{
public:

	YPtgCamera(void);
	~YPtgCamera(void);

	//FlyCapture2::Camera m_FCam;
	FlyCapture2::Error error;
	/************************************************************************/
	/*						  相机信息相关参数开始                          */
	/************************************************************************/
	BusManager						m_busMgr;				//相机或驱动的加入或移除信息时反馈信息 （读取相机）
	PGRGuid							guid;					//相机唯一标示符，区别不同相机
	GigECamera						*m_pCam;				//用于相机的操作
	FlyCapture2::Image				m_pRawImage;			//存放采集到的图像
	unsigned int					numCameras;				//相机个数
	XCamerInfoArry					m_CameraInfoArry;		//相机信息数组
	/************************************************************************/
	/*						   相机信息相关参数结束                         */
	/************************************************************************/


	BOOL   m_bStartCapture;            //相机是否开始采集
	int    m_ImgW;
	int    m_ImgH;
	int    m_nIndex;
	int    bufferNumber;
	float  m_nGain;
	float  m_nExposure;
	double m_preTime;
	double m_curTime;
	

	int			m_uNo;
	PGRGuid		m_guid;					//相机唯一标示符，区别不同相机
	BOOL		m_pIsPaused;
	BOOL		m_pIsTriggerMode;
	int			m_pCapturedImageNum;
	BOOL		m_bIsConnected;
	CWnd		*m_pConnectView;
	YCapture	*m_ptrCap;
	bool		m_bImageReady;
	float		m_pExposureTime;
	CMyImage	m_pImage;
	double		m_pShowScale;
	HANDLE      m_hWaitTimeEvent;
	MYDEVICEINFO  m_pDeviceInfo;
	CapturePara m_pCamInfo;      // Lgy
	
	int  FindAndGetCameraInfo(CameraInfo& camInfo);	//查找并获取相机的信息
	bool InitCamera(XCamerInfo XInfo);				//像机初始化、关闭
	void UninitCamera();
	
	bool StartCapure();								//开始、结束采集
	void StopCapure();
	
	void ConvertConToTrig();						//连续采集触发采集切换
	void ConvertTrigToCon();
	
	bool Trigger();						//触发采图
	bool m_bTrig;
	bool m_bTrigWin;
	//调节增益
	//void SetGain(int gain);
	
	void SetExposure(float exposure);	//调节曝光
	void PrintMessage(FlyCapture2::Error MError);
	int  RunSingleCamera( PGRGuid guid );		//打开相机
	bool CheckTriggerReady();					//查询并等待，直到相机可以进行触发
	bool CheckSoftwareTriggerPresence(); 

	__int64 m_serial;					//当前相机序列号

	void JudgeCameraIndex();
	BOOL SetFreeMode();             //连续模式
	BOOL SetSoftTriggerMode();      //软触发模式
	BOOL CaptureImage();			//捕获照片
	bool SoftTrigger();             //软触发获取
	BOOL GetDeviceInformation(CString& index,WORD& FirmwareVersion,int& m_nWidth,int& m_nHeight );
	BOOL SetPreviewPos(HWND hWnd, CRect sRect);
	BOOL PauseCamera(BOOL bIsWorking);
	BOOL CloseCamera();

	bool SetGain(float Vgain);
	BOOL SetContrast(float Contrast);            //对比度 Lgy  ..PTG的相机 暂时没找到对比度参数
	BOOL SetExposureTime(float nTime);
	bool SetBrightness(float Brightness);        //亮度 Lgy
	float GetFrameRate();						 //Lgy
	ParaRange GetParamRange(int nCamIndex,ParaRange para);    //获取参数最大最小值 Lgy
	bool SetFrameRate(float fraRate);
	BOOL ConnectCamera(int nCameraSerialNo);
	bool CheckSoftwareTriggerReady();
};

void CameraCaptureCallBack(Image* pImage, const void* pCallbackData);