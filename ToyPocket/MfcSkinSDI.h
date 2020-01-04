// MfcSkinSDI.h : interface of the CMfcSkinSDI class
//

#pragma once

#define SYSMENU_CLOSE	 100
#define SYSMENU_MAXIMIZE 101
#define SYSMENU_MINIMIZE 102
#define HTCAPPICON       51
#define TIMER_ID         1111
#include "CustomStatusBar.h"
#include <vector>
using namespace std;

class CMfcSkinSDI : public CFrameWnd
{
	
protected: // create from serialization only
	CMfcSkinSDI();
	DECLARE_DYNCREATE(CMfcSkinSDI)

// Attributes
protected:
COLORREF          m_tbBackColor,m_tbGripperColor,m_borderColor,m_borderOutlineColor,m_captionBackColor,m_captionTextColor;
COLORREF          m_systemBtnColor,m_systemBtnHighlightColor,m_systemBtnHighlightBkColor;
COLORREF          m_menuBarBkColor,m_menuHoverColor,m_menuSelectColor,m_menuTextColor;
CSize             m_sysMenuBtnSize,m_closeBtnOffset,m_maximzeBtnOffset,m_minimizeBtnOffset;
UINT              m_tbGripperWidth,m_captionHeight,m_highlightedSysMenuBtn,m_menuItemCount,m_menuBarHeight;
UINT_PTR          m_timerID;
UINT              m_mainFrmResourceID;
CRect             m_borderWidth;
CRect             m_updateRect,m_menuRect;
CRgn              m_wRgn;
BOOL              m_borderBlendStatusBar,m_enableBorderOutline,m_isCustomCaptionText,m_menuBtnMarked,m_menuItemCap,m_drawingMenuManually;
CRect             m_captionRects[4];//0-captionbarboundingrect 1- appiconrect 2- minimizebuttonrect  3-closebuttonrect
CString           m_captionText;
CFont             m_captionTextFont,m_menuTextFont;
CMenu             m_sysPopupMenu;
CToolTipCtrl      m_sysMenuTooltipClose,m_sysMenuTooltipMax,m_sysMenuTooltipMin;
TOOLINFO          m_toolItemClose,m_toolItemMax,m_toolItemMin;
vector <CString*> m_menuItemText;
vector <CRect*>   m_menuItemRect;
// Operations
public:
void tbSetBackColor(COLORREF bc);
void tbSetGripperWidth(UINT width);
void tbSetStyle();
void DrawBorder(CDC* hdc);
void borderSetDimension(int l,int r,int t,int b);
void borderSetColor(COLORREF clr);
void borderSetOutlineColor(COLORREF clr);
void borderEnableOutline(BOOL cmd);
void borderBlendStatusBar(BOOL cmd);
void DrawCaptionBar(CDC* hdc);
void DrawSystemButtons(CDC* hdc);
void SetSystemBtnColor(COLORREF clr);
void SetSystemBtnHighlightColor(COLORREF clr);
void SetSystemBtnHighlightBkColor(COLORREF clr);
void SetCaptionTextColor(COLORREF clr);
void SetCaptionBackColor(COLORREF clr);
void SetCaptionText(CString* str);
void InitilizeCustomDraw();
void HighlightSystemMenuButton(UINT nType,CDC* hdc);
void ChangeMenuToCustomDraw(CMenu* menu);
void DrawCustomMenuBar(CDC* hdc);
void SetMenuBarBottomMargin(UINT bMargin);
void SetMenuBarBkColor(COLORREF clr);
void SetMenuBarHoverColor(COLORREF clr);
void SetMenuBarSelectColor(COLORREF clr);
void SetMenuTextColor(COLORREF clr);
void CapMenuBarItems(BOOL cmd=true);
void SetMainFrmResourceID(UINT Id);
void SetCommonBkColor(COLORREF clr);
void AdjustWindowRgn();

private:
void tbSetGripperColor();
// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMfcSkinSDI();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CCustomStatusBar  m_wndStatusBar;
	CToolBar          m_wndToolBar;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysMenuMove();
	afx_msg void OnSysMenuSize();
	afx_msg void OnSysMenuRestore();
	afx_msg void OnSysMenuMaximize();
	afx_msg void OnSysMenuMinimize();
	afx_msg void OnSysMenuClose();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	virtual void RecalcLayout(BOOL bNotify = TRUE);
public:
	afx_msg void OnNcPaint();
public:
	afx_msg BOOL OnNcActivate(BOOL bActive);
public:
	afx_msg void OnPaint();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
public:
	afx_msg LRESULT OnNcHitTest(CPoint point);
public:
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
public:
	afx_msg void OnNcRButtonUp(UINT nHitTest, CPoint point);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
public:
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
public:
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
};


