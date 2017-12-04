#include "StdAfx.h"
#include "WCalibreate.h"


CWCalibrate::CWCalibrate(void)
{
	m_SuckCenter = CFloatPt(0,0);
	reload();
}


CWCalibrate::~CWCalibrate(void)
{
}

bool CWCalibrate::CALBoardAndCAM(IplImage* img, float orgX, float orgY, float SquareWidth, float SquareHeight, int board_w, int board_h, int bMethod,int CamIndex)
{
//	bool res = m_XPlaneCalibrate[CamIndex].CalibrateCameraByChessBoard(img, orgX, orgY, SquareWidth, SquareHeight, board_w, board_h, bMethod);
	return true;
}

void CWCalibrate::TESTCALBoardAndCAM()
{
	float PhyX[10] = {0,1,2,3,4,5,6,7,8,9};
	float PhyY[10] = {0,1,2,3,4,5,6,7,8,9};
	float ImgX1[10] = {10,11,12,13,14,15,16,17,18,19};
	float ImgY1[10] = {10,11,12,13,14,15,16,17,18,19};

	int ptNum = 10;
	int bMethod = 2;
	float orgX = 0;
	float orgY = 0;
	float SquareWidth = 0.5;
	float SquareHeight = 0.5;
	int board_w = 32;
	int board_h = 24;

	IplImage* img = cvLoadImage("CAL\\Calboard_0.bmp");
	bool res = CALBoardAndCAM(img, orgX, orgY, SquareWidth, SquareHeight, board_w, board_h, bMethod);

//假如是测试类模式
#ifdef TEST_CLASS
	float frealx,frealy;
	strLog.Format("使用了CAL\\Calboard_0.bmp进行的测试\r\n");
	theApp.m_resdlg->m_strRes += strLog;


// 	m_XPlaneCalibrate[0].CalculatePosInPhysical(frealx,frealy,0.1,0.1);
// 	strLog.Format("使用数据点0.1，0.1进行标定测试\r\n得到的实际坐标结果为%.4f,%.4f\r\n",frealx,frealy);
// 	theApp.m_resdlg->m_strRes += strLog;
// 
// 
// 	float fImgx,fImgy;
// 	m_XPlaneCalibrate[0].CalculatePosInImage(0,0,fImgx,fImgy);
// 	strLog.Format("使用数据点0，0进行标定测试\r\n得到的图像坐标的结果为%.4f,%.4f\r\n",fImgx,fImgy);
// 	theApp.m_resdlg->m_strRes += strLog;

#endif
}

CString CWCalibrate::HELPCALBoardAndCAM()
{
	strLog.Format("这个函数用来标定相机和标定板的关系\r\n");
	return strLog;
}

void CWCalibrate::SuckCenterCalibreate(CvPoint2D32f* pt1 , int ptnum)
{
// 	double co[4];
// 	m_circleFit.FitCircle(pt1,ptnum,co);
// 	double err = m_circleFit.CircleError(pt1,ptnum,co);
// 	XCircle cir;
// 	cir.center.x = -co[1]/2*co[0];
// 	cir.center.y = -co[2]/2*co[0];
// 	cir.nRadius = sqrt(cir.center.x*cir.center.x +cir.center.y*cir.center.y-co[3]/co[0]);
// 	m_SuckCenter = cir.center;
// #ifdef TEST_CLASS
// 	strLog.Format("使用吸嘴标定算法，拟合到的圆心坐标为   圆心（%.4f，%.4f）",cir.center.x,cir.center.y);
// #endif

}

void CWCalibrate::TESTSuckCenterCalibreate()
{
	CvPoint2D32f pt1[8];
	pt1[0] = cvPoint2D32f(-10.0,0.0);
	pt1[1] = cvPoint2D32f(-7.072,7.072);
	pt1[2] = cvPoint2D32f(0.0,10.0);
	pt1[3] = cvPoint2D32f(7.072,7.072);
	pt1[4] = cvPoint2D32f(10.0,0.0);
	pt1[5] = cvPoint2D32f(7.072,-7.072);
	pt1[6] = cvPoint2D32f(0.0,-10.0);
	pt1[7] = cvPoint2D32f(-7.072,-7.072);
	SuckCenterCalibreate(pt1,8);
}

