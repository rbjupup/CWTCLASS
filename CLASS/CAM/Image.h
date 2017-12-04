//**********************************************************************//
//������� ͼ�����롢�������ʾ����                                   //
//������ԣ� Visual C++ 6.0                                             //
//��̻����� Windows 98 / NT4.0                                         //
//˵    ����                                                            //
//           ����С��ͬ־��CMyImage������ϼ����˸߲ʡ����ͼ������롢   //
//           �������ʾ��������һЩBUG�������÷����£�                  //
//                                                                      //
//           1.��*Doc.h�ж������;                                      //
//                 CMyImage Image;                                        //
//           2.����VC++��ClassWizard����OnOpenDocument()                //
//             ��OnSaveDocument()����;                                  //
//           3.�������OnDraw(CDC* pDC)�м�����ʾ����;                  //
//                 pDoc->Image.ShowCurrentImage(pDC,0,0,w,h);           //
//           4.����������ݵĺ�������Ķ����С�                         //
//                                                                      //
//     ע�⣺ͼ������ݿ��m_nDibWidth��ͼ��Ŀ��ImageWidth�ǲ�ͬ      //
//           �ģ� ��Ϊ�����ص��λ����4,8,16,24,32֮�֣�������ͼ��      //
//           ��ÿһ�������ڴ洢����ʾʱҪ��Ϊ4�ı��������Ǿ����˲�      //
//           �� 														//
//               m_ImageWidth  = m_lpDibInfo->bmiHeader.biWidth;        //
//               m_nDibWidth = (m_ImageWidth*m_wImageDepth/8+3) & ~3    //
//               ���� m_nImageDepth =  4,8,16,24,32                     //
//               ��� m_ImageWidth  = 101��								//
//                    m_nImageDepth = 8     m_nDibWidth = 104           //
//                    m_nImageDepth = 24    m_nDibWidth = 304           //
//           so. ���Ҫ����С�Ĵ���!!!                                  //
//																		//
//			 ���ֻ����C2DArray�����ͼ������е�����,����Ͳ��ṩ����  //
//			 ��CMyImage(CMyImage &source,CPoint &LTp,CPoint &RBp)�ĺ�����,  //
//			 ��Ϊ������û��ʲô����,�������һ���ڴ�Ч��Ҫ����һЩ��    //
//                                                                      //
//ԭʼ���ߣ� ½  ��  ΰ & ��  С  ��									//
//�޸����ߣ� ½  ��  ΰ													//
//�޸����ڣ� 19/05/1999 �����˲��ٵ�Bug, ���ö��������ˡ���лLDC��      //
//�޸����ڣ� 10/12/1999 �Ľ�����ຯ��, ���������˲��١�                //
//�޸����ڣ� 18/04/2000 ���岢ʵ����ͼ���ά�����ģ���ࡣ              //
//						���Է���Ķ���������͵�ͼ�����ݡ�				//
//						�� typedef ImageTemplate< float > FloatImage;	//
//							FloatImage XGrad(w, h) ����					//
//							FloatImage XGrad;							//
//							XGrad.Construct(w, h);						//
//						������ݷ�ʽ��XGrad.lp_AddRow[y][x];			//
//�������ڣ� ��      ��                                                 //
//**********************************************************************//

#ifndef _IMAGE_H
#define _IMAGE_H

#define DIB_HEADER_MARKER         ((WORD)('M'<<8)|'B')    // define "BM"
#define PALVERSION                0x300                   // Windows version  
#define WIDTHBYTES(bits)          (((bits)+31) / 32*4)    // ��ͼ�������
#define COLORCOUNT                256                     // ����ͼ����ɫ��.
#define IMG_FORMAT_BASE_LENGTH    256                     // *.IMGͼ���ʽ�ĳ��Ȼ�
#define MAXIMGSIZE                2048                    // *.IMGͼ���ʽ��󳤶�
#define REDCOMPONENT              0x1                     // �����ɫ����
#define GREENCOMPONENT            0x10                    // ������ɫ����
#define BLUECOMPONENT             0x100                   // ������ɫ����
#define HUEIMAGE                  0x1000                  // �������ȷ���
#define SATURATIONIMAGE           0x10000                 // �������ȷ���
#define INTENSITYIMAGE            0x100000                // �������ȷ���
#pragma  comment(lib,"MyImage.lib")

//##ModelId=4868695E01A6
typedef unsigned char             P_BYTE; 
//##ModelId=4868695E01B2
typedef long                      P_LONG;

