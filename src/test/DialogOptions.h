#pragma once


// CDialogOptions dialog


class CDialogOptions : public CDialog
{
	DECLARE_DYNAMIC(CDialogOptions)

public:
	CDialogOptions(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogOptions();

// Dialog Data
	enum { IDD = IDD_DIALOG_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual void PostNcDestroy();

	afx_msg LRESULT OnUpdateData(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	void OnEnaleOption();
	


public:
	void SetwndPos(CRect cRect);

public:
	struct OPTIONS
	{
		int _nDisplayWnd;
		int _nUseGpu =1;
		int _nClaheGamma = 1;
		int _nClaheOnly = 0;
		int _nGammaOnly = 0;
		int _nClaheHisEQ =0;
		int _nHisEQOnly = 0;

	}m_Options;

	
	
	afx_msg void OnBnClickedBtApply();
	//afx_msg void OnBnClickedCheckShowDspWind2();
	afx_msg void OnBnClickedCheckShowUseGpu();
	afx_msg void OnEnChangeEdtDelay();
	afx_msg void OnBnClickedCheckShowUseClahegamma();
	afx_msg void OnBnClickedCheckShowUseClahe();
	afx_msg void OnBnClickedCheckShowUseGamma();
	afx_msg void OnBnClickedCheckShowUseHiseq();
	afx_msg void OnBnClickedCheckShowUseClahehiseq();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
