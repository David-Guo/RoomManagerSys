// Setroomdlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomMng.h"
#include "Setroomdlg.h"
#include "afxdialogex.h"

extern CRoomMngApp theApp; 
/////////////////////////////////////////////////////////////////////////////
// CSetroomdlg dialog

IMPLEMENT_DYNAMIC(CSetroomdlg, CDialog)

CSetroomdlg::CSetroomdlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetroomdlg::IDD, pParent)
	, m_roomlevel(_T(""))
	, m_roomstate(_T(""))
	, m_roomset(_T(""))
	, m_roommoney(_T(""))
	, m_roomnumber(_T(""))
{

}

CSetroomdlg::~CSetroomdlg()
{
}

void CSetroomdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_roomlevel, m_roomlevel);
	DDX_CBString(pDX, IDC_COMBO_roomstate, m_roomstate);
	DDX_Control(pDX, IDC_LIST_setroomdlg, m_setroomdlg_list);
	DDX_Text(pDX, IDC_roomConfig, m_roomset);
	DDX_Text(pDX, IDC_roomMoney, m_roommoney);
	DDX_Text(pDX, IDC_roomnumber, m_roomnumber);
}


BEGIN_MESSAGE_MAP(CSetroomdlg, CDialog)
	ON_BN_CLICKED(IDC_clearSet, &CSetroomdlg::OnBnClickedclearset)
	ON_BN_CLICKED(IDC_beginsetroom, &CSetroomdlg::OnBnClickedbeginsetroom)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetroomdlg message handlers


void CSetroomdlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	UpdateData(true);
	//CString strSQL, usetime;
	//	usetime.Format("%d-%d-%d",m_room_usetime.GetYear(),m_room_usetime.GetMonth(),m_room_usetime.GetDay());

	//int nYear,nDay,nMonth;
	//CString sYear,sDay,sMonth;
	//	CTime tTime;
	// 	tTime=tTime.GetCurrentTime(); 
	//nYear=m_room_usetime.GetYear();//提取年份
	//nDay=m_room_usetime.GetDay();//提取日
	//nMonth=m_room_usetime.GetMonth();//提取月份
	//sYear.Format("%d",nYear);//转换为字符串
	//sDay.Format("%d",nDay);//转换为字符串
	//sMonth.Format("%d",nMonth);//转换为字符串
	//格式化时间对象
	//usetime.Format("%s-%s-%s",sYear,sMonth,sDay);
	if (m_roomlevel == _T("") && m_roomnumber == _T("") && m_roommoney == _T("")) {
		MessageBox("请填写完整房间信息！", "客房管理系统");
		return;
	}
    m_pRecordset1.CreateInstance(__uuidof(Recordset));
    CString strsql;
	strsql.Format("SELECT * FROM roomsetting where 房间号='%s'",m_roomnumber);
    try//打开数据库
	{
		m_pRecordset1->Open(_variant_t(strsql),                // 查询表中所有字段
			theApp.m_pConnection.GetInterfacePtr(),	 // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)//捕获打开数据库时候可能发生的异常情况
	{
		AfxMessageBox(e->ErrorMessage());
	}
    if (!m_pRecordset1->adoEOF) {
        MessageBox("此房间号已存在！", "客房管理系统");
        return;
    }
	try
	{
		// 写入各字段值
		m_pRecordset->AddNew();
		m_pRecordset->PutCollect("房间号", _variant_t(m_roomnumber));
		m_pRecordset->PutCollect("房间类型",_variant_t(m_roomlevel));
		m_pRecordset->PutCollect("价格", _variant_t(m_roommoney));
		m_pRecordset->PutCollect("房态", _variant_t(m_roomstate));
		m_pRecordset->PutCollect("设备配置", _variant_t(m_roomset));
		//m_pRecordset->PutCollect("营业日期", _variant_t(usetime));
		m_pRecordset->Update();
		//更新数据库完毕
		MessageBox("设置成功!","客房管理系统");
	}
	catch(_com_error *e)//捕获可能发生的异常
	{
		AfxMessageBox(e->ErrorMessage());
	}
}


BOOL CSetroomdlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	enable(0);
	/////////////////////////////////////
	// 设置列表框颜色
	m_setroomdlg_list.SetTextColor(RGB (0, 0, 0));
	m_setroomdlg_list.SetTextBkColor(RGB (140, 180, 20));
	// 列表框初始化
	m_setroomdlg_list.InsertColumn(0,"房间号码");
	m_setroomdlg_list.InsertColumn(1,"房间类型");
	m_setroomdlg_list.InsertColumn(2,"价格");
	m_setroomdlg_list.InsertColumn(3,"房态");
	m_setroomdlg_list.InsertColumn(4,"设备配置");

	RECT rect;
	m_setroomdlg_list.GetWindowRect(&rect);
	int wid=rect.right-rect.left;
	int i=0;
	m_setroomdlg_list.SetColumnWidth(0,wid/6);
	m_setroomdlg_list.SetColumnWidth(1,wid/6);
	m_setroomdlg_list.SetColumnWidth(2,wid/6);
	m_setroomdlg_list.SetColumnWidth(3,wid/6);
	m_setroomdlg_list.SetColumnWidth(4,wid/3);


	//设置列表框风格
	m_setroomdlg_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	///////////////////////////////////////////

	m_pRecordset.CreateInstance(__uuidof(Recordset));

	_variant_t var;
	// 在ADO操作中建议语句中要常用try...catch()来捕获错误信息，
	// 
	try
	{//打开数据表
		m_pRecordset->Open("SELECT * FROM roomsetting",                // 查询表中所有字段
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
			return false;
		}

		// read data from the database table 
		while(!m_pRecordset->adoEOF)
		{//循环读取数据，并在列表框内显示
			//读取数据表中房间号对应字段的值
			var = m_pRecordset->GetCollect("房间号");
			if(var.vt != VT_NULL)
				showroom_roomnumber = (LPCSTR)_bstr_t(var);
			//在列表框内显示该字段的内容
			m_setroomdlg_list.InsertItem(i,showroom_roomnumber.GetBuffer(50));
			//读取数据表中房间类型对应字段的值
			var = m_pRecordset->GetCollect("房间类型");
			if(var.vt != VT_NULL)
				showroom_roomlevel = (LPCSTR)_bstr_t(var);
			//在列表框内显示该字段的内容
			m_setroomdlg_list.SetItemText(i,1,showroom_roomlevel.GetBuffer(50));
			//读取数据表中价格对应字段的值
			var = m_pRecordset->GetCollect("价格");
			if(var.vt != VT_NULL)
				showroom_roommoney = (LPCSTR)_bstr_t(var);
			//在列表框内显示该字段的内容
			m_setroomdlg_list.SetItemText(i,2,showroom_roommoney.GetBuffer(50));
			//读取数据表中房态对应字段的值
			var = m_pRecordset->GetCollect("房态");
			if(var.vt != VT_NULL)
				showroom_roomstate = (LPCSTR)_bstr_t(var);
			//在列表框内显示该字段的内容
			m_setroomdlg_list.SetItemText(i,3,showroom_roomstate.GetBuffer(50));

			//读取数据表中配置对应字段的值
			var = m_pRecordset->GetCollect("设备配置");
			if(var.vt != VT_NULL)
				showroom_roomsetting = (LPCSTR)_bstr_t(var);
			//在列表框内显示该字段的内容
			m_setroomdlg_list.SetItemText(i,4,showroom_roomsetting.GetBuffer(50));

			i++;
			//移动记录集指针到下一条记录
			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error *e)//捕获可能发生的异常
	{
		AfxMessageBox(e->ErrorMessage());
	}

	//更新显示
	UpdateData(false);
}


void CSetroomdlg::enable(bool bEnabled)
{
	// m_ComYSFS.EnableWindow(bEnabled);
	//改变各个控件的状态
	GetDlgItem(IDC_roomnumber)->EnableWindow(bEnabled);
	GetDlgItem(IDC_roomConfig)->EnableWindow(bEnabled);
	GetDlgItem(IDC_roomMoney)->EnableWindow(bEnabled);
	GetDlgItem(IDC_COMBO_roomlevel)->EnableWindow(bEnabled);
	GetDlgItem(IDC_COMBO_roomstate)->EnableWindow(bEnabled);

	GetDlgItem(IDOK)->EnableWindow(bEnabled);
}


void CSetroomdlg::OnBnClickedclearset()
{
	// TODO: Add your control notification handler code here
	//变量初始化
	m_roomnumber = _T("");
	m_roomset = _T("");
	m_roommoney = _T("");
	m_roomlevel = _T("");
	m_roomstate = _T("");
	//更新显示
	UpdateData(false);
}


void CSetroomdlg::OnBnClickedbeginsetroom()
{
	// TODO: Add your control notification handler code here
	enable(1);
}
