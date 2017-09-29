//{{AFX_INCLUDES()
#include "vsflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_WAVEDATADLG_H__6D7ABD1A_B973_41D8_930F_2FC5684E5E06__INCLUDED_)
#define AFX_WAVEDATADLG_H__6D7ABD1A_B973_41D8_930F_2FC5684E5E06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WaveDataDlg.h : header file
//

#include ".\GraphicCMN\AXGraphCtrl.h"
#include ".\GraphicCMN\AXMeasureCtrl.h"
#include "SAE_No2Cmn.h"
#include "EditEx.h"

#include "FGridCtrlLU.h"

/////////////////////////////////////////////////////////////////////////////
// CWaveDataDlg dialog

class CWaveDataDlg : public CDialog
{
// Construction
public:
	CWaveDataDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWaveDataDlg)
	enum { IDD = IDD_DIALOG_WAVE_DATA };
	CScrollBar	m_scrollX;
	CButton	m_chk_cursordisp;
	CEditEx			m_edt_coe;
	CEditEx			m_edt_tim;
	CAXMeasureCtrl	m_measY1;
	CAXGraphCtrl	m_graph;
	CFGridCtrlLU	m_ch1_grid;
	CFGridCtrlLU	m_ch2_grid;
	CFGridCtrlLU	m_ch3_grid;
	CFGridCtrlLU	m_ch4_grid;
	CVSFlexGrid	m_condset_grid;
	CFGridCtrlLU	m_view_grid;
	CVSFlexGrid	m_input_grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaveDataDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	double	m_graphXMin;
	double	m_graphXMax;
	double	m_graphYMin;
	double	m_graphYMax;

	CArray<SAE_No2,SAE_No2>	m_graphdata;

	void AdjustXRange(double *pdblMin, double *pdblMax);

	void	Initialize();
	void	InitControl();
	void	OnInitGraph();
	void	SetGraphStyle(SAE_PARA *pGRP);
	void	SetGraphStyleBase(SAE_PARA *pGRP);
	void	DispChannel(SAE_PARA* pGraphPara);
	float	GetGraphDefaultXMin();
	float	GetGraphDefaultXMax();
	float	GetGraphDefaultYMin();
	float	GetGraphDefaultYMax();
	float	GetGraphXMin();
	float	GetGraphXMax();
	float	GetGraphYMin();
	float	GetGraphYMax();
	void	CheckScrollGraph();
	void	DispChannelValue(int pos);
	void	SetGraphXScale(double dblMin, double dblMax);
	void	SetGraphYScale(double dblMin, double dblMax);
	void	GetWaveData(FILE *fp);
	void	DispGraph();
	void	ApplyControl();

	// Generated message map functions
	//{{AFX_MSG(CWaveDataDlg)
	afx_msg void OnButtonClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonScaleSet();
	afx_msg void OnCheckCursor();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnUpdateCursolGraph(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnChkCh(UINT nID);
	afx_msg void OnButtonZoom();
	afx_msg void OnButtonOrigine();
	afx_msg void OnButtonClear();
	afx_msg void OnButtonFile();
	afx_msg void OnCheckCh1();
	afx_msg void OnCheckCh2();
	afx_msg void OnCheckCh3();
	afx_msg void OnCheckCh4();
	afx_msg void OnButtonPrint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVEDATADLG_H__6D7ABD1A_B973_41D8_930F_2FC5684E5E06__INCLUDED_)
