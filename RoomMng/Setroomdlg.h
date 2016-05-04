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

	//////////////////  开始手动添加代码 ////////////////////
	CRoominfoSet mysetroomset;
	//CTETSET MYTESTSET;

	void enable(bool bEnabled);	
	// 定义ADO连接、命令、记录集变量指针
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
	//////////////////  结束手动添加代码 ////////////////////

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
