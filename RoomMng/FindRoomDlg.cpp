// FindRoomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomMng.h"
#include "FindRoomDlg.h"
#include "afxdialogex.h"

/////////////////////////////////////////////////////////////////////////////
// CFindRoomDlg dialog

IMPLEMENT_DYNAMIC(CFindRoomDlg, CDialog)

	CFindRoomDlg::CFindRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindRoomDlg::IDD, pParent)
	, m_findroom_roomlevel(_T(""))
	, m_findroom_roommoney(_T(""))
	, m_findroom_status(_T(""))
	, m_findroom_roomsetting(_T(""))
	, m_findroom_roomnumber(_T(""))
	, m_findroomdlgroomnumber(_T(""))
{

}

CFindRoomDlg::~CFindRoomDlg()
{
}

void CFindRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_findroom_roomlevel, m_findroom_roomlevel);
	DDX_Text(pDX, IDC_findroom_roommoney, m_findroom_roommoney);
	DDX_Text(pDX, IDC_findroom_roomstate, m_findroom_status);
	DDX_Text(pDX, IDC_findroom_setting, m_findroom_roomsetting);
	DDX_Control(pDX, IDC_COMBO_findroomnum, m_findroomdlgroomnumberctr);
	DDX_CBString(pDX, IDC_COMBO_findroomnum, m_findroomdlgroomnumber);
	DDX_Control(pDX, IDC_LIST_findroom, m_findroom_list);
}


BEGIN_MESSAGE_MAP(CFindRoomDlg, CDialog)
	ON_CBN_CLOSEUP(IDC_COMBO_findroomnum, &CFindRoomDlg::OnCbnCloseupCombofindroomnum)
	ON_NOTIFY(NM_CLICK, IDC_LIST_findroom, &CFindRoomDlg::OnNMClickListfindroom)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindRoomDlg message handlers


