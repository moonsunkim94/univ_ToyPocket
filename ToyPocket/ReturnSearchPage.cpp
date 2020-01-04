// ReturnSearchPage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ReturnSearchPage.h"
#include "afxdialogex.h"
#include "XLEzAutomation.h"

// CReturnSearchPage ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CReturnSearchPage, CPropertyPage)

CReturnSearchPage::CReturnSearchPage()
	: CPropertyPage(CReturnSearchPage::IDD)
	, m_res_Search(_T(""))
{

}

CReturnSearchPage::~CReturnSearchPage()
{
}

void CReturnSearchPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_re_list);
	DDX_Control(pDX, IDC_COMBO_SEARCH, m_res_Combo);
	DDX_Text(pDX, IDC_EDIT7, m_res_Search);
	DDX_Control(pDX, IDOK, m_researchbtn);
	DDX_Control(pDX, IDC_BUTTON1, m_excelbtn);
	DDX_Control(pDX, IDC_BUTTON2, m_clearbtn);
}


BEGIN_MESSAGE_MAP(CReturnSearchPage, CPropertyPage)
	ON_CBN_SELCHANGE(IDC_COMBO_SEARCH, &CReturnSearchPage::OnCbnSelchangeComboSearch)
	ON_BN_CLICKED(IDOK, &CReturnSearchPage::OnBnClickedOk)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CReturnSearchPage::OnNMRClickList1)
	ON_COMMAND(ID_RETURN_DELETE, &CReturnSearchPage::OnReturnDelete)
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CReturnSearchPage::OnHdnItemclickList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CReturnSearchPage::OnBnClickedExcelSave)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, OnCustomdrawList)
	ON_BN_CLICKED(IDC_BUTTON2, &CReturnSearchPage::OnBnClickedClear)
END_MESSAGE_MAP()


// CReturnSearchPage �޽��� ó�����Դϴ�.

void CReturnSearchPage::OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult)
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

BOOL CReturnSearchPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
		m_re_list.SetExtendedStyle(LVS_EX_FULLROWSELECT); //����ü����

	if(m_re_list.GetHeaderCtrl()->GetItemCount() <= 0)		//����� �������� ���ٸ�
	{
		CRect rect;
		m_re_list.GetClientRect(&rect);
		m_re_list.InsertColumn(0, _T(""),			LVCFMT_LEFT, 0);
		m_re_list.InsertColumn(1, _T("�����"),	LVCFMT_LEFT, 100);
		m_re_list.InsertColumn(2, _T("�Ǹų�¥"),			LVCFMT_LEFT, 120);
		m_re_list.InsertColumn(4, _T("����ó�ڵ�"),			LVCFMT_LEFT, 80);
		m_re_list.InsertColumn(5, _T("��ǰó�ڵ�"),			LVCFMT_LEFT, 80);
		m_re_list.InsertColumn(6, _T("��ǰ�ڵ�"),			LVCFMT_LEFT, 80);
		m_re_list.InsertColumn(7, _T("��ǰ����"),			    LVCFMT_LEFT, 80);
		m_re_list.InsertColumn(8, _T("��ǰ��¥"),			LVCFMT_LEFT, 80);
		m_re_list.InsertColumn(9, _T("��ǰ����"),			    LVCFMT_LEFT, 80);
		m_re_list.InsertColumn(10, _T("���԰�"),			    LVCFMT_LEFT, 80);
		m_re_list.InsertColumn(11, _T("�ǸŰ�"),			LVCFMT_LEFT, 80);
		m_re_list.InsertColumn(12, _T("���ֹ��ݾ�"),			LVCFMT_LEFT, 80);
	}

	m_res_Combo.AddString(_T("��ü�˻�"));
	m_res_Combo.AddString(_T("��ǰ��¥"));
	m_res_Combo.AddString(_T("��ǰ�ڵ�"));
	m_res_Combo.AddString(_T("��ǰó�ڵ�"));

	m_res_Combo.SetCurSel(0);

	GetDlgItem(IDC_STATIC_INPUTDATE)->ShowWindow(SW_HIDE);

	//��� ��Ʈ�� �巡��-��-��� ����
	DWORD dwExStyle = m_re_list.GetExtendedStyle();
	m_re_list.SetExtendedStyle(dwExStyle | LVS_EX_HEADERDRAGDROP );

	m_bAscending = FALSE;

	m_re_list.SortItems(&CReturnSearchPage::CompareItem, (DWORD_PTR)this);
	UpdateArrow();

	m_researchbtn.LoadBitmaps(IDB_BMP_SEARCH, NULL, NULL, NULL);
	m_researchbtn.SizeToContent(); 
	m_excelbtn.LoadBitmaps(IDB_BMP_EXCEL, NULL, NULL, NULL);
	m_excelbtn.SizeToContent();
	m_clearbtn.LoadBitmaps(IDB_BMP_CLEAR, NULL, NULL, NULL);
	m_clearbtn.SizeToContent();

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

	if(m_re_list.GetItemCount() > 0) m_re_list.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;	//�����ͺ��̽��� ������ ������
		strQuery.Format(_T("SELECT s_Key, sale_id, s_outputDate, in_ccode, out_ccode, i_code, s_outputAmount, return_date, return_reson, i_inputPrice, i_outputPrice, order_total FROM Sale WHERE return_YN= '��'"));
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
			 m_re_list.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);  
				// ù��° ���ڴ� InsertValue�� ���ؼ� ������ �� ������ �Ǵ� ����, �ι�° ���ڴ� �������� �ϳ��� 
				m_re_list.SetItemText(p, i ,tmp);
			}
			rs.MoveNext(); //���������� �̵�
		 }
	}
	rs.Close();	//���ڵ�� ��ü �Ҹ�
	db.Close();	//�����ͺ��̽� ��ü �Ҹ�

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

