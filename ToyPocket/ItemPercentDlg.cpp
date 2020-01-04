// ItemPercentDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ItemPercentDlg.h"
#include "afxdialogex.h"


// CItemPercentDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CItemPercentDlg, CDialogEx)

CItemPercentDlg::CItemPercentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CItemPercentDlg::IDD, pParent)
	, m_percent(_T(""))
{

}

CItemPercentDlg::~CItemPercentDlg()
{
}

void CItemPercentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_percent);
	DDX_Control(pDX, IDOK, m_setbtn);
	DDX_Control(pDX, IDCANCEL, m_cancelbtn);
}


BEGIN_MESSAGE_MAP(CItemPercentDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CItemPercentDlg::OnBnClickedPercent)
	ON_BN_CLICKED(IDCANCEL, &CItemPercentDlg::OnBnClickedCancel)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CItemPercentDlg �޽��� ó�����Դϴ�.


void CItemPercentDlg::OnBnClickedPercent()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();
	//CItemPercentDlg::SendMessage(WM_CLOSE);
	CDialogEx::OnOK();
}


void CItemPercentDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}


BOOL CItemPercentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_setbtn.LoadBitmaps(IDB_BMP_OKSET, NULL, NULL, NULL);
	m_setbtn.SizeToContent();
	m_cancelbtn.LoadBitmaps(IDB_BMP_CANCEL, NULL, NULL, NULL);
	m_cancelbtn.SizeToContent();
	
	CFont    m_fontTitle;
	LOGFONT  lf; 

	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 17;
	::lstrcpy(lf.lfFaceName, _T("�����ٸ����"));
	m_fontTitle.CreateFontIndirect(&lf);
	GetDlgItem(IDC_STATIC)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT1)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


BOOL CItemPercentDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CRect rt;
    GetClientRect(&rt);  // Ŭ���̾�Ʈ ������ ũ�� ���
	pDC->FillSolidRect(&rt, RGB(247, 246, 238));  

	return TRUE; 

	return CDialogEx::OnEraseBkgnd(pDC);
}
