#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "ATLComTime.h"
#include "stdafx.h"
#include "MFCApplication2.h"
#include "afxdialogex.h"
#include "AdminReg.h"
 

class CEmployeeManagementProcess : public CDialogEx
{
	DECLARE_DYNAMIC(CEmployeeManagementProcess)



public:
	CEmployeeManagementProcess(CWnd* pParent = NULL);   // standard constructor

	//CEmployeeManagementProcess & GetInstance();
	virtual ~CEmployeeManagementProcess();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGISTERDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	CDateTimeCtrl m_dDate;
	afx_msg BOOL OnInitDialog();


	 

	//void GetEmployeeInfo();

	CString GetFirstName();
	void SetFirstName(CString sFirstName);

	CString GetLastName();
	void SetLastName(CString sLastName);

	CString GetPost();
	void SetPost(CString sPost);

	void SetAge(int sAge);

	int GetAge();


	CString GetAddress();
	void SetAddress(CString sAddress);

	double GetSalary();
	CString GetDOB();
	void SetSalary(double sSalary);


	void SetDOB(COleDateTime dtDbdate);

	CString GetDept();

	int GetCheckRadio();

	void SetEmployeeID(CString sEmpId);

	void SetGender(CString sGen);

	void SetDepartmentComboBox(CString pCurVal);

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedUpdate();
	void OnBnClickedINSERT();
	afx_msg void OnBnClickedSearch();
	 

	CString m_sFname;

	private:
	CComboBox m_DeptCombo;
	CString m_sLname;
	CString m_sPost;
    COleDateTime m_sdate;
	CString m_sAddress;
    CString m_sEId;
	CString m_sDob;
	CString m_sGen;
    CString m_sDep;
	int m_iCheckRadio;
	//CEmployeeManagementProcess*  opEmpObj;
    int m_DepartmentIndex;
    int m_iAge;
	double m_dSalary;
	int m_Gender;
 
};
