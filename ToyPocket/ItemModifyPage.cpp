// ItemModifyPage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToyPocket.h"
#include "ItemModifyPage.h"
#include "afxdialogex.h"
#include "ItemSheetDlg.h"

// CItemModifyPage 대화 상자입니다.

IMPLEMENT_DYNAMIC(CItemModifyPage, CPropertyPage)

CItemModifyPage::CItemModifyPage()
	: CPropertyPage(CItemModifyPage::IDD)
	, m_icode(_T(""))
	, m_iname(_T(""))
	, m_icname(_T(""))
	, m_iccode(_T(""))
	, m_icount(_T(""))
	, m_iinput(_T(""))
	, m_ioutput(_T(""))
{

}

CItemModifyPage::~CItemModifyPage()
{
}

void CItemModifyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_ilarge);
	DDX_Control(pDX, IDC_COMBO4, m_imedium);
	DDX_Control(pDX, IDC_COMBO3, m_ismall);
	DDX_Text(pDX, IDC_EDIT7, m_icode);
	DDX_Text(pDX, IDC_EDIT4, m_iname);
	DDX_Text(pDX, IDC_EDIT14, m_icname);
	DDX_Text(pDX, IDC_EDIT5, m_iccode);
	DDX_Text(pDX, IDC_EDIT12, m_icount);
	DDX_Text(pDX, IDC_EDIT15, m_iinput);
	DDX_Text(pDX, IDC_EDIT13, m_ioutput);
	DDX_Control(pDX, IDC_EDIT7, m_icode_Edit);
	DDX_Control(pDX, IDC_EDIT4, m_iname_Edit);
	DDX_Control(pDX, IDC_EDIT14, m_icname_Edit);
	DDX_Control(pDX, IDC_EDIT5, m_iccode_Edit);
	DDX_Control(pDX, IDC_EDIT12, m_icount_Edit);
	DDX_Control(pDX, IDC_EDIT15, m_iinput_Edit);
	DDX_Control(pDX, IDC_EDIT13, m_ioutputEdit);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_idate);
	DDX_Control(pDX, IDC_IMGSTATIC, m_iimage);
	DDX_Control(pDX, IDC_IMAGE_SEARCH, m_img_set);
	DDX_Control(pDX, IDC_IMAGE_CANCLE, m_img_cancelbtn);
	DDX_Control(pDX, IDC_MDLG_ITEM_SEARCH, m_searchbtn);
	DDX_Control(pDX, IDCANCEL3, m_percentbtn);
	DDX_Control(pDX, IDC_BUTTON3, m_clearbtn);
	DDX_Control(pDX, IDC_ITEM_MODIFY, m_modifybtn);
	DDX_Control(pDX, IDCANCEL, m_cancelbtn);
	DDX_Control(pDX, IDC_BUTTON4, m_comsearch_btn);
}


BEGIN_MESSAGE_MAP(CItemModifyPage, CPropertyPage)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_MDLG_ITEM_SEARCH, &CItemModifyPage::OnBnClickedMdlgItemSearch)
	ON_BN_CLICKED(IDC_BUTTON3, &CItemModifyPage::OnBnClickedModifyClear)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CItemModifyPage::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CItemModifyPage::OnCbnSelchangeCombo4)
	ON_BN_CLICKED(IDC_IMAGE_SEARCH, &CItemModifyPage::OnBnClickedImageSearch)
	ON_BN_CLICKED(IDC_ITEM_MODIFY, &CItemModifyPage::OnBnClickedItemModify)
	ON_BN_CLICKED(IDCANCEL3, &CItemModifyPage::OnBnClickedPercent)
	ON_BN_CLICKED(IDC_BUTTON4, &CItemModifyPage::OnBnClickedComSearchBtn)
	ON_BN_CLICKED(IDC_IMAGE_CANCLE, &CItemModifyPage::OnBnClickedImageCancle)
END_MESSAGE_MAP()


// CItemModifyPage 메시지 처리기입니다.


