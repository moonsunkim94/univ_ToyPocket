// ItemPage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ItemPage.h"
#include "afxdialogex.h"
#include "ItemSheetDlg.h"
#include "ItemSearchPage.h"


// CItemPage ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CItemPage, CPropertyPage)

CItemPage::CItemPage()
	: CPropertyPage(CItemPage::IDD)
	, m_icode(_T(""))
	, m_iname(_T(""))
	, m_icname(_T(""))
	, m_iccode(_T(""))
	, m_idate(COleDateTime::GetCurrentTime())
	, m_icount(_T(""))
	, m_iinput(_T(""))
	, m_ioutput(_T(""))
	, temp(_T(""))
	, Big(_T(""))
	, Middle(_T(""))
	, Small(_T(""))
{

}

CItemPage::~CItemPage()
{
}

void CItemPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_ilarge);
	DDX_Control(pDX, IDC_COMBO4, m_imedium);
	DDX_Control(pDX, IDC_COMBO3, m_ismall);
	DDX_Text(pDX, IDC_EDIT7, m_icode);
	DDX_Text(pDX, IDC_EDIT4, m_iname);
	DDX_Text(pDX, IDC_EDIT14, m_icname);
	DDX_Text(pDX, IDC_EDIT5, m_iccode);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_idate);
	DDX_Text(pDX, IDC_EDIT12, m_icount);
	DDX_Text(pDX, IDC_EDIT15, m_iinput);
	DDX_Text(pDX, IDC_EDIT13, m_ioutput);
	DDX_Control(pDX, IDC_IMAGE, m_iimage);
	DDX_Control(pDX, IDC_EDIT13, m_outprice_Edit);
	DDX_Control(pDX, IDCANCEL2, m_img_setbtn);
	DDX_Control(pDX, IDCANCEL4, m_img_cancelbtn);
	DDX_Control(pDX, IDCANCEL3, m_percent_btn);
	DDX_Control(pDX, IDOK, m_okbtn);
	DDX_Control(pDX, IDCANCEL, m_clearbtn);
	DDX_Control(pDX, IDC_EDIT14, m_cname_Edit);
	DDX_Control(pDX, IDC_EDIT5, m_ccode_Edit);
	DDX_Control(pDX, IDC_BUTTON3, m_comsearchbtn);
}


BEGIN_MESSAGE_MAP(CItemPage, CPropertyPage)
	ON_BN_CLICKED(IDOK, &CItemPage::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CItemPage::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CItemPage::OnCbnSelchangeCombo4)
	ON_BN_CLICKED(IDCANCEL2, &CItemPage::OnBnClickedCancel2)
	ON_BN_CLICKED(IDCANCEL3, &CItemPage::OnBnClickedPercent)
	ON_BN_CLICKED(IDC_BUTTON3, &CItemPage::OnBnClickedComSearch)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDD_IMAGE_DELETE, &CItemPage::OnBnClickedImageDelete)
END_MESSAGE_MAP()


// CItemPage �޽��� ó�����Դϴ�.


