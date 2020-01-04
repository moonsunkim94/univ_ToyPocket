// SaleFormView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "SaleFormView.h"


// CSaleFormView

IMPLEMENT_DYNCREATE(CSaleFormView, CFormView)

CSaleFormView::CSaleFormView()
	: CFormView(CSaleFormView::IDD)
{

}

CSaleFormView::~CSaleFormView()
{
}

void CSaleFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSaleFormView, CFormView)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSaleFormView �����Դϴ�.

#ifdef _DEBUG
void CSaleFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSaleFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSaleFormView �޽��� ó�����Դϴ�.


void CSaleFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	 CWnd *pPlaceHolder = GetDlgItem(IDC_SALESHEET);
    SaleSheet = new CSaleSheet(_T("RETURN"));

	SaleSheet->Create(pPlaceHolder, WS_CHILD | WS_VISIBLE, 0);
	
	CRect rcSheet;

    pPlaceHolder->GetWindowRect(&rcSheet);
   
	CTabCtrl *TabCtrl = SaleSheet->GetTabControl();
	TabCtrl->MoveWindow(0, 0, rcSheet.Width(), rcSheet.Height());
	
	SaleSheet->SetWindowPos(NULL, 0, 0, rcSheet.Width(), rcSheet.Height(), SWP_NOZORDER | SWP_NOACTIVATE);

	SaleSheet->ModifyStyleEx(0, WS_EX_CONTROLPARENT);
	SaleSheet->ModifyStyle(0, WS_TABSTOP);
	SaleSheet->SetActivePage(0);

}


BOOL CSaleFormView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rt;
    GetClientRect(&rt);  // Ŭ���̾�Ʈ ������ ũ�� ���
	pDC->FillSolidRect(&rt, RGB(232, 229, 209));  

	return TRUE; 
	//return CFormView::OnEraseBkgnd(pDC);
}


HBRUSH CSaleFormView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}

