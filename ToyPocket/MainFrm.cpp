
// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include "stdafx.h"
#include "ToyPocket.h"

#include "MainFrm.h"
#include "MfcSkinSDI.h"
#include "ItemFormView.h"
#include "ToyPocketView.h"
#include "ExchangeFormView.h"
#include "ReturnFormView.h"
#include "SaleFormView.h"
#include "CompanyFormView.h"
#include "RegisterFormView.h"
#include "HomepageFormView.h"
#include "CalendarManage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CMfcSkinSDI)


BEGIN_MESSAGE_MAP(CMainFrame, CMfcSkinSDI)
	ON_WM_CREATE()
	ON_COMMAND(ID_ITEM, &CMainFrame::OnItem)
	ON_COMMAND(ID_HOME, &CMainFrame::OnHome)
	ON_COMMAND(ID_SALE, &CMainFrame::OnSale)
	ON_COMMAND(ID_COMPANY, &CMainFrame::OnCompany)
	ON_COMMAND(ID_PASSWORD_CHANGE, &CMainFrame::OnPasswordChange)
	ON_UPDATE_COMMAND_UI(ID_COMPANY, &CMainFrame::OnUpdateCompany)
	ON_UPDATE_COMMAND_UI(ID_ITEM, &CMainFrame::OnUpdateItem)
	ON_UPDATE_COMMAND_UI(ID_SALE, &CMainFrame::OnUpdateSale)
	ON_COMMAND(ID_RETURN, &CMainFrame::OnReturn)
	ON_UPDATE_COMMAND_UI(ID_RETURN, &CMainFrame::OnUpdateReturn)
	ON_COMMAND(ID_EXCHANGE, &CMainFrame::OnExchange)
	ON_UPDATE_COMMAND_UI(ID_EXCHANGE, &CMainFrame::OnUpdateExchange)
	ON_WM_ERASEBKGND()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_CALENDER, &CMainFrame::OnCalender)
	ON_UPDATE_COMMAND_UI(ID_PASSWORD_CHANGE, &CMainFrame::OnUpdatePasswordChange)
	ON_COMMAND(ID_PERYN, &CMainFrame::OnPeryn)
	ON_COMMAND(ID_NOTICE, &CMainFrame::OnNotice)
	ON_UPDATE_COMMAND_UI(ID_CALENDER, &CMainFrame::OnUpdateCalender)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	if (CMfcSkinSDI::OnCreate(lpCreateStruct) == -1)
		return -1;
		return 0;
		
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
			sizeof(indicators) / sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	//////////////////////////////////////
	this->SetMainFrmResourceID(IDR_MAINFRAME);
	this->CapMenuBarItems(true);
	this->InitilizeCustomDraw();
	this->tbSetStyle();
	this->ChangeMenuToCustomDraw(this->GetMenu());
	this->borderSetDimension(2, 2, -1, 2);
	this->SetMenuBarBottomMargin(5);
	this->SetCommonBkColor(RGB(255,198,0));//RGB(255,198,0)  //
	this->SetCaptionTextColor(RGB(255,198, 0));
	this->SetSystemBtnColor(RGB(255,198 ,0)); // �ݱ�,�ʱ�ȭ,�ִ�ȭ ����
	this->SetMenuBarHoverColor(RGB(255, 198, 0));
	this->SetMenuBarSelectColor(RGB(255,198, 0));
	this->SetMenuTextColor(RGB(0, 0, 0)); //����ǥ���� �۾� ����
	this->m_wndStatusBar.SetBackgroundColor(RGB(255,198, 0));
	this->borderSetOutlineColor(RGB(255, 198, 0));//�ѿ� �׵θ�
	return 0;

	//���� ��Ų ����. ����������.
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMfcSkinSDI::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	cs.style ^= FWS_ADDTOTITLE;

	
	// â ũ�� ���� ó�� ũ�⸦ ��Ÿ��!!
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE; 
 
	int screenX = GetSystemMetrics(SM_CXSCREEN);  //���� ��ũ�� Xũ��
	int screenY = GetSystemMetrics(SM_CYSCREEN);  //���� ��ũ�� Yũ��
	cs.x = 200;                  //ȭ���� X ù��ǥ                    
	cs.y = 200;                  //ȭ���� Y ù��ǥ           
	cs.cx = 500;//screenX;    //���� ��ũ���� X ũ�⸸ŭ (X��ǥ ������ ���� ũ�⸸ŭ)            
	cs.cy = 700;//screenY;    //���� ��ũ���� Y ũ�⸸ŭ (Y��ǥ ������ ���� ũ�⸸ŭ)   
	



	return TRUE;
}

