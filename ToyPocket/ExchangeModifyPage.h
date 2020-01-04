#pragma once
// CExchangeModifyPage 대화 상자입니다.

class CExchangeModifyPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CExchangeModifyPage)

public:
	CExchangeModifyPage();
	virtual ~CExchangeModifyPage();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_EXCHANGE_MODIFY_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CBitmapButton m_exoksetbtn;
	CBitmapButton m_excancelbtn;
	virtual BOOL OnInitDialog();

};
