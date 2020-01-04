// CalendarSet.h : CCalendarSet 클래스의 구현입니다.



// CCalendarSet 구현입니다.

// 코드 생성 위치 2015년 10월 22일 목요일, 오후 4:10

#include "stdafx.h"
#include "CalendarSet.h"
IMPLEMENT_DYNAMIC(CCalendarSet, CRecordset)

CCalendarSet::CCalendarSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_memo = L"";
	m_memo2 = L"";
	m_memo3 = L"";
	m_memo4 = L"";
	m_preyear = 0;
	m_premonth = 0;
	m_preday = 0;
	m_week = 0;
	m_day = 0;
	m_check = FALSE;
	m_check2 = FALSE;
	m_check3 = FALSE;
	m_check4 = FALSE;
	m_nFields = 13;
	m_nDefaultType = dynaset;
}
//#error 보안 문제: 연결 문자열에 암호가 포함되어 있을 수 있습니다.
// 아래 연결 문자열에 일반 텍스트 암호 및/또는 
// 다른 중요한 정보가 포함되어 있을 수 있습니다.
// 보안 관련 문제가 있는지 연결 문자열을 검토한 후에 #error을(를) 제거하십시오.
// 다른 형식으로 암호를 저장하거나 다른 사용자 인증을 사용하십시오.
CString CCalendarSet::GetDefaultConnect()
{
	return _T("DSN=ToyPocketDB;DBQ=C:\\Download\\ToyPocketDB.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CCalendarSet::GetDefaultSQL()
{
	return _T("[Calendar]");
}

void CCalendarSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 및 RFX_Int() 같은 매크로는 데이터베이스의 필드
// 형식이 아니라 멤버 변수의 형식에 따라 달라집니다.
// ODBC에서는 자동으로 열 값을 요청된 형식으로 변환하려고 합니다
	RFX_Text(pFX, _T("[memo]"), m_memo);
	RFX_Text(pFX, _T("[memo2]"), m_memo2);
	RFX_Text(pFX, _T("[memo3]"), m_memo3);
	RFX_Text(pFX, _T("[memo4]"), m_memo4);
	RFX_Long(pFX, _T("[preyear]"), m_preyear);
	RFX_Long(pFX, _T("[premonth]"), m_premonth);
	RFX_Long(pFX, _T("[preday]"), m_preday);
	RFX_Long(pFX, _T("[week]"), m_week);
	RFX_Long(pFX, _T("[day]"), m_day);
	RFX_Bool(pFX, _T("[check]"), m_check);
	RFX_Bool(pFX, _T("[check2]"), m_check2);
	RFX_Bool(pFX, _T("[check3]"), m_check3);
	RFX_Bool(pFX, _T("[check4]"), m_check4);

}
/////////////////////////////////////////////////////////////////////////////
// CCalendarSet 진단

#ifdef _DEBUG
void CCalendarSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCalendarSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


