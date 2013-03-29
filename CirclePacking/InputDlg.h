#pragma once
#include "afxwin.h"


// CInputDlg dialog

class CInputDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputDlg)

public:
	CInputDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInputDlg();

	virtual void OnFinalRelease();

// Dialog Data
	enum { IDD = IDD_DIALOG_INPUT };
	CString Argv;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedInput();
public:
	char *msg;/*串行化*/
	char *p;/*msg的移动指针*/
	CString prompt;
	int N;
};
