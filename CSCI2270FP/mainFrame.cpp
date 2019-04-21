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

void CMyForm::resetEditFields() {
	SetDlgItemText(IDC_FIRSTNAMEEDIT, "");
	SetDlgItemText(IDC_LASTNAMEEDIT, "");
	SetDlgItemText(IDC_PhoneEdit, "");
	SetDlgItemText(IDC_ADDRESSEDIT, "");
	SetDlgItemText(IDC_EMAILEDIT, "");
}


void CMyForm::OnBnClickedButtonOne() {
	//To be: Search
	TRACE0("BUTTON1 PRESSED");
	CString str;
	CString number;
	GetDlgItemText(IDC_USEREDIT_SEARCH, str);
	SetDlgItemText(IDC_USEREDIT_SEARCH, "");
	MessageBox(str); //DEBUG
	std::string searchContact = (LPCSTR)str;
	iCloud.search(searchContact);

	str = "Here are the Search Results: \r\n";

	for (int i = 0; i < iCloud.getSearchResults().size(); i++) {
		Contact* node = iCloud.getSearchResults()[i];
		number.Format("Search Result Number %d :\r\n", i + 1);
		str = str + number + _T("\r\n") + node->firstName.c_str();
		str = str + _T(" ") + node->lastName.c_str();
		str = str + _T("\r\n") + node->phoneNumber.c_str();
		str = str + _T("\r\n") + node->birthdate.c_str();
		str = str + _T("\r\n") + node->address.c_str();
		str = str + _T("\r\n") + node->email.c_str();
		str = str + _T("\r\n");

		MessageBox(str);
	}

	hasSearched = true;
	SetDlgItemText(IDC_MAIN_DISPLAY, str);
}


void CMyForm::OnBnClickedButtonTwo() {
	//Add to Contacts
	TRACE0("BUTTON2 PRESSED // CONTACTS ADDING");
	CString str;

	//Get info from Edits
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

	//Get and store values
	if (!hasSelected) {
		TRACE0("ADDING NEW CONTACT");
		//Create Contact
		iCloud.createContact(fName, lName, pNum, bDay, addR, eMail);

		//Display added (temporary, testing)
		iCloud.search(fName);

		Contact* node = iCloud.getSearchResults()[0];
		str = node->firstName.c_str();
		str = str + _T("\r\n") + node->lastName.c_str();
		str = str + _T("\r\n") + node->phoneNumber.c_str();
		str = str + _T("\r\n") + node->birthdate.c_str();
		str = str + _T("\r\n") + node->address.c_str();
		str = str + _T("\r\n") + node->email.c_str();

		TRACE0(str);

		SetDlgItemText(IDC_MAIN_DISPLAY, str);
	}
	else if (hasSearched == true && hasSelected == true && index > -1) {
		if (index < iCloud.getSearchResults().size()) {
			TRACE0("EDITING A CONTACT!");
			Contact* node = iCloud.getSearchResults()[index];
			str.Format(node->firstName.c_str());
			AfxMessageBox(str);

			iCloud.editContact(node, fName, lName, pNum, bDay, addR, eMail);

			str.Format(_T("%d"), index);
			AfxMessageBox(str);

			//For Debugging, Delete Below Later
			str = node->firstName.c_str();
			str = str + _T("\r\n") + node->lastName.c_str();
			str = str + _T("\r\n") + node->phoneNumber.c_str();
			str = str + _T("\r\n") + node->birthdate.c_str();
			str = str + _T("\r\n") + node->address.c_str();
			str = str + _T("\r\n") + node->email.c_str();

			SetDlgItemText(IDC_MAIN_DISPLAY, str);
			str.Format("Add to Contacts!");
			GetDlgItem(IDC_BUTTON_TWO)->SetWindowText(str);
			hasSearched = false;
			hasSelected = false;
		}
		else {
			SetDlgItemText(IDC_MAIN_DISPLAY, "CANNOT EDIT");
		}
	}
	
	TRACE0("RESET INPUT TO EMPTY");
	resetEditFields();
}

void CMyForm::OnBnClickedButtonThree() {
	TRACE0("BUTTON THREE //EDIT");
	CString str;
	GetDlgItemText(IDC_NUMBEREDIT, str);
	std::string selected_num = (LPCSTR)str;
	index = -1;
	try {
		index = stoi(selected_num);
		index -= 1;
	}
	catch (...) {
		MessageBox("You need to put in a value greater than 0!");
		index = -1;
	}
	//Get/Populate values
	if (hasSearched && index > -1) {
		Contact* node = iCloud.getSearchResults()[index];
		SetDlgItemText(IDC_FIRSTNAMEEDIT, node->firstName.c_str());
		SetDlgItemText(IDC_LASTNAMEEDIT, node->lastName.c_str());
		SetDlgItemText(IDC_PhoneEdit, node->phoneNumber.c_str());
		SetDlgItemText(IDC_BIRTHDATEPICK, node->birthdate.c_str());
		SetDlgItemText(IDC_ADDRESSEDIT, node->address.c_str());
		SetDlgItemText(IDC_EMAILEDIT, node->email.c_str());

		str.Format("Edit Contact!");
		GetDlgItem(IDC_BUTTON_TWO)->SetWindowText(str);
		hasSearched = true;
		hasSelected = true;
	}
	else {
		SetDlgItemText(IDC_FIRSTNAMEEDIT, "PLEASE");
		SetDlgItemText(IDC_LASTNAMEEDIT, "SEARCH");
		SetDlgItemText(IDC_PhoneEdit, "A");
		SetDlgItemText(IDC_ADDRESSEDIT, "PERSON");
		SetDlgItemText(IDC_EMAILEDIT, "FIRST");
	}

	SetDlgItemText(IDC_NUMBEREDIT, "");
}

void CMyForm::OnBnClickedButtonFour() {

}

void CMyForm::OnBnClickedButtonFive() {

}

void CMyForm::OnBnClickedButtonSix() {

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
	ON_BN_CLICKED(IDC_BUTTON_THREE, &CMyForm::OnBnClickedButtonThree)
	ON_BN_CLICKED(IDC_BUTTON_FOUR, &CMyForm::OnBnClickedButtonFour)
	ON_BN_CLICKED(IDC_BUTTON_FIVE, &CMyForm::OnBnClickedButtonFive)
	ON_BN_CLICKED(IDC_BUTTON_SIX, &CMyForm::OnBnClickedButtonSix)
END_MESSAGE_MAP()