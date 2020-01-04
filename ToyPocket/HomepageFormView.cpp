// HomepageFormView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "HomepageFormView.h"
#include "CalendarSet.h"
#include "CalenderMemoDlg.h"

#define xx1 50  //달력의 맨왼쪽위의 x좌표
#define yy1 380  //달력의 맨왼쪽위의 y좌표
#define gap1 50 //하루하루간의 간격
#define daycount1 7 //일주일은 7일
#define weekcount1 6 //한달은 많아도 5주지요
#define x2 xx1+gap1*daycount1 //달력의 맨오른쪽 아래의 x좌표
#define y2 yy1+gap1*weekcount1 //달격의 맨오른쪽 아래의 y좌표

int year1,month1,day_1;
BOOL DrawMode1 = TRUE;

// CHomepageFormView

IMPLEMENT_DYNCREATE(CHomepageFormView, CFormView)

CHomepageFormView::CHomepageFormView()
	: CFormView(CHomepageFormView::IDD)
	, m_year(_T(""))
	, m_month(_T(""))
{

}

CHomepageFormView::~CHomepageFormView()
{
}

void CHomepageFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_YEAR, m_year);
	DDX_Text(pDX, IDC_MONTH, m_month);
	DDX_Control(pDX, IDC_LAMONTH, m_lamonth);
	DDX_Control(pDX, IDC_NEMONTH, m_nemonth);
	DDX_Control(pDX, IDC_LIST1, m_noticeList);
	DDX_Control(pDX, IDC_HOMELOGO, staticsize);
	DDX_Control(pDX, IDC_BUTTON14, m_combtn);
	DDX_Control(pDX, IDC_BUTTON16, m_itembtn);
	DDX_Control(pDX, IDC_BUTTON13, m_salebtn);
	DDX_Control(pDX, IDC_BUTTON15, m_exchangebtn);
	DDX_Control(pDX, IDC_BUTTON17, m_returnbtn);
	DDX_Control(pDX, IDC_BUTTON18, m_setbtn);
}

BEGIN_MESSAGE_MAP(CHomepageFormView, CFormView)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_LAMONTH, &CHomepageFormView::OnBnClickedLamonth)
	ON_BN_CLICKED(IDC_NEMONTH, &CHomepageFormView::OnBnClickedNemonth)
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CHomepageFormView::OnHdnItemclickList1)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON14, &CHomepageFormView::OnBnClickedCompany)
	ON_BN_CLICKED(IDC_BUTTON16, &CHomepageFormView::OnBnClickedItem)
	ON_BN_CLICKED(IDC_BUTTON13, &CHomepageFormView::OnBnClickedSale)
	ON_BN_CLICKED(IDC_BUTTON15, &CHomepageFormView::OnBnClickedExchange)
	ON_BN_CLICKED(IDC_BUTTON17, &CHomepageFormView::OnBnClickedReturn)
	ON_BN_CLICKED(IDC_BUTTON18, &CHomepageFormView::OnBnClickedSet)
END_MESSAGE_MAP()


// CHomepageFormView 진단입니다.

#ifdef _DEBUG
void CHomepageFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CHomepageFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CHomepageFormView 메시지 처리기입니다.


void CHomepageFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	m_combtn.LoadBitmaps(IDB_BMP_HCOM, NULL,NULL,NULL);
	m_combtn.SizeToContent();
	m_itembtn.LoadBitmaps(IDB_BMP_HITEM, NULL,NULL,NULL);
	m_itembtn.SizeToContent();
	m_salebtn.LoadBitmaps(IDB_BMP_HSALE, NULL,NULL,NULL);
	m_salebtn.SizeToContent();
	m_exchangebtn.LoadBitmaps(IDB_BMP_HEX, NULL,NULL,NULL);
	m_exchangebtn.SizeToContent();
	m_returnbtn.LoadBitmaps(IDB_BMP_HRE, NULL,NULL,NULL);
	m_returnbtn.SizeToContent();
	m_setbtn.LoadBitmaps(IDB_BMP_HSET, NULL,NULL,NULL);
	m_setbtn.SizeToContent();
	
	int  i, x, y, j,k,r;

	for (i=0;i<weekcount1;i++)
	{
		y = yy1 + gap1*i;
		for (j=0;j<daycount1;j++)
		{
			rect[i][j].left = xx1+gap1*j;
			rect[i][j].top = yy1+gap1*i;
			rect[i][j].right = xx1+gap1*(j+1);
			rect[i][j].bottom = yy1+gap1*(i+1);
		}
	}

	m_lamonth.LoadBitmaps(IDB_BMP_PREV,NULL,NULL,NULL);
	m_lamonth.SizeToContent();
	m_nemonth.LoadBitmaps(IDB_BMP_NEXT,NULL,NULL,NULL);
	m_nemonth.SizeToContent();


	//////////////
	//↓공지사항부분
	m_noticeList.SetExtendedStyle(LVS_EX_FULLROWSELECT); //행전체선택
	
	if(m_noticeList.GetHeaderCtrl()->GetItemCount() <= 0)		//헤더에 아이템이 없다면
	{
		CRect rect;
		m_noticeList.GetClientRect(&rect);
		m_noticeList.InsertColumn(0, _T("날짜"),			LVCFMT_LEFT, 100);
		m_noticeList.InsertColumn(1, _T("공지 내용"),			LVCFMT_LEFT, 385);
	}
	m_bAscending = FALSE;
	m_noticeList.SortItems(&CHomepageFormView::CompareItem, (DWORD_PTR)this);
	UpdateArrow();

	CFont    m_fontTitle;
	LOGFONT  lf; 

	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 15;
	::lstrcpy(lf.lfFaceName, _T("나눔바른고딕"));
	m_fontTitle.CreateFontIndirect(&lf);
	GetDlgItem(IDC_STATIC1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_LIST1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_YEAR)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC3)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_MONTH)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC4)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 

			if(m_noticeList.GetItemCount() > 0) m_noticeList.DeleteAllItems();

	CDatabase db;			// 데이터베이스 객체 생성
	CRecordset rs (&db);	// 레코드셋 객체 생성
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("데이터베이스 접속실패!");

		CString strQuery;
		strQuery.Format(_T("SELECT n_date, n_notice  FROM Notice"));
		
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
			 m_noticeList.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				// 첫번째 인자는 InsertValue를 통해서 가지고 온 기준이 되는 정보, 두번째 인자는 열단위로 하나씩 
				m_noticeList.SetItemText(p, i ,tmp);
			}
			rs.MoveNext();	//다음행으로 이동
		 }
	}
	rs.Close();	//레코드셋 객체 소멸
	db.Close();	//데이터베이스 객체 소멸


}
#include "MainFrm.h"

