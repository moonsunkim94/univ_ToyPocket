#pragma once

#include "ItemPage.h"
#include "ItemModifyPage.h"
#include "ItemSearchPage.h"
#include "ItemPlusPage.h"
// CItemSheetDlg

class CItemSheetDlg : public CPropertySheet
{
	DECLARE_DYNAMIC(CItemSheetDlg)

public:
	CItemSheetDlg(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CItemSheetDlg(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CItemSheetDlg();

	CItemPage ip1;
	CItemSearchPage ip2;
	CItemModifyPage ip3;
	CItemPlusPage ip4;
protected:
	DECLARE_MESSAGE_MAP()
};


