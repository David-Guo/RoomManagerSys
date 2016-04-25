// RoominfoSet.h : Implementation of the CRoominfoSet class



// CRoominfoSet implementation

// code generated on 2016年4月25日, 17:19

#include "stdafx.h"
#include "RoominfoSet.h"
IMPLEMENT_DYNAMIC(CRoominfoSet, CRecordset)

CRoominfoSet::CRoominfoSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	column1 = L"";
	column2 = L"";
	column3 = 0.0;
	column4 = L"";
	column5 = L"";
	m_nFields = 5;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CRoominfoSet::GetDefaultConnect()
{
	return _T("DSN=roomMng;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2012;WSID=DAVID-PC;DATABASE=roomMng");
}

CString CRoominfoSet::GetDefaultSQL()
{
	return _T("[dbo].[roomsetting]");
}

void CRoominfoSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Text(pFX, _T("[房间号]"), column1);
	RFX_Text(pFX, _T("[房间类型]"), column2);
	RFX_Double(pFX, _T("[价格]"), column3);
	RFX_Text(pFX, _T("[房态]"), column4);
	RFX_Text(pFX, _T("[设备配置]"), column5);

}
/////////////////////////////////////////////////////////////////////////////
// CRoominfoSet diagnostics

#ifdef _DEBUG
void CRoominfoSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRoominfoSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