int CALLBACK CReturnSearchPage::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl *pListCtrl = ((SORTPARAM *)lParamSort)->pList;

	int iSortColumn = ((SORTPARAM *)lParamSort)->iSortColumn;
	bool bSortDirect = ((SORTPARAM *)lParamSort)->bSortDirect;

	CString    strItem1 = pListCtrl->GetItemText(static_cast<int>(lParam1), iSortColumn);
	CString    strItem2 = pListCtrl->GetItemText(static_cast<int>(lParam2), iSortColumn);

	return bSortDirect ? _tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2) : -_tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2);


}

void CReturnSearchPage::UpdateArrow(void)
{
	CHeaderCtrl* pHeaderCtrl = m_re_list.GetHeaderCtrl();
	HDITEM hdItem;
	TCHAR szBuffer[256];
	::ZeroMemory(&hdItem, sizeof(hdItem));
	::ZeroMemory(szBuffer, 256);

	hdItem.mask = -1;
	hdItem.pszText = szBuffer;
	hdItem.cchTextMax = 256;
	pHeaderCtrl->GetItem(1, &hdItem);

	hdItem.fmt &= ~(HDF_SORTDOWN | HDF_SORTUP);

	if(m_bAscending)	hdItem.fmt |= HDF_SORTDOWN;
	else				hdItem.fmt |= HDF_SORTUP;
	pHeaderCtrl->SetItem(1, &hdItem);
}


void CReturnSearchPage::OnCbnSelchangeComboSearch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nIndex;
	nIndex = m_res_Combo.GetCurSel();   // ���� ���õ� �׸��� �ε����� ����

	if(nIndex == 1)
   {
	   GetDlgItem(IDC_STATIC_INPUTDATE)->ShowWindow(SW_SHOW);
   }
	else
		GetDlgItem(IDC_STATIC_INPUTDATE)->ShowWindow(SW_HIDE);
}


void CReturnSearchPage::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
		
	UpdateData(true);

	if(m_re_list.GetItemCount() > 0) m_re_list.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
			
		int nIndex = m_res_Combo.GetCurSel();
		if(nIndex == 0){
			strQuery.Format(_T("SELECT  s_Key, sale_id, s_outputDate, in_ccode, out_ccode, i_code, s_outputAmount, return_date, return_reson, i_inputPrice, i_outputPrice, order_total FROM Sale \
							   WHERE s_outputDate LIKE '%%%s%%' OR in_ccode LIKE '%%%s%%' OR out_ccode LIKE '%%%s%%' OR i_code LIKE '%%%s%%' OR s_outputAmount LIKE '%%%s%%' OR i_inputPrice LIKE '%%%s%%' \
							   OR i_outputPrice LIKE '%%%s%%' OR order_total LIKE '%%%s%%' OR return_date LIKE '%%%s%%' OR return_reson LIKE '%%%s%%' \
							   OR sale_id LIKE '%%%s%%' AND Sale.return_YN = '��'"),
				m_res_Search,m_res_Search,m_res_Search,m_res_Search,m_res_Search,m_res_Search,m_res_Search,m_res_Search,m_res_Search,m_res_Search,m_res_Search);
			result.Format(_T("��ü�˻�-('%s')�˻���_"),m_res_Search);
		}
		if(nIndex == 1){
			strQuery.Format(_T("SELECT  s_Key, sale_id, s_outputDate,in_ccode, out_ccode,  i_code, s_outputAmount, return_date, return_reson, i_inputPrice, i_outputPrice, order_total FROM Sale WHERE return_date LIKE '%%%s%%' AND Sale.return_YN = '��'"),m_res_Search);
			result.Format(_T("��ǰ��¥-('%s')�˻���_"),m_res_Search);
		}
		if(nIndex == 2){
			strQuery.Format(_T("SELECT  s_Key, sale_id, s_outputDate, in_ccode, out_ccode,  i_code, s_outputAmount, return_date, return_reson, i_inputPrice, i_outputPrice, order_total FROM Sale WHERE i_code LIKE '%%%s%%'AND Sale.return_YN = '��'"),m_res_Search);
			result.Format(_T("��ǰ�ڵ�-('%s')�˻���_"),m_res_Search);
		}
		if(nIndex == 3){
			strQuery.Format(_T("SELECT  s_Key, sale_id, s_outputDate, in_ccode, out_ccode,  i_code, s_outputAmount, return_date, return_reson, i_inputPrice, i_outputPrice, order_total FROM Sale WHERE out_ccode LIKE '%%%s%%'AND Sale.return_YN = '��'"),m_res_Search);
			result.Format(_T("��ǰó�ڵ�-('%s')�˻���_"),m_res_Search);
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
			 m_re_list.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				m_re_list.SetItemText(p, i ,tmp);
			}
			rs.MoveNext(); 
		 }
	}
	rs.Close();
	db.Close();

}


