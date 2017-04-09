#include "stdafx.h"
#include "ProtocolData_Manager.h"


ProtocolData_Manager* ProtocolData_Manager::m_instance = NULL;

void ProtocolData_Manager::BeginPreHandleThread()
{	
	RECVPARAMX *pRecvParam = new RECVPARAMX;
	pRecvParam->mp1 = m_transmap[L"协议一"];
	pRecvParam->mp2 = m_transmap[L"协议二"];
	pRecvParam->buff = m_pBuffer_recv;
	pRecvParam->m_pArray = m_pArray;
	pRecvParam->m_pCommand = m_pCommand;
	pRecvParam->p = m_ProMgr;
	//pRecvParam->map = &m_transmap;

	m_hThread = CreateThread(NULL, 0, RecvProc, (LPVOID)(pRecvParam), 0, NULL);
	CloseHandle(m_hThread);
}

DWORD WINAPI  ProtocolData_Manager::RecvProc(LPVOID lpParameter)
{

	CBuffer* buff_recv = ((RECVPARAMX*)lpParameter)->buff;
	//std::map<CString, ProtocolData* > m_transmap = *( (std::map<CString, ProtocolData* >*)(lpParameter) );
	ProtocolData* mp1 = ((RECVPARAMX*)lpParameter)->mp1;
	ProtocolData* mp2 = ((RECVPARAMX*)lpParameter)->mp2;
	unsigned char* m_pArray = ((RECVPARAMX*)lpParameter)->m_pArray;
	unsigned char* m_pCommand = ((RECVPARAMX*)lpParameter)->m_pCommand;
	ProtocolData_Manager* m_ProMgr = ((RECVPARAMX*)lpParameter)->p;
	//mp1->show();

	while (true)
	{
		if (buff_recv->GetSize() > 0)
		{
			int len = buff_recv->GetSize();
			buff_recv->GetData((char*)m_pArray, len);
			PreHandleData(m_pArray, len, m_pCommand, m_ProMgr);
		}
		//if (buff_recv->GetSize() == 10)
		//{
		//	//ProtocolData* p_handle = m_transmap[L"协议一"];
		//	
		//	mp1->show();
		//	buff_recv->ClearBuffer();
		//}
		//else if (buff_recv->GetSize() == 9)
		//{
		//	//ProtocolData* p_handle = m_transmap[L"协议二"];
		//	//p_handle->show();
		//	mp2->show();
		//	buff_recv->ClearBuffer();
		//}
	}
	
	return 0;
}

void ProtocolData_Manager::Set_pBuffer_recv(CBuffer* pBuffer)
{
	m_pBuffer_recv = pBuffer;
}

void ProtocolData_Manager::Set_pBuffer_send(CBuffer* pBuffer)
{
	m_pBuffer_send = pBuffer;
}

void ProtocolData_Manager::PreHandleData(unsigned char *pArray, unsigned int uSize, unsigned char *pFrame, ProtocolData_Manager* p)
{
	unsigned int uArrayInd;// , uFrameInd;
	for (uArrayInd = 0; uArrayInd < uSize; uArrayInd++)
	{
		int resLen = GetAFrame(pArray[uArrayInd], pFrame);
		if (resLen != -1)
		{			
			p->p_cmddata = new CCmdData;
			p->p_cmddata->HandleData(pFrame, resLen);
			//得到一包数据
			int a = 10;
			//选择一个协议处理			
			//mp1->handledata(pFrame,resLen);
			//mp2->handledata(pFrame,resLen);
		}
	}	
}

int ProtocolData_Manager::GetAFrame(unsigned char c, unsigned char *pFrame)
{
	static int status = -1;
	static unsigned char crc_sum = 0;
	static int comReadNum = 0;
	int retStatus = -1;

	switch (status)
	{
	case -1:  //报头未找到
	{
		if (c == 0x7b)
		{
			status = 0;
			pFrame[0] = 0x7b;
			comReadNum = 1;
		}
		break;
	}
	case 0:
	{

		if (comReadNum > 1000)
		{
			status = -1;
			return -1;
		}
			
		pFrame[comReadNum] = c;
		comReadNum++;
		crc_sum += c;
		if (0x0d == c)
		{
			status = 2;
		}
		break;

	}
	case 2:
	{
		if (0x0a == c)
		{
			retStatus = 1;
			status = -1;
			pFrame[comReadNum] = c;
		}
		else
		{
			status = -1;
		}
		break;
	}

	default:break;
	}
	return retStatus;
}

ProtocolData_Manager::ProtocolData_Manager()
{
	m_pArray = new unsigned char[1000];
	m_pCommand = new unsigned char[1000];
	memset(m_pArray, 0, 1000);
	memset(m_pArray, 0, 1000);
	m_ProMgr = this;
}

ProtocolData_Manager::~ProtocolData_Manager()
{
	delete[] m_pArray;
	delete[] m_pCommand;
}

