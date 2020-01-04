#pragma once
#include "afxext.h"


// CItemPercentDlg 대화 상자입니다.

class CItemPercentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CItemPercentDlg)

public:
	CItemPercentDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CItemPercentDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ITEMPERCENTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_percent;
	afx_msg void OnBnClickedPercent();
	afx_msg void OnBnClickedCancel();
	CBitmapButton m_setbtn;
	CBitmapButton m_cancelbtn;
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
