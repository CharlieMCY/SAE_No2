// GetData.cpp : implementation file
//

#include "stdafx.h"
#include "SAE_No2.h"
#include "GetData.h"
#include "math.h"
#include ".\src\measureRadius_idl.h"
//#include ".\src\measureRadius_idl_i.c"
#include ".\src\mwcomtypes.h"
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern COM pCom[MaxSerialPortNum];
extern SAE pSae;
int flag=0;
int Count=0;
int result[1024] = {0};
CString vresult=_T("");
CString m_name;

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
/////////////////////////////////////////////////////////////////////////////
// CGetData dialog


CGetData::CGetData(CWnd* pParent /*=NULL*/)
	: CDialog(CGetData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetData)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGetData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetData)
	DDX_Control(pDX, IDC_BUTTON_APPLY, m_GetData);
	DDX_Control(pDX, IDC_COMBO_INST, m_TesterName);
	DDX_Control(pDX, IDC_COMBO_SER_PORT, m_PortNO);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGetData, CDialog)
	//{{AFX_MSG_MAP(CGetData)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_WM_TIMER()
	ON_MESSAGE(WM_COMM_RXCHAR,OnReceiveChar)
	ON_CBN_SELCHANGE(IDC_COMBO_INST, OnSelchangeComboInst)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetData message handlers

void CGetData::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	m_SerialPort.ClosePort();
	CDialog::OnCancel();
}

void CGetData::OnButtonApply() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString temp;
	m_TesterName.GetLBText(m_TesterName.GetCurSel(),temp);
	if (temp == "Roughness Tester") {
		m_name = temp;
		if( m_PortNO.GetCount()) {
			GetDlgItem(IDC_BUTTON_APPLY)->EnableWindow(FALSE);
			int SelPortNO,SelBaudRate,SelDataBits,SelStopBits;
			char SelParity;
			UpdateData(true);
			m_PortNO.GetLBText(m_PortNO.GetCurSel(),temp);
			temp.Delete(0,3);
			SelPortNO=atoi(temp);
			SelBaudRate=pCom[SelPortNO-1].BaudRate;
			SelDataBits=pCom[SelPortNO-1].DataBits;
			SelParity=pCom[SelPortNO-1].Parity;
			SelStopBits=pCom[SelPortNO-1].StopBits;
			if(SelBaudRate == 0) {
				AfxMessageBox("Please set the COM first!");
				GetDlgItem(IDC_BUTTON_APPLY)->EnableWindow(TRUE);
			}
			else if(m_SerialPort.InitPort(this,SelPortNO,SelBaudRate,SelParity,SelDataBits,SelStopBits,EV_RXCHAR|EV_CTS,512))		
			{
				m_SerialPort.StartMonitoring();
				UpdateData(false);
				SetTimer(1,100,NULL);
			}
		}
		else {
			AfxMessageBox("This COM is unavailable!\nPlease Choose other COM.");
			GetDlgItem(IDC_BUTTON_APPLY)->EnableWindow(TRUE);
		}
	}
	if (temp == "Viscosity Tester") {
		m_name = temp;
		if( m_PortNO.GetCount()) {
			GetDlgItem(IDC_BUTTON_APPLY)->EnableWindow(FALSE);
			int SelPortNO,SelBaudRate,SelDataBits,SelStopBits;
			char SelParity;
			UpdateData(true);
			m_PortNO.GetLBText(m_PortNO.GetCurSel(),temp);
			temp.Delete(0,3);
			SelPortNO=atoi(temp);
			SelBaudRate=pCom[SelPortNO-1].BaudRate;
			SelDataBits=pCom[SelPortNO-1].DataBits;
			SelParity=pCom[SelPortNO-1].Parity;
			SelStopBits=pCom[SelPortNO-1].StopBits;
			if(SelBaudRate == 0) {
				AfxMessageBox("Please set the COM first!");
				GetDlgItem(IDC_BUTTON_APPLY)->EnableWindow(TRUE);
			}
			else if(m_SerialPort.InitPort(this,SelPortNO,SelBaudRate,SelParity,SelDataBits,SelStopBits,EV_RXCHAR|EV_CTS,512))		
			{
				m_SerialPort.StartMonitoring();
				UpdateData(false);
				CString sendtext;
				sendtext="01 03 20 32 00 01 2E 05";// 01 03 20 37 00 01 3E 04 01 03 20 38 00 01 0E 07";
				sendtext=ChangeCharstr2Hexstr(sendtext);
				m_SerialPort.WriteToPort(sendtext.GetBuffer(sendtext.GetLength()),sendtext.GetLength());
				//SetTimer(1,100,NULL);				
			}
		}
		else {
			AfxMessageBox("This COM is unavailable!\nPlease Choose other COM.");
			GetDlgItem(IDC_BUTTON_APPLY)->EnableWindow(TRUE);
		}
	}
	if (temp == "Image Collection") {
		//pTwain.SelectSource();
		//pTwain.Acquire();
		//GetDlgItem(IDC_BUTTON_APPLY)->EnableWindow(FALSE);
		fstream _file;
		_file.open("C:\\Users\\Public\\Pictures\\000000.bmp",ios::in);
		if(!_file) {
			AfxMessageBox("Get data unsuccessfully!");
		}
		else {
			_file.close();
			if( FAILED(CoInitialize(NULL)))
			{
				AfxMessageBox("Initialize COM failed!");
				return;
			}
			ImeasureRadius *SNRclass = NULL;
			HRESULT hr;
			hr = CoCreateInstance(CLSID_measureRadius,NULL,CLSCTX_ALL,IID_ImeasureRadius,(void**)&SNRclass);
			if(FAILED(hr))
			{
				AfxMessageBox("Create inatance failed!");
				return;
			}
			VARIANT SNR1,SNR2;
			SNRclass->measureRadius(2,&SNR1,&SNR2);
			pSae.saein.fOuter=SNR1.dblVal;
			pSae.saein.fInner=SNR2.dblVal;
			pSae.saein.fOuter /= 200;
			pSae.saein.fInner /= 200;
			if (pSae.saein.fInner != 0 && pSae.saein.fOuter != 0) {
					AfxMessageBox("Get data successfully!");
				}
			else AfxMessageBox("Get data unsuccessfully!");
			/*if( !measureRadiusInitialize()) {
				AfxMessageBox("Could not initialize measureRadius.dll!");
			}
			else {
				mwArray mwRD(1, 1, mxDOUBLE_CLASS);
				mwArray mwRX(1, 1, mxDOUBLE_CLASS);
				measureRadius(2, mwRD, mwRX);
				pSae.saein.fOuter = mwRD.Get(1, 1);
				pSae.saein.fInner = mwRX.Get(1, 1);
				pSae.saein.fOuter /= 200;
				pSae.saein.fInner /= 200;
				if (pSae.saein.fInner != 0 && pSae.saein.fOuter != 0) {
					AfxMessageBox("Get data successfully!");
				}
				else AfxMessageBox("Get data unsuccessfully!");
			}*/
			remove("C:\\Users\\Public\\Pictures\\000000.bmp");
		}
	}
}

