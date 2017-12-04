#include "StdAfx.h"
#include "BOSSCLASS.h"
#include "mmsystem.h"

BOSSCLASS::BOSSCLASS(void)
{
	m_vecSupportClass.push_back(CLASSNAME1);
	m_vecSupportClass.push_back(CLASSNAME2);
	m_vecSupportClass.push_back(CLASSNAME3);
	m_vecSupportClass.push_back(CLASSNAME4);
	m_vecSupportClass.push_back(CLASSNAME5);
	m_vecSupportClass.push_back(CLASSNAME6);
	m_vecSupportClass.push_back(CLASSNAME7);

	vector<CString> WZNCalibreateSupportFunction;
	WZNCalibreateSupportFunction.push_back(CALFUN1);
	WZNCalibreateSupportFunction.push_back(CALFUN2);
	WZNCalibreateSupportFunction.push_back(CALFUN3);
	WZNCalibreateSupportFunction.push_back(CALFUN4);
	WZNCalibreateSupportFunction.push_back(CALFUN5);
	WZNCalibreateSupportFunction.push_back(CALFUN6);
	m_vecSupportFunction.push_back(WZNCalibreateSupportFunction);

	vector<CString> SocketClassSupportFunction;
	SocketClassSupportFunction.push_back(SOCKETFUN1);
	SocketClassSupportFunction.push_back(SOCKETFUN2);
	SocketClassSupportFunction.push_back(SOCKETFUN3);
	SocketClassSupportFunction.push_back(SOCKETFUN4);
	m_vecSupportFunction.push_back(SocketClassSupportFunction);	
	
	
	vector<CString> ComClassSupportFunction;
	ComClassSupportFunction.push_back(COMFUN1);
	ComClassSupportFunction.push_back(COMFUN2);
	m_vecSupportFunction.push_back(ComClassSupportFunction);

	vector<CString> BCGClassSupportFunction;
	BCGClassSupportFunction.push_back(BCGFUN1);
	BCGClassSupportFunction.push_back(BCGFUN2);
	m_vecSupportFunction.push_back(BCGClassSupportFunction);

	vector<CString> CAMClassSupportFunction;
	CAMClassSupportFunction.push_back(CAMFUN1);
	CAMClassSupportFunction.push_back(CAMFUN2);
	m_vecSupportFunction.push_back(CAMClassSupportFunction);

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
	if (classname == CLASSNAME1)
	{
		if (funname == CALFUN1)
			m_calibreateBoardWithMove.TESTCALBoardAndCAM();
		if (funname == CALFUN2)
			m_calibreateBoardWithMove.reload();
		if (funname == CALFUN3)
			m_calibreateBoardWithMove.save();
		if (funname == CALFUN4)
			m_calibreateBoardWithMove.TESTSuckCenterCalibreate();
		if (funname == CALFUN5)
			m_calibreateBoardWithMove.TESTGetAxisDis();
		if (funname == CALFUN6)
			m_calibreateBoardWithMove.TESTAngleOfAxis();
	}
	if (classname == CLASSNAME2)
	{
		if (funname == SOCKETFUN1){
			m_sock.InitSockLib();
			m_sock.InitServer(param[0].GetBuffer(),5006);
		}
		if (funname == SOCKETFUN2){
			m_sock.InitSockLib();
			m_sock.InitClient(param[0].GetBuffer(),5006);
			m_sock.SendMachineInfo(atoi(param[1]));
		}
		if (funname == SOCKETFUN3)
			m_sock.TestSendSingleMsg(atoi(param[0]),0);
		if (funname == SOCKETFUN4)
			m_sock.TESTGETALLSINGAL();
	}
	if (classname == CLASSNAME3)
	{
		if (funname == COMFUN1){
			DCB dcb;
			dcb.DCBlength = sizeof(DCB);
			dcb.BaudRate  =9600;
			dcb.ByteSize  =8;
			dcb.Parity    =NOPARITY;//EVENPARITY;    //NOPARITY and friends are #defined in windows.h
			dcb.StopBits  =ONESTOPBIT;//TWOSTOPBITS;//ONESTOPBIT;//  //ONESTOPBIT is also from windows.h
			m_port.SetCommDCBProperties(dcb);
			m_port.SetCommPort("COM6");
			m_port.OpenCommPort();
//			AfxMessageBox("�򿪳ɹ�");
		}
		if (funname == COMFUN2){
			double pos = m_port.ReadPos(false);
			double curpos  = pos/0x7fffff*360.0;
#ifdef TEST_CLASS
			theApp.m_resdlg->m_strRes.Format("���ú���ReadPos  \r\n���صĽ���ǣ�%.4f",curpos);
#endif
		}
	}
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
	if (classname == CLASSNAME5)
	{
		if (funname == CAMFUN1){
			CStatic* img[1];
			img[0] = &theApp.m_resdlg->m_Show;
			m_camList.ConnectCam(img,"E:\\CameraInfo.ini");
		}
		if (funname == CAMFUN2){
			m_camList.m_camera.m_pImage[0]->SaveImageToFile("E:\\pic.bmp");
			AfxMessageBox("ͼ���Ѿ�������E:\\pic.bmp");
		}
	}
	if (classname == CLASSNAME6)
	{
		if (funname == ROBOFUN1){
			if (param.size()<3){
				AfxMessageBox("�������̫�٣�����������");
				return false;
			}
			m_robo.TranslateTextToWav(param[0],param[1],atoi(param[2]));
			PlaySound(param[1],NULL, SND_ASYNC|SND_NODEFAULT );
		}
		if (funname == ROBOFUN2){
			if (param.size()<1){
				AfxMessageBox("�������̫�٣�����������");
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
	CString totalhelp = CString("�˺���û����������������");
	if (classname == CString("WZNCAlIBREATE"))
	{
		if (funname == CALFUN1)
			return m_calibreateBoardWithMove.HELPCALBoardAndCAM();
		if (funname == CALFUN2)
			return totalhelp;
		if (funname == CALFUN3)
			return totalhelp;
		if (funname == CALFUN4)
			return m_calibreateBoardWithMove.HELPSuckCenterCalibreate();
		if (funname == CALFUN5)
			return m_calibreateBoardWithMove.HELPGetAxisDis();
		if (funname == CALFUN6)
			return m_calibreateBoardWithMove.HELPAngleOfAxis();
	}
	if (classname == CString("SocketClass"))
	{
		if (funname == SOCKETFUN1)
			return CString("���õ�ǰip��ַΪ��������ַ\r\n����:������ip��ַ");
		if (funname == SOCKETFUN2)
			return CString("���õ�ǰip��ַΪ�ͻ��˵�ַ\r\n����:��������ip��ַ,�������");
		if (funname == SOCKETFUN3)
			return HELPSOCKETFUN3;
		if (funname == SOCKETFUN4)
			return CString("���Լ���������Ϣ\r\n����:��");
	}
	if (classname == CLASSNAME4)
	{
		if (funname == BCGFUN1)
			return HELPBCGFUN1;
	}
	if (classname == CLASSNAME5)
	{
		if (funname == CAMFUN1)
			return HELPCAMFUN1;
		if (funname == CAMFUN2)
			return HELPCAMFUN2;
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
