// ExchangeFormView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ExchangeFormView.h"


// CExchangeFormView

IMPLEMENT_DYNCREATE(CExchangeFormView, CFormView)

CExchangeFormView::CExchangeFormView()
	: CFormView(CExchangeFormView::IDD)
{

}

CExchangeFormView::~CExchangeFormView()
{
}

void CExchangeFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExchangeFormView, CFormView)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CExchangeFormView 진단입니다.

#ifdef _DEBUG
void CExchangeFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CExchangeFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CExchangeFormView 메시지 처리기입니다.


void CExchangeFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CWnd *pPlaceHolder = GetDlgItem(IDC_EXCHANGESHEET);
    ExchageSheet = new CExchangeSheet(_T("EXCHANGE"));

	ExchageSheet->Create(pPlaceHolder, WS_CHILD | WS_VISIBLE, 0);
	
	CRect rcSheet;

    pPlaceHolder->GetWindowRect(&rcSheet);
   
	CTabCtrl *TabCtrl = ExchageSheet->GetTabControl();
	TabCtrl->MoveWindow(0, 0, rcSheet.Width(), rcSheet.Height());
	
	ExchageSheet->SetWindowPos(NULL, 0, 0, rcSheet.Width(), rcSheet.Height(), SWP_NOZORDER | SWP_NOACTIVATE);

	ExchageSheet->ModifyStyleEx(0, WS_EX_CONTROLPARENT);
	ExchageSheet->ModifyStyle(0, WS_TABSTOP);
	ExchageSheet->SetActivePage(0);
}


BOOL CExchangeFormView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rt;
    GetClientRect(&rt);  // 클라이언트 영역의 크기 계산
	pDC->FillSolidRect(&rt, RGB(232, 229, 209));  

	return TRUE; 
	//return CFormView::OnEraseBkgnd(pDC);
}
