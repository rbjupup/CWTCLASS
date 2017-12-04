// CamList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CamList.h"

// CCamList �Ի���


	CCamList::CCamList(CWnd* pParent /*=NULL*/)
// 	, m_cameraNumber(0)
// 	, m_serialNumber(0)
// 	, m_camNum(-1)
// 	, flag(0)
// 	, m_title("")
// 	, m_dlgTitle("����б�")
{
	for (int i = 0; i< MAX_DEVICE; i++)            //Lgy
	{
		m_deviceInfo[i].m_nCameraType = -1;
		m_deviceInfo[i].m_nHeight = -1;
		m_deviceInfo[i].m_nWidth = -1;
		m_deviceInfo[i].Str_index ="-1" ;
	}

	m_EditIndex = 0;
}

CCamList::~CCamList()
{
}



// CCamList ��Ϣ�������


BOOL CCamList::ConnectCam(CStatic* m_Show[],CString iniPath)
{
	m_cameraNumber =m_camera.DetectCamera(m_deviceInfo,m_capturePara);
 	CRect rc;
 	IMGSHOW Imgshow[MAX_DEVICE];
	for (int i = 0; i < MAX_DEVICE; i++)
	{
		(*(m_Show[i])).GetWindowRect(&rc);
		Imgshow[i].ctlhwnd   = *m_Show[i];
		Imgshow[i].ctlwidth  = rc.Width();
		Imgshow[i].ctlheight = rc.Height();

	}

	m_camera.m_sCameraInfoPath = iniPath;
	int nret = m_camera.ConnectCamera(Imgshow,MAX_DEVICE);   //���ӵ�������� ����ͨ�������if������� ֻ��ʾ�б�˫�������

	for (int i = 0; i < MAX_DEVICE; i++)
	{
		m_camera.SetConnectView(i,m_Show[i]);
	}
	return TRUE;  
}
CString CCamList:: decode(int num)
{
	switch (num)
	{
	case  KSJ :
		return "KSJ";
	case  ACU :
		return "ACU";
	case  BAS :
		return "BAS";
	case  PTG :
		return "PTG";
	case  IMG :
		return "IMG";
	case  DS  :
		return "DS";

	default :
		return NULL;

	}
}

void CCamList::OnBnClickedSaveButton()
{
	

	int		deNum;		//�����dedeviceInfo�е�λ��
	YCIni	iniFile;
	CString sCameraInfoPath;
	
	sCameraInfoPath.Format("E:\\CameraInfo.ini");
	iniFile.SetValue("������Ϣ", "�������", m_cameraNumber);

	//for (int i=0; i<m_cameraNumber; i++)          //Lgy
	for (int i=0; i<MAX_DEVICE; i++)
	{
	
	    CString str = m_cameraList.GetItemText(i,1);	// ��ȡ���к�
		
		//int sNum = _ttoi(str);
		if (str == "")            //�����ȡ���б������к�Ϊ�� �� ��������ϢҲΪ�� �� Lgy
		{
			CString strNo;
			CString type;
			type=decode(0);
			strNo.Format("���%d", i+1);
			iniFile.SetValue(strNo, "֡Ƶ", "");
			iniFile.SetValue(strNo, "����", "");
			iniFile.SetValue(strNo, "�ع�ʱ��", "");
			iniFile.SetValue(strNo, "ͼ��߶�", "");
			iniFile.SetValue(strNo, "ͼ����", "");
			iniFile.SetValue(strNo, "Ʒ��", "");
			iniFile.SetValue(strNo, "���к�", "");
		}
		else 
		{
			//for (int j=0; j<m_cameraNumber; j++)     //Lgy
			CString strNo;
			CString type;
			for (int j=0; j < MAX_DEVICE; j++)
			{
				//if(sNum == m_deviceInfo[j].nIndex)     //ƥ�����кţ��ҳ������dedeviceInfo�е�λ��
				if(str == m_deviceInfo[j].Str_index)     //ƥ�����кţ��ҳ������dedeviceInfo�е�λ��
				{
					deNum = j;
					//AfxMessageBox("find");
				}
			}
			type = decode(m_deviceInfo[deNum].m_nCameraType);
			strNo.Format("���%d", i+1);
			
			m_capturePara[deNum].m_fExposureTime = m_camera.m_pExposureTime[deNum];                //�����һ���ع����ñ��浽����
			m_capturePara[deNum].m_fGain = m_camera.m_Gain[deNum];                                 //���һ���������ñ��浽����
			iniFile.SetValue(strNo, "֡Ƶ", m_capturePara[deNum].m_fFrameRate);
			iniFile.SetValue(strNo, "����", m_capturePara[deNum].m_fGain);
			iniFile.SetValue(strNo, "�ع�ʱ��", m_capturePara[deNum].m_fExposureTime);
			iniFile.SetValue(strNo, "ͼ��߶�", m_deviceInfo[deNum].m_nHeight);
			iniFile.SetValue(strNo, "ͼ����", m_deviceInfo[deNum].m_nWidth);
			iniFile.SetValue(strNo, "Ʒ��", type);
			//iniFile.SetValue(strNo, "���к�", m_deviceInfo[deNum].nIndex);  //8-24 Lgy
			iniFile.SetValue(strNo, "���к�", m_deviceInfo[deNum].Str_index);  //8-24 Lgy
		}
	}

	bool svOK = iniFile.Write(sCameraInfoPath);
	if (svOK)
		AfxMessageBox(_T("����ɹ���"));
	else
		AfxMessageBox(_T("����ʧ�ܣ�"));

}


