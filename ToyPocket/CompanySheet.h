#pragma once

#include "CompanyPage.h"
#include "CompanySearchPage.h"
#include "CompanyModifyPage.h"

// CCompanySheet

class CCompanySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CCompanySheet)

public:
	CCompanySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CCompanySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CCompanySheet();
	CCompanyPage p1;
	CCompanySearchPage p2;
	CCompanyModifyPage p3;
protected:
	DECLARE_MESSAGE_MAP()
};


