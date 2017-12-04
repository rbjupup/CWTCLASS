#pragma once
#include "Camera.h"
#include "YCIni.h"
// CCamList �Ի���

class CCamList 
{

public:
	CCamList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCamList();

	CCamera		m_camera;                // �����ָ�� Lgy
	MYDEVICEINFO	m_deviceInfo[MAX_DEVICE];
	CapturePara m_capturePara[MAX_DEVICE];
	float       m_nExposure[MAX_DEVICE];           // ����YCaptureNewDlg�޸ĺ��Ӧ�����ŵ��ع�ֵ
	
	int m_camNum;			//���ѡ�е�����һ̨���
	int flag;
	int Row;                //�б���ͼ��ѡ�е��к�
	int m_serialNumber;		//���к�
	CString m_title;		//����Ի������
	CString m_dlgTitle;		//�б�Ի������


public:
	CListCtrl m_cameraList;							
	int		  m_cameraNumber;
	CEdit m_edit;                   //�༭��ؼ�������� Lgy
	int m_EditIndex;				 //�༭��ؼ���ֵ��ʾ�������޸��������� Lgy
	BOOL ConnectCam(CStatic* m_Show[],CString iniPath);				//�����������������Ϣ


	CString decode(int num);
	void OnBnClickedSaveButton();
	void OnDblclkCameraList(NMHDR *pNMHDR, LRESULT *pResult);  //���˫���б�ؼ� Lgy                              
	void OnKillfocusEdit1();									//�޸�������ñ༭���Ӧ��ʧ������ Lgy
	void OnColumnclickCameraList(NMHDR *pNMHDR, LRESULT *pResult); //�����ͷ�������� Lgy
	void OnClose();
};