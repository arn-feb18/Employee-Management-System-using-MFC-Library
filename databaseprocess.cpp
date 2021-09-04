#include "stdafx.h"
#include "databaseprocess.h"
#include "EmployeeManagementProcess.h"
#include "stdafx.h"
#include "MFCApplication2.h"
#include "afxdialogex.h"
#include "odbcinst.h"
#include "afxdb.h"
#include <string>
#include <TCHAR.h>
#include "GetDepartment.h" 
#include "EmployeeManagement.h" 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDatabaseProcess* CDatabaseProcess::m_pDb = NULL;

CDatabaseProcess::CDatabaseProcess()
{

	CString sDriver = L"MICROSOFT ACCESS DRIVER (*.mdb)";
	CString sDsn;
	CString sFile = L"C:\\Users\\AR078355\\Documents\\Database11.mdb";

	sDsn.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s", sDriver, sFile);
	TRY{
		// Open the database
		m_databse.Open(NULL,false,false,sDsn);
	}
		CATCH(CDBException, e) {
		// If a database exception occured, show error msg
		AfxMessageBox(L"Database error: ");
	}
	END_CATCH;

}

CDatabaseProcess* CDatabaseProcess::GetInstance()
{
	if (m_pDb == NULL)
	{
		m_pDb = new CDatabaseProcess();
	}

	return m_pDb;
}

