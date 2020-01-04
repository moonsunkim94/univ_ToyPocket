// ItemSheetDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ItemSheetDlg.h"



// CItemSheetDlg

IMPLEMENT_DYNAMIC(CItemSheetDlg, CPropertySheet)

CItemSheetDlg::CItemSheetDlg(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&ip1);
	AddPage(&ip2);
	AddPage(&ip3);
	AddPage(&ip4);
}

CItemSheetDlg::CItemSheetDlg(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&ip1);
	AddPage(&ip2);
	AddPage(&ip3);
	AddPage(&ip4);
}

CItemSheetDlg::~CItemSheetDlg()
{
}


BEGIN_MESSAGE_MAP(CItemSheetDlg, CPropertySheet)
END_MESSAGE_MAP()


// CItemSheetDlg 메시지 처리기입니다.