void CItemModifyPage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CPropertyPage::OnPaint()을(를) 호출하지 마십시오.

		if(bFirst){
			CString img;
			img.Format(_T("res\\NoImage.bmp"));
			DrawBMP(img);
			//bFirst = FALSE;
		}

	if(m_icode != g_set_icode)
	{
		//m_comsearch_btn.ShowWindow(SW_HIDE);//버튼 안보이게 하기 -> 문제점 : 버튼을 사용하면서 초기화가 안먹힌다!
		m_icode_Edit.SetWindowTextW(g_set_icode);
		m_iname_Edit.SetWindowTextW(g_set_iname);
		m_iccode_Edit.SetWindowTextW(g_set_iccode);
		m_icname_Edit.SetWindowTextW(g_set_icname);
		m_icount_Edit.SetWindowTextW(g_set_icount);
		m_iinput_Edit.SetWindowTextW(g_set_iinput);
		m_ioutputEdit.SetWindowTextW(g_set_ioutput);
		
		COleDateTime Date;   //사용자가 지정한 날짜를 저장할 ColeDateTimeDate 변수   
		CString wsYear = g_set_ibirth_Year;   //년
		CString wsMonth = g_set_ibirth_Month; //월
		CString wsDay = g_set_ibirth_Day;    //일
		Date.SetDate(_tstoi(wsYear),_tstoi(wsMonth),_tstoi(wsDay));
		//COleDateTime타입은 UpdateData해줘야함 그럼 나머지안먹힘
		//그래서 변수 지우고 다시 DateTime형식의 컨트롤로 다시만듬
		m_idate.SetTime(Date);
		gbigmidsmall();

		DrawBMP(imgname_s);
	}




}
void CItemModifyPage::gbigmidsmall(void)	//카테고리 문자열 반환
{
	if(g_ilarge == "신생아/유아"){
		m_ilarge.SetCurSel(0);
		OnCbnSelchangeCombo2();
		if(g_iMiddle == "신생아"){
			m_imedium.SetCurSel(0);
			OnCbnSelchangeCombo4();
			if(g_iSmall == "치발기/딸랑이")
				m_ismall.SetCurSel(0);
			else if(g_iSmall == "모빌")
				m_ismall.SetCurSel(1);
			else if(g_iSmall == "촉각놀이/오뚝이")
				m_ismall.SetCurSel(2);
			else if(g_iSmall == "아기체육관/러닝홈")
				m_ismall.SetCurSel(3);
			else if(g_iSmall == "보행기/바운서/쏘서")
				m_ismall.SetCurSel(4);
		}
		else if(g_iMiddle == "유아"){
			m_imedium.SetCurSel(1);
			OnCbnSelchangeCombo4();
			if(g_iSmall == "공놀이")
				m_ismall.SetCurSel(0);
			else if(g_iSmall == "목욕놀이")
				m_ismall.SetCurSel(1);
			else if(g_iSmall == "병원/역할놀이")
				m_ismall.SetCurSel(2);
			else if(g_iSmall == "악기놀이")
				m_ismall.SetCurSel(3);
			else if(g_iSmall == "자동차놀이")
				m_ismall.SetCurSel(4);
		}
	} 
	
	else if(g_ilarge == "여아"){
		m_ilarge.SetCurSel(1);
		OnCbnSelchangeCombo2();
		if(g_iMiddle == "역할놀이"){
			m_imedium.SetCurSel(0);
			OnCbnSelchangeCombo4();
			if(g_iSmall == "소꿉/주방놀이")
				m_ismall.SetCurSel(0);
			else if(g_iSmall == "마트놀이")
				m_ismall.SetCurSel(1);
			else if(g_iSmall == "엄마/청소놀이")
				m_ismall.SetCurSel(2);
			else if(g_iSmall == "병원/기타놀이")
				m_ismall.SetCurSel(3);
		}
		else if(g_iMiddle == "인형"){
			m_imedium.SetCurSel(1);
			OnCbnSelchangeCombo4();
			if(Small == "공주인형")
				m_ismall.SetCurSel(0);
			else if(Small == "인형놀이")
				m_ismall.SetCurSel(1);
			else if(Small == "아기인형")
				m_ismall.SetCurSel(2);
			else if(Small == "캐릭터봉제인형")
				m_ismall.SetCurSel(3);
			else if(Small == "동물봉제인형")
				m_ismall.SetCurSel(4);
			else if(Small == "작동봉제인형")
				m_ismall.SetCurSel(5);
		}
		else if(g_iMiddle == "꾸미기"){
			m_imedium.SetCurSel(2);
			OnCbnSelchangeCombo4();
			if(g_iSmall == "드레스 및 소품")
				m_ismall.SetCurSel(0);
			else if(g_iSmall == "헤어/화장놀이")
				m_ismall.SetCurSel(1);
			else if(g_iSmall == "핸드폰/디카/기타")
				m_ismall.SetCurSel(2);
		}
	}
	else if(g_ilarge == "남아"){
		m_ilarge.SetCurSel(2);
		OnCbnSelchangeCombo2();
		if(g_iMiddle == "역할놀이"){
			m_imedium.SetCurSel(0);
			OnCbnSelchangeCombo4();
			if(g_iSmall == "공구놀이")
				m_ismall.SetCurSel(0);
			else if(g_iSmall == "카드놀이")
				m_ismall.SetCurSel(1);
			else if(g_iSmall == "품건놀이")
				m_ismall.SetCurSel(2);
			else if(g_iSmall == "코스튬플레이")
				m_ismall.SetCurSel(3);
			else if(g_iSmall == "요요/팽이놀이")
				m_ismall.SetCurSel(4);
			else if(g_iSmall == "핑거/기타놀이")
				m_ismall.SetCurSel(5);
		}
		else if(g_iMiddle == "액션"){
			m_imedium.SetCurSel(1);
			OnCbnSelchangeCombo4();
			if(g_iSmall == "변신로보트/탈것")
				m_ismall.SetCurSel(0);
			else if(g_iSmall == "액션무기")
				m_ismall.SetCurSel(1);
			else if(g_iSmall == "액션피규어")
				m_ismall.SetCurSel(2);
		}
		else if(g_iMiddle == "조종"){
			m_imedium.SetCurSel(2);
			OnCbnSelchangeCombo4();
			if(g_iSmall == "명품자동차RC")
				m_ismall.SetCurSel(0);
			else if(g_iSmall == "일반자동차RC")
				m_ismall.SetCurSel(1);
			else if(g_iSmall == "캐릭터RC")
				m_ismall.SetCurSel(2);
			else if(g_iSmall == "드론/헬기/보트/기타RC")
				m_ismall.SetCurSel(3);
		}
	}
	else if(g_ilarge == "캐릭터별"){
		m_ilarge.SetCurSel(3);
		OnCbnSelchangeCombo2();
		if(g_iMiddle == "유아캐릭터"){
			m_imedium.SetCurSel(0);
			OnCbnSelchangeCombo4();
			if(g_iSmall == "그라미")
				m_ismall.SetCurSel(0);
			else if(g_iSmall == "그린토이즈")
				m_ismall.SetCurSel(1);
			else if(g_iSmall == "라바")
				m_ismall.SetCurSel(2);
			else if(g_iSmall == "로보카폴리")
				m_ismall.SetCurSel(3);
			else if(g_iSmall == "뽀로로")
				m_ismall.SetCurSel(4);
			else if(g_iSmall == "라마즈")
				m_ismall.SetCurSel(5);
		}
		else if(g_iMiddle == "여아캐릭터"){
			m_imedium.SetCurSel(1);
			OnCbnSelchangeCombo4();
			if(g_iSmall == "겨울왕국")
				m_ismall.SetCurSel(0);
			else if(g_iSmall == "디즈니 프린세스")
				m_ismall.SetCurSel(1);
			else if(g_iSmall == "똘똘이")
				m_ismall.SetCurSel(2);
			else if(g_iSmall == "미미")
				m_ismall.SetCurSel(3);
			else if(g_iSmall == "바비")
				m_ismall.SetCurSel(4);
			else if(g_iSmall == "인사이드아웃")
				m_ismall.SetCurSel(5);
			else if(g_iSmall == "쥬쥬")
				m_ismall.SetCurSel(6);
			else if(g_iSmall == "콩순이")
				m_ismall.SetCurSel(7);
			else if(g_iSmall == "헬로키티")
				m_ismall.SetCurSel(8);
		}
		else if(g_iMiddle == "남아캐릭터"){
			m_imedium.SetCurSel(2);
			OnCbnSelchangeCombo4();
			if(g_iSmall == "건담")
				m_ismall.SetCurSel(0);
			else if(g_iSmall == "또봇")
				m_ismall.SetCurSel(1);
			else if(g_iSmall == "마인크래프트")
				m_ismall.SetCurSel(2);
			else if(g_iSmall == "미니언즈")
				m_ismall.SetCurSel(3);
			else if(g_iSmall == "어벤져스")
				m_ismall.SetCurSel(4);
			else if(g_iSmall == "원피스")
				m_ismall.SetCurSel(5);
		
		}
	}
}

