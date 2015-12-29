
// TheSolarSystemSimulator.h : main header file for the TheSolarSystemSimulator application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CTheSolarSystemSimulatorApp:
// See TheSolarSystemSimulator.cpp for the implementation of this class
//

class CTheSolarSystemSimulatorApp : public CWinAppEx
{
public:
	CTheSolarSystemSimulatorApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTheSolarSystemSimulatorApp theApp;
