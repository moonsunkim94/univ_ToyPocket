#pragma once

// CManagerPermitDlg ��ȭ �����Դϴ�.

class CManagerPermitDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManagerPermitDlg)

public:
	CManagerPermitDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CManagerPermitDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MANAGE_CONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_idEdit;
	CString m_loginid;
	CEdit m_ynEdit;
	CEdit m_permiEdit;
	CComboBox m_manage_Combo;
	BOOL m_check;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedOk();

	int nIndex;
	CString strSort;
	CString strRadio;
	virtual BOOL OnInitDialog();
	void OnRadioButton(UINT value);
	CBitmapButton m_regisearchbtn;
	CBitmapButton m_regiokbtn;
	CBitmapButton m_regicancelbtn;
	afx_msg void OnBnClickedButton1();
};
