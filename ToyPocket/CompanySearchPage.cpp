// CompanySearchPage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "CompanySearchPage.h"
#include "afxdialogex.h"
#include "CompanySheet.h"
#include "XLEzAutomation.h"

// CCompanySearchPage ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CCompanySearchPage, CPropertyPage)

CCompanySearchPage::CCompanySearchPage()
	: CPropertyPage(CCompanySearchPage::IDD)
	, m_csearch(_T(""))
{

}

CCompanySearchPage::~CCompanySearchPage()
{
}

void CCompanySearchPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT7, m_csearch);
	DDX_Control(pDX, IDC_LIST1, m_cs_list);
	DDX_Control(pDX, IDC_COMBO_SEARCH, m_combosearch);
	DDX_Control(pDX, SEARCHBTN, m_searchbtn);
	DDX_Control(pDX, IDC_BUTTON2, m_clearbtn);
	DDX_Control(pDX, IDC_BUTTON1, m_excelbtn);
	DDX_Control(pDX, IDC_EDIT7, m_Edit);
}


BEGIN_MESSAGE_MAP(CCompanySearchPage, CPropertyPage)
	ON_BN_CLICKED(SEARCHBTN, &CCompanySearchPage::OnBnClickedSearchbtn)
	ON_BN_CLICKED(IDOK, &CCompanySearchPage::OnBnClickedOk)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CCompanySearchPage::OnHdnItemclickList1)
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CCompanySearchPage::OnNMDblclkList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CCompanySearchPage::OnNMRClickList1)
	ON_COMMAND(ID_COMPANY_DELETE, &CCompanySearchPage::OnCompanyDelete)
	ON_BN_CLICKED(IDC_BUTTON1, &CCompanySearchPage::OnBnClickedExcelSave)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, OnCustomdrawList)

	ON_BN_CLICKED(IDC_BUTTON2, &CCompanySearchPage::OnBnClickedClear)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCompanySearchPage �޽��� ó�����Դϴ�.
void CCompanySearchPage::OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult)
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



void CCompanySearchPage::OnBnClickedSearchbtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(true);

	if(m_cs_list.GetItemCount() > 0) m_cs_list.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
			
		int nIndex = m_combosearch.GetCurSel();
		if(nIndex == 0){
			strQuery.Format(_T("SELECT  com_id, c_code, c_name, c_sort, c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company WHERE c_code LIKE '%%%s%%' OR c_name LIKE '%%%s%%' OR c_sort LIKE '%%%s%%' OR c_type LIKE '%%%s%%' OR c_business LIKE '%%%s%%' OR c_ceoname LIKE '%%%s%%' OR c_tel LIKE '%%%s%%'"),
				m_csearch,m_csearch,m_csearch,m_csearch,m_csearch,m_csearch,m_csearch);
			result.Format(_T("��ü�˻�-('%s')�˻���_"),m_csearch);
		}
		if(nIndex == 1){
			strQuery.Format(_T("SELECT  com_id, c_code, c_name, c_sort, c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company WHERE c_code LIKE '%%%s%%'"),m_csearch);
			result.Format(_T("�ŷ�ó�ڵ�-('%s')�˻���_"),m_csearch);
		}
		if(nIndex == 2){
			strQuery.Format(_T("SELECT  com_id, c_code, c_name, c_sort, c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company WHERE c_name LIKE '%%%s%%'"),m_csearch);
			result.Format(_T("�ŷ�ó��-('%s')�˻���_"),m_csearch);
		}
		if(nIndex == 3){
			strQuery.Format(_T("SELECT  com_id, c_code, c_name, c_sort, c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company WHERE c_type LIKE '%%%s%%'"),m_csearch);
			result.Format(_T("����-('%s')�˻���_"),m_csearch);
		}
		if(nIndex == 4){
			strQuery.Format(_T("SELECT  com_id, c_code, c_name, c_sort, c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company WHERE c_business LIKE '%%%s%%'"),m_csearch);
			result.Format(_T("����-('%s')�˻���_"),m_csearch);
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
			 m_cs_list.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				m_cs_list.SetItemText(p, i ,tmp);
			}
			rs.MoveNext(); 
		 }
	}
	rs.Close();
	db.Close();


}





