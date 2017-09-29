// AXGdiWnd.h クラスのインターフェイス
//
/********************************************************
// CLineStyleDisp	:ライン&マーカースタイル＋色付きTEXTWndクラス
// CLineButton		:ライン&マーカースタイルボタンクラス
// CLineStyleDlg	:ライン&マーカースタイルダイアログクラス
//												by YOTSUTSU
//	* History	:	date:2005,24,Mar.	新規作成
ver.1.00	
********************************************************/
//////////////////////////////////////////////////////////////////////

#if !defined(_AXGDIWND_H_INCLUDED_)
#define _AXGDIWND_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AxGdiCore.h"

/////////////////////////////////////////////////////////////////////////////
// CLineStyleDisp ウィンドウ
class CLineStyleDisp : public CAXStringWnd, public CAXLineStyle, public CAXMarkerStyle
{
// コンストラクション
public:
	CLineStyleDisp(COLORREF bkColor = ICTRLCOLOR);

// アトリビュート
public:
	///<描画マージン
	inline int SetLineMargins(int iMargin = 2);
	inline int GetLineMargins(void)	{	return m_iMargin;	}
	///<分割
	inline BOOL SetSeparateRatio(double dblRatio);
	inline double GetSeparateRatio(void)	{	return m_dblSeparateRatio;	}

// オペレーション
public:
	//描画
	virtual void DrawItem( CDC *pDC, CRect rect, CFont *pTextFont = NULL );
	void DrawSeparater( CDC *pDC, const CRect &rect );
	inline BOOL ShowSepareter(BOOL bShow = TRUE);
	void Redraw(BOOL bErase = TRUE){
		if( IsWindow( m_hWnd ) ){
			Invalidate(bErase);
			UpdateWindow();
		}
	};

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CLineStyleDisp)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	virtual BOOL OnChangeStyle(AXGCNOTIFY *pNotifyMsg );
// インプリメンテーション
public:
	virtual ~CLineStyleDisp();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CLineStyleDisp)
//	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
protected:
	int			m_iMargin;				///< マージン
	BOOL		m_bSepareterVisible;	///< セパレート枠表示フラグ
	double		m_dblSeparateRatio;		///< セパレート
};
/////////////////////////////////////////////////////////////////////////////
// CLineButton ウィンドウ
/// 色つきボタン
class CLineButton : public CButton, virtual public CAXGDIFrame, virtual public CAXLineStyle, virtual public CAXMarkerStyle
{
// コンストラクション
public:
	CLineButton();

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CLineButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CLineButton();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CLineButton)

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	UINT		m_uiStyle;			///< ボタンスタイル
	BOOL		m_bBtnDown;			///< ボタン押下中フラグ
	int			m_iCheck;			///< 現在のチェック状態

protected:

public:
	// 再表示
	virtual void Redraw(BOOL bErase = FALSE);
	
	// チェック状態設定/取得
	int  GetCheck();
	void SetCheck( int iCheck );
};
/////////////////////////////////////////////////////////////////////////////
// CLineStyleDlg ダイアログ

class CLineStyleDlg : public CColorDialog,  virtual public CAXLineStyle, virtual public CAXMarkerStyle
{
	DECLARE_DYNAMIC(CLineStyleDlg)

public:
	CLineStyleDlg( COLORREF clrInit = 0, DWORD dwFlags = 0, CWnd* pParentWnd = NULL );

	//{{AFX_DATA(CLineStyleDlg)
	CComboBox	m_lineTypeCombo;
	CComboBox	m_lineSizeCombo;
	CComboBox	m_markTypeCombo;
	CComboBox	m_markSizeCombo;
	CComboBox	m_markBkStyleCombo;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CLineStyleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CLineStyleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	//設定値定義
protected:
	static const int CLineStyleDlg::c_iLineStyle[];
	static const int CLineStyleDlg::c_iMarkStyle[];
	static const char * CLineStyleDlg::c_cLineSize[];
	static const char * CLineStyleDlg::c_cMarkSize[];
	static const char * CLineStyleDlg::c_cMarkBkStyle[];

private:
	int m_iShowLineType;	///< 線種　　　　コンボ表示/非表示
	int m_iShowLineSize;	///< 線サイズ　　コンボ表示/非表示
	int m_iShowMarkType;	///< マーク種　　コンボ表示/非表示
	int m_iShowMarkSize;	///< マークサイズコンボ表示/非表示
	int m_iShowMarkBkStyle;	///< マーカー背景コンボ表示/非表示

private:
	void OnOK();

public:
	int DoModal( int iStyle = PS_SOLID, int iSize = 0, int iMarker = 0, int iMarkSize = 8 );

