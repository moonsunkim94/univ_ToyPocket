// CalendarManage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "CalendarManage.h"
#include "CalendarSet.h"
#include "CalTimeGo.h"
#include "CalDeleteMemoDlg.h"


#define x1 150  //달력의 맨왼쪽위의 x좌표
#define y1 80  //달력의 맨왼쪽위의 y좌표
#define gap 100 //하루하루간의 간격
#define daycount 7 //일주일은 7일
#define weekcount 6 //한달은 많아도 5주지요
#define x2 x1+gap*daycount //달력의 맨오른쪽 아래의 x좌표
#define y2 y1+gap*weekcount //달격의 맨오른쪽 아래의 y좌표

int year,month,day_;
BOOL DrawMode = TRUE;

CFont font;

// CCalendarManage

IMPLEMENT_DYNCREATE(CCalendarManage, CFormView)

CCalendarManage::CCalendarManage()
	: CFormView(CCalendarManage::IDD)
	, m_year(_T(""))
	, m_month(_T(""))
{
	DrawMode = TRUE;
	rect[0][0] = new CRect(0,0,0,0);

}

CCalendarManage::~CCalendarManage()
{
}

void CCalendarManage::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PREYEAR, m_year);
	DDX_Text(pDX, IDC_PREMONTH, m_month);
	DDX_Control(pDX, IDC_PREV, m_prev);
	DDX_Control(pDX, IDC_NEXT, m_next);
	DDX_Control(pDX, IDC_PREYEAR, m_StaticYear);
}

BEGIN_MESSAGE_MAP(CCalendarManage, CFormView)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_PREV, &CCalendarManage::OnBnClickedPrev)
	ON_BN_CLICKED(IDC_NEXT, &CCalendarManage::OnBnClickedNext)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_DAYGO, &CCalendarManage::OnDaygo)
	ON_COMMAND(ID_DELETEMEMO, &CCalendarManage::OnDeletememo)
	ON_COMMAND(ID_TODAYGO, &CCalendarManage::OnTodaygo)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCalendarManage 진단입니다.

#ifdef _DEBUG
void CCalendarManage::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCalendarManage::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCalendarManage 메시지 처리기입니다.


