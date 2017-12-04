//**********************************************************************//
//函数类别： 图像输入、输出及显示的类                                   //
//编程语言： Visual C++ 6.0                                             //
//编程环境： Windows 98 / NT4.0                                         //
//说    明：                                                            //
//           在张小虎同志的CMyImage类基础上加入了高彩、真彩图像的输入、   //
//           输出及显示，修正了一些BUG。具体用法如下：                  //
//                                                                      //
//           1.在*Doc.h中定义对象;                                      //
//                 CMyImage Image;                                        //
//           2.利用VC++的ClassWizard重载OnOpenDocument()                //
//             及OnSaveDocument()函数;                                  //
//           3.在视类的OnDraw(CDC* pDC)中加入显示函数;                  //
//                 pDoc->Image.ShowCurrentImage(pDC,0,0,w,h);           //
//           4.其它获得数据的函数见类的定义中。                         //
//                                                                      //
//     注意：图像的数据宽度m_nDibWidth与图像的宽度ImageWidth是不同      //
//           的， 因为：像素点的位数有4,8,16,24,32之分，而对于图像      //
//           的每一行数据在存储和显示时要求为4的倍数，于是就有了差      //
//           别。 														//
//               m_ImageWidth  = m_lpDibInfo->bmiHeader.biWidth;        //
//               m_nDibWidth = (m_ImageWidth*m_wImageDepth/8+3) & ~3    //
//               其中 m_nImageDepth =  4,8,16,24,32                     //
//               如果 m_ImageWidth  = 101；								//
//                    m_nImageDepth = 8     m_nDibWidth = 104           //
//                    m_nImageDepth = 24    m_nDibWidth = 304           //
//           so. 因此要格外小心处理!!!                                  //
//																		//
//			 如果只是用C2DArray来获得图像对象中的数据,这里就不提供类似  //
//			 于CMyImage(CMyImage &source,CPoint &LTp,CPoint &RBp)的函数了,  //
//			 因为这样做没有什么意义,在外分配一块内存效果要更好一些。    //
//                                                                      //
//原始作者： 陆  宏  伟 & 张  小  虎									//
//修改作者： 陆  宏  伟													//
//修改日期： 19/05/1999 发现了不少的Bug, 还好都被改正了。感谢LDC。      //
//修改日期： 10/12/1999 改进了许多函数, 功能增加了不少。                //
//修改日期： 18/04/2000 定义并实现了图像二维数组的模板类。              //
//						可以方便的定义各种类型的图像数据。				//
//						如 typedef ImageTemplate< float > FloatImage;	//
//							FloatImage XGrad(w, h) 或者					//
//							FloatImage XGrad;							//
//							XGrad.Construct(w, h);						//
//						获得数据方式：XGrad.lp_AddRow[y][x];			//
//发行日期： 不      详                                                 //
//**********************************************************************//

#ifndef _IMAGE_H
#define _IMAGE_H

#define DIB_HEADER_MARKER         ((WORD)('M'<<8)|'B')    // define "BM"
#define PALVERSION                0x300                   // Windows version  
#define WIDTHBYTES(bits)          (((bits)+31) / 32*4)    // 求图像表面跨距
#define COLORCOUNT                256                     // 索引图像颜色数.
#define IMG_FORMAT_BASE_LENGTH    256                     // *.IMG图像格式的长度基
#define MAXIMGSIZE                2048                    // *.IMG图像格式最大长度
#define REDCOMPONENT              0x1                     // 定义红色分量
#define GREENCOMPONENT            0x10                    // 定义绿色分量
#define BLUECOMPONENT             0x100                   // 定义蓝色分量
#define HUEIMAGE                  0x1000                  // 定义亮度分量
#define SATURATIONIMAGE           0x10000                 // 定义亮度分量
#define INTENSITYIMAGE            0x100000                // 定义亮度分量
#pragma  comment(lib,"MyImage.lib")

//##ModelId=4868695E01A6
typedef unsigned char             P_BYTE; 
//##ModelId=4868695E01B2
typedef long                      P_LONG;

//-----------不同数据类型图像二维数组模板的定义----------
//##ModelId=4868695E01D0
template <class T> 
class AFX_CLASS_EXPORT ImageTemplate
{
public:
	T **		 lp_AddRow; // 二维数组的数据指针
	unsigned int Width;     // 数组的宽度(列数)
	unsigned int Height;    // 数组的高度(行数)
	unsigned int ImageSize; // 数组的大小
public:
	ImageTemplate(void);    // 构造函数 
	~ImageTemplate(void);   // 析构函数
	// 带参数的析构函数
	ImageTemplate(unsigned int w, unsigned int h);
	// 分配数据内存的函数
	void Construct(unsigned int w, unsigned int h);
	// 释放数据内存的函数
	void DeleteData();
	void Transpose();
	void Get_Statistic(double &Mean, double &Sigma2);
};

