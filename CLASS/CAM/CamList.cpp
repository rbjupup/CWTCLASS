// CamList.cpp : 实现文件
//

#include "stdafx.h"
#include "CamList.h"

// CCamList 对话框


	CCamList::CCamList(CWnd* pParent /*=NULL*/)
// 	, m_cameraNumber(0)
// 	, m_serialNumber(0)
// 	, m_camNum(-1)
// 	, flag(0)
// 	, m_title("")
// 	, m_dlgTitle("相机列表")
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



// CCamList 消息处理程序


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
	int nret = m_camera.ConnectCamera(Imgshow,MAX_DEVICE);   //连接到所有相机 但是通过后面的if语句限制 只显示列表双击的相机

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
	

	int		deNum;		//相机在dedeviceInfo中的位置
	YCIni	iniFile;
	CString sCameraInfoPath;
	
	sCameraInfoPath.Format("E:\\CameraInfo.ini");
	iniFile.SetValue("配置信息", "相机数量", m_cameraNumber);

	//for (int i=0; i<m_cameraNumber; i++)          //Lgy
	for (int i=0; i<MAX_DEVICE; i++)
	{
	
	    CString str = m_cameraList.GetItemText(i,1);	// 提取序列号
		
		//int sNum = _ttoi(str);
		if (str == "")            //如果获取到列表中序列号为“ ” 则配置信息也为“ ” Lgy
		{
			CString strNo;
			CString type;
			type=decode(0);
			strNo.Format("相机%d", i+1);
			iniFile.SetValue(strNo, "帧频", "");
			iniFile.SetValue(strNo, "增益", "");
			iniFile.SetValue(strNo, "曝光时间", "");
			iniFile.SetValue(strNo, "图像高度", "");
			iniFile.SetValue(strNo, "图像宽度", "");
			iniFile.SetValue(strNo, "品牌", "");
			iniFile.SetValue(strNo, "序列号", "");
		}
		else 
		{
			//for (int j=0; j<m_cameraNumber; j++)     //Lgy
			CString strNo;
			CString type;
			for (int j=0; j < MAX_DEVICE; j++)
			{
				//if(sNum == m_deviceInfo[j].nIndex)     //匹配序列号，找出相机在dedeviceInfo中的位置
				if(str == m_deviceInfo[j].Str_index)     //匹配序列号，找出相机在dedeviceInfo中的位置
				{
					deNum = j;
					//AfxMessageBox("find");
				}
			}
			type = decode(m_deviceInfo[deNum].m_nCameraType);
			strNo.Format("相机%d", i+1);
			
			m_capturePara[deNum].m_fExposureTime = m_camera.m_pExposureTime[deNum];                //将最后一次曝光设置保存到配置
			m_capturePara[deNum].m_fGain = m_camera.m_Gain[deNum];                                 //最后一次增益设置保存到配置
			iniFile.SetValue(strNo, "帧频", m_capturePara[deNum].m_fFrameRate);
			iniFile.SetValue(strNo, "增益", m_capturePara[deNum].m_fGain);
			iniFile.SetValue(strNo, "曝光时间", m_capturePara[deNum].m_fExposureTime);
			iniFile.SetValue(strNo, "图像高度", m_deviceInfo[deNum].m_nHeight);
			iniFile.SetValue(strNo, "图像宽度", m_deviceInfo[deNum].m_nWidth);
			iniFile.SetValue(strNo, "品牌", type);
			//iniFile.SetValue(strNo, "序列号", m_deviceInfo[deNum].nIndex);  //8-24 Lgy
			iniFile.SetValue(strNo, "序列号", m_deviceInfo[deNum].Str_index);  //8-24 Lgy
		}
	}

	bool svOK = iniFile.Write(sCameraInfoPath);
	if (svOK)
		AfxMessageBox(_T("保存成功！"));
	else
		AfxMessageBox(_T("保存失败！"));

}