void CItemModifyPage::OnBnClickedMdlgItemSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CItemSheetDlg* pSheet = (CItemSheetDlg*)GetParent();
	pSheet->SetActivePage(1);
}


void CItemModifyPage::OnBnClickedModifyClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		m_icode = _T("");
		m_iname = _T("");
		m_iccode = _T("");
		m_icname = _T("");
		m_icount = _T("");
		m_iinput = _T("");
		m_ioutput = _T("");
		//생일초기화
		CDateTimeCtrl *pCtrl = (CDateTimeCtrl *) GetDlgItem(IDC_DATETIMEPICKER2);
		CTime tm = CTime::GetCurrentTime();
		pCtrl->SetTime(&tm);

		
		m_ilarge.SetCurSel(-1);
		m_imedium.SetCurSel(-1);
		m_ismall.SetCurSel(-1);

		//이미지초기화
		CString img;
		img.Format(_T("res\\NoImage.bmp"));
		DrawBMP(img);

		UpdateData(false);
}


void CItemModifyPage::OnCbnSelchangeCombo2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int select1 = m_ilarge.GetCurSel();
	int select2 = m_imedium.GetCurSel();
	int select3 = m_ismall.GetCurSel();

	switch(select1){
		case 0 :
			m_imedium.ResetContent();
			m_imedium.EnableWindow(true);		//콤보박스 활성화
			m_ismall.EnableWindow(true);
			m_imedium.AddString(_T("신생아"));
			m_imedium.AddString(_T("유아"));
			m_ismall.ResetContent();
			break;
		case 1 :
			m_imedium.ResetContent();
			m_imedium.EnableWindow(true);
			m_ismall.EnableWindow(true);
			m_imedium.AddString(_T("역할놀이"));
			m_imedium.AddString(_T("인형"));
			m_imedium.AddString(_T("꾸미기"));
			m_ismall.ResetContent();
			break;
		case 2 :
			m_imedium.ResetContent();
			m_imedium.EnableWindow(true);
			m_ismall.EnableWindow(true);
			m_imedium.AddString(_T("역할놀이"));
			m_imedium.AddString(_T("액션"));
			m_imedium.AddString(_T("조종"));
			m_imedium.AddString(_T("자동차/기차"));
			m_ismall.ResetContent();
			break;
		case 3 :
			m_imedium.ResetContent();
			m_imedium.EnableWindow(true);
			m_ismall.EnableWindow(true);
			m_imedium.AddString(_T("유아캐릭터"));
			m_imedium.AddString(_T("여아캐릭터"));
			m_imedium.AddString(_T("남아캐릭터"));
			m_ismall.ResetContent();
			break;
	}
}


