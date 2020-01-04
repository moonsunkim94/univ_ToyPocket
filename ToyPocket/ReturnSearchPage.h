#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CReturnSearchPage 대화 상자입니다.

class CReturnSearchPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CReturnSearchPage)

public:
	CReturnSearchPage();
	virtual ~CReturnSearchPage();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RETURN_SEARCH_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_re_list;
	CComboBox m_res_Combo;
	CString m_res_Search;
	afx_msg void OnCbnSelchangeComboSearch();
	afx_msg void OnBnClickedOk();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
    int nListIndex;
	afx_msg void OnReturnDelete();
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
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	int m_skey;
	afx_msg void OnBnClickedExcelSave();
	CString result;
	CBitmapButton m_researchbtn;
	CBitmapButton m_excelbtn;
	CBitmapButton m_clearbtn;
	afx_msg void OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult); 
	afx_msg void OnBnClickedClear();
};