void CCalendarManage::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.



	int i,day_x,day_y,last_day,k;
	int centry, draw_x, draw_y;
    char daynum[5], y[10],m[10];
	int t_day[12]={31,28,31,30,31,30,31,31,30,31,30,31}; // 달별 날수 
    
	CString day[7]={_T("일"), _T("월"),_T("화"),_T("수"),_T("목"),_T("금"),_T("토")};      // 요일
	CPaintDC dc(this); // device context for painting
	
	CFont font7;
	font7.CreateFont(20,15,0,0, FW_NORMAL, FALSE, FALSE, 0,   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("나눔바른고딕"));
	CFont *oldFont = dc.SelectObject(&font7);

	dc.SetBkMode(TRANSPARENT);

	// TODO: Add your message handler code here
    dc.Rectangle(x1,y1,x2,y2);	// 달력 사각형 그리기
	dc.Rectangle(x1,y1-20,x2,y1); //요일 표시사각형 그리기 
	for (i=1;i<=(daycount-1);i++)  //세로줄 그리기 7줄이죠. 근데 6줄만 그리면 되죠.
    {
		dc.MoveTo(x1+gap*i,y1-20);
		dc.LineTo(x1+gap*i,y2);
	}
    for (i=1;i<=(weekcount-1);i++)  //가로줄 그리기 6줄이죠. 근데 4줄만 그리면 되죠. 두줄은 이미 그려져 있으니깐요.
    {
		dc.MoveTo(x1,y1+gap*i);
		dc.LineTo(x2,y1+gap*i);
	}
	for (i=1;i<=7;i++) {           // 요일 표시하기
        day_x = x1+gap*(i-1)+gap/2-7;
		day_y = y1-18;
	    if (i==1) dc.SetTextColor(RGB(255,0,0));        // 토요일이면 파란색, 일요일이면 빨간색
		else if (i==7) dc.SetTextColor(RGB(0,0,255));
		else dc.SetTextColor(RGB(0,0,0));
		dc.TextOut(day_x,day_y,day[i-1]);
		
	}
	CTime timer;
	timer = CTime::GetCurrentTime();
	if (DrawMode) {
	     // 현재 년월일 구하기
       year = timer.GetYear();
	   month = timer.GetMonth();
       day_ = timer.GetDay();
	}
	_itoa(year,y,10);
	_itoa(month,m,10);

	UpdateData(TRUE);  // 이걸해줘야 컨트롤(에디트박스)의 값이 바뀐답니다.
	m_year = CString(y);
	m_month = CString(m);
    UpdateData(FALSE);

    centry = (year/100+1); // 세기는 년도에 100을 나눠서 1을 빼주면 되지요.
    one_whatday = (year-1)*365+(year-1)/4-(year-1)/100+(year-1)/400; // 년도일수
	if ((year%4 == 0 && year%100 != 0) || (year%400==0)) //년도가 400으로 나누어 떨어지거나 4의배수이고 100으로 나누어 떨어지지 않으면 윤년
           t_day[1]=29;
	else t_day[1]=28;
	
	for(i=1;i<month;i++)
	    one_whatday += t_day[i-1]; // 달일수
    
	one_whatday += 1; // 그달의 1일의 요일
	one_whatday = one_whatday % 7;  // 1이면 월요일 7이면 일요일
    one_whatday += 1;
	draw_x = x1+gap*(one_whatday-1)+gap/2-7; // 1일 표시하기
    draw_y = y1+gap/2;
	
	if (one_whatday==1) dc.SetTextColor(RGB(255,0,0));     // 일요일이면 빨간색, 토요일이면 파란색 
		else if (one_whatday==7) dc.SetTextColor(RGB(0,0,255));
		else dc.SetTextColor(RGB(0,0,0));

	dc.TextOut(draw_x-33,draw_y-47,_T("1"));
    
	if ((month==1) || (month==3) || (month==5) || (month==7) || (month==8) || (month==10) || (month==12)) // 몇일까지 있는지 계산 1,3,5,7,8,10,12월은 31까지 있음.
		last_day = 31;
	else if ((month==4) || (month==6) || (month==9) || (month==11))
		last_day=30;

    if (month==2)
	if ((year%4 == 0 && year%100 != 0) || (year%400==0)) //년도가 400으로 나누어 떨어지거나 4의배수이고 100으로 나누어 떨어지지 않으면 윤년
           last_day=29;  // last_day 변수는 그달의 일수를 구하는 것입니다. 예를들면 1월은 31일이죠. 
	else last_day=28; // 그렇지 않으면 평년
	                // 윤년계산해서 2월달에 대입하기
    
	k = one_whatday+1;
	if(k>7) k=1;
	for(i=2;i<=last_day;i++) { // 날짜 표시하기
	   draw_x = draw_x+gap;  // 날짜 표시 x좌표구하기
	   if (draw_x>x2) {
		   draw_x=x1+gap/2-7;
		   draw_y=draw_y+gap; // 만약에 칸을 넘어가면 다음줄로 이동
	   }
	   _itoa(i,daynum,10);
	   if (k==1) dc.SetTextColor(RGB(255,0,0));
		   else if (k==7) dc.SetTextColor(RGB(0,0,255));
		   else dc.SetTextColor(RGB(0,0,0)); 
	   
	   dc.TextOut(draw_x-33,draw_y-47,CString(daynum));
       dc.SetTextColor(RGB(0,0,0)); 
	   k++;
	   if (k>7) k=1;
	}  
     
	dc.SelectObject(oldFont);
	 font7.DeleteObject();

	UpdateData(TRUE);

	CCalendarSet cal;
	cal.Open();

		CFont font14;

	font14.CreateFont(18,13,0,0, FW_NORMAL, FALSE, FALSE, 0,   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("나눔바른고딕"));
	CFont *oldFont1 = dc.SelectObject(&font14);

	while(!cal.IsEOF()){

	int preweek = cal.m_week;
	int preday = cal.m_day;
	int preyear = cal.m_preyear;
	int premonth = cal.m_premonth;
	BOOL ch = cal.m_check;
	BOOL ch2 = cal.m_check2;
	BOOL ch3 = cal.m_check3;
	BOOL ch4 = cal.m_check4;

	dc.SetTextColor(RGB(0,0,0));
	dc.SetBkMode(TRANSPARENT);



	if((preyear == _ttoi(m_year)) && (premonth == _ttoi(m_month))){
    
	if(cal.m_memo != ""){
	if(cal.m_memo.GetLength() <= 4){
	if(ch == TRUE){
		dc.SetTextColor(RGB(29,219,22));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+25,_T("●"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+25,cal.m_memo);
	}else{
		dc.SetTextColor(RGB(140,140,140));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+25,_T("●"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+25,cal.m_memo);
	}
	}else{
		CString lmemo;
		lmemo= cal.m_memo.Left(4);
		if(ch == TRUE){
		dc.SetTextColor(RGB(29,219,22));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+25,_T("●"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+25,lmemo+_T("..."));
	}else{
		dc.SetTextColor(RGB(140,140,140));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+25,_T("●"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+25,lmemo+_T("..."));
	}
	}
	}
	if(cal.m_memo2 != ""){
	if(cal.m_memo2.GetLength() <= 4){
	if(ch2 == TRUE){
		dc.SetTextColor(RGB(29,219,22));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+45,_T("●"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+45,cal.m_memo2);
	}else{
		dc.SetTextColor(RGB(140,140,140));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+45,_T("●"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+45,cal.m_memo2);
	}
	}else{
		CString lmemo;
		lmemo= cal.m_memo2.Left(4);
		if(ch2 == TRUE){
		dc.SetTextColor(RGB(29,219,22));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+45,_T("●"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+45,lmemo+_T("..."));
	}else{
		dc.SetTextColor(RGB(140,140,140));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+45,_T("●"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+45,lmemo+_T("..."));
	}
	}
	}
	if(cal.m_memo3 != ""){
	if(cal.m_memo3.GetLength() <= 4){
	if(ch3 == TRUE){
		dc.SetTextColor(RGB(29,219,22));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+65,_T("●"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+65,cal.m_memo3);
	}else{
		dc.SetTextColor(RGB(140,140,140));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+65,_T("●"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+65,cal.m_memo3);
	}
	}else{
	CString lmemo;
	lmemo= cal.m_memo3.Left(4);
	if(ch3 == TRUE){
		dc.SetTextColor(RGB(29,219,22));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+65,_T("●"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+65,lmemo+_T("..."));
	}else{
		dc.SetTextColor(RGB(140,140,140));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+65,_T("●"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+65,lmemo+_T("..."));
	}
	}
	}
	if(cal.m_memo4 != ""){
	if(cal.m_memo4.GetLength() <= 4){
	if(ch4 == TRUE){
		dc.SetTextColor(RGB(29,219,22));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+85,_T("●"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+85,cal.m_memo4);
	}else{
		dc.SetTextColor(RGB(140,140,140));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+85,_T("●"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+85,cal.m_memo4);
	}
	}else{
		CString lmemo;
		lmemo= cal.m_memo4.Left(4);
		if(ch4 == TRUE){
		dc.SetTextColor(RGB(29,219,22));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+85,_T("●"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+85,lmemo+_T("..."));
	}else{
		dc.SetTextColor(RGB(140,140,140));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+85,_T("●"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+85,lmemo+_T("..."));
	}
	}
	}
	}
	cal.MoveNext();
	}
	 cal.MoveLast();

	 dc.SelectObject(oldFont1);
	 font14.DeleteObject();

	// 그리기 메시지에 대해서는 CFormView::OnPaint()을(를) 호출하지 마십시오.
}


