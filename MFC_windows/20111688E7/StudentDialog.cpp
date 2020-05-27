// StudentDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "20111688E7.h"
#include "StudentDialog.h"
#include "afxdialogex.h"


// CStudentDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CStudentDialog, CDialogEx)

CStudentDialog::CStudentDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStudentDialog::IDD, pParent)
	, m_strNumber(_T(""))
	, m_strName(_T(""))
	, m_intLevel(0)
	, m_intSex(0)
	, m_strAddress(_T(""))
{

}

CStudentDialog::~CStudentDialog()
{
}

void CStudentDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NUMBER, m_strNumber);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_CBIndex(pDX, IDC_COMBO_LEVEL, m_intLevel);
	DDX_CBIndex(pDX, IDC_COMBO_SEX, m_intSex);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_strAddress);
	DDX_Control(pDX, IDC_COMBO_LEVEL, m_cbLevel);
	DDX_Control(pDX, IDC_COMBO_SEX, m_cbSex);
}


BEGIN_MESSAGE_MAP(CStudentDialog, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_LEVEL, &CStudentDialog::OnCbnSelchangeComboLevel)
	ON_CBN_SELCHANGE(IDC_COMBO_SEX, &CStudentDialog::OnCbnSelchangeComboSex)
END_MESSAGE_MAP()


// CStudentDialog �޽��� ó�����Դϴ�.


BOOL CStudentDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	if(m_intSex == 0) // ��
	{
		m_cbSex.SetCurSel(0);
	}
	else // ����
	{
		m_cbSex.SetCurSel(1);
	}

	if(m_intLevel == 0)
	{
		m_cbLevel.SetCurSel(0);
	}
	else if(m_intLevel == 1)
	{
		m_cbLevel.SetCurSel(1);
	}
	else if(m_intLevel == 2)
	{
		m_cbLevel.SetCurSel(2);
	}
	else
	{
		m_cbLevel.SetCurSel(3);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CStudentDialog::OnCbnSelchangeComboLevel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int currentSel = m_cbLevel.GetCurSel();

	if(currentSel == 0)
	{
		m_intLevel=0;
	}
	else if(currentSel == 1)
	{
		m_intLevel=1;
	}
	else if(currentSel == 2)
	{
		m_intLevel=2;
	}
	else if(currentSel == 3)
	{
		m_intLevel=3;
	}
	else
	{
	}
}


void CStudentDialog::OnCbnSelchangeComboSex()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int currentSel = m_cbSex.GetCurSel();

	if(currentSel == 0)
	{
		m_intSex=0;
	}
	else if(currentSel == 1)
	{
		m_intSex=1;
	}
	else
	{
	}
}
