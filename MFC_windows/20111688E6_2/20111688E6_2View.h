
// 20111688E6_2View.h : CMy20111688E6_2View Ŭ������ �������̽�
//

#pragma once
#include "atltypes.h"
#include "20111688E6_2Doc.h"

class CMy20111688E6_2View : public CView
{
protected: // serialization������ ��������ϴ�.
	CMy20111688E6_2View();
	DECLARE_DYNCREATE(CMy20111688E6_2View)

// Ư���Դϴ�.
public:
	CMy20111688E6_2Doc* GetDocument() const;

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
	virtual ~CMy20111688E6_2View();
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
	CString m_strOutText; // ���ڿ� ���� ����
	BOOL m_bFont; // ��Ʈ�� ��ȭ���ڿ� �����Ǿ����� ��Ÿ��
	LOGFONT m_logfont; // ��Ʈ�� ������ ����
	COLORREF m_colorText; // ���ڿ� ���� ���� ����
	CPoint m_ptPosition; // ���ڿ� ��� ��ġ ���� ����
	int m_nTextHeight; // ��µ� ���ڿ��� ���� ���� ����
	int m_nTextWidth; // ��µ� ���ڿ� �ʺ� ���� ����
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	CString strX;
	CString strY;
	afx_msg void OnDestroy();
	afx_msg void OnEnChangeEditX();
};

#ifndef _DEBUG  // 20111688E6_2View.cpp�� ����� ����
inline CMy20111688E6_2Doc* CMy20111688E6_2View::GetDocument() const
   { return reinterpret_cast<CMy20111688E6_2Doc*>(m_pDocument); }
#endif

