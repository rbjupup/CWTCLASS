#pragma once

#include <winsock2.h>
#include <afxtempl.h>
#pragma comment(lib,"ws2_32.lib")

#define MAX_DATA_LEN 256


#define NOCONFIRMTYPE -1
#define COMMUNACATE 0
#define BARCODE 1
#define SENDAOIRET 2

class CComSocket
{
public:
	CComSocket(void);
	~CComSocket(void);


public:
	void StartAcceptThread();
	void StartRecieveThread();	


	BOOL InitClient(char* strservAddr,UINT nPort);
	BOOL InitServer(char* strservAddr,UINT nPort);

	BOOL CloseSock();
	BOOL SendData(char *msg,int nLen);

	BOOL (*HandledData)(void* pData,CComSocket *pComSock);
	BOOL (*AcceptSock)(void* pData,SOCKET sock);

	BOOL CheckIsOnline(char *msg,int nLen);


public:
	//关掉线程用到
	BOOL m_bIsWork;  //是否工作  
	SOCKET m_sock;
	BOOL m_bIsConn;
	int m_index;
	int m_ntype;
	char recvData[MAX_DATA_LEN];
	int nRecvNum;

	void* pData;

public:
	static UINT AcceptThread(LPVOID lParam);
	static UINT ReciveThread(LPVOID lParam);
};

