// ItemSet.h : CItemSet�� �����Դϴ�.

#pragma once

// �ڵ� ���� ��ġ 2015�� 9�� 3�� �����, ���� 1:04

class CItemSet : public CRecordset
{
public:
	CItemSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CItemSet)

// �ʵ�/�Ű� ���� ������

// �Ʒ��� ���ڿ� ����(���� ���)�� �����ͺ��̽� �ʵ��� ���� ������ ������
// ��Ÿ���ϴ�(CStringA: ANSI ������ ����, CStringW: �����ڵ� ������ ����).
// �̰��� ODBC ����̹����� ���ʿ��� ��ȯ�� ������ �� ������ �մϴ�.
// ���� ��� �̵� ����� CString �������� ��ȯ�� �� ������
// �׷� ��� ODBC ����̹����� ��� �ʿ��� ��ȯ�� �����մϴ�.
// (����: �����ڵ�� �̵� ��ȯ�� ��� �����Ϸ���  ODBC ����̹�
// ���� 3.5 �̻��� ����ؾ� �մϴ�).

	CStringW	m_i_code;	//��ǰ�ڵ�
	CStringW	m_i_name;	//��ǰ��
	CStringW	m_i_large;	//��з�
	CStringW	m_i_medium;	//�ߺз�
	CStringW	m_i_small;	//�Һз�
	CStringW	m_c_code;	//�ŷ�ó�ڵ�
	CStringW	m_i_image;	//��ǰ�̹���
	CStringW	m_i_inputDate;	//�԰���
	long	m_i_inputAmount;	//�԰����
	long	m_i_inputPrice;	//���԰�(�������κ��� ��� �ܰ�)
	long	m_i_outputPrice;	//�Ǹ� �ݾ�(���Ⱑ . ��ǰó���� �ȶ� ����)
	CStringW	m_i_outputDate;	//�ŷ� ��¥(�ֹ� ��¥)
	long	m_i_outputAmount;	//�ֹ� ����(���� ����)

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


