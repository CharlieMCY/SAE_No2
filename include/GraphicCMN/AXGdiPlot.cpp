// AXGDIPlot.cpp : ヘッダー ファイル
//
/********************************************************
// クラスのインターフェイス
// CAXPlotStyle		:PLOTスタイルクラス
// CAXGDIPlotCtrl	:AXGDIプロット用描画クラス
//												by YOTSUTSU
//	* History	:	date:2005,15,Jul.	新規作成
ver.1.00	
********************************************************/
#include "stdafx.h"
#include "AXGDIPlot.h"

/////////////////////////////////////////////////////////////////////////////
// CAXGDIPlotCtrl
//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////
// コンストラクション
CAXGDICursor::CAXGDICursor( void )
{
	Initialize();
}
///////////////////////////////////////
/**
 * 	コンストラクタ
 * 		AXCURSORINFOの情報を元に構築する
 * 
 * 	@param org	コピー元CAXGDICursor
 */
CAXGDICursor::CAXGDICursor( const AXCURSORINFO & cursorInfo )
{
	Initialize();
	m_cursorInfo.wCusorStyle = cursorInfo.wCusorStyle; ///< Cursor style
	m_cursorInfo.iLayer = cursorInfo.iLayer;			///< DataLayer index
	m_cursorInfo.iPos = cursorInfo.iPos;				///< カーソル位置
	m_cursorInfo.xyValue = cursorInfo.xyValue;			///< 値指定
	SetString(cursorInfo.szName);						///< 名称
}	
///////////////////////////////////////
/**
 * 	コピーコンストラクタ
 * 		元のCAXGDICursorを元に構築する
 * 
 * 	@param org	コピー元CAXGDICursor
 */
CAXGDICursor::CAXGDICursor( const CAXGDICursor &org )
{	
	operator=( org );
}
///////////////////////////////////////
//デコンストラクタ
CAXGDICursor::~CAXGDICursor( void )
{
}
///////////////////////////////////////
/**
 * 	初期化関数
 * 
 * 	@param
 */
void CAXGDICursor::Initialize( void )
{
	size_t size = sizeof(AXCURSORINFO);
	memset(&m_cursorInfo,0x00,size);
	m_cursorInfo.wSize = size;///< Specifies the size, in bytes, of this structure.
	SetCursorMode( CURSORNONE );		///< カーソル無し
	ShowCursor(TRUE);					///< 表示/非表示フラグ
	m_cursorInfo.iLayer = -1;				///< DataLayer index
	m_cursorInfo.iPos = -1;					///< カーソル位置
	m_cursorInfo.xyValue.dX = 0.0;			///< 値指定
	m_cursorInfo.xyValue.dY = 0.0;			///< 値指定
	
	memset( m_cursorInfo.szName, _T('\0') ,sizeof(m_cursorInfo.szName));	///< カーソルの名前

//	m_pAXGdiCtrl = NULL;	///< CAXGDICtrlのポインタ
}
///////////////////////////////////////
/**
 * 	コピーオペレータ
 * 
 * 	@param org	コピー元CAXGDICursor
 */
CAXGDICursor & CAXGDICursor::operator=( const CAXGDICursor &src )
{
	m_cursorInfo.iLayer = src.m_cursorInfo.iLayer;		///< DataLayer index
	m_cursorInfo.iPos = src.m_cursorInfo.iPos;				///< カーソル位置
	m_cursorInfo.xyValue = src.m_cursorInfo.xyValue;		///< 値指定
	///< カーソルモード CURSORX:'X' X軸カーソル / CURSORY:'Y' Y軸カーソル / CURSORCROSS:'+' 十字カーソル
	//m_cursorInfo.wCusorStyle = src.m_cursorInfo.wCusorStyle;
	SetCursorMode(src.GetCursorMode());
	ShowCursor(src.IsShowCursor());
	ShowActiveMark(src.IsShowActiveMark());

	SetString(src.m_cursorInfo.szName);		///< カーソルの名前

	return (*this);
}
///////////////////////////////////////
/**
 * 	カーソル名称の描画
 * 
 * 	@param pDC			描画するデバイスコンテキストのポインタ
 * 	@param rect			描画領域の範囲
 *	@param point		描画する座標
 *	@param iCursorMode　カーソルモード CURSORX:'X' X軸カーソル / CURSORY:'Y' Y軸カーソル / CURSORCROSS:'+' 十字カーソル
 *	@param lpszName		描画する文字列
 *	@param color		描画するテキストカラー
 */
void CAXGDICursor::DrawCursorName( CDC *pDC, const CRect &rect, CPoint point, int iCursorMode, LPCTSTR lpszName, COLORREF color )
{
	if(lpszName == NULL)	{	return;	}
	if(0 < _tcslen(lpszName))	{//文字がセットされていれば、
		// 背景モードの変更
		int iBkMode = pDC->SetBkMode( TRANSPARENT );
		// カラーの設定
		COLORREF oldTextColor = pDC->SetTextColor( color );
		// 正確な描画位置の取得
		CSize strSize = pDC->GetTextExtent( lpszName );
		// カーソル名称描画
		if( CURSORX == iCursorMode )	{
			pDC->TextOut( point.x/*iX*/ - strSize.cx / 2, point.y/*0*/, lpszName );
		}	else if( CURSORY == iCursorMode )	{
			pDC->TextOut( point.x/*rect.right*/ - strSize.cx , point.y/*iY*/ - strSize.cy , lpszName );
		}	else	{
			pDC->TextOut( point.x/*iX*/ - strSize.cx / 2, point.y/*0*/, lpszName );
		}	
		// カラーを戻す
		pDC->SetTextColor( oldTextColor );
		// 背景モードを戻す
		pDC->SetBkMode( iBkMode );
	}
}
/////////////////////////////////////////////////////////////////////////////
// CAXPlotCursor
///////////////////////////////////////
/**
 * 	カーソルの描画
 * 
 * 	@param pDC			描画するデバイスコンテキストのポインタ
 * 	@param rect			描画領域の範囲
 *	@param point		描画する座標
 *	@param bMonochrome	モノクローム描画フラグ
 */
