#pragma once

#define MAX_CLINET_NUM  15

#include "ComSocket.h"


#define  LOADMATERIAL_INFO  319  //上料板信息  包括预定位结果和AOIBIng结果
#define  AOI_RET    320  //AOI检测结果
#define  PRE_LOCATE 321  //预定位结果
#define  MSG_CONFORM 322 //消息确认
#define  MACHINE_INFO 323 //机器信息
#define  HEART_BREAK 324  //心跳


#define LOADPICAKMATERIAL_ARRIVED  325  //取料到位信号


#define  UNLOADPCIKMATERIAL_DONE 328  //取料完成
#define  LOADPUTMATERIAL_DONE    329  //放料完成





#define   TASK_READY         330   //任务准备好
#define   TASK_RUN_ERR       331   //运行报错
#define   TASK_PAUSE         332   //暂停
#define   TASK_CONTINUE      333   //继续运行
#define   TASK_START         334   //开始工作
#define   TASK_ORGIN         335   //回原点
#define   TASK_STOP          336   //停止工作


#define  CALLIBRATECAPBMP_START       340 //开始标定
#define  CALLIBRATECAPBMP_READY       341 //标定准备好
#define  CALLIBRATECAPBMP_SINGMOV     342 //采集单步移动
#define  CALIBRATECAPBMP_DONE         343 //单帧采集完成
#define  CALIBRATECAPBMP_FINISH       344  //标定采图完成



#define  CALIBRATEBOARD_START        345  //标定采图完成
#define  CALIBRATEBOARD_DONE         346  //标定采图完成


#define STEP_MOV   350    //单步移动

#define SERVER_OFF  351  //使能关闭



#define LOADPLATFORM_CANLOAD               352 //上料请求
#define LOADPLATFORM_CANLOADCONFIRM        353 //上料请求确认
#define LOADPLATFORM_NOZZLE_CHECK_RET      354 //上料放料完成
#define LOADPLATFORM_NOZZLE_CHECK_FINISH   355 //上料动作完成后确认消息



#define UNLOADPLATFORM_CANUNLOAD               356 //下料请求
#define UNLOADPLATFORM_CANUNLOADCONFIRM        357 //下料请求确认
#define UNLOADPLATFORM_NOZZLE_CHECK_RET        358 //下料吸盘检测




#define LOAD_X_ARRIVED 360  //上料X到位
#define LOAD_Y_ARRIVED 361  //下料Y到位


#define UNLOAD_X_ARRIVED 362  //下料X到位
#define UNLOAD_X_SUCK_ARRIVED 363  //下料X吸嘴到位


#define STATUS_HADORI	370					//回过原点
#define STATUS_HADLOADTASK	371				//加载过任务了
#define STATUS_TASKERR		372				//状态异常下线
#define STATUS_Breeze		373				//状态异常下线


#define MOTIONCARD_GETPOS   400									//获取当前位置
#define MOTIONCARD_RETURNPOS   401								//返回当前位置




class CMotionCard;


struct MsgPacket
{
	WORD nType;//消息类型
	BYTE nLen;//
	BYTE nSide;//左右工位标志 0 左侧 1右侧

	WORD nRecvType;//返回当前处理的数据的接收类型
	WORD bIsAoiOK;//检测AOI是否OK 校验失败时需重发时置为FALSE

	double dAoiRet[2];//AOI检测结果  AOIbing检测胶宽
	double doffsetY;//Y方向偏移
	double dCalcuRet;//计算校验值


	MsgPacket()
	{
		Init();
	}

	void Init()
	{
		dCalcuRet=0.0;
		nLen = 0;
		nRecvType=0;

		nSide=0;
		nType=AOI_RET;
		nLen=sizeof(MsgPacket);
		bIsAoiOK = 0;
		dAoiRet[1]=dAoiRet[0]=0.0;
		doffsetY=0.0;
	}

	void CalculateValue()//计算校验值
	{
		dCalcuRet=nType+nLen+nSide+bIsAoiOK+dAoiRet[0]+dAoiRet[1]+doffsetY;
	}

	BOOL CheckValue()//检查校验值
	{
		return dCalcuRet==(nType+nLen+nSide+bIsAoiOK+dAoiRet[0]+dAoiRet[1]+doffsetY);
	}
};

class CSocketManage
{
public:
	CSocketManage(void);
	~CSocketManage(void);

public:

	double m_dOffsetY[2];//接受的预定位偏移数据
	int  m_nAxis[2];
	BOOL m_bHasRecvLoadRequest[2];
	BOOL m_bIsLoadXArrived[2];//是否上料X到位
	BOOL m_bIsUnLoadXArrived[2];//是否上料X到位
	BOOL m_bIsLoadFinish[2];//是否上料确认完成
	BOOL m_bIsLoadFinishOK[2];//
	BOOL m_bIsUnloadDone[2]; //是否下料完成
	BOOL m_bIsAxisServOff[2]; //是否使能信号断开
	BOOL m_bRequrCalibrateBoard[2];//要求进行标定
	BOOL m_bRecvData[2];//判断接受偏移数据
	BOOL m_bCalWalk[2];//判断是否开始走标


