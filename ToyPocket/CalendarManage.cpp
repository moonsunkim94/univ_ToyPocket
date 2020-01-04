// CalendarManage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "CalendarManage.h"
#include "CalendarSet.h"
#include "CalTimeGo.h"
#include "CalDeleteMemoDlg.h"


#define x1 150  //�޷��� �ǿ������� x��ǥ
#define y1 80  //�޷��� �ǿ������� y��ǥ
#define gap 100 //�Ϸ��Ϸ簣�� ����
#define daycount 7 //�������� 7��
#define weekcount 6 //�Ѵ��� ���Ƶ� 5������
#define x2 x1+gap*daycount //�޷��� �ǿ����� �Ʒ��� x��ǥ
#define y2 y1+gap*weekcount //�ް��� �ǿ����� �Ʒ��� y��ǥ

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


// CCalendarManage �����Դϴ�.

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


// CCalendarManage �޽��� ó�����Դϴ�.


void CCalendarManage::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.



	int i,day_x,day_y,last_day,k;
	int centry, draw_x, draw_y;
    char daynum[5], y[10],m[10];
	int t_day[12]={31,28,31,30,31,30,31,31,30,31,30,31}; // �޺� ���� 
    
	CString day[7]={_T("��"), _T("��"),_T("ȭ"),_T("��"),_T("��"),_T("��"),_T("��")};      // ����
	CPaintDC dc(this); // device context for painting
	
	CFont font7;
	font7.CreateFont(20,15,0,0, FW_NORMAL, FALSE, FALSE, 0,   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("�����ٸ����"));
	CFont *oldFont = dc.SelectObject(&font7);

	dc.SetBkMode(TRANSPARENT);

	// TODO: Add your message handler code here
    dc.Rectangle(x1,y1,x2,y2);	// �޷� �簢�� �׸���
	dc.Rectangle(x1,y1-20,x2,y1); //���� ǥ�û簢�� �׸��� 
	for (i=1;i<=(daycount-1);i++)  //������ �׸��� 7������. �ٵ� 6�ٸ� �׸��� ����.
    {
		dc.MoveTo(x1+gap*i,y1-20);
		dc.LineTo(x1+gap*i,y2);
	}
    for (i=1;i<=(weekcount-1);i++)  //������ �׸��� 6������. �ٵ� 4�ٸ� �׸��� ����. ������ �̹� �׷��� �����ϱ��.
    {
		dc.MoveTo(x1,y1+gap*i);
		dc.LineTo(x2,y1+gap*i);
	}
	for (i=1;i<=7;i++) {           // ���� ǥ���ϱ�
        day_x = x1+gap*(i-1)+gap/2-7;
		day_y = y1-18;
	    if (i==1) dc.SetTextColor(RGB(255,0,0));        // ������̸� �Ķ���, �Ͽ����̸� ������
		else if (i==7) dc.SetTextColor(RGB(0,0,255));
		else dc.SetTextColor(RGB(0,0,0));
		dc.TextOut(day_x,day_y,day[i-1]);
		
	}
	CTime timer;
	timer = CTime::GetCurrentTime();
	if (DrawMode) {
	     // ���� ����� ���ϱ�
       year = timer.GetYear();
	   month = timer.GetMonth();
       day_ = timer.GetDay();
	}
	_itoa(year,y,10);
	_itoa(month,m,10);

	UpdateData(TRUE);  // �̰������ ��Ʈ��(����Ʈ�ڽ�)�� ���� �ٲ��ϴ�.
	m_year = CString(y);
	m_month = CString(m);
    UpdateData(FALSE);

    centry = (year/100+1); // ����� �⵵�� 100�� ������ 1�� ���ָ� ������.
    one_whatday = (year-1)*365+(year-1)/4-(year-1)/100+(year-1)/400; // �⵵�ϼ�
	if ((year%4 == 0 && year%100 != 0) || (year%400==0)) //�⵵�� 400���� ������ �������ų� 4�ǹ���̰� 100���� ������ �������� ������ ����
           t_day[1]=29;
	else t_day[1]=28;
	
	for(i=1;i<month;i++)
	    one_whatday += t_day[i-1]; // ���ϼ�
    
	one_whatday += 1; // �״��� 1���� ����
	one_whatday = one_whatday % 7;  // 1�̸� ������ 7�̸� �Ͽ���
    one_whatday += 1;
	draw_x = x1+gap*(one_whatday-1)+gap/2-7; // 1�� ǥ���ϱ�
    draw_y = y1+gap/2;
	
	if (one_whatday==1) dc.SetTextColor(RGB(255,0,0));     // �Ͽ����̸� ������, ������̸� �Ķ��� 
		else if (one_whatday==7) dc.SetTextColor(RGB(0,0,255));
		else dc.SetTextColor(RGB(0,0,0));

	dc.TextOut(draw_x-33,draw_y-47,_T("1"));
    
	if ((month==1) || (month==3) || (month==5) || (month==7) || (month==8) || (month==10) || (month==12)) // ���ϱ��� �ִ��� ��� 1,3,5,7,8,10,12���� 31���� ����.
		last_day = 31;
	else if ((month==4) || (month==6) || (month==9) || (month==11))
		last_day=30;

    if (month==2)
	if ((year%4 == 0 && year%100 != 0) || (year%400==0)) //�⵵�� 400���� ������ �������ų� 4�ǹ���̰� 100���� ������ �������� ������ ����
           last_day=29;  // last_day ������ �״��� �ϼ��� ���ϴ� ���Դϴ�. ������� 1���� 31������. 
	else last_day=28; // �׷��� ������ ���
	                // �������ؼ� 2���޿� �����ϱ�
    
	k = one_whatday+1;
	if(k>7) k=1;
	for(i=2;i<=last_day;i++) { // ��¥ ǥ���ϱ�
	   draw_x = draw_x+gap;  // ��¥ ǥ�� x��ǥ���ϱ�
	   if (draw_x>x2) {
		   draw_x=x1+gap/2-7;
		   draw_y=draw_y+gap; // ���࿡ ĭ�� �Ѿ�� �����ٷ� �̵�
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
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("�����ٸ����"));
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
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+25,_T("��"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+25,cal.m_memo);
	}else{
		dc.SetTextColor(RGB(140,140,140));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+25,_T("��"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+25,cal.m_memo);
	}
	}else{
		CString lmemo;
		lmemo= cal.m_memo.Left(4);
		if(ch == TRUE){
		dc.SetTextColor(RGB(29,219,22));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+25,_T("��"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+25,lmemo+_T("..."));
	}else{
		dc.SetTextColor(RGB(140,140,140));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+25,_T("��"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+25,lmemo+_T("..."));
	}
	}
	}
	if(cal.m_memo2 != ""){
	if(cal.m_memo2.GetLength() <= 4){
	if(ch2 == TRUE){
		dc.SetTextColor(RGB(29,219,22));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+45,_T("��"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+45,cal.m_memo2);
	}else{
		dc.SetTextColor(RGB(140,140,140));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+45,_T("��"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+45,cal.m_memo2);
	}
	}else{
		CString lmemo;
		lmemo= cal.m_memo2.Left(4);
		if(ch2 == TRUE){
		dc.SetTextColor(RGB(29,219,22));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+45,_T("��"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+45,lmemo+_T("..."));
	}else{
		dc.SetTextColor(RGB(140,140,140));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+45,_T("��"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+45,lmemo+_T("..."));
	}
	}
	}
	if(cal.m_memo3 != ""){
	if(cal.m_memo3.GetLength() <= 4){
	if(ch3 == TRUE){
		dc.SetTextColor(RGB(29,219,22));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+65,_T("��"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+65,cal.m_memo3);
	}else{
		dc.SetTextColor(RGB(140,140,140));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+65,_T("��"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+65,cal.m_memo3);
	}
	}else{
	CString lmemo;
	lmemo= cal.m_memo3.Left(4);
	if(ch3 == TRUE){
		dc.SetTextColor(RGB(29,219,22));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+65,_T("��"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+65,lmemo+_T("..."));
	}else{
		dc.SetTextColor(RGB(140,140,140));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+65,_T("��"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+65,lmemo+_T("..."));
	}
	}
	}
	if(cal.m_memo4 != ""){
	if(cal.m_memo4.GetLength() <= 4){
	if(ch4 == TRUE){
		dc.SetTextColor(RGB(29,219,22));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+85,_T("��"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+85,cal.m_memo4);
	}else{
		dc.SetTextColor(RGB(140,140,140));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+85,_T("��"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+85,cal.m_memo4);
	}
	}else{
		CString lmemo;
		lmemo= cal.m_memo4.Left(4);
		if(ch4 == TRUE){
		dc.SetTextColor(RGB(29,219,22));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+85,_T("��"));
		dc.SetTextColor(RGB(0,51,153));
		dc.TextOut(rect[preweek][preday].left+20,rect[preweek][preday].top+85,lmemo+_T("..."));
	}else{
		dc.SetTextColor(RGB(140,140,140));
		dc.TextOut(rect[preweek][preday].left+5,rect[preweek][preday].top+85,_T("��"));
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

	// �׸��� �޽����� ���ؼ��� CFormView::OnPaint()��(��) ȣ������ ���ʽÿ�.
}


void CCalendarManage::OnBnClickedPrev()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	month=month-1;  // ���� �Ѵ� ����
	day_=1;         // ���� 1��
	DrawMode = FALSE;   // ó�� �׷����� �� �ƴ�
	if (month<1) {            // ���� 1������ ������
		year = year-1;        // �׷� �⵵�� �ϳ� �پ�����.
		month=12;             // ���� 12���� �Ѿ���.
		day_=1;          
	}
	Invalidate();        // �̰��� OnPaint�Լ��� ȣ���Ѵٰ��ϳ׿�. �׷��� �ٽ� �׷��ִ°�����.
}