void CItemModifyPage::OnCbnSelchangeCombo4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int select1 = m_ilarge.GetCurSel();
	int select2 = m_imedium.GetCurSel();
	int select3 = m_ismall.GetCurSel();
	if(select1 == 0)
	switch(select2){
		case 0 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("치발기/딸랑이"));
			m_ismall.AddString(_T("모빌"));
			m_ismall.AddString(_T("촉각놀이/오뚝이"));
			m_ismall.AddString(_T("아기체육관/러닝홈"));
			m_ismall.AddString(_T("보행기/바운서/쏘서"));
			break;
		case 1 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("공놀이"));
			m_ismall.AddString(_T("목욕놀이"));
			m_ismall.AddString(_T("병원/역할놀이"));
			m_ismall.AddString(_T("악기놀이"));
			m_ismall.AddString(_T("자동차놀이"));
			break;
	}
	else if(select1 == 1)
		switch(select2){
		case 0 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("소꿉/주방놀이"));
			m_ismall.AddString(_T("마트놀이"));
			m_ismall.AddString(_T("엄마/청소놀이"));
			m_ismall.AddString(_T("병원/기타놀이"));
			break;
		case 1 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("공주인형"));
			m_ismall.AddString(_T("인형놀이"));
			m_ismall.AddString(_T("아가인형"));
			m_ismall.AddString(_T("캐릭터봉제인형"));
			m_ismall.AddString(_T("동물봉제인형"));
			m_ismall.AddString(_T("작동봉제인형"));
			break;
        case 2 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("드레스 및 소품"));
			m_ismall.AddString(_T("헤어/화장놀이"));
			m_ismall.AddString(_T("핸드폰/디카/기타"));
	}
	else if(select1 == 2)
		switch(select2){
		case 0 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("공구놀이"));
			m_ismall.AddString(_T("카드놀이"));
			m_ismall.AddString(_T("품건놀이"));
			m_ismall.AddString(_T("코스튬플레이"));
			m_ismall.AddString(_T("요요/팽이놀이"));
			m_ismall.AddString(_T("핑거/기타놀이"));
			break;
		case 1 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("변신로보트/탈것"));
			m_ismall.AddString(_T("액션무기"));
			m_ismall.AddString(_T("액션피규어"));
			break;
        case 2 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("명품자동차RC"));
			m_ismall.AddString(_T("일반자동차RC"));
			m_ismall.AddString(_T("캐릭터RC"));
			m_ismall.AddString(_T("드론/헬기/보트/기타RC"));
			break;
		 case 3 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("빅카/트럭/중장비"));
			m_ismall.AddString(_T("일반자동차"));
			m_ismall.AddString(_T("수집자동차"));
			m_ismall.AddString(_T("자동차놀이세트"));
			m_ismall.AddString(_T("비행기/기차/기타"));
			break;
	}
	else if(select1 == 3)
		switch(select2){
		case 0 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("그라미"));
			m_ismall.AddString(_T("그린토이즈"));
			m_ismall.AddString(_T("라바"));
			m_ismall.AddString(_T("로보카폴리"));
			m_ismall.AddString(_T("뽀로로"));
			m_ismall.AddString(_T("라마즈"));
			break;
		case 1 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("겨울왕국"));
			m_ismall.AddString(_T("디즈니 프린세스"));
			m_ismall.AddString(_T("똘똘이"));
			m_ismall.AddString(_T("미미"));
			m_ismall.AddString(_T("바비"));
			m_ismall.AddString(_T("인사이드 아웃"));
			m_ismall.AddString(_T("쥬쥬"));
			m_ismall.AddString(_T("콩순이"));
			m_ismall.AddString(_T("헬로키티"));
			break;
        case 2 :
			m_ismall.ResetContent();
			m_ismall.EnableWindow(true);
			m_ismall.AddString(_T("건담"));
			m_ismall.AddString(_T("또봇"));
			m_ismall.AddString(_T("마인크래프트"));
			m_ismall.AddString(_T("미니언즈"));
			m_ismall.AddString(_T("어벤져스"));
			m_ismall.AddString(_T("원피스"));
			break;
	}
}

CString CItemModifyPage::SelectLarge(int index)		//대분류 문자열 반환
{
	switch(index)
	{
	case 0 :
		temp = _T("신생아/유아");
		break;
	case 1 :
		temp = _T("여아");
		break;
	case 2 :
		temp = _T("남아");
		break;
	case 3 :
		temp = _T("캐릭터별");
		break;
	}
	return temp;
}

