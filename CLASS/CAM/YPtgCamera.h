#pragma once	

#include "FlyCapture2.h"
#include "FlyCapture2Gui.h"
#include "camera.h"

using namespace FlyCapture2;

#pragma  comment(lib,"FlyCapture2_v100.lib")
#pragma  comment(lib,"FlyCapture2GUI_v100.lib")

struct XCamerInfo
{
	CString strCameraModel;						//�������
	CString strCameraVendor;					//�����Ӧ��
	bool	bIsColor;							//�Ƿ��ǲ�ɫ���
	__int64 nserial;							//������
	CSize	nResolution;						//����ֱ���
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
	/*						  �����Ϣ��ز�����ʼ                          */
	/************************************************************************/
	BusManager						m_busMgr;				//����������ļ�����Ƴ���Ϣʱ������Ϣ ����ȡ�����
	PGRGuid							guid;					//���Ψһ��ʾ��������ͬ���
	GigECamera						*m_pCam;				//��������Ĳ���
	FlyCapture2::Image				m_pRawImage;			//��Ųɼ�����ͼ��
	unsigned int					numCameras;				//�������
	XCamerInfoArry					m_CameraInfoArry;		//�����Ϣ����
	/************************************************************************/
	/*						   �����Ϣ��ز�������                         */
	/************************************************************************/


	BOOL   m_bStartCapture;            //����Ƿ�ʼ�ɼ�
	int    m_ImgW;
	int    m_ImgH;
	int    m_nIndex;
	int    bufferNumber;
	float  m_nGain;
	float  m_nExposure;
	double m_preTime;
	double m_curTime;
	

	int			m_uNo;
	PGRGuid		m_guid;					//���Ψһ��ʾ��������ͬ���
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
	
	int  FindAndGetCameraInfo(CameraInfo& camInfo);	//���Ҳ���ȡ�������Ϣ
	bool InitCamera(XCamerInfo XInfo);				//�����ʼ�����ر�
	void UninitCamera();
	
	bool StartCapure();								//��ʼ�������ɼ�
	void StopCapure();
	
	void ConvertConToTrig();						//�����ɼ������ɼ��л�
	void ConvertTrigToCon();
	
	bool Trigger();						//������ͼ
	bool m_bTrig;
	bool m_bTrigWin;
	//��������
	//void SetGain(int gain);
	
	void SetExposure(float exposure);	//�����ع�
	void PrintMessage(FlyCapture2::Error MError);
	int  RunSingleCamera( PGRGuid guid );		//�����
	bool CheckTriggerReady();					//��ѯ���ȴ���ֱ��������Խ��д���
	bool CheckSoftwareTriggerPresence(); 

	__int64 m_serial;					//��ǰ������к�

	void JudgeCameraIndex();
	BOOL SetFreeMode();             //����ģʽ
	BOOL SetSoftTriggerMode();      //����ģʽ
	BOOL CaptureImage();			//������Ƭ
	bool SoftTrigger();             //������ȡ
	BOOL GetDeviceInformation(CString& index,WORD& FirmwareVersion,int& m_nWidth,int& m_nHeight );
	BOOL SetPreviewPos(HWND hWnd, CRect sRect);
	BOOL PauseCamera(BOOL bIsWorking);
	BOOL CloseCamera();

	bool SetGain(float Vgain);
	BOOL SetContrast(float Contrast);            //�Աȶ� Lgy  ..PTG����� ��ʱû�ҵ��ԱȶȲ���
	BOOL SetExposureTime(float nTime);
	bool SetBrightness(float Brightness);        //���� Lgy
	float GetFrameRate();						 //Lgy
	ParaRange GetParamRange(int nCamIndex,ParaRange para);    //��ȡ���������Сֵ Lgy
	bool SetFrameRate(float fraRate);
	BOOL ConnectCamera(int nCameraSerialNo);
	bool CheckSoftwareTriggerReady();
};

void CameraCaptureCallBack(Image* pImage, const void* pCallbackData);