
// RoomMngDlg.h : header file
//

#pragma once


// CRoomMngDlg dialog
class CRoomMngDlg : public CDialogEx
{
// Construction
public:
	CRoomMngDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ROOMMNG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenucheckin();
	afx_msg void OnMenuroomsetting();
	afx_msg void OnBnClickedBtnborrowroom();
	afx_msg void OnMenufindroom();
};
