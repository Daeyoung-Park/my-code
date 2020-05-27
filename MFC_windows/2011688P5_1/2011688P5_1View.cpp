
// 2011688P5_1View.cpp : CMy2011688P5_1View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "2011688P5_1.h"
#endif

#include "2011688P5_1Doc.h"
#include "2011688P5_1View.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy2011688P5_1View

IMPLEMENT_DYNCREATE(CMy2011688P5_1View, CView)

BEGIN_MESSAGE_MAP(CMy2011688P5_1View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy2011688P5_1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_LINE, &CMy2011688P5_1View::OnLine)
	ON_COMMAND(ID_ELLIPSE, &CMy2011688P5_1View::OnEllipse)
	ON_COMMAND(ID_POLYGON, &CMy2011688P5_1View::OnPolygon)
	ON_COMMAND(ID_LINE_COLOR, &CMy2011688P5_1View::OnLineColor)
	ON_COMMAND(ID_FACE_COLOR, &CMy2011688P5_1View::OnFaceColor)
//	ON_UPDATE_COMMAND_UI(ID_LINE_COLOR, &CMy2011688P5_1View::OnUpdateLineColor)
//	ON_UPDATE_COMMAND_UI(ID_FACE_COLOR, &CMy2011688P5_1View::OnUpdateFaceColor)
	ON_COMMAND(ID_BDIAGONAL, &CMy2011688P5_1View::OnBdiagonal)
	ON_COMMAND(ID_CROSS, &CMy2011688P5_1View::OnCross)
	ON_COMMAND(ID_VERTICAL, &CMy2011688P5_1View::OnVertical)
	ON_COMMAND(ID__SHOW_BITMAP, &CMy2011688P5_1View::OnShowBitmap)
//	ON_COMMAND(AFX_IDC_MAGNIFY, &CMy2011688P5_1View::OnAfxIdcMagnify)
	ON_COMMAND(ID_REDUCE_BITMAP, &CMy2011688P5_1View::OnReduceBitmap)
	ON_COMMAND(ID_ALPHA_BLEND, &CMy2011688P5_1View::OnAlphaBlend)
	ON_COMMAND(ID_MAGNIFY_BITMAP, &CMy2011688P5_1View::OnMagnifyBitmap)
	ON_UPDATE_COMMAND_UI(ID_LINE, &CMy2011688P5_1View::OnUpdateLine)
	ON_UPDATE_COMMAND_UI(ID_ELLIPSE, &CMy2011688P5_1View::OnUpdateEllipse)
	ON_UPDATE_COMMAND_UI(ID_POLYGON, &CMy2011688P5_1View::OnUpdatePolygon)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CMy2011688P5_1View ����/�Ҹ�

CMy2011688P5_1View::CMy2011688P5_1View()
	: m_nDrawMode(0)
	, m_nHatchStyle(0)
	, m_nBitmapMode(0)
	, m_ptStart(0)
	, m_ptPrev(0)
	, m_bFirst(false)
	, m_bLButtonDown(false)
	, m_bContextMenu(false)
	, m_bHatch(false)
	, m_nCount(0)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_nDrawMode = LINE_MODE; // �׸��� ��� : ������ �׸���
	m_bContextMenu = true; 
	m_bFirst = true; 
	m_bLButtonDown = false;
	m_nCount = 0;
	
	for(int i=0; i<50; i++)
	{
		m_ptData[i] = 0; // �迭 �ʱ�ȭ
	}
	m_bHatch = false;
	m_nHatchStyle = HS_CROSS; // �ؽú귯�� ���ڰ� �������� �ʱ�ȭ
	m_colorPen = RGB(0,0,0); // �÷� ���������� �ʱ�ȭ
	m_colorBrush = RGB(255,255,255); // �÷� ������� �ʱ�ȭ
}

CMy2011688P5_1View::~CMy2011688P5_1View()
{
}

BOOL CMy2011688P5_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMy2011688P5_1View �׸���

void CMy2011688P5_1View::OnDraw(CDC* pDC)
{
	CMy2011688P5_1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CPen pen,*oldpen; // pen ��ü ����
	pen.CreatePen(PS_SOLID,1,m_colorPen); 
	oldpen = pDC->SelectObject(&pen); // pen ��ü ��� �� oldpen ������ ����
	//pDC->SetROP2(R2_COPYPEN);
	pDC->SetROP2(R2_NOTXORPEN);
	CBrush brush, *oldbrush;
	
	if(m_bHatch)
		brush.CreateHatchBrush(m_nHatchStyle,m_colorBrush);
	else
		brush.CreateSolidBrush(m_colorBrush);
	oldbrush = pDC->SelectObject(&brush);

	switch(m_nDrawMode)
	{
	case LINE_MODE: 
		pDC->MoveTo(m_ptStart); 
		pDC->LineTo(m_ptPrev); 
		break;
	case ELLIPSE_MODE:
		pDC->Ellipse(m_ptStart.x,m_ptStart.y,m_ptPrev.x,m_ptPrev.y);
		break;
	case POLYGON_MODE:
		pDC->Polygon(m_ptData,m_nCount);
		break;
	}

	pDC->SelectObject(oldpen);
	pDC->SelectObject(oldbrush);
	pen.DeleteObject();
	brush.DeleteObject();

	//
	CDC memdc; // �޸� DC ����
	memdc.CreateCompatibleDC(pDC); // ȣȯ���� �ִ� �޸� ����

	CBitmap bitmap, *oldbitmap; // ��Ʈ���� �ν��Ͻ� ����
	bitmap.LoadBitmap(IDB_WINDOWS_LOGO); // ���ҽ����� ��Ʈ�� �б�
	oldbitmap = memdc.SelectObject(&bitmap); // �޸�DC���� ��Ʈ�� ����

	BITMAP bmpinfo; // ��Ʈ�� ����
	bitmap.GetBitmap(&bmpinfo); // ���ҽ����� ��Ʈ�� ��������
	memdc.SelectObject(&bitmap); 
	
	BLENDFUNCTION bf; // ���� ����
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;

	switch(m_nBitmapMode)
	{
	case 1: // ��Ʈ�� ���
		pDC->BitBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);
		break;
	case 2: // ��Ʈ�� 2�� Ȯ�� ���
		pDC->StretchBlt(0,0,bmpinfo.bmWidth*2,bmpinfo.bmHeight*2,&memdc,0,0,
			bmpinfo.bmWidth, bmpinfo.bmHeight,SRCCOPY);
		break;
	case 3: // ��Ʈ�� 2�� ��� ���
		pDC->StretchBlt(0,0,bmpinfo.bmWidth/2,bmpinfo.bmHeight/2,&memdc,0,0,
			bmpinfo.bmWidth, bmpinfo.bmHeight,SRCCOPY);
		break;
	case 4:
		bf.SourceConstantAlpha = 128; // ���� ����
		
		pDC->AlphaBlend(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,bf);
		break;
	}
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	memdc.SelectObject(oldbitmap);
}


// CMy2011688P5_1View �μ�


void CMy2011688P5_1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy2011688P5_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMy2011688P5_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMy2011688P5_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CMy2011688P5_1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy2011688P5_1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	if(m_bContextMenu == true)
	{
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
	}
	m_bContextMenu = true;
#endif
}


// CMy2011688P5_1View ����

#ifdef _DEBUG
void CMy2011688P5_1View::AssertValid() const
{
	CView::AssertValid();
}

void CMy2011688P5_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy2011688P5_1Doc* CMy2011688P5_1View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2011688P5_1Doc)));
	return (CMy2011688P5_1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy2011688P5_1View �޽��� ó����


void CMy2011688P5_1View::OnLine()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_nDrawMode = LINE_MODE;
	m_nBitmapMode = 0;

	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	
	CString strDrawMode = (_T("���� �׸���"));
	
	pFrame->m_wndStatusBar.SetWindowText(strDrawMode);
}


void CMy2011688P5_1View::OnEllipse()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_nDrawMode = ELLIPSE_MODE;
	m_nBitmapMode = 0;

	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	
	CString strDrawMode = (_T("�� �׸���"));
	
	pFrame->m_wndStatusBar.SetWindowText(strDrawMode);
}


