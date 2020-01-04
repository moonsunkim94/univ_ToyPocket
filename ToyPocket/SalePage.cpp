// SalePage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "SalePage.h"
#include "afxdialogex.h"



// CSalePage 대화 상자입니다.

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


// CSalePage 메시지 처리기입니다.

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

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_si_List.SetExtendedStyle(LVS_EX_FULLROWSELECT); //행전체선택

	m_search_btn.LoadBitmaps(IDB_BMP_SEARCH, NULL, NULL, NULL);
	m_search_btn.SizeToContent();
	m_ok_btn.LoadBitmaps(IDB_BMP_OK, NULL, NULL, NULL);
	m_ok_btn.SizeToContent();
	m_cancel_btn.LoadBitmaps(IDB_BMP_CANCEL, NULL, NULL, NULL);
	m_cancel_btn.SizeToContent();
	m_comsearchbtn.LoadBitmaps(IDB_BMP_SEARCH, NULL, NULL, NULL);
	m_comsearchbtn.SizeToContent();
	
	if(m_si_List.GetHeaderCtrl()->GetItemCount() <= 0)		//헤더에 아이템이 없다면
	{
		CRect rect;
		m_si_List.GetClientRect(&rect);
		m_si_List.InsertColumn(0, _T("담당자"),			LVCFMT_LEFT, 100);
		m_si_List.InsertColumn(1, _T("상품코드"),			LVCFMT_LEFT, 80);
		m_si_List.InsertColumn(2, _T("상품명"),			LVCFMT_LEFT, 80);
		m_si_List.InsertColumn(3, _T("대분류"),			LVCFMT_LEFT, 80);
		m_si_List.InsertColumn(4, _T("중분류"),			    LVCFMT_LEFT, 80);
		m_si_List.InsertColumn(5, _T("소분류"),			    LVCFMT_LEFT, 80);
		m_si_List.InsertColumn(6, _T("거래처명"),			LVCFMT_LEFT, 80);
		m_si_List.InsertColumn(7, _T("거래처코드"),			LVCFMT_LEFT, 80);
		m_si_List.InsertColumn(8, _T("입고일"),			    LVCFMT_LEFT, 80);
		m_si_List.InsertColumn(9, _T("입고수량"),	LVCFMT_LEFT, 80);
		m_si_List.InsertColumn(10, _T("매입가"),	LVCFMT_LEFT, 80);
		m_si_List.InsertColumn(11, _T("판매금액"),	LVCFMT_LEFT, 80);
	}

	m_scombosearch.AddString(_T("전체검색"));
	m_scombosearch.AddString(_T("상품명"));
	m_scombosearch.AddString(_T("거래처명"));
	m_scombosearch.AddString(_T("입고날짜"));

	m_scombosearch.SetCurSel(0);
	GetDlgItem(IDC_SCOMBO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCOMBO2)->EnableWindow(FALSE);	
	GetDlgItem(IDC_SCOMBO3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	GetDlgItem(IDC_AMOUNT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCOM)->EnableWindow(FALSE);

	GetDlgItem(IDC_STATIC_INPUTDATE)->ShowWindow(SW_HIDE);

	//헤더 컨트롤 드래그-앤-드롭 가능
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

	CDatabase db;			// 데이터베이스 객체 생성
	CRecordset rs (&db);	// 레코드셋 객체 생성
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("데이터베이스 접속실패!");

		CString strQuery;	//데이터베이스에 전송할 쿼리문
		strQuery.Format(_T("SELECT item_id, i_code, i_name, i_large, i_medium, i_small, c_name, c_code, i_inputDate, i_inputAmount, i_inputPrice, i_outputPrice FROM Item"));
		
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
			 m_si_List.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);  
				// 첫번째 인자는 InsertValue를 통해서 가지고 온 기준이 되는 정보, 두번째 인자는 열단위로 하나씩 
				m_si_List.SetItemText(p, i ,tmp);
			}
			rs.MoveNext(); //다음행으로 이동
		 }
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSalePage::ReInitDialog2()
{
	if(m_si_List.GetItemCount() > 0) m_si_List.DeleteAllItems();

	CDatabase db;			// 데이터베이스 객체 생성
	CRecordset rs (&db);	// 레코드셋 객체 생성
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("데이터베이스 접속실패!");

		CString strQuery;	//데이터베이스에 전송할 쿼리문
		strQuery.Format(_T("SELECT item_id, i_code, i_name, i_large, i_medium, i_small, c_name, c_code, i_inputDate, i_inputAmount, i_inputPrice, i_outputPrice FROM Item"));
		
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
			 m_si_List.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);  
				// 첫번째 인자는 InsertValue를 통해서 가지고 온 기준이 되는 정보, 두번째 인자는 열단위로 하나씩 
				m_si_List.SetItemText(p, i ,tmp);
			}
			rs.MoveNext(); //다음행으로 이동
		 }
	}

	rs.Close();	//레코드셋 객체 소멸
	db.Close();	//데이터베이스 객체 소멸


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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int nIndex;
	nIndex = m_scombosearch.GetCurSel();   // 현재 선택된 항목의 인덱스를 얻음

	if(nIndex == 3)
   {
	   GetDlgItem(IDC_STATIC_INPUTDATE)->ShowWindow(SW_SHOW);
   }
	else
		GetDlgItem(IDC_STATIC_INPUTDATE)->ShowWindow(SW_HIDE);
}

