#pragma once

#include "ReturnSheet.h"


// CReturnFormView 폼 뷰입니다.

class CReturnFormView : public CFormView
{
	DECLARE_DYNCREATE(CReturnFormView)
protected:
	virtual ~CReturnFormView();

public:
	CReturnSheet* ReturnSheet;
	CReturnFormView();           // 동적 만들기에 사용되는 protected 생성자입니다. 
	enum { IDD = IDD_RETURNFORMVIEW };
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


