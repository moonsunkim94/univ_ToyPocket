// CompanyFormView.cpp : 구현 파일입니다.
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


// CCompanyFormView 진단입니다.

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


// CCompanyFormView 메시지 처리기입니다.


void CCompanyFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rt;
    GetClientRect(&rt);  // 클라이언트 영역의 크기 계산
    pDC->FillSolidRect(&rt, RGB(232, 229, 209));  

	return TRUE; 
	//return CFormView::OnEraseBkgnd(pDC);
}


HBRUSH CCompanyFormView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
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
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
