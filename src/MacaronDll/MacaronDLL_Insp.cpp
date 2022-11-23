#include "StdAfx.h"
#include "MacaronDLL.h"
#include "MacaronDLL_Insp.h"


#define M_DLL_NAME _T("MacaronDLL")


LPCTSTR SZ_TITLE_RESULT[CUserClass::eResult_Max] =
{
	_T("Capture1"),
	_T("Capture2"),
	_T("Capture3"),

};

LPCTSTR SZ_TITLE_OPTION[CUserClass::eOptionMax] =
{
	_T("_nDelay"),
	_T("_nDisplayWnd"),
	
};


CUserClass::CUserClass()
	:m_pOptionDlg(NULL)
{
}
CUserClass::~CUserClass()
{
	
}

void CUserClass::UpdateUIOption()
{
	if (m_VectorOption.size() <= 0)
		return;

	for (int nindex = 0; nindex < CUserClass::eOptionMax; nindex++)
	{
		switch (nindex)
		{
		case CUserClass::eOption_nDelay:
			m_pUser->m_pOptionDlg->m_Options._nDelay = m_VectorOption[nindex].dOptionValue;
			break;

		case CUserClass::eOption_nDisplayWnd:

			m_pOptionDlg->m_Options._nDisplayWnd = m_VectorOption[nindex].dOptionValue;
			break;

		default:
			break;
		}

	}
	m_pUser->m_pOptionDlg->UpdateData(FALSE);
}

void CUserClass::SampleCapture()
{
	 
	MbufCopy(m_pBase->m_pInspBuff->GetMilBufferID(), m_pBase->m_pDestBuff->GetMilBufferID());
}

//////////////////////////////////////////검사 시퀀스 처리 부분 //////////////////////////////////////////////////////////////////////




BOOL PreMeasure()
{
	BOOL bResult = TRUE;

	// TODO: Add your specialized code here to prepare measure

	m_pBase->Wait(m_pUser->m_pOptionDlg->m_Options._nDelay);


	return bResult;
}

BOOL Measure()
{
	// TODO : Add your specialized code here to measure this inspection


	m_pUser->SampleCapture();
	//m_pBase->m_pDestBuff->MilGetCopyFromOther(m_pBase->m_pInspBuff->GetMilBufferID()); // 원본이미지를 단순히 목적 버퍼에 넣는 샘플코드 



	return TRUE;
}

void PostMeasure()
{
	// TODO: Add your specialized code here after finishing measure and/or call the base class
	m_pBase->m_pDestBuff->MilCopyToDstBuffer(m_pBase->m_SrcBuffID);
}


int GetOptionCount()
{
	return CUserClass::eOptionMax;
}

void GetOption(int nIndex, LPCTSTR &OptionName, double &Val)
{
	if (m_pUser->m_VectorOption.size() <= 0) // 
		return;

	if (nIndex >= m_pUser->m_VectorOption.size()) // 
		return;

	if (nIndex < 0 ) // 
		return;

	m_pUser->m_pOptionDlg->UpdateData(TRUE);
	SaveOption();

	OptionName = m_pUser->m_VectorOption[nIndex].strOptionName;
	Val = m_pUser->m_VectorOption[nIndex].dOptionValue;
}

void SaveOption() // 다이얼로그 값을 저장 
{
	m_pUser->m_VectorOption.clear();

	for (int nindex = 0; nindex < CUserClass::eOptionMax; nindex++)
	{
		switch (nindex)
		{
		case CUserClass::eOption_nDelay:
			m_pUser->m_structOption.strOptionName = SZ_TITLE_OPTION[nindex];
			m_pUser->m_structOption.dOptionValue = m_pUser->m_pOptionDlg->m_Options._nDelay;
			break;

		case CUserClass::eOption_nDisplayWnd:
			m_pUser->m_structOption.strOptionName = SZ_TITLE_OPTION[nindex];
			m_pUser->m_structOption.dOptionValue = m_pUser->m_pOptionDlg->m_Options._nDisplayWnd;
			break;

		default:
			break;
		}
		m_pUser->m_VectorOption.push_back(m_pUser->m_structOption);
	}
}

void LoadOption(int nIndex, double Val)
{
	if (m_pUser->m_VectorOption.size() <= 0) // 파라메터 초기화 !!  저장된 값이 없으면 다이얼로그의 초기화 값으로 초기화 
	{
		SaveOption();
	}
	else
	{
		if (nIndex < 0 || nIndex >= m_pUser->m_VectorOption.size())
		{
			SaveOption();
		}
		else
		{
			m_pUser->m_VectorOption[nIndex].dOptionValue = Val;
		}
	}

	m_pUser->UpdateUIOption();

}





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////








//////////////////////////////////////////////////////// base 부분 여기는 절대 수정 하지 않는다 ////////////////////////////////////////


