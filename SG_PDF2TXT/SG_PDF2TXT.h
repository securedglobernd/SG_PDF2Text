/*

SG_PDF2TXT
(c) 2021 Secured Globe, Inc.

version 1.0	Obtober, 2021
*/
#pragma once

#ifndef __AFXWIN_H__
	#error "Missing'pch.h' PCH"
#endif

#include "resource.h"		



class CCSGPDF2TXTApp : public CWinApp
{
public:
	CCSGPDF2TXTApp();

public:
	virtual BOOL InitInstance();


	DECLARE_MESSAGE_MAP()
};

extern CCSGPDF2TXTApp theApp;
