#include "StdAfx.h"
#include "SocketManage.h"

#include "MotionCard1.h"

#include "def.h"

#define CHECK_CODE_TIME 0.2

#define LogSock(LOGDATA) 	m_LockLog.Lock();\
strLog.Format(LOGDATA);\
CWlog(strLog);\
m_LockLog.Unlock();\

extern int g_nruningThread;

//#define TEST_COMMU  1


BOOL HandledData2(void* pData,CComSocket *pComSock)
{
	CSocketManage* pSockManage=(CSocketManage*)pData;
	pSockManage->HandledData(pComSock);
	return TRUE;
}
BOOL AcceptSock2(void* pData,SOCKET sock)
{
	CSocketManage* pSockManage=(CSocketManage*)pData;
	pSockManage->AcceptSock(sock);
	return TRUE;
}



CSocketManage::CSocketManage(void)
{
	g_nruningThread = 0;
	m_bIsSockLibNormal=FALSE;
	m_Server.HandledData=&HandledData2;
	m_Server.AcceptSock=&AcceptSock2;

	m_Server.pData=this;
	for (int i=0;i<MAX_CLINET_NUM;i++)
	{
		m_Client[i].HandledData=&HandledData2;
		m_Client[i].AcceptSock=&AcceptSock2;

		m_Client[i].pData=this;
	}
	ResetStatus();
	m_pData = NULL;
	m_pMotionCard = NULL;
}


CSocketManage::~CSocketManage(void)
{	//延时事件初始化
	HANDLE m_eWaitTimeEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	for (int i = 0; i < MAX_CLINET_NUM;i++)
	{
		m_Client[i].CloseSock();
	}
	while(g_nruningThread>0){
		Sleep(1);
		WaitForSingleObject(m_eWaitTimeEvent,10);
		MSG msg;
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	}
}


BOOL CSocketManage::InitSockLib()
{
	WORD wVersioRequested;
	WSADATA wsData;
	int nErrCode;
	wVersioRequested=MAKEWORD(2,2);
	nErrCode=WSAStartup(wVersioRequested,&wsData);

	if(nErrCode!=0)
	{
		AfxMessageBox("未找到可用DLL");

		m_bIsSockLibNormal=FALSE;
		return FALSE;
	}

	m_bIsSockLibNormal=TRUE;
	return TRUE;
}
BOOL CSocketManage::UninSockLib()
{
	if (!m_bIsSockLibNormal)
	{
		return TRUE;
	}

	WSACleanup();
	m_bIsSockLibNormal=FALSE;
	return TRUE;
}


BOOL CSocketManage::CloseServer()
{

	return TRUE;
}


BOOL CSocketManage::CloseAllClient()
{

	for (int i=0;i<MAX_CLINET_NUM ;i++)
	{
		m_Client[i].CloseSock();
	}

	return TRUE;
}


BOOL CSocketManage::HandledData(CComSocket *pComSock)
{
	WORD nValue=*(WORD*)&pComSock->recvData[0];


	if(pComSock->m_ntype==BARCODE)
	{
		m_nRecvDataNum = pComSock->nRecvNum;
		memcpy(m_cBarcode,pComSock->recvData,pComSock->nRecvNum);
		m_bRecvBarcodeDone=TRUE;
		TRACE("\n%s\n",m_cBarcode);
		return TRUE;
	}
	//	memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
	BOOL bRet=TRUE;
	switch(nValue)
	{
	case LOADMATERIAL_INFO:
		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=MSG_CONFORM;

			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
			bRet=msgPacket.CheckValue();
			resendMsgPacket.nRecvType=LOADMATERIAL_INFO;
			resendMsgPacket.bIsAoiOK=bRet;

			if (bRet)
			{
				m_bRecvData[msgPacket.nSide] = TRUE;
				m_dOffsetY[msgPacket.nSide] = msgPacket.doffsetY;

	//			TRACE("\n SUCC LOADMATERIAL_INFO:%0.3lf %0.3lf checkvalue:%d\n",msgPacket.dAoiRet[0],msgPacket.dAoiRet[1],bRet);
			}
			else
			{
	//			TRACE("\n FAILED LOADMATERIAL_INFO:%0.3lf %0.3lf checkvalue:%d\n",msgPacket.dAoiRet[0],msgPacket.dAoiRet[1],bRet);
			}

			SendConfirmMsgPacket(!bRet,pComSock,resendMsgPacket);
		}

		break;
	case MSG_CONFORM:
		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=MSG_CONFORM;
			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
			bRet=msgPacket.CheckValue();
			resendMsgPacket.nRecvType=MSG_CONFORM;
			resendMsgPacket.bIsAoiOK=bRet;
	//		TRACE("\n MSG_CONFORM:  checkvalue:%d\n",bRet);

			if (!msgPacket.bIsAoiOK)
			{
				ResendMsg(!bRet,pComSock,resendMsgPacket);
			}
		}

		break;
	case MACHINE_INFO:
		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=MSG_CONFORM;

			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
			bRet=msgPacket.CheckValue();
			pComSock->m_index=msgPacket.nSide;
			pComSock->m_ntype=COMMUNACATE;
			resendMsgPacket.nRecvType=MACHINE_INFO;
			resendMsgPacket.bIsAoiOK=bRet;
	//		TRACE("\n MACHINE_INFO:%d checkvalue:%d\n",msgPacket.nSide,bRet);     
			SendConfirmMsgPacket(!bRet,pComSock,resendMsgPacket);

		}

		break;
	case HEART_BREAK:
		break;
	case TASK_READY:
		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=MSG_CONFORM;

			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
			bRet=msgPacket.CheckValue();
			resendMsgPacket.nRecvType=TASK_READY;
			resendMsgPacket.bIsAoiOK=bRet;

	//		TRACE("\n MACHINE_INFO:%d checkvalue:%d\n",msgPacket.nSide,bRet);     
			SendConfirmMsgPacket(!bRet,pComSock,resendMsgPacket);

			DealRecvData(m_pData,msgPacket);

		}
		break;
