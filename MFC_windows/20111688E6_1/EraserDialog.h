#pragma once
#include "afxcmn.h"


// CEraserDialog ��ȭ �����Դϴ�.

class CEraserDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CEraserDialog)

public:
	CEraserDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CEraserDialog();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_ERASER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	UINT m_editEraserSize; // ������ EDIT ��Ʈ�� ����
	CSpinButtonCtrl m_spinEraserSize; // ���� ��Ʈ�� ����
	virtual BOOL OnInitDialog();
};
