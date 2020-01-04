
// MfcSkinSDI.cpp : implementation of the CMfcSkinSDI class

#include "stdafx.h"
#include "MfcSkinSDI.h"
#include "windows.h"

#include "math.h" //필수선언

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMfcSkinSDI

IMPLEMENT_DYNCREATE(CMfcSkinSDI, CFrameWnd)

BEGIN_MESSAGE_MAP(CMfcSkinSDI, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_NCPAINT()
	ON_WM_NCACTIVATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_NCLBUTTONUP()
	ON_WM_NCHITTEST()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCRBUTTONUP()
	ON_WM_TIMER()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(AFX_IDS_SCMOVE,CMfcSkinSDI::OnSysMenuMove)
	ON_COMMAND(AFX_IDS_SCRESTORE,CMfcSkinSDI::OnSysMenuRestore)
	ON_COMMAND(AFX_IDS_SCSIZE,CMfcSkinSDI::OnSysMenuSize)
	ON_COMMAND(AFX_IDS_SCMAXIMIZE,CMfcSkinSDI::OnSysMenuMaximize)
	ON_COMMAND(AFX_IDS_SCMINIMIZE,CMfcSkinSDI::OnSysMenuMinimize)
	ON_COMMAND(AFX_IDS_SCCLOSE,CMfcSkinSDI::OnSysMenuClose)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMfcSkinSDI construction/destruction

CMfcSkinSDI::CMfcSkinSDI() //여기서 색 수정하시면 됩니다!!
{
	m_menuBarBkColor=m_captionBackColor=m_borderColor=m_tbBackColor=RGB(255,228,0);//제목표시줄&테두리 색
    m_captionTextColor=RGB(0,0,0);//제목표시줄 글씨 색상 지정
	tbSetGripperColor();
	m_tbGripperWidth=7;
	m_borderBlendStatusBar=true;
	m_borderWidth=CRect(::GetSystemMetrics(SM_CXSIZEFRAME),::GetSystemMetrics(SM_CYSIZEFRAME),::GetSystemMetrics(SM_CXSIZEFRAME),::GetSystemMetrics(SM_CYSIZEFRAME));
    m_borderOutlineColor=RGB(255,198,0);// 겉에 사각형 테두리 색 지정
	m_enableBorderOutline=true;
	m_borderBlendStatusBar=true;
	m_captionHeight=::GetSystemMetrics(SM_CYCAPTION);
	m_captionText.Empty();
	m_drawingMenuManually=m_isCustomCaptionText=false;
	
	NONCLIENTMETRICS ncm;
	ncm.cbSize=sizeof(NONCLIENTMETRICS);
	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS,ncm.cbSize,&ncm,0);
	m_captionTextFont.CreateFontIndirect(&ncm.lfCaptionFont);
	//////
	m_menuTextFont.CreateFontIndirect(&ncm.lfMenuFont);
	///////////////////
	m_systemBtnColor=RGB(255,255,255); //최소화, 최대화,닫기버튼 색상 지정
	m_systemBtnHighlightBkColor=RGB(240,240,240);//마우스가 최소화,최대화,닫기버튼영역 안에 갖다놓으면 바뀌는 배경 색상 지정
	m_systemBtnHighlightColor=RGB(0,0,0); //마우스가 최소화,최대화,닫기버튼영역 안에 갖다놓으면 바뀌는 버튼 색상 지정
	m_closeBtnOffset.cx=7; m_closeBtnOffset.cy=7;
	m_maximzeBtnOffset.cx=5;  m_maximzeBtnOffset.cy=5;
	m_minimizeBtnOffset.cx=5; m_minimizeBtnOffset.cy=5;
	////////////////
	m_timerID=0;
	m_menuBtnMarked=false;
	m_bAutoMenuEnable=false;//this is required to make the EnableMenuItem() function work
	m_menuItemCount=0;
	m_menuBarHeight=::GetSystemMetrics(SM_CYMENU);
	m_menuHoverColor=RGB(255,198,0);
	m_menuSelectColor=RGB(0,255,0);
	m_menuTextColor=RGB(0,255,255);
	m_menuItemCap=false;
	m_updateRect.SetRectEmpty();
	////////////
	m_mainFrmResourceID=128;
}

CMfcSkinSDI::~CMfcSkinSDI()
{
	//remove allocated memory to avoid memory leads
	if(!m_menuItemRect.empty())
	{
		for(vector<CRect*>::iterator it=m_menuItemRect.begin();it!=m_menuItemRect.end();++it)
		{
            CRect* rc=(CRect*)*it;
			delete rc;
		}
		m_menuItemRect.clear();
	}
	/////
	if(!m_menuItemText.empty())
	{
		for(vector<CString*>::iterator it=m_menuItemText.begin();it!=m_menuItemText.end();++it)
		{
            CString* str=(CString*)*it;
			delete str;
		}
		m_menuItemText.clear();
	}
}


int CMfcSkinSDI::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

BOOL CMfcSkinSDI::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


// CMfcSkinSDI diagnostics

#ifdef _DEBUG
void CMfcSkinSDI::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMfcSkinSDI::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMfcSkinSDI message handlers

/*************************THIS BLOCK HANDLES TOOLBAR CUSTOMIZATION*****************************/
BOOL CMfcSkinSDI::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{

    if(wParam == (UINT)m_wndToolBar.GetDlgCtrlID())
    {
	    CBrush br(this->m_tbBackColor);
	    CRect rect;
		CControlBar* bar=NULL;
	    //////////
	    if(this->m_wndToolBar.GetSafeHwnd()!=NULL)
	     bar=(CControlBar*)this->m_wndToolBar.GetParent();//get parent of the toolbar
	
	    if(bar!=NULL && bar->m_hWnd!=this->m_hWnd){//if it has a parent and it is not the mainframe
		CRect rctb,rc;
        bar->GetWindowRect(&rc);//get the parent's dimension
		m_wndToolBar.GetWindowRect(&rctb);//get the toolbar's dimension
		////////////////////////////
		//draw if there is a space between the toolbar and the control bar with the background color
		BOOL dragH=(rctb.left>rc.left)?true:false;//test to see if tb is draged horizontally
		UINT dragSpace=0;
		if(dragH)
		    dragSpace=abs(rctb.left-rc.left);
		///////
		this->ScreenToClient(&rc);
        this->ScreenToClient(&rctb);
		//////////////////////////////
		if(dragH){
		CRect space;
		space.CopyRect(&rc);
		////////
		space.right=dragSpace;
		////////
        CDC* dc=bar->GetWindowDC();
		dc->FillRect(&space,&br);
		}
		/////////////////////////////////////////////////
		if((m_wndToolBar.GetBarStyle() & CBRS_GRIPPER)&& rc.Width()>rc.Height())
		{//if we have to draw a gripper
		   CDC* dc=bar->GetWindowDC();
		   CRect gripRect;
		   gripRect.left=dragSpace;
		   gripRect.top=rctb.top;
		   gripRect.bottom=gripRect.top+rctb.Height();
		   gripRect.right=gripRect.left+m_tbGripperWidth;
           dc->FillRect(&gripRect,&br);
           
		   gripRect.top+=rctb.Height()/6;
		   gripRect.bottom-=rctb.Height()/6;
		   gripRect.left+=1;
		   gripRect.right=gripRect.left+(m_tbGripperWidth/2);
		   dc->Draw3dRect(&gripRect,RGB(0,0,0),RGB(128,128,128));
		}
		////////////////////////////////////////////////
		}
	//draw the toolbar background with our custom color
    m_wndToolBar.GetClientRect(&rect);
	HBRUSH hbr=(HBRUSH)br.GetSafeHandle();
    LPNMTBCUSTOMDRAW lpNMCustomDraw = (LPNMTBCUSTOMDRAW) lParam;
    FillRect(lpNMCustomDraw->nmcd.hdc, rect, hbr);
    }

	return CFrameWnd::OnNotify(wParam, lParam, pResult);
}

