#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CFindRoomDlg dialog

class CFindRoomDlg : public CDialog
{
	DECLARE_DYNAMIC(CFindRoomDlg)

public:
	CFindRoomDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFindRoomDlg();

	////////////////////////// ��ʼ�ֶ���Ӵ��� ///////////////////////
	// ����ADO���ӡ������¼������ָ��
	_ConnectionPtr	m_pConnection;
	_CommandPtr		m_pCommand;
	_RecordsetPtr	m_pRecordset,m_pRecordsetdel;

	_RecordsetPtr	m_pRecordsetout;
	CString findroom_roomnumber;
	CString findroom_roomlevel;
	CString findroom_roommoney;
	CString findroom_roomstate;
	CString findroom_roomsetting;
	////////////////////////// �����ֶ���Ӵ��� ///////////////////////

// Dialog Data
	enum { IDD = IDD_DIg_findroom };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	CString m_findroom_roomlevel;
	CString m_findroom_roommoney;
	CString m_findroom_status;
	CString m_findroom_roomsetting;
	CComboBox m_findroomdlgroomnumberctr;
	CString m_findroomdlgroomnumber;
	CString m_findroom_roomnumber;
	CListCtrl m_findroom_list;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCbnCloseupCombofindroomnum();
	afx_msg void OnNMClickListfindroom(NMHDR *pNMHDR, LRESULT *pResult);
};
