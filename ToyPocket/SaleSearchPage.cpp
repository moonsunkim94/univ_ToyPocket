// SaleSearchPage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "SaleSearchPage.h"
#include "afxdialogex.h"
#include "XLEzAutomation.h"

// CSaleSearchPage 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSaleSearchPage, CPropertyPage)

CSaleSearchPage::CSaleSearchPage()
	: CPropertyPage(CSaleSearchPage::IDD)
	, m_ssearch(_T(""))
{

}

CSaleSearchPage::~CSaleSearchPage()
{
}

void CSaleSearchPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_s_List);
	DDX_Control(pDX, IDC_COMBO1, m_ssearch_combo);
	DDX_Text(pDX, IDC_EDIT7, m_ssearch);
	DDX_Control(pDX, IDCANCEL5, m_isearch_btn);
	DDX_Control(pDX, IDC_BUTTON1, m_excelbtn);
	DDX_Control(pDX, IDC_BUTTON2, m_clearbtn);
}


BEGIN_MESSAGE_MAP(CSaleSearchPage, CPropertyPage)
	ON_BN_CLICKED(IDCANCEL5, &CSaleSearchPage::OnBnClickedSaleSearchBtn)
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CSaleSearchPage::OnHdnItemclickList1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSaleSearchPage::OnCbnSelchangeCombo1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CSaleSearchPage::OnNMRClickList1)
	ON_COMMAND(ID_SALE_DELETE, &CSaleSearchPage::OnSaleDelete)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CSaleSearchPage::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CSaleSearchPage::OnBnClickedExcelSave)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, OnCustomdrawList)
	ON_BN_CLICKED(IDC_BUTTON2, &CSaleSearchPage::OnBnClickedClear)
END_MESSAGE_MAP()


// CSaleSearchPage 메시지 처리기입니다.
void CSaleSearchPage::OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult)
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
void CSaleSearchPage::OnBnClickedSaleSearchBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);

	if(m_s_List.GetItemCount() > 0) m_s_List.DeleteAllItems();

	CDatabase db;			// 데이터베이스 객체 생성
	CRecordset rs (&db);	// 레코드셋 객체 생성
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("데이터베이스 접속실패!");

		CString strQuery;
			
		int nIndex = m_ssearch_combo.GetCurSel();
		if(nIndex == 0){
			strQuery.Format(_T("SELECT s_Key, sale_id, s_outputDate, in_ccode,out_ccode, i_code, s_outputAmount, i_inputPrice, i_outputPrice, order_total, exchange_YN, exchange_date, exchange_reason, return_YN, return_date, return_reson FROM Sale WHERE s_outputDate LIKE '%%%s%%' OR out_ccode LIKE '%%%s%%' OR i_code LIKE '%%%s%%' OR in_ccode LIKE '%%%s%%' OR s_outputAmount LIKE '%%%s%%' OR i_inputPrice LIKE '%%%s%%' OR i_outputPrice LIKE '%%%s%%' OR order_total LIKE '%%%s%%' OR return_YN LIKE '%%%s%%' OR return_date LIKE '%%%s%%' OR return_reson LIKE '%%%s%%' OR exchange_YN LIKE '%%%s%%' OR exchange_date LIKE '%%%s%%' OR exchange_reason LIKE '%%%s%%' OR sale_id LIKE '%%%s%%'"),
				m_ssearch,m_ssearch,m_ssearch,m_ssearch,m_ssearch,m_ssearch,m_ssearch,m_ssearch,m_ssearch,m_ssearch,m_ssearch,m_ssearch,m_ssearch,m_ssearch,m_ssearch);
			result.Format(_T("전체검색-('%s')검색시_"),m_ssearch);
		}
		if(nIndex == 1){
			strQuery.Format(_T("SELECT s_Key, sale_id, s_outputDate, in_ccode,out_ccode, i_code, s_outputAmount, i_inputPrice, i_outputPrice, order_total, exchange_YN, exchange_date, exchange_reason, return_YN, return_date, return_reson FROM Sale WHERE s_outputDate LIKE '%%%s%%'"),m_ssearch);
			result.Format(_T("판매날짜-('%s')검색시_"),m_ssearch);
		}
		if(nIndex == 2){
			strQuery.Format(_T("SELECT s_Key, sale_id, s_outputDate,in_ccode,out_ccode, i_code, s_outputAmount, i_inputPrice, i_outputPrice, order_total, exchange_YN, exchange_date, exchange_reason, return_YN, return_date, return_reson FROM Sale WHERE i_code LIKE '%%%s%%'"),m_ssearch);
			result.Format(_T("상품코드-('%s')검색시_"),m_ssearch);
		}
		if(nIndex == 3){
			strQuery.Format(_T("SELECT s_Key, sale_id, s_outputDate, in_ccode,out_ccode, i_code, s_outputAmount, i_inputPrice, i_outputPrice, order_total, exchange_YN, exchange_date, exchange_reason, return_YN, return_date, return_reson FROM Sale WHERE out_ccode LIKE '%%%s%%'"),m_ssearch);
			result.Format(_T("납품처코드-('%s')검색시_"),m_ssearch);
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
			 m_s_List.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				m_s_List.SetItemText(p, i ,tmp);
			}
			rs.MoveNext(); 
		 }
	}
	rs.Close();
	db.Close();
}

