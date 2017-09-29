// AXGraphCtrl.h: CAXGraphCtrl クラスのインターフェイス
//
/********************************************************
// CXYPlotData		:データクラス（データ、スケール、カーソル保持）
// CAXGraphCtrl		:グラフ描画クラス
//											by YOTSUTSU
//	* History	:	date:2005,24,Mar.	新規作成
ver.1.00	
********************************************************/
#ifndef __GRAPHCTRL_H_INCLUDED__
#define __GRAPHCTRL_H_INCLUDED__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Float.h>
#include <afxtempl.h>
#include "AXGDIPlot.h"

/////////////////////////////////////////////////////////////////////////////
// CAXGraphCtrl ウィンドウ
/////////////////////////////////////////////////////////////////////////////
/// グラフクラス
class CAXGraphCtrl : public CAXGDIPlotCtrl
{
// コンストラクション
public:
	CAXGraphCtrl( COLORREF bkColor = IBLACK );
	CAXGraphCtrl( CAXGraphCtrl &org );
	

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAXGraphCtrl)
	protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow();
//	virtual BOOL OnChildNotify( UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult );
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CAXGraphCtrl();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CAXGraphCtrl)
	afx_msg void OnDestroy();
//	afx_msg void OnPaint();
//	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDblClk( UINT nFlags, CPoint point );
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
//tachibana200612>>>>>>>>>>>>>>>>>>>>>>>>>>>
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	// 通知メッセージの処理
	virtual BOOL OnChangeActive( AXGCNOTIFY *pNotifyMsg );
	virtual BOOL OnChangeStyle( AXGCNOTIFY *pNotifyMsg );
	virtual BOOL OnChangeScale( AXGCNOTIFY *pNotifyMsg );
	virtual BOOL OnChangeCursol( AXGCNOTIFY *pNotifyMsg );
	
protected:
	// 描画前処理
	virtual void BeginPaintDC( CDC *pDC, const CRect &rect );
	// 描画
	virtual void DrawLayerData( CDC *pDC, const CRect &rect, CXYPlotData &data );
	// カーソル描画
//	virtual void DrawLayerLineCursor( CDC *pDC, const CRect &rect, CXYPlotData &data );
//	virtual void DrawLineCursor( CDC *pDC, const CRect &rect, CXYPlotData &data, AXCURSORINFO &cursorInfo );
	// エリアカーソル描画
//	virtual void DrawLayerAreaCursor( CDC *pDC, const CRect &rect, CXYPlotData &data );
//	virtual void DrawAreaCursor( CDC *pDC, const CRect &rect, CXYPlotData &data, AXAREACSRINFO &areaInfo );
//	virtual void DrawLayerAreaCsrName( CDC *pDC, const CRect &rect, CXYPlotData &data );
//	virtual void DrawAreaCsrName( CDC *pDC, const CRect &rect, CXYPlotData &data, AXAREACSRINFO &areaInfo );

	virtual void DrawActiveState( CDC *pDC, const CRect &rect );

	// マウス左ボタン押下の時のActivate
	virtual int MouseLBdownActivate( const CRect &rect, CPoint point, AXGCACTINFO *lpActiveInfo );


protected:
	/// データ(レイアーデータ)
	CArray<CXYPlotData,CXYPlotData>	m_plotData;

public:
	// 初期化
	inline CAXGraphCtrl& operator =( CAXGraphCtrl &src );
	inline virtual void RemoveAllItem(void);
	inline virtual void ClearAllItem(void);

	// レイアー追加/削除
	inline int AddLine( int iStyle = PS_SOLID, COLORREF color = 0x00ffffff, int iSize = 0, int nDataSize = 0 );
	inline int AddLine( const LINESTYLE &lineStyle, int nDataSize = 0  );
	inline int AddLine( const LINESTYLE &lineStyle, const MARKERSTYLE &markStyle, int nDataSize = 0  );
	inline int AddLine( const CAXLineStyle &axlineStyle, int nDataSize = 0  );
	inline int AddLine( const CAXLineStyle &axlineStyle, const CAXMarkerStyle &axmarkStyle, int nDataSize = 0  );
