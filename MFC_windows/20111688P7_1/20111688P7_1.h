
// 20111688P7_1.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMy20111688P7_1App:
// �� Ŭ������ ������ ���ؼ��� 20111688P7_1.cpp�� �����Ͻʽÿ�.
//

class CMy20111688P7_1App : public CWinApp
{
public:
	CMy20111688P7_1App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMy20111688P7_1App theApp;