BOOL CCompanySearchPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_cs_list.SetExtendedStyle( LVS_EX_FULLROWSELECT ); //����ü����

	if(m_cs_list.GetHeaderCtrl()->GetItemCount() <= 0)		//����� �������� ���ٸ�
	{
		CRect rect;
		m_cs_list.GetClientRect(&rect);
		m_cs_list.InsertColumn(0, _T("�����"),			LVCFMT_LEFT, 100);
		m_cs_list.InsertColumn(1, _T("�ŷ�ó�ڵ�"),			LVCFMT_LEFT, 80);
		m_cs_list.InsertColumn(2, _T("�ŷ�ó��"),			LVCFMT_LEFT, 80);
		m_cs_list.InsertColumn(3, _T("��ü�з�"),			LVCFMT_LEFT, 80);
		m_cs_list.InsertColumn(4, _T("����"),			    LVCFMT_LEFT, 70);
		m_cs_list.InsertColumn(5, _T("����"),			    LVCFMT_LEFT, 70);
		m_cs_list.InsertColumn(6, _T("��ǥ�ڸ�"),			LVCFMT_LEFT, 80);
		m_cs_list.InsertColumn(7, _T("�ŷ�ó��ȣ"),			LVCFMT_LEFT, 80);
		m_cs_list.InsertColumn(8, _T("����ڹ�ȣ"),			LVCFMT_LEFT, 80);
		m_cs_list.InsertColumn(9, _T("�ּ�"),			    LVCFMT_LEFT, 220);
		m_cs_list.InsertColumn(10, _T("�ŷ�ó ��ǥ ��ȭ"),	LVCFMT_LEFT, 110);
		m_cs_list.InsertColumn(11, _T("�ŷ�ó ��ǥ ����"),	LVCFMT_LEFT, 110);
		m_cs_list.InsertColumn(12, _T("�ŷ�ó ��ǥ ����"),	LVCFMT_LEFT, 110);
		m_cs_list.InsertColumn(13, _T("�޸�"),			    LVCFMT_LEFT, 80);
	}
	 m_combosearch.AddString(_T("��ü�˻�"));
	 m_combosearch.AddString(_T("�ŷ�ó�ڵ�"));                   //�ؽ�Ʈ �߰�
	 m_combosearch.AddString(_T("�ŷ�ó��"));
	 m_combosearch.AddString(_T("����"));
	 m_combosearch.AddString(_T("����"));
	
	 m_combosearch.SetCurSel(0);                                //�ؽ�Ʈ ����

	//��� ��Ʈ�� �巡��-��-��� ����
	DWORD dwExStyle = m_cs_list.GetExtendedStyle();
	m_cs_list.SetExtendedStyle(dwExStyle | LVS_EX_HEADERDRAGDROP );

	m_bAscending = FALSE;
	m_cs_list.SortItems(&CCompanySearchPage::CompareItem, (DWORD_PTR)this);
	UpdateArrow();
	
	m_searchbtn.LoadBitmaps(IDB_BMP_SEARCH, NULL, NULL, NULL);
	m_searchbtn.SizeToContent();

	m_excelbtn.LoadBitmaps(IDB_BMP_EXCEL, NULL, NULL, NULL);
	m_excelbtn.SizeToContent();
	m_clearbtn.LoadBitmaps(IDB_BMP_CLEAR, NULL, NULL, NULL);
	m_clearbtn.SizeToContent();

	HCURSOR hCursor;
	hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
	SetClassLong(m_cs_list.GetSafeHwnd(),GCL_HCURSOR,(LONG)hCursor);
	
	CFont    m_fontTitle;
	LOGFONT  lf; 

	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 17;
	::lstrcpy(lf.lfFaceName, _T("�����ٸ����"));
	m_fontTitle.CreateFontIndirect(&lf);
	GetDlgItem(IDC_COMBO_SEARCH)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT7)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_LIST1)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 

		if(m_cs_list.GetItemCount() > 0) m_cs_list.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
		strQuery.Format(_T("SELECT com_id, c_code, c_name, c_sort, c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company"));
		
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
			 m_cs_list.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				// ù��° ���ڴ� InsertValue�� ���ؼ� ������ �� ������ �Ǵ� ����, �ι�° ���ڴ� �������� �ϳ��� 
				m_cs_list.SetItemText(p, i ,tmp);
			}
			rs.MoveNext();	//���������� �̵�
		 }
	}
	rs.Close();	//���ڵ�� ��ü �Ҹ�
	db.Close();	//�����ͺ��̽� ��ü �Ҹ�

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