	BOOL m_bIsRecvLoadReady[8];
	BOOL m_bIsLoadReady[8];
	BOOL m_bIsLoadYArrived[8];//是否上料Y到位
	BOOL m_bIsUnloadYArrived[8]; //是否下料Y到位
	BOOL m_bIsLoadDone[8];   //是否上料完成
	BOOL m_bIsLoadDoneOK[8];  //
	BOOL m_bIsMacError[8];// 是否轴出错
	BOOL m_bCalibrateBoardDone[8];//标定标定板完成
	BOOL m_bIsCapbmpDone[8];  //是否采集单帧完成
	BOOL m_bIsCambmpReady[8];  //是否采集图像准备好


	//接收客户端消息
	BOOL GetIsLoadReady(int nAxis,BOOL& IsLoadReady);
	BOOL GetIsLoadYArrived(int nAxis);
	BOOL GetIsUnloadXArrived(int nAxis);
	BOOL GetLoadDone(int nAxis,BOOL &bLoadDoneOK);
	BOOL GetLoadDone(int nAxis);

	//接收服务器消息
    BOOL GetIsRecvLoadRequest(int nSide);
	BOOL GetIsLoadXArrived(int nSide);				//上料吸嘴是否到位
	BOOL GetIsUnLoadXArrived2(int nSide);			//下料吸嘴是否到位
	BOOL GetLoadFinish(int nSide,BOOL &bLoadDoneOK);
	BOOL GetUnloadDone(int nSide);
	BOOL GetLoadFinish(int nSide);
	BOOL GetAxisIsServOff(int nSide);

	//通信，告诉服务器
	BOOL SendLoadDone(BOOL bIsOK,int nSide);  //发送吸盘吸取结果  客户端发服务器
	BOOL SendYLoadArrived(int nSide);//客户端发送Y轴到位信号
	BOOL SendYUnloadArrived(int nSide);// 客户端发送Y轴下料到位信号
	BOOL SendSuckResult(int nSide,BOOL isOk);// 客户端告诉主机吸盘是否吸紧


	//通信，告诉客户端
	BOOL SendLoadFinish(BOOL bIsOK,int nAxis);//发送上料完成信号  服务器发客户端
	BOOL SendXLoadArrived(int nAxis);  //发送上料X轴到位信号
	BOOL SendPrelocateInfo(int nAxis,double dAoiRet1,double dAoiRet2,BOOL bIsAoiOk,double dOffsetY);//发送预定位信息
	BOOL SendXUnloadArrived(int nAxis);//通知客户端下料吸嘴已经到位
	BOOL SendLoadSuckInPos(int nAxis);//通知客户端上料料吸嘴已经到位
	BOOL SendUnLoadDone(int nAxis);//通知客户端下料线程已经结束







//标定通信
	BOOL GetIsCalibrateCambmpDone(int nAxis);			//是否采图完成
	BOOL GetIsCalibrateBoardDone(int nAxis);			//是否对应轴标定板完成
	BOOL GetIsCalibrateCambmpReady(int nAxis);			//是否采集图像准备好
	BOOL GetRecvOffsetY(int &nSide,double &dOffsetY);	//查询是否接受数据完毕
	int  GetAxisSocket(int nIndexAxis);					//获取轴号对应的通信套接字编号
	BOOL GetIsRequrCalibrateBoard(int nSide);			//检测是否要开始标定标定板
	BOOL GetbCalWalk(int nSide);						//检测是否要开始走标
	BOOL GetSingleMsg(int nSide);						//获得一个状态量

	BOOL TESTGETALLSINGAL();							//检测所有客户端收到的信号，测试用



//服务器对客户端的运动控制
	//8个软件之间的通信
	BOOL m_bTaskStop;										//判断是否停止工作
	BOOL m_bTaskPause;										//判断是否暂停工作
	BOOL m_bTaskContinue;									//判断是否继续工作
	BOOL m_bTaskStart;									    //判断是否开始工作
	BOOL m_bMachHadOri[8];									//8个工位是否发给主机回原
	BOOL m_bMachReady[8];									//8个工位是否发给主机准备好
	BOOL m_bMachUnReady[8];									//8个工位是否发给主机下线了
	BOOL m_bMachRing[8];									//8个工位是否发给主机响蜂鸣器
	int  m_bMachErrCode[8];									//8个工位发给主机的错误信号

	CMotionCard *m_pMotionCard;								//运动指针
	BOOL GetStartWork();									//检测是否收到开始工作信号
	BOOL GetStopWork();										//检测是否收到停止工作信号
	BOOL GetPauseWork();									//检测是否收到暂停工作信号
	BOOL GetContinueWork();									//检测是否收到继续工作信号	
	BOOL SendAllStartWork();								//发送开始工作信号
	BOOL SendAllStopWork();									//发送停止工作信号
	BOOL SendAllPauseWork();								//发送暂停工作信号
	BOOL SendAllContinueWork();								//发送继续工作信号

