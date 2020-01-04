#pragma once

// CNoticeDlg 대화 상자입니다.

class CNoticeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNoticeDlg)

public:
	CNoticeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CNoticeDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_NOTICE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	virtual BOOL OnInitDialog();
	typedef struct SORTPARAM
	{
		int iSortColumn;
		bool bSortDirect;
		CListCtrl *pList;
	}SORTPARAM;
	HICON m_hIcon;
	BOOL	m_bAscending;
	void UpdateArrow(void);
	int nListIndex;
	static int CALLBACK CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	CBitmapButton m_plusbtn;
	afx_msg void OnBnClickedAddBtn();
	CBitmapButton m_minusbtn;
	afx_msg void OnBnClickedDeleteBtn();
	CBitmapButton m_setbtn;
	afx_msg void OnBnClickedBModiBtn();
	CString m_addnotice;
	CEdit m_addnotice_Edit;
	CListCtrl m_noticeList;
	CString nnotice;
	CString n_ldate;
	afx_msg void OnNoticeModi();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult); 
};