void CAXPlotCursor::DrawCursor( CDC *pDC, const CRect &rect, CPoint point, BOOL bMonochrome )
{
	//描画色
	COLORREF	color = GetLineColor();
	//モノクロ
	if(bMonochrome)	{ color = IBLACK;	} 
	// ペンの作成
	CLinePen pen;
	int penStyle = GetLineStyle().iStyle;
	if( GetLineStyle().iStyle == PS_NULL && MARKNONE !=  GetMarkerStyle().iMarker)	{
		penStyle = PS_SOLID;
	}
	pen.CreatePen( penStyle, GetLineSize(), color );
	// ペンの選択
	CPen *pOldPen = pDC->SelectObject( &pen );
	
	// ブラシの作成
	CBrush	brush( color );
	
	if( GetPenStyle() != PS_NULL )	{
		const int c_iActiveMarkSize = 6;
		// Xカーソル描画
		if( GetCursorMode() == CURSORX || GetCursorMode() == CURSORCROSS ){
			pDC->MoveTo( point.x, 0 );
			pDC->LineTo( point.x, rect.Height() + 1 );
			int iSize = 0;
			if(IsShowActiveMark())	{
				// ブラシの選択
				CBrush *oldBrush = pDC->SelectObject( &brush );
				if(pDC->IsPrinting())	{	//印刷用
					iSize = MulDiv(c_iActiveMarkSize, pDC->GetDeviceCaps(LOGPIXELSY), 72);
				}	else	{
					iSize = c_iActiveMarkSize;
				}
				DrawActiveMark( pDC, rect, point, CURSORX, iSize );
				// ブラシを戻す
				pDC->SelectObject( oldBrush );
			}
			DrawCursorName( pDC, rect, CPoint(point.x, iSize ), CURSORX, GetString(), color );
		}
		// Yカーソル描画
		if( GetCursorMode() == CURSORY || GetCursorMode() == CURSORCROSS ){
			pDC->MoveTo( 0, point.y );
			pDC->LineTo( rect.Width() + 1, point.y );
			int iSize = 0;
			if(IsShowActiveMark())	{
				// ブラシの選択
				CBrush *oldBrush = pDC->SelectObject( &brush );
				if(pDC->IsPrinting())	{	//印刷用
					iSize = MulDiv(c_iActiveMarkSize, pDC->GetDeviceCaps(LOGPIXELSY), 72);
				}	else	{
					iSize = c_iActiveMarkSize;
				}
				DrawActiveMark( pDC, rect, point, CURSORY, iSize );
				// ブラシを戻す
				pDC->SelectObject( oldBrush );
			}
			if( GetCursorMode() == CURSORY )	{	
				DrawCursorName( pDC, rect, CPoint(rect.Width() - iSize, point.y), CURSORY, GetString(), color );
			}
		}
	}

	if(GetMarkerKind() != MARKNONE )	{
		// ブラシの選択
		CBrush *oldBrush = NULL;
		if( GetMarkerBkStyle() == 0 ) {
			oldBrush = (CBrush *)pDC->SelectStockObject( NULL_BRUSH );
		}	else	{
			oldBrush = pDC->SelectObject( &brush );
		}

		//サイズの決定
		int iSize = GetMarkerSize();

		if(pDC->IsPrinting())	{	//印刷用
			iSize = MulDiv(iSize, pDC->GetDeviceCaps(LOGPIXELSY), 72);
		}
		//マーカー描画
		::DrawMark( pDC, GetMarkerKind(), point, iSize );

		// ブラシを戻す
		pDC->SelectObject( oldBrush );
	}

	// ブラシの破棄
	brush.DeleteObject();

	// ペンを戻す
	pDC->SelectObject( pOldPen );

	// ペンの破棄
	pen.DeleteObject();

}
/**
 * 	カーソルActiveMark描画
 * 
 * 	@param pDC			描画するデバイスコンテキストのポインタ
 * 	@param rect			描画領域の範囲
 *	@param pos			描画する座標
 *	@param iCursorMode	X:CURSORX/Y:CURSORY
 *	@param iSize		ActiveMarkのサイズ
 */
void CAXPlotCursor::DrawActiveMark( CDC *pDC, const CRect &rect, CPoint pos, int iCursorMode, int iSize )
{
	// マーク
	POINT point[3];
	if(iCursorMode == CURSORX)	{
		// ▽
		point[0].x = pos.x;			point[0].y = iSize;
		point[1].x = pos.x - iSize;	point[1].y = 0;
		point[2].x = pos.x + iSize;	point[2].y = 0;
		pDC->Polygon( point, 3 );
		// △
		point[0].x = pos.x;			point[0].y = rect.Height() - iSize;
		point[1].x = pos.x - iSize;	point[1].y = rect.Height();
		point[2].x = pos.x + iSize;	point[2].y = rect.Height();
		pDC->Polygon( point, 3 );

	}	else
	if(iCursorMode == CURSORY)	{
		// ▽
		point[0].x = iSize;		point[0].y = pos.y;
		point[1].x = 0;			point[1].y = pos.y + iSize;
		point[2].x = 0;			point[2].y = pos.y - iSize;
		pDC->Polygon( point, 3 );
		// △
		point[0].x = rect.Width() - iSize;	point[0].y = pos.y;
		point[1].x = rect.Width();			point[1].y = pos.y + iSize;
		point[2].x = rect.Width();			point[2].y = pos.y - iSize;
		pDC->Polygon( point, 3 );
	}
}
/////////////////////////////////////////////////////////////////////////////
// CAXAreaCursor
///////////////////////////////////////
/**
 * 	エリアカーソル名称の描画
 * 
 * 	@param pDC			描画するデバイスコンテキストのポインタ
 * 	@param rect			描画領域の範囲
 *	@param bMonochrome	モノクローム描画フラグ
 */
void CAXAreaCursor::DrawAreaCursorName( CDC *pDC, const CRect &rect, BOOL bMonochrome )
{
	//if(0 < _tcslen(GetString()))	{//文字がセットされていれば、
	if(!GetString().IsEmpty())	{//文字がセットされていれば、
		// フォント色を設定
		COLORREF TextColor = GetPatternColor();

		switch(GetBrushStyle())	{
		case BS_HATCHED:	break;
		case BS_SOLID:
		default:
			TextColor = ~GetPatternColor();//GetBkColor();
			break;
		}

		//モノクロ
		if(bMonochrome)	{ 	TextColor = IBLACK;	}
	
		// 背景モードの変更
		int iBkMode = pDC->SetBkMode( TRANSPARENT );
		// カラーの設定
		COLORREF oldTextColor = pDC->SetTextColor( TextColor );
		// 正確な描画位置の取得
		CSize strSize = pDC->GetTextExtent( GetString() );
		// カーソル名称描画
		if( GetCursorMode() == CURSORX ){
			pDC->TextOut( (rect.left + rect.right - strSize.cx) / 2, rect.top, GetString() );
		}	else if( GetCursorMode() == CURSORY )	{
			pDC->TextOut( rect.right - strSize.cx, (rect.top + rect.bottom - strSize.cy) / 2, GetString() );
		}	else if( GetCursorMode() == CURSORCROSS)	{
			pDC->TextOut( (rect.left + rect.right - strSize.cx) / 2, 
				(rect.top + rect.bottom - strSize.cy) / 2, GetString() );
		}
		// カラーを戻す
		pDC->SetTextColor( oldTextColor );
		// 背景モードを戻す
		pDC->SetBkMode( iBkMode );
	}
}
///////////////////////////////////////
/**
 * 	エリアカーソルの描画
 * 
 * 	@param pDC			描画するデバイスコンテキストのポインタ
 * 	@param rect			描画領域の範囲
 *	@param bMonochrome	モノクローム描画フラグ
 */
