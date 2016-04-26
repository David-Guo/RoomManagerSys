// CheckinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomMng.h"
#include "CheckinDlg.h"
#include "afxdialogex.h"

extern CString loguserid;
extern CRoomMngApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CheckinDlg dialog

IMPLEMENT_DYNAMIC(CheckinDlg, CDialog)

	CheckinDlg::CheckinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CheckinDlg::IDD, pParent)
	, m_zhengjian_number(_T(""))
	, m_beizhu(_T(""))
	, m_gustname(_T(""))
	, m_regnumber(_T(""))
	, m_pre_discount(100)
	, m_telNumber(_T(""))
	, m_pre_handinmoney(_T(""))
	//, m_room_money(_T(""))
	, m_realmoney(_T(""))
	, m_roomnumber(_T(""))
	, m_checkdays(0)
	, m_roomlevel(_T(""))
	, m_checkindate(0)
	, m_showuser(_T(""))
{

}

CheckinDlg::~CheckinDlg()
{
}

void CheckinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_custId, m_zhengjian_number);
	DDX_Text(pDX, IDC_EDIT_log, m_beizhu);
	DDX_Text(pDX, IDC_EDIT_name, m_gustname);
	DDX_Text(pDX, IDC_EDIT_NO, m_regnumber);
	DDX_Text(pDX, IDC_EDIT_discount, m_pre_discount);
	DDX_Text(pDX, IDC_EDIT_telNum, m_telNumber);
	DDX_Text(pDX, IDC_EDIT_roomMny, m_room_money);
	//DDX_Control(pDX, IDC_EDIT_roomMny, m_room_money);
	DDX_Text(pDX, IDC_EDIT_prePay, m_pre_handinmoney);
	DDX_Text(pDX, IDC_EDIT_shouldPay, m_realmoney);
	DDX_CBString(pDX, IDC_COMBO_roomnumber, m_roomnumber);
	DDX_Text(pDX, IDC_EDIT_bookDays, m_checkdays);
	DDX_Text(pDX, IDC_EDIT_room_level, m_roomlevel);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_checkindatectr);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_checkindate);
	DDX_Text(pDX, IDC_STATICshowuser, m_showuser);
}


BEGIN_MESSAGE_MAP(CheckinDlg, CDialog)
	ON_BN_CLICKED(IDC_checkreg, &CheckinDlg::OnBnClickedcheckreg)
	ON_CBN_SELCHANGE(IDC_COMBO_roomnumber, &CheckinDlg::OnCbnSelchangeComboroomnumber)
	ON_EN_CHANGE(IDC_EDIT_discount, &CheckinDlg::OnEnChangeEditdiscount)
	ON_EN_CHANGE(IDC_EDIT_bookDays, &CheckinDlg::OnEnChangeEditbookdays)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CheckinDlg message handlers

void CheckinDlg::enable(bool bEnabled)
{
	// m_ComYSFS.EnableWindow(bEnabled);
	//更改输入框等控件状态，方便使用，防止错误操作
	GetDlgItem(IDC_EDIT_custId)->EnableWindow(bEnabled);
	GetDlgItem(IDC_EDIT_log)->EnableWindow(bEnabled);
	GetDlgItem(IDC_EDIT_name)->EnableWindow(bEnabled);
	GetDlgItem(IDC_EDIT_NO)->EnableWindow(bEnabled);
	GetDlgItem(IDC_EDIT_discount)->EnableWindow(bEnabled);
	GetDlgItem(IDC_EDIT_telNum)->EnableWindow(bEnabled);
	GetDlgItem(IDC_EDIT_roomMny)->EnableWindow(bEnabled);
	GetDlgItem(IDC_EDIT_prePay)->EnableWindow(bEnabled);
	GetDlgItem(IDC_EDIT_shouldPay)->EnableWindow(bEnabled);
	GetDlgItem(IDC_COMBO_roomnumber)->EnableWindow(bEnabled);
	GetDlgItem(IDC_EDIT_bookDays)->EnableWindow(bEnabled);
	GetDlgItem(IDC_EDIT_room_level)->EnableWindow(bEnabled);
	GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(bEnabled);
	GetDlgItem(IDOK)->EnableWindow(bEnabled);
}


