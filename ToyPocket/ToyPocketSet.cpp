
// ToyPocketSet.cpp : CToyPocketSet Ŭ������ ����
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ToyPocketSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CToyPocketSet ����

// �ڵ� ���� ��ġ 2015�� 9�� 3�� �����, ���� 1:02

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
//#error ���� ����: ���� ���ڿ��� ��ȣ�� ���ԵǾ� ���� �� �ֽ��ϴ�.
// �Ʒ� ���� ���ڿ��� �Ϲ� �ؽ�Ʈ ��ȣ ��/�Ǵ� 
// �ٸ� �߿��� ������ ���ԵǾ� ���� �� �ֽ��ϴ�.
// ���� ���� ������ �ִ��� ���� ���ڿ��� ������ �Ŀ� #error��(��) �����Ͻʽÿ�.
// �ٸ� �������� ��ȣ�� �����ϰų� �ٸ� ����� ������ ����Ͻʽÿ�.
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
// RFX_Text() �� RFX_Int() ���� ��ũ�δ� �����ͺ��̽��� �ʵ�
// ������ �ƴ϶� ��� ������ ���Ŀ� ���� �޶����ϴ�.
// ODBC������ �ڵ����� �� ���� ��û�� �������� ��ȯ�Ϸ��� �մϴ�
	RFX_Text(pFX, _T("[id]"), m_id);
	RFX_Text(pFX, _T("[password]"), m_password);
	RFX_Text(pFX, _T("[birth]"), m_birth);
	RFX_Text(pFX, _T("[email]"), m_email);
	RFX_Text(pFX, _T("[user_YN]"), m_user_YN);
	RFX_Text(pFX, _T("[permission]"), m_permission);

}
/////////////////////////////////////////////////////////////////////////////
// CToyPocketSet ����

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

