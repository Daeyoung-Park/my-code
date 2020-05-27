// TextDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "20111688E6_2.h"
#include "TextDialog.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "20111688E6_2View.h"

// CTextDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTextDialog, CDialogEx)

CTextDialog::CTextDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextDialog::IDD, pParent)
	, m_strColorOut(_T("000000"))
	, m_strFontOut(_T("system"))
	, m_strEditX(_T(""))
	, m_strEditY(_T(""))
{

}

CTextDialog::~CTextDialog()
{
}

void CTextDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_COLOR, m_strColorOut);
	DDX_Text(pDX, IDC_EDIT_FONT, m_strFontOut);
	DDX_Control(pDX, IDC_EDIT_TEXT, m_strTextString);
	DDX_Text(pDX, IDC_EDIT_X, m_strEditX);
	DDX_Text(pDX, IDC_EDIT_Y, m_strEditY);
}


BEGIN_MESSAGE_MAP(CTextDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_TEXTOUT, &CTextDialog::OnClickedButtonTextout)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CTextDialog::OnClickedButtonColor)
	ON_BN_CLICKED(IDC_BUTTON_FONT, &CTextDialog::OnClickedButtonFont)
	ON_WM_KEYDOWN()
	ON_WM_KEYDOWN()
	ON_EN_CHANGE(IDC_EDIT_X, &CTextDialog::OnEnChangeEditX)
	ON_EN_CHANGE(IDC_EDIT_Y, &CTextDialog::OnEnChangeEditY)
END_MESSAGE_MAP()


// CTextDialog �޽��� ó�����Դϴ�.


void CTextDialog::OnClickedButtonTextout()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	
	CString strString;
	m_strTextString.GetWindowText(strString);

	if(!strString.IsEmpty())
	{
		CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
		CMy20111688E6_2View* pView = (CMy20111688E6_2View*)pFrame->GetActiveView();
				
		pView->m_ptPosition.x = GetDlgItemInt(IDC_EDIT_X); // CString�����̹Ƿ� int�� �ٲپ ����
		pView->m_ptPosition.y = GetDlgItemInt(IDC_EDIT_Y); // CString�����̹Ƿ� int�� �ٲپ ����

		pView->m_strOutText = strString;
		
		
		pView->Invalidate();
	}
	else
	{
		AfxMessageBox(_T("���� �Է��ϼ���"));
	}

	UpdateData(FALSE);
}


void CTextDialog::OnClickedButtonColor()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20111688E6_2View* pView = (CMy20111688E6_2View*)pFrame->GetActiveView();

	CColorDialog dlgColor;
	if(dlgColor.DoModal() == IDOK)
	{
		pView->m_colorText = dlgColor.GetColor();
		m_strColorOut.Format(_T("%06X"),pView->m_colorText);

		pView->Invalidate();
	}

	UpdateData(FALSE);
	Invalidate(true);
}


void CTextDialog::OnClickedButtonFont()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20111688E6_2View* pView = (CMy20111688E6_2View*)pFrame->GetActiveView();
	
	CFontDialog fontDlg;
	if(fontDlg.DoModal() == IDOK)
	{
		pView->m_bFont = true;

		fontDlg.GetCurrentFont(&(pView->m_logfont));
		m_strFontOut.Format(_T("%s"),pView->m_logfont.lfFaceName);

		pView->Invalidate();
	}

	UpdateData(FALSE);
	Invalidate(true);
}



void CTextDialog::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CTextDialog::OnEnChangeEditX()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.
	
	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CTextDialog::OnEnChangeEditY()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.
	
	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