// 	case TASK_START:
// 		{
// 			MsgPacket msgPacket;
// 
// 			MsgPacket resendMsgPacket; 
// 			resendMsgPacket.nType=MSG_CONFORM;
// 
// 			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
// 			bRet=msgPacket.CheckValue();
// 			resendMsgPacket.nRecvType=TASK_START;
// 			resendMsgPacket.bIsAoiOK=bRet;
// 
// 	//		TRACE("\n MACHINE_INFO:%d checkvalue:%d\n",msgPacket.nSide,bRet);     
// 			SendConfirmMsgPacket(!bRet,pComSock,resendMsgPacket);
// 
// 			DealRecvData(m_pData,msgPacket);
// 
// 		}
// 		break;
	case UNLOADPCIKMATERIAL_DONE:

		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=MSG_CONFORM;

			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
			bRet=msgPacket.CheckValue();
			resendMsgPacket.nRecvType=UNLOADPCIKMATERIAL_DONE;
			resendMsgPacket.bIsAoiOK=bRet;

			m_bIsUnloadDone[msgPacket.nSide]=TRUE/*msgPacket.bIsAoiOK*/;


	//		TRACE("\n MACHINE_INFO:%d checkvalue:%d\n",msgPacket.nSide,bRet);     
			SendConfirmMsgPacket(!bRet,pComSock,resendMsgPacket);

		}

		break;
	case LOADPUTMATERIAL_DONE:

		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=MSG_CONFORM;


			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
			bRet=msgPacket.CheckValue();
			resendMsgPacket.nRecvType=LOADPUTMATERIAL_DONE;
			resendMsgPacket.bIsAoiOK=bRet;

			m_bIsUnloadDone[msgPacket.nSide]=TRUE/*msgPacket.bIsAoiOK*/;     
			SendConfirmMsgPacket(!bRet,pComSock,resendMsgPacket);

		}


		break;
	case CALIBRATEBOARD_START:

		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=MSG_CONFORM;


			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
			bRet=msgPacket.CheckValue();
			resendMsgPacket.nRecvType=CALIBRATEBOARD_START;
			resendMsgPacket.bIsAoiOK=bRet;

			resendMsgPacket.nRecvType=CALIBRATEBOARD_DONE;
			resendMsgPacket.nSide=msgPacket.nSide;
			resendMsgPacket.CalculateValue();

			m_bRequrCalibrateBoard[msgPacket.nSide] = TRUE;

//			TRACE("\n MACHINE_INFO:%d checkvalue:%d\n",msgPacket.nSide,bRet);     
			//  SendConfirmMsgPacket(!bRet,pComSock,resendMsgPacket);
		}

		break;
	case CALIBRATEBOARD_DONE:
		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=MSG_CONFORM;


			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
			bRet=msgPacket.CheckValue();
			resendMsgPacket.nRecvType=CALIBRATEBOARD_DONE;
			resendMsgPacket.bIsAoiOK=bRet;

			//	   m_bIsUnloadDone[msgPacket.nSide]=TRUE/*msgPacket.bIsAoiOK*/;

			m_bCalibrateBoardDone[pComSock->m_index*2+msgPacket.nSide] = TRUE;

//			TRACE("\n MACHINE_INFO:%d checkvalue:%d\n",msgPacket.nSide,bRet);     
			SendConfirmMsgPacket(!bRet,pComSock,resendMsgPacket);

		}

		break;
	case CALLIBRATECAPBMP_START:
		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=MSG_CONFORM;


			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
			bRet=msgPacket.CheckValue();
			resendMsgPacket.nRecvType=CALIBRATEBOARD_DONE;
			resendMsgPacket.bIsAoiOK=bRet;

			//	m_bCalibrateBoardDone[pComSock->m_index*4+msgPacket.nSide];
			m_bCalWalk[msgPacket.nSide] = TRUE;
#ifdef TEST_COMMU
			MsgPacket  msg;
			msg.nType=CALLIBRATECAPBMP_READY;
			msg.nSide=msgPacket.nSide;

			SendMsg(msg);


#endif


//			TRACE("\n MACHINE_INFO:%d checkvalue:%d\n",msgPacket.nSide,bRet);     
			SendConfirmMsgPacket(!bRet,pComSock,resendMsgPacket);
		}

		break;

	case CALLIBRATECAPBMP_READY:
		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=MSG_CONFORM;

			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
			bRet=msgPacket.CheckValue();
			resendMsgPacket.nRecvType=CALLIBRATECAPBMP_READY;
			resendMsgPacket.bIsAoiOK=bRet;

			m_bIsCambmpReady[/*pComSock->m_index*2+*/msgPacket.nSide] = TRUE;

	//		TRACE("\n MACHINE_INFO:%d checkvalue:%d\n",msgPacket.nSide,bRet);     
			SendConfirmMsgPacket(!bRet,pComSock,resendMsgPacket);

		}

		break;

	case CALIBRATECAPBMP_DONE:

		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=MSG_CONFORM;

			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
			bRet=msgPacket.CheckValue();
			resendMsgPacket.nRecvType=CALIBRATECAPBMP_DONE;
			resendMsgPacket.bIsAoiOK=bRet;

			m_bIsCapbmpDone[pComSock->m_index*2+msgPacket.nSide] = TRUE;

//			TRACE("\n MACHINE_INFO:%d checkvalue:%d\n",msgPacket.nSide,bRet);     
			SendConfirmMsgPacket(!bRet,pComSock,resendMsgPacket);

		}

		break;

	case CALIBRATECAPBMP_FINISH:
		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=MSG_CONFORM;


			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
			bRet=msgPacket.CheckValue();
			resendMsgPacket.nRecvType=CALIBRATECAPBMP_FINISH;
			resendMsgPacket.bIsAoiOK=bRet;

			//	m_bIsCambmpReady[pComSock->m_index*2+msgPacket.nSide];

//			TRACE("\n MACHINE_INFO:%d checkvalue:%d\n",msgPacket.nSide,bRet);     
			SendConfirmMsgPacket(!bRet,pComSock,resendMsgPacket);
		}

		break;

	case CALLIBRATECAPBMP_SINGMOV:
		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=MSG_CONFORM;

			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
			bRet=msgPacket.CheckValue();
			resendMsgPacket.nRecvType=CALLIBRATECAPBMP_SINGMOV;
			resendMsgPacket.bIsAoiOK=bRet;

			//	m_bIsCambmpReady[pComSock->m_index*2+msgPacket.nSide];

#ifdef TEST_COMMU
			MsgPacket  msg;
			msg.nType=CALIBRATECAPBMP_DONE;
			msg.nSide=msgPacket.nSide;

			SendMsg(msg);


