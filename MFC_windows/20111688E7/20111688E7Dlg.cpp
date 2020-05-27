
// 20111688E7Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "20111688E7.h"
#include "20111688E7Dlg.h"
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


// CMy20111688E7Dlg ��ȭ ����




CMy20111688E7Dlg::CMy20111688E7Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy20111688E7Dlg::IDD, pParent)
	, m_nCount(0)
	, m_nSelectedItem(0)
	, m_selectTree(false)
	, m_selectList(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy20111688E7Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_CONTROL, m_treeControl);
	DDX_Control(pDX, IDC_LIST_CONTROL, m_listControl);
}

BEGIN_MESSAGE_MAP(CMy20111688E7Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CMy20111688E7Dlg::OnClickedButtonInsert)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_CONTROL, &CMy20111688E7Dlg::OnSelchangedTreeControl)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CONTROL, &CMy20111688E7Dlg::OnItemchangedListControl)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CMy20111688E7Dlg::OnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CMy20111688E7Dlg::OnClickedButtonDelete)
END_MESSAGE_MAP()


// CMy20111688E7Dlg �޽��� ó����

BOOL CMy20111688E7Dlg::OnInitDialog()
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

	// Ʈ�� �ʱ�ȭ
	TV_INSERTSTRUCT tvStruct1; //������б� -> ��Ʈ ���
	tvStruct1.hParent = 0;
	tvStruct1.hInsertAfter = TVI_LAST;
	tvStruct1.item.mask = TVIF_TEXT;
	tvStruct1.item.pszText = _T("������б�");
	m_hRoot = m_treeControl.InsertItem(&tvStruct1);

	TV_INSERTSTRUCT tvStruct2; // ������а�
	tvStruct2.hParent = m_hRoot;
	tvStruct2.hInsertAfter = TVI_LAST;
	tvStruct2.item.mask = TVIF_TEXT;
	tvStruct2.item.pszText = _T("������а�");
	m_hKorean = m_treeControl.InsertItem(&tvStruct2);
	m_treeControl.Expand(m_hRoot,TVE_EXPAND);

	TV_INSERTSTRUCT tvStruct3; // ��ǻ�Ͱ��а�
	tvStruct3.hParent = m_hRoot;
	tvStruct3.hInsertAfter = TVI_LAST;
	tvStruct3.item.mask = TVIF_TEXT;
	tvStruct3.item.pszText = _T("��ǻ�Ͱ��а�");
	m_hComputer = m_treeControl.InsertItem(&tvStruct3);
	m_treeControl.Expand(m_hRoot,TVE_EXPAND);

	TV_INSERTSTRUCT tvStruct4; // �����а�
	tvStruct4.hParent = m_hRoot;
	tvStruct4.hInsertAfter = TVI_LAST;
	tvStruct4.item.mask = TVIF_TEXT;
	tvStruct4.item.pszText = _T("�����а�");
	m_hPhysics = m_treeControl.InsertItem(&tvStruct4);
	m_treeControl.Expand(m_hRoot,TVE_EXPAND);

	// ����Ʈ �ʱ�ȭ
	LV_COLUMN lvColumn;
	LPWSTR list[5] = {_T("�й�"),_T("�̸�"),_T("�г�"),_T("����"),_T("�ּ�")};
	int nWidth[5] = {40,90,60,40,240};

	for(int i=0; i<5; i++)
	{
		lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvColumn.fmt = LVCFMT_CENTER;
		lvColumn.pszText = list[i];
		lvColumn.iSubItem = i;
		lvColumn.cx = nWidth[i];
		m_listControl.InsertColumn(i,&lvColumn);
	}
	m_listControl.SetExtendedStyle(m_listControl.GetExtendedStyle() | 
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	// ��ư �ʱ�ȭ
	((CButton*)GetDlgItem(IDC_BUTTON_INSERT))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CMy20111688E7Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy20111688E7Dlg::OnPaint()
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
HCURSOR CMy20111688E7Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy20111688E7Dlg::OnClickedButtonInsert()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CStudentDialog studentDialog;
	int itemNum = m_listControl.GetItemCount();
	BOOL bInsert = TRUE;
	
	if(m_nSelectedNode == m_hRoot)
	{
		AfxMessageBox(_T("�а��� �����ϼ���"));
		return;
	}

	if(studentDialog.DoModal() == IDOK)
	{
		for(int i=0; i<itemNum; i++)
		{
			CString strNum = m_listControl.GetItemText(i,0); // �й� ��������

			if(strNum == studentDialog.m_strNumber) // ���ԵǴ� �л��� �й��� ���ٸ�
			{
				bInsert = FALSE;
			}
		}
			if(studentDialog.m_strName.IsEmpty() || studentDialog.m_strNumber.IsEmpty() || studentDialog.m_strAddress.IsEmpty() )
			{
				AfxMessageBox(_T("��� �׸��� �Է��ϼ���"));

				((CButton*)GetDlgItem(IDC_BUTTON_INSERT))->EnableWindow(FALSE);
				((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
				((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);

				return;
			}
			if(bInsert)
			{
				CString strLevel; // �г� ���ڿ�
				if(studentDialog.m_intLevel==0)
				{
					strLevel.Format(_T("1�г�"));
				}
				else if(studentDialog.m_intLevel==1)
				{
					strLevel.Format(_T("2�г�"));
				}
				else if(studentDialog.m_intLevel==2)
				{
					strLevel.Format(_T("3�г�"));
				}
				else if(studentDialog.m_intLevel==3)
				{
					strLevel.Format(_T("4�г�"));
				}
				
				CString strSex; // ���� ���ڿ�
				if(studentDialog.m_intSex==0)
				{
					strSex.Format(_T("����"));
				}
				else if(studentDialog.m_intSex==1)
				{
					strSex.Format(_T("����"));
				}
				
				LV_ITEM lvItem1;	
				lvItem1.mask = LVIF_TEXT;
				lvItem1.iItem = itemNum;
				lvItem1.iSubItem = 0;
				lvItem1.pszText = (LPWSTR)(LPCTSTR)studentDialog.m_strNumber;
				m_listControl.InsertItem(&lvItem1); // �й� ����
				
				LV_ITEM lvItem2;
				lvItem2.mask = LVIF_TEXT;
				lvItem2.iItem = itemNum;
				lvItem2.iSubItem = 1;
				lvItem2.pszText = (LPWSTR)(LPCTSTR)studentDialog.m_strName;
				m_listControl.SetItem(&lvItem2); // �̸� ����

				LV_ITEM lvItem3;
				lvItem3.mask = LVIF_TEXT;
				lvItem3.iItem = itemNum;
				lvItem3.iSubItem = 2;
				lvItem3.pszText = (LPWSTR)(LPCTSTR)strLevel;
				m_listControl.SetItem(&lvItem3); // �г� ����

				LV_ITEM lvItem4;
				lvItem4.mask = LVIF_TEXT;
				lvItem4.iItem = itemNum;
				lvItem4.iSubItem = 3;
				lvItem4.pszText = (LPWSTR)(LPCTSTR)strSex;
				m_listControl.SetItem(&lvItem4); // ���� ����

				LV_ITEM lvItem5;
				lvItem5.mask = LVIF_TEXT;
				lvItem5.iItem = itemNum;
				lvItem5.iSubItem = 4;
				lvItem5.pszText = (LPWSTR)(LPCTSTR)studentDialog.m_strAddress;
				m_listControl.SetItem(&lvItem5); // �ּ� ����
				
				m_studentInfo[m_nCount].strDept = m_treeControl.GetItemText(m_nSelectedNode); // �л� ����ü �迭 �ʱ�ȭ
				m_studentInfo[m_nCount].strID = studentDialog.m_strNumber;
				m_studentInfo[m_nCount].strName = studentDialog.m_strName;
				m_studentInfo[m_nCount].nGrade = studentDialog.m_intLevel;
				m_studentInfo[m_nCount].nSex = studentDialog.m_intSex;
				m_studentInfo[m_nCount].strAddress = studentDialog.m_strAddress;
				m_nCount++;
			}
			else
			{
				AfxMessageBox(_T("�̹� ��ϵ� �й��Դϴ�."));
			}
		
	}

	((CButton*)GetDlgItem(IDC_BUTTON_INSERT))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);

	UpdateData(FALSE);
}


void CMy20111688E7Dlg::OnSelchangedTreeControl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	
	m_selectTree =true; // Ʈ���� ����

	m_nSelectedNode = pNMTreeView->itemNew.hItem; // ���õ� ��� üũ
	int itemCount = m_nCount; // �迭�� ����� �л� ��
	int nDept = 0; // �а����� �л� ��

	m_listControl.DeleteAllItems(); // ����Ʈ �ʱ�ȭ

	for(int i=0; i<itemCount; i++) // ����Ʈ ��������
	{
				CString strLevel;
				if(m_studentInfo[i].nGrade==0)
				{
					strLevel.Format(_T("1�г�"));
				}
				else if(m_studentInfo[i].nGrade==1)
				{
					strLevel.Format(_T("2�г�"));
				}
				else if(m_studentInfo[i].nGrade==2)
				{
					strLevel.Format(_T("3�г�"));
				}
				else if(m_studentInfo[i].nGrade==3)
				{
					strLevel.Format(_T("4�г�"));
				}
				
				CString strSex;
				if(m_studentInfo[i].nSex==0)
				{
					strSex.Format(_T("����"));
				}
				else if(m_studentInfo[i].nSex==1)
				{
					strSex.Format(_T("����"));
				}

		if(m_nSelectedNode == m_hRoot) // ��Ʈ��� ���õǾ��ٸ� �л� �迭�� �ִ� ��� ���� -> ����Ʈ�� ����
		{
				LV_ITEM lvItem1;	
				lvItem1.mask = LVIF_TEXT;
				lvItem1.iItem = i;
				lvItem1.iSubItem = 0;
				lvItem1.pszText = (LPWSTR)(LPCTSTR)m_studentInfo[i].strID;
				m_listControl.InsertItem(&lvItem1); //
				
				LV_ITEM lvItem2;
				lvItem2.mask = LVIF_TEXT;
				lvItem2.iItem = i;
				lvItem2.iSubItem = 1;
				lvItem2.pszText = (LPWSTR)(LPCTSTR)m_studentInfo[i].strName;
				m_listControl.SetItem(&lvItem2); //

				LV_ITEM lvItem3;
				lvItem3.mask = LVIF_TEXT;
				lvItem3.iItem = i;
				lvItem3.iSubItem = 2;
				lvItem3.pszText = (LPWSTR)(LPCTSTR)strLevel;
				m_listControl.SetItem(&lvItem3); //

				LV_ITEM lvItem4;
				lvItem4.mask = LVIF_TEXT;
				lvItem4.iItem = i;
				lvItem4.iSubItem = 3;
				lvItem4.pszText = (LPWSTR)(LPCTSTR)strSex;
				m_listControl.SetItem(&lvItem4); //

				LV_ITEM lvItem5;
				lvItem5.mask = LVIF_TEXT;
				lvItem5.iItem = i;
				lvItem5.iSubItem = 4;
				lvItem5.pszText = (LPWSTR)(LPCTSTR)m_studentInfo[i].strAddress;
				m_listControl.SetItem(&lvItem5); //
		}
		else if(m_nSelectedNode == m_hKorean) // ������а� ���õǾ��ٸ�
		{
			if(m_studentInfo[i].strDept == "������а�")
			{
				LV_ITEM lvItem;	
				lvItem.mask = LVIF_TEXT;
				lvItem.iItem = nDept;
				lvItem.iSubItem = 0;
				lvItem.pszText = (LPWSTR)(LPCTSTR)m_studentInfo[i].strID;
				m_listControl.InsertItem(&lvItem); //
				
				lvItem.mask = LVIF_TEXT;
				lvItem.iItem = nDept;
				lvItem.iSubItem = 1;
				lvItem.pszText = (LPWSTR)(LPCTSTR)m_studentInfo[i].strName;
				m_listControl.SetItem(&lvItem); //

				lvItem.mask = LVIF_TEXT;
				lvItem.iItem = nDept;
				lvItem.iSubItem = 2;
				lvItem.pszText = (LPWSTR)(LPCTSTR)strLevel;
				m_listControl.SetItem(&lvItem); //

				lvItem.mask = LVIF_TEXT;
				lvItem.iItem = nDept;
				lvItem.iSubItem = 3;
				lvItem.pszText = (LPWSTR)(LPCTSTR)strSex;
				m_listControl.SetItem(&lvItem); //

				lvItem.mask = LVIF_TEXT;
				lvItem.iItem = nDept;
				lvItem.iSubItem = 4;
				lvItem.pszText = (LPWSTR)(LPCTSTR)m_studentInfo[i].strAddress;
				m_listControl.SetItem(&lvItem); //

				nDept++;
			}
		}
		else if(m_nSelectedNode == m_hComputer) // ��ǻ�Ͱ��а� ���õǾ��ٸ�
		{
			if(m_studentInfo[i].strDept == "��ǻ�Ͱ��а�") 
			{
				LV_ITEM lvItem;	
				lvItem.mask = LVIF_TEXT;
				lvItem.iItem = nDept;
				lvItem.iSubItem = 0;
				lvItem.pszText = (LPWSTR)(LPCTSTR)m_studentInfo[i].strID;
				m_listControl.InsertItem(&lvItem); //
				
				lvItem.mask = LVIF_TEXT;
				lvItem.iItem = nDept;
				lvItem.iSubItem = 1;
				lvItem.pszText = (LPWSTR)(LPCTSTR)m_studentInfo[i].strName;
				m_listControl.SetItem(&lvItem); //

				lvItem.mask = LVIF_TEXT;
				lvItem.iItem = nDept;
				lvItem.iSubItem = 2;
				lvItem.pszText = (LPWSTR)(LPCTSTR)strLevel;
				m_listControl.SetItem(&lvItem); //

				lvItem.mask = LVIF_TEXT;
				lvItem.iItem = nDept;
				lvItem.iSubItem = 3;
				lvItem.pszText = (LPWSTR)(LPCTSTR)strSex;
				m_listControl.SetItem(&lvItem); //

				lvItem.mask = LVIF_TEXT;
				lvItem.iItem = nDept;
				lvItem.iSubItem = 4;
				lvItem.pszText = (LPWSTR)(LPCTSTR)m_studentInfo[i].strAddress;
				m_listControl.SetItem(&lvItem); //

				nDept++;
			}
		}
		else if(m_nSelectedNode == m_hPhysics) // �����а� ���õǾ��ٸ�
		{
			if(m_studentInfo[i].strDept == "�����а�")
			{
				LV_ITEM lvItem;	
				lvItem.mask = LVIF_TEXT;
				lvItem.iItem = nDept; // ...
				lvItem.iSubItem = 0;
				lvItem.pszText = (LPWSTR)(LPCTSTR)m_studentInfo[i].strID;
				m_listControl.InsertItem(&lvItem); //
				
				lvItem.mask = LVIF_TEXT;
				lvItem.iItem = nDept;
				lvItem.iSubItem = 1;
				lvItem.pszText = (LPWSTR)(LPCTSTR)m_studentInfo[i].strName;
				m_listControl.SetItem(&lvItem); //

				lvItem.mask = LVIF_TEXT;
				lvItem.iItem = nDept;
				lvItem.iSubItem = 2;
				lvItem.pszText = (LPWSTR)(LPCTSTR)strLevel;
				m_listControl.SetItem(&lvItem); //

				lvItem.mask = LVIF_TEXT;
				lvItem.iItem = nDept;
				lvItem.iSubItem = 3;
				lvItem.pszText = (LPWSTR)(LPCTSTR)strSex;
				m_listControl.SetItem(&lvItem); //

				lvItem.mask = LVIF_TEXT;
				lvItem.iItem = nDept;
				lvItem.iSubItem = 4;
				lvItem.pszText = (LPWSTR)(LPCTSTR)m_studentInfo[i].strAddress;
				m_listControl.SetItem(&lvItem); //

				nDept++;
			}
		}
	}

	((CButton*)GetDlgItem(IDC_BUTTON_INSERT))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);


	UpdateData(FALSE);
	*pResult = 0;
}


