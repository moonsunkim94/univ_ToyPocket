// SaleComSearchDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "SaleComSearchDlg.h"
#include "afxdialogex.h"


// CSaleComSearchDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSaleComSearchDlg, CDialogEx)

CSaleComSearchDlg::CSaleComSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSaleComSearchDlg::IDD, pParent)
	, m_csearch(_T(""))
{

}

CSaleComSearchDlg::~CSaleComSearchDlg()
{
}

void CSaleComSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SEARCH, m_ccombobox);
	DDX_Text(pDX, IDC_EDIT7, m_csearch);
	DDX_Control(pDX, IDC_LIST1, m_cs_List);
	DDX_Control(pDX, IDOK4, m_combtn);
}


BEGIN_MESSAGE_MAP(CSaleComSearchDlg, CDialogEx)
	ON_BN_CLICKED(IDOK4, &CSaleComSearchDlg::OnBnClickedSearch)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CSaleComSearchDlg::OnHdnItemclickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CSaleComSearchDlg::OnNMDblclkList1)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, OnCustomdrawList)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CSaleComSearchDlg 메시지 처리기입니다.

void CSaleComSearchDlg::OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult)
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

void CSaleComSearchDlg::OnBnClickedSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);

	if(m_cs_List.GetItemCount() > 0) m_cs_List.DeleteAllItems();

	CDatabase db;			// 데이터베이스 객체 생성
	CRecordset rs (&db);	// 레코드셋 객체 생성
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("데이터베이스 접속실패!");

		CString strQuery;
			
		int nIndex = m_ccombobox.GetCurSel();
		if(nIndex == 0){
			strQuery.Format(_T("SELECT com_id, c_code, c_name,  c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company WHERE c_code LIKE '%%%s%%' OR c_name LIKE '%%%s%%' OR c_sort LIKE '%%%s%%' OR c_type LIKE '%%%s%%' OR c_business LIKE '%%%s%%' OR c_ceoname LIKE '%%%s%%' OR c_tel LIKE '%%%s%%' AND c_sort = '납품처'"),
				m_csearch,m_csearch,m_csearch,m_csearch,m_csearch,m_csearch,m_csearch);
		}
		if(nIndex == 1){
			strQuery.Format(_T("SELECT com_id, c_code, c_name,  c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company WHERE c_code LIKE '%%%s%%' AND c_sort = '납품처'"),m_csearch);
		}
		if(nIndex == 2){
			strQuery.Format(_T("SELECT com_id, c_code, c_name,  c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company WHERE c_name LIKE '%%%s%%' AND c_sort = '납품처'"),m_csearch);
		}
		if(nIndex == 3){
			strQuery.Format(_T("SELECT com_id, c_code, c_name,  c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company WHERE c_type LIKE '%%%s%%' AND c_sort = '납품처'"),m_csearch);
		}
		if(nIndex == 4){
			strQuery.Format(_T("SELECT com_id, c_code, c_name,  c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo FROM Company WHERE c_business LIKE '%%%s%%' AND c_sort = '납품처'"),m_csearch);
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
			 m_cs_List.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				m_cs_List.SetItemText(p, i ,tmp);
			}
			rs.MoveNext(); 
		 }
	}
	rs.Close();
	db.Close();
}


void CSaleComSearchDlg::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nColumn = phdr->iItem;
	// 현재 리스트 컨트롤에 있는 데이터 총 자료 개수만큼 저장
	 for(int i=0; i< (m_cs_List.GetItemCount()); i++)
	{
	 m_cs_List.SetItemData(i, i);
	}

	// 정렬 방식 지정(Ascend, Descend)
	 m_bAscending = !m_bAscending;


	 UpdateArrow();


	// 정렬 관련된 구조체 변수 생성 및 데이터 초기화
	SORTPARAM sortparams;
	sortparams.pList = &m_cs_List;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending;

	// 정렬 함수 호출
	m_cs_List.SortItems(&CompareItem, (LPARAM)&sortparams );
	*pResult = 0;
}


void CSaleComSearchDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    nListIndex = pNMListView->iItem;
	UpdateData();
	m_ccodeset = m_cs_List.GetItemText(nListIndex,1);
	m_cnameset = m_cs_List.GetItemText(nListIndex,2);
	*pResult = 0;
	CDialogEx::OnOK();
}


