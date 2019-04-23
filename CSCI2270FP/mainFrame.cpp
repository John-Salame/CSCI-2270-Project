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
	ccx.m_pNewViewClass = RUNTIME_CLASS(CMyForm); //Get run time structure of CMyForm
	m_pMainView = DYNAMIC_DOWNCAST(CMyForm, this->CreateView(&ccx)); //Downcast

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
	//Reset edit text bars
	SetDlgItemText(IDC_FIRSTNAMEEDIT, "");
	SetDlgItemText(IDC_LASTNAMEEDIT, "");
	SetDlgItemText(IDC_PhoneEdit, "");
	SetDlgItemText(IDC_BIRTHDATEPICK, "1/1/2011");
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
	std::string searchContact = (LPCSTR)str;
	iCloud.search(searchContact);

	str = "Here are the Search Results: \r\n";

	for (int i = 0; i < iCloud.getSearchResults().size(); i++) {
		Contact* node = iCloud.getSearchResults()[i];
		number.Format("Search Result Number %d :\r\n", i + 1);
		str = str + number + node->firstName.c_str();
		str = str + _T(" ") + node->lastName.c_str();
		str = str + _T("\r\n") + node->phoneNumber.c_str();
		str = str + _T("\r\n") + node->birthdate.c_str();
		str = str + _T("\r\n") + node->address.c_str();
		str = str + _T("\r\n") + node->email.c_str();
		str = str + _T("\r\n\r\n");
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

			iCloud.editContact(node, fName, lName, pNum, bDay, addR, eMail);

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
			str.Format("---");
			GetDlgItem(IDC_BUTTON_DELETE)->SetWindowText(str);
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
	//Select From Search
	TRACE0("BUTTON THREE //EDIT");
	CString str;
	GetDlgItemText(IDC_NUMBEREDIT, str);
	std::string selected_num = (LPCSTR)str;
	index = -1;
	//Redundant block, already prevents negatives and non numerical
	//Delete later
	try {
		index = stoi(selected_num);
		index -= 1;
	}
	catch (...) {
		MessageBox("You need to put in a value greater than 0!");
		index = -1;
	}

	//Get/Populate values
	if (hasSearched && index > -1 && index < iCloud.getSearchResults().size()) {
		Contact* node = iCloud.getSearchResults()[index];
		SetDlgItemText(IDC_FIRSTNAMEEDIT, node->firstName.c_str());
		SetDlgItemText(IDC_LASTNAMEEDIT, node->lastName.c_str());
		SetDlgItemText(IDC_PhoneEdit, node->phoneNumber.c_str());
		SetDlgItemText(IDC_BIRTHDATEPICK, node->birthdate.c_str());
		SetDlgItemText(IDC_ADDRESSEDIT, node->address.c_str());
		SetDlgItemText(IDC_EMAILEDIT, node->email.c_str());

		str.Format("Edit Contact!");
		GetDlgItem(IDC_BUTTON_TWO)->SetWindowText(str);
		str.Format("DELETE ENTRY");
		GetDlgItem(IDC_BUTTON_DELETE)->SetWindowText(str);
		str.Format("PLEASE EDIT YOUR CONTACT OR DELETE");
		GetDlgItem(IDC_MAIN_DISPLAY)->SetWindowText(str);
		hasSearched = true;
		hasSelected = true;
	}
	else {
		SetDlgItemText(IDC_FIRSTNAMEEDIT, "PLEASE");
		SetDlgItemText(IDC_LASTNAMEEDIT, "SEARCH");
		SetDlgItemText(IDC_PhoneEdit, "A");
		SetDlgItemText(IDC_ADDRESSEDIT, "VALID PERSON");
		SetDlgItemText(IDC_EMAILEDIT, "FIRST!");
	}

	SetDlgItemText(IDC_NUMBEREDIT, "");
}

