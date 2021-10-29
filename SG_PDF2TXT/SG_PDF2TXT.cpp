/*

SG_PDF2TXT
(c) 2021 Secured Globe, Inc.

version 1.0	Obtober, 2021
*/

#include "pch.h"
#include "framework.h"
#include "SG_PDF2TXT.h"
#include "SG_PDF2TXTDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCSGPDF2TXTApp

BEGIN_MESSAGE_MAP(CCSGPDF2TXTApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()



CCSGPDF2TXTApp::CCSGPDF2TXTApp()
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

}



CCSGPDF2TXTApp theApp;



BOOL CCSGPDF2TXTApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	CShellManager *pShellManager = new CShellManager;

	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	SetRegistryKey(_T("SG_PDF2TXT"));

	CCSGPDF2TXTDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}
	else if (nResponse == -1)
	{
	}

	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	return FALSE;
}

