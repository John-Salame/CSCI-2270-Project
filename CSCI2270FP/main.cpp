/** CSCI-2270 - Data Structures Project.
John Salame - 109001053
Kyran Butler - 108492940
In Ji Chung - 109215841
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
	ON_COMMAND(ID_MENU_EXIT, &CMyApp::OnMenuExit)
END_MESSAGE_MAP()


BOOL CMyApp::InitInstance() {
	CMyWindow* pFrame = new CMyWindow; //Create the CFrameWnd
	if (!pFrame) {
		return FALSE;
	}
	m_pMainWnd = pFrame;
	pFrame->LoadFrame(IDR_MAINMENU); //Load menu bar

	pFrame->ShowWindow(SW_SHOW); //Show wnd
	pFrame->UpdateWindow(); //Update wnd
	pFrame->SetWindowTextA("Hello, Happy Contacts!"); //Set wnd text


	return TRUE;
}

CMyApp happyApp;