void CHomepageFormView::OnPaint()
{
 // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	HBITMAP hbit;
	 hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_HOMELOGO));

	staticsize.SetBitmap(hbit) ;


	int i,day_x,day_y,last_day,k;
	int centry, draw_x, draw_y;
    char daynum[5], y[10],m[10];
	int t_day[12]={31,28,31,30,31,30,31,31,30,31,30,31}; // 달별 날수 
    
	CString day[7]={_T("일"), _T("월"),_T("화"),_T("수"),_T("목"),_T("금"),_T("토")};      // 요일
	CPaintDC dc(this); // device context for painting
	
	CFont font9;
	font9.CreateFont(15,10,0,0, FW_NORMAL, FALSE, FALSE, 0,   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("나눔바른고딕"));
	CFont *oldFont = dc.SelectObject(&font9);

	dc.SetBkMode(TRANSPARENT);

	// TODO: Add your message handler code here
    dc.Rectangle(xx1,yy1,x2,y2);	// 달력 사각형 그리기
	dc.Rectangle(xx1,yy1-20,x2,yy1); //요일 표시사각형 그리기 
	for (i=1;i<=(daycount1-1);i++)  //세로줄 그리기 7줄이죠. 근데 6줄만 그리면 되죠.
    {
		dc.MoveTo(xx1+gap1*i,yy1-20);
		dc.LineTo(xx1+gap1*i,y2);
	}
    for (i=1;i<=(weekcount1-1);i++)  //가로줄 그리기 6줄이죠. 근데 4줄만 그리면 되죠. 두줄은 이미 그려져 있으니깐요.
    {
		dc.MoveTo(xx1,yy1+gap1*i);
		dc.LineTo(x2,yy1+gap1*i);
	}
	for (i=1;i<=7;i++) {           // 요일 표시하기
        day_x = xx1+gap1*(i-1)+gap1/2-7;
		day_y = yy1-18;
	    if (i==1) dc.SetTextColor(RGB(255,0,0));        // 토요일이면 파란색, 일요일이면 빨간색
		else if (i==7) dc.SetTextColor(RGB(0,0,255));
		else dc.SetTextColor(RGB(0,0,0));
		dc.TextOut(day_x,day_y,day[i-1]);
		
	}
	CTime timer;
	timer = CTime::GetCurrentTime();
	if (DrawMode1) {
	     // 현재 년월일 구하기
       year1 = timer.GetYear();
	   month1 = timer.GetMonth();
       day_1 = timer.GetDay();
	}
	_itoa(year1,y,10);
	_itoa(month1,m,10);

	UpdateData(TRUE);  // 이걸해줘야 컨트롤(에디트박스)의 값이 바뀐답니다.
	m_year = CString(y);
	m_month = CString(m);
    UpdateData(FALSE);

    centry = (year1/100+1); // 세기는 년도에 100을 나눠서 1을 빼주면 되지요.
    one_whatday = (year1-1)*365+(year1-1)/4-(year1-1)/100+(year1-1)/400; // 년도일수
	if ((year1%4 == 0 && year1%100 != 0) || (year1%400==0)) //년도가 400으로 나누어 떨어지거나 4의배수이고 100으로 나누어 떨어지지 않으면 윤년
           t_day[1]=29;
	else t_day[1]=28;
	
	for(i=1;i<month1;i++)
	    one_whatday += t_day[i-1]; // 달일수
    
	one_whatday += 1; // 그달의 1일의 요일
	one_whatday = one_whatday % 7;  // 1이면 월요일 7이면 일요일
    one_whatday += 1;
	draw_x = xx1+gap1*(one_whatday-1)+gap1/2-7; // 1일 표시하기
    draw_y = yy1+gap1/2;
	
	if (one_whatday==1) dc.SetTextColor(RGB(255,0,0));     // 일요일이면 빨간색, 토요일이면 파란색 
		else if (one_whatday==7) dc.SetTextColor(RGB(0,0,255));
		else dc.SetTextColor(RGB(0,0,0));

	UpdateData(TRUE);

	CCalendarSet cal;
	cal.Open();

	CBrush curBrush1(RGB(255,193,158)); 
	CBrush * oldBrush; 
	dc.SelectObject(&curBrush1); 

	while(!cal.IsEOF()){

	int preweek = cal.m_week;
	int preday = cal.m_day;
	int preyear = cal.m_preyear;
	int premonth = cal.m_premonth;
	BOOL ch = cal.m_check;
	BOOL ch2 = cal.m_check2;
	BOOL ch3 = cal.m_check3;
	BOOL ch4 = cal.m_check4;

	if((preyear == _ttoi(m_year)) && (premonth == _ttoi(m_month))){    
		dc.Rectangle(rect[preweek][preday]);
	}
	cal.MoveNext();
	}
	 cal.MoveLast();

	 dc.SelectObject(oldBrush);

     curBrush1.DeleteObject();


	dc.TextOut(draw_x-13,draw_y-23,_T("1"));
    
	if ((month1==1) || (month1==3) || (month1==5) || (month1==7) || (month1==8) || (month1==10) || (month1==12)) // 몇일까지 있는지 계산 1,3,5,7,8,10,12월은 31까지 있음.
		last_day = 31;
	else if ((month1==4) || (month1==6) || (month1==9) || (month1==11))
		last_day=30;

    if (month1==2)
	if ((year1%4 == 0 && year1%100 != 0) || (year1%400==0)) //년도가 400으로 나누어 떨어지거나 4의배수이고 100으로 나누어 떨어지지 않으면 윤년
           last_day=29;  // last_day 변수는 그달의 일수를 구하는 것입니다. 예를들면 1월은 31일이죠. 
	else last_day=28; // 그렇지 않으면 평년
	                // 윤년계산해서 2월달에 대입하기




	k = one_whatday+1;
	if(k>7) k=1;
	for(i=2;i<=last_day;i++) { // 날짜 표시하기
	   draw_x = draw_x+gap1;  // 날짜 표시 x좌표구하기
	   if (draw_x>x2) {
		   draw_x=xx1+gap1/2-7;
		   draw_y=draw_y+gap1; // 만약에 칸을 넘어가면 다음줄로 이동
	   }
	   _itoa(i,daynum,10);
	   if (k==1) dc.SetTextColor(RGB(255,0,0));
		   else if (k==7) dc.SetTextColor(RGB(0,0,255));
		   else dc.SetTextColor(RGB(0,0,0)); 
	   
	   dc.TextOut(draw_x-13,draw_y-23,CString(daynum));
       dc.SetTextColor(RGB(0,0,0)); 
	   k++;
	   if (k>7) k=1;
	}  

	dc.SelectObject(oldFont);
	font9.DeleteObject();

    CPen pen1(PS_SOLID, 1, RGB(212,212,212)); 
	CPen * oldpen; 
	dc.SelectObject(&pen1);

	dc.MoveTo(440,30);
	dc.LineTo(440,690);

	dc.MoveTo(475,330);
	dc.LineTo(963,330);

    dc.SelectObject(oldpen);

    pen1.DeleteObject();


	// 그리기 메시지에 대해서는 CFormView::OnPaint()을(를) 호출하지 마십시오.
}


