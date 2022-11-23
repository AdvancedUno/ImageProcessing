// DialogOptions.cpp : implementation file
//

#include "stdafx.h"
#include "MacaronDLL.h"
#include "DialogOptions.h"



// CDialogOptions dialog

IMPLEMENT_DYNAMIC(CDialogOptions, CDialog)

CDialogOptions::CDialogOptions( CWnd* pParent /*=NULL*/)
: CDialog(CDialogOptions::IDD, pParent)
{
	m_Options._nDelay = 0;
	m_Options._nDisplayWnd = 0;
	Create(IDD, pParent);
}

CDialogOptions::~CDialogOptions()
{
}

void CDialogOptions::DoDataExchange(CDataExchange* pDX)
{
	
	DDX_Text(pDX, IDC_EDT_DELAY, m_Options._nDelay);
	DDX_Check(pDX, IDC_CHECK_SHOW_DSP_WIND, m_Options._nDisplayWnd);
	
	
	
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogOptions, CDialog)

	ON_BN_CLICKED(IDC_CHECK_USE_RANDOM_DELAY,	&CDialogOptions::OnEnaleOption)

	ON_BN_CLICKED(IDC_BT_APPLY, &CDialogOptions::OnBnClickedBtApply)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_CHECK_SHOW_DSP_WIND, &CDialogOptions::OnBnClickedCheckShowDspWind)
	ON_EN_CHANGE(IDC_EDT_DELAY, &CDialogOptions::OnEnChangeEdtDelay)
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	UpdateData(true);
}


BOOL CDialogOptions::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CBrush backBrush(RGB(87, 87, 87));               // 파랑색. 원하는 컬러를 넣주면 된다...
	CBrush* pOldBrush = pDC->SelectObject(&backBrush);
	CRect rect; pDC->GetClipBox(&rect);
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);
	return TRUE;
	//return CDialog::OnEraseBkgnd(pDC);
}


void CDialogOptions::OnBnClickedCheckShowDspWind()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDialogOptions::OnEnChangeEdtDelay()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
