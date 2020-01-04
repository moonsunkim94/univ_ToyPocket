// CompanySet.h : CCompanySet Ŭ������ �����Դϴ�.



// CCompanySet �����Դϴ�.

// �ڵ� ���� ��ġ 2015�� 9�� 3�� �����, ���� 1:04

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
//#error ���� ����: ���� ���ڿ��� ��ȣ�� ���ԵǾ� ���� �� �ֽ��ϴ�.
// �Ʒ� ���� ���ڿ��� �Ϲ� �ؽ�Ʈ ��ȣ ��/�Ǵ� 
// �ٸ� �߿��� ������ ���ԵǾ� ���� �� �ֽ��ϴ�.
// ���� ���� ������ �ִ��� ���� ���ڿ��� ������ �Ŀ� #error��(��) �����Ͻʽÿ�.
// �ٸ� �������� ��ȣ�� �����ϰų� �ٸ� ����� ������ ����Ͻʽÿ�.
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
// RFX_Text() �� RFX_Int() ���� ��ũ�δ� �����ͺ��̽��� �ʵ�
// ������ �ƴ϶� ��� ������ ���Ŀ� ���� �޶����ϴ�.
// ODBC������ �ڵ����� �� ���� ��û�� �������� ��ȯ�Ϸ��� �մϴ�
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
// CCompanySet ����

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


