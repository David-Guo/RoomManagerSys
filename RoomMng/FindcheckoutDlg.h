#pragma once
#include "afxcmn.h"


// CFindcheckoutDlg dialog

class CFindcheckoutDlg : public CDialog
{
	DECLARE_DYNAMIC(CFindcheckoutDlg)

public:
	CFindcheckoutDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFindcheckoutDlg();

	////////////////////////// ��ʼ�ֶ���Ӵ��� ///////////////////////
	// ����ADO���ӡ������¼������ָ��
	_ConnectionPtr	m_pConnection;
	_CommandPtr		m_pCommand;
	_RecordsetPtr	m_pRecordset;

	CString m_zhengjian_number;
	CString m_beizhu;
	CString m_gustname;
	CString m_regnumber;
	CString m_pre_discount;
	CString m_telNumber;
	CString m_room_money;
	CString m_pre_handinmoney;
	CString m_realmoney;
	CString m_roomnumber;
	CString m_checkdays;
	CString m_roomlevel;
	CString m_checkindate;
	CString m_showuser;
	void showinList();
	////////////////////////// �����ֶ���Ӵ��� ///////////////////////

// Dialog Data
	enum { IDD = IDD_DIg_findcheckin };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_findcheckout_name;
	CListCtrl m_findcheckout_list;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	
};
