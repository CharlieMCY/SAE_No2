// AXMasureCtrl.h : ヘッダー ファイル
//
/********************************************************
// クラスのインターフェイス
// CAXGDIScaleData		:スケールデータ保持クラス
// CAXMeasureStyle		:目盛り描画クラス
// CAXMeasureSpin		:目盛り用スピンボタンクラス
// CAXMeasureCtrl		:目盛り描画Wndクラス
//											by YOTSUTSU
//	* History	:	date:2005,24,Mar.	新規作成
ver.1.00	
********************************************************/
//////////////////////////////////////////////////////////////////////
#ifndef __AXMASURECTRL_H_INCLUDED__
#define __AXMASURECTRL_H_INCLUDED__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AXGdiCore.h"

//MeasureStyle

#define AMS_NONE			0x0000	///< 無	
#define AMS_XMODE			0x0001	///< X軸mode
#define AMS_YMODE			0x0002	///< Y軸mode
#define AMS_ZMODE			0x0004	///< Z軸mode
#define AMS_SHOW			0x0010L	///< 表示/非表示フラグ
#define AMS_SH_DETAIL		0x0020L	///< 詳細目盛りの表示/非表示
#define AMS_SH_MIN			0x0040L	///< MIN目盛りの表示/非表示
#define AMS_SH_MAX			0x0080L	///< MAX目盛りの表示/非表示
#define AMS_SH_DELTA		0x0100L	///< 目盛りの値の表示/非表示
#define AMS_SH_VALMIN		0x0200L	///< MIN目盛りの値の表示/非表示
#define AMS_SH_VALMAX		0x0400L	///< MAX目盛りの値の表示/非表示
#define AMS_SH_LOGZERO		0x0800L	///< LOG表示 ゼロの表示/非表示
#define AMS_INSIDE			0x0000L	///< Scale inside			目盛りの向き設定(AMS_INSIDE:内側/AMS_OUTSIDE:外側/AMS_SIDEBOTH:交差)
#define AMS_OUTSIDE			0x1000L	///< Scale outside			目盛りの向き設定(AMS_INSIDE:内側/AMS_OUTSIDE:外側/AMS_SIDEBOTH:交差)
#define AMS_SIDEBOTH		0x2000L	///< Scale inside&outside	目盛りの向き設定(AMS_INSIDE:内側/AMS_OUTSIDE:外側/AMS_SIDEBOTH:交差)
#define AMS_EN_ORG			0x00010000L	///< 目盛り原点の有効/無効
#define AMS_ADJUST			0x00020000L	///< 値表示 調整の有効/無効
#define AMS_EN_DIVDELTA		0x00040000L	///< 目盛りの分割指定の有効/無効
#define AMS_ALL				0x000FFFFFL	///< MeasureStyle All bit
//Scale Change type
#define AMS_RANGE_UP		VK_PRIOR	// VK_PAGE_UP:					（Delta分レンジ拡大）
#define AMS_RANGE_DOWN		VK_NEXT		// VK_PAGE_DOWN:				（Delta分レンジ縮小）
#define AMS_OFFSET_UP		VK_UP		// Process the UP ARROW key.　	（+Deltaオフセット）
#define AMS_OFFSET_DOWN		VK_DOWN		// Process the DOWN ARROW key.	（-Deltaオフセット）


/////////////////////////////////////////////////////////////////////////////
// 構造体
#pragma pack( push, 1 )

///< スケールデータ保持型
typedef struct tagGdiScaleInfo{	//16byte
	double		dRange;			///< データ範囲
	double		dOrg;			///< データ原点
} GDISCALEINFO;

///< MeasureStyle(目盛りスタイル)情報
typedef struct tagMeasureStyle{		//64byte
	DWORD		dwSize;			///< Specifies the size, in bytes, of this structure.
	DWORD		dwMsStyle;		///< MeasureStyle
	double		dDelta;			///< 目盛り間隔(データ値/分割 指定)
	double		dDetailDelta;	///< 詳細目盛り間隔(データ値/分割 指定)
	double		dOrgDelta;		///< 目盛り間隔の原点(データ値指定)
	short		sDetailRatio;	///< 詳細目盛り長さ比率指定[%]
	short		sFontSize;		///< 目盛りの値表示のフォントサイズ
	long		lAngle;			///< 目盛りの文字角度
	long		lReserve1;		///< 予備
	COLORREF	scaleColor;		///< スケール表示色
	COLORREF	measureColor;	///< 目盛りの値文字色
//	TCHAR		szFormat[12];	///< 目盛り値の表示書式
	BYTE		byteReserve[12];///< 予備
} MEASURESTYLE;

#pragma pack( pop )
/////////////////////////////////////////////////////////////////////////////
// 関数

