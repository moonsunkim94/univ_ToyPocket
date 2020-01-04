// CompanyPage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "CompanyPage.h"
#include "afxdialogex.h"


// CCompanyPage 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCompanyPage, CPropertyPage)

CCompanyPage::CCompanyPage()
	: CPropertyPage(CCompanyPage::IDD)
	, m_cnumber(_T(""))
	, m_cname(_T(""))
	, m_cbusiness(_T(""))
	, m_ctype(_T(""))
	, m_ctel1(_T(""))
	, m_ctel2(_T(""))
	, m_caddress(_T(""))
	, m_cceoname(_T(""))
	, m_cemail(_T(""))
	, m_cbirth(COleDateTime::GetCurrentTime())
	, m_cmtel1(_T(""))
	, m_cmtel2(_T(""))
	, m_cmemo(_T(""))
{

}

CCompanyPage::~CCompanyPage()
{
}

void CCompanyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CNUM, m_cnumber);
	DDX_Text(pDX, IDC_EDIT_CNAME, m_cname);
	DDX_Control(pDX, IDC_COMBO_SORT, m_csort);
	DDX_Text(pDX, IDC_EDIT_CBUS, m_cbusiness);
	DDX_Text(pDX, IDC_EDIT_CTYPE, m_ctype);
	DDX_Control(pDX, IDC_COMBO_TEL, m_ctel);
	DDX_Text(pDX, IDC_EDIT_TEL1, m_ctel1);
	DDX_Text(pDX, IDC_EDIT_TEL2, m_ctel2);
	DDX_Text(pDX, IDC_EDIT_ADDR, m_caddress);
	DDX_Text(pDX, IDC_EDIT_CCEO, m_cceoname);
	DDX_Text(pDX, IDC_EDIT_CEMAIL, m_cemail);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_cbirth);
	DDX_Control(pDX, IDC_COMBO_MTEL, m_cmtel);
	DDX_Text(pDX, IDC_EDIT_MTEL1, m_cmtel1);
	DDX_Text(pDX, IDC_EDIT_MTEL2, m_cmtel2);
	DDX_Text(pDX, IDC_EDIT_MEMO, m_cmemo);
	DDX_Control(pDX, IDOK, m_okbtn);
	DDX_Control(pDX, IDCANCEL, m_cancelbtn);
}


BEGIN_MESSAGE_MAP(CCompanyPage, CPropertyPage)
	ON_BN_CLICKED(IDOK, &CCompanyPage::OnBnClickedComAdd)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCompanyPage 메시지 처리기입니다.

#include "CompanySheet.h"
void CCompanyPage::OnBnClickedComAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if(m_cnumber!=""&&m_cname!=""&&m_cbusiness!=""&&m_ctype!=""&&m_ctel1!=""&&m_ctel2!=""&&m_caddress!=""&&m_cceoname!=""&&m_cemail!=""&&m_cmtel1!=""&&m_cmtel2!=""&&m_cmemo!=""){
		//m_ccode!=""&&m_cnumber!=""&&m_cname!=""&&m_cbusiness!=""&&m_ctype!=""&&m_ctel1!=""&&m_ctel2!=""&&m_caddress!=""&&m_cceoname!=""&&m_cemail!=""&&m_cmtel1!=""&&m_cmtel2!=""&&m_cmemo!=""

		int nIndex;
		CString s;
		CString strSort;
		CString strCTel;
		CString strCEOTel;
		CString sdate;
		CString tmp;
		sdate.Format(_T("%d-%02d-%02d"),m_cbirth.GetYear(),m_cbirth.GetMonth(),m_cbirth.GetDay());

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


		
		
	CDatabase db0;			// 데이터베이스 객체 생성
	CRecordset rs0 (&db0);	// 레코드셋 객체 생성
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db0.OpenEx (strConnection) == FALSE)
			  throw _T("데이터베이스 접속실패!");

		CString strQuery;
			
		 nIndex = m_csort.GetCurSel();
		if(nIndex == 0){
			strQuery.Format(_T("SELECT c_code FROM Company WHERE c_code LIKE '%%IC%%'  ORDER BY c_code ASC"));
		}
		if(nIndex == 1){
			strQuery.Format(_T("SELECT c_code FROM Company WHERE c_code LIKE '%%OC%%' ORDER BY c_code ASC"));
		}

		if (rs0.Open (CRecordset::snapshot, strQuery) == FALSE)	
			throw _T("쿼리전송 실패!");
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

	short col = rs0.GetODBCFieldCount();			//쿼리문을 이용해 검색한 내용 리스트 컨트롤에 출력
	for(int p=0 ; p<2 ; p++)
	{
		 while( ! rs0.IsEOF())
		 {
			 
			 rs0.GetFieldValue((short)p, tmp);  
			 
			 for(short i=1; i<col; i++  )
			 {
				 
				rs0.GetFieldValue(i, tmp);
				
			}
			rs0.MoveNext(); 
			
 		 }
	}
	rs0.Close();
	db0.Close();

	lastint=tmp.Right(2);
	length = lastint.GetLength();
	 nIndex = m_csort.GetCurSel();
		if(nIndex == 0){//CSORT인덱스
			result.Format(_T("IC_%04d"),_ttoi(lastint)+1);
			/*
			if(length == 1)
				result.Format(_T("IC_%04d"),_ttoi(lastint)+1);
			else
				result.Format(_T("IC_%03d"),_ttoi(lastint)+1);
				*/
		}
		else if(nIndex == 1){
			result.Format(_T("OC_%04d"),_ttoi(lastint)+1);
			/*
			if(length == 1)
				result.Format(_T("OC_%04d"),_ttoi(lastint));
			else
				result.Format(_T("OC_%03d"),_ttoi(lastint)+1);3
			*/
		}

		CDatabase db;			// 데이터베이스 객체 생성
		CRecordset rs (&db);	// 레코드셋 객체 생성
		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");	//DB오픈
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("데이터베이스 접속실패!");


			CString strQuery;	//데이터베이스에 전송할 쿼리문
			strQuery.Format(_T("INSERT INTO Company VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')"), 
				result, m_cname, strSort, m_ctype, m_cbusiness,  m_cceoname, strCTel, m_cnumber,  m_caddress, strCEOTel, m_cemail, sdate, m_cmemo, g_setid);

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
		MessageBox(_T("성공적으로 추가되었습니다."));
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
	
		CCompanySheet* pSheet = (CCompanySheet*)GetParent();
	    CCompanySearchPage* pPage = (CCompanySearchPage*)(pSheet->GetPage(1));
	    pPage->ReInitDialog();

}


BOOL CCompanyPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_csort.SetCurSel(0);
	m_ctel.SetCurSel(0);
	m_cmtel.SetCurSel(0);

	m_okbtn.LoadBitmaps(IDB_BMP_OK,NULL,NULL,NULL);
	m_okbtn.SizeToContent();
	m_cancelbtn.LoadBitmaps(IDB_BMP_CANCEL,NULL,NULL,NULL);
	m_cancelbtn.SizeToContent();

	
	HCURSOR hCursor;
	hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
	SetClassLong(m_okbtn.GetSafeHwnd(),GCL_HCURSOR,(LONG)hCursor);
	
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


HBRUSH CCompanyPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	/*
	if (pWnd->GetDlgCtrlID() == IDC_EDIT7)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	*/
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