//构造函数
//##ModelId=4868695E01F0
template <class T> 
ImageTemplate< T >::ImageTemplate(void)
{
	lp_AddRow = NULL;
	Width     = Height = 0;
}
//析构函数 
//##ModelId=4868695E01FF
template <class T>
ImageTemplate< T >::~ImageTemplate(void)
{
	DeleteData();
}
// 带参数的析构函数
//##ModelId=4868695E0201
template <class T>
ImageTemplate< T >::ImageTemplate(unsigned int w, unsigned int h)
{
	lp_AddRow	= NULL;
	Width		= w;
	Height		= h;
	ImageSize	= w * h;
	Construct(w, h);
}
// 分配数据内存的函数
//##ModelId=4868695E0204
template <class T>
void ImageTemplate< T >::Construct(unsigned int w, unsigned int h)
{
	DeleteData();
	Width = w;
	Height = h;
	ImageSize = w*h;
	if( Height    > 0 ) lp_AddRow = new T*[Height];
	if( ImageSize > 0 ) 
	{
		lp_AddRow[0]   = new T[ImageSize];
		memset(lp_AddRow[0], 0, ImageSize* sizeof(T) );
		for(unsigned int i= 1; i < Height; i++)
			lp_AddRow[i] = lp_AddRow[i- 1] + Width;
	}
}
// 释放数据内存的函数
//##ModelId=4868695E0210
template <class T>
void ImageTemplate< T >::DeleteData()
{	
	if(lp_AddRow != NULL) 
	{
		if( lp_AddRow[0] != NULL ) delete []lp_AddRow[0];
		delete []lp_AddRow;
		lp_AddRow = NULL;
	}
}
// 矩阵转置
//##ModelId=4868695E0211
template <class T>
void ImageTemplate< T >::Transpose()
{
	unsigned int i, j;
	T** temp = new T*[Height];
	temp[0]  = new T[ImageSize];
	memcpy(temp[0], lp_AddRow[0], ImageSize* sizeof(T) );
	for(i= 1; i < Height; i++)
		temp[i] = temp[i- 1] + Width;

	DeleteData();

	i	   = Width;
	Width  = Height;
	Height = i;	
	Construct(Width, Height);

	for(j= 0; j < Height; j++)
	{
		for(i= 0; i < Width; i++)
		{
			lp_AddRow[j][i] = temp[i][j];
		}
	}
	if( temp[0] != NULL ) delete []temp[0];
	if( temp    != NULL ) delete []temp;
}

template <class T>
void ImageTemplate< T >::Get_Statistic(double &Mean, double &Sigma2)
{
	double Sum = 0.0, Sum2 = 0.0;

	T *Target, *End = lp_AddRow[0] + ImageSize;
	for(Target = lp_AddRow[0]; Target < End; Target ++)
	{
		Sum  +=   *Target;
		Sum2 +=  (*Target) * (*Target);
	}
	Mean   = Sum / ImageSize;
	Sigma2 = Sum2 - Sum * Mean;
}


typedef ImageTemplate<      int      > IntImage;
typedef ImageTemplate<	   float     > FloatImage;
typedef ImageTemplate<   short int   > SintImage;
typedef ImageTemplate< unsigned char > BYTEImage;
typedef ImageTemplate<    double     > DoubleImage;

//##ModelId=4868695E024D
enum eImageType 
{ 
	//##ModelId=4868695E025E
	IllegalImage,     // 非法图像文件
	//##ModelId=4868695E025F
	BinaryImage ,     // 定义二值图像 
	//##ModelId=4868695E0260
	FourBitsImage,    // 定义4位彩色值图像
	//##ModelId=4868695E026C
	IndexColorImage,  // 定义8位彩色图像
	//##ModelId=4868695E026D
	IndexGrayImage,   // 定义8位灰度图像
	//##ModelId=4868695E026E
	HighColorImage,   // 定义16位彩色图像
	//##ModelId=4868695E026F
	TrueColorImage,   // 定义24位彩色图像
	//##ModelId=4868695E027C
	UltraColorImage   // 定义32位彩色图像
};

