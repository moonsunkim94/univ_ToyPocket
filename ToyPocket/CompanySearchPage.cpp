// CompanySearchPage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "CompanySearchPage.h"
#include "afxdialogex.h"
#include "CompanySheet.h"
#include "XLEzAutomation.h"

// CCompanySearchPage 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCompanySearchPage, CPropertyPage)

CCompanySearchPage::CCompanySearchPage()
	: CPropertyPage(CCompanySearchPage::IDD)
	, m_csearch(_T(""))
{

}

CCompanySearchPage::~CCompanySearchPage()
{
}

void CCompanySearchPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT7, m_csearch);
	DDX_Control(pDX, IDC_LIST1, m_cs_list);
	DDX_Control(pDX, IDC_COMBO_SEARCH, m_combosearch);
	DDX_Control(pDX, SEARCHBTN, m_searchbtn);
	DDX_Control(pDX, IDC_BUTTON2, m_clearbtn);
	DDX_Control(pDX, IDC_BUTTON1, m_excelbtn);
	DDX_Control(pDX, IDC_EDIT7, m_Edit);
}


BEGIN_MESSAGE_MAP(CCompanySearchPage, CPropertyPage)
	ON_BN_CLICKED(SEARCHBTN, &CCompanySearchPage::OnBnClickedSearchbtn)
	ON_BN_CLICKED(IDOK, &CCompanySearchPage::OnBnClickedOk)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CCompanySearchPage::OnHdnItemclickList1)
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CCompanySearchPage::OnNMDblclkList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CCompanySearchPage::OnNMRClickList1)
	ON_COMMAND(ID_COMPANY_DELETE, &CCompanySearchPage::OnCompanyDelete)
	ON_BN_CLICKED(IDC_BUTTON1, &CCompanySearchPage::OnBnClickedExcelSave)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, OnCustomdrawList)

	ON_BN_CLICKED(IDC_BUTTON2, &CCompanySearchPage::OnBnClickedClear)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCompanySearchPage 메시지 처리기입니다.
void CCompanySearchPage::OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult)
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



void CCompanySearchPage::OnBnClickedSearchbtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);

	if(m_cs_list.GetItemCount() > 0) m_cs_list.DeleteAllItems();

	CDatabase db;			// 데이터베이스 객체 생성
	CRecordset rs (&db);	// 레코드셋 객체 생성
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("데이터베이스 접속실패!");

		CString strQuery;
			
		int nIndex = m_combosearch.GetCurSel();
		if(nIndex == 0){
			strQuery.Format(_T("SELECT  com_id, c_code, c_name, c_sort, c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company WHERE c_code LIKE '%%%s%%' OR c_name LIKE '%%%s%%' OR c_sort LIKE '%%%s%%' OR c_type LIKE '%%%s%%' OR c_business LIKE '%%%s%%' OR c_ceoname LIKE '%%%s%%' OR c_tel LIKE '%%%s%%'"),
				m_csearch,m_csearch,m_csearch,m_csearch,m_csearch,m_csearch,m_csearch);
			result.Format(_T("전체검색-('%s')검색시_"),m_csearch);
		}
		if(nIndex == 1){
			strQuery.Format(_T("SELECT  com_id, c_code, c_name, c_sort, c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company WHERE c_code LIKE '%%%s%%'"),m_csearch);
			result.Format(_T("거래처코드-('%s')검색시_"),m_csearch);
		}
		if(nIndex == 2){
			strQuery.Format(_T("SELECT  com_id, c_code, c_name, c_sort, c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company WHERE c_name LIKE '%%%s%%'"),m_csearch);
			result.Format(_T("거래처명-('%s')검색시_"),m_csearch);
		}
		if(nIndex == 3){
			strQuery.Format(_T("SELECT  com_id, c_code, c_name, c_sort, c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company WHERE c_type LIKE '%%%s%%'"),m_csearch);
			result.Format(_T("업종-('%s')검색시_"),m_csearch);
		}
		if(nIndex == 4){
			strQuery.Format(_T("SELECT  com_id, c_code, c_name, c_sort, c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company WHERE c_business LIKE '%%%s%%'"),m_csearch);
			result.Format(_T("업태-('%s')검색시_"),m_csearch);
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
			 m_cs_list.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				m_cs_list.SetItemText(p, i ,tmp);
			}
			rs.MoveNext(); 
		 }
	}
	rs.Close();
	db.Close();


}





