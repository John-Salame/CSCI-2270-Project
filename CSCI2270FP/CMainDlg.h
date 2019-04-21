#pragma once
// CMainDlg dialog

class CMainDlg : public CDialog
{
	DECLARE_DYNAMIC(CMainDlg)
public:
	CEdit m_MainDisplay;	//Display Edit
	CEdit m_UserEdit;		//User input Edit
	CEdit m_FirstName;		//First Name
	CEdit m_LastName;		//Last Name
	CEdit m_PhoneNum;		//Phone Num
	CEdit m_Birthdate;		//B-Day
	CEdit m_Address;		//Address
	CEdit m_Email;			//Email
	CEdit m_Number;			//Number of Searched Element
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
};
