#pragma once


// CAdduserDlg dialog

class CAdduserDlg : public CDialog
{
	DECLARE_DYNAMIC(CAdduserDlg)

public:
	CAdduserDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAdduserDlg();

	// 开始手动添加的代码
	// 定义ADO连接、命令、记录集变量指针
	_ConnectionPtr	m_pConnection;
	_CommandPtr		m_pCommand;
	_RecordsetPtr	m_pRecordset;
	// 结束手动添加的代码

// Dialog Data
	enum { IDD = IDD_DIg_adduser };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_userid;
	CString m_pwd;
	virtual void OnOK();
};
