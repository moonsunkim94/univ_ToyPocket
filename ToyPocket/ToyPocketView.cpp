
// ToyPocketView.cpp : CToyPocketView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ToyPocket.h"
#endif

#include "ToyPocketSet.h"
#include "ToyPocketDoc.h"
#include "ToyPocketView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CToyPocketView

IMPLEMENT_DYNCREATE(CToyPocketView, CRecordView)

BEGIN_MESSAGE_MAP(CToyPocketView, CRecordView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CToyPocketView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON2, &CToyPocketView::OnBnClickedLogin)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON10, &CToyPocketView::OnBnClickedRegisterBtn)
END_MESSAGE_MAP()

// CToyPocketView 생성/소멸

CToyPocketView::CToyPocketView()
	: CRecordView(CToyPocketView::IDD)
	, m_loginid(_T(""))
	, m_loginpwd(_T(""))
{
	m_pSet = NULL;
	// TODO: 여기에 생성 코드를 추가합니다.

}

CToyPocketView::~CToyPocketView()
{
}

void CToyPocketView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	// 컨트롤을 데이터베이스 필드에 '연결'하기 위해 여기에 DDX_Field* 함수를 삽입할 수 있습니다. 예:
	// DDX_FieldText(pDX, IDC_MYEDITBOX, m_pSet->m_szColumn1, m_pSet);
	// DDX_FieldCheck(pDX, IDC_MYCHECKBOX, m_pSet->m_bColumn2, m_pSet);
	// 자세한 내용은 MSDN 및 ODBC 샘플을 참조하십시오.
	DDX_Text(pDX, IDC_EDIT2, m_loginid);
	DDV_MaxChars(pDX, m_loginid, 20);
	DDX_Text(pDX, IDC_EDIT1, m_loginpwd);
	DDV_MaxChars(pDX, m_loginpwd, 20);
	DDX_Control(pDX, IDC_BUTTON2, loginbtn);
	DDX_Control(pDX, IDC_LOGO_PICTURE, staticsize);
	DDX_Control(pDX, IDC_BUTTON10, m_registerbtn);
}

BOOL CToyPocketView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CRecordView::PreCreateWindow(cs);
}

void CToyPocketView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_ToyPocketSet;
	CRecordView::OnInitialUpdate();

	loginbtn.LoadBitmaps(IDB_BMP_LOGIN, NULL, NULL, NULL);
	loginbtn.SizeToContent();	
	
	m_registerbtn.LoadBitmaps(IDB_BMP_REGISTER, NULL, NULL, NULL);
	m_registerbtn.SizeToContent();	

	CFont    m_fontTitle;
	LOGFONT  lf; 

	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 17;
	::lstrcpy(lf.lfFaceName, _T("나눔바른고딕"));
	m_fontTitle.CreateFontIndirect(&lf);
	GetDlgItem(IDC_STATIC1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT1)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 
	
}


// CToyPocketView 인쇄


void CToyPocketView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CToyPocketView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CToyPocketView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CToyPocketView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CToyPocketView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CToyPocketView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CToyPocketView 진단

#ifdef _DEBUG
void CToyPocketView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CToyPocketView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CToyPocketDoc* CToyPocketView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToyPocketDoc)));
	return (CToyPocketDoc*)m_pDocument;
}
#endif //_DEBUG


// CToyPocketView 데이터베이스 지원
CRecordset* CToyPocketView::OnGetRecordset()
{
	return m_pSet;
}



// CToyPocketView 메시지 처리기


void CToyPocketView::OnBnClickedLogin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CToyPocketSet join;
	join.Open();

	CString id = m_loginid;
	CString pass = m_loginpwd;

	while(!join.IsEOF()){

	CString m_id = join.m_id;
	CString m_pass = join.m_password;

	if(m_id == id && m_pass == pass)
	{
		AfxMessageBox(_T("로그인 성공"));
		g_setid = id;
		g_pwd = pass;
		m_bIsCopyTime = TRUE;
		m_loginid=_T("");
		m_loginpwd=_T("");
		CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();		
		pFrame->SwitchView(VIEWID_HOMEPAGE);	

		pFrame->m_nFirst = 1;

		CRect rect;
		pFrame->GetWindowRect(&rect);
		
		// 대박 교수님 똑똑이
		pFrame->MoveWindow(rect.Width()/4, rect.Height()/6, 100, 100);

		CDatabase db;			// 데이터베이스 객체 생성
		
	CRecordset rs (&db);	// 레코드셋 객체 생성
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("데이터베이스 접속실패!");

		CString strQuery;
		strQuery.Format(_T("SELECT permission FROM UserData WHERE id='%s' AND password='%s'"),id, pass);
									
		if (rs.Open (CRecordset::snapshot, strQuery) == FALSE)	
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
		
	//쿼리문을 이용해 검색한 내용 리스트 컨트롤에 출력
	short col = rs.GetODBCFieldCount();	
	for(int p=0 ; p<2 ; p++)
	{
		 while( ! rs.IsEOF())		//행단위
		 {
			 //속성단위
			 rs.GetFieldValue((short)p, g_per);  
			 //id값이 기준이 된다.
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, g_per);
				// 첫번째 인자는 InsertValue를 통해서 가지고 온 기준이 되는 정보, 두번째 인자는 열단위로 하나씩 
			}
			rs.MoveNext();	//다음행으로 이동
		 }
	}

	rs.Close();	//레코드셋 객체 소멸
	db.Close();	//데이터베이스 객체 소멸
		return;
	}
		join.MoveNext();

	}

	join.MoveLast();
	AfxMessageBox(_T("로그인 실패"));
	
}

void CToyPocketView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CRecordView::OnPaint()을(를) 호출하지 마십시오.
	HBITMAP hbit;
	 hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_LOGOWHITE));

	staticsize.SetBitmap(hbit) ;




}


BOOL CToyPocketView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rt;
    GetClientRect(&rt);  // 클라이언트 영역의 크기 계산
	//pDC->FillSolidRect(&rt, RGB(250, 244, 192));  
	pDC->FillSolidRect(&rt, RGB(255, 255, 255));  
	return TRUE; 
	//return CRecordView::OnEraseBkgnd(pDC);
}


HBRUSH CToyPocketView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CRecordView::OnCtlColor(pDC, pWnd, nCtlColor);

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

	 if (pWnd->GetDlgCtrlID() == IDC_EDIT2)
	 {
		 pDC->SetBkColor(RGB(252, 249, 204));
		 pDC->SetBkMode(OPAQUE);

		 return 0;
	 }

	 if (pWnd->GetDlgCtrlID() == IDC_EDIT1)
	 {
		 pDC->SetBkColor(RGB(252, 249, 204));
		 pDC->SetBkMode(OPAQUE);

		 return 0;
	 }

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL CToyPocketView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(pMsg->wParam == VK_RETURN) // VK_RETURN 이라는 것이 엔터키를 의미합니다.
	{
		// 로그인 처리 하고자 하는 데이타 처리(서버로 메시지를 보낼 곳이 되는거겠죠?)
		OnBnClickedLogin();
		return TRUE;
	}
	return CRecordView::PreTranslateMessage(pMsg);
}


void CToyPocketView::OnBnClickedRegisterBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SwitchView(VIEWID_REGISTER_SHEET);
}
