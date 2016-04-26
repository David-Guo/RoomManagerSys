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
	GetDlgItem(IDOK)->EnableWindow(bEnabled);
}


BOOL CheckinDlg::OnInitDialog()
{

	CDialog::OnInitDialog();


	// TODO: Add extra initialization here
	enable(0);//
	//���������״̬
	CString sYear,sDay,sMonth,stime;
	CTime tTime;
	tTime=tTime.GetCurrentTime(); 
	//���õǼǵ�Ĭ��ʱ��
	m_checkindate=tTime;

	m_showuser=loguserid;

	//��ʾ��ʼ����Ϣ
	UpdateData(false);

	m_pRecordset.CreateInstance(__uuidof(Recordset));

	_variant_t var, var1;
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
			var1 = m_pRecordset->GetCollect("��̬");
			CString cmp = (LPCSTR)_bstr_t(var1);
			if(var.vt != VT_NULL)
				strroomnumber = (LPCSTR)_bstr_t(var);
			if(cmp == "����")
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


void CheckinDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	// TODO: ����ı����Ƿ��� debug ʱʹ�õ�
	//m_zhengjian_number = "123456789123456";
	//m_gustname = "gdw";
	//m_pre_discount = 100;
	//m_room_money = "118";
	//m_pre_handinmoney = "118";
	//m_realmoney = "118";
	//m_roomnumber = "001";
	//m_checkdays = 1;
	//m_roomlevel = "��׼";
	UpdateData(true);
	//////////////////////////////////////////////////////////////////////////
	/*
	*	������֤�ĺ����Ƿ�Ϊ15λ����Ϊ18λ
	*/
	CString strCertifyCode;//֤������


	//���֤������
	int nCertifyCodeLength=m_zhengjian_number.GetLength();//���֤���ĳ���
	if(nCertifyCodeLength!=15&&nCertifyCodeLength!=18)
	{
		MessageBox("������֤�ĺ����λ������ȷ!\nӦ��Ϊ15λ����18λ!",
			"���֤����",MB_OK);
		return ;
	}
	//////////////////////////////////////////////////////////////////////////
	// ���·���״̬Ϊ��������ס
	CString SQLstr;
	SQLstr="SELECT * FROM roomsetting where �����='" ;
	SQLstr+=m_roomnumber;
	SQLstr+="'";
	myroominfoset.Open(AFX_DB_USE_DEFAULT_TYPE,SQLstr);
	myroominfoset.Edit();
	myroominfoset.column4="��ס";
	myroominfoset.Update();
	myroominfoset.Requery();
	if(myroominfoset.IsOpen())
	{//�ر����ݱ�
		myroominfoset.Close();
	}

	m_pRecordset.CreateInstance(__uuidof(Recordset));

	// ��ADO�����н��������Ҫ����try...catch()�����������Ϣ��
	// 
	try
	{//�����ݿ�
		m_pRecordset->Open("SELECT * FROM checkintable",                // ��ѯ���������ֶ�
			theApp.m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)//��������ݿ�ʱ��ĸ����쳣
	{
		AfxMessageBox(e->ErrorMessage());
	}
	//////////////////////////////////////////////////////////////

	try
	{
		// д����ֶ�ֵ��׼���������ݿ�
		m_pRecordset->AddNew();
		m_pRecordset->PutCollect("ƾ֤����", _variant_t(m_regnumber));
		m_pRecordset->PutCollect("����",_variant_t(m_gustname));
		m_pRecordset->PutCollect("���֤����", _variant_t(m_zhengjian_number));
		m_pRecordset->PutCollect("��ϵ�绰", _variant_t(m_telNumber));
		m_pRecordset->PutCollect("�����", _variant_t(m_roomnumber));
		m_pRecordset->PutCollect("�ͷ�����", _variant_t(m_roomlevel));

		//CString str_room_money;
		//m_room_money.GetWindowText(str_room_money);
		m_pRecordset->PutCollect("����۸�", _variant_t(m_room_money));//str_room_money));

		CString checkindate;//��ȡ�Ǽ�ס������
		int nYear,nDay,nMonth;
		CString sYear,sDay,sMonth;
		nYear=m_checkindate.GetYear();//��ȡ���
		nDay=m_checkindate.GetDay();//��ȡ��
		nMonth=m_checkindate.GetMonth();//��ȡ�·�
		sYear.Format("%d",nYear);//ת��Ϊ�ַ���
		sDay.Format("%d",nDay);//ת��Ϊ�ַ���
		sMonth.Format("%d",nMonth);//ת��Ϊ�ַ���
		checkindate.Format("%s-%s-%s",sYear,sMonth,sDay);//��ʽ��ʱ��
		m_pRecordset->PutCollect("��סʱ��",_variant_t(checkindate));
		//����
		m_pRecordset->PutCollect("ס������", _variant_t(m_checkdays));
		//������ʱ�洢�ռ�
		char str_money[50]; 
		//_gcvt(atof(str_room_money)*m_checkdays, 4, str_money );
		_gcvt_s(str_money, 50, atof(m_room_money)*m_checkdays, 4);
		m_pRecordset->PutCollect("�޷�", _variant_t(str_money));


		m_pRecordset->PutCollect("�ۿ�",_variant_t(m_pre_discount));
		// ������ʱ�洢�ռ�
		char strhand_money[50];
		_gcvt_s(strhand_money, 50, atof(m_realmoney)*m_pre_discount/100, 4);
		//_gcvt(atof(m_realmoney)*m_pre_discount/100, 4, strhand_money );
		m_pRecordset->PutCollect("Ӧ���޷�", _variant_t(strhand_money));
		m_pRecordset->PutCollect("Ѻ��", _variant_t(m_pre_handinmoney));
		m_pRecordset->PutCollect("��ע", _variant_t(m_beizhu));
		m_pRecordset->PutCollect("�ͷ�������", _variant_t(m_showuser));

		m_pRecordset->Update();
		MessageBox("�Ǽǳɹ�!","�ͷ�����ϵͳ");
	}
	catch(_com_error *e)//����д�����ݿ�ʱ����ܷ������쳣���
	{
		AfxMessageBox(e->ErrorMessage());
	}
	///////////////////////////////////////////////////
	//�رռ�¼��
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
	tTime=tTime.GetCurrentTime(); //��ȡϵͳ��ǰ��ʱ��
	nYear=tTime.GetYear();//��ȡ���
	nDay=tTime.GetDay();//��ȡ�·�
	nMonth=tTime.GetMonth();//��ȡ��
	sYear.Format("%d",nYear);//ת��Ϊ�ַ���
	sDay.Format("%d",nDay);//ת��Ϊ�ַ���
	sMonth.Format("%d",nMonth);//ת��Ϊ�ַ�������ʽ��ʱ��
	strnowdate.Format("%s-%s-%s",sYear,sMonth,sDay);


	// ʹ��ADO�������ݿ��¼��
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	// ��ADO�����н��������Ҫ����try...catch()�����������Ϣ��
	// 
	CString strsql;
	strsql.Format("SELECT * FROM checkintable where ��סʱ��='%s'",strnowdate);
	try//�����ݿ�
	{
		m_pRecordset->Open(_variant_t(strsql),                // ��ѯ���������ֶ�
			theApp.m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)//��������ݿ�ʱ����ܷ������쳣���
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
	//�����Ǽ�ƾ֤����
	m_regnumber =strcheckinnumber;

	// �رռ�¼��
	m_pRecordset->Close();
	m_pRecordset = NULL;
	//������ʾ
	UpdateData(false);
}


void CheckinDlg::OnCbnSelchangeComboroomnumber()
{
	// TODO: Add your control notification handler code here
	int index = ((CComboBox*)GetDlgItem(IDC_COMBO_roomnumber))->GetCurSel(); //�����Ҫ������ֵ  
	((CComboBox*)GetDlgItem(IDC_COMBO_roomnumber))->SetCurSel(index); //���ó���Ҫ����ֵ��ֵ  
	UpdateData(true); //����ȡ�������������ı���ֵ

	try
	{
		//���ѡ����б���Ŀ����
		CString SQLstr;
		SQLstr="SELECT * FROM roomsetting where �����='";
		SQLstr+=m_roomnumber;
		SQLstr+="'";
		if(!myroominfoset.Open(AFX_DB_USE_DEFAULT_TYPE,SQLstr))
		{//��ѯ���ݿ�õ����ݼ���
			MessageBox("û�д˷�����룬�����ݿ�ʧ��!","�ͷ�����ϵͳ");
			if(myroominfoset.IsOpen())
			{//�ر����ݱ�
				myroominfoset.Close();
			}
			return ;
		}
		m_roomlevel=myroominfoset.column2;//��ȡ��������
		roommoney = myroominfoset.column3;
		m_room_money.Format("%f", roommoney);//��ȡ����۸�
	}
	catch(_com_error *e)//�����쳣
	{
		AfxMessageBox(e->ErrorMessage());
	}

	if(myroominfoset.IsOpen())
	{//�ر����ݱ�
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

	double fneed_room_money=0;//��ʼ��

	fneed_room_money=m_pre_discount*roommoney*m_checkdays/100;

	m_realmoney.Format("%f", fneed_room_money);
	//������ʾ
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

	double fneed_room_money=0;//��ʼ��

	fneed_room_money=m_pre_discount*roommoney*m_checkdays/100;

	m_realmoney.Format("%f", fneed_room_money);
	//������ʾ
	UpdateData(false);
	// TODO:  Add your control notification handler code here
}
