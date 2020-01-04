
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// ToyPocket.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"

//담당자
CString g_setid;

//거래처
CString g_set_ccode;
CString g_set_cnumber;
CString g_set_cname;
int g_set_csortindex;
CString g_set_ctype;
CString g_set_cbusiness;
int g_set_ctelindex;
CString g_set_ctel1;
CString g_set_ctel2;
CString g_set_caddress;
CString g_set_cceoname;
CString g_set_cemail;
CString g_wsDate; 
CString g_set_cbirth_Year;
CString g_set_cbirth_Month;
CString g_set_cbirth_Day;
int g_set_cmtelindex;
CString g_set_cmtel1;
CString g_set_cmtel2;
CString g_set_cmemo;
CString g_set_cid;

//메뉴 이벤트처리기 변수
BOOL m_bIsCopyTime = FALSE;
CString g_per;
CString g_pwd;

//메뉴
BOOL m_excheck = FALSE;
BOOL m_salecheck = FALSE;
BOOL m_recheck = FALSE;

//아이템
CString g_set_iccode;
CString g_set_iname;
CString g_set_icode;
CString g_set_icname;
CString g_set_icount;
CString g_set_ibirth_Year;
CString g_set_ibirth_Month;
CString g_set_ibirth_Day;
CString g_set_iimage;
CString g_set_iinput;
CString g_set_ioutput;
int g_set_largeindex;
int g_set_mediumindex;
int g_set_smallindex;
CString g_ilarge;
CString g_iMiddle;
CString g_iSmall;
CString imgname_s;

//판매
CString g_soutDate_Year;
CString g_soutDate_Month;
CString g_soutDate_Day;
CString g_ccode;
CString g_icode;
CString g_soutAmount;
CString g_inPrice;
CString g_outPrice;
CString g_orderTotal;

//일정
int week;
int day;
CString yearpre;
CString monthpre;
int daypre;