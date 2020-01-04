// CompanyFormView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "CompanyFormView.h"


// CCompanyFormView

IMPLEMENT_DYNCREATE(CCompanyFormView, CFormView)

CCompanyFormView::CCompanyFormView()
	: CFormView(CCompanyFormView::IDD)
{

}

CCompanyFormView::~CCompanyFormView()
{
}

void CCompanyFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCompanyFormView, CFormView)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCompanyFormView �����Դϴ�.

#ifdef _DEBUG
void CCompanyFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCompanyFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCompanyFormView �޽��� ó�����Դϴ�.


void CCompanyFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CWnd *pPlaceHolder = GetDlgItem(IDC_COMPANYSHEET);
    CompanySheet = new CCompanySheet(_T("COMPANY"));

	CompanySheet->Create(pPlaceHolder, WS_CHILD | WS_VISIBLE, 0);
	
	CRect rcSheet;

    pPlaceHolder->GetWindowRect(&rcSheet);
   
	CTabCtrl *TabCtrl = CompanySheet->GetTabControl();
	TabCtrl->MoveWindow(0, 0, rcSheet.Width(), rcSheet.Height());
	
	CompanySheet->SetWindowPos(NULL, 0, 0, rcSheet.Width(), rcSheet.Height(), SWP_NOZORDER | SWP_NOACTIVATE);

	CompanySheet->ModifyStyleEx(0, WS_EX_CONTROLPARENT);
	CompanySheet->ModifyStyle(0, WS_TABSTOP);
	CompanySheet->SetActivePage(0);

}


BOOL CCompanyFormView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rt;
    GetClientRect(&rt);  // Ŭ���̾�Ʈ ������ ũ�� ���
    pDC->FillSolidRect(&rt, RGB(232, 229, 209));  

	return TRUE; 
	//return CFormView::OnEraseBkgnd(pDC);
}


HBRUSH CCompanyFormView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_CNUM)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_CNAME)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_CBUS)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_CTYPE)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_TEL1)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_TEL2)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_ADDR)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_CCEO)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_CEMAIL)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_MTEL1)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_MTEL2)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_MEMO)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}
