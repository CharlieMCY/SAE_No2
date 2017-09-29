// AXGDICore.h : ヘッダー ファイル
//
/********************************************************
// クラスのインターフェイス
// CLinePen			:ライン用ペンクラス
// CAXLineStyle		:ラインスタイルクラス
// CAXMarkerStyle	:マーカースタイルクラス
// CAXPatternStyle	:パターンスタイルクラス
// CAXGDIFrame		:AXGDI描画クラス
// CAXColorString	:色付きTEXTクラス
// CAXGDICtrl		:AXGDI描画CWndクラス
// CAXStringWnd		:色付きTEXTWndクラス
//												by YOTSUTSU
//	* History	:	date:2005,24,Mar.	新規作成
ver.1.00	
********************************************************/
//////////////////////////////////////////////////////////////////////

#if !defined(_AXGDICORE_H_INCLUDED_)
#define _AXGDICORE_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AxGdiDef.h"// 定数

//AXColorStringStyle

/////////////////////////////////////////////////////////////////////////////
// 構造体
#pragma pack( push, 1 )
	/// ラインスタイル構造体
	typedef struct tagLineStyle{	//16Byte
		int 		iStyle;			///< 線種
		int			iSize;			///< 線サイズ
		COLORREF	color;			///< 線色
		int			iReserve1;		///< よび
	} LINESTYLE;

	/// マーカースタイル情報
	typedef struct tagMarkerStyle{	//16Byte
		int			iMarker;		///< ポインタマーカー
		int			iMarkSize;		///< マーカーサイズ
		int			iBkStyle;		///< マーカー背景描画
		int			iReserve1;		///< よび
	} MARKERSTYLE;

	/// 描画エリアのパターンスタイル情報
	typedef struct tagPatternStyle{	//16Byte
		int			iBStyle;		///< /* Brush Styles */BS_SOLID
		int			iHStyle;		///< /* Hatch Styles */HS_HORIZONTAL
		COLORREF	color;			///< 色
		int			iReserve1;		///< よび
	} PATTERNSTYLE;

	/// グラフデータ保持型
	typedef struct tagXYPoint{
		double		dX;			///< 座標X
		double		dY;			///< 座標Y
	} XYPOINT;

#pragma pack( pop )

/////////////////////////////////////////////////////////////////////////////
// 関数
//マーク描画
extern void _stdcall DrawMark( CDC *pDC, int iStyle, CPoint pos, int iSize = 8 );
//グレイカラー変換
extern COLORREF _stdcall Color2Gray( COLORREF color );
///////////////////////////////////////
/**
 * 	double->long変換
 *		倍精度浮動小数点　->　32 ビットの符号付き整数 
 * 
 * 	@param data	入力値（double:倍精度浮動小数点）
 * 	@return		出力値（long:32 ビットの符号付き整数）
 */
extern inline long _stdcall FtoL( double data )
{
	return (((data)>0.0)?(long)(data + 0.5):(long)(data - 0.5));
}
extern int _stdcall GetDecLength(double dRange);
/////////////////////////////////////////////////////////////////////////////
//ライン用ペンクラス
class CLinePen : public CPen
{
// コンストラクション
public:
	CLinePen(){};
	CLinePen( int nPenStyle, int nWidth, COLORREF crColor ){
		CreatePen( nPenStyle, nWidth, crColor );
	}

public:
	BOOL CreatePen( int nPenStyle, int nWidth, COLORREF crColor )
	{
		//return CPen::CreatePen( nPenStyle , nWidth, crColor );

		DWORD stDash[] = {10, 5	};
		DWORD stDot[]  = { 4, 4	};
		DWORD stDashDot[]    = { 10, 4, 2, 4	};
		DWORD stDashDotDOT[] = { 10, 4, 2, 4, 2, 4	};
		
		LOGBRUSH logBrush;
		logBrush.lbStyle = BS_SOLID;
		logBrush.lbColor = crColor;

		int iNum = 0;
		DWORD *pStyle;
		switch( nPenStyle ){
		case PS_DASH:		iNum = 2; pStyle = stDash;		break;
		case PS_DOT:		iNum = 2, pStyle = stDot;		break;
		case PS_DASHDOT:	iNum = 4, pStyle = stDashDot;	break;
		case PS_DASHDOTDOT:	iNum = 6, pStyle = stDashDotDOT;break;
		default:			return CPen::CreatePen( nPenStyle, nWidth, crColor );
		}

		if( nWidth <= 0 ) nWidth = 1;
		for( int i = 0; i < iNum; i++ ) pStyle[i] *= nWidth;
		return CPen::CreatePen( PS_USERSTYLE|PS_GEOMETRIC, nWidth, &logBrush, iNum, pStyle );
	}
};
/////////////////////////////////////////////////////////////////////////////
// CAXLineStyle
class CAXLineStyle
{
// コンストラクション
public:
	CAXLineStyle( int iStyle = PS_NULL , COLORREF color = IWHITE, int iSize = 0)
	{
		memset(&m_lineStyle, 0x00, sizeof(LINESTYLE) );
		SetLineStyle(iStyle, color, iSize);//デフォルト設定
	}
	CAXLineStyle( const LINESTYLE &lineStyle )
	{
		memset(&m_lineStyle, 0x00, sizeof(LINESTYLE) );
		SetLineDefault();//デフォルト設定
		SetLineStyle( lineStyle );
	}
	CAXLineStyle( const CAXLineStyle &org )
	{
		operator =(org);
	}
	virtual ~CAXLineStyle(){}
// アトリビュート
public:	
	///< ライン情報
	inline void SetLineStyle( const LINESTYLE &lineStyle );
	inline void SetLineStyle( int iStyle = PS_SOLID , COLORREF color = IWHITE, int iSize = -1);
	inline void SetLineColor( COLORREF color );

