// AXGDIPlot.h : ヘッダー ファイル
//
/********************************************************
// クラスのインターフェイス
// CAXPlotStyle		:PLOTスタイルクラス
// CAXGDIPlotCtrl	:AXGDIプロット用描画クラス
//												by YOTSUTSU
//	* History	:	date:2005,15,Jul.	新規作成
ver.1.00	
********************************************************/
//////////////////////////////////////////////////////////////////////

#if !defined(_AXGDIPLOT_H_INCLUDED_)
#define _AXGDIPLOT_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "AXGDIWnd.h"
#include "AXMeasureCtrl.h"
#include <Float.h>

//CursorStyle
#define ACSRS_NONE			0x0000	///< カーソル無	
#define ACSRS_X				0x0001	///< X軸カーソル
#define	ACSRS_Y				0x0002	///< Y軸カーソル	
#define	ACSRS_XYCROSS		0x0003	///< 十字カーソル
#define ACSRS_SHOW          0x0010	///< 表示/非表示フラグ
#define ACSRS_SHACT         0x0020	///< ACTIVEマーク表示/非表示フラグ
#define ACSRS_ALL           0xFFFF
/////////////////////////////////////////////////////////////////////////////
// 構造体
#pragma pack( push, 1 )
	///< カーソル情報
	typedef struct tagAXCursorInfoA{	//40byte
		WORD		wSize;			///< Specifies the size, in bytes, of this structure.	
		WORD		wCusorStyle;	///< Cursor style
		int			iLayer;			///< DataLayer index ( -1:データ指定/それ以外:レイヤー指定)
		int			iPos;			///< カーソル位置 データポイント指定
		int			iReserve1;		///< よび
		XYPOINT		xyValue;		///< カーソル位置 値指定
		CHAR		szName[8];		///< カーソルの名前
	} AXCURSORINFOA;
	///< カーソル情報
	typedef struct tagAXCursorInfoW{	//48byte
		WORD		wSize;			///< Specifies the size, in bytes, of this structure.	
		WORD		wCusorStyle;	///< Cursor style
		int			iLayer;			///< DataLayer index ( -1:データ指定/それ以外:レイヤー指定)
		int			iPos;			///< カーソル位置 データポイント指定
		int			iReserve1;		///< よび
		XYPOINT		xyValue;		///< カーソル位置 値指定
		WCHAR		szName[8];		///< カーソルの名前
	} AXCURSORINFOW;
#pragma pack( pop )


#ifdef UNICODE
typedef tagAXCursorInfoW	tagAXCursorInfo;
typedef AXCURSORINFOW		AXCURSORINFO;
#else
typedef tagAXCursorInfoA	tagAXCursorInfo;
typedef AXCURSORINFOA AXCURSORINFO;
#endif // UNICODE

/////////////////////////////////////////////////////////////////////////////
//CAXGDICursor
class CAXGDICursor //: public tagAXCursorInfo
{
// コンストラクション
public:
	CAXGDICursor( void );
	CAXGDICursor( const AXCURSORINFO & cursorInfo );
	//コピーコンストラクタ
	CAXGDICursor( const CAXGDICursor &org );
// アトリビュート
public:
	//カーソルモードの取得
	inline virtual int GetCursorMode( void ) const ;//	{	return m_iMode;		}
	//カーソルの表示/非表示を取得
	inline virtual BOOL IsShowCursor(void) const		{	return ( (m_cursorInfo.wCusorStyle & ACSRS_SHOW) ? TRUE : FALSE );		}
	//カーソルのACTIVEマーク表示/非表示フラグ
	inline virtual BOOL IsShowActiveMark(void) const	{	return ( (m_cursorInfo.wCusorStyle & ACSRS_SHACT) ? TRUE : FALSE );		}
	//カーソルの値の取得（値指定）
	inline virtual XYPOINT GetValue(void) const			{	return m_cursorInfo.xyValue;	}
	//カーソルのデータレイヤーの取得（データレイヤー指定）
	inline virtual int GetLayer( void ) const			{	return m_cursorInfo.iLayer;}
	//カーソルのデータポジションの取得（データレイヤー指定）
	inline virtual int GetPos( void ) const				{	return m_cursorInfo.iPos;		}
	
	//カーソルの表示/非表示を設定
	inline virtual void ShowCursor(BOOL bShow);
	//カーソルのACTIVEマーク表示/非表示フラグを設定
	inline virtual void ShowActiveMark(BOOL bShow);
	//カーソルの値の設定（値指定）
	inline virtual void SetValue( XYPOINT xyValue);
	inline virtual void SetValue( double dX, double dY );
	//カーソルのデータレイヤーの設定（データレイヤー指定）
	inline virtual void SetLayer( int iLayer, int iPos = -1);
	//カーソルのデータポジションの設定（データレイヤー指定）
	inline virtual void SetPos( int iPos );
	//カーソル名称の取得
	inline virtual CString GetString( void )	{	return (CString(m_cursorInfo.szName));	}
	inline virtual int GetString( LPTSTR lpszStringBuf, int nMaxCount ) const {
		_tcsncpy( lpszStringBuf, m_cursorInfo.szName, nMaxCount );
		lpszStringBuf[nMaxCount - 1] = '\0';
		return ( 1 );//あとで直す。
	}
//	inline virtual void GetString( void )	{	return (CString(m_cursorInfo.szName));	}
	//カーソルモードの設定
	inline virtual int SetCursorMode( int iMode );
	//カーソル名称の設定
	inline virtual void SetString( LPCTSTR lpszName );
// インプリメンテーション
public:
	//デコンストラクタ
	virtual ~CAXGDICursor( void );

protected:
	virtual void Initialize( void );

protected:

	AXCURSORINFO	m_cursorInfo;

	//CAXGDICtrl *m_pAXGdiCtrl;	///< CAXGDICtrlのポインタ
// オペレーション
public:
	CAXGDICursor & operator =( const CAXGDICursor &src );
	inline CAXGDICursor & Copy( const CAXGDICursor &src );

	// カーソル名称の描画
	static void DrawCursorName( CDC *pDC, const CRect &rect, CPoint point, int iCursorMode, LPCTSTR lpszName, COLORREF color );

};
///////////////////////////////////////
/**
 * 	カーソルモードの取得
 * 
 * 	@return CURSORX:'X' X軸カーソル / CURSORY:'Y' Y軸カーソル / CURSORCROSS:'+' 十字カーソル
 */
inline int CAXGDICursor::GetCursorMode( void ) const
{	
	if((m_cursorInfo.wCusorStyle & ACSRS_X) && (m_cursorInfo.wCusorStyle & ACSRS_Y))	{
		return CURSORCROSS;		///< 十字カーソル
	}	else if((m_cursorInfo.wCusorStyle & ACSRS_Y))	{
		return CURSORY;			///< Y軸カーソル
	}	else if((m_cursorInfo.wCusorStyle & ACSRS_X))	{
		return CURSORX;			///< X軸カーソル
	}
	return CURSORNONE;			///< カーソル無	
}
///////////////////////////////////////
/**
 * 	カーソルの表示/非表示を設定
 * 
 * 	@param	bShow	TRUE:表示/FALSE:非表示
 */
inline void CAXGDICursor::ShowCursor(BOOL bShow)
{
	if(bShow)	{	m_cursorInfo.wCusorStyle |= ACSRS_SHOW ;				}
	else		{	m_cursorInfo.wCusorStyle &= (ACSRS_ALL ^ ACSRS_SHOW) ;	}
}
///////////////////////////////////////
/**
 * 	カーソルのACTIVEマーク表示/非表示フラグを設定
 * 
 * 	@param	bShow	TRUE:表示/FALSE:非表示
 */
inline void CAXGDICursor::ShowActiveMark(BOOL bShow)
{
	if(bShow)	{	m_cursorInfo.wCusorStyle |= ACSRS_SHACT ;					}
	else		{	m_cursorInfo.wCusorStyle &= (ACSRS_ALL ^ ACSRS_SHACT) ;		}
}
///////////////////////////////////////
/**
 * 	カーソルモードの設定
 * 
 * 	@param iMode	カーソルモード
 *					CURSORX:'X' X軸カーソル / CURSORY:'Y' Y軸カーソル / CURSORCROSS:'+' 十字カーソル
 *	@return	変更前のカーソルモード
 */
inline int CAXGDICursor::SetCursorMode( int iMode )
{
	int iOld = GetCursorMode();
	/// カーソルモード

	switch(iMode)	{
	case CURSORNONE:	///< カーソル無し
	case CURSORX:		// 'X'	///< X軸カーソル
	case CURSORY:		// 'Y'	///< Y軸カーソル
	case CURSORCROSS:	// '+'	///< 十字カーソル
		m_cursorInfo.wCusorStyle &= (ACSRS_ALL ^ 0x0003) ;//消します。
		break;
	default:
		break;
	}
	switch(iMode)	{
	case CURSORNONE:	///< カーソル無し
		break;
	case CURSORX:		// 'X'	///< X軸カーソル
		m_cursorInfo.wCusorStyle |= ACSRS_X;
		break;
	case CURSORY:		// 'Y'	///< Y軸カーソル
		m_cursorInfo.wCusorStyle |= ACSRS_Y;
		break;
	case CURSORCROSS:	// '+'	///< 十字カーソル
		m_cursorInfo.wCusorStyle |= ACSRS_XYCROSS;
		break;
	}

	return iOld;
}
///////////////////////////////////////
/**
 * 	カーソルの名称の設定
 * 
 * 	@param lpszName	カーソルの名称
 *	@return
 */