/***
Used to position the control bars in our application, after calling  the default, we set the size of 
the toolbar to that of its parent if it has a parent other than the mainframe window
***/
void CMfcSkinSDI::RecalcLayout(BOOL bNotify)
{
	CFrameWnd::RecalcLayout(bNotify);

	if(this->m_wndToolBar.GetSafeHwnd()!=NULL && this->m_wndToolBar.IsVisible())
	{
	CControlBar* bar=NULL;
	bar=(CControlBar*)this->m_wndToolBar.GetParent();//get parent of the toolbar
	
	if(bar!=NULL && bar->m_hWnd!=this->m_hWnd)
	{//if it has a parent and it is not the mainframe
		CRect rctb,rc;
		bar->GetWindowRect(&rc);//get the parent's dimension
		m_wndToolBar.GetWindowRect(&rctb);//get the toolbar's dimension
		////////////////////////////
		this->ScreenToClient(&rc);
        this->ScreenToClient(&rctb);
		//////////////////////////////
		this->tbSetStyle();
		////////
		if(rc.Width()>rc.Height()){//if aligned horizontally
	        //now set the width of the toolbar equal to the parent
			m_wndToolBar.SetWindowPos(&wndTop,rctb.left,rctb.top,rc.Width()+10,rctb.Height(),SWP_SHOWWINDOW|SWP_NOMOVE);
		}
		else if(rc.Width()<rc.Height()){//if aligned vertically
            //now set the height of the toolbar equal to the parent
	        m_wndToolBar.SetWindowPos(&wndTop,rctb.left,rctb.top,rctb.Width(),rc.Height(),SWP_SHOWWINDOW|SWP_NOMOVE);
		}
	}//end of if(bar!=NULL && bar->m_hWnd!=this->m_hWnd)
	}
}

/***
Set the background color of the toolbar
@parameter bc - the color to use for the toolbar background
***/
void CMfcSkinSDI::tbSetBackColor(COLORREF bc)
{
    m_tbBackColor=bc;
}

/***
Set the gripper's color which will invert the color of the toolbar background color
Not used currently
***/
void CMfcSkinSDI::tbSetGripperColor()
{
	//invert the background color to get the gripper color
	m_tbGripperColor=RGB((255-GetRValue(m_tbBackColor)),(255-GetGValue(m_tbBackColor)),(255-GetBValue(m_tbBackColor)));
}

/***
Set the size of the toolbar's gripper width,only apply if CBRS_GRIPPER style is set during toolbar creation
@parameter width - size to set
***/

void CMfcSkinSDI::tbSetGripperWidth(UINT width)
{
    m_tbGripperWidth=width;
}

/***
Set the toolbar style so that it will not have a border around it
***/
void CMfcSkinSDI::tbSetStyle()
{
    CControlBar* bar=NULL;
	//////////
	if(this->m_wndToolBar.GetSafeHwnd()!=NULL)
	bar=(CControlBar*)this->m_wndToolBar.GetParent();//get parent of the toolbar
	
	if(bar!=NULL && bar->m_hWnd!=this->m_hWnd){//if it has a parent and it is not the mainframe
		DWORD style=bar->GetBarStyle();
		style&=~CBRS_BORDER_TOP&~CBRS_BORDER_RIGHT&~CBRS_BORDER_LEFT&~CBRS_BORDER_BOTTOM;
		bar->SetBarStyle(style);//set the controlbar's style to avoid borders(the controlbar is the parent of the toolbar in this case)
		
		style=m_wndToolBar.GetBarStyle();
		style&=~CBRS_BORDER_RIGHT&~CBRS_BORDER_LEFT;
		m_wndToolBar.SetBarStyle(style);//set the toolbar style to avoid borders
		m_wndToolBar.SetBorders();
	}
}
/**************************END OF TOOLBAR CUSTOMIZATION BLOCK******************************/

/**************************CUSTOM BORDER DRAWING BLOCK*************************************/
/***
Draw our custom border by using the values from the m_borderWidth
@parameter hdc - the device contex used to draw the border, this is the windowsDC of the main frame
                 window and is sent from the onncpaint() function
***/
void CMfcSkinSDI::DrawBorder(CDC* hdc)
{
	CRect statusRect;
	this->m_wndStatusBar.GetWindowRect(&statusRect);
	CBrush br(m_borderColor);
	CRect rect,rc;  
	this->GetWindowRect(&rc);
	//draw the top border
	rect.top=0;
	rect.bottom=m_borderWidth.top;
	rect.left=m_borderWidth.left;
	rect.right=rect.left+rc.Width()-(m_borderWidth.left+m_borderWidth.right);
	hdc->FillRect(&rect,&br);
	////////////////////
	int defaultFX=::GetSystemMetrics(SM_CXSIZEFRAME);
	//draw the left border
	rect.top=0;
	m_borderBlendStatusBar?rect.bottom=(rc.Height()-statusRect.Height()-m_borderWidth.bottom+1):rect.bottom=rc.Height();
	(defaultFX-m_borderWidth.left>0)?rect.left=(defaultFX-m_borderWidth.left):rect.left=0;
    rect.right=rect.left+m_borderWidth.left;
	hdc->FillRect(&rect,&br);
	/////////////////////
	//draw the right border
	rect.top=0;
	m_borderBlendStatusBar?rect.bottom=(rc.Height()-statusRect.Height()-m_borderWidth.bottom+1):rect.bottom=rc.Height();
	(defaultFX-m_borderWidth.right>0)?rect.left=rc.Width()-defaultFX:rect.left=rc.Width()-m_borderWidth.right;
    rect.right=rect.left+m_borderWidth.right;
	hdc->FillRect(&rect,&br);
	//////////////////////////////////////
	//if blend with status bar is set and draw the border surrounding the status bar
	//with the statusbar color
	CBrush sbBr(m_wndStatusBar.GetBackgroundColor());
	if(m_borderBlendStatusBar)
	{
	//left blended border
	rect.top=rc.Height()-statusRect.Height()-m_borderWidth.bottom+1;
	rect.bottom=rc.Height();
	(defaultFX-m_borderWidth.left>0)?rect.left=(defaultFX-m_borderWidth.left):rect.left=0;
    rect.right=rect.left+m_borderWidth.left;
	hdc->FillRect(&rect,&sbBr);
	//right blended border
    rect.top=rc.Height()-statusRect.Height()-m_borderWidth.bottom+1;
	rect.bottom=rc.Height();
	(defaultFX-m_borderWidth.right>0)?rect.left=rc.Width()-defaultFX:rect.left=rc.Width()-m_borderWidth.right;
    rect.right=rect.left+m_borderWidth.right;
	hdc->FillRect(&rect,&sbBr);
	}
	//draw the bottom border
	rect.top=rc.Height()-m_borderWidth.bottom;
	rect.bottom=rect.top+m_borderWidth.bottom;
	rect.left=m_borderWidth.left;
	rect.right=rect.left+rc.Width()-(m_borderWidth.left+m_borderWidth.right);
	m_borderBlendStatusBar?hdc->FillRect(&rect,&sbBr):hdc->FillRect(&rect,&br);
	//////////////////////////////////////
	//if outline is enabled draw the border out line
	if(m_enableBorderOutline)
	{
    rect.top=0;
	rect.bottom=rc.Height();
	(defaultFX-m_borderWidth.left>0)?rect.left=(defaultFX-m_borderWidth.left):rect.left=0;
	(defaultFX-m_borderWidth.right>0)?rect.right=(rc.Width()-(defaultFX-m_borderWidth.right)):rect.right=rc.Width();
	hdc->Draw3dRect(&rect,m_borderOutlineColor,m_borderOutlineColor);
	}
}
/***
Set the X or Y dimension of our borders
@parameter l - the horizontal width of the left border
@parameter r - the horizontal width of the right border
@parameter t - the vertical height of the top border
@parameter l - the vertical height of the bottom border
if @parameter is -1 then the default value is used
***/
void CMfcSkinSDI::borderSetDimension(int l,int r,int t,int b)
{
	l>=0?m_borderWidth.left=l:0;
	r>=0?m_borderWidth.right=r:0;
	t>=0?m_borderWidth.top=t:0;
	b>=0?m_borderWidth.bottom=b:0;
}
/***
Set the color of the borders
***/
void CMfcSkinSDI::borderSetColor(COLORREF clr)
{
	m_borderColor=clr;
}
/***
Set the color of the border outline used to draw the outline rectanlge around the window if border
out line is enabled
@parameter clr - the color used to draw the outline border
***/
void CMfcSkinSDI::borderSetOutlineColor(COLORREF clr)
{
	m_borderOutlineColor=clr;	
}
/***
Set the color of the border outline used to draw the outline rectanlge around the window if border
out line is enabled
@parameter cmd - "true" to enable border outline otherwise "false"
***/
void CMfcSkinSDI::borderEnableOutline(BOOL cmd)
{
	m_enableBorderOutline=cmd;
}

