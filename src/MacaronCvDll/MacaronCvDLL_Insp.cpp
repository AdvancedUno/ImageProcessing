#include "StdAfx.h"
#include "MacaronCvDLL.h"
#include "MacaronCvDLL_Insp.h"
#include<opencv2/cudaimgproc.hpp>
#include <opencv2/cudaarithm.hpp>
#include<opencv2/core.hpp> 
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/highgui.hpp> 
#include<opencv2/imgproc.hpp> 
#include <windows.h>
#include <iostream>
#include <opencv2/plot.hpp>
#include <thread>
#include <vector>

#include <cstring>

#define M_DLL_NAME _T("cvWINTELLIZ-X")


LPCTSTR SZ_TITLE_RESULT[CUserClass::eResult_Max] =
{
	_T("Capture1"),
	_T("Capture2"),
	_T("Capture3"),

};

LPCTSTR SZ_TITLE_OPTION[CUserClass::eOptionMax] =
{
	
	_T("_nUseGPU"),
	_T("_nClaheOnly"),
	_T("_nClaheGamma"),
	_T("_nGammaOnly"),
	_T("_nHisEQOnly"),
	_T("_nClaheHisEQ"),
	_T("_nGammaFactor"),
	_T("_nSharpening"),
	_T("_nDrawGraph"),
	_T("_nSharpeningFactor"),
	_T("_nSizeFactor"),


	
};


CUserClass::CUserClass()
	:m_pOptionDlg(NULL), nImageType(-1)
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
		case CUserClass::eOption_nUseGPU:

			m_pOptionDlg->m_Options._nUseGpu = m_VectorOption[nindex].dOptionValue;
			break;
		case CUserClass::eOption_nClaheOnly:

			m_pOptionDlg->m_Options._nClaheOnly = m_VectorOption[nindex].dOptionValue;
			break;
		case CUserClass::eOption_nClaheGamma:

			m_pOptionDlg->m_Options._nClaheGamma = m_VectorOption[nindex].dOptionValue;
			break;
		case CUserClass::eOption_nGammaOnly:

			m_pOptionDlg->m_Options._nGammaOnly = m_VectorOption[nindex].dOptionValue;
			break;
		case CUserClass::eOption_nClaheHisEQ:

			m_pOptionDlg->m_Options._nClaheHisEQ = m_VectorOption[nindex].dOptionValue;
			break;
		case CUserClass::eOption_nHisEQOnly:

			m_pOptionDlg->m_Options._nHisEQOnly = m_VectorOption[nindex].dOptionValue;
			break;
		case CUserClass::eOption_nGammaValue:

			m_pOptionDlg->m_Options._nGammaValue = m_VectorOption[nindex].dOptionValue;
			break;
		case CUserClass::eOption_nSharpening:

			m_pOptionDlg->m_Options._nSharpening = m_VectorOption[nindex].dOptionValue;
			break;
		case CUserClass::eOption_nShowGraph:

			m_pOptionDlg->m_Options._nDrawGraph = m_VectorOption[nindex].dOptionValue;
			break;
		case CUserClass::eOption_nSharpeningFactor:

			m_pOptionDlg->m_Options._nSharpeningFactor = m_VectorOption[nindex].dOptionValue;
			break;
		case CUserClass::eOption_nSizeFactor:

			m_pOptionDlg->m_Options._nSizeFactor = m_VectorOption[nindex].dOptionValue;
			break;
		case CUserClass::eOption_nLimitFactor:

			m_pOptionDlg->m_Options._nClipLimit = m_VectorOption[nindex].dOptionValue;
			break;
		case CUserClass::eOption_nGridSize:

			m_pOptionDlg->m_Options._nTilesGridSize = m_VectorOption[nindex].dOptionValue;
			break;
		default:
			break;
		}

	}
	m_pUser->m_pOptionDlg->UpdateData(FALSE);
}