	inline const LINESTYLE & GetLineStyle(void) const	{	return m_lineStyle;	}				///< ライン情報
	inline COLORREF GetLineColor(void) const			{	return m_lineStyle.color;	}		///< 線色
	inline int GetPenStyle(void) const					{	return m_lineStyle.iStyle;	}		///< 線種
	inline int GetLineSize(void) const					{	return m_lineStyle.iSize;	}		///< 線サイズ

	///<デフォルト設定
	inline void SetLineDefault( int iStyle = PS_NULL , COLORREF color = IWHITE, int iSize = 0)
	{
		SetLineStyle( iStyle, color, iSize );
	}
protected:
	LINESTYLE	m_lineStyle;	///< ライン情報
// オペレーション
public:
	// 初期化
	inline CAXLineStyle &operator =( const CAXLineStyle &src );
	inline CAXLineStyle & Copy( const CAXLineStyle &src )	{	operator =(src); return (*this);	}
// オーバーライド
public:
	///< 再描画
	virtual void Redraw(BOOL bErase = TRUE){}
};
/////////////////////////////////////////////////////////////////////////////
// CAXMarkerStyle
class CAXMarkerStyle
{
// コンストラクション
public:
	CAXMarkerStyle(int iMarker = MARKNONE, int iMarkSize = 8, int iBkStyle = 0)
	{
		memset(&m_markStyle, 0x00, sizeof(MARKERSTYLE) );
		SetMarkerStyle( iMarker, iMarkSize, iBkStyle );//デフォルト設定
	}
	CAXMarkerStyle( const MARKERSTYLE &markStyle )
	{
		memset(&m_markStyle, 0x00, sizeof(MARKERSTYLE) );
		SetMarkerDefault();
		SetMarkerStyle( markStyle );
	}
	CAXMarkerStyle( const CAXMarkerStyle &org )
	{
		operator =( org );
	}
	virtual ~CAXMarkerStyle(){};
// アトリビュート
public:
	///< マーカー情報
	inline void SetMarkerStyle( const MARKERSTYLE &markStyle );
	inline void SetMarkerStyle( int iMarker = MARKNONE, int iMarkSize = -1, int iBkStyle = -1 );
	inline int SetMarkerSize(int iMarkSize);
	
	inline const MARKERSTYLE & GetMarkerStyle(void) const {	return m_markStyle;	}		///< マーカー情報
	inline int GetMarkerKind(void) const		{	return m_markStyle.iMarker;		}	///< ポインタマーカー
	inline int GetMarkerSize(void) const		{	return m_markStyle.iMarkSize;	}	///< マーカーサイズ
	inline int GetMarkerBkStyle(void) const		{	return m_markStyle.iBkStyle;	}	///< マーカー背景描画
	
	///<デフォルト設定
	inline void SetMarkerDefault(int iMarker = MARKNONE, int iMarkSize = 8, int iBkStyle = 0)
	{
		SetMarkerStyle( iMarker, iMarkSize, iBkStyle );
	}
protected:
	MARKERSTYLE	m_markStyle;	///< マーカー情報
// オペレーション
public:
	// 初期化
	inline CAXMarkerStyle &operator =( const CAXMarkerStyle &src );
	inline CAXMarkerStyle & Copy( const CAXMarkerStyle &src )	{	operator =(src); return (*this);	}
// オーバーライド
public:
	///< 再描画
	virtual void Redraw(BOOL bErase = TRUE){}
};
/////////////////////////////////////////////////////////////////////////////
// CAXPatternStyle
class CAXPatternStyle
{
// コンストラクション
public:
	CAXPatternStyle(int iBStyle = BS_SOLID, int iHStyle = HS_HORIZONTAL, COLORREF color = IPINK )
	{
		memset(&m_patternStyle, 0x00, sizeof(PATTERNSTYLE) );
		SetPatternStyle( iBStyle, iHStyle, color );//デフォルト設定
	}
	CAXPatternStyle( const PATTERNSTYLE &patternStyle )
	{
		memset(&m_patternStyle, 0x00, sizeof(PATTERNSTYLE) );
		SetPatternStyle( patternStyle.iBStyle, patternStyle.iHStyle, patternStyle.color );//デフォルト設定
	}
	CAXPatternStyle( const CAXPatternStyle &org )
	{
		operator =( org );
	}
	virtual ~CAXPatternStyle(){};
// アトリビュート
public:
	/// 描画エリアのブラシ情報
	inline void SetPatternStyle( const PATTERNSTYLE &patternStyle );
	inline void SetPatternStyle( int iBStyle , int iHStyle , COLORREF color  );
	inline COLORREF SetPatternColor( COLORREF color );
	
