// CMainDlg.cpp : implementation file
//
#include <afxwin.h>
#include "CMainDlg.h"
#include "afxdialogex.h"
#include "mainFrame.h"
#include "stdafx.h"
#include "Contacts.h"


// CMainDlg dialog

CMainDlg::CMainDlg(CWnd* pParent) : CDialog(IDD_DIALOG_MAIN, pParent) {
}


CMainDlg::~CMainDlg() {
}

BOOL CMainDlg::OnInitDialog() {
	CDialog::OnInitDialog();
	return TRUE;
}

void CMainDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN_DISPLAY, m_MainDisplay);
	DDX_Control(pDX, IDC_USEREDIT, m_UserEdit); //UserEdit
}

IMPLEMENT_DYNAMIC(CMainDlg, CDialog)
BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
END_MESSAGE_MAP()