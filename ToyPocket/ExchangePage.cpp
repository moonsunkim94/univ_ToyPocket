// ExchangePage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ExchangePage.h"
#include "afxdialogex.h"


// CExchangePage ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CExchangePage, CPropertyPage)

CExchangePage::CExchangePage()
	: CPropertyPage(CExchangePage::IDD)
	, m_exSearch(_T(""))
	, m_sscode(_T(""))
	, m_sicode(_T(""))
	, m_sdate(COleDateTime::GetCurrentTime())
	, m_sAmount(_T(""))
	, m_exAmount(_T(""))
	, m_exDate(COleDateTime::GetCurrentTime())
	, m_exReason(_T(""))
{

}

CExchangePage::~CExchangePage()
{

}

void CExchangePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCOMBO_SEARCH, m_exCombo);
	DDX_Text(pDX, IDC_EDIT12, m_exSearch);
	DDX_Control(pDX, IDC_LIST1, m_exList);
	DDX_Control(pDX, IDC_EDIT16, m_sccode_Edit);
	DDX_Control(pDX, IDC_EDIT7, m_sicode_Edit);
	DDX_Control(pDX, IDC_DATETIMEPICKER4, m_sDate_ctrl);
	DDX_Control(pDX, IDC_EDIT18, m_sAmount_Edit);
	DDX_Text(pDX, IDC_EDIT16, m_sscode);
	DDX_Text(pDX, IDC_EDIT7, m_sicode);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER4, m_sdate);
	DDX_Text(pDX, IDC_EDIT18, m_sAmount);
	DDX_Text(pDX, IDC_EDIT8, m_exAmount);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER5, m_exDate);
	DDX_Control(pDX, IDC_COMBO2, m_exReason_Combo);
	DDX_Text(pDX, IDC_EDIT10, m_exReason);
	DDX_Control(pDX, IDC_EDIT8, m_exAmount_Edit);
	DDX_Control(pDX, IDC_IMAGE, m_eiimage);
	DDX_Control(pDX, SEARCHBTN, m_exsearchbtn);
	DDX_Control(pDX, IDOK, m_exokbtn);
	DDX_Control(pDX, IDCANCEL, m_excancelbtn);
}


BEGIN_MESSAGE_MAP(CExchangePage, CPropertyPage)
	ON_BN_CLICKED(SEARCHBTN, &CExchangePage::OnBnClickedSearchbtn)
	ON_BN_CLICKED(IDOK, &CExchangePage::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_SCOMBO_SEARCH, &CExchangePage::OnCbnSelchangeScomboSearch)
	ON_WM_PAINT()
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CExchangePage::OnHdnItemclickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CExchangePage::OnNMDblclkList1)
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	ON_CBN_SELCHANGE(IDC_COMBO2, &CExchangePage::OnCbnSelchangeCombo2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, OnCustomdrawList)
END_MESSAGE_MAP()


// CExchangePage �޽��� ó�����Դϴ�.
void CExchangePage::OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult)
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

void CExchangePage::OnBnClickedSearchbtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(true);

	if(m_exList.GetItemCount() > 0) m_exList.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
			
		int nIndex = m_exCombo.GetCurSel();
		if(nIndex == 0){
			strQuery.Format(_T("SELECT s_outputDate, c_code, i_code, s_outputAmount, i_inputPrice, i_outputPrice, order_total, sale_id FROM Sale WHERE (s_outputDate LIKE '%%%s%%' OR c_code LIKE '%%%s%%' OR i_code LIKE '%%%s%%' OR s_outputAmount LIKE '%%%s%%' OR i_inputPrice LIKE '%%%s%%' \
							   OR i_outputPrice LIKE '%%%s%%' OR order_total LIKE '%%%s%%' OR return_YN LIKE '%%%s%%' OR return_date LIKE '%%%s%%' OR return_reson LIKE '%%%s%%' OR exchange_YN LIKE '%%%s%%' \
							   OR exchange_date LIKE '%%%s%%' OR exchange_reason LIKE '%%%s%%' OR delivery_YN LIKE '%%%s%%' OR delivery_process LIKE '%%%s%%' OR sale_id LIKE '%%%s%%') AND Sale.exchange_YN = '�ƴϿ�'"),
				m_exSearch,m_exSearch,m_exSearch,m_exSearch,m_exSearch,m_exSearch,m_exSearch,m_exSearch,m_exSearch,m_exSearch,m_exSearch,m_exSearch,m_exSearch,m_exSearch,m_exSearch,m_exSearch);
		}
		if(nIndex == 1){
			strQuery.Format(_T("SELECT s_outputDate, c_code, i_code, s_outputAmount, i_inputPrice, i_outputPrice, order_total, sale_id FROM Sale WHERE s_outputDate LIKE '%%%s%%' AND exchange_YN = '�ƴϿ�'"),m_exSearch);
		}
		if(nIndex == 2){
			strQuery.Format(_T("SELECT s_outputDate, c_code, i_code, s_outputAmount, i_inputPrice, i_outputPrice, order_total, sale_id FROM Sale WHERE c_code LIKE '%%%s%%' AND exchange_YN = '�ƴϿ�'"),m_exSearch);
		}
		if(nIndex == 3){
			strQuery.Format(_T("SELECT s_outputDate, c_code, i_code, s_outputAmount, i_inputPrice, i_outputPrice, order_total, sale_id FROM Sale WHERE i_code LIKE '%%%s%%' AND exchange_YN = '�ƴϿ�'"),m_exSearch);
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
			 m_exList.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				m_exList.SetItemText(p, i ,tmp);
			}
			rs.MoveNext(); 
		 }
	}
	rs.Close();
	db.Close();

}


