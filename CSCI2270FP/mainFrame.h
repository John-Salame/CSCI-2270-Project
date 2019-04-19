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

	DECLARE_MESSAGE_MAP()

};

class CMyWindow : public CFrameWnd {
public:
	DECLARE_DYNCREATE(CMyWindow)
	BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()

	CMyForm* m_pMainView  = nullptr;
};

class CMyDocument : public CDocument {
	DECLARE_DYNCREATE(CMyDocument)

	DECLARE_MESSAGE_MAP()
};