/***
Set whether the border around the status bar should blend with the color of the status bar
@parameter cmd - True to enable
***/
void CMfcSkinSDI::borderBlendStatusBar(BOOL cmd)
{
    m_borderBlendStatusBar=cmd;
}
/*************************END OF BORDER DRAWING********************************************/

/*************************CAPTION BAR CUSTOM DRAWING BLOCK*********************************/
/***
Draw our custom captionbar
@parameter hdc - the device contex used to draw the border, this is the windowsDC of the main frame
                 window and is sent from the onncpaint() function
***/
void CMfcSkinSDI::DrawCaptionBar(CDC* hdc)
{
	CDC memdc;
	memdc.CreateCompatibleDC(hdc);
	CBitmap bmap;
	CRect rc;
	this->GetWindowRect(&rc);
	bmap.CreateDiscardableBitmap(hdc,rc.Width(),rc.Height());
	CBitmap* oldbm=memdc.SelectObject(&bmap);
	CBrush backGgnBrush(m_captionBackColor);
	////////////
	//exclude the area occupied by the system button from drawing
    CRect btnrect,newrect;
	btnrect.UnionRect(&m_captionRects[2],0);
	btnrect.UnionRect(&btnrect,&m_captionRects[3]);//4
	newrect.SubtractRect(m_captionRects[0],btnrect);//0
	///////////
	memdc.FillRect(&newrect,&backGgnBrush);//paint the background
	//제목표시줄에 앱아이콘을 그립니다.
	int oldmode=memdc.SetMapMode(MM_TEXT);
	HICON icon=::AfxGetApp()->LoadIcon(m_mainFrmResourceID);
	::DrawIconEx(memdc.m_hDC,m_captionRects[1].left,m_captionRects[1].top+2,icon,m_captionRects[1].Width(),m_captionRects[1].Height(),0,NULL,DI_NORMAL);
	memdc.SetMapMode(oldmode);

	//제목표시줄 부분 중 앱 제목부분을 그립니다.
	memdc.SetBkMode(TRANSPARENT);
	memdc.SetTextColor(m_captionTextColor);
	CFont* oldfont=memdc.SelectObject(&this->m_captionTextFont);
	if(!m_isCustomCaptionText)
		this->GetWindowText(m_captionText);
	memdc.TextOut(m_captionRects[1].right+4,m_captionRects[0].top+2,m_captionText.GetBuffer(m_captionText.GetLength()));
	memdc.SelectObject(oldfont);
	hdc->BitBlt(m_captionRects[0].left,m_captionRects[0].top,m_captionRects[0].Width(),m_captionRects[0].Height(),
		        &memdc,m_captionRects[0].left,m_captionRects[0].top,SRCCOPY);
	memdc.SelectObject(oldbm);
	bmap.DeleteObject();

	DrawSystemButtons(hdc);
}
/*
시스템 버튼들을 그립니다(close,minimize,maximize)
*/
void CMfcSkinSDI::DrawSystemButtons(CDC* hdc)
{ // 닫기,최소화,최대화버튼 새로 그리기
    CRect rcb;
	CRect btnrect;
	CBrush br(m_captionBackColor);
	btnrect.UnionRect(&m_captionRects[2],0);
	btnrect.UnionRect(&btnrect,&m_captionRects[3]);
	hdc->FillRect(&btnrect,&br);
	
	// 닫기 버튼 그리기
	rcb.CopyRect(&m_captionRects[3]);
	rcb.DeflateRect(m_closeBtnOffset.cx,m_closeBtnOffset.cy);
	CPen penb(PS_SOLID,2,m_systemBtnColor);
	CPen* oldpen=hdc->SelectObject(&penb);
	hdc->MoveTo(rcb.left,rcb.top);
	hdc->LineTo(rcb.right,rcb.bottom);
	hdc->MoveTo(rcb.left,rcb.bottom);
	hdc->LineTo(rcb.right,rcb.top);
	hdc->SelectObject(oldpen);

	CBrush brM(m_systemBtnColor);

	//최소화 버튼 그리기
	rcb.CopyRect(&m_captionRects[2]);
    rcb.DeflateRect(m_minimizeBtnOffset.cx,m_minimizeBtnOffset.cy);
    rcb.top+=(rcb.Height()/2);rcb.bottom=rcb.top+2;
	hdc->FillRect(&rcb,&brM);
}

