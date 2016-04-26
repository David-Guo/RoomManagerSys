// CheckoutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomMng.h"
#include "CheckoutDlg.h"
#include "afxdialogex.h"


extern CString loguserid;
/////////////////////////////////////////////////////////////////////////////
// CCheckoutDlg dialog

IMPLEMENT_DYNAMIC(CCheckoutDlg, CDialog)

	CCheckoutDlg::CCheckoutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckoutDlg::IDD, pParent)
	, m_regnumber(_T(""))
	, m_checkoutbeizhu(_T(""))
	, m_roomlevel(_T(""))
	, m_prehandinmoney(_T(""))
	, m_realdays(_T(""))
	, m_name(_T(""))
	, m_extramoney(_T(""))
	, m_discount(_T(""))
	, m_totalPay(_T(""))
	, m_checkoutroommoney(_T(""))
	, m_roomnumber(_T(""))
	, m_showuser(_T(""))
	, m_checkoutzhenjian_number(_T(""))
	, m_telNum(_T(""))
{

}

CCheckoutDlg::~CCheckoutDlg()
{
}

void CCheckoutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_regnumber, m_regnumber_ctr);
	DDX_CBString(pDX, IDC_COMBO_regnumber, m_regnumber);
	DDX_Text(pDX, IDC_EDIT_beizu, m_checkoutbeizhu);
	DDX_Text(pDX, IDC_STATIC_roomlevel, m_roomlevel);
	DDX_Text(pDX, IDC_EDIT1_prePay, m_prehandinmoney);
	DDX_Text(pDX, IDC_EDIT_checkDays, m_realdays);
	DDX_Text(pDX, IDC_EDIT_name, m_name);
	DDX_Text(pDX, IDC_EDIT_otherPay, m_extramoney);
	DDX_Text(pDX, IDC_EDIT_discount, m_discount);
	DDX_Text(pDX, IDC_EDIT_realmoney, m_totalPay);
	DDX_Text(pDX, IDC_EDIT_roommoney, m_checkoutroommoney);
	DDX_Text(pDX, IDC_STATIC_roomnum, m_roomnumber);
	DDX_Text(pDX, IDC_STATIC_userid, m_showuser);
	DDX_Text(pDX, IDC_STATIC_shengfenid, m_checkoutzhenjian_number);
	DDX_Text(pDX, IDC_STATIC_telNum, m_telNum);
}


BEGIN_MESSAGE_MAP(CCheckoutDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_reg, &CCheckoutDlg::OnBnClickedButtonreg)
	ON_CBN_CLOSEUP(IDC_COMBO_regnumber, &CCheckoutDlg::OnCbnCloseupComboregnumber)
	ON_EN_CHANGE(IDC_EDIT_otherPay, &CCheckoutDlg::OnEnChangeEditotherpay)
	ON_BN_CLICKED(IDC_BUTTON_clear, &CCheckoutDlg::OnBnClickedButtonclear)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckoutDlg message handlers


