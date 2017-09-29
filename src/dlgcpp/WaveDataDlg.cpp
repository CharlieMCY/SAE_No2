// WaveDataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SAE_No2.h"
#include "WaveDataDlg.h"

#include "ScaleSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SAE	pWSae;
int MAXNode_2=NOTE_WAVE_NUM;
float totaltime_2;

UINT tblChDispWId[WAVE_CH_MAX] = {
	IDC_CHECK_CH1,
	IDC_CHECK_CH2,
	IDC_CHECK_CH3,
	IDC_CHECK_CH4,
};

UINT tblChGridWId[WAVE_CH_MAX] = {	
	IDC_VSFLEXGRIDN_CH_1,
	IDC_VSFLEXGRIDN_CH_2,
	IDC_VSFLEXGRIDN_CH_3,
	IDC_VSFLEXGRIDN_CH_4,
};

void static Double2CString(double value, CString &temp) {
	int count = 0;
	if (value < 1 && value >0) {
		while (value < 1) {
			value *= 10;
			count++;
		}
		temp.Format("%.3lfe-%d", value, count);
	}
	else if (value == 0) {
		temp.Format("%d",(int)value);
	}
	else {
		while (value >= 10) {
			value /= 10;
			count++;
		}
		temp.Format("%.3lfe+%d", value, count);
	}
}
/////////////////////////////////////////////////////////////////////////////
// CWaveDataDlg dialog


CWaveDataDlg::CWaveDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWaveDataDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWaveDataDlg)
	//}}AFX_DATA_INIT
	m_measY1.SetMode(MEASUREY,0,FALSE);
}


void CWaveDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWaveDataDlg)
	DDX_Control(pDX, IDC_SCROLLBAR_X, m_scrollX);
	DDX_Control(pDX, IDC_CHECK_CURSOR, m_chk_cursordisp);
	DDX_Control(pDX, IDC_EDIT_COE, m_edt_coe);
	DDX_Control(pDX, IDC_EDIT_TIM, m_edt_tim);
	DDX_Control(pDX, IDC_VSFLEXGRIDN_CH_1, m_ch1_grid);
	DDX_Control(pDX, IDC_VSFLEXGRIDN_CH_2, m_ch2_grid);
	DDX_Control(pDX, IDC_VSFLEXGRIDN_CH_3, m_ch3_grid);
	DDX_Control(pDX, IDC_VSFLEXGRIDN_CH_4, m_ch4_grid);
	DDX_Control(pDX, IDC_VSFG_COND_SETTING, m_condset_grid);
	DDX_Control(pDX, IDC_VSFLEXGRIDN_VIEW, m_view_grid);
	DDX_Control(pDX, IDC_VSFLEXGRIDN_INPUT, m_input_grid);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_STATIC_MEAS_Y1, m_measY1);
	DDX_Control(pDX, IDC_STATIC_GRAPH, m_graph);
}


BEGIN_MESSAGE_MAP(CWaveDataDlg, CDialog)
	//{{AFX_MSG_MAP(CWaveDataDlg)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_SCALE_SET, OnButtonScaleSet)
	ON_BN_CLICKED(IDC_CHECK_CURSOR, OnCheckCursor)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_ZOOM, OnButtonZoom)
	ON_BN_CLICKED(IDC_BUTTON_ORIGINE, OnButtonOrigine)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_FILE, OnButtonFile)
	ON_BN_CLICKED(IDC_CHECK_CH1, OnCheckCh1)
	ON_BN_CLICKED(IDC_CHECK_CH2, OnCheckCh2)
	ON_BN_CLICKED(IDC_CHECK_CH3, OnCheckCh3)
	ON_BN_CLICKED(IDC_CHECK_CH4, OnCheckCh4)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnButtonPrint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaveDataDlg message handlers

void CWaveDataDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

BOOL CWaveDataDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_graphdata.SetSize(0);
	Initialize();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWaveDataDlg::Initialize()
{
	m_graphXMin = GetGraphDefaultXMin();
	m_graphXMax = GetGraphDefaultXMax();
	m_graphYMin = GetGraphDefaultYMin();
	m_graphYMax = GetGraphDefaultYMin();

	pWSae.fCoefriction	= 0;
	pWSae.fTimestop		= 0;

	pWSae.cond.Initvelocity		= 0;
	pWSae.cond.Surfpressure		= 0;
	pWSae.cond.Inertiamoment	= 0.01;
	pWSae.cond.diskpieces		= 0;

	InitControl();
	OnInitGraph();
}