// CMainFrame ����

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

// CMainFrame �޽��� ó����


void CMainFrame::SwitchView(int nID)
{
	CView* pOldView = GetActiveView();
	CView* pNewView = NULL;

	switch(nID){
		case VIEWID_ITEM_SHEET: pNewView = (CView*)m_pwndItemFormView; break;
		case VIEWID_HOME: pNewView = (CView*)m_pwndHomeFormView; break;
		case VIEWID_EXCHANGE_SHEET: pNewView = (CView*)m_pwndExchangeFormView; break;
		case VIEWID_RETURN_SHEET: pNewView = (CView*)m_pwndReturnFormView; break;
		case VIEWID_SALE_SHEET: pNewView = (CView*)m_pwndSaleFormView; break;
		case VIEWID_COMPANY_SHEET: pNewView = (CView*)m_pwndCompanyFormView; break;
		case VIEWID_REGISTER_SHEET: pNewView = (CView*)m_pwndRegisterFormView; break;
		case VIEWID_HOMEPAGE: pNewView = (CView*)m_pwndHomepageFormView; break;
		case VIEWID_CALENDERMANAGE: pNewView = (CView*)m_pwndCalenderFormView; break;
	}

	if(pNewView){
		if(pOldView == pNewView) return;

		pOldView->ShowWindow(SW_HIDE);

		pNewView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);

		pOldView->SetDlgCtrlID(nID);
		if(pNewView == (CView*)m_pwndSaleFormView){
			CSaleSheet* pSheet = m_pwndSaleFormView->SaleSheet;
			SetActiveView(pNewView); 
			if(m_salecheck == TRUE)
				pSheet->SetActivePage(1);
			else
				pSheet->SetActivePage(0);
			RecalcLayout();
			pSheet->ShowWindow(SW_SHOW);
			pNewView->ShowWindow(SW_SHOW);
		}
		else if(pNewView == (CView*)m_pwndExchangeFormView){
			CExchangeSheet* pSheet = m_pwndExchangeFormView->ExchageSheet;
			SetActiveView(pNewView);
			if(m_excheck == TRUE)
				pSheet->SetActivePage(1);
			else 
				pSheet->SetActivePage(0);
			RecalcLayout();
			pSheet->ShowWindow(SW_SHOW);
			pNewView->ShowWindow(SW_SHOW);
		}
		else if(pNewView == (CView*)m_pwndReturnFormView){
			CReturnSheet* pSheet = m_pwndReturnFormView->ReturnSheet;
			SetActiveView(pNewView);
			if(m_recheck == TRUE)
				pSheet->SetActivePage(1);
			else 
				pSheet->SetActivePage(0);
			RecalcLayout();
			pSheet->ShowWindow(SW_SHOW);
			pNewView->ShowWindow(SW_SHOW);
		}
		else{
		SetActiveView(pNewView);
		RecalcLayout();
		pNewView->ShowWindow(SW_SHOW);
		}
	}
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_pwndItemFormView = new CItemFormView;
	m_pwndHomeFormView = new CToyPocketView;
	m_pwndExchangeFormView = new CExchangeFormView;
	m_pwndReturnFormView = new CReturnFormView;
	m_pwndSaleFormView = new CSaleFormView;
	m_pwndCompanyFormView = new CCompanyFormView;
	m_pwndRegisterFormView = new CRegisterFormView;
	m_pwndHomepageFormView = new CHomepageFormView;
	m_pwndCalenderFormView = new CCalendarManage;

	m_pwndItemFormView->Create(NULL, NULL, WS_CHILD, CFrameWnd::rectDefault, this,VIEWID_ITEM_SHEET,pContext);
	m_pwndHomeFormView->Create(NULL, NULL, WS_CHILD, CFrameWnd::rectDefault, this,VIEWID_HOME,pContext);
	((CView*)m_pwndExchangeFormView)->Create(NULL, NULL, WS_CHILD, CFrameWnd::rectDefault, this,VIEWID_EXCHANGE_SHEET,pContext);
	((CView*)m_pwndReturnFormView)->Create(NULL, NULL, WS_CHILD, CFrameWnd::rectDefault, this,VIEWID_RETURN_SHEET,pContext);
	((CView*)m_pwndSaleFormView)->Create(NULL, NULL, WS_CHILD, CFrameWnd::rectDefault, this,VIEWID_SALE_SHEET,pContext);
	m_pwndCompanyFormView->Create(NULL, NULL, WS_CHILD, CFrameWnd::rectDefault, this,VIEWID_COMPANY_SHEET,pContext);
	m_pwndRegisterFormView->Create(NULL, NULL, WS_CHILD, CFrameWnd::rectDefault, this,VIEWID_REGISTER_SHEET,pContext);
	m_pwndHomepageFormView->Create(NULL, NULL, WS_CHILD, CFrameWnd::rectDefault, this,VIEWID_HOMEPAGE,pContext);
	m_pwndCalenderFormView->Create(NULL, NULL, WS_CHILD, CFrameWnd::rectDefault, this,VIEWID_CALENDERMANAGE,pContext);
	return CFrameWnd::OnCreateClient(lpcs, pContext);
}