int CALLBACK CCompanySearchPage::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl *pListCtrl = ((SORTPARAM *)lParamSort)->pList;

	int iSortColumn = ((SORTPARAM *)lParamSort)->iSortColumn;
	bool bSortDirect = ((SORTPARAM *)lParamSort)->bSortDirect;

	CString    strItem1 = pListCtrl->GetItemText(static_cast<int>(lParam1), iSortColumn);
	CString    strItem2 = pListCtrl->GetItemText(static_cast<int>(lParam2), iSortColumn);

	return bSortDirect ? _tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2) : -_tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2);


}

void CCompanySearchPage::UpdateArrow(void)
{
	CHeaderCtrl* pHeaderCtrl = m_cs_list.GetHeaderCtrl();
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

void CCompanySearchPage::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialog::OnOK(); //�̰� �׳� ��ó��Ʈ�ѿ��� ���̾�α׸� �Ⱥ��̰���

}


void CCompanySearchPage::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// ����Ʈ��Ʈ�� Į�� Ŭ���� �� ������ ����
	// Ŭ���� Į���� �ε���
	int nColumn = pNMLV->iItem;
	// ���� ����Ʈ ��Ʈ�ѿ� �ִ� ������ �� �ڷ� ������ŭ ����
	 for(int i=0; i< (m_cs_list.GetItemCount()); i++)
	{
	 m_cs_list.SetItemData(i, i);
	}

	// ���� ��� ����(Ascend, Descend)
	 m_bAscending = !m_bAscending;


	 UpdateArrow();


	// ���� ���õ� ����ü ���� ���� �� ������ �ʱ�ȭ
	SORTPARAM sortparams;
	sortparams.pList = &m_cs_list;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending;

	// ���� �Լ� ȣ��
	m_cs_list.SortItems(&CompareItem, (LPARAM)&sortparams );

	*pResult = 0;
}


HCURSOR CCompanySearchPage::OnQueryDragIcon()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	//�������ڸ��� ���̰Բ�
	return static_cast<HCURSOR>(m_hIcon);
}

#include "CompanyModifyPage.h"

