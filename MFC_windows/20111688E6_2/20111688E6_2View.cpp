
// 20111688E6_2View.cpp : CMy20111688E6_2View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "20111688E6_2.h"
#endif

#include "20111688E6_2Doc.h"
#include "20111688E6_2View.h"
#include "MainFrm.h"
#include "TextDokingPane.h"
#include "TextDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy20111688E6_2View

IMPLEMENT_DYNCREATE(CMy20111688E6_2View, CView)

BEGIN_MESSAGE_MAP(CMy20111688E6_2View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy20111688E6_2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_EDIT_X, &CMy20111688E6_2View::OnEnChangeEditX)
END_MESSAGE_MAP()

// CMy20111688E6_2View ����/�Ҹ�

CMy20111688E6_2View::CMy20111688E6_2View()
	: m_strOutText(_T(""))
	, m_bFont(FALSE)
	, m_ptPosition(0)
	, m_nTextHeight(0)
	, m_nTextWidth(0)
	, strX(_T(""))
	, strY(_T(""))
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMy20111688E6_2View::~CMy20111688E6_2View()
{
}

BOOL CMy20111688E6_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMy20111688E6_2View �׸���

void CMy20111688E6_2View::OnDraw(CDC* pDC)
{
	CMy20111688E6_2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	UpdateData(TRUE);

	CFont *oldFont, *currentFont, newFont;

	if(m_bFont) // ��Ʈ ����
	{
		newFont.CreateFontIndirect(&m_logfont);
		oldFont = pDC->SelectObject(&newFont);
	}
	else
	{
		currentFont = pDC->GetCurrentFont();
		oldFont = pDC->SelectObject(currentFont);
	}

	CSize sizeText; // ���ڿ� �ʺ� , ���� ���ϱ�
	sizeText = pDC->GetTextExtent(m_strOutText);
	m_nTextWidth = sizeText.cx;
	m_nTextHeight = sizeText.cy;


	pDC->SetTextColor(m_colorText); // ���� ����
	pDC->TextOut(m_ptPosition.x,m_ptPosition.y,m_strOutText); // ���ڿ� ���

	UpdateData(FALSE);

	pDC->SelectObject(oldFont); // ��Ʈ ����
	if(m_bFont)
	{
		newFont.DeleteObject();
	}
	else
	{
		currentFont->DeleteObject();
	}

	
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CMy20111688E6_2View �μ�


void CMy20111688E6_2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy20111688E6_2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMy20111688E6_2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMy20111688E6_2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CMy20111688E6_2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy20111688E6_2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy20111688E6_2View ����

#ifdef _DEBUG
void CMy20111688E6_2View::AssertValid() const
{
	CView::AssertValid();
}

void CMy20111688E6_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy20111688E6_2Doc* CMy20111688E6_2View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy20111688E6_2Doc)));
	return (CMy20111688E6_2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy20111688E6_2View �޽��� ó����


void CMy20111688E6_2View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
	UpdateData(TRUE);
	
	switch(nChar)
	{
	case VK_LEFT:
		m_ptPosition.x-=10;
		break;
	case VK_RIGHT:
		m_ptPosition.x+=10;
		break;
	case VK_UP:
		m_ptPosition.y-=10;
		break;
	case VK_DOWN:
		m_ptPosition.y+=10;
		break;
	case VK_HOME:
		m_ptPosition = CPoint(0,0);
		break;
	}

	RECT rect;
	GetClientRect(&rect);

	if(m_ptPosition.x > rect.right - m_nTextWidth)
	{
		m_ptPosition.x = rect.right - m_nTextWidth;
		AfxMessageBox(_T("���������� �� �̻� �� �� �����ϴ�."));
	}
	if(m_ptPosition.x < 0)
	{
		m_ptPosition.x = 0;
		AfxMessageBox(_T("�������� �� �̻� �� �� �����ϴ�."));
	}
	if(m_ptPosition.y > rect.bottom - m_nTextHeight)
	{
		m_ptPosition.y = rect.bottom - m_nTextHeight;
		AfxMessageBox(_T("�Ʒ������� �� �̻� �� �� �����ϴ�."));
	}
	if(m_ptPosition.y < 0)
	{
		m_ptPosition.y = 0;
		AfxMessageBox(_T("�������� �� �̻� �� �� �����ϴ�."));
	}

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	pFrame->m_textDokingPane.m_textDialog.SetDlgItemInt(IDC_EDIT_X,m_ptPosition.x);
	pFrame->m_textDokingPane.m_textDialog.SetDlgItemInt(IDC_EDIT_Y,m_ptPosition.y);


	Invalidate();
	
	UpdateData(FALSE);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMy20111688E6_2View::OnDestroy()
{
	CView::OnDestroy();

	

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CMy20111688E6_2View::OnEnChangeEditX()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CView::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