void CAXAreaCursor::DrawPattern( CDC *pDC, const CRect &rect, BOOL bMonochrome )
{
	//描画色
	COLORREF	color = GetPatternColor();
	//モノクロ
	if(bMonochrome)	{ color = Color2Gray( GetPatternColor() );	} 

	// ペンの作成
	CPen pen;
	pen.CreatePen( PS_SOLID, 0, color );
	// ペンの選択
	CPen *pOldPen = pDC->SelectObject( &pen );
	// ブラシの作成
	CBrush	brush;
	int iHatchStyle = GetHatchStyle();
	switch( GetBrushStyle())	{
	case BS_HATCHED:
		switch(iHatchStyle)	{
		case HS_HORIZONTAL:	break;	// 0       /* ----- */
		case HS_VERTICAL:	break;	// 1       /* ||||| */
		case HS_FDIAGONAL:	break;	// 2       /* \\\\\ */
		case HS_BDIAGONAL:	break;	// 3       /* ///// */
		case HS_CROSS:		break;	// 4       /* +++++ */
		case HS_DIAGCROSS:	break;	// 5       /* xxxxx */
		default:
			iHatchStyle = HS_HORIZONTAL;
			break;
		}		
		brush.CreateHatchBrush(iHatchStyle,	color);
		break;
	case BS_SOLID:
	default:
	//	TextColor = ~areaInfo.color;GetBkColor();
		brush.CreateSolidBrush(color);
		break;
	}

	// ブラシの選択
	CBrush *pOldBrush = pDC->SelectObject( &brush );

	pDC->Rectangle( rect );

	// ブラシを戻す
	pDC->SelectObject( pOldBrush );
	// ブラシの破棄
	brush.DeleteObject();
		// ペンを戻す
	pDC->SelectObject( pOldPen );
	// ペンの破棄
	pen.DeleteObject();

}
/////////////////////////////////////////////////////////////////////////////
// CAXGDIPlotCtrl
//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////
CAXGDIPlotCtrl::CAXGDIPlotCtrl(COLORREF bkColor /*= IBLACK*/)
	: m_axisX(MEASUREX), m_axisY(MEASUREY)
{
	SetBkColor(bkColor);
	
	///< モノクローム表示フラグ
	EnableMonochrome(FALSE);

	m_axisX.ShowMeasureMinMax(FALSE,FALSE);
	m_axisY.ShowMeasureMinMax(FALSE,FALSE);

	m_axisY.SetMeasureAngle(0);

//	m_dMeasureRatio = 0.02;		///< 軸目盛りの全体に対する比率
	m_byStyleXCross = 0;		///< 軸交差有効(0:Min/1:Max/2:Center/3:データ値指定)
	m_byStyleYCross = 0;		///< 軸交差有効(0:Min/1:Max/2:Center/3:データ値指定)
	m_dAxisXCross = 0.0;		///< 軸交差ポイント(データ値指定)
	m_dAxisYCross = 0.0;		///< 軸交差ポイント(データ値指定)

	m_byShowPlotScaleX = 0;	///< プロットデータのスケールを表示有効（X軸）
	m_byShowPlotScaleY = 0;	///< プロットデータのスケールを表示有効（Y軸）
	m_byPlotNameShowMode = 0;	///< プロットデータ名称の表示有効
	SetShowModePlotName(AX_GDIXMODE);

	m_iCursorFontSize = -1;		// カーソルフォントサイズ
	m_iAreaCsrFontSize = -1;	// エリアカーソルフォントサイズ

	ShowGridX( FALSE, PS_SOLID, ~bkColor, 0 );
	ShowGridY( FALSE, PS_SOLID, ~bkColor, 0 );

	Initialize();	//初期化

	m_bRedraw = TRUE;///< 再描画フラグ

}
/**
 * 	コピーコンストラクタ
 * 
 * 	@param org	コピー元CAXGDIPlotCtrlクラス
 */
CAXGDIPlotCtrl::CAXGDIPlotCtrl( CAXGDIPlotCtrl &org )
{
	operator=( org );
}
/// デストラクタ
CAXGDIPlotCtrl::~CAXGDIPlotCtrl()
{
	DestroyWindow();
	RemoveAllItem();
}
BEGIN_MESSAGE_MAP(CAXGDIPlotCtrl, CAXGDICtrl)
	//{{AFX_MSG_MAP(CAXGDIPlotCtrl)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK() 
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CAXGDIPlotCtrl メッセージ ハンドラ
///////////////////////////////////////
/// ウィンドウ作成時のメッセージハンドラ
void CAXGDIPlotCtrl::PreSubclassWindow() 
{
	CAXGDICtrl::PreSubclassWindow();

	// メモリビットマップ&ビットマップDCの作成
    CDC* pDC = GetDC();
	m_bitmap.CreateCompatibleBitmap( pDC, m_wndSize.cx, m_wndSize.cy );
	m_bmpDC.CreateCompatibleDC( pDC );
	m_bmpDC.SelectObject( m_bitmap );
	ReleaseDC( pDC );

	m_zoomScale.RemoveAll();

//	ModifyStyle( 0, SS_NOTIFY|WS_CHILD );
}
///////////////////////////////////////
/// ウィンドウ破棄時のメッセージハンドラ
void CAXGDIPlotCtrl::OnDestroy() 
{
	CAXGDICtrl::OnDestroy();

	// メモリビットマップ&ビットマップDCの破棄
	m_bmpDC.DeleteDC();
	m_bitmap.DeleteObject();
	m_zoomScale.RemoveAll();
}
///////////////////////////////////////
/// サイズ変更のメッセージハンドラ
void CAXGDIPlotCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CAXGDICtrl::OnSize(nType, cx, cy);

	// メモリビットマップ&ビットマップDCの破棄
	m_bmpDC.DeleteDC();
	m_bitmap.DeleteObject();

	// メモリビットマップ&ビットマップDCの再作成
    CDC* pDC = GetDC();
	m_bitmap.CreateCompatibleBitmap( pDC, cx, cy );
	m_bmpDC.CreateCompatibleDC( pDC );
	m_bmpDC.SelectObject( m_bitmap );
	ReleaseDC( pDC );

	m_bRedraw = TRUE;
}
////////////////////////////////////////////////////
void CAXGDIPlotCtrl::OnPaint() 
{
	CPaintDC dc(this); // 描画用のデバイス コンテキスト
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	// 描画用メッセージとして CStatic::OnPaint() を呼び出してはいけません
	//get rect size
//	CRect rectWnd;
	CRect rectItem;
	GetClientRect( &rectItem );
//	GetClientRect( &rectWnd );
	//rectItem = rectWnd;
//	SubcalcRect(rectItem);;
	// 描画原点設定
	// これでうまくいくようだ。MSDNよんでもよーわからん。
	CPoint oldWndOrg = dc.SetWindowOrg( 0,0 );//rectItem.left, rectItem.top );
	// フォントの取得
	LOGFONT logfont;
	GetParent()->GetFont()->GetLogFont( &logfont );

	// フォントの作成?選択
	CFont font;
	font.CreateFontIndirect( &logfont );
	CFont *pOldFont = dc.SelectObject( &font );

	// クリッピング
	CRect clipRect;
	dc.GetClipBox( clipRect );
	dc.IntersectClipRect( rectItem );

	//描画前処理
	BeginPaintDC( &dc, rectItem );

	if( m_bRedraw ) {
		//if(!IsMarginRectNull())	{
		//	m_bmpDC.FillSolidRect( rectWnd, ICTRLCOLOR );
		//}
		CFont *pOldbmpFont = m_bmpDC.SelectObject( &font );
		DrawDC( &m_bmpDC, rectItem );
		m_bmpDC.SelectObject( pOldbmpFont );
	}
	// ????????描画
	//dc.BitBlt( -rectWnd.left, -rectWnd.top, rectWnd.Width(), rectWnd.Height(), &m_bmpDC, 0, 0, SRCCOPY );
	dc.BitBlt( rectItem.left, rectItem.top, rectItem.Width(), rectItem.Height(), &m_bmpDC, 0, 0, SRCCOPY );

	//拡張描画
	DrawExDC( &dc, rectItem );
	
	//Activeな状態を描画
	DrawActiveState( &dc, rectItem );

	// 描画後処理
	EndPaintDC( &dc, rectItem );

	// クリップ領域を元に戻す
	dc.SelectClipRgn( NULL );
	dc.IntersectClipRect( clipRect );

	// フォントを戻す
	dc.SelectObject( pOldFont );
	font.DeleteObject();
	
	// 原点を戻す
	dc.SetWindowOrg( oldWndOrg );
	// Drawフラグリセット
	m_bRedraw = FALSE;
}
////////////////////////////////////////////////////
/// マウス左ボタン押下の時のメッセージハンドラ(グラフ拡大領域描画始点用)
void CAXGDIPlotCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// 拡大領域を更新
	m_guideRect.left  = point.x;
	m_guideRect.top   = point.y;
	m_guideRect.right = point.x;
	m_guideRect.bottom= point.y;

	// マウス拡大可？
	m_bZooming = IsMouseZoom();

	// マウスの移動領域を制限
	if( m_bZooming ){
		CRect graphRect;
		GetWindowRect( graphRect );
		ClipCursor( graphRect );
		// 拡大領域の始点を表示
		if(XY_ZOOM != GetMouseZoom())	{
			// 拡大領域の枠を描画
			CDC* pDC = GetDC();
			CBrush *pOldBrush = (CBrush *)pDC->SelectStockObject( NULL_BRUSH );
			int iOldRop = pDC->SetROP2( R2_NOT );
			if(X_ZOOM == GetMouseZoom())	{
				pDC->MoveTo( point.x, point.y - 5);
				pDC->LineTo( point.x, point.y  );
				pDC->MoveTo( point.x, point.y + 2);
				pDC->LineTo( point.x, point.y + 7 );	
			}	else	{
				pDC->MoveTo( point.x -5, point.y );
				pDC->LineTo( point.x , point.y );
				pDC->MoveTo( point.x + 2, point.y );
				pDC->LineTo( point.x + 7, point.y );
			}
			pDC->SetROP2( iOldRop );
			pDC->SelectObject( pOldBrush );
			ReleaseDC( pDC );
		}
	}	else	{
		if( GetSafeHwnd() && (GetFocus() == this) )	{
			CRect graphRect;
			GetClientRect( graphRect );
//			GetDrawRect( &graphRect );
			if(graphRect.PtInRect(point))	{
				graphRect.bottom -= 1;
				graphRect.right -= 1;
				///< 0:非選択/1:全体/2:データ/3:カーソル/4:エリアカーソル
				//m_activeInfo.nActive = AXGCTRLACT_NONE;
				AXGCACTINFO tempActiveInfo = m_activeInfo;
				CPoint ptGraph;
				ptGraph.x = point.x - graphRect.left;
				ptGraph.y = point.y - graphRect.top;
				MouseLBdownActivate( graphRect, ptGraph, &tempActiveInfo );
				if(tempActiveInfo.nActive != m_activeInfo.nActive
					|| tempActiveInfo.iLayer != m_activeInfo.iLayer
					|| tempActiveInfo.iLine != m_activeInfo.iLine
					|| tempActiveInfo.iIndex != m_activeInfo.iIndex )	{
					NotifyToParent(AXGCN_CHANGE_ACTIVE, &tempActiveInfo);
				}
			}
		}
	}

	CAXGDICtrl::OnLButtonDown(nFlags, point);
}
///////////////////////////////////////
// マウス左ボタンダブルクリック押下の時のメッセージハンドラ
void CAXGDIPlotCtrl::OnLButtonDblClk( UINT nFlags, CPoint point )
{
	if( GetSafeHwnd() && (GetFocus() == this))	{
		///< 0:非選択/1:全体/2:データ/3:カーソル/4:エリアカーソル
		if(m_activeInfo.nActive == AXGCTRLACT_DATA)	{
			NotifyToParent( AXGCN_CHANGE_STYLE );
		}	else if(m_activeInfo.nActive == AXGCTRLACT_CURSOL)	{
			NotifyToParent( AXGCN_CHANGE_STYLE );
		}
	}
	CAXGDICtrl::OnLButtonDblClk(nFlags, point);
}
///////////////////////////////////////
/// マウス左ボタン離した時のメッセージハンドラ(グラフ拡大描画用)
void CAXGDIPlotCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// マウスの制限を解除
	ClipCursor( NULL );
	if( m_bZooming ){
		// 拡大領域を更新
		m_guideRect.right = point.x;
		m_guideRect.bottom= point.y;
		m_guideRect.NormalizeRect();
		if(m_guideRect.Height() > 2 && m_guideRect.Width() > 2)	{
			// 拡大
			Zoom( m_guideRect );
		}	else	{
			Redraw(FALSE);
		}
		m_bZooming = FALSE;

	}
	//else if(m_bCursorActivate)	{	m_bCursorActivate = FALSE;	}
	CAXGDICtrl::OnLButtonUp(nFlags, point);
}
///////////////////////////////////////
/// マウス移動中のメッセージハンドラ(グラフ拡大領域描画用)
void CAXGDIPlotCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( nFlags == MK_LBUTTON){//マウスの左ボタンが押されている場合にセットします。
		if( m_bZooming){
			CRect beforeRect = m_guideRect;
			
			// 拡大領域を更新
			if(Y_ZOOM != GetMouseZoom())	{			
				m_guideRect.right = point.x;
			}	else	{
				m_guideRect.right = m_guideRect.left + 2;
			}
			if(X_ZOOM != GetMouseZoom())	{
				m_guideRect.bottom= point.y;
			}	else	{
				m_guideRect.bottom= m_guideRect.top + 2;
			}

			CRect afterRect = m_guideRect;

			// 拡大領域の枠を描画
			CDC* pDC = GetDC();
			CBrush *pOldBrush = (CBrush *)pDC->SelectStockObject( NULL_BRUSH );
			int iOldRop = pDC->SetROP2( R2_NOT );
			pDC->Rectangle( beforeRect );
			pDC->Rectangle( m_guideRect );
			pDC->SetROP2( iOldRop );
			pDC->SelectObject( pOldBrush );
			ReleaseDC( pDC );
		}
		/*else if(m_bCursorActivate)	{
			int index = -1;
			for( int i = 0; i <= m_plotData.GetUpperBound(); i++ ){
				if(m_plotData[i].IsCursorShow())	{
					//int index = m_plotData[i].GetPos();
					CRect graphRect;
					GetWindowRect( graphRect );
					index = (int)(  m_plotData[i].GetXscale().dRange * point.x / graphRect.Width() + 0.5 );
					if(  0 > index || index > ((*m_plotData[i])->GetUpperBound()) ) break;
					TRACE("CursorMove %d \n",index);
				}
			}
		}*/
	}
	CAXGDICtrl::OnMouseMove(nFlags, point);
}
/////////////////////////////////////////////////////////////////////////////
// private
///////////////////////////////////////
/**
 * 	初期化.
 */
