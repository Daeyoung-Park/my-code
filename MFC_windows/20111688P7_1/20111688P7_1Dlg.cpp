
// 20111688P7_1Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "20111688P7_1.h"
#include "20111688P7_1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy20111688P7_1Dlg ��ȭ ����




CMy20111688P7_1Dlg::CMy20111688P7_1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy20111688P7_1Dlg::IDD, pParent)
	, m_nSelectedItem(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strDept = _T("");
	m_strID = _T("");
	m_strName = _T("");
	m_strSelectItem = _T("");
}

void CMy20111688P7_1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STUDENT, m_listStudent);
	DDX_Text(pDX, IDC_EDIT_DEPT, m_strDept);
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_SELECTED_ITEM, m_strSelectItem);
}

BEGIN_MESSAGE_MAP(CMy20111688P7_1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CMy20111688P7_1Dlg::OnClickedButtonInsert)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_STUDENT, &CMy20111688P7_1Dlg::OnItemchangedListStudent)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CMy20111688P7_1Dlg::OnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CMy20111688P7_1Dlg::OnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CMy20111688P7_1Dlg::OnClickedButtonReset)
	ON_CBN_SELCHANGE(IDC_COMBO_STYLE, &CMy20111688P7_1Dlg::OnSelchangeComboStyle)
END_MESSAGE_MAP()


// CMy20111688P7_1Dlg �޽��� ó����

BOOL CMy20111688P7_1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	// ����Ʈ ��Ʈ�� ��ȭ
	LV_COLUMN lvColumn; // Į�� ����
	LPWSTR list[4] = {_T("����"),_T("�а�"),_T("�й�"),_T("�̸�")}; //LPWSTR : w_char
	int nWidth[4] = {50,150,100,100}; // Į�� ���� ����

	for(int i=0; i<4; i++)
	{
		lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH; // Į���� ����ũ ����
		lvColumn.fmt = LVCFMT_CENTER; // ��ġ
		lvColumn.pszText = list[i]; // Į���� �ؽ�Ʈ
		lvColumn.iSubItem = i; // Į���� �� �������� ����
		lvColumn.cx = nWidth[i];//Į���� ���� ����
		m_listStudent.InsertColumn(i,&lvColumn); // List��Ʈ�ѿ� Į�� ����
	}

	m_listStudent.SetExtendedStyle(m_listStudent.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); // List��Ʈ�� ��Ÿ�� ���� 
	((CComboBox*)GetDlgItem(IDC_COMBO_STYLE))->SetCurSel(0); // �޺� �ڽ��� �ʱ� ���ð� ����

	((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE); // ���� ��ư ��Ȱ��ȭ
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE); // ���� ��ư ��Ȱ��ȭ
	
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CMy20111688P7_1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMy20111688P7_1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMy20111688P7_1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy20111688P7_1Dlg::OnClickedButtonInsert()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nCount = m_listStudent.GetItemCount(); // List��Ʈ�ѿ� ���Ե� �������� ��
	LV_ITEM lvItem; // ������ ����
	CString strCount; // �����ۿ� �� ����

	UpdateData(TRUE);

	if(!m_strDept.IsEmpty() && !m_strID.IsEmpty() && !m_strName.IsEmpty() ) // �а�,�й�,�̸��� ��� ������� ������
	{
		lvItem.mask = LVIF_TEXT; // ������ ����
		lvItem.iItem = nCount; // �������� ������ġ
		lvItem.iSubItem = 0; // ���� Į�� �ε���
		strCount.Format(_T("%d"),nCount+1); // ����
		lvItem.pszText = (LPWSTR)(LPCTSTR)strCount; // ���� ����
		m_listStudent.InsertItem(&lvItem);

		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = nCount;
		lvItem.iSubItem = 1; // ���� Į�� �ε���
		lvItem.pszText = (LPWSTR)(LPCTSTR)m_strDept; // �а�
		m_listStudent.SetItem(&lvItem);

		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = nCount; 
		lvItem.iSubItem = 2;
		lvItem.pszText = (LPWSTR)(LPCTSTR)m_strID; // �й�
		m_listStudent.SetItem(&lvItem);

		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = nCount;
		lvItem.iSubItem = 3;
		lvItem.pszText = (LPWSTR)(LPCTSTR)m_strName; // �̸�
		m_listStudent.SetItem(&lvItem);

		m_strDept.Empty(); // ����Ʈ�� ���� �� ����Ʈ ����
		m_strID.Empty();
		m_strName.Empty();

		((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE); // ��ư Ȱ��ȭ
		((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE); // ��ư Ȱ��ȭ

		UpdateData(FALSE);
	}
	else
	{
		MessageBox(_T("��� �׸��� �Է��� �ּ���"),_T("���"),MB_OK);
	}
}


void CMy20111688P7_1Dlg::OnItemchangedListStudent(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	m_nSelectedItem = pNMLV->iItem; // ���õ� ����Ʈ�� �ε����� ������

	m_strSelectItem.Format(_T("%d"),m_nSelectedItem+1); // ���õ� ������ ��ȣ ���
	m_strDept = m_listStudent.GetItemText(m_nSelectedItem,1); // ����� �ε����� ������ ������
	m_strID = m_listStudent.GetItemText(m_nSelectedItem,2);
	m_strName = m_listStudent.GetItemText(m_nSelectedItem,3);

	((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(TRUE); // ��ư Ȱ��ȭ
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(TRUE); // ��ư Ȱ��ȭ

	UpdateData(FALSE);
	*pResult = 0;
}


void CMy20111688P7_1Dlg::OnClickedButtonModify()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CString strDept,strID,strName;
	strDept = m_strDept;
	strID = m_strID;
	strName = m_strName;
	CString strIndex;

	if(m_nSelectedItem >= 0) // ���õ� �������� �ִٸ�
	{
		if(!m_strDept.IsEmpty() && !m_strID.IsEmpty() && !m_strName.IsEmpty() ) // ����Ʈ�� ��� ������� �ʴٸ�
		{
			LV_ITEM lvItem;
			// ����Ʈ�� �ش��ϴ� ������ ����
			lvItem.mask = LVIF_TEXT;
			lvItem.iItem = m_nSelectedItem;
			lvItem.iSubItem = 0;
			strIndex.Format(_T("%d"),m_nSelectedItem+1);
			lvItem.pszText = (LPWSTR)(LPCTSTR)strIndex;
			m_listStudent.SetItem(&lvItem);

			lvItem.mask = LVIF_TEXT;
			lvItem.iItem = m_nSelectedItem;
			lvItem.iSubItem = 1;
			lvItem.pszText = (LPWSTR)(LPCTSTR)strDept;
			m_listStudent.SetItem(&lvItem);

			lvItem.mask = LVIF_TEXT;
			lvItem.iItem = m_nSelectedItem;
			lvItem.iSubItem = 2;
			lvItem.pszText = (LPWSTR)(LPCTSTR)strID;
			m_listStudent.SetItem(&lvItem);

			lvItem.mask = LVIF_TEXT;
			lvItem.iItem = m_nSelectedItem;
			lvItem.iSubItem = 3;
			lvItem.pszText = (LPWSTR)(LPCTSTR)strName;
			m_listStudent.SetItem(&lvItem);

			m_strDept.Empty();
			m_strID.Empty();
			m_strName.Empty();

			((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE); // ��Ȱ��ȭ
			((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);

			UpdateData(FALSE);
		}
		else
		{
			MessageBox(_T("��� �׸��� �Է��� �ּ���"),_T("���"),MB_OK);
		}
	}
	else
	{
		MessageBox(_T("�������� �������� �ʾҽ��ϴ�."),_T("���"),MB_OK);
	}
	
}


void CMy20111688P7_1Dlg::OnClickedButtonDelete()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_nSelectedItem >= 0) // ���õ� ����Ʈ�� �ִٸ�
	{
		m_listStudent.DeleteItem(m_nSelectedItem); // ����
		
		for(int i = m_nSelectedItem-1; i< m_listStudent.GetItemCount(); i++) // ��ȣ ��迭�ϱ�
		{
			CString strIndex;

			strIndex.Format(_T("%d"),i+1);
			m_listStudent.SetItemText(i,0,strIndex);
		}
		
		m_strDept.Empty();
		m_strID.Empty();
		m_strName.Empty();

		((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);

		UpdateData(FALSE);
	}
	else
	{
		MessageBox(_T("�������� �������� �ʾҽ��ϴ�."),_T("���"),MB_OK);
	}
}


void CMy20111688P7_1Dlg::OnClickedButtonReset()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
		m_strDept.Empty();
		m_strID.Empty();
		m_strName.Empty();

		UpdateData(FALSE);
}


void CMy20111688P7_1Dlg::OnSelchangeComboStyle()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int numSel = ((CComboBox*)GetDlgItem(IDC_COMBO_STYLE))->GetCurSel(); // �޺��ڽ����� ���õ� �����ۿ� �´� �ε����� ������
	long setStyle;

	setStyle = GetWindowLong(m_listStudent.m_hWnd,GWL_STYLE); // ��õ� �����쿡 ���� ������ ���� 
	setStyle &= ~LVS_TYPEMASK;

	switch(numSel) //�ڼ���;���;���� ������;ū ������;
	{
	case 0:
		setStyle |= LVS_REPORT; // �ڼ���
		break;
	case 1:
		setStyle |= LVS_LIST; // ���
		break;
	case 2:
		setStyle |= LVS_SMALLICON; // ���� ������
		break;
	case 3:
		setStyle |= LVS_ICON; // ū ������
		break;
	}
	SetWindowLong(m_listStudent.m_hWnd,GWL_STYLE,setStyle); // ��õ� �������� �Ӽ��� ������
}