/////////////////////////////////////////////////////////////////////////////
// CAXGDIScaleData	描画用スケールクラス
//　座標系原点を「left, top」として 座標<=>データが行える。（Logスケールも対応）
class CAXGDIScaleData
{
public:
	/**
	 * 	構築.
	 * 		スケールデータを保持する
	 * 
	 * 	@param dblMin	最小値
	 * 	@param dblMax	最大値
	 * 	@param bLog		対数表示
	 */
	CAXGDIScaleData( double dblMin = 0.0, double dblMax = 100.0, BOOL bLog = FALSE )
	{
		memset(&m_scaleInfo,0x00,sizeof(GDISCALEINFO));
		
		m_scaleInfo.dRange = 100.0;				///< データ範囲
		m_scaleInfo.dOrg = 0.0;					///< データ原点
		SetScale( dblMin, dblMax );				///< スケール設定
		SetLogMode( bLog, FALSE);				///< 対数表示有効
	}
	CAXGDIScaleData(const GDISCALEINFO & scaleInfo ,BOOL bLog = FALSE )
	{	
		CAXGDIScaleData( scaleInfo.dOrg,  scaleInfo.dRange - scaleInfo.dOrg, bLog ) ;
	}
	//コピーコンストラクタ
	CAXGDIScaleData( const CAXGDIScaleData &org)
	{
		operator =( org );
		//m_bLog = FALSE;
		//m_scaleInfo = scaleSrc.m_scaleInfo;
		//SetLogMode( scaleSrc.m_bLog, FALSE);				///< 対数表示有効
	}
// インプリメンテーション
public:
	virtual ~CAXGDIScaleData(){};
	
//	inline CAXGDIScaleData const GetAXGdiScale(void) const { 	return (*this);	}

// アトリビュート
public:
	//スケール設定
	virtual const GDISCALEINFO & SetScale( double dblMin, double dblMax );
	virtual const GDISCALEINFO & SetLogScale(double dblMin , double dblMax, BOOL bScaleAuto );
	virtual const GDISCALEINFO & SetLogMode(BOOL bLog = TRUE,BOOL bScaleAuto = TRUE);
	inline void SetOrg( double dOrg )		{	m_scaleInfo.dOrg = dOrg;	}
	inline void SetRange( double dRange )	{	m_scaleInfo.dRange = dRange;	}
	//スケール情報取得
	inline const GDISCALEINFO & GetScaleInfo( void )	{	return m_scaleInfo;	}
	inline double GetMin( void )	{	return m_scaleInfo.dOrg;	}
	inline double GetMax( void )	{	return (m_scaleInfo.dRange + m_scaleInfo.dOrg);	}
	inline double GetOrg( void )	{	return m_scaleInfo.dOrg;	}
	inline double GetRange( void )	{	return m_scaleInfo.dRange;	}
	//対数スケール
	virtual inline BOOL	IsLogMode(void)		{	return ( m_bLog);		}

protected:
	GDISCALEINFO		m_scaleInfo;	///< スケールデータ
	BOOL				m_bLog;			///< 対数表示有効
// オペレーション
public:
	//座標系関連
	//Static
	//描画用スケール取得
	static double GetDrawOrg( const CAXGDIScaleData &scale );
	static double GetDrawRange( const CAXGDIScaleData &scale );
	static double GetDrawMax( const CAXGDIScaleData &scale );
	//データから座標を求める。
	static int Data2PointX( double dXdata, const CAXGDIScaleData &scale ,int width );
	static int Data2PointY( double dYdata, const CAXGDIScaleData &scale, int height );
	//座標からデータ求める。
	static double Point2DataX( int iXdata, const CAXGDIScaleData &scale ,int width );
	static double Point2DataY( int iYdata, const CAXGDIScaleData &scale, int height );

	//Non static
	//描画用スケール取得
	inline double GetDrawOrg(void)		{	return GetDrawOrg(*this);	}
	inline double GetDrawRange(void)	{	return GetDrawRange(*this);	}
	inline double GetDrawMax(void)		{	return GetDrawMax(*this);	}
	//データから座標を求める。
	inline int Data2PointX( double dXdata, int width )	{	return Data2PointX( dXdata, (*this), width);	}
	inline int Data2PointY( double dYdata, int height )	{	return Data2PointY( dYdata, (*this), height );	}
	//座標からデータ求める。
	inline double Point2DataX( int iXdata, int width )	{	return Point2DataX( iXdata, (*this), width );	}
	inline double Point2DataY( int iYdata, int height )	{	return Point2DataY( iYdata, (*this), height );	}

