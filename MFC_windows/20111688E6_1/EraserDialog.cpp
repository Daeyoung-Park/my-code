// EraserDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "20111688E6_1.h"
#include "EraserDialog.h"
#include "afxdialogex.h"
#include "20111688E6_1View.h"
#include "MainFrm.h"


// CEraserDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CEraserDialog, CDialogEx)

CEraserDialog::CEraserDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEraserDialog::IDD, pParent)
	, m_editEraserSize(0)
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20111688E6_1View* pView = (CMy20111688E6_1View*)pFrame->GetActiveView();
	m_editEraserSize = pView->m_nEraserSize;
}

CEraserDialog::~CEraserDialog()
{
}

void CEraserDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ERASER, m_editEraserSize);
	DDX_Control(pDX, IDC_SPIN_ERASER, m_spinEraserSize);
}


BEGIN_MESSAGE_MAP(CEraserDialog, CDialogEx)
END_MESSAGE_MAP()


// CEraserDialog �޽��� ó�����Դϴ�.


BOOL CEraserDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_spinEraserSize.SetRange(2,20); // ���찳 ������ 2~20������
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
