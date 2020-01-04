#pragma once
#include "afxwin.h"

// CItemSearchPage 대화 상자입니다.

class CItemSearchPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CItemSearchPage)

public:
	CItemSearchPage();
	virtual ~CItemSearchPage();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ITEM_SEARCH_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_isearch;
	CComboBox m_icombosearch;
	CListCtrl m_is_list;
	afx_msg void OnBnClickedItemSearchbtn();
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
	virtual BOOL OnInitDialog();
	afx_msg HCURSOR OnQueryDragIcon();//
	static int CALLBACK CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);//
	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);//
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);//
	CBitmapButton m_search_btn;
	afx_msg void OnItemDelete();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	CString icode;
	afx_msg void OnBnClickedExcelSave();
	CString result;
	CBitmapButton m_excelbtn;
	CBitmapButton m_clearbtn;
	afx_msg void OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult); 
	afx_msg void OnBnClickedClear();
	void ReInitDialog();
};