/***
Highlights the system menu buttons when the mouse is hovering over the button
@parameter nType - the button to highlight(close, minimize or maximize)
@parameter hdc - the device context used to draw the highlighted button
***/
void CMfcSkinSDI::HighlightSystemMenuButton(UINT nType,CDC* hdc)
{
        CRect rcb;
		CBrush brHB(m_systemBtnHighlightColor),brHBbk(m_systemBtnHighlightBkColor);
		CRect solidfill;
		CPen pen;
		CPen* oldpen;
		////////////////////////////////
        //set the clipping region so that only the area changing is drawn
		if(!this->m_updateRect.IsRectEmpty())
	    {
	     CRgn clipRgn;clipRgn.CreateRectRgn(m_updateRect.left,m_updateRect.top,m_updateRect.right,m_updateRect.bottom);
	     hdc->SelectClipRgn(&clipRgn);
	     this->m_updateRect.SetRectEmpty();
	    }
		////////////////////////////////
		switch(nType)
		{
		case SYSMENU_CLOSE://highlight for the close button
		rcb.CopyRect(&m_captionRects[3]);
		hdc->FillRect(&m_captionRects[3],&brHBbk);
		rcb.DeflateRect(m_closeBtnOffset.cx,m_closeBtnOffset.cy);
		pen.CreatePen(PS_SOLID,2,m_systemBtnHighlightColor);
		oldpen=hdc->SelectObject(&pen);
		//rcb.top+=5;rcb.bottom+=5;
	    hdc->MoveTo(rcb.left,rcb.top);
	    hdc->LineTo(rcb.right,rcb.bottom);
	    hdc->MoveTo(rcb.left,rcb.bottom);
	    hdc->LineTo(rcb.right,rcb.top);
		hdc->SelectObject(oldpen);
		m_highlightedSysMenuBtn=nType;
		    break;
		case SYSMENU_MINIMIZE://highligh for the minimize button	
		rcb.CopyRect(&m_captionRects[2]);
		hdc->FillRect(&m_captionRects[2],&brHBbk);
        rcb.DeflateRect(m_minimizeBtnOffset.cx,m_minimizeBtnOffset.cy);
	    pen.CreatePen(PS_SOLID,2,RGB(255,0,0));//todo replace the color with a memeberfunction later
		rcb.top+=(rcb.Height()/2);rcb.bottom=rcb.top+2;
		hdc->FillRect(&rcb,&brHB);
		m_highlightedSysMenuBtn=nType;
		    break;
		default:
			break;
		}
}

/***
Sets the color of the caption text
@parameter clr - the color we want to assign to the caption text
***/
void CMfcSkinSDI::SetCaptionTextColor(COLORREF clr)
{
	m_captionTextColor=clr;
}

/***
Sets the background color of the captionbar
@parameter clr - the color we want to assign to the captionbar's background
***/
void CMfcSkinSDI::SetCaptionBackColor(COLORREF clr)
{
	 m_captionBackColor=clr;
}

/***
Sets the caption text
@parameter str - the text of the caption bar. If you didn't call this function then we will use
                 the default application title from GetWindowText() function
***/
void CMfcSkinSDI::SetCaptionText(CString* str)
{
	 if(str==NULL)
	{
		m_captionText.Empty();
		m_isCustomCaptionText=false;
	}
	else
	{
		m_captionText.Empty();
		m_captionText.Insert(0,str->GetBuffer(str->GetLength()));
		m_isCustomCaptionText=true;
	}
}

/***
Set the color used to draw the system menu buttons
@parameter clr - the color
***/
void CMfcSkinSDI::SetSystemBtnColor(COLORREF clr)
{
	m_systemBtnColor=clr;
}

/***
Set the color used to draw the system menu buttons when they are highlighted
@parameter clr - the color
***/
void CMfcSkinSDI::SetSystemBtnHighlightColor(COLORREF clr)
{
    m_systemBtnHighlightColor=clr;
}

/***
Set the color used to draw the system menu buttons background when they are highlighted
@parameter clr - the color
***/
void CMfcSkinSDI::SetSystemBtnHighlightBkColor(COLORREF clr)
{
    m_systemBtnHighlightBkColor=clr;
}
/*************************END OF CAPTION BAR CUSTOM DRAWING*******************************/

/*************************MAIN MENUBAR CUSTOM DRAWING*************************************/
/***
This function will update the menu settings so that it will be owner drawn - MF_OWNERDRAW
@parameter menu - A pointer to the main menu
***/
void CMfcSkinSDI::ChangeMenuToCustomDraw(CMenu* menu)
{
    CString* str;
	CString st;
    MENUITEMINFO mii;
	mii.cbSize=sizeof(MENUITEMINFO);

	int MenuCount = menu->GetMenuItemCount();
	for (int i=0; i<MenuCount; i++)
	{
		str=0;
		//////////////////////////////////////////
#if(WINVER >= 0x0500)
  mii.fMask=MIIM_FTYPE;
    menu->GetMenuItemInfo(i,&mii,true);
    if(mii.fType==MFT_SEPARATOR) 
	   continue;
#endif
		//////////////////////
		str=new CString();
		menu->GetMenuString(i, *str, MF_BYPOSITION);
		mii.fMask=MIIM_STATE;
		menu->GetMenuItemInfo(i,&mii,true);
	
		UINT nFlag=(MF_OWNERDRAW | MF_BYPOSITION );//add the ownerdraw flag
		//////////////////////////////////////////////////
		m_menuItemCap?str->MakeUpper():false;
		this->m_menuItemText.push_back(str);
		menu->ModifyMenu(i, nFlag, (UINT)menu->GetMenuItemID(i), (LPCTSTR)str);
	}
}

