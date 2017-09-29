//{{AFX_INCLUDES()
#include "vsflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_SCALESETDLG_H__2A507B58_AE41_4DF3_AA53_16B84E2294B8__INCLUDED_)
#define AFX_SCALESETDLG_H__2A507B58_AE41_4DF3_AA53_16B84E2294B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScaleSetDlg.h : header file
//

#include "SAE_No2defs.h"
#include "SAE_No2Cmn.h"
#include "StaticEx.h"

#include "FGridCtrlLU.h"

/////////////////////////////////////////////////////////////////////////////
// CScaleSetDlg dialog

class CScaleSetDlg : public CDialog
{
// Construction
public:
	CScaleSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScaleSetDlg)
	enum { IDD = IDD_DIALOG_SCALE_SET };
	CStaticEx	m_st_csrcolor;
	CButton	m_btn_csrcolor;
	CStaticEx	m_st_gridcolor;
	CStaticEx	m_st_bgcolor;
	CFGridCtrlLU	m_scaleset_grid;
	//}}AFX_DATA

	void	Initialize(WAVE_DLG_KIND kind, SAE_PARA* pPara);
	void	DispScaleSetting();
	void	GridToData();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScaleSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	WAVE_DLG_KIND	m_kind;
	SAE_PARA		m_para;

	// Generated message map functions
	//{{AFX_MSG(CScaleSetDlg)
	afx_msg void OnButtonBgcolor();
	afx_msg void OnButtonGridColor();
	afx_msg void OnButtonClose();
	afx_msg void OnButtonApply();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClickVsflexgridnGraph();
	afx_msg void OnButtonCsrcolor();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCALESETDLG_H__2A507B58_AE41_4DF3_AA53_16B84E2294B8__INCLUDED_)
