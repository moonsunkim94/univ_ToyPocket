// ReturnFormView.cpp : ���� �����Դϴ�.
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


// CReturnFormView �����Դϴ�.

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


// CReturnFormView �޽��� ó�����Դϴ�.


void CReturnFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rt;
    GetClientRect(&rt);  // Ŭ���̾�Ʈ ������ ũ�� ���
	pDC->FillSolidRect(&rt, RGB(232, 229, 209));  

	return TRUE; 
	//return CFormView::OnEraseBkgnd(pDC);
}
