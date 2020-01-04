// ReturnFormView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ReturnFormView.h"


// CReturnFormView

IMPLEMENT_DYNCREATE(CReturnFormView, CFormView)

CReturnFormView::CReturnFormView()
	: CFormView(CReturnFormView::IDD)
{

}

CReturnFormView::~CReturnFormView()
{
}

void CReturnFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CReturnFormView, CFormView)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CReturnFormView 진단입니다.

#ifdef _DEBUG
void CReturnFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CReturnFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CReturnFormView 메시지 처리기입니다.


void CReturnFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CWnd *pPlaceHolder = GetDlgItem(IDC_RETURNSHEET);
    ReturnSheet = new CReturnSheet(_T("RETURN"));

	ReturnSheet->Create(pPlaceHolder, WS_CHILD | WS_VISIBLE, 0);
	
	CRect rcSheet;

    pPlaceHolder->GetWindowRect(&rcSheet);
   
	CTabCtrl *TabCtrl = ReturnSheet->GetTabControl();
	TabCtrl->MoveWindow(0, 0, rcSheet.Width(), rcSheet.Height());
	
	ReturnSheet->SetWindowPos(NULL, 0, 0, rcSheet.Width(), rcSheet.Height(), SWP_NOZORDER | SWP_NOACTIVATE);

	ReturnSheet->ModifyStyleEx(0, WS_EX_CONTROLPARENT);
	ReturnSheet->ModifyStyle(0, WS_TABSTOP);
	ReturnSheet->SetActivePage(0);
}


BOOL CReturnFormView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rt;
    GetClientRect(&rt);  // 클라이언트 영역의 크기 계산
	pDC->FillSolidRect(&rt, RGB(232, 229, 209));  

	return TRUE; 
	//return CFormView::OnEraseBkgnd(pDC);
}