void CAXGDIPlotCtrl::Initialize( void )
{
	m_bZooming = FALSE;			///< 拡大中フラグ
	m_iMouseZoom = ZOOM_OFF;	///< マウス拡大機能
	m_guideRect.SetRectEmpty();	///< 拡大領域

}
/////////////////////////////////////////////////////////////////////////////
// protected
/**
 * 	グリッドを書く.
 * 		XまたはYのグリッドを描画する
 * 
 * 	@param pDC		描画するデバイスコンテキストのポインタ
 * 	@param iType	描画するグリッドのタイプ\n
 * 					GRIDX:X軸：	GRIDY:Y軸
 * 	@param rect		描画領域の範囲
 * 	@param gridInfo	描画するグリッドのグリッド情報
 */
void CAXGDIPlotCtrl::DrawGrid( CDC *pDC, int iType, const CRect &rect, const LINESTYLE &gridLine )
{
	// ペンの作成
	CLinePen pen;
	pen.CreatePen( gridLine.iStyle, gridLine.iSize,	(IsMonochrome() ? RGB(0,0,0) : gridLine.color) );

	// ペンの選択
	CPen *pOldPen = pDC->SelectObject( &pen );

	CAXMeasureStyle *pAxis = NULL;
	int iMode = 0;
	// 目盛りを書く(X)
	if( iType == GRIDX )
	{	
		iMode = MEASUREX;
		pAxis = (&m_axisX);
	}
	else if( iType == GRIDY )
	{	
		iMode = MEASUREY;
		pAxis = (&m_axisY);
	}
	// グリッド描画
	if(pAxis)	{
		if(pAxis->IsLogMode())	{
			pAxis->DrawLogScale( pDC, rect, iMode, pAxis->GetScaleType(), pAxis->GetMin(), pAxis->GetMax(), 100 );
		}	else	{
			if(pAxis->IsEnableDivDelta())	{//分割指定
				pAxis->DrawDivScale( pDC, rect, iMode, pAxis->GetScaleType(), pAxis->GetScaleDelta(), 0.0 , 0);
			}	else	{
				double dDeltaOrg = pAxis->GetMin();
				if(pAxis->IsDeltaOrgEnable())	{	dDeltaOrg = pAxis->GetDeltaOrg();	}
				pAxis->DrawScale( pDC, rect, iMode, pAxis->GetScaleType(), pAxis->GetMin(), pAxis->GetMax(), dDeltaOrg, pAxis->GetScaleDelta(), 0.0 , 0);//GetScaleDetailDelta() );
			}
		}
	}	
	// ペンを戻す
	pDC->SelectObject( pOldPen );

	// ペンの破棄
	pen.DeleteObject();
}
///////////////////////////////////////
/**
 * 	軸の目盛りを書く.
 * 		XまたはY軸の目盛りを描画する
 * 
 * 	@param pDC		描画するデバイスコンテキストのポインタ
 * 	@param rect		描画領域の範囲
 * 	@param measure	描画する目盛りクラス（CAXMeasureStyleクラス）
 */