#include "SaleSheet.h"
#include "MainFrm.h"
#include "SaleFormView.h"
#include "SalePage.h"
void CItemPage::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	if(m_icode!=""&&m_iname!=""&&m_icname!=""&&m_iccode!=""&&m_icount!=""&&m_iinput!=""&&m_ioutput!=""){
		
		CString s;
		CString sdate;
		sdate.Format(_T("%d-%02d-%02d"),m_idate.GetYear(),m_idate.GetMonth(),m_idate.GetDay());

		CString strlarge;//��з�
		strlarge = SelectLarge(m_ilarge.GetCurSel());
		CString strmid;
		strmid = SelectMedium(m_imedium.GetCurSel());	//�ߺз�
		CString strsmall;
		strsmall = SelectSmall(m_ilarge.GetCurSel(), m_imedium.GetCurSel(), m_ismall.GetCurSel());	//�Һз�


		CDatabase db;			// �����ͺ��̽� ��ü ����
		CRecordset rs (&db);	// ���ڵ�� ��ü ����
		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");	//DB����
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("�����ͺ��̽� ���ӽ���!");

			CString strQuery;	//�����ͺ��̽��� ������ ������
			strQuery.Format(_T("INSERT INTO Item VALUES ('%s', '%s', '%s', '%s','%s', '%s', '%s', '%s', 'res\\\''%s.bmp', '%s', '%s', '%s', '%s')"), 
				m_icode, m_iname, strlarge, strmid, strsmall, g_setid,  m_icname, m_iccode, imgname, sdate,  m_icount, m_iinput, m_ioutput);
			
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

		rs.Close();	//���ڵ�� ��ü �Ҹ�
		db.Close();	//�����ͺ��̽� ��ü �Ҹ�
	}else MessageBox(_T("�Էµ��� ���� ���� �ֽ��ϴ�.\n��� ���� �Է�(����)���ּ���."));
		m_icode = _T("");
		m_iname = _T("");
		m_iccode = _T("");
		m_icname = _T("");
		m_icount = _T("");
		m_iinput = _T("");
		m_ioutput = _T("");
		//�����ʱ�ȭ
		CDateTimeCtrl *pCtrl = (CDateTimeCtrl *) GetDlgItem(IDC_DATETIMEPICKER2);
		CTime tm = CTime::GetCurrentTime();
		pCtrl->SetTime(&tm);

		
		m_ilarge.SetCurSel(-1);
		m_imedium.SetCurSel(-1);
		m_ismall.SetCurSel(-1);

		//�̹����ʱ�ȭ
		CString img;
		img.Format(_T("res\\NoImage.bmp"));
		DrawBMP(img);

		UpdateData(false);

		CItemSheetDlg* pSheet = (CItemSheetDlg*)GetParent();
	    CItemSearchPage* pPage = (CItemSearchPage*)(pSheet->GetPage(1));
	    pPage->ReInitDialog();

		CSaleSheet* pSheet2 = (CSaleSheet*)GetParent();
	    CSalePage* pPage2 = (CSalePage*)(pSheet2->GetPage(0));
	    pPage2->ReInitDialog2();

		//CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
		//CSalePage *pView = (CSalePage*)pFrame->GetActiveView();
		//pView->ReInitDialog();
		//CSalePage *pPage2;
		//pPage2->ReInitDialog();

}



CString CItemPage::SelectLarge(int index)		//��з� ���ڿ� ��ȯ
{
	switch(index)
	{
	case 0 :
		temp = _T("�Ż���/����");
		break;
	case 1 :
		temp = _T("����");
		break;
	case 2 :
		temp = _T("����");
		break;
	case 3 :
		temp = _T("ĳ���ͺ�");
		break;
	}
	return temp;
}

CString CItemPage::SelectMedium(int index)		//�ߺз� ���ڿ� ��ȯ
{
	int select1 = m_ilarge.GetCurSel();
	if(select1 == 0)
	switch(index){
		case 0:
			temp = _T("�Ż���");
			break;
		case 1:
			temp = _T("����");
			break;
		}
	else if(select1 == 1)
	switch(index){
		case 0:
			temp = _T("���ҳ���");
			break;
		case 1:
			temp = _T("����");
			break;
		case 2:
			temp = _T("�ٹ̱�");
			break;
	}
	else if(select1 == 2)
	switch(index){
		case 0:
			temp = _T("���ҳ���");
			break;
		case 1:
			temp = _T("�׼�");
			break;
		case 2:
			temp = _T("����");
			break;
		case 3:
			temp = _T("�ڵ���/����");
			break;
	}
	else if(select1 == 3)
	switch(index){
		case 0:
			temp = _T("����ĳ����");
			break;
		case 1:
			temp = _T("����ĳ����");
			break;
		case 2:
			temp = _T("����ĳ����");
			break;
	}
	return temp;
}

