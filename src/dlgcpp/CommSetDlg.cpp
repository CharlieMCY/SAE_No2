// CommSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SAE_No2.h"
#include "CommSetDlg.h"
#include "InMonitor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern comused[14];
extern COM pCom[MaxSerialPortNum];

int BaudRate[]={300,600,1200,2400,4800,9600,14400,19200,38400,56000,57600,115200,230400,460800,921600};
int ParitySelNum=3;
CString Parity[]={_T("NONE"),_T("ODD"),_T("EVEN")};
int DataBits[]={6,7,8};
int StopBits[]={1,2};

/////////////////////////////////////////////////////////////////////////////
// CCommSetDlg dialog


CCommSetDlg::CCommSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCommSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCommSetDlg)
	m_strPortNO = _T("");
	m_strBaudRate = _T("");
	m_strDataBits = _T("");
	m_strStopBits = _T("");
	m_strParity = _T("");
	//}}AFX_DATA_INIT
}

void CCommSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommSetDlg)
	DDX_Control(pDX, IDC_COMBO_STOP_BIT, m_TypeList_Stop);
	DDX_Control(pDX, IDC_COMBO_SER_PORT, m_TypeList_Ser);
	DDX_Control(pDX, IDC_COMBO_DATA_BIT, m_TypeList_Data);
	DDX_Control(pDX, IDC_COMBO_BAUD_RATE, m_TypeList_Baud);
	DDX_Control(pDX, IDC_COMBO_CHECK_BIT, m_TypeList_Check);
	DDX_CBString(pDX, IDC_COMBO_SER_PORT, m_strPortNO);
	DDX_CBString(pDX, IDC_COMBO_BAUD_RATE, m_strBaudRate);
	DDX_CBString(pDX, IDC_COMBO_DATA_BIT, m_strDataBits);
	DDX_CBString(pDX, IDC_COMBO_STOP_BIT, m_strStopBits);
	DDX_CBString(pDX, IDC_COMBO_CHECK_BIT, m_strParity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommSetDlg, CDialog)
	//{{AFX_MSG_MAP(CCommSetDlg)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_CBN_SELCHANGE(IDC_COMBO_SER_PORT, OnSelchangeComboSerPort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommSetDlg message handlers

void CCommSetDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

BOOL CCommSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//m_TypeList_Ser.SetCurSel(0);
	CString temp;

	for(int i=1;i<=MaxSerialPortNum-1;i++)
	{
		if(m_SerialPort.InitPort(this->m_hWnd,i))
		{
			temp.Format("COM%d",i);		
			m_TypeList_Ser.AddString((LPCTSTR)temp);
		}
	}
	if(m_TypeList_Ser.GetCount())
	{
		m_SerialPort.InitPort(this->m_hWnd,MaxSerialPortNum);
		m_TypeList_Ser.SetCurSel(0);
	}

	for(i=0;i<sizeof(BaudRate)/sizeof(int);i++)
	{
		temp.Format("%d",BaudRate[i]);
		m_TypeList_Baud.AddString((LPCTSTR)temp);
	}
	temp.Format("%d",9600);
	m_TypeList_Baud.SetCurSel(m_TypeList_Baud.FindString(0,temp));

	for (i=0;i<ParitySelNum;i++)
	{
		m_TypeList_Check.AddString((LPCTSTR) Parity[i]);
	}
	m_TypeList_Check.SetCurSel(m_TypeList_Check.FindString(0,_T("None")));

	for(i=0;i<sizeof(StopBits)/sizeof(int);i++)
	{
		temp.Format("%d",StopBits[i]);
		m_TypeList_Stop.AddString((LPCTSTR)temp);
	}
	temp.Format("%d",1);
	m_TypeList_Stop.SetCurSel(m_TypeList_Stop.FindString(0,(LPCTSTR)temp));

	for(i=0;i<sizeof(DataBits)/sizeof(int);i++)
	{
		temp.Format("%d",DataBits[i]);
		m_TypeList_Data.AddString((LPCTSTR)temp);
	}
	temp.Format("%d",8);
	m_TypeList_Data.SetCurSel(m_TypeList_Data.FindString(0,(LPCTSTR)temp));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCommSetDlg::OnButtonApply() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString temp;
	temp=m_strPortNO;
	temp.Delete(0,3);
	int a = atoi(temp);
	pCom[a -1].PortNO = atoi(temp);
	pCom[a -1].BaudRate = atoi(m_strBaudRate);
	pCom[a -1].DataBits = atoi(m_strDataBits);
	pCom[a -1].Parity = m_strParity.GetAt(0);
	pCom[a -1].StopBits = atoi(m_strStopBits);
}

void CCommSetDlg::OnSelchangeComboSerPort() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString temp;
	m_TypeList_Ser.GetLBText(m_TypeList_Ser.GetCurSel(),temp);
	if (temp == "COM3") {
		temp.Format("%d",9600);
		m_TypeList_Baud.SetCurSel(m_TypeList_Baud.FindString(0,temp));
	}
	if (temp == "COM7") {
		temp.Format("%d",4800);
		m_TypeList_Baud.SetCurSel(m_TypeList_Baud.FindString(0,temp));
	}
}