//##ModelId=4868695E02BB
class AFX_CLASS_EXPORT C2DArray
{
public:
	//##ModelId=4868695E02CC
    P_LONG            m_nDibWidth;      // 数据的宽度
	//##ModelId=4868695E02D1
    P_LONG            m_nDibHeight;  	// 数据的高度
	//##ModelId=4868695E02DB
    P_BYTE           *m_lpDibArray;     // 数据的指针
	//##ModelId=4868695E02E0
	P_BYTE          **RowAddress;
public:
	//##ModelId=4868695E02E9
    C2DArray();
	//##ModelId=4868695E0386
    C2DArray(P_LONG width, P_LONG height);
	//##ModelId=4868695F004A
    virtual ~C2DArray();

	//##ModelId=4868695F00E6
	P_BYTE  SGetXYValue(P_LONG x, P_LONG y);   	            // 获得数据	
	//##ModelId=4868695F0182
	P_BYTE  SGetXYValue(  CPoint pt   );	                // 获得数据
	//##ModelId=4868695F021E
	void    SSetXYValue(P_LONG x, P_LONG y, P_BYTE value);  // 设置数据
	//##ModelId=4868695F02CA
	void    SSetXYValue(   CPoint pt,       P_BYTE value);  // 设置数据
 
	//##ModelId=4868695F0357
    P_LONG  GetDataWidth()  { return m_nDibWidth;  };    // 获得数据的宽度
	//##ModelId=4868695F0366
    P_LONG  GetDataHeight() { return m_nDibHeight; };    // 获得数据的高度
	//##ModelId=4868695F0367
	BOOL    CheckDataRange(P_LONG x, P_LONG y);          // 检验点的有效性
	//##ModelId=48686960001B
	BOOL    CheckDataRange(   CPoint pt    );            // 检验点的有效性

	//##ModelId=4868696000C7
	void    ReleaseDibArray();                           // 释放m_lpDibArray内存
};

//##ModelId=4868696002E9
class AFX_CLASS_EXPORT CMyImage : public C2DArray 
{
public:  //attribute	
	//##ModelId=4868696002EB
	WORD            m_wImageDepth;	         // 图像的像素深度 =1, 4,    8,  16,  24, 32
	//##ModelId=4868696002F9
    WORD            m_wColorMapNum;          // 调色板的数目   =2, 16, 256,   0,   0,  0   
	
	//##ModelId=4868696002FA
	DWORD           m_dwRBitMask;		     // R的掩码  (方便处理16及32位图像)
	//##ModelId=4868696002FB
	DWORD           m_dwGBitMask;			 // G的掩码  (方便处理16及32位图像)
	//##ModelId=4868696002FC
	DWORD           m_dwBBitMask;			 // B的掩码  (方便处理16及32位图像)

	//##ModelId=4868696002FD
	WORD            m_wlowRedBit;			 // R的最低位 (方便处理16及32位图像)
	//##ModelId=486869600309
	WORD            m_wlowGreenBit;			 // G的最低位 (方便处理16及32位图像)
	//##ModelId=48686960030A
	WORD			m_wlowBlueBit;			 // B的最低位 (方便处理16及32位图像)

	//##ModelId=48686960030B
	WORD	        m_wNumRedBits;			 // R的位数  (方便处理16及32位图像)
	//##ModelId=48686960030C
	WORD            m_wNumGreenBits;		 // G的位数  (方便处理16及32位图像)
	//##ModelId=48686960030D
	WORD			m_wNumBlueBits;			 // B的位数  (方便处理16及32位图像)
	//##ModelId=486869600318
	BOOL            m_IsExistRGBMask;        // 是否存在RGB掩码
	//##ModelId=486869600319
	BOOL            m_Is565RGBImage;         // 是否是565格式的16位图像
	//##ModelId=48686960031B
	P_LONG  		m_ImageSize;			 // 图像的大小 
	//##ModelId=486869600329
    P_LONG          m_ImageWidth;			 // 图像的宽度
	//##ModelId=48686960032E
	P_LONG          m_ImageHeight;			 // 图像的高度

	//##ModelId=486869600333
	P_LONG          m_HSIImageWidth;		 // 亮度分量图像的宽度 
	//##ModelId=486869600339
    P_LONG          m_HSIImageHeight;		 // 亮度分量图像的高度

	//##ModelId=48686960033D
	double          m_fScale;				 // 图像的显示比例
	//##ModelId=486869600347
	BOOL            m_bImgModified;			 // 图像是否被修改的标记
	//##ModelId=486869600348
	BOOL            m_IsImageDownUp;         // 图像是否上下颠倒

	//##ModelId=48686960034A
    P_BYTE         *m_lpDibArrayBuff;        // 备份图像数据的指针
	//##ModelId=486869600358
	P_BYTE	       *m_lpHSIArray;            // 亮度分量图像数据的指针