CString CItemPage::SelectSmall(int bigc, int midc, int smallc)		//�Һз� ���ڿ� ��ȯ
{
	if(bigc == 0)
	switch(midc){
		case 0: {
			switch(smallc){
				case 0:	temp = _T("ġ�߱�/������");			break;
				case 1:	temp = _T("���");					break;
				case 2:	temp = _T("�˰�����/������");		break;
				case 3:	temp = _T("�Ʊ�ü����/����Ȩ");		break;
				case 4:	temp = _T("�����/�ٿ/�");		break;
			}break; }
		case 1: {
			switch(smallc){
				case 0: temp = _T("������");			break;
				case 1: temp = _T("������");		break;
				case 3: temp = _T("����/���ҳ���");	break;
				case 4: temp = _T("�Ǳ����");		break;
				case 5: temp = _T("�ڵ�������");		break;
			}break; }
	}
	else if(bigc == 1)
	switch(midc){
		case 0: {
			switch(smallc){
				case 0:	temp = _T("�Ҳ�/�ֹ����");		break;
				case 1:	temp = _T("��Ʈ����");			break;
				case 2:	temp = _T("����/û�ҳ���");		break;
				case 3:	temp = _T("����/��Ÿ����");		break;
			}break; }
		case 1: {
			switch(smallc){
				case 0: temp = _T("��������");		break;
				case 1: temp = _T("��������");		break;
				case 3: temp = _T("�Ʊ�����");		break;
				case 4: temp = _T("ĳ���ͺ�������");	break;
				case 5: temp = _T("������������");	break;
				case 6: temp = _T("�۵���������");	break;
			}break; }
		case 2: {
			switch(smallc){
				case 0: temp = _T("�巹�� �� ��ǰ");		break;
				case 1: temp = _T("���/ȭ�����");		break;
				case 3: temp = _T("�ڵ���/��ī/��Ÿ");	break;
			}break; }
	}
	else if(bigc == 2)
	switch(midc){
		case 0: {
			switch(smallc){
				case 0:	temp = _T("��������");			break;
				case 1:	temp = _T("ī�����");			break;
				case 2:	temp = _T("���ǳ���");			break;
				case 3:	temp = _T("�ڽ�Ƭ�÷���");		break;
				case 4: temp = _T("���/���̳���");		break;
				case 5: temp = _T("�ʰ�/��Ÿ����");		break;
			}break; }
		case 1: {
			switch(smallc){
				case 0: temp = _T("���ŷκ�Ʈ/Ż��");	break;
				case 1: temp = _T("�׼ǹ���");			break;
				case 3: temp = _T("�׼��ǱԾ�");			break;
			}break; }
		case 2: {
			switch(smallc){
				case 0: temp = _T("��ǰ�ڵ���RC");				break;
				case 1: temp = _T("�Ϲ��ڵ���RC");				break;
				case 3: temp = _T("ĳ����RC");					break;
				case 4: temp = _T("���/���/��Ʈ/��ŸRC");		break;
			}break; }
		case 3: {
			switch(smallc){
				case 0:	temp = _T("��ī/Ʈ��/�����");	break;
				case 1:	temp = _T("�Ϲ��ڵ���");			break;
				case 2:	temp = _T("�����ڵ���");			break;
				case 3:	temp = _T("�ڵ������̼�Ʈ");		break;
				case 4: temp = _T("�����/����/��Ÿ");	break;
			}break; }
	}
	else if(bigc == 3)
	switch(midc){
		case 0: {
			switch(smallc){
				case 0:	temp = _T("�׶��");			break;
				case 1:	temp = _T("�׸�������");			break;
				case 2:	temp = _T("���");			break;
				case 3:	temp = _T("�κ�ī����");		break;
				case 4: temp = _T("�Ƿη�");		break;
				case 5: temp = _T("����");		break;
			}break; }
		case 1: {
			switch(smallc){
				case 0: temp = _T("�ܿ�ձ�");	break;
				case 1: temp = _T("����� ��������");			break;
				case 2: temp = _T("�ʶ���");			break;
				case 3: temp = _T("�̹�");		break;
				case 4: temp = _T("�ٺ�");		break;
				case 5: temp = _T("�λ��̵�ƿ�");		break;
				case 6: temp = _T("����");		break;
				case 7: temp = _T("�����");		break;
				case 8: temp = _T("���ŰƼ");		break;
			}break; }
		case 2: {
			switch(smallc){
				case 0: temp = _T("�Ǵ�");				break;
				case 1: temp = _T("�Ǻ�");				break;
				case 3: temp = _T("����ũ����Ʈ");					break;
				case 4: temp = _T("�̴Ͼ���");		break;
				case 5: temp = _T("�����");		break;
				case 6: temp = _T("���ǽ�");		break;
			}break; }
	}
	return temp;
}



