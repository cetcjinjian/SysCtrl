#pragma once


/*---------------------------------------------------
文件名: CmdData.h
用  途: 数据命令
日  期: 2017.04.09
版  本: 1.0
编  制: 金 健
---------------------------------------------------*/


#include "Cmd.h"
class CCmdData : public CCmd 
{
public:
	CCmdData();
	~CCmdData();
	int HandleData(unsigned char* ptr, int len) ;
	int MakeData(unsigned char* ptr, int len) ;
	int GetLength();
private:
	int data1;
	int data2;
	int data3;
	int m_length;
};