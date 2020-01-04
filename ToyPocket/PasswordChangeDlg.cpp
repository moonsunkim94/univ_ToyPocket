// PasswordChangeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "PasswordChangeDlg.h"
#include "afxdialogex.h"


// CPasswordChangeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPasswordChangeDlg, CDialogEx)

CPasswordChangeDlg::CPasswordChangeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPasswordChangeDlg::IDD, pParent)
	, m_pwd(_T(""))
	, m_changepwd(_T(""))
	, m_changepwd2(_T(""))
{

}

CPasswordChangeDlg::~CPasswordChangeDlg()
{
}

void CPasswordChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_pwdEdit);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
	DDX_Control(pDX, IDC_EDIT3, m_chpwdEdit);
	DDX_Text(pDX, IDC_EDIT3, m_changepwd);
	DDX_Control(pDX, IDC_EDIT4, m_chpwd2Edit);
	DDX_Text(pDX, IDC_EDIT4, m_changepwd2);
	DDX_Control(pDX, IDOK, m_paokbtn);
	DDX_Control(pDX, IDCANCEL, m_pacancelbtn);
}


BEGIN_MESSAGE_MAP(CPasswordChangeDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &CPasswordChangeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPasswordChangeDlg 메시지 처리기입니다.


BOOL CPasswordChangeDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rt;
    GetClientRect(&rt);  // 클라이언트 영역의 크기 계산
	pDC->FillSolidRect(&rt, RGB(247, 246, 238));  

	return TRUE;  

	return CDialogEx::OnEraseBkgnd(pDC);
}


HBRUSH CPasswordChangeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

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

	  if (pWnd->GetDlgCtrlID() == IDC_EDIT2)
	  {
		  pDC->SetBkColor(RGB(252, 249, 204));
		  pDC->SetBkMode(OPAQUE);

		  return 0;
	  }

	  if (pWnd->GetDlgCtrlID() == IDC_EDIT3)
	  {
		  pDC->SetBkColor(RGB(252, 249, 204));
		  pDC->SetBkMode(OPAQUE);

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


void CPasswordChangeDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	if(m_pwd == g_pwd){
	if(m_changepwd == m_changepwd2){
	CDatabase db;			// 데이터베이스 객체 생성
		CRecordset rs (&db);	// 레코드셋 객체 생성
		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");	//DB오픈
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("데이터베이스 접속실패!");

			CString strQuery;	//데이터베이스에 전송할 쿼리문
			strQuery.Format(_T("UPDATE UserData SET password = '%s' WHERE id='%s' AND password = '%s'"), m_changepwd, g_setid, m_pwd);

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
		m_pwdEdit.SetWindowTextW(_T(""));
		m_chpwdEdit.SetWindowTextW(_T(""));
		m_chpwd2Edit.SetWindowTextW(_T(""));
		//OnBnClickedButtonComClear();	//컨트롤 초기화

		rs.Close();	//레코드셋 객체 소멸
		db.Close();	//데이터베이스 객체 소멸
	
	}

	else{
		AfxMessageBox(_T("비밀번호가 서로 다릅니다."));
		m_chpwdEdit.SetWindowTextW(_T(""));
		m_chpwd2Edit.SetWindowTextW(_T(""));
	}
	}
	 else{
		AfxMessageBox(_T("현재 비밀번호와 다릅니다."));
		m_pwdEdit.SetWindowTextW(_T(""));
		m_chpwdEdit.SetWindowTextW(_T(""));
		m_chpwd2Edit.SetWindowTextW(_T(""));
	 }

	CDialogEx::OnOK();
}


BOOL CPasswordChangeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_paokbtn.LoadBitmaps(IDB_BMP_OK, NULL, NULL, NULL);
	m_paokbtn.SizeToContent(); 

	m_pacancelbtn.LoadBitmaps(IDB_BMP_CANCEL, NULL, NULL, NULL);
	m_pacancelbtn.SizeToContent(); 
	CFont    m_fontTitle;
	LOGFONT  lf; 

	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 17;
	::lstrcpy(lf.lfFaceName, _T("나눔바른고딕"));
	m_fontTitle.CreateFontIndirect(&lf);
	GetDlgItem(IDC_STATIC1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC3)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT3)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT4)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
