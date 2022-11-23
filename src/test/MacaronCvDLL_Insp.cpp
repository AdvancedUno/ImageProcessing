#include "StdAfx.h"
#include "MacaronCvDLL.h"
#include "MacaronCvDLL_Insp.h"


#include <cstring>

#define M_DLL_NAME _T("MacaronCvDLL")


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
	_T("_nClaheOnly"),
	_T("_nClaheGamma"),
	_T("_nGammaOnly"),
	_T("_nHisEQOnly"),
	_T("_nClaheHisEQ"),

	
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
		case CUserClass::eOption_nDelay:
			//m_pUser->m_pOptionDlg->m_Options._nDelay = m_VectorOption[nindex].dOptionValue;
			break;

		case CUserClass::eOption_nDisplayWnd:

			m_pOptionDlg->m_Options._nDisplayWnd = m_VectorOption[nindex].dOptionValue;
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
		default:
			break;
		}

	}
	m_pUser->m_pOptionDlg->UpdateData(FALSE);
}

void CUserClass::SampleCapture()
{
	//m_pBase->Wait(m_pUser->m_pOptionDlg->m_Options._nDelay);

	cv::Mat& src = m_pBase->m_MainBuff;
	cv::Mat dest, temp;

	bool useCpu = m_pUser->m_pOptionDlg->m_Options._nUseGpu == 0 ? true : false;
	bool useClaheGamma = m_pUser->m_pOptionDlg->m_Options._nClaheGamma == 1 ? true : false;
	bool useClaheOnly = m_pUser->m_pOptionDlg->m_Options._nClaheOnly == 1 ? true : false;
	bool useClaheHisEQ = m_pUser->m_pOptionDlg->m_Options._nClaheHisEQ == 1 ? true : false;
	bool useGammaOnly = m_pUser->m_pOptionDlg->m_Options._nGammaOnly == 1 ? true : false;
	bool useHisEQOnly = m_pUser->m_pOptionDlg->m_Options._nHisEQOnly == 1 ? true : false;


	if (useCpu && useClaheGamma)
		temp = claheGammaCPU(src, 1.0);
	else if (!useCpu && useClaheGamma)
		claheGammaGPU(src, 2.0);
	if (useCpu && useClaheOnly)
		temp = claheCPU(src);
	else if (!useCpu && useClaheOnly)
		temp = claheGPU(src);

	if (useCpu && useClaheHisEQ)
		temp = claheHiseqCPU(src);
	else if (!useCpu && useClaheHisEQ)
		temp = claheHiseqGPU(src);

	if (useCpu && useGammaOnly)
		temp = gammaCPU(src,1.1);
	else if (!useCpu && useGammaOnly)
		temp = gammaGPU(src,1.1);

	if (useCpu && useHisEQOnly)
		temp = hisEQCPU(src);
	else if (!useCpu && useHisEQOnly)
		temp = hisEQGPU(src);

	//cv::imwrite("C:/Users/sales/source/repos/exe_dll_TEST/result111.bmp", temp);


	
	if (nImageType > -1)
	{
		//nImageType = src.type();
		//temp.convertTo(dest, CV_8UC1);
	}

	m_pBase->m_DestBuff = src;

	//dest.release();
	//temp.release();

	src.release();
}