BOOL CCompanySearchPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_cs_list.SetExtendedStyle( LVS_EX_FULLROWSELECT ); //행전체선택

	if(m_cs_list.GetHeaderCtrl()->GetItemCount() <= 0)		//헤더에 아이템이 없다면
	{
		CRect rect;
		m_cs_list.GetClientRect(&rect);
		m_cs_list.InsertColumn(0, _T("담당자"),			LVCFMT_LEFT, 100);
		m_cs_list.InsertColumn(1, _T("거래처코드"),			LVCFMT_LEFT, 80);
		m_cs_list.InsertColumn(2, _T("거래처명"),			LVCFMT_LEFT, 80);
		m_cs_list.InsertColumn(3, _T("업체분류"),			LVCFMT_LEFT, 80);
		m_cs_list.InsertColumn(4, _T("업종"),			    LVCFMT_LEFT, 70);
		m_cs_list.InsertColumn(5, _T("업태"),			    LVCFMT_LEFT, 70);
		m_cs_list.InsertColumn(6, _T("대표자명"),			LVCFMT_LEFT, 80);
		m_cs_list.InsertColumn(7, _T("거래처번호"),			LVCFMT_LEFT, 80);
		m_cs_list.InsertColumn(8, _T("사업자번호"),			LVCFMT_LEFT, 80);
		m_cs_list.InsertColumn(9, _T("주소"),			    LVCFMT_LEFT, 220);
		m_cs_list.InsertColumn(10, _T("거래처 대표 전화"),	LVCFMT_LEFT, 110);
		m_cs_list.InsertColumn(11, _T("거래처 대표 메일"),	LVCFMT_LEFT, 110);
		m_cs_list.InsertColumn(12, _T("거래처 대표 생일"),	LVCFMT_LEFT, 110);
		m_cs_list.InsertColumn(13, _T("메모"),			    LVCFMT_LEFT, 80);
	}
	 m_combosearch.AddString(_T("전체검색"));
	 m_combosearch.AddString(_T("거래처코드"));                   //텍스트 추가
	 m_combosearch.AddString(_T("거래처명"));
	 m_combosearch.AddString(_T("업종"));
	 m_combosearch.AddString(_T("업태"));
	
	 m_combosearch.SetCurSel(0);                                //텍스트 선택

	//헤더 컨트롤 드래그-앤-드롭 가능
	DWORD dwExStyle = m_cs_list.GetExtendedStyle();
	m_cs_list.SetExtendedStyle(dwExStyle | LVS_EX_HEADERDRAGDROP );

	m_bAscending = FALSE;
	m_cs_list.SortItems(&CCompanySearchPage::CompareItem, (DWORD_PTR)this);
	UpdateArrow();
	
	m_searchbtn.LoadBitmaps(IDB_BMP_SEARCH, NULL, NULL, NULL);
	m_searchbtn.SizeToContent();

	m_excelbtn.LoadBitmaps(IDB_BMP_EXCEL, NULL, NULL, NULL);
	m_excelbtn.SizeToContent();
	m_clearbtn.LoadBitmaps(IDB_BMP_CLEAR, NULL, NULL, NULL);
	m_clearbtn.SizeToContent();

	HCURSOR hCursor;
	hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
	SetClassLong(m_cs_list.GetSafeHwnd(),GCL_HCURSOR,(LONG)hCursor);
	
	CFont    m_fontTitle;
	LOGFONT  lf; 

	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 17;
	::lstrcpy(lf.lfFaceName, _T("나눔바른고딕"));
	m_fontTitle.CreateFontIndirect(&lf);
	GetDlgItem(IDC_COMBO_SEARCH)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT7)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_LIST1)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 

		if(m_cs_list.GetItemCount() > 0) m_cs_list.DeleteAllItems();

	CDatabase db;			// 데이터베이스 객체 생성
	CRecordset rs (&db);	// 레코드셋 객체 생성
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("데이터베이스 접속실패!");

		CString strQuery;
		strQuery.Format(_T("SELECT com_id, c_code, c_name, c_sort, c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company"));
		
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
			 m_cs_list.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				// 첫번째 인자는 InsertValue를 통해서 가지고 온 기준이 되는 정보, 두번째 인자는 열단위로 하나씩 
				m_cs_list.SetItemText(p, i ,tmp);
			}
			rs.MoveNext();	//다음행으로 이동
		 }
	}
	rs.Close();	//레코드셋 객체 소멸
	db.Close();	//데이터베이스 객체 소멸

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


int CALLBACK CCompanySearchPage::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl *pListCtrl = ((SORTPARAM *)lParamSort)->pList;

	int iSortColumn = ((SORTPARAM *)lParamSort)->iSortColumn;
	bool bSortDirect = ((SORTPARAM *)lParamSort)->bSortDirect;

	CString    strItem1 = pListCtrl->GetItemText(static_cast<int>(lParam1), iSortColumn);
	CString    strItem2 = pListCtrl->GetItemText(static_cast<int>(lParam2), iSortColumn);

	return bSortDirect ? _tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2) : -_tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2);


}

