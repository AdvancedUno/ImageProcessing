// MacaronDLL.h : main header file for the MacaronDLL DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMacaronDLLApp
// See MacaronDLL.cpp for the implementation of this class
//

class CMacaronDLLApp : public CWinApp
{
public:
	CMacaronDLLApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};
