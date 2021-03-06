// AXGdiWnd.h クラスのインタ�`フェイス
//
/********************************************************
// CLineStyleDisp	:ライン&マ�`カ�`スタイル��弼原きTEXTWndクラス
// CLineButton		:ライン&マ�`カ�`スタイルボタンクラス
// CLineStyleDlg	:ライン&マ�`カ�`スタイルダイアログクラス
//												by YOTSUTSU
//	* History	:	date:2005,24,Mar.	仟�ﾗ�撹
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

// アトリビュ�`ト
public:
	///<宙鮫マ�`ジン
	inline int SetLineMargins(int iMargin = 2);
	inline int GetLineMargins(void)	{	return m_iMargin;	}
	///<蛍護
	inline BOOL SetSeparateRatio(double dblRatio);
	inline double GetSeparateRatio(void)	{	return m_dblSeparateRatio;	}

// オペレ�`ション
public:
	//宙鮫
	virtual void DrawItem( CDC *pDC, CRect rect, CFont *pTextFont = NULL );
	void DrawSeparater( CDC *pDC, const CRect &rect );
	inline BOOL ShowSepareter(BOOL bShow = TRUE);
	void Redraw(BOOL bErase = TRUE){
		if( IsWindow( m_hWnd ) ){
			Invalidate(bErase);
			UpdateWindow();
		}
	};

// オ�`バ�`ライド
	// ClassWizard は�∀謇v方のオ�`バ�`ライドを伏撹します。
	//{{AFX_VIRTUAL(CLineStyleDisp)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	virtual BOOL OnChangeStyle(AXGCNOTIFY *pNotifyMsg );
// インプリメンテ�`ション
public:
	virtual ~CLineStyleDisp();

	// 伏撹されたメッセ�`ジ マップ�v方
protected:
	//{{AFX_MSG(CLineStyleDisp)
//	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
protected:
	int			m_iMargin;				///< マ�`ジン
	BOOL		m_bSepareterVisible;	///< セパレ�`ト��燕幣フラグ
	double		m_dblSeparateRatio;		///< セパレ�`ト
};
/////////////////////////////////////////////////////////////////////////////
// CLineButton ウィンドウ
/// 弼つきボタン
class CLineButton : public CButton, virtual public CAXGDIFrame, virtual public CAXLineStyle, virtual public CAXMarkerStyle
{
// コンストラクション
public:
	CLineButton();

// アトリビュ�`ト
public:

// オペレ�`ション
public:

// オ�`バ�`ライド
	// ClassWizard は�∀謇v方のオ�`バ�`ライドを伏撹します。
	//{{AFX_VIRTUAL(CLineButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// インプリメンテ�`ション
public:
	virtual ~CLineButton();

	// 伏撹されたメッセ�`ジ マップ�v方
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
	BOOL		m_bBtnDown;			///< ボタン兀和嶄フラグ
	int			m_iCheck;			///< �F壓のチェック彜�B

protected:

public:
	// 壅燕幣
	virtual void Redraw(BOOL bErase = FALSE);
	
	// チェック彜�B�O協/函誼
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポ�`ト
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CLineStyleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	//�O協�ｶ��x
protected:
	static const int CLineStyleDlg::c_iLineStyle[];
	static const int CLineStyleDlg::c_iMarkStyle[];
	static const char * CLineStyleDlg::c_cLineSize[];
	static const char * CLineStyleDlg::c_cMarkSize[];
	static const char * CLineStyleDlg::c_cMarkBkStyle[];

private:
	int m_iShowLineType;	///< ���N　　　　コンボ燕幣/掲燕幣
	int m_iShowLineSize;	///< ��サイズ　　コンボ燕幣/掲燕幣
	int m_iShowMarkType;	///< マ�`ク�N　　コンボ燕幣/掲燕幣
	int m_iShowMarkSize;	///< マ�`クサイズコンボ燕幣/掲燕幣
	int m_iShowMarkBkStyle;	///< マ�`カ�`嘘尚コンボ燕幣/掲燕幣

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
	 * 	��サイズ�O協の燕幣/掲燕幣.
	 * 	@param bEnable	TRUE:燕幣 FALSE:掲燕幣
	 */
	void ShowLineSize( BOOL bEnable ){
		m_iShowLineSize = bEnable? SW_SHOW: SW_HIDE;
	}

	/**
	 * 	マ�`ク�O協の燕幣/掲燕幣.
	 * 	@param bEnable	TRUE:燕幣 FALSE:掲燕幣
	 */
	void ShowMark( BOOL bEnable ){
		m_iShowMarkType = bEnable? SW_SHOW: SW_HIDE;
		m_iShowMarkSize = bEnable? SW_SHOW: SW_HIDE;
		m_iShowMarkBkStyle = bEnable? SW_SHOW: SW_HIDE;	///< マ�`カ�`嘘尚コンボ燕幣/掲燕幣
	}

	/**
	 * 	マ�`クサイズ�O協の燕幣/掲燕幣.
	 * 	@param bEnable	TRUE:燕幣 FALSE:掲燕幣
	 */
	void ShowMarkSize( BOOL bEnable ){
		m_iShowMarkSize = bEnable? SW_SHOW: SW_HIDE;
	}
	/**
	 * 	マ�`カ�`嘘尚の燕幣/掲燕幣.
	 * 	@param bEnable	TRUE:燕幣 FALSE:掲燕幣
	 */
	void ShowMarkBack( BOOL bEnable ){
		m_iShowMarkBkStyle = bEnable? SW_SHOW: SW_HIDE;	///< マ�`カ�`嘘尚コンボ燕幣/掲燕幣
	}
	/**
	 * 	ちょっと弌さめのダイアログにする.
	 */
	void SetSmallSize( void ){
		m_cc.lpTemplateName = "ChooseLineStyleEx";
	}
};
/////////////////////////////////////////////////////////////////////////////
// CLineStyleDisp
///////////////////////////////////////
/**
 * 	宙鮫マ�`ジンを�O協する.
 * 
 * 	@param iMargin	宙鮫マ�`ジン
 * 	@return			參念の宙鮫マ�`ジン
 */
inline int CLineStyleDisp::SetLineMargins(int iMargin /*= 2*/)
{
	int iOldMargin = m_iMargin;
	m_iMargin = iMargin;
	return iOldMargin;
}
///////////////////////////////////////
/**
 * 	セパレ�`ト曳楕を�O協する.
 * 
 * 	@param bShow	セパレ�`ト曳楕��枠�^の��の曳楕0.0゛1.0)
 * 	@return			�O協OK/NG
 */
inline BOOL CLineStyleDisp::SetSeparateRatio(double dblRatio)
{
	if(dblRatio < 0.0 || dblRatio > 1.0 )	{	return FALSE;	}
	m_dblSeparateRatio = dblRatio;
	return TRUE;
}
///////////////////////////////////////
/**
 * 	セパレ�`ト��燕幣フラグ
 * 
 * 	@param bShow	セパレ�`ト��燕幣 嗤��/�o��
 * 	@return			參念のセパレ�`ト��燕幣フラグ
 */
inline BOOL CLineStyleDisp::ShowSepareter(BOOL bShow /*= TRUE*/)
{	
	BOOL bOld = m_bSepareterVisible;
	m_bSepareterVisible = bShow;
	return bOld;
}
#endif // !defined(_AXGDIWND_H_INCLUDED_)