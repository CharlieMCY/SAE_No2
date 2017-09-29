#if !defined(AFX_VSFLEXDATASOURCE_H__04391F14_757C_4375_A07C_C19C76B6DA62__INCLUDED_)
#define AFX_VSFLEXDATASOURCE_H__04391F14_757C_4375_A07C_C19C76B6DA62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//  Microsoft Visual C++ によって自動生成された IDispatch ラップ クラス

// メモ: このファイルの内容を編集しないでください。 このクラスが再度
//  Microsoft Visual C++ で生成された場合、変更を上書きします。

/////////////////////////////////////////////////////////////////////////////
// CVSFlexDataSourceLU ラップ クラス

class CVSFlexDataSourceLU : public COleDispatchDriver
{
public:
	CVSFlexDataSourceLU() {}		// COleDispatchDriver デフォルト コンストラクション
	CVSFlexDataSourceLU(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVSFlexDataSourceLU(const CVSFlexDataSourceLU& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// アトリビュート
public:

// オペレーション
public:
	long GetFieldCount();
	long GetRecordCount();
	CString GetFieldName(long Field);
	CString GetData(long Field, long Record);
	void SetData(long Field, long Record, LPCTSTR newData);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_VSFLEXDATASOURCE_H__04391F14_757C_4375_A07C_C19C76B6DA62__INCLUDED_)