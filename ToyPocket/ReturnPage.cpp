// ReturnPage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ReturnPage.h"
#include "afxdialogex.h"


// CReturnPage ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CReturnPage, CPropertyPage)

CReturnPage::CReturnPage()
	: CPropertyPage(CReturnPage::IDD)
	, m_reSearch(_T(""))
	, m_reAmount(_T(""))
	, m_reReason(_T(""))
	, m_reDate(COleDateTime::GetCurrentTime())
	, m_sdate(COleDateTime::GetCurrentTime())
	, m_sAmount(_T(""))
	, m_sicode(_T(""))
	, m_sscode(_T(""))
{

}

CReturnPage::~CReturnPage()
{
}

void CReturnPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_reList);
	DDX_Control(pDX, IDC_SCOMBO_SEARCH, m_reCombo);
	DDX_Text(pDX, IDC_EDIT12, m_reSearch);
	DDX_Control(pDX, IDC_EDIT14, m_sccode_Edit);
	DDX_Control(pDX, IDC_EDIT7, m_sicode_Edit);
	DDX_Text(pDX, IDC_EDIT8, m_reAmount);
	DDX_Control(pDX, IDC_COMBO2, m_reReason_Combo);
	DDX_Text(pDX, IDC_EDIT10, m_reReason);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_reDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER4, m_sdate);
	DDX_Text(pDX, IDC_EDIT18, m_sAmount);
	DDX_Text(pDX, IDC_EDIT7, m_sicode);
	DDX_Control(pDX, IDC_EDIT18, m_sAmount_Edit);
	DDX_Control(pDX, IDC_DATETIMEPICKER4, m_sDate_ctrl);
	DDX_Text(pDX, IDC_EDIT14, m_sscode);
	DDX_Control(pDX, IDC_IMAGE, m_riimage);
	DDX_Control(pDX, IDC_EDIT8, m_reAmount_Edit);
	DDX_Control(pDX, SEARCHBTN, m_researchbtn);
	DDX_Control(pDX, IDOK, m_reokbtn);
	DDX_Control(pDX, IDCANCEL, m_recancelbtn);
}


BEGIN_MESSAGE_MAP(CReturnPage, CPropertyPage)
	ON_BN_CLICKED(SEARCHBTN, &CReturnPage::OnBnClickedSearchbtn)
	ON_CBN_SELCHANGE(IDC_SCOMBO_SEARCH, &CReturnPage::OnCbnSelchangeScomboSearch)
	ON_WM_PAINT()
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CReturnPage::OnHdnItemclickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CReturnPage::OnNMDblclkList1)
	ON_BN_CLICKED(IDOK, &CReturnPage::OnBnClickedOk)
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	ON_CBN_SELCHANGE(IDC_COMBO2, &CReturnPage::OnCbnSelchangeCombo2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, OnCustomdrawList)
END_MESSAGE_MAP()


// CReturnPage �޽��� ó�����Դϴ�.

void CReturnPage::OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult)
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

