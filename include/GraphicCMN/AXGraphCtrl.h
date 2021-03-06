// AXGraphCtrl.h: CAXGraphCtrl クラスのインタ�`フェイス
//
/********************************************************
// CXYPlotData		:デ�`タクラス�┘禰`タ、スケ�`ル、カ�`ソル隠隔��
// CAXGraphCtrl		:グラフ宙鮫クラス
//											by YOTSUTSU
//	* History	:	date:2005,24,Mar.	仟�ﾗ�撹
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
	

// アトリビュ�`ト
public:

// オペレ�`ション
public:

// オ�`バ�`ライド
	// ClassWizard は�∀謇v方のオ�`バ�`ライドを伏撹します。
	//{{AFX_VIRTUAL(CAXGraphCtrl)
	protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow();
//	virtual BOOL OnChildNotify( UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult );
	//}}AFX_VIRTUAL

// インプリメンテ�`ション
public:
	virtual ~CAXGraphCtrl();

	// 伏撹されたメッセ�`ジ マップ�v方
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
	// 宥岑メッセ�`ジの�I尖
	virtual BOOL OnChangeActive( AXGCNOTIFY *pNotifyMsg );
	virtual BOOL OnChangeStyle( AXGCNOTIFY *pNotifyMsg );
	virtual BOOL OnChangeScale( AXGCNOTIFY *pNotifyMsg );
	virtual BOOL OnChangeCursol( AXGCNOTIFY *pNotifyMsg );
	
protected:
	// 宙鮫念�I尖
	virtual void BeginPaintDC( CDC *pDC, const CRect &rect );
	// 宙鮫
	virtual void DrawLayerData( CDC *pDC, const CRect &rect, CXYPlotData &data );
	// カ�`ソル宙鮫
//	virtual void DrawLayerLineCursor( CDC *pDC, const CRect &rect, CXYPlotData &data );
//	virtual void DrawLineCursor( CDC *pDC, const CRect &rect, CXYPlotData &data, AXCURSORINFO &cursorInfo );
	// エリアカ�`ソル宙鮫
//	virtual void DrawLayerAreaCursor( CDC *pDC, const CRect &rect, CXYPlotData &data );
//	virtual void DrawAreaCursor( CDC *pDC, const CRect &rect, CXYPlotData &data, AXAREACSRINFO &areaInfo );
//	virtual void DrawLayerAreaCsrName( CDC *pDC, const CRect &rect, CXYPlotData &data );
//	virtual void DrawAreaCsrName( CDC *pDC, const CRect &rect, CXYPlotData &data, AXAREACSRINFO &areaInfo );

	virtual void DrawActiveState( CDC *pDC, const CRect &rect );

	// マウス恣ボタン兀和の�rのActivate
	virtual int MouseLBdownActivate( const CRect &rect, CPoint point, AXGCACTINFO *lpActiveInfo );


protected:
	/// デ�`タ(レイア�`デ�`タ)
	CArray<CXYPlotData,CXYPlotData>	m_plotData;

public:
	// 兜豚晒
	inline CAXGraphCtrl& operator =( CAXGraphCtrl &src );
	inline virtual void RemoveAllItem(void);
	inline virtual void ClearAllItem(void);

	// レイア�`弖紗/��茅
	inline int AddLine( int iStyle = PS_SOLID, COLORREF color = 0x00ffffff, int iSize = 0, int nDataSize = 0 );
	inline int AddLine( const LINESTYLE &lineStyle, int nDataSize = 0  );
	inline int AddLine( const LINESTYLE &lineStyle, const MARKERSTYLE &markStyle, int nDataSize = 0  );
	inline int AddLine( const CAXLineStyle &axlineStyle, int nDataSize = 0  );
	inline int AddLine( const CAXLineStyle &axlineStyle, const CAXMarkerStyle &axmarkStyle, int nDataSize = 0  );
//	inline int AddLine( CAXPlotStyle &plotStyle, int nDataSize = 0  );
	// デ�`タサイズの�O協
	inline void SetDataSize( int nDataSize );
	// デ�`タの��茅
	inline void ClearAllData(void);
	inline void RemoveAllLine(void);
//200611 t.tachibana added start>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	inline void RemoveLine(int nIndex, int nCount = 1);
//200611 t.tachibana added end<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	// デ�`タ塘双勣殆の函誼
	inline CXYPlotData & operator []( int n );
	inline CXYPlotData & GetLine( int n );
	// デ�`タ塘双方
	inline int  GetLineNum(void);
	// 燕幣ライン方
	inline int  GetShowLineNum(void);

	// デ�`タ燕幣����
	void SetXScale( double dMin, double dMax, double dDelta = -1.0, double dDetailDelta = -1, BOOL bAllLayer = FALSE );
	void SetYScale( double dMin, double dMax, double dDelta = -1.0, double dDetailDelta = -1, BOOL bAllLayer = FALSE );
//200612 t.tachibana added start>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	void SetXScaleEx( double dMin, double dMax, double dDelta = -1.0, double dDetailDelta = -1, BOOL bAllLayer = FALSE, BOOL bRedraw = FALSE );
	void SetYScaleEx( double dMin, double dMax, double dDelta = -1.0, double dDetailDelta = -1, BOOL bAllLayer = FALSE, BOOL bRedraw = FALSE );
//200612 t.tachibana added end<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	//��方グラフ宙鮫
	void SetXLogScale(BOOL bLog = TRUE, BOOL bScaleAuto = TRUE );
	void SetYLogScale(BOOL bLog = TRUE, BOOL bScaleAuto = TRUE );
	// スクロ�`ル
	void  Scroll( double dScrollX, double dScrollY );
	// デ�`タのMin&Max匯凄クリア
	void ClearMinMax( void );

//******** �����C嬬 ********//
	///< マウス��寄�C嬬
	// グラフ��寄
	virtual void Zoom( CRect rectZoom );

	// 宙鮫
	virtual void DrawDC( CDC *pDC, CRect rect )				{	DrawGraph( pDC, rect );	}
	virtual void DrawExDC( CDC *pDC, const CRect &rect )	{	DrawLineCursor( pDC, rect );	}
	// グラフ宙鮫	
	virtual void DrawGraph( CDC *pDC, const CRect &rect );
	// カ�`ソル宙鮫
	virtual void DrawLineCursor( CDC *pDC, const CRect &rect );
	// 壅燕幣
	inline void Redraw(BOOL bRedraw = FALSE);
};
/////////////////////////////////////////////////////////////////////////////
// inline finction
/////////////////////////////////////////////////////////////////////////////
// CAXGraphCtrl
///////////////////////////////////////
/**
 * 	コピ�`.
 * 		嚥えられたグラフのデ�`タをコピ�`する
 * 
 * 	@param src	コピ�`圷グラフ
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
 * 	すべての秤�鵑離�リア.
 *
 */