#endif

	//		TRACE("\n MACHINE_INFO:%d checkvalue:%d\n",msgPacket.nSide,bRet);     
			SendConfirmMsgPacket(!bRet,pComSock,resendMsgPacket);

		}
		break;

	case STEP_MOV:
		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=MSG_CONFORM;

			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));

			if (m_pMotionCard!=NULL  && m_nAxis[msgPacket.nSide]!=-1)
			{
                 m_pMotionCard->TMoveRelInMode(m_nAxis[msgPacket.nSide],msgPacket.doffsetY,SPEED_MIDDLE);
			}
 
		}
		break;

	case MOTIONCARD_RETURNPOS:
		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=MSG_CONFORM;


			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
			bRet=msgPacket.CheckValue();
			resendMsgPacket.nRecvType=CALIBRATECAPBMP_DONE;
			resendMsgPacket.bIsAoiOK=bRet;

			m_bmotionCardRecePos[pComSock->m_index*2+msgPacket.nSide] = TRUE;
			m_dmotionCardRecePos[pComSock->m_index*2+msgPacket.nSide] = msgPacket.doffsetY;
			//			TRACE("\n MACHINE_INFO:%d checkvalue:%d\n",msgPacket.nSide,bRet);     
			SendConfirmMsgPacket(!bRet,pComSock,resendMsgPacket);
 
		}
		break;
	case MOTIONCARD_GETPOS://假如获得返回值
		{
			MsgPacket msgPacket;

			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));

			if (m_pMotionCard!=NULL  && m_nAxis[msgPacket.nSide]!=-1)
			{
//                 m_pMotionCard->TMoveRelInMode(m_nAxis[msgPacket.nSide],msgPacket.doffsetY,SPEED_MIDDLE);
				 m_pMotionCard->pMotor[m_nAxis[msgPacket.nSide]]->WaitMotionDone();
				 double curpos = m_pMotionCard->GetCurPos(m_nAxis[msgPacket.nSide]);
				 MsgPacket msg;
				 msg.nSide = msgPacket.nSide;
				 msg.nType = MOTIONCARD_RETURNPOS;
				 msg.doffsetY = curpos;
				 msg.CalculateValue();
				 SendMsgClient(msg,0);
			}
 
		}
		break;
	case SERVER_OFF:
		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=SERVER_OFF;

			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));

			if (msgPacket.bIsAoiOK)
			{
				m_bIsAxisServOff[msgPacket.nSide] = TRUE;
			}

		}
		break;

	case  LOADPLATFORM_NOZZLE_CHECK_RET:
		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=LOADPLATFORM_NOZZLE_CHECK_RET;

			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));

			
			m_bIsLoadDone[pComSock->m_index*2+msgPacket.nSide] = TRUE;
			
			m_bIsLoadDoneOK[pComSock->m_index*2+msgPacket.nSide] = msgPacket.bIsAoiOK;
		}
		break;
	case  LOADPLATFORM_NOZZLE_CHECK_FINISH:
		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=LOADPLATFORM_NOZZLE_CHECK_RET;

			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));


            m_bIsLoadFinish[msgPacket.nSide] = TRUE;


			m_bIsLoadFinishOK[msgPacket.nSide] = msgPacket.bIsAoiOK;

		}
		break;

	case  UNLOADPLATFORM_NOZZLE_CHECK_RET:
		{
			

		}
		break;


	case LOAD_X_ARRIVED:
		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=LOAD_X_ARRIVED;

			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));


			m_bIsLoadXArrived[msgPacket.nSide] = TRUE;
		}
		
		
		break;
	case LOAD_Y_ARRIVED:
		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=LOAD_Y_ARRIVED;

			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));


			m_bIsLoadYArrived[pComSock->m_index*2+msgPacket.nSide] = TRUE;
		}
		
		break;

	case UNLOAD_X_ARRIVED:
		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=UNLOAD_X_ARRIVED;

			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));


			m_bIsUnloadYArrived[pComSock->m_index*2+msgPacket.nSide] = TRUE;
		}
		break;

	case UNLOAD_X_SUCK_ARRIVED:	//下料吸嘴到位
		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=UNLOAD_X_SUCK_ARRIVED;

			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));


			m_bIsUnLoadXArrived[msgPacket.nSide] = TRUE;
		}
		break;
	case  LOADPLATFORM_CANLOAD:
		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=LOADPLATFORM_CANLOAD;

			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));


			m_bHasRecvLoadRequest[msgPacket.nSide] = TRUE;

		}
		break;
	case LOADPLATFORM_CANLOADCONFIRM:
		{
			MsgPacket msgPacket;

			MsgPacket resendMsgPacket; 
			resendMsgPacket.nType=LOADPLATFORM_CANLOADCONFIRM;

			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));


			m_bIsRecvLoadReady[pComSock->m_index*2+msgPacket.nSide] = TRUE;

			m_bIsLoadReady[pComSock->m_index*2+msgPacket.nSide] = msgPacket.bIsAoiOK;
		}
		break;
	case TASK_STOP:
		{
			MsgPacket msgPacket;
			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
			m_bTaskStop = TRUE;
		}
		break;
	case TASK_START:
		{
			MsgPacket msgPacket;
			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
			m_bTaskStart = TRUE;
		}
		break;
	case TASK_PAUSE:
		{
			MsgPacket msgPacket;
			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
			m_bTaskPause = TRUE;
		}
		break;
	case TASK_CONTINUE:
		{
			MsgPacket msgPacket;
			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
			m_bTaskContinue = TRUE;
		}
		break;
	case STATUS_HADORI:
		{
			MsgPacket msgPacket;
			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
			m_bMachHadOri[pComSock->m_index] = TRUE;
		}
		break;
	case STATUS_HADLOADTASK:
		{
			MsgPacket msgPacket;
			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
			m_bMachReady[pComSock->m_index] = TRUE;
		}
		break;
	case STATUS_TASKERR:
		{
			MsgPacket msgPacket;
			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
			m_bMachUnReady[pComSock->m_index] = TRUE;
		}
		break;
	case STATUS_Breeze:
		{
			MsgPacket msgPacket;
			memcpy((void*)&msgPacket,&pComSock->recvData[0],sizeof(MsgPacket));
			m_bMachRing[pComSock->m_index] = TRUE;
			m_bMachErrCode[pComSock->m_index] = (int)msgPacket.doffsetY;
		}
		break;
	default:
		break;
	}

	return TRUE;
}


BOOL CSocketManage::AcceptSock(SOCKET sock)
{
	int nIdleIndex=-1;
	for (int i=0;i<MAX_CLINET_NUM;i++)
	{
		if (!m_Client[i].m_bIsConn)
		{
			nIdleIndex=i;
			break;
		}
	}

	if (nIdleIndex!=-1)
	{
		m_Client[nIdleIndex].m_bIsWork =TRUE;
		m_Client[nIdleIndex].m_sock=sock;
		m_Client[nIdleIndex].m_bIsConn=TRUE;
		m_Client[nIdleIndex].StartRecieveThread();
		return TRUE;
	}
	return FALSE;
}


