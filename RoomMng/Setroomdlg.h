#pragma once
#include "afxcmn.h"
#include "RoominfoSet.h"


// CSetroomdlg dialog

class CSetroomdlg : public CDialog
{
	DECLARE_DYNAMIC(CSetroomdlg)

public:
	CSetroomdlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetroomdlg();

	//////////////////  ��ʼ�ֶ���Ӵ��� ////////////////////
	CRoominfoSet mysetroomset;
	//CTETSET MYTESTSET;

	void enable(bool bEnabled);	
	// ����ADO���ӡ������¼������ָ��
	_ConnectionPtr	m_pConnection;
	_CommandPtr		m_pCommand;
	_RecordsetPtr	m_pRecordset;
    _RecordsetPtr	m_pRecordset1;

	CString showroom_roomnumber;
	CString showroom_roomlevel;
	CString showroom_roommoney;
	CString showroom_roomstate;
	CString showroom_roomsetting;

	void enbale(bool bEnabled);
	//////////////////  �����ֶ���Ӵ��� ////////////////////

	// Dialog Data
	enum { IDD = IDD_DIg_setroom };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_roomlevel;
	CString m_roomstate;
	CListCtrl m_setroomdlg_list;
	CString m_roomset;
	CString m_roommoney;
	CString m_roomnumber;
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedclearset();
	afx_msg void OnBnClickedbeginsetroom();
};
