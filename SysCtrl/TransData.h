/*---------------------------------------------------
文件名: TransData.h
用  途: 通信基类
日  期: 2017.04.08
版  本: 1.0
编  制: 金 健
---------------------------------------------------*/

#pragma once

#include "stdafx.h"
#include "Buffer.h"

class TransData
{
public:
	virtual void SendData(char* src, int len) = 0;	
	virtual void Initial() = 0;
	void Set_pBuffer_recv(CBuffer* pBuffer);
	void Set_pBuffer_send(CBuffer* pBuffer);

public:
	CBuffer* m_pBuffer_recv;
	CBuffer* m_pBuffer_send;
};