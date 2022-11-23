// DialogOptions.cpp : implementation file
//

#include "stdafx.h"
#include "MacaronCvDLL.h"
#include "DialogOptions.h"



// CDialogOptions dialog

IMPLEMENT_DYNAMIC(CDialogOptions, CDialog)

CDialogOptions::CDialogOptions( CWnd* pParent /*=NULL*/)
: CDialog(CDialogOptions::IDD, pParent)
{
	//m_Options._nDelay = 0;
	//m_Options._nDisplayWnd = 0;
	m_Options._nUseGpu = 0;
	m_Options._nClaheGamma = 0;
	m_Options._nClaheOnly = 0;
	m_Options._nGammaOnly = 0;
	m_Options._nClaheHisEQ = 0; 
	m_Options._nHisEQOnly = 0;
	m_Options._nSharpening = 0;
	m_Options._nSharpeningFactor = 1.0;
	m_Options._nGammaValue = 1.0;
	m_Options._nConvertColor = 0;
	m_Options._nDrawGraph = 0;
	m_Options._nSizeFactor = 1.0;
	m_Options._nClipLimit = 3.0;
	m_Options._nTilesGridSize = 5;

	
	
	
	Create(IDD, pParent);
}

CDialogOptions::~CDialogOptions()
{
}

void CDialogOptions::DoDataExchange(CDataExchange* pDX)
{

	//DDX_Text(pDX, IDC_EDT_DELAY, m_Options._nDelay);
	//DDX_Check(pDX, IDC_CHECK_SHOW_DSP_WIND, m_Options._nDisplayWnd);
	DDX_Check(pDX, IDC_CHECK_SHOW_USE_GPU, m_Options._nUseGpu);
	DDX_Check(pDX, IDC_CHECK_SHOW_USE_CLAHEGAMMA, m_Options._nClaheGamma);
	DDX_Check(pDX, IDC_CHECK_SHOW_USE_CLAHE, m_Options._nClaheOnly);
	DDX_Check(pDX, IDC_CHECK_SHOW_USE_GAMMA, m_Options._nGammaOnly);
	DDX_Check(pDX, IDC_CHECK_SHOW_USE_CLAHEHISEQ, m_Options._nClaheHisEQ);
	DDX_Check(pDX, IDC_CHECK_SHOW_USE_HISEQ, m_Options._nHisEQOnly);
	DDX_Check(pDX, IDC_CHECK_SHOW_USE_SHARPENING, m_Options._nSharpening);
	DDX_Check(pDX, IDC_CHECK_SHOW_USE_CONVERTCOLOR, m_Options._nConvertColor);
	DDX_Check(pDX, IDC_CHECK_SHOW_USE_SHOW_GRAPH, m_Options._nDrawGraph);
	DDX_Text(pDX, IDC_EDIT_GAMMA_VALUE, m_Options._nGammaValue);
	DDX_Text(pDX, IDC_EDIT_SHARPENING_FACTOR, m_Options._nSharpeningFactor);
	DDX_Text(pDX, IDC_EDIT_GRAPH_SIZE_FACTOR, m_Options._nSizeFactor);
	DDX_Text(pDX, IDC_EDIT_LIMIT_FACTOR, m_Options._nClipLimit);
	DDX_Text(pDX, IDC_EDIT_GRID_SIZE, m_Options._nTilesGridSize);



	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_GAMMA, m_sldGAMMA);
	DDX_Control(pDX, IDC_EDIT_GAMMA_VALUE, m_edGAMMA);
	DDX_Control(pDX, IDC_SLIDER_GRAPH, m_sldGRAPH);
	DDX_Control(pDX, IDC_EDIT_GRAPH_SIZE_FACTOR, m_edGRAPH);
	DDX_Control(pDX, IDC_SLIDER_SHARP, m_sldSHARP);
	DDX_Control(pDX, IDC_EDIT_SHARPENING_FACTOR, m_edSHARP);
	DDX_Control(pDX, IDC_SLIDER_LIMIT_FACTOR, m_sldLIMIT);
	DDX_Control(pDX, IDC_SLIDER_GRID_SIZE, m_sldGRID);
	DDX_Control(pDX, IDC_EDIT_LIMIT_FACTOR, m_edLIMIT);
	DDX_Control(pDX, IDC_EDIT_GRID_SIZE, m_edGRID);


}


