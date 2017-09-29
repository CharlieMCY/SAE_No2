#if !defined(AFX_COMMSETDLG_H__194850B6_9569_4C96_8CCE_410DD0CBF9B7__INCLUDED_)
#define AFX_COMMSETDLG_H__194850B6_9569_4C96_8CCE_410DD0CBF9B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommSetDlg.h : header file
//

#include "SAE_No2defs.h"
#include "SerialPort.h"
#include "SAE_No2Cmn.h"
/////////////////////////////////////////////////////////////////////////////
// CCommSetDlg dialog

class CCommSetDlg : public CDialog
{
// Construction
public:
	CCommSetDlg(CWnd* pParent = NULL);   // standard constructor
	CSerialPort m_SerialPort;

// Dialog Data
	//{{AFX_DATA(CCommSetDlg)
	enum { IDD = IDD_DIALOG_COMM_SET };
	CComboBox	m_TypeList_Stop;
	CComboBox	m_TypeList_Ser;
	CComboBox	m_TypeList_Data;
	CComboBox	m_TypeList_Baud;
	CComboBox	m_TypeList_Check;
	CString	m_strPortNO;
	CString	m_strBaudRate;
	CString	m_strDataBits;
	CString	m_strStopBits;
	CString	m_strParity;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCommSetDlg)
	afx_msg void OnButtonClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonApply();
	afx_msg void OnSelchangeComboSerPort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMSETDLG_H__194850B6_9569_4C96_8CCE_410DD0CBF9B7__INCLUDED_)
