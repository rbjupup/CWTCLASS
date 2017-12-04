#include "StdAfx.h"
#include "ComSocket.h"
#include <vector>
using namespace std;
int g_nruningThread;						//等待线程退出再关闭类用的
UINT CComSocket::AcceptThread(LPVOID lParam)
{
	CComSocket* pSock=(CComSocket*)lParam;

	SOCKADDR_IN addrClient;
	int addrClientLen=sizeof(SOCKADDR_IN);
	while(TRUE)
	{
		SOCKET sock=accept(pSock->m_sock,(SOCKADDR*)&addrClient,&addrClientLen);
		TRACE("\nAccept:%d \n",sock);

		if(sock==INVALID_SOCKET)
		{
			break;
		}
		else
		{
            pSock->AcceptSock(pSock->pData,sock);
		}
		if (!pSock->m_bIsWork)
		{
			break;
		}
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0,0))
		{
			GetMessage(&msg, NULL, 0, 0);
			DispatchMessage(&msg);
		}
	}
	g_nruningThread--;
	return 0;
}
UINT CComSocket::ReciveThread(LPVOID lParam)
{
    CComSocket* pSock=(CComSocket*)lParam;
	int retVal;
	char tempdata[1024];
	char singalPackage[1024];
	while(TRUE)
	{

		if (!pSock->m_bIsWork)
		{
		    break;
		}

		retVal=recv(pSock->m_sock,tempdata,1024,0);
		if (retVal!=SOCKET_ERROR)
		{
			int curPackageNum = 0;//为了防止粘包
			vector<CString> vecPackage;
			pSock->nRecvNum = retVal;
			for (int i = 0 ; i < retVal ; i++)
			{
				pSock->recvData[i]=tempdata[i];
				singalPackage[curPackageNum] = tempdata[i];
				curPackageNum++;
				 if(pSock->recvData[i]==13){
					 singalPackage[i] = '\0';
					 vecPackage.push_back(CString(singalPackage));
					 memset(singalPackage,0,1024);
					 curPackageNum = 0;
				 }
			}
			memset(tempdata,0,1024);
           for (int i = 0 ; i < vecPackage.size();i++)
		   {
			   strcpy(pSock->recvData,vecPackage[i].GetBuffer());
// 			   if (pSock->recvData[retVal-1]==13)
// 			   {

				   pSock->HandledData(pSock->pData,pSock);
//				   pSock->recvData[pSock->nRecvNum]=0;
				   memset(pSock->recvData,0,MAX_DATA_LEN);
//				   pSock->nRecvNum =0;
//			   }

           }
		}
		else
		{
			TRACE("\nRECV DATA ERR\n");
			pSock->CloseSock();
			break;
		}
		
	}

	g_nruningThread--;
	return 0;
}


CComSocket::CComSocket(void)
{
	m_bIsConn=FALSE;
	m_index=-1;
	m_ntype=NOCONFIRMTYPE;
	nRecvNum=0;
	m_sock=INVALID_SOCKET;
	memset(recvData,0,MAX_DATA_LEN);
}


CComSocket::~CComSocket(void)
{

}


BOOL CComSocket::SendData(char *msg,int nLen)
{
	int nErrCode=0;
	nErrCode=send(m_sock,msg,nLen,0);
	if (nErrCode==-1)
	{
		return FALSE;
	}
	return TRUE;
}


BOOL CComSocket::InitClient(char* strservAddr,UINT nPort)
{
	int nErrCode;
	m_sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	int flag = 1;
	int ret = setsockopt( m_sock, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(flag) );
	if (ret == -1) 
	{
		AfxMessageBox("Couldn't setsockopt(TCP_NODELAY)\n"); 
		exit(-1);
	}
	SOCKADDR_IN servAddr;
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(nPort);
	servAddr.sin_addr.s_addr=inet_addr(strservAddr);

	nErrCode=connect(m_sock,(SOCKADDR*)&servAddr,sizeof(servAddr));

	if (nErrCode==-1)
	{
		m_bIsWork = FALSE;
		closesocket(m_sock);
		m_bIsConn=FALSE;
		return FALSE;
	}
	m_bIsWork = TRUE;
	StartRecieveThread();
	m_bIsConn=TRUE;
	return TRUE;
}

BOOL CComSocket::InitServer(char* strservAddr,UINT nPort)
{
	int nErrCode;

	m_sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	int flag = 1;
	int ret = setsockopt( m_sock, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(flag) );
	if (ret == -1) 
	{
		AfxMessageBox("Couldn't setsockopt(TCP_NODELAY)\n"); 
		exit(-1);
	}
	SOCKADDR_IN servAddr;
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(nPort);
	servAddr.sin_addr.s_addr=inet_addr(strservAddr);

	nErrCode=bind(m_sock,(SOCKADDR*)&servAddr,sizeof(servAddr));

	if (nErrCode==-1)
	{
		closesocket(m_sock);
		m_bIsConn=FALSE;
		return FALSE;
	}
	nErrCode=listen(m_sock,5);
	if (nErrCode==-1)
	{
		closesocket(m_sock);
		m_bIsConn=FALSE;
		return FALSE;
	}

	m_bIsWork = TRUE;
	StartAcceptThread();
	
	m_bIsConn=TRUE;
	return TRUE;
}


BOOL CComSocket::CloseSock()
{
	if (m_bIsConn)
	{
		m_bIsWork = FALSE;

		m_bIsConn=FALSE;
		m_ntype=-1;
		m_index=-1;
		closesocket(m_sock);
		m_sock=INVALID_SOCKET;
	}
	else
	{
		
	}
	
	return TRUE;
}

void CComSocket::StartAcceptThread()	
{
	TRACE("BEGIN THREAD");
	g_nruningThread++;
	AfxBeginThread(AcceptThread,this);
}

void CComSocket::StartRecieveThread()	
{
	TRACE("BEGIN RECEIVE THREAD");
	g_nruningThread++;
	AfxBeginThread(ReciveThread,this,THREAD_PRIORITY_HIGHEST);
}


BOOL CComSocket::CheckIsOnline(char *msg,int nLen)
{
	if (!m_bIsConn)
	{
		return FALSE;
	}

	if(m_ntype!=-1 && m_ntype!=0)
	{
		return TRUE;
	}

	int nErrCode=0;
	nErrCode=send(m_sock,msg,nLen,0);
	if (nErrCode==-1)
	{
		m_ntype=-1;
		m_bIsConn=FALSE;
		m_ntype=NOCONFIRMTYPE;
		closesocket(m_sock);
		return FALSE;
	}
	return TRUE;
}


