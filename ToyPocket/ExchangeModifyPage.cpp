// ExchangeModifyPage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ExchangeModifyPage.h"
#include "afxdialogex.h"


// CExchangeModifyPage ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CExchangeModifyPage, CPropertyPage)

CExchangeModifyPage::CExchangeModifyPage()
	: CPropertyPage(CExchangeModifyPage::IDD)
{

}

CExchangeModifyPage::~CExchangeModifyPage()
{
}

void CExchangeModifyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDCANCEL, m_excancelbtn);
	DDX_Control(pDX, IDOK, m_exoksetbtn);
}


BEGIN_MESSAGE_MAP(CExchangeModifyPage, CPropertyPage)
END_MESSAGE_MAP()


// CExchangeModifyPage �޽��� ó�����Դϴ�.


BOOL CExchangeModifyPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_exoksetbtn.LoadBitmaps(IDB_BMP_OKSET, NULL, NULL, NULL);
	m_exoksetbtn.SizeToContent();

	m_excancelbtn.LoadBitmaps(IDB_BMP_CANCEL, NULL, NULL, NULL);
	m_excancelbtn.SizeToContent();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