void CAXGDIPlotCtrl::DrawMeasure( CDC *pDC, const CRect &rect, CAXMeasureStyle &measure )
{
	if(!measure.IsShowScale())	{	return;	}
	//最小目盛り長さ
//	const int c_iMinLen = 6;
	// ペンの作成
	CPen pen;
	pen.CreatePen( PS_SOLID, 1, (IsMonochrome() ? RGB(0,0,0) : measure.GetScaleColor()) );
	// ペンの選択
	CPen *pOldPen = pDC->SelectObject( &pen );

	//サイズの決定
	long length = CAXMeasureCtrl::c_iMeasureSise;
	const int c_iMargin = 2;
	long margin = length + c_iMargin;
//	if(GetInitSize().cx > GetInitSize().cy)	{
//		length = (long)(m_dMeasureRatio * GetInitSize().cx);
//	}	else	{
//		length = (long)(m_dMeasureRatio * GetInitSize().cy);
//	}	

//	if(length < c_iMinLen)	{	length = c_iMinLen;	}

	if(pDC->IsPrinting())	{	//印刷用
		length = MulDiv(CAXMeasureCtrl::c_iMeasureSise, pDC->GetDeviceCaps(LOGPIXELSY), 72);
		margin = MulDiv((CAXMeasureCtrl::c_iMeasureSise + c_iMargin), pDC->GetDeviceCaps(LOGPIXELSY), 72);
		//length = FtoL((double)length * rect.Height() / GetInitSize().cy );
	}

	CRect rectScale = rect;
		
	if( MEASUREX == measure.GetScaleMode())	{
		if(GetStyleXCross() == 1)	{
			rectScale.bottom = rectScale.top + length;
		}	else if(GetStyleXCross() == 2)	{
			rectScale.top = rect.CenterPoint().y - length + 1;
			rectScale.bottom = rect.CenterPoint().y + length + 1;
		}	else if(GetStyleXCross() == 3)	{
			int iY = GetAxisY().Data2PointY(m_dAxisXCross,rect.Height());
			rectScale.top = rect.top + iY - length/2;
			rectScale.bottom = rect.top + iY + length/2;
		}	else	{
			rectScale.top = rect.bottom - length;
		}
		//目盛り軸描画
		measure.DrawScale( pDC, rectScale );


		if(GetStyleXCross() == 2 || GetStyleXCross() == 3)	{
			//目盛り値描画
			rectScale.OffsetRect( 0, margin );
			measure.DrawMeasure( pDC, rectScale );
			CAXColorString *pAXString = (&measure.GetMaxSideAXString());
			CRect rectText = rectScale;
			CRect rectName = rectScale;
			if((pAXString->GetDTPosV() == DT_VCENTER))	{
				if((measure.IsShowMeasureDelta() && (pAXString->GetDTPosH() == DT_CENTER))
					|| (measure.IsShowMeasureMax() && (pAXString->GetDTPosH() == DT_RIGHT)))	{
					rectText.OffsetRect( 0, margin );
				}
			}	else if((pAXString->GetDTPosV() == DT_BOTTOM))	{
				rectText.OffsetRect( 0, margin );
			}	else	{
				rectText.OffsetRect( 0, -2*margin );
			}
			measure.DrawMeasureMaxString( pDC, rectText, IsMonochrome() );
			pAXString = (&measure.GetMinSideAXString());
			rectText = rectScale;
			if((pAXString->GetDTPosV() == DT_VCENTER))	{
				if((measure.IsShowMeasureDelta() && (pAXString->GetDTPosH() == DT_CENTER))
					|| (measure.IsShowMeasureMin() && (pAXString->GetDTPosH() == DT_LEFT)))	{
					rectText.OffsetRect( 0, margin );
				}
			}	else if((pAXString->GetDTPosV() == DT_BOTTOM))	{
				rectText.OffsetRect( 0, margin );
			}	else	{
				rectText.OffsetRect( 0, -2*margin );
			}
			measure.DrawMeasureMinString( pDC, rectText, IsMonochrome() );
			if(measure.GetNameAXString().GetDTPosV() == DT_TOP)	{
				rectName.OffsetRect( 0, -3*margin );
			//}	else if(measure.GetNameAXString().GetDTPosV() == DT_VCENTER)	{
			}	else	{
				rectName.OffsetRect( 0, 2*margin );
			}
			measure.DrawMeasureName( pDC, rectName, -1 );
		}
	} else if( MEASUREY == measure.GetScaleMode() )	{
		if(GetStyleYCross() == 1)	{
			rectScale.left = rect.right - length;
		}	else if(GetStyleYCross() == 2)	{
			rectScale.left = rect.CenterPoint().x - length + 1;
			rectScale.right = rect.CenterPoint().x + length + 1;
		}	else if(GetStyleYCross() == 3)	{
			int iX = GetAxisX().Data2PointX(m_dAxisYCross,rect.Width());
			rectScale.left = rect.left + iX - length/2;
			rectScale.right = rect.left + iX + length/2;
		}	else	{
			rectScale.right = rect.left + length;
		}
		//目盛り描画
		measure.DrawScale( pDC, rectScale );

		if(GetStyleYCross() == 2 || GetStyleYCross() == 3)	{
			//目盛り値描画
			rectScale.OffsetRect( -margin, 0 );
			measure.DrawMeasure( pDC, rectScale );

			CAXColorString *pAXString = (&measure.GetMaxSideAXString());
			CRect rectText = rectScale;
			CRect rectName = rectScale;
			if((pAXString->GetDTPosV() == DT_VCENTER))	{
				if((measure.IsShowDetailScale() && (pAXString->GetDTPosH() == DT_CENTER))
					|| (measure.IsShowMeasureMax() && (pAXString->GetDTPosH() == DT_RIGHT)))	{
					rectText.OffsetRect( -margin, 0 );
				}
			}	else if((pAXString->GetDTPosV() == DT_BOTTOM))	{
				rectText.OffsetRect( 2*margin, 0 );
			}	else	{
				rectText.OffsetRect( -margin, 0 );
			}
			measure.DrawMeasureMaxString( pDC, rectText, IsMonochrome() );
			pAXString = (&measure.GetMinSideAXString());
			rectText = rectScale;
			if((pAXString->GetDTPosV() == DT_VCENTER))	{
				if((measure.IsShowDetailScale() && (pAXString->GetDTPosH() == DT_CENTER))
					|| (measure.IsShowMeasureMin() && (pAXString->GetDTPosH() == DT_LEFT)))	{
					rectText.OffsetRect( -margin, 0 );
				}
			}	else if((pAXString->GetDTPosV() == DT_BOTTOM))	{
				rectText.OffsetRect( 2*margin, 0 );
			}	else	{
				rectText.OffsetRect( -margin, 0 );
			}
			measure.DrawMeasureMinString( pDC, rectText, IsMonochrome() );
			if(measure.GetNameAXString().GetDTPosV() == DT_TOP)	{
				rectName.OffsetRect( -2*margin, 0 );
			//}	else if(measure.GetNameAXString().GetDTPosV() == DT_VCENTER)	{
			}	else	{
				rectName.OffsetRect( 3*margin, 0  );
			}
			measure.DrawMeasureName( pDC, rectName, -1 );
		}
	}
	// ペンを戻す
	pDC->SelectObject( pOldPen );
	// ペンの破棄
	pen.DeleteObject();
}
///////////////////////////////////////
/**
 * 	プロットデータのスケールを書く.
 * 		与えられた情報でプロットデータのスケールを描画する。
 * 
 * 	@param pDC			描画するデバイスコンテキストのポインタ
 * 	@param rect			描画領域の範囲
 *	@param iXYMode		AX_XMODE:'X'X軸/AX_YMODE:'Y'Y軸
 * 	@param nIndex		描画するindex
 * 	@param nShowLine	描画するライン数
 *	@param color		描画色
 *	@param lpszString	表示文字列
 */