void CExchangePage::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(!UpdateData()) return;

	UpdateData(TRUE);

		CString samount, eamount;	//�Ǹż���, ��ȯ����

		samount = m_sAmount.GetString();
		eamount = m_exAmount.GetString();

		CString sdate;		//�Ǹų�¥
		sdate.Format(_T("%d-%02d-%02d"),m_sdate.GetYear(),m_sdate.GetMonth(),m_sdate.GetDay());

		CString edate;		//��ȯ��¥
		edate.Format(_T("%d-%02d-%02d"),m_exDate.GetYear(),m_exDate.GetMonth(),m_exDate.GetDay());

		int nIndex;
		nIndex = m_exReason_Combo.GetCurSel(); 
		reason = SelectReason(nIndex);

		CDatabase db;			// �����ͺ��̽� ��ü ����
		CRecordset rs (&db);	// ���ڵ�� ��ü ����

		if(_ttoi(samount) ==  _ttoi(eamount)){	//�Ǹż��� == ��ȯ����
			 try
			{
				CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");	//DB����
				
				if (db.OpenEx (strConnection) == FALSE)
					  throw _T("�����ͺ��̽� ���ӽ���!");

				CString strQuery;	//�����ͺ��̽��� ������ ������
				//strQuery.Format(_T("UPDATE Sale SET exchange_YN = '��', exchange_date = '%s', exchange_reason = '%s' WHERE i_code = '%s' AND s_outputDate='%s' AND s_outputAmount = '%s'"), edate, reason, m_sicode, sdate, m_sAmount);
				strQuery.Format(_T("UPDATE Sale SET exchange_YN = '��', exchange_date = '%s', exchange_reason = '%s' WHERE i_code = '%s' AND s_outputDate='%s'"), edate, reason, m_sicode, sdate);
				//m_sAmount������ �� �����ȳ�
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
			MessageBox(_T("���������� ��ȯ�Ǿ����ϴ�."));			
			//OnBnClickedClear();	//��Ʈ�� �ʱ�ȭ

		}
		else if(_ttoi(samount) > _ttoi(eamount)){		//�Ǹż��� > ��ȯ����
			try
			{
				CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");	//DB����
				
				if (db.OpenEx (strConnection) == FALSE)
					  throw _T("�����ͺ��̽� ���ӽ���!");

				CString strQuery;	//�����ͺ��̽��� ������ ������
				CString amount;		//�Ǹż��� - ��ȯ����
				amount.Format(_T("%d"), _ttoi(m_sAmount) - _ttoi(m_exAmount));

				//strQuery.Format(_T("UPDATE Sale SET SAmount = '%s' WHERE s_outputDate ='%s' AND ICode = '%s' AND SAmount = '%s'"),
								//amount, sdate, m_sicode, m_E_Samount);
				strQuery.Format(_T("UPDATE Sale SET s_outputAmount = '%s' WHERE s_outputDate ='%s' AND i_code = '%s' AND exchange_YN='�ƴϿ�'"),
								amount, sdate, m_sicode);
				db.ExecuteSQL(strQuery);	//�����ͺ��̽��� ������ ����

				strQuery.Format(_T("INSERT INTO Sale (s_outputDate,  in_ccode, out_ccode, i_code, s_outputAmount, i_inputPrice, i_outputPrice, order_total,  return_YN, return_date, return_reson, exchange_YN, exchange_date, exchange_reason,delivery_YN, delivery_process, sale_id) VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '�ƴϿ�', \
							   '�ش����', '�ش����', '��', '%s', '%s', '�ƴϿ�', '�ش����', '%s')"), 
							  sdate,m_incode, m_sscode,m_sicode,eamount,inprice,outprice,total ,edate, reason, g_setid);
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
			MessageBox(_T("���������� ��ȯ�Ǿ����ϴ�."));
			//OnBnClickedClear();	// ���������� ��ȯ�Ǿ��� �� ��Ʈ���� �ʱ�ȭ ���ش�.
			}
		else{	// �Ǹż��� < ��ȯ����
				MessageBox(_T("������ �ٽ� Ȯ�����ּ���."));
		}
		rs.Close();	//���ڵ�� ��ü �Ҹ�
		db.Close();	//�����ͺ��̽� ��ü �Ҹ�
		m_exCombo.SetCurSel(0);
		m_exReason_Combo.SetCurSel(-1);
		GetDlgItem(IDC_STATIC_INPUTDATE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT10)->ShowWindow(SW_HIDE);
		m_exSearch = _T("");
		m_sccode_Edit.SetWindowTextW(_T(""));
		m_sicode_Edit.SetWindowTextW(_T(""));
		m_sAmount_Edit.SetWindowTextW(_T(""));
		m_exAmount_Edit.SetWindowTextW(_T(""));
		CDateTimeCtrl *pCtrl = (CDateTimeCtrl *) GetDlgItem(IDC_DATETIMEPICKER4);
		CTime tm = CTime::GetCurrentTime();
		pCtrl->SetTime(&tm);
		CDateTimeCtrl *pCtrl2 = (CDateTimeCtrl *) GetDlgItem(IDC_DATETIMEPICKER5);
		CTime tm2 = CTime::GetCurrentTime();
		pCtrl2->SetTime(&tm2);

		//�̹����ʱ�ȭ
		CString img;
		img.Format(_T("res\\NoImage.bmp"));
		DrawBMP(img);

}
CString CExchangePage::SelectReason(int index)		//��з� ���ڿ� ��ȯ
{
	switch(index)
	{
	case 0 :
		reason = _T("�ܼ�����");
		break;
	case 1 :
		reason = _T("�ҷ�");
		break;
	case 2 :
		etcresaon = m_exReason.GetString();
		reason = etcresaon;
		break;
	}
	return reason;
}

BOOL CExchangePage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_exList.SetExtendedStyle(LVS_EX_FULLROWSELECT); //����ü����

	if(m_exList.GetHeaderCtrl()->GetItemCount() <= 0)		//����� �������� ���ٸ�
	{
		CRect rect;
		m_exList.GetClientRect(&rect);
		m_exList.InsertColumn(0, _T("�����"),	LVCFMT_LEFT, 100);
		m_exList.InsertColumn(1, _T("�Ǹų�¥"),			LVCFMT_LEFT, 120);
		m_exList.InsertColumn(2, _T("����ó�ڵ�"),			LVCFMT_LEFT, 80);
		m_exList.InsertColumn(3, _T("��ǰó�ڵ�"),			LVCFMT_LEFT, 80);
		m_exList.InsertColumn(4, _T("��ǰ�ڵ�"),			LVCFMT_LEFT, 80);
		m_exList.InsertColumn(5, _T("�ֹ�����"),			    LVCFMT_LEFT, 80);
		m_exList.InsertColumn(6, _T("���԰�"),			    LVCFMT_LEFT, 80);
		m_exList.InsertColumn(7, _T("�ǸŰ�"),			LVCFMT_LEFT, 80);
		m_exList.InsertColumn(8, _T("�� �ֹ��ݾ�"),			LVCFMT_LEFT, 80);
	}

	m_exCombo.AddString(_T("��ü�˻�"));
	m_exCombo.AddString(_T("�Ǹų�¥"));
	m_exCombo.AddString(_T("�ŷ�ó�ڵ�"));
	m_exCombo.AddString(_T("��ǰ�ڵ�"));

	m_exCombo.SetCurSel(0);

	GetDlgItem(IDC_DATETIMEPICKER4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT16)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT18)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_INPUTDATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT10)->ShowWindow(SW_HIDE);

	m_exReason_Combo.AddString(_T("�ܼ�����"));
	m_exReason_Combo.AddString(_T("�ҷ�"));
	m_exReason_Combo.AddString(_T("��Ÿ"));
	m_exReason_Combo.SetCurSel(-1);

	m_exsearchbtn.LoadBitmaps(IDB_BMP_SEARCH, NULL, NULL, NULL);
	m_exsearchbtn.SizeToContent();

	m_exokbtn.LoadBitmaps(IDB_BMP_OK, NULL, NULL, NULL);
	m_exokbtn.SizeToContent();

	m_excancelbtn.LoadBitmaps(IDB_BMP_CANCEL, NULL, NULL, NULL);
	m_excancelbtn.SizeToContent();

	//��� ��Ʈ�� �巡��-��-��� ����
	DWORD dwExStyle = m_exList.GetExtendedStyle();
	m_exList.SetExtendedStyle(dwExStyle | LVS_EX_HEADERDRAGDROP );

	m_bAscending = FALSE;
	m_exList.SortItems(&CExchangePage::CompareItem, (DWORD_PTR)this);
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
	GetDlgItem(IDC_STATIC_INPUTDATE)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_SCOMBO_SEARCH)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT12)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT16)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT17)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT18)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT8)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT10)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_DATETIMEPICKER4)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_DATETIMEPICKER5)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_COMBO2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_LIST1)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 

	if(m_exList.GetItemCount() > 0) m_exList.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
		strQuery.Format(_T("SELECT sale_id, s_outputDate, in_ccode, out_ccode, i_code, s_outputAmount, i_inputPrice, i_outputPrice, order_total FROM Sale WHERE exchange_YN='�ƴϿ�' "));
		
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
			 m_exList.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				// ù��° ���ڴ� InsertValue�� ���ؼ� ������ �� ������ �Ǵ� ����, �ι�° ���ڴ� �������� �ϳ��� 
				m_exList.SetItemText(p, i ,tmp);
			}
			rs.MoveNext();	//���������� �̵�
		 }
	}
	rs.Close();	//���ڵ�� ��ü �Ҹ�
	db.Close();	//�����ͺ��̽� ��ü �Ҹ�


	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
