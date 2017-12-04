#if !defined(_COMM_ACCESS_FUNCTIONS_AND_DATA)
#define _COMM_ACCESS_FUNCTIONS_AND_DATA
#include <afxmt.h>
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Comm.h : header file
//

/*class ECommError
{
public:
    enum ErrorType
    {
        BAD_SERIAL_PORT    ,
        BAD_BAUD_RATE      ,
        BAD_PORT_NUMBER    ,
        BAD_STOP_BITS      ,
        BAD_PARITY         ,
        BAD_BYTESIZE       ,
        PORT_ALREADY_OPEN  ,
        PORT_NOT_OPEN      ,
        OPEN_ERROR         ,
        WRITE_ERROR        ,
        READ_ERROR         ,
        CLOSE_ERROR        ,
        PURGECOMM          ,
        FLUSHFILEBUFFERS   ,
        GETCOMMSTATE       ,
        SETCOMMSTATE       ,
        SETUPCOMM          ,
        SETCOMMTIMEOUTS    ,
        CLEARCOMMERROR
    };

    ECommError( ErrorType error);

    ErrorType Error;
    DWORD     Errno;   // Errno == return value from GetLastError. Can be used with FormatMessage
};*/

class CCommPort
{
protected:
	CEvent g_event; //信号量
	DWORD dwMilliseconds;//线程等待信号量时间
public:
    enum ErrorType
    {
        BAD_SERIAL_PORT    ,
        BAD_BAUD_RATE      ,
        BAD_PORT_NUMBER    ,
        BAD_STOP_BITS      ,
        BAD_PARITY         ,
        BAD_BYTESIZE       ,
        PORT_ALREADY_OPEN  ,
        PORT_NOT_OPEN      ,
        OPEN_ERROR         ,
        WRITE_ERROR        ,
        READ_ERROR         ,
        CLOSE_ERROR        ,
        PURGECOMM          ,
        FLUSHFILEBUFFERS   ,
        GETCOMMSTATE       ,
        SETCOMMSTATE       ,
        SETUPCOMM          ,
        SETCOMMTIMEOUTS    ,
        CLEARCOMMERROR
    };
	int nErrorNo;
    
	CCommPort();
    ~CCommPort();
    void OpenCommPort(void);
    void CloseCommPort(void);

    bool SendControl(unsigned int CommandType,unsigned int SendValue,unsigned int TransducerNum);
    bool ReadControl(unsigned int TransducerNum, BYTE *StartAddress ,BYTE *ReturnValue,BYTE ReturnNum );
    void SetCommPort(CString port); // void SetCommPort(const std::string & port);
    CString GetCommPort(void); // std::string GetCommPort(void);
    void SetBaudRate(unsigned int newBaud);
    unsigned int GetBaudRate(void);
    void SetParity(BYTE newParity); // see source for possible values
    BYTE GetParity(void);
    void SetByteSize(BYTE newByteSize);
    BYTE GetByteSize(void);
    void SetStopBits(BYTE newStopBits);
    BYTE GetStopBits(void);

    void SetCommDCBProperties(DCB &properties);  // avoid using DCB interface
    void GetCommDCBProperties(DCB &properties);  // Use SetBaudRate et al instead

    void GetCommProperties(COMMPROP &properties);

    void WriteString(const char *outString);
    void WriteBuffer(BYTE  *buffer, unsigned int ByteCount);
    void WriteBufferSlowly(BYTE *buffer, unsigned int ByteCount);
    int ReadString(char *str, unsigned int MaxBytes );
    int ReadBytes(BYTE *bytes, unsigned int byteCount);
    void DiscardBytes(unsigned int MaxBytes);
    void PurgeCommPort(void);
    void FlushCommPort(void);

    void  PutByte(BYTE value);
    BYTE  GetByte();
	bool GetByte2(BYTE *value);
	bool whileByte(BYTE  *buffer, unsigned int ByteCount,BYTE Buffs,int Times);
    unsigned int BytesAvailable(void);
	bool ClearBuffer(void);
    inline bool GetConnected()
    {
        return m_CommOpen;
    }

    inline HANDLE GetHandle() // allow access to the handle in case the user needs to
    {                  // do something hardcore. Avoid this if possible
        return m_hCom;
    }

    inline int GetLastError()
    {
        return nErrorNo;
    }

	bool ReadVelocity(double *Velocity);//读取松下伺服转速
	bool ReadTorque(double *Torque);//读取松下伺服扭矩
	double ReadPos(bool bIsSingleData = FALSE);//读取松下伺服编码器位置
	CString ReadEncoderStatus();//读取松下伺服编码器状态

	BYTE LRC(BYTE *data,int count);

private: 
    CCommPort(const CCommPort &);            // privatize copy construction
    CCommPort & operator=(const CCommPort&);  // and assignment.

    inline void VerifyOpen()
    {
        if(!m_CommOpen)
		{
			nErrorNo = PORT_NOT_OPEN;
//            throw ECommError(ECommError::PORT_NOT_OPEN) ;
		}
    };
    inline void VerifyClosed()
    {
        if(m_CommOpen)
		{
			nErrorNo = PORT_ALREADY_OPEN;
//            throw ECommError(ECommError::PORT_ALREADY_OPEN) ;
		}
    };

  // this stuff is private because we want to hide these details from clients
    bool          m_CommOpen;
    COMMTIMEOUTS  m_TimeOuts;
    CString       m_sCommPort; //std::string   m_CommPort;
    DCB           m_dcb;        // a DCB is a windows structure used for configuring the port
    HANDLE        m_hCom;       // handle to the comm port.
};

#endif // !defined(_COMM_ACCESS_FUNCTIONS_AND_DATA)
