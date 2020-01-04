// CompanySet.h : CCompanySet 클래스의 구현입니다.



// CCompanySet 구현입니다.

// 코드 생성 위치 2015년 9월 3일 목요일, 오후 1:04

#include "stdafx.h"
#include "CompanySet.h"
IMPLEMENT_DYNAMIC(CCompanySet, CRecordset)

CCompanySet::CCompanySet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_c_code = L"";
	m_c_name = L"";
	m_c_number = L"";
	m_c_business = L"";
	m_c_type = L"";
	m_c_ceoname = L"";
	m_c_post = L"";
	m_c_address = L"";
	m_c_sort = L"";
	m_c_tel = L"";
	m_c_mobile = L"";
	m_c_email = L"";
	m_c_birth = L"";
	m_c_memo = L"";
	m_nFields = 14;
	m_nDefaultType = dynaset;
}
//#error 보안 문제: 연결 문자열에 암호가 포함되어 있을 수 있습니다.
// 아래 연결 문자열에 일반 텍스트 암호 및/또는 
// 다른 중요한 정보가 포함되어 있을 수 있습니다.
// 보안 관련 문제가 있는지 연결 문자열을 검토한 후에 #error을(를) 제거하십시오.
// 다른 형식으로 암호를 저장하거나 다른 사용자 인증을 사용하십시오.
CString CCompanySet::GetDefaultConnect()
{
	return _T("DSN=ToyPocketDB;DBQ=C:\\Download\\ToyPocketDB.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CCompanySet::GetDefaultSQL()
{
	return _T("[Company]");
}

void CCompanySet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 및 RFX_Int() 같은 매크로는 데이터베이스의 필드
// 형식이 아니라 멤버 변수의 형식에 따라 달라집니다.
// ODBC에서는 자동으로 열 값을 요청된 형식으로 변환하려고 합니다
	RFX_Text(pFX, _T("[c_code]"), m_c_code);
	RFX_Text(pFX, _T("[c_name]"), m_c_name);
	RFX_Text(pFX, _T("[c_number]"), m_c_number);
	RFX_Text(pFX, _T("[c_business]"), m_c_business);
	RFX_Text(pFX, _T("[c_type]"), m_c_type);
	RFX_Text(pFX, _T("[c_ceoname]"), m_c_ceoname);
	RFX_Text(pFX, _T("[c_post]"), m_c_post);
	RFX_Text(pFX, _T("[c_address]"), m_c_address);
	RFX_Text(pFX, _T("[c_sort]"), m_c_sort);
	RFX_Text(pFX, _T("[c_tel]"), m_c_tel);
	RFX_Text(pFX, _T("[c_mobile]"), m_c_mobile);
	RFX_Text(pFX, _T("[c_email]"), m_c_email);
	RFX_Text(pFX, _T("[c_birth]"), m_c_birth);
	RFX_Text(pFX, _T("[c_memo]"), m_c_memo);

}
/////////////////////////////////////////////////////////////////////////////
// CCompanySet 진단

#ifdef _DEBUG
void CCompanySet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCompanySet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