	///////////////////////////////////////
	/**
	 * 	スケール情報のコピー.
	 *
	 * 	@param	scaleSrc	スケール情報
	 *	@return スケール情報
	 */
	inline CAXGDIScaleData & operator =( const CAXGDIScaleData &src )
	{
		m_scaleInfo = src.m_scaleInfo;
		m_bLog = src.m_bLog;
		SetLogMode(src.m_bLog,FALSE);	
		return (*this);
	}
	inline CAXGDIScaleData & Copy( const CAXGDIScaleData &src )
	{
		operator = (src);
		return (*this);
	}
	//スケールのオフセット
	inline const GDISCALEINFO &  SetOffset( double dOffset );
	//スケールの拡大
	inline const GDISCALEINFO &  SetZoom( double dDeltaStt, double dDeltaEnd );
// オーバーライド
public:

//メンバ変数
protected:

};
/////////////////////////////////////////////////////////////////////////////
// CAXScaleStyle
class CAXScaleStyle  : public CAXGDIScaleData
{
// コンストラクション
public:
	CAXScaleStyle( double dblMin = 0.0, double dblMax = 100.0, BOOL bLog = FALSE )//;
		: CAXGDIScaleData( dblMin, dblMax , bLog )
	{

	}
	//コピーコンストラクタ
//	CAXScaleStyle( const CAXScaleStyle &org );  

// インプリメンテーション
public:
	virtual ~CAXScaleStyle();
	// スケールスタイルのコピー
//	inline CAXScaleStyle & operator =( const CAXScaleStyle &src );
// アトリビュート
public:
	CString			m_strTitle;		//名称
	CString			m_strFormat;	//Scaleフォーマット
// オペレーション
public:
};
/////////////////////////////////////////////////////////////////////////////
// CAXMeasureStyle
class CAXMeasureStyle  : public CAXGDIScaleData
{
// コンストラクション
public:
	CAXMeasureStyle(int iMode = MEASUREX, BOOL bAdjust = TRUE);
	//コピーコンストラクタ
	CAXMeasureStyle( const CAXMeasureStyle &org );  

// インプリメンテーション
public:
	virtual ~CAXMeasureStyle();
	// スケールスタイルのコピー
	inline CAXMeasureStyle & operator =( const CAXMeasureStyle &src );
private:
	//
static void GetDetailRect(const CRect &rect, int iMode, int iType, long lRatio, LPRECT lpCalcRect );

// アトリビュート
public:
//属性設定
	///< スケールモード設定
	inline void SetScaleMode( int iMode = MEASUREX ) ;
	///< 目盛りの向き設定(AMS_INSIDE:内側/AMS_OUTSIDE:外側/AMS_SIDEBOTH:交差)
	inline int SetScaleType( int iType = AMS_INSIDE);
	///< 目盛りの表示/非表示
	inline BOOL ShowScale( BOOL bShow = TRUE, BOOL bDetailShow = TRUE);
	///< 最小値/最大値の表示/非表示
	inline void ShowScaleMinMax( BOOL bShowMin, BOOL bShowMax );	
	///< 目盛りの値の表示/非表示
	inline void ShowMeasureDelta( BOOL bShow );
	///< 最小値/最大値の値の表示/非表示
	inline void ShowMeasureMinMax( BOOL bShowMin, BOOL bShowMax );
	///< 目盛り原点の有効/無効
	inline BOOL SetDeltaOrg( BOOL bEnable = TRUE, double dOrg = 0.0 );
	///< 目盛りの分割指定の有効/無効
	inline void EnableDivDelta( BOOL bEnableDiv );
	///< LOG表示 ゼロの表示/非表示
	inline void ShowLogZero(BOOL bShow = TRUE);
	///< 値表示 調整の有効/無効
	inline void SetMeasureAdjust(BOOL bAdjust = TRUE);
	///< 詳細目盛り長さ比率指定[%]
	inline void	SetScaleDetailRaio( short sRatio );
	///< 目盛り軸のフォントサイズ
	///< 目盛り/目盛り値の表示フォーマット
	inline void	Format( LPCTSTR format, short sFontSize = -1 );
	///< 目盛り/目盛り軸の色
	inline COLORREF SetScaleColor( COLORREF color );
	///< 目盛り/目盛り値の色
	inline COLORREF SetMeasureColor( COLORREF color);
	///< 目盛り文字角度
	inline void SetMeasureAngle( long lAngle );
	// 目盛り名の単位
	//inline void	SetUnit( LPCSTR strUnit, LPCSTR format = NULL);
//属性取得
	///< MeasureStyle
	inline const MEASURESTYLE & GetStyleInfo(void)		{	return m_measureStyle;	}
	///< MeasureStyle style
	inline const DWORD	GetMsStyle(void)	{	return m_measureStyle.dwMsStyle;	}
	///< スケールモード
	inline int GetScaleMode(void) const		{	return ((m_measureStyle.dwMsStyle & AMS_YMODE) ? MEASUREY : MEASUREX);	}
	///< 目盛りの向き(0:内側/1:外側/2:交差)
	inline int GetScaleType(void) const		{	return (0x3000 & m_measureStyle.dwMsStyle);	}
	///< 目盛り原点の有効/無効
	inline BOOL IsDeltaOrgEnable(void) const{	return ((m_measureStyle.dwMsStyle & AMS_EN_ORG) ? TRUE : FALSE);	}
	///< 目盛りの表示/非表示
	inline BOOL IsShowScale(void) const		{	return ((m_measureStyle.dwMsStyle & AMS_SHOW) ? TRUE : FALSE);	}
	///< 詳細目盛りの表示/非表示
	inline BOOL IsShowDetailScale()	{	return ((m_measureStyle.dwMsStyle & AMS_SH_DETAIL) ? TRUE : FALSE);	}
	///< 最小値/最大値の表示/非表示
	inline BOOL IsShowScaleMin()	{	return ((m_measureStyle.dwMsStyle & AMS_SH_MIN) ? TRUE : FALSE);	}
	inline BOOL IsShowScaleMax()	{	return ((m_measureStyle.dwMsStyle & AMS_SH_MAX) ? TRUE : FALSE);	}
	///< 目盛りの値の表示/非表示
	inline BOOL IsShowMeasureDelta()	{	return ((m_measureStyle.dwMsStyle & AMS_SH_DELTA) ? TRUE : FALSE);	}
	// 最小値/最大値の値の表示/非表示
	inline BOOL IsShowMeasureMin()	{	return ((m_measureStyle.dwMsStyle & AMS_SH_VALMIN) ? TRUE : FALSE);	}
	inline BOOL IsShowMeasureMax()	{	return ((m_measureStyle.dwMsStyle & AMS_SH_VALMAX) ? TRUE : FALSE);	}
	///< LOG表示 ゼロの表示/非表示
	inline BOOL IsShowLogZero()	{	return ((m_measureStyle.dwMsStyle & AMS_SH_LOGZERO) ? TRUE : FALSE);	}
	///< 値表示 調整の有効/無効
	inline BOOL IsMeasureAdjust()	{	return ((m_measureStyle.dwMsStyle & AMS_ADJUST) ? TRUE : FALSE);	}
	///< 目盛り間隔(データ値/分割数)
	inline double GetScaleDelta( void )			{	return m_measureStyle.dDelta;				}
	///< 詳細目盛り間隔(データ値/分割数)
	inline double GetScaleDetailDelta( void )	{	return m_measureStyle.dDetailDelta;			}
	//Range UP/DOWN操作での増減値を取得.
	inline double GetScaleRangeDelta( void );
	///< 目盛り間隔の原点(データ値指定)
	inline double GetDeltaOrg( void )		{	return m_measureStyle.dOrgDelta;	}
	///< 目盛りの分割指定の有効/無効
	inline BOOL IsEnableDivDelta( void )	{	return ((m_measureStyle.dwMsStyle & AMS_EN_DIVDELTA) ? TRUE : FALSE);	}
	///< 詳細目盛り長さ比率指定[%]
	inline short   GetScaleDetailRatio( void )	{	return m_measureStyle.sDetailRatio;			}
	///< 目盛り軸のフォントサイズ
	inline short GetMeasureFontSize( void );
	///< 目盛り/目盛り軸の色
	inline COLORREF GetScaleColor( void );
	///< 目盛り/目盛り値の色
	inline COLORREF GetMeasureColor( void );
	///< 目盛り文字角度
	inline long GetMeasureAngle( void );
	///< 目盛り/目盛り値の表示フォーマット
	inline LPCTSTR GetFormat( void )	{	return ((LPCTSTR)(m_strFormat));			}
	// 目盛り名の単位
//	inline LPCTSTR	GetUnit( void );
	