CString CItemModifyPage::SelectMedium(int index)		//중분류 문자열 반환
{
	int select1 = m_ilarge.GetCurSel();
	if(select1 == 0)
	switch(index){
		case 0:
			temp = _T("신생아");
			break;
		case 1:
			temp = _T("유아");
			break;
		}
	else if(select1 == 1)
	switch(index){
		case 0:
			temp = _T("역할놀이");
			break;
		case 1:
			temp = _T("인형");
			break;
		case 2:
			temp = _T("꾸미기");
			break;
	}
	else if(select1 == 2)
	switch(index){
		case 0:
			temp = _T("역할놀이");
			break;
		case 1:
			temp = _T("액션");
			break;
		case 2:
			temp = _T("조종");
			break;
		case 3:
			temp = _T("자동차/기차");
			break;
	}
	else if(select1 == 3)
	switch(index){
		case 0:
			temp = _T("유아캐릭터");
			break;
		case 1:
			temp = _T("여아캐릭터");
			break;
		case 2:
			temp = _T("남아캐릭터");
			break;
	}
	return temp;
}

CString CItemModifyPage::SelectSmall(int bigc, int midc, int smallc)		//소분류 문자열 반환
{
	if(bigc == 0)
	switch(midc){
		case 0: {
			switch(smallc){
				case 0:	temp = _T("치발기/딸랑이");			break;
				case 1:	temp = _T("모빌");					break;
				case 2:	temp = _T("촉각놀이/오뚝이");		break;
				case 3:	temp = _T("아기체육관/러닝홈");		break;
				case 4:	temp = _T("보행기/바운서/쏘서");		break;
			}break; }
		case 1: {
			switch(smallc){
				case 0: temp = _T("공놀이");			break;
				case 1: temp = _T("목욕놀이");		break;
				case 3: temp = _T("병원/역할놀이");	break;
				case 4: temp = _T("악기놀이");		break;
				case 5: temp = _T("자동차놀이");		break;
			}break; }
	}
	else if(bigc == 1)
	switch(midc){
		case 0: {
			switch(smallc){
				case 0:	temp = _T("소꿉/주방놀이");		break;
				case 1:	temp = _T("마트놀이");			break;
				case 2:	temp = _T("엄마/청소놀이");		break;
				case 3:	temp = _T("병원/기타놀이");		break;
			}break; }
		case 1: {
			switch(smallc){
				case 0: temp = _T("공주인형");		break;
				case 1: temp = _T("인형놀이");		break;
				case 3: temp = _T("아기인형");		break;
				case 4: temp = _T("캐릭터봉제인형");	break;
				case 5: temp = _T("동물봉제인형");	break;
				case 6: temp = _T("작동봉제인형");	break;
			}break; }
		case 2: {
			switch(smallc){
				case 0: temp = _T("드레스 및 소품");		break;
				case 1: temp = _T("헤어/화장놀이");		break;
				case 3: temp = _T("핸드폰/디카/기타");	break;
			}break; }
	}
	else if(bigc == 2)
	switch(midc){
		case 0: {
			switch(smallc){
				case 0:	temp = _T("공구놀이");			break;
				case 1:	temp = _T("카드놀이");			break;
				case 2:	temp = _T("폼건놀이");			break;
				case 3:	temp = _T("코스튬플레이");		break;
				case 4: temp = _T("요요/팽이놀이");		break;
				case 5: temp = _T("필거/기타놀이");		break;
			}break; }
		case 1: {
			switch(smallc){
				case 0: temp = _T("변신로보트/탈것");	break;
				case 1: temp = _T("액션무기");			break;
				case 3: temp = _T("액션피규어");			break;
			}break; }
		case 2: {
			switch(smallc){
				case 0: temp = _T("명품자동차RC");				break;
				case 1: temp = _T("일반자동차RC");				break;
				case 3: temp = _T("캐릭터RC");					break;
				case 4: temp = _T("드론/헬기/보트/기타RC");		break;
			}break; }
		case 3: {
			switch(smallc){
				case 0:	temp = _T("빅카/트럭/중장비");	break;
				case 1:	temp = _T("일반자동차");			break;
				case 2:	temp = _T("수집자동차");			break;
				case 3:	temp = _T("자동차놀이세트");		break;
				case 4: temp = _T("비행기/기차/기타");	break;
			}break; }
	}
	else if(bigc == 3)
	switch(midc){
		case 0: {
			switch(smallc){
				case 0:	temp = _T("그라미");			break;
				case 1:	temp = _T("그린토이즈");			break;
				case 2:	temp = _T("라바");			break;
				case 3:	temp = _T("로보카폴리");		break;
				case 4: temp = _T("뽀로로");		break;
				case 5: temp = _T("라마즈");		break;
			}break; }
		case 1: {
			switch(smallc){
				case 0: temp = _T("겨울왕국");	break;
				case 1: temp = _T("디즈니 프린세스");			break;
				case 2: temp = _T("똘똘이");			break;
				case 3: temp = _T("미미");		break;
				case 4: temp = _T("바비");		break;
				case 5: temp = _T("인사이드아웃");		break;
				case 6: temp = _T("쥬쥬");		break;
				case 7: temp = _T("콩순이");		break;
				case 8: temp = _T("헬로키티");		break;
			}break; }
		case 2: {
			switch(smallc){
				case 0: temp = _T("건담");				break;
				case 1: temp = _T("또봇");				break;
				case 3: temp = _T("마인크래프트");					break;
				case 4: temp = _T("미니언즈");		break;
				case 5: temp = _T("어벤져스");		break;
				case 6: temp = _T("원피스");		break;
			}break; }
	}
	return temp;
}


