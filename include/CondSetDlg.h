//{{AFX_INCLUDES()
#include "vsflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_CONDSETDLG_H__146978E8_8843_4465_807A_22F9EC91C749__INCLUDED_)
#define AFX_CONDSETDLG_H__146978E8_8843_4465_807A_22F9EC91C749__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "SAE_No2defs.h"
#endif // _MSC_VER > 1000
// CondSetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCondSetDlg dialog

class CCondSetDlg : public CDialog
{
// Construction
public:
	CCondSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCondSetDlg)
	enum { IDD = IDD_DIALOG_COND_SET };
	CVSFlexGrid	m_condset_grid;
	//}}AFX_DATA
	void	Initialize(COND* pCond);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCondSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	COND	m_cond;
	void	DispCondSetting(COND* pCond);
	// Generated message map functions
	//{{AFX_MSG(CCondSetDlg)
	afx_msg void OnButtonClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButtonApply();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONDSETDLG_H__146978E8_8843_4465_807A_22F9EC91C749__INCLUDED_)
