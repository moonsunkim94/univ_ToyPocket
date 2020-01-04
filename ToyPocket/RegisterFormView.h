#pragma once

#include "ToyPocketSet.h"
#include "atlcomtime.h"
#include "afxwin.h"

// CRegisterFormView �� ���Դϴ�.

class CRegisterFormView : public CFormView
{
	DECLARE_DYNCREATE(CRegisterFormView)

protected:
	
	virtual ~CRegisterFormView();

public:
	CString sql;//�����߰�
	CToyPocketSet m_pMemSet;//�����߰�

	CRegisterFormView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	enum { IDD = IDD_REGISTER_FORM };
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