//	inline int AddLine( CAXPlotStyle &plotStyle, int nDataSize = 0  );
	// データサイズの設定
	inline void SetDataSize( int nDataSize );
	// データの削除
	inline void ClearAllData(void);
	inline void RemoveAllLine(void);
//200611 t.tachibana added start>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	inline void RemoveLine(int nIndex, int nCount = 1);
//200611 t.tachibana added end<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	// データ配列要素の取得
	inline CXYPlotData & operator []( int n );
	inline CXYPlotData & GetLine( int n );
	// データ配列数
	inline int  GetLineNum(void);
	// 表示ライン数
	inline int  GetShowLineNum(void);

	// データ表示範囲
	void SetXScale( double dMin, double dMax, double dDelta = -1.0, double dDetailDelta = -1, BOOL bAllLayer = FALSE );
	void SetYScale( double dMin, double dMax, double dDelta = -1.0, double dDetailDelta = -1, BOOL bAllLayer = FALSE );
//200612 t.tachibana added start>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	void SetXScaleEx( double dMin, double dMax, double dDelta = -1.0, double dDetailDelta = -1, BOOL bAllLayer = FALSE, BOOL bRedraw = FALSE );
	void SetYScaleEx( double dMin, double dMax, double dDelta = -1.0, double dDetailDelta = -1, BOOL bAllLayer = FALSE, BOOL bRedraw = FALSE );
//200612 t.tachibana added end<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	//対数グラフ描画
	void SetXLogScale(BOOL bLog = TRUE, BOOL bScaleAuto = TRUE );
	void SetYLogScale(BOOL bLog = TRUE, BOOL bScaleAuto = TRUE );
	// スクロール
	void  Scroll( double dScrollX, double dScrollY );
	// データのMin&Max一括クリア
	void ClearMinMax( void );

//******** 拡張機能 ********//
	///< マウス拡大機能
	// グラフ拡大
	virtual void Zoom( CRect rectZoom );

	// 描画
	virtual void DrawDC( CDC *pDC, CRect rect )				{	DrawGraph( pDC, rect );	}
	virtual void DrawExDC( CDC *pDC, const CRect &rect )	{	DrawLineCursor( pDC, rect );	}
	// グラフ描画	
	virtual void DrawGraph( CDC *pDC, const CRect &rect );
	// カーソル描画
	virtual void DrawLineCursor( CDC *pDC, const CRect &rect );
	// 再表示
	inline void Redraw(BOOL bRedraw = FALSE);
};
/////////////////////////////////////////////////////////////////////////////
// inline finction
/////////////////////////////////////////////////////////////////////////////
// CAXGraphCtrl
///////////////////////////////////////
/**
 * 	コピー.
 * 		与えられたグラフのデータをコピーする
 * 
 * 	@param src	コピー元グラフ
 * 	@return		このクラスのポインタ
 */
inline CAXGraphCtrl &CAXGraphCtrl::operator =( CAXGraphCtrl &src )
{
	RemoveAllItem();
	
	CAXGDIPlotCtrl::Copy(src);
	
	int lineNum = src.GetLineNum();
	for( int i = 0; i < lineNum; i++ ){
		m_plotData.Add( src[i] );
	}
	Redraw(TRUE);
	return *this;
}
///////////////////////////////////////
/**
 * 	すべての情報のクリア.
 *
 */
inline void CAXGraphCtrl::ClearAllItem(void)
{
	ClearAllData();
	CAXGDIPlotCtrl::ClearAllItem();
}
///////////////////////////////////////
/**
 * 	すべての情報の削除.
 *
 */
