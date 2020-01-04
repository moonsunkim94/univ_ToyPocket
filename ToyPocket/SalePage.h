#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "atlcomtime.h"
// CSalePage 대화 상자입니다.

class CSalePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CSalePage)

public:
	CSalePage();
	virtual ~CSalePage();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SALE_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_scombosearch;
	int nListIndex;
	CString m_icount;
	CString m_iccode;
	CString m_iinputprice;
	CString m_iOutputprice;
	afx_msg void OnCbnSelchangeScomboSearch();
	CStatic m_static_inputdata;
	CListCtrl m_si_List;
	afx_msg void OnBnClickedSearchbtn();
	CString m_ssearch;
	afx_msg void OnPaint();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_sicode;
	CEdit m_siname;
	afx_msg void OnBnClickedRegister();
	CString m_samount;
	COleDateTime m_sdate;
	CString m_si_code;
	CBitmapButton m_search_btn;
	CBitmapButton m_ok_btn;
	CBitmapButton m_cancel_btn;
	CString m_total_amount;
	CEdit m_totalamount_Edit;
	CComboBox m_combo1;
	CComboBox m_combo2;
	CComboBox m_combo3;
	CString m_si_name;
	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
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
	void DrawBMP(LPCTSTR lpszFileName);
	CStatic m_siimage;
	BOOL bFirst;
	CString imgname;
	CString m_icode;
	CEdit m_cname_D;
	CString m_outccode;
	CString m_outcname;
	CBitmapButton m_comsearchbtn;
	afx_msg void OnBnClickedSearchbtn2();
	void ReInitDialog2();
	afx_msg void OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult); 
};