inline void CAXGraphCtrl::ClearAllItem(void)
{
	ClearAllData();
	CAXGDIPlotCtrl::ClearAllItem();
}
///////////////////////////////////////
/**
 * 	すべての秤�鵑力�茅.
 *
 */
inline void CAXGraphCtrl::RemoveAllItem(void)
{
	//ClearActiveInfo(&m_activeInfo);	///< Active彜�Bの秤�鵑離�リア
	RemoveAllLine();					//デ�`タのクリア
	CAXGDIPlotCtrl::RemoveAllItem();
}
///////////////////////////////////////
/**
 * 	��を弖紗する.
 * 
 * 	@param	iStyle		���N
 * 	@param	color		��弼
 * 	@param	iSize		��サイズ
 *	@param	nDataSize	デ�`タサイズ
 * 	@return				弖紗した��の��桑催 0゛
 */
int CAXGraphCtrl::AddLine( int iStyle /*= PS_SOLID*/, COLORREF color /*= 0x00ffffff*/, int iSize /*= 0*/, int nDataSize /*= 0*/)
{
	int index = m_plotData.Add( CXYPlotData( iStyle, color, iSize ) );
	m_plotData[index].SetSize( nDataSize );
	return index;
}
///////////////////////////////////////
/**
 * 	��を弖紗する.
 * 
 * 	@param lineStyle	ラインスタイル
 * 	@param markStyle	マ�`カ�`スタイル
 *	@param	nDataSize	デ�`タサイズ
 * 	@return				弖紗した��の��桑催 0゛
 */
int CAXGraphCtrl::AddLine( const LINESTYLE &lineStyle, int nDataSize /*= 0*/)
{
	int index = m_plotData.Add( CXYPlotData( lineStyle ) );
	m_plotData[index].SetSize( nDataSize );
	return index;
}
///////////////////////////////////////
/**
 * 	��を弖紗する.
 * 
 * 	@param lineStyle	ラインスタイル
 * 	@param markStyle	マ�`カ�`スタイル
 *	@param	nDataSize	デ�`タサイズ
 * 	@return				弖紗した��の��桑催 0゛
 */
int CAXGraphCtrl::AddLine( const LINESTYLE &lineStyle, const MARKERSTYLE &markStyle, int nDataSize /*= 0*/ )
{
	int index = m_plotData.Add( CXYPlotData( lineStyle, markStyle ) );
	m_plotData[index].SetSize( nDataSize );
	return index;
}
///////////////////////////////////////
/**
 * 	��を弖紗する.
 * 
 * 	@param axlineStyle	ラインスタイルクラス
 *	@param	nDataSize	デ�`タサイズ
 * 	@return				弖紗した��の��桑催 0゛
 */
int CAXGraphCtrl::AddLine( const CAXLineStyle &axlineStyle, int nDataSize /*= 0*/  )
{
	int index = m_plotData.Add( CXYPlotData( axlineStyle ) );
	m_plotData[index].SetSize( nDataSize );
	return index;
}
///////////////////////////////////////
/**
 * 	��を弖紗する.
 * 
 * 	@param axlineStyle	ラインスタイルクラス
 * 	@param axmarkStyle	マ�`カ�`スタイルクラス
 *	@param	nDataSize	デ�`タサイズ
 * 	@return				弖紗した��の��桑催 0゛
 */
