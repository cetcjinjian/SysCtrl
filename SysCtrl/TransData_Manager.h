#pragma once
#include "stdafx.h"
#include "TransData.h"
#include "TransData_Com.h"
#include "TransData_Udp.h"
#include <map>

class TransData_Manager {

public:

	static TransData_Manager* GetInstance()
	{
		if (NULL == m_instance)
		{
			m_instance = new TransData_Manager();
		}			 
		return m_instance;		
	}

	void SetTrans(CString name, TransData *trans)
	{
		m_transmap[name] = trans;
	}
	void GetTrans(CString name, TransData *trans)
	{
		trans = m_transmap[name];
	}

private:
	static TransData_Manager* m_instance;
	std::map<CString, TransData* > m_transmap;
	TransData_Manager() {};
};