void CCalendarManage::OnBnClickedPrev()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	month=month-1;  // 달은 한달 감소
	day_=1;         // 날은 1일
	DrawMode = FALSE;   // 처음 그려지는 것 아님
	if (month<1) {            // 달이 1월보다 작을때
		year = year-1;        // 그럼 년도가 일년 줄어들겠죠.
		month=12;             // 달은 12월로 넘어가고요.
		day_=1;          
	}
	Invalidate();        // 이것은 OnPaint함수를 호출한다고하네요. 그래서 다시 그려주는거지요.
}


void CCalendarManage::OnBnClickedNext()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	month=month+1;       // 달은 한달 증가
	day_=1;               
	DrawMode = FALSE;      
	if (month>12) {
		year = year+1;
		month=1;
		day_=1;
	}
	Invalidate();
}

#include "CalenderMemoDlg.h"

void CCalendarManage::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	  CClientDC dc(this);

	CFont font16;
	font16.CreateFont(18,13,0,0, FW_NORMAL, FALSE, FALSE, 0,   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("나눔바른고딕"));
	CFont *oldFont1 = dc.SelectObject(&font16);

		    int  i, x, y, j,k,r;

		for (i=0;i<weekcount;i++)
			{
				for (j=0;j<daycount;j++)
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
		
		if(memo!="" || memo2!="" ||memo3!="" || memo4!=""){

		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");	//DB오픈
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("데이터베이스 접속실패!");

			CString strQuery;	//데이터베이스에 전송할 쿼리문
			strQuery.Format(_T("INSERT INTO Calendar VALUES ('%s','%s','%s','%s', %d , %d, %d, %d, %d, %d , %d, %d, %d)"),memo,memo2,memo3,memo4,year,month,pday,week,day,check,check2,check3,check4);
			
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
		
		                
		           dc.SetTextColor(RGB(155,0,155));
				   if(memo != ""){
		            if(check == TRUE){
						if(memo.GetLength() <= 4){
								dc.SetTextColor(RGB(29,219,22));
								dc.TextOut(rect[i][j].left+5,rect[i][j].top+25,_T("●"));
								dc.SetTextColor(RGB(0,51,153));
								dc.TextOut(rect[i][j].left+20,rect[i][j].top+25,memo);
						}else{
							CString lmemo;
							lmemo= memo.Left(4); 
							dc.SetTextColor(RGB(29,219,22));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+25,_T("●"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+25,lmemo+_T("..."));
						}
					}else{
						if(memo.GetLength() <= 4){
							dc.SetTextColor(RGB(140,140,140));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+25,_T("●"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+25,memo);
						}else{
							CString lmemo;
							lmemo= memo.Left(4); 
							dc.SetTextColor(RGB(140,140,140));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+25,_T("●"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+25,lmemo+_T("..."));
						}
					 }
				   }
				   if(memo2 != ""){
		            if(check2 == TRUE){
						if(memo2.GetLength() <= 4){
								dc.SetTextColor(RGB(29,219,22));
								dc.TextOut(rect[i][j].left+5,rect[i][j].top+45,_T("●"));
								dc.SetTextColor(RGB(0,51,153));
								dc.TextOut(rect[i][j].left+20,rect[i][j].top+45,memo2);
						}else{
							CString lmemo;
							lmemo= memo2.Left(4); 
							dc.SetTextColor(RGB(29,219,22));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+45,_T("●"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+45,lmemo+_T("..."));
						}
					}else{
						if(memo2.GetLength() <= 4){
							dc.SetTextColor(RGB(140,140,140));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+45,_T("●"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+45,memo2);
						}else{
							CString lmemo;
							lmemo= memo2.Left(4); 
							dc.SetTextColor(RGB(140,140,140));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+45,_T("●"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+45,lmemo+_T("..."));
						}
					 }
				   }
				   if(memo3 != ""){
		            if(check3 == TRUE){
						if(memo3.GetLength() <= 4){
								dc.SetTextColor(RGB(29,219,22));
								dc.TextOut(rect[i][j].left+5,rect[i][j].top+65,_T("●"));
								dc.SetTextColor(RGB(0,51,153));
								dc.TextOut(rect[i][j].left+20,rect[i][j].top+65,memo3);
						}else{
							CString lmemo;
							lmemo= memo3.Left(4); 
							dc.SetTextColor(RGB(29,219,22));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+65,_T("●"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+65,lmemo+_T("..."));
						}
					}else{
						if(memo3.GetLength() <= 4){
							dc.SetTextColor(RGB(140,140,140));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+65,_T("●"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+65,memo3);
						}else{
							CString lmemo;
							lmemo= memo3.Left(4); 
							dc.SetTextColor(RGB(140,140,140));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+65,_T("●"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+65,lmemo+_T("..."));
						}
					 }
				   }
				   if(memo4 != ""){
		            if(check4 == TRUE){
						if(memo4.GetLength() <= 4){
								dc.SetTextColor(RGB(29,219,22));
								dc.TextOut(rect[i][j].left+5,rect[i][j].top+85,_T("●"));
								dc.SetTextColor(RGB(0,51,153));
								dc.TextOut(rect[i][j].left+20,rect[i][j].top+85,memo4);
						}else{
							CString lmemo;
							lmemo= memo4.Left(4); ;
							dc.SetTextColor(RGB(29,219,22));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+85,_T("●"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+85,lmemo+_T("..."));
						}
					}else{
						if(memo4.GetLength() <= 4){
							dc.SetTextColor(RGB(140,140,140));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+85,_T("●"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+85,memo4);
						}else{
							CString lmemo;
							lmemo= memo4.Left(4); 
							dc.SetTextColor(RGB(140,140,140));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+85,_T("●"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+85,lmemo+_T("..."));
						}
					 }
				   }
					}
       
						break;
						}

							
				}
					if(boolpoint == TRUE)
							break;
			}

	dc.SelectObject(oldFont1);
	 font16.DeleteObject();


	CFormView::OnLButtonDown(nFlags, point);
}





