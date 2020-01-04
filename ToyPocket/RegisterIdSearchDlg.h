#pragma once

// CRegisterIdSearchDlg ��ȭ �����Դϴ�.

class CRegisterIdSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegisterIdSearchDlg)

public:
	CRegisterIdSearchDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRegisterIdSearchDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_REGISTERIDSEARCHDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_idsearchCombo;
	CString m_idsearch;
	afx_msg void OnBnClickedSearch();
	CListCtrl m_idList;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	typedef struct SORTPARAM
	{
		int iSortColumn;
		bool bSortDirect;
		CListCtrl *pList;
	}SORTPARAM;
	HICON m_hIcon;
	BOOL	m_bAscending;
	void UpdateArrow(void);
	static int CALLBACK CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	int nListIndex;
	CString m_idset;
	CString m_permiset;
	CString m_ynset;
	afx_msg void OnIddelete();
	afx_msg void OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult); 
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