void CMy2011688P5_1View::OnPolygon()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_nDrawMode = POLYGON_MODE;
	m_nBitmapMode = 0;

	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	
	CString strDrawMode = (_T("�ٰ��� �׸���"));
	
	pFrame->m_wndStatusBar.SetWindowText(strDrawMode);
}


void CMy2011688P5_1View::OnLineColor()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CColorDialog dlgColor;

	if(dlgColor.DoModal() == IDOK)
	{
		m_colorPen = dlgColor.GetColor();
	}
	Invalidate(true);
}


void CMy2011688P5_1View::OnFaceColor()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CColorDialog dlgColor;

	if(dlgColor.DoModal() == IDOK)
	{
		m_colorBrush = dlgColor.GetColor();
	}

	m_bHatch = false;
	Invalidate(true);
}



//void CMy2011688P5_1View::OnUpdateLineColor(CCmdUI *pCmdUI)
//{
//	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
//	AfxMessageBox(_T("���� ������ �����մϴ�."));
//}


//void CMy2011688P5_1View::OnUpdateFaceColor(CCmdUI *pCmdUI)
//{
//	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
//	AfxMessageBox(_T("���� ������ �����մϴ�."));
//}


void CMy2011688P5_1View::OnBdiagonal()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_nHatchStyle = HS_BDIAGONAL;

	m_bHatch = true;
	Invalidate(true);

}


void CMy2011688P5_1View::OnCross()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_nHatchStyle = HS_CROSS;

	m_bHatch = true;
	Invalidate(true);
}


void CMy2011688P5_1View::OnVertical()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_nHatchStyle = HS_VERTICAL;

	m_bHatch = true;
	Invalidate(true);
}


void CMy2011688P5_1View::OnShowBitmap()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_nBitmapMode = 1;
	m_nDrawMode = DRAW_NONE;
	Invalidate();
}


//void CMy2011688P5_1View::OnAfxIdcMagnify()
//{
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//	AfxMessageBox(_T("��Ʈ���� 2�� Ȯ���Ͽ� ����մϴ�."));
//}


void CMy2011688P5_1View::OnReduceBitmap()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_nBitmapMode = 3;
	m_nDrawMode = DRAW_NONE;
	Invalidate();
}


void CMy2011688P5_1View::OnAlphaBlend()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_nBitmapMode = 4;
	m_nDrawMode = DRAW_NONE;
	Invalidate();
}


void CMy2011688P5_1View::OnMagnifyBitmap()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_nBitmapMode = 2;
	m_nDrawMode = DRAW_NONE;
	Invalidate();
}


void CMy2011688P5_1View::OnUpdateLine(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck(m_nDrawMode == LINE_MODE ? 1 : 0);
}


void CMy2011688P5_1View::OnUpdateEllipse(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck(m_nDrawMode == ELLIPSE_MODE ? 1 : 0);

}


void CMy2011688P5_1View::OnUpdatePolygon(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck(m_nDrawMode == POLYGON_MODE ? 1 : 0);
}