void CReturnSearchPage::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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
	pContextMenu = muTemp.GetSubMenu(4);
	pContextMenu -> TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, ptInSrceen.x, ptInSrceen.y,this);
	}

	m_skey = _ttoi(m_re_list.GetItemText(nListIndex,0));
	*pResult = 0;
}


void CReturnSearchPage::OnReturnDelete()
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
			strQuery.Format(_T("DELETE * FROM Sale WHERE Sale.s_Key= %d "),m_skey);
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

	if(m_re_list.GetItemCount() > 0) m_re_list.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;	//�����ͺ��̽��� ������ ������
		strQuery.Format(_T("SELECT s_Key, sale_id, s_outputDate, in_ccode, out_ccode, i_code, s_outputAmount, return_date, return_reson, i_inputPrice, i_outputPrice, order_total FROM Sale WHERE return_YN= '��'"));
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
			 m_re_list.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);  
				// ù��° ���ڴ� InsertValue�� ���ؼ� ������ �� ������ �Ǵ� ����, �ι�° ���ڴ� �������� �ϳ��� 
				m_re_list.SetItemText(p, i ,tmp);
			}
			rs.MoveNext(); //���������� �̵�
		 }
	}
	rs.Close();	//���ڵ�� ��ü �Ҹ�
	db.Close();	//�����ͺ��̽� ��ü �Ҹ�

}


HCURSOR CReturnSearchPage::OnQueryDragIcon()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CPropertyPage::OnQueryDragIcon();
}


void CReturnSearchPage::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CPropertyPage::OnSysCommand(nID, lParam);
}


void CReturnSearchPage::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nColumn = phdr->iItem;
	// ���� ����Ʈ ��Ʈ�ѿ� �ִ� ������ �� �ڷ� ������ŭ ����
	 for(int i=0; i< (m_re_list.GetItemCount()); i++)
	{
	 m_re_list.SetItemData(i, i);
	}

	// ���� ��� ����(Ascend, Descend)
	 m_bAscending = !m_bAscending;
	 UpdateArrow();

	// ���� ���õ� ����ü ���� ���� �� ������ �ʱ�ȭ
	SORTPARAM sortparams;
	sortparams.pList = &m_re_list;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending;

	// ���� �Լ� ȣ��
	m_re_list.SortItems(&CompareItem, (LPARAM)&sortparams );

	*pResult = 0;
}


void CReturnSearchPage::OnBnClickedExcelSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_re_list.GetItemCount() <= 0)
	{
		 AfxMessageBox(_T("��ȸ�� �����Ͱ� 0���̹Ƿ� ���� ���� �� �� �����ϴ�."));
		 return;
	}

	CTime timeNow = CTime::GetCurrentTime();
	CString strDateTime;
	strDateTime = timeNow.Format(_T("%Y-%m-%d_%H��%M��%S��"));
	CString strFileName;
	strFileName.Format(_T("%s��ǰ ��ȸ_%s"), result, strDateTime);

	CFileDialog fdlg(FALSE, _T("xlsx"), strFileName+_T(".xlsx"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("xlsx ���� (*.xlsx)|*.xlsx"), NULL);
	if (fdlg.DoModal() != IDOK) return;

	CXLEzAutomation xls(FALSE);  // FALSE : ó�� ������ ȭ�鿡 ������ �ʴ´�.

	int rowOffset = 2;
	int colOffset = 1;

	int rowCount = m_re_list.GetItemCount();
	CHeaderCtrl* pHeaderCtrl = m_re_list.GetHeaderCtrl();
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
			strItemText = m_re_list.GetItemText(rowIdx, colIdx);

			// �÷� ������
			xls.SetCellValue(colIdx + colOffset, rowIdx +1 + rowOffset, strItemText);
		}
	}

	xls.SaveFileAs(fdlg.GetPathName());

	xls.ReleaseExcel();
}


void CReturnSearchPage::OnBnClickedClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_res_Search=_T("");
	m_res_Combo.SetCurSel(0);                                //�ؽ�Ʈ ����
	OnInitDialog();
}
