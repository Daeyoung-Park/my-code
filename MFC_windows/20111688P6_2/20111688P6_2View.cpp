
// 20111688P6_2View.cpp : CMy20111688P6_2View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "20111688P6_2.h"
#endif

#include "20111688P6_2Doc.h"
#include "20111688P6_2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy20111688P6_2View

IMPLEMENT_DYNCREATE(CMy20111688P6_2View, CView)

BEGIN_MESSAGE_MAP(CMy20111688P6_2View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy20111688P6_2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_RECTANGLE, &CMy20111688P6_2View::OnRectangle)
	ON_COMMAND(ID_CIRCLE, &CMy20111688P6_2View::OnCircle)
	ON_COMMAND(ID_INCREASE, &CMy20111688P6_2View::OnIncrease)
	ON_COMMAND(ID_DECREASE, &CMy20111688P6_2View::OnDecrease)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMy20111688P6_2View ����/�Ҹ�

CMy20111688P6_2View::CMy20111688P6_2View()
	: m_nDrawMode(0)
	, m_ptStart(0)
	, m_ptPrev(0)
	, m_bLButtonDown(false)
	, m_nResolution(0)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_bLButtonDown = FALSE;

	m_rtRect = CRect(0,0,0,0);
	m_nResolution = 64;
	for(int i=0; i<1024; i++)
		m_ptCircle[i] = Point(0,0);
}

CMy20111688P6_2View::~CMy20111688P6_2View()
{
}

BOOL CMy20111688P6_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMy20111688P6_2View �׸���

void CMy20111688P6_2View::OnDraw(CDC* pDC)
{
	CMy20111688P6_2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	HDC hdc = CreateCompatibleDC(pDC->GetSafeHdc()); // ���� ���۷� ����� DC ����
	CRect ClientRect; 
	int i;
	GetClientRect(&ClientRect); // ���� Ŭ���̾�Ʈ ���� ũ�� ���ϱ�
	HBITMAP bitmap = CreateCompatibleBitmap(hdc,ClientRect.Width(),ClientRect.Height()); // ���� ȭ�� ũ���� ��Ʈ�� ����

	SelectObject(hdc,bitmap); // ������ ��Ʈ���� ������� DC�� ����
	Rectangle(hdc,ClientRect.left-1,ClientRect.top-1,ClientRect.right+1,ClientRect.bottom+1); // ������� DC�� ������� ä��
	
	Graphics graphics(hdc); // ������۷� ����� dc�� �������ڷ� gdi+ ��ü ����
	Pen pen(Color(0,0,0),1); // pen ����

	switch(m_nDrawMode)
	{
	case RECTANGLE_MODE: // �簢�� �׸��� ����϶�
		graphics.DrawRectangle(&pen,m_rtRect.left,m_rtRect.top,m_rtRect.Width(),m_rtRect.Height());
		break;
	case CIRCLE_MODE: // �� �׸��� ����϶�
		graphics.DrawRectangle(&pen,m_rtRect.left,m_rtRect.top,m_rtRect.Width()-1,m_rtRect.Height()-1);
		pDC->IntersectClipRect(m_rtRect); // ũ���� ���� ����
		
		computeCircle();
		for(i=1; i< m_nResolution; i++)
		{
			graphics.DrawLine(&pen,m_ptCircle[i-1],m_ptCircle[i]);
		}

		graphics.DrawLine(&pen,m_ptCircle[i-1],m_ptCircle[0]);
	}

	::BitBlt(pDC->GetSafeHdc(),ClientRect.left,ClientRect.top,ClientRect.Width(), // �������dc�� �׸� ���� ���� dc�� �Űܼ� �׸�
		ClientRect.Height(),hdc,ClientRect.left,ClientRect.top,SRCCOPY);

	DeleteDC(hdc);
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CMy20111688P6_2View �μ�


void CMy20111688P6_2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy20111688P6_2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMy20111688P6_2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMy20111688P6_2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CMy20111688P6_2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy20111688P6_2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy20111688P6_2View ����

#ifdef _DEBUG
void CMy20111688P6_2View::AssertValid() const
{
	CView::AssertValid();
}

void CMy20111688P6_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy20111688P6_2Doc* CMy20111688P6_2View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy20111688P6_2Doc)));
	return (CMy20111688P6_2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy20111688P6_2View �޽��� ó����


void CMy20111688P6_2View::OnRectangle()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_nDrawMode = RECTANGLE_MODE;
}


void CMy20111688P6_2View::OnCircle()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_nDrawMode = CIRCLE_MODE;
}