void CHomepageFormView::OnBnClickedLamonth()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		month1=month1-1;  // 달은 한달 감소
	day_1=1;         // 날은 1일
	DrawMode1 = FALSE;   // 처음 그려지는 것 아님
	if (month1<1) {            // 달이 1월보다 작을때
		year1 = year1-1;        // 그럼 년도가 일년 줄어들겠죠.
		month1=12;             // 달은 12월로 넘어가고요.
		day_1=1;          
	}
	Invalidate(); 
}


void CHomepageFormView::OnBnClickedNemonth()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	month1=month1+1;       // 달은 한달 증가
	day_1=1;               
	DrawMode1 = FALSE;      
	if (month1>12) {
		year1 = year1+1;
		month1=1;
		day_1=1;
	}
	Invalidate();
}


void CHomepageFormView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

		CDC dc;

			CFont font10;
	font10.CreateFont(20,15,0,0, FW_NORMAL, FALSE, FALSE, 0,   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("나눔바른고딕"));
	CFont *oldFont = dc.SelectObject(&font10);

	CBrush curBrush1(RGB(255,193,158)); 
	CBrush * oldBrush; 
	dc.SelectObject(&curBrush1); 
	int  i, x, y, j,k,r;

			for (i=0;i<weekcount1;i++)
			{
				for (j=0;j<daycount1;j++)
				 {
						boolpoint = rect[i][j].PtInRect(point);
						if(boolpoint == TRUE){
							week = i;
 							day = j;
							daypre = (7- one_whatday+1) + (i-1)*7 + (j+1);
							yearpre = m_year;
 	                        monthpre = m_month;
							CCalenderMemoDlg dlg;
							 dlg.DoModal();

							dc.Rectangle(rect[i][j]);
							 int pday;
							CString memo,memo2,memo3,memo4;
							BOOL check,check2,check3,check4;
							pday = _ttoi(dlg.m_day);
							memo = dlg.m_memo;
							memo2 = dlg.m_memo2;
							memo3 = dlg.m_memo3;
							memo4 = dlg.m_memo4;
							check = dlg.m_check1;
							check2 = dlg.m_check2;
							check3 = dlg.m_check3;
							check4 = dlg.m_check4;


							int year = _ttoi(m_year);
							int month = _ttoi(m_month);


            CDatabase db;			// 데이터베이스 객체 생성
			CRecordset rs (&db);	// 레코드셋 객체 생성
		
		if(memo!=""||memo2!=""||memo3!=""||memo4!=""){

		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");	//DB오픈
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("데이터베이스 접속실패!");

			CString strQuery;	//데이터베이스에 전송할 쿼리문
			strQuery.Format(_T("INSERT INTO calendar VALUES ('%s','%s','%s','%s', %d , %d, %d, %d, %d, %d , %d, %d, %d)"),memo,memo2,memo3,memo4,year,month,pday,week,day,check,check2,check3,check4);
			
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
		MessageBox(_T("성공적으로 추가되었습니다."));
		


		rs.Close();	//레코드셋 객체 소멸
		db.Close();	//데이터베이스 객체 소멸
		                

							      }
							 break;

						}

						}
				     if(boolpoint == TRUE)
							break;	
				}
	  dc.SelectObject(oldBrush);
     curBrush1.DeleteObject();

	 dc.SelectObject(oldFont);
	font10.DeleteObject();

	 Invalidate();

	CFormView::OnLButtonDown(nFlags, point);
}


