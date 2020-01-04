// ExchangeSheet.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ExchangeSheet.h"


// CExchangeSheet

IMPLEMENT_DYNAMIC(CExchangeSheet, CPropertySheet)

CExchangeSheet::CExchangeSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&p1);
	AddPage(&p2);
	//AddPage(&p3);
}

CExchangeSheet::CExchangeSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&p1);
	AddPage(&p2);
	//AddPage(&p3);
}

CExchangeSheet::~CExchangeSheet()
{
}


BEGIN_MESSAGE_MAP(CExchangeSheet, CPropertySheet)
END_MESSAGE_MAP()


// CExchangeSheet �޽��� ó�����Դϴ�.