inline void CAXGDICursor::SetString( LPCTSTR lpszName )
{
	_tcsncpy( m_cursorInfo.szName, lpszName, sizeof(m_cursorInfo.szName) );
	m_cursorInfo.szName[sizeof(m_cursorInfo.szName)-1] = _T('\0');
}
///////////////////////////////////////
/**
 * 	カーソルの値の設定（値指定）
 * 
 * 	@param	xyValue	カーソルの値
 */
inline void CAXGDICursor::SetValue( XYPOINT xyValue )
{
	SetValue( xyValue.dX, xyValue.dY );
}
///////////////////////////////////////
/**
 * 	カーソルの値の設定（値指定）
 * 
 * 	@param	dX		カーソルのXの値
 * 	@param	dY		カーソルのYの値
 */
inline void CAXGDICursor::SetValue( double dX, double dY )
{
	m_cursorInfo.iLayer = -1;		///< DataLayer index
	m_cursorInfo.xyValue.dX = dX;		///< 値指定
	m_cursorInfo.xyValue.dY = dY;		///< 値指定
}
///////////////////////////////////////
/**
 * 	カーソルのデータレイヤーの設定（データレイヤー指定）
 * 
 * 	@param	iLayer		データレイヤーの値
 * 	@param	iPos		カーソルのポジション
 */
inline void CAXGDICursor::SetLayer( int iLayer, int iPos /*= -1*/)
{
	if(iLayer >= 0)	{
		m_cursorInfo.iLayer = iLayer;
		if(iPos >= 0)	{	m_cursorInfo.iPos = iPos;	}
//		Redraw();
	}
}
///////////////////////////////////////
/**
 * 	カーソルのデータポジションの設定（データレイヤー指定）
 * 
 * 	@param	iPos		カーソルのポジション
 */
inline void CAXGDICursor::SetPos( int iPos )
{
	if(iPos >= 0)	{	
		m_cursorInfo.iPos = iPos;
//		Redraw();
	}
}
///////////////////////////////////////
/**
 * 	コピーオペレータ
 * 
 * 	@param org	コピー元CAXGDICursor
 */
inline CAXGDICursor & CAXGDICursor::Copy( const CAXGDICursor &src )
{	
	operator =(src);
	return (*this);
}
/////////////////////////////////////////////////////////////////////////////
//CAXPlotCursor
class CAXPlotCursor : public CAXGDICursor, virtual public CAXLineStyle, virtual public CAXMarkerStyle
{
// コンストラクション
public:
	/**
	 * 	構築.
	 * 		カーソルスタイルを保持する
	 *
	 * 	@param iMode	カーソルモード	
	 *					CURSORX:'X' X軸カーソル / CURSORY:'Y' Y軸カーソル / CURSORCROSS:'+' 十字カーソル
	 * 	@param iStyle		線種
	 * 	@param color		線色
	 * 	@param iSize		線サイズ
	 */
	CAXPlotCursor( int iMode = CURSORCROSS, int iStyle = PS_SOLID, COLORREF color = 0x00FFFFFF, int iSize = 0)
		: CAXLineStyle( iStyle, color, iSize ), CAXMarkerStyle()
	{
		Initialize();
		SetCursorMode( iMode );
	}
	/**
	 * 	構築.
	 * 		ラインスタイルを元に構築する
	 * 
	 * 	@param iMode	カーソルモード
	 *					CURSORX:'X' X軸カーソル / CURSORY:'Y' Y軸カーソル / CURSORCROSS:'+' 十字カーソル
	 * 	@param lineStyle	ラインスタイル
	 */
	CAXPlotCursor( int iMode, const LINESTYLE &lineStyle)
		: CAXLineStyle( lineStyle ), CAXMarkerStyle()
	{
		Initialize();
		SetCursorMode( iMode );
	}
	/**
	 * 	構築.
	 * 		ラインスタイルを元に構築する
	 * 
	 * 	@param iMode	カーソルモード
	 *					CURSORX:'X' X軸カーソル / CURSORY:'Y' Y軸カーソル / CURSORCROSS:'+' 十字カーソル
	 * 	@param axlineStyle	ラインスタイル
	 */
	CAXPlotCursor( int iMode, const CAXLineStyle &axlineStyle )
		: CAXLineStyle( axlineStyle ), CAXMarkerStyle()
	{
		Initialize();
		SetCursorMode( iMode );
	}
	/**
	 * 	構築.
	 * 		ラインスタイル、マーカースタイルを元に構築する
	 * 
	 * 	@param iMode	カーソルモード
	 *					CURSORX:'X' X軸カーソル / CURSORY:'Y' Y軸カーソル / CURSORCROSS:'+' 十字カーソル
	 * 	@param lineStyle	ラインスタイル
	 * 	@param markStyle	マーカースタイル
	 */
	CAXPlotCursor( int iMode, const CAXLineStyle &lineStyle, const MARKERSTYLE &markStyle )
		: CAXLineStyle( lineStyle ), CAXMarkerStyle( markStyle )
	{
		Initialize();
		SetCursorMode( iMode );
	}
	/**
	 * 	構築.
	 * 		ラインスタイル、マーカースタイルを元に構築する
	 * 
	 * 	@param iMode	カーソルモード
	 *					CURSORX:'X' X軸カーソル / CURSORY:'Y' Y軸カーソル / CURSORCROSS:'+' 十字カーソル
	 * 	@param axlineStyle	ラインスタイル
	 * 	@param axmarkStyle	マーカースタイル
	 */
	CAXPlotCursor( int iMode, const CAXLineStyle &axlineStyle, const CAXMarkerStyle &axmarkStyle )
		: CAXLineStyle( axlineStyle ), CAXMarkerStyle( axmarkStyle )
	{
		Initialize();
		SetCursorMode( iMode );
	}
	/**
	 * 	コピーコンストラクタ
	 * 		元のCAXPlotCursorを元に構築する
	 * 
	 * 	@param org	コピー元CAXPlotCursor
	 */
	CAXPlotCursor( const CAXPlotCursor &org )	{	operator=( org );	}
// アトリビュート
public:

	
// インプリメンテーション
public:
	//デコンストラクタ
	virtual ~CAXPlotCursor() {};

protected:
	inline virtual void Initialize(void);
protected:
// オペレーション
public:
	inline CAXPlotCursor & operator =( const CAXPlotCursor &src );
	inline CAXPlotCursor & Copy( const CAXPlotCursor &src );

	// カーソル描画
	virtual void DrawCursor( CDC *pDC, const CRect &rect, CPoint point, BOOL bMonochrome );
	// カーソルActiveMark描画
	virtual void DrawActiveMark( CDC *pDC, const CRect &rect, CPoint pos, int iCursorMode, int iSize );
};
///////////////////////////////////////
/**
 * 	初期化関数
 * 
 * 	@param
 */
inline void CAXPlotCursor::Initialize(void)
{
	CAXGDICursor::Initialize();
}
///////////////////////////////////////
/**
 * 	コピーオペレータ
 * 
 * 	@param src	コピー元CAXPlotCursor
 */
inline CAXPlotCursor & CAXPlotCursor::operator =( const CAXPlotCursor &src )
{
	CAXGDICursor::Copy(src);
	CAXLineStyle::Copy(src);
	CAXLineStyle::Copy(src);

	return (*this);
}
///////////////////////////////////////
/**
 * 	コピーオペレータ
 * 
 * 	@param src	コピー元CAXPlotCursor
 *	@return　
 */
inline CAXPlotCursor & CAXPlotCursor::Copy( const CAXPlotCursor &src )
{
	operator =(src); 
	return (*this);
}
/////////////////////////////////////////////////////////////////////////////
// CAXAreaCursor
class CAXAreaCursor : public CAXGDICursor, virtual public CAXPatternStyle
{
	// コンストラクション
public:
	/**
	 *	構築.
	 * 	パターンスタイルを元に構築する.
	 * 
	 * 	@param	int iBStyle		Brush Styles BS_SOLID
	 * 	@param	int iHStyle		Hatch Styles HS_HORIZONTAL
	 * 	@param	COLORREF color	描画色
	 */
	CAXAreaCursor( int iMode = CURSORCROSS, int iBStyle = BS_SOLID, int iHStyle = HS_HORIZONTAL, COLORREF color = IPINK )
		: CAXPatternStyle( iBStyle , iHStyle , color )
	{
		Initialize();
		SetCursorMode( iMode );
	}
	/**
	 * 	構築.
	 * 		パターンスタイルを元に構築する
	 * 
	 * 	@param patternStyle	パターンスタイル
	 */
	CAXAreaCursor( int iMode, const PATTERNSTYLE &patternStyle )
		: CAXPatternStyle( patternStyle )
	{
		Initialize();
		SetCursorMode( iMode );
	}
	/**
	 * 	構築.
	 * 		パターンスタイルを元に構築する
	 * 
	 * 	@param patternStyle	パターンスタイル
	 */
	CAXAreaCursor( int iMode, const CAXPatternStyle &patternStyle )
		: CAXPatternStyle( patternStyle )
	{
		Initialize();
		SetCursorMode( iMode );
	}
	/**
	 * 	コピーコンストラクタ
	 * 		元のCAXAreaCursorを元に構築する
	 * 
	 * 	@param org	コピー元CCAXAreaCursor
	 */
	CAXAreaCursor( const CAXAreaCursor &org )	{	operator=( org );	}
// アトリビュート
public:
	//エリアカーソルの値の取得（値指定）
	inline virtual XYPOINT GetHeadValue(void)	{	return GetValue();	}
	//エリアカーソルのデータポジションの取得（データレイヤー指定）
	inline virtual int GetHeadPos( void )		{	return m_cursorInfo.iPos;		}
	//エリアカーソルの値の取得（値指定）
	inline virtual XYPOINT GetTailValue(void)	{	return m_xyTailValue;	}
	//エリアカーソルのデータポジションの取得（データレイヤー指定）
	inline virtual int GetTailPos( void )		{	return m_iTailPos;		}

