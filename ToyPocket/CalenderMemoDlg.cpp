// CalenderMemoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "CalenderMemoDlg.h"
#include "afxdialogex.h"
#include "CalendarSet.h"

CFont font19;

// CCalenderMemoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCalenderMemoDlg, CDialogEx)

CCalenderMemoDlg::CCalenderMemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCalenderMemoDlg::IDD, pParent)
	, m_memo(_T(""))
	, m_memo2(_T(""))
	, m_memo3(_T(""))
	, m_memo4(_T(""))
	, m_check1(FALSE)
	, m_check2(FALSE)
	, m_check3(FALSE)
	, m_check4(FALSE)
	, m_day(_T(""))
{

}

CCalenderMemoDlg::~CCalenderMemoDlg()
{
}

void CCalenderMemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_calmemo);
	DDX_Text(pDX, IDC_EDIT1, m_memo);
	DDX_Text(pDX, IDC_EDIT2, m_memo2);
	DDX_Text(pDX, IDC_EDIT3, m_memo3);
	DDX_Text(pDX, IDC_EDIT4, m_memo4);
	DDX_Check(pDX, IDC_CHECK1, m_check1);
	DDX_Check(pDX, IDC_CHECK4, m_check2);
	DDX_Check(pDX, IDC_CHECK5, m_check3);
	DDX_Check(pDX, IDC_CHECK6, m_check4);
	DDX_Control(pDX, IDC_EDIT2, m_calmemo2);
	DDX_Control(pDX, IDC_EDIT3, m_calmemo3);
	DDX_Control(pDX, IDC_EDIT4, m_calmemo4);
	DDX_Control(pDX, IDC_CHECK1, m_calcheck);
	DDX_Control(pDX, IDC_CHECK4, m_calcheck2);
	DDX_Control(pDX, IDC_CHECK5, m_calcheck3);
	DDX_Control(pDX, IDC_CHECK6, m_calcheck4);
	DDX_Control(pDX, IDC_DAY, m_preday);
	DDX_Text(pDX, IDC_DAY, m_day);
}


BEGIN_MESSAGE_MAP(CCalenderMemoDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCalenderMemoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCalenderMemoDlg::OnBnClickedCancel)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CCalenderMemoDlg 메시지 처리기입니다.



void CCalenderMemoDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	CDialogEx::OnOK();
}


void CCalenderMemoDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


BOOL CCalenderMemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	                 CString str;
					 str.Format(_T("%d"),daypre);
					 m_preday.SetWindowTextW(str);

					 UpdateData(TRUE);

	                 CCalendarSet cal;
	                 cal.Open();
					 while(!cal.IsEOF()){
						 if((week == cal.m_week) && (day == cal.m_day) && (_ttoi(yearpre) == cal.m_preyear) && (_ttoi(monthpre) == cal.m_premonth)){

						 m_calmemo.SetWindowTextW(cal.m_memo);
						 m_calmemo2.SetWindowTextW(cal.m_memo2);
						 m_calmemo3.SetWindowTextW(cal.m_memo3);
						 m_calmemo4.SetWindowTextW(cal.m_memo4);

						 m_calcheck.SetCheck(cal.m_check);
						 m_calcheck2.SetCheck(cal.m_check2);
						 m_calcheck3.SetCheck(cal.m_check3);
						 m_calcheck4.SetCheck(cal.m_check4);

						 break;
					 }
					 cal.MoveNext();
				   }
					cal.MoveLast();


			font19.CreateFont(20,15,0,0, FW_NORMAL, FALSE, FALSE, 0,   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("나눔바른고딕"));

			GetDlgItem(IDC_EDIT1)->SetFont(&font19);
            GetDlgItem(IDC_EDIT2)->SetFont(&font19);
			GetDlgItem(IDC_EDIT3)->SetFont(&font19);
			GetDlgItem(IDC_EDIT4)->SetFont(&font19);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CCalenderMemoDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CFont font4,font5;
	font4.CreateFont(30,20,0,0, FW_NORMAL, FALSE, FALSE, 0,   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Consolas"));
	font5.CreateFont(20,15,0,0, FW_NORMAL, FALSE, FALSE, 0,   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("나눔바른고딕"));
	GetDlgItem(IDC_DAY)->SetFont(&font4);
    GetDlgItem(IDC_DAYSTATIC)->SetFont(&font5);

	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
}


BOOL CCalenderMemoDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rt;
    GetClientRect(&rt);  // 클라이언트 영역의 크기 계산
	pDC->FillSolidRect(&rt, RGB(247, 246, 238));  

	return TRUE; 
	return CDialogEx::OnEraseBkgnd(pDC);
}