void CAXGDIPlotCtrl::DrawPlotName( CDC *pDC, const CRect &rect, int iXYMode, int nIndex, int nShowLine, COLORREF color, LPCTSTR lpszString )
{
	CString strData = lpszString;
	if(strData.IsEmpty())	{	return;	}
	// フォントの作成
	LOGFONT logfont;
	pDC->GetCurrentFont()->GetLogFont( &logfont );
	if(iXYMode == AX_GDIYMODE)	{
		logfont.lfEscapement = GetAxisY().GetMeasureAngle();
		logfont.lfOrientation = GetAxisY().GetMeasureAngle();
	}
	// 背景モードの変更
	int iBkMode = pDC->SetBkMode( TRANSPARENT );
	// フォント?文字色の選択
	CFont font;
	font.CreateFontIndirect( &logfont );
	CFont   *pOldFont = pDC->SelectObject( &font );
	COLORREF oldColor = pDC->SetTextColor( color );
	// 正確な描画位置の取得
	CSize strSize = pDC->GetTextExtent( strData );

	if(iXYMode == AX_GDIXMODE)	{
		// カーソル名称描画
		CPoint point;
		point.x = rect.right - strSize.cx;//(nShowLine - nIndex) * strSize.cy;
		point.y = rect.top + nIndex * strSize.cy + 1;
		pDC->TextOut(  point.x , point.y , strData);
	}	else if(iXYMode == AX_GDIYMODE)	{
		// カーソル名称描画
		CPoint point;
		point.x = rect.right - (nShowLine - nIndex) * strSize.cy;
		point.y = rect.top + strSize.cx;
		pDC->TextOut(  point.x , point.y , strData);
	}
	// 文字色を戻す
	pDC->SetTextColor( oldColor );
	// フォントを戻す&破棄
	pDC->SelectObject( pOldFont );
	font.DeleteObject();
	// 背景モードを戻す
	pDC->SetBkMode( iBkMode );
}
///////////////////////////////////////
/**
 * 	プロットデータのスケールを書く.
 * 		与えられた情報でプロットデータのスケールを描画する。
 * 
 * 	@param pDC			描画するデバイスコンテキストのポインタ
 * 	@param rect			描画領域の範囲
 *	@param iXYMode		AX_XMODE:'X'X軸/AX_YMODE:'Y'Y軸
 * 	@param nIndex		描画するindex
 * 	@param nShowLine	描画するライン数
 *	@param color		描画色
 *	@param dblMin		スケールの最小値
 *	@param dblMax		スケールの最大値
 */
void CAXGDIPlotCtrl::DrawPlotScale( CDC *pDC, const CRect &rect, int iXYMode, int nIndex, int nShowLine, COLORREF color, double dblMin, double dblMax )
{
	// フォントの作成
	LOGFONT logfont;
	pDC->GetCurrentFont()->GetLogFont( &logfont );
	if(iXYMode == AX_GDIYMODE)	{
		logfont.lfEscapement = GetAxisY().GetMeasureAngle();
		logfont.lfOrientation = GetAxisY().GetMeasureAngle();
	}
	// 背景モードの変更
	int iBkMode = pDC->SetBkMode( TRANSPARENT );
	// フォント?文字色の選択
	CFont font;
	font.CreateFontIndirect( &logfont );
	CFont   *pOldFont = pDC->SelectObject( &font );
	COLORREF oldColor = pDC->SetTextColor( color );
	
	if(iXYMode == AX_GDIXMODE)	{
		CString strData = _T("");
		strData.Format(_T("%-0.*f"),GetDecLength(dblMax - dblMin),dblMin);
		// 正確な描画位置の取得
		CSize strSize = pDC->GetTextExtent( strData );
		CPoint point;
		// カーソル名称描画
		point.x = rect.left + 1;//+ nIndex * strSize.cy;
		point.y = rect.bottom - (nShowLine - nIndex) * strSize.cy;	
		pDC->TextOut(  point.x  , point.y , strData );

		strData.Format(_T("%-0.*f"),GetDecLength(dblMax - dblMin),dblMax);
		// 正確な描画位置の取得
		strSize = pDC->GetTextExtent( strData );
		// カーソル名称描画
		point.x = rect.right - strSize.cx;
		point.y = rect.bottom - (nShowLine - nIndex) * strSize.cy;	
		pDC->TextOut(  point.x , point.y , strData );
	}	else	{
		CString strData = _T("");
		strData.Format(_T("%-0.*f"),GetDecLength(dblMax - dblMin),dblMin);
		// 正確な描画位置の取得
		CSize strSize = pDC->GetTextExtent( strData );
		CPoint point;
		// カーソル名称描画
		if( logfont.lfOrientation == 900 || logfont.lfOrientation == -900 )	{
			point.x = rect.left + nIndex * strSize.cy;
			point.y = rect.bottom;// - strSize.cx;
		}	else	{		
			point.x = rect.left;//+ nIndex * strSize.cy;
			point.y = rect.bottom - (nShowLine - nIndex) * strSize.cy;	
		}
		pDC->TextOut(  point.x , point.y , strData );

		strData.Format(_T("%-0.*f"),GetDecLength(dblMax - dblMin),dblMax);
		// 正確な描画位置の取得
		strSize = pDC->GetTextExtent( strData );
		// カーソル名称描画
		if( logfont.lfOrientation == 900 || logfont.lfOrientation == -900 )	{
			point.x = rect.left + nIndex * strSize.cy;
			point.y = rect.top + strSize.cx;
		}	else	{		
			point.x = rect.left;//+ nIndex * strSize.cy;
			point.y = rect.top + nIndex * strSize.cy;	
		}
		pDC->TextOut(  point.x , point.y , strData );
	}
	// 文字色を戻す
	pDC->SetTextColor( oldColor );
	// フォントを戻す&破棄
	pDC->SelectObject( pOldFont );
	font.DeleteObject();
	// 背景モードを戻す
	pDC->SetBkMode( iBkMode );
}
///////////////////////////////////////
/**
 * 	カーソルを書く.
 * 		与えられたカーソルクラスの情報でカーソルを描画する。
 * 
 * 	@param pDC			描画するデバイスコンテキストのポインタ
 * 	@param rect			描画領域の範囲
 * 	@param plotCursor	描画するカーソルクラス（CAXPlotCursorクラス）
 */