void CExchangePage::ReInitDialog(){
	if(m_exList.GetItemCount() > 0) m_exList.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
		strQuery.Format(_T("SELECT sale_id, s_outputDate, in_ccode, out_ccode, i_code, s_outputAmount, i_inputPrice, i_outputPrice, order_total FROM Sale WHERE exchange_YN='�ƴϿ�' "));
		
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
			 m_exList.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				// ù��° ���ڴ� InsertValue�� ���ؼ� ������ �� ������ �Ǵ� ����, �ι�° ���ڴ� �������� �ϳ��� 
				m_exList.SetItemText(p, i ,tmp);
			}
			rs.MoveNext();	//���������� �̵�
		 }
	}
	rs.Close();	//���ڵ�� ��ü �Ҹ�
	db.Close();	//�����ͺ��̽� ��ü �Ҹ�

}
int CALLBACK CExchangePage::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl *pListCtrl = ((SORTPARAM *)lParamSort)->pList;

	int iSortColumn = ((SORTPARAM *)lParamSort)->iSortColumn;
	bool bSortDirect = ((SORTPARAM *)lParamSort)->bSortDirect;

	CString    strItem1 = pListCtrl->GetItemText(static_cast<int>(lParam1), iSortColumn);
	CString    strItem2 = pListCtrl->GetItemText(static_cast<int>(lParam2), iSortColumn);

	return bSortDirect ? _tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2) : -_tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2);


}

