
// EmployeeManagement.h : header file
//

#pragma once
#include "afxwin.h"


// CEmployeeManagement dialog
class CEmployeeManagement : public CDialogEx
{
// Construction
public:
	CEmployeeManagement(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG }; 
	//enum { IDD = IDD_LOGIN };
#endif

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
	afx_msg void OnBnClickedLogin();
	//CEdit m_editCtrl;
	//afx_msg void OnEnChangeEdit1();
	//CEdit m_var;
	afx_msg void OnBnClickedOpenAdminReg();
	CString m_sUname;
	CString m_sPassword;
	afx_msg CString GetUname();
	CString GetPassword();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};


#pragma once