void CWaveDataDlg::InitControl()
{
	CFGridCtrlLU *pGrid;
	CEditEx *edit;
	CString text;

	for (int i = 0; i < WAVE_CH_MAX; i++)
	{
		pGrid = (CFGridCtrlLU *) GetDlgItem(tblChGridWId[i]);
		pGrid->SetFloatCell(1, 0, DEFAULT_INT_DIGIT, DEFAULT_DEC_DIGIT);//(row, col,intlen,declen)
		pGrid->SetFloatCell(1, 1, DEFAULT_INT_DIGIT, DEFAULT_DEC_DIGIT);
		pGrid->SetFloatCell(1, 2, DEFAULT_INT_DIGIT, DEFAULT_DEC_DIGIT);
	}

	edit = (CEditEx *) GetDlgItem(IDC_EDIT_COE);
	edit->SetFormat(EDITEX_FMTTYPE_DOUBLE);
	edit->SetReadOnly();
	text.Format(FORM_POINT_TM, pWSae.fCoefriction);
	SetDlgItemText(IDC_EDIT_COE,text);
	edit = (CEditEx *) GetDlgItem(IDC_EDIT_TIM);
	edit->SetFormat(EDITEX_FMTTYPE_DOUBLE);
	edit->SetReadOnly();
	text.Format(FORM_POINT_TB, pWSae.fTimestop);
	SetDlgItemText(IDC_EDIT_TIM,text);

	text.Format("%s", "");
	m_condset_grid.SetTextMatrix(0, 2, text);

	text.Format("%s", "");
	m_condset_grid.SetTextMatrix(1, 2, text);

	text.Format("%s", "");
	m_condset_grid.SetTextMatrix(2, 2, text);

	text.Format("%s", "");
	m_condset_grid.SetTextMatrix(3, 2, text);
	m_chk_cursordisp.SetCheck(g_data.WaveGraphPara()->grp.bDispCursor);

	for (i = 0; i < WAVE_CH_MAX; i++)	
	{
		pGrid = (CFGridCtrlLU *) GetDlgItem(IDC_VSFLEXGRIDN_VIEW);
		switch (i)
		{
		case WAVE_CH_1:
			text.Format(FORM_POINT, 0);
			break;
		case WAVE_CH_2:
			text.Format(FORM_POINT, 0);
			break;
		case WAVE_CH_3:
			text.Format(FORM_POINT, 0);
			break;
		case WAVE_CH_4:
			text.Format(FORM_POINT, 0);
			break;
		}
		pGrid->SetTextMatrix(i, 2, text);
	}
	text.Format(FORM_POINT, 0);
	pGrid->SetTextMatrix(i, 2, text);
}

void CWaveDataDlg::OnInitGraph()
{
	m_graph.SetDataSize(WAVE_CH_MAX);//最大データ点数
	m_graph.ShowFrame(FALSE);
	m_graph.AddPlotCursor(CURSORX, PS_SOLID, IRED);

	//Graph Style
	SetGraphStyle(g_data.WaveGraphPara());

	m_measY1.ShowScale(TRUE, FALSE);
	m_measY1.SetScaleType(AMS_OUTSIDE);
	m_measY1.ShowMeasureDelta(FALSE);
	m_measY1.ShowLogZero(TRUE);
	m_measY1.ShowMeasureMinMax(FALSE, FALSE);

	m_scrollX.SetScrollRange((int) GetGraphDefaultXMin(), (int) GetGraphDefaultXMax());
}

void CWaveDataDlg::SetGraphStyle(SAE_PARA *pGRP)
{
	m_graph.SetBkColor(pGRP->grp.clBgColor);					//背景
	m_graph.ShowGridX(pGRP->grp.bDispGrid, pGRP->grp.lsGrid);	//X グリッド線の表示/非表示(X). X軸のグリッド線の線種を指定し表示/非表示する(表示/非表示, グリッド線種, グリッド線色, グリッド線サイズ)
	m_graph.ShowGridY(pGRP->grp.bDispGrid, pGRP->grp.lsGrid);	//Y グリッド線の表示/非表示(Y). Y軸のグリッド線の線種を指定し表示/非表示する(表示/非表示, グリッド線種, グリッド線色, グリッド線サイズ)
	m_graph.GetAxisX().SetScaleColor(pGRP->grp.lsGrid.color);	//X軸目盛り軸の色の設定. 目盛り軸の色を設定する(COLORREF)
	m_graph.GetAxisY().SetScaleColor(pGRP->grp.lsGrid.color);	//Y軸目盛り軸の色の設定. 目盛り軸の色を設定する(COLORREF)

	SetGraphStyleBase(pGRP);
}

