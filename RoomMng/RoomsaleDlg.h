#pragma once
#include "atltime.h"
#include "afxcmn.h"
#include "afxwin.h"


// CRoomsaleDlg dialog

class CRoomsaleDlg : public CDialog
{
	DECLARE_DYNAMIC(CRoomsaleDlg)

public:
	CRoomsaleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRoomsaleDlg();

	////////////////////////// ��ʼ�ֶ���Ӵ��� ///////////////////////
	// ����ADO���ӡ������¼������ָ��
	_ConnectionPtr	m_pConnection;
	_CommandPtr		m_pCommand;
	_RecordsetPtr	m_pRecordset;

	CString m_checkoutdate;

	CString m_regnumber;
	CString m_name;
	CString m_roomnumber;
	CString m_room_money;
	CString m_realdays;
	CString m_extramoney;
	CString m_discount;
	CString m_totalPay;
	CString m_showuser;

	void showinList(int);
	////////////////////////// �����ֶ���Ӵ��� ///////////////////////

// Dialog Data
	enum { IDD = IDD_DIg_roomsale };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CTime m_roomsaleenddate;
	CTime m_roomsalebegindate;
	CListCtrl m_roomsale_list;
	double m_totalSum;
	double m_extraSum;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
