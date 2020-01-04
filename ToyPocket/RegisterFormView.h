#pragma once

#include "ToyPocketSet.h"
#include "atlcomtime.h"
#include "afxwin.h"

// CRegisterFormView 폼 뷰입니다.

class CRegisterFormView : public CFormView
{
	DECLARE_DYNCREATE(CRegisterFormView)

protected:
	
	virtual ~CRegisterFormView();

public:
	CString sql;//여기추가
	CToyPocketSet m_pMemSet;//여기추가

	CRegisterFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	enum { IDD = IDD_REGISTER_FORM };
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
	CString m_strName;
	CString m_loginpwd;
	CString m_loginpwd2;
	afx_msg void OnBnClickedRegister();
	virtual void OnInitialUpdate();
	CString m_userEmail;
	COleDateTime m_userBirth;
	afx_msg void OnBnClickedCancle();
	CEdit m_strName_Edit;
	CEdit m_loginpwd_Edit;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CBitmapButton m_registerbtn;
	CBitmapButton m_cancelbtn;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString m_userName;
};


