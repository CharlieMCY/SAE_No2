// SAE_No2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "SAE_No2.h"
#include "SAE_No2Dlg.h"

#include "CommSetDlg.h"
#include "CondSetDlg.h"
#include "InMonitor.h"
#include "ScaleSetDlg.h"
#include "WaveDataDlg.h"

#include "math.h"
//#include "GetData.h"

/*#include "mclmcr.h"
#include "matrix.h"
#include "mclcppclass.h"
#include ".\measureRadius\measureRadius.h"*/

#include <windows.h>
#include <Dbt.h>

#include <fstream>

#pragma comment(lib, "measureRadius\\measureRadius.lib")
extern "C"_declspec(dllimport) float* getWJ();
extern "C"_declspec(dllimport) float getNJ();

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int comused[14]={0};
COM pCom[MaxSerialPortNum];

UINT tblChDispId[WAVE_CH_MAX] = {
	IDC_CHECK_CH1,
	IDC_CHECK_CH2,
	IDC_CHECK_CH3,
	IDC_CHECK_CH4,
};

UINT tblChGridId[WAVE_CH_MAX] = {	
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
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSAE_No2Dlg dialog

CSAE_No2Dlg::CSAE_No2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSAE_No2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSAE_No2Dlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_measY1.SetMode(MEASUREY,0,FALSE);
}

void CSAE_No2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSAE_No2Dlg)
	DDX_Control(pDX, IDC_CHECK_PAUSE, m_btn_pause);
	DDX_Control(pDX, IDC_EDIT_TIM, m_edt_tim);
	DDX_Control(pDX, IDC_EDIT_COE, m_edt_coe);
	DDX_Control(pDX, IDC_VSFLEXGRIDN_CH_1, m_ch1_grid);
	DDX_Control(pDX, IDC_VSFLEXGRIDN_CH_2, m_ch2_grid);
	DDX_Control(pDX, IDC_VSFLEXGRIDN_CH_3, m_ch3_grid);
	DDX_Control(pDX, IDC_VSFLEXGRIDN_CH_4, m_ch4_grid);
	DDX_Control(pDX, IDC_VSFLEXGRIDN_INPUT, m_input_grid);
	DDX_Control(pDX, IDC_XYDCAPACTIVEXCTRL, m_twain);
	DDX_Control(pDX, IDC_BUTTON_TS, m_btn_ts);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_STATIC_MEAS_Y1, m_measY1);
	DDX_Control(pDX, IDC_STATIC_GRAPH, m_graph);
}

BEGIN_MESSAGE_MAP(CSAE_No2Dlg, CDialog)
	//{{AFX_MSG_MAP(CSAE_No2Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_COND_SET, OnButtonCondSet)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_IN_MONITOR, OnButtonInMonitor)
	ON_BN_CLICKED(IDC_BUTTON_COMM_SET, OnButtonCommSet)
	ON_BN_CLICKED(IDC_BUTTON_SCALE_SET, OnButtonScaleSet)
	ON_BN_CLICKED(IDC_BUTTON_WAVE_DATA, OnButtonWaveData)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, OnButtonAbout)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_CHECK_CH1, OnCheckCh1)
	ON_BN_CLICKED(IDC_CHECK_CH2, OnCheckCh2)
	ON_BN_CLICKED(IDC_CHECK_CH3, OnCheckCh3)
	ON_BN_CLICKED(IDC_CHECK_CH4, OnCheckCh4)
	ON_BN_CLICKED(IDC_BUTTON_APPLY_DATA, OnButtonApplyData)
	ON_BN_CLICKED(IDC_CHECK_PAUSE, OnCheckPause)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnButtonPrint)
	ON_BN_CLICKED(IDC_BUTTON_GET_DATA, OnButtonGetData)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_NWJ, OnButtonNwj)
	ON_BN_CLICKED(IDC_BUTTON_ND, OnButtonNd)
	ON_MESSAGE(WM_COMM_RXCHAR,OnReceiveChar)
	ON_BN_CLICKED(IDC_CHECK_MUV, OnCheckMuv)
	ON_WM_DEVICECHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSAE_No2Dlg message handlers

BOOL CSAE_No2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//m_thread = NULL;
	Initialize();

	//ModifyStyle(WS_CAPTION,0,0);
	//SendMessage(WM_SYSCOMMAND,SC_MAXIMIZE,0);
	//ShowWindow(SW_SHOWMAXIMIZED);

	GUID  hid_guid={0x6bdd1fc6,0x810f,0x11d0,0xbe,0xc7,0x08,0x00,0x2b,0xe2,0x09,0x2f};
	DEV_BROADCAST_DEVICEINTERFACE DevInt;
	memset(&DevInt,0,sizeof(DEV_BROADCAST_DEVICEINTERFACE));
	DevInt.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
	DevInt.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	DevInt.dbcc_reserved = 0;
	DevInt.dbcc_classguid = hid_guid;
	HDEVNOTIFY hDevNotify;
	hDevNotify = RegisterDeviceNotification(m_hWnd, &DevInt, DEVICE_NOTIFY_WINDOW_HANDLE);
	if(!hDevNotify){
		int Err = GetLastError();
		printf("RegisterDeviceNotification failed: %lx.\n", Err);
		return (FALSE);
	}

	/*if( !measureRadiusInitialize()) {
			AfxMessageBox("初始话measureRadius.dll失败！");
	}*/

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSAE_No2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSAE_No2Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
	CDC* pDC = GetDC();
	screenx = pDC->GetDeviceCaps(LOGPIXELSX);
	screeny = pDC->GetDeviceCaps(LOGPIXELSY);
	ReleaseDC(pDC);
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSAE_No2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSAE_No2Dlg::OnButtonCommSet() 
{
	// TODO: Add your control notification handler code here
	CCommSetDlg dlg;
	dlg.DoModal();
}

void CSAE_No2Dlg::OnButtonCondSet() 
{
	// TODO: Add your control notification handler code here
	CCondSetDlg dlg;
	dlg.Initialize(g_data.Cond());
	dlg.DoModal();
}

void CSAE_No2Dlg::OnButtonInMonitor() 
{
	// TODO: Add your control notification handler code here
	CInMonitor dlg;
	dlg.DoModal();
}

void CSAE_No2Dlg::OnButtonWaveData() 
{
	// TODO: Add your control notification handler code here
	CWaveDataDlg dlg;
	dlg.DoModal();
}

