#pragma once
class CMyApp : public CWinApp {
public:
	virtual BOOL InitInstance();
};

class CMyFrame : public CFrameWnd {
public:
	CMyFrame();
protected:
	//afx_msg means they are part of the MFC library msg dispatch sys
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	DECLARE_MESSAGE_MAP();
};