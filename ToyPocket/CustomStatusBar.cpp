
// CustomStatusBar.cpp : implementation file
//

#include "stdafx.h"
#include "CustomStatusBar.h"

// CCustomStatusBar

IMPLEMENT_DYNAMIC(CCustomStatusBar, CStatusBar)

CCustomStatusBar::CCustomStatusBar()
{
     m_statusTextColor=RGB(0,128,0);//맨 밑 NUM,CAPS, 준비 상태표시줄 글씨 색상
	 m_statusBackColor=RGB(255,228,0); // 맨 밑 상태 표시줄 색상 지정

	 //the current system font used to draw status bar text
	  NONCLIENTMETRICS ncm;
	  ncm.cbSize=sizeof(NONCLIENTMETRICS);
	  ::SystemParametersInfo(SPI_GETNONCLIENTMETRICS,ncm.cbSize,&ncm,0);
	  m_textFont.CreateFontIndirect(&ncm.lfStatusFont);
}

CCustomStatusBar::~CCustomStatusBar()
{
}

BEGIN_MESSAGE_MAP(CCustomStatusBar, CStatusBar)
	ON_WM_PAINT()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()

// CCustomStatusBar message handlers

void CCustomStatusBar::OnPaint()
{
	int parts=this->GetStatusBarCtrl().GetParts(0,0);//how many panes do we have
	CPaintDC dc(this); // device context for painting
	COLORREF oldClr=dc.SetTextColor(m_statusTextColor);
	dc.SetBkMode(TRANSPARENT);
	CFont* oldFont=dc.SelectObject(&m_textFont);
	CBrush br(m_statusBackColor);//create the background brush

	CRect rect;
	this->GetClientRect(&rect);
	dc.FillRect(&rect,&br);//paint the whole status bar first
	
    //draw the sizing gripper
	UINT gheight=rect.Height()/2;
	POINT gripper[3];
	gripper[0].x=rect.right-1;gripper[0].y=rect.bottom-1;
	gripper[1].x=rect.right-gheight;gripper[1].y=rect.bottom-1;
	gripper[2].x=rect.right-1;gripper[2].y=rect.bottom-gheight;
	dc.BeginPath();
	dc.Polyline(gripper,3);
	dc.EndPath();
	br.DeleteObject(); 
	br.CreateSolidBrush(m_statusTextColor);
	CBrush* oldBrush=dc.SelectObject(&br);
	dc.FillPath();
	dc.SelectObject(oldBrush);
 
	//now draw the pane text
	for(int i=0;i<parts;i++)
	{
		this->GetItemRect(i,&rect);
		this->DrawPaneContent(i,&dc,rect);
	}
	
	dc.SelectObject(oldFont);
	dc.SetTextColor(oldClr);
}

void CCustomStatusBar::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if(lpDrawItemStruct->hwndItem==this->GetSafeHwnd())
	{
	  CDC* hDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	  CFont* oldfont=hDC->SelectObject(&m_textFont);
	  hDC->FillSolidRect(&lpDrawItemStruct->rcItem,m_statusBackColor);
	  
	  COLORREF oldclr=hDC->SetTextColor(m_statusTextColor);
	  /////////////////
	  this->DrawPaneContent(lpDrawItemStruct->itemID,hDC,lpDrawItemStruct->rcItem);
	  ///////////////////
	  hDC->SelectObject(oldfont);
	  hDC->SetTextColor(oldclr);
	  //return;
	}
	CStatusBar::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

/***
Draws the contents of a given pane, the content of a pane might be a informative text or an indicator
@parameter pane - the position of the pane
@parameter hdc - the device context used for drawing
***/
void CCustomStatusBar::DrawPaneContent(UINT pane,CDC* hdc,RECT rect)
{
    CBrush br(m_statusBackColor);//create teh background brush
	CString paneText;
	this->GetPaneText(pane,paneText);

	hdc->FillRect(&rect,&br);//paint the background of the current pane

	rect.left+=2;//the left margin offset of the pane text we are about to draw
	SHORT state=0;
	if(this->GetItemID(pane)==ID_INDICATOR_CAPS)
	{//for the CAPSLOCK indicator
		state=::GetKeyState(VK_CAPITAL);//get the toggle state of the button
	    //if the button is toggled ON(that is CAP is on) draw the CAP indicator text
		(state&1)?hdc->DrawText(paneText.GetBuffer(paneText.GetLength()),-1,&rect,DT_LEFT|DT_SINGLELINE|DT_VCENTER):
			  hdc->DrawText(_T(" "),-1,&rect,DT_LEFT|DT_SINGLELINE|DT_VCENTER);
	}
	else if(this->GetItemID(pane)== ID_INDICATOR_NUM)
	{//for NUMSLOCK indicator
		state=::GetKeyState(VK_NUMLOCK);//get the toggle state of the button
	    //if the button is toggled ON(that is NUMS is on) draw the NUM indicator text
		(state&1)?hdc->DrawText(paneText.GetBuffer(paneText.GetLength()),-1,&rect,DT_LEFT|DT_SINGLELINE|DT_VCENTER):
			  hdc->DrawText(_T(" "),-1,&rect,DT_LEFT|DT_SINGLELINE|DT_VCENTER);
	}
	else if(this->GetItemID(pane)==ID_INDICATOR_SCRL)
	{//for SCRLLOCK indicator
		state=::GetKeyState(VK_SCROLL);//get the toggle state of the button
	    //if the button is toggled ON(that is SCRL is on) draw the SCRL indicator text
		(state&1)?hdc->DrawText(paneText.GetBuffer(paneText.GetLength()),-1,&rect,DT_LEFT|DT_SINGLELINE|DT_VCENTER):
			  hdc->DrawText(_T(" "),-1,&rect,DT_LEFT|DT_SINGLELINE|DT_VCENTER);
	}
	else
	{
	    //otherwise draw the pane text
		hdc->DrawText(paneText.GetBuffer(paneText.GetLength()),-1,&rect,DT_LEFT|DT_SINGLELINE|DT_VCENTER);
	}
}

void CCustomStatusBar::SetBackgroundColor(COLORREF clr)
{
	m_statusBackColor=clr;
}

void CCustomStatusBar::SetTextColor(COLORREF clr)
{
	m_statusTextColor=clr;
}

COLORREF CCustomStatusBar::GetBackgroundColor()
{
	return m_statusBackColor;
}