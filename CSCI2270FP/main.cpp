/** CSCI-2270 - Data Structures Project.

John Salame - 109001053
Kyran Butler - 108492940
Inji Chung -

g++ -std=c++11 main.cpp -o runner
*/

#include <iostream>
#include <string>
#include <afxwin.h>
#include "mainFrame.h"
#include "resource.h"

CMyApp happyApp;

BEGIN_MESSAGE_MAP(CMyFrame, CFrameWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

BOOL CMyApp::InitInstance() {
	m_pMainWnd = new CMyFrame();
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}