	//##ModelId=48686960035D
   	BITMAPFILEHEADER    m_bmfHeader;         // 位图的头
	//##ModelId=486869600367
    LPBITMAPINFO        m_lpDibInfo;         // 图像的信息
	//##ModelId=486869600377
	P_BYTE             *m_pUseful;           // 图像的信息内存
	//##ModelId=48686960037C
    RGBTRIPLE           ColorIndex[256];     // 备份索引图像调色板
public:	
	//##ModelId=486869600386
    CMyImage();             // 类的构造及析构函数
	//##ModelId=48686961001B
    CMyImage(CMyImage & source);
	//##ModelId=486869610098
    CMyImage(P_LONG width, P_LONG height, int PixelDepth,DWORD colornum);
	//##ModelId=486869610115
    CMyImage(CMyImage &source,CPoint &LTp, CPoint &RBp);
	
	// 对产生的部分图像处理的函数
	//##ModelId=4868696101A1
	BOOL CreateEmpty(P_LONG width, P_LONG height,int PixelDepth,DWORD colornum);
	//##ModelId=48686961021E
    BOOL CreatePartImg(CMyImage &source, CPoint &LTp, CPoint &RBp, int nScale=1);	
	//##ModelId=48686961029B
	BOOL CreateMicroImg(CMyImage &source, P_LONG MicroW, P_LONG MicroH);	

	//##ModelId=4868696102F9
	virtual ~CMyImage();    // destructor : free memory of  m_hDib and delete m_palDIB
 
    //Read or save image from or to a file  
	//##ModelId=486869610376
    virtual BOOL ReadImageFromFile(LPCTSTR lpszFileName);
	//##ModelId=4868696103C4
    virtual BOOL SaveImageToFile(LPCTSTR lpszFileName);

	//##ModelId=48686962002A
	BOOL ReadImageAsBMP(CFile * pReadFile);   //读取BMP图像
	//##ModelId=486869620078
    BOOL ReadImageAsIMG(CFile * pReadFile);   //读取IMG图像 
	//##ModelId=4868696200B7
	BOOL ReadImageAsPBM(CFile * pReadFile);   //读取PDM图像 
	//##ModelId=4868696200D6
	BOOL ReadImageAsPGM(LPCTSTR lpszFileName);//读取PGM图像 

	//##ModelId=486869620115
	BOOL SaveImageAsBMP(CFile * pSaveFile,    //保存IMG图像  
						BOOL IsNormal = false);   
	//##ModelId=486869620153
    BOOL SaveImageAsIMG(CFile * pSaveFile);	  //保存IMG图像	
	//##ModelId=486869620182
	BOOL SaveImageAsPGM(LPCTSTR lpszFileName);//保存PGM图像    
    // 图像的显示函数
	//##ModelId=4868696201B1
    BOOL ShowCurrentImage(CDC *pMpDc,CRect ShowRect);
	//##ModelId=4868696201E0
    BOOL ShowCurrentImage(CDC *pMpDc,CPoint LTp, CPoint RBp);
	//##ModelId=48686962020F
    BOOL ShowCurrentImage(CDC *pMpDc,int x1, int y1, int x2, int y2);
	//##ModelId=48686962023E
	BOOL ShowPartialImage(CDC *pMpDc,CRect ShowRect,CPoint LTp,CPoint RBp, BOOL Is1to1=false);

	// 获得图像信息的函数
	//##ModelId=48686962026C
	eImageType  GetImageType();                        // 获得图像的类型
	//##ModelId=48686962027C
	WORD        GetColorMapNum(int Depth);	           // 调色板的数目
	//##ModelId=48686962027E
    void        SelectChannel(DWORD channel);          // 选择颜色的显示分量

	//##ModelId=4868696202AB
    P_LONG      GetImageWidth()						   // 获得图像的宽度
				{ return m_ImageWidth;    }; 
	//##ModelId=4868696202AC
    P_LONG      GetImageHeight()			           // 获得图像的高度
				{ return m_ImageHeight;   };
	//##ModelId=4868696202AD
    WORD        GetImageDepth()					       // 获得图像的深度
				{ return m_wImageDepth; };
	//##ModelId=4868696202AE
    double      GetShowScale()					       // 获得图像的显示比例
				{ return m_fScale;         };
	//##ModelId=4868696202AF
    void        SetShowScale(double scale)			   // 设置图像的显示比例
				{ m_fScale = scale;        }; 
	//##ModelId=4868696202B1
	void        GetImageDimensions(LPCTSTR fileName, 
		                         unsigned int &width, 
				                 unsigned int &height, 
								 unsigned int &Depth);