void CReturnPage::OnBnClickedSearchbtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(true);

	if(m_reList.GetItemCount() > 0) m_reList.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
			
		int nIndex = m_reCombo.GetCurSel();
		if(nIndex == 0){
			strQuery.Format(_T("SELECT *,Itme.i_inputAmount FROM Sale"));
			strQuery.Format(_T("SELECT Sale.sale_id,  Sale.s_outputDate, Sale.in_ccode, Sale.out_ccode, Sale.i_code , Sale.s_outputAmount, Sale.i_inputPrice, Sale.i_outputPrice, Sale.order_total, Item.i_inputAmount FROM Item \
						   INNER JOIN Sale ON Item.i_code = Sale.i_code WHERE Sale.s_outputDate LIKE '%%%s%%' OR Sale.in_ccode LIKE '%%%s%%'  OR Sale.out_ccode LIKE '%%%s%%' OR Sale.i_code LIKE '%%%s%%' OR Sale.s_outputAmount LIKE '%%%s%%' OR \
						   Sale.i_inputPrice LIKE '%%%s%%' OR Sale.i_outputPrice LIKE '%%%s%%' OR Sale.order_total LIKE '%%%s%%' OR Sale.return_date LIKE '%%%s%%' OR Sale.return_reson LIKE '%%%s%%' OR Sale.sale_id LIKE '%%%s%%'  AND Sale.return_YN = '�ƴϿ�' AND Sale.exchange_YN = '�ƴϿ�'"),
				m_reSearch,m_reSearch,m_reSearch,m_reSearch,m_reSearch,m_reSearch,m_reSearch,m_reSearch,m_reSearch,m_reSearch,m_reSearch);
		}
		if(nIndex == 1){
			strQuery.Format(_T("SELECT *,Itme.i_inputAmount FROM Sale"));
			strQuery.Format(_T("SELECT Sale.sale_id,  Sale.s_outputDate, Sale.in_ccode, Sale.out_ccode, Sale.i_code , Sale.s_outputAmount, Sale.i_inputPrice, Sale.i_outputPrice, Sale.order_total, Item.i_inputAmount FROM Item \
						   INNER JOIN Sale ON Item.i_code = Sale.i_code WHERE Sale.s_outputDate LIKE '%%%s%%'  AND Sale.return_YN = '�ƴϿ�' AND Sale.exchange_YN = '�ƴϿ�'"),m_reSearch);
		}
		if(nIndex == 2){
			strQuery.Format(_T("SELECT *,Itme.i_inputAmount FROM Sale"));
			strQuery.Format(_T("SELECT Sale.sale_id,  Sale.s_outputDate, Sale.in_ccode, Sale.out_ccode, Sale.i_code , Sale.s_outputAmount, Sale.i_inputPrice, Sale.i_outputPrice, Sale.order_total, Item.i_inputAmount FROM Item \
						   INNER JOIN Sale ON Item.i_code = Sale.i_code WHERE Sale.out_ccode LIKE '%%%s%%' AND Sale.return_YN = '�ƴϿ�' AND Sale.exchange_YN = '�ƴϿ�'"),m_reSearch);
		}
		if(nIndex == 3){
			strQuery.Format(_T("SELECT *,Itme.i_inputAmount FROM Sale"));
			strQuery.Format(_T("SELECT Sale.sale_id,  Sale.s_outputDate, Sale.in_ccode, Sale.out_ccode, Sale.i_code , Sale.s_outputAmount, Sale.i_inputPrice, Sale.i_outputPrice, Sale.order_total, Item.i_inputAmount FROM Item \
						   INNER JOIN Sale ON Item.i_code = Sale.i_code WHERE Sale.i_code LIKE '%%%s%%' AND Sale.return_YN = '�ƴϿ�' AND Sale.exchange_YN = '�ƴϿ�'"),m_reSearch);
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
			 m_reList.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				m_reList.SetItemText(p, i ,tmp);
			}
			rs.MoveNext(); 
		 }
	}
	rs.Close();
	db.Close();

}


