// CalTimeGo.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "CalTimeGo.h"
#include "afxdialogex.h"


// CCalTimeGo 대화 상자입니다.

CFont font2, font3;

IMPLEMENT_DYNAMIC(CCalTimeGo, CDialogEx)

CCalTimeGo::CCalTimeGo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCalTimeGo::IDD, pParent)
	, m_goyear(_T(""))
	, m_gomonth(_T(""))
{

}

CCalTimeGo::~CCalTimeGo()
{
}

void CCalTimeGo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PREYEAR, m_goyear);
	DDX_Control(pDX, IDC_PREYEAR, m_goyear_Edit);
	DDX_Text(pDX, IDC_PREMONTH, m_gomonth);
	DDX_Control(pDX, IDC_PREMONTH, m_gomonth_Edit);
	DDX_Control(pDX, IDC_LAYEAR, m_layear);
	DDX_Control(pDX, IDC_LAMONTH, m_lamonth);
	DDX_Control(pDX, IDC_NEYEAR, m_neyear);
	DDX_Control(pDX, IDC_NEMONTH, m_nemonth);
}


BEGIN_MESSAGE_MAP(CCalTimeGo, CDialogEx)
	ON_STN_CLICKED(IDC_LAYEAR, &CCalTimeGo::OnStnClickedLayear)
	ON_STN_CLICKED(IDC_LAMONTH, &CCalTimeGo::OnStnClickedLamonth)
	ON_STN_CLICKED(IDC_NEYEAR, &CCalTimeGo::OnStnClickedNeyear)
	ON_STN_CLICKED(IDC_NEMONTH, &CCalTimeGo::OnStnClickedNemonth)
	ON_BN_CLICKED(IDOK, &CCalTimeGo::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCalTimeGo::OnBnClickedCancel)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CCalTimeGo 메시지 처리기입니다.


void CCalTimeGo::OnStnClickedLayear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;
	i = _ttoi(yearpre) - 1;
	yearpre.Format(_T("%d"),i);
	
	Invalidate();
}


void CCalTimeGo::OnStnClickedLamonth()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(_ttoi(monthpre) > 1){
	int i;
	i = _ttoi(monthpre) - 1;
	monthpre.Format(_T("%d"),i);
	
	Invalidate();
	} else{
		monthpre = _T("12");
		Invalidate();
	}
}


void CCalTimeGo::OnStnClickedNeyear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;
	i = _ttoi(yearpre) + 1;
	yearpre.Format(_T("%d"),i);
	
	Invalidate();
}


void CCalTimeGo::OnStnClickedNemonth()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(_ttoi(monthpre) <= 11){
	int i;
	i = _ttoi(monthpre) + 1;
	monthpre.Format(_T("%d"),i);
	Invalidate();
	}else{
		monthpre = _T("1");
		Invalidate();
	}
}


void CCalTimeGo::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	CDialogEx::OnOK();
}


void CCalTimeGo::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


BOOL CCalTimeGo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	        CTime timer;
		timer = CTime::GetCurrentTime();
	     // 현재 년월일 구하기
	      int goyear = timer.GetYear();



			font2.CreateFont(30,20,0,0, FW_NORMAL, FALSE, FALSE, 0,   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Consolas"));

			GetDlgItem(IDC_PREYEAR)->SetFont(&font2);
			GetDlgItem(IDC_PREMONTH)->SetFont(&font2);

			font3.CreateFont(25,30,0,0, FW_NORMAL, FALSE, FALSE, 0,   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("나눔바른고딕"));
			
			GetDlgItem(IDC_LAYEAR)->SetFont(&font3);
			GetDlgItem(IDC_LAMONTH)->SetFont(&font3);
			GetDlgItem(IDC_NEYEAR)->SetFont(&font3);
			GetDlgItem(IDC_NEMONTH)->SetFont(&font3);
			

			GetDlgItem(IDC_LAYEAR)->ModifyStyle (0, SS_NOTIFY);
			GetDlgItem(IDC_LAMONTH)->ModifyStyle (0, SS_NOTIFY);
			GetDlgItem(IDC_NEYEAR)->ModifyStyle (0, SS_NOTIFY);
			GetDlgItem(IDC_NEMONTH)->ModifyStyle (0, SS_NOTIFY);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CCalTimeGo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	m_goyear_Edit.SetWindowTextW(yearpre);
	m_gomonth_Edit.SetWindowTextW(monthpre);

	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
}


HBRUSH CCalTimeGo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	if (pWnd && *pWnd==m_layear)

    {
        pDC->SetTextColor(RGB(107,138,36));

    }

	if (pWnd && *pWnd==m_neyear)

    {
        pDC->SetTextColor(RGB(107,138,36));

    }

	if (pWnd && *pWnd==m_lamonth)

    {
        pDC->SetTextColor(RGB(107,138,36));

    }

	if (pWnd && *pWnd==m_nemonth)

    {
        pDC->SetTextColor(RGB(107,138,36));

    }

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL CCalTimeGo::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rt;
    GetClientRect(&rt);  // 클라이언트 영역의 크기 계산
	pDC->FillSolidRect(&rt, RGB(247, 246, 238));  

	return TRUE; 

	return CDialogEx::OnEraseBkgnd(pDC);
}
