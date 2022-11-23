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
		int _nDelay;



	}m_Options;

	
	
	afx_msg void OnBnClickedBtApply();

	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedCheckShowDspWind();
	afx_msg void OnEnChangeEdtDelay();
};