void CSAE_No2Dlg::OnButtonClear() 
{
	// TODO: Add your control notification handler code here
	CEditEx *edit;
	CString text;
	//DWORD dwExit = 0;

	m_graph.RemoveAllLine();
	m_graph.Redraw(TRUE);
	start = false;
	/*if(m_thread != NULL)
	{
		GetExitCodeThread(m_thread, &dwExit);
		if(dwExit == STILL_ACTIVE)
			TerminateThread(m_thread, 0);
		delete m_thread;
	}
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);*/
	KillTimer(1);
	OnInitGraph();
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_PAUSE)->EnableWindow(FALSE);

	text.Format("%.2f",NOTE_WAVE_NUM*0.01);
	SetDlgItemText(IDC_STATIC_XMAX,text);
	text.Format("%.2f",NOTE_WAVE_NUM*0.01/2);
	SetDlgItemText(IDC_STATIC_XMID,text);

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

	text.Format("%.1f", 0.0);
	m_input_grid.SetTextMatrix(0, 2, text);
	text.Format("%.4f", 0.0);
	m_input_grid.SetTextMatrix(1, 2, text);
	text.Format("%.4f", 0.0);
	m_input_grid.SetTextMatrix(2, 2, text);
	text.Format("%.3f", 0.0);
	m_input_grid.SetTextMatrix(4, 2, text);
	Double2CString(0, text);
	text.Format("%s", text);
	m_input_grid.SetTextMatrix(6, 2, text);


	Double2CString(5.652e-4, text);
	text.Format("%s", text);
	m_input_grid.SetTextMatrix(3, 2, text);
	Double2CString(2.54e-5, text);
	text.Format("%s", text);
	m_input_grid.SetTextMatrix(5, 2, text);
	Double2CString(3e7, text);
	text.Format("%s", text);
	m_input_grid.SetTextMatrix(7, 2, text);

	GetDlgItem(IDC_BUTTON_APPLY_DATA)->EnableWindow(TRUE);

	/*Double2CString(24, text);
	text.Format("%s", text);
	m_input_grid.SetTextMatrix(0, 2, text);
	Double2CString(0.06175, text);
	text.Format("%s", text);
	m_input_grid.SetTextMatrix(1, 2, text);
	Double2CString(0.074, text);
	text.Format("%s", text);
	m_input_grid.SetTextMatrix(2, 2, text);

	Double2CString(0.1, text);
	text.Format("%s", text);
	m_input_grid.SetTextMatrix(4, 2, text);
	
	Double2CString(6e-6, text);
	text.Format("%s", text);
	m_input_grid.SetTextMatrix(6, 2, text);*/
}

void CSAE_No2Dlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	for (int i = 0; i < WAVE_CH_MAX; i++)
	{
		g_data.GraphPara()->chp[i].fMinimum = tempmin;
		g_data.GraphPara()->chp[i].fMaximum = tempmax;
	}
	DeleteDirectory("C:\\Users\\Public\\Pictures");
	SendMessage(WM_CLOSE, 0, 0);
}

void CSAE_No2Dlg::OnClose()
{
	if (int result = MessageBox("是否退出程序？", "确认", MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		CDialog::OnCancel();
	}
}

void CSAE_No2Dlg::OnButtonAbout() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}

void CSAE_No2Dlg::Initialize()
{
	MAXNode = 0;
	opensxt = 0;
	start = false;

	m_graphXMin = GetGraphDefaultXMin();
	m_graphXMax = GetGraphDefaultXMax();
	m_graphYMin = GetGraphDefaultYMin();
	m_graphYMax = GetGraphDefaultYMax();

	tempmin = GetGraphDefaultYMin();
	tempmax = GetGraphDefaultYMax();

	pSae.fCoefriction	= 0;
	pSae.fTimestop		= 0;

	InitControl();
	OnInitGraph();
}

void CSAE_No2Dlg::InitControl()
{
	CFGridCtrlLU *pGrid;
	CEditEx *edit;
	CString text;

	m_btn_ts.LoadStdImage(IDR_LEDA, _T("PNG"));
	m_btn_ts.LoadAltImage(IDR_LEDL, _T("PNG"));
	m_btn_ts.EnableToggle(TRUE);

	for (int i = 0; i < WAVE_CH_MAX; i++)
	{
		pGrid = (CFGridCtrlLU *) GetDlgItem(tblChGridId[i]);
		pGrid->SetFloatCell(1, 0, DEFAULT_INT_DIGIT, DEFAULT_DEC_DIGIT);//(row, col,intlen,declen)
		pGrid->SetFloatCell(1, 1, DEFAULT_INT_DIGIT, DEFAULT_DEC_DIGIT);
		pGrid->SetFloatCell(1, 2, DEFAULT_INT_DIGIT, DEFAULT_DEC_DIGIT);
	}

	edit = (CEditEx *) GetDlgItem(IDC_EDIT_COE);
	edit->SetFormat(EDITEX_FMTTYPE_DOUBLE);
	edit->SetReadOnly();
	text.Format(FORM_POINT_TM, pSae.fCoefriction);
	SetDlgItemText(IDC_EDIT_COE,text);
	edit = (CEditEx *) GetDlgItem(IDC_EDIT_TIM);
	edit->SetFormat(EDITEX_FMTTYPE_DOUBLE);
	edit->SetReadOnly();
	text.Format(FORM_POINT_TB, pSae.fTimestop);
	SetDlgItemText(IDC_EDIT_TIM,text);

	text.Format("%.1f", 0.0);
	m_input_grid.SetTextMatrix(0, 2, text);
	text.Format("%.4f", 0.0);
	m_input_grid.SetTextMatrix(1, 2, text);
	text.Format("%.4f", 0.0);
	m_input_grid.SetTextMatrix(2, 2, text);
	text.Format("%.3f", 0.0);
	m_input_grid.SetTextMatrix(4, 2, text);
	Double2CString(0, text);
	text.Format("%s", text);
	m_input_grid.SetTextMatrix(6, 2, text);

	Double2CString(5.652e-4, text);
	text.Format("%s", text);
	m_input_grid.SetTextMatrix(3, 2, text);
	Double2CString(2.54e-5, text);
	text.Format("%s", text);
	m_input_grid.SetTextMatrix(5, 2, text);
	Double2CString(3e7, text);
	text.Format("%s", text);
	m_input_grid.SetTextMatrix(7, 2, text);

	text.Format("%.2f",NOTE_WAVE_NUM*0.01);
	SetDlgItemText(IDC_STATIC_XMAX,text);
	text.Format("%.2f",NOTE_WAVE_NUM*0.01/2);
	SetDlgItemText(IDC_STATIC_XMID,text);

	GetDlgItem(IDC_CHECK_PAUSE)->EnableWindow(FALSE);
}

void CSAE_No2Dlg::OnInitGraph()
{
	m_graph.SetDataSize(WAVE_CH_MAX);
	m_graph.ShowFrame(FALSE);
	m_graph.AddPlotCursor(CURSORX, PS_SOLID, IGRAY);

	//Graph Style
	SetGraphStyle(g_data.GraphPara());

	m_measY1.ShowScale(TRUE, FALSE);
	m_measY1.SetScaleType(AMS_OUTSIDE);
	m_measY1.ShowMeasureDelta(FALSE);
	m_measY1.ShowLogZero(TRUE);
	m_measY1.ShowMeasureMinMax(FALSE, FALSE);
}

