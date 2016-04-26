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
	//����Ĭ��ʱ��
	m_roomsaleenddate=tTime;
	// TODO: Add extra initialization here
	//�����б����ɫ
	m_roomsale_list.SetTextColor(RGB (0, 0, 0));
	m_roomsale_list.SetTextBkColor(RGB (140, 180, 20));
	//��ʼ���б��
	m_roomsale_list.InsertColumn(1,"ƾ֤����");
	m_roomsale_list.InsertColumn(2,"����");
	m_roomsale_list.InsertColumn(3,"�����");
	m_roomsale_list.InsertColumn(4,"����");
	m_roomsale_list.InsertColumn(5,"����");
	m_roomsale_list.InsertColumn(6,"�ۿۣ�%��");
	m_roomsale_list.InsertColumn(7,"�����������");
	m_roomsale_list.InsertColumn(8,"�ܷѷ�");

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

	//�����б����
	m_roomsale_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	// ʹ��ADO�������ݿ��¼��
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	// ��ADO�����н��������Ҫ����try...catch()�����������Ϣ��
	try
	{//�����ݱ�
		m_pRecordset->Open("SELECT * FROM checkouttable",// ��ѯ���������ֶ�
			theApp.m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)
	{//�׳��쳣���
		AfxMessageBox(e->ErrorMessage());
	}
	try
	{
		if(!m_pRecordset->BOF)//�ж�ָ���Ƿ������ݼ����
			m_pRecordset->MoveFirst();
		else
		{
			AfxMessageBox("��������Ϊ��");
			return false;
		}
		while(!m_pRecordset->adoEOF)
		{   //ѭ����ȡ���ݲ���ӡ���б����
			showinList(i);
			i++;
			m_pRecordset->MoveNext();//��¼��ָ������һ����¼
		}
	}
	catch(_com_error *e)//�׳��쳣�������ʾ�û�
	{
		AfxMessageBox(e->ErrorMessage());
	}
	// �رռ�¼��
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
	// ��ADO�����н��������Ҫ����try...catch()�����������Ϣ��
	try
	{//�����ݱ�
		m_pRecordset->Open("SELECT * FROM checkouttable",     // ��ѯ���������ֶ�
			theApp.m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)//�׳��쳣
	{
		AfxMessageBox(e->ErrorMessage());
	}
	try
	{//�ж�ָ���Ƿ������ݼ����
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		else
		{
			MessageBox("��������Ϊ��","�ͷ�����ϵͳ");
			return;
		}

		// read data from the database table 
		while(!m_pRecordset->adoEOF)
		{
			//ѭ����ȡ����
			var = m_pRecordset->GetCollect("��סʱ��");
			if(var.vt != VT_NULL)
				m_checkoutdate = (LPCSTR)_bstr_t(var);
			CString outyear,outmonth,outday;
			outyear=m_checkoutdate.Mid(0,4);
			outmonth=m_checkoutdate.Mid(5,m_checkoutdate.Find('-',6)-5);
			outday=m_checkoutdate.Mid(m_checkoutdate.ReverseFind('-')+1,m_checkoutdate.GetLength()-m_checkoutdate.ReverseFind('-'));
			//����ʱ�����
			CTime outtime(atoi(outyear),atoi(outmonth),atoi(outday));
			//����ʱ�����
			CTime begintime(m_roomsalebegindate.GetYear(),m_roomsalebegindate.GetMonth(),m_roomsalebegindate.GetDay());
			//����ʱ�����
			CTime endtime(m_roomsaleenddate.GetYear(),m_roomsaleenddate.GetMonth(),m_roomsaleenddate.GetDay());

			if((outtime<endtime)&&(outtime>begintime))
			{   //�������������ݱ���ȡ�������б������ʾ
				showinList(i);
				i++;//�ƶ���¼��ָ�뵽��һ����¼
				m_pRecordset->MoveNext();
			}

			else//���������������ֱ�������˼�¼
			{
				m_pRecordset->MoveNext();
				continue;
			}
		}
	}
	catch(_com_error *e)//�����쳣
	{
		AfxMessageBox(e->ErrorMessage());
	}
	// �رռ�¼��
	m_pRecordset->Close();
	m_pRecordset = NULL;


	//	m_show_pregetmoney = sum_pregetmoney;
	//	m_show_shouldgetmoney=sum_realmoney;
	UpdateData(false);
}


void CRoomsaleDlg::showinList(int i) {
	_variant_t var;
	//��ȡ���ݱ���ƾ֤�����ֶ�����
	var = m_pRecordset->GetCollect("ƾ֤����");
	if(var.vt != VT_NULL)
		m_regnumber = (LPCSTR)_bstr_t(var);
	m_roomsale_list.InsertItem(i,m_regnumber.GetBuffer(50));

	//��ȡ���ݱ��������ֶ�����
	var = m_pRecordset->GetCollect("����");
	if(var.vt != VT_NULL)
		m_name = (LPCSTR)_bstr_t(var);
	m_roomsale_list.SetItemText(i,1,m_name.GetBuffer(50));

	//��ȡ���ݱ��з�����ֶ�����
	var = m_pRecordset->GetCollect("�����");
	if(var.vt != VT_NULL)
		m_roomnumber = (LPCSTR)_bstr_t(var);
	m_roomsale_list.SetItemText(i,2,m_roomnumber.GetBuffer(50));

	//��ȡ���ݱ��пͷ��۸��ֶ�����
	var = m_pRecordset->GetCollect("����۸�");
	if(var.vt != VT_NULL)
		m_room_money = (LPCSTR)_bstr_t(var);
	m_roomsale_list.SetItemText(i,3,m_room_money.GetBuffer(50));

	//��ȡ���ݱ���ס�������ֶ�����
	var = m_pRecordset->GetCollect("ס������");
	if(var.vt != VT_NULL)
		m_realdays = (LPCSTR)_bstr_t(var);
	m_roomsale_list.SetItemText(i,4,m_realdays.GetBuffer(50));

	//��ȡ���ݱ����ۿ��ֶ�����
	var = m_pRecordset->GetCollect("�ۿ�");
	if(var.vt != VT_NULL)
		m_discount = (LPCSTR)_bstr_t(var);
	m_roomsale_list.SetItemText(i,5,m_discount.GetBuffer(50));

	var = m_pRecordset->GetCollect("��������");
	if(var.vt != VT_NULL)
		m_extramoney = (LPCSTR)_bstr_t(var);
	m_roomsale_list.SetItemText(i,6,m_extramoney.GetBuffer(50));

	var = m_pRecordset->GetCollect("Ӧ���޷�");
	if(var.vt != VT_NULL)
		m_totalPay = (LPCSTR)_bstr_t(var);
	m_roomsale_list.SetItemText(i,7,m_totalPay.GetBuffer(50));

	m_extraSum += atof(m_extramoney);
	m_totalSum = m_totalSum + m_extraSum + atof(m_totalPay);
}