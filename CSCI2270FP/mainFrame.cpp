#include <afxwin.h>
#include <cstring>
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
	extern Contacts iCloud;
	std::string stringer;
	switch (nChar) {
	case VK_RETURN:
		//stringer = iCloud.getExample();
		//MessageBox(stringer.c_str());
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