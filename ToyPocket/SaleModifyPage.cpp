// SaleModifyPage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "SaleModifyPage.h"
#include "afxdialogex.h"


// CSaleModifyPage ��ȭ �����Դϴ�.

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


// CSaleModifyPage �޽��� ó�����Դϴ�.


BOOL CSaleModifyPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_modifybtn.LoadBitmaps(IDB_BMP_OKSET, NULL, NULL, NULL);
	m_modifybtn.SizeToContent();
	m_modicancelbtn.LoadBitmaps(IDB_BMP_CANCEL, NULL, NULL, NULL);
	m_modicancelbtn.SizeToContent();

	m_sim_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	if(m_sim_list.GetHeaderCtrl()->GetItemCount() <= 0)		//����� �������� ���ٸ�
	{
		CRect rect;
		m_sim_list.GetClientRect(&rect);
		m_sim_list.InsertColumn(0, _T("��ǰ�ڵ�"),			LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(1, _T("��ǰ��"),			LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(2, _T("��з�"),			LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(3, _T("�ߺз�"),			    LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(4, _T("�Һз�"),			    LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(5, _T("�����"),			LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(6, _T("�ŷ�ó�̸�"),			LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(7, _T("�ŷ�ó�ڵ�"),			LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(8, _T("��ǰ�̹���"),			LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(9, _T("�԰���"),			    LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(10, _T("�԰����"),	LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(11, _T("���԰�"),	LVCFMT_LEFT, 80);
		m_sim_list.InsertColumn(12, _T("�Ǹűݾ�"),	LVCFMT_LEFT, 80);
	}

	GetDlgItem(IDC_COMBO4)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO3)->EnableWindow(FALSE);	
	GetDlgItem(IDC_COMBO2)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT14)->EnableWindow(FALSE);

	//��� ��Ʈ�� �巡��-��-��� ����
	DWORD dwExStyle = m_sim_list.GetExtendedStyle();
	m_sim_list.SetExtendedStyle(dwExStyle | LVS_EX_HEADERDRAGDROP );

	m_bAscending = FALSE;
	m_sim_list.SortItems(&CSaleModifyPage::CompareItem, (DWORD_PTR)this);
	UpdateArrow();

		if(m_sim_list.GetItemCount() > 0) m_sim_list.DeleteAllItems();

		CDatabase db;			// �����ͺ��̽� ��ü ����
		CRecordset rs (&db);	// ���ڵ�� ��ü ����
		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");
		
			if (db.OpenEx (strConnection) == FALSE)
				throw _T("�����ͺ��̽� ���ӽ���!");

			CString strQuery;	//�����ͺ��̽��� ������ ������
			strQuery.Format(_T("SELECT * FROM Item WHERE i_code LIKE '%%%s%%'"),g_icode);
		
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
				m_sim_list.InsertItem(p,tmp,0);
				for(short i=1; i<col; i++  )
				 {
					rs.GetFieldValue(i, tmp);  
					// ù��° ���ڴ� InsertValue�� ���ؼ� ������ �� ������ �Ǵ� ����, �ι�° ���ڴ� �������� �ϳ��� 
					m_sim_list.SetItemText(p, i ,tmp);

				}
				rs.MoveNext(); //���������� �̵�
			}
		}
		rs.Close();	//���ڵ�� ��ü �Ҹ�
		db.Close();	//�����ͺ��̽� ��ü �Ҹ�

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

		if(m_samount != g_soutAmount)
		{
		
		COleDateTime Date;   //����ڰ� ������ ��¥�� ������ ColeDateTimeDate ����   
		CString Year = g_soutDate_Year;   //��
		CString Month = g_soutDate_Month; //��
		CString Day = g_soutDate_Day;    //��
		Date.SetDate(_tstoi(Year),_tstoi(Month),_tstoi(Day));
		m_soutDate.SetTime(Date);

		m_samount_Edit.SetWindowTextW(g_soutAmount);
		m_sicode_Edit.SetWindowTextW(g_icode);
		
		}
	// �׸��� �޽����� ���ؼ��� CPropertyPage::OnPaint()��(��) ȣ������ ���ʽÿ�.
}


void CSaleModifyPage::OnBnClickedSalemodify()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);
	if(m_samount_modify!=""){
		
		CString sdate;
		sdate.Format(_T("%d-%02d-%02d"),m_soutdate_value.GetYear(),m_soutdate_value.GetMonth(),m_soutdate_value.GetDay());

		CString amount;		//���������
		amount.Format(_T("%d"), _ttoi(inputamount) + _ttoi(m_samount) - _ttoi(m_samount_modify));

		CDatabase db;			// �����ͺ��̽� ��ü ����
		CRecordset rs (&db);	// ���ڵ�� ��ü ����
		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");	//DB����
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("�����ͺ��̽� ���ӽ���!");

			CString strQuery;	//�����ͺ��̽��� ������ ������
			strQuery.Format(_T("UPDATE Sale SET s_outputDate ='%s' , s_outputAmount ='%s'  WHERE i_code = '%s'"), sdate,  m_samount_modify, m_sicode);
			db.ExecuteSQL(strQuery);	//�����ͺ��̽��� ������ ����

			strQuery.Format(_T("UPDATE Item SET i_inputAmount ='%s' WHERE i_code ='%s'"), amount,m_sicode);
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

		rs.Close();	//���ڵ�� ��ü �Ҹ�
		db.Close();	//�����ͺ��̽� ��ü �Ҹ�
	}else MessageBox(_T("�Էµ��� ���� ���� �ֽ��ϴ�.\n��� ���� �Է�(����)���ּ���."));
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nColumn = phdr->iItem;
	// ���� ����Ʈ ��Ʈ�ѿ� �ִ� ������ �� �ڷ� ������ŭ ����
	 for(int i=0; i< (m_sim_list.GetItemCount()); i++)
	{
	 m_sim_list.SetItemData(i, i);
	}

	// ���� ��� ����(Ascend, Descend)
	 m_bAscending = !m_bAscending;
	 UpdateArrow();

	// ���� ���õ� ����ü ���� ���� �� ������ �ʱ�ȭ
	SORTPARAM sortparams;
	sortparams.pList = &m_sim_list;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending;

	// ���� �Լ� ȣ��
	m_sim_list.SortItems(&CompareItem, (LPARAM)&sortparams );
	*pResult = 0;
}


HCURSOR CSaleModifyPage::OnQueryDragIcon()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CPropertyPage::OnQueryDragIcon();
}


void CSaleModifyPage::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CPropertyPage::OnSysCommand(nID, lParam);
}
