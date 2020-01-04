
// ToyPocketView.h : CToyPocketView 클래스의 인터페이스
//

#pragma once
#include "afxwin.h"

class CToyPocketSet;
class CToyPocketDoc;

class CToyPocketView : public CRecordView
{
public:
	CToyPocketView();
protected: // serialization에서만 만들어집니다.
	DECLARE_DYNCREATE(CToyPocketView)

public:
	enum{ IDD = IDD_TOYPOCKET_FORM };
	CToyPocketSet* m_pSet;

// 특성입니다.
public:
	CToyPocketDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CToyPocketView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLogin();
	CString m_loginid;
	CString m_loginpwd;
	afx_msg void OnBnClickedRegister();
	CBitmapButton loginbtn;
	CStatic staticsize;
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CBitmapButton m_registerbtn;
	afx_msg void OnBnClickedRegisterBtn();
};

#ifndef _DEBUG  // ToyPocketView.cpp의 디버그 버전
inline CToyPocketDoc* CToyPocketView::GetDocument() const
   { return reinterpret_cast<CToyPocketDoc*>(m_pDocument); }
#endif

