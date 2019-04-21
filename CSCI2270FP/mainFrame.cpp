#include <afxwin.h>
#include <cstring>
#include <string>
#include <vector>
#include "mainFrame.h"
#include "Contacts.h"
#include "resource.h"
#include "CMainDlg.h"

void CMyApp::OnMenuExit() {
	PostQuitMessage(0);
}

BOOL CMyWindow::PreCreateWindow(CREATESTRUCT& cs) {
	//Sets window style before showing to user
	cs.cy = ::GetSystemMetrics(SM_CYSCREEN) / 3;
	cs.cx = ::GetSystemMetrics(SM_CXSCREEN) / 3;
	cs.y = ((cs.cy * 3) - cs.cy) / 2;
	cs.x = ((cs.cx * 3) - cs.cx) / 2;

	m_strTitle = "Happy Contacts!";

	return CFrameWnd::PreCreateWindow(cs);
}

int CMyWindow::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1) {
		return -1;
	}

	CCreateContext ccx;
	ccx.m_pNewViewClass = RUNTIME_CLASS(CMyForm);
	m_pMainView = DYNAMIC_DOWNCAST(CMyForm, this->CreateView(&ccx));

	if (m_pMainView == NULL) {
		TRACE0("Form View Creation Failed!\n");
	}

	RecalcLayout();
	m_pMainView->ShowWindow(SW_SHOW);
	m_pMainView->OnInitialUpdate();
	SetActiveView(m_pMainView);
	m_pMainView->ResizeParentToFit(FALSE);

	return 0;
}

CMyForm::CMyForm() : CFormView(CMyForm::IDD) {

}

CMyForm::~CMyForm() {
	//Left Blank
}

void CMyForm::OnBnClickedButtonOne() {
	//To be: Search
	TRACE0("BUTTON1 PRESSED");
	CString str;
	GetDlgItemText(IDC_USEREDIT_SEARCH, str);
	SetDlgItemText(IDC_USEREDIT_SEARCH, "");
	SetDlgItemText(IDC_MAIN_DISPLAY, str);
}


void CMyForm::OnBnClickedButtonTwo() {
	//Add to Contacts
	TRACE0("BUTTON2 PRESSED // CONTACTS ADDING");
	CString str;

	//Get and store values
	GetDlgItemText(IDC_FIRSTNAMEEDIT, str);
	std::string fName = (LPCSTR)str;

	GetDlgItemText(IDC_LASTNAMEEDIT, str);
	std::string lName = (LPCSTR)str;

	GetDlgItemText(IDC_PhoneEdit, str);
	std::string pNum = (LPCSTR)str;

	GetDlgItemText(IDC_BIRTHDATEPICK, str);
	std::string bDay = (LPCSTR)str;

	GetDlgItemText(IDC_ADDRESSEDIT, str);
	std::string addR = (LPCSTR)str;

	GetDlgItemText(IDC_EMAILEDIT, str);
	std::string eMail = (LPCSTR)str;

	//Create Contact
	iCloud.createContact(fName, lName, pNum, bDay, addR, eMail);
	TRACE0("ADDED NEW CONTACT");

	//Set Inputs to empty
	SetDlgItemText(IDC_FIRSTNAMEEDIT, "");
	SetDlgItemText(IDC_LASTNAMEEDIT, "");
	SetDlgItemText(IDC_PhoneEdit, "");
	SetDlgItemText(IDC_ADDRESSEDIT, "");
	SetDlgItemText(IDC_EMAILEDIT, "");

	//Display added (temporary, testing)
	iCloud.search(fName);

	str = iCloud.getSearchResults()[0]->c->firstName.c_str();
	str = str + _T("\r\n") + iCloud.getSearchResults()[0]->c->lastName.c_str();
	str = str + _T("\r\n") + iCloud.getSearchResults()[0]->c->phoneNumber.c_str();
	str = str + _T("\r\n") + iCloud.getSearchResults()[0]->c->birthdate.c_str();
	str = str + _T("\r\n") + iCloud.getSearchResults()[0]->c->address.c_str();
	str = str + _T("\r\n") + iCloud.getSearchResults()[0]->c->email.c_str();

	TRACE0(str);

	SetDlgItemText(IDC_MAIN_DISPLAY, str);
	
	TRACE0("RESET INPUT TO EMPTY");
}


//Frame Map
IMPLEMENT_DYNCREATE(CMyWindow, CFrameWnd)
BEGIN_MESSAGE_MAP(CMyWindow, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

//Form View Map
IMPLEMENT_DYNCREATE(CMyForm, CFormView)
BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_ONE, &CMyForm::OnBnClickedButtonOne)
	ON_BN_CLICKED(IDC_BUTTON_TWO, &CMyForm::OnBnClickedButtonTwo)
END_MESSAGE_MAP()