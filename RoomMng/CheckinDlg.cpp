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
	, m_discount_kind(_T(""))
	, m_zhengjian_number(_T(""))
	, m_beizhu(_T(""))
	, m_gustname(_T(""))
	, m_regnumber(_T(""))
	, m_pre_discount(0)
	, m_telNumber(_T(""))
	, m_pre_handinmoney(_T(""))
	, m_room_money(_T(""))
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
	DDX_CBString(pDX, IDC_EDIT_discount, m_discount_kind);
	DDX_Text(pDX, IDC_EDIT_custId, m_zhengjian_number);
	DDX_Text(pDX, IDC_EDIT_log, m_beizhu);
	DDX_Text(pDX, IDC_EDIT_name, m_gustname);
	DDX_Text(pDX, IDC_EDIT_NO, m_regnumber);
	DDX_Text(pDX, IDC_EDIT_discount, m_pre_discount);
	DDX_Text(pDX, IDC_EDIT_telNum, m_telNumber);
	DDX_Text(pDX, IDC_EDIT_roomMny, m_room_money);
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
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CheckinDlg message handlers

void CheckinDlg::enable(bool bEnabled)
{
	// m_ComYSFS.EnableWindow(bEnabled);
	//���������ȿؼ�״̬������ʹ�ã���ֹ�������
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
	//GetDlgItem(IDC_DATETIMEPICKERalarmdate)->EnableWindow(bEnabled);
	//GetDlgItem(IDC_DATETIMEPICKERalarmtime)->EnableWindow(bEnabled);	
	GetDlgItem(IDOK)->EnableWindow(bEnabled);
}

BOOL CheckinDlg::OnInitDialog()
{

	CDialog::OnInitDialog();


	// TODO: Add extra initialization here
	enable(0);//
	//���������״̬
	int nYear,nDay,nMonth;
	CString sYear,sDay,sMonth,stime;
	CTime tTime;
	tTime=tTime.GetCurrentTime(); 
	//���õǼǵ�Ĭ��ʱ��
	m_checkindate=tTime;

	m_showuser=loguserid;

	//��ʾ��ʼ����Ϣ
	UpdateData(false);

	m_pRecordset.CreateInstance(__uuidof(Recordset));

	_variant_t var;
	CString strroomnumber;
	// ��ADO�����н��������Ҫ����try...catch()�����������Ϣ��
	// 
	try
	{
		m_pRecordset->Open("SELECT * FROM roomsetting",              // ��ѯ ���������ֶ�
			theApp.m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)//�����������ݿ��쳣
	{
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

		// read data from the database table 

		CComboBox* combobox = (CComboBox*)GetDlgItem(IDC_COMBO_roomnumber);
		while(!m_pRecordset->adoEOF)
		{//��ȡ�����
			var = m_pRecordset->GetCollect("�����");
			if(var.vt != VT_NULL)
				strroomnumber = (LPCSTR)_bstr_t(var);
			combobox->AddString(strroomnumber);//��ӵ��б�

			m_pRecordset->MoveNext();//�ƶ���¼��ָ��
		}
	}
	catch(_com_error *e)//�����쳣
	{
		AfxMessageBox(e->ErrorMessage());
	}

	// �رռ�¼��
	m_pRecordset->Close();
	m_pRecordset = NULL;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
