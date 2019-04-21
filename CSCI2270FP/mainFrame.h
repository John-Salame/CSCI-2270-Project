#pragma once
#include <afxext.h>
#include "Contacts.h"
#include "resource.h"
class CMyApp : public CWinApp {
public:
	virtual BOOL InitInstance();
	void OnMenuExit();
protected:
	DECLARE_MESSAGE_MAP()
};

class CMyForm : public CFormView {
public:
	DECLARE_DYNCREATE(CMyForm)

	enum { IDD = IDD_DIALOG_MAIN };
	CMyForm();
	virtual ~CMyForm();

	void resetEditFields();
	void OnBnClickedButtonOne();
	void OnBnClickedButtonTwo();
	void OnBnClickedButtonThree();
	void OnBnClickedButtonFour();
	void OnBnClickedButtonFive();
	void OnBnClickedButtonSix();

	DECLARE_MESSAGE_MAP()
private:
	Contacts iCloud;
	bool hasSearched = false;
	bool hasSelected = false;
	int index = -1;
	std::vector<Contact*> inOrder;
};

class CMyWindow : public CFrameWnd {
public:
	DECLARE_DYNCREATE(CMyWindow)
	BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()

	CMyForm* m_pMainView  = nullptr;
};