int CAXGraphCtrl::AddLine( const CAXLineStyle &axlineStyle, const CAXMarkerStyle &axmarkStyle, int nDataSize /*= 0*/  )
{
	int index = m_plotData.Add( CXYPlotData( axlineStyle, axmarkStyle ) );
	m_plotData[index].SetSize( nDataSize );
	return index;
}
///////////////////////////////////////
/**
 * 	デ�`タサイズを�O協する.
 * 		�O協したデ�`タサイズの�I囃を�_隠する。
 *	
 *	@param		nDataSize	�O協するデ�`タサイズ
 * 	@return		�I囃を�_隠したデ�`タサイズ
 */
inline void CAXGraphCtrl::SetDataSize( int nDataSize )
{
	//for(int index = 0; index < GetLineNum(); index++ )	{
		m_plotData/*[index].*/.SetSize( nDataSize );
	//}
}
///////////////////////////////////////
/**
 * 	すべての��をデ�`タをクリアする.
 * 		すべての��式びデ�`タをクリアします。
 */
void CAXGraphCtrl::ClearAllData(void)
{
	for(int index = 0; index < GetLineNum(); index++ )	{
		m_plotData[index].ClearAllPoint();
	}
}
///////////////////////////////////////
/**
 * 	すべての��を��茅する.
 * 		すべての��式びデ�`タを��茅します。書まで弖紗したライン桑催は畠て�o�燭砲覆蠅泙后�
 */
void CAXGraphCtrl::RemoveAllLine(void)
{
	m_plotData.RemoveAll();
}
//200611 t.tachibana added start>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
///////////////////////////////////////
/**
 * 	indexで峺協した��を��茅する.
 *		!!!!塘双勣殆方のチェックは、クラスの翌�箸拝瞰Rする駅勣が嗤る!!!!
 * 	@param nIndex	0 參貧で、GetUpperBound が卦す�ﾒ塹造燐�方のインデックス。
 * 	@param nCount	��茅する勣殆方。
 *	
 */
inline void CAXGraphCtrl::RemoveLine(int nIndex, int nCount/* = 1*/)
{
	m_plotData.RemoveAt(nIndex, nCount);
}
//200611 t.tachibana added end<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///////////////////////////////////////
/**
 * 	プロットデ�`タ函誼.
 * 	@param n	��桑催
 * 	@return		プロットデ�`タクラスのポインタ
 */
inline CXYPlotData & CAXGraphCtrl::operator []( int n )
{
	return m_plotData[n];
}
///////////////////////////////////////
/**
 * 	プロットデ�`タ函誼.
 * 	@param n	��桑催
 * 	@return		プロットデ�`タクラスのポインタ
 */
inline CXYPlotData & CAXGraphCtrl::GetLine( int n )
{
	return m_plotData[n];
}
///////////////////////////////////////
/**
 * 	��方の函誼.
 * 		�O協されている��の方を函誼する
 * 
 * 	@return	�O協されている��の方
 */
inline int CAXGraphCtrl::GetLineNum( void )
{
	return m_plotData.GetUpperBound()+1;
}
///////////////////////////////////////
/**
 * 	燕幣嶄の��方の函誼.
 * 		�O協されている燕幣嶄の��の方を函誼する
 * 
 * 	@return	�O協されている燕幣嶄の��の方
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
 * 	壅燕幣.
 * 		グラフを壅燕幣する。
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
 * 	マウスでのグラフ��寄�C嬬を�O協する.
 * 
 * 	@param iZoom	��寄�C嬬を�O協する
 *		ZOOM_OFF = 0,
 *		XY_ZOOM,		///<X圭�髻�Y圭�鬚��I圭�鬚���寄
 *		X_ZOOM,			///<X圭����寄
 *		Y_ZOOM,			///<Y圭����寄
 * 	@return			�S辛彜�Bを卦す。
 */
//inline int CAXGraphCtrl::EnableMouseZoom ( int iZoom /*= XY_ZOOM*/ )
/*
{
	if(IsEnableActivate())	{
		if(m_iMouseZoom == XY_ZOOM || m_iMouseZoom == X_ZOOM || m_iMouseZoom == Y_ZOOM  )	{
			m_iMouseZoom = iZoom;	///< マウス��寄�C嬬ON/OFFフラグ
		}
	}
	return m_iMouseZoom;
}
///////////////////////////////////////
/**
 * 	マウスでのグラフ��寄�C嬬をON/OFFする.
 * 
 * 	@return			グラフ��寄�C嬬�S辛彜�Bを卦す。
 *
inline int CAXGraphCtrl::GetMouseZoom ( void )
{
	return m_iMouseZoom;
}
///////////////////////////////////////
/**
 * 	マウスでのグラフ��寄�C嬬ON/OFFを函誼する.
 * 
 * 	@return		��寄�C嬬を嗤�織侫薀�
 *
inline BOOL CAXGraphCtrl::IsMouseZoom ()
{
	return	( m_iMouseZoom == ZOOM_OFF  ? FALSE : TRUE) ; 
}
*/
#endif // __GRAPHCTRL_H_INCLUDED__