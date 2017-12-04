#ifndef __KSJ_API_E_H__
#define __KSJ_API_E_H__

#pragma message("Include KSJApiE.h") 

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

// ���º���ֻ������KSJ_UCxxxx_MRYN/MGYN�ͺ����������Y�������ʾ֧���ⴥ����IO����

// �õ��ⴥ���ɼ�������״̬��KSJ_UP��ʾ����û�а��£�KSJ_DOWN��ʾ��������
enum KSJ_SNAPBUTTONSTATUS { KSJ_UP, KSJ_DOWN };
KSJ_API  int __stdcall KSJ_SnapButtonStatus( int nChannel, KSJ_SNAPBUTTONSTATUS *pSnapButtonStatus );

// ����GPIO���ŵ��������״̬��btDirectionλѰַ��BIT0��ӦGPIO0, BIT1��ӦGPIO1, BIT2��ӦGPIO2, BIT3��ӦGPIO3(=1��ʾ��GPIO�����=0��ʾ��GPIO����)
KSJ_API  int __stdcall KSJ_GpioSetDirection( int nChannel, unsigned char btDirection );
// ��ȡGPIO���ŵ��������״̬��pbtDirectionλѰַ��BIT0��ӦGPIO0, BIT1��ӦGPIO1, BIT2��ӦGPIO2, BIT3��ӦGPIO3(=1��ʾ��GPIO�����=0��ʾ��GPIO����)
KSJ_API  int __stdcall KSJ_GpioGetDirection( int nChannel, unsigned char *pbtDirection );

// ����GPIO���������ֻ��btDirection��Ӧλ����Ϊ1�����Ų���ͨ���˺����������������btGpioStatusλѰַ��BIT0��ӦGPIO0, BIT1��ӦGPIO1, BIT2��ӦGPIO2, BIT3��ӦGPIO3(=1��ʾ��GPIO���TTL�ߵ�ƽ��=0��ʾ��GPIO���TTL�͵�ƽ)
KSJ_API  int __stdcall KSJ_GpioSetStatus   ( int nChannel, unsigned char btGpioStatus );
// ��ȡGPIO����״̬��*pbtGpioStatusλѰַ��BIT0��ӦGPIO0, BIT1��ӦGPIO1, BIT2��ӦGPIO2, BIT3��ӦGPIO3(=1��ʾ��GPIO���TTL�ߵ�ƽ��=0��ʾ��GPIO���TTL�͵�ƽ)
KSJ_API  int __stdcall KSJ_GpioGetStatus   ( int nChannel, unsigned char *pbtGpioStatus );

// ��������ƴ����źŵ�ʹ�ܼ���Ч��ƽ, V1.0.6.8�汾ֻ֧��UC500C_MRYN,UC500M_MRYNϵ��
KSJ_API  int __stdcall KSJ_FlashControlSet ( int nChannel, bool bEnable, bool bInvert, int nMode );

KSJ_API  int __stdcall KSJ_FlashControlGet ( int nChannel, bool *pbEnable, bool *pbInvert, int *pnMode );


#ifdef __cplusplus
}
#endif

#endif