BOOL CReturnPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_reList.SetExtendedStyle(LVS_EX_FULLROWSELECT); //����ü����

	if(m_reList.GetHeaderCtrl()->GetItemCount() <= 0)		//����� �������� ���ٸ�
	{
		CRect rect;
		m_reList.GetClientRect(&rect);
		m_reList.InsertColumn(0, _T("�����"),	LVCFMT_LEFT, 100);
		m_reList.InsertColumn(1, _T("�Ǹų�¥"),			LVCFMT_LEFT, 120);
		m_reList.InsertColumn(2, _T("����ó�ڵ�"),			LVCFMT_LEFT, 80);
		m_reList.InsertColumn(3, _T("��ǰó�ڵ�"),			LVCFMT_LEFT, 80);
		m_reList.InsertColumn(4, _T("��ǰ�ڵ�"),			LVCFMT_LEFT, 80);
		m_reList.InsertColumn(5, _T("�ֹ�����"),			    LVCFMT_LEFT, 80);
		m_reList.InsertColumn(6, _T("���԰�"),			    LVCFMT_LEFT, 80);
		m_reList.InsertColumn(7, _T("�ǸŰ�"),			LVCFMT_LEFT, 80);
		m_reList.InsertColumn(8, _T("���ֹ��ݾ�"),			LVCFMT_LEFT, 80);
		m_reList.InsertColumn(9, _T("�԰����"),	LVCFMT_LEFT, 80);
	}

	m_reCombo.AddString(_T("��ü�˻�"));
	m_reCombo.AddString(_T("�Ǹų�¥"));
	m_reCombo.AddString(_T("��ǰó��"));
	m_reCombo.AddString(_T("��ǰ��"));

	m_reCombo.SetCurSel(0);

	GetDlgItem(IDC_DATETIMEPICKER4)->EnableWindow(FALSE);


	GetDlgItem(IDC_STATIC_INPUTDATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT10)->ShowWindow(SW_HIDE);

	m_reReason_Combo.AddString(_T("�ܼ�����"));
	m_reReason_Combo.AddString(_T("�ҷ�"));
	m_reReason_Combo.AddString(_T("��Ÿ"));
	m_reReason_Combo.SetCurSel(-1);
	
	//��� ��Ʈ�� �巡��-��-��� ����
	DWORD dwExStyle = m_reList.GetExtendedStyle();
	m_reList.SetExtendedStyle(dwExStyle | LVS_EX_HEADERDRAGDROP );

	m_bAscending = FALSE;
	m_reList.SortItems(&CReturnPage::CompareItem, (DWORD_PTR)this);
	UpdateArrow();

	bFirst = TRUE;

	m_researchbtn.LoadBitmaps(IDB_BMP_SEARCH, NULL, NULL, NULL);
	m_researchbtn.SizeToContent(); 

	m_reokbtn.LoadBitmaps(IDB_BMP_OK, NULL, NULL, NULL);
	m_reokbtn.SizeToContent(); 

	m_recancelbtn.LoadBitmaps(IDB_BMP_CANCEL, NULL, NULL, NULL);
	m_recancelbtn.SizeToContent();

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
	GetDlgItem(IDC_LIST1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT14)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT7)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_DATETIMEPICKER1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_DATETIMEPICKER4)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT10)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_COMBO2)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 

	if(m_reList.GetItemCount() > 0) m_reList.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
		strQuery.Format(_T("SELECT *,Itme.i_inputAmount FROM Sale"));
		strQuery.Format(_T("SELECT Sale.sale_id,  Sale.s_outputDate, Sale.in_ccode, Sale.out_ccode, Sale.i_code , Sale.s_outputAmount, Sale.i_inputPrice, Sale.i_outputPrice, Sale.order_total, Item.i_inputAmount FROM Item \
						   INNER JOIN Sale ON Item.i_code = Sale.i_code WHERE Sale.return_YN = '�ƴϿ�' AND Sale.exchange_YN = '�ƴϿ�'"));
		
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
			 m_reList.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				// ù��° ���ڴ� InsertValue�� ���ؼ� ������ �� ������ �Ǵ� ����, �ι�° ���ڴ� �������� �ϳ��� 
				m_reList.SetItemText(p, i ,tmp);
			}
			rs.MoveNext();	//���������� �̵�
		 }
	}
	rs.Close();	//���ڵ�� ��ü �Ҹ�
	db.Close();	//�����ͺ��̽� ��ü �Ҹ�

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
void CReturnPage::ReInitDialog(){
	if(m_reList.GetItemCount() > 0) m_reList.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
		strQuery.Format(_T("SELECT *,Itme.i_inputAmount FROM Sale"));
		strQuery.Format(_T("SELECT Sale.sale_id,  Sale.s_outputDate, Sale.in_ccode, Sale.out_ccode, Sale.i_code , Sale.s_outputAmount, Sale.i_inputPrice, Sale.i_outputPrice, Sale.order_total, Item.i_inputAmount FROM Item \
						   INNER JOIN Sale ON Item.i_code = Sale.i_code WHERE Sale.return_YN = '�ƴϿ�' AND Sale.exchange_YN = '�ƴϿ�'"));
		
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
			 m_reList.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				// ù��° ���ڴ� InsertValue�� ���ؼ� ������ �� ������ �Ǵ� ����, �ι�° ���ڴ� �������� �ϳ��� 
				m_reList.SetItemText(p, i ,tmp);
			}
			rs.MoveNext();	//���������� �̵�
		 }
	}
	rs.Close();	//���ڵ�� ��ü �Ҹ�
	db.Close();	//�����ͺ��̽� ��ü �Ҹ�
}