void CSalePage::OnBnClickedSearchbtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);

	if(m_si_List.GetItemCount() > 0) m_si_List.DeleteAllItems();

	CDatabase db;			// 데이터베이스 객체 생성
	CRecordset rs (&db);	// 레코드셋 객체 생성
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("데이터베이스 접속실패!");

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
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	if(bFirst){
		CString img;
		img.Format(_T("res\\NoImage.bmp"));
		DrawBMP(img);
		//bFirst = FALSE;
	}
	// 그리기 메시지에 대해서는 CPropertyPage::OnPaint()을(를) 호출하지 마십시오.
}


void CSalePage::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(!UpdateData()) return;
	UpdateData(TRUE);


	//판매날짜

	CString sdate;
		sdate.Format(_T("%d-%02d-%02d"),m_sdate.GetYear(),m_sdate.GetMonth(),m_sdate.GetDay());


	CDatabase db;			// 데이터베이스 객체 생성
	CRecordset rs (&db);	// 레코드셋 객체 생성
	

	CString amount;		//재고수량계산
	amount.Format(_T("%d"), _ttoi(m_icount) - _ttoi(m_samount));

	CString total_price;
	total_price.Format(_T("%d"), _ttoi(m_samount) * _ttoi(m_iOutputprice));
	CString s;


	if(_ttoi(m_samount) < _ttoi(m_icount)){  //판매수량 < 상품수량
		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("데이터베이스 접속실패!");

			CString strQuery;	//데이터베이스에 전송할 쿼리문
			strQuery.Format(_T("INSERT INTO Sale (s_outputDate , in_ccode, out_ccode, i_code , s_outputAmount, i_inputPrice, i_outputPrice, order_total, return_YN, return_date, return_reson, exchange_YN, exchange_date, exchange_reason, delivery_YN, delivery_process, sale_id)  VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '아니오', \
							   '해당없음', '해당없음', '아니오', '해당없음', '해당없음', '아니오', '해당없음', '%s')"), 
							   sdate,m_iccode, m_outccode, m_si_code,m_samount,m_iinputprice,m_iOutputprice,total_price , g_setid);
			db.ExecuteSQL(strQuery);	//데이터베이스에 쿼리문 전송

			strQuery.Format(_T("UPDATE Item SET i_inputAmount = '%s' WHERE i_code = '%s'"), amount, m_icode);
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

		rs.Close();	//레코드셋 객체 소멸
		db.Close();	//데이터베이스 객체 소멸
		//OnBnClickedClear();	//컨트롤 초기화
		AfxMessageBox(_T("판매되었습니다."));
		m_ssearch = _T("");
		m_si_code = _T("");
		m_si_name = _T("");
		m_total_amount = _T("");
		m_outcname = _T("");
		m_samount = _T("");
		//생일초기화
		CDateTimeCtrl *pCtrl = (CDateTimeCtrl *) GetDlgItem(IDC_DATETIMEPICKER3);
		CTime tm = CTime::GetCurrentTime();
		pCtrl->SetTime(&tm);

		
		m_scombosearch.SetCurSel(0);
		m_combo1.SetCurSel(-1);
		m_combo2.SetCurSel(-1);
		m_combo3.SetCurSel(-1);

		//이미지초기화
		CString img;
		img.Format(_T("res\\NoImage.bmp"));
		DrawBMP(img);

	}else{    //판매수량이 재고수량보다 많을 때
		AfxMessageBox(_T("판매될 수 없습니다."));
		m_samount = _T("");
	}
		
		UpdateData(false);
}


void CSalePage::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int nColumn = phdr->iItem;
	// 현재 리스트 컨트롤에 있는 데이터 총 자료 개수만큼 저장
	 for(int i=0; i< (m_si_List.GetItemCount()); i++)
	{
	 m_si_List.SetItemData(i, i);
	}

	// 정렬 방식 지정(Ascend, Descend)
	 m_bAscending = !m_bAscending;
	 UpdateArrow();

	// 정렬 관련된 구조체 변수 생성 및 데이터 초기화
	SORTPARAM sortparams;
	sortparams.pList = &m_si_List;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending;

	// 정렬 함수 호출
	m_si_List.SortItems(&CompareItem, (LPARAM)&sortparams );

	*pResult = 0;
}


HCURSOR CSalePage::OnQueryDragIcon()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CPropertyPage::OnQueryDragIcon();
}


void CSalePage::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CPropertyPage::OnSysCommand(nID, lParam);
}

void CSalePage::DrawBMP(LPCTSTR lpszFileName)	//이미지 보여주기
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

	m_siimage.GetWindowRect(&rect);//다이어로그에 배치된 컨트롤의 크기를 얻어 옴
	cp.x = rect.left;//이미지 출력을 위한 시작 x 좌표
	cp.y = rect.top;//이미지 출력을 위한 시작 y 좌표 
	ScreenToClient(&cp);//cp가 가지고 있는 좌표로 화면을 지정함
	pDC->StretchBlt(cp.x,cp.y,rect.Width(),rect.Height() ,&MemDC,0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);//이미지를 해당 컨트롤로 전송
	MemDC.SelectObject(pOldBmp);
	ReleaseDC(pDC);//DC 반환
}

#include "SaleComSearchDlg.h"


void CSalePage::OnBnClickedSearchbtn2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CSaleComSearchDlg pDlg;
	pDlg.DoModal();
	m_cname_D.SetWindowTextW(pDlg.m_cnameset);
	m_outccode = pDlg.m_ccodeset;
	//m_outcname = pDlg.m_cnameset;
}
