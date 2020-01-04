#pragma once

#include "ExchangeSheet.h"

// CExchangeFormView �� ���Դϴ�.

class CExchangeFormView : public CFormView
{
	DECLARE_DYNCREATE(CExchangeFormView)
protected:
	virtual ~CExchangeFormView();

public:
	CExchangeFormView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	CExchangeSheet* ExchageSheet;
	enum { IDD = IDD_EXCHANGEFORMVIEW };
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


