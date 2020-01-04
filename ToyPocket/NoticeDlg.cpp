// NoticeDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "NoticeDlg.h"
#include "afxdialogex.h"


// CNoticeDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CNoticeDlg, CDialogEx)

CNoticeDlg::CNoticeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNoticeDlg::IDD, pParent)
	, m_addnotice(_T(""))
{

}

CNoticeDlg::~CNoticeDlg()
{
}

void CNoticeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_plusbtn);
	DDX_Control(pDX, IDC_BUTTON2, m_minusbtn);
	DDX_Control(pDX, IDC_BUTTON3, m_setbtn);
	DDX_Text(pDX, IDC_EDIT1, m_addnotice);
	DDX_Control(pDX, IDC_EDIT1, m_addnotice_Edit);
	DDX_Control(pDX, IDC_LIST1, m_noticeList);
}


BEGIN_MESSAGE_MAP(CNoticeDlg, CDialogEx)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CNoticeDlg::OnHdnItemclickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CNoticeDlg::OnNMDblclkList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CNoticeDlg::OnNMRClickList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CNoticeDlg::OnNMClickList1)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BUTTON1, &CNoticeDlg::OnBnClickedAddBtn)
	ON_BN_CLICKED(IDC_BUTTON2, &CNoticeDlg::OnBnClickedDeleteBtn)
	ON_BN_CLICKED(IDC_BUTTON3, &CNoticeDlg::OnBnClickedBModiBtn)
	ON_COMMAND(ID_NOTICE_MODI, &CNoticeDlg::OnNoticeModi)
	ON_WM_ERASEBKGND()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, OnCustomdrawList)
END_MESSAGE_MAP()


// CNoticeDlg �޽��� ó�����Դϴ�.

void CNoticeDlg::OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult)
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

void CNoticeDlg::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
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


void CNoticeDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_addnotice_Edit.SetWindowTextW(nnotice);
	GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_SHOW);
	*pResult = 0;
}


void CNoticeDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    nListIndex = pNMListView->iItem;

	CPoint ptInSrceen;

    GetCursorPos(&ptInSrceen); //R��ư ������ǥ����


	if(nListIndex==-1){
	}
	else{
	CMenu muTemp, *pContextMenu;
	muTemp.LoadMenuW(IDR_PopupMenu);
	pContextMenu = muTemp.GetSubMenu(7);
	pContextMenu -> TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, ptInSrceen.x, ptInSrceen.y,this);
	}
	nnotice = m_noticeList.GetItemText(nListIndex,1);
	*pResult = 0;
}


void CNoticeDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    nListIndex = pNMListView->iItem;

	nnotice = m_noticeList.GetItemText(nListIndex,1);
	*pResult = 0;
}


void CNoticeDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
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


HCURSOR CNoticeDlg::OnQueryDragIcon()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CDialogEx::OnQueryDragIcon();
}


void CNoticeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialogEx::OnSysCommand(nID, lParam);
}

int CALLBACK CNoticeDlg::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl *pListCtrl = ((SORTPARAM *)lParamSort)->pList;

	int iSortColumn = ((SORTPARAM *)lParamSort)->iSortColumn;
	bool bSortDirect = ((SORTPARAM *)lParamSort)->bSortDirect;

	CString    strItem1 = pListCtrl->GetItemText(static_cast<int>(lParam1), iSortColumn);
	CString    strItem2 = pListCtrl->GetItemText(static_cast<int>(lParam2), iSortColumn);

	return bSortDirect ? _tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2) : -_tcscmp((TCHAR *)(LPCTSTR)strItem1, (TCHAR *)(LPCTSTR)strItem2);


}

void CNoticeDlg::UpdateArrow(void)
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

