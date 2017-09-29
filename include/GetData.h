#if !defined(AFX_GETDATA_H__E3F1BF56_D6C2_4A2A_82EC_10703F57DEA9__INCLUDED_)
#define AFX_GETDATA_H__E3F1BF56_D6C2_4A2A_82EC_10703F57DEA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GetData.h : header file
//

#include "SAE_No2defs.h"
#include "SerialPort.h"
#include "twain.h"
#include "TwainCPP.h"
//#include "mclmcr.h"
//#include "matrix.h"
//#include "mclcppclass.h"
//#include ".\measureRadius\measureRadius.h"

/////////////////////////////////////////////////////////////////////////////
// CGetData dialog

class CGetData : public CDialog
{
// Construction
public:
	CGetData(CWnd* pParent = NULL);   // standard constructor
	CSerialPort m_SerialPort;
	CString DevideHexChar(char HexChar);
	char CombineHexChar(char CharH,char CharL);
	CString ChangeCharstr2Hexstr(CString Charstr);
	void HexStringFilter(CString &str);
	CTwain pTwain;

// Dialog Data
	//{{AFX_DATA(CGetData)
	enum { IDD = IDD_DIALOG_GET_DATA };
	CButton	m_GetData;
	CComboBox	m_TesterName;
	CComboBox	m_PortNO;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGetData)
	afx_msg void OnButtonClose();
	afx_msg void OnButtonApply();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnReceiveChar(UINT ch, LONG port);
	afx_msg void OnSelchangeComboInst();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETDATA_H__E3F1BF56_D6C2_4A2A_82EC_10703F57DEA9__INCLUDED_)
