// CompanySet.h : CCompanySet�� �����Դϴ�.

#pragma once

// �ڵ� ���� ��ġ 2015�� 9�� 3�� �����, ���� 1:04

class CCompanySet : public CRecordset
{
public:
	CCompanySet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCompanySet)

// �ʵ�/�Ű� ���� ������

// �Ʒ��� ���ڿ� ����(���� ���)�� �����ͺ��̽� �ʵ��� ���� ������ ������
// ��Ÿ���ϴ�(CStringA: ANSI ������ ����, CStringW: �����ڵ� ������ ����).
// �̰��� ODBC ����̹����� ���ʿ��� ��ȯ�� ������ �� ������ �մϴ�.
// ���� ��� �̵� ����� CString �������� ��ȯ�� �� ������
// �׷� ��� ODBC ����̹����� ��� �ʿ��� ��ȯ�� �����մϴ�.
// (����: �����ڵ�� �̵� ��ȯ�� ��� �����Ϸ���  ODBC ����̹�
// ���� 3.5 �̻��� ����ؾ� �մϴ�).

	CStringW	m_c_code;	//��ü �ڵ�
	CStringW	m_c_name;	//�ŷ�ó��
	CStringW	m_c_number;	//����� ��ȣ('-'����)
	CStringW	m_c_business;	//����
	CStringW	m_c_type;	//����(�Ĵ� ����)
	CStringW	m_c_ceoname;	//��ǥ�ڸ�
	CStringW	m_c_post;	//���� ��ȣ
	CStringW	m_c_address;	//�� �ּ�
	CStringW	m_c_sort;	//��ü �з�
	CStringW	m_c_tel;	//ȸ�� ��ǥ ��ȭ
	CStringW	m_c_mobile;	//ȸ�� ��ǥ �޴���ȭ
	CStringW	m_c_email;	//ȸ�� ��ǥ ����
	CStringW	m_c_birth;	//ȸ�� ��ǥ �������
	CStringW	m_c_memo;	//�޸�(ȸ�翡 ���� �ų� ���)

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


