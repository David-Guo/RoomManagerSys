// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomMng.h"
#include "LoginDlg.h"
#include "afxdialogex.h"

extern CString loguserid;
/////////////////////////////////////////////////////////////////////////////
// LoginDlg dialog

IMPLEMENT_DYNAMIC(LoginDlg, CDialog)

LoginDlg::LoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(LoginDlg::IDD, pParent)
	, m_password(_T(""))
	, m_username(_T(""))
{
}

LoginDlg::~LoginDlg()
{
}

void LoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_username, m_usernamectr);
	DDX_Text(pDX, IDC_password, m_password);
	DDX_CBString(pDX, IDC_COMBO_username, m_username);
}


BEGIN_MESSAGE_MAP(LoginDlg, CDialog)
	ON_BN_CLICKED(IDOK, &LoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LoginDlg message handlers


void LoginDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString sqlStr;
	UpdateData(true);
	if(m_username.IsEmpty())//�ж��û����Ƿ�Ϊ��
	{
		MessageBox("�������û���!","�ͷ�����ϵͳ");
		return;
	}
	//construct the  sql string
	//������ѯ���
	sqlStr="SELECT * FROM usertalbe WHERE user_name='";
	sqlStr+=m_username;
	sqlStr+="'";


	sqlStr+="AND user_pwd='";
	sqlStr+=m_password;
	sqlStr+="'";
	//	MessageBox(sqlStr);
	//�����ݿ�
	if(!myuserset.Open(AFX_DB_USE_DEFAULT_TYPE,sqlStr))
	{
		MessageBox("user���ʧ��!","�ͷ�����ϵͳ");
		return;
	}
	loguserid = m_username;//�������ԱID����������Ҫ��

	if(!myuserset.IsEOF())//�ر����ݿ�����
	{
		myuserset.Close();
		CDialog::OnOK();
	}
	else
	{                         //����������ʾ
		MessageBox("��½ʧ��!","�ͷ�����ϵͳ");
		m_username=_T("");
		m_password=_T("");
		UpdateData(false);//������ʾ
		myuserset.Close();//�ر����ݿ�����
		return;
	}
}


BOOL LoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
			// ʹ��ADO�������ݿ��¼��
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	_variant_t var;
	CString struser;
	// ��ADO�����н��������Ҫ����try...catch()�����������Ϣ��
	// 
	try
	{//�����ݿ�
		m_pRecordset->Open("SELECT * FROM usertalbe",                // ��ѯ ���������ֶ�
							theApp.m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
							adOpenDynamic,
							adLockOptimistic,
							adCmdText);
	}
	catch(_com_error *e)//��������ݿ���ܷ������쳣�����ʵʱ��ʾ��ʾ
	{
		AfxMessageBox(e->ErrorMessage());
	}
	try
	{
		if(!m_pRecordset->BOF)//�ж�ָ���Ƿ������ݼ����
			m_pRecordset->MoveFirst();
//		else
//		{//��ʾ����������
//			AfxMessageBox("��������Ϊ��");
//			return false;
//		}

		// read data from the database table 
		while(!m_pRecordset->adoEOF)
		{
			var = m_pRecordset->GetCollect("user_name");
			if(var.vt != VT_NULL)
				struser = (LPCSTR)_bstr_t(var);
			m_usernamectr.AddString(struser);//�����ݿ���
			                                   //�����ݸ�������ֵ
			m_pRecordset->MoveNext();//�ƶ�����ָ��
		}

		// 
		
	}
	catch(_com_error *e)//�����쳣
	{
		AfxMessageBox(e->ErrorMessage());
	}

	// �رռ�¼��
	m_pRecordset->Close();
	m_pRecordset = NULL;

	//������ʾ
//	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL LoginDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
		if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)
	{

		DWORD def_id=GetDefID();
		 if(def_id!=0)
		 {
			 //MSG��Ϣ�Ľṹ�е�hwnd�洢���ǽ��ո���Ϣ�Ĵ��ھ��
			 CWnd *wnd=FromHandle(pMsg->hwnd);
				 char class_name[16];
			 if(GetClassName(wnd->GetSafeHwnd(),class_name,sizeof(class_name))!=0)
			 {
				 DWORD style=::GetWindowLong(pMsg->hwnd,GWL_STYLE);
				 if((style&ES_MULTILINE)==0)
				 {
					 if(_strnicmp(class_name,"edit",5)==0)
					 {   //���������õ�Ĭ�ϰ�ť����
						 GetDlgItem(LOWORD(def_id))->SetFocus();
                         pMsg->wParam=VK_TAB;//���ػس�������ϢΪtable������Ϣ��ok��2006.4.18
						
					 }
				 }

			 }
		 }
        
	}
	return CDialog::PreTranslateMessage(pMsg);
}
