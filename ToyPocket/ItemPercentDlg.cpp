// ItemPercentDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ItemPercentDlg.h"
#include "afxdialogex.h"


// CItemPercentDlg 대화 상자입니다.

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


// CItemPercentDlg 메시지 처리기입니다.


void CItemPercentDlg::OnBnClickedPercent()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	//CItemPercentDlg::SendMessage(WM_CLOSE);
	CDialogEx::OnOK();
}


void CItemPercentDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


BOOL CItemPercentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_setbtn.LoadBitmaps(IDB_BMP_OKSET, NULL, NULL, NULL);
	m_setbtn.SizeToContent();
	m_cancelbtn.LoadBitmaps(IDB_BMP_CANCEL, NULL, NULL, NULL);
	m_cancelbtn.SizeToContent();
	
	CFont    m_fontTitle;
	LOGFONT  lf; 

	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 17;
	::lstrcpy(lf.lfFaceName, _T("나눔바른고딕"));
	m_fontTitle.CreateFontIndirect(&lf);
	GetDlgItem(IDC_STATIC)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT1)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CItemPercentDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rt;
    GetClientRect(&rt);  // 클라이언트 영역의 크기 계산
	pDC->FillSolidRect(&rt, RGB(247, 246, 238));  

	return TRUE; 

	return CDialogEx::OnEraseBkgnd(pDC);
}