BOOL CSaleSearchPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_s_List.SetExtendedStyle(LVS_EX_FULLROWSELECT); //행전체선택

	if(m_s_List.GetHeaderCtrl()->GetItemCount() <= 0)		//헤더에 아이템이 없다면
	{
		CRect rect;
		m_s_List.GetClientRect(&rect);
		m_s_List.InsertColumn(0, _T(""),			LVCFMT_LEFT, 0);
		m_s_List.InsertColumn(1, _T("담당자"),	LVCFMT_LEFT, 100);
		m_s_List.InsertColumn(2, _T("판매날짜"),			LVCFMT_LEFT, 100);
		m_s_List.InsertColumn(3, _T("납입처코드"),			LVCFMT_LEFT, 80);
		m_s_List.InsertColumn(4, _T("납품처코드"),			LVCFMT_LEFT, 80);
		m_s_List.InsertColumn(5, _T("상품코드"),			LVCFMT_LEFT, 80);
		m_s_List.InsertColumn(6, _T("주문수량"),			    LVCFMT_LEFT, 80);
		m_s_List.InsertColumn(7, _T("매입가"),			    LVCFMT_LEFT, 80);
		m_s_List.InsertColumn(8, _T("판매가"),			LVCFMT_LEFT, 80);
		m_s_List.InsertColumn(9, _T("총주문금액"),			LVCFMT_LEFT, 80);
		m_s_List.InsertColumn(10, _T("교환여부"),			LVCFMT_LEFT, 60);
		m_s_List.InsertColumn(11, _T("교환날짜"),			LVCFMT_LEFT, 80);
		m_s_List.InsertColumn(12, _T("교환이유"),			    LVCFMT_LEFT, 80);
		m_s_List.InsertColumn(13, _T("반품여부"),	LVCFMT_LEFT, 60);
		m_s_List.InsertColumn(14, _T("반품날짜"),	LVCFMT_LEFT, 80);
		m_s_List.InsertColumn(15, _T("반품이유"),	LVCFMT_LEFT, 80);
	}

	m_ssearch_combo.AddString(_T("전체검색"));
	m_ssearch_combo.AddString(_T("판매날짜"));
	m_ssearch_combo.AddString(_T("상품코드"));
	m_ssearch_combo.AddString(_T("납품처코드"));

	m_ssearch_combo.SetCurSel(0);
	GetDlgItem(IDC_STATIC_INPUTDATE)->ShowWindow(SW_HIDE);

	m_isearch_btn.LoadBitmaps(IDB_BMP_SEARCH, NULL, NULL, NULL);
	m_isearch_btn.SizeToContent();
	m_excelbtn.LoadBitmaps(IDB_BMP_EXCEL, NULL, NULL, NULL);
	m_excelbtn.SizeToContent();
	m_clearbtn.LoadBitmaps(IDB_BMP_CLEAR, NULL, NULL, NULL);
	m_clearbtn.SizeToContent();

	//헤더 컨트롤 드래그-앤-드롭 가능
	DWORD dwExStyle = m_s_List.GetExtendedStyle();
	m_s_List.SetExtendedStyle(dwExStyle | LVS_EX_HEADERDRAGDROP );

	m_bAscending = FALSE;
	m_s_List.SortItems(&CSaleSearchPage::CompareItem, (DWORD_PTR)this);
	UpdateArrow();

	CFont    m_fontTitle;
	LOGFONT  lf; 

	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 17;
	::lstrcpy(lf.lfFaceName, _T("나눔바른고딕"));
	m_fontTitle.CreateFontIndirect(&lf);
	GetDlgItem(IDC_COMBO1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT7)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC_INPUTDATE)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_LIST1)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 

	if(m_s_List.GetItemCount() > 0) m_s_List.DeleteAllItems();

	CDatabase db;			// 데이터베이스 객체 생성
	CRecordset rs (&db);	// 레코드셋 객체 생성
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("데이터베이스 접속실패!");

		CString strQuery;
		strQuery.Format(_T("SELECT s_Key, sale_id, s_outputDate, in_ccode, out_ccode,  i_code, s_outputAmount, i_inputPrice, i_outputPrice, order_total, exchange_YN, exchange_date, exchange_reason, return_YN, return_date, return_reson FROM Sale"));
		
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
			 m_s_List.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				// 첫번째 인자는 InsertValue를 통해서 가지고 온 기준이 되는 정보, 두번째 인자는 열단위로 하나씩 
				m_s_List.SetItemText(p, i ,tmp);
			}
			rs.MoveNext();	//다음행으로 이동
		 }
	}
	rs.Close();	//레코드셋 객체 소멸
	db.Close();	//데이터베이스 객체 소멸

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