	inline const PATTERNSTYLE & GetPatternStyle(void) const {	return m_patternStyle;	}	///< 描画エリアのブラシ情報
	inline int GetBrushStyle(void) const	{	return m_patternStyle.iBStyle;	}		///< /* Brush Styles */BS_SOLID
	inline int GetHatchStyle(void) const	{	return m_patternStyle.iHStyle;	}		///< /* Hatch Styles */HS_HORIZONTAL
	inline COLORREF GetPatternColor(void) const	{	return m_patternStyle.color;	}		///< 色
protected:
	PATTERNSTYLE	m_patternStyle;	///< 描画エリアのブラシ情報
// オペレーション
public:
	// 初期化
	inline CAXPatternStyle &operator =( const CAXPatternStyle &src );
	inline CAXPatternStyle & Copy( const CAXPatternStyle &src )	{	operator =(src); return (*this);	}
// オーバーライド
public:
	///< 再描画
	virtual void Redraw(BOOL bErase = TRUE){}
};
/////////////////////////////////////////////////////////////////////////////
//CAXGDIFrame
class CAXGDIFrame
{
// コンストラクション
public:
	CAXGDIFrame( COLORREF bkColor = ICTRLCOLOR );
	//コピーコンストラクタ
	CAXGDIFrame( const CAXGDIFrame &org );
// インプリメンテーション
public:
	virtual ~CAXGDIFrame();
	//コピー
	inline CAXGDIFrame & operator = ( const CAXGDIFrame &src );
	inline CAXGDIFrame & Copy( const CAXGDIFrame &src )	{	operator=(src);	return *this;	}

// アトリビュート
public:
	///< 背景色
	inline COLORREF SetBkColor( COLORREF color );
	inline COLORREF GetBkColor(void)	{	return m_bkColor;	}
	///< 枠表示色
	inline COLORREF SetFrameColor( COLORREF color );
	inline COLORREF GetFrameColor(void)	{	return m_frameColor;	}
	///< 枠表示フラグ
	inline void ShowFrame(BOOL bShow = TRUE)	{	m_bFrameVisible = bShow; Redraw();	}
	inline BOOL	IsFrameVisible(void)	{	return m_bFrameVisible;	}
	///< モノクローム表示
	inline BOOL EnableMonochrome ( BOOL bEnable );
	inline BOOL IsMonochrome (void)	{	return m_bMonochrome;	}

protected:
	COLORREF	m_bkColor;			///< background color
	COLORREF	m_frameColor;		///< Frame line color
	BOOL		m_bMonochrome;		///< モノクローム表示フラグ
	BOOL		m_bFrameVisible;	///< 枠表示フラグ
// オーバーライド
public:
	///< 背景描画
	inline virtual void DrawBackground( CDC *pDC, const CRect rect );
	///< 枠描画
	inline virtual void DrawFrame( CDC *pDC, CRect rect );
// オペレーション
public:
	///< ラインスタイル描画
	virtual void DrawLineStyle( CDC *pDC, const CRect &rect, const LINESTYLE &lineStyle, long lOrientation = 0 );
	///< マーカー描画
	virtual void DrawMarker( CDC *pDC, CPoint pos, const MARKERSTYLE &markStyle, COLORREF color );
	///< 再描画
	virtual void Redraw(BOOL bErase = TRUE){}
};
/////////////////////////////////////////////////////////////////////////////
//CAXColorString
class CAXColorString
{
// コンストラクション
public:
	CAXColorString(void);
	//コピーコンストラクタ
	CAXColorString( const CAXColorString &org );
// インプリメンテーション
public:
	virtual ~CAXColorString();
	//コピー
	inline CAXColorString & operator = ( const CAXColorString &src );
	inline CAXColorString & Copy( const CAXColorString &src )	{	operator=(src);	return *this;	}
// アトリビュート
public:
	///< 文字列表示色
	inline virtual COLORREF	SetStrColor( COLORREF color = COLOR_BTNTEXT );
	inline COLORREF GetStrColor(void) const {	return( m_colorData );	}
	///< 表示文字列
	inline virtual CString GetString(void) const {	return ( m_strData );	}
	inline virtual int GetString( LPTSTR lpszStringBuf, int nMaxCount ) const {
		_tcsncpy( lpszStringBuf, m_strData, nMaxCount );
		lpszStringBuf[nMaxCount - 1] = '\0';
		return ( 1 );//あとで直す。
	}