void CHomepageFormView::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nColumn = phdr->iItem;
	// 현재 리스트 컨트롤에 있는 데이터 총 자료 개수만큼 저장
	 for(int i=0; i< (m_noticeList.GetItemCount()); i++)
	{
	 m_noticeList.SetItemData(i, i);
	}

	// 정렬 방식 지정(Ascend, Descend)
	 m_bAscending = !m_bAscending;


	 UpdateArrow();


	// 정렬 관련된 구조체 변수 생성 및 데이터 초기화
	SORTPARAM sortparams;
	sortparams.pList = &m_noticeList;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending;

	// 정렬 함수 호출
	m_noticeList.SortItems(&CompareItem, (LPARAM)&sortparams );
	*pResult = 0;
}


int CALLBACK CHomepageFormView::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl *pListCtrl = ((SORTPARAM *)lParamSort)->pList;

	int iSortColumn = ((SORTPARAM *)lParamSort)->iSortColumn;
	bool bSortDirect = ((SORTPARAM *)lParamSort)->bSortDirect;

	CString    strItem1 = pListCtrl->GetItemText(static_cast<int>(lParam1), iSortColumn);
	CString    strItem2 = pListCtrl->GetItemText(static_cast<int>(lParam2), iSortColumn);

	return bSortDirect ? _tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2) : -_tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2);


}

void CHomepageFormView::UpdateArrow(void)
{
	CHeaderCtrl* pHeaderCtrl = m_noticeList.GetHeaderCtrl();
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


BOOL CHomepageFormView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rt;
    GetClientRect(&rt);  // 클라이언트 영역의 크기 계산
	//pDC->FillSolidRect(&rt, RGB(250, 244, 192));  
	pDC->FillSolidRect(&rt, RGB(255, 255, 255));  
	return TRUE; 
	//return CFormView::OnEraseBkgnd(pDC);
}


HBRUSH CHomepageFormView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	UINT nID = pWnd->GetDlgCtrlID();			//컨트롤 핸들과 비교하기 위한 변수
 
    if(nID==IDC_STATIC1)							// 스태틱 컨트롤일때
    {    
        pDC->SetBkMode(TRANSPARENT);                              
        return (HBRUSH)::GetStockObject(NULL_BRUSH);                      
    }
	 if(nID==IDC_STATIC3)							// 스태틱 컨트롤일때
    {    
        pDC->SetBkMode(TRANSPARENT);                              
        return (HBRUSH)::GetStockObject(NULL_BRUSH);                      
    }
	  if(nID==IDC_STATIC4)							// 스태틱 컨트롤일때
    {    
        pDC->SetBkMode(TRANSPARENT);                              
        return (HBRUSH)::GetStockObject(NULL_BRUSH);                      
    }
	   if(nID==IDC_YEAR)							// 스태틱 컨트롤일때
    {    
        pDC->SetBkMode(TRANSPARENT);                              
        return (HBRUSH)::GetStockObject(NULL_BRUSH);                      
    }
	    if(nID==IDC_MONTH)							// 스태틱 컨트롤일때
    {    
        pDC->SetBkMode(TRANSPARENT);                              
        return (HBRUSH)::GetStockObject(NULL_BRUSH);                      
    }
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CHomepageFormView::OnBnClickedCompany()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SwitchView(VIEWID_COMPANY_SHEET);
}


void CHomepageFormView::OnBnClickedItem()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SwitchView(VIEWID_ITEM_SHEET);
}


void CHomepageFormView::OnBnClickedSale()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_salecheck = TRUE;
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SwitchView(VIEWID_SALE_SHEET);
}


void CHomepageFormView::OnBnClickedExchange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_excheck = TRUE;
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SwitchView(VIEWID_EXCHANGE_SHEET);
}


void CHomepageFormView::OnBnClickedReturn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_recheck = TRUE;
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SwitchView(VIEWID_RETURN_SHEET);
}

#include "PasswordChangeDlg.h"
void CHomepageFormView::OnBnClickedSet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CPasswordChangeDlg dlg;
	dlg.DoModal();
}

/*
Z

void CHomepageFormView::OnBnClickedSaleBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_salecheck = TRUE;
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SwitchView(VIEWID_SALE_SHEET);
}


void CHomepageFormView::OnBnClickedExchange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_excheck = TRUE;
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SwitchView(VIEWID_EXCHANGE_SHEET);
}


void CHomepageFormView::OnBnClickedReturn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_recheck = TRUE;
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SwitchView(VIEWID_RETURN_SHEET);

}

void CHomepageFormView::OnBnClickedSet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SwitchView(VIEWID_MANAGE_SHEET);
}

*/