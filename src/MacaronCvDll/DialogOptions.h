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
		int _nUseGpu =0;
		int _nClaheGamma = 0;
		int _nClaheOnly = 0;
		int _nGammaOnly = 0;
		int _nClaheHisEQ =0;
		int _nHisEQOnly = 0;
		int _nSharpening = 0;
		int _nConvertColor = 0;
		int _nDrawGraph = 0;
		double _nSizeFactor = 1.0;
		double _nGammaValue = 1.0;
		double _nSharpeningFactor = 1.0;
		double _nClipLimit = 3.0;
		int _nTilesGridSize = 5;
			
		bool _nCvt16 = 0;

	}m_Options;

	
	
	afx_msg void OnBnClickedBtApply();
	//afx_msg void OnBnClickedCheckShowDspWind2();
	afx_msg void OnBnClickedCheckShowUseGpu();
	//afx_msg void OnEnChangeEdtDelay();
	afx_msg void OnBnClickedCheckShowUseClahegamma();
	afx_msg void OnBnClickedCheckShowUseClahe();
	afx_msg void OnBnClickedCheckShowUseGamma();
	afx_msg void OnBnClickedCheckShowUseHiseq();
	afx_msg void OnBnClickedCheckShowUseClahehiseq();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEnChangeEditGammaValue();
	afx_msg void OnEnChangeEditSharpeningFactor();
	afx_msg void OnBnClickedCheckShowUseSharpening();
	afx_msg void OnBnClickedCheckShowUseConvertcolor();
	afx_msg void OnBnClickedCheckShowUseShowGraph();
	afx_msg void OnEnChangeEditGraphSizeFactor();

	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);


	CEdit m_edGAMMA;
	CSliderCtrl m_sldGAMMA;
	afx_msg void OnNMCustomdrawSliderGamma(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl m_sldGRAPH;
	CEdit m_edGRAPH;
	CSliderCtrl m_sldSHARP;
	CEdit m_edSHARP;

	afx_msg void OnNMCustomdrawSliderGraph(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawSliderSharp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedStaticGroupbox6();
	
	CSliderCtrl m_sldLIMIT;
	CSliderCtrl m_sldGRID;
	CEdit m_edLIMIT;
	CEdit m_edGRID;
	afx_msg void OnNMCustomdrawSliderGridSize(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeEditLimitFactor();
	afx_msg void OnEnChangeEditGridSize();
};