	inline CAXColorString & GetNameAXString( void )		{	return m_axstrName;		}	///< 名称の表示文字列
	inline CAXColorString & GetMaxSideAXString( void )	{	return m_axstrMaxSide;	}	///< Max側の表示文字列
	inline CAXColorString & GetMinSideAXString( void )	{	return m_axstrMinSide;	}	///< Min側の表示文字列
	
	//< 表示文字列
	inline virtual void SetString( LPCTSTR lpszString )		{	m_axstrName.SetString( lpszString );		}
	inline virtual COLORREF	SetStrColor( COLORREF color )	{	return m_axstrName.SetStrColor( color );	}
	inline virtual CString GetString(void) const			{	return( m_axstrName.GetString() );			}
	inline virtual COLORREF GetStrColor(void) const			{	return( m_axstrName.GetStrColor() );		}

//メンバ変数
protected:
	MEASURESTYLE			m_measureStyle;		///< MeasureStyle(目盛りスタイル)情報
	CString					m_strFormat;		///< 目盛り値の表示書式
	CAXColorString			m_axstrName;		///< 名称の表示文字列
	CAXColorString			m_axstrMaxSide;		///< MAX側の表示文字列
	CAXColorString			m_axstrMinSide;		///< MIN側の表示文字列
//	CString					m_strUnit;			///< 単位の表示文字列
//	CString					m_strNameFormat;	///< 目盛り名称の書式
// オペレーション
public:
	// 目盛り設定
	virtual void SetScale( double dMin, double dMax, double dDelta = -1.0, double dDetailDelta = -1.0 );
	// 目盛りの軸を描画.
	virtual	void DrawScale( CDC *pDC, const CRect &rect );
	// 目盛りの値を描画.
	virtual	void DrawMeasure( CDC *pDC, const CRect &rect );
	// 目盛りの名称を描画.
	virtual	void DrawMeasureName( CDC *pDC, const CRect &rect, int nFontSize );
	// 目盛りの文字列を描画.
	virtual	void DrawMeasureMaxString( CDC *pDC, const CRect &rect, BOOL bMonochrome );
	virtual	void DrawMeasureMinString( CDC *pDC, const CRect &rect, BOOL bMonochrome );
	// 目盛りの軸を描画.	
	static void DrawScale( CDC *pDC, const CRect &rect, int iMode, int iType, double dMin, double dMax, double dOrg, double dDelta, double dDetailDelta, long lDetailRatio );
	static void DrawDivScale( CDC *pDC, const CRect &rect, int iMode, int iType, double dDelta, double dDetailDelta, long lDetailRatio );
	static void DrawLogScale( CDC *pDC, const CRect &rect, int iMode, int iType, double dMin, double dMax, long lDetailRatio );
	// 目盛りの値を描画.
	static void DrawMeasure( CDC *pDC, const CRect &rect, int iMode, double dMin, double dMax, double dOrg, double dDelta, LPCTSTR lpszFormat, BOOL bAdjust );
	static void DrawDivMeasure( CDC *pDC, const CRect &rect, int iMode, double dMin, double dMax, double dDelta, LPCTSTR lpszFormat, BOOL bAdjust );
	static void DrawLogMeasure( CDC *pDC, const CRect &rect, int iMode, double dMin, double dMax, double dDelta, LPCTSTR lpszFormat, BOOL bAdjust );
	// スケール文字描画
	static void TextDraw( CDC *pDC, CRect rect, int iMode, int iX, int iY, LPCTSTR lpszData, int iAdjust);
	// スケールスタイルのスケールのコピー
	const GDISCALEINFO & CopyScale( const CAXMeasureStyle &src );
	// スケールスタイルのコピー
	CAXMeasureStyle & Copy( const CAXMeasureStyle &src );
	// 再描画
	virtual void Redraw(BOOL bErase = TRUE){}
};

