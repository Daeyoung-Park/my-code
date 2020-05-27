#pragma once
#include "afxwin.h"


// CTextDialog ��ȭ �����Դϴ�.

class CTextDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTextDialog)

public:
	CTextDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTextDialog();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_TEXT };

public:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strColorOut;
	CString m_strFontOut;
	afx_msg void OnClickedButtonTextout();
	CEdit m_strTextString;
	afx_msg void OnClickedButtonColor();
	afx_msg void OnClickedButtonFont();
	
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEnChangeEditX();
	afx_msg void OnEnChangeEditY();
	CString m_strEditX;
	CString m_strEditY;
};
