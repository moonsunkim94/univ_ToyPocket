// ReturnPage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ReturnPage.h"
#include "afxdialogex.h"


// CReturnPage 대화 상자입니다.

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


// CReturnPage 메시지 처리기입니다.

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);

	if(m_reList.GetItemCount() > 0) m_reList.DeleteAllItems();

	CDatabase db;			// 데이터베이스 객체 생성
	CRecordset rs (&db);	// 레코드셋 객체 생성
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("데이터베이스 접속실패!");

		CString strQuery;
			
		int nIndex = m_reCombo.GetCurSel();
		if(nIndex == 0){
			strQuery.Format(_T("SELECT *,Itme.i_inputAmount FROM Sale"));
			strQuery.Format(_T("SELECT Sale.sale_id,  Sale.s_outputDate, Sale.in_ccode, Sale.out_ccode, Sale.i_code , Sale.s_outputAmount, Sale.i_inputPrice, Sale.i_outputPrice, Sale.order_total, Item.i_inputAmount FROM Item \
						   INNER JOIN Sale ON Item.i_code = Sale.i_code WHERE Sale.s_outputDate LIKE '%%%s%%' OR Sale.in_ccode LIKE '%%%s%%'  OR Sale.out_ccode LIKE '%%%s%%' OR Sale.i_code LIKE '%%%s%%' OR Sale.s_outputAmount LIKE '%%%s%%' OR \
						   Sale.i_inputPrice LIKE '%%%s%%' OR Sale.i_outputPrice LIKE '%%%s%%' OR Sale.order_total LIKE '%%%s%%' OR Sale.return_date LIKE '%%%s%%' OR Sale.return_reson LIKE '%%%s%%' OR Sale.sale_id LIKE '%%%s%%'  AND Sale.return_YN = '아니오' AND Sale.exchange_YN = '아니오'"),
				m_reSearch,m_reSearch,m_reSearch,m_reSearch,m_reSearch,m_reSearch,m_reSearch,m_reSearch,m_reSearch,m_reSearch,m_reSearch);
		}
		if(nIndex == 1){
			strQuery.Format(_T("SELECT *,Itme.i_inputAmount FROM Sale"));
			strQuery.Format(_T("SELECT Sale.sale_id,  Sale.s_outputDate, Sale.in_ccode, Sale.out_ccode, Sale.i_code , Sale.s_outputAmount, Sale.i_inputPrice, Sale.i_outputPrice, Sale.order_total, Item.i_inputAmount FROM Item \
						   INNER JOIN Sale ON Item.i_code = Sale.i_code WHERE Sale.s_outputDate LIKE '%%%s%%'  AND Sale.return_YN = '아니오' AND Sale.exchange_YN = '아니오'"),m_reSearch);
		}
		if(nIndex == 2){
			strQuery.Format(_T("SELECT *,Itme.i_inputAmount FROM Sale"));
			strQuery.Format(_T("SELECT Sale.sale_id,  Sale.s_outputDate, Sale.in_ccode, Sale.out_ccode, Sale.i_code , Sale.s_outputAmount, Sale.i_inputPrice, Sale.i_outputPrice, Sale.order_total, Item.i_inputAmount FROM Item \
						   INNER JOIN Sale ON Item.i_code = Sale.i_code WHERE Sale.out_ccode LIKE '%%%s%%' AND Sale.return_YN = '아니오' AND Sale.exchange_YN = '아니오'"),m_reSearch);
		}
		if(nIndex == 3){
			strQuery.Format(_T("SELECT *,Itme.i_inputAmount FROM Sale"));
			strQuery.Format(_T("SELECT Sale.sale_id,  Sale.s_outputDate, Sale.in_ccode, Sale.out_ccode, Sale.i_code , Sale.s_outputAmount, Sale.i_inputPrice, Sale.i_outputPrice, Sale.order_total, Item.i_inputAmount FROM Item \
						   INNER JOIN Sale ON Item.i_code = Sale.i_code WHERE Sale.i_code LIKE '%%%s%%' AND Sale.return_YN = '아니오' AND Sale.exchange_YN = '아니오'"),m_reSearch);
		}
		if (rs.Open (CRecordset::snapshot, strQuery) == FALSE)	
			throw _T("쿼리전송 실패!");
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

	short col = rs.GetODBCFieldCount();			//쿼리문을 이용해 검색한 내용 리스트 컨트롤에 출력
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

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_reList.SetExtendedStyle(LVS_EX_FULLROWSELECT); //행전체선택

	if(m_reList.GetHeaderCtrl()->GetItemCount() <= 0)		//헤더에 아이템이 없다면
	{
		CRect rect;
		m_reList.GetClientRect(&rect);
		m_reList.InsertColumn(0, _T("담당자"),	LVCFMT_LEFT, 100);
		m_reList.InsertColumn(1, _T("판매날짜"),			LVCFMT_LEFT, 120);
		m_reList.InsertColumn(2, _T("납입처코드"),			LVCFMT_LEFT, 80);
		m_reList.InsertColumn(3, _T("납품처코드"),			LVCFMT_LEFT, 80);
		m_reList.InsertColumn(4, _T("상품코드"),			LVCFMT_LEFT, 80);
		m_reList.InsertColumn(5, _T("주문수량"),			    LVCFMT_LEFT, 80);
		m_reList.InsertColumn(6, _T("매입가"),			    LVCFMT_LEFT, 80);
		m_reList.InsertColumn(7, _T("판매가"),			LVCFMT_LEFT, 80);
		m_reList.InsertColumn(8, _T("총주문금액"),			LVCFMT_LEFT, 80);
		m_reList.InsertColumn(9, _T("입고수량"),	LVCFMT_LEFT, 80);
	}

	m_reCombo.AddString(_T("전체검색"));
	m_reCombo.AddString(_T("판매날짜"));
	m_reCombo.AddString(_T("납품처명"));
	m_reCombo.AddString(_T("상품명"));

	m_reCombo.SetCurSel(0);

	GetDlgItem(IDC_DATETIMEPICKER4)->EnableWindow(FALSE);


	GetDlgItem(IDC_STATIC_INPUTDATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT10)->ShowWindow(SW_HIDE);

	m_reReason_Combo.AddString(_T("단순변심"));
	m_reReason_Combo.AddString(_T("불량"));
	m_reReason_Combo.AddString(_T("기타"));
	m_reReason_Combo.SetCurSel(-1);
	
	//헤더 컨트롤 드래그-앤-드롭 가능
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
	::lstrcpy(lf.lfFaceName, _T("나눔바른고딕"));
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

	CDatabase db;			// 데이터베이스 객체 생성
	CRecordset rs (&db);	// 레코드셋 객체 생성
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("데이터베이스 접속실패!");

		CString strQuery;
		strQuery.Format(_T("SELECT *,Itme.i_inputAmount FROM Sale"));
		strQuery.Format(_T("SELECT Sale.sale_id,  Sale.s_outputDate, Sale.in_ccode, Sale.out_ccode, Sale.i_code , Sale.s_outputAmount, Sale.i_inputPrice, Sale.i_outputPrice, Sale.order_total, Item.i_inputAmount FROM Item \
						   INNER JOIN Sale ON Item.i_code = Sale.i_code WHERE Sale.return_YN = '아니오' AND Sale.exchange_YN = '아니오'"));
		
		if (rs.Open (CRecordset::snapshot, strQuery) == FALSE)	
			throw _T("쿼리전송 실패!");
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
		
	//쿼리문을 이용해 검색한 내용 리스트 컨트롤에 출력
	short col = rs.GetODBCFieldCount();	
	for(int p=0 ; p<2 ; p++)
	{
		 while( ! rs.IsEOF())		//행단위
		 {
			 //속성단위
			 CString tmp;
			 rs.GetFieldValue((short)p, tmp);  
			 //id값이 기준이 된다.
			 m_reList.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				// 첫번째 인자는 InsertValue를 통해서 가지고 온 기준이 되는 정보, 두번째 인자는 열단위로 하나씩 
				m_reList.SetItemText(p, i ,tmp);
			}
			rs.MoveNext();	//다음행으로 이동
		 }
	}
	rs.Close();	//레코드셋 객체 소멸
	db.Close();	//데이터베이스 객체 소멸

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
void CReturnPage::ReInitDialog(){
	if(m_reList.GetItemCount() > 0) m_reList.DeleteAllItems();

	CDatabase db;			// 데이터베이스 객체 생성
	CRecordset rs (&db);	// 레코드셋 객체 생성
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("데이터베이스 접속실패!");

		CString strQuery;
		strQuery.Format(_T("SELECT *,Itme.i_inputAmount FROM Sale"));
		strQuery.Format(_T("SELECT Sale.sale_id,  Sale.s_outputDate, Sale.in_ccode, Sale.out_ccode, Sale.i_code , Sale.s_outputAmount, Sale.i_inputPrice, Sale.i_outputPrice, Sale.order_total, Item.i_inputAmount FROM Item \
						   INNER JOIN Sale ON Item.i_code = Sale.i_code WHERE Sale.return_YN = '아니오' AND Sale.exchange_YN = '아니오'"));
		
		if (rs.Open (CRecordset::snapshot, strQuery) == FALSE)	
			throw _T("쿼리전송 실패!");
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
		
	//쿼리문을 이용해 검색한 내용 리스트 컨트롤에 출력
	short col = rs.GetODBCFieldCount();	
	for(int p=0 ; p<2 ; p++)
	{
		 while( ! rs.IsEOF())		//행단위
		 {
			 //속성단위
			 CString tmp;
			 rs.GetFieldValue((short)p, tmp);  
			 //id값이 기준이 된다.
			 m_reList.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				// 첫번째 인자는 InsertValue를 통해서 가지고 온 기준이 되는 정보, 두번째 인자는 열단위로 하나씩 
				m_reList.SetItemText(p, i ,tmp);
			}
			rs.MoveNext();	//다음행으로 이동
		 }
	}
	rs.Close();	//레코드셋 객체 소멸
	db.Close();	//데이터베이스 객체 소멸
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nIndex;
	nIndex = m_reCombo.GetCurSel();   // 현재 선택된 항목의 인덱스를 얻음

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
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.



	if(bFirst){
		CString img;
		img.Format(_T("res\\NoImage.bmp"));
		DrawBMP(img);
		bFirst = FALSE;
	}

	// 그리기 메시지에 대해서는 CPropertyPage::OnPaint()을(를) 호출하지 마십시오.
}