void CMyForm::OnBnClickedButtonFour() {
	//Display sorted by First Name
	TRACE0("BUTTON 4 // SORT BY FIRST NAME");
	if (!hasSelected) {
		CString str;
		iCloud.changeToFirstNames(); //Change setting to 1st name
		iCloud.getContactsInOrder(inOrder);

		str = "Here are the contacts sorted by First Name: \r\n";
		for (int i = 0; i < inOrder.size(); i++) {
			Contact* node = inOrder[i];
			str = str + node->firstName.c_str();
			str = str + _T(" ") + node->lastName.c_str();
			str = str + _T("\r\n") + node->phoneNumber.c_str();
			str = str + _T("\r\n") + node->birthdate.c_str();
			str = str + _T("\r\n") + node->address.c_str();
			str = str + _T("\r\n") + node->email.c_str();
			str = str + _T("\r\n\r\n");
		}

		SetDlgItemText(IDC_MAIN_DISPLAY, str);
	}
}

void CMyForm::OnBnClickedButtonFive() {
	//Display sorted by First Name
	TRACE0("BUTTON 5 // SORT BY LAST NAME");
	if (!hasSelected) {
		CString str;
		iCloud.changeToLastNames(); //Change setting to 1st name
		iCloud.getContactsInOrder(inOrder);

		str = "Here are the contacts sorted by Last Name: \r\n";
		for (int i = 0; i < inOrder.size(); i++) {
			Contact* node = inOrder[i];
			str = str + node->firstName.c_str();
			str = str + _T(" ") + node->lastName.c_str();
			str = str + _T("\r\n") + node->phoneNumber.c_str();
			str = str + _T("\r\n") + node->birthdate.c_str();
			str = str + _T("\r\n") + node->address.c_str();
			str = str + _T("\r\n") + node->email.c_str();
			str = str + _T("\r\n\r\n");
		}

		SetDlgItemText(IDC_MAIN_DISPLAY, str);
	}
}

void CMyForm::OnBnClickedButtonSix() {
	//Display sorted by First Name
	TRACE0("BUTTON 6 // SORT BY BIRTHDATE");
	if (!hasSelected) {
		CString str;
		iCloud.changeToBirthdates(); //Change setting to 1st name
		iCloud.getContactsInOrder(inOrder);

		str = "Here are the contacts sorted by Birth Date: \r\n";
		for (int i = 0; i < inOrder.size(); i++) {
			Contact* node = inOrder[i];
			str = str + node->firstName.c_str();
			str = str + _T(" ") + node->lastName.c_str();
			str = str + _T("\r\n") + node->phoneNumber.c_str();
			str = str + _T("\r\n") + node->birthdate.c_str();
			str = str + _T("\r\n") + node->address.c_str();
			str = str + _T("\r\n") + node->email.c_str();
			str = str + _T("\r\n\r\n");
		}

		SetDlgItemText(IDC_MAIN_DISPLAY, str);
	}
}

void CMyForm::OnBnClickedButtonDelete() {
	//Delete Element once selected element
	TRACE0("DELETE BUTTON // DELETE");
	CString str;
	CString element;
	if (hasSelected) {
		Contact* node = iCloud.getSearchResults()[index];
		element = "Deleted ";
		element = element + node->firstName.c_str();
		element = element + _T(" ") + node->lastName.c_str();
		element = element + _T(" from your contacts!");
		SetDlgItemText(IDC_MAIN_DISPLAY, element);

		iCloud.deleteFromAllTrees(node, TRUE);
		resetEditFields();

		str.Format("---");
		GetDlgItem(IDC_BUTTON_DELETE)->SetWindowText(str);
		str.Format("Add to Contacts!");
		GetDlgItem(IDC_BUTTON_TWO)->SetWindowText(str);
		str.Format("---");
		hasSearched = false;
		hasSelected = false;
	}
}

void CMyForm::MenuLoadHelper() {
//These functions are used for main menu ONLY
	CString str = "Loading From File! ...";
	
	TRACE0("LOAD FILE FUNCTION CALLED");
	iCloud.deleteEverything();
	iCloud.loadAllFromFile();

	str += _T("\r\n\r\n...Loaded!");
	SetDlgItemText(IDC_MAIN_DISPLAY, str);
	resetEditFields();

}

void CMyForm::MenuSaveHelper() {
	//These functions are used for main menu ONLY
	CString str = "Saving to File! ...";
	TRACE0("SAVE FILE FUNCTION CALLED");
	iCloud.saveAllToFile("savefile.csv");

	str += _T("\r\n\r\n...Saved!");
	resetEditFields();
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
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CMyForm::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CMyForm::MenuLoadHelper)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CMyForm::MenuSaveHelper)
END_MESSAGE_MAP()