void CItemPage::OnCbnSelchangeCombo2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int select1 = m_ilarge.GetCurSel();
	int select2 = m_imedium.GetCurSel();
	int select3 = m_ismall.GetCurSel();

	switch(select1){
		case 0 :
			m_imedium.ResetContent();
			m_imedium.EnableWindow(true);		//�޺��ڽ� Ȱ��ȭ
			m_ismall.EnableWindow(true);
			m_imedium.AddString(_T("�Ż���"));
			m_imedium.AddString(_T("����"));
			m_ismall.ResetContent();
			break;
		case 1 :
			m_imedium.ResetContent();
			m_imedium.EnableWindow(true);
			m_ismall.EnableWindow(true);
			m_imedium.AddString(_T("���ҳ���"));
			m_imedium.AddString(_T("����"));
			m_imedium.AddString(_T("�ٹ̱�"));
			m_ismall.ResetContent();
			break;
		case 2 :
			m_imedium.ResetContent();
			m_imedium.EnableWindow(true);
			m_ismall.EnableWindow(true);
			m_imedium.AddString(_T("���ҳ���"));
			m_imedium.AddString(_T("�׼�"));
			m_imedium.AddString(_T("����"));
			m_imedium.AddString(_T("�ڵ���/����"));
			m_ismall.ResetContent();
			break;
		case 3 :
			m_imedium.ResetContent();
			m_imedium.EnableWindow(true);
			m_ismall.EnableWindow(true);
			m_imedium.AddString(_T("����ĳ����"));
			m_imedium.AddString(_T("����ĳ����"));
			m_imedium.AddString(_T("����ĳ����"));
			m_ismall.ResetContent();
			break;
	}
}


