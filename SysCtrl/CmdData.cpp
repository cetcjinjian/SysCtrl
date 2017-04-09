#include "stdafx.h"
#include "CmdData.h"


CCmdData::CCmdData()
{
	m_length = sizeof(data1) +
		sizeof(data2) +
		sizeof(data3);
}

CCmdData::~CCmdData()
{

}

int CCmdData::HandleData(unsigned char* ptr, int len)
{

	int begin = 1;
	memcpy(&data1, ptr + begin, 4);
	begin += 4;

	memcpy(&data2, ptr + begin, 4);
	begin += 4;

	memcpy(&data3, ptr + begin, 4);
	begin += 4;

	return begin;
}


int CCmdData::MakeData(unsigned char* ptr, int len)
{
	int begin = 0;
	memcpy(ptr + begin, &data1, 4);
	begin += 4;

	memcpy(ptr + begin, &data1, 4);
	begin += 4;

	memcpy(ptr + begin, &data1, 4);
	begin += 4;

	return begin;
}
int CCmdData::GetLength()
{
	return m_length;
}