	int DoModal( const LINESTYLE &lineStyle, const MARKERSTYLE &markStyle )
	{	
		CAXLineStyle::SetLineStyle(lineStyle);
		CAXMarkerStyle::SetMarkerStyle(markStyle);
		return CColorDialog::DoModal();
	}

	int DoModal( const LINESTYLE &lineStyle )
	{	
		CAXLineStyle::SetLineStyle(lineStyle);
		ShowMark(FALSE);
		return CColorDialog::DoModal();
	}

	/**
	 * 	線サイズ設定の表示/非表示.
	 * 	@param bEnable	TRUE:表示 FALSE:非表示
	 */
	void ShowLineSize( BOOL bEnable ){
		m_iShowLineSize = bEnable? SW_SHOW: SW_HIDE;
	}

	/**
	 * 	マーク設定の表示/非表示.
	 * 	@param bEnable	TRUE:表示 FALSE:非表示
	 */
	void ShowMark( BOOL bEnable ){
		m_iShowMarkType = bEnable? SW_SHOW: SW_HIDE;
		m_iShowMarkSize = bEnable? SW_SHOW: SW_HIDE;
		m_iShowMarkBkStyle = bEnable? SW_SHOW: SW_HIDE;	///< マーカー背景コンボ表示/非表示
	}

	/**
	 * 	マークサイズ設定の表示/非表示.
	 * 	@param bEnable	TRUE:表示 FALSE:非表示
	 */
	void ShowMarkSize( BOOL bEnable ){
		m_iShowMarkSize = bEnable? SW_SHOW: SW_HIDE;
	}
	/**
	 * 	マーカー背景の表示/非表示.
	 * 	@param bEnable	TRUE:表示 FALSE:非表示
	 */
	void ShowMarkBack( BOOL bEnable ){
		m_iShowMarkBkStyle = bEnable? SW_SHOW: SW_HIDE;	///< マーカー背景コンボ表示/非表示
	}
	/**
	 * 	ちょっと小さめのダイアログにする.
	 */
	void SetSmallSize( void ){
		m_cc.lpTemplateName = "ChooseLineStyleEx";
	}
};
/////////////////////////////////////////////////////////////////////////////
// CLineStyleDisp
///////////////////////////////////////
/**
 * 	描画マージンを設定する.
 * 
 * 	@param iMargin	描画マージン
 * 	@return			以前の描画マージン
 */
inline int CLineStyleDisp::SetLineMargins(int iMargin /*= 2*/)
{
	int iOldMargin = m_iMargin;
	m_iMargin = iMargin;
	return iOldMargin;
}
///////////////////////////////////////
/**
 * 	セパレート比率を設定する.
 * 
 * 	@param bShow	セパレート比率（先頭の枠の比率0.0～1.0)
 * 	@return			設定OK/NG
 */
inline BOOL CLineStyleDisp::SetSeparateRatio(double dblRatio)
{
	if(dblRatio < 0.0 || dblRatio > 1.0 )	{	return FALSE;	}
	m_dblSeparateRatio = dblRatio;
	return TRUE;
}
///////////////////////////////////////
/**
 * 	セパレート枠表示フラグ
 * 
 * 	@param bShow	セパレート枠表示 有効/無効
 * 	@return			以前のセパレート枠表示フラグ
 */
inline BOOL CLineStyleDisp::ShowSepareter(BOOL bShow /*= TRUE*/)
{	
	BOOL bOld = m_bSepareterVisible;
	m_bSepareterVisible = bShow;
	return bOld;
}
#endif // !defined(_AXGDIWND_H_INCLUDED_)