void CSAE_No2Dlg::SetGraphStyle(SAE_PARA *pGRP)
{
	m_graph.SetBkColor(pGRP->grp.clBgColor);					//背景
	m_graph.ShowGridX(pGRP->grp.bDispGrid, pGRP->grp.lsGrid);	//X グリッド線の表示/非表示(X). X軸のグリッド線の線種を指定し表示/非表示する(表示/非表示, グリッド線種, グリッド線色, グリッド線サイズ)
	m_graph.ShowGridY(pGRP->grp.bDispGrid, pGRP->grp.lsGrid);	//Y グリッド線の表示/非表示(Y). Y軸のグリッド線の線種を指定し表示/非表示する(表示/非表示, グリッド線種, グリッド線色, グリッド線サイズ)
	m_graph.GetAxisX().SetScaleColor(pGRP->grp.lsGrid.color);	//X軸目盛り軸の色の設定. 目盛り軸の色を設定する(COLORREF)
	m_graph.GetAxisY().SetScaleColor(pGRP->grp.lsGrid.color);	//Y軸目盛り軸の色の設定. 目盛り軸の色を設定する(COLORREF)
	
	DispChannel(pGRP);

	SetGraphStyleBase(pGRP);
}

void CSAE_No2Dlg::SetGraphStyleBase(SAE_PARA *pGRP)
{
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
	m_graph.Redraw();
}

void CSAE_No2Dlg::OnButtonScaleSet() 
{
	// TODO: Add your control notification handler code here
	CScaleSetDlg dlg;
	dlg.Initialize(WAVE_DLG_KIND_MAIN, g_data.GraphPara());
	if (dlg.DoModal() == IDOK)
	{
		SetGraphStyle(g_data.GraphPara());
	}
}