int LoadDll(void)
{
	m_pUser = new CUserClass();
	m_pBase = new CDLLbase();

	if (m_pUser->m_pOptionDlg == NULL)
	{
		m_pUser->m_pOptionDlg = new CDialogOptions;
	}

	SaveOption();

	return eIMGDLL_MATROX;
}
void CreateMyDialog(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
		
	if (m_pUser->m_pOptionDlg == NULL)
	{ 
		m_pUser->m_pOptionDlg = new CDialogOptions;
	}
		
}
void CloseAlgoDll()
{
	CloseMyDialog();
	
	delete m_pUser;
	delete m_pBase;
}

void CloseMyDialog(void)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());
	delete m_pUser->m_pOptionDlg;

}
void ShowOptionWnd(int nShow)
{

	if (m_pUser->m_pOptionDlg == NULL)
	{
		AfxMessageBox(_T("m_pOptionDlg == NULL"));
		return;
	}

	if (nShow == 1)
	{
		//AfxMessageBox(_T("m_pOptionDlg->ShowWindow(SW_SHOW);"));
		m_pUser->m_pOptionDlg->ShowWindow(SW_SHOW);
	}
	else
	{
		//AfxMessageBox(_T("m_pOptionDlg->ShowWindow(SW_HIDE);"));
		m_pUser->m_pOptionDlg->ShowWindow(SW_HIDE);
	}


}

LPCTSTR GetDllName()
{
	return M_DLL_NAME;
}


BOOL Initialize(BYTE* pImg, int nMilBuffID, int nMIlnAppID, int nMIlSystemID, CSize cSize, int nDepth, int nChannel)
{
	BOOL	bResult = TRUE;

	// TODO: Add your specialized code here to initialize
	m_pBase->m_dwStartTime = 0;
	m_pBase->m_dwEndTime = 0;
	m_pBase->m_dwElapsTime = 0;


	m_pBase->ImgBuffInit(pImg, nMilBuffID, nMIlnAppID, nMIlSystemID, cSize, nDepth, nChannel);
	
	
	return true;
}
CString Finalize()
{
	// TODO: Add your specialized code here to finalize and/or call the base class
	m_pBase->m_dwEndTime = GetTickCount();
	m_pBase->m_dwElapsTime = m_pBase->m_dwEndTime - m_pBase->m_dwStartTime;


	CString strResult = _T("TRUE");
	return strResult;
}

int GetElapsTimeMsec()
{
	return m_pBase->m_dwElapsTime;
}

void SetWndPos(CRect cReect)
{
	m_pUser->m_pOptionDlg->SetwndPos(cReect);
}



int GetResultCount()
{
	return CUserClass::eResult_Max;
}
LPCTSTR GetResultName(int nResultIndex)
{
	return SZ_TITLE_RESULT[nResultIndex];
}
BOOL	GetResultPass(int nResultIndex)
{
	return m_pBase->m_VectorResult[nResultIndex]._nPASS;
}
double GetResultValue(int nResultIndex)
{
	return m_pBase->m_VectorResult[nResultIndex]._dValue;
}
double GetResultUpperLimit(int nResultIndex)
{
	return m_pBase->m_VectorResult[nResultIndex]._dUpperLimit;
}
double GetResultLowerLimit(int nResultIndex)
{
	return m_pBase->m_VectorResult[nResultIndex]._dLowerLimit;
}

LPCTSTR GetReportHeaders()
{
	// TODO : Make report headers of this inspection and return that

	return _T(" ");
}

LPCTSTR GetReportLowerLimits()
{
	// TODO : Make report lower limits of this inspection and return that

	return _T(" ");
}

LPCTSTR GetReportUpperLimits()
{
	// TODO : Make report upper limits of this inspection and return that

	return _T(" ");
}

LPCTSTR GetReportContents()
{
	// TODO : Make report contents of this inspection and return that

	return _T(" ");
}





