// ItemSearchDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ItemSearchDlg.h"
#include "afxdialogex.h"


// CItemSearchDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CItemSearchDlg, CDialogEx)

CItemSearchDlg::CItemSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CItemSearchDlg::IDD, pParent)
	, m_isearch(_T(""))
{

}

CItemSearchDlg::~CItemSearchDlg()
{
}

void CItemSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SEARCH, m_isearch_combo);
	DDX_Text(pDX, IDC_EDIT1, m_isearch);
	DDX_Control(pDX, IDC_LIST1, m_item_List);
	DDX_Control(pDX, IDC_BUTTON1, m_isearchbtn);
}


BEGIN_MESSAGE_MAP(CItemSearchDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CItemSearchDlg::OnBnClickedSearchButton)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CItemSearchDlg::OnHdnItemclickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CItemSearchDlg::OnNMDblclkList1)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, OnCustomdrawList)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CItemSearchDlg �޽��� ó�����Դϴ�.
void CItemSearchDlg::OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult)
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

void CItemSearchDlg::OnBnClickedSearchButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(true);

	if(m_item_List.GetItemCount() > 0) m_item_List.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
			
		int nIndex = m_isearch_combo.GetCurSel();
		if(nIndex == 0){
			strQuery.Format(_T("SELECT * FROM Item WHERE i_code LIKE '%%%s%%' OR i_name LIKE '%%%s%%' OR i_large LIKE '%%%s%%' OR i_medium LIKE '%%%s%%' OR i_small LIKE '%%%s%%' OR item_id LIKE '%%%s%%' OR i_inputDate LIKE '%%%s%%'"),
				m_isearch,m_isearch,m_isearch,m_isearch,m_isearch,m_isearch,m_isearch);
		}
		if(nIndex == 1){
			strQuery.Format(_T("SELECT * FROM Item WHERE i_code LIKE '%%%s%%'"),m_isearch);
		}
		if(nIndex == 2){
			strQuery.Format(_T("SELECT * FROM Item WHERE i_name LIKE '%%%s%%'"),m_isearch);
		}
		if(nIndex == 3){
			strQuery.Format(_T("SELECT * FROM Item WHERE c_code LIKE '%%%s%%'"),m_isearch);
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
			 m_item_List.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				m_item_List.SetItemText(p, i ,tmp);
			}
			rs.MoveNext(); 
		 }
	}
	rs.Close();
	db.Close();
}


