// HomepageFormView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "HomepageFormView.h"
#include "CalendarSet.h"
#include "CalenderMemoDlg.h"

#define xx1 50  //�޷��� �ǿ������� x��ǥ
#define yy1 380  //�޷��� �ǿ������� y��ǥ
#define gap1 50 //�Ϸ��Ϸ簣�� ����
#define daycount1 7 //�������� 7��
#define weekcount1 6 //�Ѵ��� ���Ƶ� 5������
#define x2 xx1+gap1*daycount1 //�޷��� �ǿ����� �Ʒ��� x��ǥ
#define y2 yy1+gap1*weekcount1 //�ް��� �ǿ����� �Ʒ��� y��ǥ

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


// CHomepageFormView �����Դϴ�.

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


// CHomepageFormView �޽��� ó�����Դϴ�.


void CHomepageFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	
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
	//��������׺κ�
	m_noticeList.SetExtendedStyle(LVS_EX_FULLROWSELECT); //����ü����
	
	if(m_noticeList.GetHeaderCtrl()->GetItemCount() <= 0)		//����� �������� ���ٸ�
	{
		CRect rect;
		m_noticeList.GetClientRect(&rect);
		m_noticeList.InsertColumn(0, _T("��¥"),			LVCFMT_LEFT, 100);
		m_noticeList.InsertColumn(1, _T("���� ����"),			LVCFMT_LEFT, 385);
	}
	m_bAscending = FALSE;
	m_noticeList.SortItems(&CHomepageFormView::CompareItem, (DWORD_PTR)this);
	UpdateArrow();

	CFont    m_fontTitle;
	LOGFONT  lf; 

	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 15;
	::lstrcpy(lf.lfFaceName, _T("�����ٸ����"));
	m_fontTitle.CreateFontIndirect(&lf);
	GetDlgItem(IDC_STATIC1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_LIST1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_YEAR)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC3)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_MONTH)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC4)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 

			if(m_noticeList.GetItemCount() > 0) m_noticeList.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
		strQuery.Format(_T("SELECT n_date, n_notice  FROM Notice"));
		
		if (rs.Open (CRecordset::snapshot, strQuery) == FALSE)	
			throw _T("�������� ����!");
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
		
	//�������� �̿��� �˻��� ���� ����Ʈ ��Ʈ�ѿ� ���
	short col = rs.GetODBCFieldCount();	
	for(int p=0 ; p<2 ; p++)
	{
		 while( ! rs.IsEOF())		//�����
		 {
			 //�Ӽ�����
			 CString tmp;
			 rs.GetFieldValue((short)p, tmp);  
			 //id���� ������ �ȴ�.
			 m_noticeList.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				// ù��° ���ڴ� InsertValue�� ���ؼ� ������ �� ������ �Ǵ� ����, �ι�° ���ڴ� �������� �ϳ��� 
				m_noticeList.SetItemText(p, i ,tmp);
			}
			rs.MoveNext();	//���������� �̵�
		 }
	}
	rs.Close();	//���ڵ�� ��ü �Ҹ�
	db.Close();	//�����ͺ��̽� ��ü �Ҹ�


}
#include "MainFrm.h"