void CItemModifyPage::DrawBMP(LPCTSTR lpszFileName)	//이미지 보여주기
{
	CDC* pDC = GetDC();//화면 DC를 얻어 옴
	CDC MemDC;//메모리 DC
	CBitmap bmp, *pOldBmp;
	BITMAP bm;//비트맵 정보를 저장하는 변수
	CRect rect;
	CPoint cp;

	//이미지 파일 로딩
	bmp.m_hObject = (HBITMAP)LoadImage(NULL, lpszFileName, IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
	if(bmp.m_hObject == NULL) return;
	bmp.GetBitmap(&bm);//로딩된 이미지 파일의 형태를 얻음
	MemDC.CreateCompatibleDC(pDC);//메모리 DC와 화면 DC를 호환성있도록 연결
	pOldBmp = MemDC.SelectObject(&bmp);//메모리에 적재된 이미지 선택

	m_iimage.GetWindowRect(&rect);//다이어로그에 배치된 컨트롤의 크기를 얻어 옴
	cp.x = rect.left;//이미지 출력을 위한 시작 x 좌표
	cp.y = rect.top;//이미지 출력을 위한 시작 y 좌표 
	ScreenToClient(&cp);//cp가 가지고 있는 좌표로 화면을 지정함
	pDC->StretchBlt(cp.x,cp.y,rect.Width(),rect.Height() ,&MemDC,0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);//이미지를 해당 컨트롤로 전송
	MemDC.SelectObject(pOldBmp);
	ReleaseDC(pDC);//DC 반환
}

void CItemModifyPage::bigmidsmall(void)	//카테고리 문자열 반환
{
	if(Big == "신생아/유아"){
		m_ilarge.SetCurSel(0);
		OnCbnSelchangeCombo2();
		if(Middle == "신생아"){
			m_imedium.SetCurSel(0);
			OnCbnSelchangeCombo4();
			if(Small == "치발기/딸랑이")
				m_ismall.SetCurSel(0);
			else if(Small == "모빌")
				m_ismall.SetCurSel(1);
			else if(Small == "촉각놀이/오뚝이")
				m_ismall.SetCurSel(2);
			else if(Small == "아기체육관/러닝홈")
				m_ismall.SetCurSel(3);
			else if(Small == "보행기/바운서/쏘서")
				m_ismall.SetCurSel(4);
		}
		else if(Middle == "유아"){
			m_imedium.SetCurSel(1);
			OnCbnSelchangeCombo4();
			if(Small == "공놀이")
				m_ismall.SetCurSel(0);
			else if(Small == "목욕놀이")
				m_ismall.SetCurSel(1);
			else if(Small == "병원/역할놀이")
				m_ismall.SetCurSel(2);
			else if(Small == "악기놀이")
				m_ismall.SetCurSel(3);
			else if(Small == "자동차놀이")
				m_ismall.SetCurSel(4);
		}
	} 
	
	else if(Big == "여아"){
		m_ilarge.SetCurSel(1);
		OnCbnSelchangeCombo2();
		if(Middle == "역할놀이"){
			m_imedium.SetCurSel(0);
			OnCbnSelchangeCombo4();
			if(Small == "소꿉/주방놀이")
				m_ismall.SetCurSel(0);
			else if(Small == "마트놀이")
				m_ismall.SetCurSel(1);
			else if(Small == "엄마/청소놀이")
				m_ismall.SetCurSel(2);
			else if(Small == "병원/기타놀이")
				m_ismall.SetCurSel(3);
		}
		else if(Middle == "인형"){
			m_imedium.SetCurSel(1);
			OnCbnSelchangeCombo4();
			if(Small == "공주인형")
				m_ismall.SetCurSel(0);
			else if(Small == "인형놀이")
				m_ismall.SetCurSel(1);
			else if(Small == "아기인형")
				m_ismall.SetCurSel(2);
			else if(Small == "캐릭터봉제인형")
				m_ismall.SetCurSel(3);
			else if(Small == "동물봉제인형")
				m_ismall.SetCurSel(4);
			else if(Small == "작동봉제인형")
				m_ismall.SetCurSel(5);
		}
		else if(Middle == "꾸미기"){
			m_imedium.SetCurSel(2);
			OnCbnSelchangeCombo4();
			if(Small == "드레스 및 소품")
				m_ismall.SetCurSel(0);
			else if(Small == "헤어/화장놀이")
				m_ismall.SetCurSel(1);
			else if(Small == "핸드폰/디카/기타")
				m_ismall.SetCurSel(2);
		}
	}
	else if(Big == "남아"){
		m_ilarge.SetCurSel(1);
		OnCbnSelchangeCombo2();
		if(Middle == "역할놀이"){
			m_imedium.SetCurSel(0);
			OnCbnSelchangeCombo4();
			if(Small == "공구놀이")
				m_ismall.SetCurSel(0);
			else if(Small == "카드놀이")
				m_ismall.SetCurSel(1);
			else if(Small == "품건놀이")
				m_ismall.SetCurSel(2);
			else if(Small == "코스튬플레이")
				m_ismall.SetCurSel(3);
			else if(Small == "요요/팽이놀이")
				m_ismall.SetCurSel(4);
			else if(Small == "핑거/기타놀이")
				m_ismall.SetCurSel(5);
		}
		else if(Middle == "액션"){
			m_imedium.SetCurSel(1);
			OnCbnSelchangeCombo4();
			if(Small == "변신로보트/탈것")
				m_ismall.SetCurSel(0);
			else if(Small == "액션무기")
				m_ismall.SetCurSel(1);
			else if(Small == "액션피규어")
				m_ismall.SetCurSel(2);
		}
		else if(Middle == "조종"){
			m_imedium.SetCurSel(2);
			OnCbnSelchangeCombo4();
			if(Small == "명품자동차RC")
				m_ismall.SetCurSel(0);
			else if(Small == "일반자동차RC")
				m_ismall.SetCurSel(1);
			else if(Small == "캐릭터RC")
				m_ismall.SetCurSel(2);
			else if(Small == "드론/헬기/보트/기타RC")
				m_ismall.SetCurSel(3);
		}
	}
	else if(Big == "캐릭터별"){
		m_ilarge.SetCurSel(1);
		OnCbnSelchangeCombo2();
		if(Middle == "유아캐릭터"){
			m_imedium.SetCurSel(0);
			OnCbnSelchangeCombo4();
			if(Small == "그라미")
				m_ismall.SetCurSel(0);
			else if(Small == "그린토이즈")
				m_ismall.SetCurSel(1);
			else if(Small == "라바")
				m_ismall.SetCurSel(2);
			else if(Small == "로보카폴리")
				m_ismall.SetCurSel(3);
			else if(Small == "뽀로로")
				m_ismall.SetCurSel(4);
					else if(Small == "라마즈")
				m_ismall.SetCurSel(5);
		}
		else if(Middle == "여아캐릭터"){
			m_imedium.SetCurSel(1);
			OnCbnSelchangeCombo4();
			if(Small == "겨울왕국")
				m_ismall.SetCurSel(0);
			else if(Small == "디즈니 프린세스")
				m_ismall.SetCurSel(1);
			else if(Small == "똘똘이")
				m_ismall.SetCurSel(2);
			else if(Small == "미미")
				m_ismall.SetCurSel(3);
			else if(Small == "바비")
				m_ismall.SetCurSel(4);
			else if(Small == "인사이드아웃")
				m_ismall.SetCurSel(5);
			else if(Small == "쥬쥬")
				m_ismall.SetCurSel(6);
			else if(Small == "콩순이")
				m_ismall.SetCurSel(7);
			else if(Small == "헬로키티")
				m_ismall.SetCurSel(8);
		}
		else if(Middle == "남아캐릭터"){
			m_imedium.SetCurSel(2);
			OnCbnSelchangeCombo4();
			if(Small == "건담")
				m_ismall.SetCurSel(0);
			else if(Small == "또봇")
				m_ismall.SetCurSel(1);
			else if(Small == "마인크래프트")
				m_ismall.SetCurSel(2);
			else if(Small == "미니언즈")
				m_ismall.SetCurSel(3);
			else if(Small == "어벤져스")
				m_ismall.SetCurSel(4);
			else if(Small == "원피스")
				m_ismall.SetCurSel(5);
		}
	}
}
BOOL CItemModifyPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_img_set.LoadBitmaps(IDB_BMP_IMAGE_SET, NULL, NULL, NULL);
	m_img_set.SizeToContent();
	m_img_cancelbtn.LoadBitmaps(IDB_BMP_IMAGE_CANCEL, NULL, NULL, NULL);
	m_img_cancelbtn.SizeToContent();
	m_searchbtn.LoadBitmaps(IDB_BMP_SEARCH2, NULL, NULL, NULL);
	m_searchbtn.SizeToContent();
	m_percentbtn.LoadBitmaps(IDB_BMP_PERCENT, NULL, NULL, NULL);
	m_percentbtn.SizeToContent();
	m_clearbtn.LoadBitmaps(IDB_BMP_CLEAR, NULL, NULL, NULL);
	m_clearbtn.SizeToContent();
	m_modifybtn.LoadBitmaps(IDB_BMP_OKSET, NULL, NULL, NULL);
	m_modifybtn.SizeToContent();
	m_cancelbtn.LoadBitmaps(IDB_BMP_CANCEL, NULL, NULL, NULL);
	m_cancelbtn.SizeToContent();
	m_comsearch_btn.LoadBitmaps(IDB_BMP_SEARCH2, NULL, NULL, NULL);
	m_comsearch_btn.SizeToContent();

	GetDlgItem(IDC_EDIT14)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT13)->EnableWindow(FALSE);
	m_ilarge.AddString(_T("신생아/유아"));
	m_ilarge.AddString(_T("여아"));
	m_ilarge.AddString(_T("남아"));
	m_ilarge.AddString(_T("캐릭터별"));

	bFirst = TRUE;
	
	CFont    m_fontTitle;
	LOGFONT  lf; 

	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 17;
	::lstrcpy(lf.lfFaceName, _T("나눔바른고딕"));
	m_fontTitle.CreateFontIndirect(&lf);
	GetDlgItem(IDC_STATIC1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC3)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC4)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC5)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC6)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC7)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC8)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC9)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC10)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC11)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_COMBO2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_COMBO3)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_COMBO4)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT7)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT4)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT14)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT5)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_DATETIMEPICKER2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT12)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT15)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_EDIT13)->SetFont(&m_fontTitle);
	m_fontTitle.Detach(); 
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CItemModifyPage::OnBnClickedImageSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);

	CFileDialog sDlg(false, NULL, NULL, OFN_HIDEREADONLY, 0);

	if(sDlg.DoModal() != IDOK) 
		return; 

	CString m_i;

	m_i = sDlg.GetFileName();

	imgname.Format(_T("res\\%s.bmp"), m_i);
	CopyFile(sDlg.GetPathName(), imgname, FALSE);
	AfxMessageBox(_T("이미지가 저장되었습니다."));
	DrawBMP(imgname);
}


