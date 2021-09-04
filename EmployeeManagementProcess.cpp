// EmployeeManagement.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "EmployeeManagementProcess.h"
#include "afxdialogex.h"
#include "odbcinst.h"
#include "afxdb.h"
#include <string>
#include <TCHAR.h>
#include "databaseprocess.h"
#include "EmployeeManagement.h"


// CEmployeeManagementProcess dialog

IMPLEMENT_DYNAMIC(CEmployeeManagementProcess, CDialogEx)

CEmployeeManagementProcess::CEmployeeManagementProcess(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_REGISTERDLG, pParent)
	 
	, m_sFname(_T(""))
	, m_sLname(_T(""))
	, m_sPost(_T(""))

	, m_sdate(COleDateTime::GetCurrentTime())
	, m_sAddress(_T(""))

	, m_sEId(_T(""))
	, m_iAge(0)
	, m_dSalary(0)
	 
	, m_Gender(0)
{

}




CEmployeeManagementProcess::~CEmployeeManagementProcess()
{
}

void CEmployeeManagementProcess::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dDate);
	DDX_Control(pDX, IDC_COMBO1, m_DeptCombo);
	DDX_Text(pDX, IDC_FIRSTNAME, m_sFname);
	DDX_Text(pDX, IDC_LAST_NAME, m_sLname);
	DDX_Text(pDX, IDC_POST, m_sPost);
	DDX_DateTimeCtrl(pDX, IDC_DOB, m_sdate);
	DDX_Text(pDX, IDC_ADDRESS, m_sAddress);
	DDX_Text(pDX, IDC_EMPLOYEE_ID, m_sEId);
	DDX_Text(pDX, IDC_AGE, m_iAge);
	DDX_Text(pDX, IDC_SALARY, m_dSalary);
    DDX_Radio(pDX, IDC_RADIO1, m_Gender);
}


BEGIN_MESSAGE_MAP(CEmployeeManagementProcess, CDialogEx)
	ON_BN_CLICKED(IDC_INSERT, &CEmployeeManagementProcess::OnBnClickedINSERT)
	ON_BN_CLICKED(IDC_Search, &CEmployeeManagementProcess::OnBnClickedSearch)

	ON_BN_CLICKED(IDC_Update, &CEmployeeManagementProcess::OnBnClickedUpdate)
	ON_BN_CLICKED(IDOK, &CEmployeeManagementProcess::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CEmployeeManagementProcess::OnBnClickedCancel)
	 
END_MESSAGE_MAP()


// CEmployeeManagementProcess message handlers
BOOL CEmployeeManagementProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString sDepartment;

	sDepartment.Format(_T("PopHealth"));
	m_DeptCombo.AddString(sDepartment);
	sDepartment.Format(_T("CareInsightDelivery"));
	m_DeptCombo.AddString(sDepartment);
	sDepartment.Format(_T("MedicationRecordDev"));
	m_DeptCombo.AddString(sDepartment);
	sDepartment.Format(_T("ClinicalSolutionsDev"));
	m_DeptCombo.AddString(sDepartment);
	sDepartment.Format(_T(""));
	m_DeptCombo.AddString(sDepartment);
	m_DeptCombo.SetCurSel(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}




 


CString CEmployeeManagementProcess::GetFirstName()
{
	return m_sFname;
}
void CEmployeeManagementProcess::SetFirstName(CString sFirstName)
{
	m_sFname = sFirstName;
}
CString CEmployeeManagementProcess::GetLastName()
{
	return m_sLname;
}
void CEmployeeManagementProcess::SetLastName(CString sLastName)
{
	m_sLname = sLastName;
}
CString CEmployeeManagementProcess::GetPost()
{
	return m_sPost;
}
void CEmployeeManagementProcess::SetPost(CString sPost)
{
	m_sPost = sPost;
}

