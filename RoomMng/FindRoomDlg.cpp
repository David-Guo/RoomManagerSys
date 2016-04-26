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
	//�����б����ɫ���
	//��ʼ���б��
	m_findroom_list.InsertColumn(0,"�������");
	m_findroom_list.InsertColumn(1,"��������");
	m_findroom_list.InsertColumn(2,"�۸�");
	m_findroom_list.InsertColumn(3,"��̬");
	m_findroom_list.InsertColumn(4,"�豸����");


	RECT rect;
	m_findroom_list.GetWindowRect(&rect);
	int wid=rect.right-rect.left;
	int i=0;
	m_findroom_list.SetColumnWidth(0,wid/6);
	m_findroom_list.SetColumnWidth(1,wid/6);
	m_findroom_list.SetColumnWidth(2,wid/6);
	m_findroom_list.SetColumnWidth(3,wid/6);
	m_findroom_list.SetColumnWidth(4,wid/3);

	//�����б����
	m_findroom_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	///////////////////////////////////////////
	m_pRecordsetout.CreateInstance(__uuidof(Recordset));	
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	//m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pRecordsetdel.CreateInstance(__uuidof(Recordset));


	_variant_t var;
	// ��ADO�����н��������Ҫ����try...catch()�����������Ϣ��
	// 
	try//�����ݿ�
	{
		m_pRecordset->Open("SELECT * FROM roomsetting",                // ��ѯ ���������ֶ�
			theApp.m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)
	{//������ܳ��ֵĴ��쳣���
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

		m_findroomdlgroomnumberctr.ResetContent();
		// read data from the database table 
		while(!m_pRecordset->adoEOF)
		{//ѭ���������ݣ�ʵʱ���б������ʾ
			//��ȡ���ݱ��ڷ�����ֶ�����
			var = m_pRecordset->GetCollect("�����");
			if(var.vt != VT_NULL)
				findroom_roomnumber = (LPCSTR)_bstr_t(var);
			m_findroomdlgroomnumberctr.AddString(findroom_roomnumber);
			//���б������ʾ���ֶε�����
			m_findroom_list.InsertItem(i,findroom_roomnumber.GetBuffer(50));
			//��ȡ���ݱ��ڷ��������ֶ�����
			var = m_pRecordset->GetCollect("��������");
			if(var.vt != VT_NULL)
				findroom_roomlevel = (LPCSTR)_bstr_t(var);
			//���б������ʾ���ֶε�����
			m_findroom_list.SetItemText(i,1,findroom_roomlevel.GetBuffer(50));
			//��ȡ���ݱ��ڼ۸��ֶ�����
			var = m_pRecordset->GetCollect("�۸�");
			if(var.vt != VT_NULL)
				findroom_roommoney = (LPCSTR)_bstr_t(var);
			//���б������ʾ���ֶε�����
			m_findroom_list.SetItemText(i,2,findroom_roommoney.GetBuffer(50));
			//��ȡ���ݱ��ڷ�̬�ֶ�����
			var = m_pRecordset->GetCollect("��̬");
			if(var.vt != VT_NULL)
				findroom_roomstate = (LPCSTR)_bstr_t(var);
			//���б������ʾ���ֶε�����
			m_findroom_list.SetItemText(i,3,findroom_roomstate.GetBuffer(50));
			//��ȡ���ݱ��������ֶ�����
			var = m_pRecordset->GetCollect("�豸����");
			if(var.vt != VT_NULL)
				findroom_roomsetting = (LPCSTR)_bstr_t(var);
			//���б������ʾ���ֶε�����
			m_findroom_list.SetItemText(i,4,findroom_roomsetting.GetBuffer(50));

			i++;
			//�ƶ���¼ָ��
			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error *e)//������ܵĶ�ȡ�����쳣���
	{
		AfxMessageBox(e->ErrorMessage());
	}

	// �رռ�¼��
	m_pRecordset->Close();
	//	m_pRecordset = NULL;

	//������ʾ
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
		MessageBox("����ѡ�񷿼�ţ���������Ƿ���","�ͷ�����ϵͳ");
		return;
	}
	if(m_findroom_status=="" || m_findroom_roomlevel=="" || m_findroom_roommoney=="")
	{
		MessageBox("�����б���ѡ�񷿼䣬��֤�޸���Ϣ������", "�ͷ�����ϵͳ");
		return;
	}

	//INSERT INTO checkinregtable (ƾ֤����)VALUES('%s')
	CString strsqlmend;
	strsqlmend.Format("SELECT * FROM roomsetting where �����='%s'",m_findroomdlgroomnumber);
	m_pRecordsetout->raw_Close();
	try
	{    //�����ݿ�
		m_pRecordsetout->Open(_variant_t(strsqlmend),                // ��ѯ ���������ֶ�
			theApp.m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)
	{//������ܵ��쳣�����ʵʩ��ʾ�û�
		AfxMessageBox(e->Description());
	}

	try
	{    //����������д�����ݿ�
		//����Ӧ��������д�뷿�������ֶ���
		m_pRecordsetout->PutCollect("��������", _variant_t(m_findroom_roomlevel));
		//����Ӧ��������д��۸��ֶ���
		m_pRecordsetout->PutCollect("�۸�", _variant_t(m_findroom_roommoney));
		//����Ӧ��������д�뷿̬�ֶ���
		m_pRecordsetout->PutCollect("��̬", _variant_t(m_findroom_status));
		//����Ӧ��������д��ʹ�������ֶ���
		m_pRecordsetout->PutCollect("�豸����", _variant_t(m_findroom_roomsetting));

		m_pRecordsetout->Update();

		//��ɸ������ݿ�
		MessageBox("�޸ĳɹ�!","�ͷ�����ϵͳ");
		//	UpdateData(false);
	}
	catch(_com_error *e)//�����쳣
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

	UpdateData(true);//���������Ӧ������

	CString strsql;
	strsql.Format("SELECT * FROM roomsetting where �����='%s'",m_findroomdlgroomnumber);
	m_pRecordsetout->raw_Close();
	try
	{//�����ݿ�
		m_pRecordsetout->Open(_variant_t(strsql),                // ��ѯ ���������ֶ�
			theApp.m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error *e)
	{//�����쳣
		AfxMessageBox(e->ErrorMessage());
	}

	int i=0;
	try
	{
		if(!m_pRecordsetout->BOF)//�ж�ָ���Ƿ������ݼ����
			m_pRecordsetout->MoveFirst();
		else
		{
			MessageBox("��������Ϊ��","�ͷ�����ϵͳ");
			return ;
		}
		//��ȡ��ѯ�������ݣ������б������ʾ
		//��ȡ���ݱ��ڷ�����ֶ�����
		var = m_pRecordsetout->GetCollect("�����");
		if(var.vt != VT_NULL)
			findroom_roomnumber = (LPCSTR)_bstr_t(var);
		//���б������ʾ���ֶε�����
		m_findroom_list.InsertItem(i,findroom_roomnumber.GetBuffer(50));

		//��ȡ���ݱ��ڷ��������ֶ�����
		var = m_pRecordsetout->GetCollect("��������");
		if(var.vt != VT_NULL)
			findroom_roomlevel = (LPCSTR)_bstr_t(var);
		//���б������ʾ���ֶε�����
		m_findroom_list.SetItemText(i,1,findroom_roomlevel.GetBuffer(50));
		//��ȡ���ݱ��ڼ۸��ֶ�����
		var = m_pRecordsetout->GetCollect("�۸�");
		if(var.vt != VT_NULL)
			findroom_roommoney = (LPCSTR)_bstr_t(var);
		//���б������ʾ���ֶε�����
		m_findroom_list.SetItemText(i,2,findroom_roommoney.GetBuffer(50));
		//��ȡ���ݱ��ڷ�̬�ֶ�����
		var = m_pRecordsetout->GetCollect("��̬");
		if(var.vt != VT_NULL)
			findroom_roomstate = (LPCSTR)_bstr_t(var);
		//���б������ʾ���ֶε�����
		m_findroom_list.SetItemText(i,3,findroom_roomstate.GetBuffer(50));
		//��ȡ���ݱ��������ֶ�����
		var = m_pRecordsetout->GetCollect("�豸����");
		if(var.vt != VT_NULL)
			findroom_roomsetting = (LPCSTR)_bstr_t(var);
		//���б������ʾ���ֶε�����
		m_findroom_list.SetItemText(i,4,findroom_roomsetting.GetBuffer(50));

		//������ʾ
		UpdateData(false);
	}
	catch(_com_error *e)//�����쳣
	{
		AfxMessageBox(e->ErrorMessage());
	}

	// �رռ�¼��
	m_pRecordsetout->Close();
	//	m_pRecordsetout = NULL;
	//������ʾ
	UpdateData(false);
}


void CFindRoomDlg::OnNMClickListfindroom(NMHDR *pNMHDR, LRESULT *pResult)
{
	int i = m_findroom_list.GetSelectionMark();
	//��ѡ������Ŀ�Ķ�Ӧ������ʾ�ڶ�Ӧ��������ڣ��Ա��޸�
	m_findroom_roomlevel = m_findroom_list.GetItemText(i,1);
	m_findroom_roommoney = m_findroom_list.GetItemText(i,2);
	m_findroom_status=m_findroom_list.GetItemText(i,3);
	m_findroom_roomsetting =m_findroom_list.GetItemText(i,4);

	UpdateData(FALSE);//������ʾ
	*pResult = 0;
}
