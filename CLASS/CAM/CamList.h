#pragma once
#include "Camera.h"
#include "YCIni.h"
// CCamList 对话框

class CCamList 
{

public:
	CCamList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCamList();

	CCamera		m_camera;                // 相机类指针 Lgy
	MYDEVICEINFO	m_deviceInfo[MAX_DEVICE];
	CapturePara m_capturePara[MAX_DEVICE];
	float       m_nExposure[MAX_DEVICE];           // 接收YCaptureNewDlg修改后对应相机序号的曝光值
	
	int m_camNum;			//标记选中的是哪一台相机
	int flag;
	int Row;                //列表视图被选中的行号
	int m_serialNumber;		//序列号
	CString m_title;		//相机对话框标题
	CString m_dlgTitle;		//列表对话框标题


public:
	CListCtrl m_cameraList;							
	int		  m_cameraNumber;
	CEdit m_edit;                   //编辑框控件对象变量 Lgy
	int m_EditIndex;				 //编辑框控件数值显示变量，修改相机序号用 Lgy
	BOOL ConnectCam(CStatic* m_Show[],CString iniPath);				//检测相机，更新相机信息


	CString decode(int num);
	void OnBnClickedSaveButton();
	void OnDblclkCameraList(NMHDR *pNMHDR, LRESULT *pResult);  //鼠标双击列表控件 Lgy                              
	void OnKillfocusEdit1();									//修改序号所用编辑框对应的失焦控制 Lgy
	void OnColumnclickCameraList(NMHDR *pNMHDR, LRESULT *pResult); //点击表头进行排序 Lgy
	void OnClose();
};