	// 获得或设置图像灰度值的函数
	//##ModelId=486869620309
    BYTE      GetGrayV(     long x, long y);     // 获得灰度图像的灰度值
	//##ModelId=486869620319
	BYTE      GetGrayV(     double x, double y);     // 获得灰度图像的灰度值	
	//##ModelId=486869620328
	P_BYTE      GetXYHueValue(P_LONG x, P_LONG y);     // 获得亮度图像的亮度值
	//##ModelId=486869620338
	RGBTRIPLE   GetRGBPixel(  P_LONG x, P_LONG y);     // 获得彩色图像的RGB值

	//##ModelId=486869620357
    void        SetRGBPixel(P_LONG x, P_LONG y,RGBTRIPLE color); // 设置彩色图像的RGB值
	//##ModelId=486869620366
    void        SetRGBPixel(P_LONG x, P_LONG y,DWORD color);     // 设置彩色图像的RGB值
	//##ModelId=486869620386
    void        SetGrayV(   P_LONG x, P_LONG y,P_BYTE gray);     // 设置灰度图像的灰度值

	// 一些处理时有用的函数
	//##ModelId=486869620395
	void	BackUp();		  // bakup image data.
	//##ModelId=4868696203B5
	void	ImgSwap();		  // swap image with bakup image.
	//##ModelId=4868696203C4
	void	NormalBMP();       //将BMP图转化为正常的，即高度 > 0
	//##ModelId=4868696203C5
	BOOL	BakupColorIndex(); // bakup index image color table data.

	//##ModelId=4868696203D4
    void   Inverse();                        // 正负片的显示                       
	//##ModelId=4868696203D5
    void   ImageInfo();                      // 显示图像信息的函数
	//##ModelId=4868696203E3
	
	//--------------------------------------------------------Maybe we can use----------------------------------------------------------------------------------//
	
	
	void   VerticalFlip();                   // 竖直翻转图像
	//##ModelId=4868696203E4
	void   HorizontalFlip();                 // 水平翻转图像
	//##ModelId=4868696203E5
	void   Rotate90(BOOL Clockwise=TRUE);    // 90.翻转图像  

	
	
	//-------------------------------------------------------Maybe we can use-----------------------------------------------------------------------------------//
	
	//##ModelId=4868696203E7
	BOOL   CheckPoint(P_LONG &x, P_LONG &y);  // 检验点的有效性
	//##ModelId=4868696300A7
	BOOL   CheckPoint(CPoint &pt);            // 检验点的有效性
	//##ModelId=486869630134
	BOOL   CheckRect(CPoint &p1,CPoint &p2);  // 检验区域的有效性
	//##ModelId=4868696301E0
	BOOL   CheckRect(CRect &ImageRect);        // 检验区域的有效性
	//##ModelId=48686963026C
   	void   CreateHSIImage(DWORD dwType);      // transfer to HSI data
	//##ModelId=48686963028C
	void   SwitchPseudoColor(int type=0);

	//##ModelId=48686963028E
	BOOL   ConvertToGrayImage();
	//##ModelId=4868696302E9
	void   GenerateRowAddress();
	//用来向剪贴板提供数据句柄的函数,用后最好用ReleaseCopyHandle()释放内存
	//##ModelId=4868696302EA
	HANDLE   m_hDIB;  	              // handle of transfer  image to clipboard
	//##ModelId=4868696302EB
    HANDLE   GetCopyHandle(CPoint LTp, CPoint RBp);
	//##ModelId=4868696302FA
	void     ReleaseCopyHandle();     // 释放m_hDIB内存
	
public:	// 初始化及分配、释放部分、亮度、备份图像内存一些函数
	BOOL HalfImage(CMyImage &source);
	BOOL ShowCurrentImage(HDC PhDC, int x1, int y1, int x2, int y2);
	//##ModelId=4868696302FB
    BOOL   NewHSIImg();
	//##ModelId=486869630386
    BOOL   NewBuffer();
	//##ModelId=48686964002A
	void   AllocateMemory(BOOL IsExistRGBMask=FALSE);    
	
	//##ModelId=48686964003A
	void   ReleaseHueImg();
	//##ModelId=4868696400C7
    void   ReleaseBuffer();	
	//##ModelId=486869640153
	void   ReleaseDibPalInfo();
	//##ModelId=4868696401E0
	void   InitTrueColorInfo();
	//##ModelId=4868696401EF
	void   InitGrayImageInfo();
	//##ModelId=4868696401F0
    void   DeleteMe();
private:	
	//##ModelId=48686964028C
    void   ConstructInit();
};    
HANDLE  CopyHandle (HANDLE h); 
#endif