void CExchangePage::UpdateArrow(void)
{
	CHeaderCtrl* pHeaderCtrl = m_exList.GetHeaderCtrl();
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

void CExchangePage::OnCbnSelchangeScomboSearch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	int nIndex;
	nIndex = m_exCombo.GetCurSel();   // ���� ���õ� �׸��� �ε����� ����

	if(nIndex == 1)
   {
	   GetDlgItem(IDC_STATIC_INPUTDATE)->ShowWindow(SW_SHOW);
   }
	else
		GetDlgItem(IDC_STATIC_INPUTDATE)->ShowWindow(SW_HIDE);

}


void CExchangePage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CPropertyPage::OnPaint()��(��) ȣ������ ���ʽÿ�.

	if(bFirst){
		CString img;
		img.Format(_T("res\\NoImage.bmp"));
		DrawBMP(img);
		bFirst = FALSE;
	}

	
}


void CExchangePage::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nColumn = phdr->iItem;
	// ���� ����Ʈ ��Ʈ�ѿ� �ִ� ������ �� �ڷ� ������ŭ ����
	 for(int i=0; i< (m_exList.GetItemCount()); i++)
	{
	 m_exList.SetItemData(i, i);
	}

	// ���� ��� ����(Ascend, Descend)
	 m_bAscending = !m_bAscending;
	 UpdateArrow();

	// ���� ���õ� ����ü ���� ���� �� ������ �ʱ�ȭ
	SORTPARAM sortparams;
	sortparams.pList = &m_exList;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending;

	// ���� �Լ� ȣ��
	m_exList.SortItems(&CompareItem, (LPARAM)&sortparams );

	*pResult = 0;
}


