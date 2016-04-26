// RoomsaleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomMng.h"
#include "RoomsaleDlg.h"
#include "afxdialogex.h"

extern CString loguserid;
/////////////////////////////////////////////////////////////////////////////
// CRoomsaleDlg dialog

IMPLEMENT_DYNAMIC(CRoomsaleDlg, CDialog)

	CRoomsaleDlg::CRoomsaleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRoomsaleDlg::IDD, pParent)
	, m_roomsaleenddate(0)
	, m_roomsalebegindate(0)
	, m_totalSum(0)
	, m_extraSum(0)
{

}

CRoomsaleDlg::~CRoomsaleDlg()
{
}

void CRoomsaleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_then, m_roomsaleenddate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_since, m_roomsalebegindate);
	DDX_Control(pDX, IDC_LIST1, m_roomsale_list);
	DDX_Text(pDX, IDC_STATIC_totalPay, m_totalSum);
	DDX_Text(pDX, IDC_STATIC_extraPay, m_extraSum);
}


BEGIN_MESSAGE_MAP(CRoomsaleDlg, CDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoomsaleDlg message handlers


BOOL CRoomsaleDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CTime tTime;
	tTime=tTime.GetCurrentTime(); 
	//设置默认时间
	m_roomsaleenddate=tTime;
	// TODO: Add extra initialization here
	//设置列表框颜色
	m_roomsale_list.SetTextColor(RGB (0, 0, 0));
	m_roomsale_list.SetTextBkColor(RGB (140, 180, 20));
	//初始化列表框
	m_roomsale_list.InsertColumn(1,"凭证号码");
	m_roomsale_list.InsertColumn(2,"姓名");
	m_roomsale_list.InsertColumn(3,"房间号");
	m_roomsale_list.InsertColumn(4,"房价");
	m_roomsale_list.InsertColumn(5,"天数");
	m_roomsale_list.InsertColumn(6,"折扣（%）");
	m_roomsale_list.InsertColumn(7,"其他额外费用");
	m_roomsale_list.InsertColumn(8,"总费费");

	RECT rect;
	m_roomsale_list.GetWindowRect(&rect);
	int wid=rect.right-rect.left;
	int i=0;
	m_roomsale_list.SetColumnWidth(0,wid/8);
	m_roomsale_list.SetColumnWidth(1,wid/8);
	m_roomsale_list.SetColumnWidth(2,wid/8);
	m_roomsale_list.SetColumnWidth(3,wid/8);
	m_roomsale_list.SetColumnWidth(4,wid/8);
	m_roomsale_list.SetColumnWidth(5,wid/8);
	m_roomsale_list.SetColumnWidth(6,wid/8);
	m_roomsale_list.SetColumnWidth(7,wid/8);

	//设置列表框风格
	m_roomsale_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	// 使用ADO创建数据库记录集
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	// 在ADO操作中建议语句中要常用try...catch()来捕获错误信息，
	try
	{//打开数据表
		m_pRecordset->Open("SELECT * FROM checkouttable",// 查询表中所有字段
			theApp.m_pConnection.GetInterfacePtr(),	 // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)
	{//抛出异常情况
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
		while(!m_pRecordset->adoEOF)
		{   //循环读取数据并打印到列表框中
			showinList(i);
			i++;
			m_pRecordset->MoveNext();//记录集指针下移一条记录
		}
	}
	catch(_com_error *e)//抛出异常情况，提示用户
	{
		AfxMessageBox(e->ErrorMessage());
	}
	// 关闭记录集
	m_pRecordset->Close();
	m_pRecordset = NULL;

	m_showuser=loguserid;
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CRoomsaleDlg::OnOK()
{
	// TODO: Add extra validation here
	UpdateData(true);
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	_variant_t var;
	m_roomsale_list.DeleteAllItems();
	int i=0;
	// 在ADO操作中建议语句中要常用try...catch()来捕获错误信息，
	try
	{//打开数据表
		m_pRecordset->Open("SELECT * FROM checkouttable",     // 查询表中所有字段
			theApp.m_pConnection.GetInterfacePtr(),	 // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)//抛出异常
	{
		AfxMessageBox(e->ErrorMessage());
	}
	try
	{//判断指针是否在数据集最后
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		else
		{
			MessageBox("表内数据为空","客房管理系统");
			return;
		}

		// read data from the database table 
		while(!m_pRecordset->adoEOF)
		{
			//循环读取数据
			var = m_pRecordset->GetCollect("入住时间");
			if(var.vt != VT_NULL)
				m_checkoutdate = (LPCSTR)_bstr_t(var);
			CString outyear,outmonth,outday;
			outyear=m_checkoutdate.Mid(0,4);
			outmonth=m_checkoutdate.Mid(5,m_checkoutdate.Find('-',6)-5);
			outday=m_checkoutdate.Mid(m_checkoutdate.ReverseFind('-')+1,m_checkoutdate.GetLength()-m_checkoutdate.ReverseFind('-'));
			//构造时间对象
			CTime outtime(atoi(outyear),atoi(outmonth),atoi(outday));
			//构造时间对象
			CTime begintime(m_roomsalebegindate.GetYear(),m_roomsalebegindate.GetMonth(),m_roomsalebegindate.GetDay());
			//构造时间对象
			CTime endtime(m_roomsaleenddate.GetYear(),m_roomsaleenddate.GetMonth(),m_roomsaleenddate.GetDay());

			if((outtime<endtime)&&(outtime>begintime))
			{   //满足条件的数据被读取，并在列表框内显示
				showinList(i);
				i++;//移动记录集指针到下一条记录
				m_pRecordset->MoveNext();
			}

			else//如果不满足条件就直接跳过此记录
			{
				m_pRecordset->MoveNext();
				continue;
			}
		}
	}
	catch(_com_error *e)//捕获异常
	{
		AfxMessageBox(e->ErrorMessage());
	}
	// 关闭记录集
	m_pRecordset->Close();
	m_pRecordset = NULL;


	//	m_show_pregetmoney = sum_pregetmoney;
	//	m_show_shouldgetmoney=sum_realmoney;
	UpdateData(false);
}


void CRoomsaleDlg::showinList(int i) {
	_variant_t var;
	//读取数据表中凭证号码字段数据
	var = m_pRecordset->GetCollect("凭证号码");
	if(var.vt != VT_NULL)
		m_regnumber = (LPCSTR)_bstr_t(var);
	m_roomsale_list.InsertItem(i,m_regnumber.GetBuffer(50));

	//读取数据表中姓名字段数据
	var = m_pRecordset->GetCollect("姓名");
	if(var.vt != VT_NULL)
		m_name = (LPCSTR)_bstr_t(var);
	m_roomsale_list.SetItemText(i,1,m_name.GetBuffer(50));

	//读取数据表中房间号字段数据
	var = m_pRecordset->GetCollect("房间号");
	if(var.vt != VT_NULL)
		m_roomnumber = (LPCSTR)_bstr_t(var);
	m_roomsale_list.SetItemText(i,2,m_roomnumber.GetBuffer(50));

	//读取数据表中客房价格字段数据
	var = m_pRecordset->GetCollect("房间价格");
	if(var.vt != VT_NULL)
		m_room_money = (LPCSTR)_bstr_t(var);
	m_roomsale_list.SetItemText(i,3,m_room_money.GetBuffer(50));

	//读取数据表中住宿天数字段数据
	var = m_pRecordset->GetCollect("住宿天数");
	if(var.vt != VT_NULL)
		m_realdays = (LPCSTR)_bstr_t(var);
	m_roomsale_list.SetItemText(i,4,m_realdays.GetBuffer(50));

	//读取数据表中折扣字段数据
	var = m_pRecordset->GetCollect("折扣");
	if(var.vt != VT_NULL)
		m_discount = (LPCSTR)_bstr_t(var);
	m_roomsale_list.SetItemText(i,5,m_discount.GetBuffer(50));

	var = m_pRecordset->GetCollect("其他费用");
	if(var.vt != VT_NULL)
		m_extramoney = (LPCSTR)_bstr_t(var);
	m_roomsale_list.SetItemText(i,6,m_extramoney.GetBuffer(50));

	var = m_pRecordset->GetCollect("应收宿费");
	if(var.vt != VT_NULL)
		m_totalPay = (LPCSTR)_bstr_t(var);
	m_roomsale_list.SetItemText(i,7,m_totalPay.GetBuffer(50));

	m_extraSum += atof(m_extramoney);
	m_totalSum = m_totalSum + m_extraSum + atof(m_totalPay);
}