BOOL CSocketManage::InitServer(char* servAddr,UINT nPort)
{
	m_Server.InitServer(servAddr,nPort);
	return TRUE;
}


BOOL CSocketManage::InitClient(char* servAddr,UINT nPort)
{
	int nIdleIndex=-1;
	for (int i=0;i<MAX_CLINET_NUM;i++)
	{
		if (!m_Client[i].m_bIsConn)
		{
			nIdleIndex=i;
			break;
		}
	}

	if (nIdleIndex!=-1)
	{
		m_Client[nIdleIndex].InitClient(servAddr,nPort);
		return TRUE;
	}
	return FALSE;
}

BOOL CSocketManage::CheckSockIsOnline()
{

	MsgPacket msgPacket;
	msgPacket.nType=HEART_BREAK;

	int len=sizeof(MsgPacket)+1;
	char msg[64];
	memcpy(msg,(void*)&msgPacket,len);
	msg[len]=13;

	for (int i=0;i<MAX_CLINET_NUM;i++)
	{
		BOOL bRet=m_Client[i].CheckIsOnline(msg,len+1);
		//		TRACE("\nindex:%d status:%d\n",i,bRet);
	}
	return TRUE;
}


BOOL CSocketManage::SendMsg(char *msg,int msgLen,int nIndex)
{
	if (!m_Client[nIndex].m_bIsConn)
	{
		return FALSE;
	}
	int nErrCode=0;
	nErrCode=m_Client[nIndex].SendData(msg,msgLen);
	if (nErrCode==-1)
	{
		AfxMessageBox("消息发送失败");
		return FALSE;
	}
	return TRUE;
}

BOOL CSocketManage::SendMsg(MsgPacket msg,int nIndex)//测试用  发送数据用
{
	int nChosseIndex=-1;

	if ((nChosseIndex=GetAxisSocket(nIndex))==-1)
	{
		AfxMessageBox("对应机台已经断开，请重新连接");
		return FALSE;
	}

	if (!m_Client[nChosseIndex].m_bIsConn)
	{
       AfxMessageBox("对应机台已经断开，请重新连接");
		return FALSE;
	}

	m_lastMsgPacket[nChosseIndex]=msg;

	int nErrCode=0;
	char msgchar[64]={0};
	msg.CalculateValue();
	int nLen=sizeof(msg);
	memcpy(msgchar,(void*)&msg,sizeof(msg));
	msgchar[nLen]=13;
	nErrCode=m_Client[nChosseIndex].SendData(msgchar,nLen+1);
	if (nErrCode==-1)
	{
		AfxMessageBox("消息发送失败");
		return FALSE;
	}
	return TRUE;
}

BOOL CSocketManage::SendMsgServ(MsgPacket msg,int nIndex)
{
	return SendMsg(msg,nIndex);
}
BOOL CSocketManage::SendMsgClient(MsgPacket msg,int nIndex)
{
	if (nIndex==-1)
	{
		return FALSE;
	}
	if (!m_Client[nIndex].m_bIsConn)
	{
		AfxMessageBox("未连接");	
		return FALSE;
	}

	m_lastMsgPacket[nIndex]=msg;

	int nErrCode=0;
	char msgchar[64]={0};
	msg.CalculateValue();
	int nLen=sizeof(msg);
	memcpy(msgchar,(void*)&msg,sizeof(msg));
	msgchar[nLen]=13;
	nErrCode=m_Client[nIndex].SendData(msgchar,nLen+1);
	if (nErrCode==-1)
	{
		AfxMessageBox("消息发送失败");
		return FALSE;
	}
	return TRUE;
}

void CSocketManage::ResendMsg(BOOL bNeedResend,CComSocket* pSock,MsgPacket msg)
{
	return;

	if (bNeedResend)
	{
		return;
	}

	int SendIndex=-1;
	for(int i=0;i<MAX_CLINET_NUM;i++)
	{
		if (pSock==&m_Client[i])
		{
			SendIndex=i;
			break;
		}
	}

	if (SendIndex!=-1)
	{
		char msgchar[64];
		int nLen=sizeof(MsgPacket);
		m_lastMsgPacket[SendIndex].CalculateValue();
		memcpy(msgchar,(void*)&m_lastMsgPacket[SendIndex],nLen);

		m_lastMsgPacket[SendIndex].bIsAoiOK=TRUE;
		m_lastMsgPacket[SendIndex].CalculateValue();


		msgchar[nLen]=13;

		pSock->SendData(msgchar,nLen+1);
	}


}

BOOL CSocketManage::SendConfirmMsgPacket(BOOL bNeedResend,CComSocket* pSock,MsgPacket msg)
{
	return FALSE;

	char msgchar[64];
	int nLen=sizeof(MsgPacket);

	msg.CalculateValue();

	memcpy(msgchar,(void*)&msg,nLen);

	msgchar[nLen]=13;

	pSock->SendData(msgchar,nLen+1);
	return TRUE;
}


BOOL CSocketManage::InitClientBarCodeReader(char* servAddr,UINT nPort)//初始化二维码读头
{
	int nIdleSockIndex=-1;
	if ((nIdleSockIndex=GetIdleSocket())==-1)
	{
		return FALSE;
	}

	if (!m_Client[nIdleSockIndex].InitClient(servAddr,nPort))
	{
		return FALSE;
	}

	m_Client[nIdleSockIndex].m_ntype=BARCODE;

	return TRUE;
}


BOOL CSocketManage::InitClientSendAoidata(char* servAddr,UINT nPort)//初始化上传数据
{
	int nIdleSockIndex=-1;
	if ((nIdleSockIndex=GetIdleSocket())==-1)
	{
		return FALSE;
	}

	if (!m_Client[nIdleSockIndex].InitClient(servAddr,nPort))
	{
		return FALSE;
	}
	m_Client[nIdleSockIndex].m_ntype=SENDAOIRET;
	return TRUE;
}


