#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxext.h"
 
 


// CSaleSearchPage 대화 상자입니다.

class CSaleSearchPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CSaleSearchPage)

public:
	CSaleSearchPage();
	virtual ~CSaleSearchPage();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SALE_SEARCH_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_s_List;
	CComboBox m_ssearch_combo;
	CString m_ssearch;
	afx_msg void OnBnClickedSaleSearchBtn();
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
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	CString sprice;
	CString samount;
	CString sccode;
	CString sicode;
	afx_msg void OnSaleDelete();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	CBitmapButton m_isearch_btn;
	int m_skey;
	afx_msg void OnBnClickedExcelSave();
	CString result;
	CBitmapButton m_excelbtn;
	CBitmapButton m_clearbtn;
	afx_msg void OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult); 
	afx_msg void OnBnClickedClear();
};
