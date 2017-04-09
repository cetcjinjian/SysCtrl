// SysCtrl.h : main header file for the SysCtrl application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CSysCtrlApp:
// See SysCtrl.cpp for the implementation of this class
//

class CSysCtrlApp : public CBCGPWinApp
{
public:
	CSysCtrlApp();

	// Override from CBCGPWorkspace
	virtual void PreLoadState ();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSysCtrlApp theApp;