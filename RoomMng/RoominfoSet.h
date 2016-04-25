// RoominfoSet.h : Declaration of the CRoominfoSet

#pragma once

// code generated on 2016Äê4ÔÂ25ÈÕ, 17:19

class CRoominfoSet : public CRecordset
{
public:
	CRoominfoSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRoominfoSet)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	CStringW	column1;
	CStringW	column2;
	double	column3;
	CStringW	column4;
	CStringW	column5;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


