// SetpasswordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomMng.h"
#include "SetpasswordDlg.h"
#include "afxdialogex.h"

/////////////////////////////////////////////////////////////////////////////
// CSetpasswordDlg dialog

IMPLEMENT_DYNAMIC(CSetpasswordDlg, CDialog)

	CSetpasswordDlg::CSetpasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetpasswordDlg::IDD, pParent)
	, m_userid(_T(""))
	, m_newpwd(_T(""))
	, m_oldpwd(_T(""))
{

}

CSetpasswordDlg::~CSetpasswordDlg()
{
}

void CSetpasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_username, m_userid);
	DDX_Text(pDX, IDC_newpwd, m_newpwd);
	DDX_Text(pDX, IDC_oldpwd, m_oldpwd);
}


BEGIN_MESSAGE_MAP(CSetpasswordDlg, CDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetpasswordDlg message handlers


void CSetpasswordDlg::OnOK() 
{
	// TODO: Add extra validation here

	UpdateData(true);

	m_pRecordset.CreateInstance(__uuidof(Recordset));
	//INSERT INTO checkinregtable (凭证号码)VALUES('%s')
	CString strsql;
	strsql.Format("SELECT * FROM usertalbe where user_name='%s' and user_pwd='%s'",m_userid,m_oldpwd);
	//打开数据表
	try
	{
		m_pRecordset->Open(_variant_t(strsql), // 查询表中所有字段
			theApp.m_pConnection.GetInterfacePtr(),	 // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)//捕获异常情况
	{
		AfxMessageBox(e->ErrorMessage());
	}

	if(!m_pRecordset->BOF)//判断指针是否在数据集最后
		m_pRecordset->MoveFirst();
	else
	{
		MessageBox("账号或密码错误！","客房管理系统");
		return;
	}
	try
	{       //写入数据表
		m_pRecordset->PutCollect("user_pwd", _variant_t(m_newpwd));
		m_pRecordset->Update();//更新数据表

		MessageBox("密码修改成功!","客房管理系统");
		//	UpdateData(false);
	}
	catch(_com_error *e)//捕获发生的异常
	{
		AfxMessageBox(e->ErrorMessage());
	}

	m_pRecordset->Close();
	m_pRecordset = NULL;
	CDialog::OnOK();
}