void CWaveDataDlg::SetGraphStyleBase(SAE_PARA *pGRP)
{
	DispChannel(pGRP);

	int i;
	for (i = 0; i < m_graph.GetLineNum(); i++)
	{
		m_graph.GetLine(i).SetLineStyle(pGRP->chp[i].lineStyle);
		m_graph.GetLine(i).SetMarkerStyle(pGRP->chp[i].markerStyle);

		//選択軸のみ表示可能
		m_graph.GetLine(i).Visible(pGRP->chp[i].bDisp);
	}

	m_graph.GetAxisX().EnableDivDelta(TRUE);	//Xスケール LOG表示 ゼロの表示/非表示 目盛りの分割指定の有効/無効を設定. (分割/データ値　指定)
	m_graph.GetAxisY().EnableDivDelta(TRUE);	//Yスケール LOG表示 ゼロの表示/非表示 目盛りの分割指定の有効/無効を設定. (分割/データ値　指定)
	SetGraphXScale(GetGraphXMin(), GetGraphXMax());
	SetGraphYScale(GetGraphYMin(), GetGraphYMax());
	m_measY1.SetScale(GetGraphYMin(), GetGraphYMax());

	COLORREF colorTxt = pGRP->grp.lsGrid.color;
	m_graph.GetAxisX().ShowMeasureMinMax(FALSE, FALSE);							//目盛りの値の最小値/最大値の表示/非表示を設定
	m_graph.GetAxisX().GetMaxSideAXString().SetStrColor(colorTxt);				//Max側の表示文字列
	m_graph.GetAxisX().GetMinSideAXString().SetStrColor(colorTxt);				//Min側の表示文字列
	m_graph.GetAxisX().GetNameAXString().SetStrColor(colorTxt);					//名称の表示文字列
	m_graph.GetAxisX().GetMaxSideAXString().SetDTFormat(DT_TOP | DT_CENTER);	//Max側の表示文字列位置
	m_graph.GetAxisX().GetMinSideAXString().SetDTFormat(DT_TOP | DT_CENTER);	//Min側の表示文字列位置
	m_graph.GetAxisX().GetNameAXString().SetDTFormat(DT_VCENTER | DT_RIGHT);	//名称の表示文字列位置
	m_graph.GetAxisX().SetScaleType(AMS_SIDEBOTH);								//iType  内側:AMS_INSIDE / 外側:AMS_OUTSIDE / 交差:AMS_SIDEBOTH 目盛りの向き設定(0:内側/1:外側/2:交差)
	m_graph.SetAxisXCross(3, 0.0);												//軸交差有効(0:Min/1:Max/2:Center/3:データ値指定) /double  dCross = 0.0
	m_graph.GetAxisX().SetScaleColor(colorTxt);									//目盛り軸の色の設定. 目盛り軸の色を設定する
	m_graph.GetAxisX().SetMeasureColor(colorTxt);								//目盛り値の表示色の設定. 目盛り値の表示色を設定する
	m_graph.GetAxisX().ShowMeasureDelta(FALSE);									//目盛りの値の表示/非表示を設定
	m_graph.GetAxisX().SetMeasureAdjust();										//目盛りの値の描画両端の調整の有効/無効を設定(BOOL bAdjust = TRUE)
	m_graph.GetAxisY().ShowMeasureMinMax(FALSE, FALSE);							//目盛りの値の最小値/最大値の表示/非表示を設定
	m_graph.GetAxisY().GetMaxSideAXString().SetStrColor(colorTxt);				//X軸Max文字列色設定
	m_graph.GetAxisY().GetMinSideAXString().SetStrColor(colorTxt);				//X軸Min文字列色設定
	m_graph.GetAxisY().GetMaxSideAXString().SetDTFormat(DT_VCENTER | DT_CENTER);//Max側の表示文字列位置
	m_graph.GetAxisY().GetMinSideAXString().SetDTFormat(DT_VCENTER | DT_CENTER);//Min側の表示文字列位置
	m_graph.GetAxisY().GetNameAXString().SetDTFormat(DT_VCENTER | DT_RIGHT);	//名称の表示文字列位置
	m_graph.GetAxisY().GetNameAXString().SetStrColor(colorTxt);					//名称の表示文字列色
	m_graph.GetAxisY().SetScaleType(AMS_SIDEBOTH);								//iType  内側:AMS_INSIDE / 外側:AMS_OUTSIDE / 交差:AMS_SIDEBOTH 目盛りの向き設定(0:内側/1:外側/2:交差)
	m_graph.SetAxisYCross(3, 0.0);												//軸交差有効(0:Min/1:Max/2:Center/3:データ値指定) /double  dCross = 0.0
	m_graph.GetAxisY().SetScaleColor(colorTxt);									//目盛り軸の色の設定. 目盛り軸の色を設定する
	m_graph.GetAxisY().SetMeasureColor(colorTxt);								//目盛り値の表示色の設定. 目盛り値の表示色を設定する
	m_graph.GetAxisY().ShowMeasureDelta(FALSE);									//目盛りの値の表示/非表示を設定
	m_graph.GetAxisY().SetMeasureAdjust();										//目盛りの値の描画両端の調整の有効/無効を設定(BOOL bAdjust = TRUE)
	m_graph.GetAxisX().SetDeltaOrg(TRUE, 0.0);									//目盛りの描画原点の有効/無効を設定. (データ値指定)(bEnable  TRUE:有効/FALSE:無効, dOrg  目盛り間隔の原点(データ値指定) dOrgの値を基準に描画する。)
	m_graph.GetAxisY().SetDeltaOrg(TRUE, 0.0);									//目盛りの描画原点の有効/無効を設定. (データ値指定)(bEnable  TRUE:有効/FALSE:無効, dOrg  目盛り間隔の原点(データ値指定) dOrgの値を基準に描画する。)
	m_graph.GetAxisX().Format("%.1f");											//目盛りフォーマット & フォントサイズ. 目盛りのフォーマットをprintf型式で指定する
	m_graph.GetAxisY().Format("%.1f");											//目盛りフォーマット & フォントサイズ. 目盛りのフォーマットをprintf型式で指定する
	m_graph.GetAxisY().SetMeasureAngle(900);									//目盛り文字角度を設定する. 目盛りの文字角度を設定する
	m_graph.GetPlotCursor(0).SetLineStyle(pGRP->grp.lsCursor.iStyle,
											pGRP->grp.lsCursor.color,
											pGRP->grp.lsCursor.iSize);
	m_graph.GetPlotCursor(0).ShowCursor(pGRP->grp.bDispCursor);
	m_graph.Redraw();
}

