#pragma once


// CAdduserDlg dialog

class CAdduserDlg : public CDialog
{
	DECLARE_DYNAMIC(CAdduserDlg)

public:
	CAdduserDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAdduserDlg();

	// ��ʼ�ֶ���ӵĴ���
	// ����ADO���ӡ������¼������ָ��
	_ConnectionPtr	m_pConnection;
	_CommandPtr		m_pCommand;
	_RecordsetPtr	m_pRecordset;
	// �����ֶ���ӵĴ���

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