void CItemModifyPage::OnBnClickedItemModify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if(m_icode!=""&&m_iname!=""&&m_icname!=""&&m_iccode!=""&&m_icount!=""&&m_iinput!=""&&m_ioutput!=""){
		
		CString s;
		COleDateTime selectDate;
		m_idate.GetTime(selectDate);    //datetimepicker 컨트롤 변수
		CString sdate = selectDate.Format(_T("%Y-%m-%d"));

		CString strlarge;//대분류
		strlarge = SelectLarge(m_ilarge.GetCurSel());
		CString strmid;
		strmid = SelectMedium(m_imedium.GetCurSel());	//중분류
		CString strsmall;
		strsmall = SelectSmall(m_ilarge.GetCurSel(), m_imedium.GetCurSel(), m_ismall.GetCurSel());	//소분류


		CDatabase db;			// 데이터베이스 객체 생성
		CRecordset rs (&db);	// 레코드셋 객체 생성
		try
		{
			CString strConnection(L"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=C:\\Download\\ToyPocketDB.mdb;");	//DB오픈
			
			if (db.OpenEx (strConnection) == FALSE)
				  throw _T("데이터베이스 접속실패!");

			CString strQuery;	//데이터베이스에 전송할 쿼리문
			strQuery.Format(_T("UPDATE Item SET i_code='%s', i_name='%s', i_large='%s',i_medium='%s', i_small='%s', item_id='%s', c_name='%s', \
							   c_code='%s', i_image='%s', i_inputDate='%s', i_inputAmount='%s', i_inputPrice='%s', i_outputPrice='%s' WHERE i_code='%s'"),
				m_icode, m_iname, strlarge, strmid, strsmall, g_setid,  m_icname, m_iccode, imgname, sdate,  m_icount, m_iinput, m_ioutput, m_icode);

			db.ExecuteSQL(strQuery);	//데이터베이스에 쿼리문 전송
		}
		catch (CException * e)
		{
			e->ReportError();
			e->Delete();
		}
		catch (LPCTSTR msg)
		{
			AfxMessageBox (msg);
		}
		MessageBox(_T("성공적으로 수정되었습니다."));
		//OnBnClickedButtonComClear();	//컨트롤 초기화

		rs.Close();	//레코드셋 객체 소멸
		db.Close();	//데이터베이스 객체 소멸
	}else MessageBox(_T("입력되지 않은 값이 있습니다.\n모든 값을 입력(선택)해주세요."));
		m_icode = _T("");
		m_iname = _T("");
		m_iccode = _T("");
		m_icname = _T("");
		m_icount = _T("");
		m_iinput = _T("");
		m_ioutput = _T("");
		//생일초기화
		CDateTimeCtrl *pCtrl = (CDateTimeCtrl *) GetDlgItem(IDC_DATETIMEPICKER2);
		CTime tm = CTime::GetCurrentTime();
		pCtrl->SetTime(&tm);

		
		m_ilarge.SetCurSel(-1);
		m_imedium.SetCurSel(-1);
		m_ismall.SetCurSel(-1);

		//이미지초기화
		CString img;
		img.Format(_T("res\\NoImage.bmp"));
		DrawBMP(img);

		UpdateData(false);

}
#include "ItemPercentDlg.h"

void CItemModifyPage::OnBnClickedPercent()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CItemPercentDlg pDlg;
	pDlg.DoModal();

	CString setper;
	CString setper1;
	CString editresult;

	GetDlgItemText(IDC_EDIT15,setper);
	setper1 = pDlg.m_percent;
	editresult.Format(_T("%d"), _ttoi(setper1) * _ttoi(setper));	
	m_ioutputEdit.SetWindowTextW(editresult);

}

#include "CompanySearchDlg.h"
void CItemModifyPage::OnBnClickedComSearchBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CCompanySearchDlg pDlg;
	pDlg.DoModal();
	m_icname_Edit.SetWindowTextW(pDlg.m_cnameset);
	m_iccode_Edit.SetWindowTextW(pDlg.m_ccodeset);

}


void CItemModifyPage::OnBnClickedImageCancle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	    CString img;
		img.Format(_T("res\\NoImage.bmp"));
		DrawBMP(img);
}
