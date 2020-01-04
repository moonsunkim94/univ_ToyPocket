// ItemFormView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ItemFormView.h"


// CItemFormView

IMPLEMENT_DYNCREATE(CItemFormView, CFormView)

CItemFormView::CItemFormView()
	: CFormView(CItemFormView::IDD)
{

}

CItemFormView::~CItemFormView()
{
}

void CItemFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CItemFormView, CFormView)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CItemFormView �����Դϴ�.

#ifdef _DEBUG
void CItemFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CItemFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CItemFormView �޽��� ó�����Դϴ�.


void CItemFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CWnd *pPlaceHolder = GetDlgItem(IDC_ItemSheet);
    ItemSheetDlg = new CItemSheetDlg(_T("ITEM"));

	ItemSheetDlg->Create(pPlaceHolder, WS_CHILD | WS_VISIBLE, 0);
	
	CRect rcSheet;

    pPlaceHolder->GetWindowRect(&rcSheet);
   
	CTabCtrl *TabCtrl = ItemSheetDlg->GetTabControl();
	TabCtrl->MoveWindow(0, 0, rcSheet.Width(), rcSheet.Height());
	
	ItemSheetDlg->SetWindowPos(NULL, 0, 0, rcSheet.Width(), rcSheet.Height(), SWP_NOZORDER | SWP_NOACTIVATE);

	ItemSheetDlg->ModifyStyleEx(0, WS_EX_CONTROLPARENT);
	ItemSheetDlg->ModifyStyle(0, WS_TABSTOP);
	ItemSheetDlg->SetActivePage(0);
}


BOOL CItemFormView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rt;
    GetClientRect(&rt);  // Ŭ���̾�Ʈ ������ ũ�� ���
	pDC->FillSolidRect(&rt, RGB(232, 229, 209));  

	return TRUE; 
	//return CFormView::OnEraseBkgnd(pDC);
}