BOOL CCheckoutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// 使用ADO创建数据库记录集
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	_variant_t var;
	CString strregnumber;
	// 在ADO操作中建议语句中要常用try...catch()来捕获错误信息，
	try
	{//打开数据库
		m_pRecordset->Open("SELECT * FROM checkintable",                // 查询 表中所有字段
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
		else
		{//提示错误，无数据
			AfxMessageBox("表内数据为空");
			return false;
		}

		// read data from the database table 
		while(!m_pRecordset->adoEOF)
		{
			var = m_pRecordset->GetCollect("凭证号码");
			if(var.vt != VT_NULL)
				strregnumber = (LPCSTR)_bstr_t(var);
			m_regnumber_ctr.AddString(strregnumber);//从数据库获得
			//的内容给变量赋值
			m_pRecordset->MoveNext();//移动数据指针
		}
	}
	catch(_com_error *e)//捕获异常
	{
		AfxMessageBox(e->ErrorMessage());
	}

	// 关闭记录集
	m_pRecordset->Close();
	m_pRecordset = NULL;

	m_showuser=loguserid;
	//更新显示
	UpdateData(false);
	enable(0);
	//改变输入框状态
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CCheckoutDlg::enable(bool bEnabled)
{
	// m_ComYSFS.EnableWindow(bEnabled);
	//改变输入框状态
	GetDlgItem(IDC_COMBO_regnumber)->EnableWindow(bEnabled);
	GetDlgItem(IDC_EDIT_beizu)->EnableWindow(bEnabled);
	GetDlgItem(IDC_EDIT_roommoney)->EnableWindow(bEnabled);
	GetDlgItem(IDC_EDIT1_prePay)->EnableWindow(bEnabled);
	GetDlgItem(IDC_EDIT_checkDays)->EnableWindow(bEnabled);
	GetDlgItem(IDC_EDIT_otherPay)->EnableWindow(bEnabled);
	GetDlgItem(IDC_EDIT_discount)->EnableWindow(bEnabled);
	GetDlgItem(IDC_EDIT_name)->EnableWindow(bEnabled);
	GetDlgItem(IDC_EDIT_realmoney)->EnableWindow(bEnabled);
	GetDlgItem(IDOK)->EnableWindow(bEnabled);
	//改变输入框状态完毕

}


void CCheckoutDlg::OnBnClickedButtonreg()
{
	// TODO: Add your control notification handler code here
	//改变输入框状态
	enable(1);
}


void CCheckoutDlg::OnCbnCloseupComboregnumber()
{
	// TODO: Add your control notification handler code here
	_variant_t var;
	// 使用ADO创建数据库记录集
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	// 在ADO操作中建议语句中要常用try...catch()来捕获错误信息，
	UpdateData(true);

	CString checkoutnumber;
	CString strsql;
	strsql.Format("SELECT * FROM checkintable where 凭证号码='%s'",m_regnumber);
	try// 打开数据库
	{
		m_pRecordset->Open(_variant_t(strsql),                // 查询 表中所有字段
			theApp.m_pConnection.GetInterfacePtr(),	 // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)
	{// 捕获可能发生的异常
		AfxMessageBox(e->ErrorMessage());
	}
	checkoutnumber+="T";
	checkoutnumber+=m_regnumber;
	// 生产退宿的凭证号码
	m_checknumber =checkoutnumber;

	try
	{
		if(!m_pRecordset->BOF)//判断指针是否在数据集最后
			m_pRecordset->MoveFirst();
		else
		{// 
			MessageBox("表内数据为空","客房管理系统");
			return ;
		}
		// 读取数据表中姓名字段
		var = m_pRecordset->GetCollect("姓名");
		if(var.vt != VT_NULL)
			m_name = (LPCSTR)_bstr_t(var);
		// 读取数据表中证件号码字段
		var = m_pRecordset->GetCollect("身份证号码");
		if(var.vt != VT_NULL)
			m_checkoutzhenjian_number = (LPCSTR)_bstr_t(var);
		// 读取数据表中详细地址字段
		var = m_pRecordset->GetCollect("联系电话");
		if(var.vt != VT_NULL)
			m_telNum = (LPCSTR)_bstr_t(var);
		// 读取数据表中房间号字段
		var = m_pRecordset->GetCollect("房间号");
		if(var.vt != VT_NULL)
			m_roomnumber = (LPCSTR)_bstr_t(var);
		// 读取数据表中客房类型字段
		var = m_pRecordset->GetCollect("客房类型");
		if(var.vt != VT_NULL)
			m_roomlevel = (LPCSTR)_bstr_t(var);
		// 读取数据表中客房价格字段
		var = m_pRecordset->GetCollect("房间价格");
		if(var.vt != VT_NULL)
			m_checkoutroommoney = (LPCSTR)_bstr_t(var);
		// 读取数据表中入住时间字段
		var = m_pRecordset->GetCollect("入住时间");
		if(var.vt != VT_NULL)
			checkinday = (LPCSTR)_bstr_t(var);
		// 读取数据包中住宿天数字段
		var = m_pRecordset->GetCollect("住宿天数");
		if(var.vt != VT_NULL)
			m_realdays = (LPCSTR)_bstr_t(var);
		// 读取数据表中折扣字段
		var = m_pRecordset->GetCollect("折扣");
		if(var.vt != VT_NULL)
			m_discount = (LPCSTR)_bstr_t(var);
		// 读取数据表中押金字段
		var = m_pRecordset->GetCollect("押金");
		if(var.vt != VT_NULL)
			m_prehandinmoney = (LPCSTR)_bstr_t(var);
		else
			m_prehandinmoney ="0";
		// 读取数据表中备注字段
		var = m_pRecordset->GetCollect("备注");
		if(var.vt != VT_NULL)
			m_checkoutbeizhu = (LPCSTR)_bstr_t(var);

		UpdateData(false);
	}
	catch(_com_error *e)// 捕获异常
	{
		AfxMessageBox(e->ErrorMessage());
	}

	// 关闭记录集
	m_pRecordset->Close();
	m_pRecordset = NULL;

	UpdateData(false);// 更新显示截面输入框内容
}


void CCheckoutDlg::OnEnChangeEditotherpay()
{
	// TODO:  Add your control notification handler code here
	UpdateData(true);
	double extra = atof(m_extramoney);
	double discount = atof(m_discount);
	double totalDays = atof(m_realdays);
	double roommoney = atof(m_checkoutroommoney);
	double totalPay = roommoney*totalDays*discount/100 + extra;
	m_totalPay.Format("%f", totalPay);
	UpdateData(false);
}


void CCheckoutDlg::OnBnClickedButtonclear()
{
	// TODO: Add your control notification handler code here
	m_regnumber= _T("");
	m_checkoutbeizhu = _T("");
	m_roomlevel=_T("");
	m_prehandinmoney=_T("");
	m_realdays=_T("");
	m_name=_T("");
	m_extramoney=_T("");
	m_discount=_T("");
	m_totalPay=_T("");
	m_checkoutroommoney=_T("");
	m_roomnumber=_T("");
	m_showuser=_T("");
	m_checkoutzhenjian_number=_T("");
	m_telNum=_T("");
	UpdateData(false);
}


void CCheckoutDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	// TODO: Add extra validation here
	//store the record into the checkoutregtable
	UpdateData(true);
	if(m_extramoney=="") {
		MessageBox("请填写其他费用信息！", "客房管理系统");
		return;
	}

	m_pRecordsetout.CreateInstance(__uuidof(Recordset));
	//INSERT INTO checkinregtable (凭证号码)VALUES('%s')
	CString strsqlstore;

	try// 打开数据库
	{
		m_pRecordsetout->Open("SELECT * FROM checkouttable", // 查询 表中所有字段
			theApp.m_pConnection.GetInterfacePtr(),	 // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)// 捕获异常
	{
		AfxMessageBox(e->ErrorMessage());
	}

	try
	{       // 设置数据库操作类型
		m_pRecordsetout->AddNew();
		// // 往数据表中写入凭证号码字段数据
		m_pRecordsetout->PutCollect("凭证号码", _variant_t(m_checknumber));
		m_pRecordsetout->PutCollect("姓名", _variant_t(m_name));
		m_pRecordsetout->PutCollect("身份证号码", _variant_t(m_checkoutzhenjian_number));
		m_pRecordsetout->PutCollect("联系电话", _variant_t(m_telNum));
		m_pRecordsetout->PutCollect("房间号", _variant_t(m_roomnumber));
		m_pRecordsetout->PutCollect("客房类型", _variant_t(m_roomlevel));
		m_pRecordsetout->PutCollect("房间价格", _variant_t(m_checkoutroommoney));
		m_pRecordsetout->PutCollect("入住时间", _variant_t(checkinday));
		m_pRecordsetout->PutCollect("住宿天数", _variant_t(m_realdays));
		m_pRecordsetout->PutCollect("其他费用", _variant_t(m_extramoney));
		m_pRecordsetout->PutCollect("折扣", _variant_t(m_discount));
		m_pRecordsetout->PutCollect("应收宿费", _variant_t(m_totalPay));
		m_pRecordsetout->PutCollect("押金", _variant_t(m_prehandinmoney));
		m_pRecordsetout->PutCollect("备注", _variant_t(m_checkoutbeizhu));
		m_pRecordsetout->PutCollect("客房负责人", _variant_t(m_showuser));

		// 更新数据库
		m_pRecordsetout->Update();
		MessageBox("退宿完毕!","客房管理系统");
	}
	catch(_com_error *e)
	{//捕获异常
		AfxMessageBox(e->ErrorMessage());
	}
	m_pRecordsetout->Close();// 关闭记录集
	m_pRecordsetout = NULL;
	///////////////////////////////////////////////////////////////
	//update the roomsetting table
	CString SQLstr;
	SQLstr="SELECT * FROM roomsetting where 房间号='" ;
	SQLstr+=m_roomnumber;
	SQLstr+="'";
	if(!mymendroominfoset.Open(AFX_DB_USE_DEFAULT_TYPE,SQLstr))
	{//查询数据库得到数据集合
		MessageBox("打开roomsetting 表失败，更改房间状态失败!","客房管理系统");
		if(mymendroominfoset.IsOpen())
		{
			mymendroominfoset.Close();
		}
		return ;
	}

	mymendroominfoset.Edit();//设置数据库操作类型

	mymendroominfoset.column4="空房";
	mymendroominfoset.Update();// 更新数据库
	mymendroominfoset.Requery();
	///////////////////////////////////
	if(mymendroominfoset.IsOpen())
	{
		mymendroominfoset.Close();// 关闭数据集
	}
	CDialog::OnOK();
}
