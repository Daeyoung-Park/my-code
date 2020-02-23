
// 2011688P5_1View.h : CMy2011688P5_1View Ŭ������ �������̽�
//
#include "atltypes.h"
enum DRAW{DRAW_NONE, LINE_MODE, ELLIPSE_MODE, POLYGON_MODE};
#pragma once


class CMy2011688P5_1View : public CView
{
protected: // serialization������ ��������ϴ�.
	CMy2011688P5_1View();
	DECLARE_DYNCREATE(CMy2011688P5_1View)

// Ư���Դϴ�.
public:
	CMy2011688P5_1Doc* GetDocument() const;

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
	virtual ~CMy2011688P5_1View();
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
	afx_msg void OnLine();
	afx_msg void OnEllipse();
	afx_msg void OnPolygon();
	afx_msg void OnLineColor();
	afx_msg void OnFaceColor();
//	afx_msg void OnUpdateLineColor(CCmdUI *pCmdUI);
//	afx_msg void OnUpdateFaceColor(CCmdUI *pCmdUI);
	afx_msg void OnBdiagonal();
	afx_msg void OnCross();
	afx_msg void OnVertical();
	afx_msg void OnShowBitmap();
//	afx_msg void OnAfxIdcMagnify();
	afx_msg void OnReduceBitmap();
	afx_msg void OnAlphaBlend();
	afx_msg void OnMagnifyBitmap();
	int m_nDrawMode;
	int m_nHatchStyle;
	int m_nBitmapMode;
	afx_msg void OnUpdateLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEllipse(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePolygon(CCmdUI *pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CPoint m_ptStart; // ������ �����ϴ� ����
	CPoint m_ptPrev; // ���� �� �����ϴ� ���� -> ������带 �׸��� ����
	bool m_bFirst; // ó�� �׸��� ������ üũ�ϴ� ����
	bool m_bLButtonDown; // ���� ��ư ���ȴ���
	bool m_bContextMenu; // ���ؽ�Ʈ �޴��� Ȱ��ȭ üũ�ϴ� ����
	bool m_bHatch; // ��ġ �귯�ø� ����ϴ��� Ȯ���ϴ� ����
	CPoint m_ptData[50]; // �ٰ��� ���� ������ �迭
	int m_nCount; // m_ptData �迭�� ī��Ʈ ��, �ٰ����� ���� ���� ������ �����ϴ� ����
	COLORREF m_colorPen; // �� ������ �����ϴ� ����
	COLORREF m_colorBrush; // �귯�� ������ �����ϴ� ����
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // 2011688P5_1View.cpp�� ����� ����
inline CMy2011688P5_1Doc* CMy2011688P5_1View::GetDocument() const
   { return reinterpret_cast<CMy2011688P5_1Doc*>(m_pDocument); }
#endif

