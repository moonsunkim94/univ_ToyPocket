// CalDeleteMemoDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "CalDeleteMemoDlg.h"
#include "afxdialogex.h"


// CCalDeleteMemoDlg ��ȭ �����Դϴ�.

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


// CCalDeleteMemoDlg �޽��� ó�����Դϴ�.


BOOL CCalDeleteMemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_memolist.SetExtendedStyle( LVS_EX_FULLROWSELECT ); //����ü����

	if(m_memolist.GetHeaderCtrl()->GetItemCount() <= 0)		//����� �������� ���ٸ�
	{
		CRect rect;
		m_memolist.GetClientRect(&rect);
		m_memolist.InsertColumn(0, _T("��"),			LVCFMT_LEFT, 50);
		m_memolist.InsertColumn(2, _T("����1"),			LVCFMT_LEFT, 100);
		m_memolist.InsertColumn(4, _T("����2"),			LVCFMT_LEFT, 100);
		m_memolist.InsertColumn(6, _T("����3"),			LVCFMT_LEFT, 100);
		m_memolist.InsertColumn(8, _T("����4"),			LVCFMT_LEFT, 100);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CCalDeleteMemoDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	if(m_memolist.GetItemCount() > 0) m_memolist.DeleteAllItems();

	CDatabase db;			// �����ͺ��̽� ��ü ����
	CRecordset rs (&db);	// ���ڵ�� ��ü ����

	CString str = _T("/");

	try
	{
		CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
		if (db.OpenEx (strConnection) == FALSE)
			  throw _T("�����ͺ��̽� ���ӽ���!");

		CString strQuery;
		strQuery.Format(_T("SELECT preday, memo, memo2, memo3, memo4 FROM Calendar WHERE preyear = %d AND premonth = %d ORDER BY preday DESC"),_ttoi(yearpre),_ttoi(monthpre));
		
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
			 m_memolist.InsertItem(p,tmp,0);
			 for(short i=1; i<col; i++  )
			 {
				rs.GetFieldValue(i, tmp);
				// ù��° ���ڴ� InsertValue�� ���ؼ� ������ �� ������ �Ǵ� ����, �ι�° ���ڴ� �������� �ϳ��� 
				m_memolist.SetItemText(p, i ,tmp);
			}
			rs.MoveNext();	//���������� �̵�
		 }
	}
	rs.Close();	//���ڵ�� ��ü �Ҹ�
	db.Close();	//�����ͺ��̽� ��ü �Ҹ�

	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
}


void CCalDeleteMemoDlg::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    nListIndex = pNMListView->iItem;

	daynumber = m_memolist.GetItemText(nListIndex,0);

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
			strQuery.Format(_T("DELETE * FROM Calendar WHERE preday = %d"),_ttoi(daynumber));
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

	*pResult = 0;
}


BOOL CCalDeleteMemoDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CRect rt;
    GetClientRect(&rt);  // Ŭ���̾�Ʈ ������ ũ�� ���
	pDC->FillSolidRect(&rt, RGB(247, 246, 238));  

	return TRUE; 

	return CDialogEx::OnEraseBkgnd(pDC);
}
