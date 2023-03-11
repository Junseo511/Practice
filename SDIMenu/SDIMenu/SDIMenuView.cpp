
// SDIMenuView.cpp : CSDIMenuView 클래스의 구현
//
#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SDIMenu.h"
#endif

#include "MainFrm.h"

#include "SDIMenuDoc.h"
#include "SDIMenuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSDIMenuView

IMPLEMENT_DYNCREATE(CSDIMenuView, CView)

BEGIN_MESSAGE_MAP(CSDIMenuView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSDIMenuView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DRAW_LINE, &CSDIMenuView::OnDrawLine)
	ON_COMMAND(ID_DRAW_ELLIPSE, &CSDIMenuView::OnDrawEllipse)
	ON_COMMAND(ID_DRAW_POLYGON, &CSDIMenuView::OnDrawPolygon)
	ON_COMMAND(ID_DRAW_SQUARE, &CSDIMenuView::OnDrawSquare)
	ON_COMMAND(ID_COLOR_LINE, &CSDIMenuView::OnColorLine)
	ON_COMMAND(ID_COLOR_FACE, &CSDIMenuView::OnColorFace)
	ON_COMMAND(ID_PAT_45, &CSDIMenuView::OnPat45)
	ON_COMMAND(ID_PAT_CROSS, &CSDIMenuView::OnPatCross)
	ON_COMMAND(ID_PAT_VER, &CSDIMenuView::OnPatVer)
//	ON_UPDATE_COMMAND_UI(ID_COLOR_LINE, &CSDIMenuView::OnUpdateColorLine)
ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, &CSDIMenuView::OnUpdateDrawLine)
ON_UPDATE_COMMAND_UI(ID_DRAW_ELLIPSE, &CSDIMenuView::OnUpdateDrawEllipse)
ON_UPDATE_COMMAND_UI(ID_DRAW_POLYGON, &CSDIMenuView::OnUpdateDrawPolygon)
ON_UPDATE_COMMAND_UI(ID_DRAW_SQUARE, &CSDIMenuView::OnUpdateDrawSquare)
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// 모드 설정

enum DRAW_MODE { LINE_MODE, ELLIPSE_MODE, POLYGON_MODE, SQUARE_MODE };

// CSDIMenuView 생성/소멸

CSDIMenuView::CSDIMenuView()
	: m_nDrawMode(0)
	, m_nHatchStyle(0)
	, m_ptStart(0)
	, m_ptPrev(0)
	, m_bFirst(false)
	, m_bLButtonDown(false)
	, m_bContextMenu(false)
	, m_bHatch(false)
	, m_nCount(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_nDrawMode = LINE_MODE;
	m_bContextMenu = true;
	m_bFirst = true;

	for (int i = 0; i < 100; i++)
	{
		m_ptData[i] = 0;
	}
	// memset(m_ptData, 0, sizeof(CPoint) * 100);

	m_nHatchStyle = HS_CROSS;
	m_colorPen = RGB(0, 0, 0); // black
	m_colorBrush = RGB(255, 255, 255); // white
}

CSDIMenuView::~CSDIMenuView()
{
}

BOOL CSDIMenuView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSDIMenuView 그리기


void CSDIMenuView::OnDraw(CDC* pDC)
{
	CSDIMenuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CPen pen, *oldpen;											// pen 객체 생성
	pen.CreatePen(PS_SOLID, 1, m_colorPen);						// pen 객체 등록
	oldpen = pDC->SelectObject(&pen);							// COPYPEN으로 설정
	pDC->SetROP2(R2_COPYPEN);

	CBrush brush, *oldbrush;
	if (m_bHatch)
		brush.CreateHatchBrush(m_nHatchStyle, m_colorBrush);	// brush 객체 생성
	else
		brush.CreateSolidBrush(m_colorBrush);					// brush 객체 등록
	oldbrush = pDC->SelectObject(&brush);

	switch (m_nDrawMode)
	{
	case LINE_MODE:												// 직선 그리기
		pDC->MoveTo(m_ptStart);
		pDC->LineTo(m_ptPrev);
		break;
	case ELLIPSE_MODE:											// 원 그리기
		pDC->Ellipse(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
		break;
	case SQUARE_MODE:											// 사각형 그리기
		pDC->Rectangle(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
		break;
	case POLYGON_MODE:											// 다각형 그리기
		pDC->Polygon(m_ptData, m_nCount);						// 배열에 저장한 순서대로 연결해 마지막 다각형 그리기
		break;
	}
	pDC->SelectObject(oldpen);									// 이전 pen으로 설정
	pDC->SelectObject(oldbrush);								// 이전 brush로 설정
	pen.DeleteObject();											// pen 객체 삭제
	brush.DeleteObject();										// brush 객체 삭제
}


// CSDIMenuView 인쇄


void CSDIMenuView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSDIMenuView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSDIMenuView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSDIMenuView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CSDIMenuView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSDIMenuView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	if (m_bContextMenu)
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);

	m_bContextMenu = TRUE;
#endif
}


