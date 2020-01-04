// CompanyModifyPage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "CompanyModifyPage.h"
#include "afxdialogex.h"
#include "CompanySheet.h"

// CCompanyModifyPage 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCompanyModifyPage, CPropertyPage)

CCompanyModifyPage::CCompanyModifyPage()
	: CPropertyPage(CCompanyModifyPage::IDD)
	, m_cnumber(_T(""))
	, m_cname(_T(""))
	, m_ctype(_T(""))
	, m_cbusiness(_T(""))
	, m_ctel1(_T(""))
	, m_ctel2(_T(""))
	, m_caddress(_T(""))
	, m_cceoname(_T(""))
	, m_cemail(_T(""))
	, m_cmtel1(_T(""))
	, m_cmtel2(_T(""))
	, m_cmemo(_T(""))
{

}

CCompanyModifyPage::~CCompanyModifyPage()
{
}

void CCompanyModifyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CNUM, m_cnumber);
	DDX_Text(pDX, IDC_EDIT_CNAME, m_cname);
	DDX_Control(pDX, IDC_COMBO_SORT, m_csort);
	DDX_Text(pDX, IDC_EDIT_CBUS, m_ctype);
	DDX_Text(pDX, IDC_EDIT_CTYPE, m_cbusiness);
	DDX_Control(pDX, IDC_COMBO_TEL, m_ctel);
	DDX_Text(pDX, IDC_EDIT_TEL1, m_ctel1);
	DDX_Text(pDX, IDC_EDIT_TEL2, m_ctel2);
	DDX_Text(pDX, IDC_EDIT_ADDR, m_caddress);
	DDX_Text(pDX, IDC_EDIT_CCEO, m_cceoname);
	DDX_Text(pDX, IDC_EDIT_CEMAIL, m_cemail);
	DDX_Control(pDX, IDC_COMBO_MTEL, m_cmtel);
	DDX_Text(pDX, IDC_EDIT_MTEL1, m_cmtel1);
	DDX_Text(pDX, IDC_EDIT_MTEL2, m_cmtel2);
	DDX_Text(pDX, IDC_EDIT_MEMO, m_cmemo);
	DDX_Control(pDX, IDC_EDIT_CNUM, m_ccnuber_Edit);
	DDX_Control(pDX, IDC_EDIT_CNAME, m_cname_Edit);
	DDX_Control(pDX, IDC_EDIT_CBUS, m_ctype_Edit);
	DDX_Control(pDX, IDC_EDIT_CTYPE, m_cbusiness_Edit);
	DDX_Control(pDX, IDC_EDIT_ADDR, m_caddress_Edit);
	DDX_Control(pDX, IDC_EDIT_CCEO, m_cceoname_Edit);
	DDX_Control(pDX, IDC_EDIT_CEMAIL, m_cemail_Edit);
	DDX_Control(pDX, IDC_EDIT_MEMO, m_cmemo_Edit);
	DDX_Control(pDX, IDC_COM_SEARCH_BTN, m_comsearch_btn);
	DDX_Control(pDX, IDC_EDIT_TEL1, m_ctel1_Edit);
	DDX_Control(pDX, IDC_EDIT_TEL2, m_ctel2_Edit);
	DDX_Control(pDX, IDC_EDIT_MTEL1, m_cmtel1_Edit);
	DDX_Control(pDX, IDC_EDIT_MTEL2, m_cmtel2_Edit);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_cbirth);
	DDX_Control(pDX, IDC_BUTTON_CLEAR, m_clearbtn);
	DDX_Control(pDX, IDC_BUTTON_MODI, m_modifybtn);
	DDX_Control(pDX, IDCANCEL, m_cancelbtn);
}


BEGIN_MESSAGE_MAP(CCompanyModifyPage, CPropertyPage)
	ON_BN_CLICKED(IDC_COM_SEARCH_BTN, &CCompanyModifyPage::OnBnClickedComSearchBtn)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CCompanyModifyPage::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_MODI, &CCompanyModifyPage::OnBnClickedButtonModi)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCompanyModifyPage 메시지 처리기입니다.


