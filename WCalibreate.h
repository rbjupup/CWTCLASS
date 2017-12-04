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
˵����������������궨X��Y����ͬ�������Ұ�еģ����ǻ���Ҫ�궨��Ӧ��ϵ��ʱ��ʹ�õ�

�궨����Ϊ��
	ȷ������ͱ궨��Ĺ�ϵ
	ȷ��Y��ͱ궨��Ĺ�ϵ
	ȷ����ת���ĺͱ궨��Ĺ�ϵ��ʹ��ͼ�������Ƴ�����
	ȷ����ͱ궨��ļнǣ������ᣩ

���ʹ�ã�
	������ʹ�ã�
	GETXMOVE�õ�X����Ҫ�ƶ��ľ���
	GETYMOVE�õ�Y����Ҫ�ƶ��ľ���
	CHECKCALIBRATION�õ��궨�в�

**************************************************************************************/


enum WZNERRCODE{
	ERR_NOERR,
	ERR_FINDCIRERROR,
	ERR_TOOLESSPT
};



#define MAX_CAlCLASS		10						//������8��Y��ƽ̨������Ԥ��λ�����������Ҫ10���궨��
#define MAX_AXIS			9						//������8��Y��ƽ̨������Ԥ��λ�����������Ҫ10���궨��
#define CALCLASS_INDEX_LU	0						//Ԥ��λ���Ͻ����
#define CALCLASS_INDEX_RD	1						//Ԥ��λ���½����
#define CALCLASS_INDEX_Y1	2						//1��λy��
#define CALCLASS_INDEX_Y2	3						//2��λy��
#define CALCLASS_INDEX_Y3	4						//3��λy��
#define CALCLASS_INDEX_Y4	5						//4��λy��
#define CALCLASS_INDEX_Y5	6						//5��λy��
#define CALCLASS_INDEX_Y6	7						//6��λy��
#define CALCLASS_INDEX_Y7	8						//7��λy��
#define CALCLASS_INDEX_Y8	9						//8��λy��


#define AXIS_INDEX_X	0						//x��
#define AXIS_INDEX_Y1	1						//1��λy��
#define AXIS_INDEX_Y2	2						//2��λy��
#define AXIS_INDEX_Y3	3						//3��λy��
#define AXIS_INDEX_Y4	4						//4��λy��
#define AXIS_INDEX_Y5	5						//5��λy��
#define AXIS_INDEX_Y6	6						//6��λy��
#define AXIS_INDEX_Y7	7						//7��λy��
#define AXIS_INDEX_Y8	8						//8��λy��
class CWCalibrate
{
public:
	CWCalibrate(void);
	~CWCalibrate(void);



public:
	//�궨����

	//�궨��궨
	bool CALBoardAndCAM(IplImage* img, float orgX, float orgY, float SquareWidth, float SquareHeight, int board_w, int board_h, int bMethod,int CamIndex = 0);
	void TESTCALBoardAndCAM();
	CString HELPCALBoardAndCAM();

	//�������ı궨
	//ʹ��һϵ�е�ͼƬ���궨��������
	int SuckCenterCalibreatePIC(IplImage **luImage , IplImage **rdImage ,int ptnum , CRect searchRect[2], double maxRadius[2], double minRadius[2]);
	void TESTSuckCenterCalibreatePIC();
	CString HELPSuckCenterCalibreatePIC();

	void SuckCenterCalibreate(CvPoint2D32f* pt1 , int ptnum);
	void TESTSuckCenterCalibreate();
	CString HELPSuckCenterCalibreate();

	//��Ա궨�����궨
	//�нǵı궨
	int AngleOfAxis(CFloatPt* pt,int ptNum,int axisNum);
	void TESTAngleOfAxis();
	CString HELPAngleOfAxis();

	int AngleOfAxisPIC(IplImage **luImage , IplImage **rdImage ,int ptnum , CRect searchRect[2], double maxRadius[2], double minRadius[2],int axisNum);
	int AngleOfAxisPIC(IplImage **luImage ,int ptnum , CRect searchRect, double maxRadius, double minRadius,int axisNum);



	//���غͱ���궨����
	bool save();
	bool reload();
	
	// ��Բ������ʵ�ֱ궨
	bool FindCircle(IplImage *orgImage, CRect searchRect, double maxRadius, double minRadius, double &cx, double &cy, double &radius);
	void TESTFindCircle();
	CString HELPFindCircle();
	

	//����궨���һ�ξ�����������Ҫ����ɵľ���
	double GetAxisDis(double realx,double realy,int axisNum);
	void TESTGetAxisDis();
	CString HELPGetAxisDis();

	//��ȡ������������
	CFloatPt GetSuckCenter(){
		return m_SuckCenter;
	}

private:
	//CCircleFit m_circleFit;							//�������Բ��
	//XPlaneCalibrate m_XPlaneCalibrate[MAX_CAlCLASS];//�����궨���̸�by�ܲ���
	double m_angleOfAxis[MAX_AXIS];					//������ʾ��ͱ궨��ļн�
	CString strLog;									//������ʾlog
	CFloatPt m_SuckCenter;							//��������
};