int CALLBACK CSaleSearchPage::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl *pListCtrl = ((SORTPARAM *)lParamSort)->pList;

	int iSortColumn = ((SORTPARAM *)lParamSort)->iSortColumn;
	bool bSortDirect = ((SORTPARAM *)lParamSort)->bSortDirect;

	CString    strItem1 = pListCtrl->GetItemText(static_cast<int>(lParam1), iSortColumn);
	CString    strItem2 = pListCtrl->GetItemText(static_cast<int>(lParam2), iSortColumn);

	return bSortDirect ? _tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2) : -_tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2);

}

void CSaleSearchPage::UpdateArrow(void)
{
	CHeaderCtrl* pHeaderCtrl = m_s_List.GetHeaderCtrl();
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

void CSaleSearchPage::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CPropertyPage::OnSysCommand(nID, lParam);
}


HCURSOR CSaleSearchPage::OnQueryDragIcon()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CPropertyPage::OnQueryDragIcon();
}


void CSaleSearchPage::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nColumn = phdr->iItem;
	// 현재 리스트 컨트롤에 있는 데이터 총 자료 개수만큼 저장
	 for(int i=0; i< (m_s_List.GetItemCount()); i++)
	{
	 m_s_List.SetItemData(i, i);
	}

	// 정렬 방식 지정(Ascend, Descend)
	 m_bAscending = !m_bAscending;

	 UpdateArrow();

	// 정렬 관련된 구조체 변수 생성 및 데이터 초기화
	SORTPARAM sortparams;
	sortparams.pList = &m_s_List;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending;

	// 정렬 함수 호출
	m_s_List.SortItems(&CompareItem, (LPARAM)&sortparams );

	*pResult = 0;
}

#include "SaleSheet.h"

void CSaleSearchPage::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
		int nIndex;
	nIndex = m_ssearch_combo.GetCurSel();   // 현재 선택된 항목의 인덱스를 얻음

	if(nIndex == 1)
   {
	   GetDlgItem(IDC_STATIC_INPUTDATE)->ShowWindow(SW_SHOW);
   }
	else
		GetDlgItem(IDC_STATIC_INPUTDATE)->ShowWindow(SW_HIDE);


}


void CSaleSearchPage::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    nListIndex = pNMListView->iItem;

	CPoint ptInSrceen;

    GetCursorPos(&ptInSrceen); //R버튼 눌린좌표얻음

	if(nListIndex==-1){
	}
	else{
	CMenu muTemp, *pContextMenu;
	muTemp.LoadMenuW(IDR_PopupMenu);
	pContextMenu = muTemp.GetSubMenu(0);
	pContextMenu -> TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, ptInSrceen.x, ptInSrceen.y,this);
	}

	m_skey = _ttoi(m_s_List.GetItemText(nListIndex,0));

	*pResult = 0;
}


