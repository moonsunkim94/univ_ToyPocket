// SalePage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "SalePage.h"
#include "afxdialogex.h"



// CSalePage ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSalePage, CPropertyPage)

CSalePage::CSalePage()
	: CPropertyPage(CSalePage::IDD)
	, m_ssearch(_T(""))
	, m_samount(_T(""))
	, m_sdate(COleDateTime::GetCurrentTime())
	, m_si_code(_T(""))
	, m_total_amount(_T(""))
	, m_si_name(_T(""))
	, m_outcname(_T(""))
{

}

CSalePage::~CSalePage()
{
}

void CSalePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCOMBO_SEARCH, m_scombosearch);
	DDX_Control(pDX, IDC_STATIC_INPUTDATE, m_static_inputdata);
	DDX_Control(pDX, IDC_LIST1, m_si_List);
	DDX_Text(pDX, IDC_EDIT7, m_ssearch);
	DDX_Control(pDX, IDC_EDIT8, m_sicode);
	DDX_Control(pDX, IDC_EDIT4, m_siname);
	DDX_Text(pDX, IDC_EDIT14, m_samount);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER3, m_sdate);
	DDX_Text(pDX, IDC_EDIT8, m_si_code);
	DDX_Control(pDX, SEARCHBTN, m_search_btn);
	DDX_Control(pDX, SALE_REGISTER, m_ok_btn);
	DDX_Control(pDX, IDCANCEL, m_cancel_btn);
	DDX_Text(pDX, IDC_AMOUNT, m_total_amount);
	DDX_Control(pDX, IDC_AMOUNT, m_totalamount_Edit);
	DDX_Control(pDX, IDC_SCOMBO1, m_combo1);
	DDX_Control(pDX, IDC_SCOMBO2, m_combo2);
	DDX_Control(pDX, IDC_SCOMBO3, m_combo3);
	DDX_Text(pDX, IDC_EDIT4, m_si_name);
	DDX_Control(pDX, IDC_IMAGE, m_siimage);
	DDX_Control(pDX, IDC_SCOM, m_cname_D);
	DDX_Text(pDX, IDC_SCOM, m_outcname);
	DDX_Control(pDX, SEARCHBTN2, m_comsearchbtn);
}


BEGIN_MESSAGE_MAP(CSalePage, CPropertyPage)
	ON_CBN_SELCHANGE(IDC_SCOMBO_SEARCH, &CSalePage::OnCbnSelchangeScomboSearch)
	ON_BN_CLICKED(SEARCHBTN, &CSalePage::OnBnClickedSearchbtn)
	ON_WM_PAINT()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CSalePage::OnNMDblclkList1)
	ON_BN_CLICKED(SALE_REGISTER, &CSalePage::OnBnClickedRegister)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CSalePage::OnHdnItemclickList1)
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(SEARCHBTN2, &CSalePage::OnBnClickedSearchbtn2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, OnCustomdrawList)
END_MESSAGE_MAP()


// CSalePage �޽��� ó�����Դϴ�.