int CEmployeeManagementProcess::GetAge()
{
	return m_iAge;
}
void CEmployeeManagementProcess::SetAge(int sAge)
{
	m_iAge = sAge;
}
CString CEmployeeManagementProcess::GetAddress()
{
	return m_sAddress;
}
void CEmployeeManagementProcess::SetAddress(CString sAddress)
{
	m_sAddress = sAddress;
}
double CEmployeeManagementProcess::GetSalary()
{
	return m_dSalary;
}
void CEmployeeManagementProcess::SetSalary(double dSalary)
{
	m_dSalary = dSalary;
}
CString CEmployeeManagementProcess::GetDOB()
{
	return m_sDob;
}
void CEmployeeManagementProcess::SetDOB(COleDateTime dtDbdate)
{
	m_sdate = dtDbdate;
}
CString CEmployeeManagementProcess::GetDept()
{
	return m_sDep;
}
int CEmployeeManagementProcess::GetCheckRadio()
{
	return m_Gender;
}
void CEmployeeManagementProcess::SetDepartmentComboBox(CString pCurVal)
{
	m_DepartmentIndex = _ttoi(pCurVal);

}

void CEmployeeManagementProcess::SetEmployeeID(CString sEmpId)
{
	m_sEId = sEmpId;
}

void CEmployeeManagementProcess::SetGender(CString sGen)
{
	m_sGen = sGen;
}

void CEmployeeManagementProcess::OnBnClickedINSERT()
{
	//m_iCheckRadio = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO2);
    CString sGen = _T("");

	m_dDate.GetWindowTextW(m_sDob);
	CString sDob = m_sDob;
	m_DeptCombo.GetLBText(m_DeptCombo.GetCurSel(), m_sDep);

	UpdateData(TRUE);
	COleDateTime  dCurrentDate;
	 
	dCurrentDate = COleDateTime::GetCurrentTime();
	int iCurrYear = dCurrentDate.GetYear();
	int sYear,Lyear = 2004;
	sYear =  _ttoi(sDob.Right(4));
	CString sYearr = (sDob.Right(4));
	 
	 
	if (m_sFname == _T("") || m_sLname == _T("")|| m_sDep == _T("") || m_sPost == _T("")  )
	{
		AfxMessageBox(_T("Mandatory Fields cannot be empty. "));
	}
	else if ( 1870 > sYear > 2004)
	{
		AfxMessageBox(_T("DOB invalid."));
	}
	else
		{
		CDatabaseProcess* pDBProc = CDatabaseProcess::GetInstance();

		pDBProc->SaveEmployeeInfo(this);
	 }
    

}

void CEmployeeManagementProcess::OnBnClickedSearch()
{
    UpdateData(TRUE);
    CDatabaseProcess* pDBProc = CDatabaseProcess::GetInstance();
	pDBProc->GetEmployeeInfo(this);
    UpdateData(FALSE);
	m_DeptCombo.SetCurSel(m_DepartmentIndex);
	if(m_sGen=="Male")
    CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
	else
	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
	
}



void CEmployeeManagementProcess::OnBnClickedUpdate()
{
	//m_iCheckRadio = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO2);
	m_DeptCombo.GetLBText(m_DeptCombo.GetCurSel(), m_sDep);
	m_dDate.GetWindowTextW(m_sDob);
	CString sDob = m_sDob;
	UpdateData(TRUE);
    CDatabaseProcess* pDBProc = CDatabaseProcess::GetInstance();
	pDBProc->UpdateEmployeeInfo(this);


}


void CEmployeeManagementProcess::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	EndDialog(IDD_LOGIN_DIALOG);
	CEmployeeManagement d;
	d.DoModal();
	CDatabaseProcess* pDBProc = CDatabaseProcess::GetInstance();
	pDBProc->CloseDatabase();
	
	CDialogEx::OnOK();
}


void CEmployeeManagementProcess::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDatabaseProcess* pDBProc = CDatabaseProcess::GetInstance();
	pDBProc->CloseDatabase();
	CDialogEx::OnCancel();
}


 
