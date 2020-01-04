// SaleModifyPage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "SaleModifyPage.h"
#include "afxdialogex.h"


// CSaleModifyPage 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSaleModifyPage, CPropertyPage)

CSaleModifyPage::CSaleModifyPage()
	: CPropertyPage(CSaleModifyPage::IDD)
	, m_sicode(_T(""))
	, m_siname(_T(""))
	, m_samount_modify(_T(""))
	, m_samount(_T(""))
	, m_soutdate_value(COleDateTime::GetCurrentTime())
{

}

CSaleModifyPage::~CSaleModifyPage()
{
}

void CSaleModifyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_sim_list);
	DDX_Control(pDX, IDC_EDIT4, m_siname_Edit);
	DDX_Control(pDX, IDC_EDIT8, m_sicode_Edit);
	DDX_Control(pDX, IDC_EDIT14, m_samount_Edit);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_soutDate);
	DDX_Text(pDX, IDC_EDIT8, m_sicode);
	DDX_Text(pDX, IDC_EDIT4, m_siname);
	DDX_Text(pDX, IDC_EDIT1, m_samount_modify);
	DDX_Text(pDX, IDC_EDIT14, m_samount);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_soutdate_value);
	DDX_Control(pDX, SaleModify, m_modifybtn);
	DDX_Control(pDX, IDCANCEL, m_modicancelbtn);
	DDX_Control(pDX, IDC_COMBO4, m_combo1);
	DDX_Control(pDX, IDC_COMBO3, m_combo2);
	DDX_Control(pDX, IDC_COMBO2, m_combo3);
	DDX_Control(pDX, IDC_EDIT1, m_samout_modify_Edit);
}


BEGIN_MESSAGE_MAP(CSaleModifyPage, CPropertyPage)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CSaleModifyPage::OnNMDblclkList1)
	ON_WM_PAINT()
	ON_BN_CLICKED(SaleModify, &CSaleModifyPage::OnBnClickedSalemodify)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CSaleModifyPage::OnHdnItemclickList1)
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CSaleModifyPage 메시지 처리기입니다.


