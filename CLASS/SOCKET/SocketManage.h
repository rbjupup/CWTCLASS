#pragma once

#define MAX_CLINET_NUM  15

#include "ComSocket.h"


#define  LOADMATERIAL_INFO  319  //���ϰ���Ϣ  ����Ԥ��λ�����AOIBIng���
#define  AOI_RET    320  //AOI�����
#define  PRE_LOCATE 321  //Ԥ��λ���
#define  MSG_CONFORM 322 //��Ϣȷ��
#define  MACHINE_INFO 323 //������Ϣ
#define  HEART_BREAK 324  //����


#define LOADPICAKMATERIAL_ARRIVED  325  //ȡ�ϵ�λ�ź�


#define  UNLOADPCIKMATERIAL_DONE 328  //ȡ�����
#define  LOADPUTMATERIAL_DONE    329  //�������





#define   TASK_READY         330   //����׼����
#define   TASK_RUN_ERR       331   //���б���
#define   TASK_PAUSE         332   //��ͣ
#define   TASK_CONTINUE      333   //��������
#define   TASK_START         334   //��ʼ����
#define   TASK_ORGIN         335   //��ԭ��
#define   TASK_STOP          336   //ֹͣ����


#define  CALLIBRATECAPBMP_START       340 //��ʼ�궨
#define  CALLIBRATECAPBMP_READY       341 //�궨׼����
#define  CALLIBRATECAPBMP_SINGMOV     342 //�ɼ������ƶ�
#define  CALIBRATECAPBMP_DONE         343 //��֡�ɼ����
#define  CALIBRATECAPBMP_FINISH       344  //�궨��ͼ���



#define  CALIBRATEBOARD_START        345  //�궨��ͼ���
#define  CALIBRATEBOARD_DONE         346  //�궨��ͼ���


#define STEP_MOV   350    //�����ƶ�

#define SERVER_OFF  351  //ʹ�ܹر�



#define LOADPLATFORM_CANLOAD               352 //��������
#define LOADPLATFORM_CANLOADCONFIRM        353 //��������ȷ��
#define LOADPLATFORM_NOZZLE_CHECK_RET      354 //���Ϸ������
#define LOADPLATFORM_NOZZLE_CHECK_FINISH   355 //���϶�����ɺ�ȷ����Ϣ



#define UNLOADPLATFORM_CANUNLOAD               356 //��������
#define UNLOADPLATFORM_CANUNLOADCONFIRM        357 //��������ȷ��
#define UNLOADPLATFORM_NOZZLE_CHECK_RET        358 //�������̼��




#define LOAD_X_ARRIVED 360  //����X��λ
#define LOAD_Y_ARRIVED 361  //����Y��λ


#define UNLOAD_X_ARRIVED 362  //����X��λ
#define UNLOAD_X_SUCK_ARRIVED 363  //����X���쵽λ


#define STATUS_HADORI	370					//�ع�ԭ��
#define STATUS_HADLOADTASK	371				//���ع�������
#define STATUS_TASKERR		372				//״̬�쳣����
#define STATUS_Breeze		373				//״̬�쳣����


#define MOTIONCARD_GETPOS   400									//��ȡ��ǰλ��
#define MOTIONCARD_RETURNPOS   401								//���ص�ǰλ��




class CMotionCard;


struct MsgPacket
{
	WORD nType;//��Ϣ����
	BYTE nLen;//
	BYTE nSide;//���ҹ�λ��־ 0 ��� 1�Ҳ�

	WORD nRecvType;//���ص�ǰ��������ݵĽ�������
	WORD bIsAoiOK;//���AOI�Ƿ�OK У��ʧ��ʱ���ط�ʱ��ΪFALSE

	double dAoiRet[2];//AOI�����  AOIbing��⽺��
	double doffsetY;//Y����ƫ��
	double dCalcuRet;//����У��ֵ


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

	void CalculateValue()//����У��ֵ
	{
		dCalcuRet=nType+nLen+nSide+bIsAoiOK+dAoiRet[0]+dAoiRet[1]+doffsetY;
	}

