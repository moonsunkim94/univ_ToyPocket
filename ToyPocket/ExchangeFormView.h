#pragma once

#include "ExchangeSheet.h"

// CExchangeFormView 폼 뷰입니다.

class CExchangeFormView : public CFormView
{
	DECLARE_DYNCREATE(CExchangeFormView)
protected:
	virtual ~CExchangeFormView();

public:
	CExchangeFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	CExchangeSheet* ExchageSheet;
	enum { IDD = IDD_EXCHANGEFORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


