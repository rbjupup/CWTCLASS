#ifndef __KSJ_API_B_H__
#define __KSJ_API_B_H__

#pragma message("Include KSJApiB.h") 

#ifdef KSJAPI_EXPORTS
    #define KSJ_API __declspec(dllexport)
#elif defined KSJAPI_STATIC
	#define KSJ_API
#else
    #define KSJ_API __declspec(dllimport)
#endif

/*=================================================================
	���º���ΪKSJApi.dll����������
	�����Ӧ�ó����У���Ӧ�ð���KSJAPI.H������KSJApi.LIB��
	Ȼ����Ϳ��Ե�������ĵ���������
  -----------------------------------------------------------------*/

#ifdef __cplusplus
extern "C"{
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef OPTIONAL
#define OPTIONAL
#endif

#ifdef  UNICODE                     // r_winnt

#ifndef _TCHAR_DEFINED
typedef unsigned short TCHAR, *PTCHAR;
#endif /* !_TCHAR_DEFINED */

#else   /* UNICODE */               // r_winnt
#ifndef _TCHAR_DEFINED
typedef char TCHAR, *PTCHAR;
#define _TCHAR_DEFINED
#endif /* !_TCHAR_DEFINED */

#endif /* UNICODE */  


// ��ô������ϸ��Ϣ���������κ�ʱ�����
KSJ_API  int __stdcall KSJ_GetErrorInfo( int nErrorNo, TCHAR pszErrorInfo[256] );

// ָ����־������ļ���
KSJ_API  int __stdcall KSJ_LogSet( bool bEnable,  const TCHAR *pszFolder );

KSJ_API  int __stdcall KSJ_LogGet( bool *bEnable, TCHAR *pszFolder );

// ��ʼ��KSJApi��̬��, �˺����ڲ����ȡ�����������Ŀ���������豸���д򿪲�����
KSJ_API  int __stdcall KSJ_Init( void );

// KSJ_API  int __stdcall KSJ_InitEx( int nMaj, int nMin );

// ����ʼ��KSJApi��̬�⣬������KSJ_Init��Ӧ
KSJ_API  int __stdcall KSJ_UnInit( void );

// �õ��豸��Ŀ������Ŀ��ͨ������KSJ_Init����ʱ�õ���
KSJ_API  int __stdcall KSJ_DeviceGetCount( void );

// ���Ӽѹ�ҵ����豸���Ͷ��壺M-Mircon Sensor, R-Rolling Shutter, N-No External Trigger, N-No Frame Buffer
enum KSJ_DEVICETYPE 
{ 
	KSJ_UC130C_MRNN = 0,  // Guass2
	KSJ_UC130M_MRNN,      // Guass2
	KSJ_RESERVED0,
	KSJ_UC320C_MRNN,      // Guass2
	KSJ_UC130C_MRYN,      
	KSJ_UC130M_MRYN, 
	KSJ_RESERVED1, 
	KSJ_UC320C_MRYN, 
	KSJ_UC500C_MRNN, 
	KSJ_UC500M_MRNN, 
	KSJ_UC500C_MRYN, 
	KSJ_UC500M_MRYN, 
	KSJ_UC320C_OCR, 
	KSJ_UC900C_MRNN, 
	KSJ_UC1000C_MRNN, 
	KSJ_UC900C_MRYN, 
	KSJ_UC1000C_MRYN, 

	KSJ_UC130C_MRYY,    // Elanus2
	KSJ_UC130M_MRYY,    // Elanus2 

	KSJ_UD140C_SGNN, 
	KSJ_UD140M_SGNN, 
	KSJ_UC36C_MGNN, 
	KSJ_UC36M_MGNN,
	KSJ_UC36C_MGYN,
	KSJ_UC36M_MGYN,

	KSJ_UC900C_MRYY,    // Elanus2
	KSJ_UC1000C_MRYY,   // Elanus2
	KSJ_UC1400C_MRYY,   // Elanus2
	KSJ_UC36C_MGYY,     // Elanus2
	KSJ_UC36M_MGYY,     // Elanus2
	KSJ_UC320C_MRYY,    // Elanus2
	KSJ_UC500C_MRYY,    // Elanus2
	KSJ_UC500M_MRYY,    // Elanus2

    KSJ_MUC130C_MRYN, 
	KSJ_MUC130M_MRYN, 
	KSJ_MUC320C_MRYN,

	KSJ_MUC36C_MGYYO,    // Jelly2
	KSJ_MUC36M_MGYYO,    // Jelly2 

	KSJ_MUC130C_MRYY, 
	KSJ_MUC130M_MRYY, 
	KSJ_MUC320C_MRYY, 
	KSJ_MUC500C_MRYY, 
	KSJ_MUC500M_MRYY,
    KSJ_MUC900C_MRYY, 
	KSJ_MUC1000C_MRYY, 
	KSJ_MUC1400C_MRYY,

	KSJ_UD205C_SGYY,     // Elanus2
	KSJ_UD205M_SGYY,     // Elanus2
	KSJ_UD274C_SGYY,     // Elanus2
	KSJ_UD274M_SGYY,     // Elanus2
	KSJ_UD285C_SGYY,     // Elanus2
	KSJ_UD285M_SGYY,     // Elanus2

	KSJ_MU3C500C_MRYYO,  // Jelly3 
	KSJ_MU3C500M_MRYYO,  // Jelly3
	KSJ_MU3C1000C_MRYYO, // Jelly3
	KSJ_MU3C1400C_MRYYO, // Jelly3
	KSJ_MU3V130C_CGYYO,  // Jelly3
	KSJ_MU3V130M_CGYYO,  // Jelly3
	KSJ_MU3E130C_EGYYO,  // Jelly3
	KSJ_MU3E130M_EGYYO,  // Jelly3

	KSJ_MUC36C_MGYFO,    // Jelly1
	KSJ_MUC36M_MGYFO,    // Jelly1

	KSJ_MU3C120C_MGYYO,  // Jelly3
	KSJ_MU3C120M_MGYYO,  // Jelly3
	KSJ_MU3E200C_EGYYO,  // Jelly3
	KSJ_MU3E200M_EGYYO,  // Jelly3

	KSJ_MUC130C_MRYNO,   // Jelly1
	KSJ_MUC130M_MRYNO,   // Jelly1
	KSJ_MUC320C_MRYNO,   // Jelly1

	KSJ_U3C130C_MRYNO,   // Guass3
	KSJ_U3C130M_MRYNO,   // Guass3
	KSJ_U3C320C_MRYNO,   // Guass3
	KSJ_U3C500C_MRYNO,   // Guass3
	KSJ_U3C500M_MRYNO,   // Guass3

	KSJ_MU3C1401C_MRYYO,
	KSJ_MU3C1001C_MRYYO,
	KSJ_MUC131M_MRYN,    // WD
	KSJ_MU3C501C_MRYYO,
	KSJ_MU3C501M_MRYYO,
	KSJ_MU3C121C_MGYYO,
	KSJ_MU3C121M_MGYYO,
	KSJ_MU3E131C_EGYYO,
	KSJ_MU3E131M_EGYYO,
	KSJ_MU3E201C_EGYYO,
	KSJ_MU3E201M_EGYYO,
	KSJ_MISSING_DEVICE,	// ��ʧ������豸
};

//1. �ر�ָ���������豸��ע�����е�һ������ΪnChannle�ĺ��������Զ���ָ���������������ر�ָ���������ô�ڶ�������ǲ��ܲ�����̨����ġ�
KSJ_API  int __stdcall KSJ_DeviceClose( int nChannel );

//2. �õ��豸��Ϣ���ͺţ���ţ��̼��汾�ţ�
KSJ_API  int __stdcall KSJ_DeviceGetInformation( IN int nChannel, OUT KSJ_DEVICETYPE *pDeviceType, OUT int *pnIndex, OUT unsigned short *pwFirmwareVersion );

KSJ_API  int __stdcall KSJ_DeviceGetInformationEx( IN int nChannel, OUT KSJ_DEVICETYPE *pDeviceType, OUT int *pnIndex, OUT unsigned short *pwFirmwareVersion, OUT unsigned short *pwFpgaVersion );

//3. ���ģʽ���壨��Ϊ�г����г�㣩��
enum KSJ_ADDRESSMODE { KSJ_SKIPNONE = 0, KSJ_SKIP2, KSJ_SKIP3, KSJ_SKIP4, KSJ_SKIP8 };

//4. ��ȡ�ɼ��豸��֧�ֵ�Ĭ���ӳ��������г����÷�Χ��
KSJ_API  int __stdcall KSJ_CaptureGetDefaultFieldOfView( int nChannel, int *pnColStart, int *pnRowStart, int *pnColumnSize, int *pnRowSize, KSJ_ADDRESSMODE *pColumnAddressMode, KSJ_ADDRESSMODE *pRowAddressMode );

//5. ���òɼ��ӳ���С
KSJ_API  int __stdcall KSJ_CaptureSetFieldOfView( int nChannel, int nColStart, int nRowStart, int nColSize, int nRowSize, KSJ_ADDRESSMODE ColAddressMode, KSJ_ADDRESSMODE RowAddressMode );

//6. ��ȡ�ɼ��ӳ���ʵ�ʴ�С
KSJ_API  int __stdcall KSJ_CaptureGetFieldOfView( int nChannel, int *pnColStart, int *pnRowStart, int *pnColumnSize, int *pnRowSize, KSJ_ADDRESSMODE *pColumnAddressMode, KSJ_ADDRESSMODE *pRowAddressMode );

//7. ���òɼ��ӳ���ƴ���ӳ�����
KSJ_API  int __stdcall KSJ_CaptureSetFieldOfViewEx( int nChannel, int nColStart, int nRowStart, int nColSize, int nRowSize, KSJ_ADDRESSMODE ColAddressMode, KSJ_ADDRESSMODE RowAddressMode, unsigned short wMultiFrameNum );

KSJ_API  int __stdcall KSJ_CaptureGetFieldOfViewEx( int nChannel, int *pnColStart, int *pnRowStart, int *pnColumnSize, int *pnRowSize, KSJ_ADDRESSMODE *pColumnAddressMode, KSJ_ADDRESSMODE *pRowAddressMode, unsigned short *pwMultiFrameNum );

//8. ���ö�ȡ�ĳ�ʱʱ�䣨���룩
KSJ_API  int __stdcall KSJ_CaptureSetTimeOut( int nChannel, unsigned long dwTimeOut );

KSJ_API  int __stdcall KSJ_CaptureGetTimeOut( int nChannel, unsigned long *pdwTimeOut );

//9. ���ö�ȡ����ʱ�Ƿ�������»ָ�����
KSJ_API  int __stdcall KSJ_CaptureSetRecover( int nChannel, bool bRecover );

KSJ_API  int __stdcall KSJ_CaptureGetRecover( int nChannel, bool *pbRecover );

//10. ���ö�ȡ�ĳ�ʱʱ�䣨���룩�Ͷ�ȡ����ʱ�Ƿ�������»ָ�����
KSJ_API  int __stdcall KSJ_CaptureSetTimeOutEx( int nChannel, unsigned long dwTimeOut, bool bRecover );

KSJ_API  int __stdcall KSJ_CaptureGetTimeOutEx( int nChannel, unsigned long *pdwTimeOut, bool *pbRecover );

//11.�õ��ɼ�ͼ��Ŀ�Ⱥ͸߶ȣ���λ�����أ�
KSJ_API  int __stdcall KSJ_CaptureGetSize( int nChannel, int *pnWidth, int *pnHeight );
//12. �õ��ɼ�ͼ��Ŀ�Ⱥ͸߶�,����λ������λ�����أ�
KSJ_API  int __stdcall KSJ_CaptureGetSizeEx( int nChannel, int *pnWidth, int *pnHeight, int *pnBitCount );
//13.���ڼ�����16bit�Ķ�ȡ����ģʽ,��ǰ�û�ͨ���жϷ��ص�Width, Height, BitCount���ж�ͼ���ֽ�������������������,�������˴˺���
// �����ڵ���KSJ_CaptureXXXXXXX����ǰ������ڴ���Ը���nBitsPerSample��ֵ������, nBitsPerSample=8 or 16
KSJ_API  int __stdcall KSJ_CaptureGetSizeExEx( int nChannel, int *pnWidth, int *pnHeight, int *pnBitCount, int *nBitsPerSample );

//14. �ɼ�һ֡ԭʼ����ͼ������
// ���������16λ�����ݶ�ȡģʽ,��ô�ɼ�������Ҳ��16λ��
KSJ_API  int __stdcall KSJ_CaptureRawData     ( int nChannel, unsigned char *pRawData );
//15. �ɼ�һ֡8�Ҷ�ͼ���24��32λ��ɫͼ�����ݣ���KSJ_BayerSetMode��KSJ_PreviewSetMode��أ�
// ���������16λ�����ݶ�ȡģʽ,��ô�ɼ�������Ҳ��16λ��
KSJ_API  int __stdcall KSJ_CaptureRgbData     ( int nChannel, unsigned char *pRgbData );

KSJ_API  int __stdcall KSJ_CaptureRgbDataToClipboard( int nChannel );

//16. ���������16λ�����ݶ�ȡģʽ,��ô�ɼ�������Ҳ��16λ��
KSJ_API  int __stdcall KSJ_CaptureRgbDataEx   ( int nChannel, unsigned char *pRgbData, int *pnWidth, int *pnHeight, int *pnBitCount );

// �������
enum KSJ_PARAM { 
	KSJ_EXPOSURE = 0,       // �ع�ʱ�䣨��λ�����룩
	KSJ_RED, 
	KSJ_GREEN, 
	KSJ_BLUE, 
	KSJ_GAMMA, 
	KSJ_PREVIEW_COLUMNSTART, 
	KSJ_PREVIEW_ROWSTART, 
	KSJ_CAPTURE_COLUMNSTART, 
	KSJ_CAPTURE_ROWSTART, 
	KSJ_HORIZONTALBLANK, 
	KSJ_VERTICALBLANK, 
	KSJ_FLIP, 
	KSJ_BIN, 
	KSJ_MIRROR, 
	KSJ_CONTRAST, 
	KSJ_BRIGHTNESS, 
	KSJ_VGAGAIN, 
	KSJ_CLAMPLEVEL, 
	KSJ_CDSGAIN,
	KSJ_RED_SHIFT,
	KSJ_GREEN_SHIFT,
	KSJ_BLUE_SHIFT,
    KSJ_COMPANDING,
	KSJ_EXPOSURE_LINES,    // 23
	KSJ_SATURATION,
	KSJ_TRIGGERDELAY,
	KSJ_STROBEDELAY,
	KSJ_TRIGGER_MODE,
	KSJ_TRIGGER_METHOD, 
	KSJ_BLACKLEVEL,
	KSJ_BLACKLEVEL_THRESHOLD_AUTO,
	KSJ_BLACKLEVEL_THRESHOLD_LO,
	KSJ_BLACKLEVEL_THRESHOLD_HI
};

//17. ��ò��������÷�Χ
KSJ_API  int __stdcall KSJ_GetParamRange( IN int nChannel, IN KSJ_PARAM Param, OUT int *pnMinValue, OUT int *pnMaxValue );
//18. ���ò���
KSJ_API  int __stdcall KSJ_SetParam     ( IN int nChannel, IN KSJ_PARAM Param, IN  int nValue );
//19. ��ȡ������ǰֵ
KSJ_API  int __stdcall KSJ_GetParam     ( IN int nChannel, IN KSJ_PARAM Param, OUT int *pnValue );

//20. ����Gammaֵ����Χ -9 - +9
KSJ_API  int __stdcall KSJ_GammaSetValue( int nChannel, int nValue );
//21. �򿪻�ر�GammaУ������Ӱ��Ԥ����Ӱ��ɼ�
KSJ_API  int __stdcall KSJ_GammaOn( int nChannel, bool bOn );

// ö�����ͱ�Ү��ģʽ
enum KSJ_BAYERMODE { KSJ_BGGR_BGR24 = 0, KSJ_GRBG_BGR24, KSJ_RGGB_BGR24, KSJ_GBRG_BGR24, KSJ_BGGR_BGR24_FLIP, KSJ_GRBG_BGR24_FLIP,  KSJ_RGGB_BGR24_FLIP, KSJ_GBRG_BGR24_FLIP, 
                     KSJ_BGGR_BGR32,     KSJ_GRBG_BGR32, KSJ_RGGB_BGR32, KSJ_GBRG_BGR32, KSJ_BGGR_BGR32_FLIP, KSJ_GRBG_BGR32_FLIP,  KSJ_RGGB_BGR32_FLIP, KSJ_GBRG_BGR32_FLIP,
                     KSJ_BGGR_GRAY8,     KSJ_GRBG_GRAY8, KSJ_RGGB_GRAY8, KSJ_GBRG_GRAY8, KSJ_BGGR_GRAY8_FLIP, KSJ_GRBG_GRAY8_FLIP,  KSJ_RGGB_GRAY8_FLIP, KSJ_GBRG_GRAY8_FLIP };

//22. �õ���ǰ�����Ĭ��Bayerģʽ
KSJ_API   int __stdcall KSJ_BayerGetDefaultMode( int nChannel, KSJ_BAYERMODE *pBayerMode );
//23. ����Bayerģʽ��ͬʱӰ��ɼ���Ԥ�������������������Ҫ���ã������û�������ô˹��ܡ�
KSJ_API   int __stdcall KSJ_BayerSetMode( int nChannel, KSJ_BAYERMODE BayerMode );
//24. ��õ�ǰBayerģʽ
KSJ_API   int __stdcall KSJ_BayerGetMode( int nChannel, KSJ_BAYERMODE *pBayerMode );


enum KSJ_FILTERMODE { KSJ_NEARESTNEIGHBOR, KSJ_BILINEAR, KSJ_SMOOTHHUE, KSJ_EDGESENSING, KSJ_LAPLACIAN, KSJ_FASTBILINEAR };

//25. ����Bayer Filterģʽ��ͬʱӰ��ɼ���Ԥ�������������������Ҫ���ã������û�������ô˹��ܡ�
KSJ_API   int __stdcall KSJ_FilterSetMode( int nChannel, KSJ_FILTERMODE FilterMode );
//26. ��õ�ǰBayerģʽ
KSJ_API   int __stdcall KSJ_FilterGetMode( int nChannel, KSJ_FILTERMODE *pFilterMode );

// 27.�����Զ��ع������������������Ԥ��ͼ������Ͻ�����λ��
KSJ_API  int __stdcall KSJ_AESetRegion( int nChannel, int nX, int nY,  int nW, int nH );
// 28.�Զ��ع�ص�����
typedef void (__stdcall *KSJ_AECALLBACK )( bool bSuccess, int nResult,  void *lpContext );
//29. �����Զ��ع����������Ļص����������Զ��ع����ʱ��KSJ���������Զ�����AECallback�û�ָ���Ļص�����
KSJ_API  int __stdcall KSJ_AESetCallback( int nChannel, KSJ_AECALLBACK pfAECallback, void *lpContext );
//30. ��ʼ����ֹ�Զ��ع����
KSJ_API  int __stdcall KSJ_AEStart( int nChannel, bool bStart, int nMaxCount, int nTarget );

//31. �����Զ���ƽ������
KSJ_API  int __stdcall KSJ_AWBSetRegion( int nChannel, int nX, int nY,  int nW, int nH );
//32. �Զ���ƽ��ص�����
typedef void (__stdcall *KSJ_AWBCALLBACK )( bool bSuccess, int nValueR, int nValueG, int nValueB,  void *lpContext );
//33. �����Զ���ƽ�⣨����Ӳ��������������Ļص����������Զ��ع����ʱ��KSJ���������Զ�����AECallback�û�ָ���Ļص�����
KSJ_API  int __stdcall KSJ_AWBSetCallback( int nChannel, KSJ_AWBCALLBACK fpAWBCallback, void *lpContext );
//34. ��ʼ����ֹ�Զ���ƽ�����
KSJ_API  int __stdcall KSJ_AWBStart( int nChannel, bool bStart, int nMaxCount, int nRTarget, int nGTarget, int nBTarget );

//35. ���þ۽���������
KSJ_API  int __stdcall KSJ_AFSetRegion( int nChannel, int nX, int nY,  int nW, int nH );
//36. �۽������ص�����, nValueΪ���ص�����ֵ
typedef void (__stdcall *KSJ_AFCALLBACK )( int nValue,  void *lpContext );
//37. ���þ۽������ص�
KSJ_API  int __stdcall KSJ_AFSetCallback( int nChannel, KSJ_AFCALLBACK fpAFCallback, void *lpContext );
//38. ��ʼ����ֹ�۽�����
KSJ_API  int __stdcall KSJ_AFStart( int nChannel, bool bStart );

//39. ���öԱȶȣ�����ֵ��Χ��-128~128��
KSJ_API  int __stdcall KSJ_ProcessContrastSet( int nChannel, int nContrast );

KSJ_API  int __stdcall KSJ_ProcessContrastGet( int nChannel, int *pnContrast );

KSJ_API  int __stdcall KSJ_ProcessContrastGetRange( int nChannel, int *pnMinContrast, int *pnMaxContrast );

//40. �������ȣ�����ֵ��Χ��-128~128��
KSJ_API  int __stdcall KSJ_ProcessBrightnessSet( int nChannel, int nBrightness );

KSJ_API  int __stdcall KSJ_ProcessBrightnessGet( int nChannel, int *pnBrightness );

KSJ_API  int __stdcall KSJ_ProcessBrightnessGetRange( int nChannel, int *pnMinBrightness, int *pnMaxBrightness );

KSJ_API  int __stdcall KSJ_ProcessSaturationSet( int nChannel, int nSaturation );

KSJ_API  int __stdcall KSJ_ProcessSaturationGet( int nChannel, int *pnStaturation );

KSJ_API  int __stdcall KSJ_ProcessSaturationGetRange( int nChannel, int *pnMinSaturation, int *pnMaxSaturation );


KSJ_API  int __stdcall KSJ_ExposureTimeSet( int nChannel, float fExpTimeMs );
KSJ_API  int __stdcall KSJ_ExposureTimeGet( int nChannel, float *pfExpTimeMs );

//41. ���ô˺���ʱ���뿪��Ԥ������Ƶ�ļ�����Ԥ���ӳ�
KSJ_API  int __stdcall KSJ_RecordStart  ( int nChannel, bool bStart, float fRecordRate, const TCHAR *pFileName );

//42. ���ô˺���ʱ���뿪��Ԥ������Ƶ�ļ�����Ԥ���ӳ�
KSJ_API  int __stdcall KSJ_RecordStartEx( int nChannel, bool bStart, float fRecordRate, const TCHAR *pFileName, bool bShowCompossorSelection );

//43. ���ô˺���ʱ���Թر�Ԥ������Ƶ�ļ������û����õĿ�ȸ߶ȣ��ļ�����Ƶ������KSJ_RecordAddOneFrame��ӣ�ע���ȣ��߶ȣ�����λ���������
KSJ_API  int __stdcall KSJ_RecordStartExEx( int nChannel, bool bStart, float fRecordRate, int nWidth, int nHeight, int nBitCount, const TCHAR *pFileName, bool bShowCompossorSelection );

KSJ_API  int __stdcall KSJ_RecordAddOneFrame( int nChannel, unsigned char *pFrameData, int nFrameNum, int nWidth, int nHeight, int nBitcount );

KSJ_API  int __stdcall KSJ_RecordStatusGet( int nChannel, bool *bStart );


//44. ��pData(���ΪnWidth, �߶�ΪnHeight, ����λ��ΪnBitCount)��ͼ����������Ϊ���ΪnStretchWidh, �߶�ΪnStretchHeight�����ݲ���䵽�û������pStretchData������,����λ������
KSJ_API  int __stdcall KSJ_HelperStretchBmp( unsigned char *pData, int nWidth, int nHeight, int nBitCount, unsigned char *pStretchData, int nStretchWidth, int nStretchHeight );

//45. ����ͼ��ı�����ȵõ�BMPͼ����ļ�ͷ,��Ϣͷ,����ɫ���ܵ��ֽ���Ŀ
KSJ_API  int __stdcall KSJ_HelperGetBmpFileHeaderSize( int nBitCount, int *pnTotalBytes );

//46. �õ�BMPͼ����ļ�ͷ����Ϣͷ
KSJ_API  int __stdcall KSJ_HelperGetBmpFileHeader( int nWidth, int nHeight, int nBitCount, void *pHeader );

//47. ����ΪBmp�ļ�
KSJ_API  int __stdcall KSJ_HelperSaveToBmp( unsigned char *pData, int nWidth, int nHeight, int nBitCount, const TCHAR *pszFileName );
//48. ����ΪJpg�ļ�
KSJ_API  int __stdcall KSJ_HelperSaveToJpg( unsigned char *pData, int nWidth, int nHeight, int nBitCount, int nQulity, const TCHAR *pszFileName );
//49. ����Ϊtiff�ļ�,���Ա���16bit������8bit����������
// nBitPerSample = 8 ��16
// nSamplesPerPixel = 1��3��4(�ֱ��ӦBitCount=8,24,32),�ο�KSJ_CaptureGetSizeExEx����
KSJ_API  int __stdcall KSJ_HelperSaveToTiff( unsigned char *pData, int nWidth, int nHeight, int nBitPerSample, int nSamplesPerPixel, const TCHAR *pszFileName );

///////////////////////////////////////////////Color Correction////////////////////////////////////////////////////////////////
typedef void (__stdcall *KSJ_CCCALLBACK )( bool bSuccess, int nRShift, int nGShift, int nBShift,  void *lpContext );

//50. ���º���Ϊ�����ɫУ��
KSJ_API  int __stdcall KSJ_ColorCorrectSetCallback( int nChannel, KSJ_CCCALLBACK fpCCCallback, void *lpContext );

enum KSJ_COLORCORRECT { KSJ_CC_NONE, KSJ_CC_SHIFTRGB, KSJ_CC_EQRGB, KSJ_CC_EQALL, KSJ_CC_WB };
KSJ_API  int __stdcall KSJ_ColorCorrectSet  ( int nChannel, KSJ_COLORCORRECT ColorCorrect, int nRTarget, int nGTarget, int nBTarget );
KSJ_API  int __stdcall KSJ_ColorCorrectGet  ( int nChannel, KSJ_COLORCORRECT *pColorCorrect );
KSJ_API  int __stdcall KSJ_ColorCorrectGetEx( int nChannel, KSJ_COLORCORRECT *pColorCorrect, int *pnRTarget, int *pnGTarget, int *pnBTarget );

KSJ_API  int __stdcall KSJ_ColorCorrectTableSave( int nChannel, const TCHAR *pszFileName );
KSJ_API  int __stdcall KSJ_ColorCorrectTableLoad( int nChannel, const TCHAR *pszFileName );
KSJ_API  int __stdcall KSJ_IsColorCorrectTableLoad( int nChannel, bool *bLoad );

//51. ��ƽ���������ɫУ������
enum KSJ_COLORCORRECTION { KSJCC_NONE = 0, KSJCC_WARMLIGHT, KSJCC_COOLLIGHT, KSJCC_SUNLIGHT, KSJCC_OV, KSJCC_KODAK };
KSJ_API  int __stdcall KSJ_ColorCorrectionSet( int nChannel, KSJ_COLORCORRECTION  ColorCorrect  );
KSJ_API  int __stdcall KSJ_ColorCorrectionGet( int nChannel, KSJ_COLORCORRECTION *pColorCorrect );


#ifdef __cplusplus
}
#endif

#endif


