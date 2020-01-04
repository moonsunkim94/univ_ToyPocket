
// ToyPocketView.cpp : CToyPocketView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
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

// CToyPocketView ����/�Ҹ�

CToyPocketView::CToyPocketView()
	: CRecordView(CToyPocketView::IDD)
	, m_loginid(_T(""))
	, m_loginpwd(_T(""))
{
	m_pSet = NULL;
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CToyPocketView::~CToyPocketView()
{
}

void CToyPocketView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	// ��Ʈ���� �����ͺ��̽� �ʵ忡 '����'�ϱ� ���� ���⿡ DDX_Field* �Լ��� ������ �� �ֽ��ϴ�. ��:
	// DDX_FieldText(pDX, IDC_MYEDITBOX, m_pSet->m_szColumn1, m_pSet);
	// DDX_FieldCheck(pDX, IDC_MYCHECKBOX, m_pSet->m_bColumn2, m_pSet);
	// �ڼ��� ������ MSDN �� ODBC ������ �����Ͻʽÿ�.
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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

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
	::lstrcpy(lf.lfFaceName, _T("�����ٸ����"));
	m_fontTitle.CreateFontIndirect(&lf);
	GetDlgItem(IDC_STATIC1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT1)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 
	
}


// CToyPocketView �μ�


void CToyPocketView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CToyPocketView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToyPocketView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToyPocketView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
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


// CToyPocketView ����

#ifdef _DEBUG
void CToyPocketView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CToyPocketView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CToyPocketDoc* CToyPocketView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToyPocketDoc)));
	return (CToyPocketDoc*)m_pDocument;
}
#endif //_DEBUG


// CToyPocketView �����ͺ��̽� ����
CRecordset* CToyPocketView::OnGetRecordset()
{
	return m_pSet;
}



// CToyPocketView �޽��� ó����


void CToyPocketView::OnBnClickedLogin()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
		AfxMessageBox(_T("�α��� ����"));
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
		
		// ��� ������ �ȶ���
		pFrame->MoveWindow(rect.Width()/4, rect.Height()/6, 100, 100);

		CDatabase db;			// �����ͺ��̽� ��ü ����
		
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
		strQuery.Format(_T("SELECT permission FROM UserData WHERE id='%s' AND password='%s'"),id, pass);
									
		if (rs.Open (CRecordset::snapshot, strQuery) == FALSE)	
			throw _T("�������� ����!");
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
		
	//�������� �̿��� �˻��� ���� ����Ʈ ��Ʈ�ѿ� ���
	short col = rs.GetODBCFieldCount();	
	for(int p=0 ; p<2 ; p++)
	{
		 while( ! rs.IsEOF())		//�����
		 {
			 //�Ӽ�����
			 rs.GetFieldValue((short)p, g_per);  
			 //id���� ������ �ȴ�.
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, g_per);
				// ù��° ���ڴ� InsertValue�� ���ؼ� ������ �� ������ �Ǵ� ����, �ι�° ���ڴ� �������� �ϳ��� 
			}
			rs.MoveNext();	//���������� �̵�
		 }
	}

	rs.Close();	//���ڵ�� ��ü �Ҹ�
	db.Close();	//�����ͺ��̽� ��ü �Ҹ�
		return;
	}
		join.MoveNext();

	}

	join.MoveLast();
	AfxMessageBox(_T("�α��� ����"));
	
}

void CToyPocketView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CRecordView::OnPaint()��(��) ȣ������ ���ʽÿ�.
	HBITMAP hbit;
	 hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_LOGOWHITE));

	staticsize.SetBitmap(hbit) ;




}


BOOL CToyPocketView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rt;
    GetClientRect(&rt);  // Ŭ���̾�Ʈ ������ ũ�� ���
	//pDC->FillSolidRect(&rt, RGB(250, 244, 192));  
	pDC->FillSolidRect(&rt, RGB(255, 255, 255));  
	return TRUE; 
	//return CRecordView::OnEraseBkgnd(pDC);
}


HBRUSH CToyPocketView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CRecordView::OnCtlColor(pDC, pWnd, nCtlColor);

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

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}


BOOL CToyPocketView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if(pMsg->wParam == VK_RETURN) // VK_RETURN �̶�� ���� ����Ű�� �ǹ��մϴ�.
	{
		// �α��� ó�� �ϰ��� �ϴ� ����Ÿ ó��(������ �޽����� ���� ���� �Ǵ°Ű���?)
		OnBnClickedLogin();
		return TRUE;
	}
	return CRecordView::PreTranslateMessage(pMsg);
}


void CToyPocketView::OnBnClickedRegisterBtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SwitchView(VIEWID_REGISTER_SHEET);
}
