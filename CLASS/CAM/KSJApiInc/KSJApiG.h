#ifndef __KSJ_API_G_H__
#define __KSJ_API_G_H__

#pragma message("Include KSJApiG.h") 

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

// Ӳ���Զ��ع�
KSJ_API  int __stdcall KSJ_AECSetEnable ( int nChannel, bool bEnable  );
KSJ_API  int __stdcall KSJ_AECGetEnable ( int nChannel, bool *bEnable  );

KSJ_API  int __stdcall KSJ_AECSetRange ( int nChannel, unsigned short usMin,  unsigned short usMax  );
KSJ_API  int __stdcall KSJ_AECGetRange ( int nChannel, unsigned short *usMin, unsigned short *usMax );

// �õ��Զ��ع���ڵĵ�ǰ�ع�ֵ
KSJ_API  int __stdcall KSJ_AECGetCur ( int nChannel, unsigned short *usCurGain  );

// Ӳ���Զ�����
KSJ_API  int __stdcall KSJ_AGCSetEnable ( int nChannel, bool bEnable  );
KSJ_API  int __stdcall KSJ_AGCGetEnable ( int nChannel, bool *bEnable  );

KSJ_API  int __stdcall KSJ_AGCSetRange ( int nChannel, unsigned short usMin,  unsigned short usMax  );
KSJ_API  int __stdcall KSJ_AGCGetRange ( int nChannel, unsigned short *usMin, unsigned short *usMax );

// �õ��Զ�������ڵĵ�ǰ����ֵ
KSJ_API  int __stdcall KSJ_AGCGetCur ( int nChannel, unsigned short *usCurGain  );

// ���ù̶�֡��(ͨ������sensor�Ĵ���,ʹsensor����̶�֡��)��ֻ��MUC36C/M(MGYY)��MU3E130C/M(CGYY)֧��
KSJ_API  int __stdcall KSJ_SetFixedFrameRate( int nChannel, bool bEnable,   float fFrameRate );
KSJ_API  int __stdcall KSJ_GetFixedFrameRate( int nChannel, bool *pbEnable, float *pfFrameRate );

#ifdef __cplusplus
}
#endif

#endif