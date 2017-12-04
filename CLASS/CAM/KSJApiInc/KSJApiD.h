#ifndef __KSJ_API_D_H__
#define __KSJ_API_D_H__

#pragma message("Include KSJApiD.h") 

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

//
// ���ļ�ֻ������OCR�豸(KSJ_UC320C_OCR)
// 

// KSJ_IR ����ƣ� KSJ_UV ����ƣ�KSJ_VI �ɼ����
enum KSJ_LED { KSJ_IR = 0, KSJ_UV, KSJ_VI };
// KSJ_ON ������KSJ_OFF �ƹ�
enum KSJ_LEDSTATUS { KSJ_OFF = 0, KSJ_ON };

// ���õƵ�״̬
KSJ_API  int __stdcall KSJ_LedSetStatus( int nChannel, KSJ_LED Led, KSJ_LEDSTATUS LedStatus );
KSJ_API  int __stdcall KSJ_LedGetStatus( int nChannel, KSJ_LED Led, KSJ_LEDSTATUS *pLedStatus );


#ifdef __cplusplus
}
#endif

#endif