BOOL CheckinDlg::OnInitDialog()
{

	CDialog::OnInitDialog();


	// TODO: Add extra initialization here
	enable(0);//
	//更新输入框状态
	CString sYear,sDay,sMonth,stime;
	CTime tTime;
	tTime=tTime.GetCurrentTime(); 
	//设置登记的默认时间
	m_checkindate=tTime;

	m_showuser=loguserid;

	//显示初始化信息
	UpdateData(false);

	m_pRecordset.CreateInstance(__uuidof(Recordset));

	_variant_t var, var1;
	CString strroomnumber;
	// 在ADO操作中建议语句中要常用try...catch()来捕获错误信息，
	// 
	try
	{
		m_pRecordset->Open("SELECT * FROM roomsetting",              // 查询 表中所有字段
			theApp.m_pConnection.GetInterfacePtr(),	 // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)//捕获连接数据库异常
	{
		AfxMessageBox(e->ErrorMessage());
	}
	try
	{
		if(!m_pRecordset->BOF)//判断指针是否在数据集最后
			m_pRecordset->MoveFirst();
		else
		{
			AfxMessageBox("表内数据为空");
			return false;
		}

		// read data from the database table 

		CComboBox* combobox = (CComboBox*)GetDlgItem(IDC_COMBO_roomnumber);
		while(!m_pRecordset->adoEOF)
		{//读取房间号
			var = m_pRecordset->GetCollect("房间号");
			var1 = m_pRecordset->GetCollect("房态");
			CString cmp = (LPCSTR)_bstr_t(var1);
			if(var.vt != VT_NULL)
				strroomnumber = (LPCSTR)_bstr_t(var);
			if(cmp == "空闲")
				combobox->AddString(strroomnumber);//添加到列表

			m_pRecordset->MoveNext();//移动记录集指针
		}
	}
	catch(_com_error *e)//捕获异常
	{
		AfxMessageBox(e->ErrorMessage());
	}

	// 关闭记录集
	m_pRecordset->Close();
	m_pRecordset = NULL;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CheckinDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	// TODO: 下面的变量是方便 debug 时使用的
	//m_zhengjian_number = "123456789123456";
	//m_gustname = "gdw";
	//m_pre_discount = 100;
	//m_room_money = "118";
	//m_pre_handinmoney = "118";
	//m_realmoney = "118";
	//m_roomnumber = "001";
	//m_checkdays = 1;
	//m_roomlevel = "标准";
	UpdateData(true);
	//////////////////////////////////////////////////////////////////////////
	/*
	*	检查身份证的号码是否为15位或者为18位
	*/
	CString strCertifyCode;//证件号码


	//获得证件号码
	int nCertifyCodeLength=m_zhengjian_number.GetLength();//获得证件的长度
	if(nCertifyCodeLength!=15&&nCertifyCodeLength!=18)
	{
		MessageBox("你的身份证的号码的位数不正确!\n应该为15位或者18位!",
			"身份证错误",MB_OK);
		return ;
	}
	//////////////////////////////////////////////////////////////////////////
	// 更新房间状态为已有人入住
	CString SQLstr;
	SQLstr="SELECT * FROM roomsetting where 房间号='" ;
	SQLstr+=m_roomnumber;
	SQLstr+="'";
	myroominfoset.Open(AFX_DB_USE_DEFAULT_TYPE,SQLstr);
	myroominfoset.Edit();
	myroominfoset.column4="入住";
	myroominfoset.Update();
	myroominfoset.Requery();
	if(myroominfoset.IsOpen())
	{//关闭数据表
		myroominfoset.Close();
	}

	m_pRecordset.CreateInstance(__uuidof(Recordset));

	// 在ADO操作中建议语句中要常用try...catch()来捕获错误信息，
	// 
	try
	{//打开数据库
		m_pRecordset->Open("SELECT * FROM checkintable",                // 查询表中所有字段
			theApp.m_pConnection.GetInterfacePtr(),	 // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)//捕获打开数据库时候的各种异常
	{
		AfxMessageBox(e->ErrorMessage());
	}
	//////////////////////////////////////////////////////////////

	try
	{
		// 写入各字段值，准备更新数据库
		m_pRecordset->AddNew();
		m_pRecordset->PutCollect("凭证号码", _variant_t(m_regnumber));
		m_pRecordset->PutCollect("姓名",_variant_t(m_gustname));
		m_pRecordset->PutCollect("身份证号码", _variant_t(m_zhengjian_number));
		m_pRecordset->PutCollect("联系电话", _variant_t(m_telNumber));
		m_pRecordset->PutCollect("房间号", _variant_t(m_roomnumber));
		m_pRecordset->PutCollect("客房类型", _variant_t(m_roomlevel));

		//CString str_room_money;
		//m_room_money.GetWindowText(str_room_money);
		m_pRecordset->PutCollect("房间价格", _variant_t(m_room_money));//str_room_money));

		CString checkindate;//获取登记住宿日期
		int nYear,nDay,nMonth;
		CString sYear,sDay,sMonth;
		nYear=m_checkindate.GetYear();//提取年份
		nDay=m_checkindate.GetDay();//提取日
		nMonth=m_checkindate.GetMonth();//提取月份
		sYear.Format("%d",nYear);//转换为字符串
		sDay.Format("%d",nDay);//转换为字符串
		sMonth.Format("%d",nMonth);//转换为字符串
		checkindate.Format("%s-%s-%s",sYear,sMonth,sDay);//格式化时间
		m_pRecordset->PutCollect("入住时间",_variant_t(checkindate));
		//保存
		m_pRecordset->PutCollect("住宿天数", _variant_t(m_checkdays));
		//定义临时存储空间
		char str_money[50]; 
		//_gcvt(atof(str_room_money)*m_checkdays, 4, str_money );
		_gcvt_s(str_money, 50, atof(m_room_money)*m_checkdays, 4);
		m_pRecordset->PutCollect("宿费", _variant_t(str_money));


		m_pRecordset->PutCollect("折扣",_variant_t(m_pre_discount));
		// 定义临时存储空间
		char strhand_money[50];
		_gcvt_s(strhand_money, 50, atof(m_realmoney)*m_pre_discount/100, 4);
		//_gcvt(atof(m_realmoney)*m_pre_discount/100, 4, strhand_money );
		m_pRecordset->PutCollect("应收宿费", _variant_t(strhand_money));
		m_pRecordset->PutCollect("押金", _variant_t(m_pre_handinmoney));
		m_pRecordset->PutCollect("备注", _variant_t(m_beizhu));
		m_pRecordset->PutCollect("客房负责人", _variant_t(m_showuser));

		m_pRecordset->Update();
		MessageBox("登记成功!","客房管理系统");
	}
	catch(_com_error *e)//捕获写入数据库时候可能发生的异常情况
	{
		AfxMessageBox(e->ErrorMessage());
	}
	///////////////////////////////////////////////////
	//关闭记录集
	m_pRecordset->Close();
	m_pRecordset = NULL;

	//	CDialog::OnOK();
}


void CheckinDlg::OnBnClickedcheckreg()
{
	// TODO: Add your control notification handler code here
	enable(1);

	CString strnowdate,strcheckinnumber;

	int nYear,nDay,nMonth;
	CString sYear,sDay,sMonth;
	CTime tTime;
	tTime=tTime.GetCurrentTime(); //获取系统当前的时间
	nYear=tTime.GetYear();//提取年份
	nDay=tTime.GetDay();//提取月份
	nMonth=tTime.GetMonth();//提取日
	sYear.Format("%d",nYear);//转换为字符串
	sDay.Format("%d",nDay);//转换为字符串
	sMonth.Format("%d",nMonth);//转换为字符串，格式化时间
	strnowdate.Format("%s-%s-%s",sYear,sMonth,sDay);


	// 使用ADO创建数据库记录集
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	// 在ADO操作中建议语句中要常用try...catch()来捕获错误信息，
	// 
	CString strsql;
	strsql.Format("SELECT * FROM checkintable where 入住时间='%s'",strnowdate);
	try//打开数据库
	{
		m_pRecordset->Open(_variant_t(strsql),                // 查询表中所有字段
			theApp.m_pConnection.GetInterfacePtr(),	 // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)//捕获打开数据库时候可能发生的异常情况
	{
		AfxMessageBox(e->ErrorMessage());
	}
	strcheckinnumber+=strnowdate;
	strcheckinnumber+="D";
	int num = 0;
	while (!m_pRecordset->adoEOF) {
		num++;
		m_pRecordset->MoveNext();
	}
	strcheckinnumber+=(LPCSTR)_bstr_t(num + 1);
	//产生登记凭证号码
	m_regnumber =strcheckinnumber;

	// 关闭记录集
	m_pRecordset->Close();
	m_pRecordset = NULL;
	//更新显示
	UpdateData(false);
}


void CheckinDlg::OnCbnSelchangeComboroomnumber()
{
	// TODO: Add your control notification handler code here
	int index = ((CComboBox*)GetDlgItem(IDC_COMBO_roomnumber))->GetCurSel(); //获得想要的索引值  
	((CComboBox*)GetDlgItem(IDC_COMBO_roomnumber))->SetCurSel(index); //设置成想要索引值的值  
	UpdateData(true); //来获取关联变量，即改变后的值

	try
	{
		//获得选择的列表项目内容
		CString SQLstr;
		SQLstr="SELECT * FROM roomsetting where 房间号='";
		SQLstr+=m_roomnumber;
		SQLstr+="'";
		if(!myroominfoset.Open(AFX_DB_USE_DEFAULT_TYPE,SQLstr))
		{//查询数据库得到数据集合
			MessageBox("没有此房间号码，打开数据库失败!","客房管理系统");
			if(myroominfoset.IsOpen())
			{//关闭数据表
				myroominfoset.Close();
			}
			return ;
		}
		m_roomlevel=myroominfoset.column2;//读取房间类型
		roommoney = myroominfoset.column3;
		m_room_money.Format("%f", roommoney);//读取房间价格
	}
	catch(_com_error *e)//捕获异常
	{
		AfxMessageBox(e->ErrorMessage());
	}

	if(myroominfoset.IsOpen())
	{//关闭数据表
		myroominfoset.Close();
	}
	UpdateData(false);
}


void CheckinDlg::OnEnChangeEditdiscount()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(true);
	CString need_room_money;

	double fneed_room_money=0;//初始化

	fneed_room_money=m_pre_discount*roommoney*m_checkdays/100;

	m_realmoney.Format("%f", fneed_room_money);
	//更新显示
	UpdateData(false);
	// TODO:  Add your control notification handler code here
}


void CheckinDlg::OnEnChangeEditbookdays()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(true);
	CString need_room_money;

	double fneed_room_money=0;//初始化

	fneed_room_money=m_pre_discount*roommoney*m_checkdays/100;

	m_realmoney.Format("%f", fneed_room_money);
	//更新显示
	UpdateData(false);
	// TODO:  Add your control notification handler code here
}
