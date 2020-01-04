// ItemSet.h : CItemSet 클래스의 구현입니다.



// CItemSet 구현입니다.

// 코드 생성 위치 2015년 9월 3일 목요일, 오후 1:04

#include "stdafx.h"
#include "ItemSet.h"
IMPLEMENT_DYNAMIC(CItemSet, CRecordset)

CItemSet::CItemSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_i_code = L"";
	m_i_name = L"";
	m_i_large = L"";
	m_i_medium = L"";
	m_i_small = L"";
	m_c_code = L"";
	m_i_image = L"";
	m_i_inputDate = L"";
	m_i_inputAmount = 0;
	m_i_inputPrice = 0;
	m_i_outputPrice = 0;
	m_i_outputDate = L"";
	m_i_outputAmount = 0;
	m_nFields = 13;
	m_nDefaultType = dynaset;
}
//#error 보안 문제: 연결 문자열에 암호가 포함되어 있을 수 있습니다.
// 아래 연결 문자열에 일반 텍스트 암호 및/또는 
// 다른 중요한 정보가 포함되어 있을 수 있습니다.
// 보안 관련 문제가 있는지 연결 문자열을 검토한 후에 #error을(를) 제거하십시오.
// 다른 형식으로 암호를 저장하거나 다른 사용자 인증을 사용하십시오.
CString CItemSet::GetDefaultConnect()
{
	return _T("DSN=ToyPocketDB;DBQ=C:\\Download\\ToyPocketDB.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CItemSet::GetDefaultSQL()
{
	return _T("[Item]");
}

void CItemSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 및 RFX_Int() 같은 매크로는 데이터베이스의 필드
// 형식이 아니라 멤버 변수의 형식에 따라 달라집니다.
// ODBC에서는 자동으로 열 값을 요청된 형식으로 변환하려고 합니다
	RFX_Text(pFX, _T("[i_code]"), m_i_code);
	RFX_Text(pFX, _T("[i_name]"), m_i_name);
	RFX_Text(pFX, _T("[i_large]"), m_i_large);
	RFX_Text(pFX, _T("[i_medium]"), m_i_medium);
	RFX_Text(pFX, _T("[i_small]"), m_i_small);
	RFX_Text(pFX, _T("[c_code]"), m_c_code);
	RFX_Text(pFX, _T("[i_image]"), m_i_image);
	RFX_Text(pFX, _T("[i_inputDate]"), m_i_inputDate);
	RFX_Long(pFX, _T("[i_inputAmount]"), m_i_inputAmount);
	RFX_Long(pFX, _T("[i_inputPrice]"), m_i_inputPrice);
	RFX_Long(pFX, _T("[i_outputPrice]"), m_i_outputPrice);
	RFX_Text(pFX, _T("[i_outputDate]"), m_i_outputDate);
	RFX_Long(pFX, _T("[i_outputAmount]"), m_i_outputAmount);

}
/////////////////////////////////////////////////////////////////////////////
// CItemSet 진단

#ifdef _DEBUG
void CItemSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CItemSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


