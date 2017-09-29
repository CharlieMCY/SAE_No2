// ScaleSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SAE_No2.h"
#include "ScaleSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScaleSetDlg dialog


CScaleSetDlg::CScaleSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScaleSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScaleSetDlg)
	//}}AFX_DATA_INIT
}


void CScaleSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScaleSetDlg)
	DDX_Control(pDX, IDC_STATIC_CSR_COLOR, m_st_csrcolor);
	DDX_Control(pDX, IDC_BUTTON_CSRCOLOR, m_btn_csrcolor);
	DDX_Control(pDX, IDC_STATIC_GRID_COLOR, m_st_gridcolor);
	DDX_Control(pDX, IDC_STATIC_BG_COLOR, m_st_bgcolor);
	DDX_Control(pDX, IDC_VSFLEXGRIDN_GRAPH, m_scaleset_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScaleSetDlg, CDialog)
	//{{AFX_MSG_MAP(CScaleSetDlg)
	ON_BN_CLICKED(IDC_BUTTON_BGCOLOR, OnButtonBgcolor)
	ON_BN_CLICKED(IDC_BUTTON_GRID_COLOR, OnButtonGridColor)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_CSRCOLOR, OnButtonCsrcolor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScaleSetDlg message handlers

void CScaleSetDlg::Initialize(WAVE_DLG_KIND	kind, SAE_PARA* pPara)
{
	m_kind = kind;
	memcpy(&m_para, pPara, sizeof(SAE_PARA));
}

void CScaleSetDlg::DispScaleSetting()
{
	CString text;
	for (int i = 0; i < WAVE_CH_MAX; i++)
	{
		//Min
		text.Format(FORM_POINT_TL, m_para.chp[i].fMinimum);
		m_scaleset_grid.SetTextMatrix(i + 1, 1, text);
		//Max
		text.Format(FORM_POINT_TL, m_para.chp[i].fMaximum);
		m_scaleset_grid.SetTextMatrix(i + 1, 2, text);
		m_scaleset_grid.SetCellBkColor(i + 1, 3, m_para.chp[i].lineStyle.color);
	}
	m_st_bgcolor.SetBkColor(m_para.grp.clBgColor);
	m_st_gridcolor.SetBkColor(m_para.grp.lsGrid.color);
	m_st_csrcolor.SetBkColor(m_para.grp.lsCursor.color);
}

void CScaleSetDlg::OnButtonBgcolor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_para.grp.clBgColor = dlg.GetColor();
		DispScaleSetting();
	}
}

void CScaleSetDlg::OnButtonGridColor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_para.grp.lsGrid.color = dlg.GetColor();
		DispScaleSetting();
	}
}

void CScaleSetDlg::OnButtonCsrcolor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_para.grp.lsCursor.color = dlg.GetColor();
		DispScaleSetting();
	}
}

void CScaleSetDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CScaleSetDlg::OnButtonApply() 
{
	// TODO: Add your control notification handler code here
	GridToData();
	switch (m_kind)
	{
	case WAVE_DLG_KIND_MAIN:
		g_data.SetGraphPara(&m_para);
		break;
	case WAVE_DLG_KIND_FILE:
		g_data.SetWaveGraphPara(&m_para);
		break;
	}
	CDialog::OnOK();
}

void CScaleSetDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	DispScaleSetting();
	
	if (m_kind == WAVE_DLG_KIND_MAIN)
	{
		m_btn_csrcolor.ShowWindow(SW_HIDE);
		m_st_csrcolor.ShowWindow(SW_HIDE);
	}
	else
	{
		m_btn_csrcolor.ShowWindow(SW_SHOW);
		m_st_csrcolor.ShowWindow(SW_SHOW);
	}
	// TODO: Add your message handler code here
	CDialog::OnShowWindow(bShow, nStatus);
}

BEGIN_EVENTSINK_MAP(CScaleSetDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CScaleSetDlg)
	ON_EVENT(CScaleSetDlg, IDC_VSFLEXGRIDN_GRAPH, -600 /* Click */, OnClickVsflexgridnGraph, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CScaleSetDlg::OnClickVsflexgridnGraph() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	int row = 0;
	switch (m_scaleset_grid.GetCol())
	{
	case 3:	//Color
		row = m_scaleset_grid.GetRow();
		if (row > 0)
		{
			if (dlg.DoModal() == IDOK)
			{
				m_para.chp[row - 1].lineStyle.color = dlg.GetColor();
				DispScaleSetting();
			}
		}
		break;
	default:
		break;
	}
}

void CScaleSetDlg::GridToData() 
{
	CString text;
	for (int i = 0; i < WAVE_CH_MAX; i++)
	{
		//Min
		text = m_scaleset_grid.GetTextMatrix(i + 1, 1);
		m_para.chp[i].fMinimum = (float) atof(text);
		//Max
		text = m_scaleset_grid.GetTextMatrix(i + 1, 2);
		m_para.chp[i].fMaximum = (float) atof(text);
	}
}