void CReturnPage::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nColumn = phdr->iItem;
	// 현재 리스트 컨트롤에 있는 데이터 총 자료 개수만큼 저장
	 for(int i=0; i< (m_reList.GetItemCount()); i++)
	{
	 m_reList.SetItemData(i, i);
	}

	// 정렬 방식 지정(Ascend, Descend)
	 m_bAscending = !m_bAscending;
	 UpdateArrow();

	// 정렬 관련된 구조체 변수 생성 및 데이터 초기화
	SORTPARAM sortparams;
	sortparams.pList = &m_reList;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending;

	// 정렬 함수 호출
	m_reList.SortItems(&CompareItem, (LPARAM)&sortparams );

	*pResult = 0;
}


void CReturnPage::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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

	COleDateTime Date;   //사용자가 지정한 날짜를 저장할 ColeDateTimeDate 변수   
	CString wsYear = g_set_ibirth_Year;   //년
	CString wsMonth = g_set_ibirth_Month; //월
	CString wsDay = g_set_ibirth_Day;    //일
	Date.SetDate(_tstoi(wsYear),_tstoi(wsMonth),_tstoi(wsDay));
	//COleDateTime타입은 UpdateData해줘야함 그럼 나머지안먹힘
	//그래서 변수 지우고 다시 DateTime형식의 컨트롤로 다시만듬
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if(!UpdateData()) return;
	UpdateData(TRUE);


	//판매날짜

	CString sdate;
		sdate.Format(_T("%d-%02d-%02d"),m_sdate.GetYear(),m_sdate.GetMonth(),m_sdate.GetDay());

    //반품날짜

    CString rdate;
		rdate.Format(_T("%d-%02d-%02d"),m_reDate.GetYear(),m_reDate.GetMonth(),m_reDate.GetDay());
	
	int nIndex;
	nIndex = m_reReason_Combo.GetCurSel(); 
    reason = SelectReason(nIndex);

	itemAmount.Format(_T("%d"), _ttoi(itemAmount) + _ttoi(m_reAmount));

	CDatabase db;			// 데이터베이스 객체 생성
	CRecordset rs (&db);	// 레코드셋 객체 생성
	

		if(_ttoi(m_reAmount) == _ttoi(m_sAmount)){
			try   
			{
				CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");

				if (db.OpenEx (strConnection) == FALSE)
					throw _T("데이터베이스 접속실패!");

				CString strQuery;	//데이터베이스에 전송할 쿼리문
				strQuery.Format(_T("UPDATE Sale SET return_YN='예', return_date='%s', return_reson='%s' WHERE i_code='%s'AND s_outputDate='%s'"),
					rdate ,reason ,m_sicode ,sdate);
				db.ExecuteSQL(strQuery);	//데이터베이스에 쿼리문 전송
				strQuery.Format(_T("UPDATE Item SET i_inputAmount='%s' WHERE i_code='%s'"), m_reAmount, m_sicode);
				db.ExecuteSQL(strQuery);	//데이터베이스에 쿼리문 전송
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
			MessageBox(_T("성공적으로 반품되었습니다."));
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
					throw _T("데이터베이스 접속실패!");

				CString strQuery;	//데이터베이스에 전송할 쿼리문

				strQuery.Format(_T("UPDATE Sale SET s_outputAmount='%s' WHERE i_code='%s' AND return_YN='아니오' AND s_outputDate='%s'"),AA ,m_sicode ,sdate);
				db.ExecuteSQL(strQuery);	//데이터베이스에 쿼리문 전송

				strQuery.Format(_T("INSERT INTO Sale (s_outputDate, in_ccode, out_ccode, i_code, s_outputAmount, i_inputPrice, i_outputPrice, order_total,  return_YN, return_date, return_reson, exchange_YN, exchange_date, exchange_reason,delivery_YN, delivery_process, sale_id) VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '예', \
							   '%s', '%s', '아니오', '해당없음', '해당없음', '아니오', '해당없음', '%s')"), 
							  sdate,m_incode, m_sscode, m_sicode,m_reAmount,inputprice,outputprice,total ,rdate, reason, g_setid);

				//strQuery.Format(_T("INSERT INTO Sale VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s', '예', '%s', '%s', '아니오', '해당없음', '해당없음', '아니오', '해당없음', '%s')"),
					//sdate ,m_sscode ,m_sicode,m_sAmount,inputprice,outputprice,total,rdate,reason,g_setid);
				db.ExecuteSQL(strQuery);	//데이터베이스에 쿼리문 전송

				strQuery.Format(_T("UPDATE Item SET i_inputAmount='%s' WHERE i_code='%s'"), itemAmount, m_sicode);
				db.ExecuteSQL(strQuery);	//데이터베이스에 쿼리문 전송
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

			MessageBox(_T("성공적으로 반품되었습니다."));
		}
		else {
			MessageBox(_T("수량을 다시 확인해주세요."));
		}
		rs.Close();		//레코드셋 객체 소멸
		db.Close();		//데이터베이스 객체 소멸

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

		//이미지초기화
		CString img;
		img.Format(_T("res\\NoImage.bmp"));
		DrawBMP(img);
}