void CCompanySearchPage::UpdateArrow(void)
{
	CHeaderCtrl* pHeaderCtrl = m_cs_list.GetHeaderCtrl();
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

void CCompanySearchPage::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialog::OnOK(); //이건 그냥 픽처컨트롤에서 다이얼로그만 안보이게함

}


void CCompanySearchPage::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// 리스트컨트롤 칼럼 클릭할 때 데이터 정렬
	// 클릭한 칼럼의 인덱스
	int nColumn = pNMLV->iItem;
	// 현재 리스트 컨트롤에 있는 데이터 총 자료 개수만큼 저장
	 for(int i=0; i< (m_cs_list.GetItemCount()); i++)
	{
	 m_cs_list.SetItemData(i, i);
	}

	// 정렬 방식 지정(Ascend, Descend)
	 m_bAscending = !m_bAscending;


	 UpdateArrow();


	// 정렬 관련된 구조체 변수 생성 및 데이터 초기화
	SORTPARAM sortparams;
	sortparams.pList = &m_cs_list;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending;

	// 정렬 함수 호출
	m_cs_list.SortItems(&CompareItem, (LPARAM)&sortparams );

	*pResult = 0;
}


HCURSOR CCompanySearchPage::OnQueryDragIcon()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//실행하자마자 보이게끔
	return static_cast<HCURSOR>(m_hIcon);
}

#include "CompanyModifyPage.h"

void CCompanySearchPage::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    nListIndex = pNMListView->iItem;

	int formindex;
	
	CString num1;
	//g_set_ccode = m_cs_list.GetItemText(nListIndex,0);

	g_set_cnumber = m_cs_list.GetItemText(nListIndex,8);
	g_set_cname = m_cs_list.GetItemText(nListIndex,2);

	//g_set_csortindex = m_cs_list.GetItemText(nListIndex,1);
	if(m_cs_list.GetItemText(nListIndex,3)==_T("납입처"))
		g_set_csortindex = 0;
	else
		g_set_csortindex = 1;

	g_set_ctype = m_cs_list.GetItemText(nListIndex,4);
	g_set_cbusiness = m_cs_list.GetItemText(nListIndex,5);

	g_set_caddress = m_cs_list.GetItemText(nListIndex,9);
	g_set_cceoname = m_cs_list.GetItemText(nListIndex,6);
	g_set_cemail = m_cs_list.GetItemText(nListIndex,11);

	g_set_cmemo = m_cs_list.GetItemText(nListIndex,13);
	//생일은 11
	AfxExtractSubString(g_set_cbirth_Year,m_cs_list.GetItemText(nListIndex,12), 0,'-');
	AfxExtractSubString(g_set_cbirth_Month,m_cs_list.GetItemText(nListIndex,12), 1,'-');
	AfxExtractSubString(g_set_cbirth_Day,m_cs_list.GetItemText(nListIndex,12), 2,'-');


	CString ctel;
	CString cmTel;
	//ctel
	AfxExtractSubString(ctel,m_cs_list.GetItemText(nListIndex,7), 0,'-');
	if(ctel==_T("02"))
		g_set_ctelindex = 0;
	else
		g_set_ctelindex = 1;
	//set_ctel
	AfxExtractSubString(g_set_ctel1,m_cs_list.GetItemText(nListIndex,7), 1,'-');
	AfxExtractSubString(g_set_ctel2,m_cs_list.GetItemText(nListIndex,7), 2,'-');

	AfxExtractSubString(cmTel,m_cs_list.GetItemText(nListIndex,10), 0,'-');
	if(cmTel==_T("010"))
		g_set_cmtelindex = 0;
	else
		g_set_cmtelindex = 1;
	//set_ctel
	AfxExtractSubString(g_set_cmtel1,m_cs_list.GetItemText(nListIndex,10), 1,'-');
	AfxExtractSubString(g_set_cmtel2,m_cs_list.GetItemText(nListIndex,10), 2,'-');


	UpdateData(FALSE);//필요한가

	CCompanySheet* pSheet = (CCompanySheet*)GetParent();
	pSheet->SetActivePage(2);
	*pResult = 0;
	//modifypage의 에디트 컨트롤의 위에 변수들 넣어줘야함
}


void CCompanySearchPage::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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
	pContextMenu = muTemp.GetSubMenu(2);
	pContextMenu -> TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, ptInSrceen.x, ptInSrceen.y,this);
	}
	ccode = m_cs_list.GetItemText(nListIndex,1);

	*pResult = 0;
}