CString CWCalibrate::HELPSuckCenterCalibreate()
{
	strLog.Format("这个函数用来标定吸嘴中心\r\n输入：无\r\n");
	return strLog;
}

bool CWCalibrate::reload()
{
	CString appPath;
	appPath = GetAppPath();
	for (int i = 0 ; i < MAX_CAlCLASS; i++)
	{
		strLog.Format("%sCAL\\CALDATA\\data%d.ini",appPath,i);
		if(!FileExist(strLog))
			continue;
		//m_XPlaneCalibrate[i].LoadParaFile(strLog);
	}
	YCIni file;
	bool flag;
	strLog.Format("%sCAL\\CALDATA\\sysdata.ini",appPath);
	if(!FileExist(strLog))
		return true;
	flag=file.Read(strLog);
	flag=flag && file.GetValue("标定保存参数","吸嘴中心",m_SuckCenter);
	return flag;
}	

bool CWCalibrate::save()
{
	CString appPath;
	appPath = GetAppPath();
	for (int i = 0 ; i < MAX_CAlCLASS; i++)
	{
		strLog.Format("%sCAL\\CALDATA\\data%d.ini",appPath,i);
		if(!FileExist(strLog)){
			strLog.Format("%sCAL\\CALDATA",appPath);
			CreateAllDirectories(strLog);
			strLog.Format("%sCAL\\CALDATA\\data%d.ini",appPath,i);
		}
		//m_XPlaneCalibrate[i].SaveParaFile(strLog);
	}
	YCIni file;
	bool flag = true;
	strLog.Format("%sCAL\\CALDATA\\sysdata.ini",appPath);
	if(!FileExist(strLog)){
		strLog.Format("%sCAL\\CALDATA",appPath);
		CreateAllDirectories(strLog);
		strLog.Format("%sCAL\\CALDATA\\sysdata.ini",appPath);
	}
	file.Read(strLog);
	flag=flag && file.SetValue("标定保存参数","吸嘴中心",m_SuckCenter);
	flag=file.Write(strLog);
#ifdef TEST_CLASS
	theApp.m_resdlg->m_strRes.Format("测试函数：保存参数，参数保存在运行文件夹\\cal\\caldata里面");
#endif
	return flag;
}
bool CWCalibrate::FindCircle(IplImage *orgImage, CRect searchRect, double maxRadius, double minRadius, double &cx, double &cy, double &radius)
{
// 	IplImage *grayImage = cvCreateImage(cvSize(orgImage->width,orgImage->height),IPL_DEPTH_8U,1);
// 	if(orgImage->nChannels == 3)
// 		cvCvtColor(orgImage, grayImage, CV_BGR2GRAY);
// 	else if(orgImage->nChannels == 1)
// 		cvCopy(orgImage, grayImage);
// 	
// 	cvThreshold(grayImage, grayImage, 0, 255, CV_THRESH_OTSU);
// #ifdef TEST_CLASS
// 	strLog.Format("%sPIC\\PicOfFindCir.bmp",GetAppPath());
// 	cvSaveImage(strLog,grayImage);
// 	theApp.m_resdlg->m_strRes += CString("临时二值化图片保存在了PIC下面\r\n");
// #endif
// 	CvSeq* contours=NULL,* c=NULL;
// 	CvMemStorage* storage=cvCreateMemStorage();
// 	cvFindContours(grayImage, storage, &contours,sizeof(CvContour),CV_RETR_LIST, CV_CHAIN_APPROX_NONE); //在二值图像中寻找轮廓
// 	//找到面积小于200*200的轮廓，针头直径小于200像素
// 	double areaTh = 200*200;
// 	CArray<XCircle,XCircle&> cList;
// 	int maxArea = PI*maxRadius*maxRadius;
// 	int minArea = PI*minRadius*minRadius;
// 	XCircle realCircle;
// 	double minErr = 100000;
// 	for(c=contours;c!=NULL;c=c->h_next)
// 	{	
// 		double area;
// 		area = cvContourArea( c, CV_WHOLE_SEQ );
// 		area = fabs(area);
// 		if(area < maxArea && area > minArea)
// 		{
// 			int totalPtNum = c->total;
// 			CvPoint2D32f* points = NULL;
// 			points = new CvPoint2D32f [totalPtNum];
// 			for(int ii=0; ii<c->total; ii++)
// 			{
// 				CvPoint temppt = *CV_GET_SEQ_ELEM(CvPoint, c, ii);
// 				points[ii].x = temppt.x;
// 				points[ii].y = temppt.y;
// //				cvRectangle(orgImage, temppt, temppt, CV_RGB(0,0,255),1);
// 			}
// 			double co[4];
// 			m_circleFit.FitCircle( points, totalPtNum,co);
// 			double err = m_circleFit.CircleError(points, totalPtNum, co);
// 			if(err < 3)
// 			{
// 				XCircle cir;
// 				cir.center.x = -co[1]/(2*co[0]);
// 				cir.center.y = -co[2]/(2*co[0]);
// 				cir.nRadius = sqrt(cir.center.x*cir.center.x+cir.center.y*cir.center.y-co[3]/co[0]);
// 				cir.bPN = !(c->flags & CV_SEQ_FLAG_HOLE);
// 				if(cir.center.x>searchRect.left && cir.center.x<searchRect.right && cir.center.y>searchRect.top && cir.center.y<searchRect.bottom && cir.nRadius>minRadius && cir.nRadius<maxRadius)
// 				{
// 					if(err<minErr)
// 					{
// 						realCircle.center.x = cir.center.x;
// 						realCircle.center.y = cir.center.y;
// 						realCircle.nRadius = cir.nRadius;
// 						minErr = err;
// 						cList.Add(cir);
// #ifdef TEST_CLASS
// 						strLog.Format("找到圆：center（%.4f,%.4f），半径为%.4f\r\n",cir.center.x,cir.center.y,cir.nRadius);
// 						theApp.m_resdlg->m_strRes += strLog;
// #endif
// 
// 					}
// 				}
// 			}
// 			delete [] points;
// 		}
// 	}
// 	cvReleaseMemStorage(&storage);			
// 	cvReleaseImage(&grayImage);
// 	int num = cList.GetSize();
// 	bool bFind = false;
// 	if(num == 0)
// 	{
// 		bFind = false;
// 		return false;
// 	}
// 	cx = realCircle.center.x;
// 	cy = realCircle.center.y;
// 	radius = realCircle.nRadius;
		
	return true;
}