void CSalePage::OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult)
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
BOOL CSalePage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_si_List.SetExtendedStyle(LVS_EX_FULLROWSELECT); //����ü����

	m_search_btn.LoadBitmaps(IDB_BMP_SEARCH, NULL, NULL, NULL);
	m_search_btn.SizeToContent();
	m_ok_btn.LoadBitmaps(IDB_BMP_OK, NULL, NULL, NULL);
	m_ok_btn.SizeToContent();
	m_cancel_btn.LoadBitmaps(IDB_BMP_CANCEL, NULL, NULL, NULL);
	m_cancel_btn.SizeToContent();
	m_comsearchbtn.LoadBitmaps(IDB_BMP_SEARCH, NULL, NULL, NULL);
	m_comsearchbtn.SizeToContent();
	
	if(m_si_List.GetHeaderCtrl()->GetItemCount() <= 0)		//����� �������� ���ٸ�
	{
		CRect rect;
		m_si_List.GetClientRect(&rect);
		m_si_List.InsertColumn(0, _T("�����"),			LVCFMT_LEFT, 100);
		m_si_List.InsertColumn(1, _T("��ǰ�ڵ�"),			LVCFMT_LEFT, 80);
		m_si_List.InsertColumn(2, _T("��ǰ��"),			LVCFMT_LEFT, 80);
		m_si_List.InsertColumn(3, _T("��з�"),			LVCFMT_LEFT, 80);
		m_si_List.InsertColumn(4, _T("�ߺз�"),			    LVCFMT_LEFT, 80);
		m_si_List.InsertColumn(5, _T("�Һз�"),			    LVCFMT_LEFT, 80);
		m_si_List.InsertColumn(6, _T("�ŷ�ó��"),			LVCFMT_LEFT, 80);
		m_si_List.InsertColumn(7, _T("�ŷ�ó�ڵ�"),			LVCFMT_LEFT, 80);
		m_si_List.InsertColumn(8, _T("�԰���"),			    LVCFMT_LEFT, 80);
		m_si_List.InsertColumn(9, _T("�԰����"),	LVCFMT_LEFT, 80);
		m_si_List.InsertColumn(10, _T("���԰�"),	LVCFMT_LEFT, 80);
		m_si_List.InsertColumn(11, _T("�Ǹűݾ�"),	LVCFMT_LEFT, 80);
	}

	m_scombosearch.AddString(_T("��ü�˻�"));
	m_scombosearch.AddString(_T("��ǰ��"));
	m_scombosearch.AddString(_T("�ŷ�ó��"));
	m_scombosearch.AddString(_T("�԰�¥"));

	m_scombosearch.SetCurSel(0);
	GetDlgItem(IDC_SCOMBO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCOMBO2)->EnableWindow(FALSE);	
	GetDlgItem(IDC_SCOMBO3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	GetDlgItem(IDC_AMOUNT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCOM)->EnableWindow(FALSE);

	GetDlgItem(IDC_STATIC_INPUTDATE)->ShowWindow(SW_HIDE);

	//��� ��Ʈ�� �巡��-��-��� ����
	DWORD dwExStyle = m_si_List.GetExtendedStyle();
	m_si_List.SetExtendedStyle(dwExStyle | LVS_EX_HEADERDRAGDROP );

	m_bAscending = FALSE;
	m_si_List.SortItems(&CSalePage::CompareItem, (DWORD_PTR)this);
	UpdateArrow();

	bFirst = TRUE;

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
	GetDlgItem(IDC_STATIC7)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC8)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC9)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_SCOMBO_SEARCH)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT7)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT4)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT8)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_LIST1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_SCOMBO1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_SCOMBO2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_SCOMBO3)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_AMOUNT)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT14)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_DATETIMEPICKER3)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_SCOM)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC_INPUTDATE)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC10)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 

	if(m_si_List.GetItemCount() > 0) m_si_List.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;	//�����ͺ��̽��� ������ ������
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
			 m_si_List.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);  
				// ù��° ���ڴ� InsertValue�� ���ؼ� ������ �� ������ �Ǵ� ����, �ι�° ���ڴ� �������� �ϳ��� 
				m_si_List.SetItemText(p, i ,tmp);
			}
			rs.MoveNext(); //���������� �̵�
		 }
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CSalePage::ReInitDialog2()
{
	if(m_si_List.GetItemCount() > 0) m_si_List.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;	//�����ͺ��̽��� ������ ������
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
			 m_si_List.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);  
				// ù��° ���ڴ� InsertValue�� ���ؼ� ������ �� ������ �Ǵ� ����, �ι�° ���ڴ� �������� �ϳ��� 
				m_si_List.SetItemText(p, i ,tmp);
			}
			rs.MoveNext(); //���������� �̵�
		 }
	}

	rs.Close();	//���ڵ�� ��ü �Ҹ�
	db.Close();	//�����ͺ��̽� ��ü �Ҹ�


}

int CALLBACK CSalePage::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl *pListCtrl = ((SORTPARAM *)lParamSort)->pList;

	int iSortColumn = ((SORTPARAM *)lParamSort)->iSortColumn;
	bool bSortDirect = ((SORTPARAM *)lParamSort)->bSortDirect;

	CString    strItem1 = pListCtrl->GetItemText(static_cast<int>(lParam1), iSortColumn);
	CString    strItem2 = pListCtrl->GetItemText(static_cast<int>(lParam2), iSortColumn);

	return bSortDirect ? _tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2) : -_tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2);


}

void CSalePage::UpdateArrow(void)
{
	CHeaderCtrl* pHeaderCtrl = m_si_List.GetHeaderCtrl();
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

void CSalePage::OnCbnSelchangeScomboSearch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int nIndex;
	nIndex = m_scombosearch.GetCurSel();   // ���� ���õ� �׸��� �ε����� ����

	if(nIndex == 3)
   {
	   GetDlgItem(IDC_STATIC_INPUTDATE)->ShowWindow(SW_SHOW);
   }
	else
		GetDlgItem(IDC_STATIC_INPUTDATE)->ShowWindow(SW_HIDE);
}

