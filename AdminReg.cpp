// insert.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "AdminReg.h"
#include "afxdialogex.h"
#include "odbcinst.h"
#include "afxdb.h"
#include "stdafx.h"
#include "MFCApplication2.h"
#include "EmployeeManagement.h"
#include "afxdialogex.h"
#include "odbcinst.h"
#include "afxdb.h"
#include <string>
#include "databaseprocess.h"

// insert dialog

IMPLEMENT_DYNAMIC(CAdminReg, CDialogEx)

CAdminReg::CAdminReg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	 
	, m_sAdmin(_T(""))
	, m_sPass(_T(""))
	, m_sConfirmPass(_T(""))

	, m_sUname(_T(""))
{

}

CAdminReg::~CAdminReg()
{
}

void CAdminReg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	 
	DDX_Text(pDX, IDC_ADMIN, m_sAdmin);
	DDX_Text(pDX, IDC_PASS, m_sPass);
	DDX_Text(pDX, IDC_CONFIRM_PASS, m_sConfirmPass);
	DDX_Text(pDX, IDC_USER_NAME, m_sUname);
	 
}


BEGIN_MESSAGE_MAP(CAdminReg, CDialogEx)
 
	ON_BN_CLICKED(IDC_BUTTON1, &CAdminReg::OnBnClickedInsert)
	 
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &CAdminReg::OnDtnDatetimechangeDatetimepicker1)
END_MESSAGE_MAP()


// CAdminReg message handlers


 
CString CAdminReg::GetAdminName()
{
	return m_sAdmin;
}
CString CAdminReg::GetPass()
{
	return m_sPass;
}
CString CAdminReg::GetUserID()
{
	return m_sUname;
}
void CAdminReg::OnBnClickedInsert()
{
	
	UpdateData(TRUE);

	 
	if (m_sAdmin.IsEmpty() || m_sPass.IsEmpty() || m_sConfirmPass.IsEmpty())
	{
		AfxMessageBox(_T("Username and Password cannot be empty"));
		 
	}
	else if (m_sPass.GetLength() < 7)
	{
		AfxMessageBox(_T("Password minimum length should be 8."));
	}
	else if (m_sPass != m_sConfirmPass)
	{
		AfxMessageBox(_T("Password did not Match."));
	}

	else
	{
		CDatabaseProcess* pDBProc = CDatabaseProcess::GetInstance();

		pDBProc->SaveAdmin(this);
	}
	 

	 
} 

void CAdminReg::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
