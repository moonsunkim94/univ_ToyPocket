#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "atlcomtime.h"

// CReturnPage 대화 상자입니다.

class CReturnPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CReturnPage)

public:
	CReturnPage();
	virtual ~CReturnPage();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RETURN_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString SelectReason(int index);	
	afx_msg void OnBnClickedSearchbtn();
	virtual BOOL OnInitDialog();
	CListCtrl m_reList;
	CComboBox m_reCombo;
	CString m_reSearch;
	afx_msg void OnCbnSelchangeScomboSearch();
	afx_msg void OnPaint();
	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	int nListIndex;
	CEdit m_sccode_Edit;
	CEdit m_sicode_Edit;
	afx_msg void OnBnClickedOk();
	CString m_reAmount;
	CComboBox m_reReason_Combo;
	CString m_reReason;
	COleDateTime m_reDate;
	COleDateTime m_sdate;
	CString m_sAmount;
	CString m_sicode;
	CString itemAmount;
	CEdit m_sAmount_Edit;
	CDateTimeCtrl m_sDate_ctrl;
	CString reason;
	CString m_sscode;
	CString inputprice;
	CString outputprice;
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
	CString etcresaon;
	afx_msg void OnCbnSelchangeCombo2();
	void DrawBMP(LPCTSTR lpszFileName);
	BOOL bFirst;
	CString imgname;
	CStatic m_riimage;
	CString m_icode;
	CEdit m_reAmount_Edit;
	CBitmapButton m_researchbtn;
	CBitmapButton m_reokbtn;
	CBitmapButton m_recancelbtn;
	CString m_incode;
	afx_msg void OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult);
	void ReInitDialog();
};