/////////////////////////////////////////////////////////////////////////////
// CAXMeasureSpin
class CAXMeasureSpin : public CSpinButtonCtrl
{
public:
	CAXMeasureSpin(){};

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAXMeasureCtrl ウィンドウ
class CAXMeasureCtrl : public CAXGDICtrl, public CAXMeasureStyle
{
// コンストラクション
public:
	CAXMeasureCtrl( int iMode = MEASUREX, int iMargin = 0 ,BOOL bAdjust = TRUE);
	// コピーコンストラクタ
	CAXMeasureCtrl( const CAXMeasureCtrl &org );
// アトリビュート
public:
	static const int c_iMeasureSise;				// 目盛りの脚の長さ

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAXMeasureCtrl)
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CAXMeasureCtrl();
	// CAXMeasureCtrlのコピー
	inline CAXMeasureCtrl & operator =( const CAXMeasureCtrl &src );
	inline CAXMeasureCtrl & operator =( const CAXMeasureStyle &src );
	inline CAXMeasureCtrl & operator =( const CAXGDIScaleData &src );

	inline CAXMeasureCtrl & Copy( const CAXMeasureCtrl &src )	{	operator=(src);	return *this;	}
	inline CAXMeasureCtrl & CopyStyle( const CAXMeasureStyle &src )
	{
		CAXMeasureStyle::Copy(src);
		return *this;
	}
	// 描画領域取得
	//virtual void GetDrawRect(LPRECT lpRect) const;
	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CAXMeasureCtrl)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	// 通知メッセージの処理
	virtual BOOL OnChangeActive( AXGCNOTIFY *pNotifyMsg );
	virtual BOOL OnChangeStyle( AXGCNOTIFY *pNotifyMsg );
	virtual BOOL OnChangeScale( AXGCNOTIFY *pNotifyMsg );
//	virtual BOOL OnChangeCursol( AXGCNOTIFY *pNotifyMsg );

protected:
	BOOL		m_bErase;			///< WM_ERASEBKGND描画
	int			m_iMargin;			///< マージン(+:外側）
//	int			m_iMeasureSpan;		///< 目盛り間隔
	CSize		m_spinSize;			///< スピンサイズ
//	CSize		m_measureSize;		///< 初期表示時のサイズ

	int			m_iFontSize;		///< 文字列描画サイズ

	CAXMeasureSpin	m_spinCtrl[2];	///< スピンボタン

public:
	// モード変更
	void SetMode(int iMode = MEASUREX, int iMargin = 0 ,BOOL bAdjust = TRUE);
	// ウィンドウサイズ変更
	void MoveWindow( int x, int y, int nWidth, int nHeight, BOOL bRepaint = TRUE );
	void MoveWindow( LPCRECT lpRect, BOOL bRepaint = TRUE );
	BOOL SetWindowPos( const CWnd* pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags );

	// ウインドウサイズ取得
	void GetClientRect(LPRECT lpRect);
	void GetWindowRect(LPRECT lpRect);

	///< 文字列描画サイズ 
	inline void	SetFontSize( int iSize = -1 );
	inline int	GetFontSize( void ) const ;

	// スピンの表示/非表示
	BOOL ShowSpin( BOOL bShow );
	BOOL IsShowSpin(void) const ;

	// 目盛り描画
	virtual void DrawDC( CDC *pDC, CRect rect );
	
	// 更新
	inline void Redraw( void );

protected:
	// 描画マージンを取得する。
	inline const int GetWindowMargin( void ) const		{	return m_iMargin;	}	///< 描画マージン

	// サイズ計算
	virtual void CalcRect( CRect &rect );
	virtual void SubcalcRect( CRect &rect );

	// スピン初期化
	void CreateSpin();

	// スピンの再配置
	void RecalcLayoutSpin();
	// 目盛り名の描画
//	virtual void DrawMeasureName( CDC *pDC, const CRect &rect, LPCSTR strName );
	// 描画前処理
	virtual void BeginPaintDC( CDC *pDC, const CRect &rect );
	// 描画後処理
	virtual void EndPaintDC( CDC *pDC, const CRect &rect );
	virtual void DrawActiveFrame( CDC *pDC, const CRect &rect, int size = 7 );
	//virtual void DrawBackground( CDC *pDC, const CRect rect );
};
/////////////////////////////////////////////////////////////////////////////
// inline finction
/////////////////////////////////////////////////////////////////////////////
// CAXGDIScaleData
///////////////////////////////////////
/**
 * 	スケールのオフセット.
 *
 * 	@param	dOffset		オフセット値
 *	@return スケール情報
 */