void CMy2011688P5_1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CClientDC dc(this); // Ŭ���̾�Ʈ DC ��ü ����
	CPen pen, *oldpen;
	pen.CreatePen(PS_SOLID,1,m_colorPen); // �� ����
	oldpen = dc.SelectObject(&pen); // pen ���

	dc.SetROP2(R2_NOTXORPEN); // ���� �׸� �������� �ٽ� �������� ���� ������ �׸� �׸��� �������� �׸� �׷���
	//dc.SetROP2(R2_COPYPEN);
	//dc.SetROP2(R2_XORPEN);

	CBrush brush, *oldbrush;
	if(m_bHatch)
		brush.CreateHatchBrush(m_nHatchStyle,m_colorBrush);
	else
		brush.CreateSolidBrush(m_colorBrush);

	oldbrush = dc.SelectObject(&brush);

	switch(m_nDrawMode)
	{
	case LINE_MODE:
		if(m_bLButtonDown)
		{
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptPrev); // ���� ���� ����

			dc.MoveTo(m_ptStart);
			dc.LineTo(point); // ���� ���� �׸�

			m_ptPrev = point; // ���� ���� ���� �� ����
		}
		break;
	case ELLIPSE_MODE:
		if(m_bLButtonDown)
		{
			dc.Ellipse(m_ptStart.x,m_ptStart.y,m_ptPrev.x,m_ptPrev.y); // ���� �� ����

			dc.Ellipse(m_ptStart.x,m_ptStart.y,point.x,point.y); // ���� �� �׸���
			
			m_ptPrev = point; // ���� ���� ���� �� ����
		}
		break;
	case POLYGON_MODE:
		if(!m_bFirst)
		{
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptPrev);
			
			dc.MoveTo(m_ptStart);
			dc.LineTo(point);
			m_ptPrev = point;
		}
		break;
	}

	dc.SelectObject(oldpen);
	dc.SelectObject(oldbrush);
	pen.DeleteObject();
	brush.DeleteObject();
	//
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	
	CString strPoint;
	strPoint.Format(_T("���콺 ��ġ x : %d, y : %d"),point.x,point.y);
	
	pFrame->m_wndStatusBar.SetPaneText(1,strPoint);

	CView::OnMouseMove(nFlags, point);
}


void CMy2011688P5_1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(m_bFirst) // ���� �ִ� �׸� ���� �� �ְ� �ϴ� �κ�
	{
		m_ptStart = m_ptPrev = 0;
		m_bLButtonDown = false;
		m_bFirst = true;
		m_nCount = 0;
		for(int i=0; i<50; i++)
		{
			m_ptData[i] = 0;
		}
		Invalidate(true);
	}

	switch(m_nDrawMode)
	{
	case LINE_MODE:
	case ELLIPSE_MODE:
		m_bLButtonDown = true; // ���� ��ư ����
		m_ptStart = m_ptPrev = point; // ���� ���� ���� ���� ���� ���� ����
		m_bFirst = false;
		break;
	case POLYGON_MODE:
		if(m_bFirst == true)
			m_bFirst = false;
		m_ptStart = m_ptPrev = point; // ���� ���� ���� ���� ���� ���� ����
		m_ptData[m_nCount] = point; // ���� �� ����
		m_nCount++;
		break;
	}

	if(m_nBitmapMode == 0) // ��尡 ���ٸ�
	{
		RECT rectClient;
		SetCapture(); // ���콺 ĸ�� (������� ��� �� ���ʹ�ư ���� �� ����) -> ���콺�� ���� ��� �̺�Ʈ ������
		GetClientRect(&rectClient);
		ClientToScreen(&rectClient); // ��ũ�� ��ǥ�� ��ȯ
		::ClipCursor(&rectClient); // ���콺 �̵������� ���� ����ü ����(Ŭ���̾�Ʈ ����)���� ����
	}
	CView::OnLButtonDown(nFlags, point);
}


void CMy2011688P5_1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(m_bLButtonDown) // ���� ��ư�� ���� ���¿��ٸ�
	{
		if(m_nDrawMode == LINE_MODE || m_nDrawMode == ELLIPSE_MODE)
		{
			m_bLButtonDown = false;
			m_bFirst = true;

			ReleaseCapture();
			::ClipCursor(NULL); // ���콺 �̵����� ���� ����
			Invalidate(true);
		}
	}
	CView::OnLButtonUp(nFlags, point);
}


void CMy2011688P5_1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if(m_nDrawMode == POLYGON_MODE)
	{
		if(!m_bFirst)
		{
			m_bContextMenu = FALSE;
			m_ptData[m_nCount] = point; // �迭�� ���� �� ����
			m_nCount++; // ī��Ʈ ����
			m_bFirst = TRUE;

			//ReleaseCapture(); // ���콺 ĸ�� ����
			//::ClipCursor(NULL);
			Invalidate(TRUE);
		}
	}

	CView::OnRButtonDown(nFlags, point);
}