	BOOL CheckValue()//���У��ֵ
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

	double m_dOffsetY[2];//���ܵ�Ԥ��λƫ������
	int  m_nAxis[2];
	BOOL m_bHasRecvLoadRequest[2];
	BOOL m_bIsLoadXArrived[2];//�Ƿ�����X��λ
	BOOL m_bIsUnLoadXArrived[2];//�Ƿ�����X��λ
	BOOL m_bIsLoadFinish[2];//�Ƿ�����ȷ�����
	BOOL m_bIsLoadFinishOK[2];//
	BOOL m_bIsUnloadDone[2]; //�Ƿ��������
	BOOL m_bIsAxisServOff[2]; //�Ƿ�ʹ���źŶϿ�
	BOOL m_bRequrCalibrateBoard[2];//Ҫ����б궨
	BOOL m_bRecvData[2];//�жϽ���ƫ������
	BOOL m_bCalWalk[2];//�ж��Ƿ�ʼ�߱�


	BOOL m_bIsRecvLoadReady[8];
	BOOL m_bIsLoadReady[8];
	BOOL m_bIsLoadYArrived[8];//�Ƿ�����Y��λ
	BOOL m_bIsUnloadYArrived[8]; //�Ƿ�����Y��λ
	BOOL m_bIsLoadDone[8];   //�Ƿ��������
	BOOL m_bIsLoadDoneOK[8];  //
	BOOL m_bIsMacError[8];// �Ƿ������
	BOOL m_bCalibrateBoardDone[8];//�궨�궨�����
	BOOL m_bIsCapbmpDone[8];  //�Ƿ�ɼ���֡���
	BOOL m_bIsCambmpReady[8];  //�Ƿ�ɼ�ͼ��׼����


	//���տͻ�����Ϣ
	BOOL GetIsLoadReady(int nAxis,BOOL& IsLoadReady);
	BOOL GetIsLoadYArrived(int nAxis);
	BOOL GetIsUnloadXArrived(int nAxis);
	BOOL GetLoadDone(int nAxis,BOOL &bLoadDoneOK);
	BOOL GetLoadDone(int nAxis);

	//���շ�������Ϣ
    BOOL GetIsRecvLoadRequest(int nSide);
	BOOL GetIsLoadXArrived(int nSide);				//���������Ƿ�λ
	BOOL GetIsUnLoadXArrived2(int nSide);			//���������Ƿ�λ
	BOOL GetLoadFinish(int nSide,BOOL &bLoadDoneOK);
	BOOL GetUnloadDone(int nSide);
	BOOL GetLoadFinish(int nSide);
	BOOL GetAxisIsServOff(int nSide);

	//ͨ�ţ����߷�����
	BOOL SendLoadDone(BOOL bIsOK,int nSide);  //����������ȡ���  �ͻ��˷�������
	BOOL SendYLoadArrived(int nSide);//�ͻ��˷���Y�ᵽλ�ź�
	BOOL SendYUnloadArrived(int nSide);// �ͻ��˷���Y�����ϵ�λ�ź�
	BOOL SendSuckResult(int nSide,BOOL isOk);// �ͻ��˸������������Ƿ�����


	//ͨ�ţ����߿ͻ���
	BOOL SendLoadFinish(BOOL bIsOK,int nAxis);//������������ź�  ���������ͻ���
	BOOL SendXLoadArrived(int nAxis);  //��������X�ᵽλ�ź�
	BOOL SendPrelocateInfo(int nAxis,double dAoiRet1,double dAoiRet2,BOOL bIsAoiOk,double dOffsetY);//����Ԥ��λ��Ϣ
	BOOL SendXUnloadArrived(int nAxis);//֪ͨ�ͻ������������Ѿ���λ
	BOOL SendLoadSuckInPos(int nAxis);//֪ͨ�ͻ��������������Ѿ���λ
	BOOL SendUnLoadDone(int nAxis);//֪ͨ�ͻ��������߳��Ѿ�����







//�궨ͨ��
	BOOL GetIsCalibrateCambmpDone(int nAxis);			//�Ƿ��ͼ���
	BOOL GetIsCalibrateBoardDone(int nAxis);			//�Ƿ��Ӧ��궨�����
	BOOL GetIsCalibrateCambmpReady(int nAxis);			//�Ƿ�ɼ�ͼ��׼����
	BOOL GetRecvOffsetY(int &nSide,double &dOffsetY);	//��ѯ�Ƿ�����������
	int  GetAxisSocket(int nIndexAxis);					//��ȡ��Ŷ�Ӧ��ͨ���׽��ֱ��
	BOOL GetIsRequrCalibrateBoard(int nSide);			//����Ƿ�Ҫ��ʼ�궨�궨��
	BOOL GetbCalWalk(int nSide);						//����Ƿ�Ҫ��ʼ�߱�
	BOOL GetSingleMsg(int nSide);						//���һ��״̬��

	BOOL TESTGETALLSINGAL();							//������пͻ����յ����źţ�������



//�������Կͻ��˵��˶�����
	//8�����֮���ͨ��
	BOOL m_bTaskStop;										//�ж��Ƿ�ֹͣ����
	BOOL m_bTaskPause;										//�ж��Ƿ���ͣ����
	BOOL m_bTaskContinue;									//�ж��Ƿ��������
	BOOL m_bTaskStart;									    //�ж��Ƿ�ʼ����
	BOOL m_bMachHadOri[8];									//8����λ�Ƿ񷢸�������ԭ
	BOOL m_bMachReady[8];									//8����λ�Ƿ񷢸�����׼����
	BOOL m_bMachUnReady[8];									//8����λ�Ƿ񷢸�����������
	BOOL m_bMachRing[8];									//8����λ�Ƿ񷢸������������
	int  m_bMachErrCode[8];									//8����λ���������Ĵ����ź�

	CMotionCard *m_pMotionCard;								//�˶�ָ��
	BOOL GetStartWork();									//����Ƿ��յ���ʼ�����ź�
	BOOL GetStopWork();										//����Ƿ��յ�ֹͣ�����ź�
	BOOL GetPauseWork();									//����Ƿ��յ���ͣ�����ź�
	BOOL GetContinueWork();									//����Ƿ��յ����������ź�	
	BOOL SendAllStartWork();								//���Ϳ�ʼ�����ź�
	BOOL SendAllStopWork();									//����ֹͣ�����ź�
	BOOL SendAllPauseWork();								//������ͣ�����ź�
	BOOL SendAllContinueWork();								//���ͼ��������ź�

	BOOL SendSingalStatue(int Type,int machNum);
	BOOL SendAllAxisIsServOff();
	//�ͻ��˸��������ع�ԭ����߼��ع�������
	BOOL SendCmputerReady();									//����׼����
	BOOL GetComputerReady(int nmachIndex);					//��ȡ�����׼����

	BOOL SendMachReady();									//��������
	BOOL GetMachReady(int nmachIndex);						//��ȡ����Ƿ�����

	BOOL SendMachUnReady();									//��������
	BOOL GetMachUnReady(int nmachIndex);						//��ȡ����Ƿ�����

	BOOL SendBuzzerRing(double ERRCODE = 0);									//���ͷ�����������
	BOOL GetBuzzerRing(int nmachIndex, int &ERRCODE);						//��ȡ������������


//motioncard���
	BOOL m_bmotionCardRecePos[8];							//motioncard�Ƿ񷵻�������
	double m_dmotionCardRecePos[8];							//�յ�������
	BOOL MoveDis(int nAxis,double dis);

	BOOL mcSendAxisCurPos(int nAxis);

	BOOL GetClientReturnPos(int nmachIndex,double &dis);




//barcode��������
	BOOL m_bStartRecv;//��ʼ���ն�ά������
	BOOL m_bRecvBarcodeDone;//����Barcode���
	char m_cBarcode[30];//��ȡ���Ķ�ά����ֵ
	int m_nRecvDataNum;
	void *m_pData;
	BOOL m_bIsSockLibNormal;