void CUserClass::SampleCapture()
{
	//m_pBase->Wait(m_pUser->m_pOptionDlg->m_Options._nDelay);

	

	cv::Mat& src = m_pBase->m_MainBuff; double minVal, maxVal; std::bitset<9> mode;



	

	bool bUseCpu = m_pUser->m_pOptionDlg->m_Options._nUseGpu == 0 ? true : false;
	bool bUseClaheGamma = m_pUser->m_pOptionDlg->m_Options._nClaheGamma == 1 ? true : false;
	bool bUseClaheOnly = m_pUser->m_pOptionDlg->m_Options._nClaheOnly == 1 ? true : false;
	bool bUseClaheHisEQ = m_pUser->m_pOptionDlg->m_Options._nClaheHisEQ == 1 ? true : false;
	bool bUseGammaOnly = m_pUser->m_pOptionDlg->m_Options._nGammaOnly == 1 ? true : false;
	bool bUseHisEQOnly = m_pUser->m_pOptionDlg->m_Options._nHisEQOnly == 1 ? true : false;
	bool bUseSharpening = m_pUser->m_pOptionDlg->m_Options._nSharpening == 1 ? true : false;
	bool bUseConvertColor = m_pUser->m_pOptionDlg->m_Options._nConvertColor == 1 ? true : false;
	bool bUseDisplayGraph = m_pUser->m_pOptionDlg->m_Options._nDrawGraph == 1 ? true : false;

	

	mode.set(0, bUseCpu);mode.set(1,bUseClaheGamma);mode.set(2,bUseClaheOnly);mode.set(3, bUseClaheHisEQ);
	mode.set(4, bUseGammaOnly);mode.set(5, bUseHisEQOnly);mode.set(6, bUseSharpening);mode.set(7, bUseConvertColor);
	mode.set(8, bUseDisplayGraph);

	
	
	double dSizeFactor = m_pUser->m_pOptionDlg->m_Options._nSizeFactor;
	double dGammaValue = m_pUser->m_pOptionDlg->m_Options._nGammaValue;
	double dSharpeningFactor = m_pUser->m_pOptionDlg->m_Options._nSharpeningFactor;
	double dLimitFactor = m_pUser->m_pOptionDlg->m_Options._nClipLimit;
	int iGridSize = m_pUser->m_pOptionDlg->m_Options._nTilesGridSize;


	if (dLimitFactor < 1 || dLimitFactor > 300) {
		dLimitFactor = 40;
	}
	
	if (iGridSize < 1 || iGridSize > 100) {
		iGridSize = 10;
	}





	if (bUseDisplayGraph) {
		if (dSizeFactor < 1.0 || dSizeFactor > 10.0) {
			//AfxMessageBox(_T("Graph Size Factor Should be between 0.1 and 1"));
			dSizeFactor = 5.0;
		}
	}
	if (dGammaValue < 1.0 || dSizeFactor > 10.0) {
		//AfxMessageBox(_T("GAMMA Factor Should be between 1 and 10"));
		dGammaValue = 5.0;
	}
	if (bUseSharpening) {
		if (dSharpeningFactor < 1.0 || dSharpeningFactor > 10.0) {
			//AfxMessageBox(_T("Sharpening Factor Should be between 1 and 10"));
			dSharpeningFactor = 5.0;
		}
	}


	convert(src, mode, dSizeFactor/10, dGammaValue/3, 1.0+dSharpeningFactor/10, dLimitFactor/10, iGridSize);


	if (m_pUser->m_pOptionDlg->m_Options._nCvt16 != false) {
		cv::minMaxLoc(src, &minVal, &maxVal);
		src.convertTo(src, CV_16U, maxVal, 0);
	}



	m_pBase->m_DestBuff = src;

	src.release();
}



//////////////////////////////////////////�˻� ������ ó�� �κ� //////////////////////////////////////////////////////////////////////








BOOL PreMeasure()
{
	BOOL bResult = TRUE;


	// TODO: Add your specialized code here to prepare measure
	m_pUser->SampleCapture();
	

	

	return bResult;
}

BOOL Measure()
{
	// TODO : Add your specialized code here to measure this inspection


	return TRUE;
}

