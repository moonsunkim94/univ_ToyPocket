
// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.


#include <afxdisp.h>        // MFC �ڵ�ȭ Ŭ�����Դϴ�.


 // ���⿡�� �信 ���� DB ������ ���õ˴ϴ�.

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC�� ���� �� ��Ʈ�� ���� ����






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

//����� ������� ����
extern CString g_setid;

//�ŷ�ó
extern CString g_set_ccode;
extern CString g_set_cnumber;
extern CString g_set_cname;
extern int g_set_csortindex;
extern CString set_csort; //������
extern CString g_set_ctype;
extern CString g_set_cbusiness;
extern int g_set_ctelindex;
extern CString set_ctel;//������
extern CString g_set_ctel1;
extern CString g_set_ctel2;
extern CString g_set_caddress;
extern CString g_set_cceoname;
extern CString g_set_cemail;
extern CString g_set_cbirth_Year;//������
extern CString g_set_cbirth_Month;
extern CString g_set_cbirth_Day;
extern int g_set_cmtelindex;
extern CString set_cmtel;//������
extern CString g_set_cmtel1;
extern CString g_set_cmtel2;
extern CString g_set_cmemo;
extern CString g_set_cid;

//�α��� �� �޴���Ȱ��ȭ ���� BOOL����
extern BOOL m_bIsCopyTime;
extern CString g_per;
extern CString g_pwd;

//�޴� 
extern BOOL m_excheck;
extern BOOL m_salecheck;
extern BOOL m_recheck;

//������
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

//�Ǹ�
extern CString g_soutDate_Year;
extern CString g_soutDate_Month;
extern CString g_soutDate_Day;
extern CString g_ccode;
extern CString g_icode;
extern CString g_soutAmount;
extern CString g_inPrice;
extern CString g_outPrice;
extern CString g_orderTotal;

//����
extern int week;
extern int day;
extern CString yearpre;
extern CString monthpre;
extern int daypre;