void CCamList::OnDblclkCameraList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_camera.m_sCameraInfoPath = "E:\\CameraInfo.ini";
	int nRow = m_cameraList.GetSelectionMark();		
	if (m_cameraList.GetCheck(nRow)&&m_cameraList.GetItemText(nRow,1)!= "")		//选中框被勾上，双击之后设置视频显示窗口 Lgy
	{

//  		CString temp1,temp2;
// 		int		CamType;
 		int		nCamIndex = m_cameraList.GetSelectionMark();      //获取选中行号,与相机下标相同
/*-----------------------------注释代码只连接双击的相机-----------------------------------*/
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
	
		//	int uCamNo = atoi(m_cameraList.GetItemText(nCamIndex,1));		 //获取到序列号
		//	int nret = m_camera.ConnectSelCamera(nCamIndex,CamType,uCamNo); 
		    int nIndex =atoi(m_cameraList.GetItemText(nCamIndex,0));         //获取到相机序号
/*-----------------------------以上注释代码只连接双击的相机-----------------------------------*/
			CWnd *Wnd = AfxGetMainWnd();   //获得主窗口指针
			HWND hwnd = Wnd->GetSafeHwnd();//句柄
			HWND CtrlHwnd1;// = ::GetDlgItem(hwnd,IDC_SHOW_IMG1);//控件句柄
			CWnd *Img1;// = this->FromHandle(CtrlHwnd1);         //获取控件指针
			CRect rc;
			IMGSHOW Imgshow[MAX_DEVICE];
			Img1->GetWindowRect(&rc);

		    Imgshow[0].ctlhwnd   = CtrlHwnd1;
			Imgshow[0].ctlwidth  = rc.Width();
			Imgshow[0].ctlheight = rc.Height();

			
			//int nret = m_camera.ConnectCamera();   //连接到所有相机 但是通过后面的if语句限制 只显示列表双击的相机
			int nret = m_camera.ConnectCamera(Imgshow,MAX_DEVICE);   //连接到所有相机 但是通过后面的if语句限制 只显示列表双击的相机

// 			if (GetParent()->GetDlgItem(IDC_SHOW_IMG1+nIndex-1))	  //？nCameraIndex
// 			{
// 				m_camera.SetConnectView(nCamIndex,GetParent()->GetDlgItem(IDC_SHOW_IMG1+nIndex-1));
// 				//Invalidate(TRUE);
// 			}
	}
 	else										//未被选中，双击可以修改相机序号
 	{
		m_edit.SetParent(&m_cameraList);	    //将列表控件设为m_edit编辑框父窗口
		CRect	rect;
 		CString Text; 
  		
		Row = m_cameraList.GetSelectionMark();			    //获取选中行号
 		Text = m_cameraList.GetItemText(Row,0);				//选中行号第0列文本
		m_cameraList.GetSubItemRect(Row,0,LVIR_LABEL,rect); //选中行号0列矩形界面
 
		m_edit.MoveWindow(rect);		//编辑框移动
 		m_edit.SetWindowTextA(Text);	//文本显示
		m_edit.ShowWindow(SW_SHOW);		//显示编辑框
 		m_edit.SetSel(0,60);			//编辑框文本选中状态
 		m_edit.SetFocus();				//编辑框焦点
		
 	}

	*pResult = 0;
}

void CCamList::OnKillfocusEdit1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString CamIndex;
	m_edit.GetWindowTextA(CamIndex);   //获取修改后输入的值
	m_edit.ShowWindow(SW_HIDE);
	m_EditIndex = atoi(CamIndex);
	m_cameraList.SetItemText(Row,0,CamIndex);
}


void CCamList::OnColumnclickCameraList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	
	int RowCount = m_cameraList.GetItemCount();						//获取行数
	int ColCount = m_cameraList.GetHeaderCtrl()->GetItemCount();	//获取列数
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值

}
