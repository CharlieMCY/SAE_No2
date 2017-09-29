// SAE_No2Dlg.h : header file
//
//{{AFX_INCLUDES()
#include "vsflexgrid.h"
#include "xydcapactivex.h"
//}}AFX_INCLUDES

#if !defined(AFX_SAE_NO2DLG_H__431AD600_3908_4114_8319_2488497E4B0A__INCLUDED_)
#define AFX_SAE_NO2DLG_H__431AD600_3908_4114_8319_2488497E4B0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include ".\GraphicCMN\AXGraphCtrl.h"
#include ".\GraphicCMN\AXMeasureCtrl.h"
#include "SAE_No2Cmn.h"
#include "EditEx.h"
#include "SerialPort.h"
#include "GdipButton.h"
#include "ClutchModel.h"
#include "WaitDlg.h"

#include "xydcapactivex.h"
//#include ".\src\measureRadius_idl.h"
//#include ".\src\mwcomtypes.h"

#include "FGridCtrlLU.h"

/////////////////////////////////////////////////////////////////////////////
// CSAE_No2Dlg dialog

class CSAE_No2Dlg : public CDialog
{
// Construction
public:
	CSAE_No2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSAE_No2Dlg)
	enum { IDD = IDD_SAE_NO2_DIALOG };
	CButton	m_btn_pause;
	CEditEx	m_edt_tim;
	CEditEx	m_edt_coe;
	CAXMeasureCtrl	m_measY1;
	CAXGraphCtrl	m_graph;
	CFGridCtrlLU	m_ch1_grid;
	CFGridCtrlLU	m_ch2_grid;
	CFGridCtrlLU	m_ch3_grid;
	CFGridCtrlLU	m_ch4_grid;
	CVSFlexGrid	m_input_grid;
	CXYDCapActiveX	m_twain;
	CGdipButton	m_btn_ts;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSAE_No2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	static UINT	ThreadFunc(LPVOID pThreadParam);

// Implementation
protected:
	SAE	pSae;

	int	screenx, screeny;
	int	printx, printy;
	double	ratex, ratey;
	double tempmax, tempmin;

	int MAXNode;
	int opensxt;

	HICON m_hIcon;

	CWinThread* m_thread;

	CSerialPort m_SerialPort;
	ClutchModel m_clumod;

	BOOL	w_pause;
	BOOL	w_muv;
	BOOL	start;

	double	m_graphXMin;
	double	m_graphXMax;
	double	m_graphYMin;
	double	m_graphYMax;

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
	void	SetGraphXScale(double dblMin, double dblMax);
	void	SetGraphYScale(double dblMin, double dblMax);
	void	SaveWaveData(FILE *fp);
	void	DispTime(float time);
	void	DispGraph();
	void	DeleteDirectory(char* sDirName);
	
	CString DevideHexChar(char HexChar);
	char CombineHexChar(char CharH,char CharL);
	CString ChangeCharstr2Hexstr(CString Charstr);
	void HexStringFilter(CString &str);

	// Generated message map functions
	//{{AFX_MSG(CSAE_No2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCondSet();
	afx_msg void OnButtonExit();
	afx_msg void OnClose();
	afx_msg void OnButtonInMonitor();
	afx_msg void OnButtonCommSet();
	afx_msg void OnButtonScaleSet();
	afx_msg void OnButtonWaveData();
	afx_msg void OnChkCh(UINT nID);
	afx_msg void OnButtonClear();
	afx_msg void OnButtonAbout();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonSave();
	afx_msg void OnCheckCh1();
	afx_msg void OnCheckCh2();
	afx_msg void OnCheckCh3();
	afx_msg void OnCheckCh4();
	afx_msg void OnButtonApplyData();
	afx_msg void OnCheckPause();
	afx_msg void OnButtonPrint();
	afx_msg void OnButtonGetData();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonNwj();
	afx_msg void OnButtonNd();
	afx_msg void OnReceiveChar(UINT ch, LONG port);
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD dwData);
	afx_msg void OnCheckMuv();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAE_NO2DLG_H__431AD600_3908_4114_8319_2488497E4B0A__INCLUDED_)
