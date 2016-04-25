// CheckinSet.h : Declaration of the CCheckinSet

#pragma once

// code generated on 2016Äê4ÔÂ25ÈÕ, 15:05

class CCheckinSet : public CRecordset
{
public:
	CCheckinSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCheckinSet)

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
	CStringW	column3;
	CStringW	column4;
	CStringW	column5;
	CStringW	column6;
	double	column7;
	CTime	column8;
	float	column9;
	double	column10;
	float	column11;
	double	column12;
	double	column13;
	CStringW	column14;
	CStringW	column15;

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