	//エリアカーソルの値の設定（値指定）
	inline virtual void SetAreaValue( XYPOINT xyHeadValue, XYPOINT xyTailValue );
	inline virtual void SetHeadValue( double dHeadX, double dHeadY );
	inline virtual void SetTailValue( double dTailX, double dTailY );
	//エリアカーソルのデータレイヤーの設定（データレイヤー指定）
	inline virtual void SetLayer( int iLayer, int iHeadPos = -1, int iTailPos = -1 );
	//エリアカーソルのデータポジションの設定（データレイヤーポジション指定）
	inline virtual void SetPos( int iHeadPos, int iTailPos );
	
	//エリアカーソル位置をオフセットする。（値指定）
	inline virtual void OffsetValue( XYPOINT xyDelta );
	inline virtual void OffsetValue( double dDeltaX, double dDeltaY );
	//エリアカーソル位置をオフセットする。（ポジション指定）
	inline virtual void OffsetPos( int iDeltaPos );


// インプリメンテーション
public:
	//デコンストラクタ
	virtual ~CAXAreaCursor() {};

protected:
	inline virtual void Initialize( void );
protected:

	int			m_iTailPos;			///< カーソル位置 データポイント指定
	XYPOINT		m_xyTailValue;		///< カーソル位置 値指定
// オペレーション
public:
	inline CAXAreaCursor & operator =( const CAXAreaCursor &src );
	inline CAXAreaCursor & Copy( const CAXAreaCursor &src );

	// エリアカーソル名称の描画
	virtual void DrawAreaCursorName( CDC *pDC, const CRect &rect, BOOL bMonochrome );
	// エリアカーソルのパターン描画
	virtual void DrawPattern( CDC *pDC, const CRect &rect, BOOL bMonochrome );
};
///////////////////////////////////////
/**
 * 	初期化関数
 * 
 * 	@param
 */
void CAXAreaCursor::Initialize( void )
{
	m_iTailPos = -1;			///< カーソル位置 データポイント指定
	m_xyTailValue.dX = 0.0;		///< カーソル位置 値指定
	m_xyTailValue.dY = 0.0;		///< カーソル位置 値指定
	CAXGDICursor::Initialize();
}
///////////////////////////////////////
/**
 * 	カーソルの値の設定（値指定）
 * 
 * 	@param	xyHeadValue	カーソルの先頭の値
 * 	@param	xyTailValue	カーソルの最後の値
 */
inline void CAXAreaCursor::SetAreaValue( XYPOINT xyHeadValue, XYPOINT xyTailValue )
{
	SetHeadValue( xyHeadValue.dX, xyHeadValue.dY );
	SetTailValue( xyTailValue.dX, xyTailValue.dY );
}
///////////////////////////////////////
/**
 * 	カーソルの先頭の値の設定（値指定）
 * 
 * 	@param	dHeadX		カーソルの先頭のX値
 * 	@param	dHeadY		カーソルの先頭のY値
 */
inline void CAXAreaCursor::SetHeadValue( double dHeadX, double dHeadY )
{
	SetValue( dHeadX, dHeadY );
}
///////////////////////////////////////
/**
 * 	カーソルの最後の値の設定（値指定）
 * 
 * 	@param	dTailX		カーソルの最後のX値
 * 	@param	dTailY		カーソルの最後のY値
 */
inline void CAXAreaCursor::SetTailValue( double dTailX, double dTailY )
{
	m_cursorInfo.iLayer = -1;		///< DataLayer index
	m_xyTailValue.dX = dTailX;		///< 値指定
	m_xyTailValue.dY = dTailY;		///< 値指定
}
///////////////////////////////////////
/**
 * 	カーソルのデータレイヤーの設定（データレイヤー指定）
 * 
 * 	@param	iLayer		データレイヤーの値
 * 	@param	iPos		カーソルの先頭ポジション
 * 	@param	iPos		カーソルの最後ポジション
 */
inline void CAXAreaCursor::SetLayer( int iLayer, int iHeadPos /*= -1*/, int iTailPos /*= -1*/ )
{
	if(iLayer >= 0)	{
		m_cursorInfo.iLayer = iLayer;
		SetPos( iHeadPos, iTailPos );
//		Redraw();
	}
}
///////////////////////////////////////
/**
 * 	カーソルのデータポジションの設定（データレイヤー指定）
 * 
 * 	@param	iHeadPos		カーソルの先頭ポジション
 * 	@param	iTailPos		カーソルの最後ポジション
 */
inline void CAXAreaCursor::SetPos( int iHeadPos, int iTailPos )
{
	if(iHeadPos >= 0)	{	m_cursorInfo.iPos = iHeadPos;	}
	if(iTailPos >= 0)	{	m_iTailPos = iTailPos;	}
}
///////////////////////////////////////
/**
 * 	エリアカーソル位置をオフセットする。（値指定）
 * 
 * 	@param xyDelta		オフセットするXY値
 *
 */
inline void CAXAreaCursor::OffsetValue( XYPOINT xyDelta )
{
	OffsetValue( xyDelta.dX, xyDelta.dY );
}
///////////////////////////////////////
/**
 * 	エリアカーソル位置をオフセットする。（値指定）
 * 
 * 	@param dDeltaX		オフセットするX値
 *	@param dDeltaY		オフセットするY値
 */
inline void CAXAreaCursor::OffsetValue( double dDeltaX, double dDeltaY )
{
	SetHeadValue( GetHeadValue().dX + dDeltaX, GetHeadValue().dY + dDeltaY );
	SetTailValue( GetTailValue().dX + dDeltaX, GetTailValue().dY + dDeltaY );
}
///////////////////////////////////////
/**
 * 	エリアカーソル位置をオフセットする。（ポジション指定）
 * 
 * 	@param iDeltaPos	オフセットするポジション
 */
inline void CAXAreaCursor::OffsetPos( int iDeltaPos )
{
	SetPos( GetHeadPos() + iDeltaPos, GetTailPos() + iDeltaPos );
}
///////////////////////////////////////
/**
 * 	コピーオペレータ
 * 
 * 	@param src	コピー元CAXAreaCursor
 */
inline CAXAreaCursor & CAXAreaCursor::operator =( const CAXAreaCursor &src )
{
	CAXGDICursor::Copy(src);
	CAXPatternStyle::Copy(src);
	m_iTailPos = src.m_iTailPos;			///< カーソル位置 データポイント指定
	m_xyTailValue = src.m_xyTailValue;		///< カーソル位置 値指定

	return (*this);
}
///////////////////////////////////////
/**
 * 	コピーオペレータ
 * 
 * 	@param src	コピー元CAXAreaCursor
 */
inline CAXAreaCursor & CAXAreaCursor::Copy( const CAXAreaCursor &src )
{
	operator =(src); 
	return (*this);
}
/////////////////////////////////////////////////////////////////////////////
// CAXPlotData
///< memory type 0:ノーマル（MEMNORMAL）/1:リングメモリ（MEMRING）
typedef enum E_MEMORY_TYPE{
	MEMNORMAL = 0,	///< ノーマル（MEMNORMAL）
	MEMRING,		///< リングメモリ（MEMRING）
};

template<class TYPE, class ARG_TYPE>
class CAXPlotData : public CAXLineStyle, public CAXMarkerStyle//, public CAXItemName 
{
// コンストラクション
public:
	/**
	 * 	構築.
	 * 		プロットスタイルを保持する
	 * 
	 * 	@param iStyle		線種
	 * 	@param color		線色
	 * 	@param iSize		線サイズ
	 */
	CAXPlotData(int iStyle = PS_SOLID, COLORREF color = 0x00FFFFFF, int iSize = 0)
		: CAXLineStyle( iStyle, color, iSize ), CAXMarkerStyle()
	{
		Initialize();
	}
	/**
	 * 	構築.
	 * 		ラインスタイルを元に構築する
	 * 
	 * 	@param lineStyle	ラインスタイル
	 */
	CAXPlotData( const LINESTYLE &lineStyle)
		: CAXLineStyle( lineStyle ), CAXMarkerStyle()
	{
		Initialize();
	}
	/**
	 * 	構築.
	 * 		ラインスタイルを元に構築する
	 * 
	 * 	@param axlineStyle	ラインスタイル
	 */
	CAXPlotData( const CAXLineStyle &axlineStyle )
		: CAXLineStyle( axlineStyle ), CAXMarkerStyle()
	{
		Initialize();
	}
	/**
	 * 	構築.
	 * 		ラインスタイル、マーカースタイルを元に構築する
	 * 
	 * 	@param lineStyle	ラインスタイル
	 * 	@param markStyle	マーカースタイル
	 */
	CAXPlotData( const LINESTYLE &lineStyle, const MARKERSTYLE &markStyle )
		: CAXLineStyle( lineStyle ), CAXMarkerStyle( markStyle )
	{
		Initialize();
	}
	/**
	 * 	構築.
	 * 		ラインスタイル、マーカースタイルを元に構築する
	 * 
	 * 	@param axlineStyle	ラインスタイル
	 * 	@param axmarkStyle	マーカースタイル
	 */
	CAXPlotData( const CAXLineStyle &axlineStyle, const CAXMarkerStyle &axmarkStyle )
		: CAXLineStyle( axlineStyle ), CAXMarkerStyle( axmarkStyle )
	{
		Initialize();
	}
	/**
	 * 	コピーコンストラクタ
	 * 		元のCAXPlotDataを元に構築する
	 * 
	 * 	@param org	コピー元CAXPlotData
	 */
	CAXPlotData( const CAXPlotData &org )	{	operator=( org );	}
// インプリメンテーション
public:
	//デコンストラクタ
	virtual ~CAXPlotData() {	RemoveAllItem();	};
	///////////////////////////////////////
	/**
	 * 	プロットデータのコピー.
	 * 	@param src	コピー元のプロットスタイル
	 * 	@return		プロットスタイルのポインタ
	 */
	inline CAXPlotData & operator =( const CAXPlotData &src )
	{
//		CAXItemName::Copy(src);
		m_strItemName = src.m_strItemName;	///< データ名称

		m_lineStyle = src.m_lineStyle;		///< ラインスタイル
		m_markStyle = src.m_markStyle;		///< マーカースタイル
		m_iMarkDelta = src.m_iMarkDelta;	///< マーク間隔(インデックス指定)
		m_iMarkEdge = src.m_iMarkEdge;		///< マーク始点終点(インデックス指定)
		m_bVisible = src.m_bVisible;		///< 表示フラグ

		m_byReversalX = src.m_byReversalX;	///< Xデータ反転
		m_byReversalY = src.m_byReversalY;	///< Yデータ反転
		
		m_nIndex = -1;						///< データインデックス
		SetSize( src.m_nSize );	//m_nSize;	///< データサイズ

		m_plotData.Copy( src.m_plotData );
		m_nIndex = src.m_nIndex;			///< データインデックス
		m_nHead = src.m_nHead;				///< データの先頭

		m_Xscale = src.m_Xscale;			//X軸スケール
		m_Yscale = src.m_Yscale;			//Y軸スケール

		m_dataMin = src.m_dataMin;			///< データ最小値
		m_dataMax = src.m_dataMax;			///< データ最大値
		///< memory type 0:ノーマル（MEMNORMAL）/1:リングメモリ（MEMRING）
		m_nMemType = src.m_nMemType;
		m_bRedraw = TRUE;

		return *this;
	}
	inline CAXPlotData & Copy( const CAXPlotData &src )
	{
		operator=(src);
		return *this;
	}
	///////////////////////////////////////
	/**
	 * 	アイテム全削除.
	 * 
	 *	
	 */
	virtual void RemoveAllItem( void )
	{	
//		CAXItemName::ClearName();
		m_strItemName.Empty();	///< データ名称
		RemoveAllPoint();//データの削除
	}
//メンバ変数
public:
	BOOL			m_bRedraw;		///< 再描画フラグ
protected:
	BOOL			m_bVisible;		///< 表示フラグ
	BYTE			m_byReversalX;	///< Xデータ反転
	BYTE			m_byReversalY;	///< Yデータ反転
	int				m_iMarkDelta;	///< マーク間隔(インデックス指定)
	int				m_iMarkEdge;	///< マーク始点終点(インデックス指定)
	
	int				m_nMemType;		///< memory type 0:ノーマル（MEMNORMAL）/1:リングメモリ（MEMRING）
	int				m_nSize;		///< データサイズ
	int				m_nIndex;		///< データインデックス
	int				m_nHead;		///< データの先頭

	CAXGDIScaleData	m_Xscale;		///< Xaxis
	CAXGDIScaleData	m_Yscale;		///< Yaxis

	ARG_TYPE			m_dataMin;		///< データ最小値
	ARG_TYPE			m_dataMax;		///< データ最大値
	CString				m_strItemName;	///< データ名称

	/// プロットデータ
	CArray<TYPE,ARG_TYPE>	m_plotData;
private:
	
protected:
	inline virtual void CompareMinMax( ARG_TYPE checkData ) {}
	virtual void Initialize( void )
	{
		RemoveAllItem();		///< アイテム全削除
		m_bRedraw = TRUE;		///< 再描画フラグ
		m_bVisible = TRUE;		///< 表示フラグ
		m_byReversalX = 0;		///< Xデータ反転
		m_byReversalY = 0;		///< Yデータ反転
		m_iMarkDelta = 1;		///< マーク間隔(インデックス指定)
		m_iMarkEdge = 0;		///< マーク始点終点(インデックス指定)
		m_nSize = -1;			///< データサイズ
		m_nMemType = MEMNORMAL;	///< memory type 0:ノーマル（MEMNORMAL）/1:リングメモリ（MEMRING）
	}
public:
	inline virtual void ClearMinMax( void ) {}
	///////////////////////////////////////
	/**
	 * 	プロットデータの表示/非表示を設定する.
	 * 
	 * 	@param bVisible	プロットデータを表示するかのフラグ(TRUE:表示 FALSE:非表示)
	 * 	@return			以前の表示/非表示状態を返す。
	 */
	inline BOOL Visible( BOOL bVisible )
	{
		m_bRedraw = TRUE;
		BOOL bOld = m_bVisible;
		m_bVisible = bVisible;
		return bOld;
	}
	///////////////////////////////////////
	/**
	 * 	プロットデータの表示/非表示を取得する.
	 * 
	 * 	@return			表示/非表示状態を返す。
	 */
	inline BOOL IsVisible(void)	{	return m_bVisible;	}

	/// 表示文字列の設定
	inline virtual void SetName(LPCTSTR lpszName)	{	m_strItemName = lpszName;		}
	///< 表示文字列
	inline virtual CString GetName(void)			{	return m_strItemName;	}
	
//マーカー表示間隔を設定する.
	///////////////////////////////////////
	/**
	 * 	マーカー表示間隔を設定する.
	 * 
	 * 	@param iMarkDelta	マーク表示間隔
	 * 	@param iMarkEdge	データの端からのマーク非表示範囲
	 * 
	 */
	void SetMarkerDelta( int iMarkDelta, int iMarkEdge )
	{
		if( iMarkDelta <  0 ) {	return;	}
		m_iMarkDelta = iMarkDelta;
		m_iMarkEdge = iMarkEdge;
		m_bRedraw = TRUE;
	}
	inline int	GetMarkerDelta( void )	{	return m_iMarkDelta;	}
	inline int	GetMarkerEdge( void )	{	return m_iMarkEdge;		}

	//反転表示
	///////////////////////////////////////
	/**
	 * 	プロットデータの反転表示を設定する.
	 * 
	 * 	@param iRvsX	プロットデータX軸を反転表示するかのフラグ(1:反転 / 0:非反転 / それ以外:変更しない)
	 * 	@param iRvsY	プロットデータY軸を反転表示するかのフラグ(1:反転 / 0:非反転 / それ以外:変更しない)
	 * 	@return
	 */
	inline virtual void EnableReversal( int iRvsX, int iRvsY )
	{
		if(iRvsX == 0)			{	m_byReversalX = 0;	}
		else	if(iRvsX == 1)	{	m_byReversalX = 1;	}
		if(iRvsY == 0)			{	m_byReversalY = 0;	}
		else	if(iRvsY == 1)	{	m_byReversalY = 1;	}
	}
	inline BOOL IsReversalX(void)		{	return (m_byReversalX == 1 ? TRUE : FALSE);	}
	inline BOOL IsReversalY(void)		{	return (m_byReversalY == 1 ? TRUE : FALSE);	}
	
	//データメモリタイプ
	inline	int GetMemType( void )	{	return m_nMemType;	}
	inline	BOOL SetMemType( int type = MEMRING )
	{	
		if(m_nSize > 0)	{	return FALSE;	}
		m_nMemType = type;
		return TRUE;
	}

//データアクセス
	///////////////////////////////////////
	/**
	 * 	データサイズを設定する.
	 * 		設定したデータサイズの領域を確保する。
	 *	
	 *	@param		nSize	設定するデータサイズ
	 * 	@return		領域を確保したデータサイズ
	 */
	virtual int SetSize( int nSize )
	{
		m_nIndex = -1;		///< データインデックス
		m_nHead = -1;		///< データの先頭

		if( nSize > 0)	{
			if(m_nSize != nSize)	{
				m_plotData.RemoveAll();
				m_plotData.SetSize( nSize );
				m_nSize = m_plotData.GetSize();		///< データサイズ
				if(m_nSize != nSize)	{	ASSERT(FALSE);	}
			}
		}	else	{
			m_plotData.RemoveAll();
			m_nSize = m_plotData.GetSize();
		}
		
		return m_nSize;
	}
	inline virtual int GetSize( void ) const	{	return m_plotData.GetSize();	}
	///////////////////////////////////////
	/**
	 * 	データ取得.
	 * 	@param nIndex	先頭からのインデックス番号
	 * 	@return			データのポインタ
	 */
	inline virtual TYPE & operator [] ( int nIndex )
	{
		if( nIndex < 0 || nIndex >= GetSize())	{	ASSERT(FALSE);	}
		
		int index = nIndex;
		///< memory type 0:ノーマル（MEMNORMAL）/1:リングメモリ（MEMRING）
		if(m_nMemType == MEMRING)	{
			if(m_nHead < 0)	{	return m_plotData[ index ];	}
			index = m_nHead + nIndex;
			if( index >= GetSize())	{	index -= (GetSize());	}
		}	
		
		return m_plotData[ index ];
	}
	///////////////////////////////////////
	/**
	 * 	データ数取得.
	 * 		設定されているデータポイントの数を取得する。
	 * 
	 * 	@return		設定されているデータポイント数
	 */
	inline virtual int GetNum( void )
	{
		///< memory type 0:ノーマル（MEMNORMAL）/1:リングメモリ（MEMRING）
		if(m_nMemType == MEMRING)	{
			if( m_nHead < 0)	{	return	(m_nIndex + 1);	}
		}	else	{
			if( m_nSize > 0 )	{	return	(m_nIndex + 1);	}
		}
		return m_plotData.GetUpperBound()+1;
	}
	///////////////////////////////////////
	/**
	 * 	データのクリア.
	 * 
	 */
	virtual void ClearAllPoint( void )
	{
		m_nIndex = -1;			///< データインデックス
		m_nHead = -1;			///< データの先
		///< memory type 0:ノーマル（MEMNORMAL）/1:リングメモリ（MEMRING）
		if(m_nMemType != MEMRING)	{
			if( m_nSize <= 0)	{	///< データサイズ
				m_plotData.RemoveAll();
			}
		}
		m_bRedraw = TRUE;
	}
	///////////////////////////////////////
	/**
	 * 	データの領域削除.
	 * 
	 */
	virtual void RemoveAllPoint( void )
	{
		m_nIndex = -1;		///< データインデックス
		m_nHead = -1;		///< データの先頭
		m_nSize = -1;		///< データサイズ
		m_plotData.RemoveAll();
		m_bRedraw = TRUE;
	}
	///////////////////////////////////////
	/**
	 * 	データの追加.
	 * 
	 * 	@param newData	追加するデータ
	 *	@return データを追加したインデックスを返す。
	 */
	inline virtual int AddPoint( ARG_TYPE newData )
	{
		CompareMinMax(newData);
		///< memory type 0:ノーマル（MEMNORMAL）/1:リングメモリ（MEMRING）
		m_bRedraw = TRUE;
		if(m_nMemType == MEMRING)	{
			if(++m_nIndex >= GetSize())	{
				m_nIndex = 0;
				m_nHead = 0;
			}
			m_plotData.SetAt( m_nIndex, newData );
			//m_bRedraw = TRUE;
			if(m_nHead < 0)				{	return m_nIndex;	}
			if(++m_nHead >= GetSize())	{	m_nHead = 0;		}
		}	else	{
			if( ++m_nIndex >= m_nSize)	{
				return m_plotData.Add( newData );
			}	else	{		
				m_plotData.SetAt( m_nIndex, newData );
			}
		}
		return m_nIndex;
	}
	///////////////////////////////////////
	/**
	 * 	データリストの参照.
	 * 		データリストクラスの参照を返す。
	 * 
	 * 	@return		データリストを格納してあるCArrayクラスのポインタ
	 */
	inline virtual CArray<TYPE,ARG_TYPE> *operator *()
	{
		return &m_plotData;
	}

	// データ情報
	inline const TYPE &GetMin(void)	{	return m_dataMin;	}	///< データ最小値
	inline const TYPE &GetMax(void)	{	return m_dataMax;	}	///< データ最大値

	// データ表示範囲
	inline CAXGDIScaleData & GetXscale(void)	{	return m_Xscale;	}	//Xaxis
	inline CAXGDIScaleData & GetYscale(void)	{	return m_Yscale;	}	//Yaxis
	///////////////////////////////////////
	/**
	 * 	データの表示範囲設定.
	 * 		データの表示範囲を設定する。\n
	 * 
	 * 	@param dMin	データ表示範囲(MIN)
	 * 	@param dMax	データ表示範囲(MAX)
	 */
	inline void  SetXScale( double dMin, double dMax)
	{
		m_Xscale.SetScale( dMin, dMax);
		m_bRedraw = TRUE;
	}
	inline void  SetYScale( double dMin, double dMax)
	{
		m_Yscale.SetScale( dMin, dMax);
		m_bRedraw = TRUE;
	}
	// スクロール
	inline void  Scroll( double dScrollX, double dScrollY )
	{
		if( dScrollX != 0.0 ) m_Xscale.SetOffset( dScrollX );
		if( dScrollY != 0.0 ) m_Yscale.SetOffset( dScrollY );
		m_bRedraw = TRUE;
	}
// オーバーライド
public:
	///< 再描画
	virtual void Redraw(BOOL bErase = TRUE)	{ m_bRedraw = TRUE; }
//デバッグ用
	inline virtual void DebugDataSet( void ) {};


//061120 tachibana modified start>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	void UpdateStyle(const LINESTYLE &lineStyle, const MARKERSTYLE &markStyle);
//061120 tachibana modified end<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
};
/////////////////////////////////////////////////////////////////////////////
// inline finction
/////////////////////////////////////////////////////////////////////////////
// CAXPlotData

/////////////////////////////////////////////////////////////////////////////
// CXYPlotData
class CXYPlotData : public CAXPlotData<XYPOINT,XYPOINT>
{
public:
	/**
	 * 	構築.
	 * 		プロットデータを保持する
	 * 
	 * 	@param iStyle		線種
	 * 	@param color		線色
	 * 	@param iSize		線サイズ
	 */
	CXYPlotData( int iStyle = PS_SOLID, COLORREF color = 0x00FFFFFF, int iSize = 0 )
		: CAXPlotData<XYPOINT,XYPOINT>( iStyle, color, iSize )
	{
		ClearMinMax();
	}
	/**
	 * 	構築.
	 * 		ラインスタイルを元に構築する
	 * 
	 * 	@param lineStyle	ラインスタイル
	 */
	CXYPlotData( const LINESTYLE &lineStyle )
		: CAXPlotData<XYPOINT,XYPOINT>( lineStyle )
	{
		ClearMinMax();
	}
	/**
	 * 	構築.
	 * 		ラインスタイルを元に構築する
	 * 
	 * 	@param lineStyle	ラインスタイル
	 */
	CXYPlotData( const CAXLineStyle &axlineStyle )
		: CAXPlotData<XYPOINT,XYPOINT>( axlineStyle )
	{
		ClearMinMax();
	}	
	/**
	 * 	構築.
	 * 		ラインスタイル、マーカースタイルを元に構築する
	 * 
	 * 	@param lineStyle	ラインスタイル
	 * 	@param markStyle	マーカースタイル
	 */
	CXYPlotData( const LINESTYLE &lineStyle, const MARKERSTYLE &markStyle )
		: CAXPlotData<XYPOINT,XYPOINT>( lineStyle, markStyle )
	{
		ClearMinMax();
	}
	/**
	 * 	構築.
	 * 		ラインスタイル、マーカースタイルを元に構築する
	 * 
	 * 	@param lineStyle	ラインスタイル
	 * 	@param markStyle	マーカースタイル
	 */
	CXYPlotData( const CAXLineStyle &axlineStyle, const CAXMarkerStyle &axmarkStyle )
		: CAXPlotData<XYPOINT,XYPOINT>( axlineStyle, axmarkStyle )
	{
		ClearMinMax();
	}
	/**
	 * 	構築.
	 * 		元のCXYPlotDataを元に構築する
	 * 
	 * 	@param org	コピー元CXYPlotData
	 */
	CXYPlotData( const CXYPlotData &org )
	{
		operator=( org );
	}

	/**
	 * 	破棄.
	 * 		プロットデータを破棄する。
	 */
	virtual ~CXYPlotData()
	{
		RemoveAllItem();
	}
private:

//オーバーライド
protected:
	void Initialize( void )
	{
		CAXPlotData<XYPOINT,XYPOINT>::Initialize();
	}
public:
	inline virtual void CompareMinMax( XYPOINT checkData )
	{
		// 最大値/最小値更新
		m_dataMin.dX = __min(m_dataMin.dX,checkData.dX);		///< データ最小値
		m_dataMin.dY = __min(m_dataMin.dY,checkData.dY);		///< データ最小値
		m_dataMax.dX = __max(m_dataMax.dX,checkData.dX);		///< データ最大値
		m_dataMax.dY = __max(m_dataMax.dY,checkData.dY);		///< データ最大値
	}
public:
	virtual void ClearMinMax( void )
	{
		m_dataMin.dX = DBL_MAX;		///< データ最小値
		m_dataMin.dY = DBL_MAX;		///< データ最小値
		m_dataMax.dX = -DBL_MAX;	///< データ最大値
		m_dataMax.dY = -DBL_MAX;	///< データ最大値
	}
	///////////////////////////////////////
	/**
	 * 	データ追加.
	 * 		データのポイントを追加する。
	 * 
	 * 	@param dX	データポイントX
	 * 	@param dY	データポイントY
	 * 	@return		追加した要素のインデックス
	 */
	inline int AddPoint( double dX, double dY )
	{
		XYPOINT pnt;
		pnt.dX = dX;
		pnt.dY = dY;
		return (CAXPlotData<XYPOINT,XYPOINT>::AddPoint(pnt));
	}
	virtual void ClearAllPoint( void )
	{
		ClearMinMax();
		CAXPlotData<XYPOINT,XYPOINT>::ClearAllPoint();
	}
	virtual void RemoveAllPoint( void )
	{
		ClearMinMax();
		CAXPlotData<XYPOINT,XYPOINT>::RemoveAllPoint();
	}
	virtual void RemoveAllItem( void )
	{
		ClearMinMax();
		CAXPlotData<XYPOINT,XYPOINT>::RemoveAllItem();
	}
	inline double dataX( int index )
	{
		return (CAXPlotData<XYPOINT,XYPOINT>::operator[](index)).dX;
	}
	inline double dataY( int index )
	{
		return (CAXPlotData<XYPOINT,XYPOINT>::operator[](index)).dY;
	}
};
/////////////////////////////////////////////////////////////////////////////
// CDBLPlotData
///< ScrollMode 0:INCREMENT/1:DECREMENT
typedef enum E_SCROLL_MODE{
	INC_SCROLL = 0,	///< 0:INCREMENT
	DEC_SCROLL,		///< 1:DECREMENT
};
class CDBLPlotData : public CAXPlotData<double,double>
{
public:
	/**
	 * 	構築.
	 * 		プロットデータを保持する
	 * 
	 * 	@param iStyle		線種
	 * 	@param color		線色
	 * 	@param iSize		線サイズ
	 */
	CDBLPlotData( int iStyle = PS_SOLID, COLORREF color = 0x00FFFFFF, int iSize = 0 )
		: CAXPlotData<double,double>( iStyle, color, iSize )
	{
		LocalInitialize();
	}
	/**
	 * 	構築.
	 * 		ラインスタイルを元に構築する
	 * 
	 * 	@param lineStyle	ラインスタイル
	 */
	CDBLPlotData( const LINESTYLE &lineStyle )
		: CAXPlotData<double,double>( lineStyle )
	{
		LocalInitialize();
	}
	/**
	 * 	構築.
	 * 		ラインスタイルを元に構築する
	 * 
	 * 	@param lineStyle	ラインスタイル
	 */
	CDBLPlotData( const CAXLineStyle &axlineStyle )
		: CAXPlotData<double,double>( axlineStyle )
	{
		LocalInitialize();
	}
	/**
	 * 	構築.
	 * 		ラインスタイル、マーカースタイルを元に構築する
	 * 
	 * 	@param lineStyle	ラインスタイル
	 * 	@param markStyle	マーカースタイル
	 */
	CDBLPlotData( const LINESTYLE &lineStyle, const MARKERSTYLE &markStyle )
		: CAXPlotData<double,double>( lineStyle, markStyle )
	{
		LocalInitialize();
	}
	/**
	 * 	構築.
	 * 		ラインスタイル、マーカースタイルを元に構築する
	 * 
	 * 	@param lineStyle	ラインスタイル
	 * 	@param markStyle	マーカースタイル
	 */
	CDBLPlotData( const CAXLineStyle &axlineStyle, const CAXMarkerStyle &axmarkStyle )
		: CAXPlotData<double,double>( axlineStyle, axmarkStyle )
	{
		LocalInitialize();
	}
	/**
	 * 	構築.
	 * 		元のCDBLPlotDataを元に構築する
	 * 
	 * 	@param org	コピー元CDBLPlotData
	 */
	CDBLPlotData( const CDBLPlotData &org )
	{
		operator=( org );
	}
	/**
	 * 	破棄.
	 * 		チャンネルデータを破棄する。
	 */
	virtual ~CDBLPlotData()
	{
		RemoveAllItem();
	}
private:
//メンバ変数
protected:
	double			m_dXdelta;		///< データ1点あたりのX軸の増分値
	double			m_dXoffset;		///< X軸のオフセット
	int				m_scrollMode;	///< ScrollMode 0:INC_SCROLL/1:DEC_SCROLL
//オーバーライド
protected:
	inline virtual void CompareMinMax( double checkData )
	{	// 最大値/最小値更新
		m_dataMin = __min(m_dataMin,checkData);		///< データ最小値
		m_dataMax = __max(m_dataMax,checkData);		///< データ最大値
	}
	virtual void LocalInitialize( void )
	{
		m_dXdelta = 1.0;		///< データ1点あたりのX軸の増分値
		m_dXoffset = 0.0;		///< X軸のオフセット
		m_scrollMode = INC_SCROLL;	///< ScrollMode 0:INC_SCROLL/1:DEC_SCROLL
		ClearMinMax();
	}
	virtual void Initialize( void )
	{
		ClearMinMax();
		CAXPlotData<double,double>::Initialize();
	}
public:
	// 初期化
	inline CDBLPlotData &operator =( const CDBLPlotData &src )
	{
		CAXPlotData<double,double>::Copy(src);
		m_dXdelta = src.m_dXdelta;		///< データ1点あたりのX軸の増分値
		m_dXoffset = src.m_dXoffset;	///< X軸のオフセット
		m_scrollMode = src.m_scrollMode;	///< ScrollMode 0:INC_SCROLL/1:DEC_SCROLL
		return *this;
	}
	inline CDBLPlotData &Copy( const CDBLPlotData &src )
	{
		operator=(src);
		return *this;
	}
	virtual void ClearMinMax( void )
	{
		m_dataMin = DBL_MAX;		///< データ最小値
		m_dataMax = -DBL_MAX;	///< データ最大値
	}
	virtual void ClearAllPoint( void )
	{
		ClearMinMax();
		CAXPlotData<double,double>::ClearAllPoint();
	}
	virtual void RemoveAllPoint( void )
	{
		ClearMinMax();
		CAXPlotData<double,double>::RemoveAllPoint();
	}
	inline void SetXdelta( double Delta );
	inline void SetXoffset( double Offset );
	inline int	SetScrollMode( int scrollMode = DEC_SCROLL );
	inline double GetXdelta( void )		{	return m_dXdelta;	}		///< データ1点あたりのX軸の増分値
	inline double GetXoffset( void )	{	return 	m_dXoffset;	}		///< X軸のオフセット
	inline int GetScrollMode( void )	{	return m_scrollMode;	}	///< ScrollMode 0:INC_SCROLL/1:DEC_SCROLL
	inline double dataX( int index )
	{
		if(m_scrollMode == DEC_SCROLL)	{///< ScrollMode 0:INC_SCROLL/1:DEC_SCROLL)
			return (GetXoffset() + GetXdelta() * (index - GetNum()));
		}
		return (GetXoffset() + GetXdelta() * index);
	}
	inline double dataY( int index )
	{
		return (operator[](index));
	//	return (m_plotData[index]);
	}
};
///////////////////////////////////////
/**
 * 	データ1点あたりのX軸の増分値を設定する.
 * 
 * 	@param Delta	///< 設定するデータ1点あたりのX軸の増分値
 */
inline void CDBLPlotData::SetXdelta( double Delta )
{
	if(Delta > 1.0e-38)	{
		m_dXdelta = Delta;
		Redraw(TRUE);
	}	
}
///////////////////////////////////////
/**
 * 	X軸のオフセットを設定する.
 * 
 * 	@param Offset	///< X軸のオフセット
 */
inline void CDBLPlotData::SetXoffset( double Offset )
{
	m_dXoffset = Offset;
	Redraw(TRUE);
}
///////////////////////////////////////
/**
 * 	X軸のScrollモードを設定する.
 * 
 * 	@param scrollMode	0:INC_SCROLL/1:DEC_SCROLL
 *	@return 変更前のScrollモード
 */
