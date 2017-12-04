#ifndef __KSJ_API_H_H__
#define __KSJ_API_H_H__

#pragma message("Include KSJApiH.h") 


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

// ������Ϊ16���ش���ģʽʱ���ɼ����ݱ�����ʱ��һ����
// ������Ϊ16���ش���ģʽʱ��Ԥ��ͼ����ͨ��KSJAPI��16���ص�����ת��Ϊ8���ص�������ʾ�ġ�ת����ʽ��������ģʽ�����ü��Ƿ������LUT��������
// ���������LUT����LUT��ת����������������ģʽ��ת����

// �õ�sensor��������ı���λ��������ʶ��16λ�������ݵ���Чλ�������ұ�Ĵ�С��
KSJ_API  int __stdcall KSJ_GetADCResolution( int nChannel, int *pnADCResolution );

// �������Ϊ16bit�Ĳɼ�ģʽ,����ʵ��AD��ת������,��Чλ�����Ը���KSJ_GetADCResolution������ȡ
KSJ_API  int __stdcall KSJ_SetData16Bits ( int nChannel, bool bEnable  );
KSJ_API  int __stdcall KSJ_GetData16Bits ( int nChannel, bool *bEnable );







#ifdef __cplusplus
}
#endif

#endif