void CSalePage::OnBnClickedSearchbtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(true);

	if(m_si_List.GetItemCount() > 0) m_si_List.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
			
		int nIndex = m_scombosearch.GetCurSel();
		if(nIndex == 0){
			strQuery.Format(_T("SELECT item_id, i_code, i_name, i_large, i_medium, i_small, c_name, c_code, i_inputDate, i_inputAmount, i_inputPrice, i_outputPrice FROM Item WHERE i_code LIKE '%%%s%%' OR i_name LIKE '%%%s%%' OR i_large LIKE '%%%s%%' OR i_medium LIKE '%%%s%%' OR i_small LIKE '%%%s%%' OR item_id LIKE '%%%s%%' OR i_inputDate LIKE '%%%s%%'"),
				m_ssearch,m_ssearch,m_ssearch,m_ssearch,m_ssearch,m_ssearch,m_ssearch);
		}
		if(nIndex == 1){
			strQuery.Format(_T("SELECT item_id, i_code, i_name, i_large, i_medium, i_small, c_name, c_code, i_inputDate, i_inputAmount, i_inputPrice, i_outputPrice FROM Item WHERE i_cname LIKE '%%%s%%'"),m_ssearch);
		}
		if(nIndex == 2){
			strQuery.Format(_T("SELECT item_id, i_code, i_name, i_large, i_medium, i_small, c_name, c_code, i_inputDate, i_inputAmount, i_inputPrice, i_outputPrice FROM Item WHERE c_code LIKE '%%%s%%'"),m_ssearch);
		}
		if(nIndex == 3){
			strQuery.Format(_T("SELECT item_id, i_code, i_name, i_large, i_medium, i_small, c_name, c_code, i_inputDate, i_inputAmount, i_inputPrice, i_outputPrice FROM Item WHERE i_inputDate LIKE '%%%s%%'"),m_ssearch);
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
			 m_si_List.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				m_si_List.SetItemText(p, i ,tmp);
			}
			rs.MoveNext(); 
		 }
	}
	rs.Close();
	db.Close();
}


void CSalePage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	if(bFirst){
		CString img;
		img.Format(_T("res\\NoImage.bmp"));
		DrawBMP(img);
		//bFirst = FALSE;
	}
	// �׸��� �޽����� ���ؼ��� CPropertyPage::OnPaint()��(��) ȣ������ ���ʽÿ�.
}


void CSalePage::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    nListIndex = pNMListView->iItem;

	m_sicode.SetWindowTextW(m_si_List.GetItemText(nListIndex,1));
	m_siname.SetWindowTextW(m_si_List.GetItemText(nListIndex,2));
	m_totalamount_Edit.SetWindowTextW(m_si_List.GetItemText(nListIndex,9));
	GetDlgItem(IDC_SCOMBO1)->SetWindowTextW(m_si_List.GetItemText(nListIndex,3));
	GetDlgItem(IDC_SCOMBO2)->SetWindowTextW(m_si_List.GetItemText(nListIndex,4));
	GetDlgItem(IDC_SCOMBO3)->SetWindowTextW(m_si_List.GetItemText(nListIndex,5));
	
	m_icode= m_si_List.GetItemText(nListIndex,1);
	m_icount = m_si_List.GetItemText(nListIndex,9);
	m_iccode = m_si_List.GetItemText(nListIndex,7);
	m_iinputprice = m_si_List.GetItemText(nListIndex,10);
	m_iOutputprice = m_si_List.GetItemText(nListIndex,11);

	imgname.Format(_T("res\\item\\%s.bmp"),m_icode);
	DrawBMP(imgname);

	*pResult = 0;
}


