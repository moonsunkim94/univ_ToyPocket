#pragma once
#include "afxwin.h"
#include "afxext.h"


// CItemPlusPage 대화 상자입니다.

class CItemPlusPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CItemPlusPage)

public:
	CItemPlusPage();
	virtual ~CItemPlusPage();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ITEM_ADD_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSearchButton();
	afx_msg void OnBnClickedItemPlus();
	CEdit m_iname_Edit;
	CEdit m_icode_Edit;
	CEdit m_cname_Edit;
	CEdit m_ccode_Edit;
	CEdit m_first;
	CEdit m_second;
	CEdit m_third;
	CEdit m_inprice_Edit;
	CEdit m_outprice_Edit;
	CEdit m_date;
	CEdit m_inamount_Edit;
	CString m_iplus_amount;
	CString m_inamount;
	CString m_iname;
	CBitmapButton m_isearchbtn;
	CBitmapButton m_addbtn;
	CBitmapButton m_cancelbtn;
	afx_msg void OnPaint();
};