BOOL CItemSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_isearchbtn.LoadBitmaps(IDB_BMP_SEARCH, NULL, NULL, NULL);
	m_isearchbtn.SizeToContent();
	m_item_List.SetExtendedStyle(LVS_EX_FULLROWSELECT); //����ü����
	
	if(m_item_List.GetHeaderCtrl()->GetItemCount() <= 0)		//����� �������� ���ٸ�
	{
		CRect rect;
		m_item_List.GetClientRect(&rect);
		m_item_List.InsertColumn(0, _T("�����"),			LVCFMT_LEFT, 80);
		m_item_List.InsertColumn(1, _T("��ǰ�ڵ�"),			LVCFMT_LEFT, 80);
		m_item_List.InsertColumn(2, _T("��ǰ��"),			LVCFMT_LEFT, 80);
		m_item_List.InsertColumn(3, _T("��з�"),			LVCFMT_LEFT, 80);
		m_item_List.InsertColumn(4, _T("�ߺз�"),			    LVCFMT_LEFT, 80);
		m_item_List.InsertColumn(5, _T("�Һз�"),			    LVCFMT_LEFT, 80);
		m_item_List.InsertColumn(6, _T("�ŷ�ó��"),			LVCFMT_LEFT, 80);
		m_item_List.InsertColumn(7, _T("�ŷ�ó�ڵ�"),			LVCFMT_LEFT, 80);
		m_item_List.InsertColumn(8, _T("�԰���"),			    LVCFMT_LEFT, 80);
		m_item_List.InsertColumn(9, _T("�԰����"),	LVCFMT_LEFT, 80);
		m_item_List.InsertColumn(10, _T("���԰�"),	LVCFMT_LEFT, 80);
		m_item_List.InsertColumn(11, _T("�Ǹűݾ�"),	LVCFMT_LEFT, 80);
	}
	
	 m_isearch_combo.AddString(_T("��ü�˻�"));
	 m_isearch_combo.AddString(_T("��ǰ�ڵ�"));                   //�ؽ�Ʈ �߰�
	 m_isearch_combo.AddString(_T("��ǰ��"));
	 m_isearch_combo.AddString(_T("ȸ���ڵ�"));
	
	m_isearch_combo.SetCurSel(0);
	
	//��� ��Ʈ�� �巡��-��-��� ����
	DWORD dwExStyle = m_item_List.GetExtendedStyle();
	m_item_List.SetExtendedStyle(dwExStyle | LVS_EX_HEADERDRAGDROP );
	
	m_bAscending = FALSE;
	m_item_List.SortItems(&CItemSearchDlg::CompareItem, (DWORD_PTR)this);
	UpdateArrow();
	CFont    m_fontTitle;
	LOGFONT  lf; 

	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 17;
	::lstrcpy(lf.lfFaceName, _T("�����ٸ����"));
	m_fontTitle.CreateFontIndirect(&lf);
	GetDlgItem(IDC_COMBO_SEARCH)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_LIST1)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 

		if(m_item_List.GetItemCount() > 0) m_item_List.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
		strQuery.Format(_T("SELECT item_id, i_code, i_name, i_large, i_medium, i_small, c_name, c_code, i_inputDate, i_inputAmount, i_inputPrice, i_outputPrice FROM Item"));
		
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
			 m_item_List.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				// ù��° ���ڴ� InsertValue�� ���ؼ� ������ �� ������ �Ǵ� ����, �ι�° ���ڴ� �������� �ϳ��� 
				m_item_List.SetItemText(p, i ,tmp);
			}
			rs.MoveNext();	//���������� �̵�
		 }
	}
	rs.Close();	//���ڵ�� ��ü �Ҹ�
	db.Close();	//�����ͺ��̽� ��ü �Ҹ�
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CItemSearchDlg::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nColumn = phdr->iItem;
	// ���� ����Ʈ ��Ʈ�ѿ� �ִ� ������ �� �ڷ� ������ŭ ����
	 for(int i=0; i< (m_item_List.GetItemCount()); i++)
	{
	 m_item_List.SetItemData(i, i);
	}

	// ���� ��� ����(Ascend, Descend)
	 m_bAscending = !m_bAscending;

	 UpdateArrow();

	// ���� ���õ� ����ü ���� ���� �� ������ �ʱ�ȭ
	SORTPARAM sortparams;
	sortparams.pList = &m_item_List;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending;

	// ���� �Լ� ȣ��
	m_item_List.SortItems(&CompareItem, (LPARAM)&sortparams );
	*pResult = 0;
}


void CItemSearchDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    nListIndex = pNMListView->iItem;
	UpdateData();
	m_iname = m_item_List.GetItemText(nListIndex,2);
	m_icode = m_item_List.GetItemText(nListIndex,1);
	m_cname = m_item_List.GetItemText(nListIndex,6);
	m_ccode = m_item_List.GetItemText(nListIndex,7);
	m_combo1 = m_item_List.GetItemText(nListIndex,3);
	m_combo2 = m_item_List.GetItemText(nListIndex,4);
	m_combo3 = m_item_List.GetItemText(nListIndex,5);
	m_inprice = m_item_List.GetItemText(nListIndex,10);
	m_outprice = m_item_List.GetItemText(nListIndex,11);
	m_inamount = m_item_List.GetItemText(nListIndex,9);
	m_inDate = m_item_List.GetItemText(nListIndex,8);
	*pResult = 0;
	CDialogEx::OnOK();
}


void CItemSearchDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.

}

int CALLBACK CItemSearchDlg::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl *pListCtrl = ((SORTPARAM *)lParamSort)->pList;

	int iSortColumn = ((SORTPARAM *)lParamSort)->iSortColumn;
	bool bSortDirect = ((SORTPARAM *)lParamSort)->bSortDirect;

	CString    strItem1 = pListCtrl->GetItemText(static_cast<int>(lParam1), iSortColumn);
	CString    strItem2 = pListCtrl->GetItemText(static_cast<int>(lParam2), iSortColumn);

	return bSortDirect ? _tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2) : -_tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2);


}

void CItemSearchDlg::UpdateArrow(void)
{
	CHeaderCtrl* pHeaderCtrl = m_item_List.GetHeaderCtrl();
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

HCURSOR CItemSearchDlg::OnQueryDragIcon()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CDialogEx::OnQueryDragIcon();
}


void CItemSearchDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialogEx::OnSysCommand(nID, lParam);
}


BOOL CItemSearchDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CRect rt;
    GetClientRect(&rt);  // Ŭ���̾�Ʈ ������ ũ�� ���
	pDC->FillSolidRect(&rt, RGB(247, 246, 238));  

	return TRUE; 

	return CDialogEx::OnEraseBkgnd(pDC);
}
