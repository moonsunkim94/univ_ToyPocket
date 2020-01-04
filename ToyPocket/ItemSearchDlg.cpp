// ItemSearchDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ItemSearchDlg.h"
#include "afxdialogex.h"


// CItemSearchDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CItemSearchDlg, CDialogEx)

CItemSearchDlg::CItemSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CItemSearchDlg::IDD, pParent)
	, m_isearch(_T(""))
{

}

CItemSearchDlg::~CItemSearchDlg()
{
}

void CItemSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SEARCH, m_isearch_combo);
	DDX_Text(pDX, IDC_EDIT1, m_isearch);
	DDX_Control(pDX, IDC_LIST1, m_item_List);
	DDX_Control(pDX, IDC_BUTTON1, m_isearchbtn);
}


BEGIN_MESSAGE_MAP(CItemSearchDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CItemSearchDlg::OnBnClickedSearchButton)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CItemSearchDlg::OnHdnItemclickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CItemSearchDlg::OnNMDblclkList1)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, OnCustomdrawList)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CItemSearchDlg 메시지 처리기입니다.
void CItemSearchDlg::OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult)
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

void CItemSearchDlg::OnBnClickedSearchButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);

	if(m_item_List.GetItemCount() > 0) m_item_List.DeleteAllItems();

	CDatabase db;			// 데이터베이스 객체 생성
	CRecordset rs (&db);	// 레코드셋 객체 생성
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("데이터베이스 접속실패!");

		CString strQuery;
			
		int nIndex = m_isearch_combo.GetCurSel();
		if(nIndex == 0){
			strQuery.Format(_T("SELECT * FROM Item WHERE i_code LIKE '%%%s%%' OR i_name LIKE '%%%s%%' OR i_large LIKE '%%%s%%' OR i_medium LIKE '%%%s%%' OR i_small LIKE '%%%s%%' OR item_id LIKE '%%%s%%' OR i_inputDate LIKE '%%%s%%'"),
				m_isearch,m_isearch,m_isearch,m_isearch,m_isearch,m_isearch,m_isearch);
		}
		if(nIndex == 1){
			strQuery.Format(_T("SELECT * FROM Item WHERE i_code LIKE '%%%s%%'"),m_isearch);
		}
		if(nIndex == 2){
			strQuery.Format(_T("SELECT * FROM Item WHERE i_name LIKE '%%%s%%'"),m_isearch);
		}
		if(nIndex == 3){
			strQuery.Format(_T("SELECT * FROM Item WHERE c_code LIKE '%%%s%%'"),m_isearch);
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
			 m_item_List.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				m_item_List.SetItemText(p, i ,tmp);
			}
			rs.MoveNext(); 
		 }
	}
	rs.Close();
	db.Close();
}


