#pragma once
#include "afxwin.h"


// CStudentDialog ��ȭ �����Դϴ�.

class CStudentDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CStudentDialog)

public:
	CStudentDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CStudentDialog();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_STUDENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strNumber; // �й�
	CString m_strName; // �̸�
	int m_intLevel; // �г�
	int m_intSex; // ����
	CString m_strAddress; // �ּ�
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboLevel();
	CComboBox m_cbLevel; // �г�
	CComboBox m_cbSex; // ����
	afx_msg void OnCbnSelchangeComboSex();
};