void CWaveDataDlg::DispChannel(SAE_PARA* pGRP)
{
	CButton *pbtnDisp;
	CFGridCtrlLU *pGrid;
	CString text;
	for (int i = 0; i < WAVE_CH_MAX; i++)
	{
		//Disp
		pbtnDisp = (CButton *) GetDlgItem(tblChDispWId[i]);
		pbtnDisp->SetCheck(pGRP->chp[i].bDisp);

		pGrid = (CFGridCtrlLU *) GetDlgItem(tblChGridWId[i]);
		//Min
		text.Format(FORM_POINT_TL, pGRP->chp[i].fMinimum);
		pGrid->SetTextMatrix(1, 0, text);
		//Max
		text.Format(FORM_POINT_TL, pGRP->chp[i].fMaximum);
		pGrid->SetTextMatrix(1, 1, text);
		//Line color
		pGrid->SetCellBkColor(1, 2, pGRP->chp[i].lineStyle.color);
	}
}

void CWaveDataDlg::OnButtonScaleSet() 
{
	CScaleSetDlg dlg;
	// TODO: Add your control notification handler code here
	dlg.Initialize(WAVE_DLG_KIND_FILE, g_data.WaveGraphPara());
	if (dlg.DoModal() == IDOK)
	{
		SetGraphStyle(g_data.WaveGraphPara());
	}
}

void CWaveDataDlg::OnButtonClear() 
{
	// TODO: Add your control notification handler code here
	m_graphdata.SetSize(0);
	CFGridCtrlLU *pGrid;
	CEditEx *edit;
	CString text;

	m_graph.RemoveAllLine();
	m_graph.Redraw(TRUE);
	m_graph.SetDataSize(WAVE_CH_MAX);

	edit = (CEditEx *) GetDlgItem(IDC_EDIT_COE);
	edit->SetFormat(EDITEX_FMTTYPE_DOUBLE);
	edit->SetReadOnly();
	text.Format(FORM_POINT_TM, 0);
	SetDlgItemText(IDC_EDIT_COE,text);
	edit = (CEditEx *) GetDlgItem(IDC_EDIT_TIM);
	edit->SetFormat(EDITEX_FMTTYPE_DOUBLE);
	edit->SetReadOnly();
	text.Format(FORM_POINT_TB, 0);
	SetDlgItemText(IDC_EDIT_TIM,text);

	for (int i = 0; i < WAVE_CH_MAX; i++)	
	{
		pGrid = (CFGridCtrlLU *) GetDlgItem(IDC_VSFLEXGRIDN_VIEW);
		switch (i)
		{
		case WAVE_CH_1:
			text.Format(FORM_POINT, 0);
			break;
		case WAVE_CH_2:
			text.Format(FORM_POINT, 0);
			break;
		case WAVE_CH_3:
			text.Format(FORM_POINT, 0);
			break;
		case WAVE_CH_4:
			text.Format(FORM_POINT, 0);
			break;
		}
		pGrid->SetTextMatrix(i, 2, text);
	}
	text.Format(FORM_POINT, 0);
	pGrid->SetTextMatrix(i, 2, text);

	text.Format("%s", "");
	m_condset_grid.SetTextMatrix(0, 2, text);

	text.Format("%s", "");
	m_condset_grid.SetTextMatrix(1, 2, text);

	text.Format("%s", "");
	m_condset_grid.SetTextMatrix(2, 2, text);

	text.Format("%s", "");
	m_condset_grid.SetTextMatrix(3, 2, text);

	text.Format("%s", "");
	m_input_grid.SetTextMatrix(0, 2, text);

	text.Format("%s", "");
	m_input_grid.SetTextMatrix(1, 2, text);

	text.Format("%s", "");
	m_input_grid.SetTextMatrix(2, 2, text);

	text.Format("%s", "");
	m_input_grid.SetTextMatrix(3, 2, text);

	text.Format("%s", "");
	m_input_grid.SetTextMatrix(4, 2, text);

	text.Format("%s", "");
	m_input_grid.SetTextMatrix(5, 2, text);

	text.Format("%s", "");
	m_input_grid.SetTextMatrix(6, 2, text);

	text.Format("%s", "");
	m_input_grid.SetTextMatrix(7, 2, text);
}