//-----------��ͬ��������ͼ���ά����ģ��Ķ���----------
//##ModelId=4868695E01D0
template <class T> 
class AFX_CLASS_EXPORT ImageTemplate
{
public:
	T **		 lp_AddRow; // ��ά���������ָ��
	unsigned int Width;     // ����Ŀ��(����)
	unsigned int Height;    // ����ĸ߶�(����)
	unsigned int ImageSize; // ����Ĵ�С
public:
	ImageTemplate(void);    // ���캯�� 
	~ImageTemplate(void);   // ��������
	// ����������������
	ImageTemplate(unsigned int w, unsigned int h);
	// ���������ڴ�ĺ���
	void Construct(unsigned int w, unsigned int h);
	// �ͷ������ڴ�ĺ���
	void DeleteData();
	void Transpose();
	void Get_Statistic(double &Mean, double &Sigma2);
};

//���캯��
//##ModelId=4868695E01F0
template <class T> 
ImageTemplate< T >::ImageTemplate(void)
{
	lp_AddRow = NULL;
	Width     = Height = 0;
}
//�������� 
//##ModelId=4868695E01FF
template <class T>
ImageTemplate< T >::~ImageTemplate(void)
{
	DeleteData();
}
// ����������������
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
// ���������ڴ�ĺ���
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
// �ͷ������ڴ�ĺ���
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
// ����ת��
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
	IllegalImage,     // �Ƿ�ͼ���ļ�
	//##ModelId=4868695E025F
	BinaryImage ,     // �����ֵͼ�� 
	//##ModelId=4868695E0260
	FourBitsImage,    // ����4λ��ɫֵͼ��
	//##ModelId=4868695E026C
	IndexColorImage,  // ����8λ��ɫͼ��
	//##ModelId=4868695E026D
	IndexGrayImage,   // ����8λ�Ҷ�ͼ��
	//##ModelId=4868695E026E
	HighColorImage,   // ����16λ��ɫͼ��
	//##ModelId=4868695E026F
	TrueColorImage,   // ����24λ��ɫͼ��
	//##ModelId=4868695E027C
	UltraColorImage   // ����32λ��ɫͼ��
};

//##ModelId=4868695E02BB
class AFX_CLASS_EXPORT C2DArray
{
public:
	//##ModelId=4868695E02CC
    P_LONG            m_nDibWidth;      // ���ݵĿ��
	//##ModelId=4868695E02D1
    P_LONG            m_nDibHeight;  	// ���ݵĸ߶�
	//##ModelId=4868695E02DB
    P_BYTE           *m_lpDibArray;     // ���ݵ�ָ��
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
	P_BYTE  SGetXYValue(P_LONG x, P_LONG y);   	            // �������	
	//##ModelId=4868695F0182
	P_BYTE  SGetXYValue(  CPoint pt   );	                // �������
	//##ModelId=4868695F021E
	void    SSetXYValue(P_LONG x, P_LONG y, P_BYTE value);  // ��������
	//##ModelId=4868695F02CA
	void    SSetXYValue(   CPoint pt,       P_BYTE value);  // ��������
 
	//##ModelId=4868695F0357
    P_LONG  GetDataWidth()  { return m_nDibWidth;  };    // ������ݵĿ��
	//##ModelId=4868695F0366
    P_LONG  GetDataHeight() { return m_nDibHeight; };    // ������ݵĸ߶�
	//##ModelId=4868695F0367
	BOOL    CheckDataRange(P_LONG x, P_LONG y);          // ��������Ч��
	//##ModelId=48686960001B
	BOOL    CheckDataRange(   CPoint pt    );            // ��������Ч��

	//##ModelId=4868696000C7
	void    ReleaseDibArray();                           // �ͷ�m_lpDibArray�ڴ�
};

//##ModelId=4868696002E9
class AFX_CLASS_EXPORT CMyImage : public C2DArray 
{
public:  //attribute	
	//##ModelId=4868696002EB
	WORD            m_wImageDepth;	         // ͼ���������� =1, 4,    8,  16,  24, 32
	//##ModelId=4868696002F9
    WORD            m_wColorMapNum;          // ��ɫ�����Ŀ   =2, 16, 256,   0,   0,  0   
	
	//##ModelId=4868696002FA
	DWORD           m_dwRBitMask;		     // R������  (���㴦��16��32λͼ��)
	//##ModelId=4868696002FB
	DWORD           m_dwGBitMask;			 // G������  (���㴦��16��32λͼ��)
	//##ModelId=4868696002FC
	DWORD           m_dwBBitMask;			 // B������  (���㴦��16��32λͼ��)

	//##ModelId=4868696002FD
	WORD            m_wlowRedBit;			 // R�����λ (���㴦��16��32λͼ��)
	//##ModelId=486869600309
	WORD            m_wlowGreenBit;			 // G�����λ (���㴦��16��32λͼ��)
	//##ModelId=48686960030A
	WORD			m_wlowBlueBit;			 // B�����λ (���㴦��16��32λͼ��)