void CSaleSearchPage::OnSaleDelete()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int ret;
	ret = AfxMessageBox(_T("삭제하시겠습니까?"), MB_YESNO|MB_ICONSTOP);
	if(ret == IDYES){
	UpdateData(TRUE);

	CDatabase db;			// 데이터베이스 객체 생성
	CRecordset rs (&db);	// 레코드셋 객체 생성
	
		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("데이터베이스 접속실패!");

			CString strQuery;	//데이터베이스에 전송할 쿼리문
			strQuery.Format(_T("DELETE * FROM Sale WHERE Sale.s_Key= %d "),m_skey);
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
	}
	if(m_s_List.GetItemCount() > 0) m_s_List.DeleteAllItems();

	CDatabase db;			// 데이터베이스 객체 생성
	CRecordset rs (&db);	// 레코드셋 객체 생성
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("데이터베이스 접속실패!");

		CString strQuery;
		strQuery.Format(_T("SELECT s_Key, sale_id, s_outputDate, in_ccode, out_ccode,  i_code, s_outputAmount, i_inputPrice, i_outputPrice, order_total, exchange_YN, exchange_date, exchange_reason, return_YN, return_date, return_reson FROM Sale"));
		
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
			 m_s_List.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				// 첫번째 인자는 InsertValue를 통해서 가지고 온 기준이 되는 정보, 두번째 인자는 열단위로 하나씩 
				m_s_List.SetItemText(p, i ,tmp);
			}
			rs.MoveNext();	//다음행으로 이동
		 }
	}
	rs.Close();	//레코드셋 객체 소멸
	db.Close();	//데이터베이스 객체 소멸

}


void CSaleSearchPage::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    nListIndex = pNMListView->iItem;
	AfxExtractSubString(g_soutDate_Year,m_s_List.GetItemText(nListIndex,2), 0,'-');
	AfxExtractSubString(g_soutDate_Month,m_s_List.GetItemText(nListIndex,2), 1,'-');
	AfxExtractSubString(g_soutDate_Day,m_s_List.GetItemText(nListIndex,2), 2,'-');

	g_soutAmount = m_s_List.GetItemText(nListIndex,5);
	g_icode = m_s_List.GetItemText(nListIndex,4);

	CSaleSheet* pSheet = (CSaleSheet*)GetParent();
	pSheet->SetActivePage(2);
	*pResult = 0;
}


void CSaleSearchPage::OnBnClickedExcelSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_s_List.GetItemCount() <= 0)
	{
		 AfxMessageBox(_T("조회된 데이터가 0건이므로 엑셀 저장 할 수 없습니다."));
		 return;
	}

	CTime timeNow = CTime::GetCurrentTime();
	CString strDateTime;
	strDateTime = timeNow.Format(_T("%Y-%m-%d_%H시%M분%S초"));
	CString strFileName;
	strFileName.Format(_T("판매 조회_%s"), strDateTime);

	CFileDialog fdlg(FALSE, _T("xlsx"), strFileName+_T(".xlsx"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("xlsx 파일 (*.xlsx)|*.xlsx"), NULL);
	if (fdlg.DoModal() != IDOK) return;

	CXLEzAutomation xls(FALSE);  // FALSE : 처리 과정을 화면에 보이지 않는다.

	int rowOffset = 2;
	int colOffset = 1;

	int rowCount = m_s_List.GetItemCount();
	CHeaderCtrl* pHeaderCtrl = m_s_List.GetHeaderCtrl();
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
			strItemText = m_s_List.GetItemText(rowIdx, colIdx);

			// 컬럼 데이터
			xls.SetCellValue(colIdx + colOffset, rowIdx +1 + rowOffset, strItemText);
		}
	}

	xls.SaveFileAs(fdlg.GetPathName());

	xls.ReleaseExcel();
}


void CSaleSearchPage::OnBnClickedClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ssearch=_T("");
	m_ssearch_combo.SetCurSel(0);                                //텍스트 선택
	OnInitDialog();
}
