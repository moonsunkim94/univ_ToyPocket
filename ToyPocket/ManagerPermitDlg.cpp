// ManagerPermitDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ManagerPermitDlg.h"
#include "afxdialogex.h"


// CManagerPermitDlg ��ȭ �����Դϴ�.

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


// CManagerPermitDlg �޽��� ó�����Դϴ�.


BOOL CManagerPermitDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rt;
    GetClientRect(&rt);  // Ŭ���̾�Ʈ ������ ũ�� ���
	pDC->FillSolidRect(&rt, RGB(247, 246, 238));  

	return TRUE; 

	return CDialogEx::OnEraseBkgnd(pDC);
}


HBRUSH CManagerPermitDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

		 /*

		 if (pWnd->GetDlgCtrlID() == IDC_EDIT1)
		 {
			 pDC->SetBkColor(RGB(252, 249, 204));
			 pDC->SetBkMode(OPAQUE);

			 return 0;
		 }
          */
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}


void CManagerPermitDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	nIndex = m_manage_Combo.GetCurSel();
	if(nIndex == -1)
			return;
	m_manage_Combo.GetLBText(nIndex, strSort);
	

		CDatabase db;			// �����ͺ��̽� ��ü ����
		CRecordset rs (&db);	// ���ڵ�� ��ü ����
		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");	//DB����
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("�����ͺ��̽� ���ӽ���!");

			CString strQuery;	//�����ͺ��̽��� ������ ������
			strQuery.Format(_T("UPDATE UserData SET permission = '%s' , user_YN = '%s' WHERE id='%s'"), strSort, strRadio, m_loginid);

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
		//OnBnClickedButtonComClear();	//��Ʈ�� �ʱ�ȭ

		rs.Close();	//���ڵ�� ��ü �Ҹ�
		db.Close();	//�����ͺ��̽� ��ü �Ҹ�

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

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

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
	::lstrcpy(lf.lfFaceName, _T("�����ٸ����"));
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
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CManagerPermitDlg::OnRadioButton(UINT value){
	UpdateData(TRUE);
	switch(m_check){
	case 0 :
		strRadio = _T("��");
		break;
	case 1:
		strRadio = _T("�ƴϿ�");
		break;
	}
}


#include "RegisterIdSearchDlg.h"
void CManagerPermitDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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