void CSAE_No2Dlg::DispChannel(SAE_PARA* pGRP)
{
	CButton *pbtnDisp;
	CFGridCtrlLU *pGrid;
	CString text;
	for (int i = 0; i < WAVE_CH_MAX; i++)
	{
		//Disp
		pbtnDisp = (CButton *) GetDlgItem(tblChDispId[i]);
		pbtnDisp->SetCheck(pGRP->chp[i].bDisp);

		pGrid = (CFGridCtrlLU *) GetDlgItem(tblChGridId[i]);
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

float CSAE_No2Dlg::GetGraphDefaultXMin() 
{
	return 0.0;
}

float CSAE_No2Dlg::GetGraphDefaultXMax()
{
	return (float) NOTE_WAVE_NUM;
}

float CSAE_No2Dlg::GetGraphDefaultYMin()
{
	return g_data.GetGraphYMin();
}

float CSAE_No2Dlg::GetGraphDefaultYMax()
{
	return g_data.GetGraphYMax();
}

float CSAE_No2Dlg::GetGraphXMin()
{
	return (float) m_graphXMin;
}

float CSAE_No2Dlg::GetGraphXMax()
{
	return (float) m_graphXMax;
}

float CSAE_No2Dlg::GetGraphYMin()
{
	return g_data.GetGraphYMin();
}

float CSAE_No2Dlg::GetGraphYMax()
{
	return g_data.GetGraphYMax();
}

void CSAE_No2Dlg::SetGraphXScale(double dblMin, double dblMax)
{
	m_graphXMin = dblMin;
	m_graphXMax = dblMax;
	m_graph.SetXScaleEx(dblMin, dblMax, 10, 2, TRUE, FALSE);	
}

void CSAE_No2Dlg::SetGraphYScale(double dblMin, double dblMax)
{
	m_graphYMin = dblMin;
	m_graphYMax = dblMax;
	m_graph.SetYScaleEx(dblMin, dblMax, 10, 2, TRUE, FALSE);
}

void CSAE_No2Dlg::OnChkCh(UINT nID)
{
	SAE_PARA GRP;
	memcpy(&GRP, g_data.GraphPara(), sizeof(SAE_PARA));

	for (int i = 0; i < WAVE_CH_MAX; i++)
	{
		if (nID == tblChDispId[i])
		{
			CButton *pBtn = (CButton *) GetDlgItem(nID);
			GRP.chp[i].bDisp = pBtn->GetCheck() ? TRUE : FALSE;
			g_data.SetGraphPara(&GRP);
			SetGraphStyle(g_data.GraphPara());
		}
	}
}

void CSAE_No2Dlg::DispGraph()
{
	int i;
	pSae.cond.Initvelocity	= g_data.Cond()->Initvelocity;
	pSae.cond.Surfpressure	= g_data.Cond()->Surfpressure;
	pSae.cond.Inertiamoment	= g_data.Cond()->Inertiamoment;
	pSae.cond.diskpieces	= g_data.Cond()->diskpieces;
	//画面更新STOP
	//LockWindowUpdate();

	for (i = 0; i < WAVE_CH_MAX; i++)
	{
		m_graph.GetLine(i).ClearAllPoint();
	}

	/*for (i = 0; i < (int)(pSae.fTimestop*20); i++)
	{
		while(w_pause){;}
		m_graph.GetLine(WAVE_CH_1).AddPoint(i, pSae.saem[i].fRotavelocity);
		m_graph.GetLine(WAVE_CH_2).AddPoint(i, pSae.saem[i].fPreforce);
		m_graph.GetLine(WAVE_CH_3).AddPoint(i, pSae.saem[i].fTorque);
		m_graph.GetLine(WAVE_CH_4).AddPoint(i, pSae.saem[i].fFlimthick);
		time += pSae.fTimestop/((int)(pSae.fTimestop*20));
		DispTime(time);
		SetGraphStyleBase(g_data.GraphPara());
		//Sleep(int(pSae.fTimestop*1000)/NOTE_WAVE_NUM-1200/NOTE_WAVE_NUM);
		Sleep(50);
	}

	CString text;
	text.Format("%.6f",pSae.fCoefriction);
	SetDlgItemText(IDC_EDIT_COE,text);
	UpdateWindow();

	for (i = (int)(pSae.fTimestop*20); i < NOTE_WAVE_NUM; i++)
	{
		while(w_pause){;}
		m_graph.GetLine(WAVE_CH_1).AddPoint(i, pSae.saem[i].fRotavelocity);
		m_graph.GetLine(WAVE_CH_2).AddPoint(i, pSae.saem[i].fPreforce);
		m_graph.GetLine(WAVE_CH_3).AddPoint(i, pSae.saem[i].fTorque);
		m_graph.GetLine(WAVE_CH_4).AddPoint(i, pSae.saem[i].fFlimthick);
		SetGraphStyleBase(g_data.GraphPara());
		time += pSae.fTimestop/((int)(pSae.fTimestop*20));
		//Sleep(int(pSae.fTimestop*1000)/NOTE_WAVE_NUM-1200/NOTE_WAVE_NUM);
		Sleep(50);
	}

	GetDlgItem(IDC_BUTTON_CLEAR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_APPLY_DATA)->EnableWindow(TRUE);

	m_thread = NULL;*/
	
	//画面更新
	//UnlockWindowUpdate();
}

void CSAE_No2Dlg::DispTime(float time)
{
	CString text;
	text.Format(FORM_POINT_TB,time);
	SetDlgItemText(IDC_EDIT_TIM,text);
	UpdateWindow();
}

int pointtime;
double w_rel;
double Tc;
double h;
double indextime;
double endtime;
double Finmin;
double muu;
void CSAE_No2Dlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	CString text;
	start = true;
	text.Format("%.6f",0);
	SetDlgItemText(IDC_EDIT_COE,text);

	text.Format("%.2f",NOTE_WAVE_NUM*0.01);
	SetDlgItemText(IDC_STATIC_XMAX,text);
	text.Format("%.2f",NOTE_WAVE_NUM*0.01/2);
	SetDlgItemText(IDC_STATIC_XMID,text);

	UpdateWindow();
	//GetDlgItem(IDC_BUTTON_CLEAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_APPLY_DATA)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_PAUSE)->EnableWindow(TRUE);
	w_pause = FALSE;
	CButton* pbtnDisp = (CButton *) GetDlgItem(IDC_CHECK_PAUSE);
	pbtnDisp->SetCheck(w_pause);
	//m_thread = AfxBeginThread(ThreadFunc, this);
	DispGraph();

	pointtime=0;
	w_rel=pSae.cond.Initvelocity;
	Tc=0;
	h=pSae.saein.fFilmthick;
	indextime = 0;
	endtime = 0;
	Finmin = 0;

	m_clumod.Temp0 = pSae.saein.fTemperature; 			//环境温度
	m_clumod.ro = pSae.saein.fOuter;				//外径
	m_clumod.ri = pSae.saein.fInner;				//内径
	m_clumod.sigma = pSae.saein.fSurfroughness;			//表面粗糙度
	m_clumod.h0 = pSae.saein.fFilmthick;				//初始膜厚
	m_clumod.d = pSae.saein.fThicklining;				//摩擦材厚度
	m_clumod.m = pSae.saein.fAsperityden;				//粗糙密度
	m_clumod.mu0 = pSae.saein.fViscosity;				//粘度
	m_clumod.mu = 6.23e-3;				//动力粘度
	m_clumod.w0 = pSae.cond.Initvelocity;				//初始转速
	m_clumod.Jm = pSae.cond.Inertiamoment;				//转动惯量
	m_clumod.faces = pSae.cond.diskpieces;			//摩擦片面数
	m_clumod.Pre = pSae.cond.Surfpressure;				//设定面压
	m_clumod.Temp = 80;			//设定油温
	m_clumod.Tc_k1 = 0;
	m_clumod.wrel_k1  = pSae.cond.Initvelocity;

	pSae.saem = (SAE_MINI*)malloc(NOTE_WAVE_NUM*sizeof(SAE_MINI));
	m_graphXMax=GetGraphDefaultXMax();
	MAXNode=0;


	UpdateData(false);
	//LockWindowUpdate();
	SetTimer(1,10,NULL);
}

double T_BL, T_HL;
double Papp;
void CSAE_No2Dlg::OnTimer(UINT nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
		if(w_pause){KillTimer(1);}
		if (pointtime >= GetGraphDefaultXMax()) {
			CString text;
			MAXNode+=1;
			m_graphXMax=MAXNode;
			pSae.saem = (SAE_MINI*)realloc(pSae.saem,MAXNode*sizeof(SAE_MINI));
			text.Format("%.2f",indextime);
			SetDlgItemText(IDC_STATIC_XMAX,text);
			text.Format("%.2f",indextime/2);
			SetDlgItemText(IDC_STATIC_XMID,text);
			//OnInitGraph();
		}

		if (w_rel > 0) {
			if (indextime <= 0.1) {
				Finmin = 0;
			}
			else if (indextime > 0.1) {
				Finmin = m_clumod.Pre * 10 * indextime - m_clumod.Pre;
				if (Finmin >= m_clumod.Pre) Finmin=m_clumod.Pre;
			} 
			
			m_clumod.Papp = m_clumod.WetClutchPistonSetting(Finmin);
			pSae.saem[pointtime].fPreforce = Finmin;
			h = m_clumod.WetClutchFilmThickness(m_clumod.Papp, m_clumod.Temp, h);
			pSae.saem[pointtime].fFlimthick = h;
			
			w_rel = m_clumod.WetClutchUnlocked(m_clumod.Temp, m_clumod.Papp, h, Tc, w_rel);
			pSae.saem[pointtime].fRotavelocity = w_rel;
			if (w_rel <= 0) w_rel = 0;
			
			T_BL = m_clumod.WetClutchMLandBLmode(h, w_rel, m_clumod.Papp, m_clumod.w0);
			
			T_HL = m_clumod.WetClutchMLandHLmode(h, w_rel, m_clumod.w0);
			if (T_HL < 0) T_HL = 0;

			muu = m_clumod.WetClutchMuModel(Finmin*(1e3)*Ap, T_HL+T_BL);
			pSae.saem[pointtime].fCoe = muu;
			
			Tc = T_HL+T_BL;
			pSae.saem[pointtime].fTorque = Tc;
			pSae.saem[pointtime].fTHL = T_HL;
			pSae.saem[pointtime].fTBL = T_BL;
			
		}
		else if (endtime <= 0.3){
			if (endtime <= 0.1) {
				Finmin = m_clumod.Pre;
			}
			else if (endtime <= 0.2) {
				Finmin = - m_clumod.Pre * 10 * endtime + m_clumod.Pre * 2;
				if (Finmin <= 0) Finmin=0;
			}
			else if (endtime <= 0.3)
				Finmin = 0;
			
			m_clumod.Papp = m_clumod.WetClutchPistonSetting(Finmin);
			pSae.saem[pointtime].fPreforce = Finmin;
			muu = m_clumod.WetClutchMuModel(Finmin*(1e3)*Ap, T_HL+T_BL);
			pSae.saem[pointtime].fCoe = muu;
			h = m_clumod.WetClutchFilmThickness(m_clumod.Papp, m_clumod.Temp, h);
			pSae.saem[pointtime].fFlimthick = h;
			pSae.saem[pointtime].fTorque=0;
			pSae.saem[pointtime].fTHL=0;
			pSae.saem[pointtime].fTBL=0;
			pSae.saem[pointtime].fRotavelocity=0;
			endtime += 0.01;
			
		}else {
			pSae.saem[pointtime].fPreforce = Finmin;
			pSae.saem[pointtime].fFlimthick = h;
			pSae.saem[pointtime].fTorque=0;
			pSae.saem[pointtime].fTHL=0;
			pSae.saem[pointtime].fTBL=0;
			pSae.saem[pointtime].fRotavelocity=0;
			endtime += 0.01;
		}

		//if(pSae.saem[pointtime].fRotavelocity/100>)

		m_graph.GetLine(WAVE_CH_1).AddPoint(pointtime, pSae.saem[pointtime].fRotavelocity/100);
		m_graph.GetLine(WAVE_CH_2).AddPoint(pointtime, pSae.saem[pointtime].fPreforce/10);
		m_graph.GetLine(WAVE_CH_3).AddPoint(pointtime, pSae.saem[pointtime].fTorque);
		m_graph.GetLine(WAVE_CH_4).AddPoint(pointtime, pSae.saem[pointtime].fFlimthick*100000);
		if (pSae.saem[pointtime].fRotavelocity>0) {
			DispTime(indextime);
			pSae.fTimestop = indextime;
			pSae.fCoefriction = pSae.saem[pointtime].fCoe;
		}
		SetGraphStyleBase(g_data.GraphPara());
		indextime += 0.01;
		pointtime++;
		MAXNode = pointtime;
		if (endtime >= 0.6) {
			KillTimer(1);
			//GetDlgItem(IDC_BUTTON_CLEAR)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_APPLY_DATA)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK_PAUSE)->EnableWindow(FALSE);
			CString text;
			text.Format("%.6f",pSae.fCoefriction);
			SetDlgItemText(IDC_EDIT_COE,text);
			if (pointtime >= GetGraphDefaultXMax()) {
				text.Format("%.2f",indextime);
				SetDlgItemText(IDC_STATIC_XMAX,text);
				text.Format("%.2f",indextime/2);
				SetDlgItemText(IDC_STATIC_XMID,text);
			}
		}
		break;
	case 2:
		CString temp;
		temp="20";
		temp=ChangeCharstr2Hexstr(temp);
		m_SerialPort.WriteToPort(temp.GetBuffer(temp.GetLength()),temp.GetLength());
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

/*UINT CSAE_No2Dlg::ThreadFunc(LPVOID pThreadParam)
{
	CSAE_No2Dlg* pDlg = (CSAE_No2Dlg*) pThreadParam;
	pDlg->DispGraph();
	return 0;
}*/

void CSAE_No2Dlg::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	CTime time = CTime::GetCurrentTime();
	CString m_strTime = time.Format("%Y%m%d %H-%M-%S");
	CFileDialog dlg(FALSE, NULL, m_strTime, OFN_HIDEREADONLY| OFN_OVERWRITEPROMPT,
		"All Files(*.csv)| *.csv||", AfxGetMainWnd());
	CString strPath;
	if (dlg.DoModal() == IDOK)
	{
		strPath = dlg.GetPathName();
		if (strPath.Right(4) != ".csv")
			strPath += ".csv";
		FILE* fp;
		char filename[1000];
		strncpy (filename, (LPCTSTR)strPath, sizeof(filename));
		fp=fopen(filename, "w+");
		SaveWaveData(fp);
		fclose(fp);
	}
}

void CSAE_No2Dlg::SaveWaveData(FILE *fp)
{
	int i;
	memcpy(&pSae.cond, g_data.Cond(), sizeof(COND));
	fprintf(fp, "%d\n",MAXNode);
	fprintf(fp, "%s,%s,%s,%s\n", "初始转速", "设定压力", "转动惯量", "摩擦片面数");
	fprintf(fp, "%d, %f, %f, %d\n", pSae.cond.Initvelocity, pSae.cond.Surfpressure,
		pSae.cond.Inertiamoment, pSae.cond.diskpieces);
	fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s\n", "温度", "摩擦片内径", "摩擦片外径", "摩擦材厚度", 
		"润滑油粘度", "初始油膜厚度", "摩擦材表面粗糙度", "粗糙密度");
	fprintf(fp, "%f, %f, %f, %.7f, %f, %.7f, %.9f, %.2f\n", pSae.saein.fTemperature, pSae.saein.fInner, pSae.saein.fOuter,
		pSae.saein.fThicklining, pSae.saein.fViscosity, pSae.saein.fFilmthick, pSae.saein.fSurfroughness, pSae.saein.fAsperityden);
	fprintf(fp, "%s,%s\n", "最大摩擦系数", "停止时间");
	fprintf(fp, "%f, %f\n", pSae.fCoefriction, pSae.fTimestop);
	fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s\n", "时间", "转速", "压力", "扭矩", "粘性扭矩", "粗糙接触扭矩", "油膜厚度", "动摩擦系数");
	for (i = 0; i < MAXNode; i++)
	{
		fprintf(fp, "%.2f, %f, %f, %f, %f, %f, %f, %f\n", i/100.0, pSae.saem[i].fRotavelocity, 
			pSae.saem[i].fPreforce, pSae.saem[i].fTorque, pSae.saem[i].fTHL, pSae.saem[i].fTBL, 
			pSae.saem[i].fFlimthick, pSae.saem[i].fCoe);
	}
}
void CSAE_No2Dlg::OnCheckCh1() 
{
	// TODO: Add your control notification handler code here
	UINT nID = IDC_CHECK_CH1;
	OnChkCh(nID);
}

