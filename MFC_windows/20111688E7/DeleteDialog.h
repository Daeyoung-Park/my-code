#pragma once


// CDeleteDialog ��ȭ �����Դϴ�.

class CDeleteDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CDeleteDialog)

public:
	CDeleteDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDeleteDialog();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_DELETE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
