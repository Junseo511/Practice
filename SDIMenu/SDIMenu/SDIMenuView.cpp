
// SDIMenuView.cpp : CSDIMenuView Ŭ������ ����
//
#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
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

// ��� ����

enum DRAW_MODE { LINE_MODE, ELLIPSE_MODE, POLYGON_MODE, SQUARE_MODE };

// CSDIMenuView ����/�Ҹ�

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
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CSDIMenuView �׸���


void CSDIMenuView::OnDraw(CDC* pDC)
{
	CSDIMenuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	CPen pen, *oldpen;											// pen ��ü ����
	pen.CreatePen(PS_SOLID, 1, m_colorPen);						// pen ��ü ���
	oldpen = pDC->SelectObject(&pen);							// COPYPEN���� ����
	pDC->SetROP2(R2_COPYPEN);

	CBrush brush, *oldbrush;
	if (m_bHatch)
		brush.CreateHatchBrush(m_nHatchStyle, m_colorBrush);	// brush ��ü ����
	else
		brush.CreateSolidBrush(m_colorBrush);					// brush ��ü ���
	oldbrush = pDC->SelectObject(&brush);

	switch (m_nDrawMode)
	{
	case LINE_MODE:												// ���� �׸���
		pDC->MoveTo(m_ptStart);
		pDC->LineTo(m_ptPrev);
		break;
	case ELLIPSE_MODE:											// �� �׸���
		pDC->Ellipse(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
		break;
	case SQUARE_MODE:											// �簢�� �׸���
		pDC->Rectangle(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
		break;
	case POLYGON_MODE:											// �ٰ��� �׸���
		pDC->Polygon(m_ptData, m_nCount);						// �迭�� ������ ������� ������ ������ �ٰ��� �׸���
		break;
	}
	pDC->SelectObject(oldpen);									// ���� pen���� ����
	pDC->SelectObject(oldbrush);								// ���� brush�� ����
	pen.DeleteObject();											// pen ��ü ����
	brush.DeleteObject();										// brush ��ü ����
}


// CSDIMenuView �μ�


void CSDIMenuView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSDIMenuView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CSDIMenuView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CSDIMenuView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
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


// CSDIMenuView ����

#ifdef _DEBUG
void CSDIMenuView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIMenuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIMenuDoc* CSDIMenuView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIMenuDoc)));
	return (CSDIMenuDoc*)m_pDocument;
}
#endif //_DEBUG


// CSDIMenuView �޽��� ó����


void CSDIMenuView::OnDrawLine()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// MessageBox(_T("������ �׸��ϴ�."));
	m_nDrawMode = LINE_MODE;
	
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_wndStatusBar.SetWindowTextW(_T("�����׸���"));
}


void CSDIMenuView::OnDrawEllipse()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// MessageBox(_T("���� �׸��ϴ�."));
	m_nDrawMode = ELLIPSE_MODE;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_wndStatusBar.SetWindowTextW(_T("���׸���"));
}


void CSDIMenuView::OnDrawPolygon()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// MessageBox(_T("�ٰ����� �׸��ϴ�."));
	m_nDrawMode = POLYGON_MODE;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_wndStatusBar.SetWindowTextW(_T("�ٰ����׸���"));
}


void CSDIMenuView::OnDrawSquare()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// MessageBox(_T("�簢���� �׸��ϴ�."));
	m_nDrawMode = SQUARE_MODE;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_wndStatusBar.SetWindowTextW(_T("�簢���׸���"));
}


void CSDIMenuView::OnColorLine()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// MessageBox(_T("���� ���� �����մϴ�."));
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// MessageBox(_T("���� ���� �����մϴ�."));
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// MessageBox(_T("���̸� ���� 45���� �����մϴ�."));
	m_nHatchStyle = HS_BDIAGONAL;
	m_bHatch = TRUE;
	Invalidate(false);
}


void CSDIMenuView::OnPatCross()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// MessageBox(_T("���̸� ���ڰ��� �����մϴ�."));
	m_nHatchStyle = HS_CROSS;
	m_bHatch = TRUE;
	Invalidate(false);
}


void CSDIMenuView::OnPatVer()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// MessageBox(_T("���̸� ���������� �����մϴ�."));
	m_nHatchStyle = HS_VERTICAL;
	m_bHatch = TRUE;
	Invalidate(false);
}


//void CSDIMenuView::OnUpdateColorLine(CCmdUI *pCmdUI)
//{
//	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
//}


void CSDIMenuView::OnUpdateDrawLine(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck((m_nDrawMode == LINE_MODE)? TRUE : FALSE);
}


void CSDIMenuView::OnUpdateDrawEllipse(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck((m_nDrawMode == ELLIPSE_MODE) ? TRUE : FALSE);
}


void CSDIMenuView::OnUpdateDrawPolygon(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck((m_nDrawMode == POLYGON_MODE) ? TRUE : FALSE);
}


void CSDIMenuView::OnUpdateDrawSquare(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck((m_nDrawMode == SQUARE_MODE) ? TRUE : FALSE);
}


