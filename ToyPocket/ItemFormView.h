#pragma once

#include "ItemSheetDlg.h"
#include "afxwin.h"

// CItemFormView 폼 뷰입니다.

class CItemFormView : public CFormView
{
	DECLARE_DYNCREATE(CItemFormView)
public:
	CItemFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