void CCalendarManage::OnBnClickedNext()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	month=month+1;       // ���� �Ѵ� ����
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	  CClientDC dc(this);

	CFont font16;
	font16.CreateFont(18,13,0,0, FW_NORMAL, FALSE, FALSE, 0,   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("�����ٸ����"));
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


            CDatabase db;			// �����ͺ��̽� ��ü ����
			CRecordset rs (&db);	// ���ڵ�� ��ü ����
		
		if(memo!="" || memo2!="" ||memo3!="" || memo4!=""){

		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");	//DB����
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("�����ͺ��̽� ���ӽ���!");

			CString strQuery;	//�����ͺ��̽��� ������ ������
			strQuery.Format(_T("INSERT INTO Calendar VALUES ('%s','%s','%s','%s', %d , %d, %d, %d, %d, %d , %d, %d, %d)"),memo,memo2,memo3,memo4,year,month,pday,week,day,check,check2,check3,check4);
			
			db.ExecuteSQL(strQuery);	//�����ͺ��̽��� ������ ����
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
		MessageBox(_T("���������� �߰��Ǿ����ϴ�."));
		
		                
		           dc.SetTextColor(RGB(155,0,155));
				   if(memo != ""){
		            if(check == TRUE){
						if(memo.GetLength() <= 4){
								dc.SetTextColor(RGB(29,219,22));
								dc.TextOut(rect[i][j].left+5,rect[i][j].top+25,_T("��"));
								dc.SetTextColor(RGB(0,51,153));
								dc.TextOut(rect[i][j].left+20,rect[i][j].top+25,memo);
						}else{
							CString lmemo;
							lmemo= memo.Left(4); 
							dc.SetTextColor(RGB(29,219,22));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+25,_T("��"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+25,lmemo+_T("..."));
						}
					}else{
						if(memo.GetLength() <= 4){
							dc.SetTextColor(RGB(140,140,140));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+25,_T("��"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+25,memo);
						}else{
							CString lmemo;
							lmemo= memo.Left(4); 
							dc.SetTextColor(RGB(140,140,140));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+25,_T("��"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+25,lmemo+_T("..."));
						}
					 }
				   }
				   if(memo2 != ""){
		            if(check2 == TRUE){
						if(memo2.GetLength() <= 4){
								dc.SetTextColor(RGB(29,219,22));
								dc.TextOut(rect[i][j].left+5,rect[i][j].top+45,_T("��"));
								dc.SetTextColor(RGB(0,51,153));
								dc.TextOut(rect[i][j].left+20,rect[i][j].top+45,memo2);
						}else{
							CString lmemo;
							lmemo= memo2.Left(4); 
							dc.SetTextColor(RGB(29,219,22));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+45,_T("��"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+45,lmemo+_T("..."));
						}
					}else{
						if(memo2.GetLength() <= 4){
							dc.SetTextColor(RGB(140,140,140));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+45,_T("��"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+45,memo2);
						}else{
							CString lmemo;
							lmemo= memo2.Left(4); 
							dc.SetTextColor(RGB(140,140,140));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+45,_T("��"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+45,lmemo+_T("..."));
						}
					 }
				   }
				   if(memo3 != ""){
		            if(check3 == TRUE){
						if(memo3.GetLength() <= 4){
								dc.SetTextColor(RGB(29,219,22));
								dc.TextOut(rect[i][j].left+5,rect[i][j].top+65,_T("��"));
								dc.SetTextColor(RGB(0,51,153));
								dc.TextOut(rect[i][j].left+20,rect[i][j].top+65,memo3);
						}else{
							CString lmemo;
							lmemo= memo3.Left(4); 
							dc.SetTextColor(RGB(29,219,22));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+65,_T("��"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+65,lmemo+_T("..."));
						}
					}else{
						if(memo3.GetLength() <= 4){
							dc.SetTextColor(RGB(140,140,140));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+65,_T("��"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+65,memo3);
						}else{
							CString lmemo;
							lmemo= memo3.Left(4); 
							dc.SetTextColor(RGB(140,140,140));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+65,_T("��"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+65,lmemo+_T("..."));
						}
					 }
				   }
				   if(memo4 != ""){
		            if(check4 == TRUE){
						if(memo4.GetLength() <= 4){
								dc.SetTextColor(RGB(29,219,22));
								dc.TextOut(rect[i][j].left+5,rect[i][j].top+85,_T("��"));
								dc.SetTextColor(RGB(0,51,153));
								dc.TextOut(rect[i][j].left+20,rect[i][j].top+85,memo4);
						}else{
							CString lmemo;
							lmemo= memo4.Left(4); ;
							dc.SetTextColor(RGB(29,219,22));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+85,_T("��"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+85,lmemo+_T("..."));
						}
					}else{
						if(memo4.GetLength() <= 4){
							dc.SetTextColor(RGB(140,140,140));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+85,_T("��"));
							dc.SetTextColor(RGB(0,51,153));
							dc.TextOut(rect[i][j].left+20,rect[i][j].top+85,memo4);
						}else{
							CString lmemo;
							lmemo= memo4.Left(4); 
							dc.SetTextColor(RGB(140,140,140));
							dc.TextOut(rect[i][j].left+5,rect[i][j].top+85,_T("��"));
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CPoint ptInSrceen;

    GetCursorPos(&ptInSrceen); //R��ư ������ǥ����

	CMenu muTemp, *pContextMenu;
	muTemp.LoadMenuW(IDR_CALENDER);
	pContextMenu = muTemp.GetSubMenu(0);
	pContextMenu -> TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, ptInSrceen.x, ptInSrceen.y,this);
	CFormView::OnRButtonDown(nFlags, point);

	CFormView::OnRButtonDown(nFlags, point);
}


void CCalendarManage::OnDaygo()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	    year = _ttoi(ye);     // �⵵�� ù��° ����Ʈ �ڽ��� ������.
		month = _ttoi(mo);   // ���� �ι�° ����Ʈ �ڽ��� ���Դϴ�.
	    day_ = 1;
	    DrawMode = FALSE;
        Invalidate();
	}
	UpdateData(FALSE);

}


void CCalendarManage::OnDeletememo()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	yearpre = m_year;
 	monthpre = m_month;
	CCalDeleteMemoDlg dlg;
	dlg.DoModal();

	Invalidate();
}


void CCalendarManage::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("�����ٸ����"));
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CTime timer;
	timer = CTime::GetCurrentTime();
	     // ���� ����� ���ϱ�
       int yea = timer.GetYear();
	   int mont = timer.GetMonth();
	    year = yea;     // �⵵�� ù��° ����Ʈ �ڽ��� ������.
		month = mont;   // ���� �ι�° ����Ʈ �ڽ��� ���Դϴ�.
	    day_ = 1;
	    DrawMode = FALSE;
		Invalidate();

}


BOOL CCalendarManage::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CRect rt;
    GetClientRect(&rt);  // Ŭ���̾�Ʈ ������ ũ�� ���
	pDC->FillSolidRect(&rt, RGB(247, 246, 238));  

	return TRUE; 


	return CFormView::OnEraseBkgnd(pDC);
}


HBRUSH CCalendarManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.

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
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}
