#pragma once
#include "afxwin.h"
#include "RoominfoSet.h"


// CCheckoutDlg dialog

class CCheckoutDlg : public CDialog
{
	DECLARE_DYNAMIC(CCheckoutDlg)

public:
	CCheckoutDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCheckoutDlg();

	// ��ʼ�ֶ���ӵĴ���
	CRoominfoSet mymendroominfoset;
	void enable(bool bEnabled);

	// ����ADO���ӡ������¼������ָ��
	_ConnectionPtr	m_pConnection;
	_CommandPtr		m_pCommand;
	_RecordsetPtr	m_pRecordset;

	_RecordsetPtr	m_pRecordsetout;
	CString checkinday;
	// �����ֶ���ӵĴ���

	// Dialog Data
	enum { IDD = IDD_DIg_checkout };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_checknumber;
	CComboBox m_regnumber_ctr;
	CString m_regnumber;
	CString m_checkoutbeizhu;
	CString m_roomlevel;
	CString m_prehandinmoney;
	CString m_realdays;
	CString m_name;
	CString m_extramoney;
	CString m_discount;
	CString m_totalPay;
	CString m_checkoutroommoney;
	CString m_roomnumber;
	virtual BOOL OnInitDialog();
	CString m_showuser;
	afx_msg void OnBnClickedButtonreg();
	afx_msg void OnCbnCloseupComboregnumber();
	CString m_checkoutzhenjian_number;
	CString m_telNum;
	afx_msg void OnEnChangeEditotherpay();
	afx_msg void OnBnClickedButtonclear();
	virtual void OnOK();
};
