#pragma once
// CExchangeModifyPage ��ȭ �����Դϴ�.

class CExchangeModifyPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CExchangeModifyPage)

public:
	CExchangeModifyPage();
	virtual ~CExchangeModifyPage();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_EXCHANGE_MODIFY_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CBitmapButton m_exoksetbtn;
	CBitmapButton m_excancelbtn;
	virtual BOOL OnInitDialog();

};