// CSDIMenuView 진단

#ifdef _DEBUG
void CSDIMenuView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIMenuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIMenuDoc* CSDIMenuView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIMenuDoc)));
	return (CSDIMenuDoc*)m_pDocument;
}
#endif //_DEBUG


// CSDIMenuView 메시지 처리기


void CSDIMenuView::OnDrawLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// MessageBox(_T("직선을 그립니다."));
	m_nDrawMode = LINE_MODE;
	
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_wndStatusBar.SetWindowTextW(_T("직선그리기"));
}


void CSDIMenuView::OnDrawEllipse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// MessageBox(_T("원을 그립니다."));
	m_nDrawMode = ELLIPSE_MODE;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_wndStatusBar.SetWindowTextW(_T("원그리기"));
}


void CSDIMenuView::OnDrawPolygon()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// MessageBox(_T("다각형을 그립니다."));
	m_nDrawMode = POLYGON_MODE;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_wndStatusBar.SetWindowTextW(_T("다각형그리기"));
}


void CSDIMenuView::OnDrawSquare()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// MessageBox(_T("사각형을 그립니다."));
	m_nDrawMode = SQUARE_MODE;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_wndStatusBar.SetWindowTextW(_T("사각형그리기"));
}


void CSDIMenuView::OnColorLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// MessageBox(_T("선의 색을 변경합니다."));
	CColorDialog dlgColor;
	if (dlgColor.DoModal() == IDOK)
	{
		m_colorPen = dlgColor.GetColor();
	}
	UpdateData();
	Invalidate(false);
}


void CSDIMenuView::OnColorFace()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// MessageBox(_T("면의 색을 변경합니다."));
	CColorDialog dlgColor;
	if (dlgColor.DoModal() == IDOK)
	{
		m_colorBrush = dlgColor.GetColor();
	}
	m_bHatch = FALSE;
	UpdateData();
	Invalidate(false);
}


void CSDIMenuView::OnPat45()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// MessageBox(_T("무늬를 왼쪽 45도로 변경합니다."));
	m_nHatchStyle = HS_BDIAGONAL;
	m_bHatch = TRUE;
	Invalidate(false);
}


void CSDIMenuView::OnPatCross()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// MessageBox(_T("무늬를 십자가로 변경합니다."));
	m_nHatchStyle = HS_CROSS;
	m_bHatch = TRUE;
	Invalidate(false);
}


void CSDIMenuView::OnPatVer()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// MessageBox(_T("무늬를 수직선으로 변경합니다."));
	m_nHatchStyle = HS_VERTICAL;
	m_bHatch = TRUE;
	Invalidate(false);
}


//void CSDIMenuView::OnUpdateColorLine(CCmdUI *pCmdUI)
//{
//	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
//}


void CSDIMenuView::OnUpdateDrawLine(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck((m_nDrawMode == LINE_MODE)? TRUE : FALSE);
}


void CSDIMenuView::OnUpdateDrawEllipse(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck((m_nDrawMode == ELLIPSE_MODE) ? TRUE : FALSE);
}


void CSDIMenuView::OnUpdateDrawPolygon(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck((m_nDrawMode == POLYGON_MODE) ? TRUE : FALSE);
}


void CSDIMenuView::OnUpdateDrawSquare(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck((m_nDrawMode == SQUARE_MODE) ? TRUE : FALSE);
}