inline const GDISCALEINFO & CAXGDIScaleData::SetOffset( double dOffset )
{	
	m_scaleInfo.dOrg += dOffset; return (m_scaleInfo);
}
///////////////////////////////////////
/**
 * 	スケールの拡大.
 *
 * 	@param	dDeltaStt		拡大始点
 * 	@param	dDeltaEnd		拡大終点
 *	@return スケール情報
 */
inline const GDISCALEINFO & CAXGDIScaleData::SetZoom( double dDeltaStt, double dDeltaEnd )
{
	SetScale( dDeltaStt * m_scaleInfo.dRange + m_scaleInfo.dOrg,
			dDeltaEnd * m_scaleInfo.dRange + m_scaleInfo.dOrg);

	return (m_scaleInfo);
}
/////////////////////////////////////////////////////////////////////////////
// CAXMeasureStyle
///////////////////////////////////////
/**
 * 	CAXMeasureStyleクラスのコピー.
 * 		与えられたスケールスタイルをコピーする
 * 
 * 	@param src	コピー元スケールスタイル
 * 	@return		このクラスのポインタ
 */
inline CAXMeasureStyle & CAXMeasureStyle::operator =( const CAXMeasureStyle &src )
{
	CAXGDIScaleData::Copy(src);

//	CopyScale(src);
//	m_measureStyle = src.GetStyleInfo();
	///< Style
//	DWORD dwNewStyle = (AMS_ALL & src.GetMsStyle());
//	m_measureStyle.dwMsStyle = dwNewStyle;

	m_measureStyle = src.m_measureStyle;	///< MeasureStyle(目盛りスタイル)情報

	m_axstrName = src.m_axstrName;			///< 名称の表示文字列
	m_axstrMaxSide = src.m_axstrMaxSide;	///< Up側の表示文字列
	m_axstrMinSide = src.m_axstrMinSide;	///< Down側の表示文字列
//	m_strUnit = src.m_strUnit;				///< 単位の表示文字列
	m_strFormat = src.m_strFormat;			///< 目盛り値の表示書式
//	m_strNameFormat = src.m_strNameFormat;	///< 目盛り名称の書式

	Redraw();

	return *this;
}
///////////////////////////////////////
/**
 * 	スケールモード設定.
 *
 * 	@param	iMode		MEASUREX/MEASUREY
 *	@return 
 */
inline void CAXMeasureStyle::SetScaleMode( int iMode /*= MEASUREX*/ )
{
	if(iMode == MEASUREY)	{	m_measureStyle.dwMsStyle |= AMS_YMODE ;				}
	else					{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_YMODE) ;	}
}
///////////////////////////////////////
/**
 * 	目盛りの向き設定.
 *
 * 	@param	iType		内側:AMS_INSIDE / 外側:AMS_OUTSIDE / 交差:AMS_SIDEBOTH
 *						目盛りの向き設定(0:内側/1:外側/2:交差)
 *	@return 変更前の目盛りの向き
 */
inline int CAXMeasureStyle::SetScaleType( int iType /*= AMS_INSIDE*/)
{
	int iOld = GetScaleType();	
	if(iType >= 0 && iType < 0x3000)	{
		m_measureStyle.dwMsStyle &= (AMS_ALL ^ 0x3000) ;//消します。
		m_measureStyle.dwMsStyle |= iType;
	}
	return iOld;
}
//////////////////////////////////////
/**
 * 	目盛りの描画原点の有効/無効を設定. (データ値指定)
 *
 * 	@param	bEnable		TREU:有効/FALSE:無効
 * 	@param	dOrg		目盛り間隔の原点(データ値指定)
 *						dOrgの値を基準に描画する。
 *	@return	変更前の状態
 */
inline BOOL CAXMeasureStyle::SetDeltaOrg( BOOL bEnable /*= TRUE*/, double dOrg /*= 0.0*/ )
{
	BOOL bOld = IsDeltaOrgEnable();

	if(bEnable)	{	m_measureStyle.dwMsStyle |= AMS_EN_ORG ;				}
	else		{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_EN_ORG) ;	}

	m_measureStyle.dOrgDelta = dOrg;

	return bOld;
}
//////////////////////////////////////
/**
 * 	目盛りの分割指定の有効/無効を設定. (分割/データ値　指定)
 *
 * 	@param	bEnableDiv		TREU:有効（分割指定）/FALSE:無効（データ値指定）
 *						
 *	@return
 */
inline void CAXMeasureStyle::EnableDivDelta( BOOL bEnableDiv )
{
	if(bEnableDiv)	{	m_measureStyle.dwMsStyle |= AMS_EN_DIVDELTA ;				}
	else			{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_EN_DIVDELTA) ;	}
}
//////////////////////////////////////
/**
 * 	目盛りの表示/非表示を設定.
 *
 * 	@param	bShow		表示/非表示
 * 	@param	bDetailShow	詳細目盛りの表示/非表示
 *
 *	@return 変更前の状態
 */
inline BOOL CAXMeasureStyle::ShowScale( BOOL bShow /*= TRUE*/,BOOL bDetailShow /*= TRUE*/)
{
	BOOL bOld = IsShowScale();
	if(bShow)					{	m_measureStyle.dwMsStyle |= AMS_SHOW ;				}
	else						{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_SHOW) ;	}

	if(bShow && bDetailShow)	{	m_measureStyle.dwMsStyle |= AMS_SH_DETAIL ;				}
	else						{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_SH_DETAIL) ;	}

	return bOld;
}
//////////////////////////////////////
/**
 * 	最小値/最大値の目盛りの表示/非表示を設定.
 *
 * 	@param	bShowMin	最小値　表示/非表示
 *　@param	bShowMax	最大値　表示/非表示
 *	@return 
 */
