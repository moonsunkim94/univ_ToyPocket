// CompanySheet.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "CompanySheet.h"


// CCompanySheet

IMPLEMENT_DYNAMIC(CCompanySheet, CPropertySheet)

CCompanySheet::CCompanySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&p1);
	AddPage(&p2);
	AddPage(&p3);
}

CCompanySheet::CCompanySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&p1);
	AddPage(&p2);
	AddPage(&p3);
}

CCompanySheet::~CCompanySheet()
{
}


BEGIN_MESSAGE_MAP(CCompanySheet, CPropertySheet)
END_MESSAGE_MAP()


// CCompanySheet 메시지 처리기입니다.