void CItemPage::OnCbnSelchangeCombo4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int select1 = m_ilarge.GetCurSel();
	int select2 = m_imedium.GetCurSel();
	int select3 = m_ismall.GetCurSel();
	if(select1 == 0)
	switch(select2){
		case 0 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("ġ�߱�/������"));
			m_ismall.AddString(_T("���"));
			m_ismall.AddString(_T("�˰�����/������"));
			m_ismall.AddString(_T("�Ʊ�ü����/����Ȩ"));
			m_ismall.AddString(_T("�����/�ٿ/�"));
			break;
		case 1 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("������"));
			m_ismall.AddString(_T("������"));
			m_ismall.AddString(_T("����/���ҳ���"));
			m_ismall.AddString(_T("�Ǳ����"));
			m_ismall.AddString(_T("�ڵ�������"));
			break;
	}
	else if(select1 == 1)
		switch(select2){
		case 0 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("�Ҳ�/�ֹ����"));
			m_ismall.AddString(_T("��Ʈ����"));
			m_ismall.AddString(_T("����/û�ҳ���"));
			m_ismall.AddString(_T("����/��Ÿ����"));
			break;
		case 1 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("��������"));
			m_ismall.AddString(_T("��������"));
			m_ismall.AddString(_T("�ư�����"));
			m_ismall.AddString(_T("ĳ���ͺ�������"));
			m_ismall.AddString(_T("������������"));
			m_ismall.AddString(_T("�۵���������"));
			break;
        case 2 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("�巹�� �� ��ǰ"));
			m_ismall.AddString(_T("���/ȭ�����"));
			m_ismall.AddString(_T("�ڵ���/��ī/��Ÿ"));
	}
	else if(select1 == 2)
		switch(select2){
		case 0 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("��������"));
			m_ismall.AddString(_T("ī�����"));
			m_ismall.AddString(_T("ǰ�ǳ���"));
			m_ismall.AddString(_T("�ڽ�Ƭ�÷���"));
			m_ismall.AddString(_T("���/���̳���"));
			m_ismall.AddString(_T("�ΰ�/��Ÿ����"));
			break;
		case 1 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("���ŷκ�Ʈ/Ż��"));
			m_ismall.AddString(_T("�׼ǹ���"));
			m_ismall.AddString(_T("�׼��ǱԾ�"));
			break;
        case 2 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("��ǰ�ڵ���RC"));
			m_ismall.AddString(_T("�Ϲ��ڵ���RC"));
			m_ismall.AddString(_T("ĳ����RC"));
			m_ismall.AddString(_T("���/���/��Ʈ/��ŸRC"));
			break;
		 case 3 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("��ī/Ʈ��/�����"));
			m_ismall.AddString(_T("�Ϲ��ڵ���"));
			m_ismall.AddString(_T("�����ڵ���"));
			m_ismall.AddString(_T("�ڵ������̼�Ʈ"));
			m_ismall.AddString(_T("�����/����/��Ÿ"));
			break;
	}
	else if(select1 == 3)
		switch(select2){
		case 0 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("�׶��"));
			m_ismall.AddString(_T("�׸�������"));
			m_ismall.AddString(_T("���"));
			m_ismall.AddString(_T("�κ�ī����"));
			m_ismall.AddString(_T("�Ƿη�"));
			m_ismall.AddString(_T("����"));
			break;
		case 1 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("�ܿ�ձ�"));
			m_ismall.AddString(_T("����� ��������"));
			m_ismall.AddString(_T("�ʶ���"));
			m_ismall.AddString(_T("�̹�"));
			m_ismall.AddString(_T("�ٺ�"));
			m_ismall.AddString(_T("�λ��̵� �ƿ�"));
			m_ismall.AddString(_T("����"));
			m_ismall.AddString(_T("�����"));
			m_ismall.AddString(_T("���ŰƼ"));
			break;
        case 2 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("�Ǵ�"));
			m_ismall.AddString(_T("�Ǻ�"));
			m_ismall.AddString(_T("����ũ����Ʈ"));
			m_ismall.AddString(_T("�̴Ͼ���"));
			m_ismall.AddString(_T("�����"));
			m_ismall.AddString(_T("���ǽ�"));
			break;
	}
}

