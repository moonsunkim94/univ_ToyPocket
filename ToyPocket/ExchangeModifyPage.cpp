// ExchangeModifyPage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ExchangeModifyPage.h"
#include "afxdialogex.h"


// CExchangeModifyPage 대화 상자입니다.

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


// CExchangeModifyPage 메시지 처리기입니다.


BOOL CExchangeModifyPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_exoksetbtn.LoadBitmaps(IDB_BMP_OKSET, NULL, NULL, NULL);
	m_exoksetbtn.SizeToContent();

	m_excancelbtn.LoadBitmaps(IDB_BMP_CANCEL, NULL, NULL, NULL);
	m_excancelbtn.SizeToContent();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
