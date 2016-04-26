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
	//INSERT INTO checkinregtable (ƾ֤����)VALUES('%s')
	CString strsql;
	strsql.Format("SELECT * FROM usertalbe where user_name='%s' and user_pwd='%s'",m_userid,m_oldpwd);
	//�����ݱ�
	try
	{
		m_pRecordset->Open(_variant_t(strsql), // ��ѯ���������ֶ�
			theApp.m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)//�����쳣���
	{
		AfxMessageBox(e->ErrorMessage());
	}

	if(!m_pRecordset->BOF)//�ж�ָ���Ƿ������ݼ����
		m_pRecordset->MoveFirst();
	else
	{
		MessageBox("�˺Ż��������","�ͷ�����ϵͳ");
		return;
	}
	try
	{       //д�����ݱ�
		m_pRecordset->PutCollect("user_pwd", _variant_t(m_newpwd));
		m_pRecordset->Update();//�������ݱ�

		MessageBox("�����޸ĳɹ�!","�ͷ�����ϵͳ");
		//	UpdateData(false);
	}
	catch(_com_error *e)//���������쳣
	{
		AfxMessageBox(e->ErrorMessage());
	}

	m_pRecordset->Close();
	m_pRecordset = NULL;
	CDialog::OnOK();
}
