#pragma once

#include "../../xcSys/xcBase/xcImgProc/xcImgeBuffer.h"

#include <string>
#include <iostream>

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
		eOption_nDelay,
		eOption_nDisplayWnd,
		eOptionMax,
	};
	struct OPTION_VAL
	{
		LPCTSTR strOptionName;
		double	dOptionValue;
	}m_structOption;

	std::vector<OPTION_VAL> m_VectorOption;

	void UpdateUIOption();


public: //// ������ �����ϴ� �˰��� 

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


	int m_SrcBuffID = -1;
	BYTE* m_gByte;
	cxImgBuff* m_pInitSys;
	cxImgBuff* m_pInspBuff;
	cxImgBuff* m_pDestBuff;
	cxImgBuff::tImageProperties pPorp;

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