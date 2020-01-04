#pragma once
#include "afxwin.h"
#include "afxcmn.h"
// CExchangeSearchPage 대화 상자입니다.

class CExchangeSearchPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CExchangeSearchPage)

public:
	CExchangeSearchPage();
	virtual ~CExchangeSearchPage();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_EXCHANGE_SEARCH_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
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
	afx_msg void OnCbnSelchangeComboSearch();
	CComboBox m_ex_Combo;
	CString m_ex_Search;
	CListCtrl m_ex_list;
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnExchangeDelete();
	int m_skey;
	afx_msg void OnBnClickedExcelSave();
	CString result;
	CBitmapButton m_exsearchbtn;
	CBitmapButton m_excelbtn;
	CBitmapButton m_clearbtn;
	afx_msg void OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedClear();
};