	inline void SetString( LPCTSTR lpszString );
	///< 表示スタイル
	virtual WORD SetTextStyle(WORD wStyle = (SS_CENTER | SS_CENTERIMAGE));
	virtual WORD GetTextStyle(void) const;
	///< 描画フォーマット
	inline UINT SetDTFormat( UINT nFormat /*= (DT_VCENTER | DT_CENTER)*/);///< DrawText Format
	inline UINT GetDTFormat(void) const		{	return m_nDTFormat;		}	///< DrawText Format
	inline UINT	GetDTPosV(void) const		{	return GetDTPosV(m_nDTFormat);	}
	inline UINT	GetDTPosH(void) const		{	return GetDTPosH(m_nDTFormat);	}

protected:
	inline static UINT	GetDTPosV( UINT nDTFormat )	{
		if(nDTFormat & DT_VCENTER)		{	return DT_VCENTER;	}
		else if(nDTFormat & DT_BOTTOM)	{	return DT_BOTTOM;	}
		return DT_TOP;
	}
	inline static UINT	GetDTPosH( UINT nDTFormat )	{
		if(nDTFormat & DT_CENTER)		{	return DT_CENTER;	}
		else if(nDTFormat & DT_RIGHT)	{	return DT_RIGHT;	}
		return DT_LEFT;
	}
protected:
	CString		m_strData;			///< Display string
	COLORREF	m_colorData;		///< string color
	UINT		m_nDTFormat;		///< DrawText Format

// オペレーション
public:
	virtual void TextDraw( CDC* pDC, CRect &rect, CFont &font, BOOL bMonochrome, long lfOrientation );
	virtual void TextDraw( CDC* pDC, CRect &rect, CFont &font, LPCTSTR lpszString, const COLORREF textColor, UINT nDTFormat, long lfOrientation );
// オーバーライド
public:
	///< 再描画
	virtual void Redraw(BOOL bErase = TRUE){}
};
/////////////////////////////////////////////////////////////////////////////
//CAXGDICtrl
/*
 * CAXGDICtrl Control Mesages
 */
typedef enum E_AXGDICTRL_NOTIFY{
//#define GCN_SETFOCUS			1	//
//#define GCN_KILLFOCUS			2	//
	AXGCN_CHANGE_ACTIVE = 1,	//Activeなアイテムを変更する。(更新前にMessageをCall)
	AXGCN_UPDATE_ACTIVE,		//Activeなアイテムを更新した。(更新後にMessageをCall)
	AXGCN_CHANGE_STYLE,			//Activeなアイテムのスタイルを変更する。(更新前にMessageをCall)
	AXGCN_UPDATE_STYLE,			//Activeなアイテムのスタイルを更新した。(更新後にMessageをCall)
	AXGCN_CHANGE_SCALE,			//Activeなアイテムのスケールを変更する。(更新前にMessageをCall)
	AXGCN_UPDATE_SCALE,			//Activeなアイテムのスケールを更新した。(更新後にMessageをCall)
	AXGCN_CHANGE_CURSOL,		//Activeなカーソルの位置を更新する。(更新前にMessageをCall)
	AXGCN_UPDATE_CURSOL,		//Activeなカーソルの位置を更新した。(更新後にMessageをCall)
};

typedef enum E_AXGDICTRL_KIND{
	AXGCTRL_NONE = 0,		///< 0:非選択
	AXGCTRL_GRAPH_WND,		///< 1:グラフコントロール
	AXGCTRL_CHART_WND,		///< 2:チャートコントロール
	AXGCTRL_GRAPH,			///< 1:グラフコントロール
	AXGCTRL_CHART,			///< 2:チャートコントロール

	AXGCTRL_MEASURE = 10,	///< 10:メジャーコントロール
	AXGCTRL_STRING,			///< 11:ストリングコントロール
	AXGCTRL_LINESTYLE,		///< 12:ラインスタイルコントロール
};

///< 0:非選択/1:全体/2:データ/3:カーソル/4:エリアカーソル
typedef enum E_AXGDICTRLACTIVE_TYPE{
	AXGCTRLACT_NONE = 0,	///< 0:非選択
	AXGCTRLACT_FRAME,		///< 1:全体
	AXGCTRLACT_DATA,		///< 2:データ
	AXGCTRLACT_CURSOL,		///< 3:カーソル
	AXGCTRLACT_AREACSL,		///< 4:エリアカーソル
};

typedef struct tagAXGCActiveInfo{
	UINT	nKind;			///< AXGDICtrlの種類（E_AXGDICTRL_KIND参照）
	UINT	nActive;		///< 0:非選択/1:全体/2:データ/3:カーソル/4:エリアカーソル/
	int		iLayer;			///< Activeなレイヤー番号				-1:無効 0オリジン
	int		iLine;			///< Activeなレイヤーライン番号			-1:無効 0オリジン
	int		iIndex;			///< Activeなレイヤーのインデックス情報	-1:無効 0オリジン
}AXGCACTINFO;

typedef struct tagAXGDICtrlNotify{
	NMHDR		hdr;		///< すべての WM_NOTIFY メッセージに共通な情報
	AXGCACTINFO	activeInfo;	///< 通知に関連付けられたコントロールの情報
	UINT		nKeyParam;	///< Keyboad Message
} AXGCNOTIFY, FAR* LPAXGCNOTIFY;

///<MouseZoomType マウス拡大機能
typedef enum E_MOUSE_ZOOM{
	ZOOM_OFF = 0,	///< 無
	XY_ZOOM,		///< X方向、Y方向の両方向を拡大
	X_ZOOM,			///< X方向拡大
	Y_ZOOM,			///< Y方向拡大
};