void CWaveDataDlg::OnCheckCursor() 
{
	// TODO: Add your control notification handler code here
	SAE_PARA GRP;
	memcpy(&GRP, g_data.WaveGraphPara(), sizeof(SAE_PARA));
	
	GRP.grp.bDispCursor = m_chk_cursordisp.GetCheck() ? TRUE : FALSE;
	g_data.SetWaveGraphPara(&GRP);
	SetGraphStyle(g_data.WaveGraphPara());
}

float CWaveDataDlg::GetGraphDefaultXMin()
{
	return 0.0;
}

float CWaveDataDlg::GetGraphDefaultXMax()
{
	return (float) MAXNode_2;
}

float CWaveDataDlg::GetGraphDefaultYMin()
{
	float fResult = g_data.GetWaveGraphYMin();
	return fResult;
}

float CWaveDataDlg::GetGraphDefaultYMax()
{
	float fResult = g_data.GetWaveGraphYMax();
	return fResult;
}

float CWaveDataDlg::GetGraphXMin()
{
#if 0
	float fResult = GetGraphDefaultXMin();
	//min maxが逆転することがある？
	if (m_graph.GetLineNum() > 0)
	{
		fResult = (float) m_graph.GetLine(0).GetXscale().GetMin();
	}
	return fResult;
#else
	return (float) m_graphXMin;
#endif
}

float CWaveDataDlg::GetGraphXMax()
{
#if 0
	float fResult = GetGraphDefaultXMax();
	if (m_graph.GetLineNum() > 0)
	{
		fResult = (float) m_graph.GetLine(0).GetXscale().GetMax();
	}
	return fResult;
#else
	return (float) m_graphXMax;
#endif
}

float CWaveDataDlg::GetGraphYMin()
{
	return g_data.GetWaveGraphYMin();
}

float CWaveDataDlg::GetGraphYMax()
{
	return g_data.GetWaveGraphYMax();
}

void CWaveDataDlg::OnButtonZoom() 
{
	// TODO: Add your control notification handler code here
	double dblMin = GetGraphXMin();
	double dblMax = GetGraphXMax();

	dblMax -= dblMin;

	dblMax = GetLogXMaxScale(dblMax);

	if (dblMin > GetGraphDefaultXMin())
	{
		dblMin = GetGraphDefaultXMin();
	}

	AdjustXRange(&dblMin, &dblMax);

	if (dblMin < dblMax)
	{
		SetGraphXScale(dblMin, dblMax);
	}
}

void CWaveDataDlg::AdjustXRange(double *pdblMin, double *pdblMax)
{
	double dblRange = *pdblMax - *pdblMin;
	if (dblRange > 0.0)
	{
		double dblCenter = *pdblMin + (dblRange / 2.0);

		SCROLLINFO scrollInfo;
		m_scrollX.GetScrollInfo(&scrollInfo);
		// 現在のスクロール位置
		double dblDist = scrollInfo.nPos - dblCenter;

		if (((*pdblMin + dblDist) > 0) && ((*pdblMax + dblDist) < MAXNode_2))
		{
			*pdblMin += dblDist;
			*pdblMax += dblDist;
		}
		else if ((*pdblMin + dblDist) > 0)
		{
			*pdblMax = (double) MAXNode_2;
			*pdblMin = *pdblMax - dblRange;
		}
		else if ((*pdblMax + dblDist) < MAXNode_2)
		{
			*pdblMin = 0.0;
			*pdblMax = *pdblMin + dblRange;
		}
	}
}

void CWaveDataDlg::OnButtonOrigine() 
{
	// TODO: Add your control notification handler code here
	SetGraphXScale(GetGraphDefaultXMin(), GetGraphDefaultXMax());
}

void CWaveDataDlg::CheckScrollGraph()
{
	double dX = m_graph.GetPlotCursor(0).GetValue().dX;
	double dblMin = GetGraphXMin();
	double dblMax = GetGraphXMax();
	double dblRange = dblMax - dblMin;

	if ((dblMin <= dX) && (dX <= dblMax))
	{
		//no scroll
	}
	else if (dblMax < dX)	//right Scroll
	{
		if ((dX + dblRange) <= GetGraphDefaultXMax())
		{
			dblMin = dX;
			dblMax = dX + dblRange;
		}
		else
		{
			dblMax = GetGraphDefaultXMax();
			dblMin = dblMax - dblRange;
		}
		SetGraphXScale(dblMin, dblMax);
	}
	else if (dX < dblMin)	//left scroll
	{
		if ((dX - dblRange) >= GetGraphDefaultXMin())
		{
			dblMax = dX;
			dblMin = dX - dblRange;
		}
		else
		{
			dblMin = GetGraphDefaultXMin();
			dblMax = dblMin + dblRange;
		}
		SetGraphXScale(dblMin, dblMax);
	}
}

void CWaveDataDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar == (&m_scrollX))
	{
		SCROLLINFO scrollInfo;
		m_scrollX.GetScrollInfo(&scrollInfo);
		// 現在のスクロール位置
		int cp = scrollInfo.nPos;
		switch(nSBCode)
		{
		case SB_LINELEFT:			// 左へスクロール
			cp--;
			break;
		case SB_LINERIGHT:			// 右へスクロール
			cp++;
			break;
		case SB_PAGELEFT:			// 1 ページ左へスクロール
			cp -= 10;
			break;
		case SB_PAGERIGHT:			// 1 ページ右へスクロール
			cp += 10;
			break;
		case SB_THUMBPOSITION:		// 絶対位置へスクロール(nPos)
		case SB_THUMBTRACK:			// 指定位置へドラッグ(nPos)
			cp = scrollInfo.nTrackPos;
			break;
		case SB_LEFT:				// 左端へスクロール
			cp = scrollInfo.nMin;
			break;
		case SB_RIGHT:				// 右端へスクロール
			cp = scrollInfo.nMax;
			break;
		default:
			return;
		}
		if (cp < scrollInfo.nMin)	{	cp = scrollInfo.nMin;	}
		if (cp > scrollInfo.nMax)	{	cp = scrollInfo.nMax;	}
		// スクロールボックスの位置変更
		m_scrollX.SetScrollPos(cp);
		m_graph.GetPlotCursor(0).SetPos(cp);
		m_graph.GetPlotCursor(0).SetValue(cp, 0);
		CheckScrollGraph();
		DispChannelValue(cp);
		m_graph.Redraw();
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CWaveDataDlg::OnUpdateCursolGraph(NMHDR * pNotifyStruct, LRESULT * result)
{
	LPAXGCNOTIFY pNotify = (LPAXGCNOTIFY) pNotifyStruct;
	AXGCACTINFO &activeInfo = pNotify->activeInfo;

	if (pNotify->activeInfo.nActive == AXGCTRLACT_CURSOL)
	{///< 3:カーソル
		CAXPlotCursor &cursor = m_graph.GetPlotCursor(activeInfo.iIndex);
		if (cursor.GetLayer() >= 0)
		{
			int pos = cursor.GetPos();
			if (pos >= 0 && pos < m_graph[activeInfo.iLayer].GetNum())
			{
				m_scrollX.SetScrollPos(pos);
			}
		}
		*result = TRUE;
	}
}

void CWaveDataDlg::SetGraphXScale(double dblMin, double dblMax)
{
	m_graphXMin = dblMin;
	m_graphXMax = dblMax;
	m_graph.SetXScaleEx(dblMin, dblMax, 10, 2, TRUE, TRUE);
}

void CWaveDataDlg::SetGraphYScale(double dblMin, double dblMax)
{
	m_graphYMin = dblMin;
	m_graphYMax = dblMax;
	m_graph.SetYScaleEx(dblMin, dblMax, 10, 2, TRUE, TRUE);
}

void CWaveDataDlg::OnChkCh(UINT nID)
{
	SAE_PARA GRP;
	memcpy(&GRP, g_data.WaveGraphPara(), sizeof(SAE_PARA));

	for (int i = 0; i < WAVE_CH_MAX; i++)
	{
		if (nID == tblChDispWId[i])
		{
			CButton *pBtn = (CButton *) GetDlgItem(tblChDispWId[i]);
			GRP.chp[i].bDisp = pBtn->GetCheck() ? TRUE : FALSE;
			g_data.SetWaveGraphPara(&GRP);
			SetGraphStyle(g_data.WaveGraphPara());
		}
	}
}

void CWaveDataDlg::DispChannelValue(int pos)
{
	if (!m_graphdata.GetSize()) return;
	CString text;
	float time;
	//float totaltime=2;
	CFGridCtrlLU *pGrid;
	if (pos == MAXNode_2) return;
	for (int i = 0; i < WAVE_CH_MAX; i++)	
	{
		pGrid = (CFGridCtrlLU *) GetDlgItem(IDC_VSFLEXGRIDN_VIEW);
		switch (i)
		{
		case WAVE_CH_1:
			text.Format(FORM_POINT, m_graphdata[0].saem[pos].fRotavelocity*100);
			break;
		case WAVE_CH_2:
			text.Format(FORM_POINT, m_graphdata[0].saem[pos].fPreforce*10);
			break;
		case WAVE_CH_3:
			text.Format(FORM_POINT, m_graphdata[0].saem[pos].fTorque*10);
			break;
		case WAVE_CH_4:
			text.Format(FORM_POINT, m_graphdata[0].saem[pos].fFlimthick);
			break;
		}
		pGrid->SetTextMatrix(i, 2, text);
	}
	time = totaltime_2 / MAXNode_2 * pos;
	text.Format(FORM_POINT, time);
	pGrid->SetTextMatrix(i, 2, text);
}

void CWaveDataDlg::OnButtonFile() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY| OFN_OVERWRITEPROMPT,
		"All Files(*.csv)| *.csv||", AfxGetMainWnd());
	CString strPath;
	m_graphdata.SetSize(1);
	if (dlg.DoModal() == IDOK)
	{
		strPath = dlg.GetPathName();
		FILE* fp;
		char filename[1000];
		strncpy (filename, (LPCTSTR)strPath, sizeof(filename));
		fp=fopen(filename, "r+");
		GetWaveData(fp);
		Initialize();
		ApplyControl();
		DispGraph();
		fclose(fp);
	}
}

