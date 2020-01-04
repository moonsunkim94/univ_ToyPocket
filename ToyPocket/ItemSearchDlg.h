#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxext.h"


// CItemSearchDlg ��ȭ �����Դϴ�.

class CItemSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CItemSearchDlg)

public:
	CItemSearchDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CItemSearchDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ITEMSEARCHDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_isearch_combo;
	CString m_isearch;
	CListCtrl m_item_List;
	afx_msg void OnBnClickedSearchButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	static int CALLBACK CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
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
	CString m_iname;
	CString m_icode;
	CString m_cname;
	CString m_ccode;
	CString m_combo1;
	CString m_combo2;
	CString m_combo3;
	CString m_inprice;
	CString m_outprice;
	CString m_inamount;
	CString m_inDate;
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	CBitmapButton m_isearchbtn;
	afx_msg void OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult); 
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