void CCompanySearchPage::OnCompanyDelete()
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
			strQuery.Format(_T("DELETE * FROM Company WHERE c_code = '%s' "),ccode);
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

	if(m_cs_list.GetItemCount() > 0) m_cs_list.DeleteAllItems();

	CDatabase db1;			// 데이터베이스 객체 생성
	CRecordset rs1 (&db1);	// 레코드셋 객체 생성
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db1.OpenEx (strConnection) == FALSE)
			  throw _T("데이터베이스 접속실패!");

		CString strQuery;
		strQuery.Format(_T("SELECT com_id, c_code, c_name, c_sort, c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company"));
		
		if (rs1.Open (CRecordset::snapshot, strQuery) == FALSE)	
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
	short col1 = rs1.GetODBCFieldCount();	
	for(int p=0 ; p<2 ; p++)
	{
		 while( ! rs1.IsEOF())		//행단위
		 {
			 //속성단위
			 CString tmp;
			 rs1.GetFieldValue((short)p, tmp);  
			 //id값이 기준이 된다.
			 m_cs_list.InsertItem(p,tmp,0);
			 for(short i=1; i<col1; i++  )
			 {
				rs1.GetFieldValue(i, tmp);
				// 첫번째 인자는 InsertValue를 통해서 가지고 온 기준이 되는 정보, 두번째 인자는 열단위로 하나씩 
				m_cs_list.SetItemText(p, i ,tmp);
			}
			rs1.MoveNext();	//다음행으로 이동
		 }
	}
	rs1.Close();	//레코드셋 객체 소멸
	db1.Close();	//데이터베이스 객체 소멸

	
}


void CCompanySearchPage::OnBnClickedExcelSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_cs_list.GetItemCount() <= 0)
	{
		 AfxMessageBox(_T("조회된 데이터가 0건이므로 엑셀 저장 할 수 없습니다."));
		 return;
	}

	CTime timeNow = CTime::GetCurrentTime();
	CString strDateTime;
	strDateTime = timeNow.Format(_T("%Y-%m-%d_%H시%M분%S초"));
	CString strFileName;
	strFileName.Format(_T("%s거래처 조회_%s"), result, strDateTime);

	CFileDialog fdlg(FALSE, _T("xlsx"), strFileName+_T(".xlsx"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("xlsx 파일 (*.xlsx)|*.xlsx"), NULL);
	if (fdlg.DoModal() != IDOK) return;

	CXLEzAutomation xls(FALSE);  // FALSE : 처리 과정을 화면에 보이지 않는다.

	int rowOffset = 2;
	int colOffset = 1;

	int rowCount = m_cs_list.GetItemCount();
	CHeaderCtrl* pHeaderCtrl = m_cs_list.GetHeaderCtrl();
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
			strItemText = m_cs_list.GetItemText(rowIdx, colIdx);

			// 컬럼 데이터
			xls.SetCellValue(colIdx + colOffset, rowIdx +1 + rowOffset, strItemText);
		}
	}

	xls.SaveFileAs(fdlg.GetPathName());

	xls.ReleaseExcel();
}


void CCompanySearchPage::OnBnClickedClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_csearch=_T("");
	m_combosearch.SetCurSel(0);                                //텍스트 선택
	OnInitDialog();
}


HBRUSH CCompanySearchPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	/*
	if (pWnd->GetDlgCtrlID() == IDC_EDIT7)
	{
		pDC->SetBkColor(RGB(252, 249, 204));
		pDC->SetBkMode(OPAQUE);

		return 0;
	}
	*/
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CCompanySearchPage::ReInitDialog()
{

	if(m_cs_list.GetItemCount() > 0) m_cs_list.DeleteAllItems();

	CDatabase db1;			// 데이터베이스 객체 생성
	CRecordset rs1 (&db1);	// 레코드셋 객체 생성
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db1.OpenEx (strConnection) == FALSE)
			  throw _T("데이터베이스 접속실패!");

		CString strQuery;
		strQuery.Format(_T("SELECT com_id, c_code, c_name, c_sort, c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company"));

		if (rs1.Open (CRecordset::snapshot, strQuery) == FALSE)	
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
	short col1 = rs1.GetODBCFieldCount();	
	for(int p=0 ; p<2 ; p++)
	{
		 while( ! rs1.IsEOF())		//행단위
		 {
			 //속성단위
			 CString tmp;
			 rs1.GetFieldValue((short)p, tmp);  
			 //id값이 기준이 된다.
			 m_cs_list.InsertItem(p,tmp,0);
			 for(short i=1; i<col1; i++  )
			 {
				rs1.GetFieldValue(i, tmp);
				// 첫번째 인자는 InsertValue를 통해서 가지고 온 기준이 되는 정보, 두번째 인자는 열단위로 하나씩 
				m_cs_list.SetItemText(p, i ,tmp);
			}
			rs1.MoveNext();	//다음행으로 이동
		 }
	}
	rs1.Close();	//레코드셋 객체 소멸
	db1.Close();	//데이터베이스 객체 소멸

	return;
}


