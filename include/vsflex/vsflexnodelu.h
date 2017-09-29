#if !defined(AFX_VSFLEXNODELU_H__802E30BE_044B_4421_A0C2_479B130FAC39__INCLUDED_)
#define AFX_VSFLEXNODELU_H__802E30BE_044B_4421_A0C2_479B130FAC39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//  Microsoft Visual C++ によって自動生成された IDispatch ラップ クラス

// メモ: このファイルの内容を編集しないでください。 このクラスが再度
//  Microsoft Visual C++ で生成された場合、変更を上書きします。


// このインターフェイスによって参照されるディスパッチ インターフェイス。
class CPicture;

/////////////////////////////////////////////////////////////////////////////
// CVSFlexNodeLU ラップ クラス

class CVSFlexNodeLU : public COleDispatchDriver
{
public:
	CVSFlexNodeLU() {}		// COleDispatchDriver デフォルト コンストラクション
	CVSFlexNodeLU(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVSFlexNodeLU(const CVSFlexNodeLU& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// アトリビュート
public:

// オペレーション
public:
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	CString GetKey();
	void SetKey(LPCTSTR lpszNewValue);
	CPicture GetImage();
	void SetImage(LPDISPATCH newValue);
	void SetRefImage(LPDISPATCH newValue);
	BOOL GetExpanded();
	void SetExpanded(BOOL bNewValue);
	short GetLevel();
	long GetChildren();
	long GetRow();
	void SetRow(long nNewValue);
	BOOL Move(long MoveTo, const VARIANT& TargetNode);
	void Sort(long How);
	void EnsureVisible();
	void Select();
	CVSFlexNodeLU GetNode(long Which);
	CVSFlexNodeLU AddNode(long AddWhere, LPCTSTR Item, const VARIANT& Key, const VARIANT& Image);
	void RemoveNode();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_VSFLEXNODELU_H__802E30BE_044B_4421_A0C2_479B130FAC39__INCLUDED_)