#pragma once



/*---------------------------------------------------
文件名: Cmd.h
用  途: 命令基类
日  期: 2017.04.09
版  本: 1.0
编  制: 金 健
---------------------------------------------------*/

#include "stdafx.h"
#include <string>
class CCmd
{
public:
	//virtual std::string GetVersion() = 0;
	virtual int HandleData(unsigned char* ptr,int len ) = 0;
	virtual int MakeData(unsigned char* ptr, int len) = 0;
	virtual int GetLength() = 0;
	void show() { ; };
};