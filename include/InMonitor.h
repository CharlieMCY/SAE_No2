#if !defined(AFX_INMONITOR_H__5596C370_8504_4FDB_9087_31692E61C5AB__INCLUDED_)
#define AFX_INMONITOR_H__5596C370_8504_4FDB_9087_31692E61C5AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InMonitor.h : header file
//

#include "SAE_No2defs.h"
#include "SerialPort.h"
#include "EditEx.h"

/////////////////////////////////////////////////////////////////////////////
// CInMonitor dialog

class CInMonitor : public CDialog
{
// Construction
public:
	CInMonitor(CWnd* pParent = NULL);   // standard constructor
	CSerialPort m_SerialPort;

// Dialog Data
	//{{AFX_DATA(CInMonitor)
	enum { IDD = IDD_DIALOG_IN_MONITOR };
	CEditEx	m_edt_ri8;
	CEditEx	m_edt_ri7;
	CEditEx	m_edt_ui6;
	CEditEx	m_edt_ui5;
	CEditEx	m_edt_ui4;
	CEditEx	m_edt_ui3;
	CEditEx	m_edt_ui2;
	CEditEx	m_edt_ui1;
	CEditEx	m_edt_ri6;
	CEditEx	m_edt_ri5;
	CEditEx	m_edt_ri4;
	CEditEx	m_edt_ri3;
	CEditEx	m_edt_ri2;
	CEditEx	m_edt_ri1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInMonitor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void	DispInMoni();
	// Generated message map functions
	//{{AFX_MSG(CInMonitor)
	afx_msg void OnButtonClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INMONITOR_H__5596C370_8504_4FDB_9087_31692E61C5AB__INCLUDED_)
