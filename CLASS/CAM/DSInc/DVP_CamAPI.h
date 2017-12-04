/*-----------------------------------------------------------------------------*\
| 功能:  声明DVP_CAMSDK.dll的函数接口                            
| 版权:  版权所有                                                     
\*-----------------------------------------------------------------------------*/

#ifndef _CAMAPI_H_
#define _CAMAPI_H_
#include "DVP_Define.H"

#define DLL_EXPORT
#ifdef DLL_EXPORT
#define DS_API extern "C" __declspec(dllexport) 
#else
#define DS_API extern "C" __declspec(dllimport) 
#endif


/*----------------------------------------------------------------------------------*\
| 功  能：获取相机列表                                                     
|                                                                          
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                          
|                                                                          
| 参  数：                                                                 
|       1   Out tDSCameraDevInfo *pDSCameraList 相机基本信息首地址  
|       2   Out INT              *piNums        相机数量            
|                                                                          
| 注  意：                                                                 
|         *piNums为连接本计算机并可访问的相机数量                          
\*----------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetDevList(tDSCameraDevInfo *pDSCameraList, INT *piNums);

/*----------------------------------------------------------------------------------*\
| 功  能：初始化相机（可预览图像）                                     
|                                                                      
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                      
|                                                                      
| 参  数：                                                             
|       1   In  DS_SNAP_PROC pCallbackFunction  回调函数指针                      
|       2   In  LPCSTR lpszFriendlyName     相机昵称                              
|       3   In  HWND hWndDisplay            显示窗口句柄                         
|       4   Out INT *piCameraID             相机编号                              
|                                                                      
| 注  意：
|       1、相机昵称从tDSCameraDevInfo中获取
|       2、摄像头ID，1至n为有效ID，-n至0为无效；                     
|       3、每调用CameraInit成功一次，ID值加1，依次累加，避免ID重复。 
\*----------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraInit(DS_SNAP_PROC pCallbackFunction, 
                                         LPCSTR lpszFriendlyName,
                                           HWND hWndDisplay,
                                            INT *piCameraID);


/*----------------------------------------------------------------------------------*\
| 功  能：初始化相机（不可预览图像）                                     
|                                                                        
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                        
|                                                                        
| 参  数：                                                               
|       1   In  LPCSTR lpszFriendlyName 相机昵称                                         
|       2   Out INT *piCameraID         相机编号                                         
|                                                                     
| 注  意：
|       1、相机昵称从tDSCameraDevInfo中获取
|       2、摄像头ID，1至n为有效ID，-n至0为无效；                      
|       3、每调用CameraInitEx成功一次，ID值加1，依次累加，避免ID重复。 
\*---------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraInitEx(LPCSTR lpszFriendlyName, INT *piCameraID);


/*---------------------------------------------------------------------------------*\
| 功  能：获取相机设备参数范围                                                       
|                                                                                  
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                                     
|                                                                                  
| 参  数：                                                                          
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）              
|       2   Out tDSCameraCap &sDSCameraCap  相机设备参数范围结构               
|                                                                                  
| 注  意：                                                                          
|       本函数可获取相机相关参数的数值范围和默认值                                                                        
\*---------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetCapability(
    INT iCameraID,
    tDSCameraCapability &sDSCameraCap);


/*---------------------------------------------------------------------------------*\
| 功  能：反初始化相机                                                 
|                                                                     
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                       
|                                                                     
| 参  数：                                                            
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）              
|                                                                     
| 注  意：                                                            
|       用于释放内存分配空间，必须在程序退出前调用                     
\*--------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraUnInit(INT iCameraID);


/*--------------------------------------------------------------------------------*\
| 功  能：打开视频流                                                    
|                                                                     
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                        
|                                                                     
| 参  数：                                                            
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）              
|                                                                      
| 注  意：                                                             
|       无                                                           
\*--------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraPlay(INT iCameraID);


/*--------------------------------------------------------------------------------*\
| 功  能：暂停视频流                                                   
|                                                                     
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                        
|                                                                     
| 参  数：                                                            
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）              
|                                                                     
| 注  意：                                                            
|       无                                                          
\*--------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraPause(INT iCameraID);


/*--------------------------------------------------------------------------------*\
| 功  能：停止视频流                                                  
|                                                                    
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                       
|                                                                    
| 参  数：                                                           
|       1   In  INT iCameraID  相机编号（由相机初始化成功后返回）              
|                                                                    
| 注  意：                                                           
|       无                                                         
\*--------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraStop(INT iCameraID);


/*--------------------------------------------------------------------------------*\
| 功  能：相机重启                                                  
|                                                                    
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                       
|                                                                    
| 参  数：                                                           
|       1   In  INT iCameraID  相机编号（由相机初始化成功后返回）              
|		2   In  UINT uRestartType 重置类型                                     
|                                                                    
| 注  意：                                                           
|        如果同时重启sensor和缓存则给参数"SENSOR_RESTART|BUFFER_RESTART"
\*-------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraRestart(INT iCameraID, UINT uRestartType);


/*-------------------------------------------------------------------------------*\
| 功  能：打开相机电源                                                 
|                                                                     
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                       
|                                                                     
| 参  数：                                                            
|       1   In  INT iCameraID  相机编号（由相机初始化成功后返回）               
|                                                                     
| 注  意：                                                            
|       无                                                          
\*-------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraPowerUp(INT iCameraID);


/*-------------------------------------------------------------------------------*\
| 功  能：关闭相机电源                                                 
|                                                                     
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                       
|                                                                     
| 参  数：                                                            
|       1   In  INT  iCameraID  相机编号（由相机初始化成功后返回）               
|                                                                     
| 注  意：                                                            
|       无                                                          
\*-------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraPowerDown(INT iCameraID);


/*-------------------------------------------------------------------------------*\
| 功  能：图像数据处理                                                            
|                                                                                
| 返回值：调用成功返回RGB24图像数据首地址，否则返回NULL                             
|                                                                                
| 参  数：                                                                       
|       1   In  INT iCameraID   相机编号（回调函数          ）                          
|       2   In  BYTE *pbyRAW    图像数据首地址，回调函数参数                          
|       3   In  tDSFrameInfo *psFrInfo 图像帧数据信息，参见tDSFrameInfo定义           
|                                                                                
| 注  意：                                                                       
|       无                                                                     
\*-------------------------------------------------------------------------------*/
DS_API BYTE* CameraISP(INT iCameraID, BYTE *pbyRAW, tDSFrameInfo *psFrInfo);


