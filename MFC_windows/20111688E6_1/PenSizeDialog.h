#pragma once
#include "afxcmn.h"


// CPenSizeDialog ��ȭ �����Դϴ�.

class CPenSizeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPenSizeDialog)

public:
	CPenSizeDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPenSizeDialog();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_PEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	UINT m_editPenSize; // ������ ��Ʈ�� ����
	CSpinButtonCtrl m_spinPenSize; // ���� ��Ʈ�� ����
	virtual BOOL OnInitDialog();
};
