
// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.


#include <afxdisp.h>        // MFC 자동화 클래스입니다.


 // 여기에서 뷰에 대한 DB 지원이 선택됩니다.

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원






#include <afxdb.h>        // ODBC
#include <afxdlgs.h>



#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

//담당자 등록위한 변수
extern CString g_setid;

//거래처
extern CString g_set_ccode;
extern CString g_set_cnumber;
extern CString g_set_cname;
extern int g_set_csortindex;
extern CString set_csort; //보완점
extern CString g_set_ctype;
extern CString g_set_cbusiness;
extern int g_set_ctelindex;
extern CString set_ctel;//보완점
extern CString g_set_ctel1;
extern CString g_set_ctel2;
extern CString g_set_caddress;
extern CString g_set_cceoname;
extern CString g_set_cemail;
extern CString g_set_cbirth_Year;//보완점
extern CString g_set_cbirth_Month;
extern CString g_set_cbirth_Day;
extern int g_set_cmtelindex;
extern CString set_cmtel;//보완점
extern CString g_set_cmtel1;
extern CString g_set_cmtel2;
extern CString g_set_cmemo;
extern CString g_set_cid;

//로그인 전 메뉴비활성화 위한 BOOL변수
extern BOOL m_bIsCopyTime;
extern CString g_per;
extern CString g_pwd;

//메뉴 
extern BOOL m_excheck;
extern BOOL m_salecheck;
extern BOOL m_recheck;

//아이템
extern CString g_set_icode;
extern CString g_set_iname;
extern CString g_set_iccode;
extern CString g_set_icname;
extern CString g_set_icount;
extern CString g_set_ibirth_Year;
extern CString g_set_ibirth_Month;
extern CString g_set_ibirth_Day;
extern CString g_set_iimage;
extern CString g_set_iinput;
extern CString g_set_ioutput;
extern int g_set_largeindex;
extern int g_set_mediumindex;
extern int g_set_smallindex;

extern CString g_ilarge;
extern CString g_iMiddle;
extern CString g_iSmall;

extern CString imgname_s;

//판매
extern CString g_soutDate_Year;
extern CString g_soutDate_Month;
extern CString g_soutDate_Day;
extern CString g_ccode;
extern CString g_icode;
extern CString g_soutAmount;
extern CString g_inPrice;
extern CString g_outPrice;
extern CString g_orderTotal;

//일정
extern int week;
extern int day;
extern CString yearpre;
extern CString monthpre;
extern int daypre;