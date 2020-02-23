// TextDokingPane.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "20111688E6_2.h"
#include "TextDokingPane.h"
#include "TextDialog.h"

// CTextDokingPane

IMPLEMENT_DYNAMIC(CTextDokingPane, CDockablePane)

CTextDokingPane::CTextDokingPane()
{

}

CTextDokingPane::~CTextDokingPane()
{
}


BEGIN_MESSAGE_MAP(CTextDokingPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CTextDokingPane �޽��� ó�����Դϴ�.




int CTextDokingPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	if(!m_textDialog.Create(IDD_DIALOG_TEXT,this))
	{
		TRACE0("Ű�е� �����츦 ������ ���Ͽ����ϴ�.\n");
		return -1;
	}

	m_textDialog.ShowWindow(SW_SHOW);
	
	return 0;
}


void CTextDokingPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	if(m_textDialog.GetSafeHwnd())
	{
		m_textDialog.MoveWindow(0,0,cx,cy);
		m_textDialog.SetFocus();
	}
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}