CString CReturnPage::SelectReason(int index)		//대분류 문자열 반환
{
	switch(index)
	{
	case 0 :
		reason = _T("단순변심");
		break;
	case 1 :
		reason = _T("불량");
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CPropertyPage::OnQueryDragIcon();
}


void CReturnPage::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CPropertyPage::OnSysCommand(nID, lParam);
}


void CReturnPage::OnCbnSelchangeCombo2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nIndex;
	nIndex = m_reReason_Combo.GetCurSel();   // 현재 선택된 항목의 인덱스를 얻음

	if(nIndex == 2)
   {
	   GetDlgItem(IDC_EDIT10)->ShowWindow(SW_SHOW);
   }
	else
		GetDlgItem(IDC_EDIT10)->ShowWindow(SW_HIDE);
}

void CReturnPage::DrawBMP(LPCTSTR lpszFileName)	//이미지 보여주기
{
	CDC* pDC = GetDC();//화면 DC를 얻어 옴
	CDC MemDC;//메모리 DC
	CBitmap bmp, *pOldBmp;
	BITMAP bm;//비트맵 정보를 저장하는 변수
	CRect rect;
	CPoint cp;

	//이미지 파일 로딩
	bmp.m_hObject = (HBITMAP)LoadImage(NULL, lpszFileName, IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
	if(bmp.m_hObject == NULL) return;
	bmp.GetBitmap(&bm);//로딩된 이미지 파일의 형태를 얻음
	MemDC.CreateCompatibleDC(pDC);//메모리 DC와 화면 DC를 호환성있도록 연결
	pOldBmp = MemDC.SelectObject(&bmp);//메모리에 적재된 이미지 선택

	m_riimage.GetWindowRect(&rect);//다이어로그에 배치된 컨트롤의 크기를 얻어 옴
	cp.x = rect.left;//이미지 출력을 위한 시작 x 좌표
	cp.y = rect.top;//이미지 출력을 위한 시작 y 좌표 
	ScreenToClient(&cp);//cp가 가지고 있는 좌표로 화면을 지정함
	pDC->StretchBlt(cp.x,cp.y,rect.Width(),rect.Height() ,&MemDC,0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);//이미지를 해당 컨트롤로 전송
	MemDC.SelectObject(pOldBmp);
	ReleaseDC(pDC);//DC 반환
}