void CMfcSkinSDI::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if(lpDrawItemStruct->CtlType==ODT_MENU)
	{
	  CDC* hDC = CDC::FromHandle(lpDrawItemStruct->hDC);
      ////////////
	  UINT l_menuItemCount=GetMenu()->GetMenuItemCount();
	  if(l_menuItemCount==m_menuItemCount && !m_menuItemRect.empty() && !m_drawingMenuManually)
		  m_menuItemRect.erase(m_menuItemRect.begin(),m_menuItemRect.end());
	  if(m_menuItemCount>0 && !m_drawingMenuManually)
	  {
	  m_drawingMenuManually=false;
	  CRect *rect;
	  rect=new CRect;
	  rect->CopyRect(&lpDrawItemStruct->rcItem);
	  m_menuItemRect.push_back(rect);
	  m_menuItemCount--;
	  }
	  //////////////////////////////////
	  lpDrawItemStruct->rcItem.bottom+=1;
	  hDC->FillSolidRect(&lpDrawItemStruct->rcItem, m_menuBarBkColor);

#if(WINVER >= 0x0500)
	  if((lpDrawItemStruct->itemState & ODS_HOTLIGHT))
	  {
		  hDC->FillSolidRect(&lpDrawItemStruct->rcItem, m_menuHoverColor);
	  }
#endif
	  if((lpDrawItemStruct->itemState & ODS_SELECTED) &&(lpDrawItemStruct->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	  {
		  hDC->FillSolidRect(&lpDrawItemStruct->rcItem, m_menuSelectColor);
	  }
	  CString* str = (CString*)lpDrawItemStruct->itemData;
	  hDC->SetTextColor(m_menuTextColor);
	  hDC->DrawText(str->GetBuffer(str->GetLength()),-1,&lpDrawItemStruct->rcItem,DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	  return;
	}
	CFrameWnd::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CMfcSkinSDI::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if(lpMeasureItemStruct->CtlType==ODT_MENU)
	{//just in case
	CDC *hdc=this->GetWindowDC();
	CString* str = (CString*)lpMeasureItemStruct->itemData;
	//assign the height of the menu item
	lpMeasureItemStruct->itemHeight = m_menuBarHeight;
	//assign the width of the menu item
	int count=str->GetLength();
	CSize size=hdc->GetTextExtent(str->GetBuffer(count),count);
	lpMeasureItemStruct->itemWidth = size.cx;
	this->ReleaseDC(hdc);
	}
	CFrameWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

/***
This function will draw the non-client area behind the menubar, along with the ownerdrawn menu itself
@parameter hdc - the drawing device context
***/
void CMfcSkinSDI::DrawCustomMenuBar(CDC* hdc)
{
	CRect mRect,rect;
	CBrush br(m_menuBarBkColor);
	this->GetWindowRect(&rect);
	mRect.top=m_borderWidth.top + m_captionHeight;
	mRect.bottom=mRect.top + m_menuBarHeight;
	mRect.left=m_borderWidth.left;
	mRect.right=rect.Width()-(m_borderWidth.right);
	hdc->FillRect(&mRect,&br);
    ///////////
	if(!m_menuItemRect.empty()){
	//if we already have info about the menu item dimension them call OnDrawItem() manually to avoid
	//to much flickring when the window is sized or moved
	////////////
	CFont* oldfont=hdc->SelectObject(&m_menuTextFont);
	CMenu* menu=this->GetMenu();
    DRAWITEMSTRUCT dis;
	dis.CtlType=ODT_MENU;
	dis.hDC=hdc->GetSafeHdc();
	dis.hwndItem=(HWND)menu->GetSafeHmenu();
	dis.itemAction=ODA_DRAWENTIRE;
	dis.itemState=ODS_NOFOCUSRECT;
    ////////////
	vector<CString*>::size_type sj=0;
	for(vector<CRect*>::size_type j=0;j<m_menuItemRect.size();j++)
	{
	dis.itemID=menu->GetMenuItemID((int)j);
    dis.itemData=(ULONG_PTR)m_menuItemText[sj];
	sj++;
	CRect* irect=(CRect*)m_menuItemRect.at(j);
	dis.rcItem=(RECT)*irect;
	/////
	m_drawingMenuManually=true;//we are drawing the menu manually, this has important meaning in the
	                           //OnDrawItem() function
	this->OnDrawItem(0,&dis);
	}
	hdc->SelectObject(oldfont);
	}
	else
	{
	//otherwise update the menu area using the default wndproc, this normally wouldn't excecute 
	//more than once since after this we will have info about the dimensions of the menu items
	//from the OnDrawItem() function.
	m_drawingMenuManually=false;//we are not drawing the menu manually, rather we are using the default wndproc
	this->GetWindowRect(&rect);
	rect.top += m_borderWidth.top + m_captionHeight;  
	rect.bottom = rect.top + m_menuBarHeight; 
	rect.left= 0; 
	rect.right=rect.left+rect.Width();
	HRGN hRgnMenu = ::CreateRectRgnIndirect(&rect);  
	DefWindowProc(WM_NCPAINT, (WPARAM)hRgnMenu, NULL);//only update the menubar area, which will eventually call ondrawitem() 
    DeleteObject(hRgnMenu);
	}	
}

/***
The intent of this function is to increase the vertical distance between the bottom of the menubar 
and the top of the toolbar so that the UI doesn't look over crowded.
@parameter bMargin - the new bottom margin of the menubar
***/
void CMfcSkinSDI::SetMenuBarBottomMargin(UINT bMargin)
{
	m_menuBarHeight=::GetSystemMetrics(SM_CYMENU)+bMargin;
}

/***
Sets the background color of the menu bar
@parameter clr - the new background color of the menubar
***/
void CMfcSkinSDI::SetMenuBarBkColor(COLORREF clr)
{
	m_menuBarBkColor=clr;
}

/***
Sets the hover color of the menu bar(when the mouse hovers over the menu item)
@parameter clr - the new hover color of the menubar
***/
void CMfcSkinSDI::SetMenuBarHoverColor(COLORREF clr)
{
	m_menuHoverColor=clr;
}

/***
Sets the select color of the menubar(when the menu item is selected by a mouse click)
@parameter clr - the new select color of the menubar
***/
void CMfcSkinSDI::SetMenuBarSelectColor(COLORREF clr)
{
	m_menuSelectColor=clr;
}

/***
Sets the text color of the menubar items
@parameter clr - the new text color of the menubar items
***/
void CMfcSkinSDI::SetMenuTextColor(COLORREF clr)
{
    m_menuTextColor=clr;
}

/***
Determines whether the main menubar items should be capitalized
@parameter cmd - if true menubar items are capitalized, if false the default is used
***/
void CMfcSkinSDI::CapMenuBarItems(BOOL cmd)
{
    m_menuItemCap=cmd;
}
/*************************END OF MAIN MENUBAR CUSTOM DRAW**************************************/

/*************************FUNCTIONS THAT HANDLE THE SYS_MENU ITEMS COMMNAD****************/
void CMfcSkinSDI::OnSysMenuMove()
{
	this->SendMessage(WM_SYSCOMMAND,(WPARAM)SC_MOVE); 
}

void CMfcSkinSDI::OnSysMenuRestore()
{
	this->SendMessage(WM_SYSCOMMAND,(WPARAM)SC_RESTORE); 
}

void CMfcSkinSDI::OnSysMenuSize()
{
	this->SendMessage(WM_SYSCOMMAND,(WPARAM)SC_SIZE); 
}

void CMfcSkinSDI::OnSysMenuMinimize()
{
	this->SendMessage(WM_SYSCOMMAND,(WPARAM)SC_MINIMIZE); 
}

void CMfcSkinSDI::OnSysMenuMaximize()
{
	this->SendMessage(WM_SYSCOMMAND,(WPARAM)SC_MAXIMIZE); 
}

void CMfcSkinSDI::OnSysMenuClose()
{
	this->SendMessage(WM_SYSCOMMAND,(WPARAM)SC_CLOSE); 
}

void CMfcSkinSDI::InitilizeCustomDraw()
{
    //lets get the system menu and save it to our custom popup menu so that we don't have to create one from scratch
	this->m_sysPopupMenu.Attach(this->GetSystemMenu(false)->m_hMenu);
	this->ModifyStyle(WS_SYSMENU,0);//disable the system menu style from the window,this will prevent the default system button to be drawn on the titlebar
	
	//set the menu item IDs to the respective elements;make sure these ids are defined
	
	MENUITEMINFO mii;
	mii.cbSize=sizeof(MENUITEMINFO);

	mii.fMask=MIIM_ID;
	mii.wID=AFX_IDS_SCRESTORE;//the id for the restore menu item
	::SetMenuItemInfo(m_sysPopupMenu.GetSafeHmenu(),0,true,&mii);
	
	mii.fMask=MIIM_ID;
	mii.wID=AFX_IDS_SCMOVE;//the id for the move menu item
	::SetMenuItemInfo(m_sysPopupMenu.GetSafeHmenu(),1,true,&mii);
	
	mii.fMask=MIIM_ID;
	mii.wID=AFX_IDS_SCSIZE;//the id for the size menu item
	::SetMenuItemInfo(m_sysPopupMenu.GetSafeHmenu(),2,true,&mii);

	mii.fMask=MIIM_ID;
	mii.wID=AFX_IDS_SCMINIMIZE;//the id for the minimize menu item
	::SetMenuItemInfo(m_sysPopupMenu.GetSafeHmenu(),3,true,&mii);
    
	mii.fMask=MIIM_ID;
	mii.wID=AFX_IDS_SCMAXIMIZE;//the id for the maximize menu item
	::SetMenuItemInfo(m_sysPopupMenu.GetSafeHmenu(),4,true,&mii);

	mii.fMask=MIIM_ID;
	mii.wID=AFX_IDS_SCCLOSE;//the id for the close menu item
	::SetMenuItemInfo(m_sysPopupMenu.GetSafeHmenu(),6,true,&mii);
	
    ///////////////////////////////////
	//settting the tooltips for our system mens
	//the close button tooltip
	m_sysMenuTooltipClose.Create(this,TTF_TRACK | TTS_ALWAYSTIP | WS_CHILD | WS_VISIBLE);
	m_toolItemClose.cbSize   = sizeof(TOOLINFO);
    m_toolItemClose.uFlags   = TTF_IDISHWND | TTF_TRACK | TTF_ABSOLUTE;
	m_toolItemClose.hwnd     = this->m_hWnd;
    m_toolItemClose.hinst    = 0;
    m_toolItemClose.lpszText = _T("Close");
	m_toolItemClose.uId      = (UINT_PTR)this->m_hWnd;
	m_toolItemClose.rect.left=m_captionRects[3].left;
	m_toolItemClose.rect.top=m_captionRects[3].top;
	m_toolItemClose.rect.right=m_captionRects[3].right;
	m_toolItemClose.rect.bottom=m_captionRects[3].bottom;
	m_sysMenuTooltipClose.SetToolInfo(&m_toolItemClose);
	m_sysMenuTooltipClose.AddTool(this,_T("Close"),&m_captionRects[4],(UINT_PTR)this->m_hWnd);
	m_sysMenuTooltipClose.Activate(true);
	
	//the minimize button tooltip
	m_sysMenuTooltipMin.Create(this,TTF_TRACK | TTS_ALWAYSTIP | WS_CHILD | WS_VISIBLE);
	m_toolItemMin.cbSize   = sizeof(TOOLINFO);
    m_toolItemMin.uFlags   = TTF_IDISHWND | TTF_TRACK | TTF_ABSOLUTE;
	m_toolItemMin.hwnd     = this->m_hWnd;
    m_toolItemMin.hinst    = 0;
    m_toolItemMin.lpszText = _T("Maximize");
	m_toolItemMin.uId      = (UINT_PTR)this->m_hWnd;
	m_toolItemMin.rect.left=m_captionRects[2].left;
	m_toolItemMin.rect.top=m_captionRects[2].top;
	m_toolItemMin.rect.right=m_captionRects[2].right;
	m_toolItemMin.rect.bottom=m_captionRects[2].bottom;
	m_sysMenuTooltipMin.SetToolInfo(&m_toolItemMin);
	m_sysMenuTooltipMin.AddTool(this,_T("Minimize"),&m_captionRects[2],(UINT_PTR)this->m_hWnd);
	m_sysMenuTooltipMin.Activate(true);
}

void CMfcSkinSDI::SetMainFrmResourceID(UINT Id)
{
    m_mainFrmResourceID=Id;
}

/***
Set a common background color for the captionbar, borders, toolbar and the menubar
@parameter clr - The new color to set
***/
void CMfcSkinSDI::SetCommonBkColor(COLORREF clr)
{
   m_menuBarBkColor=m_captionBackColor=m_borderColor=m_tbBackColor=clr;
}

/***
This function adjusts the window's region when the widnow border is changed in thickness
***/
void CMfcSkinSDI::AdjustWindowRgn()
{
    CRect rc;  
    this->GetWindowRect(&rc);  
	/////////////////////////////////////////////////////////////
	CRgn wrgn;
	BOOL res=false;
	int defaultFX=::GetSystemMetrics(SM_CXSIZEFRAME);
	if((defaultFX-m_borderWidth.left>0) || (defaultFX-m_borderWidth.right>0))
	{
	    UINT newFXL=0,newFXR=0;
		if((defaultFX-m_borderWidth.left>0))
		  newFXL=defaultFX-m_borderWidth.left;
	    if(defaultFX-m_borderWidth.right>0)
		   newFXR=defaultFX-m_borderWidth.right;

       res=wrgn.CreateRectRgn(newFXL,0,rc.Width()-newFXR,rc.Height());
	}
	else
	   res=wrgn.CreateRectRgn(0,0,rc.Width(),rc.Height());
	if(res)
		this->SetWindowRgn(wrgn,0);
}

void CMfcSkinSDI::OnNcPaint()
{
	CDC* hdc;
	hdc=this->GetWindowDC();
	////////////////////////////
	if(!this->m_updateRect.IsRectEmpty())
	{//if we have set an update region, make sure only that area is updated(painted)
	CRgn clipRgn;clipRgn.CreateRectRgn(m_updateRect.left,m_updateRect.top,m_updateRect.right,m_updateRect.bottom);
	hdc->SelectClipRgn(&clipRgn);
	this->m_updateRect.SetRectEmpty();
	}
	/////////////////////////////
	this->DrawCaptionBar(hdc);
	this->DrawCustomMenuBar(hdc);
	this->DrawBorder(hdc);//draw the borders
	ReleaseDC(hdc);
}

BOOL CMfcSkinSDI::OnNcActivate(BOOL bActive)
{
	//these changes here are needed to avoid flickering when the window is activated
	//CFrameWnd::OnNcActivate(bActive);
	OnNcPaint();
	return true;
}

void CMfcSkinSDI::OnPaint()
{
	CFrameWnd::OnPaint();
	OnNcPaint();
}

void CMfcSkinSDI::OnSize(UINT nType, int cx, int cy)
{
	CRect rc;  
    this->GetWindowRect(&rc);  
	int defaultFX=::GetSystemMetrics(SM_CXSIZEFRAME);
	/////////////////////////////////////////////////////////////
	AdjustWindowRgn();
    /////////////////////////////////////////////////////////////
	//Set the dimensions of the captionbar
	m_captionRects[0].top=m_borderWidth.top;
	m_captionRects[0].bottom=m_captionRects[0].top+m_captionHeight;
	m_captionRects[0].left=m_borderWidth.left;
	m_captionRects[0].right=m_captionRects[0].left+rc.Width()-(m_borderWidth.left+m_borderWidth.right);
    //calculate the application icons position and size
	if(m_captionRects[1].IsRectEmpty())
	m_captionRects[1].SetRect(m_captionRects[0].left+5,m_captionRects[0].top,m_captionRects[0].left+21,m_captionRects[0].top+16);
    //calculate the system menu button sizes
	CRect rcb;
	this->GetWindowRect(&rcb);
	//the close button
	rcb.top=m_borderWidth.top;
	rcb.left=rcb.Width()-(2*defaultFX)-(m_captionHeight);
	rcb.right=rcb.left+m_captionHeight;
	rcb.bottom=rcb.top+m_captionHeight;
	m_captionRects[3].CopyRect(&rcb);

	int width=(rcb.Width()+2);//
	//the minimize button
    width=(rcb.Width()+2);
    rcb.left-=width;
	rcb.right-=width;
	m_captionRects[2].CopyRect(&rcb);
	/////////////////////////////////////////////////
	//enabling/disabling popup menu items for the system menu based on the state of the window
	if(nType==SIZE_RESTORED&&::IsMenu(m_sysPopupMenu.GetSafeHmenu()))
	{
		this->m_sysPopupMenu.EnableMenuItem(AFX_IDS_SCRESTORE,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);//disable restore

	    this->m_sysPopupMenu.EnableMenuItem(AFX_IDS_SCMOVE,MF_BYCOMMAND | MF_ENABLED);//enable move item
		this->m_sysPopupMenu.EnableMenuItem(AFX_IDS_SCSIZE,MF_BYCOMMAND | MF_ENABLED);//enable size item
		this->m_sysPopupMenu.EnableMenuItem(AFX_IDS_SCMAXIMIZE,MF_BYCOMMAND | MF_ENABLED);//enable maximize item
	}
	m_menuItemCount=GetMenu()->GetMenuItemCount();//get the number of item in the main menu
    
	CFrameWnd::OnSize(nType, cx, cy);
}

BOOL CMfcSkinSDI::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle , CWnd* pParentWnd , CCreateContext* pContext)
{
	BOOL result=CFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext);
	if(result){
     //ModifyStyle(WS_CAPTION, 0); //Remove the titlebar from the frame using the ModifyStyle
	}
	return result; 
}

LRESULT CMfcSkinSDI::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	 if(message==WM_NCCALCSIZE)
	 {  
	    if(wParam)
		{
		LPNCCALCSIZE_PARAMS param=(LPNCCALCSIZE_PARAMS)lParam;

		if(m_menuBarHeight>(UINT)::GetSystemMetrics(SM_CYMENU))
		param->rgrc[0].top+=(m_menuBarHeight-::GetSystemMetrics(SM_CYMENU));
		
		if(!this->IsZoomed())
		{//if the window is not maximized
		//adjust the space the client occupies based on the current border dimension
		if(::GetSystemMetrics(SM_CXSIZEFRAME)-m_borderWidth.left<0)//use this only to increase the size of the border, to decrease use setwindowrgn() at onsize()
			param->rgrc[0].left-=(::GetSystemMetrics(SM_CXSIZEFRAME)-m_borderWidth.left);
		if(::GetSystemMetrics(SM_CXSIZEFRAME)-m_borderWidth.right<0)//use this only to increase the size of the border, to decrease use setwindowrgn() at onsize()
			param->rgrc[0].right+=(::GetSystemMetrics(SM_CXSIZEFRAME)-m_borderWidth.right);
		if(::GetSystemMetrics(SM_CYSIZEFRAME)-m_borderWidth.top!=0)
			param->rgrc[0].top-=(::GetSystemMetrics(SM_CYSIZEFRAME)-m_borderWidth.top);
		if(::GetSystemMetrics(SM_CYSIZEFRAME)-m_borderWidth.bottom!=0)
			param->rgrc[0].bottom+=(::GetSystemMetrics(SM_CYSIZEFRAME)-m_borderWidth.bottom);
		}
		}
		else{
        LPRECT param=(LPRECT)lParam;

		if(m_menuBarHeight>(UINT)::GetSystemMetrics(SM_CYMENU))
		param->top+=(m_menuBarHeight-::GetSystemMetrics(SM_CYMENU));

		if(!this->IsZoomed())
		{//if the window is not maximized
        //adjust the space the client occupies based on the current border dimension
		if(::GetSystemMetrics(SM_CXSIZEFRAME)-m_borderWidth.left<0)//use this only to increase the size of the border, to decrease use setwindowrgn() at onsize()
			param->left-=(::GetSystemMetrics(SM_CXSIZEFRAME)-m_borderWidth.left);
		if(::GetSystemMetrics(SM_CXSIZEFRAME)-m_borderWidth.right<0)//use this only to increase the size of the border, to decrease use setwindowrgn() at onsize()
			param->right+=(::GetSystemMetrics(SM_CXSIZEFRAME)-m_borderWidth.right);
		if(::GetSystemMetrics(SM_CYSIZEFRAME)-m_borderWidth.top!=0)
			param->top-=(::GetSystemMetrics(SM_CYSIZEFRAME)-m_borderWidth.top);
		if(::GetSystemMetrics(SM_CYSIZEFRAME)-m_borderWidth.bottom!=0)
			param->bottom+=(::GetSystemMetrics(SM_CYSIZEFRAME)-m_borderWidth.bottom);
		}
		}
	 }
#if(WINVER >= 0x0500)
	 else if(message==WM_NCMOUSELEAVE)
	 {
		if(this->m_menuBtnMarked){
		   switch(this->m_highlightedSysMenuBtn)
		   {
            case SYSMENU_CLOSE:
			   this->m_updateRect.CopyRect(&m_captionRects[3]);//set the update region of the window so that only that area is redrawn;avoids flickering
			   this->OnNcPaint();
			   this->m_sysMenuTooltipClose.SendMessage(TTM_TRACKACTIVATE,(WPARAM)FALSE, (LPARAM)&m_toolItemClose);
			   break;
		    case SYSMENU_MINIMIZE:
		       this->m_updateRect.CopyRect(&m_captionRects[2]);//set the update region of the window so that only that area is redrawn;avoids flickering
			   this->OnNcPaint();
			   this->m_sysMenuTooltipMin.SendMessage(TTM_TRACKACTIVATE,(WPARAM)FALSE, (LPARAM)&m_toolItemMin);
			   break;
		   }
		m_menuBtnMarked=false;
		return 0;
		}
	 }
#endif
	
	return CFrameWnd::DefWindowProc(message, wParam, lParam);
}