BEGIN_MESSAGE_MAP(CDialogOptions, CDialog)

	//ON_BN_CLICKED(IDC_CHECK_USE_RANDOM_DELAY,	&CDialogOptions::OnEnaleOption)
	ON_BN_CLICKED(IDC_BT_APPLY, &CDialogOptions::OnBnClickedBtApply)
	
	ON_BN_CLICKED(IDC_CHECK_SHOW_USE_GPU, &CDialogOptions::OnBnClickedCheckShowUseGpu)
	//ON_EN_CHANGE(IDC_EDT_DELAY, &CDialogOptions::OnEnChangeEdtDelay)
	ON_BN_CLICKED(IDC_CHECK_SHOW_USE_CLAHEGAMMA, &CDialogOptions::OnBnClickedCheckShowUseClahegamma)
	ON_BN_CLICKED(IDC_CHECK_SHOW_USE_CLAHE, &CDialogOptions::OnBnClickedCheckShowUseClahe)
	ON_BN_CLICKED(IDC_CHECK_SHOW_USE_GAMMA, &CDialogOptions::OnBnClickedCheckShowUseGamma)
	ON_BN_CLICKED(IDC_CHECK_SHOW_USE_HISEQ, &CDialogOptions::OnBnClickedCheckShowUseHiseq)
	ON_BN_CLICKED(IDC_CHECK_SHOW_USE_CLAHEHISEQ, &CDialogOptions::OnBnClickedCheckShowUseClahehiseq)
	ON_EN_CHANGE(IDC_EDIT_GAMMA_VALUE, &CDialogOptions::OnEnChangeEditGammaValue)
	ON_EN_CHANGE(IDC_EDIT_SHARPENING_FACTOR, &CDialogOptions::OnEnChangeEditSharpeningFactor)
	ON_BN_CLICKED(IDC_CHECK_SHOW_USE_SHARPENING, &CDialogOptions::OnBnClickedCheckShowUseSharpening)
	ON_BN_CLICKED(IDC_CHECK_SHOW_USE_CONVERTCOLOR, &CDialogOptions::OnBnClickedCheckShowUseConvertcolor)
	ON_BN_CLICKED(IDC_CHECK_SHOW_USE_SHOW_GRAPH, &CDialogOptions::OnBnClickedCheckShowUseShowGraph)
	ON_EN_CHANGE(IDC_EDIT_GRAPH_SIZE_FACTOR, &CDialogOptions::OnEnChangeEditGraphSizeFactor)
	ON_WM_ERASEBKGND()
	
	
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_GAMMA, &CDialogOptions::OnNMCustomdrawSliderGamma)
	ON_WM_HSCROLL()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_GRAPH, &CDialogOptions::OnNMCustomdrawSliderGraph)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SHARP, &CDialogOptions::OnNMCustomdrawSliderSharp)
	ON_BN_CLICKED(IDC_STATIC_GROUPBOX6, &CDialogOptions::OnBnClickedStaticGroupbox6)
	
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_GRID_SIZE, &CDialogOptions::OnNMCustomdrawSliderGridSize)
	ON_EN_CHANGE(IDC_EDIT_LIMIT_FACTOR, &CDialogOptions::OnEnChangeEditLimitFactor)
	ON_EN_CHANGE(IDC_EDIT_GRID_SIZE, &CDialogOptions::OnEnChangeEditGridSize)
END_MESSAGE_MAP()

// CDialogOptions message handlers

void CDialogOptions::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;

	CDialog::PostNcDestroy();
}

LRESULT CDialogOptions::OnUpdateData(WPARAM wParam, LPARAM lParam)
{
	BOOL	bSaveAndValidate = (BOOL) wParam;

	UpdateData(bSaveAndValidate);

	// TODO: Add your specialized code here
	if(bSaveAndValidate)
	{
	}
	else
	{
		OnEnaleOption();
	}

	return 0;
}

