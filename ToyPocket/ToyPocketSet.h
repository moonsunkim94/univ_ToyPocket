
// ToyPocketSet.h: CToyPocketSet Ŭ������ �������̽�
//


#pragma once

// �ڵ� ���� ��ġ 2015�� 9�� 3�� �����, ���� 1:02

class CToyPocketSet : public CRecordset
{
public:
	CToyPocketSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CToyPocketSet)

// �ʵ�/�Ű� ���� ������

// �Ʒ��� ���ڿ� ����(���� ���)�� �����ͺ��̽� �ʵ��� ���� ������ ������
// ��Ÿ���ϴ�(CStringA: ANSI ������ ����, CStringW: �����ڵ� ������ ����).
// �̰��� ODBC ����̹����� ���ʿ��� ��ȯ�� ������ �� ������ �մϴ�.
// ���� ��� �̵� ����� CString �������� ��ȯ�� �� ������
// �׷� ��� ODBC ����̹����� ��� �ʿ��� ��ȯ�� �����մϴ�.
// (����: �����ڵ�� �̵� ��ȯ�� ��� �����Ϸ���  ODBC ����̹�
// ���� 3.5 �̻��� ����ؾ� �մϴ�).

	CStringW	m_id;	//���̵�
	CStringW	m_password;	//��й�ȣ
	CStringW	m_birth;	//����
	CStringW	m_email;	//�̸���
	CStringW	m_user_YN;	//���� ���� ����
	CStringW	m_permission;	//����

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