CDLLbase::CDLLbase()
	: m_pInspBuff(NULL)
	, m_pDestBuff(NULL)
	, m_pInitSys(NULL)
	, m_gByte(NULL)
{
	
	InitResultValue();
}
CDLLbase::~CDLLbase()
{
	m_VectorResult.clear();
	delete m_pInspBuff;
	m_pInspBuff = NULL;

	delete m_pDestBuff;
	m_pDestBuff = NULL;

	delete m_pInitSys;
	m_pInitSys = NULL;

	delete[]m_gByte;
}
void CDLLbase::ImgBuffInit(BYTE* pImg, int nMilBuffID, int nMIlnAppID, int nMIlSystemID, CSize cSize, int nDepth, int nChannel)
{


	m_pBase->m_dwStartTime = GetTickCount();

	m_pBase->m_pInspBuff->SetAppID(nMIlnAppID);

	m_pBase->m_pInspBuff->GetImageProperties(nMilBuffID, &m_pBase->pPorp);

	if (m_pBase->m_pInspBuff->GetAppID() < 0)
	{
		AfxMessageBox(_T("GetAppID NULL"));
	}
	else
	{
		if (m_pBase->m_pInspBuff->GetSystemID() < 0)
		{
			m_pBase->m_pInitSys = new cxImgBuff;
			m_pBase->m_pInspBuff = new  cxImgBuff;
			m_pBase->m_pDestBuff = new  cxImgBuff;

			m_pBase->m_pInitSys->InitSystem();

			CString strtemp = _T("");

			if (m_pBase->m_pInspBuff->GetMilBufferID() < 0)
			{
				m_pBase->m_SrcBuffID = nMilBuffID;
				m_pBase->m_gByte = new BYTE[m_pBase->pPorp._ImageSize.cx * m_pBase->pPorp._ImageSize.cy * (m_pBase->pPorp._nDepth / 8)];
			//	m_pBase->m_gByte = new BYTE[m_pBase->pPorp._ImageSize.cx * m_pBase->pPorp._ImageSize.cy];

				m_pBase->m_pInspBuff->MilCreateBuffer(GetDllName(), m_pBase->pPorp._ImageSize.cx, m_pBase->pPorp._ImageSize.cy, m_pBase->pPorp._nDepth, m_pBase->pPorp._nBandSize);
				m_pBase->m_pInspBuff->MilCreateDspBuffer(GetDllName());
				MdispControl(m_pBase->m_pInspBuff->GetMilDisplayID(), M_FILL_DISPLAY, M_ENABLE);	//디스플레이 화면에 맞춤

				m_pBase->m_pDestBuff->MilCreateBuffer(GetDllName(), m_pBase->pPorp._ImageSize.cx, m_pBase->pPorp._ImageSize.cy, m_pBase->pPorp._nDepth, m_pBase->pPorp._nBandSize);
				m_pBase->m_pDestBuff->MilCreateDspBuffer(GetDllName());
				MdispControl(m_pBase->m_pDestBuff->GetMilDisplayID(), M_FILL_DISPLAY, M_ENABLE);	//디스플레이 화면에 맞춤
			}

		}

		MbufGet2d(m_pBase->m_SrcBuffID, 0, 0, m_pBase->pPorp._ImageSize.cx, m_pBase->pPorp._ImageSize.cy, m_pBase->m_gByte); // Opnecv로도 사용하기위해.. BYTE 포인터로도 저장 
		m_pBase->m_pInspBuff->SetBytedataToMilBuff(m_pBase->m_gByte, m_pBase->pPorp._ImageSize.cy, m_pBase->pPorp._ImageSize.cx, m_pBase->pPorp._nBandSize); // 영상을 가져오기 메트록스 버퍼로  
		if (m_pUser->m_pOptionDlg->m_Options._nDisplayWnd)
		{
			//m_pInspBuff->MilSetNewWindowDisplay(m_pInspBuff->GetMilDisplayID(), m_pInspBuff->GetMilBufferID());
			m_pBase->m_pDestBuff->MilSetNewWindowDisplay(m_pBase->m_pDestBuff->GetMilDisplayID(), m_pBase->m_pInspBuff->GetMilBufferID());
		}
	}
}


void CDLLbase::InitResultValue()
{
	m_VectorResult.clear();

	for (int nResultIndex = 0; nResultIndex < CUserClass::eResult_Max; nResultIndex++)
	{
		m_structResult._strName = SZ_TITLE_RESULT[nResultIndex];
		m_structResult._nPASS = 1;
		m_structResult._dValue = 0;
		m_structResult._dUpperLimit = -9999999;
		m_structResult._dLowerLimit = +9999999;
		m_VectorResult.push_back(m_structResult);
	}

}

void CDLLbase::SetResult(int nReusltIndex, int nValue)
{
	if (nReusltIndex >= m_VectorResult.size())
		return;
	if (nReusltIndex < 0)
		return;

	m_VectorResult[nReusltIndex]._nPASS = nValue;
}
void CDLLbase::SetResult(int nReusltIndex, double dValue)
{
	if (nReusltIndex >= m_VectorResult.size())
		return;
	if (nReusltIndex < 0)
		return;

	m_VectorResult[nReusltIndex]._dValue = dValue;
}

void CDLLbase::SetUpperLimit(int nReusltIndex, double dLimit)
{
	if (nReusltIndex >= m_VectorResult.size())
		return;
	if (nReusltIndex < 0)
		return;

	m_VectorResult[nReusltIndex]._dUpperLimit = dLimit;
}
void CDLLbase::SetLowerLimit(int nReusltIndex, double dLimit)
{
	if (nReusltIndex >= m_VectorResult.size())
		return;
	if (nReusltIndex < 0)
		return;

	m_VectorResult[nReusltIndex]._dLowerLimit = dLimit;
}

void CDLLbase::Wait(DWORD dwMillisecond)
{
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount();

	while (GetTickCount() - dwStart < dwMillisecond)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}