void CCompanySearchPage::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    nListIndex = pNMListView->iItem;

	int formindex;
	
	CString num1;
	//g_set_ccode = m_cs_list.GetItemText(nListIndex,0);

	g_set_cnumber = m_cs_list.GetItemText(nListIndex,8);
	g_set_cname = m_cs_list.GetItemText(nListIndex,2);

	//g_set_csortindex = m_cs_list.GetItemText(nListIndex,1);
	if(m_cs_list.GetItemText(nListIndex,3)==_T("����ó"))
		g_set_csortindex = 0;
	else
		g_set_csortindex = 1;

	g_set_ctype = m_cs_list.GetItemText(nListIndex,4);
	g_set_cbusiness = m_cs_list.GetItemText(nListIndex,5);

	g_set_caddress = m_cs_list.GetItemText(nListIndex,9);
	g_set_cceoname = m_cs_list.GetItemText(nListIndex,6);
	g_set_cemail = m_cs_list.GetItemText(nListIndex,11);

	g_set_cmemo = m_cs_list.GetItemText(nListIndex,13);
	//������ 11
	AfxExtractSubString(g_set_cbirth_Year,m_cs_list.GetItemText(nListIndex,12), 0,'-');
	AfxExtractSubString(g_set_cbirth_Month,m_cs_list.GetItemText(nListIndex,12), 1,'-');
	AfxExtractSubString(g_set_cbirth_Day,m_cs_list.GetItemText(nListIndex,12), 2,'-');


	CString ctel;
	CString cmTel;
	//ctel
	AfxExtractSubString(ctel,m_cs_list.GetItemText(nListIndex,7), 0,'-');
	if(ctel==_T("02"))
		g_set_ctelindex = 0;
	else
		g_set_ctelindex = 1;
	//set_ctel
	AfxExtractSubString(g_set_ctel1,m_cs_list.GetItemText(nListIndex,7), 1,'-');
	AfxExtractSubString(g_set_ctel2,m_cs_list.GetItemText(nListIndex,7), 2,'-');

	AfxExtractSubString(cmTel,m_cs_list.GetItemText(nListIndex,10), 0,'-');
	if(cmTel==_T("010"))
		g_set_cmtelindex = 0;
	else
		g_set_cmtelindex = 1;
	//set_ctel
	AfxExtractSubString(g_set_cmtel1,m_cs_list.GetItemText(nListIndex,10), 1,'-');
	AfxExtractSubString(g_set_cmtel2,m_cs_list.GetItemText(nListIndex,10), 2,'-');


	UpdateData(FALSE);//�ʿ��Ѱ�

	CCompanySheet* pSheet = (CCompanySheet*)GetParent();
	pSheet->SetActivePage(2);
	*pResult = 0;
	//modifypage�� ����Ʈ ��Ʈ���� ���� ������ �־������
}


void CCompanySearchPage::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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
	pContextMenu = muTemp.GetSubMenu(2);
	pContextMenu -> TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, ptInSrceen.x, ptInSrceen.y,this);
	}
	ccode = m_cs_list.GetItemText(nListIndex,1);

	*pResult = 0;
}




void CCompanySearchPage::OnCompanyDelete()
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
			strQuery.Format(_T("DELETE * FROM Company WHERE c_code = '%s' "),ccode);
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

	if(m_cs_list.GetItemCount() > 0) m_cs_list.DeleteAllItems();

	CDatabase db1;			// �����ͺ��̽� ��ü ����
	CRecordset rs1 (&db1);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db1.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
		strQuery.Format(_T("SELECT com_id, c_code, c_name, c_sort, c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company"));
		
		if (rs1.Open (CRecordset::snapshot, strQuery) == FALSE)	
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
	short col1 = rs1.GetODBCFieldCount();	
	for(int p=0 ; p<2 ; p++)
	{
		 while( ! rs1.IsEOF())		//�����
		 {
			 //�Ӽ�����
			 CString tmp;
			 rs1.GetFieldValue((short)p, tmp);  
			 //id���� ������ �ȴ�.
			 m_cs_list.InsertItem(p,tmp,0);
			 for(short i=1; i<col1; i++  )
			 {
				rs1.GetFieldValue(i, tmp);
				// ù��° ���ڴ� InsertValue�� ���ؼ� ������ �� ������ �Ǵ� ����, �ι�° ���ڴ� �������� �ϳ��� 
				m_cs_list.SetItemText(p, i ,tmp);
			}
			rs1.MoveNext();	//���������� �̵�
		 }
	}
	rs1.Close();	//���ڵ�� ��ü �Ҹ�
	db1.Close();	//�����ͺ��̽� ��ü �Ҹ�

	
}


