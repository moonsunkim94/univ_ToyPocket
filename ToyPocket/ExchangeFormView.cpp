// ExchangeFormView.cpp : ���� �����Դϴ�.
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


// CExchangeFormView �����Դϴ�.

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


// CExchangeFormView �޽��� ó�����Դϴ�.


void CExchangeFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rt;
    GetClientRect(&rt);  // Ŭ���̾�Ʈ ������ ũ�� ���
	pDC->FillSolidRect(&rt, RGB(232, 229, 209));  

	return TRUE; 
	//return CFormView::OnEraseBkgnd(pDC);
}
