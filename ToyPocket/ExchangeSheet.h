#pragma once
#include "ExchangePage.h"
#include "ExchangeModifyPage.h"
#include "ExchangeSearchPage.h"

// CExchangeSheet

class CExchangeSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CExchangeSheet)

public:
	CExchangeSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CExchangeSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CExchangeSheet();

	CExchangePage p1;
	//CExchangeModifyPage p2;
	CExchangeSearchPage p2;
protected:
	DECLARE_MESSAGE_MAP()
};