BOOL CItemSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_isearchbtn.LoadBitmaps(IDB_BMP_SEARCH, NULL, NULL, NULL);
	m_isearchbtn.SizeToContent();
	m_item_List.SetExtendedStyle(LVS_EX_FULLROWSELECT); //행전체선택
	
	if(m_item_List.GetHeaderCtrl()->GetItemCount() <= 0)		//헤더에 아이템이 없다면
	{
		CRect rect;
		m_item_List.GetClientRect(&rect);
		m_item_List.InsertColumn(0, _T("담당자"),			LVCFMT_LEFT, 80);
		m_item_List.InsertColumn(1, _T("상품코드"),			LVCFMT_LEFT, 80);
		m_item_List.InsertColumn(2, _T("상품명"),			LVCFMT_LEFT, 80);
		m_item_List.InsertColumn(3, _T("대분류"),			LVCFMT_LEFT, 80);
		m_item_List.InsertColumn(4, _T("중분류"),			    LVCFMT_LEFT, 80);
		m_item_List.InsertColumn(5, _T("소분류"),			    LVCFMT_LEFT, 80);
		m_item_List.InsertColumn(6, _T("거래처명"),			LVCFMT_LEFT, 80);
		m_item_List.InsertColumn(7, _T("거래처코드"),			LVCFMT_LEFT, 80);
		m_item_List.InsertColumn(8, _T("입고일"),			    LVCFMT_LEFT, 80);
		m_item_List.InsertColumn(9, _T("입고수량"),	LVCFMT_LEFT, 80);
		m_item_List.InsertColumn(10, _T("매입가"),	LVCFMT_LEFT, 80);
		m_item_List.InsertColumn(11, _T("판매금액"),	LVCFMT_LEFT, 80);
	}
	
	 m_isearch_combo.AddString(_T("전체검색"));
	 m_isearch_combo.AddString(_T("상품코드"));                   //텍스트 추가
	 m_isearch_combo.AddString(_T("상품명"));
	 m_isearch_combo.AddString(_T("회사코드"));
	
	m_isearch_combo.SetCurSel(0);
	
	//헤더 컨트롤 드래그-앤-드롭 가능
	DWORD dwExStyle = m_item_List.GetExtendedStyle();
	m_item_List.SetExtendedStyle(dwExStyle | LVS_EX_HEADERDRAGDROP );
	
	m_bAscending = FALSE;
	m_item_List.SortItems(&CItemSearchDlg::CompareItem, (DWORD_PTR)this);
	UpdateArrow();
	CFont    m_fontTitle;
	LOGFONT  lf; 

	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 17;
	::lstrcpy(lf.lfFaceName, _T("나눔바른고딕"));
	m_fontTitle.CreateFontIndirect(&lf);
	GetDlgItem(IDC_COMBO_SEARCH)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_LIST1)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 

		if(m_item_List.GetItemCount() > 0) m_item_List.DeleteAllItems();

	CDatabase db;			// 데이터베이스 객체 생성
	CRecordset rs (&db);	// 레코드셋 객체 생성
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("데이터베이스 접속실패!");

		CString strQuery;
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
			 m_item_List.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				// 첫번째 인자는 InsertValue를 통해서 가지고 온 기준이 되는 정보, 두번째 인자는 열단위로 하나씩 
				m_item_List.SetItemText(p, i ,tmp);
			}
			rs.MoveNext();	//다음행으로 이동
		 }
	}
	rs.Close();	//레코드셋 객체 소멸
	db.Close();	//데이터베이스 객체 소멸
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CItemSearchDlg::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nColumn = phdr->iItem;
	// 현재 리스트 컨트롤에 있는 데이터 총 자료 개수만큼 저장
	 for(int i=0; i< (m_item_List.GetItemCount()); i++)
	{
	 m_item_List.SetItemData(i, i);
	}

	// 정렬 방식 지정(Ascend, Descend)
	 m_bAscending = !m_bAscending;

	 UpdateArrow();

	// 정렬 관련된 구조체 변수 생성 및 데이터 초기화
	SORTPARAM sortparams;
	sortparams.pList = &m_item_List;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending;

	// 정렬 함수 호출
	m_item_List.SortItems(&CompareItem, (LPARAM)&sortparams );
	*pResult = 0;
}


void CItemSearchDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    nListIndex = pNMListView->iItem;
	UpdateData();
	m_iname = m_item_List.GetItemText(nListIndex,2);
	m_icode = m_item_List.GetItemText(nListIndex,1);
	m_cname = m_item_List.GetItemText(nListIndex,6);
	m_ccode = m_item_List.GetItemText(nListIndex,7);
	m_combo1 = m_item_List.GetItemText(nListIndex,3);
	m_combo2 = m_item_List.GetItemText(nListIndex,4);
	m_combo3 = m_item_List.GetItemText(nListIndex,5);
	m_inprice = m_item_List.GetItemText(nListIndex,10);
	m_outprice = m_item_List.GetItemText(nListIndex,11);
	m_inamount = m_item_List.GetItemText(nListIndex,9);
	m_inDate = m_item_List.GetItemText(nListIndex,8);
	*pResult = 0;
	CDialogEx::OnOK();
}


void CItemSearchDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

}

int CALLBACK CItemSearchDlg::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl *pListCtrl = ((SORTPARAM *)lParamSort)->pList;

	int iSortColumn = ((SORTPARAM *)lParamSort)->iSortColumn;
	bool bSortDirect = ((SORTPARAM *)lParamSort)->bSortDirect;

	CString    strItem1 = pListCtrl->GetItemText(static_cast<int>(lParam1), iSortColumn);
	CString    strItem2 = pListCtrl->GetItemText(static_cast<int>(lParam2), iSortColumn);

	return bSortDirect ? _tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2) : -_tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2);


}

void CItemSearchDlg::UpdateArrow(void)
{
	CHeaderCtrl* pHeaderCtrl = m_item_List.GetHeaderCtrl();
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

HCURSOR CItemSearchDlg::OnQueryDragIcon()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnQueryDragIcon();
}


void CItemSearchDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnSysCommand(nID, lParam);
}


BOOL CItemSearchDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rt;
    GetClientRect(&rt);  // 클라이언트 영역의 크기 계산
	pDC->FillSolidRect(&rt, RGB(247, 246, 238));  

	return TRUE; 

	return CDialogEx::OnEraseBkgnd(pDC);
}