BOOL CMfcSkinSDI::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
    pDC->GetClipBox(&rect);// Erase the area needed
	CDC memdc;
	memdc.CreateCompatibleDC(pDC);
	CBitmap bmap;
	bmap.CreateDiscardableBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* oldbm=memdc.SelectObject(&bmap);
	CBrush backBrush(m_captionBackColor);
	memdc.SelectObject(&backBrush);
	memdc.FillRect(&rect,&backBrush);
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),pDC,rect.left,rect.top,SRCCOPY);
    //////
	memdc.SelectObject(oldbm);
	bmap.DeleteObject();
    return TRUE;
}

/***
This is used to unhighlight highlighted button when the mouse move outsied of our window
***/
void CMfcSkinSDI::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==TIMER_ID){
		CPoint point;
		::GetCursorPos(&point);
	    CRect rc;
	    this->GetWindowRect(&rc);
	    point.y=point.y-rc.top;
	    point.x=point.x-rc.left;
	   
		if(m_menuBtnMarked&&!m_captionRects[3].PtInRect(point)&&!m_captionRects[2].PtInRect(point)&&!m_captionRects[1].PtInRect(point)){
		   if(m_timerID!=0)
		   {
			this->KillTimer(m_timerID);
			m_timerID=0;
		   }
		   switch(this->m_highlightedSysMenuBtn)
		   {
            case SYSMENU_CLOSE:
			   this->m_updateRect.CopyRect(&m_captionRects[3]);//set the update region of the window so that only that area is redrawn;avoids flickering
			   this->OnNcPaint();
			   this->m_sysMenuTooltipClose.SendMessage(TTM_TRACKACTIVATE,(WPARAM)FALSE, (LPARAM)&m_toolItemClose);
			   break;
		  
		    case SYSMENU_MINIMIZE:
		       this->m_updateRect.CopyRect(&m_captionRects[2]);//set the update region of the window so that only that area is redrawn;avoids flickering
			   this->OnNcPaint();
			   this->m_sysMenuTooltipMin.SendMessage(TTM_TRACKACTIVATE,(WPARAM)FALSE, (LPARAM)&m_toolItemMin);
			   break;
		   }
		m_menuBtnMarked=false;
		
	}
	}
	CFrameWnd::OnTimer(nIDEvent);
}

