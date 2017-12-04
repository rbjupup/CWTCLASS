/*-----------------------------------------------------------------------------*\
| ����:  ����DVP_CAMSDK.dll�ĺ����ӿ�                            
| ��Ȩ:  ��Ȩ����                                                     
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
| ��  �ܣ���ȡ����б�                                                     
|                                                                          
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                          
|                                                                          
| ��  ����                                                                 
|       1   Out tDSCameraDevInfo *pDSCameraList ���������Ϣ�׵�ַ  
|       2   Out INT              *piNums        �������            
|                                                                          
| ע  �⣺                                                                 
|         *piNumsΪ���ӱ���������ɷ��ʵ��������                          
\*----------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetDevList(tDSCameraDevInfo *pDSCameraList, INT *piNums);

/*----------------------------------------------------------------------------------*\
| ��  �ܣ���ʼ���������Ԥ��ͼ��                                     
|                                                                      
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                      
|                                                                      
| ��  ����                                                             
|       1   In  DS_SNAP_PROC pCallbackFunction  �ص�����ָ��                      
|       2   In  LPCSTR lpszFriendlyName     ����ǳ�                              
|       3   In  HWND hWndDisplay            ��ʾ���ھ��                         
|       4   Out INT *piCameraID             ������                              
|                                                                      
| ע  �⣺
|       1������ǳƴ�tDSCameraDevInfo�л�ȡ
|       2������ͷID��1��nΪ��ЧID��-n��0Ϊ��Ч��                     
|       3��ÿ����CameraInit�ɹ�һ�Σ�IDֵ��1�������ۼӣ�����ID�ظ��� 
\*----------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraInit(DS_SNAP_PROC pCallbackFunction, 
                                         LPCSTR lpszFriendlyName,
                                           HWND hWndDisplay,
                                            INT *piCameraID);


/*----------------------------------------------------------------------------------*\
| ��  �ܣ���ʼ�����������Ԥ��ͼ��                                     
|                                                                        
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                        
|                                                                        
| ��  ����                                                               
|       1   In  LPCSTR lpszFriendlyName ����ǳ�                                         
|       2   Out INT *piCameraID         ������                                         
|                                                                     
| ע  �⣺
|       1������ǳƴ�tDSCameraDevInfo�л�ȡ
|       2������ͷID��1��nΪ��ЧID��-n��0Ϊ��Ч��                      
|       3��ÿ����CameraInitEx�ɹ�һ�Σ�IDֵ��1�������ۼӣ�����ID�ظ��� 
\*---------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraInitEx(LPCSTR lpszFriendlyName, INT *piCameraID);


/*---------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ����豸������Χ                                                       
|                                                                                  
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                                     
|                                                                                  
| ��  ����                                                                          
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�              
|       2   Out tDSCameraCap &sDSCameraCap  ����豸������Χ�ṹ               
|                                                                                  
| ע  �⣺                                                                          
|       �������ɻ�ȡ�����ز�������ֵ��Χ��Ĭ��ֵ                                                                        
\*---------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetCapability(
    INT iCameraID,
    tDSCameraCapability &sDSCameraCap);


/*---------------------------------------------------------------------------------*\
| ��  �ܣ�����ʼ�����                                                 
|                                                                     
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                       
|                                                                     
| ��  ����                                                            
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�              
|                                                                     
| ע  �⣺                                                            
|       �����ͷ��ڴ����ռ䣬�����ڳ����˳�ǰ����                     
\*--------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraUnInit(INT iCameraID);


/*--------------------------------------------------------------------------------*\
| ��  �ܣ�����Ƶ��                                                    
|                                                                     
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                        
|                                                                     
| ��  ����                                                            
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�              
|                                                                      
| ע  �⣺                                                             
|       ��                                                           
\*--------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraPlay(INT iCameraID);


/*--------------------------------------------------------------------------------*\
| ��  �ܣ���ͣ��Ƶ��                                                   
|                                                                     
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                        
|                                                                     
| ��  ����                                                            
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�              
|                                                                     
| ע  �⣺                                                            
|       ��                                                          
\*--------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraPause(INT iCameraID);


/*--------------------------------------------------------------------------------*\
| ��  �ܣ�ֹͣ��Ƶ��                                                  
|                                                                    
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                       
|                                                                    
| ��  ����                                                           
|       1   In  INT iCameraID  �����ţ��������ʼ���ɹ��󷵻أ�              
|                                                                    
| ע  �⣺                                                           
|       ��                                                         
\*--------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraStop(INT iCameraID);


/*--------------------------------------------------------------------------------*\
| ��  �ܣ��������                                                  
|                                                                    
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                       
|                                                                    
| ��  ����                                                           
|       1   In  INT iCameraID  �����ţ��������ʼ���ɹ��󷵻أ�              
|		2   In  UINT uRestartType ��������                                     
|                                                                    
| ע  �⣺                                                           
|        ���ͬʱ����sensor�ͻ����������"SENSOR_RESTART|BUFFER_RESTART"
\*-------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraRestart(INT iCameraID, UINT uRestartType);


/*-------------------------------------------------------------------------------*\
| ��  �ܣ��������Դ                                                 
|                                                                     
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                       
|                                                                     
| ��  ����                                                            
|       1   In  INT iCameraID  �����ţ��������ʼ���ɹ��󷵻أ�               
|                                                                     
| ע  �⣺                                                            
|       ��                                                          
\*-------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraPowerUp(INT iCameraID);


/*-------------------------------------------------------------------------------*\
| ��  �ܣ��ر������Դ                                                 
|                                                                     
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                       
|                                                                     
| ��  ����                                                            
|       1   In  INT  iCameraID  �����ţ��������ʼ���ɹ��󷵻أ�               
|                                                                     
| ע  �⣺                                                            
|       ��                                                          
\*-------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraPowerDown(INT iCameraID);


/*-------------------------------------------------------------------------------*\
| ��  �ܣ�ͼ�����ݴ���                                                            
|                                                                                
| ����ֵ�����óɹ�����RGB24ͼ�������׵�ַ�����򷵻�NULL                             
|                                                                                
| ��  ����                                                                       
|       1   In  INT iCameraID   �����ţ��ص�����          ��                          
|       2   In  BYTE *pbyRAW    ͼ�������׵�ַ���ص���������                          
|       3   In  tDSFrameInfo *psFrInfo ͼ��֡������Ϣ���μ�tDSFrameInfo����           
|                                                                                
| ע  �⣺                                                                       
|       ��                                                                     
\*-------------------------------------------------------------------------------*/
DS_API BYTE* CameraISP(INT iCameraID, BYTE *pbyRAW, tDSFrameInfo *psFrInfo);