void CSAE_No2Dlg::OnCheckCh2() 
{
	// TODO: Add your control notification handler code here
	UINT nID = IDC_CHECK_CH2;
	OnChkCh(nID);
}

void CSAE_No2Dlg::OnCheckCh3() 
{
	// TODO: Add your control notification handler code here
	UINT nID = IDC_CHECK_CH3;
	OnChkCh(nID);
}

void CSAE_No2Dlg::OnCheckCh4() 
{
	// TODO: Add your control notification handler code here
	UINT nID = IDC_CHECK_CH4;
	OnChkCh(nID);
}

void CSAE_No2Dlg::OnButtonApplyData() 
{
	// TODO: Add your control notification handler code here
	CVSFlexGrid *pVsFG;
	CString strData;

	pVsFG = (CVSFlexGrid *)GetDlgItem( IDC_VSFLEXGRIDN_INPUT );

	strData = pVsFG->GetTextMatrix(0, 2);
	pSae.saein.fTemperature = ( double )atof( strData );

	strData = pVsFG->GetTextMatrix(1, 2);
	pSae.saein.fInner = ( double )atof( strData );

	strData = pVsFG->GetTextMatrix(2, 2);
	pSae.saein.fOuter = ( double )atof( strData );

	strData = pVsFG->GetTextMatrix(3, 2);
	pSae.saein.fThicklining = ( double )atof( strData );

	strData = pVsFG->GetTextMatrix(4, 2);
	pSae.saein.fViscosity = ( double )atof( strData );

	strData = pVsFG->GetTextMatrix(5, 2);
	pSae.saein.fFilmthick = ( double )atof( strData );

	strData = pVsFG->GetTextMatrix(6, 2);
	pSae.saein.fSurfroughness = ( double )atof( strData );

	strData = pVsFG->GetTextMatrix(7, 2);
	pSae.saein.fAsperityden = ( double )atof( strData );
}

void CSAE_No2Dlg::OnCheckPause() 
{
	// TODO: Add your control notification handler code here
	CButton *pBtn = (CButton *) GetDlgItem(IDC_CHECK_PAUSE);
	w_pause = pBtn->GetCheck() ? TRUE : FALSE;
	if (!w_pause) SetTimer(1,10,NULL);
}