void CMfcSkinSDI::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	LRESULT nHitTest=this->OnNcHitTest(point);
	CPoint lpoint=point;
	CRect rc;
	this->GetWindowRect(&rc);
	lpoint.y=point.y-rc.top;
	lpoint.x=point.x-rc.left;
	
	if(m_captionRects[0].PtInRect(lpoint)&&(nHitTest==HTCAPTION||nHitTest==HTCAPPICON))
		this->m_sysPopupMenu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
}

void CMfcSkinSDI::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
    CPoint lpoint=point;
	CRect rc;
	this->GetWindowRect(&rc);
	lpoint.y=point.y-rc.top;
	lpoint.x=point.x-rc.left;
	//////////////////////////////////
	//determine where the pointer is when mouse is clicked and do respective action
	if(m_captionRects[1].PtInRect(lpoint))
	{//inside the app icon; show the system popup menu
		this->m_sysPopupMenu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
	}
	else if(m_captionRects[3].PtInRect((POINT)lpoint))
	{// close button was clicked
	    this->SendMessage(WM_SYSCOMMAND,(WPARAM)SC_CLOSE); 
		return;
	}

	else if(m_captionRects[2].PtInRect((POINT)lpoint))
	{// minimize button was clicked
        this->SendMessage(WM_SYSCOMMAND,(WPARAM)SC_MINIMIZE); 
	}
	
	CFrameWnd::OnNcLButtonUp(nHitTest, point);
}

