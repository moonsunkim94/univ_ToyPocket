
// MainFrm.h : CMainFrame 클래스의 인터페이스
//

#pragma once
#include "MfcSkinSDI.h"

#include "ItemFormView.h"
#include "ToyPocketView.h"

#define VIEWID_DEFALULT AFX_IDW_PANE_FIRST
#define VIEWID_ITEM_SHEET AFX_IDW_PANE_FIRST + 1
#define VIEWID_HOME AFX_IDW_PANE_FIRST + 2
#define VIEWID_EXCHANGE_SHEET AFX_IDW_PANE_FIRST + 3
#define VIEWID_RETURN_SHEET AFX_IDW_PANE_FIRST + 4
#define VIEWID_SALE_SHEET AFX_IDW_PANE_FIRST + 5
#define VIEWID_COMPANY_SHEET AFX_IDW_PANE_FIRST + 6
#define VIEWID_REGISTER_SHEET AFX_IDW_PANE_FIRST + 7
#define VIEWID_HOMEPAGE AFX_IDW_PANE_FIRST + 8
#define VIEWID_CALENDERMANAGE AFX_IDW_PANE_FIRST + 9

class CReturnFormView;
class CSaleFormView;
class CExchangeFormView;

class CMainFrame : public CMfcSkinSDI
{
	
protected: // serialization에서만 만들어집니다.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:
	CView* m_pwndItemFormView;
	CView* m_pwndHomeFormView;
	CExchangeFormView* m_pwndExchangeFormView;//
	CReturnFormView* m_pwndReturnFormView;//
	CSaleFormView* m_pwndSaleFormView;//
	CView* m_pwndCompanyFormView;
	CView* m_pwndRegisterFormView;
	CView* m_pwndHomepageFormView;
	CView* m_pwndCalenderFormView;
// 작업입니다.
public:
	int m_nFirst;

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	void SwitchView(int nID);
	afx_msg void OnItem();
	afx_msg void OnHome();
	afx_msg void OnSale();
	afx_msg void OnCompany();
	afx_msg void OnPasswordChange();
	afx_msg void OnUpdateCompany(CCmdUI *pCmdUI);
	afx_msg void OnUpdateItem(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSale(CCmdUI *pCmdUI);
	afx_msg void OnReturn();
	afx_msg void OnUpdateReturn(CCmdUI *pCmdUI);
	afx_msg void OnExchange();
	afx_msg void OnUpdateExchange(CCmdUI *pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnCalender();
	afx_msg void OnUpdatePasswordChange(CCmdUI *pCmdUI);
	afx_msg void OnPeryn();
	afx_msg void OnNotice();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnUpdateCalender(CCmdUI *pCmdUI);
};