void PostMeasure()
{
	// TODO: Add your specialized code here after finishing measure and/or call the base class
	
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

void SaveOption() // ���̾�α� ���� ���� 
{
	m_pUser->m_VectorOption.clear();

	for (int nindex = 0; nindex < CUserClass::eOptionMax; nindex++)
	{
		switch (nindex)
		{

		case CUserClass::eOption_nUseGPU:
			m_pUser->m_structOption.strOptionName = SZ_TITLE_OPTION[nindex];
			m_pUser->m_structOption.dOptionValue = m_pUser->m_pOptionDlg->m_Options._nUseGpu;
			break;
		case CUserClass::eOption_nClaheOnly:
			m_pUser->m_structOption.strOptionName = SZ_TITLE_OPTION[nindex];
			m_pUser->m_structOption.dOptionValue = m_pUser->m_pOptionDlg->m_Options._nClaheOnly;
			break;
		case CUserClass::eOption_nClaheGamma:
			m_pUser->m_structOption.strOptionName = SZ_TITLE_OPTION[nindex];
			m_pUser->m_structOption.dOptionValue = m_pUser->m_pOptionDlg->m_Options._nClaheGamma;
			break;
		case CUserClass::eOption_nGammaOnly:
			m_pUser->m_structOption.strOptionName = SZ_TITLE_OPTION[nindex];
			m_pUser->m_structOption.dOptionValue = m_pUser->m_pOptionDlg->m_Options._nGammaOnly;
			break;
		case CUserClass::eOption_nHisEQOnly:
			m_pUser->m_structOption.strOptionName = SZ_TITLE_OPTION[nindex];
			m_pUser->m_structOption.dOptionValue = m_pUser->m_pOptionDlg->m_Options._nHisEQOnly;
			break;
		case CUserClass::eOption_nClaheHisEQ:
			m_pUser->m_structOption.strOptionName = SZ_TITLE_OPTION[nindex];
			m_pUser->m_structOption.dOptionValue = m_pUser->m_pOptionDlg->m_Options._nClaheHisEQ;
			break;
		case CUserClass::eOption_nGammaValue:
			m_pUser->m_structOption.strOptionName = SZ_TITLE_OPTION[nindex];
			m_pUser->m_structOption.dOptionValue = m_pUser->m_pOptionDlg->m_Options._nGammaValue;
			break;
		case CUserClass::eOption_nSharpening:
			m_pUser->m_structOption.strOptionName = SZ_TITLE_OPTION[nindex];
			m_pUser->m_structOption.dOptionValue = m_pUser->m_pOptionDlg->m_Options._nSharpening;
			break;
		case CUserClass::eOption_nShowGraph:
			m_pUser->m_structOption.strOptionName = SZ_TITLE_OPTION[nindex];
			m_pUser->m_structOption.dOptionValue = m_pUser->m_pOptionDlg->m_Options._nDrawGraph;
			break;
		case CUserClass::eOption_nSharpeningFactor:
			m_pUser->m_structOption.strOptionName = SZ_TITLE_OPTION[nindex];
			m_pUser->m_structOption.dOptionValue = m_pUser->m_pOptionDlg->m_Options._nSharpeningFactor;
			break;

		case CUserClass::eOption_nSizeFactor:
			m_pUser->m_structOption.strOptionName = SZ_TITLE_OPTION[nindex];
			m_pUser->m_structOption.dOptionValue = m_pUser->m_pOptionDlg->m_Options._nSizeFactor;
			break;
		case CUserClass::eOption_nLimitFactor:
			m_pUser->m_structOption.strOptionName = SZ_TITLE_OPTION[nindex];
			m_pUser->m_structOption.dOptionValue = m_pUser->m_pOptionDlg->m_Options._nClipLimit;
			break;
		case CUserClass::eOption_nGridSize:
			m_pUser->m_structOption.strOptionName = SZ_TITLE_OPTION[nindex];
			m_pUser->m_structOption.dOptionValue = m_pUser->m_pOptionDlg->m_Options._nTilesGridSize;
			break;
		default:
			break;
		}
		m_pUser->m_VectorOption.push_back(m_pUser->m_structOption);
	}
}

void LoadOption(int nIndex, double Val)
{
	if (m_pUser->m_VectorOption.size() <= 0) // �Ķ���� �ʱ�ȭ !!  ����� ���� ������ ���̾�α��� �ʱ�ȭ ������ �ʱ�ȭ 
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








//////////////////////////////////////////////////////// base �κ� ����� ���� ���� ���� �ʴ´� ////////////////////////////////////////


int LoadDll(void)
{
	
	m_pUser = new CUserClass();
	m_pBase = new CDLLbase();

	if (m_pUser->m_pOptionDlg == NULL)
	{
		m_pUser->m_pOptionDlg = new CDialogOptions;
	}

	SaveOption();
	
	return eIMGDLL_OPENCV;
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

	m_pBase->m_dwStartTime =  GetTickCount();

	
	
	if (nDepth == 8 && nChannel == 1) {
		cv::Mat Img_Destination8Bit_Gray(cSize.cy, cSize.cx, CV_8UC1);
		Img_Destination8Bit_Gray.data = reinterpret_cast<uchar*>(pImg);
		m_pBase->m_MainBuff = Img_Destination8Bit_Gray; // ���۰� ���ǵǾ����� �̹����� �����´�. 
	}
	else if (nDepth == 8 && nChannel == 3) {
		
		 // ���۰� ���ǵǾ����� �̹����� �����´�.
		cv::Mat Img_Destination8Bit_Gray(cSize.cy, cSize.cx, CV_8UC1);
		Img_Destination8Bit_Gray.data = reinterpret_cast<uchar*>(pImg);
		cv::cvtColor(Img_Destination8Bit_Gray, Img_Destination8Bit_Gray, CV_BGR2GRAY);
		m_pBase->m_MainBuff = Img_Destination8Bit_Gray;
	} 
	else  if (nDepth == 16 && nChannel == 1) {
		//m_pBase->m_MainBuff = cv::Mat(cSize.cy, cSize.cx, CV_16UC1, pImg).clone(); // ���۰� ���ǵǾ����� �̹����� �����´�. 
		cv::Mat Img_Source16Bit_Gray(cSize.cy, cSize.cx, CV_16UC1);
		cv::Mat Img_Destination8Bit_Gray(cSize.cy, cSize.cx, CV_8UC1);
		Img_Source16Bit_Gray.data = reinterpret_cast<uchar*>(pImg);
		double minVal, maxVal;
		cv::minMaxLoc(Img_Source16Bit_Gray, &minVal, &maxVal); 
		Img_Source16Bit_Gray.convertTo(Img_Destination8Bit_Gray, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
		m_pBase->m_MainBuff = Img_Destination8Bit_Gray;
		m_pUser->m_pOptionDlg->m_Options._nCvt16 = true;
		
		
	}
	else  if (nDepth == 16 && nChannel == 3) {
		cv::Mat Img_Source16Bit_Gray(cSize.cy, cSize.cx, CV_16UC3);double minVal, maxVal;
		cv::Mat Img_Destination8Bit_Gray(cSize.cy, cSize.cx, CV_8UC3);
		Img_Source16Bit_Gray.data = reinterpret_cast<uchar*>(pImg);
		cv::minMaxLoc(Img_Source16Bit_Gray, &minVal, &maxVal); 
		Img_Source16Bit_Gray.convertTo(Img_Destination8Bit_Gray, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
		cv::cvtColor(Img_Destination8Bit_Gray, Img_Destination8Bit_Gray, CV_BGR2GRAY);
		m_pBase->m_MainBuff = Img_Destination8Bit_Gray;
		m_pUser->m_pOptionDlg->m_Options._nCvt16 = true; // ���۰� ���ǵǾ����� �̹����� �����´�. 
	}
	else {
		cv::Mat Img_Destination8Bit_Gray(cSize.cy, cSize.cx, CV_8UC1);
		Img_Destination8Bit_Gray.data = reinterpret_cast<uchar*>(pImg);
		m_pBase->m_MainBuff = Img_Destination8Bit_Gray; // ���۰� ���ǵǾ����� �̹����� �����´�. 
	}


	
	
	return true;
}
CString Finalize()
{
	// TODO: Add your specialized code here to finalize and/or call the base class
	
	//m_pBase->m_dwEndTime = GetTickCount();
	m_pBase->m_dwElapsTime = GetTickCount() - m_pBase->m_dwStartTime;


	CString strResult = _T("TRUE");
	return strResult;
}

int GetElapsTimeMsec()
{
	return m_pBase->m_dwElapsTime;
}

cv::Mat GetResultCvImg()
{

	return m_pBase->m_DestBuff.clone();
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
	:m_gByte(NULL)
{
	
	InitResultValue();
}
CDLLbase::~CDLLbase()
{
	m_VectorResult.clear();

	m_DestBuff.release();
	m_MainBuff.release();

	cv::destroyAllWindows();

	delete[]m_gByte;
}
void CDLLbase::ImgBuffInit(BYTE* pImg, int nMilBuffID, int nMIlnAppID, int nMIlSystemID, CSize cSize, int nDepth, int nChannel)
{

 // Matorx �����̱� ������ ���д�. // Matrox ������
}



cv::String CDLLbase::SetCvString(CString str)
{
	USES_CONVERSION;
	std::string strMulti = CW2A(str);
	//std::string strMulti((LPCTSTR)str);
	//std::string strMulti = CW2A(str);

	return strMulti;
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