void CCalendarManage::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CPoint ptInSrceen;

    GetCursorPos(&ptInSrceen); //R버튼 눌린좌표얻음

	CMenu muTemp, *pContextMenu;
	muTemp.LoadMenuW(IDR_CALENDER);
	pContextMenu = muTemp.GetSubMenu(0);
	pContextMenu -> TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, ptInSrceen.x, ptInSrceen.y,this);
	CFormView::OnRButtonDown(nFlags, point);

	CFormView::OnRButtonDown(nFlags, point);
}


void CCalendarManage::OnDaygo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	yearpre = m_year;
 	monthpre = m_month;

	CCalTimeGo dlg;
	dlg.DoModal();	

	CString ye = dlg.m_goyear;
	CString mo = dlg.m_gomonth;

	int m;
	UpdateData(TRUE);
    m = _ttoi(mo);
	if ((m>1) && (m<12)) {
	    year = _ttoi(ye);     // 년도는 첫번째 에디트 박스의 값이죠.
		month = _ttoi(mo);   // 달은 두번째 에디트 박스의 값입니다.
	    day_ = 1;
	    DrawMode = FALSE;
        Invalidate();
	}
	UpdateData(FALSE);

}


void CCalendarManage::OnDeletememo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	yearpre = m_year;
 	monthpre = m_month;
	CCalDeleteMemoDlg dlg;
	dlg.DoModal();

	Invalidate();
}