BOOL CSaleComSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_combtn.LoadBitmaps(IDB_BMP_SEARCH, NULL, NULL, NULL);
	m_combtn.SizeToContent();
	m_cs_List.SetExtendedStyle( LVS_EX_FULLROWSELECT ); //행전체선택

	if(m_cs_List.GetHeaderCtrl()->GetItemCount() <= 0)		//헤더에 아이템이 없다면
	{
		CRect rect;
		m_cs_List.GetClientRect(&rect);
		m_cs_List.InsertColumn(0, _T("담당자"),			LVCFMT_LEFT, 80);
		m_cs_List.InsertColumn(1, _T("거래처코드"),			LVCFMT_LEFT, 80);
		m_cs_List.InsertColumn(2, _T("거래처명"),			LVCFMT_LEFT, 80);
		m_cs_List.InsertColumn(3, _T("업종"),			    LVCFMT_LEFT, 70);
		m_cs_List.InsertColumn(4, _T("업태"),			    LVCFMT_LEFT, 70);
		m_cs_List.InsertColumn(5, _T("대표자명"),			LVCFMT_LEFT, 80);
		m_cs_List.InsertColumn(6, _T("거래처번호"),			LVCFMT_LEFT, 80);
		m_cs_List.InsertColumn(7, _T("사업자번호"),			LVCFMT_LEFT, 80);
		m_cs_List.InsertColumn(8, _T("주소"),			    LVCFMT_LEFT, 80);
		m_cs_List.InsertColumn(9, _T("거래처 대표 전화"),	LVCFMT_LEFT, 110);
		m_cs_List.InsertColumn(10, _T("거래처 대표 메일"),	LVCFMT_LEFT, 110);
		m_cs_List.InsertColumn(11, _T("거래처 대표 생일"),	LVCFMT_LEFT, 110);
		m_cs_List.InsertColumn(12, _T("메모"),			    LVCFMT_LEFT, 80);
	}
	 m_ccombobox.AddString(_T("전체검색"));
	 m_ccombobox.AddString(_T("거래처코드"));                   //텍스트 추가
	 m_ccombobox.AddString(_T("거래처명"));
	 m_ccombobox.AddString(_T("업종"));
	 m_ccombobox.AddString(_T("업태"));
	
	 m_ccombobox.SetCurSel(0);                                //텍스트 선택

	//헤더 컨트롤 드래그-앤-드롭 가능
	DWORD dwExStyle = m_cs_List.GetExtendedStyle();
	m_cs_List.SetExtendedStyle(dwExStyle | LVS_EX_HEADERDRAGDROP );

	m_bAscending = FALSE;
	m_cs_List.SortItems(&CSaleComSearchDlg::CompareItem, (DWORD_PTR)this);
	UpdateArrow();
	
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
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSaleComSearchDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if(m_cs_List.GetItemCount() > 0) m_cs_List.DeleteAllItems();

	CDatabase db;			// 데이터베이스 객체 생성
	CRecordset rs (&db);	// 레코드셋 객체 생성
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("데이터베이스 접속실패!");

		CString strQuery;
		strQuery.Format(_T("SELECT com_id, c_code, c_name,  c_type, c_business, c_ceoname, c_tel, c_number, c_address, c_mobile, c_email, c_birth, c_memo  FROM Company WHERE c_sort = '납품처'"));
		
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
			 m_cs_List.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				// 첫번째 인자는 InsertValue를 통해서 가지고 온 기준이 되는 정보, 두번째 인자는 열단위로 하나씩 
				m_cs_List.SetItemText(p, i ,tmp);
			}
			rs.MoveNext();	//다음행으로 이동
		 }
	}
	rs.Close();	//레코드셋 객체 소멸
	db.Close();	//데이터베이스 객체 소멸
}


int CALLBACK CSaleComSearchDlg::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl *pListCtrl = ((SORTPARAM *)lParamSort)->pList;

	int iSortColumn = ((SORTPARAM *)lParamSort)->iSortColumn;
	bool bSortDirect = ((SORTPARAM *)lParamSort)->bSortDirect;

	CString    strItem1 = pListCtrl->GetItemText(static_cast<int>(lParam1), iSortColumn);
	CString    strItem2 = pListCtrl->GetItemText(static_cast<int>(lParam2), iSortColumn);

	return bSortDirect ? _tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2) : -_tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2);


}

void CSaleComSearchDlg::UpdateArrow(void)
{
	CHeaderCtrl* pHeaderCtrl = m_cs_List.GetHeaderCtrl();
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
HCURSOR CSaleComSearchDlg::OnQueryDragIcon()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnQueryDragIcon();
}


void CSaleComSearchDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnSysCommand(nID, lParam);
}


BOOL CSaleComSearchDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rt;
    GetClientRect(&rt);  // 클라이언트 영역의 크기 계산
	pDC->FillSolidRect(&rt, RGB(247, 246, 238));  

	return TRUE; 

	return CDialogEx::OnEraseBkgnd(pDC);
}
