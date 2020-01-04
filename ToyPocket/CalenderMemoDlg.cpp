// CalenderMemoDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "CalenderMemoDlg.h"
#include "afxdialogex.h"
#include "CalendarSet.h"

CFont font19;

// CCalenderMemoDlg ��ȭ �����Դϴ�.

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


// CCalenderMemoDlg �޽��� ó�����Դϴ�.



void CCalenderMemoDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();
	CDialogEx::OnOK();
}


void CCalenderMemoDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}


BOOL CCalenderMemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

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
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("�����ٸ����"));

			GetDlgItem(IDC_EDIT1)->SetFont(&font19);
            GetDlgItem(IDC_EDIT2)->SetFont(&font19);
			GetDlgItem(IDC_EDIT3)->SetFont(&font19);
			GetDlgItem(IDC_EDIT4)->SetFont(&font19);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CCalenderMemoDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	CFont font4,font5;
	font4.CreateFont(30,20,0,0, FW_NORMAL, FALSE, FALSE, 0,   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Consolas"));
	font5.CreateFont(20,15,0,0, FW_NORMAL, FALSE, FALSE, 0,   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("�����ٸ����"));
	GetDlgItem(IDC_DAY)->SetFont(&font4);
    GetDlgItem(IDC_DAYSTATIC)->SetFont(&font5);

	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
}


BOOL CCalenderMemoDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rt;
    GetClientRect(&rt);  // Ŭ���̾�Ʈ ������ ũ�� ���
	pDC->FillSolidRect(&rt, RGB(247, 246, 238));  

	return TRUE; 
	return CDialogEx::OnEraseBkgnd(pDC);
}
