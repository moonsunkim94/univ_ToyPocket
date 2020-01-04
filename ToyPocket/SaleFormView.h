#pragma once

#include "SaleSheet.h"

// CSaleFormView �� ���Դϴ�.

class CSaleFormView : public CFormView
{
	DECLARE_DYNCREATE(CSaleFormView)

protected:
	virtual ~CSaleFormView();

public:
	CSaleSheet* SaleSheet;
	CSaleFormView();// ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	enum { IDD = IDD_SALEFORMVIEW };
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
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