class CAXGDICtrl : public CWnd, virtual public CAXGDIFrame
{
	//DECLARE_DYNAMIC(CAXGDICtrl)
public:
	/// ユーザーパラメータ
	typedef struct tagUserParam{
		DWORD		m_dwParam1;		///< ユーザーパラメータ１
		DWORD		m_dwParam2;		///< ユーザーパラメータ２
	} USERPARAM;
// コンストラクション
public:
	CAXGDICtrl( UINT nKind = AXGCTRL_NONE, COLORREF bkColor = ICTRLCOLOR );
	//コピーコンストラクタ
	CAXGDICtrl( const CAXGDICtrl &org );

// インプリメンテーション
public:
	virtual ~CAXGDICtrl();
	inline CAXGDICtrl & operator = ( const CAXGDICtrl &src );
	inline CAXGDICtrl & Copy( const CAXGDICtrl &src );
// アトリビュート
public:
	// 初期サイズを取得する。
	inline const CSize & GetInitSize( void ) const	{	return m_wndSize;	}	///< グラフのRect
	///< AXGDICtrlの種類（E_AXGDICTRL_KIND参照）
	inline UINT GetCtrlKind(void) const	{	return m_nKind;	}
	//******** 拡張機能 ********//
	//Activate
	inline void EnableActivate( BOOL bEnable );
	inline BOOL IsEnableActivate( void );

	// ユーザーパラメータ
	inline void  SetUserParam( DWORD dwParam1, DWORD dwParam2 );
	inline USERPARAM &GetUserParam( void );
// オペレーション
public:
	// 印刷用
	virtual void PrintDC( CDC *pDC, const CRect &rect, BOOL bMonochrome = FALSE, BOOL bDrawExFlag = FALSE );

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAXGDICtrl)
	public:
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
protected:
	// 親Wndクラスへの通知
	virtual void NotifyToParent(UINT nCode, AXGCACTINFO *lpActiveInfo = NULL, UINT nKey = 0x0000);
	// 通知メッセージの処理
	virtual BOOL OnChangeActive( AXGCNOTIFY *pNotifyMsg );
	virtual BOOL OnChangeStyle( AXGCNOTIFY *pNotifyMsg );
	virtual BOOL OnChangeScale( AXGCNOTIFY *pNotifyMsg );
	virtual BOOL OnChangeCursol( AXGCNOTIFY *pNotifyMsg );
	// 選択状態描画
	virtual void DrawActiveState( CDC *pDC, const CRect &rect );
	virtual void DrawActiveFrame( CDC *pDC, const CRect &rect, int size = 7 );
	// 描画前処理
	virtual void BeginPaintDC( CDC *pDC, const CRect &rect ){};
	// 描画後処理
	virtual void EndPaintDC( CDC *pDC, const CRect &rect ){};

public:
	// 初期サイズを変更する。
	virtual const CSize & RecalcInitSize(void);
	// 描画
	///< 背景描画
//	virtual void DrawBackground( CDC *pDC, const CRect rect );
	virtual void DrawDC( CDC *pDC, CRect rect ){};
	virtual void DrawExDC( CDC *pDC, const CRect &rect ){};
	virtual void Redraw(BOOL bErase = TRUE){
		if( IsWindow( m_hWnd ) ){
			Invalidate(bErase);
			UpdateWindow();
		}
	};

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CAXGDICtrl)
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//afx_msg BOOL OnEraseBkgnd( CDC* pDC );

	afx_msg void OnChangeActive(NMHDR * pNotifyStruct, LRESULT* result );
	afx_msg void OnChangeStyle(NMHDR * pNotifyStruct, LRESULT* result );
	afx_msg void OnChangeScale(NMHDR * pNotifyStruct, LRESULT* result );
	afx_msg void OnChangeCursol(NMHDR * pNotifyStruct, LRESULT* result );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	UINT		m_nKind;		///< AXGDICtrlの種類（E_AXGDICTRL_KIND参照）
	CSize		m_wndSize;		///< 初期表示時のサイズ
	AXGCACTINFO	m_activeInfo;	///< Active状態の情報
	USERPARAM	m_userParam;	///< ユーザーパラメータ
protected:
	// アクティブ情報初期化
	inline void ClearActiveInfo( AXGCACTINFO *lpActiveInfo );
};
/////////////////////////////////////////////////////////////////////////////
//CAXStringWnd
class CAXStringWnd : public CAXGDICtrl, virtual public CAXColorString
{
// コンストラクション
public:
	CAXStringWnd( COLORREF bkColor = ICTRLCOLOR );
	//コピーコンストラクタ
	CAXStringWnd( const CAXStringWnd &org );

// インプリメンテーション
public:
	virtual ~CAXStringWnd();
	inline CAXStringWnd & operator = ( const CAXStringWnd &src );
	inline CAXStringWnd & Copy( const CAXStringWnd &src );
// アトリビュート
public:
	///< Test size adjust
	inline void SetTextSizeAdjust(BOOL bAdjust = TRUE)	{	m_bTextSizeAdjust = bAdjust;	}
	///< 描画角度
	inline void SetTextOrientation(long nOrientation)	{	m_lfOrientation = nOrientation;	}

// オペレーション
public:
	virtual void DrawDC( CDC *pDC, CRect rect );
	virtual void DrawItem( CDC *pDC, CRect rect, CFont *pTextFont = NULL );
	virtual void TextDraw( CDC* pDC, CRect rect, CFont *pTextFont = NULL );


// オーバーライド
public:
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAXStringWnd)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	virtual void Redraw(BOOL bErase = TRUE){
		if( IsWindow( m_hWnd ) ){	Invalidate(bErase);	UpdateWindow();	}
	};
	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CAXStringWnd)
	//afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	BOOL		m_bTextSizeAdjust;	///< Test size adjust
	long		m_lfOrientation;	///< 描画角度
	
};
/////////////////////////////////////////////////////////////////////////////
// inline finction
/////////////////////////////////////////////////////////////////////////////
// CAXLineStyle
///////////////////////////////////////
/**
 * 	線設定
 * 
 * 	@param lineStyle	線のStyle
 */