void CMainFrame::OnItem()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	SwitchView(VIEWID_ITEM_SHEET);
}

void CMainFrame::OnReturn()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if(g_per == "manager"){
		AfxMessageBox(_T("������ �����ϴ�."), MB_ICONEXCLAMATION);
	}
	else 
		SwitchView(VIEWID_RETURN_SHEET);

}


void CMainFrame::OnExchange()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if(g_per == "manager"){
		AfxMessageBox(_T("������ �����ϴ�."), MB_ICONEXCLAMATION);
	}
	else
		SwitchView(VIEWID_EXCHANGE_SHEET);
}

void CMainFrame::OnHome()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if(!m_bIsCopyTime)//�α����϶��� Ȩȭ�� ���̰� �α����� �ƴ� ���� Ȩ��ư ������ �� �α���ȭ���� ���̰Բ�
		SwitchView(VIEWID_HOME);
	else
		SwitchView(VIEWID_HOMEPAGE);
}


void CMainFrame::OnSale()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if(g_per == "manager"){
		AfxMessageBox(_T("������ �����ϴ�."), MB_ICONEXCLAMATION);
	}
	else 
		SwitchView(VIEWID_SALE_SHEET);
	
}


void CMainFrame::OnCompany()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
		SwitchView(VIEWID_COMPANY_SHEET);
}

#include "PasswordChangeDlg.h"
void CMainFrame::OnPasswordChange()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CPasswordChangeDlg dlg;
	dlg.DoModal();
}


void CMainFrame::OnUpdateCompany(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if(m_bIsCopyTime)
		pCmdUI->Enable(TRUE);
	else{
		AfxMessageBox(_T("�α��� �� �̿밡���մϴ�."), MB_ICONEXCLAMATION);
		 pCmdUI->Enable(FALSE);
	}
}



void CMainFrame::OnUpdateItem(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	
	if(m_bIsCopyTime)
		pCmdUI->Enable(TRUE);
	else{
		AfxMessageBox(_T("�α��� �� �̿밡���մϴ�."), MB_ICONEXCLAMATION);
		 pCmdUI->Enable(FALSE);
	}
	
}