void CHomepageFormView::OnPaint()
{
 // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	HBITMAP hbit;
	 hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_HOMELOGO));

	staticsize.SetBitmap(hbit) ;


	int i,day_x,day_y,last_day,k;
	int centry, draw_x, draw_y;
    char daynum[5], y[10],m[10];
	int t_day[12]={31,28,31,30,31,30,31,31,30,31,30,31}; // �޺� ���� 
    
	CString day[7]={_T("��"), _T("��"),_T("ȭ"),_T("��"),_T("��"),_T("��"),_T("��")};      // ����
	CPaintDC dc(this); // device context for painting
	
	CFont font9;
	font9.CreateFont(15,10,0,0, FW_NORMAL, FALSE, FALSE, 0,   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("�����ٸ����"));
	CFont *oldFont = dc.SelectObject(&font9);

	dc.SetBkMode(TRANSPARENT);

	// TODO: Add your message handler code here
    dc.Rectangle(xx1,yy1,x2,y2);	// �޷� �簢�� �׸���
	dc.Rectangle(xx1,yy1-20,x2,yy1); //���� ǥ�û簢�� �׸��� 
	for (i=1;i<=(daycount1-1);i++)  //������ �׸��� 7������. �ٵ� 6�ٸ� �׸��� ����.
    {
		dc.MoveTo(xx1+gap1*i,yy1-20);
		dc.LineTo(xx1+gap1*i,y2);
	}
    for (i=1;i<=(weekcount1-1);i++)  //������ �׸��� 6������. �ٵ� 4�ٸ� �׸��� ����. ������ �̹� �׷��� �����ϱ��.
    {
		dc.MoveTo(xx1,yy1+gap1*i);
		dc.LineTo(x2,yy1+gap1*i);
	}
	for (i=1;i<=7;i++) {           // ���� ǥ���ϱ�
        day_x = xx1+gap1*(i-1)+gap1/2-7;
		day_y = yy1-18;
	    if (i==1) dc.SetTextColor(RGB(255,0,0));        // ������̸� �Ķ���, �Ͽ����̸� ������
		else if (i==7) dc.SetTextColor(RGB(0,0,255));
		else dc.SetTextColor(RGB(0,0,0));
		dc.TextOut(day_x,day_y,day[i-1]);
		
	}
	CTime timer;
	timer = CTime::GetCurrentTime();
	if (DrawMode1) {
	     // ���� ����� ���ϱ�
       year1 = timer.GetYear();
	   month1 = timer.GetMonth();
       day_1 = timer.GetDay();
	}
	_itoa(year1,y,10);
	_itoa(month1,m,10);

	UpdateData(TRUE);  // �̰������ ��Ʈ��(����Ʈ�ڽ�)�� ���� �ٲ��ϴ�.
	m_year = CString(y);
	m_month = CString(m);
    UpdateData(FALSE);

    centry = (year1/100+1); // ����� �⵵�� 100�� ������ 1�� ���ָ� ������.
    one_whatday = (year1-1)*365+(year1-1)/4-(year1-1)/100+(year1-1)/400; // �⵵�ϼ�
	if ((year1%4 == 0 && year1%100 != 0) || (year1%400==0)) //�⵵�� 400���� ������ �������ų� 4�ǹ���̰� 100���� ������ �������� ������ ����
           t_day[1]=29;
	else t_day[1]=28;
	
	for(i=1;i<month1;i++)
	    one_whatday += t_day[i-1]; // ���ϼ�
    
	one_whatday += 1; // �״��� 1���� ����
	one_whatday = one_whatday % 7;  // 1�̸� ������ 7�̸� �Ͽ���
    one_whatday += 1;
	draw_x = xx1+gap1*(one_whatday-1)+gap1/2-7; // 1�� ǥ���ϱ�
    draw_y = yy1+gap1/2;
	
	if (one_whatday==1) dc.SetTextColor(RGB(255,0,0));     // �Ͽ����̸� ������, ������̸� �Ķ��� 
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
    
	if ((month1==1) || (month1==3) || (month1==5) || (month1==7) || (month1==8) || (month1==10) || (month1==12)) // ���ϱ��� �ִ��� ��� 1,3,5,7,8,10,12���� 31���� ����.
		last_day = 31;
	else if ((month1==4) || (month1==6) || (month1==9) || (month1==11))
		last_day=30;

    if (month1==2)
	if ((year1%4 == 0 && year1%100 != 0) || (year1%400==0)) //�⵵�� 400���� ������ �������ų� 4�ǹ���̰� 100���� ������ �������� ������ ����
           last_day=29;  // last_day ������ �״��� �ϼ��� ���ϴ� ���Դϴ�. ������� 1���� 31������. 
	else last_day=28; // �׷��� ������ ���
	                // �������ؼ� 2���޿� �����ϱ�




	k = one_whatday+1;
	if(k>7) k=1;
	for(i=2;i<=last_day;i++) { // ��¥ ǥ���ϱ�
	   draw_x = draw_x+gap1;  // ��¥ ǥ�� x��ǥ���ϱ�
	   if (draw_x>x2) {
		   draw_x=xx1+gap1/2-7;
		   draw_y=draw_y+gap1; // ���࿡ ĭ�� �Ѿ�� �����ٷ� �̵�
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


	// �׸��� �޽����� ���ؼ��� CFormView::OnPaint()��(��) ȣ������ ���ʽÿ�.
}


void CHomepageFormView::OnBnClickedLamonth()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
		month1=month1-1;  // ���� �Ѵ� ����
	day_1=1;         // ���� 1��
	DrawMode1 = FALSE;   // ó�� �׷����� �� �ƴ�
	if (month1<1) {            // ���� 1������ ������
		year1 = year1-1;        // �׷� �⵵�� �ϳ� �پ�����.
		month1=12;             // ���� 12���� �Ѿ���.
		day_1=1;          
	}
	Invalidate(); 
}