int CALLBACK CReturnPage::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl *pListCtrl = ((SORTPARAM *)lParamSort)->pList;

	int iSortColumn = ((SORTPARAM *)lParamSort)->iSortColumn;
	bool bSortDirect = ((SORTPARAM *)lParamSort)->bSortDirect;

	CString    strItem1 = pListCtrl->GetItemText(static_cast<int>(lParam1), iSortColumn);
	CString    strItem2 = pListCtrl->GetItemText(static_cast<int>(lParam2), iSortColumn);

	return bSortDirect ? _tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2) : -_tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2);


}

void CReturnPage::UpdateArrow(void)
{
	CHeaderCtrl* pHeaderCtrl = m_reList.GetHeaderCtrl();
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


void CReturnPage::OnCbnSelchangeScomboSearch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nIndex;
	nIndex = m_reCombo.GetCurSel();   // ���� ���õ� �׸��� �ε����� ����

	if(nIndex == 1)
   {
	   GetDlgItem(IDC_STATIC_INPUTDATE)->ShowWindow(SW_SHOW);
   }
	else
		GetDlgItem(IDC_STATIC_INPUTDATE)->ShowWindow(SW_HIDE);
}


void CReturnPage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.



	if(bFirst){
		CString img;
		img.Format(_T("res\\NoImage.bmp"));
		DrawBMP(img);
		bFirst = FALSE;
	}

	// �׸��� �޽����� ���ؼ��� CPropertyPage::OnPaint()��(��) ȣ������ ���ʽÿ�.
}


void CReturnPage::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nColumn = phdr->iItem;
	// ���� ����Ʈ ��Ʈ�ѿ� �ִ� ������ �� �ڷ� ������ŭ ����
	 for(int i=0; i< (m_reList.GetItemCount()); i++)
	{
	 m_reList.SetItemData(i, i);
	}

	// ���� ��� ����(Ascend, Descend)
	 m_bAscending = !m_bAscending;
	 UpdateArrow();

	// ���� ���õ� ����ü ���� ���� �� ������ �ʱ�ȭ
	SORTPARAM sortparams;
	sortparams.pList = &m_reList;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending;

	// ���� �Լ� ȣ��
	m_reList.SortItems(&CompareItem, (LPARAM)&sortparams );

	*pResult = 0;
}


