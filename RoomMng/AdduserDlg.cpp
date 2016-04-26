// AdduserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomMng.h"
#include "AdduserDlg.h"
#include "afxdialogex.h"


// CAdduserDlg dialog

IMPLEMENT_DYNAMIC(CAdduserDlg, CDialog)

	CAdduserDlg::CAdduserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdduserDlg::IDD, pParent)
	, m_userid(_T(""))
	, m_pwd(_T(""))
{

}

CAdduserDlg::~CAdduserDlg()
{
}

void CAdduserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_username, m_userid);
	DDX_Text(pDX, IDC_oldpwd, m_pwd);
}


BEGIN_MESSAGE_MAP(CAdduserDlg, CDialog)
END_MESSAGE_MAP()


// CAdduserDlg message handlers


void CAdduserDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(true);

	m_pRecordset.CreateInstance(__uuidof(Recordset));
	//INSERT INTO checkinregtable (凭证号码)VALUES('%s')
	CString strsql;
	strsql.Format("SELECT * FROM usertalbe where user_name='%s'" ,m_userid);
	//打开数据表
	try
	{
		m_pRecordset->Open(_variant_t(strsql), // 查询表中 user_name 字段
			theApp.m_pConnection.GetInterfacePtr(),	 // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)//捕获异常情况
	{
		AfxMessageBox(e->ErrorMessage());
	}

	if(m_pRecordset->BOF){ //判断指针是否在数据集最后 
		//m_pRecordset->MoveFirst();
		try
		{ // 写入各字段值，准备更新数据库
			m_pRecordset->AddNew();
			m_pRecordset->PutCollect("user_name", _variant_t(m_userid));
			m_pRecordset->PutCollect("user_pwd", _variant_t(m_pwd));

			m_pRecordset->Update();
			MessageBox("添加账号成功！", "客房管理系统");
		}
		catch(_com_error *e)//捕获写入数据库时候可能发生的异常情况
		{
			AfxMessageBox(e->ErrorMessage());
		}
	}
	else
	{
		MessageBox("改账号已存在，请重新输入！","客房管理系统");
		return;
	}

	m_pRecordset->Close();
	m_pRecordset = NULL;
	//CDialog::OnOK();
}
