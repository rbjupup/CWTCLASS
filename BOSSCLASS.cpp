#include "StdAfx.h"
#include "BOSSCLASS.h"
#include "mmsystem.h"

BOSSCLASS::BOSSCLASS(void)
{
//	m_vecSupportClass.push_back(CLASSNAME1);
//	m_vecSupportClass.push_back(CLASSNAME2);
//	m_vecSupportClass.push_back(CLASSNAME3);
	m_vecSupportClass.push_back(CLASSNAME4);
//	m_vecSupportClass.push_back(CLASSNAME5);
	m_vecSupportClass.push_back(CLASSNAME6);
	m_vecSupportClass.push_back(CLASSNAME7);

	vector<CString> WZNCalibreateSupportFunction;
	WZNCalibreateSupportFunction.push_back(CALFUN1);
	WZNCalibreateSupportFunction.push_back(CALFUN2);
	WZNCalibreateSupportFunction.push_back(CALFUN3);
	WZNCalibreateSupportFunction.push_back(CALFUN4);
	WZNCalibreateSupportFunction.push_back(CALFUN5);
	WZNCalibreateSupportFunction.push_back(CALFUN6);
//	m_vecSupportFunction.push_back(WZNCalibreateSupportFunction);

	vector<CString> SocketClassSupportFunction;
	SocketClassSupportFunction.push_back(SOCKETFUN1);
	SocketClassSupportFunction.push_back(SOCKETFUN2);
	SocketClassSupportFunction.push_back(SOCKETFUN3);
	SocketClassSupportFunction.push_back(SOCKETFUN4);
//	m_vecSupportFunction.push_back(SocketClassSupportFunction);	
	
	
	vector<CString> ComClassSupportFunction;
	ComClassSupportFunction.push_back(COMFUN1);
	ComClassSupportFunction.push_back(COMFUN2);
//	m_vecSupportFunction.push_back(ComClassSupportFunction);

	vector<CString> BCGClassSupportFunction;
	BCGClassSupportFunction.push_back(BCGFUN1);
	BCGClassSupportFunction.push_back(BCGFUN2);
	m_vecSupportFunction.push_back(BCGClassSupportFunction);

	vector<CString> CAMClassSupportFunction;
	CAMClassSupportFunction.push_back(CAMFUN1);
	CAMClassSupportFunction.push_back(CAMFUN2);
//	m_vecSupportFunction.push_back(CAMClassSupportFunction);

	vector<CString> ROBOClassSupportFunction;
	ROBOClassSupportFunction.push_back(ROBOFUN1);
	ROBOClassSupportFunction.push_back(ROBOFUN2);
	ROBOClassSupportFunction.push_back(ROBOFUN3);
	ROBOClassSupportFunction.push_back(ROBOFUN4);
	ROBOClassSupportFunction.push_back(ROBOFUN5);
	m_vecSupportFunction.push_back(ROBOClassSupportFunction);


	vector<CString> MFCBTNClassSupportFunction;
	MFCBTNClassSupportFunction.push_back(MFCBTNFUN1);
	m_vecSupportFunction.push_back(MFCBTNClassSupportFunction);
}


BOSSCLASS::~BOSSCLASS(void)
{
}

vector<CString> BOSSCLASS::GetSupportClass()
{
	return m_vecSupportClass;
}

bool BOSSCLASS::CallFunction( CString classname,CString funname ,vector<CString> param)
{
	if (classname == CLASSNAME4)
	{
		if (funname == BCGFUN1){
			m_cwBcg.openABCGdlg();
		}
		if (funname == BCGFUN2){
			AfxMessageBox(HELPBCGFUN2);
			m_cwBcg.openABCGdlg();
		}
	}

	if (classname == CLASSNAME6)
	{
		if (funname == ROBOFUN1){
			if (param.size()<3){
				AfxMessageBox("输入参数太少，请重新输入");
				return false;
			}
			m_robo.TranslateTextToWav(param[0],param[1],atoi(param[2]));
			PlaySound(param[1],NULL, SND_ASYNC|SND_NODEFAULT );
		}
		if (funname == ROBOFUN2){
			if (param.size()<1){
				AfxMessageBox("输入参数太少，请重新输入");
				return false;
			}
			m_robo.Talk(param[0]);
		}
		if (funname == ROBOFUN3){
			AfxMessageBox(m_robo.StartListen());
		}
		if (funname == ROBOFUN4){
			for (int i = 0 ;i < 10; i++)
			{
				m_robo.PIKAFreeStyle();
			}
		}
		if (funname == ROBOFUN5){
				m_robo.ChatTuLing();
		}
	}
	if (classname == CLASSNAME7)
	{
		if (funname == MFCBTNFUN1){
			m_cwmfcBtn.DoModal();
		}

	}
	return true;
}

CString BOSSCLASS::GetFunctionHelp(CString classname,CString funname){
	CString totalhelp = CString("此函数没有声明，无需输入");

	if (classname == CLASSNAME4)
	{
		if (funname == BCGFUN1)
			return HELPBCGFUN1;
	}
	if (classname == CLASSNAME6)
	{
		if (funname == ROBOFUN1)
			return HELPROBOFUN1;
		if (funname == ROBOFUN2)
			return HELPROBOFUN2;
		if (funname == ROBOFUN3)
			return HELPROBOFUN3;
		if (funname == ROBOFUN4)
			return HELPROBOFUN4;
		if (funname == ROBOFUN5)
			return HELPROBOFUN5;
	}
	if (classname == CLASSNAME7)
	{
		if (funname == MFCBTNFUN1)
			return HELPMFCBTNFUN1;
	}
	return totalhelp;
}
vector<CString> BOSSCLASS::GetSupportFunCtion( CString ClassName )
{
	for (int i = 0 ; i < m_vecSupportClass.size(); i++)
	{
		if (m_vecSupportClass[i] == ClassName)
		{
			return m_vecSupportFunction[i];
		}
	}
	vector<CString> strvecnull;
	return strvecnull;
}