void CItemPage::DrawBMP(LPCTSTR lpszFileName)	//�̹��� �����ֱ�
{
	CDC* pDC = GetDC();//ȭ�� DC�� ��� ��
	CDC MemDC;//�޸� DC
	CBitmap bmp, *pOldBmp;
	BITMAP bm;//��Ʈ�� ������ �����ϴ� ����
	CRect rect;
	CPoint cp;

	//�̹��� ���� �ε�
	bmp.m_hObject = (HBITMAP)LoadImage(NULL, lpszFileName, IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
	if(bmp.m_hObject == NULL) return;
	bmp.GetBitmap(&bm);//�ε��� �̹��� ������ ���¸� ����
	MemDC.CreateCompatibleDC(pDC);//�޸� DC�� ȭ�� DC�� ȣȯ���ֵ��� ����
	pOldBmp = MemDC.SelectObject(&bmp);//�޸𸮿� ����� �̹��� ����

	m_iimage.GetWindowRect(&rect);//���̾�α׿� ��ġ�� ��Ʈ���� ũ�⸦ ��� ��
	cp.x = rect.left;//�̹��� ����� ���� ���� x ��ǥ
	cp.y = rect.top;//�̹��� ����� ���� ���� y ��ǥ 
	ScreenToClient(&cp);//cp�� ������ �ִ� ��ǥ�� ȭ���� ������
	pDC->StretchBlt(cp.x,cp.y,rect.Width(),rect.Height() ,&MemDC,0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);//�̹����� �ش� ��Ʈ�ѷ� ����
	MemDC.SelectObject(pOldBmp);
	ReleaseDC(pDC);//DC ��ȯ
}



void CItemPage::OnBnClickedCancel2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(true);

	CFileDialog sDlg(false, NULL, NULL, OFN_HIDEREADONLY, 0);

	if(sDlg.DoModal() != IDOK) 
		return; 

	CString m_i;

	m_i = sDlg.GetFileName();

	imgname.Format(_T("res\\item\\%s.bmp"),m_i);
	CopyFile(sDlg.GetPathName(), imgname, FALSE);
	AfxMessageBox(_T("�̹����� ����Ǿ����ϴ�."));
	DrawBMP(imgname);
}


