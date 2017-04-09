
#include "stdafx.h"
#include "TransData_Com.h"
#include "COM_CONSTDEF.h"


void TransData_Com::SendData(char* src, int len) {

}

void TransData_Com::Initial() {

	BOOL bFlag = Init(COM_CTRL_NAME, COM_CTRL_BAUD, COM_CTRL_BUFSIZE, COM_CTRL_CODE);
	if (bFlag)
	{
		BeginRead();
	}
	else
	{
		AfxMessageBox(L"COM Init Fail!");
	}
}


TransData_Com::TransData_Com()
{
	m_hCom = INVALID_HANDLE_VALUE;
	m_pArray = NULL;
	m_pCommandLine = NULL;
	m_isContinue = true;
	m_iReadSizeResult = 0;
	m_bReadStarted = false;

	Timerld = timeSetEvent(40, 0, (LPTIMECALLBACK)SendProc, NULL, TIME_PERIODIC);
	if (Timerld == NULL)
		AfxMessageBox(L"发送缓冲区定时器设置失败");
}


TransData_Com::~TransData_Com()
{
	if (m_pArray != NULL) delete[] m_pArray;
	if (m_pCommandLine != NULL) delete[] m_pCommandLine;
	if (m_hCom != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hCom);
	}
}







bool TransData_Com::InitComm(const CString &com, int baudrate)
{
	//初始化串口
	COMMTIMEOUTS commtimeouts;

	m_hCom = CreateFile(_T("\\\\.\\") + com, GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);

	if (m_hCom == INVALID_HANDLE_VALUE) return false;

	DCB dcb = { 0 };
	if (!GetCommState(m_hCom, &dcb)) return false;

	dcb.BaudRate = baudrate;
	dcb.ByteSize = 8;
	dcb.StopBits = ONESTOPBIT;
	dcb.Parity = NOPARITY;
	dcb.fBinary = TRUE;
	dcb.fDsrSensitivity = false;
	dcb.fParity = 0;
	dcb.fInX = false;
	dcb.fOutX = false;
	dcb.fNull = false;
	dcb.fAbortOnError = false;
	dcb.fOutxCtsFlow = false;
	dcb.fOutxDsrFlow = false;
	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;

	BOOL res;

	res = SetCommState(m_hCom, &dcb);
	if (!res) return false;

	commtimeouts.ReadIntervalTimeout = 0;//MAXDWORD;
	commtimeouts.ReadTotalTimeoutMultiplier = 0;
	commtimeouts.ReadTotalTimeoutConstant = 0;
	commtimeouts.WriteTotalTimeoutMultiplier = 0;
	commtimeouts.WriteTotalTimeoutConstant = 0;

	res = SetCommTimeouts(m_hCom, &commtimeouts);
	if (!res) return false;

	PurgeComm(m_hCom, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	return true;
}

bool TransData_Com::Init(const CString &com, int baudrate, int readbufsize,int iName)
{
	bool res;
	
	m_iName = iName;

	if (readbufsize <= 0) return false;

	m_iReadSize = readbufsize;//指定串口读取大小
	m_iReadBufferSize = readbufsize;//指定串口读取缓存大小

	m_pArray = new char[readbufsize];//开辟指定内存区域
	if (m_pArray == NULL) return false;
	m_pCommandLine = new char[readbufsize];//开辟指定内存区域
	if (m_pCommandLine == NULL) return false;

	res = InitComm(com, baudrate);//根据指定的名字以及波特率初始化串口

	return res;
}



bool TransData_Com::SetReadSize(int size)
{
	//设置读取大小，如果新值小于原缓存大小，仅将大小赋给m_iReadSize，否则不但按新值指定串口读取大小及缓存大小
	//而且重新开辟指定的内存区域
	if (size <= 0) return false;

	if (size <= m_iReadBufferSize)
	{
		m_iReadSize = size;
		return true;
	}

	m_iReadBufferSize = size;
	m_iReadSize = size;

	if (m_pArray != NULL) delete[] m_pArray;
	m_pArray = new char[size];
	if (m_pArray == NULL) return false;

	if (m_pCommandLine != NULL) delete[] m_pCommandLine;
	m_pCommandLine = new char[size];
	if (m_pCommandLine == NULL) return false;

	return true;
}





UINT TransData_Com::Read(void)
{

	HANDLE	    hcom = m_hCom;

	DWORD		dwRes;
	DWORD		dwOvRes;
	DWORD		dwCommEvent;
	DWORD		dwStoredFlags;
	BOOL		isread;
	BOOL		iswait;
	OVERLAPPED	osStatus = { 0 };
	OVERLAPPED	osRead = { 0 };
	COMSTAT		ComStat;
	int			count = 0;
	int			length;
	BOOL		is_timeout;



	dwStoredFlags = EV_RXCHAR;

	PurgeComm(hcom, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	if (!SetCommMask(hcom, dwStoredFlags))
	{
		AfxMessageBox(L"error in setcommmask !");
		return 0;
	}

	osStatus.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (osStatus.hEvent == NULL)
	{
		AfxMessageBox(L"error in create event !");
		CloseHandle(osStatus.hEvent);
		return 0;
	}

	osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (osRead.hEvent == NULL)
	{
		AfxMessageBox(L"error in create read event !");
		CloseHandle(osRead.hEvent);
		return 0;
	}

	isread = false;
	iswait = false;
	is_timeout = false;
	m_isContinue = true;


	//SetCommMask(hcom, dwStoredFlags);

	while (m_isContinue)
	{
		if (is_timeout)
		{
			if (!SetCommMask(hcom, dwStoredFlags))
			{
				AfxMessageBox(L"error in setcommmask1 !");
				//return 0;
				continue;
			}

			is_timeout = false;
		}

		if (WaitCommEvent(hcom, &dwCommEvent, &osStatus))
		{
			isread = true;
		}
		else
		{
			if (GetLastError() == ERROR_IO_PENDING) iswait = true;
			else
			{
				//AfxMessageBox("error in waitcommevent !");
				CloseHandle(osStatus.hEvent);
				CloseHandle(osRead.hEvent);
				//bComFlag = FALSE;
				//::SendMessage(m_hWnd, WM_SERIAL_ERROR, 0, 0);
				AfxMessageBox(L"串口错误");
				return 0;
			}
		}

		if (iswait)
		{
			dwRes = WaitForSingleObject(osStatus.hEvent, THREAD_TIME_WAIT);
			switch (dwRes)
			{
			case WAIT_OBJECT_0:
				if (!GetOverlappedResult(hcom, &osStatus, &dwOvRes, FALSE))
				{
					AfxMessageBox(L"error in waitforsingleobject !");
					CloseHandle(osStatus.hEvent);
					CloseHandle(osRead.hEvent);
					return 0;
				}
				else isread = true;
				break;

			case WAIT_TIMEOUT:
				is_timeout = true;
				break;

			default:
				CloseHandle(osStatus.hEvent);
				CloseHandle(osRead.hEvent);
				return 0;
			}

			iswait = false;
		}

		if (isread)
		{
			ClearCommError(hcom, &dwRes, &ComStat);
			length = ComStat.cbInQue;
			if ((length) > m_iReadBufferSize) length = m_iReadBufferSize;
			ReadFile(hcom, m_pArray, length, &dwRes, &osRead);

			//将数据放入环形缓存
			m_pBuffer_recv->AddData(m_pArray, length);

			isread = false;
		}
	}

	CloseHandle(osStatus.hEvent);
	CloseHandle(osRead.hEvent);

	//	AfxMessageBox("end read !");

	return 0;
}

UINT TransData_Com::Write(void)
{
	char			*array = m_pWriteArray;
	int				size = m_iWriteSize;
	HWND			hwnd = m_hWnd;
	HANDLE			hcom = m_hCom;

	OVERLAPPED		osWrite = { 0 };
	DWORD			dwWritten;
	DWORD			dwRes;

	osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (osWrite.hEvent == NULL)
	{
		AfxMessageBox(L"error create event !");
		return 0;
	}

	if (WriteFile(hcom, array, size, &dwWritten, &osWrite))
	{
		AfxMessageBox(L"write data succeed !");
		CloseHandle(osWrite.hEvent);
		return 0;
	}

	if (GetLastError() != ERROR_IO_PENDING)
	{
		AfxMessageBox(L"write data error !");
		CloseHandle(osWrite.hEvent);
		return 0;
	}

	dwRes = WaitForSingleObject(osWrite.hEvent, INFINITE);
	switch (dwRes)
	{
	case WAIT_OBJECT_0:
		if (!GetOverlappedResult(hcom, &osWrite, &dwWritten, FALSE))
		{
			AfxMessageBox(L"write data error !");
			CloseHandle(osWrite.hEvent);
			return 0;
		}

		break;

	case WAIT_TIMEOUT:
		AfxMessageBox(L"time out !");
		break;

	default:
		AfxMessageBox(L"write data error!");
		break;
	}

	CloseHandle(osWrite.hEvent);

	//	::PostMessage(hwnd,WM_COM_WRITE_FINISH,0,m_iName);

	return 0;
}

UINT TransData_Com::RunWrite(LPVOID lpparam)
{
	TransData_Com* This = (TransData_Com *)(lpparam);

	This->Write();

	return 0;
}

UINT TransData_Com::RunRead(LPVOID lpparam)
{
	TransData_Com* This = (TransData_Com *)(lpparam);

	This->SetReadStartFlag(true);
	This->Read();
	This->SetReadStartFlag(false);

	return 0;
}

void TransData_Com::BeginRead(void)
{
	AfxBeginThread(RunRead, this);
}

void TransData_Com::StopRead(void)
{
	m_isContinue = false;
}

void TransData_Com::WriteData(char *array, int size)
{
	m_pWriteArray = array;
	m_iWriteSize = size;

	Write();
}

void TransData_Com::WriteDataThread(char *array, int size)
{
	m_pWriteArray = array;
	m_iWriteSize = size;

	AfxBeginThread(RunWrite, this);
}

char * TransData_Com::GetReadData(int &iSize)
{
	iSize = m_iReadSizeResult;

	return m_pArray;
}

bool TransData_Com::ReadStopped()
{
	return (!m_bReadStarted);
}

void TransData_Com::SetReadStartFlag(bool bStarted)
{
	m_bReadStarted = bStarted;
}


void TransData_Com::SendProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	//UINT m_TimerId = ::SetTimer(NULL, 0, 1000, TimerProc);
	//int a = 10;
	//发送缓存中的数据
}