//cv::Mat CUserClass::claheGammaGPU(cv::Mat img) {
//	
//
//	cv::cuda::GpuMat imgGpu(img);
//
//
//	float invGamma = 2.1;
//
//	cv::Mat table(1, 256, CV_8U);
//	uchar* p = table.ptr();
//
//
//	//#pragma omp parallel for num_threads(4)
//	for (int i = 0; i < 256; i++) {
//		p[i] = (pow((i / 255.0), 1.0 / invGamma) * 255.0);
//	}
//
//
//
//
//	cv::Ptr<cv::cuda::LookUpTable>temp;
//	temp = cv::cuda::createLookUpTable(table);
//
//	//temp->transform(imgGpu, imgGpu);
//
//
//
//
//	std::vector<cv::cuda::GpuMat> lab_planes(3);
//	cv::cuda::split(imgGpu, lab_planes);
//
//	cv::Ptr<cv::cuda::CLAHE> clahe = cv::cuda::createCLAHE();
//	clahe->setClipLimit(4);
//
//
//	clahe->apply(imgGpu, imgGpu);
//
//
//
//	imgGpu.download(img);
//
//	return img.clone();
//
//}
//
//
//cv::Mat CUserClass::claheGammaCPU(cv::Mat img) {
//
//	float invGamma = 2.2;
//
//	cv::Mat table(1, 256, CV_8U);
//	uchar* p = table.ptr();
//	for (int i = 0; i < 256; i++) {
//		p[i] = (pow((i / 255.0), 1 / invGamma) * 255);
//	}
//	LUT(img, table, img);
//
//	cv::cvtColor(img, img, cv::COLOR_GRAY2BGR);
//	cv::cvtColor(img, img, cv::COLOR_BGR2Lab);
//
//	std::vector<cv::Mat> lab_planes(3);
//	cv::split(img, lab_planes);
//
//	cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
//	clahe->setClipLimit(4);
//	cv::Mat dst;
//	clahe->apply(lab_planes[0], dst);
//
//	dst.copyTo(lab_planes[0]);
//	cv::merge(lab_planes, img);
//	cv::cvtColor(img, img, cv::COLOR_Lab2BGR);
//	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
//
//	return img.clone();
//}
//
//
//cv::Mat CUserClass::claheNGPU(cv::Mat img) {
//
//	bool bCheckType = 0;
//	bool bCheckChannel = 0;
//
//	//Gpu로 업로드 및 Gpu 객체 생성
//	cv::cuda::GpuMat imgGpu(img);
//
//	//들어온 이미지가 8 bit 이미지인지 확인 및 변경
//	if (imgGpu.type() != CV_8UC1 & imgGpu.type() != CV_8UC3) {
//		//imgGpu.convertTo(imgGpu, CV_8U);
//		//bCheckType = true;
//	}
//
//	//들어온 이미지가 1 channel 이미지인지 확인 및 변경
//	if (imgGpu.channels() > 1) {
//		cv::cuda::cvtColor(imgGpu, imgGpu, cv::COLOR_BGR2GRAY);
//		bCheckChannel = true;
//	}
//
//	//CLAHE 적용
//	//std::vector<cv::cuda::GpuMat> lab_planes(3);
//	//cv::cuda::split(imgGpu, lab_planes);
//	cv::Ptr<cv::cuda::CLAHE> clahe = cv::cuda::createCLAHE();
//	clahe->setClipLimit(4); //Set Threshold value
//	clahe->apply(imgGpu, imgGpu);
//
//	//이미지 기존 bit로 변환
//	if (bCheckType) {
//		//imgGpu.convertTo(imgGpu, CV_16UC1);
//	}
//
//	//이미지 기존 chanenl로 변환
//	if (bCheckChannel) {
//		cv::cuda::cvtColor(imgGpu, imgGpu, cv::COLOR_GRAY2BGR);
//	}
//
//	//이미지 다운로드
//	imgGpu.download(img);
//
//
//
//	return img.clone();
//
//
//}