	//##ModelId=48686960030B
	WORD	        m_wNumRedBits;			 // R��λ��  (���㴦��16��32λͼ��)
	//##ModelId=48686960030C
	WORD            m_wNumGreenBits;		 // G��λ��  (���㴦��16��32λͼ��)
	//##ModelId=48686960030D
	WORD			m_wNumBlueBits;			 // B��λ��  (���㴦��16��32λͼ��)
	//##ModelId=486869600318
	BOOL            m_IsExistRGBMask;        // �Ƿ����RGB����
	//##ModelId=486869600319
	BOOL            m_Is565RGBImage;         // �Ƿ���565��ʽ��16λͼ��
	//##ModelId=48686960031B
	P_LONG  		m_ImageSize;			 // ͼ��Ĵ�С 
	//##ModelId=486869600329
    P_LONG          m_ImageWidth;			 // ͼ��Ŀ��
	//##ModelId=48686960032E
	P_LONG          m_ImageHeight;			 // ͼ��ĸ߶�

	//##ModelId=486869600333
	P_LONG          m_HSIImageWidth;		 // ���ȷ���ͼ��Ŀ�� 
	//##ModelId=486869600339
    P_LONG          m_HSIImageHeight;		 // ���ȷ���ͼ��ĸ߶�

	//##ModelId=48686960033D
	double          m_fScale;				 // ͼ�����ʾ����
	//##ModelId=486869600347
	BOOL            m_bImgModified;			 // ͼ���Ƿ��޸ĵı��
	//##ModelId=486869600348
	BOOL            m_IsImageDownUp;         // ͼ���Ƿ����µߵ�

	//##ModelId=48686960034A
    P_BYTE         *m_lpDibArrayBuff;        // ����ͼ�����ݵ�ָ��
	//##ModelId=486869600358
	P_BYTE	       *m_lpHSIArray;            // ���ȷ���ͼ�����ݵ�ָ��

	//##ModelId=48686960035D
   	BITMAPFILEHEADER    m_bmfHeader;         // λͼ��ͷ
	//##ModelId=486869600367
    LPBITMAPINFO        m_lpDibInfo;         // ͼ�����Ϣ
	//##ModelId=486869600377
	P_BYTE             *m_pUseful;           // ͼ�����Ϣ�ڴ�
	//##ModelId=48686960037C
    RGBTRIPLE           ColorIndex[256];     // ��������ͼ���ɫ��
public:	
	//##ModelId=486869600386
    CMyImage();             // ��Ĺ��켰��������
	//##ModelId=48686961001B
    CMyImage(CMyImage & source);
	//##ModelId=486869610098
    CMyImage(P_LONG width, P_LONG height, int PixelDepth,DWORD colornum);
	//##ModelId=486869610115
    CMyImage(CMyImage &source,CPoint &LTp, CPoint &RBp);
	
	// �Բ����Ĳ���ͼ����ĺ���
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
	BOOL ReadImageAsBMP(CFile * pReadFile);   //��ȡBMPͼ��
	//##ModelId=486869620078
    BOOL ReadImageAsIMG(CFile * pReadFile);   //��ȡIMGͼ�� 
	//##ModelId=4868696200B7
	BOOL ReadImageAsPBM(CFile * pReadFile);   //��ȡPDMͼ�� 
	//##ModelId=4868696200D6
	BOOL ReadImageAsPGM(LPCTSTR lpszFileName);//��ȡPGMͼ�� 

	//##ModelId=486869620115
	BOOL SaveImageAsBMP(CFile * pSaveFile,    //����IMGͼ��  
						BOOL IsNormal = false);   
	//##ModelId=486869620153
    BOOL SaveImageAsIMG(CFile * pSaveFile);	  //����IMGͼ��	
	//##ModelId=486869620182
	BOOL SaveImageAsPGM(LPCTSTR lpszFileName);//����PGMͼ��    
    // ͼ�����ʾ����
	//##ModelId=4868696201B1
    BOOL ShowCurrentImage(CDC *pMpDc,CRect ShowRect);
	//##ModelId=4868696201E0
    BOOL ShowCurrentImage(CDC *pMpDc,CPoint LTp, CPoint RBp);
	//##ModelId=48686962020F
    BOOL ShowCurrentImage(CDC *pMpDc,int x1, int y1, int x2, int y2);
	//##ModelId=48686962023E
	BOOL ShowPartialImage(CDC *pMpDc,CRect ShowRect,CPoint LTp,CPoint RBp, BOOL Is1to1=false);

	// ���ͼ����Ϣ�ĺ���
	//##ModelId=48686962026C
	eImageType  GetImageType();                        // ���ͼ�������
	//##ModelId=48686962027C
	WORD        GetColorMapNum(int Depth);	           // ��ɫ�����Ŀ
	//##ModelId=48686962027E
    void        SelectChannel(DWORD channel);          // ѡ����ɫ����ʾ����

	//##ModelId=4868696202AB
    P_LONG      GetImageWidth()						   // ���ͼ��Ŀ��
				{ return m_ImageWidth;    }; 
	//##ModelId=4868696202AC
    P_LONG      GetImageHeight()			           // ���ͼ��ĸ߶�
				{ return m_ImageHeight;   };
	//##ModelId=4868696202AD
    WORD        GetImageDepth()					       // ���ͼ������
				{ return m_wImageDepth; };
	//##ModelId=4868696202AE
    double      GetShowScale()					       // ���ͼ�����ʾ����
				{ return m_fScale;         };
	//##ModelId=4868696202AF
    void        SetShowScale(double scale)			   // ����ͼ�����ʾ����
				{ m_fScale = scale;        }; 
	//##ModelId=4868696202B1
	void        GetImageDimensions(LPCTSTR fileName, 
		                         unsigned int &width, 
				                 unsigned int &height, 
								 unsigned int &Depth);

	// ��û�����ͼ��Ҷ�ֵ�ĺ���
	//##ModelId=486869620309
    BYTE      GetGrayV(     long x, long y);     // ��ûҶ�ͼ��ĻҶ�ֵ
	//##ModelId=486869620319
	BYTE      GetGrayV(     double x, double y);     // ��ûҶ�ͼ��ĻҶ�ֵ	
	//##ModelId=486869620328
	P_BYTE      GetXYHueValue(P_LONG x, P_LONG y);     // �������ͼ�������ֵ
	//##ModelId=486869620338
	RGBTRIPLE   GetRGBPixel(  P_LONG x, P_LONG y);     // ��ò�ɫͼ���RGBֵ

	//##ModelId=486869620357
    void        SetRGBPixel(P_LONG x, P_LONG y,RGBTRIPLE color); // ���ò�ɫͼ���RGBֵ
	//##ModelId=486869620366
    void        SetRGBPixel(P_LONG x, P_LONG y,DWORD color);     // ���ò�ɫͼ���RGBֵ
	//##ModelId=486869620386
    void        SetGrayV(   P_LONG x, P_LONG y,P_BYTE gray);     // ���ûҶ�ͼ��ĻҶ�ֵ

	// һЩ����ʱ���õĺ���
	//##ModelId=486869620395
	void	BackUp();		  // bakup image data.
	//##ModelId=4868696203B5
	void	ImgSwap();		  // swap image with bakup image.
	//##ModelId=4868696203C4
	void	NormalBMP();       //��BMPͼת��Ϊ�����ģ����߶� > 0
	//##ModelId=4868696203C5
	BOOL	BakupColorIndex(); // bakup index image color table data.

	//##ModelId=4868696203D4
    void   Inverse();                        // ����Ƭ����ʾ                       
	//##ModelId=4868696203D5
    void   ImageInfo();                      // ��ʾͼ����Ϣ�ĺ���
	//##ModelId=4868696203E3
	
	//--------------------------------------------------------Maybe we can use----------------------------------------------------------------------------------//
	
	
	void   VerticalFlip();                   // ��ֱ��תͼ��
	//##ModelId=4868696203E4
	void   HorizontalFlip();                 // ˮƽ��תͼ��
	//##ModelId=4868696203E5
	void   Rotate90(BOOL Clockwise=TRUE);    // 90.��תͼ��  

	
	
	//-------------------------------------------------------Maybe we can use-----------------------------------------------------------------------------------//
	
	//##ModelId=4868696203E7
	BOOL   CheckPoint(P_LONG &x, P_LONG &y);  // ��������Ч��
	//##ModelId=4868696300A7
	BOOL   CheckPoint(CPoint &pt);            // ��������Ч��
	//##ModelId=486869630134
	BOOL   CheckRect(CPoint &p1,CPoint &p2);  // �����������Ч��
	//##ModelId=4868696301E0
	BOOL   CheckRect(CRect &ImageRect);        // �����������Ч��
	//##ModelId=48686963026C
   	void   CreateHSIImage(DWORD dwType);      // transfer to HSI data
	//##ModelId=48686963028C
	void   SwitchPseudoColor(int type=0);

	//##ModelId=48686963028E
	BOOL   ConvertToGrayImage();
	//##ModelId=4868696302E9
	void   GenerateRowAddress();
	//������������ṩ���ݾ���ĺ���,�ú������ReleaseCopyHandle()�ͷ��ڴ�
	//##ModelId=4868696302EA
	HANDLE   m_hDIB;  	              // handle of transfer  image to clipboard
	//##ModelId=4868696302EB
    HANDLE   GetCopyHandle(CPoint LTp, CPoint RBp);
	//##ModelId=4868696302FA
	void     ReleaseCopyHandle();     // �ͷ�m_hDIB�ڴ�
	
public:	// ��ʼ�������䡢�ͷŲ��֡����ȡ�����ͼ���ڴ�һЩ����
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

