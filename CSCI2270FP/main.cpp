/** CSCI-2270 - Data Structures Project.
John Salame - 109001053
Kyran Butler - 108492940
Inji Chung -
g++ -std=c++11 main.cpp -o runner
*/

#include <iostream>
#include <string>
#include <afxwin.h>
#include <afxext.h>
#include "mainFrame.h"
#include "resource.h"
#include "Contacts.h"

//Main App Map
BEGIN_MESSAGE_MAP(CMyApp, CWinApp)
	ON_COMMAND(ID_MENU_EXIT, OnMenuExit)
END_MESSAGE_MAP()


BOOL CMyApp::InitInstance() {
	CSingleDocTemplate* pDocTemplate; //Single Doc template
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINMENU,
		RUNTIME_CLASS(CMyDocument),
		RUNTIME_CLASS(CMyWindow),
		RUNTIME_CLASS(CMyEditor)
	);
	AddDocTemplate(pDocTemplate);

	CCommandLineInfo cmdInfo;

	if (!ProcessShellCommand(cmdInfo)) {
		return false;
	}

	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

CMyApp happyApp;