void CSalePage::OnBnClickedRegister()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(!UpdateData()) return;
	UpdateData(TRUE);


	//�Ǹų�¥

	CString sdate;
		sdate.Format(_T("%d-%02d-%02d"),m_sdate.GetYear(),m_sdate.GetMonth(),m_sdate.GetDay());


	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	

	CString amount;		//���������
	amount.Format(_T("%d"), _ttoi(m_icount) - _ttoi(m_samount));

	CString total_price;
	total_price.Format(_T("%d"), _ttoi(m_samount) * _ttoi(m_iOutputprice));
	CString s;


	if(_ttoi(m_samount) < _ttoi(m_icount)){  //�Ǹż��� < ��ǰ����
		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("�����ͺ��̽� ���ӽ���!");

			CString strQuery;	//�����ͺ��̽��� ������ ������
			strQuery.Format(_T("INSERT INTO Sale (s_outputDate , in_ccode, out_ccode, i_code , s_outputAmount, i_inputPrice, i_outputPrice, order_total, return_YN, return_date, return_reson, exchange_YN, exchange_date, exchange_reason, delivery_YN, delivery_process, sale_id)  VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '�ƴϿ�', \
							   '�ش����', '�ش����', '�ƴϿ�', '�ش����', '�ش����', '�ƴϿ�', '�ش����', '%s')"), 
							   sdate,m_iccode, m_outccode, m_si_code,m_samount,m_iinputprice,m_iOutputprice,total_price , g_setid);
			db.ExecuteSQL(strQuery);	//�����ͺ��̽��� ������ ����

			strQuery.Format(_T("UPDATE Item SET i_inputAmount = '%s' WHERE i_code = '%s'"), amount, m_icode);
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
		//OnBnClickedClear();	//��Ʈ�� �ʱ�ȭ
		AfxMessageBox(_T("�ǸŵǾ����ϴ�."));
		m_ssearch = _T("");
		m_si_code = _T("");
		m_si_name = _T("");
		m_total_amount = _T("");
		m_outcname = _T("");
		m_samount = _T("");
		//�����ʱ�ȭ
		CDateTimeCtrl *pCtrl = (CDateTimeCtrl *) GetDlgItem(IDC_DATETIMEPICKER3);
		CTime tm = CTime::GetCurrentTime();
		pCtrl->SetTime(&tm);

		
		m_scombosearch.SetCurSel(0);
		m_combo1.SetCurSel(-1);
		m_combo2.SetCurSel(-1);
		m_combo3.SetCurSel(-1);

		//�̹����ʱ�ȭ
		CString img;
		img.Format(_T("res\\NoImage.bmp"));
		DrawBMP(img);

	}else{    //�Ǹż����� ���������� ���� ��
		AfxMessageBox(_T("�Ǹŵ� �� �����ϴ�."));
		m_samount = _T("");
	}
		
		UpdateData(false);
}


void CSalePage::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int nColumn = phdr->iItem;
	// ���� ����Ʈ ��Ʈ�ѿ� �ִ� ������ �� �ڷ� ������ŭ ����
	 for(int i=0; i< (m_si_List.GetItemCount()); i++)
	{
	 m_si_List.SetItemData(i, i);
	}

	// ���� ��� ����(Ascend, Descend)
	 m_bAscending = !m_bAscending;
	 UpdateArrow();

	// ���� ���õ� ����ü ���� ���� �� ������ �ʱ�ȭ
	SORTPARAM sortparams;
	sortparams.pList = &m_si_List;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending;

	// ���� �Լ� ȣ��
	m_si_List.SortItems(&CompareItem, (LPARAM)&sortparams );

	*pResult = 0;
}


HCURSOR CSalePage::OnQueryDragIcon()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CPropertyPage::OnQueryDragIcon();
}


void CSalePage::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CPropertyPage::OnSysCommand(nID, lParam);
}

void CSalePage::DrawBMP(LPCTSTR lpszFileName)	//�̹��� �����ֱ�
{
	CDC* pDC = GetDC();//ȭ�� DC�� ��� ��
	CDC MemDC;//�޸� DC
	CBitmap bmp, *pOldBmp;
	BITMAP bm;//��Ʈ�� ������ �����ϴ� ����
	CRect rect;
	CPoint cp;

	//�̹��� ���� �ε�
	bmp.m_hObject = (HBITMAP)LoadImage(NULL, lpszFileName, IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
	if(bmp.m_hObject == NULL) return;
	bmp.GetBitmap(&bm);//�ε��� �̹��� ������ ���¸� ����
	MemDC.CreateCompatibleDC(pDC);//�޸� DC�� ȭ�� DC�� ȣȯ���ֵ��� ����
	pOldBmp = MemDC.SelectObject(&bmp);//�޸𸮿� ����� �̹��� ����

	m_siimage.GetWindowRect(&rect);//���̾�α׿� ��ġ�� ��Ʈ���� ũ�⸦ ��� ��
	cp.x = rect.left;//�̹��� ����� ���� ���� x ��ǥ
	cp.y = rect.top;//�̹��� ����� ���� ���� y ��ǥ 
	ScreenToClient(&cp);//cp�� ������ �ִ� ��ǥ�� ȭ���� ������
	pDC->StretchBlt(cp.x,cp.y,rect.Width(),rect.Height() ,&MemDC,0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);//�̹����� �ش� ��Ʈ�ѷ� ����
	MemDC.SelectObject(pOldBmp);
	ReleaseDC(pDC);//DC ��ȯ
}

#include "SaleComSearchDlg.h"


void CSalePage::OnBnClickedSearchbtn2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CSaleComSearchDlg pDlg;
	pDlg.DoModal();
	m_cname_D.SetWindowTextW(pDlg.m_cnameset);
	m_outccode = pDlg.m_ccodeset;
	//m_outcname = pDlg.m_cnameset;
}