void CWCalibrate::TESTFindCircle()
{

}

CString CWCalibrate::HELPFindCircle()
{
	return CString("说明：这个函数是用来在图上寻找一个圆的函数\r\n输入：1、图片路径 2、最大半径 3、最小半径 \r\n返回：圆心和半径");
}

int CWCalibrate::SuckCenterCalibreatePIC(IplImage **luImage , IplImage **rdImage ,int ptnum , CRect searchRect[2], double maxRadius[2], double minRadius[2])
{
// 	double *picxlu = new double[ptnum];//左上角相机的图像x坐标
// 	double *picxrd = new double[ptnum];//右上角相机的图像x坐标
// 	double *picylu = new double[ptnum];//左上角相机的图像y坐标
// 	double *picyrd = new double[ptnum];//右上角相机的图像y坐标
// 	double *picrlu = new double[ptnum];//左上角相机的图像圆半径
// 	double *picrrd = new double[ptnum];//右上角相机的图像圆半径
// 
// 	double *realxlu = new double[ptnum];//左上角相机的真实x坐标
// 	double *realxrd = new double[ptnum];//右上角相机的真实x坐标
// 	double *realylu = new double[ptnum];//左上角相机的真实y坐标
// 	double *realyrd = new double[ptnum];//右上角相机的真实y坐标
// 
// 	double *realxcn = new double[ptnum];//使用标定算法得到的图像x坐标转的真实坐标
// 	double *realycn = new double[ptnum];//使用标定算法得到的图像y坐标转的真实坐标
// 	CvPoint2D32f *centerPt = new CvPoint2D32f[ptnum];//用来拟合吸嘴中心的实际的圆
// 	//提取左边图像的圆心
// 	//如果没有拟合到圆心的话返回没找到圆
// 	for (int i = 0; i < ptnum; i++)
// 	{
// 		bool res = FindCircle(luImage[i],searchRect[0],maxRadius[0],minRadius[0],picxlu[i],picylu[i],picrlu[i]);
// 		if(!res)
// 			return ERR_FINDCIRERROR;
// 		
// 	}
// 	//提取右边图像的圆心
// 	for (int i = 0; i < ptnum; i++)
// 	{
// 		bool res = FindCircle(rdImage[i],searchRect[1],maxRadius[1],minRadius[0],picxrd[i],picyrd[i],picrrd[i]);
// 		if(!res)
// 			return ERR_FINDCIRERROR;
// 	}
// 	//转化为标定板坐标
// 	for (int i = 0; i < ptnum;i++)
// 	{
// 		float realx,realy;
// 		m_XPlaneCalibrate[CALCLASS_INDEX_LU].CalculatePosInPhysical(realx,realy,picxlu[i],picylu[i]);
// 		realxlu[i] = realx;
// 		realylu[i] = realy;
// 		m_XPlaneCalibrate[CALCLASS_INDEX_RD].CalculatePosInPhysical(realx,realy,picxrd[i],picyrd[i]);
// 		realxrd[i] = realx;
// 		realyrd[i] = realy;
// 	}
// 	//计算中心坐标
// 	for (int i = 0; i < ptnum; i++)
// 	{
// 		realxcn[i] = (picxlu[i] + picxrd[i])/2.0;
// 		realycn[i] = (picylu[i] + picyrd[i])/2.0;
// 	}
// 
// 	for (int i = 0; i < ptnum; i++)
// 	{
// 		centerPt[i] = cvPoint2D32f(realxcn[i], realycn[i]);
// 	}
// 
// 	//拟合吸嘴中心
// 
// 	SuckCenterCalibreate(centerPt,ptnum);
// 
// 	delete[] picxlu  ;
// 	delete[] picxrd  ;
// 	delete[] picylu  ;
// 	delete[] picyrd  ;
// 	delete[] picrlu  ;
// 	delete[] picrrd  ;
// 	delete[] centerPt;
// 	delete[] realxlu ;
// 	delete[] realxrd ;
// 	delete[] realylu ;
// 	delete[] realyrd ;
// 	delete[] realxcn ;
// 	delete[] realycn ;
 	return ERR_NOERR;
}

