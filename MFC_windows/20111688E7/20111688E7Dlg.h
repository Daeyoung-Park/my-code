
// 20111688E7Dlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "studentdialog.h"
#include "deletedialog.h"

typedef struct
{
	CString strDept;
	CString strID;
	CString strName;
	int nGrade;
	int nSex;
	CString strAddress;
}Student;


// CMy20111688E7Dlg ��ȭ ����
class CMy20111688E7Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMy20111688E7Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MY20111688E7_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_treeControl;
	CListCtrl m_listControl;
	HTREEITEM m_hRoot; // ��Ʈ���
	CStudentDialog m_CStudentDialog; // �л� ���� ���̾�α� 
	HTREEITEM m_hKorean; // ������а�
	HTREEITEM m_hComputer; // ��ǻ���а�
	HTREEITEM m_hPhysics; // �����а�
	Student m_studentInfo[50]; // �л� ���� ������ �迭
	int m_nCount; // �迭�� ����� �л� ��
	int m_nSelectedItem; // ���õ� ����Ʈ �ε���
	HTREEITEM m_nSelectedNode; // ���õ� ���
	afx_msg void OnClickedButtonInsert();
	afx_msg void OnSelchangedTreeControl(NMHDR *pNMHDR, LRESULT *pResult);
	bool m_selectTree; // Ʈ���� ���õǾ��ٸ�
	bool m_selectList; // ����Ʈ�� ���õǾ��ٸ�
	afx_msg void OnItemchangedListControl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedButtonModify();
	afx_msg void OnClickedButtonDelete();
	CDeleteDialog m_deleteDialog; // ���� ���̾�α�
};