void CCompanySearchPage::OnBnClickedExcelSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_cs_list.GetItemCount() <= 0)
	{
		 AfxMessageBox(_T("��ȸ�� �����Ͱ� 0���̹Ƿ� ���� ���� �� �� �����ϴ�."));
		 return;
	}

	CTime timeNow = CTime::GetCurrentTime();
	CString strDateTime;
	strDateTime = timeNow.Format(_T("%Y-%m-%d_%H��%M��%S��"));
	CString strFileName;
	strFileName.Format(_T("%s�ŷ�ó ��ȸ_%s"), result, strDateTime);

	CFileDialog fdlg(FALSE, _T("xlsx"), strFileName+_T(".xlsx"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("xlsx ���� (*.xlsx)|*.xlsx"), NULL);
	if (fdlg.DoModal() != IDOK) return;

	CXLEzAutomation xls(FALSE);  // FALSE : ó�� ������ ȭ�鿡 ������ �ʴ´�.

	int rowOffset = 2;
	int colOffset = 1;

	int rowCount = m_cs_list.GetItemCount();
	CHeaderCtrl* pHeaderCtrl = m_cs_list.GetHeaderCtrl();
	int colCount = pHeaderCtrl->GetItemCount();
	int rowIdx;
	int colIdx;

	CString strItemText; 
	for (colIdx = 0; colIdx < colCount; colIdx++){
		HDITEM hdi; 
		hdi.mask = HDI_TEXT; 
		hdi.pszText = strItemText.GetBuffer( 256 ); 
		hdi.cchTextMax = 256; 
		pHeaderCtrl->GetItem( colIdx, &hdi ); 
		strItemText.ReleaseBuffer();
		xls.SetCellValue(colIdx + colOffset, 0 + rowOffset, strItemText);
	}

	for (rowIdx = 0; rowIdx < rowCount; rowIdx++)
	{
		for (colIdx = 0; colIdx < colCount; colIdx++)
		{
			strItemText = m_cs_list.GetItemText(rowIdx, colIdx);

			// �÷� ������
			xls.SetCellValue(colIdx + colOffset, rowIdx +1 + rowOffset, strItemText);
		}
	}

	xls.SaveFileAs(fdlg.GetPathName());

	xls.ReleaseExcel();
}


void CCompanySearchPage::OnBnClickedClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_csearch=_T("");
	m_combosearch.SetCurSel(0);                                //�ؽ�Ʈ ����
	OnInitDialog();
}


HBRUSH CCompanySearchPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	/*
	if (pWnd->GetDlgCtrlID() == IDC_EDIT7)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	*/
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}

void CCompanySearchPage::ReInitDialog()
{

	if(m_cs_list.GetItemCount() > 0) m_cs_list.DeleteAllItems();

	CDatabase db1;			// �����ͺ��̽� ��ü ����
	CRecordset rs1 (&db1);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db1.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
		strQuery.Format(_T("SELECT com_id, c_code, c_name, c_sort, c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company"));

		if (rs1.Open (CRecordset::snapshot, strQuery) == FALSE)	
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
	short col1 = rs1.GetODBCFieldCount();	
	for(int p=0 ; p<2 ; p++)
	{
		 while( ! rs1.IsEOF())		//�����
		 {
			 //�Ӽ�����
			 CString tmp;
			 rs1.GetFieldValue((short)p, tmp);  
			 //id���� ������ �ȴ�.
			 m_cs_list.InsertItem(p,tmp,0);
			 for(short i=1; i<col1; i++  )
			 {
				rs1.GetFieldValue(i, tmp);
				// ù��° ���ڴ� InsertValue�� ���ؼ� ������ �� ������ �Ǵ� ����, �ι�° ���ڴ� �������� �ϳ��� 
				m_cs_list.SetItemText(p, i ,tmp);
			}
			rs1.MoveNext();	//���������� �̵�
		 }
	}
	rs1.Close();	//���ڵ�� ��ü �Ҹ�
	db1.Close();	//�����ͺ��̽� ��ü �Ҹ�

	return;
}