void CCompanyModifyPage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CPropertyPage::OnPaint()을(를) 호출하지 마십시오.
	if(m_cnumber != g_set_cnumber)
	{
		//m_comsearch_btn.ShowWindow(SW_HIDE);//버튼 안보이게 하기 -> 문제점 : 버튼을 사용하면서 초기화가 안먹힌다!
		//m_ccode_edit.SetWindowTextW(g_set_ccode);
		m_ccnuber_Edit.SetWindowTextW(g_set_cnumber);
		m_cname_Edit.SetWindowTextW(g_set_cname);
		m_csort.SetCurSel(g_set_csortindex);
		m_ctype_Edit.SetWindowTextW(g_set_ctype);
		m_cbusiness_Edit.SetWindowTextW(g_set_cbusiness);
		m_ctel.SetCurSel(g_set_ctelindex);
		m_ctel1_Edit.SetWindowTextW(g_set_ctel1);
		m_ctel2_Edit.SetWindowTextW(g_set_ctel2);
		m_caddress_Edit.SetWindowTextW(g_set_caddress);
		m_cceoname_Edit.SetWindowTextW(g_set_cceoname);
		m_cemail_Edit.SetWindowTextW(g_set_cemail);
		//생일
		COleDateTime Date;   //사용자가 지정한 날짜를 저장할 ColeDateTimeDate 변수   
		CString wsYear = g_set_cbirth_Year;   //년
		CString wsMonth = g_set_cbirth_Month; //월
		CString wsDay = g_set_cbirth_Day;    //일
		Date.SetDate(_tstoi(wsYear),_tstoi(wsMonth),_tstoi(wsDay));
		//COleDateTime타입은 UpdateData해줘야함 그럼 나머지안먹힘
		//그래서 변수 지우고 다시 DateTime형식의 컨트롤로 다시만듬
		m_cbirth.SetTime(Date);
		
		m_cmtel.SetCurSel(g_set_cmtelindex);
		m_cmtel1_Edit.SetWindowTextW(g_set_cmtel1);
		m_cmtel2_Edit.SetWindowTextW(g_set_cmtel2);
		m_cmemo_Edit.SetWindowTextW(g_set_cmemo);
	}
}

void CCompanyModifyPage::OnBnClickedComSearchBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CCompanySheet* pSheet = (CCompanySheet*)GetParent();
	pSheet->SetActivePage(1);
}


BOOL CCompanyModifyPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_csort.SetCurSel(0);
	m_ctel.SetCurSel(0);
	m_cmtel.SetCurSel(0);
	m_comsearch_btn.LoadBitmaps(IDB_BMP_SEARCH2, NULL, NULL, NULL);
	m_comsearch_btn.SizeToContent();
	m_clearbtn.LoadBitmaps(IDB_BMP_CLEAR, NULL, NULL, NULL);
	m_clearbtn.SizeToContent();
	m_modifybtn.LoadBitmaps(IDB_BMP_OKSET, NULL, NULL, NULL);
	m_modifybtn.SizeToContent();
	m_cancelbtn.LoadBitmaps(IDB_BMP_CANCEL, NULL, NULL, NULL);
	m_cancelbtn.SizeToContent();

	CFont    m_fontTitle;
	LOGFONT  lf; 

	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 17;
	::lstrcpy(lf.lfFaceName, _T("나눔바른고딕"));
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
	GetDlgItem(IDC_STATIC13)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC14)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT_CNUM)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT_CNAME)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_COMBO_SORT)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT_CBUS)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT_CTYPE)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_COMBO_TEL)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT_TEL1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT_TEL2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT_ADDR)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT_CCEO)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT_CEMAIL)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_DATETIMEPICKER1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_COMBO_MTEL)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT_MTEL1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT_MTEL2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT_MEMO)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CCompanyModifyPage::OnBnClickedButtonClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		//m_comsearch_btn.ShowWindow(SW_SHOWNORMAL);
		m_cnumber = _T("");
		m_cname = _T("");
		m_csort.SetCurSel(0);
		m_ctype = _T("");
		m_cbusiness = _T("");
		m_ctel.SetCurSel(0);
		m_ctel1 = _T("");
		m_ctel2 = _T("");
		m_caddress = _T("");
		m_cceoname = _T("");
		m_cemail = _T("");
		m_cmtel.SetCurSel(0);
		m_cmtel1 = _T("");
		m_cmtel2 = _T("");
		m_cmemo = _T("");
		//생일초기화
		CDateTimeCtrl *pCtrl = (CDateTimeCtrl *) GetDlgItem(IDC_DATETIMEPICKER1);
		CTime tm = CTime::GetCurrentTime();
		pCtrl->SetTime(&tm);
		UpdateData(false);
}


