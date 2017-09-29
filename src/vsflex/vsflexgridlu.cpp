// Microsoft Visual C++ で自動生成された IDispatch ラップ クラス

// メモ: このファイルの内容を編集しないでください。 このクラスが再度
//  Microsoft Visual C++ で生成された場合、変更を上書きします。


#include "stdafx.h"
#include "vsflexgridlu.h"

// このインターフェイスによって参照されるディスパッチ インターフェイス
#include "picture.h"
#include "font.h"
#include "vsflexdatasourcelu.h"
#include "VSFlexNodelu.h"

/////////////////////////////////////////////////////////////////////////////
// CVSFlexGridLU

IMPLEMENT_DYNCREATE(CVSFlexGridLU, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CVSFlexGridLU プロパティ

/////////////////////////////////////////////////////////////////////////////
// CVSFlexGridLU オペレーション

CString CVSFlexGridLU::GetFontName()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetFontName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

float CVSFlexGridLU::GetFontSize()
{
	float result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetFontSize(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL CVSFlexGridLU::GetFontBold()
{
	BOOL result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetFontBold(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CVSFlexGridLU::GetFontItalic()
{
	BOOL result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetFontItalic(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CVSFlexGridLU::GetFontStrikethru()
{
	BOOL result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetFontStrikethru(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CVSFlexGridLU::GetFontUnderline()
{
	BOOL result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetFontUnderline(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CVSFlexGridLU::GetRows()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetRows(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetCols()
{
	long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetCols(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

short CVSFlexGridLU::GetVersion()
{
	short result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetVersion(short nNewValue)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CVSFlexGridLU::GetFormatString()
{
	CString result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetFormatString(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CVSFlexGridLU::GetFixedRows()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetFixedRows(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetFixedCols()
{
	long result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetFixedCols(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetTopRow()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetTopRow(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetLeftCol()
{
	long result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetLeftCol(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetRowSel()
{
	long result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetRowSel(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetColSel()
{
	long result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetColSel(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetRow()
{
	long result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetRow(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetCol()
{
	long result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetCol(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CVSFlexGridLU::GetText()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

unsigned long CVSFlexGridLU::GetBackColor()
{
	unsigned long result;
	InvokeHelper(DISPID_BACKCOLOR, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetBackColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(DISPID_BACKCOLOR, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CVSFlexGridLU::GetForeColor()
{
	unsigned long result;
	InvokeHelper(DISPID_FORECOLOR, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetForeColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(DISPID_FORECOLOR, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CVSFlexGridLU::GetBackColorFixed()
{
	unsigned long result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetBackColorFixed(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x14, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CVSFlexGridLU::GetForeColorFixed()
{
	unsigned long result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetForeColorFixed(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CVSFlexGridLU::GetBackColorSel()
{
	unsigned long result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetBackColorSel(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x16, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CVSFlexGridLU::GetForeColorSel()
{
	unsigned long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetForeColorSel(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CVSFlexGridLU::GetBackColorBkg()
{
	unsigned long result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetBackColorBkg(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL CVSFlexGridLU::GetWordWrap()
{
	BOOL result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetWordWrap(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CVSFlexGridLU::GetTextStyle()
{
	long result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetTextStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetTextStyleFixed()
{
	long result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetTextStyleFixed(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CVSFlexGridLU::GetScrollTrack()
{
	BOOL result;
	InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetScrollTrack(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CVSFlexGridLU::GetFocusRect()
{
	long result;
	InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetFocusRect(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetHighLight()
{
	long result;
	InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetHighLight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetRedraw()
{
	long result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetRedraw(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetScrollBars()
{
	long result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetScrollBars(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x20, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetMouseRow()
{
	long result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CVSFlexGridLU::GetMouseCol()
{
	long result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CVSFlexGridLU::GetCellLeft()
{
	long result;
	InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CVSFlexGridLU::GetCellTop()
{
	long result;
	InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CVSFlexGridLU::GetCellWidth()
{
	long result;
	InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CVSFlexGridLU::GetCellHeight()
{
	long result;
	InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CVSFlexGridLU::GetRowHeightMin()
{
	long result;
	InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetRowHeightMin(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x27, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetFillStyle()
{
	long result;
	InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetFillStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x28, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetGridLines()
{
	long result;
	InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetGridLines(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x29, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetGridLinesFixed()
{
	long result;
	InvokeHelper(0x2a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetGridLinesFixed(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

unsigned long CVSFlexGridLU::GetGridColor()
{
	unsigned long result;
	InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetGridColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CVSFlexGridLU::GetGridColorFixed()
{
	unsigned long result;
	InvokeHelper(0x2c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetGridColorFixed(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CVSFlexGridLU::GetCellBackColor()
{
	unsigned long result;
	InvokeHelper(0x2d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetCellBackColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CVSFlexGridLU::GetCellForeColor()
{
	unsigned long result;
	InvokeHelper(0x2e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetCellForeColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long CVSFlexGridLU::GetCellAlignment()
{
	long result;
	InvokeHelper(0x2f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetCellAlignment(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetCellTextStyle()
{
	long result;
	InvokeHelper(0x30, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetCellTextStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x30, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CPicture CVSFlexGridLU::GetCellPicture()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x31, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CPicture(pDispatch);
}

void CVSFlexGridLU::SetCellPicture(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x31, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void CVSFlexGridLU::SetRefCellPicture(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x31, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

long CVSFlexGridLU::GetCellPictureAlignment()
{
	long result;
	InvokeHelper(0x32, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetCellPictureAlignment(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x32, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CVSFlexGridLU::GetCellFontName()
{
	CString result;
	InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetCellFontName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x33, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

float CVSFlexGridLU::GetCellFontSize()
{
	float result;
	InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetCellFontSize(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x34, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL CVSFlexGridLU::GetCellFontBold()
{
	BOOL result;
	InvokeHelper(0x35, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetCellFontBold(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x35, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CVSFlexGridLU::GetCellFontItalic()
{
	BOOL result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetCellFontItalic(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

float CVSFlexGridLU::GetCellFontWidth()
{
	float result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetCellFontWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL CVSFlexGridLU::GetCellFontUnderline()
{
	BOOL result;
	InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetCellFontUnderline(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x38, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CVSFlexGridLU::GetCellFontStrikethru()
{
	BOOL result;
	InvokeHelper(0x39, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetCellFontStrikethru(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x39, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

float CVSFlexGridLU::GetFontWidth()
{
	float result;
	InvokeHelper(0x3a, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetFontWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x3a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString CVSFlexGridLU::GetClip()
{
	CString result;
	InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetClip(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void CVSFlexGridLU::SetSort(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetSelectionMode()
{
	long result;
	InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetSelectionMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetMergeCells()
{
	long result;
	InvokeHelper(0x3e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetMergeCells(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CPicture CVSFlexGridLU::GetPicture()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xfffffdf5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CPicture(pDispatch);
}

long CVSFlexGridLU::GetPictureType()
{
	long result;
	InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetPictureType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x40, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CVSFlexGridLU::GetAllowBigSelection()
{
	BOOL result;
	InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetAllowBigSelection(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x41, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CVSFlexGridLU::GetAllowUserResizing()
{
	long result;
	InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetAllowUserResizing(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x42, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetMousePointer()
{
	long result;
	InvokeHelper(0xfffffdf7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetMousePointer(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xfffffdf7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CPicture CVSFlexGridLU::GetMouseIcon()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xfffffdf6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CPicture(pDispatch);
}

void CVSFlexGridLU::SetMouseIcon(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xfffffdf6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void CVSFlexGridLU::SetRefMouseIcon(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xfffffdf6, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL CVSFlexGridLU::GetVirtualData()
{
	BOOL result;
	InvokeHelper(0x46, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetVirtualData(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x46, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CVSFlexGridLU::GetEditable()
{
	long result;
	InvokeHelper(0x47, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetEditable(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x47, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CVSFlexGridLU::GetComboList()
{
	CString result;
	InvokeHelper(0x48, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetComboList(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x48, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double CVSFlexGridLU::GetValue()
{
	double result;
	InvokeHelper(0x49, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

unsigned long CVSFlexGridLU::GetFloodColor()
{
	unsigned long result;
	InvokeHelper(0x4a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetFloodColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

short CVSFlexGridLU::GetCellFloodPercent()
{
	short result;
	InvokeHelper(0x4b, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetCellFloodPercent(short nNewValue)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x4b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

unsigned long CVSFlexGridLU::GetCellFloodColor()
{
	unsigned long result;
	InvokeHelper(0x4c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetCellFloodColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long CVSFlexGridLU::GetSubtotalPosition()
{
	long result;
	InvokeHelper(0x4d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetSubtotalPosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetBorderStyle()
{
	long result;
	InvokeHelper(DISPID_BORDERSTYLE, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetBorderStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(DISPID_BORDERSTYLE, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

COleFont CVSFlexGridLU::GetFont()
{
	LPDISPATCH pDispatch;
	InvokeHelper(DISPID_FONT, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return COleFont(pDispatch);
}

void CVSFlexGridLU::SetFont(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(DISPID_FONT, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void CVSFlexGridLU::SetRefFont(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(DISPID_FONT, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL CVSFlexGridLU::GetEnabled()
{
	BOOL result;
	InvokeHelper(DISPID_ENABLED, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(DISPID_ENABLED, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CVSFlexGridLU::GetAppearance()
{
	long result;
	InvokeHelper(DISPID_APPEARANCE, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetAppearance(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(DISPID_APPEARANCE, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetOutlineBar()
{
	long result;
	InvokeHelper(0x52, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetOutlineBar(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x52, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

unsigned long CVSFlexGridLU::GetTreeColor()
{
	unsigned long result;
	InvokeHelper(0x53, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetTreeColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x53, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

short CVSFlexGridLU::GetGridLineWidth()
{
	short result;
	InvokeHelper(0x54, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetGridLineWidth(short nNewValue)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x54, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CVSFlexGridLU::GetAutoResize()
{
	BOOL result;
	InvokeHelper(0x55, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetAutoResize(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x55, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CVSFlexGridLU::GetBottomRow()
{
	long result;
	InvokeHelper(0x56, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CVSFlexGridLU::GetRightCol()
{
	long result;
	InvokeHelper(0x57, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CVSFlexGridLU::GetExtendLastCol()
{
	BOOL result;
	InvokeHelper(0x58, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetExtendLastCol(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x58, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CVSFlexGridLU::GetClientWidth()
{
	long result;
	InvokeHelper(0x59, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CVSFlexGridLU::GetClientHeight()
{
	long result;
	InvokeHelper(0x5a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString CVSFlexGridLU::GetEditText()
{
	CString result;
	InvokeHelper(0x5b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetEditText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x5b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CVSFlexGridLU::GetHWnd()
{
	long result;
	InvokeHelper(DISPID_HWND, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CVSFlexGridLU::GetAutoSizeMode()
{
	long result;
	InvokeHelper(0x5d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetAutoSizeMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CVSFlexGridLU::GetRightToLeft()
{
	BOOL result;
	InvokeHelper(0x5e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetRightToLeft(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CVSFlexGridLU::GetMultiTotals()
{
	BOOL result;
	InvokeHelper(0x5f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetMultiTotals(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

unsigned long CVSFlexGridLU::GetBackColorAlternate()
{
	unsigned long result;
	InvokeHelper(0x60, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetBackColorAlternate(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long CVSFlexGridLU::GetOwnerDraw()
{
	long result;
	InvokeHelper(0x61, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetOwnerDraw(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x61, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetDataMode()
{
	long result;
	InvokeHelper(0x62, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetDataMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x62, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetOLEDragMode()
{
	long result;
	InvokeHelper(0x63, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetOLEDragMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x63, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetOLEDropMode()
{
	long result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetOLEDropMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetTabBehavior()
{
	long result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetTabBehavior(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

unsigned long CVSFlexGridLU::GetSheetBorder()
{
	unsigned long result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetSheetBorder(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL CVSFlexGridLU::GetAllowSelection()
{
	BOOL result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetAllowSelection(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CVSFlexGridLU::GetPicturesOver()
{
	BOOL result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetPicturesOver(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CVSFlexGridLU::GetCellChecked()
{
	long result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetCellChecked(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetMergeCompare()
{
	long result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetMergeCompare(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetEllipsis()
{
	long result;
	InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetEllipsis(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetOutlineCol()
{
	long result;
	InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetOutlineCol(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetRowHeightMax()
{
	long result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetRowHeightMax(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetAutoSearch()
{
	long result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetAutoSearch(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetExplorerBar()
{
	long result;
	InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetExplorerBar(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CVSFlexGridLU::GetEditMask()
{
	CString result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetEditMask(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x70, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CVSFlexGridLU::GetEditSelStart()
{
	long result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetEditSelStart(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x71, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetEditSelLength()
{
	long result;
	InvokeHelper(0x72, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetEditSelLength(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x72, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CVSFlexGridLU::GetEditSelText()
{
	CString result;
	InvokeHelper(0x73, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetEditSelText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x73, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CVSFlexGridLU::GetEditMaxLength()
{
	long result;
	InvokeHelper(0x74, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetEditMaxLength(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x74, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetComboIndex()
{
	long result;
	InvokeHelper(0x75, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetComboIndex(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x75, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetComboCount()
{
	long result;
	InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CVSFlexGridLU::GetColAlignment(long Col)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x77, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		Col);
	return result;
}

void CVSFlexGridLU::SetColAlignment(long Col, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x77, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Col, nNewValue);
}

long CVSFlexGridLU::GetColWidth(long Col)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x78, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		Col);
	return result;
}

void CVSFlexGridLU::SetColWidth(long Col, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x78, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Col, nNewValue);
}

long CVSFlexGridLU::GetRowHeight(long Row)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x79, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		Row);
	return result;
}

void CVSFlexGridLU::SetRowHeight(long Row, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x79, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Row, nNewValue);
}

BOOL CVSFlexGridLU::GetMergeRow(long Row)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Row);
	return result;
}

void CVSFlexGridLU::SetMergeRow(long Row, BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL;
	InvokeHelper(0x7a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Row, bNewValue);
}

BOOL CVSFlexGridLU::GetMergeCol(long Col)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Col);
	return result;
}

void CVSFlexGridLU::SetMergeCol(long Col, BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL;
	InvokeHelper(0x7b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Col, bNewValue);
}

void CVSFlexGridLU::SetRowPosition(long Row, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x7c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Row, nNewValue);
}

void CVSFlexGridLU::SetColPosition(long Col, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x7d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Col, nNewValue);
}

VARIANT CVSFlexGridLU::GetRowData(long Row)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		Row);
	return result;
}

void CVSFlexGridLU::SetRowData(long Row, const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x7e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Row, &newValue);
}

VARIANT CVSFlexGridLU::GetColData(long Col)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		Col);
	return result;
}

void CVSFlexGridLU::SetColData(long Col, const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x7f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Col, &newValue);
}

void CVSFlexGridLU::AddItem(LPCTSTR Item, const VARIANT& Row)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x80, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Item, &Row);
}

void CVSFlexGridLU::RemoveItem(const VARIANT& Row)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x81, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Row);
}

CString CVSFlexGridLU::GetTextMatrix(long Row, long Col)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x82, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		Row, Col);
	return result;
}

void CVSFlexGridLU::SetTextMatrix(long Row, long Col, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x82, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Row, Col, lpszNewValue);
}

void CVSFlexGridLU::Clear(const VARIANT& Where, const VARIANT& What)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x83, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Where, &What);
}

void CVSFlexGridLU::EditCell()
{
	InvokeHelper(0x84, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

double CVSFlexGridLU::GetValueMatrix(long Row, long Col)
{
	double result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x85, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms,
		Row, Col);
	return result;
}

BOOL CVSFlexGridLU::GetIsSubtotal(long Row)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x86, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Row);
	return result;
}

void CVSFlexGridLU::SetIsSubtotal(long Row, BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL;
	InvokeHelper(0x86, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Row, bNewValue);
}

void CVSFlexGridLU::Subtotal(long Function, const VARIANT& GroupOn, const VARIANT& TotalOn, const VARIANT& Format, const VARIANT& BackColor, const VARIANT& ForeColor, const VARIANT& FontBold, const VARIANT& Caption, const VARIANT& MatchFrom, 
		const VARIANT& TotalOnly)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x87, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Function, &GroupOn, &TotalOn, &Format, &BackColor, &ForeColor, &FontBold, &Caption, &MatchFrom, &TotalOnly);
}

void CVSFlexGridLU::Refresh()
{
	InvokeHelper(DISPID_REFRESH, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CVSFlexGridLU::Outline(short Level)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x89, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Level);
}

long CVSFlexGridLU::GetFixedAlignment(long Col)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		Col);
	return result;
}

void CVSFlexGridLU::SetFixedAlignment(long Col, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x8a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Col, nNewValue);
}

BOOL CVSFlexGridLU::GetRowIsVisible(long Row)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Row);
	return result;
}

BOOL CVSFlexGridLU::GetColIsVisible(long Col)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Col);
	return result;
}

long CVSFlexGridLU::GetRowPos(long Row)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		Row);
	return result;
}

long CVSFlexGridLU::GetColPos(long Col)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		Col);
	return result;
}

BOOL CVSFlexGridLU::GetIsSelected(long Row)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Row);
	return result;
}

void CVSFlexGridLU::SetIsSelected(long Row, BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL;
	InvokeHelper(0x8f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Row, bNewValue);
}

long CVSFlexGridLU::GetIsCollapsed(long Row)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x91, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		Row);
	return result;
}

void CVSFlexGridLU::SetIsCollapsed(long Row, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x91, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Row, nNewValue);
}

void CVSFlexGridLU::Select(long Row, long Col, const VARIANT& RowSel, const VARIANT& ColSel)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x92, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Row, Col, &RowSel, &ColSel);
}

void CVSFlexGridLU::AutoSize(long Col1, const VARIANT& Col2, const VARIANT& Equal, const VARIANT& ExtraSpace)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x93, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Col1, &Col2, &Equal, &ExtraSpace);
}

void CVSFlexGridLU::CellBorder(unsigned long Color, short Left, short Top, short Right, short Bottom, short Vertical, short Horizontal)
{
	static BYTE parms[] =
		VTS_I4 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2;
	InvokeHelper(0x95, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Color, Left, Top, Right, Bottom, Vertical, Horizontal);
}

void CVSFlexGridLU::OLEDrag()
{
	InvokeHelper(0x96, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CVSFlexGridLU::SaveGrid(LPCTSTR FileName, long SaveWhat, const VARIANT& FixedCells)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_VARIANT;
	InvokeHelper(0x97, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName, SaveWhat, &FixedCells);
}

void CVSFlexGridLU::LoadGrid(LPCTSTR FileName, long LoadWhat, const VARIANT& FixedCells)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_VARIANT;
	InvokeHelper(0x98, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName, LoadWhat, &FixedCells);
}

void CVSFlexGridLU::Archive(LPCTSTR ArcFileName, LPCTSTR FileName, long Action)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0x99, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ArcFileName, FileName, Action);
}

VARIANT CVSFlexGridLU::GetArchiveInfo(LPCTSTR ArcFileName, long InfoType, const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_VARIANT;
	InvokeHelper(0x9a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		ArcFileName, InfoType, &Index);
	return result;
}

long CVSFlexGridLU::GetColSort(long Col)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		Col);
	return result;
}

void CVSFlexGridLU::SetColSort(long Col, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x9b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Col, nNewValue);
}

CString CVSFlexGridLU::GetColFormat(long Col)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		Col);
	return result;
}

void CVSFlexGridLU::SetColFormat(long Col, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x9c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Col, lpszNewValue);
}

long CVSFlexGridLU::GetColDataType(long Col)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		Col);
	return result;
}

void CVSFlexGridLU::SetColDataType(long Col, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x9d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Col, nNewValue);
}

VARIANT CVSFlexGridLU::GetCell(long Setting, const VARIANT& Row1, const VARIANT& Col1, const VARIANT& Row2, const VARIANT& Col2)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x9e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		Setting, &Row1, &Col1, &Row2, &Col2);
	return result;
}

void CVSFlexGridLU::SetCell(long Setting, const VARIANT& Row1, const VARIANT& Col1, const VARIANT& Row2, const VARIANT& Col2, const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x9e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Setting, &Row1, &Col1, &Row2, &Col2, &newValue);
}

void CVSFlexGridLU::SetRefCell(long Setting, const VARIANT& Row1, const VARIANT& Col1, const VARIANT& Row2, const VARIANT& Col2, const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x9e, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 Setting, &Row1, &Col1, &Row2, &Col2, &newValue);
}

long CVSFlexGridLU::GetRowStatus(long Row)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		Row);
	return result;
}

void CVSFlexGridLU::SetRowStatus(long Row, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x9f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Row, nNewValue);
}

long CVSFlexGridLU::GetFindRow(const VARIANT& Item, const VARIANT& Row, const VARIANT& Col, const VARIANT& CaseSensitive, const VARIANT& FullMatch)
{
	long result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xa0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		&Item, &Row, &Col, &CaseSensitive, &FullMatch);
	return result;
}

CString CVSFlexGridLU::GetComboItem(const VARIANT& Index)
{
	CString result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xa1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		&Index);
	return result;
}

CString CVSFlexGridLU::GetComboData(const VARIANT& Index)
{
	CString result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xa2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		&Index);
	return result;
}

void CVSFlexGridLU::BindToArray(const VARIANT& VariantArray, const VARIANT& RowDim, const VARIANT& ColDim, const VARIANT& PageDim, const VARIANT& CurrentPage)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xa3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &VariantArray, &RowDim, &ColDim, &PageDim, &CurrentPage);
}

CString CVSFlexGridLU::GetColEditMask(long Col)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xa4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		Col);
	return result;
}

void CVSFlexGridLU::SetColEditMask(long Col, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0xa4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Col, lpszNewValue);
}

CString CVSFlexGridLU::GetColComboList(long Col)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xa5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		Col);
	return result;
}

void CVSFlexGridLU::SetColComboList(long Col, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0xa5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Col, lpszNewValue);
}

short CVSFlexGridLU::GetRowOutlineLevel(long Row)
{
	short result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xa6, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms,
		Row);
	return result;
}

void CVSFlexGridLU::SetRowOutlineLevel(long Row, short nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I2;
	InvokeHelper(0xa6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Row, nNewValue);
}

long CVSFlexGridLU::GetSelectedRows()
{
	long result;
	InvokeHelper(0xa7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CVSFlexGridLU::GetSelectedRow(long Index)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xa8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		Index);
	return result;
}

BOOL CVSFlexGridLU::GetScrollTips()
{
	BOOL result;
	InvokeHelper(0xa9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetScrollTips(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xa9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString CVSFlexGridLU::GetScrollTipText()
{
	CString result;
	InvokeHelper(0xaa, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetScrollTipText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xaa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL CVSFlexGridLU::GetRowHidden(long Row)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xab, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Row);
	return result;
}

void CVSFlexGridLU::SetRowHidden(long Row, BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL;
	InvokeHelper(0xab, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Row, bNewValue);
}

BOOL CVSFlexGridLU::GetColHidden(long Col)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xac, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Col);
	return result;
}

void CVSFlexGridLU::SetColHidden(long Col, BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL;
	InvokeHelper(0xac, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Col, bNewValue);
}

long CVSFlexGridLU::GetColWidthMin()
{
	long result;
	InvokeHelper(0xad, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetColWidthMin(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xad, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetColWidthMax()
{
	long result;
	InvokeHelper(0xae, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetColWidthMax(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xae, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void CVSFlexGridLU::GetMergedRange(long Row, long Col, long* R1, long* C1, long* R2, long* C2)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4;
	InvokeHelper(0xaf, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Row, Col, R1, C1, R2, C2);
}

BOOL CVSFlexGridLU::GetShowComboButton()
{
	BOOL result;
	InvokeHelper(0xb0, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetShowComboButton(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CPicture CVSFlexGridLU::GetCellButtonPicture()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xb1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CPicture(pDispatch);
}

void CVSFlexGridLU::SetCellButtonPicture(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xb1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void CVSFlexGridLU::SetRefCellButtonPicture(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xb1, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

long CVSFlexGridLU::GetComboSearch()
{
	long result;
	InvokeHelper(0xb2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetComboSearch(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void CVSFlexGridLU::LoadArray(const VARIANT& VariantArray, const VARIANT& RowDim, const VARIANT& ColDim, const VARIANT& PageDim, const VARIANT& CurrentPage)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xb3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &VariantArray, &RowDim, &ColDim, &PageDim, &CurrentPage);
}

BOOL CVSFlexGridLU::GetAutoSizeMouse()
{
	BOOL result;
	InvokeHelper(0xb4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetAutoSizeMouse(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void CVSFlexGridLU::GetSelection(long* Row1, long* Col1, long* Row2, long* Col2)
{
	static BYTE parms[] =
		VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4;
	InvokeHelper(0xb5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Row1, Col1, Row2, Col2);
}

CString CVSFlexGridLU::GetClipSeparators()
{
	CString result;
	InvokeHelper(0xb6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetClipSeparators(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xb6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void CVSFlexGridLU::PrintGrid(const VARIANT& DocName, const VARIANT& ShowDialog, const VARIANT& Orientation, const VARIANT& MarginLR, const VARIANT& MarginTB)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xb7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &DocName, &ShowDialog, &Orientation, &MarginLR, &MarginTB);
}

long CVSFlexGridLU::GetColImageList(long Col)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		Col);
	return result;
}

void CVSFlexGridLU::SetColImageList(long Col, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0xb8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Col, nNewValue);
}

CString CVSFlexGridLU::GetColKey(long Col)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		Col);
	return result;
}

void CVSFlexGridLU::SetColKey(long Col, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0xb9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Col, lpszNewValue);
}

long CVSFlexGridLU::GetColIndex(LPCTSTR Key)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xba, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		Key);
	return result;
}

long CVSFlexGridLU::GetFrozenRows()
{
	long result;
	InvokeHelper(0xbc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetFrozenRows(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xbc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetFrozenCols()
{
	long result;
	InvokeHelper(0xbd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetFrozenCols(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xbd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CVSFlexGridLU::GetAllowUserFreezing()
{
	long result;
	InvokeHelper(0xbe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetAllowUserFreezing(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xbe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

unsigned long CVSFlexGridLU::GetBackColorFrozen()
{
	unsigned long result;
	InvokeHelper(0xbf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetBackColorFrozen(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xbf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CVSFlexGridLU::GetForeColorFrozen()
{
	unsigned long result;
	InvokeHelper(0xc0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetForeColorFrozen(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CVSFlexDataSourceLU CVSFlexGridLU::GetFlexDataSource()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xc1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CVSFlexDataSourceLU(pDispatch);
}

void CVSFlexGridLU::SetFlexDataSource(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xc1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long CVSFlexGridLU::GetNodeRow(long Row, long Which)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0xc2, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		Row, Which);
	return result;
}

CString CVSFlexGridLU::BuildComboList(LPDISPATCH rs, LPCTSTR FieldList, const VARIANT& KeyField, const VARIANT& BackColor)
{
	CString result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_BSTR VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xc3, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		rs, FieldList, &KeyField, &BackColor);
	return result;
}

CPicture CVSFlexGridLU::GetNodeOpenPicture()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xc4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CPicture(pDispatch);
}

void CVSFlexGridLU::SetNodeOpenPicture(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xc4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void CVSFlexGridLU::SetRefNodeOpenPicture(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xc4, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

CPicture CVSFlexGridLU::GetNodeClosedPicture()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xc5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CPicture(pDispatch);
}

void CVSFlexGridLU::SetNodeClosedPicture(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xc5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void CVSFlexGridLU::SetRefNodeClosedPicture(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xc5, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

void CVSFlexGridLU::ShowCell(long Row, long Col)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0xc6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Row, Col);
}

float CVSFlexGridLU::GetAutoSearchDelay()
{
	float result;
	InvokeHelper(0xc7, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetAutoSearchDelay(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xc7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long CVSFlexGridLU::GetEditWindow()
{
	long result;
	InvokeHelper(0xc8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CPicture CVSFlexGridLU::GetWallPaper()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CPicture(pDispatch);
}

void CVSFlexGridLU::SetWallPaper(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void CVSFlexGridLU::SetRefWallPaper(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xc9, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

long CVSFlexGridLU::GetWallPaperAlignment()
{
	long result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexGridLU::SetWallPaperAlignment(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double CVSFlexGridLU::GetAggregate(long Aggregate, long Row1, long Col1, long Row2, long Col2)
{
	double result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms,
		Aggregate, Row1, Col1, Row2, Col2);
	return result;
}

long CVSFlexGridLU::DragRow(long Row)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xcc, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		Row);
	return result;
}

CVSFlexNodeLU CVSFlexGridLU::GetNode(const VARIANT& Row)
{
	LPDISPATCH pDispatch;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xcd, DISPATCH_METHOD, VT_DISPATCH, (void*)&pDispatch, parms,
		&Row);
	return CVSFlexNodeLU(pDispatch);
}

long CVSFlexGridLU::GetColIndent(long Col)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		Col);
	return result;
}

void CVSFlexGridLU::SetColIndent(long Col, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0xcf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Col, nNewValue);
}
