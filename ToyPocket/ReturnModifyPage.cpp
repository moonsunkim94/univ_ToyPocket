// ReturnModifyPage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ReturnModifyPage.h"
#include "afxdialogex.h"


// CReturnModifyPage ��ȭ �����Դϴ�.

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


// CReturnModifyPage �޽��� ó�����Դϴ�.


BOOL CReturnModifyPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_researchbtn.LoadBitmaps(IDB_BMP_SEARCH, NULL, NULL, NULL);
	m_researchbtn.SizeToContent(); 

	m_resetokbtn.LoadBitmaps(IDB_BMP_OKSET, NULL, NULL, NULL);
	m_resetokbtn.SizeToContent();

	m_recancelbtn.LoadBitmaps(IDB_BMP_CANCEL, NULL, NULL, NULL);
	m_recancelbtn.SizeToContent(); 



	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
