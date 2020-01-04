#pragma once
#include "afxwin.h"
#include "atlcomtime.h"
#include "afxext.h"


// CItemModifyPage 대화 상자입니다.

class CItemModifyPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CItemModifyPage)

public:
	CItemModifyPage();
	virtual ~CItemModifyPage();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ITEM_MODIFY_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	CComboBox m_ilarge;
	CComboBox m_imedium;
	CComboBox m_ismall;
	CString m_icode;
	CString m_iname;
	CString m_icname;
	CString m_iccode;
	CString m_icount;
	CString m_iinput;
	CString m_ioutput;
	CEdit m_icode_Edit;
	CEdit m_iname_Edit;
	CEdit m_icname_Edit;
	CEdit m_iccode_Edit;
	CEdit m_icount_Edit;
	CEdit m_iinput_Edit;
	CEdit m_ioutputEdit;
	CDateTimeCtrl m_idate;
	afx_msg void OnBnClickedMdlgItemSearch();
	afx_msg void OnBnClickedModifyClear();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo4();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedImageSearch();
	afx_msg void OnBnClickedItemModify();
	CString Big;
	CString Middle;
	CString Small;
	CString imgname;
	CString SelectSmall(int bigc, int midc, int smallc);
	CString SelectMedium(int index);
	CString SelectLarge(int index);
	CString temp;
	void DrawBMP(LPCTSTR lpszFileName);
	void bigmidsmall(void);
	void gbigmidsmall(void);
	CStatic m_iimage;
	CBitmapButton m_img_set;
	CBitmapButton m_img_cancelbtn;
	CBitmapButton m_searchbtn;
	CBitmapButton m_percentbtn;
	CBitmapButton m_clearbtn;
	CBitmapButton m_modifybtn;
	CBitmapButton m_cancelbtn;
	afx_msg void OnBnClickedPercent();
	afx_msg void OnBnClickedComSearchBtn();
	CBitmapButton m_comsearch_btn;
	BOOL bFirst;
	afx_msg void OnBnClickedImageCancle();
};
