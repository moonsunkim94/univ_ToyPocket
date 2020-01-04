// SaleSet.h : CSaleSet�� �����Դϴ�.

#pragma once

// �ڵ� ���� ��ġ 2015�� 9�� 3�� �����, ���� 1:04

class CSaleSet : public CRecordset
{
public:
	CSaleSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSaleSet)

// �ʵ�/�Ű� ���� ������

// �Ʒ��� ���ڿ� ����(���� ���)�� �����ͺ��̽� �ʵ��� ���� ������ ������
// ��Ÿ���ϴ�(CStringA: ANSI ������ ����, CStringW: �����ڵ� ������ ����).
// �̰��� ODBC ����̹����� ���ʿ��� ��ȯ�� ������ �� ������ �մϴ�.
// ���� ��� �̵� ����� CString �������� ��ȯ�� �� ������
// �׷� ��� ODBC ����̹����� ��� �ʿ��� ��ȯ�� �����մϴ�.
// (����: �����ڵ�� �̵� ��ȯ�� ��� �����Ϸ���  ODBC ����̹�
// ���� 3.5 �̻��� ����ؾ� �մϴ�).

	CStringW	m_i_outputDate;	//�ŷ� ��¥(�ֹ� ��¥)
	CStringW	m_c_code;	//�ŷ�ó �ڵ�
	CStringW	m_i_code;	//��ǰ �ڵ�
	long	m_i_outputAmount;	//�ֹ� ����(���� ����)
	long	m_i_inputPrice;	//���԰�(�������κ��� ��� �ܰ�)
	long	m_i_outputPrice;	//�Ǹ� �ݾ�(���Ⱑ . ��ǰó���� �ȶ� ����)
	long	m_order_total;	//�� �ֹ� �ݾ�(�ܰ�*���� or �Ǹűݾ�*����)
	CStringW	m_return_YN;	//��ǰ ��� ����
	CStringW	m_return_date;	//��ǰ ��¥
	CStringW	m_return_reson;	//��ǰ ����
	CStringW	m_exchange_YN;	//��ȯ ��� ����
	CStringW	m_exchange_date;	//��ȯ ��¥
	CStringW	m_exchange_reason;	//��ȯ ����
	CStringW	m_delivery_YN;	//��� ��� ����
	CStringW	m_delivery_process;	//��� ��Ȳ

// ������
	// �����翡�� ������ ���� �Լ� ������
	public:
	virtual CString GetDefaultConnect();	// �⺻ ���� ���ڿ�

	virtual CString GetDefaultSQL(); 	// ���ڵ� ������ �⺻ SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ����

// ����
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