void CDialogOptions::OnEnaleOption()
{
	
	GetDlgItem(IDC_EDT_DELAY)				->EnableWindow(TRUE);

}
void CDialogOptions::SetwndPos(CRect cRect)
{
	MoveWindow(cRect, TRUE);
}


void CDialogOptions::OnBnClickedBtApply()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	UpdateData(true);
}



void CDialogOptions::OnBnClickedCheckShowUseGpu()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//m_Options._nUseGpu = 1;

	return;

}


//void CDialogOptions::OnEnChangeEdtDelay()
//{
//	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
//	// CDialog::OnInitDialog() �Լ��� ������ 
//	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
//	// �� �˸� �޽����� ������ �ʽ��ϴ�.
//
//	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
//}



void CDialogOptions::OnBnClickedCheckShowUseClahegamma()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//m_Options._nClaheGamma = 1;
	return;
}


void CDialogOptions::OnBnClickedCheckShowUseClahe()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//m_Options._nClaheOnly = 1;
	return;
}


void CDialogOptions::OnBnClickedCheckShowUseGamma()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//m_Options._nGammaOnly = 1;
	return;
}


void CDialogOptions::OnBnClickedCheckShowUseHiseq()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//m_Options._nHisEQOnly = 1;
	return;
}


void CDialogOptions::OnBnClickedCheckShowUseClahehiseq()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//m_Options._nClaheHisEQ = 1;
	return;
}

BOOL CDialogOptions::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CBrush backBrush(RGB(60, 60, 60));               // �Ķ���. ���ϴ� �÷��� ���ָ� �ȴ�...
	CBrush* pOldBrush = pDC->SelectObject(&backBrush);
	CRect rect; pDC->GetClipBox(&rect);
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);
	return TRUE;
}


void CDialogOptions::OnEnChangeEditGammaValue()
{

	CString sPos;
	m_edGAMMA.GetWindowText(sPos);
	int iPos = _ttoi(sPos);

	m_sldGAMMA.SetPos(iPos);

}


void CDialogOptions::OnEnChangeEditSharpeningFactor()
{
	
	CString sPos;
	
	m_edSHARP.GetWindowText(sPos);
	int iPos = _ttoi(sPos);

	m_sldSHARP.SetPos(iPos);


}


void CDialogOptions::OnBnClickedCheckShowUseSharpening()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//m_Options._nSharpening = 1;
	return;

}

void CDialogOptions::OnBnClickedCheckShowUseConvertcolor()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//m_Options._nConvertColor = 1;
	return;
}

void CDialogOptions::OnBnClickedCheckShowUseShowGraph()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//m_Options._nDrawGraph = 1;
	return;
}


void CDialogOptions::OnEnChangeEditGraphSizeFactor()
{
	CString sPos;
	m_edGRAPH.GetWindowText(sPos);
	int iPos = _ttoi(sPos);

	m_sldGRAPH.SetPos(iPos);

}

void CDialogOptions::OnEnChangeEditLimitFactor()
{
	CString sPos;
	m_edLIMIT.GetWindowText(sPos);
	int iPos = _ttoi(sPos);

	m_sldLIMIT.SetPos(iPos);
}


void CDialogOptions::OnEnChangeEditGridSize()
{
	CString sPos;
	m_edGRID.GetWindowText(sPos);
	int iPos = _ttoi(sPos);

	m_sldGRID.SetPos(iPos);
}