void CWaveDataDlg::GetWaveData(FILE *fp)
{
	int i;
	fscanf(fp, "%f*[^\n]",&totaltime_2);
	MAXNode_2 = totaltime_2/0.01;
	fscanf(fp, "%d, %lf, %lf, %d%*[^\n]", &m_graphdata[0].cond.Initvelocity, &m_graphdata[0].cond.Surfpressure,
		&m_graphdata[0].cond.Inertiamoment, &m_graphdata[0].cond.diskpieces);
	fscanf(fp, "%f, %f, %f, %f, %f, %lf, %f, %f%*[^\n]", &m_graphdata[0].saein.fTemperature, &m_graphdata[0].saein.fInner,
		&m_graphdata[0].saein.fOuter,&m_graphdata[0].saein.fThicklining, &m_graphdata[0].saein.fViscosity,
		&m_graphdata[0].saein.fFilmthick, &m_graphdata[0].saein.fSurfroughness, &m_graphdata[0].saein.fAsperityden);
	fscanf(fp, "%f, %f%*[^\n]", &m_graphdata[0].fCoefriction, &m_graphdata[0].fTimestop);
	for (i = 0; i < MAXNode_2; i++)
	{
		fscanf(fp, "%f, %f, %f, %f%*[^\n]", &m_graphdata[0].saem[i].fRotavelocity, &m_graphdata[0].saem[i].fPreforce,
			&m_graphdata[0].saem[i].fTorque, &m_graphdata[0].saem[i].fFlimthick);
	}
}

void CWaveDataDlg::DispGraph()
{
	int i;
	//画面更新STOP
	//LockWindowUpdate();

	for (i = 0; i < WAVE_CH_MAX; i++)
	{
		m_graph.GetLine(i).ClearAllPoint();
	}
	for (i = 0; i < MAXNode_2; i++)
	{
		m_graph.GetLine(WAVE_CH_1).AddPoint(i, m_graphdata[0].saem[i].fRotavelocity);
		m_graph.GetLine(WAVE_CH_2).AddPoint(i, m_graphdata[0].saem[i].fPreforce);
		m_graph.GetLine(WAVE_CH_3).AddPoint(i, m_graphdata[0].saem[i].fTorque);
		m_graph.GetLine(WAVE_CH_4).AddPoint(i, m_graphdata[0].saem[i].fFlimthick);
	}
	SetGraphStyle(g_data.WaveGraphPara());

	//画面更新
	//UnlockWindowUpdate();	
}

void CWaveDataDlg::ApplyControl()
{
	CEditEx *edit;
	CString text;

	edit = (CEditEx *) GetDlgItem(IDC_EDIT_COE);
	edit->SetFormat(EDITEX_FMTTYPE_DOUBLE);
	edit->SetReadOnly();
	text.Format(FORM_POINT_TM, m_graphdata[0].fCoefriction);
	SetDlgItemText(IDC_EDIT_COE,text);
	edit = (CEditEx *) GetDlgItem(IDC_EDIT_TIM);
	edit->SetFormat(EDITEX_FMTTYPE_DOUBLE);
	edit->SetReadOnly();
	text.Format(FORM_POINT_TB, m_graphdata[0].fTimestop);
	SetDlgItemText(IDC_EDIT_TIM,text);

	text.Format("%d", m_graphdata[0].cond.Initvelocity);
	m_condset_grid.SetTextMatrix(0, 2, text);

	text.Format(FORM_POINT, m_graphdata[0].cond.Surfpressure);
	m_condset_grid.SetTextMatrix(1, 2, text);

	text.Format(FORM_POINT, m_graphdata[0].cond.Inertiamoment);
	m_condset_grid.SetTextMatrix(2, 2, text);

	text.Format("%d", m_graphdata[0].cond.diskpieces);
	m_condset_grid.SetTextMatrix(3, 2, text);

	text.Format("%.1f", m_graphdata[0].saein.fTemperature);
	m_input_grid.SetTextMatrix(0, 2, text);

	text.Format("%.4f", m_graphdata[0].saein.fInner);
	m_input_grid.SetTextMatrix(1, 2, text);

	text.Format("%.4f", m_graphdata[0].saein.fOuter);
	m_input_grid.SetTextMatrix(2, 2, text);

	Double2CString(m_graphdata[0].saein.fThicklining, text);
	text.Format("%s", text);
	m_input_grid.SetTextMatrix(3, 2, text);

	text.Format("%.5f", m_graphdata[0].saein.fViscosity);
	m_input_grid.SetTextMatrix(4, 2, text);

	Double2CString(m_graphdata[0].saein.fFilmthick, text);
	text.Format("%s", text);
	m_input_grid.SetTextMatrix(5, 2, text);

	Double2CString(m_graphdata[0].saein.fSurfroughness, text);
	text.Format("%s", text);
	m_input_grid.SetTextMatrix(6, 2, text);

	Double2CString(m_graphdata[0].saein.fAsperityden, text);
	text.Format("%s", text);
	m_input_grid.SetTextMatrix(7, 2, text);
}

