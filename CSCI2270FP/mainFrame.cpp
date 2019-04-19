#include <afxwin.h>
#include <cstring>
#include <string>
#include "mainFrame.h"
#include "Contacts.h"
#include "resource.h"

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

//Frame Map
IMPLEMENT_DYNCREATE(CMyWindow, CFrameWnd)
BEGIN_MESSAGE_MAP(CMyWindow, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

//Document Map
IMPLEMENT_DYNCREATE(CMyDocument, CDocument)
BEGIN_MESSAGE_MAP(CMyDocument, CDocument)
END_MESSAGE_MAP()

//Form View Map
IMPLEMENT_DYNCREATE(CMyForm, CFormView)
BEGIN_MESSAGE_MAP(CMyForm, CFormView)
END_MESSAGE_MAP()