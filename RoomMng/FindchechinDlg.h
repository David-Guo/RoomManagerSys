#pragma once
#include "afxcmn.h"


// CFindchechinDlg dialog

class CFindchechinDlg : public CDialog
{
	DECLARE_DYNAMIC(CFindchechinDlg)

public:
	CFindchechinDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFindchechinDlg();

	// ��ʼ�ֶ���ӵĴ���
	CString sendfindroomnumber;
	// ����ADO���ӡ������¼������ָ��
	_ConnectionPtr	m_pConnection;
	_CommandPtr		m_pCommand;
	_RecordsetPtr	m_pRecordset;
	_RecordsetPtr	m_pRecordsetfind;

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
	// �����ֶ���ӵĴ���

// Dialog Data
	enum { IDD = IDD_DIg_findcheckin };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_findcheckin_name;
	CListCtrl m_findcheckin_list;
	virtual BOOL OnInitDialog();
};