void CSDIMenuView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CString strPoint;
	strPoint.Format(_T("마우스 위치 x:%d, y:%d"), point.x, point.y);

	pFrame->m_wndStatusBar.SetPaneText(1, strPoint);

	//====================================================================

	CClientDC dc(this);							// 클라이언트 객체 얻음
	CPen pen, *oldpen;
	pen.CreatePen(PS_SOLID, 1, m_colorPen);		// Pen 객체 생성
	oldpen = dc.SelectObject(&pen);				// Pen 객체 등록

	dc.SetROP2(R2_NOTXORPEN);					// R2_NOTXORPEN으로 설정

	CBrush brush, *oldbrush;
	if (m_bHatch)
		brush.CreateHatchBrush(m_nHatchStyle, m_colorBrush);	// Hatch Brush 객체 생성
	else
		brush.CreateSolidBrush(m_colorBrush);	// Solid Brush 객체 생성

	oldbrush = dc.SelectObject(&brush);			// brush 객체 등록

	switch (m_nDrawMode)
	{
	case LINE_MODE:								// 직선 그리기
		if (m_bLButtonDown)
		{
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptPrev);				// 이전 직선 지움
			dc.MoveTo(m_ptStart);
			dc.LineTo(point);					// 현재 직선 그림
			m_ptPrev = point;					// 이전 점에 현재 점을 저장
		}
		break;

	case ELLIPSE_MODE:							// 원 그리기
		if (m_bLButtonDown)
		{
			dc.Ellipse(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
			dc.Ellipse(m_ptStart.x, m_ptStart.y, point.x, point.y);
			m_ptPrev = point;					// 이전 점에 현재 점을 저장
		}
		break;

	case SQUARE_MODE:
		if (m_bLButtonDown)
		{
			dc.Rectangle(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
			dc.Rectangle(m_ptStart.x, m_ptStart.y, point.x, point.y);
			m_ptPrev = point;					// 이전 점에 현재 점을 저장
		}
		break;

	case POLYGON_MODE:							// 다각형 그리기
		if (!m_bFirst)
		{
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptPrev);
			dc.MoveTo(m_ptStart);
			dc.LineTo(point);
			m_ptPrev = point;					// 이전 점에 현재 점을 저장
		}
		break;

	}
	dc.SelectObject(oldpen);					// 이전 pen으로 설정
	dc.SelectObject(oldbrush);					// 이전 brush로 설정
	pen.DeleteObject();							// pen 객체 삭제
	brush.DeleteObject();						// brush 객체 삭제

	CView::OnMouseMove(nFlags, point);
}


void CSDIMenuView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bFirst)
	{
		m_ptStart = m_ptPrev = 0;
		m_bLButtonDown = false;
		m_nCount = 0;
		for (int i = 0; i < 100; i++)	m_ptData[i] = 0;
		UpdateData();
		Invalidate(false);
	}
	
	switch (m_nDrawMode)
	{
	case LINE_MODE:
	case SQUARE_MODE:
	case ELLIPSE_MODE:
		m_bLButtonDown = true;				// 왼쪽버튼이 눌림
		m_ptStart = m_ptPrev = point;		// 시작점과 이전 점에 현재 점을 저장
		m_bFirst = false;					// 처음 그리는 것
		break;
	case POLYGON_MODE:
		if (m_bFirst == true)	m_bFirst = false;	// 처음 그리는 것 -> false
		m_ptStart = m_ptPrev = point;		// 시작점과 이전 점에 현재 점을 저장
		m_ptData[m_nCount] = point;			// 현재 점을 저장
		m_nCount++;							// 카운트 증가
		break;
	}

	RECT rectClient;						// 구조체 변수 선언
	SetCapture();							// 마우스 캡처
	GetClientRect(&rectClient);				// 클라이언트 영역 받음
	ClientToScreen(&rectClient);			// 스크린 좌표계 변환
	::ClipCursor(&rectClient);				// 마우스 이동범위를 클라이언트 영역으로 제한

	CView::OnLButtonDown(nFlags, point);
}


void CSDIMenuView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bLButtonDown)
	{
		if (m_nDrawMode == LINE_MODE || m_nDrawMode == ELLIPSE_MODE || m_nDrawMode == SQUARE_MODE)
		{
			m_bLButtonDown = false;
			m_bFirst = true;
			ReleaseCapture();				// 마우스 캡처 해제
			::ClipCursor(NULL);				// 마우스 클립 해제
			UpdateData();
			Invalidate(false);				// 화면 갱신
		}
	}
	CView::OnLButtonUp(nFlags, point);
}


void CSDIMenuView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_nDrawMode == POLYGON_MODE)
	{
		if (!m_bFirst)
		{
			m_bContextMenu = FALSE;			// 처음 그리는 것이 아니면

			m_ptData[m_nCount] = point;		// 컨텍스트 메뉴 비활성
			m_nCount++;						// 배열에 현재 점을 저장하고 카운트 증가
			// 체크 변수 초기화 => 다시 다각형을 그리기 위해
			m_bFirst = true;
			ReleaseCapture();				// 마우스 캡처 해제
			::ClipCursor(NULL);				// 마우스 클립 해제
			Invalidate(false);				// 화면 갱신
		}
	}
	CView::OnRButtonDown(nFlags, point);
}
