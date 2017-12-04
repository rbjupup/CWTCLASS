#pragma once
#include "CLASSTEST.h"
//#include "XPlaneCalibrate.h"
//#include "CircleFit.h"
#include "XFunCom.h"
#include <afxtempl.h>
#include "opencv2/opencv.hpp"
#include "cv.h"
#include "Def.h"
#include "YCIni.h"
using namespace std;
using namespace cv;
struct XCircle{
	CFloatPt center;
	double nRadius;
	bool bPN;
};


/************************************************************************************
说明：这个类是用来标定X和Y不在同个相机视野中的，但是还需要标定对应关系的时候使用的

标定步骤为：
	确定相机和标定板的关系
	确定Y轴和标定板的关系
	确定旋转中心和标定板的关系（使用图像坐标推出来）
	确定轴和标定板的夹角（左右轴）

类的使用：
	函数的使用：
	GETXMOVE得到X轴需要移动的距离
	GETYMOVE得到Y轴需要移动的距离
	CHECKCALIBRATION得到标定残差

**************************************************************************************/


enum WZNERRCODE{
	ERR_NOERR,
	ERR_FINDCIRERROR,
	ERR_TOOLESSPT
};



#define MAX_CAlCLASS		10						//由于有8个Y轴平台，两个预定位相机，所以需要10个标定类
#define MAX_AXIS			9						//由于有8个Y轴平台，两个预定位相机，所以需要10个标定类
#define CALCLASS_INDEX_LU	0						//预定位左上角相机
#define CALCLASS_INDEX_RD	1						//预定位右下角相机
#define CALCLASS_INDEX_Y1	2						//1工位y轴
#define CALCLASS_INDEX_Y2	3						//2工位y轴
#define CALCLASS_INDEX_Y3	4						//3工位y轴
#define CALCLASS_INDEX_Y4	5						//4工位y轴
#define CALCLASS_INDEX_Y5	6						//5工位y轴
#define CALCLASS_INDEX_Y6	7						//6工位y轴
#define CALCLASS_INDEX_Y7	8						//7工位y轴
#define CALCLASS_INDEX_Y8	9						//8工位y轴


#define AXIS_INDEX_X	0						//x轴
#define AXIS_INDEX_Y1	1						//1工位y轴
#define AXIS_INDEX_Y2	2						//2工位y轴
#define AXIS_INDEX_Y3	3						//3工位y轴
#define AXIS_INDEX_Y4	4						//4工位y轴
#define AXIS_INDEX_Y5	5						//5工位y轴
#define AXIS_INDEX_Y6	6						//6工位y轴
#define AXIS_INDEX_Y7	7						//7工位y轴
#define AXIS_INDEX_Y8	8						//8工位y轴
class CWCalibrate
{
public:
	CWCalibrate(void);
	~CWCalibrate(void);



public:
	//标定流程

	//标定板标定
	bool CALBoardAndCAM(IplImage* img, float orgX, float orgY, float SquareWidth, float SquareHeight, int board_w, int board_h, int bMethod,int CamIndex = 0);
	void TESTCALBoardAndCAM();
	CString HELPCALBoardAndCAM();

	//吸嘴中心标定
	//使用一系列的图片来标定吸嘴中心
	int SuckCenterCalibreatePIC(IplImage **luImage , IplImage **rdImage ,int ptnum , CRect searchRect[2], double maxRadius[2], double minRadius[2]);
	void TESTSuckCenterCalibreatePIC();
	CString HELPSuckCenterCalibreatePIC();

	void SuckCenterCalibreate(CvPoint2D32f* pt1 , int ptnum);
	void TESTSuckCenterCalibreate();
	CString HELPSuckCenterCalibreate();

	//轴对标定板带入标定
	//夹角的标定
	int AngleOfAxis(CFloatPt* pt,int ptNum,int axisNum);
	void TESTAngleOfAxis();
	CString HELPAngleOfAxis();

	int AngleOfAxisPIC(IplImage **luImage , IplImage **rdImage ,int ptnum , CRect searchRect[2], double maxRadius[2], double minRadius[2],int axisNum);
	int AngleOfAxisPIC(IplImage **luImage ,int ptnum , CRect searchRect, double maxRadius, double minRadius,int axisNum);



	//加载和保存标定数据
	bool save();
	bool reload();
	
	// 找圆，用来实现标定
	bool FindCircle(IplImage *orgImage, CRect searchRect, double maxRadius, double minRadius, double &cx, double &cy, double &radius);
	void TESTFindCircle();
	CString HELPFindCircle();
	

	//计算标定板的一段距离在轴上面要折算成的距离
	double GetAxisDis(double realx,double realy,int axisNum);
	void TESTGetAxisDis();
	CString HELPGetAxisDis();

	//获取吸嘴中心坐标
	CFloatPt GetSuckCenter(){
		return m_SuckCenter;
	}

private:
	//CCircleFit m_circleFit;							//用来拟合圆心
	//XPlaneCalibrate m_XPlaneCalibrate[MAX_CAlCLASS];//用来标定棋盘格（by周博）
	double m_angleOfAxis[MAX_AXIS];					//用来表示轴和标定板的夹角
	CString strLog;									//用来显示log
	CFloatPt m_SuckCenter;							//吸嘴中心
};

