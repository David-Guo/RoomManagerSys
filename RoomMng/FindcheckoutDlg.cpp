// FindcheckoutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomMng.h"
#include "FindcheckoutDlg.h"
#include "afxdialogex.h"

/////////////////////////////////////////////////////////////////////////////
// CFindcheckoutDlg dialog

IMPLEMENT_DYNAMIC(CFindcheckoutDlg, CDialog)

	CFindcheckoutDlg::CFindcheckoutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindcheckoutDlg::IDD, pParent)
	, m_findcheckout_name(_T(""))
{

}

CFindcheckoutDlg::~CFindcheckoutDlg()
{
}

void CFindcheckoutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_findcheckout_name, m_findcheckout_name);
	DDX_Control(pDX, IDC_LIST1, m_findcheckout_list);
}


BEGIN_MESSAGE_MAP(CFindcheckoutDlg, CDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindcheckoutDlg message handlers


BOOL CFindcheckoutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	//�����б����ɫ
	m_findcheckout_list.SetTextColor(RGB (0, 0, 0));
	m_findcheckout_list.SetTextBkColor(RGB (140, 180, 20));
	//��ʼ���б������
	m_findcheckout_list.InsertColumn(0,"ƾ֤����");
	m_findcheckout_list.InsertColumn(1,"����");
	m_findcheckout_list.InsertColumn(2,"���֤����");
	m_findcheckout_list.InsertColumn(3,"��ϵ�绰");
	m_findcheckout_list.InsertColumn(4,"�����");
	m_findcheckout_list.InsertColumn(5,"��������");
	m_findcheckout_list.InsertColumn(6,"�ͷ��۸�");
	m_findcheckout_list.InsertColumn(7,"��סʱ��");
	m_findcheckout_list.InsertColumn(8,"ס������");
	m_findcheckout_list.InsertColumn(9,"��������");
	m_findcheckout_list.InsertColumn(10,"�ۿ�");
	m_findcheckout_list.InsertColumn(11,"Ӧ���޷�");
	m_findcheckout_list.InsertColumn(12,"Ѻ��");
	m_findcheckout_list.InsertColumn(13,"��ע");

	RECT rect;
	m_findcheckout_list.GetWindowRect(&rect);
	int wid=rect.right-rect.left;
	m_findcheckout_list.SetColumnWidth(0,wid/9);
	m_findcheckout_list.SetColumnWidth(1,wid/9);
	m_findcheckout_list.SetColumnWidth(2,wid/9);
	m_findcheckout_list.SetColumnWidth(3,wid/9);
	m_findcheckout_list.SetColumnWidth(4,wid/9);
	m_findcheckout_list.SetColumnWidth(5,wid/9);
	m_findcheckout_list.SetColumnWidth(6,wid/9);
	m_findcheckout_list.SetColumnWidth(7,wid/9);
	m_findcheckout_list.SetColumnWidth(8,wid/9);
	m_findcheckout_list.SetColumnWidth(9,wid/9);
	m_findcheckout_list.SetColumnWidth(10,wid/9);
	m_findcheckout_list.SetColumnWidth(11,wid/9);
	m_findcheckout_list.SetColumnWidth(12,wid/9);
	m_findcheckout_list.SetColumnWidth(13,wid/9);

	//��ʼ���б���������
	m_findcheckout_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	// ʹ��ADO�������ݿ��¼��
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	// ��ADO�����н��������Ҫ����try...catch()�����������Ϣ��
	try
	{   //�����ݿ�
		m_pRecordset->Open("SELECT * FROM checkouttable",    // ��ѯ ���������ֶ�
			theApp.m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)//��������ݿ�ʱ����ܷ������쳣�����ʵʱ��ʾ
	{
		AfxMessageBox(e->ErrorMessage());
	}

	if(!m_pRecordset->BOF)//�ж�ָ���Ƿ������ݼ����
		m_pRecordset->MoveFirst();
	else
	{
		AfxMessageBox("��������Ϊ�գ�");
		return false;
	}
	// �����ݿ��ж�ȡ���ݲ�չ�ֵ� List ��
	showinList();	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CFindcheckoutDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(true);

	// ʹ��ADO�������ݿ��¼��
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	// ��ADO�����н��������Ҫ����try...catch()�����������Ϣ
	m_findcheckout_list.DeleteAllItems();
	CString strsqlfind;
	strsqlfind.Format("SELECT * FROM checkouttable where ����='%s'",m_findcheckout_name);
	try
	{//�����ݿ�
		m_pRecordset->Open((_variant_t)(strsqlfind),                // ��ѯ ���������ֶ�
			theApp.m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)//��������ݿ�ʱ����쳣
	{
		AfxMessageBox(e->ErrorMessage());
	}

	if(!m_pRecordset->BOF)//�ж�ָ���Ƿ������ݼ����
		m_pRecordset->MoveFirst();
	else
	{
		AfxMessageBox("û�иü�¼��");
		return;
	}

	// �����ݿ��ж�ȡ���ݲ�չ�ֵ� List ��
	showinList();
	//CDialog::OnOK();
}


void CFindcheckoutDlg::showinList() {
	try
	{
		_variant_t var;
		int i=0;
		// read data from the database table 
		while(!m_pRecordset->adoEOF)
		{//ѭ����ȡ���ݣ����б������ʾ
			var = m_pRecordset->GetCollect("ƾ֤����");
			if(var.vt != VT_NULL)
				m_regnumber = (LPCSTR)_bstr_t(var);
			//���б������ʾ
			m_findcheckout_list.InsertItem(i,m_regnumber.GetBuffer(50));
			//��ȡ���ݱ��������ֶ�����
			var = m_pRecordset->GetCollect("����");
			if(var.vt != VT_NULL)
				m_gustname = (LPCSTR)_bstr_t(var);
			//���б������ʾ
			m_findcheckout_list.SetItemText(i,1,m_gustname.GetBuffer(50));
			//��ȡ���ݱ���֤�������ֶ�����
			var = m_pRecordset->GetCollect("���֤����");
			if(var.vt != VT_NULL)
				m_zhengjian_number = (LPCSTR)_bstr_t(var);
			//���б������ʾ
			m_findcheckout_list.SetItemText(i,2,m_zhengjian_number.GetBuffer(50));
			//��ȡ���ݱ��г��������ֶ�����
			var = m_pRecordset->GetCollect("��ϵ�绰");
			if(var.vt != VT_NULL)
				m_telNumber = (LPCSTR)_bstr_t(var);
			//���б������ʾ
			m_findcheckout_list.SetItemText(i,3,m_telNumber.GetBuffer(50));
			//��ȡ���ݱ��з�����ֶ�����
			var = m_pRecordset->GetCollect("�����");
			if(var.vt != VT_NULL)
				m_roomnumber = (LPCSTR)_bstr_t(var);
			//���б������ʾ
			m_findcheckout_list.SetItemText(i,4,m_roomnumber.GetBuffer(50));
			//��ȡ���ݱ��пͷ������ֶ�����
			var = m_pRecordset->GetCollect("�ͷ�����");
			if(var.vt != VT_NULL)
				m_roomlevel = (LPCSTR)_bstr_t(var);
			//���б������ʾ
			m_findcheckout_list.SetItemText(i,5,m_roomlevel.GetBuffer(50));
			//��ȡ���ݱ��пͷ��۸��ֶ�����
			var = m_pRecordset->GetCollect("����۸�");
			if(var.vt != VT_NULL)
				m_room_money = (LPCSTR)_bstr_t(var);
			//���б������ʾ
			m_findcheckout_list.SetItemText(i,6,m_room_money.GetBuffer(50));
			//��ȡ���ݱ���ס�������ֶ�����
			var = m_pRecordset->GetCollect("��סʱ��");
			if(var.vt != VT_NULL)
				m_checkindate = (LPCSTR)_bstr_t(var);
			//���б������ʾ
			m_findcheckout_list.SetItemText(i,7,m_checkindate.GetBuffer(50));
			//��ȡ���ݱ���ס�������ֶ�����
			var = m_pRecordset->GetCollect("ס������");
			if(var.vt != VT_NULL)
				m_checkdays = (LPCSTR)_bstr_t(var);
			//���б������ʾ
			m_findcheckout_list.SetItemText(i,8,m_checkdays.GetBuffer(50));
			//��ȡ���ݱ����޷��ֶ�����
			var = m_pRecordset->GetCollect("��������");
			if(var.vt != VT_NULL)
				m_pre_discount = (LPCSTR)_bstr_t(var);
			//���б������ʾ
			m_findcheckout_list.SetItemText(i,9,m_pre_discount.GetBuffer(50));
			//��ȡ���ݱ����ۿ��ֶ�����
			var = m_pRecordset->GetCollect("�ۿ�");
			if(var.vt != VT_NULL)
				m_pre_discount = (LPCSTR)_bstr_t(var);
			//���б������ʾ
			m_findcheckout_list.SetItemText(i,10,m_pre_discount.GetBuffer(50));
			//��ȡ���ݱ���Ӧ���޷��ֶ�����
			var = m_pRecordset->GetCollect("Ӧ���޷�");
			if(var.vt != VT_NULL)
				m_realmoney = (LPCSTR)_bstr_t(var);
			//���б������ʾ
			m_findcheckout_list.SetItemText(i,11,m_realmoney.GetBuffer(50));
			//��ȡ���ݱ���Ѻ���ֶ�����
			var = m_pRecordset->GetCollect("Ѻ��");
			if(var.vt != VT_NULL)
				m_pre_handinmoney = (LPCSTR)_bstr_t(var);
			//���б������ʾ
			m_findcheckout_list.SetItemText(i,12,m_pre_handinmoney.GetBuffer(50));
			//��ȡ���ݱ��б�ע�ֶ�����
			var = m_pRecordset->GetCollect("��ע");
			if(var.vt != VT_NULL)
				m_beizhu = (LPCSTR)_bstr_t(var);
			//���б������ʾ
			m_findcheckout_list.SetItemText(i,13,m_beizhu.GetBuffer(50));
			i++;
			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error *e)//�����쳣
	{
		AfxMessageBox(e->ErrorMessage());
	}

	// �رռ�¼��
	m_pRecordset->Close();
	m_pRecordset = NULL;

	//��ʾ���½����ڵ���Ӧ����
	UpdateData(false);
}
