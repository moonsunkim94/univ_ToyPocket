#pragma once

// CReturnModifyPage ��ȭ �����Դϴ�.

class CReturnModifyPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CReturnModifyPage)

public:
	CReturnModifyPage();
	virtual ~CReturnModifyPage();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RETURN_MODIFY_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CBitmapButton m_researchbtn;
	CBitmapButton m_resetokbtn;
	CBitmapButton m_recancelbtn;
	virtual BOOL OnInitDialog();
};
