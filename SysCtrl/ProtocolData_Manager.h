#pragma once
#include "stdafx.h"
#include "ProtocolData.h"
#include "ProtocolData_protocol1.h"
#include "ProtocolData_protocol2.h"
#include <map>
#include "Buffer.h"
#include "Cmd.h"
#include "CmdData.h"





class ProtocolData_Manager
{
public:

	static ProtocolData_Manager* GetInstance()
	{
		if (NULL == m_instance)
		{
			m_instance = new ProtocolData_Manager();
		}
		return m_instance; 
	}

	void SetProtocols(CString name, ProtocolData *trans)
	{
		m_transmap[name] = trans;
	}
	void GetProtocols(CString name, ProtocolData *trans)
	{
		trans = m_transmap[name];
	}

	void BeginPreHandleThread();
	static DWORD WINAPI RecvProc(LPVOID lpParameter);

	void Set_pBuffer_recv(CBuffer* pBuffer);
	void Set_pBuffer_send(CBuffer* pBuffer);


	static void PreHandleData(unsigned char *pArray, unsigned int uSize, unsigned char *pFrame, ProtocolData_Manager* p);
	static int GetAFrame(unsigned char c, unsigned char *pFrame);
	~ProtocolData_Manager();	
private:

	HANDLE	m_hThread;
	static ProtocolData_Manager* m_instance;
	std::map<CString, ProtocolData* > m_transmap;
	ProtocolData_Manager();

	CBuffer* m_pBuffer_recv;
	CBuffer* m_pBuffer_send;
	unsigned char* m_pArray;
	unsigned char* m_pCommand;
	
	ProtocolData_Manager* m_ProMgr;

public:
	CCmdData* p_cmddata;
};


struct RECVPARAMX
{
	CBuffer*		buff;
	//std::map<CString, ProtocolData*>*	map;
	ProtocolData* mp1;
	ProtocolData* mp2;
	unsigned char* m_pArray;
	unsigned char* m_pCommand;
	ProtocolData_Manager* p;
};