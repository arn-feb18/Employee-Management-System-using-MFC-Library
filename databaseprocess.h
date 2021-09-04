#pragma once
#include "stdafx.h"
#include "afxdialogex.h"
#include "odbcinst.h"
#include "afxdb.h"
#include <string>
#include <TCHAR.h>
#include "EmployeeManagementProcess.h"
#include "EmployeeManagement.h"
class CDatabaseProcess
{
private:

	CDatabaseProcess();

	CDatabase m_databse;
public:
	static CDatabaseProcess* m_pDb;
	
	static  CDatabaseProcess* GetInstance();
	void CloseDatabase();
	bool Login(CEmployeeManagement* pLoginObj);
	void SaveAdmin(CAdminReg * pInsertObj);
	void SaveEmployeeInfo(CEmployeeManagementProcess * pEmpObj);
	void GetEmployeeInfo(CEmployeeManagementProcess* pEmpObj);
	void UpdateEmployeeInfo(CEmployeeManagementProcess * pEmpObj);
	 
};