// RegisterIdSearchDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "RegisterIdSearchDlg.h"
#include "afxdialogex.h"


// CRegisterIdSearchDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRegisterIdSearchDlg, CDialogEx)

CRegisterIdSearchDlg::CRegisterIdSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRegisterIdSearchDlg::IDD, pParent)
	, m_idsearch(_T(""))
{

}

CRegisterIdSearchDlg::~CRegisterIdSearchDlg()
{
}

void CRegisterIdSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_idsearchCombo);
	DDX_Text(pDX, IDC_EDIT2, m_idsearch);
	DDX_Control(pDX, IDC_LIST1, m_idList);
}


BEGIN_MESSAGE_MAP(CRegisterIdSearchDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRegisterIdSearchDlg::OnBnClickedSearch)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CRegisterIdSearchDlg::OnHdnItemclickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CRegisterIdSearchDlg::OnNMDblclkList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CRegisterIdSearchDlg::OnNMRClickList1)
	ON_COMMAND(ID_IDDELETE, &CRegisterIdSearchDlg::OnIddelete)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, OnCustomdrawList)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CRegisterIdSearchDlg �޽��� ó�����Դϴ�.
void CRegisterIdSearchDlg::OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult)
{
 NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
 *pResult = 0;

 if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
 {
  *pResult = CDRF_NOTIFYITEMDRAW;
 }
 else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
 {
  if( (pLVCD->nmcd.dwItemSpec % 2)== 0  )
  {
   pLVCD->clrText     = RGB(0, 0, 0);            
   pLVCD->clrTextBk = RGB(219, 239, 252);
  }
  else
  {
   pLVCD->clrText     = RGB(0, 0, 0);          
   pLVCD->clrTextBk = RGB(255, 255, 255);
  }

  *pResult = CDRF_DODEFAULT;
 }
}

void CRegisterIdSearchDlg::OnBnClickedSearch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(true);

	if(m_idList.GetItemCount() > 0) m_idList.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
			
		int nIndex = m_idsearchCombo.GetCurSel();
		if(nIndex == 0){
			strQuery.Format(_T("SELECT id, name, permission, user_YN, birth, email FROM UserData WHERE id LIKE '%%%s%%' OR name LIKE '%%%s%%' OR birth LIKE '%%%s%%' OR email LIKE '%%%s%%' OR user_YN LIKE '%%%s%%' OR permission LIKE '%%%s%%' "),
				m_idsearch,m_idsearch,m_idsearch,m_idsearch,m_idsearch,m_idsearch);
		}
		if(nIndex == 1){
			strQuery.Format(_T("SELECT id, name, permission, user_YN, birth, email FROM UserData WHERE id LIKE '%%%s%%'"),m_idsearch);
		}
		if(nIndex == 2){
			strQuery.Format(_T("SELECT id, name, permission, user_YN, birth, email FROM UserData WHERE name LIKE '%%%s%%'"),m_idsearch);
		}
		if(nIndex == 3){
			strQuery.Format(_T("SELECT id, name, permission, user_YN, birth, email FROM UserData WHERE permission LIKE '%%%s%%'"),m_idsearch);
		}
		if(nIndex == 4){
			strQuery.Format(_T("SELECT id, name, permission, user_YN, birth, email FROM UserData WHERE user_YN LIKE '%%%s%%'"),m_idsearch);
		}

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

	short col = rs.GetODBCFieldCount();			//�������� �̿��� �˻��� ���� ����Ʈ ��Ʈ�ѿ� ���
	for(int p=0 ; p<2 ; p++)
	{
		 while( ! rs.IsEOF())
		 {
			 CString tmp;
			 rs.GetFieldValue((short)p, tmp);  
			 m_idList.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				m_idList.SetItemText(p, i ,tmp);
			}
			rs.MoveNext(); 
		 }
	}
	rs.Close();
	db.Close();
}


BOOL CRegisterIdSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_idList.SetExtendedStyle( LVS_EX_FULLROWSELECT ); //����ü����

	if(m_idList.GetHeaderCtrl()->GetItemCount() <= 0)		//����� �������� ���ٸ�
	{
		CRect rect;
		m_idList.GetClientRect(&rect);
		m_idList.InsertColumn(0, _T("���̵�"),			LVCFMT_LEFT, 80);
		m_idList.InsertColumn(1, _T("�̸�"),			LVCFMT_LEFT, 70);
		m_idList.InsertColumn(2, _T("����"),			LVCFMT_LEFT, 80);
		m_idList.InsertColumn(3, _T("��뿩��"),			LVCFMT_LEFT, 70);
		m_idList.InsertColumn(4, _T("����"),			    LVCFMT_LEFT, 70);
		m_idList.InsertColumn(5, _T("�̸���"),			    LVCFMT_LEFT, 80);
	}
	 m_idsearchCombo.AddString(_T("��ü�˻�"));
	 m_idsearchCombo.AddString(_T("���̵�"));                   //�ؽ�Ʈ �߰�
	 m_idsearchCombo.AddString(_T("�̸�"));
	 m_idsearchCombo.AddString(_T("����"));
	 m_idsearchCombo.AddString(_T("��뿩��"));
	 m_idsearchCombo.SetCurSel(0);                                //�ؽ�Ʈ ����

	//��� ��Ʈ�� �巡��-��-��� ����
	DWORD dwExStyle = m_idList.GetExtendedStyle();
	m_idList.SetExtendedStyle(dwExStyle | LVS_EX_HEADERDRAGDROP );

	m_bAscending = FALSE;
	m_idList.SortItems(&CRegisterIdSearchDlg::CompareItem, (DWORD_PTR)this);
	UpdateArrow();

	CFont    m_fontTitle;
	LOGFONT  lf; 

	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 17;
	::lstrcpy(lf.lfFaceName, _T("�����ٸ����"));
	m_fontTitle.CreateFontIndirect(&lf);
	GetDlgItem(IDC_COMBO1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_LIST1)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CRegisterIdSearchDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
	if(m_idList.GetItemCount() > 0) m_idList.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
		strQuery.Format(_T("SELECT id, name, permission, user_YN, birth, email FROM UserData"));
		
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
			 CString tmp;
			 rs.GetFieldValue((short)p, tmp);  
			 //id���� ������ �ȴ�.
			 m_idList.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				// ù��° ���ڴ� InsertValue�� ���ؼ� ������ �� ������ �Ǵ� ����, �ι�° ���ڴ� �������� �ϳ��� 
				m_idList.SetItemText(p, i ,tmp);
			}
			rs.MoveNext();	//���������� �̵�
		 }
	}
	rs.Close();	//���ڵ�� ��ü �Ҹ�
	db.Close();	//�����ͺ��̽� ��ü �Ҹ�
}

