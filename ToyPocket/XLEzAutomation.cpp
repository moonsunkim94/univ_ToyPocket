// EzAutomation.cpp: implementation of the CXLEzAutomation class.
//This wrapper classe is provided for easy access to basic automation  
//methods of the CXLAutoimation.
//Only very basic set of methods is provided here.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "XLAutomationTester.h"
#include "XLEzAutomation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//

//////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////
CXLEzAutomation::CXLEzAutomation()
{
	//Starts Excel with bVisible = TRUE and creates empty worksheet 
	m_pXLServer = new CXLAutomation;
}

CXLEzAutomation::CXLEzAutomation(BOOL bVisible)
{
	//Can be used to start Excel in background (bVisible = FALSE)
	m_pXLServer = new CXLAutomation(bVisible);

}

CXLEzAutomation::~CXLEzAutomation()
{
	if(NULL != m_pXLServer)
		delete m_pXLServer;
}


//Create XY plot of the type xlXYScatterLinesNoMarkers
//XY 차트 생성
BOOL CXLEzAutomation::CreateXYChart(int nYColumn)
{
	return m_pXLServer->CreateXYChart(nYColumn);
}
//Force update data source range . If new data points have been added to
//the data source, these points will be added to the plot.
//Default assumes data are placed in A and B columns of the Excel worksheet.
//XY 차트 업데이트
BOOL CXLEzAutomation::UpdateXYChart(int nYColumn)
{
	return m_pXLServer->UpdatePlotRange(nYColumn);
}
//Use clipboard to export szDataCollection to Excel worksheet
//클립보드 사용
BOOL CXLEzAutomation::ExportCString(CString szDataCollection)
{
	return m_pXLServer->PasteStringToWorksheet(szDataCollection);

}
//Set cell value: Worksheet.Cells(nColumn, nRow).Value = szValue
//Cell 값 설정
BOOL CXLEzAutomation::SetCellValue(int nColumn, int nRow, CString szValue)
{
	BOOL bResult;

	bResult = m_pXLServer->SetCellsValueToString((double) nColumn, (double)nRow, szValue);
	return bResult;
}
//Quit Excel
//엑셀 닫기
BOOL CXLEzAutomation::ReleaseExcel()
{
	return m_pXLServer->ReleaseExcel();
}
//Delete line from worksheet

//현재 워크시트의 열 삭제
BOOL CXLEzAutomation::DeleteRow(int nRow)
{
	return m_pXLServer->DeleteRow(nRow);
}
//Save workbook as Excel file
//엑셀 파일 저장
BOOL CXLEzAutomation::SaveFileAs(CString szFileName)
{
	return m_pXLServer->SaveAs(szFileName, xlNormal,  _T(""), _T(""), FALSE, FALSE); 
}
//Returns Worksheet.Cells(nColumn, nRow).Value
//Cell값 얻음
CString CXLEzAutomation::GetCellValue(int nColumn, int nRow)
{
	return m_pXLServer->GetCellValueCString(nColumn, nRow);
}
//Insert picture from file. Position it at (Column, Row) on the worksheet. 
//The method resizes the picture to 50% of the original size (see 0.5, 0.5)
//그림 파일 삽입
BOOL CXLEzAutomation::InsertPictureFromFile(CString szFileName, int Column, int Row)
{
	return m_pXLServer->InsertPictureToWorksheet(szFileName, Column, Row, 0.5, 0.5);
}
//Insert picture which was previously placed on clipboard
//Does not resize picture (see 0.0, 0.0)
//DIB 그림 삽입
BOOL CXLEzAutomation::InsertPictureFromClipboard(int Column, int Row)
{
	return m_pXLServer->InsertPictureToWorksheet(NULL, Column, Row, 0.0, 0.0);
}
//Place image to clipboard using XLAutomation method
//이미지를 클립보드에 복사
BOOL CXLEzAutomation::PlacePictureToClipboard(BYTE *pImage)
{
	return m_pXLServer->PlaceImageToClipboard(pImage);
}
//Open Excell file
//읽기를 위한 엑셀 파일 열기
BOOL CXLEzAutomation::OpenExcelFile(CString szFileName)
{
	return m_pXLServer->OpenExcelFile(szFileName);
}
//Insert picture from buffer. If pImage = NULL, the picture from clipboard will be inserted.
//The picture is placed at (Column, Row) on worksheet
//The picture can be resized in % of its original size
//by specifying dXScale and dYScale
//If no resize is needed, make dXScal = 0.0 and dYScale = 0.0 
//버퍼에서 이미지 가져옴
BOOL CXLEzAutomation::InsertPictureFromBuffer(BYTE *pImage, int Column, int Row, double dXScale, double dYScale)
{
	return m_pXLServer->InsertPictureToWorksheet(pImage, Column, Row, dXScale, dYScale);
}