void CReturnPage::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    nListIndex = pNMListView->iItem;

	m_sccode_Edit.SetWindowTextW(m_reList.GetItemText(nListIndex,3));
	m_sicode_Edit.SetWindowTextW(m_reList.GetItemText(nListIndex,4));
	//itemAmount = m_reList.GetItemText(nListIndex,16);
	m_sAmount_Edit.SetWindowTextW(m_reList.GetItemText(nListIndex,5));
	//inputprice = m_reList.GetItemText(nListIndex,4);
	//outputprice = m_reList.GetItemText(nListIndex,5);

	AfxExtractSubString(g_set_ibirth_Year,m_reList.GetItemText(nListIndex,1), 0,'-');
	AfxExtractSubString(g_set_ibirth_Month,m_reList.GetItemText(nListIndex,1), 1,'-');
	AfxExtractSubString(g_set_ibirth_Day,m_reList.GetItemText(nListIndex,1), 2,'-');

	COleDateTime Date;   //����ڰ� ������ ��¥�� ������ ColeDateTimeDate ����   
	CString wsYear = g_set_ibirth_Year;   //��
	CString wsMonth = g_set_ibirth_Month; //��
	CString wsDay = g_set_ibirth_Day;    //��
	Date.SetDate(_tstoi(wsYear),_tstoi(wsMonth),_tstoi(wsDay));
	//COleDateTimeŸ���� UpdateData������� �׷� �������ȸ���
	//�׷��� ���� ����� �ٽ� DateTime������ ��Ʈ�ѷ� �ٽø���
	m_sDate_ctrl.SetTime(Date);

	m_icode = m_reList.GetItemText(nListIndex,4);
	m_incode =  m_reList.GetItemText(nListIndex,2);
	inputprice =  m_reList.GetItemText(nListIndex,6);
	outputprice =  m_reList.GetItemText(nListIndex,7);
	//total =  m_reList.GetItemText(nListIndex,8);
	imgname.Format(_T("res\\item\\%s.bmp"),m_icode);
	DrawBMP(imgname);

	*pResult = 0;
}


void CReturnPage::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if(!UpdateData()) return;
	UpdateData(TRUE);


	//�Ǹų�¥

	CString sdate;
		sdate.Format(_T("%d-%02d-%02d"),m_sdate.GetYear(),m_sdate.GetMonth(),m_sdate.GetDay());

    //��ǰ��¥

    CString rdate;
		rdate.Format(_T("%d-%02d-%02d"),m_reDate.GetYear(),m_reDate.GetMonth(),m_reDate.GetDay());
	
	int nIndex;
	nIndex = m_reReason_Combo.GetCurSel(); 
    reason = SelectReason(nIndex);

	itemAmount.Format(_T("%d"), _ttoi(itemAmount) + _ttoi(m_reAmount));

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	

		if(_ttoi(m_reAmount) == _ttoi(m_sAmount)){
			try   
			{
				CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");

				if (db.OpenEx (strConnection) == FALSE)
					throw _T("�����ͺ��̽� ���ӽ���!");

				CString strQuery;	//�����ͺ��̽��� ������ ������
				strQuery.Format(_T("UPDATE Sale SET return_YN='��', return_date='%s', return_reson='%s' WHERE i_code='%s'AND s_outputDate='%s'"),
					rdate ,reason ,m_sicode ,sdate);
				db.ExecuteSQL(strQuery);	//�����ͺ��̽��� ������ ����
				strQuery.Format(_T("UPDATE Item SET i_inputAmount='%s' WHERE i_code='%s'"), m_reAmount, m_sicode);
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
			MessageBox(_T("���������� ��ǰ�Ǿ����ϴ�."));
		}
		else if(_ttoi(m_reAmount) < _ttoi(m_sAmount)){
			CString AA;
			AA.Format(_T("%d"),_ttoi(m_sAmount)-_ttoi(m_reAmount));

			CString total;
			total.Format(_T("%d"),_ttoi(outputprice)*_ttoi(m_reAmount));

			try
			{
				CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");

				if (db.OpenEx (strConnection) == FALSE)
					throw _T("�����ͺ��̽� ���ӽ���!");

				CString strQuery;	//�����ͺ��̽��� ������ ������

				strQuery.Format(_T("UPDATE Sale SET s_outputAmount='%s' WHERE i_code='%s' AND return_YN='�ƴϿ�' AND s_outputDate='%s'"),AA ,m_sicode ,sdate);
				db.ExecuteSQL(strQuery);	//�����ͺ��̽��� ������ ����

				strQuery.Format(_T("INSERT INTO Sale (s_outputDate, in_ccode, out_ccode, i_code, s_outputAmount, i_inputPrice, i_outputPrice, order_total,  return_YN, return_date, return_reson, exchange_YN, exchange_date, exchange_reason,delivery_YN, delivery_process, sale_id) VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '��', \
							   '%s', '%s', '�ƴϿ�', '�ش����', '�ش����', '�ƴϿ�', '�ش����', '%s')"), 
							  sdate,m_incode, m_sscode, m_sicode,m_reAmount,inputprice,outputprice,total ,rdate, reason, g_setid);

				//strQuery.Format(_T("INSERT INTO Sale VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s', '��', '%s', '%s', '�ƴϿ�', '�ش����', '�ش����', '�ƴϿ�', '�ش����', '%s')"),
					//sdate ,m_sscode ,m_sicode,m_sAmount,inputprice,outputprice,total,rdate,reason,g_setid);
				db.ExecuteSQL(strQuery);	//�����ͺ��̽��� ������ ����

				strQuery.Format(_T("UPDATE Item SET i_inputAmount='%s' WHERE i_code='%s'"), itemAmount, m_sicode);
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

			MessageBox(_T("���������� ��ǰ�Ǿ����ϴ�."));
		}
		else {
			MessageBox(_T("������ �ٽ� Ȯ�����ּ���."));
		}
		rs.Close();		//���ڵ�� ��ü �Ҹ�
		db.Close();		//�����ͺ��̽� ��ü �Ҹ�

		m_reCombo.SetCurSel(0);
		m_reReason_Combo.SetCurSel(-1);
		GetDlgItem(IDC_STATIC_INPUTDATE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT10)->ShowWindow(SW_HIDE);
		m_reSearch = _T("");
		m_sccode_Edit.SetWindowTextW(_T(""));
		m_sicode_Edit.SetWindowTextW(_T(""));
		m_sAmount_Edit.SetWindowTextW(_T(""));
		m_reAmount_Edit.SetWindowTextW(_T(""));
		CDateTimeCtrl *pCtrl = (CDateTimeCtrl *) GetDlgItem(IDC_DATETIMEPICKER4);
		CTime tm = CTime::GetCurrentTime();
		pCtrl->SetTime(&tm);
		CDateTimeCtrl *pCtrl2 = (CDateTimeCtrl *) GetDlgItem(IDC_DATETIMEPICKER1);
		CTime tm2 = CTime::GetCurrentTime();
		pCtrl2->SetTime(&tm2);

		//�̹����ʱ�ȭ
		CString img;
		img.Format(_T("res\\NoImage.bmp"));
		DrawBMP(img);
}

CString CReturnPage::SelectReason(int index)		//��з� ���ڿ� ��ȯ
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
		etcresaon = m_reReason.GetString();
		reason = etcresaon;
		break;
	}
	return reason;
}

