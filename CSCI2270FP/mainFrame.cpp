#include <afxwin.h>
#include <cstring>
#include <string>
#include "mainFrame.h"
#include "Contacts.h"

CMyFrame::CMyFrame() {
	Create(NULL, TEXT("My APP FRAME")); //Creates a new window
}

void CMyFrame::OnLButtonDown(UINT nFlags, CPoint point) { //On Left Mouse Click
	CFrameWnd::OnLButtonDown(nFlags, point);
	MessageBox("Left Button Clicked!");
}

void CMyFrame::OnPaint() { //Redraws application as needed
	CPaintDC dc(this);
	dc.TextOut(0, 0, "Hello, Happy World!");
}

int CMyFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CFrameWnd::OnCreate(lpCreateStruct) == 0) {
		MessageBox("Good Morning!");
		return 0;
	}
	else {
		return -1;
	}
}

void CMyFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	std::string apricot;
	switch (nChar) {
	case VK_ESCAPE:
		happyContacts.createContact("Jeff", "Kaplan", "123-456-7890", "4/20/1889", "Austria", "aussie@bundestadt.org");
		apricot = happyContacts.treeHead()->c->firstName;
		MessageBox(apricot.c_str());
		break;
	case VK_RETURN:
		MessageBox("Testing");
		break;
	case VK_F1:
		MessageBox("F1!");
		break;
	case VK_DELETE:
		MessageBox("You can't delete what aint there");
		break;
	default:
		MessageBox("Thonk");
		break;
	}
}