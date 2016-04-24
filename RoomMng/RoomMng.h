
// RoomMng.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CRoomMngApp:
// See RoomMng.cpp for the implementation of this class
//

class CRoomMngApp : public CWinApp
{
public:
	CRoomMngApp();
	CDatabase m_DB;

	// 定义ADO连接变量指针
	_ConnectionPtr	m_pConnection;

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CRoomMngApp theApp;