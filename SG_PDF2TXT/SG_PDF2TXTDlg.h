/*

SG_PDF2TXT
(c) 2021 Secured Globe, Inc.

version 1.0	Obtober, 2021
*/
#pragma once

#define COLOR_FG RGB(173, 81, 106)
#define COLOR_BG RGB(60, 155, 178)

class CCSGPDF2TXTDlg : public CDialogEx
{
public:
	CCSGPDF2TXTDlg(CWnd* pParent = nullptr);	

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SG_PDF2TXT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


protected:
	HICON m_hIcon;
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnBrowse();
	afx_msg void OnBnClickedBtnConvert();
	CString m_szPDFPath;
};