void CExchangePage::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    nListIndex = pNMListView->iItem;
	
	m_sccode_Edit.SetWindowTextW(m_exList.GetItemText(nListIndex,3));
	m_sicode_Edit.SetWindowTextW(m_exList.GetItemText(nListIndex,4));
	//itemAmount = m_reList.GetItemText(nListIndex,16);
	m_sAmount_Edit.SetWindowTextW(m_exList.GetItemText(nListIndex,5));
	//m_ss = m_exList.GetItemText(nListIndex,2);
	//inprice = m_exList.GetItemText(nListIndex,4);
	//outprice = m_exList.GetItemText(nListIndex,5);
	//total = m_exList.GetItemText(nListIndex,6);
	//isdate=m_exList.GetItemText(nListIndex,0);
	AfxExtractSubString(g_set_ibirth_Year,m_exList.GetItemText(nListIndex,1), 0,'-');
	AfxExtractSubString(g_set_ibirth_Month,m_exList.GetItemText(nListIndex,1), 1,'-');
	AfxExtractSubString(g_set_ibirth_Day,m_exList.GetItemText(nListIndex,1), 2,'-');

	COleDateTime Date;   //����ڰ� ������ ��¥�� ������ ColeDateTimeDate ����   
	CString wsYear = g_set_ibirth_Year;   //��
	CString wsMonth = g_set_ibirth_Month; //��
	CString wsDay = g_set_ibirth_Day;    //��
	Date.SetDate(_tstoi(wsYear),_tstoi(wsMonth),_tstoi(wsDay));
	//COleDateTimeŸ���� UpdateData������� �׷� �������ȸ���
	//�׷��� ���� ����� �ٽ� DateTime������ ��Ʈ�ѷ� �ٽø���
	m_sDate_ctrl.SetTime(Date);
	
	m_icode = m_exList.GetItemText(nListIndex,4);//��ǰ�ڵ�
	m_incode = m_exList.GetItemText(nListIndex,2);//����ó�ڵ�
	inprice = m_exList.GetItemText(nListIndex,6);
	outprice = m_exList.GetItemText(nListIndex,7);
	total = m_exList.GetItemText(nListIndex,8);
	imgname.Format(_T("res\\item\\%s.bmp"),m_icode);
	DrawBMP(imgname);

	
	*pResult = 0;
}


HCURSOR CExchangePage::OnQueryDragIcon()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CPropertyPage::OnQueryDragIcon();
}


void CExchangePage::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CPropertyPage::OnSysCommand(nID, lParam);
}


void CExchangePage::OnCbnSelchangeCombo2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nIndex;
	nIndex = m_exReason_Combo.GetCurSel();   // ���� ���õ� �׸��� �ε����� ����

	if(nIndex == 2)
   {
	   GetDlgItem(IDC_EDIT10)->ShowWindow(SW_SHOW);
   }
	else
		GetDlgItem(IDC_EDIT10)->ShowWindow(SW_HIDE);
}

void CExchangePage::DrawBMP(LPCTSTR lpszFileName)	//�̹��� �����ֱ�
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

	m_eiimage.GetWindowRect(&rect);//���̾�α׿� ��ġ�� ��Ʈ���� ũ�⸦ ��� ��
	cp.x = rect.left;//�̹��� ����� ���� ���� x ��ǥ
	cp.y = rect.top;//�̹��� ����� ���� ���� y ��ǥ 
	ScreenToClient(&cp);//cp�� ������ �ִ� ��ǥ�� ȭ���� ������
	pDC->StretchBlt(cp.x,cp.y,rect.Width(),rect.Height() ,&MemDC,0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);//�̹����� �ش� ��Ʈ�ѷ� ����
	MemDC.SelectObject(pOldBmp);
	ReleaseDC(pDC);//DC ��ȯ
}