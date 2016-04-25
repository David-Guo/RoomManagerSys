#pragma once

#include "Userset.h"
#include "afxwin.h"
// LoginDlg dialog

class LoginDlg : public CDialog
{
	DECLARE_DYNAMIC(LoginDlg)

public:
	LoginDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~LoginDlg();

	CUserset myuserset;

	// 定义ADO连接、命令、记录集变量指针
	_ConnectionPtr	m_pConnection;
	_CommandPtr		m_pCommand;
	_RecordsetPtr	m_pRecordset;
// Dialog Data
	enum { IDD = IDD_LOGINdlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();

	CComboBox m_usernamectr;
	CString m_password;
	CString m_username;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
