
// SDIMenuView.h : CSDIMenuView Ŭ������ �������̽�
//

#pragma once
#include "atltypes.h"


class CSDIMenuView : public CView
{
protected: // serialization������ ��������ϴ�.
	CSDIMenuView();
	DECLARE_DYNCREATE(CSDIMenuView)

// Ư���Դϴ�.
public:
	CSDIMenuDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CSDIMenuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawLine();
	afx_msg void OnDrawEllipse();
	afx_msg void OnDrawPolygon();
	afx_msg void OnDrawSquare();
	afx_msg void OnColorLine();
	afx_msg void OnColorFace();
	afx_msg void OnPat45();
	afx_msg void OnPatCross();
	afx_msg void OnPatVer();
	int m_nDrawMode;
	int m_nHatchStyle;
//	afx_msg void OnUpdateColorLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawEllipse(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawPolygon(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawSquare(CCmdUI *pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CPoint m_ptStart;
	CPoint m_ptPrev;
	bool m_bFirst;
	bool m_bLButtonDown;
	bool m_bContextMenu;
	bool m_bHatch;
	CPoint m_ptData[100];
	int m_nCount;
	COLORREF m_colorPen;
	COLORREF m_colorBrush;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // SDIMenuView.cpp�� ����� ����
inline CSDIMenuDoc* CSDIMenuView::GetDocument() const
   { return reinterpret_cast<CSDIMenuDoc*>(m_pDocument); }
#endif