int FixLine(CFloatPt* pt,int ptNum,cv::Vec4f &line_para){

	//输入拟合点
	vector<CvPoint> points;
	for (int i = 0; i < ptNum; i++)
	{
		pt[i].x *=1000;
		pt[i].y *=1000;
		points.push_back(cvPoint(pt[i].x, pt[i].y));
	}
	
	cv::fitLine(points, line_para, CV_DIST_L2, 0, 0.01, 0.01);
	line_para[1] /=1000;
	line_para[2] /=1000;


	return ERR_NOERR;
}
int CWCalibrate::AngleOfAxis(CFloatPt* pt,int ptNum,int axisNum)
{

	if (ptNum <= 1)
		return ERR_TOOLESSPT;

// 	//获取点斜式的点和斜率
// 	cv::Vec4f line_para;
// 	FixLine(pt, ptNum, line_para);
// 	cv::Point point0;
// 	point0.x = line_para[2];
// 	point0.y = line_para[3];
// 	double k = line_para[1] / line_para[0];

	//得到始末两个点
	double newy1 = pt[0].y;//k*(pt[0].x -point0.x) + point0.y;
	double newy2 = pt[ptNum - 1].y;//k*(pt[ptNum - 1].x -point0.x) + point0.y;


	m_angleOfAxis[axisNum] = atan2(newy2-newy1,pt[ptNum - 1].x - pt[0].x);
	
	return ERR_NOERR;
}
void CWCalibrate::TESTGetAxisDis(){
	double ang1[9] = {0,30,90,120,180,-30,-90,-120,-180};
	double test_realx[8] = {100,70.7,0,  -70.7,-100,70.7, 0,   -70.7};
	double test_realy[8] = {0,  70.7,100,70.7, 0,   -70.7,-100,-70.7};

	for (int i = 0; i < 9; i++)
	{
		m_angleOfAxis[0] = ANG2RAD(ang1[i]);
		for (int j = 0; j < 8; j++)
		{
			double dis = GetAxisDis(test_realx[j],test_realy[j],0);
			strLog.Format("当真实坐标是 （%.4f,%.4f）,夹角为%.4f 的时候\r\n得到的距离投影长度为：%.4f\r\n",
				test_realx[j],test_realy[j],ang1[i],dis) ;
#ifdef TEST_CLASS
			theApp.m_resdlg->m_strRes += strLog;
#endif
		}
	}

}

