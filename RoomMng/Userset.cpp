// Userset.h : Implementation of the CUserset class



// CUserset implementation

// code generated on 2016Äê4ÔÂ25ÈÕ, 0:53

#include "stdafx.h"
#include "Userset.h"
IMPLEMENT_DYNAMIC(CUserset, CRecordset)

CUserset::CUserset(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_user_name = L"";
	m_user_pwd = L"";
	m_nFields = 2;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CUserset::GetDefaultConnect()
{
	return _T("DSN=roomMng;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2012;WSID=DAVID-PC;DATABASE=roomMng");
}

CString CUserset::GetDefaultSQL()
{
	return _T("[dbo].[usertalbe]");
}

void CUserset::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Text(pFX, _T("[user_name]"), m_user_name);
	RFX_Text(pFX, _T("[user_pwd]"), m_user_pwd);

}
/////////////////////////////////////////////////////////////////////////////
// CUserset diagnostics

#ifdef _DEBUG
void CUserset::AssertValid() const
{
	CRecordset::AssertValid();
}

void CUserset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


