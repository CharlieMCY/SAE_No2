#if !defined(AFX_EDITEX_H__8471DBE6_A41F_441D_8705_AA6B3B894FBC__INCLUDED_)
#define AFX_EDITEX_H__8471DBE6_A41F_441D_8705_AA6B3B894FBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditEx.h : ヘッダー ファイル
//

typedef enum EDITEX_FMTTYPE {
	EDITEX_FMTTYPE_NORMAL	= 0,	//なんでも入力可能
	EDITEX_FMTTYPE_INT,				//整数値のみ受付
	EDITEX_FMTTYPE_DOUBLE,			//小数受付
};

/////////////////////////////////////////////////////////////////////////////
// CEditEx ウィンドウ

class CEditEx : public CEdit
{
// コンストラクション
public:
	CEditEx();

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CEditEx)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CEditEx();
	void SetRange(double dblMin, double dblMax);
	void SetFormat(EDITEX_FMTTYPE fmtType);
	// 生成されたメッセージ マップ関数
protected:
	double			m_foldValue;
	double			m_dblMinValue;
	double			m_dblMaxValue;
	BOOL			m_bChanging;
	CString			m_strFormat;
	EDITEX_FMTTYPE	m_fmtType;
	void OnChangeDouble();
	void OnChangeInt();
	//{{AFX_MSG(CEditEx)
	afx_msg void OnChange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_EDITEX_H__8471DBE6_A41F_441D_8705_AA6B3B894FBC__INCLUDED_)