// ItemFormView.cpp : 구현 파일입니다.
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


// CItemFormView 진단입니다.

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


// CItemFormView 메시지 처리기입니다.


void CItemFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rt;
    GetClientRect(&rt);  // 클라이언트 영역의 크기 계산
	pDC->FillSolidRect(&rt, RGB(232, 229, 209));  

	return TRUE; 
	//return CFormView::OnEraseBkgnd(pDC);
}
