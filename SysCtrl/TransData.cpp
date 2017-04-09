#include "stdafx.h"
#include "TransData.h"
#include "Buffer.h"


void TransData::Set_pBuffer_recv(CBuffer* pBuffer)
{
	m_pBuffer_recv = pBuffer;
}

void TransData::Set_pBuffer_send(CBuffer* pBuffer)
{
	m_pBuffer_send = pBuffer;
}