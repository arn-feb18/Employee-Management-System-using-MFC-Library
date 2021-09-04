#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// insert dialog

class CAdminReg : public CDialogEx
{
	DECLARE_DYNAMIC(CAdminReg)

public:
	CAdminReg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAdminReg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnEnChangeEdit1();
	CString GetAdminName();
	CString GetPass();
	CString GetUserID();


	afx_msg void OnBnClickedInsert();

	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	CDateTimeCtrl m_DTPicker;
	CString m_sAdmin;
	CString m_sPass;
	CString m_sConfirmPass;
	CString m_sUname;
};
#pragma once


// CInsert dialog

class CInsert : public CDialogEx
{
	DECLARE_DYNAMIC(CInsert)

public:
	CInsert(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInsert();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
