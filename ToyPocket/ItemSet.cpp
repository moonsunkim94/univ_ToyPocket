// ItemSet.h : CItemSet Ŭ������ �����Դϴ�.



// CItemSet �����Դϴ�.

// �ڵ� ���� ��ġ 2015�� 9�� 3�� �����, ���� 1:04

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
//#error ���� ����: ���� ���ڿ��� ��ȣ�� ���ԵǾ� ���� �� �ֽ��ϴ�.
// �Ʒ� ���� ���ڿ��� �Ϲ� �ؽ�Ʈ ��ȣ ��/�Ǵ� 
// �ٸ� �߿��� ������ ���ԵǾ� ���� �� �ֽ��ϴ�.
// ���� ���� ������ �ִ��� ���� ���ڿ��� ������ �Ŀ� #error��(��) �����Ͻʽÿ�.
// �ٸ� �������� ��ȣ�� �����ϰų� �ٸ� ����� ������ ����Ͻʽÿ�.
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
// RFX_Text() �� RFX_Int() ���� ��ũ�δ� �����ͺ��̽��� �ʵ�
// ������ �ƴ϶� ��� ������ ���Ŀ� ���� �޶����ϴ�.
// ODBC������ �ڵ����� �� ���� ��û�� �������� ��ȯ�Ϸ��� �մϴ�
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
// CItemSet ����

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


