#pragma once
#include "stdafx.h"
#include "ProtocolData.h"


class ProtocolData_protocol2 : public ProtocolData
{
public:
	void show()
	{
		AfxMessageBox(L"协议二处理");
	}
};