BOOL CDialogOptions::OnInitDialog()
{
	CDialog::OnInitDialog();

	//////////// WINTELLIZ-X ��ü �ʱ�ȭ �۾� ////////////
	//SetWindowTheme(GetDlgItem(IDC_STATIC)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_CHECK_SHOW_USE_GPU)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_CHECK_SHOW_USE_CLAHEGAMMA)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_CHECK_SHOW_USE_CLAHE)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_CHECK_SHOW_USE_GAMMA)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_CHECK_SHOW_USE_CLAHEHISEQ)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_CHECK_SHOW_USE_HISEQ)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_EDIT_GAMMA_VALUE)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_EDIT_SHARPENING_FACTOR)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_EDIT_GRID_SIZE)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_EDIT_LIMIT_FACTOR)->m_hWnd, _T(""), _T(""));

	SetWindowTheme(GetDlgItem(IDC_CHECK_SHOW_USE_SHARPENING)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_CHECK_SHOW_USE_CONVERTCOLOR)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_CHECK_SHOW_USE_SHOW_GRAPH)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_EDIT_GRAPH_SIZE_FACTOR)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STATIC)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STATIC_GROUPBOX1)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STATIC_GROUPBOX2)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STATIC_GROUPBOX3)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STATIC_GROUPBOX4)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STATIC_GROUPBOX5)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STATIC_GROUPBOX6)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STATIC_GROUPBOX7)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STATIC_GROUPBOX8)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_SLIDER_GAMMA)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_SLIDER_GRAPH)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_SLIDER_SHARP)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_SLIDER_GRID_SIZE)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_SLIDER_LIMIT_FACTOR)->m_hWnd, _T(""), _T(""));

	///////// GAMMA SLIDER///////////
	m_sldGAMMA.SetRange(1, 10);
	m_sldGAMMA.SetPos(5);
	m_sldGAMMA.SetLineSize(1);
	m_sldGAMMA.SetPageSize(1);

	int iPos = m_sldGAMMA.GetPos();
	CString sPos;
	sPos.Format(_T("%d"), iPos);
	m_edGAMMA.SetWindowText(sPos);


	///////// GRAPH SLIDER///////////
	m_sldGRAPH.SetRange(1, 10);
	m_sldGRAPH.SetPos(5);
	m_sldGRAPH.SetLineSize(1);
	m_sldGRAPH.SetPageSize(1);

	int iPosG = m_sldGRAPH.GetPos();
	CString sPosG;
	sPosG.Format(_T("%d"), iPosG);
	m_edGRAPH.SetWindowText(sPosG);



	///////// SHARP SLIDER///////////
	m_sldSHARP.SetRange(1, 10);
	m_sldSHARP.SetPos(5);
	m_sldSHARP.SetLineSize(1);
	m_sldSHARP.SetPageSize(1);

	int iPosS = m_sldSHARP.GetPos();
	CString sPosS;
	sPosS.Format(_T("%d"), iPosS);
	m_edSHARP.SetWindowText(sPosS);

	///////// GRID SIZE SLIDER///////////
	m_sldGRID.SetRange(1, 100);
	m_sldGRID.SetPos(10);
	m_sldGRID.SetLineSize(1);
	m_sldGRID.SetPageSize(1);

	int iPosGrid = m_sldGRID.GetPos();
	CString sPosGrid;
	sPosGrid.Format(_T("%d"), iPosGrid);
	m_edGRID.SetWindowText(sPosGrid);

	///////// LIMIT SLIDER///////////
	m_sldLIMIT.SetRange(0, 300);
	m_sldLIMIT.SetPos(40);
	m_sldLIMIT.SetLineSize(1);
	m_sldLIMIT.SetPageSize(1);

	int iPosLimit = m_sldLIMIT.GetPos();
	CString sPosLimit;
	sPosLimit.Format(_T("%d"), iPosLimit);
	m_edLIMIT.SetWindowText(sPosLimit);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}






