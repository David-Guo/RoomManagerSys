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
	//nYear=m_room_usetime.GetYear();//��ȡ���
	//nDay=m_room_usetime.GetDay();//��ȡ��
	//nMonth=m_room_usetime.GetMonth();//��ȡ�·�
	//sYear.Format("%d",nYear);//ת��Ϊ�ַ���
	//sDay.Format("%d",nDay);//ת��Ϊ�ַ���
	//sMonth.Format("%d",nMonth);//ת��Ϊ�ַ���
	//��ʽ��ʱ�����
	//usetime.Format("%s-%s-%s",sYear,sMonth,sDay);
	if (m_roomlevel == _T("") && m_roomnumber == _T("") && m_roommoney == _T("")) {
		MessageBox("����д����������Ϣ��", "�ͷ�����ϵͳ");
		return;
	}
    m_pRecordset1.CreateInstance(__uuidof(Recordset));
    CString strsql;
	strsql.Format("SELECT * FROM roomsetting where �����='%s'",m_roomnumber);
    try//�����ݿ�
	{
		m_pRecordset1->Open(_variant_t(strsql),                // ��ѯ���������ֶ�
			theApp.m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)//��������ݿ�ʱ����ܷ������쳣���
	{
		AfxMessageBox(e->ErrorMessage());
	}
    if (!m_pRecordset1->adoEOF) {
        MessageBox("�˷�����Ѵ��ڣ�", "�ͷ�����ϵͳ");
        return;
    }
	try
	{
		// д����ֶ�ֵ
		m_pRecordset->AddNew();
		m_pRecordset->PutCollect("�����", _variant_t(m_roomnumber));
		m_pRecordset->PutCollect("��������",_variant_t(m_roomlevel));
		m_pRecordset->PutCollect("�۸�", _variant_t(m_roommoney));
		m_pRecordset->PutCollect("��̬", _variant_t(m_roomstate));
		m_pRecordset->PutCollect("�豸����", _variant_t(m_roomset));
		//m_pRecordset->PutCollect("Ӫҵ����", _variant_t(usetime));
		m_pRecordset->Update();
		//�������ݿ����
		MessageBox("���óɹ�!","�ͷ�����ϵͳ");
	}
	catch(_com_error *e)//������ܷ������쳣
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
	// �����б����ɫ
	m_setroomdlg_list.SetTextColor(RGB (0, 0, 0));
	m_setroomdlg_list.SetTextBkColor(RGB (140, 180, 20));
	// �б���ʼ��
	m_setroomdlg_list.InsertColumn(0,"�������");
	m_setroomdlg_list.InsertColumn(1,"��������");
	m_setroomdlg_list.InsertColumn(2,"�۸�");
	m_setroomdlg_list.InsertColumn(3,"��̬");
	m_setroomdlg_list.InsertColumn(4,"�豸����");

	RECT rect;
	m_setroomdlg_list.GetWindowRect(&rect);
	int wid=rect.right-rect.left;
	int i=0;
	m_setroomdlg_list.SetColumnWidth(0,wid/6);
	m_setroomdlg_list.SetColumnWidth(1,wid/6);
	m_setroomdlg_list.SetColumnWidth(2,wid/6);
	m_setroomdlg_list.SetColumnWidth(3,wid/6);
	m_setroomdlg_list.SetColumnWidth(4,wid/3);


	//�����б����
	m_setroomdlg_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	///////////////////////////////////////////

	m_pRecordset.CreateInstance(__uuidof(Recordset));

	_variant_t var;
	// ��ADO�����н��������Ҫ����try...catch()�����������Ϣ��
	// 
	try
	{//�����ݱ�
		m_pRecordset->Open("SELECT * FROM roomsetting",                // ��ѯ���������ֶ�
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
			return false;
		}

		// read data from the database table 
		while(!m_pRecordset->adoEOF)
		{//ѭ����ȡ���ݣ������б������ʾ
			//��ȡ���ݱ��з���Ŷ�Ӧ�ֶε�ֵ
			var = m_pRecordset->GetCollect("�����");
			if(var.vt != VT_NULL)
				showroom_roomnumber = (LPCSTR)_bstr_t(var);
			//���б������ʾ���ֶε�����
			m_setroomdlg_list.InsertItem(i,showroom_roomnumber.GetBuffer(50));
			//��ȡ���ݱ��з������Ͷ�Ӧ�ֶε�ֵ
			var = m_pRecordset->GetCollect("��������");
			if(var.vt != VT_NULL)
				showroom_roomlevel = (LPCSTR)_bstr_t(var);
			//���б������ʾ���ֶε�����
			m_setroomdlg_list.SetItemText(i,1,showroom_roomlevel.GetBuffer(50));
			//��ȡ���ݱ��м۸��Ӧ�ֶε�ֵ
			var = m_pRecordset->GetCollect("�۸�");
			if(var.vt != VT_NULL)
				showroom_roommoney = (LPCSTR)_bstr_t(var);
			//���б������ʾ���ֶε�����
			m_setroomdlg_list.SetItemText(i,2,showroom_roommoney.GetBuffer(50));
			//��ȡ���ݱ��з�̬��Ӧ�ֶε�ֵ
			var = m_pRecordset->GetCollect("��̬");
			if(var.vt != VT_NULL)
				showroom_roomstate = (LPCSTR)_bstr_t(var);
			//���б������ʾ���ֶε�����
			m_setroomdlg_list.SetItemText(i,3,showroom_roomstate.GetBuffer(50));

			//��ȡ���ݱ������ö�Ӧ�ֶε�ֵ
			var = m_pRecordset->GetCollect("�豸����");
			if(var.vt != VT_NULL)
				showroom_roomsetting = (LPCSTR)_bstr_t(var);
			//���б������ʾ���ֶε�����
			m_setroomdlg_list.SetItemText(i,4,showroom_roomsetting.GetBuffer(50));

			i++;
			//�ƶ���¼��ָ�뵽��һ����¼
			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error *e)//������ܷ������쳣
	{
		AfxMessageBox(e->ErrorMessage());
	}

	//������ʾ
	UpdateData(false);
}


void CSetroomdlg::enable(bool bEnabled)
{
	// m_ComYSFS.EnableWindow(bEnabled);
	//�ı�����ؼ���״̬
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
	//������ʼ��
	m_roomnumber = _T("");
	m_roomset = _T("");
	m_roommoney = _T("");
	m_roomlevel = _T("");
	m_roomstate = _T("");
	//������ʾ
	UpdateData(false);
}


void CSetroomdlg::OnBnClickedbeginsetroom()
{
	// TODO: Add your control notification handler code here
	enable(1);
}
