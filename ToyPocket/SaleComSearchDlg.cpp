// SaleComSearchDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "SaleComSearchDlg.h"
#include "afxdialogex.h"


// CSaleComSearchDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSaleComSearchDlg, CDialogEx)

CSaleComSearchDlg::CSaleComSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSaleComSearchDlg::IDD, pParent)
	, m_csearch(_T(""))
{

}

CSaleComSearchDlg::~CSaleComSearchDlg()
{
}

void CSaleComSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SEARCH, m_ccombobox);
	DDX_Text(pDX, IDC_EDIT7, m_csearch);
	DDX_Control(pDX, IDC_LIST1, m_cs_List);
	DDX_Control(pDX, IDOK4, m_combtn);
}


BEGIN_MESSAGE_MAP(CSaleComSearchDlg, CDialogEx)
	ON_BN_CLICKED(IDOK4, &CSaleComSearchDlg::OnBnClickedSearch)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CSaleComSearchDlg::OnHdnItemclickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CSaleComSearchDlg::OnNMDblclkList1)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, OnCustomdrawList)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CSaleComSearchDlg �޽��� ó�����Դϴ�.

void CSaleComSearchDlg::OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult)
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

void CSaleComSearchDlg::OnBnClickedSearch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(true);

	if(m_cs_List.GetItemCount() > 0) m_cs_List.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
			
		int nIndex = m_ccombobox.GetCurSel();
		if(nIndex == 0){
			strQuery.Format(_T("SELECT com_id, c_code, c_name,  c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company WHERE c_code LIKE '%%%s%%' OR c_name LIKE '%%%s%%' OR c_sort LIKE '%%%s%%' OR c_type LIKE '%%%s%%' OR c_business LIKE '%%%s%%' OR c_ceoname LIKE '%%%s%%' OR c_tel LIKE '%%%s%%' AND c_sort = '��ǰó'"),
				m_csearch,m_csearch,m_csearch,m_csearch,m_csearch,m_csearch,m_csearch);
		}
		if(nIndex == 1){
			strQuery.Format(_T("SELECT com_id, c_code, c_name,  c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company WHERE c_code LIKE '%%%s%%' AND c_sort = '��ǰó'"),m_csearch);
		}
		if(nIndex == 2){
			strQuery.Format(_T("SELECT com_id, c_code, c_name,  c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company WHERE c_name LIKE '%%%s%%' AND c_sort = '��ǰó'"),m_csearch);
		}
		if(nIndex == 3){
			strQuery.Format(_T("SELECT com_id, c_code, c_name,  c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company WHERE c_type LIKE '%%%s%%' AND c_sort = '��ǰó'"),m_csearch);
		}
		if(nIndex == 4){
			strQuery.Format(_T("SELECT com_id, c_code, c_name,  c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company WHERE c_business LIKE '%%%s%%' AND c_sort = '��ǰó'"),m_csearch);
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
			 m_cs_List.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				m_cs_List.SetItemText(p, i ,tmp);
			}
			rs.MoveNext(); 
		 }
	}
	rs.Close();
	db.Close();
}


void CSaleComSearchDlg::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nColumn = phdr->iItem;
	// ���� ����Ʈ ��Ʈ�ѿ� �ִ� ������ �� �ڷ� ������ŭ ����
	 for(int i=0; i< (m_cs_List.GetItemCount()); i++)
	{
	 m_cs_List.SetItemData(i, i);
	}

	// ���� ��� ����(Ascend, Descend)
	 m_bAscending = !m_bAscending;


	 UpdateArrow();


	// ���� ���õ� ����ü ���� ���� �� ������ �ʱ�ȭ
	SORTPARAM sortparams;
	sortparams.pList = &m_cs_List;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending;

	// ���� �Լ� ȣ��
	m_cs_List.SortItems(&CompareItem, (LPARAM)&sortparams );
	*pResult = 0;
}


void CSaleComSearchDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    nListIndex = pNMListView->iItem;
	UpdateData();
	m_ccodeset = m_cs_List.GetItemText(nListIndex,1);
	m_cnameset = m_cs_List.GetItemText(nListIndex,2);
	*pResult = 0;
	CDialogEx::OnOK();
}


