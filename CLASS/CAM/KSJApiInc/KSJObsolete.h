#ifndef __KSJ_API_OBSOLETE_H__
#define __KSJ_API_OBSOLETE_H__

#pragma message("Include KSJApiObsolete.h") 


#ifdef KSJAPI_EXPORTS
    #define KSJ_API __declspec(dllexport)
#elif defined KSJAPI_STATIC
	#define KSJ_API
#else
    #define KSJ_API __declspec(dllimport)
#endif

// Ϊ�˱��ֶ��Ͽͻ����õļ����ԣ�����ļ��еĺ�������ǰ�汾����ģ������°汾����Ȼ�������������Ѿ����Ƽ�ʹ�õĺ�����
// ������һЩ�����������������������Ҳ��Щ�����Ѿ�����֧�֡�
#ifdef __cplusplus
extern "C"{
#endif

enum KSJ_TRIGGERSTATUS { KSJ_NO, KSJ_HAVE };
// ��ȡ֡�����Ƿ���ͼ�����ݣ��Ѳ���֧�֣�
KSJ_API  int __stdcall KSJ_TriggerStatusGet ( int nChannel, KSJ_TRIGGERSTATUS *pTriggerStatus  );

#if 0

KSJ_API  int __stdcall KSJ_IsSupportLUT( int nChannel );                      // Use KSJ_QueryFunction
KSJ_API  int __stdcall KSJ_EnableLUT( int nChannel, bool bEnable );           // Use KSJ_LutSetEnable
KSJ_API  int __stdcall KSJ_IsEnableLUT( int nChannel, bool *pbEnable );       // Use KSJ_LutGetEnable


// ���������ʹ��������ұ�д�뵽24LC1024��LUT_BASE_ADDRESSΪ��ַ��ulOffsetAddressΪƫ�Ƶĵ�ַ��
KSJ_API  int __stdcall KSJ_ReadLUT ( int nChannel, unsigned short usOffsetAddress, int nBytes, unsigned char *pData   );
// nBytes���벻����64�ֽڣ�usOffsetAddress ��0��ʼ��
KSJ_API  int __stdcall KSJ_WriteLUT( int nChannel, unsigned short usOffsetAddress, unsigned char *pData, int nBytes  );

// ����Ӱ���
// �����Ҫͨ�����Ӽ�ר�õ�Ӱ������ɹ�������, �˺�������ݲ��ұ�Ĳ�ͬ���ͽ�����Ӧ�ļ���
// ����12bit->8bit����10bit->8bitӳ���, �⺯����������16bit���ݴ���ģʽʱ,ͨ��Ӱ��֮�������ʾ���˹�����PC�˼�����ɡ�
KSJ_API  int __stdcall KSJ_LoadMapTableFile( int nChannel, bool bLoad, const TCHAR *pszTableName );    // Use KSJ_LutSetKtb

#endif
#ifdef __cplusplus
}
#endif

#endif