BOOL CSaleModifyPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_modifybtn.LoadBitmaps(IDB_BMP_OKSET, NULL, NULL, NULL);
	m_modifybtn.SizeToContent();
	m_modicancelbtn.LoadBitmaps(IDB_BMP_CANCEL, NULL, NULL, NULL);
	m_modicancelbtn.SizeToContent();

	m_sim_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	if(m_sim_list.GetHeaderCtrl()->GetItemCount() <= 0)		//헤더에 아이템이 없다면
	{
		CRect rect;
		m_sim_list.GetClientRect(&rect);
		m_sim_list.InsertColumn(0, _T("상품코드"),			LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(1, _T("상품명"),			LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(2, _T("대분류"),			LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(3, _T("중분류"),			    LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(4, _T("소분류"),			    LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(5, _T("담당자"),			LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(6, _T("거래처이름"),			LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(7, _T("거래처코드"),			LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(8, _T("상품이미지"),			LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(9, _T("입고일"),			    LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(10, _T("입고수량"),	LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(11, _T("매입가"),	LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(12, _T("판매금액"),	LVCFMT_LEFT, 80);
	}

	GetDlgItem(IDC_COMBO4)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO3)->EnableWindow(FALSE);	
	GetDlgItem(IDC_COMBO2)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT14)->EnableWindow(FALSE);

	//헤더 컨트롤 드래그-앤-드롭 가능
	DWORD dwExStyle = m_sim_list.GetExtendedStyle();
	m_sim_list.SetExtendedStyle(dwExStyle | LVS_EX_HEADERDRAGDROP );

	m_bAscending = FALSE;
	m_sim_list.SortItems(&CSaleModifyPage::CompareItem, (DWORD_PTR)this);
	UpdateArrow();

		if(m_sim_list.GetItemCount() > 0) m_sim_list.DeleteAllItems();

		CDatabase db;			// 데이터베이스 객체 생성
		CRecordset rs (&db);	// 레코드셋 객체 생성
		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
			if (db.OpenEx (strConnection) == FALSE)
				throw _T("데이터베이스 접속실패!");

			CString strQuery;	//데이터베이스에 전송할 쿼리문
			strQuery.Format(_T("SELECT * FROM Item WHERE i_code LIKE '%%%s%%'"),g_icode);
		
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
				m_sim_list.InsertItem(p,tmp,0);
				for(short i=1; i<col; i++  )
				 {
					rs.GetFieldValue(i, tmp);  
					// 첫번째 인자는 InsertValue를 통해서 가지고 온 기준이 되는 정보, 두번째 인자는 열단위로 하나씩 
					m_sim_list.SetItemText(p, i ,tmp);

				}
				rs.MoveNext(); //다음행으로 이동
			}
		}
		rs.Close();	//레코드셋 객체 소멸
		db.Close();	//데이터베이스 객체 소멸

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

int CALLBACK CSaleModifyPage::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl *pListCtrl = ((SORTPARAM *)lParamSort)->pList;

	int iSortColumn = ((SORTPARAM *)lParamSort)->iSortColumn;
	bool bSortDirect = ((SORTPARAM *)lParamSort)->bSortDirect;

	CString    strItem1 = pListCtrl->GetItemText(static_cast<int>(lParam1), iSortColumn);
	CString    strItem2 = pListCtrl->GetItemText(static_cast<int>(lParam2), iSortColumn);

	return bSortDirect ? _tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2) : -_tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2);


}

void CSaleModifyPage::UpdateArrow(void)
{
	CHeaderCtrl* pHeaderCtrl = m_sim_list.GetHeaderCtrl();
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

void CSaleModifyPage::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	 NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	 nListIndex = pNMListView->iItem;

	 m_siname_Edit.SetWindowTextW(m_sim_list.GetItemText(nListIndex,1));
	 GetDlgItem(IDC_COMBO4)->SetWindowTextW(m_sim_list.GetItemText(nListIndex,2));
	 GetDlgItem(IDC_COMBO3)->SetWindowTextW(m_sim_list.GetItemText(nListIndex,3));
	 GetDlgItem(IDC_COMBO2)->SetWindowTextW(m_sim_list.GetItemText(nListIndex,4));

	 inputamount = m_sim_list.GetItemText(nListIndex,10);

	*pResult = 0;
}


void CSaleModifyPage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

		if(m_samount != g_soutAmount)
		{
		
		COleDateTime Date;   //사용자가 지정한 날짜를 저장할 ColeDateTimeDate 변수   
		CString Year = g_soutDate_Year;   //년
		CString Month = g_soutDate_Month; //월
		CString Day = g_soutDate_Day;    //일
		Date.SetDate(_tstoi(Year),_tstoi(Month),_tstoi(Day));
		m_soutDate.SetTime(Date);

		m_samount_Edit.SetWindowTextW(g_soutAmount);
		m_sicode_Edit.SetWindowTextW(g_icode);
		
		}
	// 그리기 메시지에 대해서는 CPropertyPage::OnPaint()을(를) 호출하지 마십시오.
}


void CSaleModifyPage::OnBnClickedSalemodify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	if(m_samount_modify!=""){
		
		CString sdate;
		sdate.Format(_T("%d-%02d-%02d"),m_soutdate_value.GetYear(),m_soutdate_value.GetMonth(),m_soutdate_value.GetDay());

		CString amount;		//재고수량계산
		amount.Format(_T("%d"), _ttoi(inputamount) + _ttoi(m_samount) - _ttoi(m_samount_modify));

		CDatabase db;			// 데이터베이스 객체 생성
		CRecordset rs (&db);	// 레코드셋 객체 생성
		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");	//DB오픈
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("데이터베이스 접속실패!");

			CString strQuery;	//데이터베이스에 전송할 쿼리문
			strQuery.Format(_T("UPDATE Sale SET s_outputDate ='%s' , s_outputAmount ='%s'  WHERE i_code = '%s'"), sdate,  m_samount_modify, m_sicode);
			db.ExecuteSQL(strQuery);	//데이터베이스에 쿼리문 전송

			strQuery.Format(_T("UPDATE Item SET i_inputAmount ='%s' WHERE i_code ='%s'"), amount,m_sicode);
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
		MessageBox(_T("성공적으로 수정되었습니다."));

		rs.Close();	//레코드셋 객체 소멸
		db.Close();	//데이터베이스 객체 소멸
	}else MessageBox(_T("입력되지 않은 값이 있습니다.\n모든 값을 입력(선택)해주세요."));
		m_combo1.SetCurSel(-1);
		m_combo2.SetCurSel(-1);
		m_combo3.SetCurSel(-1);
		m_sicode_Edit.SetWindowTextW(_T(""));
		m_siname_Edit.SetWindowTextW(_T(""));
		m_samount_Edit.SetWindowTextW(_T(""));
		m_samout_modify_Edit.SetWindowTextW(_T(""));
		CDateTimeCtrl *pCtrl = (CDateTimeCtrl *) GetDlgItem(IDC_DATETIMEPICKER1);
		CTime tm = CTime::GetCurrentTime();
		pCtrl->SetTime(&tm);
}


void CSaleModifyPage::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nColumn = phdr->iItem;
	// 현재 리스트 컨트롤에 있는 데이터 총 자료 개수만큼 저장
	 for(int i=0; i< (m_sim_list.GetItemCount()); i++)
	{
	 m_sim_list.SetItemData(i, i);
	}

	// 정렬 방식 지정(Ascend, Descend)
	 m_bAscending = !m_bAscending;
	 UpdateArrow();

	// 정렬 관련된 구조체 변수 생성 및 데이터 초기화
	SORTPARAM sortparams;
	sortparams.pList = &m_sim_list;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending;

	// 정렬 함수 호출
	m_sim_list.SortItems(&CompareItem, (LPARAM)&sortparams );
	*pResult = 0;
}


HCURSOR CSaleModifyPage::OnQueryDragIcon()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CPropertyPage::OnQueryDragIcon();
}


void CSaleModifyPage::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CPropertyPage::OnSysCommand(nID, lParam);
}
