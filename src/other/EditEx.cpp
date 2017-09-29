// EditEx.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "SAE_No2.h"
#include "EditEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//default Min
const double dblDefaultMinValue = -99999999.0;
//default Max
const double dblDefaultMaxValue = 99999999.0;

/////////////////////////////////////////////////////////////////////////////
// CEditEx
///////////////////////////////////////
/**
 * 	コンストラクタ
 * 		
 * 	
 */
CEditEx::CEditEx()
{
	m_foldValue		= 0.0;
	m_bChanging		= FALSE;
	m_dblMinValue	= dblDefaultMinValue;
	m_dblMaxValue	= dblDefaultMaxValue;
	SetFormat(EDITEX_FMTTYPE_NORMAL);
}
///////////////////////////////////////
/**
 * 	デストラクタ
 * 		
 * 	
 */
CEditEx::~CEditEx()
{
}

BEGIN_MESSAGE_MAP(CEditEx, CEdit)
	//{{AFX_MSG_MAP(CEditEx)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditEx メッセージ ハンドラ
///////////////////////////////////////
/**
 * 	EditChange時：float 入力チェック
 * 	
 */
void CEditEx::OnChange() 
{
	switch (m_fmtType)
	{
	case EDITEX_FMTTYPE_INT:
		OnChangeInt();
		break;
	case EDITEX_FMTTYPE_DOUBLE:
		OnChangeDouble();
		break;
	default:
		break;
	}
}

///////////////////////////////////////
/**
 * 	EditChange時：DOUBLE 入力チェック
 * 	
 */
void CEditEx::OnChangeDouble() 
{
	CString text;
	GetWindowText(text);

	BOOL IsfVal = TRUE;
	double dblValue;

	int len = text.GetLength();
	if (len)
	{
		int decCount = 0;
		for (int i = 0; i < len; i++)
		{	
			char c = text.GetAt(i); 
			if ((i == 0) && (c == '-'))
			{
			}
			else if (c == '.')
			{
				if (++decCount > 1)
				{
					IsfVal = FALSE;
					break;
				}
			}
			else if (!isdigit(c))
			{
				IsfVal = FALSE;
				break;
			}
		}
	}
	else
	{
		IsfVal = FALSE;
	}

	if (IsfVal)
	{
		dblValue = (double) atof(text);
		IsfVal = ((m_dblMinValue <= dblValue) && (dblValue <= m_dblMaxValue));
	}
	if (IsfVal)
	{
		m_foldValue = dblValue;
	}
	else
	{
		text.Format(m_strFormat, m_foldValue);
		SetWindowText(text);
	}
}
///////////////////////////////////////
/**
 * 	EditChange時：INT 入力チェック
 * 	
 */
void CEditEx::OnChangeInt() 
{
	CString text;
	GetWindowText(text);

	BOOL IsIntVal = TRUE;
	int iValue;

	int len = text.GetLength();
	if (len)
	{
		for (int i = 0; i < len; i++)
		{	
			char c = text.GetAt(i); 
			if ((i == 0) && (c == '-'))
			{
			}
			else if (!isdigit(c))
			{
				IsIntVal = FALSE;
			}
		}
	}
	else
	{
		IsIntVal = FALSE;
	}

	if (IsIntVal)
	{
		iValue = atoi(text);
		IsIntVal = ((m_dblMinValue <= iValue) && (iValue <= m_dblMaxValue));
	}
	if (IsIntVal)
	{
		m_foldValue = (double) iValue;
	}
	else
	{
		text.Format(m_strFormat, (int) m_foldValue);
		SetWindowText(text);
	}
}

///////////////////////////////////////
/**
 * 	最小値?最大値設定
 * 	
 */
void CEditEx::SetRange(double dblMin, double dblMax)
{
	m_dblMinValue	= dblMin;
	m_dblMaxValue	= dblMax;
}

///////////////////////////////////////
/**
 * 	Format Typeを設定
 * 	
 */
void CEditEx::SetFormat(EDITEX_FMTTYPE fmtType)
{
	switch (fmtType)
	{
	case EDITEX_FMTTYPE_NORMAL:
		m_fmtType = fmtType;
		m_strFormat = "";
		break;
	case EDITEX_FMTTYPE_INT:
		m_fmtType = fmtType;
		m_strFormat = "%d";
		break;
	case EDITEX_FMTTYPE_DOUBLE:
		m_fmtType = fmtType;
		m_strFormat = "%.1f";
		break;
	default:
		break;
	}
}