void CAXGDIPlotCtrl::DrawPlotCursor( CDC *pDC, const CRect &rect, CAXPlotCursor &plotCursor )
{
	if(!plotCursor.IsShowCursor())			{	return;	}
	if(plotCursor.GetLayer() >= 0)	{	return;	}

	// 無効インデックスなら復帰
	BOOL bDraw = FALSE;
	//カーソルモード	CURSORX:'X' X軸カーソル / CURSORY:'Y' Y軸カーソル / CURSORCROSS:'+' 十字カーソル
	if( (CURSORX == plotCursor.GetCursorMode()) || (CURSORCROSS == plotCursor.GetCursorMode()) )	{
		if( (GetAxisX().GetMin() <= plotCursor.GetValue().dX)
			&& (plotCursor.GetValue().dX <= GetAxisX().GetMax()) )	{
			 bDraw = TRUE;
		}
	}
	if( (!bDraw) && ((CURSORY == plotCursor.GetCursorMode()) || (CURSORCROSS == plotCursor.GetCursorMode())) )	{
		if( (GetAxisY().GetMin() <= plotCursor.GetValue().dY)
			&& (plotCursor.GetValue().dY <= GetAxisY().GetMax()) )	{
			 bDraw = TRUE;
		}
	}
	if(!bDraw)	{	return;	}

	// 描画原点設定
	CPoint oldOrg = pDC->SetViewportOrg( rect.left, rect.top );

	// データ描画位置設定
	CPoint cpData;
	cpData.x = GetAxisX().Data2PointX(plotCursor.GetValue().dX, rect.Width());
	cpData.y = GetAxisY().Data2PointY(plotCursor.GetValue().dY, rect.Height());

	// カーソル描画
	plotCursor.DrawCursor( pDC, rect, cpData, IsMonochrome() );

	// 原点を戻す
	pDC->SetViewportOrg( oldOrg );
}
///////////////////////////////////////
/**
 * 	カーソルを書く.
 * 		与えられたデータクラス＆カーソルクラスの情報でカーソルを描画する。
 * 
 * 	@param pDC			描画するデバイスコンテキストのポインタ
 * 	@param rect			描画領域の範囲
 *	@param data			カーソルクラスで指定したデータレイヤー
 * 	@param plotCursor	描画するカーソルクラス（CAXPlotCursorクラス）
 */
void CAXGDIPlotCtrl::DrawPlotCursor( CDC *pDC, const CRect &rect, CXYPlotData &data, CAXPlotCursor &plotCursor )
{
	// 非表示なら復帰
	if(!plotCursor.IsShowCursor())				{	return;	}
	// 無効レイヤーなら復帰
	if(plotCursor.GetLayer() < 0)			{	return;	}
	// 無効インデックスなら復帰
	int index = plotCursor.GetPos();
	if(  0 > index || index >= data.GetNum() )	{	return;	}
	
	// 描画原点設定
	CPoint oldOrg = pDC->SetViewportOrg( rect.left, rect.top );

	// データ描画位置設定
	CPoint cpData;
	double dXrvs = 1.0;
	if(data.IsReversalX() && (!data.GetXscale().IsLogMode()))		{	dXrvs = -1.0;	}
	cpData.x = data.GetXscale().Data2PointX( data.dataX(index)/*data[index].dX*/ * dXrvs, rect.Width() );
	double dYrvs = 1.0;
	if(data.IsReversalY() && (!data.GetYscale().IsLogMode()))		{	dYrvs = -1.0;	}
	cpData.y = data.GetYscale().Data2PointY( data.dataY(index)/*data[index].dY*/ * dYrvs, rect.Height() );

	// カーソル描画
	plotCursor.DrawCursor( pDC, rect, cpData, IsMonochrome() );

	// 原点を戻す
	pDC->SetViewportOrg( oldOrg );
}
///////////////////////////////////////
/**
 * 	カーソルを書く.
 * 		与えられたデータクラス＆カーソルクラスの情報でカーソルを描画する。
 * 
 * 	@param pDC			描画するデバイスコンテキストのポインタ
 * 	@param rect			描画領域の範囲
 *	@param data			カーソルクラスで指定したデータレイヤー
 * 	@param plotCursor	描画するカーソルクラス（CAXPlotCursorクラス）
 */
void CAXGDIPlotCtrl::DrawPlotCursor( CDC *pDC, const CRect &rect, CDBLPlotData &data, CAXPlotCursor &plotCursor )
{
	// 非表示なら復帰
	if(!plotCursor.IsShowCursor())				{	return;	}
	// 無効レイヤーなら復帰
	if(plotCursor.GetLayer() < 0)			{	return;	}
	// 無効インデックスなら復帰
	int index = plotCursor.GetPos();
	if(  0 > index || index >= data.GetNum() )	{	return;	}

	// 描画原点設定
	CPoint oldOrg = pDC->SetViewportOrg( rect.left, rect.top );

	// データ描画位置設定
	CPoint cpData;
	double dXrvs = 1.0;
	if(data.IsReversalX() && (!data.GetXscale().IsLogMode()))		{	dXrvs = -1.0;	}
	cpData.x = data.GetXscale().Data2PointX( data.dataX(index)/*data[index].dX*/ * dXrvs, rect.Width() );
	double dYrvs = 1.0;
	if(data.IsReversalY() && (!data.GetYscale().IsLogMode()))		{	dYrvs = -1.0;	}
	cpData.y = data.GetYscale().Data2PointY( data.dataY(index)/*data[index].dY*/ * dYrvs, rect.Height() );
	
	// カーソル描画
	plotCursor.DrawCursor( pDC, rect, cpData, IsMonochrome() );

	// 原点を戻す
	pDC->SetViewportOrg( oldOrg );
}
///////////////////////////////////////
/**
 * 	エリアカーソル、または、エリアカーソル名称を書く.
 * 		与えられたデータクラス＆カーソルクラスの情報でエリアカーソルを描画する。
 * 
 * 	@param pDC			描画するデバイスコンテキストのポインタ
 * 	@param rect			描画領域の範囲
 * 	@param areaCursor	描画するカーソルクラス（CAXAreaCursorクラス）
 * 	@param bDrawName	エリアカーソル名称の描画フラグ
 */
void CAXGDIPlotCtrl::DrawAreaCursor( CDC *pDC, const CRect &rect, CAXAreaCursor &areaCursor, BOOL bDrawName /*= FALSE*/ )
{
	// 非表示なら復帰
	if( !areaCursor.IsShowCursor() )		{	return;	}
	// レイヤーが設定されていれば、もどる。
	if( areaCursor.GetLayer() >= 0)	{	return;	}

	// 無効インデックスなら復帰
	BOOL bDraw = FALSE;
	double dXhead,dXtail;
	if( areaCursor.GetValue().dX <= areaCursor.GetTailValue().dX )	{
		dXhead = areaCursor.GetValue().dX;
		dXtail = areaCursor.GetTailValue().dX;
	}	else	{
		dXhead = areaCursor.GetTailValue().dX;
		dXtail = areaCursor.GetValue().dX;
	}

	//カーソルモード	CURSORX:'X' X軸カーソル / CURSORY:'Y' Y軸カーソル / CURSORCROSS:'+' 十字カーソル
	if( (CURSORX == areaCursor.GetCursorMode()) || (CURSORCROSS == areaCursor.GetCursorMode()) )	{
		if( (GetAxisX().GetMin() <= dXtail ) && ( dXhead <= GetAxisX().GetMax()) )	{
			 bDraw = TRUE;
		}
	}
	double dYhead,dYtail;
	if( areaCursor.GetValue().dY <= areaCursor.GetTailValue().dY )	{
		dYhead = areaCursor.GetValue().dY;
		dYtail = areaCursor.GetTailValue().dY;
	}	else	{
		dYhead = areaCursor.GetTailValue().dY;
		dYtail = areaCursor.GetValue().dY;
	}
	if( (!bDraw) && ((CURSORY == areaCursor.GetCursorMode()) || (CURSORCROSS == areaCursor.GetCursorMode())) )	{
		if( (GetAxisY().GetMin() <= dYtail)	&& (dYhead <= GetAxisY().GetMax()) )	{
			 bDraw = TRUE;
		}
	}
	if(!bDraw)	{	return;	}

	// 描画原点設定
	CPoint oldOrg = pDC->SetViewportOrg( rect.left, rect.top );

	// 描画するエリア
	CRect rectDraw( 0, 0, rect.Width(), rect.Height() );

	// Xエリアカーソル描画
	if( areaCursor.GetCursorMode() == CURSORX || areaCursor.GetCursorMode() == CURSORCROSS ){
		rectDraw.left = GetAxisX().Data2PointX( dXhead, rect.Width() );
		rectDraw.right = GetAxisX().Data2PointX( dXtail, rect.Width() );
	}
	// Yエリアカーソル描画
	if( areaCursor.GetCursorMode() == CURSORY || areaCursor.GetCursorMode() == CURSORCROSS ){
		rectDraw.top = GetAxisY().Data2PointY( dYhead, rect.Height() );
		rectDraw.bottom = GetAxisY().Data2PointY( dYtail, rect.Height() );
	}
	rectDraw.NormalizeRect();//正規化
	if(bDrawName)	{
		areaCursor.DrawAreaCursorName( pDC, rectDraw, IsMonochrome() );
	}	else	{
		rectDraw.bottom += 1;
		rectDraw.right += 1;
		areaCursor.DrawPattern( pDC, rectDraw, IsMonochrome() );
	}

	// 原点を戻す
	pDC->SetViewportOrg( oldOrg );
}
///////////////////////////////////////
/**
 * 	エリアカーソル、または、エリアカーソル名称を書く.
 * 		与えられたデータクラス＆カーソルクラスの情報でエリアカーソルを描画する。
 * 
 * 	@param pDC			描画するデバイスコンテキストのポインタ
 * 	@param rect			描画領域の範囲
 *	@param data			カーソルクラスで指定したデータレイヤー
 * 	@param areaCursor	描画するカーソルクラス（CAXAreaCursorクラス）
 * 	@param bDrawName	エリアカーソル名称の描画フラグ
 */
