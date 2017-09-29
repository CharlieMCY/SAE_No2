// SAE_No2.h : main header file for the SAE_NO2 application
//

#if !defined(AFX_SAE_NO2_H__5810E280_7603_4021_95C8_194FC67D5C22__INCLUDED_)
#define AFX_SAE_NO2_H__5810E280_7603_4021_95C8_194FC67D5C22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSAE_No2App:
// See SAE_No2.cpp for the implementation of this class
//

class CSAE_No2App : public CWinApp
{
public:
	CSAE_No2App();
	ULONG_PTR m_pGdiToken;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSAE_No2App)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSAE_No2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAE_NO2_H__5810E280_7603_4021_95C8_194FC67D5C22__INCLUDED_)