BOOL CNoticeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_noticeList.SetExtendedStyle(LVS_EX_FULLROWSELECT); //����ü����
	
	if(m_noticeList.GetHeaderCtrl()->GetItemCount() <= 0)		//����� �������� ���ٸ�
	{
		CRect rect;
		m_noticeList.GetClientRect(&rect);
		m_noticeList.InsertColumn(0, _T("��     ¥"),			LVCFMT_LEFT, 100);
		m_noticeList.InsertColumn(1, _T("���� ����"),			LVCFMT_LEFT, 561);
	}
	m_bAscending = FALSE;
	m_noticeList.SortItems(&CNoticeDlg::CompareItem, (DWORD_PTR)this);
	UpdateArrow();

	GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_HIDE);

	m_plusbtn.LoadBitmaps(IDB_BMP_PLUS, NULL, NULL, NULL);
	m_plusbtn.SizeToContent();
	m_minusbtn.LoadBitmaps(IDB_BMP_MINUS, NULL, NULL, NULL);
	m_minusbtn.SizeToContent();
	m_setbtn.LoadBitmaps(IDB_BMP_MODIFY, NULL, NULL, NULL);
	m_setbtn.SizeToContent();

	CFont    m_fontTitle;
	LOGFONT  lf; 

	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 17;
	::lstrcpy(lf.lfFaceName, _T("�����ٸ����"));
	m_fontTitle.CreateFontIndirect(&lf);
	GetDlgItem(IDC_EDIT1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_LIST1)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CNoticeDlg::OnBnClickedAddBtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	if(m_addnotice!=""){
		CTime tm = CTime::GetCurrentTime();
		CString sdate;
		sdate.Format(_T("%d-%02d-%02d"),tm.GetYear(),tm.GetMonth(),tm.GetDay());


		CDatabase db;			// �����ͺ��̽� ��ü ����
		CRecordset rs (&db);	// ���ڵ�� ��ü ����
		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");	//DB����
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("�����ͺ��̽� ���ӽ���!");


			CString strQuery;	//�����ͺ��̽��� ������ ������
			strQuery.Format(_T("INSERT INTO Notice VALUES ('%s', '%s')"), sdate, m_addnotice);

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
		//OnBnClickedButtonComClear();	//��Ʈ�� �ʱ�ȭ
		//�������� �̿��� �˻��� ���� ����Ʈ ��Ʈ�ѿ� ���
		rs.Close();	//���ڵ�� ��ü �Ҹ�
		db.Close();	//�����ͺ��̽� ��ü �Ҹ�
	}else MessageBox(_T("�Էµ��� ���� ���� �ֽ��ϴ�.\n��� ���� �Է�(����)���ּ���."));

	m_addnotice = _T("");
	UpdateData(false);
	Invalidate();
}


void CNoticeDlg::OnBnClickedDeleteBtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int ret;
	ret = AfxMessageBox(_T("�����Ͻðڽ��ϱ�?"), MB_YESNO|MB_ICONSTOP);
	if(ret == IDYES){
	UpdateData(TRUE);

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����
	
		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("�����ͺ��̽� ���ӽ���!");

			CString strQuery;	//�����ͺ��̽��� ������ ������
			strQuery.Format(_T("DELETE * FROM Notice WHERE n_notice = '%s' "),nnotice);
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

		rs.Close();	//���ڵ�� ��ü �Ҹ�
		db.Close();	//�����ͺ��̽� ��ü �Ҹ�
		}
	Invalidate();
}


void CNoticeDlg::OnBnClickedBModiBtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	if(m_addnotice!=""){
		
		CTime tm = CTime::GetCurrentTime();
		CString sdate;
		sdate.Format(_T("%d-%02d-%02d"),tm.GetYear(),tm.GetMonth(),tm.GetDay());

		CDatabase db;			// �����ͺ��̽� ��ü ����
		CRecordset rs (&db);	// ���ڵ�� ��ü ����
		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");	//DB����
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("�����ͺ��̽� ���ӽ���!");

			CString strQuery;	//�����ͺ��̽��� ������ ������
			strQuery.Format(_T("UPDATE Notice SET n_date='%s', n_notice='%s' WHERE n_notice='%s'"),sdate, m_addnotice, nnotice);

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
		MessageBox(_T("���������� �����Ǿ����ϴ�."));
		//OnBnClickedButtonComClear();	//��Ʈ�� �ʱ�ȭ

		rs.Close();	//���ڵ�� ��ü �Ҹ�
		db.Close();	//�����ͺ��̽� ��ü �Ҹ�
	}else MessageBox(_T("�Էµ��� ���� ���� �ֽ��ϴ�.\n��� ���� �Է�(����)���ּ���."));
	m_addnotice=_T("");
	UpdateData(FALSE);
	Invalidate();
	GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_HIDE);
}


void CNoticeDlg::OnNoticeModi()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_addnotice_Edit.SetWindowTextW(nnotice);
	GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_SHOW);
}


BOOL CNoticeDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rt;
    GetClientRect(&rt);  // Ŭ���̾�Ʈ ������ ũ�� ���
	pDC->FillSolidRect(&rt, RGB(247, 246, 238));  

	return TRUE; 
	//return CDialogEx::OnEraseBkgnd(pDC);
}
