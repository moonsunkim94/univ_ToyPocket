// SaleSheet.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "SaleSheet.h"


// CSaleSheet

IMPLEMENT_DYNAMIC(CSaleSheet, CPropertySheet)

CSaleSheet::CSaleSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&p1);
	AddPage(&p2);
}

CSaleSheet::CSaleSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&p1);
	AddPage(&p2);
}

CSaleSheet::~CSaleSheet()
{
}


BEGIN_MESSAGE_MAP(CSaleSheet, CPropertySheet)
END_MESSAGE_MAP()


// CSaleSheet �޽��� ó�����Դϴ�.
