// Microsoft Visual C++ で自動生成された IDispatch ラップ クラス

// メモ: このファイルの内容を編集しないでください。 このクラスが再度
//  Microsoft Visual C++ で生成された場合、変更を上書きします。


#include "stdafx.h"
#include "vsflexdatasource.h"


/////////////////////////////////////////////////////////////////////////////
// CVSFlexDataSourceLU プロパティ

/////////////////////////////////////////////////////////////////////////////
// CVSFlexDataSourceLU オペレーション

long CVSFlexDataSourceLU::GetFieldCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CVSFlexDataSourceLU::GetRecordCount()
{
	long result;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

CString CVSFlexDataSourceLU::GetFieldName(long Field)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		Field);
	return result;
}

CString CVSFlexDataSourceLU::GetData(long Field, long Record)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		Field, Record);
	return result;
}

void CVSFlexDataSourceLU::SetData(long Field, long Record, LPCTSTR newData)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Field, Record, newData);
}