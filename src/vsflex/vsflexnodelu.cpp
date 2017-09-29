// Microsoft Visual C++ で自動生成された IDispatch ラップ クラス

// メモ: このファイルの内容を編集しないでください。 このクラスが再度
//  Microsoft Visual C++ で生成された場合、変更を上書きします。


#include "stdafx.h"
#include "vsflexnodelu.h"

// このインターフェイスによって参照されるディスパッチ インターフェイス
#include "picture1.h"


/////////////////////////////////////////////////////////////////////////////
// CVSFlexNodeLU プロパティ

/////////////////////////////////////////////////////////////////////////////
// CVSFlexNodeLU オペレーション

CString CVSFlexNodeLU::GetText()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CVSFlexNodeLU::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString CVSFlexNodeLU::GetKey()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CVSFlexNodeLU::SetKey(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CPicture CVSFlexNodeLU::GetImage()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CPicture(pDispatch);
}

void CVSFlexNodeLU::SetImage(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void CVSFlexNodeLU::SetRefImage(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL CVSFlexNodeLU::GetExpanded()
{
	BOOL result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVSFlexNodeLU::SetExpanded(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

short CVSFlexNodeLU::GetLevel()
{
	short result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

long CVSFlexNodeLU::GetChildren()
{
	long result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CVSFlexNodeLU::GetRow()
{
	long result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVSFlexNodeLU::SetRow(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CVSFlexNodeLU::Move(long MoveTo, const VARIANT& TargetNode)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		MoveTo, &TargetNode);
	return result;
}

void CVSFlexNodeLU::Sort(long How)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 How);
}

void CVSFlexNodeLU::EnsureVisible()
{
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CVSFlexNodeLU::Select()
{
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CVSFlexNodeLU CVSFlexNodeLU::GetNode(long Which)
{
	LPDISPATCH pDispatch;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&pDispatch, parms,
		Which);
	return CVSFlexNodeLU(pDispatch);
}

CVSFlexNodeLU CVSFlexNodeLU::AddNode(long AddWhere, LPCTSTR Item, const VARIANT& Key, const VARIANT& Image)
{
	LPDISPATCH pDispatch;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_DISPATCH, (void*)&pDispatch, parms,
		AddWhere, Item, &Key, &Image);
	return CVSFlexNodeLU(pDispatch);
}

void CVSFlexNodeLU::RemoveNode()
{
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}