void CCompanyModifyPage::OnBnClickedButtonModi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if(m_cnumber!=""&&m_cname!=""&&m_cbusiness!=""&&m_ctype!=""&&m_ctel1!=""&&m_ctel2!=""&&m_caddress!=""&&m_cceoname!=""&&m_cemail!=""&&m_cmtel1!=""&&m_cmtel2!=""&&m_cmemo!=""){
		
		int nIndex;
		CString s;
		CString strSort;
		CString strCTel;
		CString strCEOTel;
		COleDateTime selectDate;
		m_cbirth.GetTime(selectDate);    //datetimepicker 컨트롤 변수
		CString sdate = selectDate.Format(_T("%Y-%m-%d"));
		
		nIndex = m_csort.GetCurSel();
		if(nIndex == -1)
			return;
		m_csort.GetLBText(nIndex, strSort);	

		nIndex = m_ctel.GetCurSel();
		if(nIndex == -1)
			return;		
		m_ctel.GetLBText(nIndex, s);
		strCTel.Format(_T("%s-%s-%s"),s, m_ctel1, m_ctel2);

		nIndex = m_cmtel.GetCurSel();
		if(nIndex == -1)
			return;		
		m_cmtel.GetLBText(nIndex, s);
		strCEOTel.Format(_T("%s-%s-%s"),s, m_cmtel1, m_cmtel2);

		CDatabase db;			// 데이터베이스 객체 생성
		CRecordset rs (&db);	// 레코드셋 객체 생성
		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");	//DB오픈
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("데이터베이스 접속실패!");

			CString strQuery;	//데이터베이스에 전송할 쿼리문
			strQuery.Format(_T("UPDATE Company SET c_name='%s', c_sort='%s', c_type='%s', c_business='%s', c_ceoname='%s', c_tel='%s', \
							   c_number='%s', c_address='%s', c_mobile='%s', c_email='%s', c_birth='%s',c_memo='%s',com_id='%s' WHERE c_name='%s'"),
							    m_cname, strSort, m_ctype, m_cbusiness, m_cceoname, strCTel, m_cnumber, m_caddress, strCEOTel, m_cemail, sdate, m_cmemo, g_setid, m_cname);

			db.ExecuteSQL(strQuery);	//데이터베이스에 쿼리문 전송
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
		MessageBox(_T("성공적으로 수정되었습니다."));
		//OnBnClickedButtonComClear();	//컨트롤 초기화

		rs.Close();	//레코드셋 객체 소멸
		db.Close();	//데이터베이스 객체 소멸
	}else MessageBox(_T("입력되지 않은 값이 있습니다.\n모든 값을 입력(선택)해주세요."));
	
		m_cnumber = _T("");
		m_cname = _T("");
		m_csort.SetCurSel(0);
		m_ctype = _T("");
		m_cbusiness = _T("");
		m_ctel.SetCurSel(0);
		m_ctel1 = _T("");
		m_ctel2 = _T("");
		m_caddress = _T("");
		m_cceoname = _T("");
		m_cemail = _T("");
		m_cmtel.SetCurSel(0);
		m_cmtel1 = _T("");
		m_cmtel2 = _T("");
		m_cmemo = _T("");
		//생일초기화
		CDateTimeCtrl *pCtrl = (CDateTimeCtrl *) GetDlgItem(IDC_DATETIMEPICKER1);
		CTime tm = CTime::GetCurrentTime();
		pCtrl->SetTime(&tm);
		UpdateData(false);
}


HBRUSH CCompanyModifyPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	/*
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_CNUM)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_CNAME)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_CBUS)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_CTYPE)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_TEL1)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_TEL2)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_ADDR)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_CCEO)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_CEMAIL)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_MTEL1)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_MTEL2)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT_MEMO)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	*/
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
