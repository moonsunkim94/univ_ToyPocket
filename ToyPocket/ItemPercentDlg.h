#pragma once
#include "afxext.h"


// CItemPercentDlg ��ȭ �����Դϴ�.

class CItemPercentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CItemPercentDlg)

public:
	CItemPercentDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CItemPercentDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ITEMPERCENTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
