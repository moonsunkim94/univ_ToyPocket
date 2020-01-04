// CalDeleteMemoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "CalDeleteMemoDlg.h"
#include "afxdialogex.h"


// CCalDeleteMemoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCalDeleteMemoDlg, CDialogEx)

CCalDeleteMemoDlg::CCalDeleteMemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCalDeleteMemoDlg::IDD, pParent)
{

}

CCalDeleteMemoDlg::~CCalDeleteMemoDlg()
{
}

void CCalDeleteMemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_memolist);
}


BEGIN_MESSAGE_MAP(CCalDeleteMemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CCalDeleteMemoDlg::OnNMDblclkList2)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CCalDeleteMemoDlg 메시지 처리기입니다.


BOOL CCalDeleteMemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_memolist.SetExtendedStyle( LVS_EX_FULLROWSELECT ); //행전체선택

	if(m_memolist.GetHeaderCtrl()->GetItemCount() <= 0)		//헤더에 아이템이 없다면
	{
		CRect rect;
		m_memolist.GetClientRect(&rect);
		m_memolist.InsertColumn(0, _T("일"),			LVCFMT_LEFT, 50);
		m_memolist.InsertColumn(2, _T("일정1"),			LVCFMT_LEFT, 100);
		m_memolist.InsertColumn(4, _T("일정2"),			LVCFMT_LEFT, 100);
		m_memolist.InsertColumn(6, _T("일정3"),			LVCFMT_LEFT, 100);
		m_memolist.InsertColumn(8, _T("일정4"),			LVCFMT_LEFT, 100);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CCalDeleteMemoDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	if(m_memolist.GetItemCount() > 0) m_memolist.DeleteAllItems();

	CDatabase db;			// 데이터베이스 객체 생성
	CRecordset rs (&db);	// 레코드셋 객체 생성

	CString str = _T("/");

	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("데이터베이스 접속실패!");

		CString strQuery;
		strQuery.Format(_T("SELECT preday, memo, memo2, memo3, memo4 FROM Calendar WHERE preyear = %d AND premonth = %d ORDER BY preday DESC"),_ttoi(yearpre),_ttoi(monthpre));
		
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
			 m_memolist.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				// 첫번째 인자는 InsertValue를 통해서 가지고 온 기준이 되는 정보, 두번째 인자는 열단위로 하나씩 
				m_memolist.SetItemText(p, i ,tmp);
			}
			rs.MoveNext();	//다음행으로 이동
		 }
	}
	rs.Close();	//레코드셋 객체 소멸
	db.Close();	//데이터베이스 객체 소멸

	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
}


void CCalDeleteMemoDlg::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    nListIndex = pNMListView->iItem;

	daynumber = m_memolist.GetItemText(nListIndex,0);

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
			strQuery.Format(_T("DELETE * FROM Calendar WHERE preday = %d"),_ttoi(daynumber));
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
	Invalidate();

	*pResult = 0;
}


BOOL CCalDeleteMemoDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rt;
    GetClientRect(&rt);  // 클라이언트 영역의 크기 계산
	pDC->FillSolidRect(&rt, RGB(247, 246, 238));  

	return TRUE; 

	return CDialogEx::OnEraseBkgnd(pDC);
}