inline void CAXLineStyle::SetLineStyle( const LINESTYLE &lineStyle )
{
	SetLineStyle(lineStyle.iStyle, lineStyle.color, lineStyle.iSize );
}
///////////////////////////////////////
/**
 * 	線設定
 * 
 * 	@param iStyle	線の種類
 * 	@param color	線の色
 * 	@param iSize	線のサイズ
 */
inline void CAXLineStyle::SetLineStyle( int iStyle, COLORREF color, int iSize )
{
	m_lineStyle.iStyle = iStyle;
	m_lineStyle.color  = color;
	if(iSize >= 0)	{	m_lineStyle.iSize = iSize;	}
	m_lineStyle.iReserve1 = 0;
	Redraw();
}
///////////////////////////////////////
/**
 * 	線の色設定
 * 
 * 	@param color	線の色
 */
inline void CAXLineStyle::SetLineColor( COLORREF color )
{
	m_lineStyle.color  = color;
	Redraw();
}
///////////////////////////////////////
/**
 * 	ラインスタイルのコピー.
 * 
 * 	@param src	コピー元ラインスタイル
 * 	@return		このクラスのポインタ
 */
inline CAXLineStyle & CAXLineStyle::operator =( const CAXLineStyle &src )
{
	m_lineStyle  = src.m_lineStyle;
	Redraw();
	return *this;
}
/////////////////////////////////////////////////////////////////////////////
// CAXMarkerStyle
///////////////////////////////////////
/**
 * 	マーカースタイルを設定する.
 * 
 * 	@param markStyle		マーカーの情報
 */
inline void CAXMarkerStyle::SetMarkerStyle( const MARKERSTYLE &markStyle )
{
	SetMarkerStyle( markStyle.iMarker, markStyle.iMarkSize, markStyle.iBkStyle );
}
///////////////////////////////////////
/**
 * 	マーカースタイルを設定する.
 * 
 * 	@param iMarker		マーカースタイル
 * 	@param iMarkSize	マークサイズ
 * 	@param iBkStyle		マーカー背景　0:無/1:有/-1:変更しない
 */
inline void CAXMarkerStyle::SetMarkerStyle( int iMarker /*= MARKNONE*/, int iMarkSize /*= -1*/, int iBkStyle /*= -1*/ )
{
	m_markStyle.iMarker = iMarker;
	if( iMarkSize  >=  0 ) m_markStyle.iMarkSize  = iMarkSize;
	if( iBkStyle >=  0 ) m_markStyle.iBkStyle = iBkStyle;
//	m_markStyle.iReserve1 = 0;
	Redraw();
}
///////////////////////////////////////
/**
 * 	マーカーサイズを設定する.
 * 
 * 	@param iMarkSize	マークサイズ
 * 	@return 変更前のマークサイズ
 */
inline int CAXMarkerStyle::SetMarkerSize(int iMarkSize)
{	
	int iOld = m_markStyle.iMarkSize;
	if( iMarkSize  >  0 ) m_markStyle.iMarkSize  = iMarkSize;
	return iOld;
}
///////////////////////////////////////
/**
 * 	マーカースタイルのコピー.
 * 
 * 	@param src	コピー元マーカースタイル
 * 	@return		このクラスのポインタ
 */
inline CAXMarkerStyle & CAXMarkerStyle::operator =( const CAXMarkerStyle &src )
{
	m_markStyle = src.m_markStyle;
	Redraw();
	return *this;
}
/////////////////////////////////////////////////////////////////////////////
// CAXPatternStyle
///////////////////////////////////////
/**
 * 	描画エリアのブラシスタイルを設定する.
 * 
 * 	@param patternStyle		描画エリアのブラシスタイル
 */
inline void CAXPatternStyle::SetPatternStyle( const PATTERNSTYLE &patternStyle )
{
	SetPatternStyle( patternStyle.iBStyle, patternStyle.iHStyle, patternStyle.color );//デフォルト設定
}
///////////////////////////////////////
/**
 * 	描画エリアのブラシスタイルを設定する.
 * 
 * 	@param	int iBStyle		Brush Styles BS_SOLID
 * 	@param	int iHStyle		Hatch Styles HS_HORIZONTAL
 * 	@param	COLORREF color	描画色
 */
inline void CAXPatternStyle::SetPatternStyle( int iBStyle , int iHStyle , COLORREF color  )
{
	m_patternStyle.iBStyle = iBStyle;		///<  Brush Styles BS_SOLID
	m_patternStyle.iHStyle = iHStyle;		///<  Hatch Styles HS_HORIZONTAL
	m_patternStyle.color = color;			///< 色
	m_patternStyle.iReserve1 = 0;
	Redraw();
}
///////////////////////////////////////
/**
 * 	描画エリアのブラシ色を設定する.
 * 
 * 	@param color	ブラシ色
 * 	@return 変更前のブラシ色
 */
