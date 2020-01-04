// ItemSearchPage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ItemSearchPage.h"
#include "afxdialogex.h"
#include "XLEzAutomation.h"

// CItemSearchPage ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CItemSearchPage, CPropertyPage)

CItemSearchPage::CItemSearchPage()
	: CPropertyPage(CItemSearchPage::IDD)
	, m_isearch(_T(""))
{

}

CItemSearchPage::~CItemSearchPage()
{
}

void CItemSearchPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT7, m_isearch);
	DDX_Control(pDX, IDC_COMBO_SEARCH, m_icombosearch);
	DDX_Control(pDX, IDC_LIST1, m_is_list);
	DDX_Control(pDX, SEARCHBTN, m_search_btn);
	DDX_Control(pDX, IDC_BUTTON1, m_excelbtn);
	DDX_Control(pDX, IDC_BUTTON2, m_clearbtn);
}


BEGIN_MESSAGE_MAP(CItemSearchPage, CPropertyPage)
	ON_BN_CLICKED(SEARCHBTN, &CItemSearchPage::OnBnClickedItemSearchbtn)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CItemSearchPage::OnHdnItemclickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CItemSearchPage::OnNMDblclkList1)
	ON_COMMAND(ID_ITEM_DELETE, &CItemSearchPage::OnItemDelete)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CItemSearchPage::OnNMRClickList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CItemSearchPage::OnBnClickedExcelSave)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, OnCustomdrawList)
	ON_BN_CLICKED(IDC_BUTTON2, &CItemSearchPage::OnBnClickedClear)
END_MESSAGE_MAP()


// CItemSearchPage �޽��� ó�����Դϴ�.
void CItemSearchPage::OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult)
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


void CItemSearchPage::OnBnClickedItemSearchbtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(true);

	if(m_is_list.GetItemCount() > 0) m_is_list.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
			
		int nIndex = m_icombosearch.GetCurSel();
		if(nIndex == 0){
			strQuery.Format(_T("SELECT item_id, i_code, i_name, i_large, i_medium, i_small, c_name, c_code, i_inputDate, i_inputAmount, i_inputPrice, i_outputPrice FROM Item WHERE i_code LIKE '%%%s%%' OR i_name LIKE '%%%s%%' OR i_large LIKE '%%%s%%' OR i_medium LIKE '%%%s%%' OR i_small LIKE '%%%s%%' OR item_id LIKE '%%%s%%' OR i_inputDate LIKE '%%%s%%'"),
				m_isearch,m_isearch,m_isearch,m_isearch,m_isearch,m_isearch,m_isearch);
			result.Format(_T("��ü�˻�-('%s')�˻���_"),m_isearch);
		}
		if(nIndex == 1){
			strQuery.Format(_T("SELECT item_id, i_code, i_name, i_large, i_medium, i_small, c_name, c_code, i_inputDate, i_inputAmount, i_inputPrice, i_outputPrice FROM Item WHERE i_code LIKE '%%%s%%'"),m_isearch);
			result.Format(_T("��ǰ �ڵ�-('%s')�˻���_"),m_isearch);
		}
		if(nIndex == 2){
			strQuery.Format(_T("SELECT item_id, i_code, i_name, i_large, i_medium, i_small, c_name, c_code, i_inputDate, i_inputAmount, i_inputPrice, i_outputPrice FROM Item WHERE i_name LIKE '%%%s%%'"),m_isearch);
			result.Format(_T("��ǰ��-('%s')�˻���_"),m_isearch);
		}
		if(nIndex == 3){
			strQuery.Format(_T("SELECT item_id, i_code, i_name, i_large, i_medium, i_small, c_name, c_code, i_inputDate, i_inputAmount, i_inputPrice, i_outputPrice FROM Item WHERE c_code LIKE '%%%s%%'"),m_isearch);
			result.Format(_T("�ŷ�ó �ڵ�-('%s')�˻���_"),m_isearch);
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
			 m_is_list.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				m_is_list.SetItemText(p, i ,tmp);
			}
			rs.MoveNext(); 
		 }
	}
	rs.Close();
	db.Close();
}


