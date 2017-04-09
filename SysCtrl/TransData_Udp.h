/*---------------------------------------------------
文件名: TransData_Udp.h
用  途: UDP通信类
日  期: 2017.04.08
版  本: 1.0
编  制: 金 健
---------------------------------------------------*/


#pragma once
#include "stdafx.h"
#include "TransData.h"
#include "UDP_CONSTDEF.h"
#include <mmsystem.h>


#pragma comment(lib,"winmm")

struct RECVPARAM
{
	SOCKET		sock;
	CBuffer*	buff_recv;
};


class TransData_Udp : public TransData
{
public:
	void SendData(char* src, int len);	
	void Initial();

	TransData_Udp();
	~TransData_Udp();
	void SetNet(CString, int, CString, int);
	static DWORD WINAPI RecvProc(LPVOID lpParameter);
	static void CALLBACK SendProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);

private:
	CString str_localIP, str_remoteIP;
	int i_localPort, i_remotePort;

	SOCKET						m_socketServer;
	SOCKET						m_socketClient;
	SOCKADDR_IN					addrSock;
	SOCKADDR_IN					addrFrom;
	SOCKADDR_IN					addrSrv;
	HANDLE						m_hThread;
	MMRESULT Timerld;
};