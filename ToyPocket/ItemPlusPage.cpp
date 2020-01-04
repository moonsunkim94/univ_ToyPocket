// ItemPlusPage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ItemPlusPage.h"
#include "afxdialogex.h"
#include "ItemSearchDlg.h"

// CItemPlusPage ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CItemPlusPage, CPropertyPage)

CItemPlusPage::CItemPlusPage()
	: CPropertyPage(CItemPlusPage::IDD)
	, m_iplus_amount(_T(""))
	, m_inamount(_T(""))
	, m_iname(_T(""))
{

}

CItemPlusPage::~CItemPlusPage()
{
}

void CItemPlusPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INAME, m_iname_Edit);
	DDX_Control(pDX, IDC_ICODE, m_icode_Edit);
	DDX_Control(pDX, IDC_CNAME, m_cname_Edit);
	DDX_Control(pDX, IDC_CCODE, m_ccode_Edit);
	DDX_Control(pDX, IDC_FIRST, m_first);
	DDX_Control(pDX, IDC_SECOND, m_second);
	DDX_Control(pDX, IDC_THIRD, m_third);
	DDX_Control(pDX, IDC_INPRICE, m_inprice_Edit);
	DDX_Control(pDX, IDC_OUTPRICE, m_outprice_Edit);
	DDX_Control(pDX, IDC_INDATE, m_date);
	DDX_Control(pDX, IDC_INAMOUNT, m_inamount_Edit);
	DDX_Text(pDX, IDC_INADDAMOUNT, m_iplus_amount);
	DDX_Text(pDX, IDC_INAMOUNT, m_inamount);
	DDX_Text(pDX, IDC_INAME, m_iname);
	DDX_Control(pDX, IDC_BUTTON1, m_isearchbtn);
	DDX_Control(pDX, IDOK, m_addbtn);
	DDX_Control(pDX, IDCANCEL, m_cancelbtn);
}


BEGIN_MESSAGE_MAP(CItemPlusPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &CItemPlusPage::OnBnClickedSearchButton)
	ON_BN_CLICKED(IDOK, &CItemPlusPage::OnBnClickedItemPlus)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CItemPlusPage �޽��� ó�����Դϴ�.


BOOL CItemPlusPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_isearchbtn.LoadBitmaps(IDB_BMP_SEARCH2, NULL, NULL, NULL);
	m_isearchbtn.SizeToContent();
	m_addbtn.LoadBitmaps(IDB_BMP_OKSET, NULL, NULL, NULL);
	m_addbtn.SizeToContent();
	m_cancelbtn.LoadBitmaps(IDB_BMP_CANCEL, NULL, NULL, NULL);
	m_cancelbtn.SizeToContent();

	GetDlgItem(IDC_INAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_ICODE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_CCODE)->EnableWindow(FALSE);
	GetDlgItem(IDC_INPRICE)->EnableWindow(FALSE);
	GetDlgItem(IDC_OUTPRICE)->EnableWindow(FALSE);
	GetDlgItem(IDC_INAMOUNT)->EnableWindow(FALSE);
	GetDlgItem(IDC_FIRST)->EnableWindow(FALSE);
	GetDlgItem(IDC_SECOND)->EnableWindow(FALSE);
	GetDlgItem(IDC_THIRD)->EnableWindow(FALSE);
	GetDlgItem(IDC_INDATE)->EnableWindow(FALSE);

	CFont    m_fontTitle;
	LOGFONT  lf; 

	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 17;
	::lstrcpy(lf.lfFaceName, _T("�����ٸ����"));
	m_fontTitle.CreateFontIndirect(&lf);
	GetDlgItem(IDC_STATIC1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC3)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC4)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC5)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC6)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC7)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC8)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC9)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC10)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC11)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC12)->SetFont(&m_fontTitle);
	
	GetDlgItem(IDC_INAME)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_ICODE)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_CNAME)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_CCODE)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_FIRST)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_SECOND)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_THIRD)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_INPRICE)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_OUTPRICE)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_INDATE)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_INAMOUNT)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_INADDAMOUNT)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CItemPlusPage::OnBnClickedSearchButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CItemSearchDlg pDlg;
	pDlg.DoModal();
	m_iname_Edit.SetWindowTextW(pDlg.m_iname);
	m_icode_Edit.SetWindowTextW(pDlg.m_icode);
	m_cname_Edit.SetWindowTextW(pDlg.m_cname);
	m_ccode_Edit.SetWindowTextW(pDlg.m_ccode);
	m_inprice_Edit.SetWindowTextW(pDlg.m_inprice);
	m_outprice_Edit.SetWindowTextW(pDlg.m_outprice);
	m_inamount_Edit.SetWindowTextW(pDlg.m_inamount);
	m_first.SetWindowTextW(pDlg.m_combo1);
	m_second.SetWindowTextW(pDlg.m_combo2);
	m_third.SetWindowTextW(pDlg.m_combo3);
	m_date.SetWindowTextW(pDlg.m_inDate);
}


void CItemPlusPage::OnBnClickedItemPlus()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	if(m_iname!=""){
	
		CString m_icount;
		m_icount.Format(_T("%d"),_ttoi(m_iplus_amount) + _ttoi(m_inamount));

		CDatabase db;			// �����ͺ��̽� ��ü ����
		CRecordset rs (&db);	// ���ڵ�� ��ü ����
		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");	//DB����
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("�����ͺ��̽� ���ӽ���!");

			CString strQuery;	//�����ͺ��̽��� ������ ������
			strQuery.Format(_T("UPDATE Item SET i_inputAmount='%s' WHERE i_name='%s'"),
				 m_icount, m_iname);

			db.ExecuteSQL(strQuery);	//�����ͺ��̽��� ������ ����
		}
		catch (CException * e)
		{
			e->ReportError();
			e->Delete();
		}
		catch (LPCTSTR msg)
		{
			AfxMessageBox (msg);
		}
		MessageBox(_T("���������� �߰��Ǿ����ϴ�."));
		//OnBnClickedButtonComClear();	//��Ʈ�� �ʱ�ȭ

		rs.Close();	//���ڵ�� ��ü �Ҹ�
		db.Close();	//�����ͺ��̽� ��ü �Ҹ�
	}else MessageBox(_T("�Էµ��� ���� ���� �ֽ��ϴ�.\n��� ���� �Է�(����)���ּ���."));
	
	m_icode_Edit.SetWindowTextW(_T(""));
	m_cname_Edit.SetWindowTextW(_T(""));
	m_ccode_Edit.SetWindowTextW(_T(""));
	m_first.SetWindowTextW(_T(""));
	m_second.SetWindowTextW(_T(""));
	m_third.SetWindowTextW(_T(""));
	m_inprice_Edit.SetWindowTextW(_T(""));
	m_outprice_Edit.SetWindowTextW(_T(""));
	m_date.SetWindowTextW(_T(""));
	m_iplus_amount = _T("");
	m_inamount = _T("");
	m_iname = _T("");
	UpdateData(false);
}


void CItemPlusPage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	CPen pen1(PS_SOLID, 1, RGB(189,189,189)); 
	CPen * oldpen; 
	dc.SelectObject(&pen1);

	dc.MoveTo(25,270);
	dc.LineTo(900,270);

    dc.SelectObject(oldpen);

    pen1.DeleteObject();
	// �׸��� �޽����� ���ؼ��� CPropertyPage::OnPaint()��(��) ȣ������ ���ʽÿ�.
}