BOOL CItemSearchPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_search_btn.LoadBitmaps(IDB_BMP_SEARCH, NULL, NULL, NULL);
	m_search_btn.SizeToContent();
	m_excelbtn.LoadBitmaps(IDB_BMP_EXCEL, NULL, NULL, NULL);
	m_excelbtn.SizeToContent();
	m_clearbtn.LoadBitmaps(IDB_BMP_CLEAR, NULL, NULL, NULL);
	m_clearbtn.SizeToContent();

	m_is_list.SetExtendedStyle(LVS_EX_FULLROWSELECT); //����ü����
	
	if(m_is_list.GetHeaderCtrl()->GetItemCount() <= 0)		//����� �������� ���ٸ�
	{
		CRect rect;
		m_is_list.GetClientRect(&rect);
		m_is_list.InsertColumn(0, _T("�����"),			LVCFMT_LEFT, 110);
		m_is_list.InsertColumn(1, _T("��ǰ�ڵ�"),			LVCFMT_LEFT, 80);
		m_is_list.InsertColumn(2, _T("��ǰ��"),			LVCFMT_LEFT, 80);
		m_is_list.InsertColumn(3, _T("��з�"),			LVCFMT_LEFT, 80);
		m_is_list.InsertColumn(4, _T("�ߺз�"),			    LVCFMT_LEFT, 80);
		m_is_list.InsertColumn(5, _T("�Һз�"),			    LVCFMT_LEFT, 80);
		m_is_list.InsertColumn(6, _T("�ŷ�ó��"),			LVCFMT_LEFT, 80);
		m_is_list.InsertColumn(7, _T("�ŷ�ó�ڵ�"),			LVCFMT_LEFT, 80);
		m_is_list.InsertColumn(8, _T("�԰���"),			    LVCFMT_LEFT, 80);
		m_is_list.InsertColumn(9, _T("�԰����"),	LVCFMT_LEFT, 80);
		m_is_list.InsertColumn(10, _T("���԰�"),	LVCFMT_LEFT, 80);
		m_is_list.InsertColumn(11, _T("�Ǹűݾ�"),	LVCFMT_LEFT, 80);
	}
	
	 m_icombosearch.AddString(_T("��ü�˻�"));
	 m_icombosearch.AddString(_T("��ǰ�ڵ�"));                   //�ؽ�Ʈ �߰�
	 m_icombosearch.AddString(_T("��ǰ��"));
	 m_icombosearch.AddString(_T("ȸ���ڵ�"));
	
	m_icombosearch.SetCurSel(0);
	
	//��� ��Ʈ�� �巡��-��-��� ����
	DWORD dwExStyle = m_is_list.GetExtendedStyle();
	m_is_list.SetExtendedStyle(dwExStyle | LVS_EX_HEADERDRAGDROP );
	
	m_bAscending = FALSE;
	m_is_list.SortItems(&CItemSearchPage::CompareItem, (DWORD_PTR)this);
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

		if(m_is_list.GetItemCount() > 0) m_is_list.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
		strQuery.Format(_T("SELECT item_id, i_code, i_name, i_large, i_medium, i_small, c_name, c_code, i_inputDate, i_inputAmount, i_inputPrice, i_outputPrice  FROM Item"));
		
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
			 m_is_list.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				// ù��° ���ڴ� InsertValue�� ���ؼ� ������ �� ������ �Ǵ� ����, �ι�° ���ڴ� �������� �ϳ��� 
				m_is_list.SetItemText(p, i ,tmp);
			}
			rs.MoveNext();	//���������� �̵�
		 }
	}
	rs.Close();	//���ڵ�� ��ü �Ҹ�
	db.Close();	//�����ͺ��̽� ��ü �Ҹ�

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


int CALLBACK CItemSearchPage::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl *pListCtrl = ((SORTPARAM *)lParamSort)->pList;

	int iSortColumn = ((SORTPARAM *)lParamSort)->iSortColumn;
	bool bSortDirect = ((SORTPARAM *)lParamSort)->bSortDirect;

	CString    strItem1 = pListCtrl->GetItemText(static_cast<int>(lParam1), iSortColumn);
	CString    strItem2 = pListCtrl->GetItemText(static_cast<int>(lParam2), iSortColumn);

	return bSortDirect ? _tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2) : -_tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2);


}

void CItemSearchPage::UpdateArrow(void)
{
	CHeaderCtrl* pHeaderCtrl = m_is_list.GetHeaderCtrl();
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

HCURSOR CItemSearchPage::OnQueryDragIcon()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CPropertyPage::OnQueryDragIcon();
}


void CItemSearchPage::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CPropertyPage::OnSysCommand(nID, lParam);
}


void CItemSearchPage::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nColumn = phdr->iItem;
	// ���� ����Ʈ ��Ʈ�ѿ� �ִ� ������ �� �ڷ� ������ŭ ����
	 for(int i=0; i< (m_is_list.GetItemCount()); i++)
	{
	 m_is_list.SetItemData(i, i);
	}

	// ���� ��� ����(Ascend, Descend)
	 m_bAscending = !m_bAscending;

	 UpdateArrow();

	// ���� ���õ� ����ü ���� ���� �� ������ �ʱ�ȭ
	SORTPARAM sortparams;
	sortparams.pList = &m_is_list;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending;

	// ���� �Լ� ȣ��
	m_is_list.SortItems(&CompareItem, (LPARAM)&sortparams );

	*pResult = 0;
}

