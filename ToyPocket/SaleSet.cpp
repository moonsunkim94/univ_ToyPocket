// SaleSet.h : CSaleSet Ŭ������ �����Դϴ�.



// CSaleSet �����Դϴ�.

// �ڵ� ���� ��ġ 2015�� 9�� 3�� �����, ���� 1:04

#include "stdafx.h"
#include "SaleSet.h"
IMPLEMENT_DYNAMIC(CSaleSet, CRecordset)

CSaleSet::CSaleSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_i_outputDate = L"";
	m_c_code = L"";
	m_i_code = L"";
	m_i_outputAmount = 0;
	m_i_inputPrice = 0;
	m_i_outputPrice = 0;
	m_order_total = 0;
	m_return_YN = L"";
	m_return_date = L"";
	m_return_reson = L"";
	m_exchange_YN = L"";
	m_exchange_date = L"";
	m_exchange_reason = L"";
	m_delivery_YN = L"";
	m_delivery_process = L"";
	m_nFields = 15;
	m_nDefaultType = dynaset;
}
//#error ���� ����: ���� ���ڿ��� ��ȣ�� ���ԵǾ� ���� �� �ֽ��ϴ�.
// �Ʒ� ���� ���ڿ��� �Ϲ� �ؽ�Ʈ ��ȣ ��/�Ǵ� 
// �ٸ� �߿��� ������ ���ԵǾ� ���� �� �ֽ��ϴ�.
// ���� ���� ������ �ִ��� ���� ���ڿ��� ������ �Ŀ� #error��(��) �����Ͻʽÿ�.
// �ٸ� �������� ��ȣ�� �����ϰų� �ٸ� ����� ������ ����Ͻʽÿ�.
CString CSaleSet::GetDefaultConnect()
{
	return _T("DSN=ToyPocketDB;DBQ=C:\\Download\\ToyPocketDB.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CSaleSet::GetDefaultSQL()
{
	return _T("[Sale]");
}

void CSaleSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() ���� ��ũ�δ� �����ͺ��̽��� �ʵ�
// ������ �ƴ϶� ��� ������ ���Ŀ� ���� �޶����ϴ�.
// ODBC������ �ڵ����� �� ���� ��û�� �������� ��ȯ�Ϸ��� �մϴ�
	RFX_Text(pFX, _T("[i_outputDate]"), m_i_outputDate);
	RFX_Text(pFX, _T("[c_code]"), m_c_code);
	RFX_Text(pFX, _T("[i_code]"), m_i_code);
	RFX_Long(pFX, _T("[i_outputAmount]"), m_i_outputAmount);
	RFX_Long(pFX, _T("[i_inputPrice]"), m_i_inputPrice);
	RFX_Long(pFX, _T("[i_outputPrice]"), m_i_outputPrice);
	RFX_Long(pFX, _T("[order_total]"), m_order_total);
	RFX_Text(pFX, _T("[return_YN]"), m_return_YN);
	RFX_Text(pFX, _T("[return_date]"), m_return_date);
	RFX_Text(pFX, _T("[return_reson]"), m_return_reson);
	RFX_Text(pFX, _T("[exchange_YN]"), m_exchange_YN);
	RFX_Text(pFX, _T("[exchange_date]"), m_exchange_date);
	RFX_Text(pFX, _T("[exchange_reason]"), m_exchange_reason);
	RFX_Text(pFX, _T("[delivery_YN]"), m_delivery_YN);
	RFX_Text(pFX, _T("[delivery_process]"), m_delivery_process);

}
/////////////////////////////////////////////////////////////////////////////
// CSaleSet ����

#ifdef _DEBUG
void CSaleSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSaleSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