void CGetData::OnReceiveChar(UINT ch, LONG port)
{
	CString temp;
	CString sendtext;
	if (m_name == "Roughness Tester") {
		if (Count==6) {
			//m_SerialPort.StopMonitoring();
			pSae.saein.fSurfroughness=(1000*result[1]+100*result[2]+10*result[3]+result[4])/(float)pow(10,result[5]);
			pSae.saein.fSurfroughness /= 1e6;
			AfxMessageBox("Get data successfully!");
			//GetDlgItem(IDC_BUTTON_APPLY)->EnableWindow(TRUE);
		}
		if (flag==0) {
			temp = DevideHexChar(ch);
			if (temp == "2D") {
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
	if (m_name == "Viscosity Tester") {
		if (flag == 0) {
			temp = DevideHexChar(ch);
			Count++;
			if (Count == 4 || Count == 5) {
				vresult += temp;
			}
			if (Count == 7) {
				pSae.saein.fTemperature = HTOI((string)vresult)/10.0;
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
					pSae.saein.fViscosity = (double)HTOI((string)vresult);
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
				if (Count == 4 || Count == 5) {
					vresult += temp;
				}
				if (Count == 7) {
					pSae.saein.fViscosity = (double)HTOI((string)vresult);// + pSae.saein.fViscosity * 16 * 16 * 16 * 16;
					vresult=_T("");
					AfxMessageBox("Get data successfully!");
				}
			}
		}
	}
}

BOOL CGetData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString temp;
	flag = 0;
	Count = 0;
	memset(result, 0, sizeof(result));
	for(int i=1;i<=MaxSerialPortNum-1;i++)
	{
		if(m_SerialPort.InitPort(this,i))
		{
			temp.Format("COM%d",i);		
			m_PortNO.AddString((LPCTSTR)temp);
		}
	}
	if(m_PortNO.GetCount())
	{
		m_SerialPort.InitPort(this,MaxSerialPortNum);
		m_PortNO.SetCurSel(0);
	}
	
	m_TesterName.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGetData::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CString temp;
	temp="20";
	temp=ChangeCharstr2Hexstr(temp);
	m_SerialPort.WriteToPort(temp.GetBuffer(temp.GetLength()),temp.GetLength());
	CDialog::OnTimer(nIDEvent);
}

CString CGetData::ChangeCharstr2Hexstr(CString Charstr)
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

void CGetData::HexStringFilter(CString &str)
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
char CGetData::CombineHexChar(char CharH,char CharL)
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


CString CGetData::DevideHexChar(char HexChar)
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

void CGetData::OnSelchangeComboInst() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString temp;
	m_TesterName.GetLBText(m_TesterName.GetCurSel(),temp);
	if (temp == "Image Collection") {
		temp.Format("");
		m_PortNO.SetCurSel(m_PortNO.FindString(0,temp));
		GetDlgItem(IDC_COMBO_SER_PORT)->EnableWindow(FALSE);
	}
	if (temp == "Roughness Tester") {
		temp.Format("COM7");
		m_PortNO.SetCurSel(m_PortNO.FindString(0,temp));
		GetDlgItem(IDC_COMBO_SER_PORT)->EnableWindow(TRUE);
	}
	if (temp == "Viscosity Tester") {
		temp.Format("COM3");
		m_PortNO.SetCurSel(m_PortNO.FindString(0,temp));
		GetDlgItem(IDC_COMBO_SER_PORT)->EnableWindow(TRUE);
	}
}

int CGetData::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_GetData.CreateEx(WS_EX_CLIENTEDGE,NULL,NULL,
		WS_CHILD | WS_VISIBLE | CBRS_TOP| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,0,0,0,0,m_hWnd,NULL);
	pTwain.InitTwain(m_hWnd);
	return 0;
}