#include "ItemSheetDlg.h"
void CItemSearchPage::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    nListIndex = pNMListView->iItem;

	g_set_icode = m_is_list.GetItemText(nListIndex,1);

	g_set_iname = m_is_list.GetItemText(nListIndex,2);
	g_set_iccode = m_is_list.GetItemText(nListIndex,7);
	g_set_icname = m_is_list.GetItemText(nListIndex,6);
	g_set_icount = m_is_list.GetItemText(nListIndex,9);
	g_set_iinput = m_is_list.GetItemText(nListIndex,10);
	g_set_ioutput = m_is_list.GetItemText(nListIndex,11);

	AfxExtractSubString(g_set_ibirth_Year,m_is_list.GetItemText(nListIndex,8), 0,'-');
	AfxExtractSubString(g_set_ibirth_Month,m_is_list.GetItemText(nListIndex,8), 1,'-');
	AfxExtractSubString(g_set_ibirth_Day,m_is_list.GetItemText(nListIndex,8), 2,'-');


	g_ilarge = m_is_list.GetItemText(nListIndex,3);
	g_iMiddle = m_is_list.GetItemText(nListIndex,4);
	g_iSmall = m_is_list.GetItemText(nListIndex,5);
	
	imgname_s.Format(_T("res\\item\\%s.bmp"),g_set_icode);
	

	CItemSheetDlg* pSheet = (CItemSheetDlg*)GetParent();
	pSheet->SetActivePage(2);
	*pResult = 0;
}


void CItemSearchPage::OnItemDelete()
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
			strQuery.Format(_T("DELETE * FROM Item WHERE i_code LIKE '%%%s%%' "),icode);
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
	

		if(m_is_list.GetItemCount() > 0) m_is_list.DeleteAllItems();

	CDatabase db1;			// �����ͺ��̽� ��ü ����
	CRecordset rs1 (&db1);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db1.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");
       
		CString strQuery;
		strQuery.Format(_T("SELECT item_id, i_code, i_name, i_large, i_medium, i_small, c_name, c_code, i_inputDate, i_inputAmount, i_inputPrice, i_outputPrice  FROM Item"));

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
			 m_is_list.InsertItem(p,tmp,0);
			 for(short i=1; i<col1; i++  )
			 {
				rs1.GetFieldValue(i, tmp);
				// ù��° ���ڴ� InsertValue�� ���ؼ� ������ �� ������ �Ǵ� ����, �ι�° ���ڴ� �������� �ϳ��� 
				m_is_list.SetItemText(p, i ,tmp);
			}
			rs1.MoveNext();	//���������� �̵�
		 }
	}
	rs1.Close();	//���ڵ�� ��ü �Ҹ�
	db1.Close();	//�����ͺ��̽� ��ü �Ҹ�
}


void CItemSearchPage::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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
	pContextMenu = muTemp.GetSubMenu(1);
	pContextMenu -> TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, ptInSrceen.x, ptInSrceen.y,this);
	}

	icode = m_is_list.GetItemText(nListIndex,1);

	*pResult = 0;
}


void CItemSearchPage::OnBnClickedExcelSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_is_list.GetItemCount() <= 0)
	{
		 AfxMessageBox(_T("��ȸ�� �����Ͱ� 0���̹Ƿ� ���� ���� �� �� �����ϴ�."));
		 return;
	}

	CTime timeNow = CTime::GetCurrentTime();
	CString strDateTime;
	strDateTime = timeNow.Format(_T("%Y-%m-%d_%H��%M��%S��"));
	CString strFileName;
	strFileName.Format(_T("%s��ǰ ��ȸ_%s"), result,strDateTime);

	CFileDialog fdlg(FALSE, _T("xlsx"), strFileName+_T(".xlsx"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("xlsx ���� (*.xlsx)|*.xlsx"), NULL);
	if (fdlg.DoModal() != IDOK) return;

	CXLEzAutomation xls(FALSE);  // FALSE : ó�� ������ ȭ�鿡 ������ �ʴ´�.

	int rowOffset = 2;
	int colOffset = 1;

	int rowCount = m_is_list.GetItemCount();
	CHeaderCtrl* pHeaderCtrl = m_is_list.GetHeaderCtrl();
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
			strItemText = m_is_list.GetItemText(rowIdx, colIdx);

			// �÷� ������
			xls.SetCellValue(colIdx + colOffset, rowIdx +1 + rowOffset, strItemText);
		}
	}

	xls.SaveFileAs(fdlg.GetPathName());

	xls.ReleaseExcel();
}


void CItemSearchPage::OnBnClickedClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_isearch=_T("");
	m_icombosearch.SetCurSel(0);                                //�ؽ�Ʈ ����
	OnInitDialog();
}

void CItemSearchPage::ReInitDialog()
{

	if(m_is_list.GetItemCount() > 0) m_is_list.DeleteAllItems();

	CDatabase db1;			// �����ͺ��̽� ��ü ����
	CRecordset rs1 (&db1);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db1.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");
       
		CString strQuery;
		strQuery.Format(_T("SELECT item_id, i_code, i_name, i_large, i_medium, i_small, c_name, c_code, i_inputDate, i_inputAmount, i_inputPrice, i_outputPrice  FROM Item"));

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
			 m_is_list.InsertItem(p,tmp,0);
			 for(short i=1; i<col1; i++  )
			 {
				rs1.GetFieldValue(i, tmp);
				// ù��° ���ڴ� InsertValue�� ���ؼ� ������ �� ������ �Ǵ� ����, �ι�° ���ڴ� �������� �ϳ��� 
				m_is_list.SetItemText(p, i ,tmp);
			}
			rs1.MoveNext();	//���������� �̵�
		 }
	}
	rs1.Close();	//���ڵ�� ��ü �Ҹ�
	db1.Close();	//�����ͺ��̽� ��ü �Ҹ�

	return;
}
