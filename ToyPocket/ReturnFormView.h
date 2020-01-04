#pragma once

#include "ReturnSheet.h"


// CReturnFormView �� ���Դϴ�.

class CReturnFormView : public CFormView
{
	DECLARE_DYNCREATE(CReturnFormView)
protected:
	virtual ~CReturnFormView();

public:
	CReturnSheet* ReturnSheet;
	CReturnFormView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�. 
	enum { IDD = IDD_RETURNFORMVIEW };
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


