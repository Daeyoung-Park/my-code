
// 20111688E6_1.h : 20111688E6_1 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMy20111688E6_1App:
// �� Ŭ������ ������ ���ؼ��� 20111688E6_1.cpp�� �����Ͻʽÿ�.
//

class CMy20111688E6_1App : public CWinAppEx
{
public:
	CMy20111688E6_1App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy20111688E6_1App theApp;
