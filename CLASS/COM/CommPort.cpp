// Com232.cpp : implementation file
//

#include "stdafx.h"
#include "COMMPORT.H "
#ifndef  USE_DLL

CCommPort::CCommPort()
	:m_CommOpen(false),
	m_sCommPort("COM6"),
	m_hCom(0)
{
	m_dcb.DCBlength = sizeof(DCB);
	m_dcb.BaudRate  =115200;
	m_dcb.ByteSize  =8;
	m_dcb.Parity    =NOPARITY;//EVENPARITY;    //NOPARITY and friends are #defined in windows.h
	m_dcb.StopBits  =ONESTOPBIT;//TWOSTOPBITS;//ONESTOPBIT;//  //ONESTOPBIT is also from windows.h

	nErrorNo = -1;
	dwMilliseconds=2000;
	g_event.SetEvent();
}

CCommPort::~CCommPort()
{
	if(m_CommOpen)
		CloseCommPort();
}

////////////////////////////////////////////////////////////////////////////////
void CCommPort::OpenCommPort(void)
{
	if(m_CommOpen)   // if already open, don't bother
		return;

	DCB tempDCB;
	tempDCB.BaudRate  =  m_dcb.BaudRate;
	tempDCB.ByteSize  =  m_dcb.ByteSize;
	tempDCB.Parity    =  m_dcb.Parity;
	tempDCB.StopBits  =  m_dcb.StopBits;

	m_hCom = CreateFile(m_sCommPort, // m_sCommPort.c_str(),
		GENERIC_READ | GENERIC_WRITE,
		0,    /* comm devices must be opened w/exclusive-access */
		NULL, /* no security attrs */
		OPEN_EXISTING, /* comm devices must use OPEN_EXISTING */
		0,    /* not overlapped I/O */
		NULL  /* hTemplate must be NULL for comm devices */
		);

	if(m_hCom == INVALID_HANDLE_VALUE)
	{
		nErrorNo = OPEN_ERROR;
		//        throw ECommError(ECommError::OPEN_ERROR);
	}


	// Now get the DCB properties of the port we just opened
	if(!GetCommState(m_hCom,&m_dcb))
	{
		// something is hay wire, close the port and return
		CloseHandle(m_hCom);
		nErrorNo = GETCOMMSTATE;
		return ;
		//        throw ECommError(ECommError::GETCOMMSTATE);
	}

	// dcb contains the actual port properties.  Now copy our settings into this dcb
	m_dcb.BaudRate  =  tempDCB.BaudRate;
	m_dcb.ByteSize  =  tempDCB.ByteSize;
	m_dcb.Parity    =  tempDCB.Parity;
	m_dcb.StopBits  =  tempDCB.StopBits;

	// now we can set the properties of the port with our settings.
	if(!SetCommState(m_hCom,&m_dcb))
	{
		// something is hay wire, close the port and return
		CloseHandle(m_hCom);
		nErrorNo = SETCOMMSTATE;
		return ;
		//        throw ECommError(ECommError::SETCOMMSTATE);
	}

	if(!SetupComm(m_hCom, 64, 32))
	{
		// something is hay wire, close the port and return
		CloseHandle(m_hCom);
		nErrorNo = SETUPCOMM;
		return ;
		//        throw ECommError(ECommError::SETUPCOMM);
	}

	m_TimeOuts.ReadIntervalTimeout         = 5;
	m_TimeOuts.ReadTotalTimeoutMultiplier  = 1;
	m_TimeOuts.ReadTotalTimeoutConstant    = 40;
	m_TimeOuts.WriteTotalTimeoutMultiplier = 1;
	m_TimeOuts.WriteTotalTimeoutConstant   = 20;
	if(!SetCommTimeouts(m_hCom, &m_TimeOuts))
	{
		// something is hay wire, close the port and return
		CloseHandle(m_hCom);
		nErrorNo = SETCOMMTIMEOUTS;
		return ;
		//        throw ECommError(ECommError::SETCOMMTIMEOUTS);
	}

	// if we made it to here then success
	m_CommOpen = true;
}