inline int CDBLPlotData::SetScrollMode( int scrollMode /*= DEC_SCROLL*/ )
{
	int iMode = GetScrollMode();
	if(scrollMode == INC_SCROLL || scrollMode == DEC_SCROLL )	{
		m_scrollMode = scrollMode;
	}
	return iMode;
}
/////////////////////////////////////////////////////////////////////////////
//CAXGDIPlotCtrl
class CAXGDIPlotCtrl : public CAXGDICtrl
{
// コンストラクション
public:
	CAXGDIPlotCtrl( COLORREF bkColor = IBLACK );
	CAXGDIPlotCtrl( CAXGDIPlotCtrl &org );

// アトリビュート
public:
	// グリッドラインクラスを取得する(X).
	inline CAXLineStyle & GetGridXStyle(void)	{	return	m_gridX;	}		///< グリッドラインスタイル
	// グリッドラインクラスを取得する(Y).
	inline CAXLineStyle & GetGridYStyle(void)	{	return 	m_gridY;	}		///< グリッドラインスタイル
	//目盛り表示 
	inline CAXMeasureStyle & GetAxisX()	{	return m_axisX;	}	///< X軸目盛りスケール
	inline CAXMeasureStyle & GetAxisY()	{	return m_axisY;	}	///< Y軸目盛りスケール
	///< 軸交差設定　(0:Min/1:Max/2:Center/3:データ値指定)
	inline BYTE GetStyleXCross(void) const	{	return m_byStyleXCross;	}
	inline BYTE GetStyleYCross(void) const	{	return m_byStyleYCross;	}
	///< プロットデータのスケールを表示有効（X軸）
	inline BOOL IsShowPlotScaleX( void ) const 
	{
		return ( m_byShowPlotScaleX ? TRUE : FALSE );
	}
	///< プロットデータのスケールを表示有効（Y軸）
	inline BOOL IsShowPlotScaleY( void ) const 
	{
		return ( m_byShowPlotScaleY ? TRUE : FALSE );
	}
	///< プロットデータ名称の表示有効
	inline BOOL IsShowPlotName( void ) const 
	{
		return ( (m_byPlotNameShowMode & AX_GDISHOW) ? TRUE : FALSE );
	}
	///< プロットデータ名称の表示モード取得
	inline int GetShowModePlotName( void ) const {		return ( AX_GDIALLMODE & m_byPlotNameShowMode );	}
	//
	void SetAxisXCross( BYTE byCrossStyle, double dCross = 0.0 )
	{
		m_byStyleXCross = byCrossStyle;	///< 軸交差有効(0:Min/1:Max/2:Center/3:データ値指定)
		m_dAxisXCross = dCross;		///< 軸交差ポイント(データ値指定)
	}
	void SetAxisYCross( BYTE byCrossStyle, double dCross = 0.0 )
	{
		m_byStyleYCross = byCrossStyle;	///< 軸交差有効(0:Min/1:Max/2:Center/3:データ値指定)
		m_dAxisYCross = dCross;		///< 軸交差ポイント(データ値指定)
	}
	inline void ShowPlotScaleX( BOOL bShow )///< プロットデータのスケールを表示有効（X軸）
	{
		m_byShowPlotScaleX = ( bShow ? 1 : 0 );
	}
	inline void ShowPlotScaleY( BOOL bShow )///< プロットデータのスケールを表示有効（Y軸）
	{
		m_byShowPlotScaleY = ( bShow ? 1 : 0 );
	}
	///< プロットデータ名称の表示有効
	inline void ShowPlotName( BOOL bShow )
	{
		if(bShow)	{	m_byPlotNameShowMode |= AX_GDISHOW;	}
		else		{	m_byPlotNameShowMode &= (0xff ^ AX_GDISHOW);	}
	}
	inline int SetShowModePlotName( int iMode = AX_GDIXMODE )
	{
		int iOldMode = GetShowModePlotName();
		m_byPlotNameShowMode &= (0xff ^ AX_GDIALLMODE);
		m_byPlotNameShowMode |= iMode;
		return iOldMode;
	}
	//カーソルのフォントサイズを設定する。
	inline void	SetCursorFontSize( int iFontSize )	{	m_iCursorFontSize = iFontSize;	}
	inline int	GetCursorFontSize( void )			{	return m_iCursorFontSize;		}
	//カーソルのフォントサイズを設定する。
	inline void	SetAreaCsrFontSize( int iFontSize )	{	m_iAreaCsrFontSize = iFontSize;	}
	inline int	GetAreaCsrFontSize( void )			{	return m_iAreaCsrFontSize;		}

/*	double SetMeasureRatio(double dRatio)	{
		if( dRatio > 0.0 && dRatio <= 100.0)	{
			m_dMeasureRatio = dRatio;	///< 軸目盛りの全体に対する比率
			Redraw(TRUE);
		}
		return m_dMeasureRatio;	///< 軸目盛りの全体に対する比率
	}*/
	// グリッド線
	inline void	ShowGridX( BOOL bShow, const LINESTYLE &lineStyle );
	inline void	ShowGridY( BOOL bShow, const LINESTYLE &lineStyle );
	inline void	ShowGridX( BOOL bShow, int iStyle = -1, COLORREF color = IGRAY, int iSize = -1 );
	inline void	ShowGridY( BOOL bShow, int iStyle = -1, COLORREF color = IGRAY, int iSize = -1 );


// オペレーション
public:
	inline CAXGDIPlotCtrl & Copy( const CAXGDIPlotCtrl &src )	{	operator=(src);	return *this;	}
	inline CAXGDIPlotCtrl & operator=( const CAXGDIPlotCtrl &src );

	inline virtual void RemoveAllItem(void);
	inline virtual void ClearAllItem(void);
// オーバーライド
public:
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAXGDIPlotCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

protected:

// インプリメンテーション
public:
	virtual ~CAXGDIPlotCtrl();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CAXGDIPlotCtrl)
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk( UINT nFlags, CPoint point );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void Initialize( void );	//初期化
	// 描画
	virtual void DrawGrid( CDC *pDC, int iType, const CRect &rect,const LINESTYLE &gridLine );
	virtual void DrawMeasure( CDC *pDC, const CRect &rect, CAXMeasureStyle &measure );
	virtual void DrawPlotName( CDC *pDC, const CRect &rect, int iXYMode, int nIndex, int nShowLine, COLORREF color, LPCTSTR lpszString );
	virtual void DrawPlotScale( CDC *pDC, const CRect &rect, int iXYMode, int nIndex, int nShowLine, COLORREF color, double dblMin, double dblMax );

	// カーソルの描画
	virtual void DrawPlotCursor( CDC *pDC, const CRect &rect, CAXPlotCursor &plotCursor );
	virtual void DrawPlotCursor( CDC *pDC, const CRect &rect, CXYPlotData &data, CAXPlotCursor &plotCursor );
	virtual void DrawPlotCursor( CDC *pDC, const CRect &rect, CDBLPlotData &data, CAXPlotCursor &plotCursor );
	// エリアカーソルの描画
	virtual void DrawAreaCursor( CDC *pDC, const CRect &rect, CAXAreaCursor &areaCursor, BOOL bDrawName = FALSE );
	virtual void DrawAreaCursor( CDC *pDC, const CRect &rect, CXYPlotData &data, CAXAreaCursor &areaCursor, BOOL bDrawName = FALSE );
	virtual void DrawAreaCursor( CDC *pDC, const CRect &rect, CDBLPlotData &data, CAXAreaCursor &areaCursor, BOOL bDrawName = FALSE );

	// マウス左ボタン押下の時のActivate
	virtual int MouseLBdownActivate( const CRect &rect, CPoint point, AXGCACTINFO *lpActiveInfo ){ return AXGCTRLACT_NONE;};

protected:
	CDC				m_bmpDC;			///< ビットマップDC
	CBitmap			m_bitmap;			///< メモリビットマップ
//	RECT			m_rectMargin;		///< 描画マージン
	BOOL			m_bRedraw;			///< 再描画フラグ

	//グリッド 
	BOOL			m_bShowGridX;	///< グリッド表示有効（X軸）
	BOOL			m_bShowGridY;	///< グリッド表示有効（Y軸）
	CAXLineStyle	m_gridX;		///< グリッドラインスタイル
	CAXLineStyle	m_gridY;		///< グリッドラインスタイル

	//目盛り表示 
	CAXMeasureStyle	m_axisX;			///< X軸目盛りスケール
	CAXMeasureStyle	m_axisY;			///< Y軸目盛りスケール
	BYTE			m_byStyleXCross;	///< 軸交差有効(0:Min/1:Max/2:Center/3:データ値指定)
	BYTE			m_byStyleYCross;	///< 軸交差有効(0:Min/1:Max/2:Center/3:データ値指定)
	double			m_dAxisXCross;		///< 軸交差ポイント(データ値指定)
	double			m_dAxisYCross;		///< 軸交差ポイント(データ値指定)

	BYTE			m_byShowPlotScaleX;		///< プロットデータのスケールの表示有効（X軸）
	BYTE			m_byShowPlotScaleY;		///< プロットデータのスケールの表示有効（Y軸）
	BYTE			m_byPlotNameShowMode;	///< プロットデータ名称の表示モード

	int				m_iCursorFontSize;	// カーソルフォントサイズ
	int				m_iAreaCsrFontSize;	// エリアカーソルフォントサイズ

//	double			m_dMeasureRatio;	///< 軸目盛りの全体に対する比率

	CArray<CAXPlotCursor,CAXPlotCursor> m_plotCursor;	//カーソル
	CArray<CAXAreaCursor,CAXAreaCursor> m_areaCursor;	//エリアカーソル

public:
	//カーソルを追加します。
	int AddPlotCursor( int iMode = CURSORCROSS, int iStyle = PS_SOLID, COLORREF color = 0x00FFFFFF, int iSize = 0 )
	{
		CAXPlotCursor plotCursor( iMode, iStyle, color, iSize );
		return m_plotCursor.Add( plotCursor );
	}
	//カーソルを追加します。
	int AddPlotCursor( int iMode, const LINESTYLE &lineStyle )
	{
		CAXPlotCursor plotCursor( iMode, lineStyle );
		return m_plotCursor.Add( plotCursor );
	}
	
	inline int GetPlotCursorNum(void)	{	return m_plotCursor.GetSize();	}

	inline CAXPlotCursor & GetPlotCursor(int index)	{	return m_plotCursor[index];	}
	///////////////////////////////////////
	/**
	 * 	カーソル全削除
	 * 		カーソルをクリアする。
	 */
	inline void ClearPlotCursor( void )	{	m_plotCursor.RemoveAll();	}