void CMy20111688E7Dlg::OnItemchangedListControl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_nSelectedItem = pNMLV->iItem;

	m_selectList = true;

		((CButton*)GetDlgItem(IDC_BUTTON_INSERT))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(TRUE);

	*pResult = 0;
}


void CMy20111688E7Dlg::OnClickedButtonModify()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	
	CStudentDialog studentDialog;
	// 1. ����Ʈ�� �ִ� �� -> �л� ���� ���̾�α׿� ���� 
	studentDialog.m_strNumber = m_listControl.GetItemText(m_nSelectedItem,0); // �й�
	studentDialog.m_strName = m_listControl.GetItemText(m_nSelectedItem,1); // �̸�
	if(m_listControl.GetItemText(m_nSelectedItem,2) == "1�г�") //1�г� �ΰ��
	{
		studentDialog.m_intLevel = 0;
	}
	else if(m_listControl.GetItemText(m_nSelectedItem,2) == "2�г�") //2�г� �ΰ��
	{
		studentDialog.m_intLevel = 1;
	}
	else if(m_listControl.GetItemText(m_nSelectedItem,2) == "3�г�") //1�г� �ΰ��
	{
		studentDialog.m_intLevel = 2;
	}
	else // 4�г��ΰ��
	{
		studentDialog.m_intLevel = 3;
	}
	if(m_listControl.GetItemText(m_nSelectedItem,3) == "����") // ����
	{
		studentDialog.m_intSex = 0;
	}
	else if(m_listControl.GetItemText(m_nSelectedItem,3) == "����") 
	{
		studentDialog.m_intSex = 1;
	}
	studentDialog.m_strAddress = m_listControl.GetItemText(m_nSelectedItem,4); // �ּ�

if(studentDialog.DoModal() == IDOK) // 2. ������ �л� ���� ���̾�α��� �� ������ ����Ʈ�� ����
{
		LV_ITEM lvItem;

				CString strLevel;
				if(studentDialog.m_intLevel==0)
				{
					strLevel.Format(_T("1�г�"));
				}
				else if(studentDialog.m_intLevel==1)
				{
					strLevel.Format(_T("2�г�"));
				}
				else if(studentDialog.m_intLevel==2)
				{
					strLevel.Format(_T("3�г�"));
				}
				else if(studentDialog.m_intLevel==3)
				{
					strLevel.Format(_T("4�г�"));
				}
				
				CString strSex;
				if(studentDialog.m_intSex==0)
				{
					strSex.Format(_T("����"));
				}
				else if(studentDialog.m_intSex==1)
				{
					strSex.Format(_T("����"));
				}

		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = m_nSelectedItem;
		lvItem.iSubItem = 0;
		lvItem.pszText = (LPWSTR)(LPCTSTR)studentDialog.m_strNumber;
		m_listControl.SetItem(&lvItem);

		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = m_nSelectedItem;
		lvItem.iSubItem = 1;
		lvItem.pszText = (LPWSTR)(LPCTSTR)studentDialog.m_strName;
		m_listControl.SetItem(&lvItem);

		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = m_nSelectedItem;
		lvItem.iSubItem = 2;
		lvItem.pszText = (LPWSTR)(LPCTSTR)strLevel;
		m_listControl.SetItem(&lvItem);

		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = m_nSelectedItem;
		lvItem.iSubItem = 3;
		lvItem.pszText = (LPWSTR)(LPCTSTR)strSex;
		m_listControl.SetItem(&lvItem);

		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = m_nSelectedItem;
		lvItem.iSubItem = 4;
		lvItem.pszText = (LPWSTR)(LPCTSTR)studentDialog.m_strAddress;
		m_listControl.SetItem(&lvItem);

	if(!studentDialog.m_strNumber.IsEmpty() && !studentDialog.m_strName.IsEmpty() && !studentDialog.m_strAddress)
	{
		AfxMessageBox(_T("�˸��� �����͸� �Է��ϼ���"));
		return;
	}

}
	for(int i=0; i<m_nCount; i++) // 3. ������ ����Ʈ ���� -> �л� �迭 ����ü���� ����( if �й� �̿� ) 
	{
		if(m_listControl.GetItemText(m_nSelectedItem,0) == m_studentInfo[i].strID) // �й��� ���ٸ�
		{
			m_studentInfo[i].strName = studentDialog.m_strName;
			m_studentInfo[i].nGrade = studentDialog.m_intLevel;
			m_studentInfo[i].nSex = studentDialog.m_intSex;
			m_studentInfo[i].strAddress = studentDialog.m_strAddress;
		}
	}

	((CButton*)GetDlgItem(IDC_BUTTON_INSERT))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);

	m_selectTree = false;
	m_selectList = false;

	UpdateData(FALSE);
}


