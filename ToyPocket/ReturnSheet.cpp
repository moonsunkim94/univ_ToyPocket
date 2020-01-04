// ReturnSheet.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ReturnSheet.h"


// CReturnSheet

IMPLEMENT_DYNAMIC(CReturnSheet, CPropertySheet)

CReturnSheet::CReturnSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&p1);
	AddPage(&p2);
}

CReturnSheet::CReturnSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&p1);
	AddPage(&p2);
}

CReturnSheet::~CReturnSheet()
{
}


BEGIN_MESSAGE_MAP(CReturnSheet, CPropertySheet)
END_MESSAGE_MAP()


// CReturnSheet �޽��� ó�����Դϴ�.