void CSAE_No2Dlg::OnButtonPrint() 
{
	// TODO: Add your control notification handler code here
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

int flag=0;
int Count=0;
int result[1024] = {0};
CString vresult=_T("");
CString m_name;
float resulttemp = 0;
float resulttemp2 = 0;

static long HTOI(const string& s) {
   long res=0;
   for (int i = 0; i < s.size(); i++) {
	   long tmp=0;
	   if (s[i] >= '0' && s[i] <= '9')
		   tmp = s[i] - '0';
	   if (s[i] >= 'A' && s[i] <= 'F')
		   tmp = s[i] - 'A' + 10;
	   if (s[i] >= 'a' && s[i] <= 'f')
		   tmp = s[i] - 'a' + 10;
	   res=res * 16 + tmp;
   }
   return res;
}

CString CSAE_No2Dlg::ChangeCharstr2Hexstr(CString Charstr)
{
	CString Hexstr=_T("");
	Charstr.MakeUpper();
	HexStringFilter(Charstr);
	int Length=Charstr.GetLength();
	if(Length%2)
		Charstr.Delete(Length-1);
	Length=Charstr.GetLength();
	for(int i=0;i<Length/2;i++)
	{
		Hexstr+=CombineHexChar(Charstr.GetAt(i*2),Charstr.GetAt(i*2+1));
	}
	return Hexstr;
}

void CSAE_No2Dlg::HexStringFilter(CString &str)
{
	BOOL bOK;
	for(int i=0;i<str.GetLength();)
	{
		bOK=((str.GetAt(i)>='0')&&(str.GetAt(i)<='9'))||
			((str.GetAt(i)>='A')&&(str.GetAt(i)<='F'))||
			((str.GetAt(i)>='a')&&(str.GetAt(i)<='f'));
		if(!bOK)
			str.Delete(i);
		else i++;	
	}
}
char CSAE_No2Dlg::CombineHexChar(char CharH,char CharL)
{
	char result;
	CString temp;
	if(CharH>='0'&&CharH<='9')			result=(CharH-'0');
	else if(CharH>='a'&&CharH<='f')		result=(CharH-'a'+10);
	else if(CharH>='A'&&CharH<='F')		result=(CharH-'A'+10);
	else								result=0;
	result<<=4;	
	if(CharL>='0'&&CharL<='9')			result+=(CharL-'0');
	else if(CharL>='a'&&CharL<='f')		result+=(CharL-'a'+10);
	else if(CharL>='A'&&CharL<='F')		result+=(CharL-'A'+10);
	else								result+=0;
	return result;
}


CString CSAE_No2Dlg::DevideHexChar(char HexChar)
{
	CString result=_T("");
	int temp=(HexChar&0xF0)>>4;
	if(temp<10)
		result+=(temp+'0');
	else 
		result+=(temp+'A'-10);
	temp=HexChar&0x0F;
	if(temp<10)
		result+=(temp+'0');
	else 
		result+=(temp+'A'-10);
	return result;
}

CWaitDlg* wdlg;
void CSAE_No2Dlg::OnButtonGetData() 
{
	// TODO: Add your control notification handler code here
	/*CGetData dlg;
	//dlg.DoModal();

	if (dlg.DoModal() == IDCANCEL)
	{
		CString text;
		if (pSae.saein.fTemperature != 0) {
			text.Format("%.1f", pSae.saein.fTemperature);
			m_input_grid.SetTextMatrix(0, 2, text);
		}
		if (pSae.saein.fInner != 0) {
			text.Format("%.4f", pSae.saein.fInner);
			m_input_grid.SetTextMatrix(1, 2, text);
		}
		if (pSae.saein.fOuter != 0) {
			text.Format("%.4f", pSae.saein.fOuter);
			m_input_grid.SetTextMatrix(2, 2, text);
		}
		if (pSae.saein.fViscosity != 0) {
			text.Format(FORM_POINT, pSae.saein.fViscosity);
			m_input_grid.SetTextMatrix(4, 2, text);
		}
		if (pSae.saein.fSurfroughness != 0) {
			Double2CString(pSae.saein.fSurfroughness, text);
			text.Format("%s", text);
			m_input_grid.SetTextMatrix(6, 2, text);
		}
	}*/

	//UpdateData(true);
	//CString temp;
	//m_name = temp;
	int SelPortNO,SelBaudRate,SelDataBits,SelStopBits;
	char SelParity;
	//UpdateData(true);
	//temp.Delete(0,3);
	m_name = "1";
	SelPortNO=7;
	SelBaudRate=4800;
	SelDataBits=8;
	SelParity='N';
	SelStopBits=1;
	Count = 0;
	flag = 0;
	memset(result, 0, sizeof(result));
	if(m_SerialPort.InitPort(this->m_hWnd,SelPortNO,SelBaudRate,SelParity,SelDataBits,SelStopBits,EV_RXCHAR|EV_CTS,512))		
	{
		wdlg = new CWaitDlg;
		wdlg->Create(IDD_DIALOG_WAIT,this);
		wdlg->m_msg="请按‘START’键开始并稍候...";
		wdlg->UpdateData(FALSE);
		wdlg->CenterWindow();
		wdlg->ShowWindow(SW_SHOW);
		wdlg->RedrawWindow();
		m_SerialPort.StartMonitoring();
		//UpdateData(false);
		SetTimer(2,100,NULL);
	}
	else {
		AfxMessageBox("串口8打开错误！\n请使用其他串口。");
	}
}

static void mesRad() {
	__try {
		float *p;
		p = getWJ();
		//resulttemp = getWJ();
		resulttemp = p[0];
		TRACE("%f",resulttemp);
		//resulttemp2 = getNJ();
		resulttemp2 = p[1];
		TRACE("%f",resulttemp2);
	}
	__except( EXCEPTION_EXECUTE_HANDLER ) {
		AfxMessageBox("图像处理失败！");
	}
}

void CSAE_No2Dlg::OnButtonNwj() 
{
	// TODO: Add your control notification handler code here
	
	CString text;
	fstream _file;

	wdlg = new CWaitDlg;
	wdlg->Create(IDD_DIALOG_WAIT,this);
	wdlg->m_msg="正在处理，请稍候...";
	wdlg->UpdateData(FALSE);
	wdlg->CenterWindow();
	wdlg->ShowWindow(SW_SHOW);
	wdlg->RedrawWindow();

	m_twain.StartRunEx(0, 3488, 2616, 2);
	m_twain.OpenAutomaticExposure(1);
	m_twain.SetBrightness(200);
	m_twain.CaptureImage("aa.bmp");

	_file.open("aa.bmp",ios::in);
	if(!_file) {
		wdlg->DestroyWindow();
		AfxMessageBox("拍摄图片失败！");
	}
	else {
		_file.close();
		/*if( FAILED(CoInitialize(NULL)))
		{
			AfxMessageBox("初始化控件失败！");
			return;
		}
		ImeasureRadius *SNRclass = NULL;
		HRESULT hr;
		hr = CoCreateInstance(CLSID_measureRadius,NULL,CLSCTX_ALL,IID_ImeasureRadius,(void**)&SNRclass);
		if(FAILED(hr))
		{
			AfxMessageBox("创建实例失败！");
			return;
		}
		VARIANT SNR1,SNR2;
		SNRclass->measureRadius(2,&SNR1,&SNR2);
		resulttemp=SNR1.dblVal;
		resulttemp2=SNR2.dblVal;
		resulttemp /= 200;
		resulttemp2 /= 200;
		if (resulttemp != 0 && resulttemp2 != 0) {
			AfxMessageBox("获取数据成功！");
		}
		else AfxMessageBox("获取数据失败！");*/

		/*mwArray mwRD(1, 1, mxDOUBLE_CLASS);
		mwArray mwRX(1, 1, mxDOUBLE_CLASS);
		mwArray ctrl(1, 1, mxDOUBLE_CLASS);
		double x[1] = {0};
		ctrl.SetData(x,1);
		measureRadius(2, mwRD, mwRX, ctrl);*/

		//m_thread = AfxBeginThread(ThreadFunc, this, 0, 0, 0, NULL);

		/*DWORD dwExit = 0;
		if (m_thread != NULL) {
			GetExitCodeThread(m_thread, &dwExit);
			while (dwExit == STILL_ACTIVE) {
				GetExitCodeThread(m_thread, &dwExit);
			}
			TerminateThread(m_thread, 0);
			delete m_thread;
		}*/

		mesRad();

		resulttemp /= 100;
		resulttemp2 /= 100;
		if (resulttemp != 0 && resulttemp2 != 0) {
			wdlg->DestroyWindow();
			//AfxMessageBox("获取数据成功！");
			CClientDC *pDC = new CClientDC(GetDlgItem(IDC_STATIC_TX));
			CRect rect;
			GetDlgItem(IDC_STATIC_TX)->GetWindowRect(&rect);
			Graphics graphics(pDC->m_hDC);	// Create a GDI+ graphics object
			Image image(L"abcd.png");	// Construct an image
			graphics.DrawImage(&image, 0, 0, rect.Width(), rect.Height());
			text.Format("%.4f", resulttemp2);
			m_input_grid.SetTextMatrix(1, 2, text);
			text.Format("%.4f", resulttemp);
			m_input_grid.SetTextMatrix(2, 2, text);
		}
		else {
			wdlg->DestroyWindow();
			AfxMessageBox("获取数据失败！");
		}

		DeleteDirectory("C:\\Users\\Public\\Pictures");
		//remove("abc.png");
	}
}

void CSAE_No2Dlg::OnButtonNd() 
{
	// TODO: Add your control notification handler code here
	int SelPortNO,SelBaudRate,SelDataBits,SelStopBits;
	char SelParity;
	//UpdateData(true);
	//temp.Delete(0,3);
	m_name = "2";
	SelPortNO=3;
	SelBaudRate=9600;
	SelDataBits=8;
	SelParity='N';
	SelStopBits=1;
	Count = 0;
	flag = 0;
	memset(result, 0, sizeof(result));
	if(m_SerialPort.InitPort(this->m_hWnd,SelPortNO,SelBaudRate,SelParity,SelDataBits,SelStopBits,EV_RXCHAR|EV_CTS,512))		
	{
		m_SerialPort.StartMonitoring();
		//UpdateData(false);
		CString sendtext;
		sendtext="01 03 20 32 00 01 2E 05";// 01 03 20 37 00 01 3E 04 01 03 20 38 00 01 0E 07";
		sendtext=ChangeCharstr2Hexstr(sendtext);
		m_SerialPort.WriteToPort(sendtext.GetBuffer(sendtext.GetLength()),sendtext.GetLength());
	}
	else {
		AfxMessageBox("串口3打开错误！\n请使用其他串口。");
	}
}

void CSAE_No2Dlg::OnReceiveChar(UINT ch, LONG port)
{
	CString temp;
	CString sendtext;
	CString text;
	if (m_name == "1") {
		if (Count==6) {
			resulttemp=(1000*result[1]+100*result[2]+10*result[3]+result[4])/(float)pow(10,result[5]);
			resulttemp /= 1e6;
			//AfxMessageBox("数据获取成功！");
			Double2CString(resulttemp, text);
			text.Format("%s", text);
			m_input_grid.SetTextMatrix(6, 2, text);
			KillTimer(2);
			m_SerialPort.StopMonitoring();
			m_SerialPort.ClosePort();
			TRACE("OK");
			wdlg->DestroyWindow();
			//GetDlgItem(IDC_BUTTON_APPLY)->EnableWindow(TRUE);
		}
		if (flag==0) {
			temp = DevideHexChar(ch);
			if (temp == "2D"||temp == "25"||temp == "29") {
				flag =1;
			}
		}
		else {
			temp = DevideHexChar(ch);
			temp.Delete(0,1);
			result[Count]=atoi(temp);
			Count++;
		}
	}
	if (m_name == "2") {
		if (flag == 0) {
			temp = DevideHexChar(ch);
			Count++;
			if (Count == 4 || Count == 5) {
				vresult += temp;
			}
			if (Count == 7) {
				resulttemp = HTOI((string)vresult)/10.0;
				if (resulttemp != 0) {
					text.Format("%.1f", resulttemp);
					m_input_grid.SetTextMatrix(0, 2, text);
				}
				flag = 1;
				Count = 0;
				vresult=_T("");
				//AfxMessageBox("Get data successfully!");
				sendtext="01 03 20 37 00 01 3E 04";
				sendtext=ChangeCharstr2Hexstr(sendtext);
				m_SerialPort.WriteToPort(sendtext.GetBuffer(sendtext.GetLength()),sendtext.GetLength());
			}
		}
		else {
			if (flag == 1) {
				temp = DevideHexChar(ch);
				Count++;
				if (Count == 4 || Count == 5) {
					vresult += temp;
				}
				if (Count == 7) {
					resulttemp2 = (double)HTOI((string)vresult);
					flag = 2;
					Count = 0;
					vresult=_T("");
					sendtext="01 03 20 38 00 01 0E 07";
					sendtext=ChangeCharstr2Hexstr(sendtext);
					m_SerialPort.WriteToPort(sendtext.GetBuffer(sendtext.GetLength()),sendtext.GetLength());
				}
			}
			if (flag == 2) {
				temp = DevideHexChar(ch);
				Count++;
				if (Count == 5 || Count == 6) {
					vresult += temp;
				}
				if (Count == 7) {
					resulttemp2 = ((double)HTOI((string)vresult) + resulttemp2 * 16 * 16 * 16 * 16)/10;
					resulttemp2 /= 1000;
					//resulttemp2 = (6+rand()%100/100)/1000;
					vresult=_T("");
					if (resulttemp2 != 0) {
						text.Format("%.4f", resulttemp2);
						m_input_grid.SetTextMatrix(4, 2, text);
					}
					//AfxMessageBox("获取数据成功！");
					m_SerialPort.StopMonitoring();
					m_SerialPort.ClosePort();
				}
			}
		}
	}
}

BOOL CSAE_No2Dlg::OnDeviceChange(UINT nEventType,DWORD dwData)
{
	DEV_BROADCAST_DEVICEINTERFACE* dbd = (DEV_BROADCAST_DEVICEINTERFACE*) dwData;	//这里进行信息匹配,比如guid等
	
	//针对各个事件进行处理
	switch (nEventType)
	{
		case DBT_DEVICEREMOVECOMPLETE:
			//m_btn_ts.SetImage(0);
			//MessageBox("移除USB");
			break;
		case DBT_DEVICEARRIVAL:
			if (opensxt == 0) {
				m_twain.Initial();
				m_btn_ts.SetImage(1);
				opensxt = 1;
			}
			//MessageBox("发现USB");
			break;
		default:
			break;
	}
	return TRUE;
}

void CSAE_No2Dlg::DeleteDirectory(char* sDirName) {
	char sPath[200];
	strcpy(sPath, sDirName);
	CFileFind ff;
	BOOL bFound;
	char sTempFileFind[200];
	strcpy(sTempFileFind, sPath);
	strcat(sTempFileFind, "\\*.jpg");
	bFound = ff.FindFile(sTempFileFind);
	while(bFound) {
		bFound = ff.FindNextFile();
		CString sFilePath = ff.GetFilePath();
		if(ff.IsDirectory()) {
			if(!ff.IsDots())
				DeleteDirectory((LPSTR)(LPCTSTR)sFilePath);
		} else {
			if(ff.IsReadOnly()) {
				SetFileAttributes(sFilePath, FILE_ATTRIBUTE_NORMAL);
			}
				DeleteFile(sFilePath);
		}
	}
	ff.Close();
	SetFileAttributes(sPath, FILE_ATTRIBUTE_NORMAL);
	if (!strcmp(sPath,sDirName)) {
		return;
	}
	RemoveDirectory(sPath);
}

void CSAE_No2Dlg::OnCheckMuv() 
{
	// TODO: Add your control notification handler code here
	CButton *pBtn = (CButton *) GetDlgItem(IDC_CHECK_MUV);
	w_muv = pBtn->GetCheck() ? TRUE : FALSE;
	CFGridCtrlLU *pGrid;
	CString text;
	int i;
	//CString text;
	if (w_muv) {
		CWnd *pWnd;
        pWnd = GetDlgItem(IDC_CHECK_CH2);	//获取控件指针，IDC_EDIT1为控件ID号
        pWnd->ShowWindow( SW_HIDE );		//隐藏控件
		pWnd = GetDlgItem(IDC_CHECK_CH3);
        pWnd->ShowWindow( SW_HIDE );
		pWnd = GetDlgItem(IDC_CHECK_CH4);
        pWnd->ShowWindow( SW_HIDE );
		pWnd = GetDlgItem(IDC_VSFLEXGRIDN_CH_2);
        pWnd->ShowWindow( SW_HIDE );
		pWnd = GetDlgItem(IDC_VSFLEXGRIDN_CH_3);
        pWnd->ShowWindow( SW_HIDE );
		pWnd = GetDlgItem(IDC_VSFLEXGRIDN_CH_4);
        pWnd->ShowWindow( SW_HIDE );
		pGrid = (CFGridCtrlLU *) GetDlgItem(tblChGridId[0]);
		pGrid->SetTextMatrix(0, 0, _T("        摩擦系数         	"));

		tempmin = g_data.GraphPara()->chp[0].fMinimum;
		tempmax = g_data.GraphPara()->chp[0].fMaximum;
		for (i = 0; i < WAVE_CH_MAX; i++)
		{
			m_graph.GetLine(i).ClearAllPoint();
			g_data.GraphPara()->chp[i].fMinimum = 10;
			g_data.GraphPara()->chp[i].fMaximum = 20;
		}
		DispChannel(g_data.GraphPara());
		if ( start) {
			m_graphXMax = m_clumod.w0;
			text.Format("%.0f",m_clumod.w0);
			SetDlgItemText(IDC_STATIC_XMAX,text);
			text.Format("%.0f",m_clumod.w0/2);
			SetDlgItemText(IDC_STATIC_XMID,text);
			for (i = 0; i < MAXNode; i++) {
				if (pSae.saem[i].fRotavelocity != 0 && pSae.saem[i].fCoe != 0) {
					m_graph.GetLine(WAVE_CH_1).AddPoint(pSae.saem[i].fRotavelocity, pSae.saem[i].fCoe*100);
				}
			}
			SetGraphStyleBase(g_data.GraphPara());
		}
		
	}
	else {
		CWnd *pWnd;
		pWnd = GetDlgItem(IDC_CHECK_CH2);	//获取控件指针，IDC_EDIT为控件ID号
		pWnd->ShowWindow( SW_SHOW );		//显示控件
		pWnd = GetDlgItem(IDC_CHECK_CH3);
        pWnd->ShowWindow( SW_SHOW );
		pWnd = GetDlgItem(IDC_CHECK_CH4);
        pWnd->ShowWindow( SW_SHOW );
		pWnd = GetDlgItem(IDC_VSFLEXGRIDN_CH_2);
        pWnd->ShowWindow( SW_SHOW );
		pWnd = GetDlgItem(IDC_VSFLEXGRIDN_CH_3);
        pWnd->ShowWindow( SW_SHOW );
		pWnd = GetDlgItem(IDC_VSFLEXGRIDN_CH_4);
        pWnd->ShowWindow( SW_SHOW );
		pGrid = (CFGridCtrlLU *) GetDlgItem(tblChGridId[0]);
		pGrid->SetTextMatrix(0, 0, _T("          转速          	"));

		
		for (i = 0; i < WAVE_CH_MAX; i++)
		{
			m_graph.GetLine(i).ClearAllPoint();
			g_data.GraphPara()->chp[i].fMinimum = tempmin;
			g_data.GraphPara()->chp[i].fMaximum = tempmax;
		}
		DispChannel(g_data.GraphPara());
		if ( start) {
			m_graphXMax = MAXNode;
			text.Format("%.2f",indextime);
			SetDlgItemText(IDC_STATIC_XMAX,text);
			text.Format("%.2f",indextime/2);
			SetDlgItemText(IDC_STATIC_XMID,text);
			for (i = 0; i < MAXNode; i++) {
				m_graph.GetLine(WAVE_CH_1).AddPoint(i, pSae.saem[i].fRotavelocity/100);
				m_graph.GetLine(WAVE_CH_2).AddPoint(i, pSae.saem[i].fPreforce/10);
				m_graph.GetLine(WAVE_CH_3).AddPoint(i, pSae.saem[i].fTorque);
				m_graph.GetLine(WAVE_CH_4).AddPoint(i, pSae.saem[i].fFlimthick*100000);
			}
			SetGraphStyleBase(g_data.GraphPara());
		}
		
	}
}
