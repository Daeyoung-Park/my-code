
// 20111688E6_1View.cpp : CMy20111688E6_1View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "20111688E6_1.h"
#endif

#include "20111688E6_1Doc.h"
#include "20111688E6_1View.h"
#include "PenSizeDialog.h"
#include "EraserDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy20111688E6_1View

IMPLEMENT_DYNCREATE(CMy20111688E6_1View, CView)

BEGIN_MESSAGE_MAP(CMy20111688E6_1View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy20111688E6_1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_PEN_SIZE, &CMy20111688E6_1View::OnPenSize)
	ON_COMMAND(ID_PEN_COLOR, &CMy20111688E6_1View::OnPenColor)
	ON_COMMAND(ID_ERASER_SIZE, &CMy20111688E6_1View::OnEraserSize)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMy20111688E6_1View ����/�Ҹ�

CMy20111688E6_1View::CMy20111688E6_1View()
	: m_nPenSize(1)
	, m_nEraserSize(4)
	, m_ptPrev(0)
	, m_nDrawMode(false)
	, m_nEraserMode(false)
	, m_nClickAndMove(false)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_colorPen = RGB(0,0,0);
}

CMy20111688E6_1View::~CMy20111688E6_1View()
{
}

BOOL CMy20111688E6_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMy20111688E6_1View �׸���

void CMy20111688E6_1View::OnDraw(CDC* pDC)
{
	CMy20111688E6_1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	HDC hdc = CreateCompatibleDC(pDC->GetSafeHdc());
	CRect ClientRect;
	GetClientRect(&ClientRect);
	
	Rectangle(hdc,ClientRect.left-1,ClientRect.top-1,ClientRect.right+1,ClientRect.bottom+1);
	
	Graphics graphics(hdc);
	

	if(m_nDrawMode == true && m_nClickAndMove == true)
	{
		Gdiplus::Color cr;
		cr.SetFromCOLORREF(m_colorPen);
		Pen pen(Color(cr),m_nPenSize);
		
		graphics.DrawLine(&pen,m_ptPrev.x,m_ptPrev.y,m_ptPrev.x-0.1,m_ptPrev.y-0.1);
	}

	if(m_nEraserMode == true && m_nClickAndMove == true)
	{
		Gdiplus::Color cr;
		cr.SetFromCOLORREF(RGB(255,255,255));
		Pen pen(Color(cr),m_nEraserSize);

		graphics.DrawLine(&pen,m_ptPrev.x,m_ptPrev.y,m_ptPrev.x-0.1,m_ptPrev.y-0.1);
	}
	
	::BitBlt(pDC->GetSafeHdc(),ClientRect.left,
		ClientRect.top,
		ClientRect.Width(),
		ClientRect.Height(),
		hdc,
		ClientRect.left,
		ClientRect.top,
		SRCCOPY);

	DeleteDC(hdc);
	
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CMy20111688E6_1View �μ�


void CMy20111688E6_1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy20111688E6_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMy20111688E6_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMy20111688E6_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CMy20111688E6_1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);

	m_nEraserMode = false;

	ReleaseCapture();
	::ClipCursor(NULL);
}

void CMy20111688E6_1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy20111688E6_1View ����

#ifdef _DEBUG
void CMy20111688E6_1View::AssertValid() const
{
	CView::AssertValid();
}

void CMy20111688E6_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy20111688E6_1Doc* CMy20111688E6_1View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy20111688E6_1Doc)));
	return (CMy20111688E6_1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy20111688E6_1View �޽��� ó����


void CMy20111688E6_1View::OnPenSize()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CPenSizeDialog* pDlgPen = new CPenSizeDialog();
	if(pDlgPen->DoModal() == IDOK)
	{
		m_nPenSize = (int)pDlgPen->m_editPenSize;
	}
}


void CMy20111688E6_1View::OnPenColor()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CColorDialog dlgColor;
	if(dlgColor.DoModal()==IDOK)
	{
		m_colorPen = dlgColor.GetColor();
	}

}


void CMy20111688E6_1View::OnEraserSize()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CEraserDialog* pDlgEraser = new CEraserDialog();
	if(pDlgEraser->DoModal() == IDOK)
	{
		m_nEraserSize = (int)pDlgEraser->m_editEraserSize;
	}
}


void CMy20111688E6_1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_nDrawMode = true;

	m_ptPrev = point;

	RECT rectClient;
	GetClientRect(&rectClient);
	ClientToScreen(&rectClient);
	SetCapture();
	::ClipCursor(&rectClient);

	CView::OnLButtonDown(nFlags, point);
}


void CMy20111688E6_1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_nEraserMode = true;

	m_ptPrev = point;

	RECT rectClient;
	GetClientRect(&rectClient);
	ClientToScreen(&rectClient);
	SetCapture();
	::ClipCursor(&rectClient);

	CView::OnRButtonDown(nFlags, point);
}


void CMy20111688E6_1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	m_nDrawMode = false;

	ReleaseCapture();
	::ClipCursor(NULL);

	CView::OnLButtonUp(nFlags, point);
}


void CMy20111688E6_1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CClientDC dc(this);
	Graphics graphics(dc);
	

	if(m_nDrawMode)
	{
		m_nClickAndMove = true;

		Gdiplus::Color cr;
		cr.SetFromCOLORREF(m_colorPen);
		Pen pen(Color(cr),m_nPenSize);

		graphics.DrawLine(&pen,m_ptPrev.x,m_ptPrev.y,point.x,point.y);

		m_ptPrev = point;
	}

	if(m_nEraserMode)
	{
		m_nClickAndMove = true;

		Gdiplus::Color cr;
		cr.SetFromCOLORREF(RGB(255,255,255));
		Pen pen(Color(cr),m_nEraserSize);

		graphics.DrawLine(&pen,m_ptPrev.x,m_ptPrev.y,point.x,point.y);

		m_ptPrev = point;
	}

	CView::OnMouseMove(nFlags, point);
}
