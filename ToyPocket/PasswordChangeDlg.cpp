// PasswordChangeDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "PasswordChangeDlg.h"
#include "afxdialogex.h"


// CPasswordChangeDlg ��ȭ �����Դϴ�.

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


// CPasswordChangeDlg �޽��� ó�����Դϴ�.


BOOL CPasswordChangeDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CRect rt;
    GetClientRect(&rt);  // Ŭ���̾�Ʈ ������ ũ�� ���
	pDC->FillSolidRect(&rt, RGB(247, 246, 238));  

	return TRUE;  

	return CDialogEx::OnEraseBkgnd(pDC);
}


HBRUSH CPasswordChangeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

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


	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}


void CPasswordChangeDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);
	if(m_pwd == g_pwd){
	if(m_changepwd == m_changepwd2){
	CDatabase db;			// �����ͺ��̽� ��ü ����
		CRecordset rs (&db);	// ���ڵ�� ��ü ����
		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");	//DB����
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("�����ͺ��̽� ���ӽ���!");

			CString strQuery;	//�����ͺ��̽��� ������ ������
			strQuery.Format(_T("UPDATE UserData SET password = '%s' WHERE id='%s' AND password = '%s'"), m_changepwd, g_setid, m_pwd);

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
		MessageBox(_T("���������� �����Ǿ����ϴ�."));
		m_pwdEdit.SetWindowTextW(_T(""));
		m_chpwdEdit.SetWindowTextW(_T(""));
		m_chpwd2Edit.SetWindowTextW(_T(""));
		//OnBnClickedButtonComClear();	//��Ʈ�� �ʱ�ȭ

		rs.Close();	//���ڵ�� ��ü �Ҹ�
		db.Close();	//�����ͺ��̽� ��ü �Ҹ�
	
	}

	else{
		AfxMessageBox(_T("��й�ȣ�� ���� �ٸ��ϴ�."));
		m_chpwdEdit.SetWindowTextW(_T(""));
		m_chpwd2Edit.SetWindowTextW(_T(""));
	}
	}
	 else{
		AfxMessageBox(_T("���� ��й�ȣ�� �ٸ��ϴ�."));
		m_pwdEdit.SetWindowTextW(_T(""));
		m_chpwdEdit.SetWindowTextW(_T(""));
		m_chpwd2Edit.SetWindowTextW(_T(""));
	 }

	CDialogEx::OnOK();
}


BOOL CPasswordChangeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_paokbtn.LoadBitmaps(IDB_BMP_OK, NULL, NULL, NULL);
	m_paokbtn.SizeToContent(); 

	m_pacancelbtn.LoadBitmaps(IDB_BMP_CANCEL, NULL, NULL, NULL);
	m_pacancelbtn.SizeToContent(); 
	CFont    m_fontTitle;
	LOGFONT  lf; 

	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 17;
	::lstrcpy(lf.lfFaceName, _T("�����ٸ����"));
	m_fontTitle.CreateFontIndirect(&lf);
	GetDlgItem(IDC_STATIC1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC3)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT3)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT4)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
