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
	m_Options._nDisplayWnd = 0;
	m_Options._nUseGpu = 1;
	m_Options._nClaheGamma = 1;
	m_Options._nClaheOnly = 0;
	m_Options._nGammaOnly = 0;
	m_Options._nClaheHisEQ = 0; 
	m_Options._nHisEQOnly = 0;
	Create(IDD, pParent);
}

CDialogOptions::~CDialogOptions()
{
}

void CDialogOptions::DoDataExchange(CDataExchange* pDX)
{
	
	//DDX_Text(pDX, IDC_EDT_DELAY, m_Options._nDelay);
	DDX_Check(pDX, IDC_CHECK_SHOW_DSP_WIND, m_Options._nDisplayWnd);
	DDX_Check(pDX, IDC_CHECK_SHOW_USE_GPU, m_Options._nUseGpu);
	DDX_Check(pDX, IDC_CHECK_SHOW_USE_CLAHEGAMMA, m_Options._nClaheGamma);
	DDX_Check(pDX, IDC_CHECK_SHOW_USE_CLAHE, m_Options._nClaheOnly);
	DDX_Check(pDX, IDC_CHECK_SHOW_USE_GAMMA, m_Options._nGammaOnly);
	DDX_Check(pDX, IDC_CHECK_SHOW_USE_CLAHEHISEQ, m_Options._nClaheHisEQ);
	DDX_Check(pDX, IDC_CHECK_SHOW_USE_HISEQ, m_Options._nHisEQOnly);
	
	
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogOptions, CDialog)

	ON_BN_CLICKED(IDC_CHECK_USE_RANDOM_DELAY,	&CDialogOptions::OnEnaleOption)
	ON_BN_CLICKED(IDC_BT_APPLY, &CDialogOptions::OnBnClickedBtApply)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_CHECK_SHOW_USE_GPU, &CDialogOptions::OnBnClickedCheckShowUseGpu)
	ON_EN_CHANGE(IDC_EDT_DELAY, &CDialogOptions::OnEnChangeEdtDelay)
	ON_BN_CLICKED(IDC_CHECK_SHOW_USE_CLAHEGAMMA, &CDialogOptions::OnBnClickedCheckShowUseClahegamma)
	ON_BN_CLICKED(IDC_CHECK_SHOW_USE_CLAHE, &CDialogOptions::OnBnClickedCheckShowUseClahe)
	ON_BN_CLICKED(IDC_CHECK_SHOW_USE_GAMMA, &CDialogOptions::OnBnClickedCheckShowUseGamma)
	ON_BN_CLICKED(IDC_CHECK_SHOW_USE_HISEQ, &CDialogOptions::OnBnClickedCheckShowUseHiseq)
	ON_BN_CLICKED(IDC_CHECK_SHOW_USE_CLAHEHISEQ, &CDialogOptions::OnBnClickedCheckShowUseClahehiseq)

	
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

}


void CDialogOptions::OnEnChangeEdtDelay()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}



void CDialogOptions::OnBnClickedCheckShowUseClahegamma()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_Options._nUseGpu = 1;
}


void CDialogOptions::OnBnClickedCheckShowUseClahe()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_Options._nClaheOnly = 1;
}


void CDialogOptions::OnBnClickedCheckShowUseGamma()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CDialogOptions::OnBnClickedCheckShowUseHiseq()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CDialogOptions::OnBnClickedCheckShowUseClahehiseq()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

BOOL CDialogOptions::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CBrush backBrush(RGB(87, 87, 87));               // �Ķ���. ���ϴ� �÷��� ���ָ� �ȴ�...
	CBrush* pOldBrush = pDC->SelectObject(&backBrush);
	CRect rect; pDC->GetClipBox(&rect);
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);
	return TRUE;
}