inline COLORREF CAXPatternStyle::SetPatternColor( COLORREF color )
{	
	int iOld = m_patternStyle.color;
	m_patternStyle.color  = color;
	return iOld;
}
///////////////////////////////////////
/**
 * 	描画エリアのブラシスタイルのコピー.
 * 
 * 	@param src	コピー元ブラシスタイル
 * 	@return		このクラスのポインタ
 */
inline CAXPatternStyle & CAXPatternStyle::operator =( const CAXPatternStyle &src )
{
	m_patternStyle = src.m_patternStyle;
	Redraw();
	return *this;
}
/////////////////////////////////////////////////////////////////////////////
// CAXGDIFrame
///////////////////////////////////////
/**
 * 	CAXGDIFrameクラスのコピー.
 * 		与えられたCAXGDIFrameクラスをコピーする
 * 
 * 	@param src	コピー元スCAXGDIFrameクラス
 * 	@return		このクラスのポインタ
 */
inline CAXGDIFrame & CAXGDIFrame::operator = ( const CAXGDIFrame &src )
{
	m_bkColor = src.m_bkColor;				///< background color
	m_frameColor = src.m_frameColor;		///< Frame line color
	m_bMonochrome = src.m_bMonochrome;		///< モノクローム表示フラグ
	m_bFrameVisible = src.m_bFrameVisible;	///< 枠表示フラグ
	Redraw();
	return (*this);
}
///////////////////////////////////////
/**
 * 	背景色設定.
 * 	@param color	背景色
 */
inline COLORREF CAXGDIFrame::SetBkColor( COLORREF color )
{
	COLORREF oldColor = m_bkColor;
	m_bkColor = color;
	Redraw();
	return oldColor;
}
///////////////////////////////////////
/**
 * 	枠色設定.
 * 	@param color	枠色
 * 	@return		変更前の枠色
 */
inline COLORREF CAXGDIFrame::SetFrameColor( COLORREF color )
{
	COLORREF oldColor = m_frameColor;		///<Frame line color
	m_frameColor = color;
	Redraw();
	return oldColor;
}
///////////////////////////////////////
/**
 * 	モノクローム表示設定.
 * 	@param bEnable	TRUE:有効/FALSE:無効
 * 	@return		変更前の表示設定
 */
inline BOOL CAXGDIFrame::EnableMonochrome ( BOOL bEnable )
{	
	BOOL bOld = m_bMonochrome;
	m_bMonochrome = bEnable;
	return bOld;
}
///////////////////////////////////////
/**
 * 	背景を描画する。
 * 	@param	pDC			描画デバイスコンテキスト
 * 	@param	rect		描画エリア
 */
inline void CAXGDIFrame::DrawBackground( CDC *pDC, const CRect rect )
{
	//background draw
	pDC->FillSolidRect( rect, (IsMonochrome() ? IWHITE : GetBkColor()) );
}
///////////////////////////////////////
/**
 * 	枠を描画する。
 * 	@param	pDC			描画デバイスコンテキスト
 * 	@param	rect		描画エリア
 */
inline void CAXGDIFrame::DrawFrame( CDC *pDC, CRect rect )
{
	//Frame draw
	if(IsFrameVisible())	{	
		pDC->FrameRect( rect, &CBrush((IsMonochrome() ? IBLACK : GetFrameColor())) );
	}
}
/////////////////////////////////////////////////////////////////////////////
// CAXColorString
///////////////////////////////////////
/**
 * 	CAXColorStringクラスのコピー.
 * 		与えられたCAXColorStringクラスをコピーする
 * 
 * 	@param src	コピー元スCAXColorStringクラス
 * 	@return		このクラスのポインタ
 */
inline CAXColorString & CAXColorString::operator = ( const CAXColorString &src )
{
	m_colorData = src.m_colorData;		///< font color
	m_strData = src.m_strData;			///< Display string
	m_nDTFormat = src.m_nDTFormat;		///< Display style
	Redraw();

	return *this;
}
///////////////////////////////////////
/**
 *	set draw string
 *	
 *	@param	lpszString		draw string
 */
inline void CAXColorString::SetString( LPCTSTR lpszString )
{
	m_strData = lpszString;
	Redraw();
}
///////////////////////////////////////
/**
 *	set font color
 *	
 *	@param	color	font color
 *	@return	Old Value
 */
inline COLORREF	CAXColorString::SetStrColor( COLORREF color )
{
	COLORREF oldColor = m_colorData;
	m_colorData = color;
	Redraw();
	return oldColor;
}
///////////////////////////////////////
/**
 *	set draw text format
 *	
 *	@param	nFormat	draw text format: DT_TOP / DT_LEFT / DT_CENTER / DT_RIGHT / DT_VCENTER / DT_BOTTOM   
 *	@return	Old Value
 */
