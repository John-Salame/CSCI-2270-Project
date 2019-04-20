#pragma once
// CMainDlg dialog

class CMainDlg : public CDialog
{
	DECLARE_DYNAMIC(CMainDlg)
public:
	CEdit m_MainDisplay; //Display Edit
	CEdit m_UserEdit; //User input Edit
	CMainDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual BOOL OnInitDialog();
	virtual ~CMainDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MAIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV Support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOne();
	afx_msg void OnBnClickedButtonTwo();

};