double CWCalibrate::GetAxisDis(double realx,double realy,int axisNum)
{
	//求新的长度需要先算真实长度
	double realLong = sqrt(realx*realx + realy*realy);
	//真实夹角
	double realAng = atan2(realy,realx);
	//夹角差
	double ang = m_angleOfAxis[axisNum] - realAng;
	//求夹角差的cos值
	//真实长度乘以该值即为投影长度
	return realLong*cos(ang);
}

CString CWCalibrate::HELPGetAxisDis()
{
	return CString("测试函数的设计思路是：带入0，45，90，等8个坐标\r\n\
使用0，30，90，120，等8个坐标做测试，看看投影长度是不是对的");
}

CString CWCalibrate::HELPAngleOfAxis()
{
	return CString("测试函数的设计思路是：使用不同方向的数据\r\n\
看看算出来的角度是不是对的");
}

void CWCalibrate::TESTAngleOfAxis()
{
	CFloatPt pts[4][4] = {
		{CFloatPt(-10.1,-10.1),CFloatPt(0.1,0.1),CFloatPt(10,10),CFloatPt(20,20.1)},
		{CFloatPt(10,-10.1),CFloatPt(0.1,0.1),CFloatPt(-10,10),CFloatPt(-20,20.1)},
		{CFloatPt(10,10),CFloatPt(0.1,0.1),CFloatPt(-10,-10),CFloatPt(-20,-20.1)},
		{CFloatPt(-10,10),CFloatPt(0.1,0.1),CFloatPt(10,-10),CFloatPt(20,-20.1)},

	};
#ifdef TEST_CLASS 
	strLog.Format("使用了4组点测试角度获取\r\n");
		theApp.m_resdlg->m_strRes+=strLog;
#endif
	for (int i = 0; i < 4; i++)
	{
		int res = AngleOfAxis(pts[i],4,0);
#ifdef TEST_CLASS 
		strLog.Format("点的数据为\r\n（%.4f,%.4f）（%.4f,%.4f）（%.4f,%.4f）\r\n",pts[i][0].x,pts[i][0].y,pts[i][1].x,pts[i][1].y,pts[i][2].x,pts[i][2].y);
		theApp.m_resdlg->m_strRes+=strLog;
		strLog.Format("得打的返回值为%d,角度为%.4f\r\n",res,RAD2ANG(m_angleOfAxis[0]));
		theApp.m_resdlg->m_strRes+=strLog;
#endif
	}
}



