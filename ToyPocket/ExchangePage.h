#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"
#include "atlcomtime.h"

// CExchangePage 대화 상자입니다.

class CExchangePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CExchangePage)

public:
	CExchangePage();
	virtual ~CExchangePage();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_EXCHANGE_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_exCombo;
	CString m_exSearch;
	afx_msg void OnBnClickedSearchbtn();
	CListCtrl m_exList;
	CEdit m_sccode_Edit;
	CEdit m_sicode_Edit;
	CDateTimeCtrl m_sDate_ctrl;
	CEdit m_sAmount_Edit;
	CString m_sscode;
	CString m_sicode;
	COleDateTime m_sdate;
	CString m_sAmount;
	CString m_exAmount;
	COleDateTime m_exDate;
	CComboBox m_exReason_Combo;
	CString m_exReason;
	afx_msg void OnBnClickedOk();
	int nListIndex;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeScomboSearch();
	afx_msg void OnPaint();
	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	CString SelectReason(int index);
	CString reason;
	CString isdate;
	CString m_ss;
	CString inprice;
	CString outprice;
	CString total;
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
	afx_msg void OnCbnSelchangeCombo2();
	CString etcresaon;
	CEdit m_exAmount_Edit;
	CStatic m_eiimage;
	void DrawBMP(LPCTSTR lpszFileName);
	BOOL bFirst;
	CString imgname;
	CString m_icode;
	CString m_incode;
	CBitmapButton m_exsearchbtn;
	CBitmapButton m_exokbtn;
	CBitmapButton m_excancelbtn;
	afx_msg void OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult);
	void ReInitDialog();
};
