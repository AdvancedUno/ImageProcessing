// MacaronCvDLL.h : main header file for the MacaronCvDLL DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMacaronCvDLLApp
// See MacaronCvDLL.cpp for the implementation of this class
//

class CMacaronCvDLLApp : public CWinApp
{
public:
	CMacaronCvDLLApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};
