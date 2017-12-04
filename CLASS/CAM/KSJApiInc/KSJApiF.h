#ifndef __KSJ_API_F_H__
#define __KSJ_API_F_H__

#pragma message("Include KSJApiF.h") 

#ifdef KSJAPI_EXPORTS
    #define KSJ_API __declspec(dllexport)
#elif defined KSJAPI_STATIC
	#define KSJ_API
#else
    #define KSJ_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"{
#endif

// ���֡�����
KSJ_API  int __stdcall KSJ_EmptyFrameBuffer ( int nChannel );

// ����ģʽ����
enum KSJ_TRIGGERMODE { KSJ_TRIGGER_INTERNAL, KSJ_TRIGGER_EXTERNAL, KSJ_TRIGGER_SOFTWARE, KSJ_TRIGGER_FIXFRAMERATE };
KSJ_API  int __stdcall KSJ_TriggerModeSet ( int nChannel, KSJ_TRIGGERMODE TriggerMode   );
KSJ_API  int __stdcall KSJ_TriggerModeGet ( int nChannel, KSJ_TRIGGERMODE *pTriggerMode );

// ����У������ֵ�͸���ֵ���ã�Ӳ����֧�ִ����ã����������ʱ��Ч��
KSJ_API  int __stdcall KSJ_BadPixelCorrectionSetThreshold( int nChannel, unsigned char btLow,   unsigned char btHigh   );
KSJ_API  int __stdcall KSJ_BadPixelCorrectionGetThreshold( int nChannel, unsigned char *pbtLow, unsigned char *pbtHigh );

enum KSJ_THRESHOLD { KSJ_THRESHOLD_LOW, KSJ_THRESHOLD_HIGH };
// ����У�����ü���ֵ���ã�����ֵ����˸���Ļ���
KSJ_API  int __stdcall KSJ_BadPixelCorrectionSet( int nChannel, bool bEnable,   KSJ_THRESHOLD Threshold );
KSJ_API  int __stdcall KSJ_BadPixelCorrectionGet( int nChannel, bool *pbEnable, KSJ_THRESHOLD *pThreshold);

// ������ģʽ���ã�ʹ�ý�ȡ8λ��ʽ��
enum KSJ_SENSITIVITYMODE { KSJ_LOW = 0, KSJ_MID, KSJ_HIGH, KSJ_HIGHER, KSJ_HIGHEST };
KSJ_API  int __stdcall KSJ_SensitivitySetMode( int nChannel, KSJ_SENSITIVITYMODE SensitivityMode   );
KSJ_API  int __stdcall KSJ_SensitivityGetMode( int nChannel, KSJ_SENSITIVITYMODE *pSensitivityMode );

// �ⴥ��ģʽʱ���ⴥ���źŵĴ�����ʽ����
enum KSJ_TRIGGERMETHOD { KSJ_TRIGGER_FALLINGEDGE, KSJ_TRIGGER_RISINGEDGE, KSJ_TRIGGER_HIGHLEVEL, KSJ_TRIGGER_LOWLEVEL };
KSJ_API  int __stdcall KSJ_TriggerMethodSet ( int nChannel, KSJ_TRIGGERMETHOD  TriggerMethod  );
KSJ_API  int __stdcall KSJ_TriggerMethodGet ( int nChannel, KSJ_TRIGGERMETHOD *pTriggerMethod  );

// �ⴥ��ģʽʱ�����ô����ź���Ч���ɼ�����ʱʱ��
KSJ_API  int __stdcall KSJ_TriggerDelaySet( int nChannel, unsigned short wDelay   );
KSJ_API  int __stdcall KSJ_TriggerDelayGet( int nChannel, unsigned short *pwDelay );
KSJ_API  int __stdcall KSJ_TriggerDelayGetRange( int nChannel, unsigned short *wMin, unsigned short *wMax );

// ������ź������ʵ������������ʱ����
KSJ_API  int __stdcall KSJ_StrobeDelaySet( int nChannel, unsigned short wDelay   );
KSJ_API  int __stdcall KSJ_StrobeDelayGet( int nChannel, unsigned short *pwDelay );
KSJ_API  int __stdcall KSJ_StrobeDelayGetRange( int nChannel, unsigned short *wMin, unsigned short *wMax );

// �����֡����ٲɼ�ԭʼͼ��
KSJ_API  int __stdcall KSJ_CaptureRawDataAfterEmptyFrameBuffer     ( int nChannel, unsigned char *pRawData );
// �����֡����ٲɼ���ɫͼ��
KSJ_API  int __stdcall KSJ_CaptureRgbDataAfterEmptyFrameBuffer     ( int nChannel, unsigned char *pRgbData );
// �����֡����ٲɼ���ɫͼ��
KSJ_API  int __stdcall KSJ_CaptureRgbDataExAfterEmptyFrameBuffer   ( int nChannel, unsigned char *pRgbData, int *pnWidth, int *pnHeight, int *pnBitCount );

// ����ͼ�񴫸����Ĺ�����ʽ���ݲ�֧�֣�
enum KSJ_SENSORMODE { KSJ_SM_TRIGGER_MODE, KSJ_SM_FREERUN_MODE };
KSJ_API  int __stdcall KSJ_SensorModeSet ( int nChannel, KSJ_SENSORMODE SensorMode  );
KSJ_API  int __stdcall KSJ_SensorModeGet ( int nChannel, KSJ_SENSORMODE *SensorMode  );


#ifdef __cplusplus
}
#endif

#endif