/*-------------------------------------------------------------------------------*\
| 功  能：RAW转RGB算法选择                                                            
|                                                                                
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                             
|                                                                                
| 参  数：                                                                       
|       1   In  INT iCameraID       摄像头ID，回调函数参数                     
|       2   In  INT	iRawToRGBType   RAW转RGB算法编号                           
|                                                                                
| 注  意：                                                                       
|       无                                                                     
\*-------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetBayertoRGBType(INT iCameraID, INT iRawToRGBType);


/*-------------------------------------------------------------------------------*\
| 功  能：获取当前RAW转RGB算法编号                                                            
|                                                                                
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                            
|                                                                                
| 参  数：                                                                       
|       1   In  INT iCameraID   摄像头ID，回调函数参数                         
|       2   In  INT *piRawToRGBType RAW转RGB算法编号                           
|                                                                                
| 注  意：                                                                       
|       无                                                                     
\*--------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetBayertoRGBType(INT iCameraID, INT *piRawToRGBType);


/*--------------------------------------------------------------------------------*\
| 功  能：显示RGB24位图像数据                                                        
|                                                                                   
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                                     
|                                                                                   
| 参  数：                                                                          
|       1   In  INT  iCameraID  相机编号（回调函数          ）                              
|       2   In  BYTE *pbyRGB24  RGB24图像数据首地址                                      
|       3   In  tDSFrameInfo *psFrInfo  图像数据详细信息，参见tDSFrameInfo定义            
|                                                                                   
| 注  意：                                                                          
|       无                                                                        
\*--------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraDisplayRGB24(
    INT iCameraID, 
    BYTE *pbyRGB24, 
    tDSFrameInfo *psFrInfo);


/*----------------------------------------------------------------------------*\
| 功  能：显示ROI区域选择框                                             
|                                                                      
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                        
|                                                                      
| 参  数：                                                             
|       1   In  INT iCameraID   相机编号（回调函数          ）                
|       2   In  tDSROISize sROISize ROI区域选择框位置和尺寸                 
|                                                                      
| 注  意：                                                             
|         无                                                           
\*----------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraDisplayROISel(INT iCameraID, tDSROISize sROISize);


/*----------------------------------------------------------------------------*\
| 功  能：设置预览图像尺寸                                                 
|                                                                        
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                           
|                                                                        
| 参  数：                                                                
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）                 
|       2   In  INT iWidth      预览图像宽度                                                            
|       3   In  INT iHeight     预览图像高度                                                            
|                                                                        
| 注  意：                                                                
|         无                                                              
\*----------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetDisplaySize(
    INT iCameraID,             
    INT iWidth,                
    INT iHeight);


/*----------------------------------------------------------------------------*\
| 功  能：开启录影功能                                                       
|                                                                           
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                             
|                                                                           
| 参  数：                                                                  
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）              
|       2   In  LPCSTR lpszFileName  视频文件的路径和名称                             
|                                                                           
| 注  意：                                                                  
|       无                                                                
\*----------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraStartRecordVideo(INT iCameraID, LPCSTR lpszFileName);


/*----------------------------------------------------------------------------*\
| 功  能：开启录影功能，不自动添加相机名和时间到录影文件名                                                     
|                                                                           
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                             
|                                                                           
| 参  数：                                                                  
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）              
|       2   In  LPCSTR lpszFileName  视频文件的路径和名称                             
|                                                                           
| 注  意：                                                                  
|       无                                                                
\*----------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraStartRecordVideoEx(INT iCameraID, LPCSTR lpszFileName);

/*----------------------------------------------------------------------------*\
| 功  能：停止录影功能                                                  
|                                                                      
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                        
|                                                                      
| 参  数：                                                             
|       1   In  INT iCameraID  相机编号（由相机初始化成功后返回）              
|                                                                      
| 注  意：                                                             
|       无                                                           
\*----------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraStopRecordVideo(INT iCameraID);


/*----------------------------------------------------------------------------*\
| 功  能：设置视频文件最大占用空间                                      
|                                                                     
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                        
|                                                                     
| 参  数：                                                            
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）	             
|       2   In  INT iFileSize   视频文件最大占用空间，单位：Mega BYTE           
|                                                                     
| 注  意：                                                            
|       录制时，当文件达到设置的最大占用空间，将生成新的视频文件       
\*---------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetRecordFileSize(INT iCameraID, INT iFileSize);


/*---------------------------------------------------------------------------*\
| 功  能：获取视频文件的最大占用空间                                      
|                                                                       
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                         
|                                                                       
| 参  数：                                                              
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）                  
|       2   Out INT *piFileSize 视频文件最大占用空间，单位：Mega BYTE              
|                                                                       
| 注  意：                                                              
|       无                                                            
\*---------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetRecordFileSize(INT iCameraID, INT *piFileSize);


/*---------------------------------------------------------------------------*\
| 功  能：设置视频文件的图像质量                                        
|                                                                     
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                        
|                                                                     
| 参  数：                                                            
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）              
|       2   In  INT iQuality    视频文件的图像质量                             
|                                                                     
| 注  意：                                                            
|       iQuality 值为 1：低等质量；2：中等质量；3：高等质量            
\*---------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetRecordAVIQuality(INT iCameraID, INT iQuality);


/*---------------------------------------------------------------------------*\
| 功  能：获取视频文件的图像质量                                         
|                                                                      
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                         
|                                                                      
| 参  数：                                                             
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）              
|       2   Out INT *piQuality  视频文件的图像质量                             
|                                                                      
| 注  意：                                                             
|       *piQuality 值为 1：低等质量；2：中等质量；3：高等质量           
\*---------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetRecordAVIQuality(INT iCameraID, INT *piQuality);


/*---------------------------------------------------------------------------*\
| 功  能：设置视频文件的图像压缩编码器                                  
|                                                                     
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                       
|                                                                     
| 参  数：                                                            
|       1   In  INT iCameraID  相机编号（由相机初始化成功后返回）              
|       2   In  INT iCodeType  视频文件的图像压缩编码器                       
|                                                                     
| 注  意：                                                            
|       iCodeType 值为 1：MPEG4；                                   
\*--------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetRecordEncoder(INT iCameraID, INT iCodeType);


/*--------------------------------------------------------------------------*\
| 功  能：获取视频文件的图像压缩编码器                                    
|                                                                       
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                         
|                                                                       
| 参  数：                                                              
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT *piCodeType 视频文件的图像压缩编码器                      
|                                                                       
| 注  意：                                                              
|       *piCodeType 值为 1：MPEG4；                                   
\*--------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetRecordEncoder(INT iCameraID, INT *piCodeType);


/*--------------------------------------------------------------------------*\
| 功  能：获取录影的帧率                                                 
|                                                                       
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                         
|                                                                       
| 参  数：                                                              
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）            
|       2   Out float *pfRate 录影的帧率，单位：FPS                          
|                                                                       
| 注  意：                                                              
|       无                                                            
\*--------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetRecordRate(INT iCameraID, float *pfRate);


/*-----------------------------------------------------------------------------------*\
| 功  能：将图像数据写入视频文件                                                     
|                                                                                  
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                                     
|                                                                                  
| 参  数：                                                                         
|       1   In  INT iCameraID   相机编号（回调函数          ）                               
|       2   In  BYTE *pbyRGB    RGB24位图像数据首地址                                     
|       3   In  tDSFrameInfo *psFrInfo 图像数据详细信息，参见tDSFrameInfo定义             
|                                                                                  
| 注  意：                                                                         
|       无                                                                       
\*-----------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraRecordFrame(
    INT iCameraID,             
    BYTE *pbyRGB,       
    tDSFrameInfo *psFrInfo);


/*-----------------------------------------------------------------------------------*\
| 功  能：获取相机图像数据首地址                                                   
|                                                                                
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                                   
|                                                                                
| 参  数：                                                                       
|       1   In  INT iCameraID    相机编号（由相机初始化成功后返回）             
|       2   In  emDSDataType emDataType 图像数据类型                           
|       3   Out BYTE **pbyBuffer        图像数据首地址                         
|                                                                                
| 注  意：                                                                       
|       1、emDataType参考emDSDataType枚举类型
|       2、如果emDataType不在支持范围，错误码为STATUS_PARAMETER_INVALID
|       3、与CameraReleaseImageBuffer配对使用      
|       4、只在使用CameraInitEx初始化相机时使用，否则会返回STATUS_NOT_SUPPORTED
\*-----------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetImageBuffer(
    INT iCameraID,     
    emDSDataType emDataType, 
    BYTE **pbyBuffer);


/*--------------------------------------------------------------------------------------------*\
| 功  能：释放相机图像数据首地址                                                            
|                                                                                         
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                                            
|                                                                                         
| 参  数：                                                                                
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）                        
|       2   In  emDSDataType emDataType 图像数据类型                                    
|       3   In  BYTE *pbyBuffer         图像数据首地址                                   
|                                                                                         
| 注  意：                                                                                
|       1、emDataType参考emDSDataType枚举类型                                            
|       2、与CameraGetImageBuffer配对使用，pbyBuffer指向的数据处理完成，需调用此接口释放数据
|       3、CameraReleaseImageBuffer的数据类型必需与CameraGetImageBuffer的一致              
\*--------------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraReleaseImageBuffer(
    INT iCameraID,                         
    emDSDataType emDataType,         
    BYTE *pbyBuffer);


/*------------------------------------------------------------------------------------*\
| 功  能：获取相机帧数统计信息                                                        
|                                                                                   
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                                      
|                                                                                   
| 参  数：                                                                           
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）              
|       2   Out DSFrameCount *psFrameCount  帧数统计信息                      
|                                                                                   
| 注  意：                                                                           
|       无                                                                        
\*------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetFrameCount(INT iCameraID, tDSFrameCount *psFrameCount);


/*---------------------------------------------------------------------------------*\
| 功  能：保存相机当前图像数据到指定文件                                           
|                                                                               
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                                  
|                                                                               
| 参  数：                                                                       
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）                  
|       2   In  LPCSTR lpszFileName 图像文件路径和名称                             
|       3   In  BYTE byFileType     图像文件类型                                   
|       4   In  BYTE byQuality      JPEG类型图像文件的图像质量                      
|                                                                               
| 注  意：                                                                       
|       1、byFileType参考emDSFileType枚举类型，对各值作或运算，即可保存多类型文件 
|       2、byQuality只在JPEG类型中生效，范围是1~100，其他类型设置任意值。
\*---------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraCaptureFile(
    INT iCameraID,                    
    LPCSTR lpszFileName,         
    BYTE byFileType,          
    BYTE byQuality);

/*---------------------------------------------------------------------------------*\
| 功  能：保存相机当前图像数据到指定文件,保存ROI的图像数据用这个接口                                           
|                                                                               
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                                  
|                                                                               
| 参  数：                                                                       
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）                  
|       2   In  LPCSTR lpszFileName    图像文件路径和名称                          
|       3   In  BYTE byFileType  图像文件类型                                      
|       4   In  BYTE byQuality   JPEG类型图像文件的图像质量                         
|                                                                               
| 注  意：                                                                       
|       1、byFileType参考emDSFileType枚举类型，对各值作或运算，即可保存多类型文件； 
|       2、byQuality只在JPEG类型中生效，范围是1~100，其他类型设置任意值；
|       3、与CameraCaptureFile兼容，增加保存ROI模式图像数据功能。
\*---------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraCaptureFileEx(
    INT iCameraID,           
    LPCSTR lpszFileName,   
    BYTE byFileType,    
    BYTE byQuality);

/*---------------------------------------------------------------------------------*\
| 功  能： 抓取一帧图像到缓冲区，尺寸由设置为捕捉的分辨率决定                                           
|                                                                               
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                                  
|                                                                               
| 参  数：                                                                       
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）                  
|       2   In  BYTE *pbyData	保存图像数据的缓冲区指针                        
|		3	Out tDSFrameInfo *psFrameInfo   图像数据基本信息	               
|       4   In  emDSDataType emDataType     数据类型                                
|                                                                               
| 注  意：                                                                       
|       1、emDataType参考emDSDataType定义，目前支持RAW数据和RGB24类型。
\*---------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraCaptureDataEx(
    INT iCameraID,         
    BYTE *pbyData,       
    tDSFrameInfo	*psFrameInfo, 
    emDSDataType emDataType);

/*--------------------------------------------------------------------------------------*\
| 功  能：保存RGB24位图像数据到BMP文件                                                  
|                                                                                     
| 返回值：调用成功返回STATUS_OK，否则返回错误代码                                        
|                                                                                     
| 参  数：                                                                             
|       1   In  INT iCameraID   相机编号（回调函数          ）                             
|       2   In  LPCSTR  lpszFileName  图像文件路径和名称                                
|       3   In  BYTE    *pbyRGB24     RGB24位图像数据首地址                             
|       4   In  tDSFrameInfo *psFrInfo 图像数据详细信息，参见tDSFrameInfo定义            
|                                                                                     
| 注  意：                                                                             
|       无                                                                          
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSaveBMPFile(
    INT iCameraID,       
    LPCSTR lpszFileName,  
    BYTE *pbyRGB24, 
    tDSFrameInfo *psFrInfo);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取相机图像数据缓存
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  BYTE *pbyImageBuffer  相机图像数据缓存首地址                   
|       3   In  emDSDataType emDataType  相机图像数据类型                      
|       4   In  tDSFrameInfo &sFrInfo    本帧图像数据的基本信息                
|
| 注  意：
|       1、10位、12位、16位的图像数据均采用16位（即2字节）存储；
|       2、16位数据的排列方式是“Little-Endian”，即低位数据在前字节，高位数据在后字节；
|       3、图像宽度、高度和数据位数均可在“&sFrInfo”中获得；
|       4、图像数据总字节数 = 图像宽度 X 图象高度 X 每像素字节数。
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetImageData(
    INT iCameraID,        
    BYTE *pbyImageBuffer, 
    emDSDataType emDataType, 
    tDSFrameInfo &sFrInfo);


/*--------------------------------------------------------------------------------------*\
| 功  能：保存当前显示图像
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  LPCSTR lpFileName      图像文件的路径和名称                    
|       3   In  BYTE *pbyImageBuffer 图像数据缓存首地址                        
|       4   In  tDSFrameInfo  *psFrInfo 图像数据的帧信息                       
|       5   In  BYTE byFileType      图像文件类型                              
|       6   In  BYTE byQuality       JPEG类型图像文件的图像质量                
|
| 注  意：
|       1、byQuality只在JPEG类型中生效，范围是1~100，其他类型设置任意值。
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSaveCurrentImage(
    INT iCameraID,          
    LPCSTR lpszFileName,    
    BYTE *pbyImageBuffer,    
    tDSFrameInfo *psFrInfo,   
    BYTE byFileType,            
    BYTE byQuality);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置图像翻转状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID  相机编号（由相机初始化成功后返回）                      
|       2   In  emDSMirrorDirection  emDir  图像翻转方向标识（水平或垂直）             
|       3   In  BOOL bEnable   图像翻转状态                                            
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetMirror(INT iCameraID, emDSMirrorDirection emDir, BOOL bEnable);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取图像翻转状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID  相机编号（由相机初始化成功后返回）                      
|       2   In  emDSMirrorDirection  emDir  图像翻转方向标识（水平或垂直）             
|       3   Out BOOL *pbEnable  图像翻转状态                                           
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetMirror(INT iCameraID, emDSMirrorDirection emDir, BOOL *pbEnable);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置图像选择状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT	iRotation   图像旋转参数                                   
|
| 注  意：
|      旋转参数定义：	0:未旋转 1:顺时针旋转90度 2:逆时针旋转90度
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetRotation(INT iCameraID, INT iRotation);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取图像选择状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT	*piRotation	图像旋转参数                                   
|
| 注  意：
|       旋转参数定义：	0:不旋转 1:顺时针旋转90度 2:逆时针旋转90度
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetRotation(INT iCameraID, INT *piRotation);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置图像单色状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  BOOL bEnable    图像单色状态                                   
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetMonochrome(INT iCameraID, BOOL bEnable);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取图像单色状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out BOOL *pbEnable  图像单色状态                                   
|
| 注  意：
|        无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetMonochrome(INT iCameraID, BOOL *pbEnable);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置图像反色状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  BOOL bEnable 图像反色状态                                      
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetInverse(INT iCameraID, BOOL bEnable);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取图像反色状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID  相机编号（由相机初始化成功后返回）              
|       2   Out BOOL *pbEnable 图像反色状态                                    
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetInverse(INT iCameraID, BOOL *pbEnable);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置自动曝光状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  BOOL bState     自动曝光状态                                   
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetAeState(INT iCameraID, BOOL bState);

/*--------------------------------------------------------------------------------------*\
| 功  能：获取自动曝光状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out BOOL *pbAeState 自动曝光状态                                   
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetAeState(INT iCameraID, BOOL *pbAeState);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置自动曝光目标值
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  BYTE byAeTarget 自动曝光目标值                                 
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetAeTarget(INT iCameraID, BYTE byAeTarget);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取自动曝光目标值
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out BYTE *pbyAeTarget    自动曝光目标值                            
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetAeTarget(INT iCameraID, BYTE *pbyAeTarget);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置自动曝光参考区域
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT iHOff       水平偏移量，单位：像素                         
|       3   In  INT iVOff       垂直偏移量，单位：像素                         
|       4   In  INT iWidth      参考区域宽度，单位：像素                       
|       5   In  INT iHeight     参考区域高度，单位：像素                       
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetAEWindow(
    INT iCameraID,                    
    INT iHOff,            
    INT iVOff,            
    INT iWidth,         
    INT iHeight);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置曝光时间
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  UINT64  uExposureTime  曝光时间，单位：0.1us                   
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetExposureTime(INT iCameraID, UINT64 uExposureTime);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取曝光时间
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out UINT64  *puExposureTime  曝光时间，单位：0.1us                 
|       3   Out UINT64  *puExpTimeMax    曝光时间最大值，单位：0.1us           
|       4   Out UINT64  *puExpTimeMin    曝光时间最小值，单位：0.1us           
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetExposureTime(
    INT iCameraID,          
    UINT64 *puExposureTime,     
    UINT64 *puExpTimeMax,      
    UINT64 *puExpTimeMin);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置自动曝光模式
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT	iMode       曝光模式编号                                   
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetAeMode(INT iCameraID, INT iMode);

/*--------------------------------------------------------------------------------------*\
| 功  能：获取自动曝光模式
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT	*piMode		曝光模式编号                                   
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetAeMode(INT iCameraID, INT *piMode);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置自动曝光算法
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT iScheme	    自动曝光算法编号                               
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetAeScheme(INT iCameraID, INT iScheme);

/*--------------------------------------------------------------------------------------*\
| 功  能：获取自动曝光算法
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT	*piScheme	自动曝光算法编号                               
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetAeScheme(INT iCameraID, INT *piScheme);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置曝光增益
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  float fAnalogGain 曝光增益值，单位：倍数                       
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetAnalogGain(INT iCameraID, float fAnalogGain);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取曝光增益
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out float *pfAnalogGain   曝光增益值，单位：倍数                   
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetAnalogGain(INT iCameraID, float *pfAnalogGain);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置消除图像杂点状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  BOOL bEnable    消除图像杂点状态                               
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetDeadPixelCorrectionState(INT iCameraID, BOOL bEnable);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取消除图像杂点状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out BOOL *pbEnable  消除图像杂点状态                               
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetDeadPixelCorrectionState(INT iCameraID, BOOL *pbEnable);


/*--------------------------------------------------------------------------------------*\
| 功  能：更新图像杂点位置坐标
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|
| 注  意：
|       用于在特别环境时，更新相机保存的杂点位置坐标
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraCreateDefectCorrectionInfo(INT iCameraID);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置图像锐化状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  BOOL bEnable    图像锐化状态                                   
|
| 注  意：
|        无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetEdgeEnhance(INT iCameraID, BOOL bEnable);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取图像锐化状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out BOOL *pbEnable  图像锐化状态                                   
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetEdgeEnhance(INT iCameraID, BOOL *pbEnable);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置图像锐化目标值
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  BYTE byEdgeGain 图像锐化目标值                                 
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetEdgeGain(INT iCameraID, BYTE byEdgeGain);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取图像锐化目标值
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out BYTE *pbyEdgeGain    图像锐化目标值                            
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetEdgeGain(INT iCameraID, BYTE *pbyEdgeGain);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置图像降噪状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  BOOL bReduction 图像降噪状态                                   
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetNoiseReductionState(INT iCameraID, BOOL bReduction);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取图像降噪状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out BOOL    *pbReduction    图像降噪状态                           
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetNoiseReductionState(INT iCameraID, BOOL *pbReduction);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置图像降噪目标值
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT iReduction  图像降噪目标值                                 
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetNoiseReduction(INT iCameraID, INT iReduction);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取图像降噪目标值
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT *piReduction    图像降噪目标值                             
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetNoiseReduction(INT iCameraID, INT *piReduction);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置图像3D降噪状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  BOOL b3DReduction  图像3D降噪状态                              
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSet3DNoiseReductionState(INT iCameraID, BOOL b3DReduction);

/*--------------------------------------------------------------------------------------*\
| 功  能：获取图像3D降噪状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out BOOL *pb3DReduction  图像3D降噪状态                            
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGet3DNoiseReductionState(INT iCameraID, BOOL *pb3DReduction);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置图像3D降噪目标值
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT i3DReduction    图像3D降噪目标值                           
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSet3DNoiseReduction(INT iCameraID, INT i3DReduction);

/*--------------------------------------------------------------------------------------*\
| 功  能：获取图像3D降噪目标值
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT *pi3DReduction  图像3D降噪目标值                           
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGet3DNoiseReduction(INT iCameraID, INT *pi3DReduction);

/*--------------------------------------------------------------------------------------*\
| 功  能：一次性白平衡功能
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetOnceWB(INT iCameraID);

/*--------------------------------------------------------------------------------------*\
| 功  能：获取自动白平衡是否可用
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID       相机编号（由相机初始化成功后返回）   
|       2   Out BOOL *pbAvailabe    自动白平衡是否可用             
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraIsAWBAvailable(INT iCameraID, BOOL *pbAvailabe);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置自动白平衡状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  BOOL bAWBState  自动白平衡状态                                 
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetAWBState(INT iCameraID, BOOL bAWBState);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取自动白平衡状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out BOOL *pbAWBState 自动白平衡状态                                
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetAWBState(INT iCameraID, BOOL *pbAWBState);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置白平衡参考区域
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT iHOff       水平偏移量，单位：像素                         
|       3   In  INT iVOff       垂直偏移量，单位：像素                         
|       4   In  INT iWidth      参考区域宽度，单位：像素                       
|       5   In  INT iHeight     参考区域高度，单位：像素                       
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetWBWindow(INT iCameraID, 
                                          INT iHOff, 
                                          INT iVOff, 
                                          INT iWidth, 
                                          INT iHeight);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置一次黑电平自动调节
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraBlackLevelOnce(INT iCameraID);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置黑电平调节使能状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）                  
|       2   In  BOOL bBlackLevel 黑电平使能状态 TRUE：使能，FALSE：取消             
|
| 注  意：
|         无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetBlackLevelState(INT iCameraID, BOOL bBlackLevel);

/*--------------------------------------------------------------------------------------*\
| 功  能：获取黑电平调节使能状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out BOOL    *pbBlackLevel   黑电平使能状态                         
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetBlackLevelState(INT iCameraID, BOOL *pbBlackLevel);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置黑电平参数
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT iLevelForR  红色分量黑电平                                 
|       3   In  INT iLevelForG  绿色分量黑电平                                 
|       4   In  INT iLevelForB  蓝色分量黑电平                                 
|       5   In  INT iMaxValue   最大允许值                                     
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetBlackLevel(INT iCameraID, 
											INT iLevelForR,
											INT iLevelForG,
											INT iLevelForB,
											INT iMaxValue=4095);

/*--------------------------------------------------------------------------------------*\
| 功  能：获取黑电平参数
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT *piLevelForR    红色分量黑电平                             
|       3   Out INT *piLevelForG    绿色分量黑电平                             
|       4   Out INT *piLevelForB    蓝色分量黑电平                             
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetBlackLevel(INT iCameraID, 
											INT *piLevelForR,
											INT *piLevelForG,
											INT *piLevelForB);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置各色彩通道的增益
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  float fRGain    红通道增益                                     
|       3   In  float fGGain    绿通道增益                                     
|       4   In  float fBGain    蓝通道增益                                     
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetGain(
    INT iCameraID,  
    float fRGain,   
    float fGGain,    
    float fBGain);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取各色彩通道的增益
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID  相机编号（由相机初始化成功后返回）              
|       2   Out float *pfRGain 红通道增益                                      
|       3   Out float *pfGGain 绿通道增益                                      
|       4   Out float *pfBGain 蓝通道增益                                      
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetGain(
    INT iCameraID,         
    float *pfRGain,     
    float *pfGGain,    
    float *pfBGain);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置色彩饱和度状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  BOOL  bEnable   色彩饱和度状态                                 
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetColorEnhancement(INT iCameraID, BOOL bEnable);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取色彩饱和度状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out BOOL    *pbEnable 色彩饱和度状态                               
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetColorEnhancement(INT iCameraID, BOOL *pbEnable);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置色彩饱和度值
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  BYTE    bySaturation    色彩饱和度值                           
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetSaturation(INT iCameraID, BYTE bySaturation);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取色彩饱和度值
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out BYTE    *pbySaturation  色彩饱和度值                           
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetSaturation(INT iCameraID, BYTE *pbySaturation);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置伽玛调节使能状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  BOOL    bGamma  伽玛使能状态 TRUE：势能，FALSE：取消           
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetGammaState(INT iCameraID, BOOL bGamma);

/*--------------------------------------------------------------------------------------*\
| 功  能：获取伽玛调节使能状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out BOOL *pbGamma   伽玛使能状态指针                               
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetGammaState(INT iCameraID, BOOL *pbGamma);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置伽玛值
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  BYTE byGamma    伽玛值                                         
|
| 注  意：
|         无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetGamma(INT iCameraID, BYTE byGamma);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取伽玛值
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out BYTE *pbyGamma  伽玛值                                         
|
| 注  意：
|         无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetGamma(INT iCameraID, BYTE *pbyGamma);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置对比度调节使能状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）                 
|       2   In  BOOL bContrast  对比度使能状态 TRUE：使能，FALSE：取消             
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetContrastState(INT iCameraID, BOOL bContrast);

/*--------------------------------------------------------------------------------------*\
| 功  能：获取对比度调节使能状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out BOOL    *pbContast 对比度使能状态指针                          
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetContrastState(INT iCameraID, BOOL *pbContrast);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置对比度值
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  BYTE    byContrast  对比度值                                   
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetContrast(INT iCameraID, BYTE byContrast);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取对比度值
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out BYTE *pbyContrast   对比度值                                   
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetContrast(INT iCameraID, BYTE *pbyContrast);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置帧率
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  emDSFrameSpeed  emFrameSpeed  帧率                             
|
| 注  意：
|       emFrameSpeed参考emDSFrameSpeed枚举类型
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetFrameSpeed(INT iCameraID, emDSFrameSpeed emFrameSpeed);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取帧率
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out emDSFrameSpeed  *pemFrameSpeed  帧率                           
|
| 注  意：
|         emFrameSpeed参考emDSFrameSpeed枚举类型
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetFrameSpeed(INT iCameraID, emDSFrameSpeed *pemFrameSpeed);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置抗频闪状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  BOOL    bEnable 抗频闪状态                                     
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetAntiFlick(INT iCameraID, BOOL bEnable);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取抗频闪状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out BOOL    *pbEnable   抗频闪状态                                 
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetAntiFlick(INT iCameraID, BOOL *pbEnable);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置抗频闪参数
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）                 
|       2   In  emDSLightFrequency  emFrequency  抗频闪参数（灯光频率）            
|
| 注  意：
|         无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetLightFrequency(INT iCameraID, emDSLightFrequency emFrequency);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取抗频闪参数
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）                  
|       2   Out emDSLightFrequency  *pemFrequency  抗频闪参数（灯光频率）           
|
| 注  意：
|         无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetLightFrequency(INT iCameraID, emDSLightFrequency *pemFrequency);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置相机预定义的分辨率模式
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT iSel        预定义的分辨率索引号                           
|       3   In  BOOL bCapture   预览或拍照模式的分辨率                         
|
| 注  意：
|       1、相机支持的预定义分辨率模式通过函数CameraGetCapability获取
|       2、bCapture为TRUE时设置拍照模式的分辨率，否则设置预览模式的分辨率
|       3、使用该函数，设置相机的分辨率后，需调用函数CameraPlay，启动视频流
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetImageSizeSel(INT iCameraID, INT iSel, BOOL bCapture = FALSE);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取相机预定义的分辨率模式
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT *piSel      预定义的分辨率索引号                           
|       3   In  BOOL bCapture   预览或拍照模式的分辨率                         
|
| 注  意：
|         1、bCapture为TRUE时获取拍照模式的分辨率，否则获取预览模式的分辨率
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetImageSizeSel(INT iCameraID, INT *piSel, BOOL bCapture = FALSE);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置相机的分辨率模式（ROI）
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  BOOL bReserve   保留参数，暂未启用			                   
|       3   In  INT iHOff       水平偏移量，单位：像素                         
|       4   In  INT iVOff       垂直偏移量，单位：像素                         
|       5   In  INT iWidth      区域宽度，单位：像素                           
|       6   In  INT iHeight     区域高度，单位：像素                           
|       7   In  BOOL bCapture   设置的分辨率是预览或拍照                       
|
| 注  意：
|       1、bCapture为TRUE时设置拍照模式的分辨率，否则设置预览模式的分辨率
\*--------------------------------------------------------------------------------------*/
DS_API  emDSCameraStatus CameraSetImageSize(
    INT iCameraID,                    
    BOOL bReserve,                    
    INT iHOff,                    
    INT iVOff,                    
    INT iWidth,                  
    INT iHeight,            
    BOOL bCapture = FALSE);

