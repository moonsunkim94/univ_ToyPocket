// RegisterFormView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "RegisterFormView.h"
#include "MainFrm.h"

// CRegisterFormView

IMPLEMENT_DYNCREATE(CRegisterFormView, CFormView)

CRegisterFormView::CRegisterFormView()
	: CFormView(CRegisterFormView::IDD)
	, m_strName(_T(""))
	, m_loginpwd(_T(""))
	, m_loginpwd2(_T(""))
	, m_userEmail(_T(""))
	, m_userBirth(COleDateTime::GetCurrentTime())
	, m_userName(_T(""))
{

}

CRegisterFormView::~CRegisterFormView()
{
}

void CRegisterFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_strName);
	DDV_MaxChars(pDX, m_strName, 20);
	DDX_Text(pDX, IDC_EDIT1, m_loginpwd);
	DDV_MaxChars(pDX, m_loginpwd, 20);
	DDX_Text(pDX, IDC_EDIT3, m_loginpwd2);
	DDX_Text(pDX, IDC_EDIT4, m_userEmail);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_userBirth);
	DDX_Control(pDX, IDC_EDIT2, m_strName_Edit);
	DDX_Control(pDX, IDC_EDIT1, m_loginpwd_Edit);
	DDX_Control(pDX, IDC_BUTTON2, m_registerbtn);
	DDX_Control(pDX, IDC_BUTTON1, m_cancelbtn);
	DDX_Text(pDX, IDC_EDIT14, m_userName);
}

BEGIN_MESSAGE_MAP(CRegisterFormView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CRegisterFormView::OnBnClickedRegister)
	ON_BN_CLICKED(IDC_BUTTON1, &CRegisterFormView::OnBnClickedCancle)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CRegisterFormView 진단입니다.

#ifdef _DEBUG
void CRegisterFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CRegisterFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRegisterFormView 메시지 처리기입니다.


void CRegisterFormView::OnBnClickedRegister()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if(m_strName!=""&&m_loginpwd!=""&&m_loginpwd2!=""&&m_userName!=""&&m_userEmail){
		
		CString s;
		CString sdate;
		sdate.Format(_T("%d-%02d-%02d"),m_userBirth.GetYear(),m_userBirth.GetMonth(),m_userBirth.GetDay());

		CDatabase db;			// 데이터베이스 객체 생성
		CRecordset rs (&db);	// 레코드셋 객체 생성
		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");	//DB오픈
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("데이터베이스 접속실패!");

			CString strQuery;	//데이터베이스에 전송할 쿼리문
			strQuery.Format(_T("INSERT INTO UserData VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s')"), 
				m_strName, m_loginpwd, m_userName, sdate, m_userEmail, _T("예"), _T("manager") );
			
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
		UpdateData(false);

		AfxMessageBox(_T("가입완료!"));

		CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
		pFrame->SwitchView(VIEWID_HOME);
}


void CRegisterFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	
	m_registerbtn.LoadBitmaps(IDB_BMP_REGISTER2, NULL, NULL, NULL);
	m_registerbtn.SizeToContent();	
	m_cancelbtn.LoadBitmaps(IDB_BMP_CANCEL, NULL, NULL, NULL);
	m_cancelbtn.SizeToContent();	
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	sql="select * from UserData";

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
	GetDlgItem(IDC_EDIT1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT3)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_DATETIMEPICKER1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT4)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT14)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 

}


void CRegisterFormView::OnBnClickedCancle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SwitchView(VIEWID_HOME);
}


BOOL CRegisterFormView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rt;
    GetClientRect(&rt);  // 클라이언트 영역의 크기 계산
	pDC->FillSolidRect(&rt, RGB(255, 255, 255));  

	return TRUE; 
	//return CFormView::OnEraseBkgnd(pDC);
}


HBRUSH CRegisterFormView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	UINT nID = pWnd->GetDlgCtrlID();			//컨트롤 핸들과 비교하기 위한 변수
 
   if(nID==IDC_STATIC1)							// 스태틱 컨트롤일때
    {    
        pDC->SetBkMode(TRANSPARENT);                              
        return (HBRUSH)::GetStockObject(NULL_BRUSH);                      
    }
	 if(nID==IDC_STATIC2)							// 스태틱 컨트롤일때
    {    
        pDC->SetBkMode(TRANSPARENT);                              
        return (HBRUSH)::GetStockObject(NULL_BRUSH);                      
    }
	  if(nID==IDC_STATIC3)							// 스태틱 컨트롤일때
    {    
        pDC->SetBkMode(TRANSPARENT);                              
        return (HBRUSH)::GetStockObject(NULL_BRUSH);                      
    }
	   if(nID==IDC_STATIC4)							// 스태틱 컨트롤일때
    {    
        pDC->SetBkMode(TRANSPARENT);                              
        return (HBRUSH)::GetStockObject(NULL_BRUSH);                      
    }
	    if(nID==IDC_STATIC5)							// 스태틱 컨트롤일때
    {    
        pDC->SetBkMode(TRANSPARENT);                              
        return (HBRUSH)::GetStockObject(NULL_BRUSH);                      
    }
		 if(nID==IDC_STATIC6)							// 스태틱 컨트롤일때
    {    
        pDC->SetBkMode(TRANSPARENT);                              
        return (HBRUSH)::GetStockObject(NULL_BRUSH);                      
    }

	///////////////
	if ( pWnd->GetDlgCtrlID() == IDC_EDIT2 )
    {
        pDC->SetBkColor( RGB(252, 249, 204) );
        pDC->SetBkMode( OPAQUE );
 
        return 0;
    }
	
	if ( pWnd->GetDlgCtrlID() == IDC_EDIT1 )
    {
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode( OPAQUE );
 
        return 0;
    }

	if ( pWnd->GetDlgCtrlID() == IDC_EDIT3 )
    {
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode( OPAQUE );
 
        return 0;
    }

	if ( pWnd->GetDlgCtrlID() == IDC_EDIT14 )
    {
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode( OPAQUE );
 
        return 0;
    }

	if (pWnd->GetDlgCtrlID() == IDC_EDIT4)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