HBRUSH CDialogOptions::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);


	if (pWnd->GetDlgCtrlID() == IDC_STATIC)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);

	}if (pWnd->GetDlgCtrlID() == IDC_CHECK_SHOW_USE_GPU)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	if (pWnd->GetDlgCtrlID() == IDC_CHECK_SHOW_USE_CLAHEGAMMA)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}if (pWnd->GetDlgCtrlID() == IDC_CHECK_SHOW_USE_CLAHE)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}if (pWnd->GetDlgCtrlID() == IDC_CHECK_SHOW_USE_GAMMA)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}if (pWnd->GetDlgCtrlID() == IDC_CHECK_SHOW_USE_CLAHEHISEQ)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}if (pWnd->GetDlgCtrlID() == IDC_CHECK_SHOW_USE_HISEQ)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}if (pWnd->GetDlgCtrlID() == IDC_EDIT_GAMMA_VALUE)
	{
		pDC->SetBkColor(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	}if (pWnd->GetDlgCtrlID() == IDC_EDIT_SHARPENING_FACTOR)
	{
		pDC->SetBkColor(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	}if (pWnd->GetDlgCtrlID() == IDC_CHECK_SHOW_USE_SHARPENING)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}if (pWnd->GetDlgCtrlID() == IDC_CHECK_SHOW_USE_CONVERTCOLOR)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}if (pWnd->GetDlgCtrlID() == IDC_CHECK_SHOW_USE_SHOW_GRAPH)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_GRAPH_SIZE_FACTOR)
	{
		pDC->SetBkColor(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_LIMIT_FACTOR)
	{
		pDC->SetBkColor(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_GRID_SIZE)
	{
		pDC->SetBkColor(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	}
	
	
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_GROUPBOX1)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	} if (pWnd->GetDlgCtrlID() == IDC_STATIC_GROUPBOX2)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	} if (pWnd->GetDlgCtrlID() == IDC_STATIC_GROUPBOX3)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	} if (pWnd->GetDlgCtrlID() == IDC_STATIC_GROUPBOX4)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	} if (pWnd->GetDlgCtrlID() == IDC_STATIC_GROUPBOX5)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_GROUPBOX6)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_GROUPBOX7)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_GROUPBOX8)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	if (pWnd->GetDlgCtrlID() == IDC_SLIDER_GAMMA)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	} 
	if (pWnd->GetDlgCtrlID() == IDC_SLIDER_GRAPH)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	} 
	if (pWnd->GetDlgCtrlID() == IDC_SLIDER_SHARP)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	} 
	if (pWnd->GetDlgCtrlID() == IDC_SLIDER_LIMIT_FACTOR)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	}
	if (pWnd->GetDlgCtrlID() == IDC_SLIDER_GRID_SIZE)
	{
		pDC->SetBkColor(RGB(60, 60, 60));
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	}
	
	

	return hbr;
}







void CDialogOptions::OnNMCustomdrawSliderGamma(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}


void CDialogOptions::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if (IDC_SLIDER_GAMMA == pScrollBar->GetDlgCtrlID()) {

		int iPos = m_sldGAMMA.GetPos();

		CString sPos;
		sPos.Format(_T("%d"), iPos);
		m_edGAMMA.SetWindowText(sPos);

	}else if (IDC_SLIDER_GRAPH == pScrollBar->GetDlgCtrlID()) {

		int temp = m_sldGRAPH.GetPos();
		int iPos = temp;

		CString sPos;
		
		sPos.Format(_T("%d"), iPos);
	
		

		m_edGRAPH.SetWindowText(sPos);

	}else if (IDC_SLIDER_SHARP == pScrollBar->GetDlgCtrlID()) {

		int iPos = m_sldSHARP.GetPos();

		CString sPos;
		sPos.Format(_T("%d"), iPos);


		m_edSHARP.SetWindowText(sPos);

	}
	else if (IDC_SLIDER_LIMIT_FACTOR == pScrollBar->GetDlgCtrlID()) {

		int iPos = m_sldLIMIT.GetPos();

		CString sPos;
		sPos.Format(_T("%d"), iPos);


		m_edLIMIT.SetWindowText(sPos);

	}
	else if (IDC_SLIDER_GRID_SIZE == pScrollBar->GetDlgCtrlID()) {

		int iPos = m_sldGRID.GetPos();

		CString sPos;
		sPos.Format(_T("%d"), iPos);


		m_edGRID.SetWindowText(sPos);

	}



	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDialogOptions::OnNMCustomdrawSliderGraph(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}


void CDialogOptions::OnNMCustomdrawSliderSharp(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}


void CDialogOptions::OnBnClickedStaticGroupbox6()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}








void CDialogOptions::OnNMCustomdrawSliderGridSize(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}