void CMainFrame::OnUpdateSale(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if(m_bIsCopyTime)
		pCmdUI->Enable(TRUE);
	else{
		AfxMessageBox(_T("�α��� �� �̿밡���մϴ�."), MB_ICONEXCLAMATION);
		 pCmdUI->Enable(FALSE);
	}
}


void CMainFrame::OnUpdateReturn(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if(m_bIsCopyTime)
		pCmdUI->Enable(TRUE);
	else{
		AfxMessageBox(_T("�α��� �� �̿밡���մϴ�."), MB_ICONEXCLAMATION);
		 pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnUpdateExchange(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if(m_bIsCopyTime)
		pCmdUI->Enable(TRUE);
	else{
		AfxMessageBox(_T("�α��� �� �̿밡���մϴ�."), MB_ICONEXCLAMATION);
		 pCmdUI->Enable(FALSE);
	}
}


BOOL CMainFrame::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	

	return CFrameWnd::OnEraseBkgnd(pDC);
}


void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	// â ũ�� ����, �۾����� �ӻ��� �Ф�
	// �ӻ��� ���� ����
	if(m_nFirst == 1) {
		lpMMI->ptMinTrackSize.x = 1024; //����
		lpMMI->ptMinTrackSize.y = 768; // ����

		lpMMI->ptMaxTrackSize.x = 1024;
		lpMMI->ptMaxTrackSize.y = 768;
	}
	else if(m_nFirst == 2) {
		lpMMI->ptMinTrackSize.x = 500; //����
		lpMMI->ptMinTrackSize.y = 700; // ����

		lpMMI->ptMaxTrackSize.x = 500;
		lpMMI->ptMaxTrackSize.y = 700;
	}

	CMfcSkinSDI::OnGetMinMaxInfo(lpMMI);
}


void CMainFrame::OnCalender()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	SwitchView(VIEWID_CALENDERMANAGE);
}


void CMainFrame::OnUpdatePasswordChange(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if(m_bIsCopyTime)
		pCmdUI->Enable(TRUE);
	else{
		AfxMessageBox(_T("�α��� �� �̿밡���մϴ�."), MB_ICONEXCLAMATION);
		 pCmdUI->Enable(FALSE);
	}
}

#include "ManagerPermitDlg.h"
void CMainFrame::OnPeryn()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if(g_per == "super"){
		CManagerPermitDlg dlg;
		dlg.DoModal();
	}
	else{
		int ret;
		ret = AfxMessageBox(_T("������ �����ϴ�."), MB_ICONEXCLAMATION);
	}
}

#include "NoticeDlg.h"
void CMainFrame::OnNotice()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if(g_per == "super"){
		CNoticeDlg dlg;
		dlg.DoModal();
	}
	else{
		int ret;
		ret = AfxMessageBox(_T("������ �����ϴ�."), MB_ICONEXCLAMATION);
	}
}


BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	 if (pMsg->message == WM_KEYDOWN)
    {
        switch ( pMsg->wParam )
        {  
        case VK_ESCAPE:
			int ret;
			ret = AfxMessageBox(_T("�α׾ƿ� �Ͻðڽ��ϱ�?"), MB_YESNO|MB_ICONSTOP);
			if(ret == IDYES){
				SwitchView(VIEWID_HOME);
				m_bIsCopyTime=false;
				m_nFirst = 2;
				CRect rect;
				GetWindowRect(&rect);
				MoveWindow(rect.Width()/4, rect.Height()/6, 100, 100);

				break;
			}
		break;
        }
    }
	return CMfcSkinSDI::PreTranslateMessage(pMsg);
}


void CMainFrame::OnUpdateCalender(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if(m_bIsCopyTime)
		pCmdUI->Enable(TRUE);
	else{
		AfxMessageBox(_T("�α��� �� �̿밡���մϴ�."), MB_ICONEXCLAMATION);
		 pCmdUI->Enable(FALSE);
	}
}