inline UINT CAXColorString::SetDTFormat( UINT nFormat )
{	
	UINT nOld = m_nDTFormat;

	UINT nNewDTFormat = (m_nDTFormat & ~0x000F) | nFormat;
	m_nDTFormat = nNewDTFormat;
	return 	nOld;
}
/////////////////////////////////////////////////////////////////////////////
// CAXGDICtrl
///////////////////////////////////////
/**
 * 	CAXGDICtrlクラスのコピー.
 * 		与えられたCAXGDICtrlクラスをコピーする
 * 
 * 	@param src	コピー元スCAXGDICtrlクラス
 * 	@return		このクラスのポインタ
 */
inline CAXGDICtrl & CAXGDICtrl::operator = ( const CAXGDICtrl &src )
{
	CAXGDIFrame::Copy(src);
	
	ClearActiveInfo( &m_activeInfo );	///< Active状態の情報
	m_userParam = src.m_userParam;	///< ユーザーパラメータ
	Redraw();
	return *this;
}
///////////////////////////////////////
/**
 * 	CAXGDICtrlクラスのコピー.
 * 		与えられたCAXGDICtrlクラスをコピーする
 * 
 * 	@param src	コピー元スCAXGDICtrlクラス
 * 	@return		このクラスのポインタ
 */
inline CAXGDICtrl & CAXGDICtrl::Copy( const CAXGDICtrl &src )
{
	operator=(src);
	return *this;
}
///////////////////////////////////////
/**
 * 	コントロールの選択有効機能をON/OFFする.
 * 
 * 	@param bEnable	選択機能を有効にするかのフラグ(TRUE:ON FALSE:OFF)
 * 	@return			
 */
inline void CAXGDICtrl::EnableActivate( BOOL bEnable )
{
	if( bEnable )	{
		if(GetSafeHwnd())	{	ModifyStyle( 0, SS_NOTIFY|WS_CHILD );	}//<<<<重要
	}	else	{
		if(GetSafeHwnd())	{	ModifyStyle( SS_NOTIFY, 0 );	}//<<<<重要
	}
}
///////////////////////////////////////
/**
 * 	コントロールの選択有効機能を取得する.
 * 
 * 	@return　TRUE:有効 FALSE:無効			
 */
inline BOOL CAXGDICtrl::IsEnableActivate( void )
{
	if(GetSafeHwnd())	{
		if( (GetStyle() & SS_NOTIFY) && (GetStyle() & WS_CHILD) )	{	return TRUE;	}
	}
	return FALSE;
}
///////////////////////////////////////
/**
 * 	ユーザーパラメータ設定.
 * 
 * 	@param dwParam1	ユーザーパラメータ1
 * 	@param dwParam2	ユーザーパラメータ2
 */
inline void CAXGDICtrl::SetUserParam( DWORD dwParam1, DWORD dwParam2 )
{
	m_userParam.m_dwParam1 = dwParam1;
	m_userParam.m_dwParam2 = dwParam2;
}
///////////////////////////////////////
/**
 * 	ユーザーパラメータ取得.
 * 
 * 	@return		ユーザーパラメータ
 */
inline CAXGDICtrl::USERPARAM & CAXGDICtrl::GetUserParam()
{
	return m_userParam;
}
///////////////////////////////////////
/**
 * 	Activeな情報のクリア.
 *
 */
inline void CAXGDICtrl::ClearActiveInfo( AXGCACTINFO *lpActiveInfo )
{
	///< Active状態の情報のクリア
	memset(lpActiveInfo, 0x00, sizeof(AXGCACTINFO));

	
	///< AXGDICtrlの種類（E_AXGDICTRL_KIND参照）
	lpActiveInfo->nKind = AXGCTRL_NONE;
	///< 0:非選択/1:全体/2:データ/3:カーソル/4:エリアカーソル
	lpActiveInfo->nActive = AXGCTRLACT_NONE;
	lpActiveInfo->iLayer = -1;	///< Activeなレイヤー番号
	lpActiveInfo->iLine = -1;	///< Activeなレイヤーライン番号
	lpActiveInfo->iIndex = -1;	///< Activeなレイヤーのインデックス情報
}
/////////////////////////////////////////////////////////////////////////////
// CAXStringWnd
///////////////////////////////////////
/**
 * 	CAXStringWndクラスのコピー.
 * 		与えられたCAXStringWndクラスをコピーする
 * 
 * 	@param src	コピー元CAXStringWndクラス
 * 	@return		このクラスのポインタ
 */
inline CAXStringWnd & CAXStringWnd::operator = ( const CAXStringWnd &src )
{
	CAXGDICtrl::Copy(src);
	CAXColorString::Copy(src);
	m_bTextSizeAdjust = src.m_bTextSizeAdjust;	///< Test size adjust
	m_lfOrientation = src.m_lfOrientation;	///< 描画角度

	Redraw();
	return *this;
}
///////////////////////////////////////
/**
 * 	CAXStringWndクラスのコピー.
 * 		与えられたCAXStringWndクラスをコピーする
 * 
 * 	@param src	コピー元CAXStringWndクラス
 * 	@return		このクラスのポインタ
 */
inline CAXStringWnd & CAXStringWnd::Copy( const CAXStringWnd &src )
{
	operator=(src);
	return *this;
}
#endif // !defined(_AXGDICORE_H_INCLUDED_)