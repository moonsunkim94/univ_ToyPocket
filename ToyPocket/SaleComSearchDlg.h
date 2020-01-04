#pragma once

// CSaleComSearchDlg 대화 상자입니다.

class CSaleComSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSaleComSearchDlg)

public:
	CSaleComSearchDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSaleComSearchDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SALE_COM_SEARCHDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ccombobox;
	CString m_csearch;
	CListCtrl m_cs_List;
	CBitmapButton m_combtn;
	afx_msg void OnBnClickedSearch();
	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
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
	CString m_ccodeset;
	CString m_cnameset;
	afx_msg void OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult); 
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
