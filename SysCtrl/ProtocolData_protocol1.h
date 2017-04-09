#pragma once
#include "stdafx.h"
#include "ProtocolData.h"


class ProtocolData_protocol1 : public ProtocolData
{
public:
	void show()
	{
		AfxMessageBox(L"协议一处理");
	}
};