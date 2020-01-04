#pragma once

#include "ItemSheetDlg.h"
#include "afxwin.h"

// CItemFormView �� ���Դϴ�.

class CItemFormView : public CFormView
{
	DECLARE_DYNCREATE(CItemFormView)
public:
	CItemFormView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
protected:
	
	virtual ~CItemFormView();

public:
	CItemSheetDlg* ItemSheetDlg;
	enum { IDD = IDD_ITEMFORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


