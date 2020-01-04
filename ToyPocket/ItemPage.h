#pragma once
#include "afxwin.h"
#include "atlcomtime.h"
#include "afxext.h"



// CItemPage 대화 상자입니다.

class CItemPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CItemPage)

public:
	CItemPage();
	virtual ~CItemPage();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ITEM_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ilarge;//
	CComboBox m_imedium;//
	CComboBox m_ismall;//
	CString m_icode;//
	CString m_iname;//
	CString m_icname;//
	CString m_iccode;//
	COleDateTime m_idate;//
	CString m_icount;//
	CString m_iinput;//
	CString m_ioutput;//
	CString Big;
	CString Middle;
	CString Small;
	CString imgname;
	afx_msg void OnBnClickedOk();//
	CString SelectSmall(int bigc, int midc, int smallc);
	CString SelectMedium(int index);
	CString SelectLarge(int index);
	CString temp;
	afx_msg void OnCbnSelchangeCombo2();//
	afx_msg void OnCbnSelchangeCombo4();//
	void DrawBMP(LPCTSTR lpszFileName);
	afx_msg void OnBnClickedCancel2();//
	CStatic m_iimage;
	virtual BOOL OnInitDialog();
	void bigmidsmall(void);
	afx_msg void OnBnClickedPercent();
	CEdit m_outprice_Edit;
	CBitmapButton m_img_setbtn;
	CBitmapButton m_img_cancelbtn;
	CBitmapButton m_percent_btn;
	CBitmapButton m_okbtn;
	CBitmapButton m_clearbtn;
	afx_msg void OnBnClickedComSearch();
	CEdit m_cname_Edit;
	CEdit m_ccode_Edit;
	CBitmapButton m_comsearchbtn;
	afx_msg void OnPaint();
	BOOL bFirst;
	afx_msg void OnBnClickedImageDelete();
};
