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
	if(m_username.IsEmpty())//判断用户名是否为空
	{
		MessageBox("请输入用户名!","客房管理系统");
		return;
	}
	//construct the  sql string
	//创建查询语句
	sqlStr="SELECT * FROM usertalbe WHERE user_name='";
	sqlStr+=m_username;
	sqlStr+="'";


	sqlStr+="AND user_pwd='";
	sqlStr+=m_password;
	sqlStr+="'";
	//	MessageBox(sqlStr);
	//打开数据库
	if(!myuserset.Open(AFX_DB_USE_DEFAULT_TYPE,sqlStr))
	{
		MessageBox("user表打开失败!","客房管理系统");
		return;
	}
	loguserid = m_username;//保存操作员ID，其他窗口要用

	if(!myuserset.IsEOF())//关闭数据库连接
	{
		myuserset.Close();
		CDialog::OnOK();
	}
	else
	{                         //给出错误提示
		MessageBox("登陆失败!","客房管理系统");
		m_username=_T("");
		m_password=_T("");
		UpdateData(false);//更新显示
		myuserset.Close();//关闭数据库连接
		return;
	}
}


BOOL LoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
			// 使用ADO创建数据库记录集
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	_variant_t var;
	CString struser;
	// 在ADO操作中建议语句中要常用try...catch()来捕获错误信息，
	// 
	try
	{//打开数据库
		m_pRecordset->Open("SELECT * FROM usertalbe",                // 查询 表中所有字段
							theApp.m_pConnection.GetInterfacePtr(),	 // 获取库接库的IDispatch指针
							adOpenDynamic,
							adLockOptimistic,
							adCmdText);
	}
	catch(_com_error *e)//捕获打开数据库可能发生的异常情况并实时显示提示
	{
		AfxMessageBox(e->ErrorMessage());
	}
	try
	{
		if(!m_pRecordset->BOF)//判断指针是否在数据集最后
			m_pRecordset->MoveFirst();
//		else
//		{//提示错误，无数据
//			AfxMessageBox("表内数据为空");
//			return false;
//		}

		// read data from the database table 
		while(!m_pRecordset->adoEOF)
		{
			var = m_pRecordset->GetCollect("user_name");
			if(var.vt != VT_NULL)
				struser = (LPCSTR)_bstr_t(var);
			m_usernamectr.AddString(struser);//从数据库获得
			                                   //的内容给变量赋值
			m_pRecordset->MoveNext();//移动数据指针
		}

		// 
		
	}
	catch(_com_error *e)//捕获异常
	{
		AfxMessageBox(e->ErrorMessage());
	}

	// 关闭记录集
	m_pRecordset->Close();
	m_pRecordset = NULL;

	//更新显示
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
			 //MSG消息的结构中的hwnd存储的是接收该消息的窗口句柄
			 CWnd *wnd=FromHandle(pMsg->hwnd);
				 char class_name[16];
			 if(GetClassName(wnd->GetSafeHwnd(),class_name,sizeof(class_name))!=0)
			 {
				 DWORD style=::GetWindowLong(pMsg->hwnd,GWL_STYLE);
				 if((style&ES_MULTILINE)==0)
				 {
					 if(_strnicmp(class_name,"edit",5)==0)
					 {   //将焦点设置到默认按钮上面
						 GetDlgItem(LOWORD(def_id))->SetFocus();
                         pMsg->wParam=VK_TAB;//重载回车键盘消息为table键盘消息，ok！2006.4.18
						
					 }
				 }

			 }
		 }
        
	}
	return CDialog::PreTranslateMessage(pMsg);
}
