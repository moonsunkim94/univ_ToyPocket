#pragma once

#include "ReturnPage.h"
#include "ReturnSearchPage.h"

// CReturnSheet

class CReturnSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CReturnSheet)

public:
	CReturnSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CReturnSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CReturnSheet();
	
	CReturnPage p1;
	CReturnSearchPage p2;

protected:
	DECLARE_MESSAGE_MAP()
};