void CHomepageFormView::OnBnClickedNemonth()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	month1=month1+1;       // ���� �Ѵ� ����
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

		CDC dc;

			CFont font10;
	font10.CreateFont(20,15,0,0, FW_NORMAL, FALSE, FALSE, 0,   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("�����ٸ����"));
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


            CDatabase db;			// �����ͺ��̽� ��ü ����
			CRecordset rs (&db);	// ���ڵ�� ��ü ����
		
		if(memo!=""||memo2!=""||memo3!=""||memo4!=""){

		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");	//DB����
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("�����ͺ��̽� ���ӽ���!");

			CString strQuery;	//�����ͺ��̽��� ������ ������
			strQuery.Format(_T("INSERT INTO calendar VALUES ('%s','%s','%s','%s', %d , %d, %d, %d, %d, %d , %d, %d, %d)"),memo,memo2,memo3,memo4,year,month,pday,week,day,check,check2,check3,check4);
			
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
		


		rs.Close();	//���ڵ�� ��ü �Ҹ�
		db.Close();	//�����ͺ��̽� ��ü �Ҹ�
		                

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nColumn = phdr->iItem;
	// ���� ����Ʈ ��Ʈ�ѿ� �ִ� ������ �� �ڷ� ������ŭ ����
	 for(int i=0; i< (m_noticeList.GetItemCount()); i++)
	{
	 m_noticeList.SetItemData(i, i);
	}

	// ���� ��� ����(Ascend, Descend)
	 m_bAscending = !m_bAscending;


	 UpdateArrow();


	// ���� ���õ� ����ü ���� ���� �� ������ �ʱ�ȭ
	SORTPARAM sortparams;
	sortparams.pList = &m_noticeList;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending;

	// ���� �Լ� ȣ��
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rt;
    GetClientRect(&rt);  // Ŭ���̾�Ʈ ������ ũ�� ���
	//pDC->FillSolidRect(&rt, RGB(250, 244, 192));  
	pDC->FillSolidRect(&rt, RGB(255, 255, 255));  
	return TRUE; 
	//return CFormView::OnEraseBkgnd(pDC);
}


HBRUSH CHomepageFormView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	UINT nID = pWnd->GetDlgCtrlID();			//��Ʈ�� �ڵ�� ���ϱ� ���� ����
 
    if(nID==IDC_STATIC1)							// ����ƽ ��Ʈ���϶�
    {    
        pDC->SetBkMode(TRANSPARENT);                              
        return (HBRUSH)::GetStockObject(NULL_BRUSH);                      
    }
	 if(nID==IDC_STATIC3)							// ����ƽ ��Ʈ���϶�
    {    
        pDC->SetBkMode(TRANSPARENT);                              
        return (HBRUSH)::GetStockObject(NULL_BRUSH);                      
    }
	  if(nID==IDC_STATIC4)							// ����ƽ ��Ʈ���϶�
    {    
        pDC->SetBkMode(TRANSPARENT);                              
        return (HBRUSH)::GetStockObject(NULL_BRUSH);                      
    }
	   if(nID==IDC_YEAR)							// ����ƽ ��Ʈ���϶�
    {    
        pDC->SetBkMode(TRANSPARENT);                              
        return (HBRUSH)::GetStockObject(NULL_BRUSH);                      
    }
	    if(nID==IDC_MONTH)							// ����ƽ ��Ʈ���϶�
    {    
        pDC->SetBkMode(TRANSPARENT);                              
        return (HBRUSH)::GetStockObject(NULL_BRUSH);                      
    }
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}


void CHomepageFormView::OnBnClickedCompany()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SwitchView(VIEWID_COMPANY_SHEET);
}


void CHomepageFormView::OnBnClickedItem()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SwitchView(VIEWID_ITEM_SHEET);
}


void CHomepageFormView::OnBnClickedSale()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_salecheck = TRUE;
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SwitchView(VIEWID_SALE_SHEET);
}


void CHomepageFormView::OnBnClickedExchange()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_excheck = TRUE;
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SwitchView(VIEWID_EXCHANGE_SHEET);
}


void CHomepageFormView::OnBnClickedReturn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_recheck = TRUE;
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SwitchView(VIEWID_RETURN_SHEET);
}

#include "PasswordChangeDlg.h"
void CHomepageFormView::OnBnClickedSet()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CPasswordChangeDlg dlg;
	dlg.DoModal();
}

/*
Z

void CHomepageFormView::OnBnClickedSaleBtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_salecheck = TRUE;
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SwitchView(VIEWID_SALE_SHEET);
}


void CHomepageFormView::OnBnClickedExchange()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_excheck = TRUE;
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SwitchView(VIEWID_EXCHANGE_SHEET);
}


void CHomepageFormView::OnBnClickedReturn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_recheck = TRUE;
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SwitchView(VIEWID_RETURN_SHEET);

}

void CHomepageFormView::OnBnClickedSet()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SwitchView(VIEWID_MANAGE_SHEET);
}

*/