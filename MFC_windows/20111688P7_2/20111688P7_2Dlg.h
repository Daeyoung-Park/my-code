
// 20111688P7_2Dlg.h : ��� ����
//

#pragma once


// CMy20111688P7_2Dlg ��ȭ ����
class CMy20111688P7_2Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMy20111688P7_2Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MY20111688P7_2_DIALOG };

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
	afx_msg void OnSelchangedTreeControl(NMHDR *pNMHDR, LRESULT *pResult);
	CTreeCtrl m_treeControl; // Ʈ�� ��Ʈ�� ����
	CString m_strSelectedNode; // ���õ� ��� ���ڿ� ���
	CString m_strNodeText; //  �Է��� ��� �ؽ�Ʈ
	HTREEITEM m_hRoot; // ��Ʈ�� �ش��ϴ� ���
	HTREEITEM m_hSelectedNode; // ���õ� ���
	afx_msg void OnBegindragTreeControl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedButtonInsert();
	afx_msg void OnClickedButtonModify();
	afx_msg void OnClickedButtonDelete();
};