BOOL CSocketManage::SendReadBarcodeCmd()//发送读取二维码命令
{
	m_LockLog.Lock();
	strLog.Format("ip信号： 发送IP信号 SendReadBarcodeCmd 发送编号是%d" , 0);
	CWlog(strLog);
	m_LockLog.Unlock();
	int nBarcodeIndex;
	if ((nBarcodeIndex=FindBarcodeReaderIndex())==-1)
	{
		return FALSE;
	}

	char msg[128]={0};
	msg[0]='L';
	msg[1]='O';
	msg[2]='N';
	msg[3]=0x0d;

	BOOL bRet=m_Client[nBarcodeIndex].SendData(msg,4);
	//	send(m_barcodesock,msg,4,0);


	LTimeCount mt;
	mt.Start();
	mt.End();
	while(mt.GetUseTime()<CHECK_CODE_TIME)
	{
		MSG msg;
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
			Sleep(1);
		mt.End();
	}

	msg[0]='L';
	msg[1]='O';
	msg[2]='F';
	msg[3]='F';
	msg[4]=0x0d;


	bRet=m_Client[nBarcodeIndex].SendData(msg,5);

	return TRUE;
}
BOOL CSocketManage::SendBarCodeAndAoiRet()//发送AOI检测结果及二维码
{

	return TRUE;
}

int CSocketManage::GetIdleSocket()
{
	int nIdleSockIndex=-1;
	for(int i=0;i<MAX_CLINET_NUM;i++)
	{
		if (!m_Client[i].m_bIsConn)
		{
			nIdleSockIndex=i;
			break;
		}
	}

	return nIdleSockIndex;

}


int CSocketManage::FindBarcodeReaderIndex()
{
	for(int i=0;i<MAX_CLINET_NUM;i++)
	{
		if (m_Client[i].m_ntype==BARCODE)
		{
			return i;
		}
	}

	return -1;
}

int CSocketManage::FindSendAoidataIndex()
{
	for(int i=0;i<MAX_CLINET_NUM;i++)
	{
		if (m_Client[i].m_ntype==SENDAOIRET)
		{
			return i;
		}
	}
	return -1;
}

BOOL CSocketManage::GetRecvOffsetY(int &nSide,double &dOffsetY)//查询是否接受数据完毕
{

	for (int i=0;i<2;i++)
	{
		if (m_bRecvData[i])
		{
			nSide = i;
			dOffsetY = m_dOffsetY[i];

			m_bRecvData[i] = FALSE;
			return TRUE;
		}
	}


	return FALSE;
}

BOOL CSocketManage::GetConnStatus(int nMacIndex)
{
	int nAxisIndex = -1;
	for (int i=0;i<MAX_CLINET_NUM;i++)
	{
		if (m_Client[i].m_index == nMacIndex)
		{
			nAxisIndex = i;
			break;
		}
	}

	if (nAxisIndex == -1)
	{
		return FALSE;
	}

	return m_Client[nAxisIndex].m_bIsConn;
}