void CCalendarManage::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
		   int  i, x, y, j,k,r;

			for (i=0;i<weekcount;i++)
			{
				y = y1 + gap*i;
				for (j=0;j<daycount;j++)
				 {
							rect[i][j].left = x1+gap*j;
							rect[i][j].top = y1+gap*i;
							rect[i][j].right = x1+gap*(j+1);
							rect[i][j].bottom = y1+gap*(i+1);
				}
			}

			font.CreateFont(20,15,0,0, FW_NORMAL, FALSE, FALSE, 0,   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("나눔바른고딕"));
			GetDlgItem(IDC_PREYEAR)->SetFont(&font);
			GetDlgItem(IDC_PREMONTH)->SetFont(&font);
			GetDlgItem(IDC_STATIC1)->SetFont(&font);
			GetDlgItem(IDC_STATIC2)->SetFont(&font);

			m_prev.LoadBitmaps(IDB_BMP_PREV,NULL,NULL,NULL);
	        m_prev.SizeToContent();
			m_next.LoadBitmaps(IDB_BMP_NEXT,NULL,NULL,NULL);
	        m_next.SizeToContent();
}


void CCalendarManage::OnTodaygo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CTime timer;
	timer = CTime::GetCurrentTime();
	     // 현재 년월일 구하기
       int yea = timer.GetYear();
	   int mont = timer.GetMonth();
	    year = yea;     // 년도는 첫번째 에디트 박스의 값이죠.
		month = mont;   // 달은 두번째 에디트 박스의 값입니다.
	    day_ = 1;
	    DrawMode = FALSE;
		Invalidate();

}


BOOL CCalendarManage::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rt;
    GetClientRect(&rt);  // 클라이언트 영역의 크기 계산
	pDC->FillSolidRect(&rt, RGB(247, 246, 238));  

	return TRUE; 


	return CFormView::OnEraseBkgnd(pDC);
}


HBRUSH CCalendarManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	UINT nID = pWnd->GetDlgCtrlID();

	if (nCtlColor == CTLCOLOR_STATIC )

    {
		if(nID==IDC_PREYEAR)
		{
			 pDC->SetBkMode(TRANSPARENT);
			 return (HBRUSH)::GetStockObject(NULL_BRUSH);
		}
		if(nID==IDC_STATIC1)
		{
			 pDC->SetBkMode(TRANSPARENT);
			 return (HBRUSH)::GetStockObject(NULL_BRUSH);

		}
		if(nID==IDC_PREMONTH)
		{
			 pDC->SetBkMode(TRANSPARENT);
			 return (HBRUSH)::GetStockObject(NULL_BRUSH);

		}
		if(nID==IDC_STATIC2)
		{
			 pDC->SetBkMode(TRANSPARENT);
			 return (HBRUSH)::GetStockObject(NULL_BRUSH);

		}
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
