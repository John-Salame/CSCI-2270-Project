#pragma once
#include "Contacts.h"
#include <afxext.h>
class CMyApp : public CWinApp {
public:
	virtual BOOL InitInstance();
	void OnMenuExit();

	DECLARE_MESSAGE_MAP()
};

class CMyWindow : public CFrameWnd {
	DECLARE_DYNCREATE(CMyWindow)
	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
};

class CMyDocument : public CDocument {
	DECLARE_DYNCREATE(CMyDocument)

	DECLARE_MESSAGE_MAP();
};

class CMyEditor : public CEditView {
	DECLARE_DYNCREATE(CMyEditor)

	DECLARE_MESSAGE_MAP();
};