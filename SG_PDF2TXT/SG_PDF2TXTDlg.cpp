/*

SG_PDF2TXT
(c) 2021 Secured Globe, Inc.

version 1.0	Obtober, 2021
*/
#include "pch.h"
#include "framework.h"
#include "SG_PDF2TXT.h"
#include "SG_PDF2TXTDlg.h"
#include "afxdialogex.h"

#include <string>
#include "SG_PDF2Txt_proc.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCSGPDF2TXTDlg 对话框



CCSGPDF2TXTDlg::CCSGPDF2TXTDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SG_PDF2TXT_DIALOG, pParent)
	, m_szPDFPath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCSGPDF2TXTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_PDF_PATH, m_szPDFPath);
}

BEGIN_MESSAGE_MAP(CCSGPDF2TXTDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BROWSE, &CCSGPDF2TXTDlg::OnBnClickedBtnBrowse)
	ON_BN_CLICKED(IDC_BTN_CONVERT, &CCSGPDF2TXTDlg::OnBnClickedBtnConvert)
END_MESSAGE_MAP()



BOOL CCSGPDF2TXTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		


	return TRUE;  
}


void CCSGPDF2TXTDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CCSGPDF2TXTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCSGPDF2TXTDlg::OnBnClickedBtnBrowse()
{
	CFileDialog w_cfOpen(TRUE, _T("pdf"), (LPCTSTR)0, 6UL, _T("PDF Files(*.pdf)|*.pdf|"));

	// update data from ui
	UpdateData(TRUE);

	// show open file dialog
	if (w_cfOpen.DoModal() != IDOK)
		return;

	m_szPDFPath = w_cfOpen.GetPathName();

	// update data to ui
	UpdateData(FALSE);
}
HBRUSH hBrWhite = []()
{
	return CreateSolidBrush(COLOR_BG);
}();

HBRUSH hBrYellow = []()
{
	return CreateSolidBrush(COLOR_FG);
}();
HBRUSH CCSGPDF2TXTDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	// Our custom edit-control
	int CtrlId = pWnd->GetDlgCtrlID();
	switch (CtrlId)
	{
		case IDC_EDT_PDF_PATH:
		{
			pDC->SetBkColor(COLOR_FG);
			return hBrYellow;
		}
	}
	pDC->SetBkColor(COLOR_BG);
	return hBrWhite;

	// All the rest
	return CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
}


void CCSGPDF2TXTDlg::OnBnClickedBtnConvert()
{
	// update data from ui
	UpdateData(TRUE);

	// convert unicode path to utf8 path
	wstring w_wszPath = m_szPDFPath.GetBuffer();
	m_szPDFPath.ReleaseBuffer();
	int w_nLen = WideCharToMultiByte(CP_UTF8, 0, w_wszPath.data(), -1, NULL, NULL, NULL, NULL);
	char* w_pszPath = new char[w_nLen + 1];
	memset(w_pszPath, 0x00, w_nLen + 1);
	WideCharToMultiByte(CP_UTF8, 0, w_wszPath.data(), w_wszPath.size(), w_pszPath, w_nLen, NULL, NULL);
	string w_szPath(w_pszPath);
	delete[] w_pszPath;
	string w_szOutPath = w_szPath + ".txt";

	// process pdf2txt
	pdf2txt(w_szPath, w_szOutPath);
	wstring target(w_szOutPath.begin(), w_szOutPath.end());
	ShellExecute(GetForegroundWindow()->GetSafeHwnd(), L"OPEN", target.c_str(), NULL, NULL, 1);
	MessageBox(_T("Completed"), _T("pdf2txt"), MB_ICONINFORMATION | MB_OK);
}
