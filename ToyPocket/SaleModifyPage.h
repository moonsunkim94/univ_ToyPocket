#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "atlcomtime.h"
#include "afxext.h"


// CSaleModifyPage ��ȭ �����Դϴ�.

class CSaleModifyPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CSaleModifyPage)

public:
	CSaleModifyPage();
	virtual ~CSaleModifyPage();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SALE_MODIFY_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_sim_list;
	CEdit m_siname_Edit;
	CEdit m_sicode_Edit;
	CEdit m_samount_Edit;
	CDateTimeCtrl m_soutDate;
	CString m_sicode;
	CString m_siname;
	int nListIndex;
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPaint();
	CString m_samount_modify;
	afx_msg void OnBnClickedSalemodify();
	CString m_samount;
	CString inputamount;
	COleDateTime m_soutdate_value;
	CBitmapButton m_modifybtn;
	CBitmapButton m_modicancelbtn;
	CComboBox m_combo1;
	CComboBox m_combo2;
	CComboBox m_combo3;
	CEdit m_samout_modify_Edit;
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
};
