
// 20111688P7_1Dlg.h : ��� ����
//

#pragma once


// CMy20111688P7_1Dlg ��ȭ ����
class CMy20111688P7_1Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMy20111688P7_1Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MY20111688P7_1_DIALOG };

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
	CListCtrl m_listStudent; // ����Ʈ ��Ʈ�� ����
	CString m_strDept; // �а� ��Ʈ��
	CString m_strID; // �й� ��Ʈ��
	CString m_strName; // �̸� ��Ʈ��
	CString m_strSelectItem; // ���õ� �������� ��ȣ
	afx_msg void OnClickedButtonInsert();
	int m_nSelectedItem;
	afx_msg void OnItemchangedListStudent(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedButtonModify();
	afx_msg void OnClickedButtonDelete();
	afx_msg void OnClickedButtonReset();
	afx_msg void OnSelchangeComboStyle();
};