	CComSocket m_Server;//�������׽���
	CComSocket m_Client[MAX_CLINET_NUM];//�ͻ���
	MsgPacket m_lastMsgPacket[MAX_CLINET_NUM];//���һ�η��͵����ݰ� 

	
	CString strLog;								//����д��־�ļ���
	CCriticalSection m_LockLog;					//����д��־����
	BOOL ResetStatus();
	BOOL CloseServer();
	BOOL CloseAllClient();
	BOOL CheckIsBarcodeConn(); //���ɨ��ǹ�Ƿ�����
	BOOL CheckMacConn(int nAxis);//�������Ƿ�����
	BOOL GetConnStatus(int nMacIndex);//��ȡ��ǰ������Ӧ�׽�������״̬
	BOOL InitSockLib();//��ʼ�����绷�� ���ȵ���
	BOOL UninSockLib();//ж�������
	BOOL InitClient(char* servAddr,UINT nPort);//��ʼ���ͻ���
	BOOL InitServer(char* servAddr,UINT nPort);//��ʼ��������
	BOOL SendMsgServ(MsgPacket msg,int nIndex=0);//������������Ϣ��
	BOOL SendMsgClient(MsgPacket msg,int nIndex=0);//�ͻ��˷�����Ϣ��

    //msg�������ݣ����һ��ֵΪ����ӵ���ֹ��
	//msgLenΪ�������ݳ��ȣ�������ֹ��
	//nIndex���������ȿ��ܻ��õ� ��Ӧ�Ļ�����
	BOOL SendMsg(char *msg,int msgLen,int nIndex=0);//������  ����������
	BOOL SendMsg(MsgPacket msg,int nIndex=0);//������  ����������

	//�ɸ���ʵ������޸��ڲ��Ĵ����߼�
	BOOL HandledData(CComSocket *pComSock);//������ܵ�������
	
	//����Ϊͨ�����ú���  ������ʱ�����õ�
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	
	BOOL AcceptSock(SOCKET sock);//�����׽�����Ӧ


	BOOL InitClientBarCodeReader(char* servAddr,UINT nPort);//��ʼ����ά���ͷ
	BOOL InitClientSendAoidata(char* servAddr,UINT nPort);//��ʼ���ϴ�����


	int FindBarcodeReaderIndex();//����ɨ��ǹ��Ӧ�׽��ֱ��
	int FindSendAoidataIndex(); //�����ϴ����ݶ�Ӧ�׽��ֱ��

	BOOL SendReadBarcodeCmd();//���Ͷ�ȡ��ά������
	BOOL SendBarCodeAndAoiRet();//����AOI���������ά��


	BOOL CheckSockIsOnline();//����׽����Ƿ����

	void ResendMsg(BOOL bNeedResend,CComSocket* pSock,MsgPacket msg); //��֤δͨ�� ���ط�


	int GetIdleSocket();//��ȡ��ǰ���ÿ����׽���




	BOOL (*DealRecvData)(void *pData,MsgPacket msg);

	////////////////////////////////////////////////////////////////////////
	//������Ϣ
	///////////////////////////////////////////////////////////////////////

// 	BOOL SendMachineServError();//���ͻ���ʹ���쳣






	BOOL TestSendSingleMsg(int SingalType,int nSide);						//����һ���ź�

	BOOL SendConfirmMsgPacket(BOOL bNeedResend,CComSocket* pSock,MsgPacket msg);//��������ȷ����Ϣ
    BOOL SendMachineInfo(int nIndex);     //�����豸�����Ϣ



    /////////////////////////////////////////////////////////////////
	//����ִ�к���ָ��
	/////////////////////////////////////////////////////////////////

 	BOOL (*PauseWork)();
 	BOOL (*StartWork)();
 	BOOL (*StopWork)();

};

