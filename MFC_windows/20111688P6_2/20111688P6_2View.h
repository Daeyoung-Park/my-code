
// 20111688P6_2View.h : CMy20111688P6_2View Ŭ������ �������̽�
//
#include "MainFrm.h"
#include "atltypes.h"
#include "gdiplustypes.h"
#define RECTANGLE_MODE		1
#define CIRCLE_MODE			2

#pragma once

#include "math.h"
#define M_PI	3.141592649

class CMy20111688P6_2View : public CView
{
protected: // serialization������ ��������ϴ�.
	CMy20111688P6_2View();
	DECLARE_DYNCREATE(CMy20111688P6_2View)

// Ư���Դϴ�.
public:
	CMy20111688P6_2Doc* GetDocument() const;

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
	virtual ~CMy20111688P6_2View();
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
	int m_nDrawMode;
	afx_msg void OnRectangle();
	afx_msg void OnCircle();
	afx_msg void OnIncrease();
	afx_msg void OnDecrease();
	CPoint m_ptStart; // ������ ����
	CPoint m_ptPrev; // ������ ����
	bool m_bLButtonDown; // ���� ��ư ���ȴ���
	CRect m_rtRect; // �簢�� ��ǥ ����
	Point m_ptCircle[1025]; // �� ��ǥ ����
	int m_nResolution; // �ػ� ����
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void computeCircle(void);
};

#ifndef _DEBUG  // 20111688P6_2View.cpp�� ����� ����
inline CMy20111688P6_2Doc* CMy20111688P6_2View::GetDocument() const
   { return reinterpret_cast<CMy20111688P6_2Doc*>(m_pDocument); }
#endif