void CDatabaseProcess::CloseDatabase()
{

	m_databse.Close();
}
bool CDatabaseProcess::Login(CEmployeeManagement* pLoginObj)
{
	if (pLoginObj == NULL)
		return 0;
	CString sUname, sPassword, sName, sPass;
	CString SqlString;
	sUname = pLoginObj->GetUname();
	sPassword = pLoginObj->GetPassword();
	CRecordset recset(&m_databse);

	// Build the SQL statement
	//SqlString = "SELECT * FROM Login";
	SqlString.Format(_T("SELECT * FROM Login WHERE `Username`='%s' AND `Password`='%s'"), sUname, sPassword);
	// Execute the query
	CT2CA tempString2(SqlString);
	std::string query2(tempString2);
	m_databse.ExecuteSQL(SqlString);
	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);


	if (!recset.IsEOF())
	{

		// Copy each column into a variable
		//recset.GetFieldValue(L"ID",strID);
		recset.GetFieldValue(L"Username", sName);
		recset.GetFieldValue(L"Password", sPass);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
void CDatabaseProcess::SaveAdmin(CAdminReg* pInsertObj)
{
	if (pInsertObj == NULL)
		return;
	CString sPass  ;
	CString sUname;
	CString sAname  ;
	sPass = pInsertObj->GetPass();
	sUname = pInsertObj->GetUserID();
	sAname = pInsertObj->GetAdminName();
	CString strQuery;
	strQuery.Format(_T("INSERT INTO Login(`Username`, `Password`,`AName`) VALUES ('%s', '%s','%s')"), sUname, sPass, sAname);
	CT2CA tempString(strQuery);
	std::string query(tempString);
	m_databse.ExecuteSQL(strQuery);
	 
}

void CDatabaseProcess::SaveEmployeeInfo(CEmployeeManagementProcess* pEmpObj)
{
	if (pEmpObj == NULL)
		return;

	CString sFName;
	CString sLastName;
	CString sPost;
	//int sAge;
	CString sAddress = _T("");;
	double dSalary;
	CString sDob;
	CString sComboDep;
	int iCheckRadio ;

	sFName = pEmpObj->GetFirstName();
	sLastName = pEmpObj->GetLastName();
	sPost = pEmpObj->GetPost();
	 
	sAddress = pEmpObj->GetAddress();
	dSalary = pEmpObj->GetSalary();
	sDob = pEmpObj->GetDOB();
	sComboDep = pEmpObj->GetDept();
	iCheckRadio = pEmpObj->GetCheckRadio();

	CString SqlString;
	CString  strName, strAge;
	CString strID;

	CMapping1& omap = CMapping1::CMapping1();
	static CMapStringToString&  myMAP = omap.GetMap();
	CMapStringToString::CPair *pCurVal;
	pCurVal = myMAP.PGetFirstAssoc();
	TRY{
		// Open the database
	// database.Open(NULL,false,false,sDsn);
	CString sGen=_T("");
	CString strQuery;
	CString strQuery1;


	int iDeptId;
	while (pCurVal != NULL)
	{
		//AfxMessageBox(pCurVal->key);
		//AfxMessageBox(pCurVal->value);
		//iDeptId = _ttoi(pCurVal->key);
		if (pCurVal->value == sComboDep)
		{
			
			iDeptId = _ttoi(pCurVal->key);

			break;
		} 
		pCurVal = myMAP.PGetNextAssoc(pCurVal);
	}

	strQuery.Format(_T("INSERT INTO Employee(`EFirstName`,`ELastName`,`Post`,`DepartmentId`   ) VALUES ('%s','%s','%s',%d  )"), sFName, sLastName, sPost, iDeptId);

	//strQuery.Format(_T("INSERT INTO Employee(`EFirstName`,`ELastName`,`Post`  ) VALUES ('%s','%s','%s'  )"), m_sFname, m_sLname, m_sPost);
	CT2CA tempString(strQuery);
	std::string query(tempString);
	m_databse.ExecuteSQL(strQuery);

	CRecordset recset(&m_databse);
	SqlString = "SELECT TOP 1 * FROM Employee ORDER BY EmpId DESC ";
	recset.Open(CRecordset::forwardOnly, SqlString);
	recset.GetFieldValue(L"EmpId", strID);

	if (iCheckRadio == 0)
	{
		sGen = _T("Male");

	}


	else if( iCheckRadio == 1)
	{
		sGen = _T("Female");
	}

		strQuery.Format(_T("INSERT INTO EmpPrsnl(`EmpId`,`Gender`,`DOB` ,`Address` ) VALUES ('%s','%s' ,'%s' ,'%s'  )"), strID, sGen, sDob, sAddress);
		CT2CA tempString4(strQuery);
		std::string query4(tempString4);
		m_databse.ExecuteSQL(strQuery);



	strQuery.Format(_T("INSERT INTO Salary(`Empid`,`Salary`) VALUES ('%s',%lf)"),strID, dSalary);
	CT2CA tempString2(strQuery);
	std::string query2(tempString2);
	m_databse.ExecuteSQL(strQuery);

	// Close the database
	//database.Close();
	}CATCH(CDBException, e) {
		// If a database exception occured, show error msg
		AfxMessageBox(L"Database error: ");
	}
	END_CATCH;
	// TODO: Add your control notification handler code here

}


void CDatabaseProcess::GetEmployeeInfo(CEmployeeManagementProcess* pEmpObj)
{

	if (pEmpObj == NULL)
		return;
	CString SqlString, SqlString2;

	CMapping1& omap = CMapping1::CMapping1();
	static CMapStringToString&  myMAP = omap.GetMap();
	CMapStringToString::CPair *pCurVal;
	pCurVal = myMAP.PGetFirstAssoc();
	int iRec = 0;


	CRecordset recset(&m_databse);


	// Build the SQL statement
	SqlString = "SELECT * FROM Employee";

	// Execute the query

	recset.Open(CRecordset::forwardOnly, SqlString);
	CString sdbFirstName;
	CString  sdbDeptID;
	CString  sdbLastName;
	CString  sdbPost;
	CString  sdbEid;
	CString  dbsDob;
	COleDateTime  dtDbdate;
	CString  dbsGen;
	CString  dbsAge;
	CString dbsAddress;
	CString  sdbSalary;
	COleDateTime dCurrentDate;

	int ii = 1;
	int inTokenPos = 0;
	CString newdate = (_T(""));
	// Loop through each record


	while (!recset.IsEOF()) {
		recset.GetFieldValue(L"EFirstName", sdbFirstName);
		recset.GetFieldValue(L"ELastName", sdbLastName);
		recset.GetFieldValue(L"Post", sdbPost);
		recset.GetFieldValue(L"DepartmentId", sdbDeptID);
		recset.GetFieldValue(L"EmpId", sdbEid);

		if (pEmpObj->m_sFname == sdbFirstName)
		{

			pEmpObj->SetFirstName(sdbFirstName);
			pEmpObj->SetLastName(sdbLastName);
			pEmpObj->SetPost(sdbPost);
			pEmpObj->SetEmployeeID(sdbEid);



			while (pCurVal != NULL)
			{
				//AfxMessageBox(pCurVal->key+ m_sdbDeptID);
				if (pCurVal->key == sdbDeptID)
				{


					pEmpObj->SetDepartmentComboBox(pCurVal->key);

					break;
				}
				pCurVal = myMAP.PGetNextAssoc(pCurVal);
			}

			break;
		}
		recset.MoveNext();
	}

	CRecordset recset1(&m_databse);
	CString sDob;
	CString SqlString1 = _T("");


	CString sEmpId, sEmpId1;
	CString str, str1;
	dCurrentDate = COleDateTime::GetCurrentTime();
	int dCurrYear = dCurrentDate.GetYear();
	int iMyDate, iAge;
	SqlString1 = "SELECT * FROM EmpPrsnl";
	recset1.Open(CRecordset::forwardOnly, SqlString1);
	while (!recset1.IsEOF()) {
		recset1.GetFieldValue(L"DOB", dbsDob);
		recset1.GetFieldValue(L"Gender", dbsGen);
		//recset1.GetFieldValue(L"Age", dbsAge);
		recset1.GetFieldValue(L"Address", dbsAddress);
		recset1.GetFieldValue(L"EmpId", sEmpId);
		if (sdbEid == sEmpId)
		{
			dbsDob.Replace(_T("00:00:00"), _T(""));
			dtDbdate.ParseDateTime(dbsDob);


			pEmpObj->SetDOB(dtDbdate);
			iMyDate = dtDbdate.GetYear();
			iAge = dCurrYear - iMyDate;

			pEmpObj->SetAge(iAge);

			pEmpObj->SetAddress(dbsAddress);
			pEmpObj->SetGender(dbsGen);

			break;

		}
		recset1.MoveNext();
	}

	CRecordset recset2(&m_databse);
	SqlString2 = "SELECT * FROM Salary";
	recset2.Open(CRecordset::forwardOnly, SqlString2);
	while (!recset2.IsEOF()) {
		recset2.GetFieldValue(L"Salary", sdbSalary);
		recset2.GetFieldValue(L"EmpId", sEmpId1);
		if (sdbEid == sEmpId1)
		{
			//m_sSalary = sSalary;
			pEmpObj->SetSalary(_ttof(sdbSalary));

		}
		recset2.MoveNext();

	}
	//database.Close();

}

void CDatabaseProcess::UpdateEmployeeInfo(CEmployeeManagementProcess* pEmpObj)
{
	if (pEmpObj == NULL)
		return;
	CString sFName;
	CString sLastName;
	CString sPost;
	CString sAddress;
	double dSalary;
	CString sDob;
	CString sComboDep;
	int iCheckRadio;

	sFName = pEmpObj->GetFirstName();
	sLastName = pEmpObj->GetLastName();
	sPost = pEmpObj->GetPost();

	sAddress = pEmpObj->GetAddress();
	dSalary = pEmpObj->GetSalary();
	sDob = pEmpObj->GetDOB();
	sComboDep = pEmpObj->GetDept();
	iCheckRadio = pEmpObj->GetCheckRadio();

	CString sGen;
	int iDeptId;
	CString strQuery, strQuery1;
	CString strQuery2;
	CString  SqlString1;
	CString SqlString2, SqlString4;

	CMapping1& omap = CMapping1::CMapping1();
	static CMapStringToString&  myMAP = omap.GetMap();
	CMapStringToString::CPair *pCurVal;
	pCurVal = myMAP.PGetFirstAssoc();
	TRY{

	CString sFirstName, sLname;
	CString sEmp;
	CRecordset recset2(&m_databse);
	CRecordset recset1(&m_databse);
	CRecordset recset(&m_databse);
	SqlString1.Format(_T("SELECT * FROM Employee WHERE EFirstName='%s' AND ELastName='%s'"), sFName, sLastName);

	recset1.Open(CRecordset::forwardOnly, SqlString1);
	recset1.GetFieldValue(L"EmpId", sEmp);
	if (sEmp == "")
	{
		AfxMessageBox(_T("No Records Found"));
	}
	if (sPost == _T(""))
	{
		recset1.GetFieldValue(L"Post", sPost);
	}

	CString sDepartment;

	if (sComboDep != _T(""))
	{


		while (pCurVal != NULL)
		{

			if (pCurVal->value == sComboDep)
			{

				iDeptId = _ttoi(pCurVal->key);

				break;
			}
			pCurVal = myMAP.PGetNextAssoc(pCurVal);
		}


	}
	else
	{
		recset1.GetFieldValue(L"DepartmentId", sDepartment);
		iDeptId = _ttoi(sDepartment);
	}

	SqlString2.Format(_T("SELECT * FROM EmpPrsnl WHERE EmpId=%d"), _ttoi(sEmp));
	recset.Open(CRecordset::forwardOnly, SqlString2);

	if (sAddress == _T(""))
	{
		recset.GetFieldValue(L"Address", sAddress);
	}



	if (iCheckRadio == 0)
	{
		sGen = _T("Male");
	}


	else if (iCheckRadio == 1)
	{

		sGen = _T("Female");
	}

	else
	{
		recset.GetFieldValue(L"Gender", sGen);
	}
		COleDateTime  dCurrentDate;
		CString sYear,sYear1;
		dCurrentDate = COleDateTime::GetCurrentTime();
		int iCurrYear = dCurrentDate.GetYear();
		sYear = sDob.Right(4);
		sYear1.Format(_T("%d"), iCurrYear);


		if (sYear1 == sYear)
		{
			recset.GetFieldValue(L"DOB", sDob);
		}
		CString sSalary;
		SqlString2.Format(_T("SELECT * FROM Salary WHERE EmpId=%d"), _ttoi(sEmp));
		recset2.Open(CRecordset::forwardOnly, SqlString2);
		if (dSalary == 0)
		{
			recset2.GetFieldValue(L"Salary", sSalary);
			dSalary = _ttoi(sSalary);
		}

		 strQuery.Format(_T("UPDATE  EmpPrsnl SET `DOB`='%s',`Gender`='%s' ,`Address`='%s'   WHERE `EmpId`=%d "), sDob, sGen, sAddress,_ttoi(sEmp));
		CT2CA tempString(strQuery);
		std::string query(tempString);
		m_databse.ExecuteSQL(strQuery);

		strQuery1.Format(_T("UPDATE Employee SET `Post`='%s',`DepartmentId`=%d   WHERE `EmpId`=%d "),sPost, iDeptId,  _ttoi(sEmp));
		m_databse.ExecuteSQL(strQuery1);

		strQuery2.Format(_T("UPDATE Salary  SET  `Salary`=%d WHERE `EmpId`=%d "),  dSalary, _ttoi(sEmp));
		CT2CA tempString2(strQuery2);
		std::string query2(tempString2);
		m_databse.ExecuteSQL(strQuery2);
		// Close the database

	//	database.Close();


	}CATCH(CDBException, e) {
		// If a database exception occured, show error msg
		AfxMessageBox(_T("Database error: ") );
	}
	END_CATCH;
}
