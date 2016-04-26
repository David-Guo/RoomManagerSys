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
	// ʹ��ADO�������ݿ��¼��
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	_variant_t var;
	CString strregnumber;
	// ��ADO�����н��������Ҫ����try...catch()�����������Ϣ��
	try
	{//�����ݿ�
		m_pRecordset->Open("SELECT * FROM checkintable",                // ��ѯ ���������ֶ�
			theApp.m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)//��������ݿ���ܷ������쳣�����ʵʱ��ʾ��ʾ
	{
		AfxMessageBox(e->ErrorMessage());
	}
	try
	{
		if(!m_pRecordset->BOF)//�ж�ָ���Ƿ������ݼ����
			m_pRecordset->MoveFirst();
		else
		{//��ʾ����������
			AfxMessageBox("��������Ϊ��");
			return false;
		}

		// read data from the database table 
		while(!m_pRecordset->adoEOF)
		{
			var = m_pRecordset->GetCollect("ƾ֤����");
			if(var.vt != VT_NULL)
				strregnumber = (LPCSTR)_bstr_t(var);
			m_regnumber_ctr.AddString(strregnumber);//�����ݿ���
			//�����ݸ�������ֵ
			m_pRecordset->MoveNext();//�ƶ�����ָ��
		}
	}
	catch(_com_error *e)//�����쳣
	{
		AfxMessageBox(e->ErrorMessage());
	}

	// �رռ�¼��
	m_pRecordset->Close();
	m_pRecordset = NULL;

	m_showuser=loguserid;
	//������ʾ
	UpdateData(false);
	enable(0);
	//�ı������״̬
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CCheckoutDlg::enable(bool bEnabled)
{
	// m_ComYSFS.EnableWindow(bEnabled);
	//�ı������״̬
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
	//�ı������״̬���

}


void CCheckoutDlg::OnBnClickedButtonreg()
{
	// TODO: Add your control notification handler code here
	//�ı������״̬
	enable(1);
}


void CCheckoutDlg::OnCbnCloseupComboregnumber()
{
	// TODO: Add your control notification handler code here
	_variant_t var;
	// ʹ��ADO�������ݿ��¼��
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	// ��ADO�����н��������Ҫ����try...catch()�����������Ϣ��
	UpdateData(true);

	CString checkoutnumber;
	CString strsql;
	strsql.Format("SELECT * FROM checkintable where ƾ֤����='%s'",m_regnumber);
	try// �����ݿ�
	{
		m_pRecordset->Open(_variant_t(strsql),                // ��ѯ ���������ֶ�
			theApp.m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)
	{// ������ܷ������쳣
		AfxMessageBox(e->ErrorMessage());
	}
	checkoutnumber+="T";
	checkoutnumber+=m_regnumber;
	// �������޵�ƾ֤����
	m_checknumber =checkoutnumber;

	try
	{
		if(!m_pRecordset->BOF)//�ж�ָ���Ƿ������ݼ����
			m_pRecordset->MoveFirst();
		else
		{// 
			MessageBox("��������Ϊ��","�ͷ�����ϵͳ");
			return ;
		}
		// ��ȡ���ݱ��������ֶ�
		var = m_pRecordset->GetCollect("����");
		if(var.vt != VT_NULL)
			m_name = (LPCSTR)_bstr_t(var);
		// ��ȡ���ݱ���֤�������ֶ�
		var = m_pRecordset->GetCollect("���֤����");
		if(var.vt != VT_NULL)
			m_checkoutzhenjian_number = (LPCSTR)_bstr_t(var);
		// ��ȡ���ݱ�����ϸ��ַ�ֶ�
		var = m_pRecordset->GetCollect("��ϵ�绰");
		if(var.vt != VT_NULL)
			m_telNum = (LPCSTR)_bstr_t(var);
		// ��ȡ���ݱ��з�����ֶ�
		var = m_pRecordset->GetCollect("�����");
		if(var.vt != VT_NULL)
			m_roomnumber = (LPCSTR)_bstr_t(var);
		// ��ȡ���ݱ��пͷ������ֶ�
		var = m_pRecordset->GetCollect("�ͷ�����");
		if(var.vt != VT_NULL)
			m_roomlevel = (LPCSTR)_bstr_t(var);
		// ��ȡ���ݱ��пͷ��۸��ֶ�
		var = m_pRecordset->GetCollect("����۸�");
		if(var.vt != VT_NULL)
			m_checkoutroommoney = (LPCSTR)_bstr_t(var);
		// ��ȡ���ݱ�����סʱ���ֶ�
		var = m_pRecordset->GetCollect("��סʱ��");
		if(var.vt != VT_NULL)
			checkinday = (LPCSTR)_bstr_t(var);
		// ��ȡ���ݰ���ס�������ֶ�
		var = m_pRecordset->GetCollect("ס������");
		if(var.vt != VT_NULL)
			m_realdays = (LPCSTR)_bstr_t(var);
		// ��ȡ���ݱ����ۿ��ֶ�
		var = m_pRecordset->GetCollect("�ۿ�");
		if(var.vt != VT_NULL)
			m_discount = (LPCSTR)_bstr_t(var);
		// ��ȡ���ݱ���Ѻ���ֶ�
		var = m_pRecordset->GetCollect("Ѻ��");
		if(var.vt != VT_NULL)
			m_prehandinmoney = (LPCSTR)_bstr_t(var);
		else
			m_prehandinmoney ="0";
		// ��ȡ���ݱ��б�ע�ֶ�
		var = m_pRecordset->GetCollect("��ע");
		if(var.vt != VT_NULL)
			m_checkoutbeizhu = (LPCSTR)_bstr_t(var);

		UpdateData(false);
	}
	catch(_com_error *e)// �����쳣
	{
		AfxMessageBox(e->ErrorMessage());
	}

	// �رռ�¼��
	m_pRecordset->Close();
	m_pRecordset = NULL;

	UpdateData(false);// ������ʾ�������������
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
		MessageBox("����д����������Ϣ��", "�ͷ�����ϵͳ");
		return;
	}

	m_pRecordsetout.CreateInstance(__uuidof(Recordset));
	//INSERT INTO checkinregtable (ƾ֤����)VALUES('%s')
	CString strsqlstore;

	try// �����ݿ�
	{
		m_pRecordsetout->Open("SELECT * FROM checkouttable", // ��ѯ ���������ֶ�
			theApp.m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)// �����쳣
	{
		AfxMessageBox(e->ErrorMessage());
	}

	try
	{       // �������ݿ��������
		m_pRecordsetout->AddNew();
		// // �����ݱ���д��ƾ֤�����ֶ�����
		m_pRecordsetout->PutCollect("ƾ֤����", _variant_t(m_checknumber));
		m_pRecordsetout->PutCollect("����", _variant_t(m_name));
		m_pRecordsetout->PutCollect("���֤����", _variant_t(m_checkoutzhenjian_number));
		m_pRecordsetout->PutCollect("��ϵ�绰", _variant_t(m_telNum));
		m_pRecordsetout->PutCollect("�����", _variant_t(m_roomnumber));
		m_pRecordsetout->PutCollect("�ͷ�����", _variant_t(m_roomlevel));
		m_pRecordsetout->PutCollect("����۸�", _variant_t(m_checkoutroommoney));
		m_pRecordsetout->PutCollect("��סʱ��", _variant_t(checkinday));
		m_pRecordsetout->PutCollect("ס������", _variant_t(m_realdays));
		m_pRecordsetout->PutCollect("��������", _variant_t(m_extramoney));
		m_pRecordsetout->PutCollect("�ۿ�", _variant_t(m_discount));
		m_pRecordsetout->PutCollect("Ӧ���޷�", _variant_t(m_totalPay));
		m_pRecordsetout->PutCollect("Ѻ��", _variant_t(m_prehandinmoney));
		m_pRecordsetout->PutCollect("��ע", _variant_t(m_checkoutbeizhu));
		m_pRecordsetout->PutCollect("�ͷ�������", _variant_t(m_showuser));

		// �������ݿ�
		m_pRecordsetout->Update();
		MessageBox("�������!","�ͷ�����ϵͳ");
	}
	catch(_com_error *e)
	{//�����쳣
		AfxMessageBox(e->ErrorMessage());
	}
	m_pRecordsetout->Close();// �رռ�¼��
	m_pRecordsetout = NULL;
	///////////////////////////////////////////////////////////////
	//update the roomsetting table
	CString SQLstr;
	SQLstr="SELECT * FROM roomsetting where �����='" ;
	SQLstr+=m_roomnumber;
	SQLstr+="'";
	if(!mymendroominfoset.Open(AFX_DB_USE_DEFAULT_TYPE,SQLstr))
	{//��ѯ���ݿ�õ����ݼ���
		MessageBox("��roomsetting ��ʧ�ܣ����ķ���״̬ʧ��!","�ͷ�����ϵͳ");
		if(mymendroominfoset.IsOpen())
		{
			mymendroominfoset.Close();
		}
		return ;
	}

	mymendroominfoset.Edit();//�������ݿ��������

	mymendroominfoset.column4="�շ�";
	mymendroominfoset.Update();// �������ݿ�
	mymendroominfoset.Requery();
	///////////////////////////////////
	if(mymendroominfoset.IsOpen())
	{
		mymendroominfoset.Close();// �ر����ݼ�
	}
	CDialog::OnOK();
}
