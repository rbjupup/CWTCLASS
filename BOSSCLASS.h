#pragma once
#include <vector>
using namespace std;

#include "DefineOfString.h"
#include "CLASS/BCG/CWBCG.h"
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
	CWBCG     m_cwBcg;						//BCG���Խ���
	CWROBO    m_robo;						//AI��
	CWMFCBtn m_cwmfcBtn;					//͸����ť�Ի���
};