BOOL CSaleComSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_combtn.LoadBitmaps(IDB_BMP_SEARCH, NULL, NULL, NULL);
	m_combtn.SizeToContent();
	m_cs_List.SetExtendedStyle( LVS_EX_FULLROWSELECT ); //����ü����

	if(m_cs_List.GetHeaderCtrl()->GetItemCount() <= 0)		//����� �������� ���ٸ�
	{
		CRect rect;
		m_cs_List.GetClientRect(&rect);
		m_cs_List.InsertColumn(0, _T("�����"),			LVCFMT_LEFT, 80);
		m_cs_List.InsertColumn(1, _T("�ŷ�ó�ڵ�"),			LVCFMT_LEFT, 80);
		m_cs_List.InsertColumn(2, _T("�ŷ�ó��"),			LVCFMT_LEFT, 80);
		m_cs_List.InsertColumn(3, _T("����"),			    LVCFMT_LEFT, 70);
		m_cs_List.InsertColumn(4, _T("����"),			    LVCFMT_LEFT, 70);
		m_cs_List.InsertColumn(5, _T("��ǥ�ڸ�"),			LVCFMT_LEFT, 80);
		m_cs_List.InsertColumn(6, _T("�ŷ�ó��ȣ"),			LVCFMT_LEFT, 80);
		m_cs_List.InsertColumn(7, _T("����ڹ�ȣ"),			LVCFMT_LEFT, 80);
		m_cs_List.InsertColumn(8, _T("�ּ�"),			    LVCFMT_LEFT, 80);
		m_cs_List.InsertColumn(9, _T("�ŷ�ó ��ǥ ��ȭ"),	LVCFMT_LEFT, 110);
		m_cs_List.InsertColumn(10, _T("�ŷ�ó ��ǥ ����"),	LVCFMT_LEFT, 110);
		m_cs_List.InsertColumn(11, _T("�ŷ�ó ��ǥ ����"),	LVCFMT_LEFT, 110);
		m_cs_List.InsertColumn(12, _T("�޸�"),			    LVCFMT_LEFT, 80);
	}
	 m_ccombobox.AddString(_T("��ü�˻�"));
	 m_ccombobox.AddString(_T("�ŷ�ó�ڵ�"));                   //�ؽ�Ʈ �߰�
	 m_ccombobox.AddString(_T("�ŷ�ó��"));
	 m_ccombobox.AddString(_T("����"));
	 m_ccombobox.AddString(_T("����"));
	
	 m_ccombobox.SetCurSel(0);                                //�ؽ�Ʈ ����

	//��� ��Ʈ�� �巡��-��-��� ����
	DWORD dwExStyle = m_cs_List.GetExtendedStyle();
	m_cs_List.SetExtendedStyle(dwExStyle | LVS_EX_HEADERDRAGDROP );

	m_bAscending = FALSE;
	m_cs_List.SortItems(&CSaleComSearchDlg::CompareItem, (DWORD_PTR)this);
	UpdateArrow();
	
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
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CSaleComSearchDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
	if(m_cs_List.GetItemCount() > 0) m_cs_List.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
		strQuery.Format(_T("SELECT com_id, c_code, c_name,  c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo  FROM Company WHERE c_sort = '��ǰó'"));
		
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
			 m_cs_List.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				// ù��° ���ڴ� InsertValue�� ���ؼ� ������ �� ������ �Ǵ� ����, �ι�° ���ڴ� �������� �ϳ��� 
				m_cs_List.SetItemText(p, i ,tmp);
			}
			rs.MoveNext();	//���������� �̵�
		 }
	}
	rs.Close();	//���ڵ�� ��ü �Ҹ�
	db.Close();	//�����ͺ��̽� ��ü �Ҹ�
}


int CALLBACK CSaleComSearchDlg::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl *pListCtrl = ((SORTPARAM *)lParamSort)->pList;

	int iSortColumn = ((SORTPARAM *)lParamSort)->iSortColumn;
	bool bSortDirect = ((SORTPARAM *)lParamSort)->bSortDirect;

	CString    strItem1 = pListCtrl->GetItemText(static_cast<int>(lParam1), iSortColumn);
	CString    strItem2 = pListCtrl->GetItemText(static_cast<int>(lParam2), iSortColumn);

	return bSortDirect ? _tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2) : -_tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2);


}

void CSaleComSearchDlg::UpdateArrow(void)
{
	CHeaderCtrl* pHeaderCtrl = m_cs_List.GetHeaderCtrl();
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
HCURSOR CSaleComSearchDlg::OnQueryDragIcon()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CDialogEx::OnQueryDragIcon();
}


void CSaleComSearchDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialogEx::OnSysCommand(nID, lParam);
}


BOOL CSaleComSearchDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CRect rt;
    GetClientRect(&rt);  // Ŭ���̾�Ʈ ������ ũ�� ���
	pDC->FillSolidRect(&rt, RGB(247, 246, 238));  

	return TRUE; 

	return CDialogEx::OnEraseBkgnd(pDC);
}