	BOOL SendSingalStatue(int Type,int machNum);
	BOOL SendAllAxisIsServOff();
	//客户端告诉主机回过原点或者加载过任务了
	BOOL SendCmputerReady();									//发送准备好
	BOOL GetComputerReady(int nmachIndex);					//获取软件是准备好

	BOOL SendMachReady();									//发送上线
	BOOL GetMachReady(int nmachIndex);						//获取软件是否上线

	BOOL SendMachUnReady();									//发送下线
	BOOL GetMachUnReady(int nmachIndex);						//获取软件是否下线

	BOOL SendBuzzerRing(double ERRCODE = 0);									//发送蜂鸣器响命令
	BOOL GetBuzzerRing(int nmachIndex, int &ERRCODE);						//获取蜂鸣器响命令


//motioncard相关
	BOOL m_bmotionCardRecePos[8];							//motioncard是否返回了数据
	double m_dmotionCardRecePos[8];							//收到的数据
	BOOL MoveDis(int nAxis,double dis);

	BOOL mcSendAxisCurPos(int nAxis);

	BOOL GetClientReturnPos(int nmachIndex,double &dis);




//barcode和主控制
	BOOL m_bStartRecv;//开始接收二维码数据
	BOOL m_bRecvBarcodeDone;//接收Barcode完成
	char m_cBarcode[30];//读取到的二维码数值
	int m_nRecvDataNum;
	void *m_pData;
	BOOL m_bIsSockLibNormal;

	CComSocket m_Server;//服务器套接字
	CComSocket m_Client[MAX_CLINET_NUM];//客户端
	MsgPacket m_lastMsgPacket[MAX_CLINET_NUM];//最近一次发送的数据包 

	
	CString strLog;								//用来写日志文件的
	CCriticalSection m_LockLog;					//用来写日志的锁
	BOOL ResetStatus();
	BOOL CloseServer();
	BOOL CloseAllClient();
	BOOL CheckIsBarcodeConn(); //检测扫描枪是否连接
	BOOL CheckMacConn(int nAxis);//检测机器是否连接
	BOOL GetConnStatus(int nMacIndex);//获取当前机器对应套接字连接状态
	BOOL InitSockLib();//初始化网络环境 最先调用
	BOOL UninSockLib();//卸载网络库
	BOOL InitClient(char* servAddr,UINT nPort);//初始化客户端
	BOOL InitServer(char* servAddr,UINT nPort);//初始化服务器
	BOOL SendMsgServ(MsgPacket msg,int nIndex=0);//服务器发送消息用
	BOOL SendMsgClient(MsgPacket msg,int nIndex=0);//客户端发送消息用

    //msg发送数据，最后一个值为额外加的终止符
	//msgLen为所传数据长度，包括终止符
	//nIndex服务器调度可能会用到 对应的机器号
	BOOL SendMsg(char *msg,int msgLen,int nIndex=0);//测试用  发送数据用
	BOOL SendMsg(MsgPacket msg,int nIndex=0);//测试用  发送数据用

	//可根据实际情况修改内部的处理逻辑
	BOOL HandledData(CComSocket *pComSock);//处理接受到的数据
	
	//以上为通信所用函数  以下暂时不会用到
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	
	BOOL AcceptSock(SOCKET sock);//接受套接字响应


	BOOL InitClientBarCodeReader(char* servAddr,UINT nPort);//初始化二维码读头
	BOOL InitClientSendAoidata(char* servAddr,UINT nPort);//初始化上传数据


	int FindBarcodeReaderIndex();//查找扫描枪对应套接字编号
	int FindSendAoidataIndex(); //查找上传数据对应套接字编号

	BOOL SendReadBarcodeCmd();//发送读取二维码命令
	BOOL SendBarCodeAndAoiRet();//发送AOI检测结果及二维码


	BOOL CheckSockIsOnline();//检查套接字是否掉线

	void ResendMsg(BOOL bNeedResend,CComSocket* pSock,MsgPacket msg); //验证未通过 需重发


	int GetIdleSocket();//获取当前可用空闲套接字




	BOOL (*DealRecvData)(void *pData,MsgPacket msg);

	////////////////////////////////////////////////////////////////////////
	//发送消息
	///////////////////////////////////////////////////////////////////////

// 	BOOL SendMachineServError();//发送机器使能异常






	BOOL TestSendSingleMsg(int SingalType,int nSide);						//发送一个信号

	BOOL SendConfirmMsgPacket(BOOL bNeedResend,CComSocket* pSock,MsgPacket msg);//发送数据确认消息
    BOOL SendMachineInfo(int nIndex);     //发送设备遍号信息



    /////////////////////////////////////////////////////////////////
	//部分执行函数指针
	/////////////////////////////////////////////////////////////////

 	BOOL (*PauseWork)();
 	BOOL (*StartWork)();
 	BOOL (*StopWork)();

};

