#pragma once

// CReturnModifyPage 대화 상자입니다.

class CReturnModifyPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CReturnModifyPage)

public:
	CReturnModifyPage();
	virtual ~CReturnModifyPage();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RETURN_MODIFY_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CBitmapButton m_researchbtn;
	CBitmapButton m_resetokbtn;
	CBitmapButton m_recancelbtn;
	virtual BOOL OnInitDialog();
};
