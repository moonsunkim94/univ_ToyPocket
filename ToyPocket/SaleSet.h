// SaleSet.h : CSaleSet의 선언입니다.

#pragma once

// 코드 생성 위치 2015년 9월 3일 목요일, 오후 1:04

class CSaleSet : public CRecordset
{
public:
	CSaleSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSaleSet)

// 필드/매개 변수 데이터

// 아래의 문자열 형식(있을 경우)은 데이터베이스 필드의 실제 데이터 형식을
// 나타냅니다(CStringA: ANSI 데이터 형식, CStringW: 유니코드 데이터 형식).
// 이것은 ODBC 드라이버에서 불필요한 변환을 수행할 수 없도록 합니다.
// 원할 경우 이들 멤버를 CString 형식으로 변환할 수 있으며
// 그럴 경우 ODBC 드라이버에서 모든 필요한 변환을 수행합니다.
// (참고: 유니코드와 이들 변환을 모두 지원하려면  ODBC 드라이버
// 버전 3.5 이상을 사용해야 합니다).

	CStringW	m_i_outputDate;	//거래 날짜(주문 날짜)
	CStringW	m_c_code;	//거래처 코드
	CStringW	m_i_code;	//상품 코드
	long	m_i_outputAmount;	//주문 수량(매출 수량)
	long	m_i_inputPrice;	//매입가(공장으로부터 사온 단가)
	long	m_i_outputPrice;	//판매 금액(매출가 . 납품처한테 팔때 가격)
	long	m_order_total;	//총 주문 금액(단가*수량 or 판매금액*수량)
	CStringW	m_return_YN;	//반품 사실 유무
	CStringW	m_return_date;	//반품 날짜
	CStringW	m_return_reson;	//반품 이유
	CStringW	m_exchange_YN;	//교환 사실 유무
	CStringW	m_exchange_date;	//교환 날짜
	CStringW	m_exchange_reason;	//교환 이유
	CStringW	m_delivery_YN;	//배송 사실 유무
	CStringW	m_delivery_process;	//배송 현황

// 재정의
	// 마법사에서 생성한 가상 함수 재정의
	public:
	virtual CString GetDefaultConnect();	// 기본 연결 문자열

	virtual CString GetDefaultSQL(); 	// 레코드 집합의 기본 SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX 지원

// 구현
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