inline void CAXGraphCtrl::RemoveAllItem(void)
{
	//ClearActiveInfo(&m_activeInfo);	///< Active状態の情報のクリア
	RemoveAllLine();					//データのクリア
	CAXGDIPlotCtrl::RemoveAllItem();
}
///////////////////////////////////////
/**
 * 	線を追加する.
 * 
 * 	@param	iStyle		線種
 * 	@param	color		線色
 * 	@param	iSize		線サイズ
 *	@param	nDataSize	データサイズ
 * 	@return				追加した線の線番号 0～
 */
int CAXGraphCtrl::AddLine( int iStyle /*= PS_SOLID*/, COLORREF color /*= 0x00ffffff*/, int iSize /*= 0*/, int nDataSize /*= 0*/)
{
	int index = m_plotData.Add( CXYPlotData( iStyle, color, iSize ) );
	m_plotData[index].SetSize( nDataSize );
	return index;
}
///////////////////////////////////////
/**
 * 	線を追加する.
 * 
 * 	@param lineStyle	ラインスタイル
 * 	@param markStyle	マーカースタイル
 *	@param	nDataSize	データサイズ
 * 	@return				追加した線の線番号 0～
 */
int CAXGraphCtrl::AddLine( const LINESTYLE &lineStyle, int nDataSize /*= 0*/)
{
	int index = m_plotData.Add( CXYPlotData( lineStyle ) );
	m_plotData[index].SetSize( nDataSize );
	return index;
}
///////////////////////////////////////
/**
 * 	線を追加する.
 * 
 * 	@param lineStyle	ラインスタイル
 * 	@param markStyle	マーカースタイル
 *	@param	nDataSize	データサイズ
 * 	@return				追加した線の線番号 0～
 */
int CAXGraphCtrl::AddLine( const LINESTYLE &lineStyle, const MARKERSTYLE &markStyle, int nDataSize /*= 0*/ )
{
	int index = m_plotData.Add( CXYPlotData( lineStyle, markStyle ) );
	m_plotData[index].SetSize( nDataSize );
	return index;
}
///////////////////////////////////////
/**
 * 	線を追加する.
 * 
 * 	@param axlineStyle	ラインスタイルクラス
 *	@param	nDataSize	データサイズ
 * 	@return				追加した線の線番号 0～
 */
int CAXGraphCtrl::AddLine( const CAXLineStyle &axlineStyle, int nDataSize /*= 0*/  )
{
	int index = m_plotData.Add( CXYPlotData( axlineStyle ) );
	m_plotData[index].SetSize( nDataSize );
	return index;
}
///////////////////////////////////////
/**
 * 	線を追加する.
 * 
 * 	@param axlineStyle	ラインスタイルクラス
 * 	@param axmarkStyle	マーカースタイルクラス
 *	@param	nDataSize	データサイズ
 * 	@return				追加した線の線番号 0～
 */
int CAXGraphCtrl::AddLine( const CAXLineStyle &axlineStyle, const CAXMarkerStyle &axmarkStyle, int nDataSize /*= 0*/  )
{
	int index = m_plotData.Add( CXYPlotData( axlineStyle, axmarkStyle ) );
	m_plotData[index].SetSize( nDataSize );
	return index;
}
///////////////////////////////////////
/**
 * 	データサイズを設定する.
 * 		設定したデータサイズの領域を確保する。
 *	
 *	@param		nDataSize	設定するデータサイズ
 * 	@return		領域を確保したデータサイズ
 */
inline void CAXGraphCtrl::SetDataSize( int nDataSize )
{
	//for(int index = 0; index < GetLineNum(); index++ )	{
		m_plotData/*[index].*/.SetSize( nDataSize );
	//}
}
///////////////////////////////////////
/**
 * 	すべての線をデータをクリアする.
 * 		すべての線及びデータをクリアします。
 */
void CAXGraphCtrl::ClearAllData(void)
{
	for(int index = 0; index < GetLineNum(); index++ )	{
		m_plotData[index].ClearAllPoint();
	}
}
///////////////////////////////////////
/**
 * 	すべての線を削除する.
 * 		すべての線及びデータを削除します。今まで追加したライン番号は全て無効になります。
 */