BOOL CFindRoomDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	m_findroom_list.SetTextColor(RGB (0, 0, 0));
	m_findroom_list.SetTextBkColor(RGB (140, 180, 20));
	//设置列表框颜色完毕
	//初始化列表框
	m_findroom_list.InsertColumn(0,"房间号码");
	m_findroom_list.InsertColumn(1,"房间类型");
	m_findroom_list.InsertColumn(2,"价格");
	m_findroom_list.InsertColumn(3,"房态");
	m_findroom_list.InsertColumn(4,"设备配置");


	RECT rect;
	m_findroom_list.GetWindowRect(&rect);
	int wid=rect.right-rect.left;
	int i=0;
	m_findroom_list.SetColumnWidth(0,wid/6);
	m_findroom_list.SetColumnWidth(1,wid/6);
	m_findroom_list.SetColumnWidth(2,wid/6);
	m_findroom_list.SetColumnWidth(3,wid/6);
	m_findroom_list.SetColumnWidth(4,wid/3);

	//设置列表框风格
	m_findroom_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	///////////////////////////////////////////
	m_pRecordsetout.CreateInstance(__uuidof(Recordset));	
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	//m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pRecordsetdel.CreateInstance(__uuidof(Recordset));


	_variant_t var;
	// 在ADO操作中建议语句中要常用try...catch()来捕获错误信息，
	// 
	try//打开数据库
	{
		m_pRecordset->Open("SELECT * FROM roomsetting",                // 查询 表中所有字段
			theApp.m_pConnection.GetInterfacePtr(),	 // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)
	{//捕获可能出现的打开异常情况
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

		m_findroomdlgroomnumberctr.ResetContent();
		// read data from the database table 
		while(!m_pRecordset->adoEOF)
		{//循环读入数据，实时在列表框内显示
			//读取数据表内房间号字段数据
			var = m_pRecordset->GetCollect("房间号");
			if(var.vt != VT_NULL)
				findroom_roomnumber = (LPCSTR)_bstr_t(var);
			m_findroomdlgroomnumberctr.AddString(findroom_roomnumber);
			//在列表框内显示该字段的内容
			m_findroom_list.InsertItem(i,findroom_roomnumber.GetBuffer(50));
			//读取数据表内房间类型字段数据
			var = m_pRecordset->GetCollect("房间类型");
			if(var.vt != VT_NULL)
				findroom_roomlevel = (LPCSTR)_bstr_t(var);
			//在列表框内显示该字段的内容
			m_findroom_list.SetItemText(i,1,findroom_roomlevel.GetBuffer(50));
			//读取数据表内价格字段数据
			var = m_pRecordset->GetCollect("价格");
			if(var.vt != VT_NULL)
				findroom_roommoney = (LPCSTR)_bstr_t(var);
			//在列表框内显示该字段的内容
			m_findroom_list.SetItemText(i,2,findroom_roommoney.GetBuffer(50));
			//读取数据表内房态字段数据
			var = m_pRecordset->GetCollect("房态");
			if(var.vt != VT_NULL)
				findroom_roomstate = (LPCSTR)_bstr_t(var);
			//在列表框内显示该字段的内容
			m_findroom_list.SetItemText(i,3,findroom_roomstate.GetBuffer(50));
			//读取数据表内配置字段数据
			var = m_pRecordset->GetCollect("设备配置");
			if(var.vt != VT_NULL)
				findroom_roomsetting = (LPCSTR)_bstr_t(var);
			//在列表框内显示该字段的内容
			m_findroom_list.SetItemText(i,4,findroom_roomsetting.GetBuffer(50));

			i++;
			//移动记录指针
			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error *e)//捕获可能的读取数据异常情况
	{
		AfxMessageBox(e->ErrorMessage());
	}

	// 关闭记录集
	m_pRecordset->Close();
	//	m_pRecordset = NULL;

	//更新显示
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CFindRoomDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(true);
	if(m_findroomdlgroomnumber=="")
	{
		MessageBox("请先选择房间号！否则操作非法！","客房管理系统");
		return;
	}
	if(m_findroom_status=="" || m_findroom_roomlevel=="" || m_findroom_roommoney=="")
	{
		MessageBox("请点击列表栏选择房间，保证修改信息完整！", "客房管理系统");
		return;
	}

	//INSERT INTO checkinregtable (凭证号码)VALUES('%s')
	CString strsqlmend;
	strsqlmend.Format("SELECT * FROM roomsetting where 房间号='%s'",m_findroomdlgroomnumber);
	m_pRecordsetout->raw_Close();
	try
	{    //打开数据库
		m_pRecordsetout->Open(_variant_t(strsqlmend),                // 查询 表中所有字段
			theApp.m_pConnection.GetInterfacePtr(),	 // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)
	{//捕获可能的异常情况，实施提示用户
		AfxMessageBox(e->Description());
	}

	try
	{    //将变量数据写入数据库
		//将对应输入内容写入房间类型字段内
		m_pRecordsetout->PutCollect("房间类型", _variant_t(m_findroom_roomlevel));
		//将对应输入内容写入价格字段内
		m_pRecordsetout->PutCollect("价格", _variant_t(m_findroom_roommoney));
		//将对应输入内容写入房态字段内
		m_pRecordsetout->PutCollect("房态", _variant_t(m_findroom_status));
		//将对应输入内容写入使用设置字段内
		m_pRecordsetout->PutCollect("设备配置", _variant_t(m_findroom_roomsetting));

		m_pRecordsetout->Update();

		//完成更新数据库
		MessageBox("修改成功!","客房管理系统");
		//	UpdateData(false);
	}
	catch(_com_error *e)//捕获异常
	{
		AfxMessageBox(e->ErrorMessage());
	}

	CDialog::OnOK();
}


void CFindRoomDlg::OnCbnCloseupCombofindroomnum()
{
	// TODO: Add your control notification handler code here
	m_findroom_list.DeleteAllItems();
	_variant_t var;

	UpdateData(true);//读入变量对应的数据

	CString strsql;
	strsql.Format("SELECT * FROM roomsetting where 房间号='%s'",m_findroomdlgroomnumber);
	m_pRecordsetout->raw_Close();
	try
	{//打开数据库
		m_pRecordsetout->Open(_variant_t(strsql),                // 查询 表中所有字段
			theApp.m_pConnection.GetInterfacePtr(),	 // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)
	{//捕获异常
		AfxMessageBox(e->ErrorMessage());
	}

	int i=0;
	try
	{
		if(!m_pRecordsetout->BOF)//判断指针是否在数据集最后
			m_pRecordsetout->MoveFirst();
		else
		{
			MessageBox("表内数据为空","客房管理系统");
			return ;
		}
		//读取查询到的数据，并在列表框内显示
		//读取数据表内房间号字段数据
		var = m_pRecordsetout->GetCollect("房间号");
		if(var.vt != VT_NULL)
			findroom_roomnumber = (LPCSTR)_bstr_t(var);
		//在列表框内显示该字段的内容
		m_findroom_list.InsertItem(i,findroom_roomnumber.GetBuffer(50));

		//读取数据表内房间类型字段数据
		var = m_pRecordsetout->GetCollect("房间类型");
		if(var.vt != VT_NULL)
			findroom_roomlevel = (LPCSTR)_bstr_t(var);
		//在列表框内显示该字段的内容
		m_findroom_list.SetItemText(i,1,findroom_roomlevel.GetBuffer(50));
		//读取数据表内价格字段数据
		var = m_pRecordsetout->GetCollect("价格");
		if(var.vt != VT_NULL)
			findroom_roommoney = (LPCSTR)_bstr_t(var);
		//在列表框内显示该字段的内容
		m_findroom_list.SetItemText(i,2,findroom_roommoney.GetBuffer(50));
		//读取数据表内房态字段数据
		var = m_pRecordsetout->GetCollect("房态");
		if(var.vt != VT_NULL)
			findroom_roomstate = (LPCSTR)_bstr_t(var);
		//在列表框内显示该字段的内容
		m_findroom_list.SetItemText(i,3,findroom_roomstate.GetBuffer(50));
		//读取数据表内配置字段数据
		var = m_pRecordsetout->GetCollect("设备配置");
		if(var.vt != VT_NULL)
			findroom_roomsetting = (LPCSTR)_bstr_t(var);
		//在列表框内显示该字段的内容
		m_findroom_list.SetItemText(i,4,findroom_roomsetting.GetBuffer(50));

		//更新显示
		UpdateData(false);
	}
	catch(_com_error *e)//捕获异常
	{
		AfxMessageBox(e->ErrorMessage());
	}

	// 关闭记录集
	m_pRecordsetout->Close();
	//	m_pRecordsetout = NULL;
	//更新显示
	UpdateData(false);
}


void CFindRoomDlg::OnNMClickListfindroom(NMHDR *pNMHDR, LRESULT *pResult)
{
	int i = m_findroom_list.GetSelectionMark();
	//将选定的项目的对应内容显示在对应的输入框内，以便修改
	m_findroom_roomlevel = m_findroom_list.GetItemText(i,1);
	m_findroom_roommoney = m_findroom_list.GetItemText(i,2);
	m_findroom_status=m_findroom_list.GetItemText(i,3);
	m_findroom_roomsetting =m_findroom_list.GetItemText(i,4);

	UpdateData(FALSE);//更新显示
	*pResult = 0;
}
