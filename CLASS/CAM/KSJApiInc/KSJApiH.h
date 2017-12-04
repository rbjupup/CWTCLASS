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

// 当设置为16比特传输模式时，采集数据比正常时多一倍。
// 当设置为16比特传输模式时，预览图像是通过KSJAPI将16比特的数据转换为8比特的数据显示的。转换方式由灵敏度模式的设置及是否加载了LUT来决定。
// 如果加载了LUT则以LUT来转换，否则由灵敏度模式来转换。

// 得到sensor可以输出的比特位数，用于识别16位传输数据的有效位数及查找表的大小。
KSJ_API  int __stdcall KSJ_GetADCResolution( int nChannel, int *pnADCResolution );

// 设置相机为16bit的采集模式,根据实际AD的转换精度,有效位数可以根据KSJ_GetADCResolution函数获取
KSJ_API  int __stdcall KSJ_SetData16Bits ( int nChannel, bool bEnable  );
KSJ_API  int __stdcall KSJ_GetData16Bits ( int nChannel, bool *bEnable );







#ifdef __cplusplus
}
#endif

#endif