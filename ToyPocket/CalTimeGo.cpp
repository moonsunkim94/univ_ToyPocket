// CalTimeGo.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "CalTimeGo.h"
#include "afxdialogex.h"


// CCalTimeGo ��ȭ �����Դϴ�.

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


// CCalTimeGo �޽��� ó�����Դϴ�.


void CCalTimeGo::OnStnClickedLayear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int i;
	i = _ttoi(yearpre) - 1;
	yearpre.Format(_T("%d"),i);
	
	Invalidate();
}


void CCalTimeGo::OnStnClickedLamonth()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int i;
	i = _ttoi(yearpre) + 1;
	yearpre.Format(_T("%d"),i);
	
	Invalidate();
}


void CCalTimeGo::OnStnClickedNemonth()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();
	CDialogEx::OnOK();
}


void CCalTimeGo::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}


BOOL CCalTimeGo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	        CTime timer;
		timer = CTime::GetCurrentTime();
	     // ���� ����� ���ϱ�
	      int goyear = timer.GetYear();



			font2.CreateFont(30,20,0,0, FW_NORMAL, FALSE, FALSE, 0,   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Consolas"));

			GetDlgItem(IDC_PREYEAR)->SetFont(&font2);
			GetDlgItem(IDC_PREMONTH)->SetFont(&font2);

			font3.CreateFont(25,30,0,0, FW_NORMAL, FALSE, FALSE, 0,   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("�����ٸ����"));
			
			GetDlgItem(IDC_LAYEAR)->SetFont(&font3);
			GetDlgItem(IDC_LAMONTH)->SetFont(&font3);
			GetDlgItem(IDC_NEYEAR)->SetFont(&font3);
			GetDlgItem(IDC_NEMONTH)->SetFont(&font3);
			

			GetDlgItem(IDC_LAYEAR)->ModifyStyle (0, SS_NOTIFY);
			GetDlgItem(IDC_LAMONTH)->ModifyStyle (0, SS_NOTIFY);
			GetDlgItem(IDC_NEYEAR)->ModifyStyle (0, SS_NOTIFY);
			GetDlgItem(IDC_NEMONTH)->ModifyStyle (0, SS_NOTIFY);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CCalTimeGo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	m_goyear_Edit.SetWindowTextW(yearpre);
	m_gomonth_Edit.SetWindowTextW(monthpre);

	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
}


HBRUSH CCalTimeGo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.

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

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}


BOOL CCalTimeGo::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CRect rt;
    GetClientRect(&rt);  // Ŭ���̾�Ʈ ������ ũ�� ���
	pDC->FillSolidRect(&rt, RGB(247, 246, 238));  

	return TRUE; 

	return CDialogEx::OnEraseBkgnd(pDC);
}
