#pragma once

// CRegisterIdSearchDlg 대화 상자입니다.

class CRegisterIdSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegisterIdSearchDlg)

public:
	CRegisterIdSearchDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRegisterIdSearchDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_REGISTERIDSEARCHDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
