// InMonitor.cpp : implementation file
//

#include "stdafx.h"
#include "SAE_No2.h"
#include "InMonitor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern comused[14];

/////////////////////////////////////////////////////////////////////////////
// CInMonitor dialog


int tblEdIdRi[ MAX_RI_CH ] = {
	IDC_EDIT_RI_1,
	IDC_EDIT_RI_2,
	IDC_EDIT_RI_3,
	IDC_EDIT_RI_4,
	IDC_EDIT_RI_5,
	IDC_EDIT_RI_6,
	IDC_EDIT_RI_7,
	IDC_EDIT_RI_8,
};

CInMonitor::CInMonitor(CWnd* pParent /*=NULL*/)
	: CDialog(CInMonitor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInMonitor)
	//}}AFX_DATA_INIT
}


void CInMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInMonitor)
	DDX_Control(pDX, IDC_EDIT_RI_8, m_edt_ri8);
	DDX_Control(pDX, IDC_EDIT_RI_7, m_edt_ri7);
	DDX_Control(pDX, IDC_EDIT_RI_6, m_edt_ri6);
	DDX_Control(pDX, IDC_EDIT_RI_5, m_edt_ri5);
	DDX_Control(pDX, IDC_EDIT_RI_4, m_edt_ri4);
	DDX_Control(pDX, IDC_EDIT_RI_3, m_edt_ri3);
	DDX_Control(pDX, IDC_EDIT_RI_2, m_edt_ri2);
	DDX_Control(pDX, IDC_EDIT_RI_1, m_edt_ri1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInMonitor, CDialog)
	//{{AFX_MSG_MAP(CInMonitor)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInMonitor message handlers

void CInMonitor::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CInMonitor::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	DispInMoni();
	// TODO: Add your message handler code here
}

BOOL CInMonitor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int i;
	CEditEx *edit;
	for(i=1;i<=MaxSerialPortNum-1;i++)
	{
		if(m_SerialPort.InitPort(this->m_hWnd,i))
		{
			comused[i -1] = 1;
		}
		else {
			comused[i -1] = 0;
		}
	}
	for( i=0; i<MAX_RI_CH; i++ ) {
		edit = (CEditEx *) GetDlgItem(tblEdIdRi[i]);
		//edit->SetFormat(EDITEX_FMTTYPE_INT);
		edit->SetReadOnly();
	}

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInMonitor::DispInMoni() {
	int i;

	for( i=0; i<MAX_RI_CH; i++ ) {
		if (comused[i] == 0) {
			SetDlgItemText( tblEdIdRi[i], "ÎÞ");
		}
		else if (comused[i] == 1) {
			SetDlgItemText( tblEdIdRi[i], "Ê¹ÓÃ");
		}
	}
}
