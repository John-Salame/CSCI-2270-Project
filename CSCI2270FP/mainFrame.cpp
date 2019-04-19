#include <afxwin.h>
#include <cstring>
#include <string>
#include "mainFrame.h"
#include "Contacts.h"
#include "resource.h"

void CMyApp::OnMenuExit() {
	PostQuitMessage(0);
}

int CMyWindow::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CFrameWnd::OnCreate(lpCreateStruct) == 0) {
		return 0;
	}
	else {
		return -1;
	}
}

//Frame Map
IMPLEMENT_DYNCREATE(CMyWindow, CFrameWnd)
BEGIN_MESSAGE_MAP(CMyWindow, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

//Document Map
IMPLEMENT_DYNCREATE(CMyDocument, CDocument)
BEGIN_MESSAGE_MAP(CMyDocument, CDocument)
END_MESSAGE_MAP()

//Edit View Map
IMPLEMENT_DYNCREATE(CMyEditor, CEditView)
BEGIN_MESSAGE_MAP(CMyEditor, CEditView)
END_MESSAGE_MAP()