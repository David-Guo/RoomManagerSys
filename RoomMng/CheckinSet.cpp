// CheckinSet.h : Implementation of the CCheckinSet class



// CCheckinSet implementation

// code generated on 2016��4��25��, 15:05

#include "stdafx.h"
#include "CheckinSet.h"
IMPLEMENT_DYNAMIC(CCheckinSet, CRecordset)

CCheckinSet::CCheckinSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	column1 = L"";
	column2 = L"";
	column3 = L"";
	column4 = L"";
	column5 = L"";
	column6 = L"";
	column7 = 0.0;
	column8;
	column9 = 0.0;
	column10 = 0.0;
	column11 = 0.0;
	column12 = 0.0;
	column13 = 0.0;
	column14 = L"";
	column15 = L"";
	m_nFields = 15;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CCheckinSet::GetDefaultConnect()
{
	return _T("DSN=roomMng;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2012;WSID=DAVID-PC;DATABASE=roomMng");
}

CString CCheckinSet::GetDefaultSQL()
{
	return _T("[dbo].[checkintable]");
}

void CCheckinSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Text(pFX, _T("[ƾ֤����]"), column1);
	RFX_Text(pFX, _T("[����]"), column2);
	RFX_Text(pFX, _T("[���֤����]"), column3);
	RFX_Text(pFX, _T("[��ϵ�绰]"), column4);
	RFX_Text(pFX, _T("[�����]"), column5);
	RFX_Text(pFX, _T("[�ͷ�����]"), column6);
	RFX_Double(pFX, _T("[����۸�]"), column7);
	RFX_Date(pFX, _T("[��סʱ��]"), column8);
	RFX_Single(pFX, _T("[ס������]"), column9);
	RFX_Double(pFX, _T("[�޷�]"), column10);
	RFX_Single(pFX, _T("[�ۿ�]"), column11);
	RFX_Double(pFX, _T("[Ӧ���޷�]"), column12);
	RFX_Double(pFX, _T("[Ѻ��]"), column13);
	RFX_Text(pFX, _T("[��ע]"), column14);
	RFX_Text(pFX, _T("[�ͷ�������]"), column15);

}
/////////////////////////////////////////////////////////////////////////////
// CCheckinSet diagnostics

#ifdef _DEBUG
void CCheckinSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCheckinSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