void CAXGraphCtrl::RemoveAllLine(void)
{
	m_plotData.RemoveAll();
}
//200611 t.tachibana added start>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
///////////////////////////////////////
/**
 * 	indexで指定した線を削除する.
 *		!!!!配列要素数のチェックは、クラスの外側で意識する必要が有る!!!!
 * 	@param nIndex	0 以上で、GetUpperBound が返す値以下の整数のインデックス。
 * 	@param nCount	削除する要素数。
 *	
 */
inline void CAXGraphCtrl::RemoveLine(int nIndex, int nCount/* = 1*/)
{
	m_plotData.RemoveAt(nIndex, nCount);
}
//200611 t.tachibana added end<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///////////////////////////////////////
/**
 * 	プロットデータ取得.
 * 	@param n	線番号
 * 	@return		プロットデータクラスのポインタ
 */
inline CXYPlotData & CAXGraphCtrl::operator []( int n )
{
	return m_plotData[n];
}
///////////////////////////////////////
/**
 * 	プロットデータ取得.
 * 	@param n	線番号
 * 	@return		プロットデータクラスのポインタ
 */
inline CXYPlotData & CAXGraphCtrl::GetLine( int n )
{
	return m_plotData[n];
}
///////////////////////////////////////
/**
 * 	線数の取得.
 * 		設定されている線の数を取得する
 * 
 * 	@return	設定されている線の数
 */
inline int CAXGraphCtrl::GetLineNum( void )
{
	return m_plotData.GetUpperBound()+1;
}
///////////////////////////////////////
/**
 * 	表示中の線数の取得.
 * 		設定されている表示中の線の数を取得する
 * 
 * 	@return	設定されている表示中の線の数
 */
inline int CAXGraphCtrl::GetShowLineNum( void )
{
	int showLine = 0;
	for(int i = 0; i < GetLineNum(); i++ )	{
		if(GetLine(i).IsVisible())	{	showLine++;	}
	}

	return showLine;
}
///////////////////////////////////////
/**
 * 	再表示.
 * 		グラフを再表示する。
 */
inline void CAXGraphCtrl::Redraw(BOOL bRedraw /*= FALSE*/)
{
	if( IsWindow( m_hWnd ) ){
		if(bRedraw)	{	m_bRedraw = bRedraw;	}
		Invalidate();
		UpdateWindow();
	}
}
///////////////////////////////////////
/**
 * 	マウスでのグラフ拡大機能を設定する.
 * 
 * 	@param iZoom	拡大機能を設定する
 *		ZOOM_OFF = 0,
 *		XY_ZOOM,		///<X方向、Y方向の両方向を拡大
 *		X_ZOOM,			///<X方向拡大
 *		Y_ZOOM,			///<Y方向拡大
 * 	@return			許可状態を返す。
 */
//inline int CAXGraphCtrl::EnableMouseZoom ( int iZoom /*= XY_ZOOM*/ )
/*
{
	if(IsEnableActivate())	{
		if(m_iMouseZoom == XY_ZOOM || m_iMouseZoom == X_ZOOM || m_iMouseZoom == Y_ZOOM  )	{
			m_iMouseZoom = iZoom;	///< マウス拡大機能ON/OFFフラグ
		}
	}
	return m_iMouseZoom;
}
///////////////////////////////////////
/**
 * 	マウスでのグラフ拡大機能をON/OFFする.
 * 
 * 	@return			グラフ拡大機能許可状態を返す。
 *
inline int CAXGraphCtrl::GetMouseZoom ( void )
{
	return m_iMouseZoom;
}
///////////////////////////////////////
/**
 * 	マウスでのグラフ拡大機能ON/OFFを取得する.
 * 
 * 	@return		拡大機能を有効フラグ
 *
inline BOOL CAXGraphCtrl::IsMouseZoom ()
{
	return	( m_iMouseZoom == ZOOM_OFF  ? FALSE : TRUE) ; 
}
*/
#endif // __GRAPHCTRL_H_INCLUDED__