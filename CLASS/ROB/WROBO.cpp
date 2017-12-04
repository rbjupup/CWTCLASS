#include "StdAfx.h"
#include "WROBO.h"
#include "pinyin.h"

CWROBO::CWROBO(void)
{
	m_sex = sex::MAN;
}


CWROBO::~CWROBO(void)
{
}

BOOL CWROBO::TranslateTextToWav(CString text,CString savePath,int soundType)
{
	return m_mouse.Text2WAV(text,savePath,soundType);
}

BOOL CWROBO::Talk(CString text)
{
	return m_mouse.TalkText(text,m_sex);
}

CString CWROBO::StartListen()
{
	return m_ear.Listen();
}


CString GetAnswer(CString strLis)
{
	if(strLis.Find(change2PinYin("���ĳ���"),0) != -1){
		return CString("���Ǿʹ󷢴ȱ��ĸ����㣡");
	}
	else if(strLis.Find(change2PinYin("���类�ƻ�"),0) != -1){
		return CString("Ϊ���ػ�����ĺ�ƽ");
	}
	else if(strLis.Find(change2PinYin("а��"),0) != -1){
		return CString("�ɰ������˵ķ��ɽ�ɫ");
	}
	else if(strLis.Find(change2PinYin("���"),0) != -1){
		return CString("С���ɣ������Ǵ��������ӵĻ���ӣ��׶�����ɫ�������ڵ������ǣ���");
	}
	else if(strLis.Find(change2PinYin("��������"),0) != -1){
		return CString("��");
	}
	return CString("ʶ��ʧ��");
}

void CWROBO::PIKAFreeStyle()
{
	CString strLis;
	strLis = m_ear.Listen();
	CString pinyin = change2PinYin(strLis);
	CString answer;
	answer = GetAnswer(pinyin);
	m_mouse.TalkText(answer);
	return;
}

void CWROBO::ChatTuLing()
{
	while(1){
		CString strLis;
		strLis = m_ear.Listen();
		if (strLis == "�˳�"||strLis == "����д�߳�ʧ��"||strLis == "ʶ�����,�߳�δ���ؾ��˳�"||strLis == "")
		{
			m_mouse.TalkText(strLis,0);
			m_mouse.TalkText(CString("�ټ�"),0);
			return;
		}
		CString strTuling = m_brain.ChatTuling(strLis);
		m_mouse.TalkText(strTuling,0);
	}
}