HCURSOR CReturnPage::OnQueryDragIcon()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CPropertyPage::OnQueryDragIcon();
}


void CReturnPage::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CPropertyPage::OnSysCommand(nID, lParam);
}


void CReturnPage::OnCbnSelchangeCombo2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nIndex;
	nIndex = m_reReason_Combo.GetCurSel();   // ���� ���õ� �׸��� �ε����� ����

	if(nIndex == 2)
   {
	   GetDlgItem(IDC_EDIT10)->ShowWindow(SW_SHOW);
   }
	else
		GetDlgItem(IDC_EDIT10)->ShowWindow(SW_HIDE);
}

void CReturnPage::DrawBMP(LPCTSTR lpszFileName)	//�̹��� �����ֱ�
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

	m_riimage.GetWindowRect(&rect);//���̾�α׿� ��ġ�� ��Ʈ���� ũ�⸦ ��� ��
	cp.x = rect.left;//�̹��� ����� ���� ���� x ��ǥ
	cp.y = rect.top;//�̹��� ����� ���� ���� y ��ǥ 
	ScreenToClient(&cp);//cp�� ������ �ִ� ��ǥ�� ȭ���� ������
	pDC->StretchBlt(cp.x,cp.y,rect.Width(),rect.Height() ,&MemDC,0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);//�̹����� �ش� ��Ʈ�ѷ� ����
	MemDC.SelectObject(pOldBmp);
	ReleaseDC(pDC);//DC ��ȯ
}
