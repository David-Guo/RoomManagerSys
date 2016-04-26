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
	//INSERT INTO checkinregtable (ƾ֤����)VALUES('%s')
	CString strsql;
	strsql.Format("SELECT * FROM usertalbe where user_name='%s'" ,m_userid);
	//�����ݱ�
	try
	{
		m_pRecordset->Open(_variant_t(strsql), // ��ѯ���� user_name �ֶ�
			theApp.m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)//�����쳣���
	{
		AfxMessageBox(e->ErrorMessage());
	}

	if(m_pRecordset->BOF){ //�ж�ָ���Ƿ������ݼ���� 
		//m_pRecordset->MoveFirst();
		try
		{ // д����ֶ�ֵ��׼���������ݿ�
			m_pRecordset->AddNew();
			m_pRecordset->PutCollect("user_name", _variant_t(m_userid));
			m_pRecordset->PutCollect("user_pwd", _variant_t(m_pwd));

			m_pRecordset->Update();
			MessageBox("����˺ųɹ���", "�ͷ�����ϵͳ");
		}
		catch(_com_error *e)//����д�����ݿ�ʱ����ܷ������쳣���
		{
			AfxMessageBox(e->ErrorMessage());
		}
	}
	else
	{
		MessageBox("���˺��Ѵ��ڣ����������룡","�ͷ�����ϵͳ");
		return;
	}

	m_pRecordset->Close();
	m_pRecordset = NULL;
	//CDialog::OnOK();
}