BOOL CItemPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_img_setbtn.LoadBitmaps(IDB_BMP_IMAGE_SET, NULL, NULL, NULL);
	m_img_setbtn.SizeToContent();
	m_img_cancelbtn.LoadBitmaps(IDB_BMP_IMAGE_CANCEL, NULL, NULL, NULL);
	m_img_cancelbtn.SizeToContent();
	m_percent_btn.LoadBitmaps(IDB_BMP_PERCENT, NULL, NULL, NULL);
	m_percent_btn.SizeToContent();
	m_okbtn.LoadBitmaps(IDB_BMP_OK, NULL, NULL, NULL);
	m_okbtn.SizeToContent();
	m_clearbtn.LoadBitmaps(IDB_BMP_CLEAR, NULL, NULL, NULL);
	m_clearbtn.SizeToContent();
	m_comsearchbtn.LoadBitmaps(IDB_BMP_SEARCH2, NULL, NULL, NULL);
	m_comsearchbtn.SizeToContent();

	GetDlgItem(IDC_EDIT13)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT14)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);

	m_ilarge.AddString(_T("�Ż���/����"));
	m_ilarge.AddString(_T("����"));
	m_ilarge.AddString(_T("����"));
	m_ilarge.AddString(_T("ĳ���ͺ�"));

	bFirst = TRUE;

	CFont    m_fontTitle;
	LOGFONT  lf; 

	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 17;
	::lstrcpy(lf.lfFaceName, _T("�����ٸ����"));
	m_fontTitle.CreateFontIndirect(&lf);
	GetDlgItem(IDC_STATIC1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC3)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC4)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC5)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC6)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC7)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC8)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC9)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC10)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC11)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_COMBO2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_COMBO3)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_COMBO4)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT7)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT4)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT14)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT5)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_DATETIMEPICKER2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT12)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT15)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT13)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CItemPage::bigmidsmall(void)	//ī�װ� ���ڿ� ��ȯ
{
	if(Big == "�Ż���/����"){
		m_ilarge.SetCurSel(0);
		OnCbnSelchangeCombo2();
		if(Middle == "�Ż���"){
			m_imedium.SetCurSel(0);
			OnCbnSelchangeCombo4();
			if(Small == "ġ�߱�/������")
				m_ismall.SetCurSel(0);
			else if(Small == "���")
				m_ismall.SetCurSel(1);
			else if(Small == "�˰�����/������")
				m_ismall.SetCurSel(2);
			else if(Small == "�Ʊ�ü����/����Ȩ")
				m_ismall.SetCurSel(3);
			else if(Small == "�����/�ٿ/�")
				m_ismall.SetCurSel(4);
		}
		else if(Middle == "����"){
			m_imedium.SetCurSel(1);
			OnCbnSelchangeCombo4();
			if(Small == "������")
				m_ismall.SetCurSel(0);
			else if(Small == "������")
				m_ismall.SetCurSel(1);
			else if(Small == "����/���ҳ���")
				m_ismall.SetCurSel(2);
			else if(Small == "�Ǳ����")
				m_ismall.SetCurSel(3);
			else if(Small == "�ڵ�������")
				m_ismall.SetCurSel(4);
		}
	} 
	
	else if(Big == "����"){
		m_ilarge.SetCurSel(1);
		OnCbnSelchangeCombo2();
		if(Middle == "���ҳ���"){
			m_imedium.SetCurSel(0);
			OnCbnSelchangeCombo4();
			if(Small == "�Ҳ�/�ֹ����")
				m_ismall.SetCurSel(0);
			else if(Small == "��Ʈ����")
				m_ismall.SetCurSel(1);
			else if(Small == "����/û�ҳ���")
				m_ismall.SetCurSel(2);
			else if(Small == "����/��Ÿ����")
				m_ismall.SetCurSel(3);
		}
		else if(Middle == "����"){
			m_imedium.SetCurSel(1);
			OnCbnSelchangeCombo4();
			if(Small == "��������")
				m_ismall.SetCurSel(0);
			else if(Small == "��������")
				m_ismall.SetCurSel(1);
			else if(Small == "�Ʊ�����")
				m_ismall.SetCurSel(2);
			else if(Small == "ĳ���ͺ�������")
				m_ismall.SetCurSel(3);
			else if(Small == "������������")
				m_ismall.SetCurSel(4);
			else if(Small == "�۵���������")
				m_ismall.SetCurSel(5);
		}
		else if(Middle == "�ٹ̱�"){
			m_imedium.SetCurSel(2);
			OnCbnSelchangeCombo4();
			if(Small == "�巹�� �� ��ǰ")
				m_ismall.SetCurSel(0);
			else if(Small == "���/ȭ�����")
				m_ismall.SetCurSel(1);
			else if(Small == "�ڵ���/��ī/��Ÿ")
				m_ismall.SetCurSel(2);
		}
	}
	else if(Big == "����"){
		m_ilarge.SetCurSel(1);
		OnCbnSelchangeCombo2();
		if(Middle == "���ҳ���"){
			m_imedium.SetCurSel(0);
			OnCbnSelchangeCombo4();
			if(Small == "��������")
				m_ismall.SetCurSel(0);
			else if(Small == "ī�����")
				m_ismall.SetCurSel(1);
			else if(Small == "ǰ�ǳ���")
				m_ismall.SetCurSel(2);
			else if(Small == "�ڽ�Ƭ�÷���")
				m_ismall.SetCurSel(3);
			else if(Small == "���/���̳���")
				m_ismall.SetCurSel(4);
			else if(Small == "�ΰ�/��Ÿ����")
				m_ismall.SetCurSel(5);
		}
		else if(Middle == "�׼�"){
			m_imedium.SetCurSel(1);
			OnCbnSelchangeCombo4();
			if(Small == "���ŷκ�Ʈ/Ż��")
				m_ismall.SetCurSel(0);
			else if(Small == "�׼ǹ���")
				m_ismall.SetCurSel(1);
			else if(Small == "�׼��ǱԾ�")
				m_ismall.SetCurSel(2);
		}
		else if(Middle == "����"){
			m_imedium.SetCurSel(2);
			OnCbnSelchangeCombo4();
			if(Small == "��ǰ�ڵ���RC")
				m_ismall.SetCurSel(0);
			else if(Small == "�Ϲ��ڵ���RC")
				m_ismall.SetCurSel(1);
			else if(Small == "ĳ����RC")
				m_ismall.SetCurSel(2);
			else if(Small == "���/���/��Ʈ/��ŸRC")
				m_ismall.SetCurSel(3);
		}
	}
	else if(Big == "ĳ���ͺ�"){
		m_ilarge.SetCurSel(1);
		OnCbnSelchangeCombo2();
		if(Middle == "����ĳ����"){
			m_imedium.SetCurSel(0);
			OnCbnSelchangeCombo4();
			if(Small == "�׶��")
				m_ismall.SetCurSel(0);
			else if(Small == "�׸�������")
				m_ismall.SetCurSel(1);
			else if(Small == "���")
				m_ismall.SetCurSel(2);
			else if(Small == "�κ�ī����")
				m_ismall.SetCurSel(3);
			else if(Small == "�Ƿη�")
				m_ismall.SetCurSel(4);
			else if(Small == "����")
				m_ismall.SetCurSel(5);
		}
		else if(Middle == "����ĳ����"){
			m_imedium.SetCurSel(1);
			OnCbnSelchangeCombo4();
			if(Small == "�ܿ�ձ�")
				m_ismall.SetCurSel(0);
			else if(Small == "����� ��������")
				m_ismall.SetCurSel(1);
			else if(Small == "�ʶ���")
				m_ismall.SetCurSel(2);
			else if(Small == "�̹�")
				m_ismall.SetCurSel(3);
			else if(Small == "�ٺ�")
				m_ismall.SetCurSel(4);
			else if(Small == "�λ��̵�ƿ�")
				m_ismall.SetCurSel(5);
			else if(Small == "����")
				m_ismall.SetCurSel(6);
			else if(Small == "�����")
				m_ismall.SetCurSel(7);
			else if(Small == "���ŰƼ")
				m_ismall.SetCurSel(8);
		}
		else if(Middle == "����ĳ����"){
			m_imedium.SetCurSel(2);
			OnCbnSelchangeCombo4();
			if(Small == "�Ǵ�")
				m_ismall.SetCurSel(0);
			else if(Small == "�Ǻ�")
				m_ismall.SetCurSel(1);
			else if(Small == "����ũ����Ʈ")
				m_ismall.SetCurSel(2);
			else if(Small == "�̴Ͼ���")
				m_ismall.SetCurSel(3);
			else if(Small == "�����")
				m_ismall.SetCurSel(4);
			else if(Small == "���ǽ�")
				m_ismall.SetCurSel(5);
		}
	}
}
#include "ItemPercentDlg.h"
void CItemPage::OnBnClickedPercent()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	CItemPercentDlg pDlg;
	pDlg.DoModal();

	CString setper;
	CString setper1;
	CString editresult;

	GetDlgItemText(IDC_EDIT15,setper);
	setper1 = pDlg.m_percent;
	editresult.Format(_T("%.2f"), _ttof(setper)+_ttof(setper1) * _ttof(setper));	
	m_outprice_Edit.SetWindowTextW(editresult);
}

#include "CompanySearchDlg.h"
void CItemPage::OnBnClickedComSearch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CCompanySearchDlg pDlg;
	pDlg.DoModal();
	m_cname_Edit.SetWindowTextW(pDlg.m_cnameset);
	m_ccode_Edit.SetWindowTextW(pDlg.m_ccodeset);
}


void CItemPage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

		if(bFirst){
		CString img;
		img.Format(_T("res\\NoImage.bmp"));
		DrawBMP(img);
	}

	// �׸��� �޽����� ���ؼ��� CPropertyPage::OnPaint()��(��) ȣ������ ���ʽÿ�.
}


void CItemPage::OnBnClickedImageDelete()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
		CString img;
		img.Format(_T("res\\NoImage.bmp"));
		DrawBMP(img);
}
