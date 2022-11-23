#pragma once

#include <Math.h>
#ifdef _DEBUG 
#pragma comment(lib, "opencv_world451d.lib")
#else 
#pragma comment(lib, "opencv_world451.lib")
#endif


#include "../../../xcInclude/xcImgProc/opencv/opencv2/opencv.hpp" 
#include "../../../xcInclude/xcImgProc/opencv/opencv2/core/types_c.h"
#include "../../../xcInclude/xcImgProc/opencv/opencv2/core/core_c.h"
#include "../../../xcInclude/xcImgProc/opencv/opencv2/imgproc/imgproc_c.h"

#include <opencv2\highgui\highgui.hpp>

#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudaarithm.hpp>
#include <algorithm>
#include<iterator>
#include <io.h>
#include<opencv2/cudafilters.hpp>
#include<opencv2/cudafeatures2d.hpp>
#include <string>
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/opencv.hpp>
#include "Macaron.h"

#ifdef CREATEDLL_EXPORTS
#define INSPDLL_DECLSPEC __declspec(dllexport)
#else
#define INSPDLL_DECLSPEC __declspec(dllimport)
#endif
#include "DialogOptions.h"


class CUserClass // ������ �����ϴ� �Լ��� ������ �ڵ��� �ϴ� �κ�
{
public:
	CUserClass();
	~CUserClass();

public:

	int nImageType;

	CDialogOptions* m_pOptionDlg;

	enum RESULT
	{
		eResult_Capture1,
		eResult_Capture2,
		eResult_Capture3,
		eResult_Max,
	};



	enum
	{
		eOption_nUseGPU,
		eOption_nClaheOnly,
		eOption_nClaheGamma,
		eOption_nGammaOnly,
		eOption_nHisEQOnly,
		eOption_nClaheHisEQ,
		eOption_nGammaValue,
		eOption_nSharpening,
		eOption_nShowGraph,
		eOption_nSharpeningFactor,
		eOption_nSizeFactor,
		eOption_nLimitFactor,
		eOption_nGridSize,
		eOptionMax,
	};
	struct OPTION_VAL
	{
		LPCTSTR strOptionName;
		double	dOptionValue;
	}m_structOption;

	std::vector<OPTION_VAL> m_VectorOption;

	void UpdateUIOption();


public: //// ������ �����ϴ� �˰���� 

	void SampleCapture();
	
};




/////// ������������������� ���ϴ� ���� �ǵ帮�� ���� �������������////////////
extern "C" {

	class 	CUserClass;
	class 	CDLLbase;
	
	
			
	CDLLbase *m_pBase;
	CUserClass* m_pUser;
	
	enum IMGDLL_TYPE
	{
		eIMGDLL_OPENCV,
		eIMGDLL_MATROX,
	};

	INSPDLL_DECLSPEC int LoadDll();
	INSPDLL_DECLSPEC void CreateMyDialog();
	INSPDLL_DECLSPEC void CloseMyDialog();
	INSPDLL_DECLSPEC void CloseAlgoDll();
	INSPDLL_DECLSPEC void ShowOptionWnd(int nShow);
	INSPDLL_DECLSPEC LPCTSTR GetDllName(void);
	INSPDLL_DECLSPEC void	SetWndPos(CRect cReect);
	/// ui �� ��Ÿ �κ� ///////////////////////////



	///�˻� ������ �κ�

	INSPDLL_DECLSPEC BOOL	Initialize(BYTE* pImg, int nMilBuffID, int nMIlnAppID, int nMIlSystemID, CSize cSize, int nDepth, int nChannel);
	INSPDLL_DECLSPEC BOOL	PreMeasure();
	INSPDLL_DECLSPEC BOOL	Measure();
	INSPDLL_DECLSPEC void	PostMeasure();
	INSPDLL_DECLSPEC CString	Finalize();
	INSPDLL_DECLSPEC int	GetElapsTimeMsec();
	INSPDLL_DECLSPEC cv::Mat GetResultCvImg();
	
	///�˻� ��� ������ �κ� 
	
	INSPDLL_DECLSPEC int GetResultCount();
	INSPDLL_DECLSPEC LPCTSTR GetResultName(int nResultIndex);
	INSPDLL_DECLSPEC BOOL	GetResultPass( int nResultIndex);
	INSPDLL_DECLSPEC double GetResultValue(int nResultIndex);
	INSPDLL_DECLSPEC double GetResultUpperLimit(int nResultIndex);
	INSPDLL_DECLSPEC double GetResultLowerLimit(int nResultIndex);

	// �ɼ� ���� �� �ҷ����� ��� 

	INSPDLL_DECLSPEC int GetOptionCount();
	INSPDLL_DECLSPEC void GetOption(int nIndex,LPCTSTR &OptionName, double &Val);
	INSPDLL_DECLSPEC void SaveOption();
	INSPDLL_DECLSPEC void LoadOption(int nIndex, double Val);
	
}


class CDLLbase
{
public:
	CDLLbase();
	~CDLLbase();


	void ImgBuffInit(BYTE* pImg, int nMilBuffID, int nMIlnAppID, int nMIlSystemID, CSize cSize, int nDepth, int nChannel);

	BYTE* m_gByte;

	cv::Mat m_MainBuff;



	cv::Mat m_DestBuff;

	cv::String		SetCvString(CString str);

	DWORD m_dwStartTime = 0;
	DWORD m_dwEndTime = 0;
	DWORD m_dwElapsTime = 0;

	struct RESULTVAL
	{
		LPCTSTR _strName;
		int _nPASS;
		double _dValue;
		double _dUpperLimit;
		double _dLowerLimit;
	}m_structResult;

	std::vector<RESULTVAL> m_VectorResult;


	

	void InitResultValue();

	void SetResult(int nReusltIndex, int nValue);
	void SetResult(int nReusltIndex, double dValue);
	void SetUpperLimit(int nReusltIndex, double dLimit);
	void SetLowerLimit(int nReusltIndex, double dLimit);
	
	void Wait(DWORD dwMillisecond);

};