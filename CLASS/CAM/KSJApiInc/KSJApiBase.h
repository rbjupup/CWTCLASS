#ifndef __KSJ_API_BASE_H__
#define __KSJ_API_BASE_H__

// #pragma message("Include KSJApiBase.h") 

#ifdef KSJAPI_EXPORTS
#define KSJ_API __declspec(dllexport)
#elif defined KSJAPI_STATIC
#define KSJ_API
#else
#define KSJ_API __declspec(dllimport)
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef OPTIONAL
#define OPTIONAL
#endif

#ifdef __cplusplus
extern "C"{
#endif
	// Device Type
	enum KSJ_DEVICETYPE
	{
		KSJ_UC130C_MRNN = 0,  // 0 Guass2
		KSJ_UC130M_MRNN,      // Guass2
		KSJ_RESERVED0,
		KSJ_UC320C_MRNN,      // Guass2
		KSJ_UC130C_MRYN,
		KSJ_UC130M_MRYN,
		KSJ_RESERVED1,
		KSJ_UC320C_MRYN,
		KSJ_UC500C_MRNN,
		KSJ_UC500M_MRNN,
		KSJ_UC500C_MRYN,     // 10
		KSJ_UC500M_MRYN,
		KSJ_UC320C_OCR,      // Not Support
		KSJ_UC900C_MRNN,     // Not Support
		KSJ_UC1000C_MRNN,    // Not Support
		KSJ_UC900C_MRYN,     // Not Support
		KSJ_UC1000C_MRYN,    // Not Support
		KSJ_UC130C_MRYY,     // Elanus2
		KSJ_UC130M_MRYY,     // Elanus2 
		KSJ_UD140C_SGNN,     // Not Support
		KSJ_UD140M_SGNN,     // 20 Not Support
		KSJ_UC36C_MGNN,      // Not Support
		KSJ_UC36M_MGNN,      // Not Support
		KSJ_UC36C_MGYN,      // Not Support
		KSJ_UC36M_MGYN,      // Not Support
		KSJ_UC900C_MRYY,     // Elanus2
		KSJ_UC1000C_MRYY,    // Elanus2
		KSJ_UC1400C_MRYY,    // Elanus2
		KSJ_UC36C_MGYY,      // Elanus2
		KSJ_UC36M_MGYY,      // Elanus2
		KSJ_UC320C_MRYY,     // 30 Elanus2
		KSJ_UC500C_MRYY,     // Elanus2
		KSJ_UC500M_MRYY,     // Elanus2
		KSJ_MUC130C_MRYN,    // OEM
		KSJ_MUC130M_MRYN,    // 34 OEM
		KSJ_MUC320C_MRYN,    // OEM
		KSJ_MUC36C_MGYYO,    // Jelly2
		KSJ_MUC36M_MGYYO,    // Jelly2 
		KSJ_MUC130C_MRYY,    // Not Support
		KSJ_MUC130M_MRYY,    // Not Support
		KSJ_MUC320C_MRYY,    // Not Support
		KSJ_MUC500C_MRYYO,   // Jelly2
		KSJ_MUC500M_MRYYO,   // Jelly2
		KSJ_MUC900C_MRYY,    // Not Support
		KSJ_MUC1000C_MRYY,   // Not Support
		KSJ_MUC1400C_MRYY,   // Not Support
		KSJ_UD205C_SGYY,     // Elanus2
		KSJ_UD205M_SGYY,     // Elanus2
		KSJ_UD274C_SGYY,     // Elanus2
		KSJ_UD274M_SGYY,     // Elanus2
		KSJ_UD285C_SGYY,     // Elanus2
		KSJ_UD285M_SGYY,     // Elanus2
		KSJ_MU3C500C_MRYYO,  // Jelly3 
		KSJ_MU3C500M_MRYYO,  // Jelly3
		KSJ_MU3C1000C_MRYYO, // Jelly3
		KSJ_MU3C1400C_MRYYO, // Jelly3
		KSJ_MU3V130C_CGYYO,  // Jelly3
		KSJ_MU3V130M_CGYYO,  // Jelly3
		KSJ_MU3E130C_EGYYO,  // Jelly3
		KSJ_MU3E130M_EGYYO,  // Jelly3
		KSJ_MUC36C_MGYFO,    // Jelly1
		KSJ_MUC36M_MGYFO,    // Jelly1
		KSJ_MU3C120C_MGYYO,  // Jelly3
		KSJ_MU3C120M_MGYYO,  // Jelly3
		KSJ_MU3E200C_EGYYO,  // Jelly3
		KSJ_MU3E200M_EGYYO,  // Jelly3
		KSJ_MUC130C_MRYNO,   // Jelly1
		KSJ_MUC130M_MRYNO,   // Jelly1
		KSJ_MUC320C_MRYNO,   // Jelly1
		KSJ_U3C130C_MRYNO,   // Not Support
		KSJ_U3C130M_MRYNO,   // Not Support
		KSJ_U3C320C_MRYNO,   // Not Support
		KSJ_U3C500C_MRYNO,   // Guass3
		KSJ_U3C500M_MRYNO,   // Guass3
		KSJ_MU3C1401C_MRYYO,
		KSJ_MU3C1001C_MRYYO,
		KSJ_MUC131M_MRYN,    // OEM Device
		KSJ_MU3C501C_MRYYO,
		KSJ_MU3C501M_MRYYO,
		KSJ_MU3C121C_MGYYO,
		KSJ_MU3C121M_MGYYO,
		KSJ_MU3E131C_EGYYO,
		KSJ_MU3E131M_EGYYO,
		KSJ_MU3E201C_EGYYO,
		KSJ_MU3E201M_EGYYO,    
		KSJ_MISSING_DEVICE,	  // Device Lost Program
		KSJ_MU3S230C_SGYYO,   // Jelly3 Sony IMX174
		KSJ_MU3S230M_SGYYO,   // Jelly3 Sony IMX174
		KSJ_MU3S640C_SRYYO,   // Jelly3 Sony IMX178
		KSJ_MU3S640M_SRYYO,   // Jelly3 Sony IMX178
		KSJ_CUD285C_SGYYO,
		KSJ_CUD285M_SGYYO,
		KSJ_MU3S231C_SGYYO,   // Jelly3 Sony IMX249
		KSJ_MU3S231M_SGYYO,   // Jelly3 Sony IMX249
		KSJ_MU3S500C_SGYYO,
		KSJ_MU3S500M_SGYYO,
		KSJ_MU3S1200C_SRYYO,
		KSJ_MU3S1200M_SRYYO,
		KSJ_MU3L2K7C_AGYYO,
		KSJ_MU3L2K7M_AGYYO,
		KSJ_MU3L4K3C_AGYYO,    // 100
		KSJ_MU3L4K3M_AGYYO,
		KSJ_MU3HS2000C_SRYYO,
		KSJ_MU3HS2000M_SRYYO,

		KSJ_MU3HS500C_SGYYO,
		KSJ_MU3HS500M_SGYYO,
		KSJ_MU3HS230C_SGYYO,   // imx174 
		KSJ_MU3HS230M_SGYYO,
		KSJ_MU3HI400C_IGYYO, 
		KSJ_MU3HI400M_IGYYO,

		KSJ_TEST_CAMERA
	};
	// Enable or Disable Log output
	KSJ_API  int __stdcall KSJ_LogSet(bool bEnable, const TCHAR *pszFolder);
	// Get Log Status
	KSJ_API  int __stdcall KSJ_LogGet(bool *bEnable, TCHAR *pszFolder);

	// Get KSJApi.dll Version, call any time.
	KSJ_API  int __stdcall KSJ_GetVersion(OUT int *pnMaj1, OUT int *pnMaj2, OUT int *pnMin1, OUT int *pnMin2);
	// Get Return String Information. call any time.
	KSJ_API  int __stdcall KSJ_GetErrorInfo(IN int nErrorNo, OUT TCHAR pszErrorInfo[256]);
	// Initial KSJApi.dll. This Function don't Open Device, only get connected Device Number.
	KSJ_API  int __stdcall KSJ_Init(void);
	//KSJ_API  int __stdcall KSJ_InitEx(int nMaj, int nMin);

	// Uninitial KSJApi.dll. This should call correspond to KSJ_Init.
	KSJ_API  int __stdcall KSJ_UnInit(void);
	// Get Connected Device Number, Must call after KSJ_Init.
	KSJ_API  int __stdcall KSJ_DeviceGetCount(void);
	// Get Device Information.
	KSJ_API  int __stdcall KSJ_DeviceGetInformation(IN int nIndex, OUT KSJ_DEVICETYPE *pDeviceType, OUT int *pnSerials, OUT unsigned short *pwFirmwareVersion);
	// Get Device Information.
	KSJ_API  int __stdcall KSJ_DeviceGetInformationEx(IN int nIndex, OUT KSJ_DEVICETYPE *pDeviceType, OUT int *pnSerials, OUT unsigned short *pwFirmwareVersion, OUT unsigned short *pwFpgaVersion);
	// Device Parameter Settings
	enum KSJ_PARAM
	{
		KSJ_EXPOSURE = 0,        // Exposure Time (ms)
		KSJ_RED,                 // Red Gain, for line scan sensor map to seg0, for ccd map to KSJ_VGAGAIN
		KSJ_GREEN,               // Green Gain, for line scan sensor map to seg1, for ccd map to KSJ_LAMPLEVEL
		KSJ_BLUE,                // Blue Gain, for CCD map to KSJ_CDSGAIN
		KSJ_GAMMA,               // Gamma
		KSJ_PREVIEW_COLUMNSTART, // Preview Col Start
		KSJ_PREVIEW_ROWSTART,    // Preview Row Start
		KSJ_CAPTURE_COLUMNSTART, // Capture Col Start
		KSJ_CAPTURE_ROWSTART,    // Capture Row Start
		KSJ_HORIZONTALBLANK,     // Horizontal Blank
		KSJ_VERTICALBLANK,       // Vertical Blank
		KSJ_FLIP,                // Flip
		KSJ_BIN,                 // Binning
		KSJ_MIRROR,              // Mirror
		KSJ_CONTRAST,            // Contrast
		KSJ_BRIGHTNESS,          // Brightness
		KSJ_VGAGAIN,             // VGA Gain(CCD)
		KSJ_CLAMPLEVEL,          // Clamp Level(CCD)
		KSJ_CDSGAIN,             // CDS Gain(CCD)
		KSJ_RED_SHIFT,           // Not Use
		KSJ_GREEN_SHIFT,         // Not Use
		KSJ_BLUE_SHIFT,          // Not Use
		KSJ_COMPANDING,          // Companding
		KSJ_EXPOSURE_LINES,      // Exposure Lines
		KSJ_SATURATION,          // Saturation
		KSJ_TRIGGERDELAY,        // Trigger Delay Step = 100uS
		KSJ_STROBEDELAY,         // Not Use
		KSJ_TRIGGER_MODE,        // Trigger Mode
		KSJ_TRIGGER_METHOD,      // Trigger Method
		KSJ_BLACKLEVEL,          // Black Level
		KSJ_BLACKLEVEL_THRESHOLD_AUTO, // Black Level Threshold Auto
		KSJ_BLACKLEVEL_THRESHOLD_LO,   // Black Level Low Threshold
		KSJ_BLACKLEVEL_THRESHOLD_HI    // Black Level High Threshold
	};

	// Get Settings Range
	KSJ_API  int __stdcall KSJ_GetParamRange(IN int nIndex, IN KSJ_PARAM Param, OUT int *pnMinValue, OUT int *pnMaxValue);
	// Set Parameter
	KSJ_API  int __stdcall KSJ_SetParam(IN int nIndex, IN KSJ_PARAM Param, IN  int nValue);
	// Get Current Parameter Value
	KSJ_API  int __stdcall KSJ_GetParam(IN int nIndex, IN KSJ_PARAM Param, OUT int *pnValue);

	// Set Exposure Time (ms) for float format.( more precision )
	KSJ_API  int __stdcall KSJ_ExposureTimeSet(int nIndex, float fExpTimeMs);
	// Get Exposure Time (ms) for float format.
	KSJ_API  int __stdcall KSJ_ExposureTimeGet(int nIndex, float *pfExpTimeMs);

	// Skip Mode (Address Mode)
	enum KSJ_ADDRESSMODE 
	{ 
		KSJ_SKIPNONE = 0, 
		KSJ_SKIP2, 
		KSJ_SKIP3, 
		KSJ_SKIP4,
		KSJ_SKIP8 
	};
	///////////////////////////////////////////Capture/////////////////////////////////
	// Get The Max Capture FOV( Field Of View £© supported by device
	KSJ_API  int __stdcall KSJ_CaptureGetDefaultFieldOfView(int nIndex, int *pnColStart, int *pnRowStart, int *pnColSize, int *pnRowSize, KSJ_ADDRESSMODE *pColAddressMode, KSJ_ADDRESSMODE *pRowAddressMode);
	// Set Capture FOV/AOI( Field Of View / Area Of Interesting £©
	KSJ_API  int __stdcall KSJ_CaptureSetFieldOfView(int nIndex, int nColStart, int nRowStart, int nColSize, int nRowSize, KSJ_ADDRESSMODE ColAddressMode, KSJ_ADDRESSMODE RowAddressMode);
	// Get Current Capture FOV / AOI( Field Of View / Area Of Interesting £©
	KSJ_API  int __stdcall KSJ_CaptureGetFieldOfView(int nIndex, int *pnColStart, int *pnRowStart, int *pnColSize, int *pnRowSize, KSJ_ADDRESSMODE *pColAddressMode, KSJ_ADDRESSMODE *pRowAddressMode);
	// Get Capture Image's Width and Height in Pixel Unit.
	KSJ_API  int __stdcall KSJ_CaptureGetSize(int nIndex, int *pnWidth, int *pnHeight);
	// Get Capture Image's Width, Height in Pixel Unit and BitCount( 8, 24, 32 )
	KSJ_API  int __stdcall KSJ_CaptureGetSizeEx(int nIndex, int *pnWidth, int *pnHeight, int *pnBitCount);
	// Capture Raw Data. ( Note: When Set 16bits, Buffer Should double )
	KSJ_API  int __stdcall KSJ_CaptureRawData(int nIndex, unsigned char *pRawData);
	// Capture 8, 24, 32 Format Image Data.( Note: When Set 16bits, Buffer Should double )
	KSJ_API  int __stdcall KSJ_CaptureRgbData(int nIndex, unsigned char *pRgbData);
	// Capture 8, 24, 32 Format Image Data.( Note: When Set 16bits, Buffer Should double )
	KSJ_API  int __stdcall KSJ_CaptureRgbDataEx(int nIndex, unsigned char *pRgbData, int *pnWidth, int *pnHeight, int *pnBitCount);
	// Save to Bmp Format
	KSJ_API  int __stdcall KSJ_HelperSaveToBmp(unsigned char *pData, int nWidth, int nHeight, int nBitCount, const TCHAR *pszFileName);
	// Save to Jpg Format
	KSJ_API  int __stdcall KSJ_HelperSaveToJpg(unsigned char *pData, int nWidth, int nHeight, int nBitCount, int nQulity, const TCHAR *pszFileName);

	///////////////////////////////////////////Preview/////////////////////////////////
	// Get The Max Preview FOV( Field Of View £© supported by device
	KSJ_API  int __stdcall KSJ_PreviewGetDefaultFieldOfView(int nIndex, int *pnColStart, int *pnRowStart, int *pnColSize, int *pnRowSize, KSJ_ADDRESSMODE *pColAddressMode, KSJ_ADDRESSMODE *pRowAddressMode);
	// Set Preview FOV/AOI( Field Of View / Area Of Interesting £©
	KSJ_API  int __stdcall KSJ_PreviewSetFieldOfView(int nIndex, int nColStart, int nRowStart, int nColSize, int nRowSize, KSJ_ADDRESSMODE ColAddressMode, KSJ_ADDRESSMODE RowAddressMode);
	// Get Current Preview FOV / AOI( Field Of View / Area Of Interesting £©
	KSJ_API  int __stdcall KSJ_PreviewGetFieldOfView(int nIndex, int *pnColStart, int *pnRowStart, int *pnColSize, int *pnRowSize, KSJ_ADDRESSMODE *pColAddressMode, KSJ_ADDRESSMODE *pRowAddressMode);
	// Get Preivew Image's Width and Height in Pixel Unit.
	KSJ_API  int __stdcall KSJ_PreviewGetSize(int nIndex, int *pnWidth, int *pnHeight);
	// Get Preview Image's Width, Height in Pixel Unit and BitCount( 8, 24, 32 )
	KSJ_API  int __stdcall KSJ_PreviewGetSizeEx(int nIndex, int *pnWidth, int *pnHeight, int *pnBitCount);
	// Set Preview Position
	KSJ_API  int __stdcall KSJ_PreviewSetPos(int nIndex, HWND hWnd, int x, int y, int nWidth, int nHeight);
	// Get Preview Position
	KSJ_API  int __stdcall KSJ_PreviewGetPos(int nIndex, int *px, int *py, int *pnWidth, int *pnHeight);
	// Preview Mode
	enum KSJ_PREVIEWMODE
	{
		PM_RAWDATA, 
		PM_RGBDATA
	};
	// Set Preview Mode
	KSJ_API  int __stdcall KSJ_PreviewSetMode(int nIndex, KSJ_PREVIEWMODE PreviewMode);
	// Get Preview Mode
	KSJ_API  int __stdcall KSJ_PreviewGetMode(int nIndex, KSJ_PREVIEWMODE *pPreviewMode);
	// Get Default Mode
	KSJ_API  int __stdcall KSJ_PreviewGetDefaultMode(int nIndex, KSJ_PREVIEWMODE *pPreviewMode);
    // Start or Stop Preview
	KSJ_API  int __stdcall KSJ_PreviewStart(int nIndex, bool bStart);
	// Pause or Resume Preview
	KSJ_API  int __stdcall KSJ_PreviewPause(int nIndex, bool bPause);
	enum    KSJ_PREVIEWSTATUS 
	{
		PS_STOP,
		PS_START,
		PS_PAUSE
	};
	// Get Preview Status
	KSJ_API  int __stdcall KSJ_PreviewGetStatus(int nIndex, KSJ_PREVIEWSTATUS *pPreviewStatus);
	// Get Preview Frame Rate
	KSJ_API  int __stdcall KSJ_PreviewGetFrameRate(int nIndex, float *fFrameRate);
	// Get Paused Image Data when PS_PAUSE Status
	KSJ_API  int __stdcall KSJ_PreviewGetPausedData(int nIndex, unsigned char *pData);
	// Get Paused Image Data when PS_PAUSE Status
	KSJ_API  int __stdcall KSJ_PreviewGetPausedDataEx(int nIndex, unsigned char *pData, int *pnWidth, int *pnHeight, int *pnBitCount);

	// Captrue and Show may Parallel
	KSJ_API  int __stdcall KSJ_PreviewStartEx(int nIndex, bool bStart, bool bParallel );

	KSJ_API  int __stdcall KSJ_PreviewGetStatusEx(int nIndex, KSJ_PREVIEWSTATUS *pPreviewStatus, bool *pbParallel);
	// Get Capture and Show Frame rate when Preview Parallel.
	KSJ_API  int __stdcall KSJ_PreviewGetFrameRateEx(int nIndex, float *fFrameRateCapture, float *fFrameRateShow);






#ifdef __cplusplus
}
#endif

#endif
