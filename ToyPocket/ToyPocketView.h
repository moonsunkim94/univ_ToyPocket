
// ToyPocketView.h : CToyPocketView Ŭ������ �������̽�
//

#pragma once
#include "afxwin.h"

class CToyPocketSet;
class CToyPocketDoc;

class CToyPocketView : public CRecordView
{
public:
	CToyPocketView();
protected: // serialization������ ��������ϴ�.
	DECLARE_DYNCREATE(CToyPocketView)

public:
	enum{ IDD = IDD_TOYPOCKET_FORM };
	CToyPocketSet* m_pSet;

// Ư���Դϴ�.
public:
	CToyPocketDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CToyPocketView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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

#ifndef _DEBUG  // ToyPocketView.cpp�� ����� ����
inline CToyPocketDoc* CToyPocketView::GetDocument() const
   { return reinterpret_cast<CToyPocketDoc*>(m_pDocument); }
#endif

