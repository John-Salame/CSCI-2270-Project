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
	SetRegistryKey(_T("Unhappy :<"));
	
	CMyWindow* pFrame = new CMyWindow;
	if (!pFrame) {
		return FALSE;
	}
	m_pMainWnd = pFrame;
	pFrame->LoadFrame(IDR_MAINMENU);

	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	return TRUE;
}

CMyApp happyApp;
