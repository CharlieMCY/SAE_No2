// CondSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SAE_No2.h"
#include "CondSetDlg.h"
#include "SAE_No2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCondSetDlg dialog


CCondSetDlg::CCondSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCondSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCondSetDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCondSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCondSetDlg)
	DDX_Control(pDX, IDC_VSFG_COND_SETTING, m_condset_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCondSetDlg, CDialog)
	//{{AFX_MSG_MAP(CCondSetDlg)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCondSetDlg message handlers

void CCondSetDlg::Initialize(COND* pCond) 
{
	memcpy(&m_cond, pCond, sizeof(COND));
}

void CCondSetDlg::DispCondSetting(COND* pCond) 
{
	CString text;
	text.Format("%d", pCond->Initvelocity);
	m_condset_grid.SetTextMatrix(0, 2, text);

	text.Format(FORM_POINT, pCond->Surfpressure);
	m_condset_grid.SetTextMatrix(1, 2, text);

	text.Format(FORM_POINT, pCond->Inertiamoment);
	m_condset_grid.SetTextMatrix(2, 2, text);

	text.Format("%d", pCond->diskpieces);
	m_condset_grid.SetTextMatrix(3, 2, text);

}

void CCondSetDlg::OnButtonApply() 
{
	// TODO: Add your control notification handler code here
	COND Cond_Data = {0};
	CVSFlexGrid *pVsFG;
	CString strData;

	pVsFG = (CVSFlexGrid *)GetDlgItem( IDC_VSFG_COND_SETTING );

	strData = pVsFG->GetTextMatrix(0, 2);
	Cond_Data.Initvelocity =  atoi( strData );

	strData = pVsFG->GetTextMatrix(1, 2);
	Cond_Data.Surfpressure =  ( double )atof( strData );

	strData = pVsFG->GetTextMatrix(2, 2);
	Cond_Data.Inertiamoment = ( double )atof( strData );

	strData = pVsFG->GetTextMatrix(3, 2);
	Cond_Data.diskpieces = atoi( strData );

	g_data.SetCond(&Cond_Data);

	CDialog::OnOK();
}

void CCondSetDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CCondSetDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	DispCondSetting(&m_cond);

	CDialog::OnShowWindow(bShow, nStatus);
}
