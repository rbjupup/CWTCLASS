#ifndef __KSJ_API_C_H__
#define __KSJ_API_C_H__

#pragma message("Include KSJApiC.h") 

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

// ����Ԥ���ӳ�
KSJ_API  int __stdcall KSJ_PreviewSetFieldOfView( int nChannel, int nColStart, int nRowStart, int nColSize, int nRowSize, KSJ_ADDRESSMODE ColAddressMode, KSJ_ADDRESSMODE RowAddressMode );

// ��ȡԤ���ӳ�
KSJ_API  int __stdcall KSJ_PreviewGetFieldOfView( int nChannel, int *pnColStart, int *pnRowStart, int *pnColumnSize, int *pnRowSize, KSJ_ADDRESSMODE *pColumnAddressMode, KSJ_ADDRESSMODE *pRowAddressMode );

// Get Default Field Of View for Preview
KSJ_API  int __stdcall KSJ_PreviewGetDefaultFieldOfView( int nChannel, int *pnColStart, int *pnRowStart, int *pnColumnSize, int *pnRowSize, KSJ_ADDRESSMODE *pColumnAddressMode, KSJ_ADDRESSMODE *pRowAddressMode );

KSJ_API  int __stdcall KSJ_PreviewSetFieldOfViewEx( int nChannel, int nColStart, int nRowStart, int nColSize, int nRowSize, KSJ_ADDRESSMODE ColAddressMode, KSJ_ADDRESSMODE RowAddressMode, unsigned short wMultiFrameNum );

KSJ_API  int __stdcall KSJ_PreviewGetFieldOfViewEx( int nChannel, int *pnColStart, int *pnRowStart, int *pnColumnSize, int *pnRowSize, KSJ_ADDRESSMODE *pColumnAddressMode, KSJ_ADDRESSMODE *pRowAddressMode, unsigned short *pwMultiFrameNum );

// ��ȡ���û����õ��ӳ�ģʽ�£�Ԥ��ͼ��Ŀ�Ⱥ͸߶ȣ����أ�
KSJ_API  int __stdcall KSJ_PreviewGetSize       ( int nChannel, int *pnWidth, int *pnHeight );

KSJ_API  int __stdcall KSJ_PreviewGetSizeEx     ( int nChannel, int *pnWidth, int *pnHeight, int *pnBitCount );

// ����Ԥ��ͼ�����ʾλ��
KSJ_API  int __stdcall KSJ_PreviewSetPos        ( int nChannel, HWND hWnd, int x, int y, int nWidth, int nHeight );
// ��ȡԤ��ͼ�����ʾλ��
KSJ_API  int __stdcall KSJ_PreviewGetPos        ( int nChannel, int *px, int *py, int *pnWidth, int *pnHeight );
// ����Ԥ��ģʽ
enum KSJ_PREVIEWMODE { PM_RAWDATA, PM_RGBDATA };
KSJ_API  int __stdcall KSJ_PreviewSetMode       ( int nChannel, KSJ_PREVIEWMODE PreviewMode  );
// ��ȡԤ��ģʽ
KSJ_API  int __stdcall KSJ_PreviewGetMode       ( int nChannel, KSJ_PREVIEWMODE *pPreviewMode  );

KSJ_API  int __stdcall KSJ_PreviewGetDefaultMode( int nChannel, KSJ_PREVIEWMODE *pPreviewMode  );

// ������ֹͣԤ��
KSJ_API  int __stdcall KSJ_PreviewStart         ( int nChannel, bool bStart );
// ��ͣ�����Ԥ��
KSJ_API  int __stdcall KSJ_PreviewPause         ( int nChannel, bool bPause );

enum    KSJ_PREVIEWSTATUS { PS_STOP, PS_START, PS_PAUSE };
// �õ���ǰ��Ƶ����״̬��ֹͣ����������ͣ
KSJ_API  int __stdcall KSJ_PreviewGetStatus     ( int nChannel, KSJ_PREVIEWSTATUS *pPreviewStatus );
 
// ��ȡ��ͣʱ��ͼ�����ݣ��û����������KSJ_PreviewPause( , true); �ɹ�����á����ݵ�ǰ���õ�Ԥ��ģʽ��ȡ����Ӧ�����ݡ�
KSJ_API  int __stdcall KSJ_PreviewGetPausedData ( int nChannel, unsigned char *pData );

KSJ_API  int __stdcall KSJ_PreviewGetPausedDataEx ( int nChannel, unsigned char *pData, int *pnWidth, int *pnHeight, int *pnBitCount );

// ��ȡԤ��֡��
KSJ_API  int __stdcall KSJ_PreviewGetFrameRate  ( int nChannel, float *fFrameRate );

// ����Ԥ���ص�
typedef VOID (WINAPI *KSJ_PREVIEWCALLBACK )( unsigned char *pImageData, int nWidth, int nHeight, int nBitCount,  void *lpContext );
KSJ_API  int __stdcall KSJ_PreviewSetCallback   ( int nChannel, KSJ_PREVIEWCALLBACK pfPreviewCallback, void *lpContext );

typedef VOID (WINAPI *KSJ_PREVIEWCALLBACKEX )( HDC  hDC, unsigned char *pImageData, int nWidth, int nHeight, int nBitCount,  void *lpContext );
KSJ_API  int __stdcall KSJ_PreviewSetCallbackEx   ( int nChannel, KSJ_PREVIEWCALLBACKEX pfPreviewCallbackEx, void *lpContext );


#ifdef __cplusplus
}
#endif

#endif