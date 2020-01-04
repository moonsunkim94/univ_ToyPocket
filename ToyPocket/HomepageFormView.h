#pragma once
#include "afxext.h"
#include "afxwin.h"



// CHomepageFormView 폼 뷰입니다.

class CHomepageFormView : public CFormView
{
	DECLARE_DYNCREATE(CHomepageFormView)

protected:
	
	virtual ~CHomepageFormView();

public:
	CHomepageFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	enum { IDD = IDD_HOMEPAGE_FORM };
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
	//CBitmapButton m_combtn;
	virtual void OnInitialUpdate();
	//CBitmapButton m_itembtn;
	//CBitmapButton m_salebtn;
	//CBitmapButton m_exchangebtn;
	//CBitmapButton m_returnbtn;
	//CBitmapButton m_setbtn;
	//afx_msg void OnBnClickedComBtn();
	//afx_msg void OnBnClickedItemBtn();
	//afx_msg void OnBnClickedSaleBtn();
	//afx_msg void OnBnClickedExchange();
	//afx_msg void OnBnClickedReturn();
	//afx_msg void OnBnClickedSet();
	CString m_year;
	CString m_month;
	int one_whatday;
	CRect rect[6][7];
	BOOL boolpoint;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedLamonth();
	afx_msg void OnBnClickedNemonth();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CBitmapButton m_lamonth;
	CBitmapButton m_nemonth;
	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_noticeList;
	typedef struct SORTPARAM
	{
		int iSortColumn;
		bool bSortDirect;
		CListCtrl *pList;
	}SORTPARAM;
	HICON m_hIcon;
	BOOL	m_bAscending;
	void UpdateArrow(void);
	int nListIndex;
	static int CALLBACK CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	
	CStatic staticsize;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBitmapButton m_combtn;
	CBitmapButton m_itembtn;
	CBitmapButton m_salebtn;
	CBitmapButton m_exchangebtn;
	CBitmapButton m_returnbtn;
	CBitmapButton m_setbtn;
	afx_msg void OnBnClickedCompany();
	afx_msg void OnBnClickedItem();
	afx_msg void OnBnClickedSale();
	afx_msg void OnBnClickedExchange();
	afx_msg void OnBnClickedReturn();
	afx_msg void OnBnClickedSet();
};


