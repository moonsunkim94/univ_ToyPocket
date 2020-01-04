
// ToyPocketSet.cpp : CToyPocketSet 클래스의 구현
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ToyPocketSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CToyPocketSet 구현

// 코드 생성 위치 2015년 9월 3일 목요일, 오후 1:02

IMPLEMENT_DYNAMIC(CToyPocketSet, CRecordset)

CToyPocketSet::CToyPocketSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_id = L"";
	m_password = L"";
	m_birth = L"";
	m_email = L"";
	m_user_YN = L"";
	m_permission = L"";
	m_nFields = 6;
	m_nDefaultType = dynaset;
}
//#error 보안 문제: 연결 문자열에 암호가 포함되어 있을 수 있습니다.
// 아래 연결 문자열에 일반 텍스트 암호 및/또는 
// 다른 중요한 정보가 포함되어 있을 수 있습니다.
// 보안 관련 문제가 있는지 연결 문자열을 검토한 후에 #error을(를) 제거하십시오.
// 다른 형식으로 암호를 저장하거나 다른 사용자 인증을 사용하십시오.
CString CToyPocketSet::GetDefaultConnect()
{
	return _T("DSN=ToyPocketDB;DBQ=C:\\Download\\ToyPocketDB.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CToyPocketSet::GetDefaultSQL()
{
	return _T("[UserData]");
}

void CToyPocketSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 및 RFX_Int() 같은 매크로는 데이터베이스의 필드
// 형식이 아니라 멤버 변수의 형식에 따라 달라집니다.
// ODBC에서는 자동으로 열 값을 요청된 형식으로 변환하려고 합니다
	RFX_Text(pFX, _T("[id]"), m_id);
	RFX_Text(pFX, _T("[password]"), m_password);
	RFX_Text(pFX, _T("[birth]"), m_birth);
	RFX_Text(pFX, _T("[email]"), m_email);
	RFX_Text(pFX, _T("[user_YN]"), m_user_YN);
	RFX_Text(pFX, _T("[permission]"), m_permission);

}
/////////////////////////////////////////////////////////////////////////////
// CToyPocketSet 진단

#ifdef _DEBUG
void CToyPocketSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CToyPocketSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

