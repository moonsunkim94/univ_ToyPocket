// CompanySet.h : CCompanySet의 선언입니다.

#pragma once

// 코드 생성 위치 2015년 9월 3일 목요일, 오후 1:04

class CCompanySet : public CRecordset
{
public:
	CCompanySet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCompanySet)

// 필드/매개 변수 데이터

// 아래의 문자열 형식(있을 경우)은 데이터베이스 필드의 실제 데이터 형식을
// 나타냅니다(CStringA: ANSI 데이터 형식, CStringW: 유니코드 데이터 형식).
// 이것은 ODBC 드라이버에서 불필요한 변환을 수행할 수 없도록 합니다.
// 원할 경우 이들 멤버를 CString 형식으로 변환할 수 있으며
// 그럴 경우 ODBC 드라이버에서 모든 필요한 변환을 수행합니다.
// (참고: 유니코드와 이들 변환을 모두 지원하려면  ODBC 드라이버
// 버전 3.5 이상을 사용해야 합니다).

	CStringW	m_c_code;	//업체 코드
	CStringW	m_c_name;	//거래처명
	CStringW	m_c_number;	//사업자 번호('-'포함)
	CStringW	m_c_business;	//업태
	CStringW	m_c_type;	//종목(파는 종류)
	CStringW	m_c_ceoname;	//대표자명
	CStringW	m_c_post;	//우편 번호
	CStringW	m_c_address;	//상세 주소
	CStringW	m_c_sort;	//업체 분류
	CStringW	m_c_tel;	//회사 대표 전화
	CStringW	m_c_mobile;	//회사 대표 휴대전화
	CStringW	m_c_email;	//회사 대표 메일
	CStringW	m_c_birth;	//회사 대표 생년월일
	CStringW	m_c_memo;	//메모(회사에 관한 거나 등등)

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


