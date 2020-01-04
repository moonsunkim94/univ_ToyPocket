#pragma once

#include "SalePage.h"
#include "SaleSearchPage.h"

// CSaleSheet

class CSaleSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CSaleSheet)

public:
	CSaleSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CSaleSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CSaleSheet();

	CSalePage p1;
	CSaleSearchPage p2;
protected:
	DECLARE_MESSAGE_MAP()
};


