// PenSizeDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "20111688E6_1.h"
#include "PenSizeDialog.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "20111688E6_1View.h"

// CPenSizeDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPenSizeDialog, CDialogEx)

CPenSizeDialog::CPenSizeDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPenSizeDialog::IDD, pParent)
	, m_editPenSize(0)
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20111688E6_1View* pView = (CMy20111688E6_1View*)pFrame->GetActiveView();
	m_editPenSize = pView->m_nPenSize;
}

CPenSizeDialog::~CPenSizeDialog()
{
}

void CPenSizeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PEN, m_editPenSize);
	DDX_Control(pDX, IDC_SPIN_PEN, m_spinPenSize);
}


BEGIN_MESSAGE_MAP(CPenSizeDialog, CDialogEx)
END_MESSAGE_MAP()


// CPenSizeDialog �޽��� ó�����Դϴ�.


BOOL CPenSizeDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_spinPenSize.SetRange(1,10); // �� ������ 1~10������

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