int CWCalibrate::AngleOfAxisPIC(IplImage **luImage , IplImage **rdImage ,int ptnum , CRect searchRect[2], double maxRadius[2], double minRadius[2],int axisNum)
{
// 	double *picxlu = new double[ptnum];//左上角相机的图像x坐标
// 	double *picxrd = new double[ptnum];//右上角相机的图像x坐标
// 	double *picylu = new double[ptnum];//左上角相机的图像y坐标
// 	double *picyrd = new double[ptnum];//右上角相机的图像y坐标
// 	double *picrlu = new double[ptnum];//左上角相机的图像圆半径
// 	double *picrrd = new double[ptnum];//右上角相机的图像圆半径
// 
// 	double *realxlu = new double[ptnum];//左上角相机的真实x坐标
// 	double *realxrd = new double[ptnum];//右上角相机的真实x坐标
// 	double *realylu = new double[ptnum];//左上角相机的真实y坐标
// 	double *realyrd = new double[ptnum];//右上角相机的真实y坐标
// 
// 	double *realxcn = new double[ptnum];//使用标定算法得到的图像x坐标转的真实坐标
// 	double *realycn = new double[ptnum];//使用标定算法得到的图像y坐标转的真实坐标
// 	//提取左边图像的圆心
// 	//如果没有拟合到圆心的话返回没找到圆
// 	for (int i = 0; i < ptnum; i++)
// 	{
// 		bool res = FindCircle(luImage[i],searchRect[0],maxRadius[0],minRadius[0],picxlu[i],picylu[i],picrlu[i]);
// 		if(!res)
// 			return ERR_FINDCIRERROR;
// 
// 	}
// 	//提取右边图像的圆心
// 	for (int i = 0; i < ptnum; i++)
// 	{
// 		bool res = FindCircle(rdImage[i],searchRect[1],maxRadius[1],minRadius[0],picxrd[i],picyrd[i],picrrd[i]);
// 		if(!res)
// 			return ERR_FINDCIRERROR;
// 	}
// 	//转化为标定板坐标
// 	for (int i = 0; i < ptnum;i++)
// 	{
// 		float realx,realy;
// 		m_XPlaneCalibrate[CALCLASS_INDEX_LU].CalculatePosInPhysical(realx,realy,picxlu[i],picylu[i]);
// 		realxlu[i] = realx;
// 		realylu[i] = realy;
// 		m_XPlaneCalibrate[CALCLASS_INDEX_RD].CalculatePosInPhysical(realx,realy,picxrd[i],picyrd[i]);
// 		realxrd[i] = realx;
// 		realyrd[i] = realy;
// 	}
// 	//计算中心坐标
// 	for (int i = 0; i < ptnum; i++)
// 	{
// 		realxcn[i] = (picxlu[i] + picxrd[i])/2.0;
// 		realycn[i] = (picylu[i] + picyrd[i])/2.0;
// 	}
// 
// 	CFloatPt *centerPt = new CFloatPt[ptnum];//用来拟合吸嘴中心的实际的圆
// 	for (int i = 0; i < ptnum; i++)
// 	{
// 		centerPt[i] = CFloatPt(realxcn[i], realycn[i]);
// 	}
// 
// 	//拟合吸嘴中心
// 
// 	AngleOfAxis(centerPt,ptnum,axisNum);
// 
// 	delete[] picxlu  ;
// 	delete[] picxrd  ;
// 	delete[] picylu  ;
// 	delete[] picyrd  ;
// 	delete[] picrlu  ;
// 	delete[] picrrd  ;
// 	delete[] centerPt;
// 	delete[] realxlu ;
// 	delete[] realxrd ;
// 	delete[] realylu ;
// 	delete[] realyrd ;
// 	delete[] realxcn ;
// 	delete[] realycn ;
 	return ERR_NOERR;
}

int CWCalibrate::AngleOfAxisPIC(IplImage **luImage ,int ptnum , CRect searchRect, double maxRadius, double minRadius,int axisNum)
{
// 	double *picxlu = new double[ptnum];//左上角相机的图像x坐标
// 	double *picylu = new double[ptnum];//左上角相机的图像y坐标
// 	double *picrlu = new double[ptnum];//左上角相机的图像圆半径
// 	double *realxlu = new double[ptnum];//左上角相机的真实x坐标
// 	double *realylu = new double[ptnum];//左上角相机的真实y坐标
// 	for (int i = 0; i < ptnum; i++)
// 	{
// 		bool res = FindCircle(luImage[i],searchRect,maxRadius,minRadius,picxlu[i],picylu[i],picrlu[i]);
// 		if(!res)
// 			return ERR_FINDCIRERROR;
// 	}
// 
// 	//转化为标定板坐标
// 	for (int i = 0; i < ptnum;i++)
// 	{
// 		float realx,realy;
// 		m_XPlaneCalibrate[CALCLASS_INDEX_LU].CalculatePosInPhysical(realx,realy,picxlu[i],picylu[i]);
// 		realxlu[i] = realx;
// 		realylu[i] = realy;
// 	}
// 
// 
// 	CFloatPt *centerPt = new CFloatPt[ptnum];//用来拟合吸嘴中心的实际的圆
// 	for (int i = 0; i < ptnum; i++)
// 	{
// 		centerPt[i] = CFloatPt(realxlu[i], realylu[i]);
// 	}
// 
// 	//拟合吸嘴中心
// 
// 	AngleOfAxis(centerPt,ptnum,axisNum);
// 
// 	delete[] picxlu;
// 	delete[] picylu;
// 	delete[] picrlu;
// 	delete[] centerPt;
// 	delete[] realxlu;
// 	delete[] realylu;
	return 0;
}