int CALLBACK CRegisterIdSearchDlg::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl *pListCtrl = ((SORTPARAM *)lParamSort)->pList;

	int iSortColumn = ((SORTPARAM *)lParamSort)->iSortColumn;
	bool bSortDirect = ((SORTPARAM *)lParamSort)->bSortDirect;

	CString    strItem1 = pListCtrl->GetItemText(static_cast<int>(lParam1), iSortColumn);
	CString    strItem2 = pListCtrl->GetItemText(static_cast<int>(lParam2), iSortColumn);

	return bSortDirect ? _tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2) : -_tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2);


}

void CRegisterIdSearchDlg::UpdateArrow(void)
{
	CHeaderCtrl* pHeaderCtrl = m_idList.GetHeaderCtrl();
	HDITEM hdItem;
	TCHAR szBuffer[256];
	::ZeroMemory(&hdItem, sizeof(hdItem));
	::ZeroMemory(szBuffer, 256);

	hdItem.mask = -1;
	hdItem.pszText = szBuffer;
	hdItem.cchTextMax = 256;
	pHeaderCtrl->GetItem(0, &hdItem);

	hdItem.fmt &= ~(HDF_SORTDOWN | HDF_SORTUP);

	if(m_bAscending)	hdItem.fmt |= HDF_SORTDOWN;
	else				hdItem.fmt |= HDF_SORTUP;
	pHeaderCtrl->SetItem(0, &hdItem);
}

HCURSOR CRegisterIdSearchDlg::OnQueryDragIcon()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CDialogEx::OnQueryDragIcon();
}


void CRegisterIdSearchDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialogEx::OnSysCommand(nID, lParam);
}


void CRegisterIdSearchDlg::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nColumn = phdr->iItem;
	// ���� ����Ʈ ��Ʈ�ѿ� �ִ� ������ �� �ڷ� ������ŭ ����
	 for(int i=0; i< (m_idList.GetItemCount()); i++)
	{
	 m_idList.SetItemData(i, i);
	}

	// ���� ��� ����(Ascend, Descend)
	 m_bAscending = !m_bAscending;


	 UpdateArrow();


	// ���� ���õ� ����ü ���� ���� �� ������ �ʱ�ȭ
	SORTPARAM sortparams;
	sortparams.pList = &m_idList;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending;

	// ���� �Լ� ȣ��
	m_idList.SortItems(&CompareItem, (LPARAM)&sortparams );
	*pResult = 0;
}


void CRegisterIdSearchDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    nListIndex = pNMListView->iItem;
	UpdateData();
	m_idset = m_idList.GetItemText(nListIndex,0);
	m_permiset = m_idList.GetItemText(nListIndex,2);
	m_ynset = m_idList.GetItemText(nListIndex,3);
	*pResult = 0;
	CDialogEx::OnOK();
}


void CRegisterIdSearchDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    nListIndex = pNMListView->iItem;

	CPoint ptInSrceen;

    GetCursorPos(&ptInSrceen); //R��ư ������ǥ����


	if(nListIndex==-1){
	}
	else{
	CMenu muTemp, *pContextMenu;
	muTemp.LoadMenuW(IDR_PopupMenu);
	pContextMenu = muTemp.GetSubMenu(6);
	pContextMenu -> TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, ptInSrceen.x, ptInSrceen.y,this);
	}
	m_idset = m_idList.GetItemText(nListIndex,0);
	*pResult = 0;
}


void CRegisterIdSearchDlg::OnIddelete()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	int ret;
	ret = AfxMessageBox(_T("�����Ͻðڽ��ϱ�?"), MB_YESNO|MB_ICONSTOP);
	if(ret == IDYES){
	UpdateData(TRUE);

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	
		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("�����ͺ��̽� ���ӽ���!");

			CString strQuery;	//�����ͺ��̽��� ������ ������
			strQuery.Format(_T("DELETE * FROM UserData WHERE id = '%s' "),m_idset);
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

		rs.Close();	//���ڵ�� ��ü �Ҹ�
		db.Close();	//�����ͺ��̽� ��ü �Ҹ�
		}
	Invalidate();
}


BOOL CRegisterIdSearchDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.


	CRect rt;
    GetClientRect(&rt);  // Ŭ���̾�Ʈ ������ ũ�� ���
	pDC->FillSolidRect(&rt, RGB(247, 246, 238));  

	return TRUE; 

	return CDialogEx::OnEraseBkgnd(pDC);
}