void CWaveDataDlg::OnCheckCh1() 
{
	// TODO: Add your control notification handler code here
	UINT nID = IDC_CHECK_CH1;
	OnChkCh(nID);
}

void CWaveDataDlg::OnCheckCh2() 
{
	// TODO: Add your control notification handler code here
	UINT nID = IDC_CHECK_CH2;
	OnChkCh(nID);
}

void CWaveDataDlg::OnCheckCh3() 
{
	// TODO: Add your control notification handler code here
	UINT nID = IDC_CHECK_CH3;
	OnChkCh(nID);
}

void CWaveDataDlg::OnCheckCh4() 
{
	// TODO: Add your control notification handler code here
	UINT nID = IDC_CHECK_CH4;
	OnChkCh(nID);
}

void CWaveDataDlg::OnButtonPrint() 
{
	// TODO: Add your control notification handler code here
	int	screenx, screeny;
	int	printx, printy;
	double	ratex, ratey;
	CDC* pDC = GetDC();
	screenx = pDC->GetDeviceCaps(LOGPIXELSX);
	screeny = pDC->GetDeviceCaps(LOGPIXELSY);
	ReleaseDC(pDC);
	CRect dlgrect, framerect;
	GetWindowRect(dlgrect);
	m_graph.GetWindowRect(framerect);
	int x, y;
	x = framerect.left	-	dlgrect.left;
	y = framerect.top	-	dlgrect.top;
	DWORD dwflags = PD_PAGENUMS | PD_USEDEVMODECOPIES | PD_HIDEPRINTTOFILE | PD_SELECTION;
	CPrintDialog m_printdlg(FALSE, dwflags, NULL);

	if(m_printdlg.DoModal() == IDOK)
	{
		CDC dc;
		dc.Attach(m_printdlg.GetPrinterDC());
		printx	=	dc.GetDeviceCaps(LOGPIXELSX);
		printy	=	dc.GetDeviceCaps(LOGPIXELSY);
		ratex	=	(double)(printx)/screenx;
		ratey	=	(double)(printy)/screeny;

		CClientDC pdc(this);
		CBitmap bmp;
		bmp.CreateCompatibleBitmap(&pdc, framerect.Width(), framerect.Height());
		CDC imagedc;
		imagedc.CreateCompatibleDC(&pdc);
		imagedc.SelectObject(&bmp);
		imagedc.StretchBlt(0, 0, framerect.Width()+20, framerect.Height(), &pdc, x-25, y-25, framerect.Width()+25, framerect.Height(), SRCCOPY);
		BITMAP bmap;
		bmp.GetBitmap(&bmap);
		int panelsize = 0;
		if(bmap.bmBitsPixel < 16)
		{
			panelsize = pow(2, bmap.bmBitsPixel * sizeof(RGBQUAD));
		}
		BITMAPINFO* bInfo = (BITMAPINFO*) LocalAlloc (LPTR, sizeof(BITMAPINFO) + panelsize);
		bInfo->bmiHeader.biClrImportant = 0;
		bInfo->bmiHeader.biBitCount = bmap.bmBitsPixel;
		bInfo->bmiHeader.biCompression = 0;
		bInfo->bmiHeader.biHeight = bmap.bmHeight;
		bInfo->bmiHeader.biPlanes = bmap.bmPlanes;
		bInfo->bmiHeader.biSize = sizeof(BITMAPINFO);
		bInfo->bmiHeader.biSizeImage = bmap.bmWidthBytes * bmap.bmHeight;
		bInfo->bmiHeader.biWidth = bmap.bmWidth;
		bInfo->bmiHeader.biXPelsPerMeter = 0;
		bInfo->bmiHeader.biYPelsPerMeter = 0;
		char *pData = new char[bmap.bmWidthBytes * bmap.bmHeight];
		::GetDIBits(imagedc.m_hDC, bmp, 0, bmap.bmHeight, pData, bInfo, DIB_RGB_COLORS);

		dc.StartDoc("print");
		::StretchDIBits(dc.m_hDC, 100, 100, (int)((framerect.Width()+25) * ratex), (int)(framerect.Height() * ratey), 0 ,0,
			framerect.Width()+25, framerect.Height(), pData, bInfo, DIB_RGB_COLORS, SRCCOPY);
		dc.EndDoc();
		LocalFree(bInfo);
		delete[] pData;
		bmp.DeleteObject();
	}
}