inline void CAXMeasureStyle::ShowScaleMinMax( BOOL bShowMin, BOOL bShowMax )
{
	if(bShowMin)	{	m_measureStyle.dwMsStyle |= AMS_SH_MIN ;				}
	else			{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_SH_MIN) ;	}
	if(bShowMax)	{	m_measureStyle.dwMsStyle |= AMS_SH_MAX ;				}
	else			{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_SH_MAX) ;	}
}
//////////////////////////////////////
/**
 * 	目盛りの値の表示/非表示を設定.
 *
 * 	@param	bShow		表示/非表示
 *
 *	@return 
 */
inline void CAXMeasureStyle::ShowMeasureDelta( BOOL bShow )
{
	if(bShow)	{	m_measureStyle.dwMsStyle |= AMS_SH_DELTA ;				}
	else		{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_SH_DELTA) ;	}
}
//////////////////////////////////////
/**
 * 	目盛りの値の最小値/最大値の表示/非表示を設定.
 *
 * 	@param	bShowMin	最小値　表示/非表示
 *　@param	bShowMax	最大値　表示/非表示
 *	@return 
 */
inline void CAXMeasureStyle::ShowMeasureMinMax( BOOL bShowMin, BOOL bShowMax )
{
	if(bShowMin)	{	m_measureStyle.dwMsStyle |= AMS_SH_VALMIN ;				}
	else			{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_SH_VALMIN) ;	}
	if(bShowMax)	{	m_measureStyle.dwMsStyle |= AMS_SH_VALMAX ;				}
	else			{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_SH_VALMAX) ;	}
}
//////////////////////////////////////
/**
 * 	対数スケール時の目盛りの値のゼロの表示/非表示を設定.
 *
 * 	@param	bShow		表示/非表示
 *	@return 
 */
inline void CAXMeasureStyle::ShowLogZero(BOOL bShow /*= TRUE*/)
{
	if(bShow)	{	m_measureStyle.dwMsStyle |= AMS_SH_LOGZERO ;				}
	else		{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_SH_LOGZERO ) ;	}
}
//////////////////////////////////////
/**
 * 	目盛りの値の描画両端の調整の有効/無効を設定.
 *
 * 	@param	bAdjust		TRUE:有効/FALSE：無効
 *	@return 
 */
inline void CAXMeasureStyle::SetMeasureAdjust(BOOL bAdjust /*= TRUE*/)
{
	if(bAdjust)	{	m_measureStyle.dwMsStyle |= AMS_ADJUST ;				}
	else		{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_ADJUST ) ;	}
}
//////////////////////////////////////
/**
 * 	目盛り長さに対する詳細目盛り長さ比率指定[%].
 *
 * 	@param	lRatio		0～100で0～100%
 *	@return 
 */
inline void	CAXMeasureStyle::SetScaleDetailRaio( short sRatio )
{
	if(sRatio >= 0 || sRatio <= 100)		{	m_measureStyle.sDetailRatio = sRatio;		}
}
//////////////////////////////////////
/**
 * 	Range UP/DOWN操作での増減値を取得.
 *
 *	@return Range UP/DOWN操作での増減値
 */
inline double CAXMeasureStyle::GetScaleRangeDelta( void )
{	
	if(IsEnableDivDelta())	{
		if(m_measureStyle.dDelta >= 2.0)	{
			return (GetRange() / m_measureStyle.dDelta);
		}	else	{
			return 0.0;
		}
	}
	return m_measureStyle.dDelta;
}
//////////////////////////////////////
/**
 * 	目盛り軸のフォントサイズを取得.
 *
 *	@return フォントサイズ
 */
inline short CAXMeasureStyle::GetMeasureFontSize( void )
{
	return m_measureStyle.sFontSize;		///< 目盛りの値表示のフォントサイズ
}
///////////////////////////////////////
/**
 * 	目盛り軸の色の設定.
 * 		目盛り軸の色を設定する
 * 
 * 	@param color	設定する目盛りの色
 * 	@return			元の目盛り色
 */
inline COLORREF CAXMeasureStyle::SetScaleColor( COLORREF color )
{
	COLORREF oldColor = m_measureStyle.scaleColor;
	m_measureStyle.scaleColor = color;
	Redraw();
	return oldColor;
}
///////////////////////////////////////
/**
 * 	目盛り軸の色の取得.
 * 		現在の目盛り軸の色を取得する
 * 
 * 	@return			現在の目盛り色
 */
inline COLORREF CAXMeasureStyle::GetScaleColor()
{
	return m_measureStyle.scaleColor;
}
///////////////////////////////////////
/**
 * 	目盛り値の表示色の設定.
 * 		目盛り値の表示色を設定する
 * 
 * 	@param color	設定する目盛りの色
 * 	@return			元の目盛り色
 */
inline COLORREF CAXMeasureStyle::SetMeasureColor( COLORREF color )
{
	COLORREF oldColor = m_measureStyle.measureColor;
	m_measureStyle.measureColor = color;
	Redraw();
	return oldColor;
}
///////////////////////////////////////
/**
 * 	目盛り値の表示色の取得.
 * 		現在の目盛り値の表示色を取得する
 * 
 * 	@return			現在の目盛り色
 */