/*-------------------------------------------------------------------------------*\
| ��  �ܣ�RAWתRGB�㷨ѡ��                                                            
|                                                                                
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                             
|                                                                                
| ��  ����                                                                       
|       1   In  INT iCameraID       ����ͷID���ص���������                     
|       2   In  INT	iRawToRGBType   RAWתRGB�㷨���                           
|                                                                                
| ע  �⣺                                                                       
|       ��                                                                     
\*-------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetBayertoRGBType(INT iCameraID, INT iRawToRGBType);


/*-------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ��ǰRAWתRGB�㷨���                                                            
|                                                                                
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                            
|                                                                                
| ��  ����                                                                       
|       1   In  INT iCameraID   ����ͷID���ص���������                         
|       2   In  INT *piRawToRGBType RAWתRGB�㷨���                           
|                                                                                
| ע  �⣺                                                                       
|       ��                                                                     
\*--------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetBayertoRGBType(INT iCameraID, INT *piRawToRGBType);


/*--------------------------------------------------------------------------------*\
| ��  �ܣ���ʾRGB24λͼ������                                                        
|                                                                                   
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                                     
|                                                                                   
| ��  ����                                                                          
|       1   In  INT  iCameraID  �����ţ��ص�����          ��                              
|       2   In  BYTE *pbyRGB24  RGB24ͼ�������׵�ַ                                      
|       3   In  tDSFrameInfo *psFrInfo  ͼ��������ϸ��Ϣ���μ�tDSFrameInfo����            
|                                                                                   
| ע  �⣺                                                                          
|       ��                                                                        
\*--------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraDisplayRGB24(
    INT iCameraID, 
    BYTE *pbyRGB24, 
    tDSFrameInfo *psFrInfo);


/*----------------------------------------------------------------------------*\
| ��  �ܣ���ʾROI����ѡ���                                             
|                                                                      
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                        
|                                                                      
| ��  ����                                                             
|       1   In  INT iCameraID   �����ţ��ص�����          ��                
|       2   In  tDSROISize sROISize ROI����ѡ���λ�úͳߴ�                 
|                                                                      
| ע  �⣺                                                             
|         ��                                                           
\*----------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraDisplayROISel(INT iCameraID, tDSROISize sROISize);


/*----------------------------------------------------------------------------*\
| ��  �ܣ�����Ԥ��ͼ��ߴ�                                                 
|                                                                        
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                           
|                                                                        
| ��  ����                                                                
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�                 
|       2   In  INT iWidth      Ԥ��ͼ����                                                            
|       3   In  INT iHeight     Ԥ��ͼ��߶�                                                            
|                                                                        
| ע  �⣺                                                                
|         ��                                                              
\*----------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetDisplaySize(
    INT iCameraID,             
    INT iWidth,                
    INT iHeight);


/*----------------------------------------------------------------------------*\
| ��  �ܣ�����¼Ӱ����                                                       
|                                                                           
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                             
|                                                                           
| ��  ����                                                                  
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�              
|       2   In  LPCSTR lpszFileName  ��Ƶ�ļ���·��������                             
|                                                                           
| ע  �⣺                                                                  
|       ��                                                                
\*----------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraStartRecordVideo(INT iCameraID, LPCSTR lpszFileName);


/*----------------------------------------------------------------------------*\
| ��  �ܣ�����¼Ӱ���ܣ����Զ�����������ʱ�䵽¼Ӱ�ļ���                                                     
|                                                                           
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                             
|                                                                           
| ��  ����                                                                  
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�              
|       2   In  LPCSTR lpszFileName  ��Ƶ�ļ���·��������                             
|                                                                           
| ע  �⣺                                                                  
|       ��                                                                
\*----------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraStartRecordVideoEx(INT iCameraID, LPCSTR lpszFileName);

/*----------------------------------------------------------------------------*\
| ��  �ܣ�ֹͣ¼Ӱ����                                                  
|                                                                      
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                        
|                                                                      
| ��  ����                                                             
|       1   In  INT iCameraID  �����ţ��������ʼ���ɹ��󷵻أ�              
|                                                                      
| ע  �⣺                                                             
|       ��                                                           
\*----------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraStopRecordVideo(INT iCameraID);


/*----------------------------------------------------------------------------*\
| ��  �ܣ�������Ƶ�ļ����ռ�ÿռ�                                      
|                                                                     
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                        
|                                                                     
| ��  ����                                                            
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�	             
|       2   In  INT iFileSize   ��Ƶ�ļ����ռ�ÿռ䣬��λ��Mega BYTE           
|                                                                     
| ע  �⣺                                                            
|       ¼��ʱ�����ļ��ﵽ���õ����ռ�ÿռ䣬�������µ���Ƶ�ļ�       
\*---------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetRecordFileSize(INT iCameraID, INT iFileSize);


/*---------------------------------------------------------------------------*\
| ��  �ܣ���ȡ��Ƶ�ļ������ռ�ÿռ�                                      
|                                                                       
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                         
|                                                                       
| ��  ����                                                              
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�                  
|       2   Out INT *piFileSize ��Ƶ�ļ����ռ�ÿռ䣬��λ��Mega BYTE              
|                                                                       
| ע  �⣺                                                              
|       ��                                                            
\*---------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetRecordFileSize(INT iCameraID, INT *piFileSize);


/*---------------------------------------------------------------------------*\
| ��  �ܣ�������Ƶ�ļ���ͼ������                                        
|                                                                     
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                        
|                                                                     
| ��  ����                                                            
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�              
|       2   In  INT iQuality    ��Ƶ�ļ���ͼ������                             
|                                                                     
| ע  �⣺                                                            
|       iQuality ֵΪ 1���͵�������2���е�������3���ߵ�����            
\*---------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetRecordAVIQuality(INT iCameraID, INT iQuality);


/*---------------------------------------------------------------------------*\
| ��  �ܣ���ȡ��Ƶ�ļ���ͼ������                                         
|                                                                      
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                         
|                                                                      
| ��  ����                                                             
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�              
|       2   Out INT *piQuality  ��Ƶ�ļ���ͼ������                             
|                                                                      
| ע  �⣺                                                             
|       *piQuality ֵΪ 1���͵�������2���е�������3���ߵ�����           
\*---------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetRecordAVIQuality(INT iCameraID, INT *piQuality);


/*---------------------------------------------------------------------------*\
| ��  �ܣ�������Ƶ�ļ���ͼ��ѹ��������                                  
|                                                                     
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                       
|                                                                     
| ��  ����                                                            
|       1   In  INT iCameraID  �����ţ��������ʼ���ɹ��󷵻أ�              
|       2   In  INT iCodeType  ��Ƶ�ļ���ͼ��ѹ��������                       
|                                                                     
| ע  �⣺                                                            
|       iCodeType ֵΪ 1��MPEG4��                                   
\*--------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetRecordEncoder(INT iCameraID, INT iCodeType);


/*--------------------------------------------------------------------------*\
| ��  �ܣ���ȡ��Ƶ�ļ���ͼ��ѹ��������                                    
|                                                                       
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                         
|                                                                       
| ��  ����                                                              
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT *piCodeType ��Ƶ�ļ���ͼ��ѹ��������                      
|                                                                       
| ע  �⣺                                                              
|       *piCodeType ֵΪ 1��MPEG4��                                   
\*--------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetRecordEncoder(INT iCameraID, INT *piCodeType);


/*--------------------------------------------------------------------------*\
| ��  �ܣ���ȡ¼Ӱ��֡��                                                 
|                                                                       
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                         
|                                                                       
| ��  ����                                                              
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�            
|       2   Out float *pfRate ¼Ӱ��֡�ʣ���λ��FPS                          
|                                                                       
| ע  �⣺                                                              
|       ��                                                            
\*--------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetRecordRate(INT iCameraID, float *pfRate);


/*-----------------------------------------------------------------------------------*\
| ��  �ܣ���ͼ������д����Ƶ�ļ�                                                     
|                                                                                  
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                                     
|                                                                                  
| ��  ����                                                                         
|       1   In  INT iCameraID   �����ţ��ص�����          ��                               
|       2   In  BYTE *pbyRGB    RGB24λͼ�������׵�ַ                                     
|       3   In  tDSFrameInfo *psFrInfo ͼ��������ϸ��Ϣ���μ�tDSFrameInfo����             
|                                                                                  
| ע  �⣺                                                                         
|       ��                                                                       
\*-----------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraRecordFrame(
    INT iCameraID,             
    BYTE *pbyRGB,       
    tDSFrameInfo *psFrInfo);


/*-----------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ���ͼ�������׵�ַ                                                   
|                                                                                
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                                   
|                                                                                
| ��  ����                                                                       
|       1   In  INT iCameraID    �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  emDSDataType emDataType ͼ����������                           
|       3   Out BYTE **pbyBuffer        ͼ�������׵�ַ                         
|                                                                                
| ע  �⣺                                                                       
|       1��emDataType�ο�emDSDataTypeö������
|       2�����emDataType����֧�ַ�Χ��������ΪSTATUS_PARAMETER_INVALID
|       3����CameraReleaseImageBuffer���ʹ��      
|       4��ֻ��ʹ��CameraInitEx��ʼ�����ʱʹ�ã�����᷵��STATUS_NOT_SUPPORTED
\*-----------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetImageBuffer(
    INT iCameraID,     
    emDSDataType emDataType, 
    BYTE **pbyBuffer);


/*--------------------------------------------------------------------------------------------*\
| ��  �ܣ��ͷ����ͼ�������׵�ַ                                                            
|                                                                                         
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                                            
|                                                                                         
| ��  ����                                                                                
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�                        
|       2   In  emDSDataType emDataType ͼ����������                                    
|       3   In  BYTE *pbyBuffer         ͼ�������׵�ַ                                   
|                                                                                         
| ע  �⣺                                                                                
|       1��emDataType�ο�emDSDataTypeö������                                            
|       2����CameraGetImageBuffer���ʹ�ã�pbyBufferָ������ݴ�����ɣ�����ô˽ӿ��ͷ�����
|       3��CameraReleaseImageBuffer���������ͱ�����CameraGetImageBuffer��һ��              
\*--------------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraReleaseImageBuffer(
    INT iCameraID,                         
    emDSDataType emDataType,         
    BYTE *pbyBuffer);


/*------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ���֡��ͳ����Ϣ                                                        
|                                                                                   
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                                      
|                                                                                   
| ��  ����                                                                           
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�              
|       2   Out DSFrameCount *psFrameCount  ֡��ͳ����Ϣ                      
|                                                                                   
| ע  �⣺                                                                           
|       ��                                                                        
\*------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetFrameCount(INT iCameraID, tDSFrameCount *psFrameCount);


/*---------------------------------------------------------------------------------*\
| ��  �ܣ����������ǰͼ�����ݵ�ָ���ļ�                                           
|                                                                               
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                                  
|                                                                               
| ��  ����                                                                       
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�                  
|       2   In  LPCSTR lpszFileName ͼ���ļ�·��������                             
|       3   In  BYTE byFileType     ͼ���ļ�����                                   
|       4   In  BYTE byQuality      JPEG����ͼ���ļ���ͼ������                      
|                                                                               
| ע  �⣺                                                                       
|       1��byFileType�ο�emDSFileTypeö�����ͣ��Ը�ֵ�������㣬���ɱ���������ļ� 
|       2��byQualityֻ��JPEG��������Ч����Χ��1~100������������������ֵ��
\*---------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraCaptureFile(
    INT iCameraID,                    
    LPCSTR lpszFileName,         
    BYTE byFileType,          
    BYTE byQuality);

/*---------------------------------------------------------------------------------*\
| ��  �ܣ����������ǰͼ�����ݵ�ָ���ļ�,����ROI��ͼ������������ӿ�                                           
|                                                                               
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                                  
|                                                                               
| ��  ����                                                                       
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�                  
|       2   In  LPCSTR lpszFileName    ͼ���ļ�·��������                          
|       3   In  BYTE byFileType  ͼ���ļ�����                                      
|       4   In  BYTE byQuality   JPEG����ͼ���ļ���ͼ������                         
|                                                                               
| ע  �⣺                                                                       
|       1��byFileType�ο�emDSFileTypeö�����ͣ��Ը�ֵ�������㣬���ɱ���������ļ��� 
|       2��byQualityֻ��JPEG��������Ч����Χ��1~100������������������ֵ��
|       3����CameraCaptureFile���ݣ����ӱ���ROIģʽͼ�����ݹ��ܡ�
\*---------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraCaptureFileEx(
    INT iCameraID,           
    LPCSTR lpszFileName,   
    BYTE byFileType,    
    BYTE byQuality);

/*---------------------------------------------------------------------------------*\
| ��  �ܣ� ץȡһ֡ͼ�񵽻��������ߴ�������Ϊ��׽�ķֱ��ʾ���                                           
|                                                                               
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                                  
|                                                                               
| ��  ����                                                                       
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�                  
|       2   In  BYTE *pbyData	����ͼ�����ݵĻ�����ָ��                        
|		3	Out tDSFrameInfo *psFrameInfo   ͼ�����ݻ�����Ϣ	               
|       4   In  emDSDataType emDataType     ��������                                
|                                                                               
| ע  �⣺                                                                       
|       1��emDataType�ο�emDSDataType���壬Ŀǰ֧��RAW���ݺ�RGB24���͡�
\*---------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraCaptureDataEx(
    INT iCameraID,         
    BYTE *pbyData,       
    tDSFrameInfo	*psFrameInfo, 
    emDSDataType emDataType);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����RGB24λͼ�����ݵ�BMP�ļ�                                                  
|                                                                                     
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������                                        
|                                                                                     
| ��  ����                                                                             
|       1   In  INT iCameraID   �����ţ��ص�����          ��                             
|       2   In  LPCSTR  lpszFileName  ͼ���ļ�·��������                                
|       3   In  BYTE    *pbyRGB24     RGB24λͼ�������׵�ַ                             
|       4   In  tDSFrameInfo *psFrInfo ͼ��������ϸ��Ϣ���μ�tDSFrameInfo����            
|                                                                                     
| ע  �⣺                                                                             
|       ��                                                                          
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSaveBMPFile(
    INT iCameraID,       
    LPCSTR lpszFileName,  
    BYTE *pbyRGB24, 
    tDSFrameInfo *psFrInfo);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ���ͼ�����ݻ���
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  BYTE *pbyImageBuffer  ���ͼ�����ݻ����׵�ַ                   
|       3   In  emDSDataType emDataType  ���ͼ����������                      
|       4   In  tDSFrameInfo &sFrInfo    ��֡ͼ�����ݵĻ�����Ϣ                
|
| ע  �⣺
|       1��10λ��12λ��16λ��ͼ�����ݾ�����16λ����2�ֽڣ��洢��
|       2��16λ���ݵ����з�ʽ�ǡ�Little-Endian��������λ������ǰ�ֽڣ���λ�����ں��ֽڣ�
|       3��ͼ���ȡ��߶Ⱥ�����λ�������ڡ�&sFrInfo���л�ã�
|       4��ͼ���������ֽ��� = ͼ���� X ͼ��߶� X ÿ�����ֽ�����
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetImageData(
    INT iCameraID,        
    BYTE *pbyImageBuffer, 
    emDSDataType emDataType, 
    tDSFrameInfo &sFrInfo);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ����浱ǰ��ʾͼ��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  LPCSTR lpFileName      ͼ���ļ���·��������                    
|       3   In  BYTE *pbyImageBuffer ͼ�����ݻ����׵�ַ                        
|       4   In  tDSFrameInfo  *psFrInfo ͼ�����ݵ�֡��Ϣ                       
|       5   In  BYTE byFileType      ͼ���ļ�����                              
|       6   In  BYTE byQuality       JPEG����ͼ���ļ���ͼ������                
|
| ע  �⣺
|       1��byQualityֻ��JPEG��������Ч����Χ��1~100������������������ֵ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSaveCurrentImage(
    INT iCameraID,          
    LPCSTR lpszFileName,    
    BYTE *pbyImageBuffer,    
    tDSFrameInfo *psFrInfo,   
    BYTE byFileType,            
    BYTE byQuality);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����ͼ��ת״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID  �����ţ��������ʼ���ɹ��󷵻أ�                      
|       2   In  emDSMirrorDirection  emDir  ͼ��ת�����ʶ��ˮƽ��ֱ��             
|       3   In  BOOL bEnable   ͼ��ת״̬                                            
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetMirror(INT iCameraID, emDSMirrorDirection emDir, BOOL bEnable);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡͼ��ת״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID  �����ţ��������ʼ���ɹ��󷵻أ�                      
|       2   In  emDSMirrorDirection  emDir  ͼ��ת�����ʶ��ˮƽ��ֱ��             
|       3   Out BOOL *pbEnable  ͼ��ת״̬                                           
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetMirror(INT iCameraID, emDSMirrorDirection emDir, BOOL *pbEnable);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����ͼ��ѡ��״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT	iRotation   ͼ����ת����                                   
|
| ע  �⣺
|      ��ת�������壺	0:δ��ת 1:˳ʱ����ת90�� 2:��ʱ����ת90��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetRotation(INT iCameraID, INT iRotation);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡͼ��ѡ��״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT	*piRotation	ͼ����ת����                                   
|
| ע  �⣺
|       ��ת�������壺	0:����ת 1:˳ʱ����ת90�� 2:��ʱ����ת90��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetRotation(INT iCameraID, INT *piRotation);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����ͼ��ɫ״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  BOOL bEnable    ͼ��ɫ״̬                                   
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetMonochrome(INT iCameraID, BOOL bEnable);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡͼ��ɫ״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out BOOL *pbEnable  ͼ��ɫ״̬                                   
|
| ע  �⣺
|        ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetMonochrome(INT iCameraID, BOOL *pbEnable);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����ͼ��ɫ״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  BOOL bEnable ͼ��ɫ״̬                                      
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetInverse(INT iCameraID, BOOL bEnable);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡͼ��ɫ״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID  �����ţ��������ʼ���ɹ��󷵻أ�              
|       2   Out BOOL *pbEnable ͼ��ɫ״̬                                    
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetInverse(INT iCameraID, BOOL *pbEnable);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ������Զ��ع�״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  BOOL bState     �Զ��ع�״̬                                   
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetAeState(INT iCameraID, BOOL bState);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ�Զ��ع�״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out BOOL *pbAeState �Զ��ع�״̬                                   
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetAeState(INT iCameraID, BOOL *pbAeState);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ������Զ��ع�Ŀ��ֵ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  BYTE byAeTarget �Զ��ع�Ŀ��ֵ                                 
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetAeTarget(INT iCameraID, BYTE byAeTarget);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ�Զ��ع�Ŀ��ֵ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out BYTE *pbyAeTarget    �Զ��ع�Ŀ��ֵ                            
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetAeTarget(INT iCameraID, BYTE *pbyAeTarget);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ������Զ��ع�ο�����
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT iHOff       ˮƽƫ��������λ������                         
|       3   In  INT iVOff       ��ֱƫ��������λ������                         
|       4   In  INT iWidth      �ο������ȣ���λ������                       
|       5   In  INT iHeight     �ο�����߶ȣ���λ������                       
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetAEWindow(
    INT iCameraID,                    
    INT iHOff,            
    INT iVOff,            
    INT iWidth,         
    INT iHeight);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ������ع�ʱ��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  UINT64  uExposureTime  �ع�ʱ�䣬��λ��0.1us                   
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetExposureTime(INT iCameraID, UINT64 uExposureTime);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ�ع�ʱ��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out UINT64  *puExposureTime  �ع�ʱ�䣬��λ��0.1us                 
|       3   Out UINT64  *puExpTimeMax    �ع�ʱ�����ֵ����λ��0.1us           
|       4   Out UINT64  *puExpTimeMin    �ع�ʱ����Сֵ����λ��0.1us           
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetExposureTime(
    INT iCameraID,          
    UINT64 *puExposureTime,     
    UINT64 *puExpTimeMax,      
    UINT64 *puExpTimeMin);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ������Զ��ع�ģʽ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT	iMode       �ع�ģʽ���                                   
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetAeMode(INT iCameraID, INT iMode);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ�Զ��ع�ģʽ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT	*piMode		�ع�ģʽ���                                   
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetAeMode(INT iCameraID, INT *piMode);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ������Զ��ع��㷨
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT iScheme	    �Զ��ع��㷨���                               
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetAeScheme(INT iCameraID, INT iScheme);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ�Զ��ع��㷨
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT	*piScheme	�Զ��ع��㷨���                               
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetAeScheme(INT iCameraID, INT *piScheme);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ������ع�����
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  float fAnalogGain �ع�����ֵ����λ������                       
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetAnalogGain(INT iCameraID, float fAnalogGain);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ�ع�����
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out float *pfAnalogGain   �ع�����ֵ����λ������                   
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetAnalogGain(INT iCameraID, float *pfAnalogGain);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���������ͼ���ӵ�״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  BOOL bEnable    ����ͼ���ӵ�״̬                               
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetDeadPixelCorrectionState(INT iCameraID, BOOL bEnable);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ����ͼ���ӵ�״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out BOOL *pbEnable  ����ͼ���ӵ�״̬                               
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetDeadPixelCorrectionState(INT iCameraID, BOOL *pbEnable);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����ͼ���ӵ�λ������
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|
| ע  �⣺
|       �������ر𻷾�ʱ���������������ӵ�λ������
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraCreateDefectCorrectionInfo(INT iCameraID);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����ͼ����״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  BOOL bEnable    ͼ����״̬                                   
|
| ע  �⣺
|        ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetEdgeEnhance(INT iCameraID, BOOL bEnable);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡͼ����״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out BOOL *pbEnable  ͼ����״̬                                   
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetEdgeEnhance(INT iCameraID, BOOL *pbEnable);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����ͼ����Ŀ��ֵ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  BYTE byEdgeGain ͼ����Ŀ��ֵ                                 
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetEdgeGain(INT iCameraID, BYTE byEdgeGain);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡͼ����Ŀ��ֵ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out BYTE *pbyEdgeGain    ͼ����Ŀ��ֵ                            
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetEdgeGain(INT iCameraID, BYTE *pbyEdgeGain);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����ͼ����״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  BOOL bReduction ͼ����״̬                                   
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetNoiseReductionState(INT iCameraID, BOOL bReduction);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡͼ����״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out BOOL    *pbReduction    ͼ����״̬                           
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetNoiseReductionState(INT iCameraID, BOOL *pbReduction);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����ͼ����Ŀ��ֵ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT iReduction  ͼ����Ŀ��ֵ                                 
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetNoiseReduction(INT iCameraID, INT iReduction);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡͼ����Ŀ��ֵ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT *piReduction    ͼ����Ŀ��ֵ                             
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetNoiseReduction(INT iCameraID, INT *piReduction);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����ͼ��3D����״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  BOOL b3DReduction  ͼ��3D����״̬                              
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSet3DNoiseReductionState(INT iCameraID, BOOL b3DReduction);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡͼ��3D����״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out BOOL *pb3DReduction  ͼ��3D����״̬                            
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGet3DNoiseReductionState(INT iCameraID, BOOL *pb3DReduction);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����ͼ��3D����Ŀ��ֵ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT i3DReduction    ͼ��3D����Ŀ��ֵ                           
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSet3DNoiseReduction(INT iCameraID, INT i3DReduction);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡͼ��3D����Ŀ��ֵ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT *pi3DReduction  ͼ��3D����Ŀ��ֵ                           
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGet3DNoiseReduction(INT iCameraID, INT *pi3DReduction);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�һ���԰�ƽ�⹦��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetOnceWB(INT iCameraID);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ�Զ���ƽ���Ƿ����
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID       �����ţ��������ʼ���ɹ��󷵻أ�   
|       2   Out BOOL *pbAvailabe    �Զ���ƽ���Ƿ����             
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraIsAWBAvailable(INT iCameraID, BOOL *pbAvailabe);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ������Զ���ƽ��״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  BOOL bAWBState  �Զ���ƽ��״̬                                 
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetAWBState(INT iCameraID, BOOL bAWBState);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ�Զ���ƽ��״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out BOOL *pbAWBState �Զ���ƽ��״̬                                
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetAWBState(INT iCameraID, BOOL *pbAWBState);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ����ð�ƽ��ο�����
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT iHOff       ˮƽƫ��������λ������                         
|       3   In  INT iVOff       ��ֱƫ��������λ������                         
|       4   In  INT iWidth      �ο������ȣ���λ������                       
|       5   In  INT iHeight     �ο�����߶ȣ���λ������                       
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetWBWindow(INT iCameraID, 
                                          INT iHOff, 
                                          INT iVOff, 
                                          INT iWidth, 
                                          INT iHeight);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����һ�κڵ�ƽ�Զ�����
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraBlackLevelOnce(INT iCameraID);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ����úڵ�ƽ����ʹ��״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�                  
|       2   In  BOOL bBlackLevel �ڵ�ƽʹ��״̬ TRUE��ʹ�ܣ�FALSE��ȡ��             
|
| ע  �⣺
|         ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetBlackLevelState(INT iCameraID, BOOL bBlackLevel);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ�ڵ�ƽ����ʹ��״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out BOOL    *pbBlackLevel   �ڵ�ƽʹ��״̬                         
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetBlackLevelState(INT iCameraID, BOOL *pbBlackLevel);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ����úڵ�ƽ����
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT iLevelForR  ��ɫ�����ڵ�ƽ                                 
|       3   In  INT iLevelForG  ��ɫ�����ڵ�ƽ                                 
|       4   In  INT iLevelForB  ��ɫ�����ڵ�ƽ                                 
|       5   In  INT iMaxValue   �������ֵ                                     
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetBlackLevel(INT iCameraID, 
											INT iLevelForR,
											INT iLevelForG,
											INT iLevelForB,
											INT iMaxValue=4095);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ�ڵ�ƽ����
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT *piLevelForR    ��ɫ�����ڵ�ƽ                             
|       3   Out INT *piLevelForG    ��ɫ�����ڵ�ƽ                             
|       4   Out INT *piLevelForB    ��ɫ�����ڵ�ƽ                             
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetBlackLevel(INT iCameraID, 
											INT *piLevelForR,
											INT *piLevelForG,
											INT *piLevelForB);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ����ø�ɫ��ͨ��������
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  float fRGain    ��ͨ������                                     
|       3   In  float fGGain    ��ͨ������                                     
|       4   In  float fBGain    ��ͨ������                                     
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetGain(
    INT iCameraID,  
    float fRGain,   
    float fGGain,    
    float fBGain);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ��ɫ��ͨ��������
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID  �����ţ��������ʼ���ɹ��󷵻أ�              
|       2   Out float *pfRGain ��ͨ������                                      
|       3   Out float *pfGGain ��ͨ������                                      
|       4   Out float *pfBGain ��ͨ������                                      
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetGain(
    INT iCameraID,         
    float *pfRGain,     
    float *pfGGain,    
    float *pfBGain);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����ɫ�ʱ��Ͷ�״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  BOOL  bEnable   ɫ�ʱ��Ͷ�״̬                                 
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetColorEnhancement(INT iCameraID, BOOL bEnable);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡɫ�ʱ��Ͷ�״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out BOOL    *pbEnable ɫ�ʱ��Ͷ�״̬                               
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetColorEnhancement(INT iCameraID, BOOL *pbEnable);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����ɫ�ʱ��Ͷ�ֵ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  BYTE    bySaturation    ɫ�ʱ��Ͷ�ֵ                           
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetSaturation(INT iCameraID, BYTE bySaturation);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡɫ�ʱ��Ͷ�ֵ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out BYTE    *pbySaturation  ɫ�ʱ��Ͷ�ֵ                           
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetSaturation(INT iCameraID, BYTE *pbySaturation);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����٤�����ʹ��״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  BOOL    bGamma  ٤��ʹ��״̬ TRUE�����ܣ�FALSE��ȡ��           
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetGammaState(INT iCameraID, BOOL bGamma);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ٤�����ʹ��״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out BOOL *pbGamma   ٤��ʹ��״ָ̬��                               
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetGammaState(INT iCameraID, BOOL *pbGamma);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����٤��ֵ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  BYTE byGamma    ٤��ֵ                                         
|
| ע  �⣺
|         ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetGamma(INT iCameraID, BYTE byGamma);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ٤��ֵ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out BYTE *pbyGamma  ٤��ֵ                                         
|
| ע  �⣺
|         ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetGamma(INT iCameraID, BYTE *pbyGamma);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ����öԱȶȵ���ʹ��״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�                 
|       2   In  BOOL bContrast  �Աȶ�ʹ��״̬ TRUE��ʹ�ܣ�FALSE��ȡ��             
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetContrastState(INT iCameraID, BOOL bContrast);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ�Աȶȵ���ʹ��״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out BOOL    *pbContast �Աȶ�ʹ��״ָ̬��                          
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetContrastState(INT iCameraID, BOOL *pbContrast);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ����öԱȶ�ֵ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  BYTE    byContrast  �Աȶ�ֵ                                   
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetContrast(INT iCameraID, BYTE byContrast);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ�Աȶ�ֵ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out BYTE *pbyContrast   �Աȶ�ֵ                                   
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetContrast(INT iCameraID, BYTE *pbyContrast);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����֡��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  emDSFrameSpeed  emFrameSpeed  ֡��                             
|
| ע  �⣺
|       emFrameSpeed�ο�emDSFrameSpeedö������
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetFrameSpeed(INT iCameraID, emDSFrameSpeed emFrameSpeed);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ֡��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out emDSFrameSpeed  *pemFrameSpeed  ֡��                           
|
| ע  �⣺
|         emFrameSpeed�ο�emDSFrameSpeedö������
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetFrameSpeed(INT iCameraID, emDSFrameSpeed *pemFrameSpeed);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ����ÿ�Ƶ��״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  BOOL    bEnable ��Ƶ��״̬                                     
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetAntiFlick(INT iCameraID, BOOL bEnable);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ��Ƶ��״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out BOOL    *pbEnable   ��Ƶ��״̬                                 
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetAntiFlick(INT iCameraID, BOOL *pbEnable);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ����ÿ�Ƶ������
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�                 
|       2   In  emDSLightFrequency  emFrequency  ��Ƶ���������ƹ�Ƶ�ʣ�            
|
| ע  �⣺
|         ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetLightFrequency(INT iCameraID, emDSLightFrequency emFrequency);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ��Ƶ������
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�                  
|       2   Out emDSLightFrequency  *pemFrequency  ��Ƶ���������ƹ�Ƶ�ʣ�           
|
| ע  �⣺
|         ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetLightFrequency(INT iCameraID, emDSLightFrequency *pemFrequency);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ��������Ԥ����ķֱ���ģʽ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT iSel        Ԥ����ķֱ���������                           
|       3   In  BOOL bCapture   Ԥ��������ģʽ�ķֱ���                         
|
| ע  �⣺
|       1�����֧�ֵ�Ԥ����ֱ���ģʽͨ������CameraGetCapability��ȡ
|       2��bCaptureΪTRUEʱ��������ģʽ�ķֱ��ʣ���������Ԥ��ģʽ�ķֱ���
|       3��ʹ�øú�������������ķֱ��ʺ�����ú���CameraPlay��������Ƶ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetImageSizeSel(INT iCameraID, INT iSel, BOOL bCapture = FALSE);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ���Ԥ����ķֱ���ģʽ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT *piSel      Ԥ����ķֱ���������                           
|       3   In  BOOL bCapture   Ԥ��������ģʽ�ķֱ���                         
|
| ע  �⣺
|         1��bCaptureΪTRUEʱ��ȡ����ģʽ�ķֱ��ʣ������ȡԤ��ģʽ�ķֱ���
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetImageSizeSel(INT iCameraID, INT *piSel, BOOL bCapture = FALSE);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���������ķֱ���ģʽ��ROI��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  BOOL bReserve   ������������δ����			                   
|       3   In  INT iHOff       ˮƽƫ��������λ������                         
|       4   In  INT iVOff       ��ֱƫ��������λ������                         
|       5   In  INT iWidth      �����ȣ���λ������                           
|       6   In  INT iHeight     ����߶ȣ���λ������                           
|       7   In  BOOL bCapture   ���õķֱ�����Ԥ��������                       
|
| ע  �⣺
|       1��bCaptureΪTRUEʱ��������ģʽ�ķֱ��ʣ���������Ԥ��ģʽ�ķֱ���
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
| ��  �ܣ���ȡ����ķֱ���ģʽ��ROI��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out BOOL *pbROI     ���õķֱ�����Ԥ�����ROI                      
|       3   Out INT *piHOff     ˮƽƫ��������λ������                         
|       4   Out INT *piVOff     ��ֱƫ��������λ������                         
|       5   Out INT *piWidth    �����ȣ���λ������                           
|       6   Out INT *piHeight   ����߶ȣ���λ������                           
|       7   In  BOOL bCapture   ���õķֱ�����Ԥ��������                       
|
| ע  �⣺
|         1��bROIΪTRUEʱ��ǰ��ROI�ֱ��ʣ�����ǰ��Ԥ����ֱ���
|         2��bCaptureΪTRUEʱ��ȡ����ģʽ�ķֱ��ʣ������ȡԤ��ģʽ�ķֱ���
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
| ��  �ܣ����ô����ͼ�����ݰ����ȣ�ǧ���������
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT iPack       ���ݰ�����������                               
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetTransPackLen(INT iCameraID, INT iPack);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ�����ͼ�����ݰ����ȣ�ǧ���������
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT *piPack     ���ݰ�����������                               
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetTransPackLen(INT iCameraID, INT *piPack);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����ʱ�����λ��ǧ���������
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT iUnit       ʱ�����λ������                               
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetTimeStampUnit(INT iCameraID, INT iUnit);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡʱ�����λ��ǧ���������
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT *piUnit     ʱ�����λ������                               
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetTimeStampUnit(INT iCameraID, INT *piUnit);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���������Ĳ�������
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  emDSParameterTeam emTeam �����������𣨹�4�飩               
|
| ע  �⣺
|         ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSaveParameter(INT iCameraID, emDSParameterTeam emTeam);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ����Ĳ������ã���ʹ����Ч
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  emDSParameterTeam emTeam    �����������𣨹�4�飩            
|
| ע  �⣺
|         ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraReadParameter(INT iCameraID, emDSParameterTeam emTeam);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���������Ĳ����������ļ�
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSaveParameterToIni(INT iCameraID);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ��������ļ���ȡ����Ĳ�������ʹ����Ч
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraLoadParameterFromIni(INT iCameraID);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���������Ĳ�����ini�ļ�����ʹ����Ч
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|		2   In  LPCSTR  lpszIniPath ���������ini�ļ���·��                    
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSaveParameterToIniEx(INT iCameraID, LPCSTR lpszIniPath);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ��������ļ���ȡ����Ĳ�������ʹ����Ч
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|		2   In  LPCSTR  lpszIniPath ���������ini�ļ���·��                    
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraLoadParameterFromIniEx(INT iCameraID, LPCSTR lpszIniPath);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ��ǰʹ�õı���������
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out emDSParameterTeam *pemTeam  �����������𣨹�4�飩            
|
| ע  �⣺
|         ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetCurrentParameterTeam(INT iCameraID, emDSParameterTeam *pemTeam);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ��������Ĭ�ϳ�����������
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraLoadDefaultParameter(INT iCameraID);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�������������ͼ����������
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  emDSDataType emMediaType    ͼ����������                       
|
| ע  �⣺
|         �������֧�ֵ��������ͣ���ο�����ֲ�
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetMediaType(INT iCameraID, emDSDataType emMediaType);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ��������ͼ����������
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out emDSDataType *pemMediaType  ͼ����������                       
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetMediaType(INT iCameraID, emDSDataType *pemMediaType);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�������������ͼ����������
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT iSel        ͼ����������������                             
|
| ע  �⣺
|       �������֧�ֵľ����������ͣ���ο�����ֲ�
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetMediaTypeSel(INT iCameraID, INT iSel);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ��������ͼ����������
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT *piSel      ͼ����������������                             
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetMediaTypeSel(INT iCameraID, INT *piSel);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����ɫ�ʽ�������
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT iSel        ͼ��ɫ�ʾ���������                             
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetRgbMatrixSel(INT iCameraID, INT iSel);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ��ǰ��ɫ�ʽ�������
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT *piSel      ͼ��ɫ�ʾ���������                             
|
| ע  �⣺
|         ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetRgbMatrixSel(INT iCameraID, INT *piSel);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�ʹ��Ӧ��ɫ�ʽ�������������Ч
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  float   fMatrix[3][3]  ͼ��ɫ�ʾ�������                        
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraApplyColorMatrix(INT iCameraID, float fMatrix[3][3]);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ����ù���ģʽ������ģʽ��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT iSnapMode   ����ģʽ                                       
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetTriggerMode(INT iCameraID, INT iSnapMode);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ����ģʽ������ģʽ��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT *piSnapMode ����ģʽ                                       
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetTriggerMode(INT iCameraID, INT *piSnapMode);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����������һ֡ͼ�񣨴���ģʽ��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraTrigger(INT iCameraID);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ����ô�����ƽ����
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|	    1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻�)             
|       2   In  INT iPulseStyle	    ������ƽ��Ե����                          
|       3   In  UINT uPulseWidth    �����ƽʱ��                              
|       4	In  UINT uDelay	        ��ʱ��Ϣ                                  
|       5   In  UINT uFilterWidth   �˲������                                
|       
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetTriggerPulse(
    INT iCameraID,          
    INT iPulseStyle,        
    UINT uPulseWidth,        
    UINT uDelay,            
    UINT uFilterWidth);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ������ƽ����
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT *piPulseStyle   ������ƽ��Ե����                           
|	    3   Out UINT *puPulseWidth  �����ƽʱ��                               
|       4   Out UINT *puDelay       ��ʱ��Ϣ                                   
|       5   Out UINT *puFilterWidth �˲������                                 
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetTriggerPulse(
    INT iCameraID,                          
    INT *piPulseStyle,               
    UINT *puPulseWidth,            
    UINT *puDelay,               
    UINT *puFilterWidth);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ����������źŲ���
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT iPulseStyle �����źű�Ե����                               
|	    3   In  UINT uPulseWidth    �����ƽʱ��                               
|       4   In  UINT uDelay     ��ʱ��Ϣ                                       
|       
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetStrobePulse(
    INT iCameraID,            
    INT iPulseStyle,         
    UINT uPulseWidth,        
    UINT uDelay);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ�����źŲ�����Ϣ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT *piPulseStyle   �����źű�Ե����                           
|	    3   Out UINT *puPulseWidth	�����ƽʱ��                               
|       4   Out UINT *puDelay       ��ʱ��Ϣ                                   
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetStrobePulse(
    INT iCameraID,                           
    INT *piPulseStyle,                 
    UINT *puPulseWidth,              
    UINT *puDelay);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ����ô���ģʽ���ع�ģʽ����
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT iSel        �ع�ģʽ����                                   
|
| ע  �⣺
|         ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetExposureSelForTrig(INT iCameraID, INT iSel);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ����ģʽ���ع�ģʽ���������źŲ�����Ϣ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT *piSel      �ع�ģʽ����                                   
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetExposureSelForTrig(INT iCameraID, INT *piSel);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����ͼ��ɼ���֡��������ģʽ��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  BYTE byCount    �ɼ���֡��                                     
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetTriggerCount(INT iCameraID, BYTE byCount);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ����÷ֱ���ģʽ������ģʽ��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT iSel        �ֱ���ģʽ������                               
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetResolutionModeSelForTrig(INT iCameraID, INT iSel);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ�ֱ���ģʽ������ģʽ��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT *piSel      �ֱ���ģʽ������                               
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetResolutionModeSelForTrig(INT iCameraID, INT *piSel);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����Ԥ�����ͼ��ߴ磨����ģʽ��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT iSel        ͼ��ߴ�������                                 
|
| ע  �⣺
|       iSel��ӦtDSImageSize��iIndex��Ա
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetImageSizeSelForTrig(INT iCameraID, INT iSel);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡԤ�����ͼ��ߴ磨����ģʽ��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT *piSel      ͼ��ߴ�������                                 
|
| ע  �⣺
|       *piSel��ӦtDSImageSize��iIndex��Ա
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetImageSizeSelForTrig(INT iCameraID, INT *piSel);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ������ع�ʱ�䣨����ģʽ��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  UINT64 uExpTime �ع�ʱ�䣬��λ��0.1us                          
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetExpTimeForTrig(INT iCameraID, UINT64 uExpTime);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ�ع�ʱ�䣨����ģʽ��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out UINT64 *puExpTime       �ع�ʱ�䣬��λ��0.1us                  
|       3   Out UINT64 *puExpTimeMax    ����ع�ʱ�䣬��λ��0.1us              
|       4   Out UINT64 *puExpTimeMin    ��С�ع�ʱ�䣬��λ��0.1us              
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetExpTimeForTrig(
    INT iCameraID,        
    UINT64 *puExpTime,        
    UINT64 *puExpTimeMax,    
    UINT64 *puExpTimeMin);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ������ع����棨����ģʽ��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  float fGain �ع����棬��λ������                               
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetAnalogGainForTrig(INT iCameraID, float fGain);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ�ع����棨����ģʽ��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out float *pfGain   �ع����棬��λ������                           
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetAnalogGainForTrig(INT iCameraID, float *pfGain);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ����÷ֱ���ģʽ������ģʽ��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  BOOL bROI       �Ƿ�ΪROIģʽ��Ԥ����ģʽ                      
|       3   In  INT iHOff       ˮƽƫ��������λ������                         
|       4   In  INT iVOff       ��ֱƫ��������λ������                         
|       5   In  INT iWidth      ͼ���ȣ���λ������                           
|       6   In  INT iHeight     ͼ��߶ȣ���λ������                           
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetImageSizeForTrig(
    INT iCameraID,                   
    BOOL bROI,                      
    INT iHOff,                    
    INT iVOff,                   
    INT iWidth,              
    INT iHeight);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ�ֱ���ģʽ������ģʽ��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out BOOL *pbROI     �Ƿ�ΪROIģʽ��Ԥ����ģʽ                      
|       3   Out INT *piHOff     ˮƽƫ��������λ������                         
|       4   Out INT *piVOff     ��ֱƫ��������λ������                         
|       5   Out INT *piWidth    ͼ���ȣ���λ������                           
|       6   Out INT *piHeight   ͼ��߶ȣ���λ������                           
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetImageSizeForTrig(
    INT iCameraID,                         
    BOOL *pbROI,                    
    INT *piHOff,                     
    INT *piVOff,
    INT *piWidth,           
    INT *piHeight);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�д��������к�
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT iLevel      ���кż���                                     
|       3   In  BYTE *pbySN     ���к�����                                     
|       4   In  INT iSize       ���к��ֽ���                                   
|       5   Out INT *piWritten  ʵ��д����ֽ���                               
|
| ע  �⣺
|       1��iLevel��ֵΪ 2���������кţ�ͨ��SDKֻ��д��������к�
|       2�����кŵ��ֽ������Ϊ��32�ֽ�
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraWriteSN(
    INT iCameraID,                   
    INT iLevel,               
    BYTE *pbySN,           
    INT iSize, 
    INT *piWritten);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ������к�
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT iLevel      ���кż���                                     
|       3   Out BYTE *pbySN     ���к�����                                     
|       4   In  INT iSize       ���к��ֽ���                                   
|       5   Out INT *piReaded   ʵ�ʻ�ȡ���ֽ���                               
|
| ע  �⣺
|       1��iLevel��ֵΪ 1��һ�����кţ�2���������к�
|       2�����кŵ��ֽ������Ϊ��32�ֽ�
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraReadSN(
    INT iCameraID,       
    INT iLevel,          
    BYTE *pbySN,         
    INT iSize,            
    INT *piReaded);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ����߼����ô���
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out tPropertyPageInfo *psPageInfo  ����߼����ô�����Ϣ            
|       3   In  BYTE byType     �߼����ô�������                               
|
| ע  �⣺
|       byType��ֵΪ 0���豸�߼����ô��ڣ�1��ͼ����ģ�鴰��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetPropertyPageInfo(
    INT iCameraID, 
    tDSPropertyPageInfo *psPageInfo, 
    BYTE byType);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ʾ����߼����ô���
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  HWND hwndDisplay    Ԥ�����ھ��                               
|       3   In  BYTE byType         �߼����ô�������                           
|
| ע  �⣺
|       byType��ֵΪ 0���豸�߼����ô��ڣ�1��ͼ����ģ�鴰��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraShowSettingPage(INT iCameraID, HWND hwndDisplay, BYTE byType);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡSDK�汾��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  DWORD   adwVersion  SDK�汾��            
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetSDKVersion(DWORD adwVersion[4]);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ�û��Զ����GPIO�����״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out USHORT *puGPIO  GPIO�����״̬(�ߵ͵�ƽ)                       
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetUserGPIOIn(INT iCameraID, USHORT *puGPIO);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ�û��Զ����GPIO�����״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out USHORT *puGPIO  GPIO�����״̬(�ߵ͵�ƽ)                       
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetUserGPIOOut(INT iCameraID, USHORT *puGPIO);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ������û��Զ����GPIO�����״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  USHORT uGPIO    GPIO�����״̬(�ߵ͵�ƽ)                       
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetUserGPIOOut(INT iCameraID, USHORT uGPIO);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���GPIO�����״̬���ߵ͵�ƽ��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out USHORT *puGPIO  GPIO�����״̬(�ߵ͵�ƽ)                       
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetUserGPIOInEx(INT iCameraID, USHORT *uGPIO);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���GPIO�ڷ���״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�              
|       2   Out USHORT *puGPIO  GPIO�ڷ���״̬(0��ʾ���룬1��ʾ���)            
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetUserGPIODirEx(INT iCameraID, USHORT *uGPIO);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����GPIO�ڵķ���
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  USHORT uGPIO    GPIO�ڷ���״̬(0��ʾ���룬1��ʾ���)           
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetUserGPIODirEx(INT iCameraID, USHORT uGPIO);


/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����GPIO�ڵ�ģʽ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT iMode       GPIOģʽ(0��ʾGPIO��1��ʾ�ڶ�����)             
|
| ע  �⣺
|       ��GPIO��ĳ��λ��֧�ֵڶ�����ʱ����������Ч
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetUserGPIOModeEx(INT iCameraID, INT iMode);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���GPIO�ڵ�ģʽ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT *piMode     GPIOģʽ(0��ʾGPIO��1��ʾ�ڶ�����)             
|
| ע  �⣺
|       ��GPIO��ĳ��λ��֧�ֵڶ�����ʱ����������Ч
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetUserGPIOModeEx(INT iCameraID, INT *piMode);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ������ⴥ��������/����ơ�����ر�
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  BOOL bStrobOut  FALSE��ʾ�رգ�TRUE��ʾ��                    
|
| ע  �⣺
|       ��GPIO��ĳ��λ��֧�ֵڶ�����ʱ����������Ч
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetStrobeOutStateEx(INT iCameraID, BOOL bStrobeOut);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡ�ⴥ��������/����ơ�����رյ�״̬
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out BOOL *pbStrobOut FALSE��ʾ�رգ�TRUE��ʾ��                   
|
| ע  �⣺
|       ��GPIO��ĳ��λ��֧�ֵڶ�����ʱ����������Ч
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetStrobeOutStateEx(INT iCameraID, BOOL *pbStrobeOut);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����Gige����ķ���ģʽ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�                 
|       2   In  INT iMode   Gige�������ģʽ �ο�emDSGigeCameraMode����	           
|
| ע  �⣺
|       ��
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetGigeAccessMode(INT iCameraID, INT iMode);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡGige����ķ���ģʽ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT *piMode	    Gige�������ģʽ                               
|
| ע  �⣺
|       
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetGigeAccessMode(INT iCameraID, INT *piMode);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����Gige���ͼ�����ݱ��ĵ�Ŀ��IP��ַ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT iIP[4]  Ŀ��IP��ַ��iIP[0].iIP[1].iIP[2].iIP[3]	           
|
| ע  �⣺
|        
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetGigeFrameDestIP(INT iCameraID, INT iIP[4]);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡGige���ͼ�����ݱ��ĵ�Ŀ��IP��ַ
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT iIP[4]  Ŀ��IP��ַ��iIP[0].iIP[1].iIP[2].iIP[3]	           
|
| ע  �⣺
|       
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetGigeFrameDestIP(INT iCameraID, INT iIP[4]);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ�����Gige�����Ŀ��˿�
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT iPort       Gige�����Ŀ��˿�                             
|
| ע  �⣺
|         
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraSetGigeFrameDestPort(INT iCameraID, INT iPort);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ���ȡGige�����Ŀ��˿�
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   Out INT *piPort     Gige�����Ŀ��˿�                 	           
|
| ע  �⣺
|       
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGetGigeFrameDestPort(INT iCameraID, INT *piPort);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ����뵽�鲥��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT iIP[4]  �鲥��ip��iIP[0].iIP[1].iIP[2].iIP[3]              
|
| ע  �⣺
|         
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGigeJoinMulticas(INT iCameraID, INT iIP[4]);

/*--------------------------------------------------------------------------------------*\
| ��  �ܣ��뿪�鲥��
|
| ����ֵ�����óɹ�����STATUS_OK�����򷵻ش������
|
| ��  ����
|       1   In  INT iCameraID   �����ţ��������ʼ���ɹ��󷵻أ�             
|       2   In  INT iIP[4]  �鲥��ip��iIP[0].iIP[1].iIP[2].iIP[3]              
|
| ע  �⣺
|         
\*--------------------------------------------------------------------------------------*/
DS_API emDSCameraStatus CameraGigeLeaveMulticas(INT iCameraID, INT iIP[4]);


#endif