void CMy20111688P6_2View::OnIncrease()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if(m_nResolution >= 1024)
	{
		AfxMessageBox(_T("���� �ִ� �ػ��� 1024�Դϴ�."));
	}
	else
	{
		m_nResolution = m_nResolution * 2;
	}
	Invalidate();

	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CString strResol;
	strResol.Format(_T("�ػ� : %d "),m_nResolution);
	pFrame->m_wndStatusBar.SetPaneText(1,strResol);
}


void CMy20111688P6_2View::OnDecrease()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if(m_nResolution <= 2)
	{
		AfxMessageBox(_T("���� �ּ� �ػ��� 2�Դϴ�."));
	}
	else
	{
		m_nResolution = m_nResolution / 2;
	}
	
	Invalidate();

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CString strResol;
	strResol.Format(_T("�ػ� : %d"),m_nResolution);
	pFrame->m_wndStatusBar.SetPaneText(1,strResol);
}


void CMy20111688P6_2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch(m_nDrawMode)
	{
	case RECTANGLE_MODE:
		m_rtRect = CRect(0,0,0,0);

	case CIRCLE_MODE:
		m_ptStart = m_ptPrev = point;
		m_bLButtonDown = true;
		for(int i=0; i<1024; i++)
			m_ptCircle[i] = Point(0,0); // �� �ʱ�ȭ

		Invalidate(TRUE);

		RECT rectClient; // �簢 ����ü ���� ����
		SetCapture(); // ���콺 ĸó
		GetClientRect(&rectClient); // Ŭ���̾�Ʈ ���� ����
		ClientToScreen(&rectClient); // ��ũ�� ��ǥ��� ��ȯ
		::ClipCursor(&rectClient); // ���콺 �̵� ���� Ŭ���̾�Ʈ �������� ����
		break;
	}
	CView::OnLButtonDown(nFlags, point);
}


void CMy20111688P6_2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CClientDC dc(this);

	Graphics graphics(dc);
	Pen pen(Color(0,0,0),1); // ���� ������ �׷��� ��ü ����
	Pen XORpen(Color(255,255,255),1); // ���� ������ �׷��� ��ü ����

	switch(m_nDrawMode)
	{
	case RECTANGLE_MODE:
		if(m_bLButtonDown)
		{
			CRect PrevRect = CRect(m_ptStart.x,m_ptStart.y,m_ptPrev.x,m_ptPrev.y); // ���� �簢�� ��ǥ ����
			CRect CurRect = CRect(m_ptStart.x,m_ptStart.y,point.x,point.y); // ���� �簢�� ��ǥ ����
			
			graphics.DrawRectangle(&XORpen,PrevRect.left,PrevRect.top,PrevRect.Width(),PrevRect.Height()); // ���� �簢�� ����
			graphics.DrawRectangle(&pen,CurRect.left,CurRect.top,CurRect.Width(),CurRect.Height()); // ���� �簢�� ����

			m_ptPrev = point;
		}
		break;
	case CIRCLE_MODE:
		if(m_bLButtonDown)
		{
			m_ptPrev = point;
			Invalidate();
		}
		break;
	}

	CView::OnMouseMove(nFlags, point);
}


void CMy20111688P6_2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch(m_nDrawMode)
	{
	case RECTANGLE_MODE:
		if(m_bLButtonDown)
		{
			m_bLButtonDown = false;
			m_rtRect = CRect(m_ptStart.x,m_ptStart.y,point.x,point.y);
		}
		break;
	case CIRCLE_MODE:
		if(m_bLButtonDown)
		{
			m_bLButtonDown = false;
			m_ptPrev = point;
		}
		break;
	}

	ReleaseCapture();
	::ClipCursor(NULL);
	Invalidate(true);

	CView::OnLButtonUp(nFlags, point);
}


void CMy20111688P6_2View::computeCircle(void)
{
	double x,y,r,radian;

	r = sqrt( (double) ( (m_ptStart.x - m_ptPrev.x)*(m_ptStart.x - m_ptPrev.x) + (m_ptStart.y - m_ptPrev.y)*(m_ptStart.y - m_ptPrev.y) ) );
	radian = M_PI * 2 / (double)m_nResolution;

	for(int i=0; i<m_nResolution; i++) // �ػ󵵿� ���� ���� ��ǥ
	{
		x = m_ptStart.x + r*cos(radian*i);
		y = m_ptStart.y + r*sin(radian*i);
		m_ptCircle[i] = Point(x,y);
	}
}