LRESULT CMfcSkinSDI::OnNcHitTest(CPoint point)
{
	CPoint lpoint=point;
	CRect rc;
	this->GetWindowRect(&rc);
	lpoint.y=point.y-rc.top;
	lpoint.x=point.x-rc.left;
	
	if(m_captionRects[3].PtInRect((POINT)lpoint))
	{//the close button
		return HTBORDER;
	}
	else if(m_captionRects[2].PtInRect((POINT)lpoint))
	{//the minimize button
		return HTBORDER;
	}
	else if(m_captionRects[1].PtInRect((POINT)lpoint))
	{//the app icon
		return HTCAPPICON;//this is a custom defnition
	}
	else if(m_captionRects[0].PtInRect(lpoint))
	{
        return HTCAPTION;
	}
	return CFrameWnd::OnNcHitTest(point);
}

/***
Many things are happening here. When the user is moving the move over the non-client are we need to
handle button highlighting for the system menubuttons and
reverting from their highlighted state to their orginal state based on the cursor's location
***/
void CMfcSkinSDI::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	CPoint lpoint=point;
	CRect rc;
	this->GetWindowRect(&rc);
	lpoint.y=point.y-rc.top;
	lpoint.x=point.x-rc.left;

	if(m_captionRects[3].PtInRect((POINT)lpoint))
	{
		switch(this->m_highlightedSysMenuBtn)
		{
		case SYSMENU_MINIMIZE:
			this->m_updateRect.CopyRect(&m_captionRects[2]);//set the update region of the window so that only that area is redrawn;avoids flickering
			this->OnNcPaint();
			this->m_sysMenuTooltipMin.SendMessage(TTM_TRACKACTIVATE,(WPARAM)FALSE, (LPARAM)&m_toolItemMin);
			break;
		}
		
		CDC* hdc=this->GetWindowDC();
		this->m_updateRect.CopyRect(&m_captionRects[3]);//set the update region of the window so that only that area is redrawn;avoids flickering
		this->HighlightSystemMenuButton(SYSMENU_CLOSE,hdc);
		ReleaseDC(hdc);
		this->m_sysMenuTooltipClose.SendMessage(TTM_TRACKACTIVATE,(WPARAM)TRUE, (LPARAM)&m_toolItemClose);
		m_menuBtnMarked=true;	
		///////////////
		if(m_timerID==0)
			m_timerID=this->SetTimer(TIMER_ID,100,NULL);
	}
	else if(m_captionRects[3].PtInRect((POINT)lpoint))
	{
		switch(this->m_highlightedSysMenuBtn)
		{
        case SYSMENU_CLOSE:
			this->m_updateRect.CopyRect(&m_captionRects[3]);//set the update region of the window so that only that area is redrawn;avoids flickering
			this->OnNcPaint();
			this->m_sysMenuTooltipClose.SendMessage(TTM_TRACKACTIVATE,(WPARAM)FALSE, (LPARAM)&m_toolItemClose);
			break;
		case SYSMENU_MINIMIZE:
			this->m_updateRect.CopyRect(&m_captionRects[2]);//set the update region of the window so that only that area is redrawn;avoids flickering
			this->OnNcPaint();
			this->m_sysMenuTooltipMin.SendMessage(TTM_TRACKACTIVATE,(WPARAM)FALSE, (LPARAM)&m_toolItemMin);
			break;
		}
            
		CDC* hdc=this->GetWindowDC();
		this->m_updateRect.CopyRect(&m_captionRects[3]);//set the update region of the window so that only that area is redrawn;avoids flickering
	    this->HighlightSystemMenuButton(SYSMENU_MAXIMIZE,hdc);
		ReleaseDC(hdc);
        this->m_sysMenuTooltipMax.SendMessage(TTM_TRACKACTIVATE,(WPARAM)TRUE, (LPARAM)&m_toolItemMax);
		m_menuBtnMarked=true;
		////////////////
		if(m_timerID==0)
			m_timerID=this->SetTimer(TIMER_ID,100,NULL);
	}
	else if(m_captionRects[2].PtInRect((POINT)lpoint))
	{
        switch(this->m_highlightedSysMenuBtn)
		{
        case SYSMENU_CLOSE:
		    this->m_updateRect.CopyRect(&m_captionRects[4]);//set the update region of the window so that only that area is redrawn;avoids flickering
			this->OnNcPaint();
			this->m_sysMenuTooltipClose.SendMessage(TTM_TRACKACTIVATE,(WPARAM)FALSE, (LPARAM)&m_toolItemClose);
			break;
		}

		CDC* hdc=this->GetWindowDC();
		this->m_updateRect.CopyRect(&m_captionRects[2]);//set the update region of the window so that only that area is redrawn;avoids flickering
		this->HighlightSystemMenuButton(SYSMENU_MINIMIZE,hdc);
		ReleaseDC(hdc);
		this->m_sysMenuTooltipMin.SendMessage(TTM_TRACKACTIVATE,(WPARAM)TRUE, (LPARAM)&m_toolItemMin);
		m_menuBtnMarked=true;
		////////////////
		if(m_timerID==0)
			m_timerID=this->SetTimer(TIMER_ID,100,NULL);
	}
	else
	{
		if(m_timerID!=0)
		{
			this->KillTimer(m_timerID);
			m_timerID=0;
		}
		if(m_menuBtnMarked)
		{
		   switch(this->m_highlightedSysMenuBtn)
		   {
            case SYSMENU_CLOSE:
			   this->m_updateRect.CopyRect(&m_captionRects[4]);//set the update region of the window so that only that area is redrawn;avoids flickering
			   this->OnNcPaint();
			   this->m_sysMenuTooltipClose.SendMessage(TTM_TRACKACTIVATE,(WPARAM)FALSE, (LPARAM)&m_toolItemClose);
			   break;
		    case SYSMENU_MINIMIZE:
		       this->m_updateRect.CopyRect(&m_captionRects[2]);//set the update region of the window so that only that area is redrawn;avoids flickering
			   this->OnNcPaint();
			   this->m_sysMenuTooltipMin.SendMessage(TTM_TRACKACTIVATE,(WPARAM)FALSE, (LPARAM)&m_toolItemMin);
			   break;
		   }
           m_menuBtnMarked=false;
		}
	}
	CFrameWnd::OnNcMouseMove(nHitTest, point);
}

void CMfcSkinSDI::OnNcRButtonUp(UINT nHitTest, CPoint point)
{
	CPoint lpoint=point;
	CRect rc;
	this->GetWindowRect(&rc);
	lpoint.y=point.y-rc.top;
	lpoint.x=point.x-rc.left;
	
	if(m_captionRects[0].PtInRect(lpoint) && nHitTest==HTCAPTION)
		return;
		//this->OnContextMenu(this,point);

	CFrameWnd::OnNcRButtonUp(nHitTest, point);
}
