#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "atltime.h"
#include "CheckinSet.h"
#include "RoominfoSet.h"

// CheckinDlg dialog

class CheckinDlg : public CDialog
{
	DECLARE_DYNAMIC(CheckinDlg)

public:
	CheckinDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CheckinDlg();

	// ��ʼ�ֶ���ӵĴ���
	CCheckinSet mycheckinregset;
	CRoominfoSet myroominfoset;
	void enable(bool bEnabled);

	CString	regnumber;
	double roommoney;

	bool issave;
	// ����ADO���ӡ������¼������ָ��
	_ConnectionPtr	m_pConnection;
	_CommandPtr		m_pCommand;
	_RecordsetPtr	m_pRecordset;
	// �����ֶ���ӵĴ���

// Dialog Data
	enum { IDD = IDD_DIg_checkin };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CString m_discount_kind;
	CString m_zhengjian_number;
	CString m_beizhu;
	CString m_gustname;
	CString m_regnumber;
	float m_pre_discount;
	CString m_telNumber;
	CString m_room_money;
	CString m_pre_handinmoney;
	CString m_realmoney;
	CComboBox m_roomnumberctr;
	CString m_roomnumber;
	double m_checkdays;
	CString m_roomlevel;
	CDateTimeCtrl m_checkindatectr;
	CTime m_checkindate;
	CString m_showuser;

	
	virtual void OnOK();
	afx_msg void OnBnClickedcheckreg();
	afx_msg void OnCbnSelchangeComboroomnumber();
	afx_msg void OnEnChangeEditdiscount();
	afx_msg void OnEnChangeEditbookdays();
};
