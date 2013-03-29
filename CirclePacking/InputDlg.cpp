// InputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CirclePacking.h"
#include "InputDlg.h"
#include "CirclePackingView.h"

// CInputDlg dialog
extern CCirclePackingView *pView;

IMPLEMENT_DYNAMIC(CInputDlg, CDialog)

CInputDlg::CInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputDlg::IDD, pParent)
{

	EnableAutomation();
	msg=(char*)malloc(200);
	p=msg;
}

CInputDlg::~CInputDlg()
{
	free(msg);
}

void CInputDlg::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INPUT, Argv);
}


BEGIN_MESSAGE_MAP(CInputDlg, CDialog)
	ON_BN_CLICKED(ID_INPUT_BUTTON, &CInputDlg::OnBnClickedInput)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CInputDlg, CDialog)
END_DISPATCH_MAP()

// Note: we add support for IID_IInputDlg to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {4C4864FE-CFCD-41A9-9F39-A77E6C5F59D3}
static const IID IID_IInputDlg =
{ 0x4C4864FE, 0xCFCD, 0x41A9, { 0x9F, 0x39, 0xA7, 0x7E, 0x6C, 0x5F, 0x59, 0xD3 } };

BEGIN_INTERFACE_MAP(CInputDlg, CDialog)
	INTERFACE_PART(CInputDlg, IID_IInputDlg, Dispatch)
END_INTERFACE_MAP()


// CInputDlg message handlers
/*
 * Э�飺 �����İ뾶\0СԲ����\0СԲ1�İ뾶\0СԲ2�İ뾶\0
 */
char buf[200];

UINT mainthread(LPVOID pParam)
{
	pView->OnPackingStart(buf);
	return 1;
}

void CInputDlg::OnBnClickedInput()
{
	UpdateData(TRUE);
	CString text;
	GetDlgItem(ID_INPUT_BUTTON)->GetWindowText(text);
	if(!text.Compare("���������뾶"))
	{
		GetDlgItem(IDC_INPUT)->GetWindowText(text);
		if(text.GetLength()==0)
		{
			OnCancel();
			return;
		}
		prompt="�����뾶��"+text+"��";
		GetDlgItem(IDC_ARGV)->SetWindowText(prompt);
		lstrcpy(p,text);
		p+=text.GetLength();
		*p=0;
		++p;
		GetDlgItem(ID_INPUT_BUTTON)->SetWindowText("����СԲ����");
	}
	else if(!text.Compare("����СԲ����"))
	{
		GetDlgItem(IDC_INPUT)->GetWindowText(text);
		if(text.GetLength()==0)
		{
			OnCancel();
			return;
		}
		prompt.Append("СԲ������"+text+"��СԲ�뾶�� ");
		GetDlgItem(IDC_ARGV)->SetWindowText(prompt);
		lstrcpy(p,text);
		p+=text.GetLength();
		*p=0;
		++p;

		N=(int)atoi(text);
		if(N==1)
		{
			text="�������һ��СԲ�뾶";
			GetDlgItem(ID_INPUT_BUTTON)->SetWindowText(text);
		}
		else if(N>1)
		{
			text="��������"+text+ "��СԲ�뾶";
			GetDlgItem(ID_INPUT_BUTTON)->SetWindowText(text);
		}
		else
		{
			OnCancel();
			return;
		}
	}
	else if(!text.Compare("�������һ��СԲ�뾶"))
	{
		GetDlgItem(IDC_INPUT)->GetWindowText(text);
		if(text.GetLength()==0)
		{
			OnCancel();
			return;
		}
		prompt.Append(text+"��");
		CStatusBar*   pStatus=(CStatusBar*)AfxGetApp()->m_pMainWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR);   
		pStatus->SetPaneText(0,prompt);   
		lstrcpy(p,text);
		p+=text.GetLength();
		*p=0;
		++p;
		--N;
		OnOK();
		memcpy(buf,msg,p-msg);
		p=msg;
		AfxBeginThread(mainthread,NULL);
		return;
	}
	else
	{
		GetDlgItem(IDC_INPUT)->GetWindowText(text);
		if(text.GetLength()==0)
		{
			OnCancel();
			return;
		}
		prompt.Append(text+"  ");
		GetDlgItem(IDC_ARGV)->SetWindowText(prompt);
		lstrcpy(p,text);
		p+=text.GetLength();
		*p=0;
		++p;
		--N;
		if(N==1)
		{
			text="�������һ��СԲ�뾶";
			GetDlgItem(ID_INPUT_BUTTON)->SetWindowText(text);
		}
		else if(N>1)
		{
			char buf1[100];
			sprintf(buf1,"��������%d��СԲ�뾶",N);
			GetDlgItem(ID_INPUT_BUTTON)->SetWindowText(buf1);
		}
		else
		{
			OnCancel();
			return;
		}
	}
}