void CAXGDIPlotCtrl::DrawAreaCursor( CDC *pDC, const CRect &rect, CXYPlotData &data, CAXAreaCursor &areaCursor, BOOL bDrawName /*= FALSE*/ )
{
	// 非表示なら復帰
	if(!areaCursor.IsShowCursor())				{	return;	}
	// 無効レイヤーなら復帰
	if(areaCursor.GetLayer() < 0)			{	return;	}
	// 無効インデックスなら復帰
	int iPosHead = areaCursor.GetPos();
	if(  0 > iPosHead || iPosHead >= data.GetNum() )	{	return;	}
	int iPosTail = areaCursor.GetTailPos();
	if(  0 > iPosTail || iPosTail >= data.GetNum() )	{	return;	}

	// 描画原点設定
	CPoint oldOrg = pDC->SetViewportOrg( rect.left, rect.top );

	// 描画するエリア
	CRect rectDraw( 0, 0, rect.Width(), rect.Height() );

	// Xエリアカーソル描画
	if( areaCursor.GetCursorMode() == CURSORX || areaCursor.GetCursorMode() == CURSORCROSS ){
		double dXrvs = 1.0;
		if(data.IsReversalX() && (!data.GetXscale().IsLogMode()))		{	dXrvs = -1.0;	}
		rectDraw.left = data.GetXscale().Data2PointX( data.dataX(iPosHead) * dXrvs, rect.Width() );
		rectDraw.right = data.GetXscale().Data2PointX( data.dataX(iPosTail) * dXrvs, rect.Width() );
	}
	// Yエリアカーソル描画
	if( areaCursor.GetCursorMode() == CURSORY || areaCursor.GetCursorMode() == CURSORCROSS ){
		double dYrvs = 1.0;
		if(data.IsReversalY() && (!data.GetYscale().IsLogMode()))		{	dYrvs = -1.0;	}
		rectDraw.top = data.GetYscale().Data2PointY( data.dataY(iPosHead) * dYrvs, rect.Height() );
		rectDraw.bottom = data.GetYscale().Data2PointY( data.dataY(iPosTail) * dYrvs, rect.Height() );
	}
	rectDraw.NormalizeRect();//正規化
	if(bDrawName)	{
		areaCursor.DrawAreaCursorName( pDC, rectDraw, IsMonochrome() );
	}	else	{
		rectDraw.bottom += 1;
		rectDraw.right += 1;
		areaCursor.DrawPattern( pDC, rectDraw, IsMonochrome() );
	}

	// 原点を戻す
	pDC->SetViewportOrg( oldOrg );
}
///////////////////////////////////////
/**
 * 	エリアカーソル、または、エリアカーソル名称を書く.
 * 		与えられたデータクラス＆カーソルクラスの情報でエリアカーソルを描画する。
 * 
 * 	@param pDC			描画するデバイスコンテキストのポインタ
 * 	@param rect			描画領域の範囲
 *	@param data			カーソルクラスで指定したデータレイヤー
 * 	@param areaCursor	描画するカーソルクラス（CAXAreaCursorクラス）
 * 	@param bDrawName	エリアカーソル名称の描画フラグ
 */
void CAXGDIPlotCtrl::DrawAreaCursor( CDC *pDC, const CRect &rect, CDBLPlotData &data, CAXAreaCursor &areaCursor, BOOL bDrawName /*= FALSE*/ )
{
	// 非表示なら復帰
	if(!areaCursor.IsShowCursor())				{	return;	}
	// 無効レイヤーなら復帰
	if(areaCursor.GetLayer() < 0)			{	return;	}
	// 無効インデックスなら復帰
	int iPosHead = areaCursor.GetPos();
	if(  0 > iPosHead || iPosHead >= data.GetNum() )	{	return;	}
	int iPosTail = areaCursor.GetTailPos();
	if(  0 > iPosTail || iPosTail >= data.GetNum() )	{	return;	}

	// 描画原点設定
	CPoint oldOrg = pDC->SetViewportOrg( rect.left, rect.top );

	// 描画するエリア
	CRect rectDraw( 0, 0, rect.Width(), rect.Height() );

	// Xエリアカーソル描画
	if( areaCursor.GetCursorMode() == CURSORX || areaCursor.GetCursorMode() == CURSORCROSS ){
		double dXrvs = 1.0;
		if(data.IsReversalX() && (!data.GetXscale().IsLogMode()))		{	dXrvs = -1.0;	}
		rectDraw.left = data.GetXscale().Data2PointX( data.dataX(iPosHead) * dXrvs, rect.Width() );
		rectDraw.right = data.GetXscale().Data2PointX( data.dataX(iPosTail) * dXrvs, rect.Width() );
	}
	// Yエリアカーソル描画
	if( areaCursor.GetCursorMode() == CURSORY || areaCursor.GetCursorMode() == CURSORCROSS ){
		double dYrvs = 1.0;
		if(data.IsReversalY() && (!data.GetYscale().IsLogMode()))		{	dYrvs = -1.0;	}
		rectDraw.top = data.GetYscale().Data2PointY( data.dataY(iPosHead) * dYrvs, rect.Height() );
		rectDraw.bottom = data.GetYscale().Data2PointY( data.dataY(iPosTail) * dYrvs, rect.Height() );
	}
	rectDraw.NormalizeRect();//正規化	
	if(bDrawName)	{
		areaCursor.DrawAreaCursorName( pDC, rectDraw, IsMonochrome() );
	}	else	{
		rectDraw.bottom += 1;
		rectDraw.right += 1;
		areaCursor.DrawPattern( pDC, rectDraw, IsMonochrome() );
	}

	// 原点を戻す
	pDC->SetViewportOrg( oldOrg );

}
//************************ 拡張機能 ************************///
///////////////////////////////////////
/**
 * 	マウスでのグラフ拡大機能を設定する.
 * 
 * 	@param iZoom	拡大機能を設定する
 *		ZOOM_OFF = 0,	///<無効
 *		XY_ZOOM,		///<X方向、Y方向の両方向を拡大
 *		X_ZOOM,			///<X方向拡大
 *		Y_ZOOM,			///<Y方向拡大
 * 	@return			許可状態を返す。
 */
int CAXGDIPlotCtrl::EnableMouseZoom ( int iZoom /*= XY_ZOOM*/ )
{
	if(IsEnableActivate())	{
		if(iZoom == XY_ZOOM || iZoom == X_ZOOM || iZoom == Y_ZOOM  )	{
			m_iMouseZoom = iZoom;	///< マウス拡大機能ON/OFFフラグ
		}
	}
	return m_iMouseZoom;
}