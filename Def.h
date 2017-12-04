//��ά��(double��)

#ifndef _DEF_H
#define _DEF_H

#include "math.h"

#define		CAMERA_LIST	0
#define		RESULT_LIST	1

#define  ANG2RAD(ang1)   (CV_PI*(ang1/180))
#define  RAD2ANG(ang1)   (180*(ang1/CV_PI))

class CFloatPt 
{
public:
	double x, y;

public:
	CFloatPt(                    ) {x =         0.0F; y =         0.0F;};
	CFloatPt(double x1, double y1) {x =           x1; y =           y1;};
	CFloatPt(const CFloatPt &pt  ) {x =         pt.x; y =         pt.y;};
	CFloatPt(const CPoint &pt    ) {x = (double)pt.x; y = (double)pt.y;};
	CFloatPt(const POINT & pt    ) {x = (double)pt.x; y = (double)pt.y;};
	
	CFloatPt* operator= (CFloatPt*      pPt)
	{x =       pPt->x; y =       pPt->y; return  this;};
	CFloatPt& operator= (const CFloatPt& pt)
	{x =         pt.x; y =         pt.y; return *this;};
	CFloatPt& operator= (const CPoint&   pt)
	{x = (double)pt.x; y = (double)pt.y; return *this;};
	CFloatPt& operator= (const POINT&    pt)
	{x = (double)pt.x; y = (double)pt.y; return *this;};
	CFloatPt& operator- (CFloatPt& pt)
	{x -= pt.x; y -= pt.y; return *this;};

	double Distance2Point( CFloatPt p = CFloatPt(0,0)) 
	{
		return sqrt( (x-p.x)* (x-p.x) + (y-p.y)* (y-p.y) );
	} 
	double Distance2Point(double fX, double fY)
	{
		return sqrt( (x-fX)* (x-fX) + (y-fY)* (y-fY) );
	}
};

struct DRect
{
public:
	long m_nWidth;				//��
	long m_nHeight;				//��
	CPoint m_CenterPt;			//����
	double m_fAngle;			//����
	DRect()
	{
		m_nWidth = m_nHeight = 0;
		m_CenterPt = CPoint(0, 0);
		m_fAngle = 0;
	}
	BOOL IsPtInRect(CPoint pt)
	{
		double dx, dy, d1, d2;
		dx = cos(m_fAngle);
		dy = sin(m_fAngle);
		d1 = fabs((pt.x- m_CenterPt.x)*dx+ (pt.y- m_CenterPt.y)*dy);		//��ֱ���߾���
		d2 = fabs((pt.x- m_CenterPt.x)*dy- (pt.y- m_CenterPt.y)*dx);		//�����߾���
		if (d1 < m_nWidth/2 && d2 < m_nHeight/2)
		{
			return TRUE;
		}
		return FALSE;
	} 
};

// struct LINE
// {
// 	CPoint pt0;
// 	CPoint pt1;
// 	LINE()
// 	{
// 		pt0 = CPoint(0,0);
// 		pt1 = CPoint(0,0);
// 	}
// };

//�任����
struct Transform
{
	double m_fCos;
	double m_fSin;
	double m_fX;
	double m_fY;
	Transform()
	{
		m_fCos = 1;
		m_fSin = 0;
		m_fX = 0;
		m_fY = 0;
	}
};

struct LParamLine   // ֱ�߷��� ax+by+c=0 
{
	double a;
	double b;
	double c;
	double lineWidth;  // �߿��
	double SlopeAngle; // ����б�ǣ���x��н�˳ʱ��Ϊ��
	void InitMe(double x1, double y1, double x2, double y2)
	{
		double angle = atan2(y1-y2, x1-x2);
		a = -sin(angle);
		b = cos(angle);
		c = -(a*x1+ b*y1);
	}
	CFloatPt ConvertLine(LParamLine line)
	{
		CFloatPt fPT;
		fPT.x = int((c*line.b- line.c*b)/(line.a*b- a*line.b+ 1.0e-10)+ 0.5);
		fPT.y = int((c*line.a- line.c*a)/(-line.a*b+ a*line.b+ 1.0e-10)+ 0.5);
		return fPT;
	}
};
#endif