inline COLORREF CAXMeasureStyle::GetMeasureColor()
{
	return m_measureStyle.measureColor;
}
///////////////////////////////////////
/**
 * 	目盛り文字角度を設定する.
 * 		目盛りの文字角度を設定する
 * 
 * 	@param lAngle	文字角度(1/10度単位)
 */
inline void CAXMeasureStyle::SetMeasureAngle( long lAngle )
{
	m_measureStyle.lAngle = lAngle;
}
///////////////////////////////////////
/**
 * 	目盛り文字角度を取得する.
 * 		目盛りの文字角度を取得する
 * 
 * 	@return 文字角度(1/10度単位)
 */
inline long CAXMeasureStyle::GetMeasureAngle( void )
{
	return ( m_measureStyle.lAngle );
}
///////////////////////////////////////
/**
 * 	目盛りフォーマット & フォントサイズ.
 * 		目盛りのフォーマットをprintf型式で指定する
 * 
 * 	@param format		目盛りのフォーマット
 * 	@param sFontSize	目盛りのフォントサイズ
 */
inline void	CAXMeasureStyle::Format( LPCTSTR format, short sFontSize /*= -1*//*, int iSpan /*= 1*/ )
{
//	m_iMeasureSpan = ( iSpan > 0 )? iSpan: 1;
//	m_strFormat = format;

//	size_t size = sizeof(m_measureStyle.szFormat)/sizeof(TCHAR);
	m_strFormat = format;
//	_tcsncpy( m_measureStyle.szFormat, format, size);
//	m_measureStyle.szFormat[size-1] = _T('\0');

	if(sFontSize > 0)	{	m_measureStyle.sFontSize = sFontSize;	}
}
///////////////////////////////////////
/**
 * 	軸の単位名を設定する.
 * 		単位名を設定する
 * 
 * 	@param color	設定する単位名
 * 	@param format	フォーマット　例）%s [%s]
 *
inline void CAXMeasureStyle::SetUnit( LPCSTR strUnit, LPCSTR format )
{
	m_strUnit = strUnit;
	if(format != NULL)	{	m_strNameFormat = format;	}
	Redraw();
}
///////////////////////////////////////
/**
 * 	目盛り名の単位を取得する.
 * 		目盛り名の単位を取得する
 * 
 * 	@return color	取得する目盛り名の単位
 *
inline LPCTSTR CAXMeasureStyle::GetUnit(void)
{
	return (LPCTSTR)m_strUnit;			///< 目盛り名の単位
}
/////////////////////////////////////////////////////////////////////////////
// CAXMeasureCtrl
///////////////////////////////////////
/**
 * 	CAXMeasureCtrlのコピー.
 *		与えられたCAXMeasureCtrlをコピーする
 *
 * 	@param src	コピー元CAXMeasureCtrl
 * 	@return		このクラスのポインタ
 */
inline CAXMeasureCtrl & CAXMeasureCtrl::operator =( const CAXMeasureCtrl &src )
{
	CAXMeasureStyle::Copy(src);
	CAXGDICtrl::Copy(src);

	m_iFontSize = src.m_iFontSize;			///< 文字列描画サイズ
//	m_strUnit = src.m_strUnit;				///< 目盛り名の単位
//	m_strNameFormat = src.m_strNameFormat;	///< 目盛り名称の書式
	Redraw();
	return *this;
}
///////////////////////////////////////
/**
 * 	CAXMeasureStyleのコピー.
 * 		与えられたスケールスタイルをコピーする
 * 
 * 	@param src	コピー元スケールスタイル
 * 	@return		このクラスのポインタ
 */
inline CAXMeasureCtrl & CAXMeasureCtrl::operator =( const CAXMeasureStyle &src )
{
	CAXMeasureStyle::Copy(src);

	Redraw();
	return *this;
}
///////////////////////////////////////
/**
 * 	CAXGDIScaleDataのコピー.
 * 		与えられたスケール情報をコピーする
 * 
 * 	@param src	コピー元スケール情報
 * 	@return		このクラスのポインタ
 */
inline CAXMeasureCtrl & CAXMeasureCtrl::operator =( const CAXGDIScaleData &src )
{
	CAXGDIScaleData::Copy(src);

	Redraw();
	return *this;
}
///////////////////////////////////////
/**
 * 	軸の文字列のフォントサイズを設定する.
 * 		フォントサイズを設定する
 * 
 * 	@param iSize	フォントサイズ
 * 	@return
 */
inline void CAXMeasureCtrl::SetFontSize( int iSize /*= -1*/ )
{
	m_iFontSize = iSize;
}
///////////////////////////////////////
/**
 * 	軸の文字列のフォントサイズを取得する.
 * 		フォントサイズを取得する.
 * 
 * 	@param
 * 	@return　フォントサイズ
 */
inline int CAXMeasureCtrl::GetFontSize(void) const
{
	return m_iFontSize;
}
/**
 *	画面更新.
 */
inline void CAXMeasureCtrl::Redraw(void)
{
	if( IsWindow( m_hWnd ) ){
		Invalidate();
		UpdateWindow();
	}
}
/////////////////////////////////////////////////////////////////////////////

#endif // __AXMASURECTRL_H_INCLUDED__