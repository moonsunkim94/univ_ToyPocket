// ReturnModifyPage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ReturnModifyPage.h"
#include "afxdialogex.h"


// CReturnModifyPage 대화 상자입니다.

IMPLEMENT_DYNAMIC(CReturnModifyPage, CPropertyPage)

CReturnModifyPage::CReturnModifyPage()
	: CPropertyPage(CReturnModifyPage::IDD)
{

}

CReturnModifyPage::~CReturnModifyPage()
{
}

void CReturnModifyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL2, m_researchbtn);
	DDX_Control(pDX, IDOK, m_resetokbtn);
	DDX_Control(pDX, IDCANCEL, m_recancelbtn);
}


BEGIN_MESSAGE_MAP(CReturnModifyPage, CPropertyPage)
END_MESSAGE_MAP()


// CReturnModifyPage 메시지 처리기입니다.


BOOL CReturnModifyPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_researchbtn.LoadBitmaps(IDB_BMP_SEARCH, NULL, NULL, NULL);
	m_researchbtn.SizeToContent(); 

	m_resetokbtn.LoadBitmaps(IDB_BMP_OKSET, NULL, NULL, NULL);
	m_resetokbtn.SizeToContent();

	m_recancelbtn.LoadBitmaps(IDB_BMP_CANCEL, NULL, NULL, NULL);
	m_recancelbtn.SizeToContent(); 



	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