void CCamList::OnDblclkCameraList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_camera.m_sCameraInfoPath = "E:\\CameraInfo.ini";
	int nRow = m_cameraList.GetSelectionMark();		
	if (m_cameraList.GetCheck(nRow)&&m_cameraList.GetItemText(nRow,1)!= "")		//ѡ�п򱻹��ϣ�˫��֮��������Ƶ��ʾ���� Lgy
	{

//  		CString temp1,temp2;
// 		int		CamType;
 		int		nCamIndex = m_cameraList.GetSelectionMark();      //��ȡѡ���к�,������±���ͬ
/*-----------------------------ע�ʹ���ֻ����˫�������-----------------------------------*/
// 		temp1 =m_cameraList.GetItemText(nCamIndex,2);
// 			if (temp1 == "KSJ")
// 				CamType = 1;
// 			if (temp1 == "PTG")
// 				CamType = 4;
// 			if (temp1 == "IMG")
// 				CamType = 5;
// 			if (temp1 == "ACU")
// 				CamType = 2;
// 			if (temp1 == "BAS")
//				CamType = 3;
	
		//	int uCamNo = atoi(m_cameraList.GetItemText(nCamIndex,1));		 //��ȡ�����к�
		//	int nret = m_camera.ConnectSelCamera(nCamIndex,CamType,uCamNo); 
		    int nIndex =atoi(m_cameraList.GetItemText(nCamIndex,0));         //��ȡ��������
/*-----------------------------����ע�ʹ���ֻ����˫�������-----------------------------------*/
			CWnd *Wnd = AfxGetMainWnd();   //���������ָ��
			HWND hwnd = Wnd->GetSafeHwnd();//���
			HWND CtrlHwnd1;// = ::GetDlgItem(hwnd,IDC_SHOW_IMG1);//�ؼ����
			CWnd *Img1;// = this->FromHandle(CtrlHwnd1);         //��ȡ�ؼ�ָ��
			CRect rc;
			IMGSHOW Imgshow[MAX_DEVICE];
			Img1->GetWindowRect(&rc);

		    Imgshow[0].ctlhwnd   = CtrlHwnd1;
			Imgshow[0].ctlwidth  = rc.Width();
			Imgshow[0].ctlheight = rc.Height();

			
			//int nret = m_camera.ConnectCamera();   //���ӵ�������� ����ͨ�������if������� ֻ��ʾ�б�˫�������
			int nret = m_camera.ConnectCamera(Imgshow,MAX_DEVICE);   //���ӵ�������� ����ͨ�������if������� ֻ��ʾ�б�˫�������

// 			if (GetParent()->GetDlgItem(IDC_SHOW_IMG1+nIndex-1))	  //��nCameraIndex
// 			{
// 				m_camera.SetConnectView(nCamIndex,GetParent()->GetDlgItem(IDC_SHOW_IMG1+nIndex-1));
// 				//Invalidate(TRUE);
// 			}
	}
 	else										//δ��ѡ�У�˫�������޸�������
 	{
		m_edit.SetParent(&m_cameraList);	    //���б�ؼ���Ϊm_edit�༭�򸸴���
		CRect	rect;
 		CString Text; 
  		
		Row = m_cameraList.GetSelectionMark();			    //��ȡѡ���к�
 		Text = m_cameraList.GetItemText(Row,0);				//ѡ���кŵ�0���ı�
		m_cameraList.GetSubItemRect(Row,0,LVIR_LABEL,rect); //ѡ���к�0�о��ν���
 
		m_edit.MoveWindow(rect);		//�༭���ƶ�
 		m_edit.SetWindowTextA(Text);	//�ı���ʾ
		m_edit.ShowWindow(SW_SHOW);		//��ʾ�༭��
 		m_edit.SetSel(0,60);			//�༭���ı�ѡ��״̬
 		m_edit.SetFocus();				//�༭�򽹵�
		
 	}

	*pResult = 0;
}

void CCamList::OnKillfocusEdit1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString CamIndex;
	m_edit.GetWindowTextA(CamIndex);   //��ȡ�޸ĺ������ֵ
	m_edit.ShowWindow(SW_HIDE);
	m_EditIndex = atoi(CamIndex);
	m_cameraList.SetItemText(Row,0,CamIndex);
}


void CCamList::OnColumnclickCameraList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	int RowCount = m_cameraList.GetItemCount();						//��ȡ����
	int ColCount = m_cameraList.GetHeaderCtrl()->GetItemCount();	//��ȡ����
	CString temp0,temp1,temp2;
	for (int i = 1;i <RowCount; i++ )
	{
		for (int j = 0; j < RowCount - i; j++)
		{
			temp1 = m_cameraList.GetItemText(j,0);
			temp2 = m_cameraList.GetItemText(j+1,0);
			int nRe = StrCmpI(temp1,temp2);
			if (nRe > 0)
			{
				for (int m = 0; m < ColCount; m++)
				{
					temp1 = m_cameraList.GetItemText(j,m);
					temp2 = m_cameraList.GetItemText(j+1,m);
					m_cameraList.SetItemText(j,m,temp2);
					m_cameraList.SetItemText(j+1,m,temp1);
				}
			}
		}
	}
	*pResult = 0;
}


void CCamList::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

}