/*--------------------------------------------------------------------------------------*\
| 功  能：获取相机的分辨率模式（ROI）
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out BOOL *pbROI     设置的分辨率是预定义或ROI                      
|       3   Out INT *piHOff     水平偏移量，单位：像素                         
|       4   Out INT *piVOff     垂直偏移量，单位：像素                         
|       5   Out INT *piWidth    区域宽度，单位：像素                           
|       6   Out INT *piHeight   区域高度，单位：像素                           
|       7   In  BOOL bCapture   设置的分辨率是预览或拍照                       
|
| 注  意：
|         1、bROI为TRUE时当前是ROI分辨率，否则当前是预定义分辨率
|         2、bCapture为TRUE时获取拍照模式的分辨率，否则获取预览模式的分辨率
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetImageSize(
    INT iCameraID,              
    BOOL *pbROI,          
    INT *piHOff,           
    INT *piVOff,         
    INT *piWidth,          
    INT *piHeight,         
    BOOL bCapture = FALSE);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置传输的图像数据包长度（千兆网相机）
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT iPack       数据包长度索引号                               
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetTransPackLen(INT iCameraID, INT iPack);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取传输的图像数据包长度（千兆网相机）
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT *piPack     数据包长度索引号                               
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetTransPackLen(INT iCameraID, INT *piPack);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置时间戳单位（千兆网相机）
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT iUnit       时间戳单位索引号                               
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetTimeStampUnit(INT iCameraID, INT iUnit);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取时间戳单位（千兆网相机）
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT *piUnit     时间戳单位索引号                               
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetTimeStampUnit(INT iCameraID, INT *piUnit);


/*--------------------------------------------------------------------------------------*\
| 功  能：保存相机的参数设置
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  emDSParameterTeam emTeam 保存参数的组别（共4组）               
|
| 注  意：
|         无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSaveParameter(INT iCameraID, emDSParameterTeam emTeam);


/*--------------------------------------------------------------------------------------*\
| 功  能：读取相机的参数设置，并使其生效
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  emDSParameterTeam emTeam    保存参数的组别（共4组）            
|
| 注  意：
|         无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraReadParameter(INT iCameraID, emDSParameterTeam emTeam);

/*--------------------------------------------------------------------------------------*\
| 功  能：保存相机的参数到配置文件
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSaveParameterToIni(INT iCameraID);

/*--------------------------------------------------------------------------------------*\
| 功  能：从配置文件读取相机的参数，并使其生效
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraLoadParameterFromIni(INT iCameraID);

/*--------------------------------------------------------------------------------------*\
| 功  能：保存相机的参数到ini文件，并使其生效
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|		2   In  LPCSTR  lpszIniPath 保存参数的ini文件的路径                    
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSaveParameterToIniEx(INT iCameraID, LPCSTR lpszIniPath);

/*--------------------------------------------------------------------------------------*\
| 功  能：从配置文件读取相机的参数，并使其生效
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|		2   In  LPCSTR  lpszIniPath 保存参数的ini文件的路径                    
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraLoadParameterFromIniEx(INT iCameraID, LPCSTR lpszIniPath);

/*--------------------------------------------------------------------------------------*\
| 功  能：获取当前使用的保存参数组别
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out emDSParameterTeam *pemTeam  保存参数的组别（共4组）            
|
| 注  意：
|         无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetCurrentParameterTeam(INT iCameraID, emDSParameterTeam *pemTeam);


/*--------------------------------------------------------------------------------------*\
| 功  能：读出相机默认出厂参数设置
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraLoadDefaultParameter(INT iCameraID);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置相机输出的图像数据类型
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  emDSDataType emMediaType    图像数据类型                       
|
| 注  意：
|         各款相机支持的数据类型，请参考相关手册
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetMediaType(INT iCameraID, emDSDataType emMediaType);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取相机输出的图像数据类型
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out emDSDataType *pemMediaType  图像数据类型                       
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetMediaType(INT iCameraID, emDSDataType *pemMediaType);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置相机输出的图像数据类型
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT iSel        图像数据类型索引号                             
|
| 注  意：
|       各款相机支持的具体数据类型，请参考相关手册
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetMediaTypeSel(INT iCameraID, INT iSel);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取相机输出的图像数据类型
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT *piSel      图像数据类型索引号                             
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetMediaTypeSel(INT iCameraID, INT *piSel);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置色彩矫正矩阵
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT iSel        图像色彩矩阵索引号                             
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetRgbMatrixSel(INT iCameraID, INT iSel);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取当前的色彩矫正矩阵
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT *piSel      图像色彩矩阵索引号                             
|
| 注  意：
|         无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetRgbMatrixSel(INT iCameraID, INT *piSel);


/*--------------------------------------------------------------------------------------*\
| 功  能：使对应的色彩矫正矩阵数据生效
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  float   fMatrix[3][3]  图像色彩矩阵数据                        
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraApplyColorMatrix(INT iCameraID, float fMatrix[3][3]);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置工作模式（触发模式）
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT iSnapMode   工作模式                                       
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetTriggerMode(INT iCameraID, INT iSnapMode);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取工作模式（触发模式）
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT *piSnapMode 工作模式                                       
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetTriggerMode(INT iCameraID, INT *piSnapMode);


/*--------------------------------------------------------------------------------------*\
| 功  能：触发相机输出一帧图像（触发模式）
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraTrigger(INT iCameraID);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置触发电平参数
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|	    1   In  INT iCameraID   相机编号（由相机初始化成功后返回)             
|       2   In  INT iPulseStyle	    触发电平边缘极性                          
|       3   In  UINT uPulseWidth    脉冲电平时间                              
|       4	In  UINT uDelay	        延时信息                                  
|       5   In  UINT uFilterWidth   滤波器宽度                                
|       
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetTriggerPulse(
    INT iCameraID,          
    INT iPulseStyle,        
    UINT uPulseWidth,        
    UINT uDelay,            
    UINT uFilterWidth);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取触发电平参数
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT *piPulseStyle   触发电平边缘极性                           
|	    3   Out UINT *puPulseWidth  脉冲电平时间                               
|       4   Out UINT *puDelay       延时信息                                   
|       5   Out UINT *puFilterWidth 滤波器宽度                                 
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetTriggerPulse(
    INT iCameraID,                          
    INT *piPulseStyle,               
    UINT *puPulseWidth,            
    UINT *puDelay,               
    UINT *puFilterWidth);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置闪光信号参数
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT iPulseStyle 闪光信号边缘极性                               
|	    3   In  UINT uPulseWidth    脉冲电平时间                               
|       4   In  UINT uDelay     延时信息                                       
|       
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetStrobePulse(
    INT iCameraID,            
    INT iPulseStyle,         
    UINT uPulseWidth,        
    UINT uDelay);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取闪光信号参数信息
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT *piPulseStyle   闪光信号边缘极性                           
|	    3   Out UINT *puPulseWidth	脉冲电平时间                               
|       4   Out UINT *puDelay       延时信息                                   
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetStrobePulse(
    INT iCameraID,                           
    INT *piPulseStyle,                 
    UINT *puPulseWidth,              
    UINT *puDelay);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置触发模式的曝光模式索引
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT iSel        曝光模式索引                                   
|
| 注  意：
|         无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetExposureSelForTrig(INT iCameraID, INT iSel);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取触发模式的曝光模式索引闪光信号参数信息
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT *piSel      曝光模式索引                                   
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetExposureSelForTrig(INT iCameraID, INT *piSel);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置图像采集的帧数（触发模式）
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  BYTE byCount    采集的帧数                                     
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetTriggerCount(INT iCameraID, BYTE byCount);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置分辨率模式（触发模式）
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT iSel        分辨率模式索引号                               
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetResolutionModeSelForTrig(INT iCameraID, INT iSel);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取分辨率模式（触发模式）
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT *piSel      分辨率模式索引号                               
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetResolutionModeSelForTrig(INT iCameraID, INT *piSel);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置预定义的图像尺寸（触发模式）
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT iSel        图像尺寸索引号                                 
|
| 注  意：
|       iSel对应tDSImageSize的iIndex成员
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetImageSizeSelForTrig(INT iCameraID, INT iSel);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取预定义的图像尺寸（触发模式）
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT *piSel      图像尺寸索引号                                 
|
| 注  意：
|       *piSel对应tDSImageSize的iIndex成员
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetImageSizeSelForTrig(INT iCameraID, INT *piSel);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置曝光时间（触发模式）
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  UINT64 uExpTime 曝光时间，单位：0.1us                          
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetExpTimeForTrig(INT iCameraID, UINT64 uExpTime);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取曝光时间（触发模式）
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out UINT64 *puExpTime       曝光时间，单位：0.1us                  
|       3   Out UINT64 *puExpTimeMax    最大曝光时间，单位：0.1us              
|       4   Out UINT64 *puExpTimeMin    最小曝光时间，单位：0.1us              
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetExpTimeForTrig(
    INT iCameraID,        
    UINT64 *puExpTime,        
    UINT64 *puExpTimeMax,    
    UINT64 *puExpTimeMin);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置曝光增益（触发模式）
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  float fGain 曝光增益，单位：倍数                               
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetAnalogGainForTrig(INT iCameraID, float fGain);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取曝光增益（触发模式）
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out float *pfGain   曝光增益，单位：倍数                           
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetAnalogGainForTrig(INT iCameraID, float *pfGain);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置分辨率模式（触发模式）
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  BOOL bROI       是否为ROI模式或预定义模式                      
|       3   In  INT iHOff       水平偏移量，单位：像素                         
|       4   In  INT iVOff       垂直偏移量，单位：像素                         
|       5   In  INT iWidth      图像宽度，单位：像素                           
|       6   In  INT iHeight     图像高度，单位：像素                           
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetImageSizeForTrig(
    INT iCameraID,                   
    BOOL bROI,                      
    INT iHOff,                    
    INT iVOff,                   
    INT iWidth,              
    INT iHeight);

/*--------------------------------------------------------------------------------------*\
| 功  能：获取分辨率模式（触发模式）
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out BOOL *pbROI     是否为ROI模式或预定义模式                      
|       3   Out INT *piHOff     水平偏移量，单位：像素                         
|       4   Out INT *piVOff     垂直偏移量，单位：像素                         
|       5   Out INT *piWidth    图像宽度，单位：像素                           
|       6   Out INT *piHeight   图像高度，单位：像素                           
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetImageSizeForTrig(
    INT iCameraID,                         
    BOOL *pbROI,                    
    INT *piHOff,                     
    INT *piVOff,
    INT *piWidth,           
    INT *piHeight);


/*--------------------------------------------------------------------------------------*\
| 功  能：写入相机序列号
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT iLevel      序列号级别                                     
|       3   In  BYTE *pbySN     序列号数据                                     
|       4   In  INT iSize       序列号字节数                                   
|       5   Out INT *piWritten  实际写入的字节数                               
|
| 注  意：
|       1、iLevel的值为 2：二级序列号，通过SDK只能写入二级序列号
|       2、序列号的字节数最大为：32字节
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraWriteSN(
    INT iCameraID,                   
    INT iLevel,               
    BYTE *pbySN,           
    INT iSize, 
    INT *piWritten);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取相机序列号
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT iLevel      序列号级别                                     
|       3   Out BYTE *pbySN     序列号数据                                     
|       4   In  INT iSize       序列号字节数                                   
|       5   Out INT *piReaded   实际获取的字节数                               
|
| 注  意：
|       1、iLevel的值为 1：一级序列号；2：二级序列号
|       2、序列号的字节数最大为：32字节
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraReadSN(
    INT iCameraID,       
    INT iLevel,          
    BYTE *pbySN,         
    INT iSize,            
    INT *piReaded);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取相机高级配置窗口
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out tPropertyPageInfo *psPageInfo  相机高级配置窗口信息            
|       3   In  BYTE byType     高级配置窗口类型                               
|
| 注  意：
|       byType的值为 0：设备逻辑配置窗口；1：图像处理模块窗口
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetPropertyPageInfo(
    INT iCameraID, 
    tDSPropertyPageInfo *psPageInfo, 
    BYTE byType);


/*--------------------------------------------------------------------------------------*\
| 功  能：显示相机高级配置窗口
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  HWND hwndDisplay    预览窗口句柄                               
|       3   In  BYTE byType         高级配置窗口类型                           
|
| 注  意：
|       byType的值为 0：设备逻辑配置窗口；1：图像处理模块窗口
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraShowSettingPage(INT iCameraID, HWND hwndDisplay, BYTE byType);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取SDK版本号
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  DWORD   adwVersion  SDK版本号            
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetSDKVersion(DWORD adwVersion[4]);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取用户自定义的GPIO输入口状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out USHORT *puGPIO  GPIO输入口状态(高低电平)                       
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetUserGPIOIn(INT iCameraID, USHORT *puGPIO);


/*--------------------------------------------------------------------------------------*\
| 功  能：获取用户自定义的GPIO输出口状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out USHORT *puGPIO  GPIO输出口状态(高低电平)                       
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetUserGPIOOut(INT iCameraID, USHORT *puGPIO);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置用户自定义的GPIO输出口状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  USHORT uGPIO    GPIO输出口状态(高低电平)                       
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetUserGPIOOut(INT iCameraID, USHORT uGPIO);


/*--------------------------------------------------------------------------------------*\
| 功  能：读GPIO输入口状态（高低电平）
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out USHORT *puGPIO  GPIO输入口状态(高低电平)                       
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetUserGPIOInEx(INT iCameraID, USHORT *uGPIO);


/*--------------------------------------------------------------------------------------*\
| 功  能：读GPIO口方向状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）              
|       2   Out USHORT *puGPIO  GPIO口方向状态(0表示输入，1表示输出)            
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetUserGPIODirEx(INT iCameraID, USHORT *uGPIO);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置GPIO口的方向
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  USHORT uGPIO    GPIO口方向状态(0表示输入，1表示输出)           
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetUserGPIODirEx(INT iCameraID, USHORT uGPIO);


/*--------------------------------------------------------------------------------------*\
| 功  能：设置GPIO口的模式
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT iMode       GPIO模式(0表示GPIO，1表示第二功能)             
|
| 注  意：
|       当GPIO的某个位不支持第二功能时，该设置无效
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetUserGPIOModeEx(INT iCameraID, INT iMode);

/*--------------------------------------------------------------------------------------*\
| 功  能：读GPIO口的模式
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT *piMode     GPIO模式(0表示GPIO，1表示第二功能)             
|
| 注  意：
|       当GPIO的某个位不支持第二功能时，该设置无效
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetUserGPIOModeEx(INT iCameraID, INT *piMode);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置外触发“快门/闪光灯”打开与关闭
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  BOOL bStrobOut  FALSE表示关闭，TRUE表示打开                    
|
| 注  意：
|       当GPIO的某个位不支持第二功能时，该设置无效
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetStrobeOutStateEx(INT iCameraID, BOOL bStrobeOut);

/*--------------------------------------------------------------------------------------*\
| 功  能：获取外触发“快门/闪光灯”打开与关闭的状态
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out BOOL *pbStrobOut FALSE表示关闭，TRUE表示打开                   
|
| 注  意：
|       当GPIO的某个位不支持第二功能时，该设置无效
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetStrobeOutStateEx(INT iCameraID, BOOL *pbStrobeOut);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置Gige相机的访问模式
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）                 
|       2   In  INT iMode   Gige相机访问模式 参考emDSGigeCameraMode定义	           
|
| 注  意：
|       无
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetGigeAccessMode(INT iCameraID, INT iMode);

/*--------------------------------------------------------------------------------------*\
| 功  能：获取Gige相机的访问模式
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT *piMode	    Gige相机访问模式                               
|
| 注  意：
|       
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetGigeAccessMode(INT iCameraID, INT *piMode);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置Gige相机图像数据报文的目标IP地址
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT iIP[4]  目标IP地址，iIP[0].iIP[1].iIP[2].iIP[3]	           
|
| 注  意：
|        
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetGigeFrameDestIP(INT iCameraID, INT iIP[4]);

/*--------------------------------------------------------------------------------------*\
| 功  能：获取Gige相机图像数据报文的目标IP地址
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT iIP[4]  目标IP地址，iIP[0].iIP[1].iIP[2].iIP[3]	           
|
| 注  意：
|       
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetGigeFrameDestIP(INT iCameraID, INT iIP[4]);

/*--------------------------------------------------------------------------------------*\
| 功  能：设置Gige相机的目标端口
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT iPort       Gige相机的目标端口                             
|
| 注  意：
|         
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetGigeFrameDestPort(INT iCameraID, INT iPort);

/*--------------------------------------------------------------------------------------*\
| 功  能：获取Gige相机的目标端口
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   Out INT *piPort     Gige相机的目标端口                 	           
|
| 注  意：
|       
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetGigeFrameDestPort(INT iCameraID, INT *piPort);

/*--------------------------------------------------------------------------------------*\
| 功  能：加入到组播组
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT iIP[4]  组播组ip，iIP[0].iIP[1].iIP[2].iIP[3]              
|
| 注  意：
|         
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGigeJoinMulticas(INT iCameraID, INT iIP[4]);

/*--------------------------------------------------------------------------------------*\
| 功  能：离开组播组
|
| 返回值：调用成功返回STATUS_OK，否则返回错误代码
|
| 参  数：
|       1   In  INT iCameraID   相机编号（由相机初始化成功后返回）             
|       2   In  INT iIP[4]  组播组ip，iIP[0].iIP[1].iIP[2].iIP[3]              
|
| 注  意：
|         
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGigeLeaveMulticas(INT iCameraID, INT iIP[4]);


#endif