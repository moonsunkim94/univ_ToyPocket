#pragma once

// CPasswordChangeDlg 대화 상자입니다.

class CPasswordChangeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPasswordChangeDlg)

public:
	CPasswordChangeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPasswordChangeDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PASSWORD_CHANGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CEdit m_pwdEdit;
	CString m_pwd;
	CEdit m_chpwdEdit;
	CString m_changepwd;
	CEdit m_chpwd2Edit;
	CString m_changepwd2;
	CBitmapButton m_paokbtn;
	CBitmapButton m_pacancelbtn;
};
