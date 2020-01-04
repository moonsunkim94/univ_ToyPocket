// RegisterFormView.cpp : ���� �����Դϴ�.
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


// CRegisterFormView �����Դϴ�.

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


// CRegisterFormView �޽��� ó�����Դϴ�.


void CRegisterFormView::OnBnClickedRegister()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	if(m_strName!=""&&m_loginpwd!=""&&m_loginpwd2!=""&&m_userName!=""&&m_userEmail){
		
		CString s;
		CString sdate;
		sdate.Format(_T("%d-%02d-%02d"),m_userBirth.GetYear(),m_userBirth.GetMonth(),m_userBirth.GetDay());

		CDatabase db;			// �����ͺ��̽� ��ü ����
		CRecordset rs (&db);	// ���ڵ�� ��ü ����
		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");	//DB����
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("�����ͺ��̽� ���ӽ���!");

			CString strQuery;	//�����ͺ��̽��� ������ ������
			strQuery.Format(_T("INSERT INTO UserData VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s')"), 
				m_strName, m_loginpwd, m_userName, sdate, m_userEmail, _T("��"), _T("manager") );
			
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
		UpdateData(false);

		AfxMessageBox(_T("���ԿϷ�!"));

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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	sql="select * from UserData";

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SwitchView(VIEWID_HOME);
}


BOOL CRegisterFormView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rt;
    GetClientRect(&rt);  // Ŭ���̾�Ʈ ������ ũ�� ���
	pDC->FillSolidRect(&rt, RGB(255, 255, 255));  

	return TRUE; 
	//return CFormView::OnEraseBkgnd(pDC);
}


HBRUSH CRegisterFormView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	UINT nID = pWnd->GetDlgCtrlID();			//��Ʈ�� �ڵ�� ���ϱ� ���� ����
 
   if(nID==IDC_STATIC1)							// ����ƽ ��Ʈ���϶�
    {    
        pDC->SetBkMode(TRANSPARENT);                              
        return (HBRUSH)::GetStockObject(NULL_BRUSH);                      
    }
	 if(nID==IDC_STATIC2)							// ����ƽ ��Ʈ���϶�
    {    
        pDC->SetBkMode(TRANSPARENT);                              
        return (HBRUSH)::GetStockObject(NULL_BRUSH);                      
    }
	  if(nID==IDC_STATIC3)							// ����ƽ ��Ʈ���϶�
    {    
        pDC->SetBkMode(TRANSPARENT);                              
        return (HBRUSH)::GetStockObject(NULL_BRUSH);                      
    }
	   if(nID==IDC_STATIC4)							// ����ƽ ��Ʈ���϶�
    {    
        pDC->SetBkMode(TRANSPARENT);                              
        return (HBRUSH)::GetStockObject(NULL_BRUSH);                      
    }
	    if(nID==IDC_STATIC5)							// ����ƽ ��Ʈ���϶�
    {    
        pDC->SetBkMode(TRANSPARENT);                              
        return (HBRUSH)::GetStockObject(NULL_BRUSH);                      
    }
		 if(nID==IDC_STATIC6)							// ����ƽ ��Ʈ���϶�
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

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}
