// ManagerPermitDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ManagerPermitDlg.h"
#include "afxdialogex.h"


// CManagerPermitDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManagerPermitDlg, CDialogEx)

CManagerPermitDlg::CManagerPermitDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManagerPermitDlg::IDD, pParent)
	, m_loginid(_T(""))
	, m_check(FALSE)
{

}

CManagerPermitDlg::~CManagerPermitDlg()
{
}

void CManagerPermitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_idEdit);
	DDX_Text(pDX, IDC_EDIT1, m_loginid);
	DDX_Control(pDX, IDC_EDIT3, m_ynEdit);
	DDX_Control(pDX, IDC_EDIT2, m_permiEdit);
	DDX_Control(pDX, IDC_COMBO1, m_manage_Combo);
	DDX_Radio(pDX, IDC_RADIO1, m_check);
	DDX_Control(pDX, IDC_BUTTON1, m_regisearchbtn);
	DDX_Control(pDX, IDOK, m_regiokbtn);
	DDX_Control(pDX, IDCANCEL, m_regicancelbtn);
}


BEGIN_MESSAGE_MAP(CManagerPermitDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &CManagerPermitDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CManagerPermitDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CManagerPermitDlg 메시지 처리기입니다.


BOOL CManagerPermitDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rt;
    GetClientRect(&rt);  // 클라이언트 영역의 크기 계산
	pDC->FillSolidRect(&rt, RGB(247, 246, 238));  

	return TRUE; 

	return CDialogEx::OnEraseBkgnd(pDC);
}


HBRUSH CManagerPermitDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

		 /*

		 if (pWnd->GetDlgCtrlID() == IDC_EDIT1)
		 {
			 pDC->SetBkColor(RGB(252, 249, 204));
			 pDC->SetBkMode(OPAQUE);

			 return 0;
		 }
          */
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CManagerPermitDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	nIndex = m_manage_Combo.GetCurSel();
	if(nIndex == -1)
			return;
	m_manage_Combo.GetLBText(nIndex, strSort);
	

		CDatabase db;			// 데이터베이스 객체 생성
		CRecordset rs (&db);	// 레코드셋 객체 생성
		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");	//DB오픈
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("데이터베이스 접속실패!");

			CString strQuery;	//데이터베이스에 전송할 쿼리문
			strQuery.Format(_T("UPDATE UserData SET permission = '%s' , user_YN = '%s' WHERE id='%s'"), strSort, strRadio, m_loginid);

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

		m_manage_Combo.SetCurSel(-1);
		m_idEdit.SetWindowTextW(_T(""));
		CButton* pButton = (CButton*)GetDlgItem(IDC_RADIO1);
		pButton->SetCheck(false); 
		CButton* pButton2 = (CButton*)GetDlgItem(IDC_RADIO2);
		pButton2->SetCheck(false); 

		GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT3)->ShowWindow(SW_HIDE);

	CDialogEx::OnOK();
}


BOOL CManagerPermitDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_manage_Combo.AddString(_T("admin"));
	m_manage_Combo.AddString(_T("manager"));
	m_manage_Combo.SetCurSel(-1);

	CButton* pButton = (CButton*)GetDlgItem(IDC_RADIO1);
		pButton->SetCheck(false); 
		CButton* pButton2 = (CButton*)GetDlgItem(IDC_RADIO2);
		pButton2->SetCheck(false); 
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT3)->ShowWindow(SW_HIDE);

	m_regisearchbtn.LoadBitmaps(IDB_BMP_SEARCH2, NULL, NULL, NULL);
	m_regisearchbtn.SizeToContent(); 

	m_regiokbtn.LoadBitmaps(IDB_BMP_OK, NULL, NULL, NULL);
	m_regiokbtn.SizeToContent(); 

	m_regicancelbtn.LoadBitmaps(IDB_BMP_CANCEL, NULL, NULL, NULL);
	m_regicancelbtn.SizeToContent(); 

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
	GetDlgItem(IDC_COMBO1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_RADIO1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_RADIO2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT3)->SetFont(&m_fontTitle);

	m_fontTitle.Detach(); 

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CManagerPermitDlg::OnRadioButton(UINT value){
	UpdateData(TRUE);
	switch(m_check){
	case 0 :
		strRadio = _T("예");
		break;
	case 1:
		strRadio = _T("아니오");
		break;
	}
}


#include "RegisterIdSearchDlg.h"
void CManagerPermitDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CRegisterIdSearchDlg pDlg;
	pDlg.DoModal();
	m_idEdit.SetWindowTextW(pDlg.m_idset);
	m_permiEdit.SetWindowTextW(pDlg.m_permiset);
	m_ynEdit.SetWindowTextW(pDlg.m_ynset);
	GetDlgItem(IDC_STATIC4)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC5)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC6)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT3)->ShowWindow(SW_SHOW);
}