void CMy20111688E7Dlg::OnClickedButtonDelete()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	

if(m_deleteDialog.DoModal() == IDOK)
{
	for(int i=0; i<m_nCount; i++)
	{
		if(m_listControl.GetItemText(m_nSelectedItem,0) == m_studentInfo[i].strID) // �й��� ���ٸ� student ����
		{
			int j;
			for(j=i; j<m_nCount-1; j++)
			{
				m_studentInfo[j].strDept = m_studentInfo[j+1].strDept;
				m_studentInfo[j].strID = m_studentInfo[j+1].strID;
				m_studentInfo[j].strName = m_studentInfo[j+1].strName;
				m_studentInfo[j].nGrade = m_studentInfo[j+1].nGrade;
				m_studentInfo[j].nSex = m_studentInfo[j+1].nSex;
				m_studentInfo[j].strAddress = m_studentInfo[j+1].strAddress;
			}
			m_studentInfo[j].strDept.Empty();
			m_studentInfo[j].strID.Empty(); 
			m_studentInfo[j].strName.Empty();
			m_studentInfo[j].nGrade = 0;
			m_studentInfo[j].nSex = 0;
			m_studentInfo[j].strAddress.Empty();

			m_nCount--;
		}
	}
	
	m_listControl.DeleteItem(m_nSelectedItem);
	 // ����Ʈ���� ����
}
	((CButton*)GetDlgItem(IDC_BUTTON_INSERT))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);
	
	UpdateData(FALSE);

}