BOOL CSocketManage::GetIsCalibrateBoardDone(int nAxis)
{
	if (m_bCalibrateBoardDone[nAxis])
	{
		m_bCalibrateBoardDone[nAxis] = FALSE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

BOOL CSocketManage::GetIsCalibrateCambmpDone(int nAxis)
{
	if (m_bIsCapbmpDone[nAxis])
	{
		m_bIsCapbmpDone[nAxis] = FALSE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

BOOL CSocketManage::GetIsCalibrateCambmpReady(int nAxis)  //是否对应轴标定板完成
{
	if (m_bIsCambmpReady[nAxis])
	{
		m_bIsCambmpReady[nAxis] = FALSE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int CSocketManage::GetAxisSocket(int nIndexAxis)
{
	int nAxisIndex = -1;
	for (int i=0;i<MAX_CLINET_NUM;i++)
	{
		if (m_Client[i].m_index == nIndexAxis/2)
		{
			nAxisIndex = i;
			break;
		}
	}

	return nAxisIndex;
}


BOOL CSocketManage::GetAxisIsServOff(int nSide)
{
	if (m_bIsAxisServOff[nSide])
	{
		m_bIsAxisServOff[nSide] = FALSE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CSocketManage::GetLoadFinish(int nSide)
{
	if (m_bIsLoadFinish[nSide])
	{
		m_bIsLoadFinish[nSide] = FALSE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}
BOOL CSocketManage::GetLoadDone(int nAxis)
{
	if (m_bIsLoadDone[nAxis])
	{
		m_bIsLoadDone[nAxis] = FALSE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CSocketManage::GetLoadDone(int nAxis,BOOL &bLoadDoneOK)
{
	if (m_bIsLoadDone[nAxis])
	{
		m_bIsLoadDone[nAxis] = FALSE;
		bLoadDoneOK = m_bIsLoadDoneOK[nAxis];
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
}
BOOL CSocketManage::GetLoadFinish(int nSide,BOOL &bLoadDoneOK)
{
	if (m_bIsLoadFinish[nSide])
	{
		m_bIsLoadFinish[nSide] = FALSE;
		bLoadDoneOK = m_bIsLoadFinishOK[nSide];
	}
	else
	{
		return FALSE;
	}
}


BOOL CSocketManage::GetUnloadDone(int nSide)
{
	if (m_bIsUnloadDone[nSide])
	{
		m_bIsUnloadDone[nSide] = FALSE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}


BOOL CSocketManage::GetIsLoadXArrived(int nSide)
{
	if (m_bIsLoadXArrived[nSide])
	{
        m_bIsLoadXArrived[nSide]=FALSE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
BOOL CSocketManage::GetIsLoadYArrived(int nAxis)
{
	if (m_bIsLoadYArrived[nAxis])
	{
		m_bIsLoadYArrived[nAxis]=FALSE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
BOOL CSocketManage::GetIsUnloadXArrived(int nAxis)
{
	if (m_bIsUnloadYArrived[nAxis])
	{
		m_bIsUnloadYArrived[nAxis]=FALSE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


BOOL CSocketManage::SendAllAxisIsServOff()
{
	
	return TRUE;
}


BOOL CSocketManage::SendLoadDone(BOOL bIsOK,int nSide) //发送吸盘吸取结果
{
	m_LockLog.Lock();
	strLog.Format("ip信号： 发送IP信号 SendLoadDone 发送编号是%d" , nSide);
	CWlog(strLog);
	m_LockLog.Unlock();
	MsgPacket msg;
	msg.nSide = nSide;
	msg.nType = LOADPLATFORM_NOZZLE_CHECK_RET;
	msg.bIsAoiOK = bIsOK;
	msg.CalculateValue();

	return SendMsgClient(msg,0);
}
BOOL CSocketManage::SendLoadFinish(BOOL bIsOK,int nAxis)//发送上料完成信号
{
	m_LockLog.Lock();
	strLog.Format("ip信号： 发送IP信号 SendLoadFinish 发送编号是%d" , nAxis);
	CWlog(strLog);
	m_LockLog.Unlock();
	MsgPacket msg;
	msg.nSide = nAxis%2;
	msg.nType = LOADPLATFORM_NOZZLE_CHECK_FINISH;
	msg.bIsAoiOK = bIsOK;
    msg.CalculateValue();

    return SendMsgServ(msg,nAxis);
}


BOOL CSocketManage::SendXLoadArrived(int nAxis)  //发送上料X轴到位信号
{
	m_LockLog.Lock();
	strLog.Format("ip信号： 发送IP信号 SendXLoadArrived 发送编号是%d" , nAxis);
	CWlog(strLog);
	m_LockLog.Unlock();
	MsgPacket msg;
	msg.nSide = nAxis%2;
	msg.nType = LOAD_X_ARRIVED;
	msg.CalculateValue();

	return SendMsgServ(msg,nAxis);
}

BOOL CSocketManage::SendYLoadArrived(int nSide)//发送上料Y轴到位信号
{
	m_LockLog.Lock();
	strLog.Format("ip信号： 发送IP信号 SendYLoadArrived 发送编号是%d" , nSide);
	CWlog(strLog);
	m_LockLog.Unlock();
	MsgPacket msg;
	msg.nSide = nSide;
	msg.nType = LOAD_Y_ARRIVED;
	msg.CalculateValue();

	return SendMsgClient(msg,0);
}

BOOL CSocketManage::SendYUnloadArrived(int nSide)//发送下料Y轴到位信号
{
	m_LockLog.Lock();
	strLog.Format("ip信号： 发送IP信号 SendYUnloadArrived 发送编号是%d" , nSide);
	CWlog(strLog);
	m_LockLog.Unlock();
	MsgPacket msg;
	msg.nSide = nSide;
	msg.nType = UNLOAD_X_ARRIVED;
	msg.CalculateValue();

	return SendMsgClient(msg,0);
}

BOOL CSocketManage::SendMachineInfo(int nIndex)     //发送设备信息
{
	m_LockLog.Lock();
	strLog.Format("ip信号： 发送IP信号 SendMachineInfo 发送编号是%d" , nIndex);
	CWlog(strLog);
	m_LockLog.Unlock();
	MsgPacket msg;
	msg.nSide = nIndex;
	msg.nType = MACHINE_INFO;
	msg.CalculateValue();

	return SendMsgClient(msg,0);
}


BOOL CSocketManage::SendPrelocateInfo(int nAxis,double dAoiRet1,double dAoiRet2,BOOL bIsAoiOk,double dOffsetY)
{

	m_LockLog.Lock();
	strLog.Format("ip信号： 发送IP信号 SendPrelocateInfo 发送编号是%d" , nAxis);
	CWlog(strLog);
	m_LockLog.Unlock();
	MsgPacket msg;

	msg.nType=LOADMATERIAL_INFO;
	msg.nSide=nAxis%2;

	msg.dAoiRet[0]= dAoiRet1;//AOIbing结果
	msg.dAoiRet[1]= dAoiRet2;
	msg.bIsAoiOK = bIsAoiOk;
	msg.doffsetY = dOffsetY;

	msg.CalculateValue();

	return SendMsgServ(msg,nAxis);
}

BOOL CSocketManage::ResetStatus()
{

	memset(m_cBarcode,0,30);


	for (int i=0;i<8;i++)
	{
		m_bIsCapbmpDone[i]  = FALSE;  //是否采集单帧完成
		m_bIsCambmpReady[i] = FALSE;  //是否采集图像准备好
		m_bCalibrateBoardDone[i] = FALSE;
		m_bIsLoadYArrived[i] = FALSE;//是否上料Y到位
		m_bIsUnloadYArrived[i] = FALSE; //是否下料Y到位
		m_bIsLoadDone[i]    = FALSE;   //是否上料完成
		m_bIsRecvLoadReady[i]  = FALSE ;
		m_bIsLoadReady[i]      = FALSE ;
		m_bIsLoadDone[i] = FALSE;   //是否上料完成
		m_bIsLoadDoneOK[i] = FALSE;  //
		m_bMachHadOri[i]  = FALSE;	
		m_bMachReady[i]  = FALSE;
		m_bMachUnReady[i]  = FALSE;
		m_bMachRing[i]  = FALSE;
		m_bMachErrCode[i] = -1;
		m_bmotionCardRecePos[i] = FALSE;
		m_dmotionCardRecePos[i] = 0.0;
	}
	for (int i = 0; i < 2;i++)
	{
		m_bHasRecvLoadRequest[i] = FALSE;
		m_bIsAxisServOff[i] =FALSE;
		m_bIsLoadFinishOK[i] =FALSE;	
		m_bIsUnloadDone[i] =FALSE;	
		m_bIsLoadFinish[i] =FALSE;	
		m_bRequrCalibrateBoard[i] =FALSE;		
		m_bRecvData[i]=FALSE;
		m_bIsLoadXArrived[i] = FALSE;//是否上料X到位
		m_dOffsetY[i]=0.2;
		m_nAxis[i] = -1;	
		m_bCalWalk[i] = FALSE;
		m_bIsUnLoadXArrived[i] = FALSE;//是否吸嘴到位
	}

	m_bTaskStop = FALSE;
	m_bTaskPause = FALSE;	
	m_bTaskContinue = FALSE;
	m_bTaskStart = FALSE;	
	return TRUE;
}
BOOL CSocketManage::GetIsLoadReady(int nAxis,BOOL& IsLoadReady)
{
	if (m_bIsRecvLoadReady[nAxis])
	{
		m_bIsRecvLoadReady[nAxis] = FALSE;
		IsLoadReady = m_bIsLoadReady[nAxis];
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	
}

BOOL CSocketManage::GetIsRecvLoadRequest(int nSide)
{

	if (m_bHasRecvLoadRequest[nSide])
	{
       m_bHasRecvLoadRequest[nSide] = FALSE;
	   return TRUE;
	} 
	else
	{
		return FALSE;
	}
}


BOOL CSocketManage::SendAllStartWork()
{

	LogSock("ip信号： 全部开始")
	for (int i=0;i<8;i++)
	{
		SendSingalStatue(TASK_START,i);
	}
	return TRUE;
}
BOOL CSocketManage::SendAllStopWork()
{

	LogSock("ip信号： 全部停止")
	for (int i=0;i<8;i++)
	{
		SendSingalStatue(TASK_STOP,i);
	}
	return TRUE;
}
BOOL CSocketManage::SendAllPauseWork()
{
	LogSock("ip信号： 全部暂停")
	for (int i=0;i<8;i++)
	{
		SendSingalStatue(TASK_PAUSE,i);
	}
	return TRUE;
}

BOOL CSocketManage::CheckIsBarcodeConn() //检测扫描枪是否连接
{
	int nBarcodeIndex = -1;
	if ((nBarcodeIndex=FindBarcodeReaderIndex())==-1)
	{
		return FALSE;
	}

	return m_Client[nBarcodeIndex].m_bIsConn;
}
BOOL CSocketManage::CheckMacConn(int nAxis)//检测机器是否连接
{
	int nSockIndex = -1;
	if ((nSockIndex=GetAxisSocket(nAxis/2))==-1)
	{
		return FALSE;
	}

	return m_Client[nSockIndex].m_bIsConn;
}

BOOL CSocketManage::GetIsRequrCalibrateBoard(int nSide)
{
	if (m_bRequrCalibrateBoard[nSide])
	{
		m_bRequrCalibrateBoard[nSide] = FALSE;
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
}

BOOL CSocketManage::GetbCalWalk(int nSide)
{
	if (m_bCalWalk[nSide])
	{
		m_bCalWalk[nSide] = FALSE;
		return TRUE;
	} 
	else
	{
		return FALSE;
	}

}

BOOL CSocketManage::GetStopWork()
{
	if (m_bTaskStop)
	{
		m_bTaskStop = FALSE;
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
}

BOOL CSocketManage::GetIsUnLoadXArrived2(int nSide)
{
	if (m_bIsUnLoadXArrived[nSide])
	{
		m_bIsUnLoadXArrived[nSide]=FALSE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CSocketManage::SendXUnloadArrived(int nAxis)
{
	m_LockLog.Lock();
	strLog.Format("ip信号： 发送IP信号 SendXUnloadArrived 发送编号是%d" , nAxis);
	CWlog(strLog);
	m_LockLog.Unlock();
	MsgPacket msg;
	msg.nSide = nAxis%2;
	msg.nType = UNLOAD_X_SUCK_ARRIVED;
	msg.CalculateValue();

	return SendMsgServ(msg,nAxis);
}

BOOL CSocketManage::TESTGETALLSINGAL()
{
	bool ret;
	double offset;
	while(1){
		for (int i = 0; i < 8; i++)
		{
			ret =  GetIsCalibrateCambmpDone(i);			//是否采图完成
			if (ret)
			{
				strLog.Format("服务器：获得采图完成信号,信号%d",i);AfxMessageBox(strLog); ret = false;
			}

			ret =  GetIsCalibrateBoardDone(i);			//是否对应轴标定板完成
			if (ret)
			{
				strLog.Format("服务器：获得标定板完成信号,信号%d",i);AfxMessageBox(strLog); ret = false;
			}

			ret =  GetIsCalibrateCambmpReady(i);		//是否采集图像准备好
			if (ret)
			{
				strLog.Format("服务器：获得采集图像准备好信号,信号%d",i);AfxMessageBox(strLog); ret = false;
			}

// 			ret =  GetAxisSocket(i);					//获取轴号对应的通信套接字编号
// 			if (ret)
// 			{
// 				strLog.Format("服务器：获得轴号对应的通信套接字编号,信号%d",i);AfxMessageBox(strLog); ret = false;
// 			}

			ret =  GetIsLoadYArrived(i);						//上料到位
			if (ret)
			{
				strLog.Format("服务器：收到上料y轴到位,信号%d",i);AfxMessageBox(strLog); ret = false;
			}

			ret =  GetLoadDone(i);						//上料机器接收到信号已离开
			if (ret)
			{
				strLog.Format("服务器：收到上料机器接收到信号已离开,信号%d",i);AfxMessageBox(strLog); ret = false;
			}

			ret =  GetIsUnloadXArrived(i);						//收到上料吸嘴已关闭信号
			if (ret)
			{
				strLog.Format("服务器：收到上料吸嘴已关闭信号,信号%d",i);AfxMessageBox(strLog); ret = false;
			}


			ret =  GetComputerReady(i);							//软件已经回过原，可以控制它开始
			if (ret)
			{
				strLog.Format("服务器：回过原信号,信号%d",i);AfxMessageBox(strLog); ret = false;
			}
			ret =  GetMachReady(i);						//收到软件上线信号
			if (ret)
			{
				strLog.Format("服务器：收到软件上线信号,信号%d",i);AfxMessageBox(strLog); ret = false;
			}
			ret =  GetMachUnReady(i);						//收到软件下线信号
			if (ret)
			{
				strLog.Format("服务器：收到软件下线信号,信号%d",i);AfxMessageBox(strLog); ret = false;
			}

		}
		for (int i = 0; i < 2; i++)
		{
			ret =  GetRecvOffsetY(i,offset);			//查询是否接受数据完毕
			if (ret)
			{
				strLog.Format("客户端：接收到偏移量,信号%d",i);AfxMessageBox(strLog); ret = false;
			}

			ret =  GetIsRequrCalibrateBoard(i);			//检测是否要开始标定标定板
			if (ret)
			{
				strLog.Format("客户端：接收到开始标定标定板信号,信号%d",i);AfxMessageBox(strLog); ret = false;
			}

			ret =  GetbCalWalk(i);						//检测是否要开始走标
			if (ret)
			{
				strLog.Format("客户端：接收到开始走标信号,信号%d",i);AfxMessageBox(strLog); ret = false;
			}

			ret =  GetStopWork();						//检测是否停止
			if (ret)
			{
				strLog.Format("客户端：接收到停止运动信号,信号%d",i);AfxMessageBox(strLog); ret = false;
			}
			ret =  GetIsUnLoadXArrived2(i);						//检测下料吸嘴是否到了
			if (ret)
			{
				strLog.Format("客户端：收到主机吸嘴到位信号,信号%d",i);AfxMessageBox(strLog); ret = false;
			}

		}



		MSG msg;
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	}


}

BOOL CSocketManage::TestSendSingleMsg(int SingalType,int nSide)
{
	//通信，告诉服务器
	switch(SingalType){
	case 0:
		SendLoadDone(TRUE,nSide);  //发送吸盘吸取结果  客户端发服务器
		break;
	case 1:
		SendYLoadArrived(nSide);//发送上料Y轴到位信号
		break;
	case 2:
		SendYUnloadArrived(nSide);//发送下料Y轴到位信号
		break;
	case 3:	
		SendLoadFinish(TRUE,nSide);//发送上料完成信号  服务器发客户端
		break;
	case 4:
		SendXLoadArrived(nSide);  //发送上料X轴到位信号
		break;
	case 5:
		SendXUnloadArrived(nSide);//通知客户端下料吸嘴已经到位
		break;
	case 6:
		SendAllStartWork();
		break;
	case 7:
		SendAllStopWork();
		break;
	case 8:
		SendAllStopWork();
		break;
	case 9:
		SendAllAxisIsServOff();
		break;
	case 10:
		SendPrelocateInfo(nSide,0.1,0.1,TRUE,0.3);
		break;
	case 11:
		SendLoadSuckInPos(nSide);
		break;
	case 12:
		SendSuckResult(nSide,true);
		break;
	case 13:
		SendUnLoadDone(nSide);
	case 14:
		SendMachReady();
	case 15:
		SendMachUnReady();
	case 16:
		SendCmputerReady();
		break;
	}
	return FALSE;
}

BOOL CSocketManage::SendLoadSuckInPos(int nAxis)
{
	return TRUE;
	LogSock("ip信号： 发送吸嘴下到位 ")
	MsgPacket msg;
	msg.nType = LOAD_X_ARRIVED;
	msg.nSide=nAxis%2;
	msg.CalculateValue();

	return SendMsg(msg,nAxis);
}

BOOL CSocketManage::SendSuckResult(int nSide,BOOL isOk)
{
	return TRUE;
	LogSock("ip信号： 发送吸取结果 ")
	MsgPacket msg;
	msg.nType=LOADPLATFORM_NOZZLE_CHECK_RET;
	msg.nSide=nSide;
	msg.bIsAoiOK=isOk;
	msg.CalculateValue();

	return SendMsgClient(msg);
}

BOOL CSocketManage::SendUnLoadDone(int nAxis)
{
	LogSock("ip信号： 发送给下料完成信号 ")
	MsgPacket msg;
	msg.nType=UNLOADPCIKMATERIAL_DONE;
	msg.nSide=nAxis%2;

	msg.CalculateValue();

	return SendMsg(msg,nAxis);
}

BOOL CSocketManage::SendSingalStatue(int Type,int machNum)
{
	LogSock("ip信号： 发运动控制 类型：%d 轴号",Type,machNum);
	MsgPacket msg;
	msg.nType = Type;
	msg.CalculateValue();
	if (GetConnStatus(machNum))
		SendMsg(msg,2*machNum);
	return TRUE;
}

BOOL CSocketManage::SendAllContinueWork()
{
	LogSock("ip信号： 全部继续")
	for (int i=0;i<8;i++)
	{
		SendSingalStatue(TASK_CONTINUE,i);
	}
	return TRUE;
}

BOOL CSocketManage::GetStartWork()
{
	if (m_bTaskStart)
	{
		LogSock("ip信号： 收到开始工作信号 ")
		m_bTaskStart = FALSE;
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
}

BOOL CSocketManage::GetPauseWork()
{
	if (m_bTaskPause)
	{
		LogSock("ip信号： 收到暂停工作信号 ")
		m_bTaskPause = FALSE;
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
}

BOOL CSocketManage::GetContinueWork()
{
	if (m_bTaskContinue)
	{
		LogSock("ip信号： 收到继续工作信号 ")
		m_bTaskContinue = FALSE;
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
}

BOOL CSocketManage::SendCmputerReady()
{
	LogSock("ip信号： 发送回过原信号 ")
	MsgPacket msg;
	msg.nType = STATUS_HADORI;
	msg.CalculateValue();
	return SendMsgClient(msg,0);
}

BOOL CSocketManage::SendMachReady()
{
	LogSock("ip信号： 准备好信号 ")
	MsgPacket msg;
	msg.nType = STATUS_HADLOADTASK;
	msg.CalculateValue();
	return SendMsgClient(msg,0);
}

BOOL CSocketManage::SendMachUnReady()
{
	LogSock("ip信号： 发送下线 ")
	MsgPacket msg;
	msg.nType = STATUS_TASKERR;
	msg.CalculateValue();
	return SendMsgClient(msg,0);
}

BOOL CSocketManage::SendBuzzerRing(double ERRCODE)
{
	LogSock("ip信号： 发送蜂鸣器信号 ")
	MsgPacket msg;
	msg.doffsetY = ERRCODE;
	msg.nType = STATUS_Breeze;
	msg.CalculateValue();
	return SendMsgClient(msg,0);
}
BOOL CSocketManage::GetComputerReady(int nmachIndex)
{
	if (m_bMachHadOri[nmachIndex])
	{
		LogSock("ip信号： 收到回过原信号 %d",nmachIndex)
		m_bMachHadOri[nmachIndex] = FALSE;
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
}

BOOL CSocketManage::GetMachReady(int nmachIndex)
{
	if (m_bMachReady[nmachIndex])
	{
		LogSock("ip信号： 收到上线信号 %d",nmachIndex)
		m_bMachReady[nmachIndex] = FALSE;
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
}

BOOL CSocketManage::GetMachUnReady(int nmachIndex)
{
	if (m_bMachUnReady[nmachIndex])
	{
		LogSock("ip信号： 收到下线信号 %d",nmachIndex)
		m_bMachUnReady[nmachIndex] = FALSE;
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
}

BOOL CSocketManage::GetBuzzerRing(int nmachIndex,int &ERRCODE)
{
	if (m_bMachRing[nmachIndex])
	{
		LogSock("ip信号： 收到蜂鸣器信号 %d",nmachIndex)
		m_bMachRing[nmachIndex] = FALSE;
		ERRCODE = m_bMachErrCode[nmachIndex];
		m_bMachErrCode[nmachIndex] = -1;
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
}

BOOL CSocketManage::MoveDis(int nAxis,double dis)
{
	MsgPacket msg;
	msg.nType=STEP_MOV;
	msg.doffsetY = dis ;
	msg.nSide = nAxis%2;

	BOOL res = SendMsg(msg,nAxis);
	return res;
}


BOOL CSocketManage::GetClientReturnPos(int nmachIndex,double &dis)
{
	if (m_bmotionCardRecePos[nmachIndex])
	{
		m_bmotionCardRecePos[nmachIndex] = FALSE;
		dis = m_dmotionCardRecePos[nmachIndex];
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
}

BOOL CSocketManage::mcSendAxisCurPos(int nAxis)
{
	MsgPacket msg;
	msg.nType=MOTIONCARD_GETPOS;
	msg.nSide = nAxis%2;

	return SendMsg(msg,nAxis);
}