//cv::Mat CUserClass::claheCPU(cv::Mat img) {
//
//	cv::cvtColor(img, img, cv::COLOR_GRAY2BGR);
//	cv::cvtColor(img, img, cv::COLOR_BGR2Lab);
//
//	std::vector<cv::Mat> lab_planes(3);
//	cv::split(img, lab_planes);
//
//	cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
//	clahe->setClipLimit(4);
//	cv::Mat dst;
//	clahe->apply(lab_planes[0], dst);
//
//	dst.copyTo(lab_planes[0]);
//	cv::merge(lab_planes, img);
//	cv::cvtColor(img, img, cv::COLOR_Lab2BGR);
//	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
//
//	return img.clone();
//}
//
//
//
//cv::Mat CUserClass::claheHiseqGPU(cv::Mat img) {
//
//	cv::cuda::GpuMat imgGpu(img);
//
//	//cuda::calcHist(imgGpu,mask,imgGpu);
//	cv::cuda::equalizeHist(imgGpu, imgGpu);
//
//	std::vector<cv::cuda::GpuMat> lab_planes(3);
//	cv::cuda::split(imgGpu, lab_planes);
//
//	cv::Ptr<cv::cuda::CLAHE> clahe = cv::cuda::createCLAHE();
//	clahe->setClipLimit(4);
//
//	clahe->apply(imgGpu, imgGpu);
//
//	imgGpu.download(img);
//	return img.clone();
//}
//
//
//cv::Mat CUserClass::claheHiseqCPU(cv::Mat img) {
//
//
//	cv::cvtColor(img, img, cv::COLOR_GRAY2BGR);
//	cv::cvtColor(img, img, cv::COLOR_BGR2Lab);
//
//	std::vector<cv::Mat> lab_planes(3);
//	cv::split(img, lab_planes);
//
//	cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
//	clahe->setClipLimit(4);
//	cv::Mat dst;
//	clahe->apply(lab_planes[0], dst);
//
//	dst.copyTo(lab_planes[0]);
//	cv::merge(lab_planes, img);
//	cv::cvtColor(img, img, cv::COLOR_Lab2BGR);
//	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
//
//	cv::equalizeHist(img, img);
//	return img.clone();
//
//}
//
//
//
//cv::Mat CUserClass::gammaGPU(cv::Mat img)
//{
//
//	cv::cuda::GpuMat imgGpu(img);
//
//	float invGamma = 2.1;
//
//
//	cv::Mat table(1, 256, CV_8U);
//	uchar* p = table.ptr();
//
//	#pragma omp parallel for num_threads(4)
//	for (int i = 0; i < 256; i++) {
//		p[i] = (pow((i / 255.0), 1.0 / invGamma) * 255.0);
//	}
//
//	cv::Ptr<cv::cuda::LookUpTable> temp = cv::cuda::createLookUpTable(table);
//
//	temp->transform(imgGpu, imgGpu);
//
//	imgGpu.download(img);
//	return img.clone();
//
//}
//cv::Mat CUserClass::gammaCPU(cv::Mat img)
//{
//	float invGamma = 2.2;
//
//	cv::Mat table(1, 256, CV_8U);
//	uchar* p = table.ptr();
//	for (int i = 0; i < 256; i++) {
//		p[i] = (pow((i / 255.0), 1 / invGamma) * 255);
//	}
//	cv::LUT(img, table, img);
//
//	return img.clone();
//
//}
//
//
//cv::Mat CUserClass::hisEQGPU(cv::Mat& img) {
//
//	cv::cuda::GpuMat imgGpu, imgGpuGray;
//
//	imgGpu.upload(img);
//
//	cv::cuda::GpuMat hist_equalized_image;
//
//	cv::cuda::cvtColor(imgGpu, hist_equalized_image, cv::COLOR_GRAY2BGR);
//	cv::cuda::cvtColor(hist_equalized_image, hist_equalized_image, cv::COLOR_BGR2YCrCb);
//
//	std::vector<cv::cuda::GpuMat> vec_channels;
//	cv::cuda::split(hist_equalized_image, vec_channels);
//
//	cv::cuda::equalizeHist(vec_channels[0], vec_channels[0]);
//
//	cv::cuda::merge(vec_channels, hist_equalized_image);
//
//	cv::cuda::cvtColor(hist_equalized_image, hist_equalized_image, cv::COLOR_YCrCb2BGR);
//	cv::cuda::cvtColor(hist_equalized_image, hist_equalized_image, cv::COLOR_BGR2GRAY);
//
//	hist_equalized_image.download(img);
//
//	return img.clone();
//
//}
//
//cv::Mat CUserClass::hisEQCPU(cv::Mat& img) {
//
//	cv::Mat hist_equalized_image;
//	cv::cvtColor(img, img, cv::COLOR_BGR2YCrCb);
//
//	std::vector<cv::Mat> vec_channels;
//	cv::split(img, vec_channels);
//
//	cv::equalizeHist(vec_channels[0], vec_channels[0]);
//
//	cv::merge(vec_channels, img);
//
//	cv::cvtColor(img, img, cv::COLOR_YCrCb2BGR);
//
//	return img.clone();
//
//}
//
//
//


