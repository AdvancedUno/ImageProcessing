// MacaronCvDLL.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "MacaronCvDLL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CMacaronCvDLLApp

BEGIN_MESSAGE_MAP(CMacaronCvDLLApp, CWinApp)
END_MESSAGE_MAP()


// CMacaronCvDLLApp construction

CMacaronCvDLLApp::CMacaronCvDLLApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMacaronCvDLLApp object

CMacaronCvDLLApp theApp;


// CMacaronCvDLLApp √ ±‚»≠

BOOL CMacaronCvDLLApp::InitInstance()
{
	CWinApp::InitInstance();

	switch(CoInitialize(NULL))
	{
	case E_INVALIDARG:
	case E_OUTOFMEMORY:
	case E_UNEXPECTED:
		return FALSE;
	}

	AfxEnableControlContainer();

	m_pMainWnd = new CWnd();

	return TRUE;
}

int CMacaronCvDLLApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	delete m_pMainWnd;

	return CWinApp::ExitInstance();
}
