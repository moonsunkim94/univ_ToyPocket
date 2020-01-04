#pragma once

#include "SaleSheet.h"

// CSaleFormView 폼 뷰입니다.

class CSaleFormView : public CFormView
{
	DECLARE_DYNCREATE(CSaleFormView)

protected:
	virtual ~CSaleFormView();

public:
	CSaleSheet* SaleSheet;
	CSaleFormView();// 동적 만들기에 사용되는 protected 생성자입니다.
	enum { IDD = IDD_SALEFORMVIEW };
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
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


