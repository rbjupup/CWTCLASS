#pragma once
#include <vector>
using namespace std;

#include "WCalibreate.h"
#include "CLASS/SOCKET/SocketManage.h"
#include "CLASS/COM/Commport.h"
#include "DefineOfString.h"
#include "CLASS/BCG/CWBCG.h"
#include "CLASS/CAM/CamList.h"
#include "CLASS/ROB/WROBO.h"
#include "CLASS/MFCCTRL/WMFCBtn.h"
#include "stdafx.h"







class BOSSCLASS
{
public:
	BOSSCLASS(void);
	vector<CString> GetSupportClass();
	vector<CString> GetSupportFunCtion(CString ClassName);
	bool CallFunction(CString classname,CString funname,vector<CString> );
	CString GetFunctionHelp(CString classname,CString funname);
	~BOSSCLASS(void);

private:
	vector<CString> m_vecSupportClass;
	vector<vector<CString>> m_vecSupportFunction;
	CWCalibrate m_calibreateBoardWithMove;
	CSocketManage m_sock;					//测试类：sock
	CCommPort m_port;
	CWBCG     m_cwBcg;						//BCG测试界面
	CCamList   m_camList;					//相机类
	CWROBO    m_robo;						//AI类
	CWMFCBtn m_cwmfcBtn;					//透明按钮对话框
};

