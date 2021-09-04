
// EmployeeManagement .cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "EmployeeManagement.h"
#include "afxdialogex.h"
#include "odbcinst.h"
#include "afxdb.h"
#include <string>
#include <Cstring>
#include "EmployeeManagementProcess.h"
#include "AdminReg.h"
#include "databaseprocess.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CEmployeeManagement  dialog



CEmployeeManagement::CEmployeeManagement(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION2_DIALOG, pParent)
	, m_sUname(_T(""))
	, m_sPassword(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEmployeeManagement::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	 
    DDX_Text(pDX, IDC_USER_NAME, m_sUname);
	DDX_Text(pDX, IDC_PASSWORD, m_sPassword);
}

BEGIN_MESSAGE_MAP(CEmployeeManagement, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CEmployeeManagement::OnBnClickedLogin)
	//ON_EN_CHANGE(IDC_EDIT1, &CEmployeeManagement::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON4, &CEmployeeManagement::OnBnClickedOpenAdminReg)
	ON_BN_CLICKED(IDOK, &CEmployeeManagement::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CEmployeeManagement::OnBnClickedCancel)
END_MESSAGE_MAP()


// CEmployeeManagement  message handlers

BOOL CEmployeeManagement::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEmployeeManagement::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEmployeeManagement::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEmployeeManagement::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CEmployeeManagement::GetUname()
{
	return m_sUname;
}
CString CEmployeeManagement::GetPassword()
{
	return m_sPassword;
}

void CEmployeeManagement::OnBnClickedLogin()
{
	bool bFlag, bFlag1 = FALSE;
	UpdateData(TRUE);
	CDatabaseProcess* pDBProc = CDatabaseProcess::GetInstance();
	bFlag = pDBProc->Login(this);
	if (m_sUname.IsEmpty() || m_sPassword.IsEmpty())
	{
		AfxMessageBox(_T("Username and Password cannot be empty"));
		bFlag1 = TRUE;
	}
	

	else if (bFlag == FALSE && bFlag1 == FALSE)
	{
		AfxMessageBox(_T("Username and Password did not match.Try again. "));

	}
	else
	{
		EndDialog(IDD_LOGIN_DIALOG);
		CEmployeeManagementProcess d;
		d.DoModal();


	}



}





void CEmployeeManagement::OnBnClickedOpenAdminReg()
{
	// TODO: Add your control notification handler code here
	CAdminReg d;
	d.DoModal();
}




void CEmployeeManagement::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDatabaseProcess* pDBProc = CDatabaseProcess::GetInstance();
	pDBProc->CloseDatabase();
    CDialogEx::OnOK();
}


void CEmployeeManagement::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDatabaseProcess* pDBProc = CDatabaseProcess::GetInstance();
	pDBProc->CloseDatabase();
	CDialogEx::OnCancel();
}