void CSDIMenuView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CString strPoint;
	strPoint.Format(_T("���콺 ��ġ x:%d, y:%d"), point.x, point.y);

	pFrame->m_wndStatusBar.SetPaneText(1, strPoint);

	//====================================================================

	CClientDC dc(this);							// Ŭ���̾�Ʈ ��ü ����
	CPen pen, *oldpen;
	pen.CreatePen(PS_SOLID, 1, m_colorPen);		// Pen ��ü ����
	oldpen = dc.SelectObject(&pen);				// Pen ��ü ���

	dc.SetROP2(R2_NOTXORPEN);					// R2_NOTXORPEN���� ����

	CBrush brush, *oldbrush;
	if (m_bHatch)
		brush.CreateHatchBrush(m_nHatchStyle, m_colorBrush);	// Hatch Brush ��ü ����
	else
		brush.CreateSolidBrush(m_colorBrush);	// Solid Brush ��ü ����

	oldbrush = dc.SelectObject(&brush);			// brush ��ü ���

	switch (m_nDrawMode)
	{
	case LINE_MODE:								// ���� �׸���
		if (m_bLButtonDown)
		{
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptPrev);				// ���� ���� ����
			dc.MoveTo(m_ptStart);
			dc.LineTo(point);					// ���� ���� �׸�
			m_ptPrev = point;					// ���� ���� ���� ���� ����
		}
		break;

	case ELLIPSE_MODE:							// �� �׸���
		if (m_bLButtonDown)
		{
			dc.Ellipse(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
			dc.Ellipse(m_ptStart.x, m_ptStart.y, point.x, point.y);
			m_ptPrev = point;					// ���� ���� ���� ���� ����
		}
		break;

	case SQUARE_MODE:
		if (m_bLButtonDown)
		{
			dc.Rectangle(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
			dc.Rectangle(m_ptStart.x, m_ptStart.y, point.x, point.y);
			m_ptPrev = point;					// ���� ���� ���� ���� ����
		}
		break;

	case POLYGON_MODE:							// �ٰ��� �׸���
		if (!m_bFirst)
		{
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptPrev);
			dc.MoveTo(m_ptStart);
			dc.LineTo(point);
			m_ptPrev = point;					// ���� ���� ���� ���� ����
		}
		break;

	}
	dc.SelectObject(oldpen);					// ���� pen���� ����
	dc.SelectObject(oldbrush);					// ���� brush�� ����
	pen.DeleteObject();							// pen ��ü ����
	brush.DeleteObject();						// brush ��ü ����

	CView::OnMouseMove(nFlags, point);
}


void CSDIMenuView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
		m_bLButtonDown = true;				// ���ʹ�ư�� ����
		m_ptStart = m_ptPrev = point;		// �������� ���� ���� ���� ���� ����
		m_bFirst = false;					// ó�� �׸��� ��
		break;
	case POLYGON_MODE:
		if (m_bFirst == true)	m_bFirst = false;	// ó�� �׸��� �� -> false
		m_ptStart = m_ptPrev = point;		// �������� ���� ���� ���� ���� ����
		m_ptData[m_nCount] = point;			// ���� ���� ����
		m_nCount++;							// ī��Ʈ ����
		break;
	}

	RECT rectClient;						// ����ü ���� ����
	SetCapture();							// ���콺 ĸó
	GetClientRect(&rectClient);				// Ŭ���̾�Ʈ ���� ����
	ClientToScreen(&rectClient);			// ��ũ�� ��ǥ�� ��ȯ
	::ClipCursor(&rectClient);				// ���콺 �̵������� Ŭ���̾�Ʈ �������� ����

	CView::OnLButtonDown(nFlags, point);
}


void CSDIMenuView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_bLButtonDown)
	{
		if (m_nDrawMode == LINE_MODE || m_nDrawMode == ELLIPSE_MODE || m_nDrawMode == SQUARE_MODE)
		{
			m_bLButtonDown = false;
			m_bFirst = true;
			ReleaseCapture();				// ���콺 ĸó ����
			::ClipCursor(NULL);				// ���콺 Ŭ�� ����
			UpdateData();
			Invalidate(false);				// ȭ�� ����
		}
	}
	CView::OnLButtonUp(nFlags, point);
}


void CSDIMenuView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_nDrawMode == POLYGON_MODE)
	{
		if (!m_bFirst)
		{
			m_bContextMenu = FALSE;			// ó�� �׸��� ���� �ƴϸ�

			m_ptData[m_nCount] = point;		// ���ؽ�Ʈ �޴� ��Ȱ��
			m_nCount++;						// �迭�� ���� ���� �����ϰ� ī��Ʈ ����
			// üũ ���� �ʱ�ȭ => �ٽ� �ٰ����� �׸��� ����
			m_bFirst = true;
			ReleaseCapture();				// ���콺 ĸó ����
			::ClipCursor(NULL);				// ���콺 Ŭ�� ����
			Invalidate(false);				// ȭ�� ����
		}
	}
	CView::OnRButtonDown(nFlags, point);
}
