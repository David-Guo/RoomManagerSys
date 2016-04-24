
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
	try//�������ݿ�
	{
		CString strConnect;
		strConnect.Format(L"DSN=myhotel;");
		if(!m_DB.OpenEx(strConnect, CDatabase::useCursorLib))
		{
			AfxMessageBox(L"Unable to Connect to the Specified Data Source");
			return FALSE ;
		}
	}
	catch(CDBException *pE)//�׳��쳣
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
	// ��ʼ��COM,����ADO���ӵȲ���
	CoInitialize(NULL);
	if (!AfxOleInit())
	{
		AfxMessageBox(L"OLE��ʼ������!");
		return FALSE;
	}
	m_pConnection.CreateInstance(__uuidof(Connection));

	// ��ADO�����н��������Ҫ����try...catch()�����������Ϣ��
	// 
	try                 
	{	//Provider=DAVID-PC\SQLEXPRESS;Persist Security Info=False;Data Source=myhotel
		// �򿪱������ݿ�Data Source=DAVID-PC\SQLEXPRESS;Initial Catalog=myhotel;Integrated Security=True;Connect Timeout=15;Encrypt=False;TrustServerCertificate=False
		m_pConnection->Open("DAVID-PC\SQLEXPRESS;Persist Security=False;Data Source=myhotel","","",adModeUnknown);

	}
	catch(_com_error e)//�׳����ܷ������쳣
	{
		CString errormessage;
		errormessage.Format(L"�������ݿ�ʧ�ܣ�\r\n������Ϣ:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
		//AfxMessageBox("���ݿ�����ʧ�ܣ�ȷ�����ݿ�������ȷ!");
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