////////////////////////////////////////////////////////////////////////////////
void CCommPort::CloseCommPort(void)
{
	if(!m_CommOpen)       // if already closed, return
		return;

	if(CloseHandle(m_hCom) != 0) // CloseHandle is non-zero on success
	{
		m_CommOpen = false;
	}
	else
	{
		nErrorNo = CLOSE_ERROR;
		//      throw ECommError(ECommError::CLOSE_ERROR);
	}
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
void CCommPort::SetCommDCBProperties(DCB &properties)
{
	if(m_CommOpen)  // port is open
	{
		if(!SetCommState(m_hCom,&properties))  // try to set the state directly
		{
			nErrorNo = SETCOMMSTATE;
			//            throw ECommError(ECommError::SETCOMMSTATE);          // bomb out if failed
		}
		else                                       // copy the new properties
			m_dcb = properties;                      // if success
	}
	else                                         // comm port is not open
		m_dcb = properties;                        // best we can do is save a copy
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

void CCommPort::GetCommDCBProperties(DCB &properties)
{
	properties = m_dcb;
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

void CCommPort::SetBaudRate(unsigned int newBaud)
{
	unsigned int oldBaudRate = m_dcb.BaudRate; // make a backup of the old baud rate
	m_dcb.BaudRate = newBaud;                // assign new rate

	if(m_CommOpen)                     // check for open comm port
	{
		if(!SetCommState(m_hCom,&m_dcb))   // try to set the new comm settings
		{                                      // if failure
			m_dcb.BaudRate = oldBaudRate;        // restore old baud rate
			nErrorNo = BAD_BAUD_RATE;
			//            throw ECommError(ECommError::BAD_BAUD_RATE);     // bomb out
		}
	}
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
void CCommPort::SetByteSize(BYTE newByteSize)
{
	BYTE oldByteSize = m_dcb.ByteSize; // make a backup of the old byte size
	m_dcb.ByteSize = newByteSize;              // assign new size

	if(m_CommOpen)                     // check for open comm port
	{
		if(!SetCommState(m_hCom,&m_dcb))     // try to set the new comm settings
		{                                      // if failure
			m_dcb.ByteSize = oldByteSize;          // restore old byte size
			nErrorNo = BAD_BYTESIZE;
			//            throw ECommError (ECommError::BAD_BYTESIZE);                        // bomb out
		}
	}
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
void CCommPort::SetParity(BYTE newParity)
{
	BYTE oldParity = m_dcb.Parity;     // make a backup of the old parity
	m_dcb.Parity = newParity;                  // assign new parity

	if(m_CommOpen)                     // check for open comm port
	{
		if(!SetCommState(m_hCom,&m_dcb))     // try to set the new comm settings
		{                                    // if failure
			m_dcb.Parity = oldParity;              // restore old parity
			nErrorNo = BAD_PARITY;
			//            throw ECommError(ECommError::BAD_PARITY);  // bomb out
		}
	}
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
void CCommPort::SetStopBits(BYTE newStopBits)
{
	BYTE oldStopBits = m_dcb.StopBits; // make a backup of old #of stop bits
	m_dcb.StopBits = newStopBits;              // assign new # of stop bits

	if(m_CommOpen)                     // check for open comm port
	{
		if(!SetCommState(m_hCom,&m_dcb))     // try to set the new comm settings
		{                                    // if failure
			m_dcb.StopBits = oldStopBits;          // restore old # of stop bits
			nErrorNo = BAD_STOP_BITS;
			//            throw ECommError(ECommError::BAD_STOP_BITS);                        // bomb out
		}
	}
}
////////////////////////////////////////////////////////////////////////////////

unsigned int CCommPort::GetBaudRate(void)
{
	return m_dcb.BaudRate;
}

BYTE CCommPort::GetByteSize(void)
{
	return m_dcb.ByteSize;
}

BYTE CCommPort::GetParity(void)
{
	return m_dcb.Parity;
}

BYTE CCommPort::GetStopBits(void)
{
	return m_dcb.StopBits;
}

void CCommPort::WriteBuffer(BYTE *buffer, unsigned int ByteCount)
{
	VerifyOpen();
	DWORD dummy;
	if( (ByteCount == 0) || (buffer == NULL))
		return;
	WaitForSingleObject(g_event,dwMilliseconds);
	g_event.ResetEvent();
	if(!WriteFile(m_hCom,buffer,ByteCount,&dummy,NULL))
	{
		nErrorNo = WRITE_ERROR;
		//        throw ECommError(ECommError::WRITE_ERROR);
	}
	g_event.SetEvent();
}
bool CCommPort::whileByte(BYTE  *buffer, unsigned int ByteCount,BYTE Buffs,int Times)
{
	while(Times>0)
	{
		WriteBuffer(buffer,ByteCount);
		while (Times--&&!BytesAvailable())
		{
			Sleep(1);
		}
		for (int i=0;i<(int)BytesAvailable();i++)
		{
			if (GetByte()==Buffs)
			{
				return TRUE;
			}
		}
		Sleep(1);
		Times--;
	}
	return FALSE;
}
void CCommPort::WriteBufferSlowly(BYTE *buffer, unsigned int ByteCount)
{
	VerifyOpen();
	DWORD dummy;
	BYTE *ptr = buffer;

	for (unsigned int j=0; j<ByteCount; j++)
	{
		WaitForSingleObject(g_event,dwMilliseconds);
		g_event.ResetEvent();
		if(!WriteFile(m_hCom,ptr,1,&dummy,NULL))
		{
			nErrorNo = WRITE_ERROR;
			//            throw ECommError(ECommError::WRITE_ERROR);
		}
		g_event.SetEvent();
		// Use FlushCommPort to wait until the character has been sent.
		FlushCommPort();
		++ptr;
	}
}

void CCommPort::WriteString(const char *outString)
{
	VerifyOpen();

	DWORD dummy;
	WaitForSingleObject(g_event,dwMilliseconds);
	g_event.ResetEvent();
	if(!WriteFile(m_hCom,outString, strlen(outString),&dummy,NULL))
	{
		nErrorNo = WRITE_ERROR;
		//        throw ECommError(ECommError::WRITE_ERROR);
	}
	g_event.SetEvent();
}

int CCommPort::ReadBytes(BYTE *buffer, unsigned int MaxBytes)
{
	VerifyOpen();
	DWORD bytes_read;
	WaitForSingleObject(g_event,dwMilliseconds);
	g_event.ResetEvent();
	if(!ReadFile(m_hCom,buffer,MaxBytes,&bytes_read,NULL))
	{
		nErrorNo = READ_ERROR;
		//        throw ECommError(ECommError::READ_ERROR);
	}
	g_event.SetEvent();
	// add a null terminate if bytes_read < byteCount
	// if the two are equal, there is no space to put a null terminator
	if(bytes_read < MaxBytes)
		buffer[bytes_read]='\0';

	return bytes_read;
}

int CCommPort::ReadString(char *str, unsigned int MaxBytes )
{
	VerifyOpen();

	if(MaxBytes == 0u)
		return 0;
	str[0]='\0';
	unsigned int  Bytes;
	Bytes=BytesAvailable();
	if(Bytes ==0)
	{
		return 0;
	}
	else if (Bytes<MaxBytes)
	{
		MaxBytes=Bytes;
	}
	BYTE NewChar;
	unsigned int Index=0;
	while(Index < MaxBytes)
	{
		NewChar = GetByte();
		// if the byte is a \r or \n, don't add it to the string
		if( (NewChar != '\r') && (NewChar != '\n'))
		{
			str[Index] = (char) NewChar;
			Index++;
		}

		// when /r is received, we are done reading the string, so return
		// don't forget to terminate the string with a \0.
		if(NewChar == '\r')
		{
			str[Index] = '\0';
			return Index +1;
		}
	}

	// if the while loop false through, then MaxBytes were received without
	// receiveing a \n. Add null terminator to the string and return the number
	str[MaxBytes-1]='\0';
	return MaxBytes;
}

void CCommPort::DiscardBytes(unsigned int MaxBytes)
{
	VerifyOpen();
	if(MaxBytes == 0)
		return;

	BYTE *dummy= new BYTE[MaxBytes];
	ReadBytes(dummy, MaxBytes); // 串口号在此函数中
	delete []dummy;
}

void CCommPort::PurgeCommPort(void)
{
	VerifyOpen();
	if(!PurgeComm(m_hCom,PURGE_RXCLEAR))
	{
		nErrorNo = PURGECOMM;
		//        throw ECommError(ECommError::PURGECOMM);
	}

}

void CCommPort::FlushCommPort(void)
{
	VerifyOpen();
	WaitForSingleObject(g_event,dwMilliseconds);
	g_event.ResetEvent();
	if(!FlushFileBuffers(m_hCom))
	{
		nErrorNo = FLUSHFILEBUFFERS;
		//        throw ECommError(ECommError::FLUSHFILEBUFFERS);
	}
	g_event.SetEvent();
}
void CCommPort::PutByte(BYTE value)
{
	VerifyOpen();

	DWORD dummy;
	WaitForSingleObject(g_event,dwMilliseconds);
	g_event.ResetEvent();
	if(!WriteFile(m_hCom,&value,1,&dummy,NULL))
	{
		nErrorNo = WRITE_ERROR;
		//        throw ECommError(ECommError::WRITE_ERROR);
	}
	g_event.SetEvent();
}

BYTE CCommPort::GetByte()
{
	VerifyOpen();

	DWORD dummy;
	BYTE  value;
	WaitForSingleObject(g_event,dwMilliseconds);
	g_event.ResetEvent();
	if(!ReadFile(m_hCom,&value,1,&dummy,NULL))
	{
		nErrorNo = READ_ERROR;
		//        throw ECommError(ECommError::READ_ERROR);
	}
	g_event.SetEvent();
	return value;
}   
bool CCommPort::GetByte2(BYTE *value)
{
	VerifyOpen();
	if (!BytesAvailable())
	{
		return false;
	}

	DWORD dummy;
	WaitForSingleObject(g_event,dwMilliseconds);
	g_event.ResetEvent();
	if(!ReadFile(m_hCom,value,1,&dummy,NULL))
	{
		nErrorNo = READ_ERROR;
		//        throw ECommError(ECommError::READ_ERROR);
	}
	g_event.SetEvent();
	return true;
} 
unsigned int CCommPort::BytesAvailable(void)
{
	VerifyOpen();

	COMSTAT comstat;
	DWORD dummy;
	if (!m_CommOpen)
	{
		return false;
	}
	if(!ClearCommError(m_hCom, &dummy, &comstat))
	{
		nErrorNo = CLEARCOMMERROR;
		//        throw ECommError(ECommError::CLEARCOMMERROR);
	}
	return comstat.cbInQue;
}
bool CCommPort::ClearBuffer(void)
{
	int n=BytesAvailable();
	if (n>0)
	{
		byte *Buffer=new byte[n];
		ReadBytes(Buffer,n);
		delete []Buffer;
	}
	return TRUE;
}
void CCommPort::SetCommPort(CString port) // void CCommPort::SetCommPort(const std::string & port)
{
	nErrorNo = -1;

	VerifyClosed();   // can't change comm port once comm is open
	// could close and reopen, but don't want to

	m_sCommPort = port;
}

CString CCommPort::GetCommPort(void) // std::string CCommPort::GetCommPort(void)
{
	return m_sCommPort;
}

void CCommPort::GetCommProperties(COMMPROP &properties)
{
	VerifyOpen();

	COMMPROP prop;
	ZeroMemory(&prop, sizeof(COMMPROP));
	::GetCommProperties(m_hCom, &prop);

	properties = prop;
}

//---------------------------------------------------------------------------
// 资料格式，变频器设置P92 = 04 : Modbus RTU 模式, 资料格式: <8,E,1>
// 通讯地址，变频器设置P88 = 01~254 
// 通讯速度，变频器设置P89 = 01 : 9600 Baud Rate
// 台达DELTA变频器写指令
bool CCommPort::SendControl(
	unsigned int CommandType,   // 写指令方式, 0=初始化
	unsigned int SendValue,     // 待发送数据
	unsigned int TransducerNum) // 通讯地址
{
	unsigned char  pControlCode[8];
	unsigned int   tmpValue;
	if(CommandType==0) // 初始化
	{
		tmpValue=SendValue; // 待发送数据
		pControlCode[0]=TransducerNum;   // 通讯地址
		pControlCode[1]=0x06;            // CMD, 指令码   // 03H=读取N个字, 06H=写1个字(word)
		pControlCode[2]=0x20;            // 数据地址 // 0x2001 = 写频率指令的地址
		pControlCode[3]=0x01;            // 数据地址
		pControlCode[4]=tmpValue>>8;     // 待发送数据
		pControlCode[5]=tmpValue;
	}
	else
	{
		pControlCode[0]=TransducerNum;   // 通讯地址
		pControlCode[1]=0x06;            // CMD, 指令码   // 03H=读取N个字, 06H=写1个字(word)
		pControlCode[2]=0x20;            // 数据地址 // 0x2000 = 对驱动器的指令地址, 启停正反向
		pControlCode[3]=0x00;            // 数据地址
		pControlCode[4]=0x00;
		pControlCode[5]=SendValue;       // 待发送数据
	}
	unsigned int reg_crc=0xFFFF;
	for(int i=0;i<6;i++)
	{
		reg_crc^=pControlCode[i];
		for(int j=0;j<8;j++)
		{
			if(reg_crc&0x01)
				reg_crc=(reg_crc>>1)^0xA001;
			else
				reg_crc=reg_crc>>1;
		}
	}
	pControlCode[6]=reg_crc;
	pControlCode[7]=reg_crc>>8;
	WriteBuffer(pControlCode,sizeof(unsigned char)*8); // 串口号在此函数中
	Sleep(100);

	//vertify
	unsigned char szByteAvailable = BytesAvailable();
	if(szByteAvailable!=sizeof(unsigned char)*8)
		return false;

	unsigned char BytesRead =0;
	if(szByteAvailable > 0)
	{
		BYTE *buffer = new BYTE[szByteAvailable];
		BytesRead = ReadBytes(buffer,szByteAvailable); // 串口号在此函数中
		if(BytesRead)
		{
			for(int i=0;i<sizeof(unsigned char)*8;i++)
			{
				if(buffer[i]!=pControlCode[i])
				{
					delete []buffer;
					return false;
				}
			}
		}
		delete []buffer;
		return true;
	}

	return false;
}

//---------------------------------------------------------------------------
// 资料格式，变频器设置P92 = 04 : Modbus RTU 模式, 资料格式: <8,E,1>
// 通讯地址，变频器设置P88 = 01~254 
// 通讯速度，变频器设置P89 = 01 : 9600 Baud Rate
// 台达DELTA变频器读指令
bool CCommPort::ReadControl(
	unsigned int TransducerNum,  // 通讯地址
	unsigned char *StartAddress, // 读起始地址
	unsigned char *ReturnValue,  // 读回应值
	BYTE     ReturnNum )         // 读取N个字
{
	unsigned char  pControlCode[8];

	pControlCode[0]=TransducerNum;   // ADR, 通讯地址
	pControlCode[1]=0x03;            // CMD, 指令码   // 03H=读取N个字, 06H=写1个字(word)
	pControlCode[2]=StartAddress[1]; // 读起始地址 如 = 0x21 // tmpChar[1]=0x21 // 0x2102
	pControlCode[3]=StartAddress[0]; // 读起始地址 如 = 0x02 // tmpChar[0]=0x02
	pControlCode[4]=0;               // 资料数
	pControlCode[5]=ReturnNum;       // 资料数 // 读取N个字, N最大为12(以word计算)

	unsigned int reg_crc=0xFFFF;
	for(int i=0;i<6;i++)
	{
		reg_crc^=pControlCode[i];
		for(int j=0;j<8;j++)
		{
			if(reg_crc&0x01)
				reg_crc=(reg_crc>>1)^0xA001;
			else
				reg_crc=reg_crc>>1;
		}
	}
	pControlCode[6]=reg_crc;        // RCR CHK Low
	pControlCode[7]=reg_crc>>8;     // RCR CHK High

	WriteBuffer(pControlCode,sizeof(unsigned char)*8); // 串口号在此函数中

	Sleep(100);

	//vertify
	unsigned char szByteAvailable = BytesAvailable();
	if(szByteAvailable!=sizeof(unsigned char)*(5+ReturnNum*2))
		return false;

	unsigned char BytesRead =0;
	if(szByteAvailable > 0)
	{
		BYTE *buffer = new BYTE[szByteAvailable];
		BytesRead = ReadBytes(buffer,szByteAvailable); // 回应读起始地址如0x2102中的内容 // 串口号在此函数中
		if(BytesRead)
		{
			if(buffer[0]!=pControlCode[0])
				return false;
			memcpy(ReturnValue,buffer+3,ReturnNum*2); // 读回应值
			//	ShowMessage(IntToStr(buffer[4])+"x"+IntToStr(buffer[3]));
		}
		delete []buffer;
		return true;
	}

	return false;
}
BYTE CCommPort::LRC(BYTE *data,int count)
{
	int s=0;
	BYTE s2;
	for (int i=0;i<count;i++)
	{
		s=s+data[i];
	}
	s2=s%256;
	s2=255-s2+1;
	return s2;
}
double CCommPort::ReadPos(bool bIsSingleData)
{
	double dis=0;
	if (BytesAvailable()>0)
	{
		int n=BytesAvailable();
		BYTE *buff=new BYTE[n];
		ReadBytes(buff,n);
		delete[] buff;
	}
	PutByte(0x05);
	BYTE s=GetByte();
	if (s==0x04)
	{
		BYTE data[4]={0x00,0x01,0xd2,0x00};
		data[3]=LRC(data,3);
		WriteBuffer(data,4);
		s=GetByte();
		if (s==0x06)
		{
			s=GetByte();
			if (s==0x05)
			{
				PutByte(0x04);
				for (int i = 0; i<10;i++)
				{
					if (BytesAvailable()==15)
					{
						break;
					}
					Sleep(2);
				}
				BYTE*buff=new BYTE[15];
				ReadBytes(buff,15);
				if (LRC(buff,14)==buff[14])
				{
					PutByte(0x06);					
					int l=buff[7];
					int m = buff[8];
					int h=buff[9];
					dis=(h<<16)|(m<<8)|l;
					if (bIsSingleData==false)//读取多圈数据
					{
						l = buff[10];
						h = buff[11];
						int count = h<<8|l;
						if (count>32768)
						{
							count -=65536;
						}
						dis = count* 0x7fffff +dis;
					}
				}
				else
				{
					PutByte(0x15);
				}
				delete []buff;
				return dis;
			}
		}
	}
	return 0;
}
CString CCommPort::ReadEncoderStatus()//读取松下伺服编码器状态
{
	CString str = "通讯异常";
	double dis=0;
	if (BytesAvailable()>0)
	{
		int n=BytesAvailable();
		BYTE *buff=new BYTE[n];
		ReadBytes(buff,n);
		delete[] buff;
	}
	PutByte(0x05);
	BYTE s=GetByte();
	if (s==0x04)
	{
		BYTE data[4]={0x00,0x01,0xd2,0x00};
		data[3]=LRC(data,3);
		WriteBuffer(data,4);
		s=GetByte();
		if (s==0x06)
		{
			s=GetByte();
			if (s==0x05)
			{
				PutByte(0x04);
				for (int i = 0; i<10;i++)
				{
					if (BytesAvailable()==15)
					{
						break;
					}
					Sleep(2);
				}
				
				BYTE*buff=new BYTE[15];
				ReadBytes(buff,15);
				if (LRC(buff,14)==buff[14])
				{
					str="正常";
					PutByte(0x06);
					int l=buff[5];
					if (l&1<<7)str = "电池报警";
					if (l&1<<6)str = "电池报警";
					if (l&1<<5)str = "多圈报警";
					if (l&1<<3)str = "计数器溢出";
					if (l&1<<2)str = "计数报警";
					if (l&1<<1)str = "全绝对式状态";
					if (l&1<<0)str = "过速度";
				}
				else
				{
					PutByte(0x15);
				}

				delete []buff;
				return str;
			}
		}
	}
	return str;
}
bool CCommPort::ReadTorque(double *Torque)
{
	*Torque=0;
	if (BytesAvailable()>0)
	{
		int n=BytesAvailable();
		BYTE *buff=new BYTE[n];
		ReadBytes(buff,n);
		delete[] buff;
	}
	PutByte(0x05);
	BYTE s=GetByte();
	if (s==0x04)
	{
		BYTE data[4]={0x00,0x01,0x52,0x00};
		data[3]=LRC(data,3);
		WriteBuffer(data,4);
		s=GetByte();
		if (s==0x06)
		{
			s=GetByte();
			if (s==0x05)
			{
				PutByte(0x04);
				BYTE*buff=new BYTE[7];
				ReadBytes(buff,7);
				if (LRC(buff,6)==buff[6])
				{
					PutByte(0x06);
					int h=buff[4];//高8位
					int l=buff[3];//低8位
					//	h=0XAF;
					//	l=0XC8;
					short T=(h<<8)|l;//合成16位
					double Tv=T;
					Tv=Tv/2000*2.0*100.0;//扭矩转换 单位Ncm
					*Torque=Tv;
					delete []buff;
					return 1;
				}
				else
				{
					PutByte(0x15);
					delete []buff;
					return 0;
				}
			}
		}
	}
	return 0;

}
bool CCommPort::ReadVelocity(double *Velocity)
{
	*Velocity=0;
	if (BytesAvailable()>0)
	{
		int n=BytesAvailable();
		BYTE *buff=new BYTE[n];
		ReadBytes(buff,n);
		delete[] buff;
	}
	PutByte(0x05);
	BYTE s=GetByte();
	if (s==0x04)
	{
		BYTE data[4]={0x00,0x01,0x42,0x00};
		data[3]=LRC(data,3);
		WriteBuffer(data,4);
		s=GetByte();
		if (s==0x06)
		{
			s=GetByte();
			if (s==0x05)
			{
				PutByte(0x04);
				BYTE*buff=new BYTE[7];
				ReadBytes(buff,7);
				if (LRC(buff,6)==buff[6])
				{
					PutByte(0x06);
					int h=buff[4];//高8位
					int l=buff[3];//低8位
					//	h=0XAF;
					//	l=0XC8;
					short V=(h<<8)|l;//合成16位
					double Tv=V;
					*Velocity=Tv;//单位 r/min
					delete []buff;
					return 1;
				}
				else
				{
					PutByte(0x15);
					delete []buff;
					return 0;
				}
			}
		}
	}
	return 0;
}
#endif