/////////////
	int AddAreaCursor( int iMode = CURSORCROSS, int iBStyle = BS_SOLID, int iHStyle = HS_HORIZONTAL, COLORREF color = ILIGHTPINK )
	{
		CAXAreaCursor areaCursor( iMode, iBStyle, iHStyle, color );
		return m_areaCursor.Add( areaCursor );
	}
	
	int AddAreaCursor( int iMode, const PATTERNSTYLE &patternStyle )
	{
		CAXAreaCursor areaCursor( iMode, patternStyle );
		return m_areaCursor.Add( areaCursor );
	}

	inline int GetAreaCursorNum(void)	{	return m_areaCursor.GetSize();	}

	inline CAXAreaCursor & GetAreaCursor(int index)	{	return m_areaCursor[index];	}
	///////////////////////////////////////
	/**
	 * 	エリアカーソル全削除.
	 * 		エリアカーソルをクリアする。
	 */
	inline void ClearAreaCursor( void )		{	m_areaCursor.RemoveAll();	}

	//************************ 拡張機能 ************************//
protected:
	BOOL			m_bZooming;		///< 拡大中フラグ
	int				m_iMouseZoom;	///< マウス拡大機能ON/OFFフラグ
	CRect			m_guideRect;	///< 拡大領域
	
	/// 拡大縮小スケール
	CArray<CAXGDIScaleData,CAXGDIScaleData>	m_zoomScale;

	// グラフ拡大
	virtual void Zoom( CRect rectZoom ){};
public:
	///< マウス拡大機能
	virtual int EnableMouseZoom ( int iZoom = XY_ZOOM );
	inline virtual int GetMouseZoom ( void );
	inline virtual BOOL IsMouseZoom ( void );
};
/////////////////////////////////////////////////////////////////////////////
// CAXGDIPlotCtrl
///////////////////////////////////////
/**
 * 	グリッド線の表示/非表示(X).
 * 		X軸のグリッド線の線種を指定し表示/非表示する。
 * 
 * 	@param bShow	TRUE:表示 FALSE:非表示
 * 	@param iStyle	グリッド線種
 * 	@param color	グリッド線色
 * 	@param iSize	グリッド線サイズ
 */
inline void CAXGDIPlotCtrl::ShowGridX( BOOL bShow, int iStyle /*= -1*/, COLORREF color /*= -1*/, int iSize /*= -1*/ )
{
	m_bShowGridX = bShow;
	if(iStyle >= PS_SOLID)	{	m_gridX.SetLineStyle( iStyle, color, iSize );	}
	Redraw(TRUE);
}
///////////////////////////////////////
/**
 * 	グリッド線の表示/非表示(Y).
 * 		Y軸のグリッド線の線種を指定し表示/非表示する。
 * 
 * 	@param bShow	TRUE:表示 FALSE:非表示
 * 	@param iStyle	グリッド線種
 * 	@param color	グリッド線色
 * 	@param iSize	グリッド線サイズ
 */
inline void CAXGDIPlotCtrl::ShowGridY( BOOL bShow, int iStyle /*= -1*/, COLORREF color /*= -1*/, int iSize /*= -1*/ )
{
	m_bShowGridY = bShow;
	if(iStyle >= PS_SOLID)	{	m_gridY.SetLineStyle( iStyle, color, iSize );	}
	Redraw(TRUE);
}
///////////////////////////////////////
/**
 * 	グリッド線の表示/非表示(X).
 * 		X軸のグリッド線の線種を指定し表示/非表示する。
 * 
 * 	@param bShow	TRUE:表示 FALSE:非表示
 * 	@param lineStyle	ラインスタイル
 */
inline void	CAXGDIPlotCtrl::ShowGridX( BOOL bShow, const LINESTYLE &lineStyle )
{
	m_bShowGridX = bShow;
	m_gridX.SetLineStyle( lineStyle );
	Redraw(TRUE);
}
///////////////////////////////////////
/**
 * 	グリッド線の表示/非表示(Y).
 * 		Y軸のグリッド線の線種を指定し表示/非表示する。
 * 
 * 	@param bShow	TRUE:表示 FALSE:非表示
 * 	@param lineStyle	ラインスタイル
 */
inline void	CAXGDIPlotCtrl::ShowGridY( BOOL bShow, const LINESTYLE &lineStyle )
{
	m_bShowGridY = bShow;
	m_gridY.SetLineStyle( lineStyle );
	Redraw(TRUE);
}
///////////////////////////////////////
/**
 * 	CAXGDIPlotCtrlのコピー.
 * 	@param src	コピー元のCAXGDIPlotCtrl
 * 	@return		CAXGDIPlotCtrlのポインタ
 */
inline CAXGDIPlotCtrl & CAXGDIPlotCtrl::operator=( const CAXGDIPlotCtrl &src )
{
	m_bkColor = src.m_bkColor;

	m_axisX = src.m_axisX;
	m_axisY = src.m_axisY;

	m_bShowGridX = src.m_bShowGridX;	///< グリッド表示有効（X軸）
	m_bShowGridY = src.m_bShowGridY;	///< グリッド表示有効（Y軸）
	m_gridX = src.m_gridX;		///< グリッドラインスタイル
	m_gridY = src.m_gridY;		///< グリッドラインスタイル

//	m_dMeasureRatio = src.m_dMeasureRatio;		///< 軸目盛りの全体に対する比率
	m_byStyleXCross = src.m_byStyleXCross;		///< 軸交差有効(0:Min/1:Max/2:Center/3:データ値指定)
	m_byStyleYCross = src.m_byStyleYCross;		///< 軸交差有効(0:Min/1:Max/2:Center/3:データ値指定)
	m_dAxisXCross = src.m_dAxisXCross;		///< 軸交差ポイント(データ値指定)
	m_dAxisYCross = src.m_dAxisYCross;		///< 軸交差ポイント(データ値指定)
	ShowPlotScaleX(src.IsShowPlotScaleX());///< プロットデータのスケールを表示有効（X軸）
	ShowPlotScaleY(src.IsShowPlotScaleY());///< プロットデータのスケールを表示有効（X軸）
	ShowPlotName(src.IsShowPlotName());	///< プロットデータ名称の表示有効
	SetShowModePlotName(src.GetShowModePlotName());

	if(0)	{
		double dRatio = (double)(GetInitSize().cy) / src.GetInitSize().cy;		///< グラフのRect
		if(src.m_iCursorFontSize > 0)	{
		m_iCursorFontSize = FtoL(src.m_iCursorFontSize * dRatio);		// カーソルフォントサイズ
		if(m_iCursorFontSize < 6)	{	m_iCursorFontSize = 6;	}
		}
		if(src.m_iAreaCsrFontSize > 0)	{
			m_iAreaCsrFontSize = FtoL(src.m_iAreaCsrFontSize * dRatio);	// エリアカーソルフォントサイズ
			if(m_iAreaCsrFontSize < 6)	{	m_iAreaCsrFontSize = 6;	}
		}
	}	else	{
		m_iCursorFontSize = src.m_iCursorFontSize;		// カーソルフォントサイズ
		m_iAreaCsrFontSize = src.m_iAreaCsrFontSize;	// エリアカーソルフォントサイズ
	}

	m_plotCursor.RemoveAll();
	if( src.m_plotCursor.GetSize() > 0 )	{
		m_plotCursor.Copy( src.m_plotCursor );
	}

	m_areaCursor.RemoveAll();
	if( src.m_areaCursor.GetSize() > 0 )	{
		m_areaCursor.Copy( src.m_areaCursor );
	}

	CAXGDICtrl::Copy(src);
	Initialize();

	return *this;
}
///////////////////////////////////////
/**
 * 	すべての情報のクリア.
 *
 */
inline void CAXGDIPlotCtrl::ClearAllItem(void)
{
	ClearActiveInfo(&m_activeInfo);	///< Active状態の情報のクリア
	m_zoomScale.RemoveAll();
	m_plotCursor.RemoveAll();
	m_areaCursor.RemoveAll();
	m_iMouseZoom = ZOOM_OFF;
}
///////////////////////////////////////
/**
 * 	すべての情報のクリア.
 *
 */
inline void CAXGDIPlotCtrl::RemoveAllItem(void)
{
	ClearAllItem();
}
///////////////////////////////////////
/**
 * 	マウスでのグラフ拡大機能をON/OFFする.
 * 
 * 	@return			グラフ拡大機能許可状態を返す。
 */
inline int CAXGDIPlotCtrl::GetMouseZoom ( void )
{
	return m_iMouseZoom;
}
///////////////////////////////////////
/**
 * 	マウスでのグラフ拡大機能ON/OFFを取得する.
 * 
 * 	@return		拡大機能を有効フラグ
 */
inline BOOL CAXGDIPlotCtrl::IsMouseZoom ( void )
{
	return	( m_iMouseZoom == ZOOM_OFF  ? FALSE : TRUE) ; 
}
/////////////////////////////////////////////////////////////////////////////
// inline finction
/////////////////////////////////////////////////////////////////////////////
// CDBLPlotData
///////////////////////////////////////


#endif // !defined(_AXGDIPLOT_H_INCLUDED_)