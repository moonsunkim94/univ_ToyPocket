// CalendarSet.h : CCalendarSet Ŭ������ �����Դϴ�.



// CCalendarSet �����Դϴ�.

// �ڵ� ���� ��ġ 2015�� 10�� 22�� �����, ���� 4:10

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
//#error ���� ����: ���� ���ڿ��� ��ȣ�� ���ԵǾ� ���� �� �ֽ��ϴ�.
// �Ʒ� ���� ���ڿ��� �Ϲ� �ؽ�Ʈ ��ȣ ��/�Ǵ� 
// �ٸ� �߿��� ������ ���ԵǾ� ���� �� �ֽ��ϴ�.
// ���� ���� ������ �ִ��� ���� ���ڿ��� ������ �Ŀ� #error��(��) �����Ͻʽÿ�.
// �ٸ� �������� ��ȣ�� �����ϰų� �ٸ� ����� ������ ����Ͻʽÿ�.
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
// RFX_Text() �� RFX_Int() ���� ��ũ�δ� �����ͺ��̽��� �ʵ�
// ������ �ƴ϶� ��� ������ ���Ŀ� ���� �޶����ϴ�.
// ODBC������ �ڵ����� �� ���� ��û�� �������� ��ȯ�Ϸ��� �մϴ�
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
// CCalendarSet ����

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


