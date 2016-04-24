
// RoomMng.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "RoomMng.h"
#include "RoomMngDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoomMngApp

BEGIN_MESSAGE_MAP(CRoomMngApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoomMngApp construction

CRoomMngApp::CRoomMngApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CRoomMngApp object

CRoomMngApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRoomMngApp initialization

BOOL CRoomMngApp::InitInstance()
{
	try//连接数据库
	{
		CString strConnect;
		strConnect.Format(L"DSN=myhotel;");
		if(!m_DB.OpenEx(strConnect, CDatabase::useCursorLib))
		{
			AfxMessageBox(L"Unable to Connect to the Specified Data Source");
			return FALSE ;
		}
	}
	catch(CDBException *pE)//抛出异常
	{
		pE->ReportError();
		pE->Delete();
		return FALSE;
	}

	AfxEnableControlContainer();
	//SetDialogBkColor (RGB (140, 180, 220), RGB (225, 71, 6,));
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	//Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	//Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// ------------------------------------------------------------------------------------------------
	// 初始化COM,创建ADO连接等操作
	CoInitialize(NULL);
	if (!AfxOleInit())
	{
		AfxMessageBox(L"OLE初始化出错!");
		return FALSE;
	}
	m_pConnection.CreateInstance(__uuidof(Connection));

	// 在ADO操作中建议语句中要常用try...catch()来捕获错误信息，
	// 
	try                 
	{	//Provider=DAVID-PC\SQLEXPRESS;Persist Security Info=False;Data Source=myhotel
		// 打开本地数据库Data Source=DAVID-PC\SQLEXPRESS;Initial Catalog=myhotel;Integrated Security=True;Connect Timeout=15;Encrypt=False;TrustServerCertificate=False
		m_pConnection->Open("DAVID-PC\SQLEXPRESS;Persist Security=False;Data Source=myhotel","","",adModeUnknown);

	}
	catch(_com_error e)//抛出可能发生的异常
	{
		CString errormessage;
		errormessage.Format(L"连接数据库失败！\r\n错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
		//AfxMessageBox("数据库连接失败，确认数据库配置正确!");
		return FALSE;
	} 
	// ---------------------------------------------------------------------------------------------------


	CRoomMngDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