//////////////////////////////////////////검사 시퀀스 처리 부분 //////////////////////////////////////////////////////////////////////








BOOL PreMeasure()
{
	BOOL bResult = TRUE;


	// TODO: Add your specialized code here to prepare measure
	m_pUser->SampleCapture();
	//m_pBase->Wait(m_pUser->m_pOptionDlg->m_Options._nDelay);

	

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

void SaveOption() // 다이얼로그 값을 저장 
{
	m_pUser->m_VectorOption.clear();

	for (int nindex = 0; nindex < CUserClass::eOptionMax; nindex++)
	{
		switch (nindex)
		{
		case CUserClass::eOption_nDelay:
			//m_pUser->m_structOption.strOptionName = SZ_TITLE_OPTION[nindex];
			//m_pUser->m_structOption.dOptionValue = m_pUser->m_pOptionDlg->m_Options._nDelay;
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
		AfxMessageBox(_T("m_pOptionDlg->ShowWindow(SW_SHOW);"));
		m_pUser->m_pOptionDlg->ShowWindow(SW_SHOW);
	}
	else
	{
		AfxMessageBox(_T("m_pOptionDlg->ShowWindow(SW_HIDE);"));
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


	m_pBase->m_dwStartTime = GetTickCount();

	
	if (nDepth == 8 && nChannel == 1) {
		cv::Mat Img_Destination8Bit_Gray(2944, 2352, CV_8UC1);
		Img_Destination8Bit_Gray.data = reinterpret_cast<uchar*>(pImg);
		m_pBase->m_MainBuff = Img_Destination8Bit_Gray; // 버퍼가 정의되었으니 이미지만 가져온다. 
	}
	else if (nDepth == 8 && nChannel == 3) {
		m_pBase->m_MainBuff = cv::Mat(cSize.cy, cSize.cx, CV_8UC3, pImg).clone(); // 버퍼가 정의되었으니 이미지만 가져온다.
	} 
	else  if (nDepth == 16 && nChannel == 1) {
		//m_pBase->m_MainBuff = cv::Mat(cSize.cy, cSize.cx, CV_16UC1, pImg).clone(); // 버퍼가 정의되었으니 이미지만 가져온다. 
		cv::Mat Img_Source16Bit_Gray(2944, 2352, CV_16UC1);
		cv::Mat Img_Destination8Bit_Gray(2944, 2352, CV_8UC1);
		Img_Source16Bit_Gray.data = reinterpret_cast<uchar*>(pImg);
		double minVal, maxVal;
		cv::minMaxLoc(Img_Source16Bit_Gray, &minVal, &maxVal); //find minimum and maximum intensities
		Img_Source16Bit_Gray.convertTo(Img_Destination8Bit_Gray, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
		m_pBase->m_MainBuff = Img_Destination8Bit_Gray;
		
	}
	else  if (nDepth == 16 && nChannel == 3)
		m_pBase->m_MainBuff = cv::Mat(cSize.cy, cSize.cx, CV_16UC1, pImg).clone(); // 버퍼가 정의되었으니 이미지만 가져온다. 
	else
		m_pBase->m_MainBuff = cv::Mat(cSize.cy, cSize.cx, CV_8UC1, pImg).clone(); // 버퍼가 정의되었으니 이미지만 가져온다. 
	
	//m_pBase->m_dwStartTime = GetTickCount();
	
	
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

 // Matorx 전용이기 때문에 비어둔다. // Matrox 사용안함
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


