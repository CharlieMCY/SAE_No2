// AXGDICore.cpp クラスのインプリメンテーション
//
/********************************************************
// CAXGDIFrame		:AXGDI描画クラス
// CAXColorString	:色付きTEXTクラス
// CAXStringWnd		:色付きTEXTWndクラス
//												by YOTSUTSU
//	* History	:	date:2005,24,Mar.	新規作成
ver.1.00	
********************************************************/
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AXGDICore.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


///////////////////////////////////////
/**
 * 	マーク描画.
 * 		マークを描画する
 * 
 * 	@param pDC		描画するデバイスコンテキスト
 * 	@param iStyle	マーク種別
 * 	@param pos		描画位置
 * 	@param iSize	マークサイズ
 */
void _stdcall DrawMark( CDC *pDC, int iStyle, CPoint pos, int iSize /*= 2*/ )
{
	int		iHalfSize = iSize / 2;
	CPoint	oldPoint;
	// マーク
	POINT point[4];
	switch( iStyle ){
	case MARKCIRCLE:		// ○
		pDC->Ellipse( pos.x - iHalfSize, pos.y - iHalfSize, pos.x + (iHalfSize + 1), pos.y + (iHalfSize + 1) );
		break;
	case MARKCROSS:			// ×
		oldPoint = pDC->GetCurrentPosition();
		pDC->MoveTo( pos.x - iHalfSize, pos.y - iHalfSize );
		pDC->LineTo( pos.x + (iHalfSize + 1), pos.y + (iHalfSize + 1) );
		pDC->MoveTo( pos.x - iHalfSize, pos.y + iHalfSize );
		pDC->LineTo( pos.x + (iHalfSize + 1), pos.y - (iHalfSize + 1) );
		pDC->MoveTo( oldPoint );
		break;
	case MARKSQUARE:		// □
		pDC->Rectangle( pos.x - iHalfSize, pos.y - iHalfSize,
						pos.x + iHalfSize, pos.y + iHalfSize );
		break;
	case MARKTRYANGLE:		// △
		point[0].x = pos.x;				point[0].y = pos.y - iHalfSize;
		point[1].x = pos.x - iHalfSize;	point[1].y = pos.y + iHalfSize;
		point[2].x = pos.x + iHalfSize;	point[2].y = pos.y + iHalfSize;
		pDC->Polygon( point, 3 );
		break;
	case MARKRTRYANGLE:		// ▽
		point[0].x = pos.x;				point[0].y = pos.y + iHalfSize;
		point[1].x = pos.x - iHalfSize;	point[1].y = pos.y - iHalfSize;
		point[2].x = pos.x + iHalfSize;	point[2].y = pos.y - iHalfSize;
		pDC->Polygon( point, 3 );
		break;
	case MARKASTERISK:		// ＊
		oldPoint = pDC->GetCurrentPosition();
		pDC->MoveTo( pos.x - iHalfSize, pos.y - iHalfSize );
		pDC->LineTo( pos.x + (iHalfSize + 1), pos.y + (iHalfSize + 1) );
		pDC->MoveTo( pos.x - iHalfSize, pos.y + iHalfSize );
		pDC->LineTo( pos.x + (iHalfSize + 1), pos.y - (iHalfSize + 1) );
		pDC->MoveTo( pos.x,				pos.y - iHalfSize );
		pDC->LineTo( pos.x,				pos.y + (iHalfSize + 1) );
		pDC->MoveTo( oldPoint );
		break;
	case MARKPLUS:			// ＋
		oldPoint = pDC->GetCurrentPosition();
		pDC->MoveTo( pos.x, pos.y - iHalfSize );
		pDC->LineTo( pos.x, pos.y + (iHalfSize + 1) );
		pDC->MoveTo( pos.x - iHalfSize, pos.y );
		pDC->LineTo( pos.x + (iHalfSize + 1), pos.y );
		pDC->MoveTo( oldPoint );
		break;
	case MARKDIAMOND:		//◇
		//oldPoint = pDC->GetCurrentPosition();
		point[0].x = pos.x;				point[0].y = pos.y - iHalfSize;
		point[1].x = pos.x - iHalfSize;	point[1].y = pos.y;
		point[2].x = pos.x;				point[2].y = pos.y + iHalfSize;
		point[3].x = pos.x + iHalfSize;	point[3].y = pos.y;
		pDC->Polygon( point, 4 );
		break;
	}
}
///////////////////////////////////////
/**
 * 	グレイカラー値取得（COLORREF：カラー値として使われる 32 ビット値）
 *		フルカラー値からグレイカラー変換後の値を取得 
 * 
 * 	@param data	フルカラー値
 * 	@return		グレイカラー変換値
 */
COLORREF _stdcall Color2Gray( COLORREF color )
{
	COLORREF grayColor = color;
//出力画素 = (0.299 * R + 0.587 * G + 0.114 * B) * 256 / 256
//　　　　　　　　　　　= (77 * R + 150 * G + 29 * B) >> 8
	BYTE red = GetRValue(color);
	BYTE green = GetGValue(color);
	BYTE blue = GetBValue(color);
	BYTE gray = (BYTE)( ( 2 * red + 4 * green + blue ) / 7 );
	grayColor = RGB( gray, gray, gray);

	return grayColor;
}
/////////////////////////////////////////////////
int _stdcall GetDecLength(double dRange)
{
	int iZero;
	double dVal = fabs(dRange);

	//if(dVal >= 10000.0)		{	sZero = 0;	}//どっちがいいのか
	//else 
	if(dVal >= 1000.0)		{	iZero = 0;	}
	else if(dVal >= 100.0)	{	iZero = 1;	}
	else if(dVal >= 10.0)	{	iZero = 2;	}
	else if(dVal >= 1.0)	{	iZero = 3;	}
	else					{	iZero = 4;	}

	return	(iZero);
}
/////////////////////////////////////////////////////////////////////////////
// CAXGDIFrame
//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////
CAXGDIFrame::CAXGDIFrame( COLORREF bkColor /*= ICTRLCOLOR*/ )
{
#ifdef _DEBUG
if(1)	{
	size_t  sizeByte;

	sizeByte = sizeof(LINESTYLE);		TRACE("tagLineStyle= %d, ", sizeByte);
	sizeByte = sizeof(MARKERSTYLE);		TRACE("tagMarkerStyle= %d, ", sizeByte);

	TRACE("\n");
}
#endif

	m_bkColor = bkColor;			///<default background color
	m_frameColor = GetSysColor( COLOR_WINDOWFRAME );	///<Frame line color
	EnableMonochrome(FALSE);
	ShowFrame(FALSE);
}
///////////////////////////////////////
/**
 * 	コピーコンストラクタ
 * 		与えられたCAXGDIFrameをコピーする
 * 
 * 	@param org	コピー元CAXGDIFrameクラス
 */
CAXGDIFrame::CAXGDIFrame( const CAXGDIFrame &org )
{
	operator = (org);
}
///////////////////////////////////////
//デストラクタ
CAXGDIFrame::~CAXGDIFrame()
{
}
///////////////////////////////////////
/**
 * 	ラインスタイル描画
 * 
 * 	@param pDC			描画デバイスコンテキスト
 * 	@param rect			描画エリア
 * 	@param lineStyle	描画ラインスタイル
 *	@param lOrientation 描画ラインの角度（0.1°)
 */
void CAXGDIFrame::DrawLineStyle( CDC *pDC, const CRect &rect, const LINESTYLE &lineStyle, long lOrientation /*= 0*/ )
{
	if(lineStyle.iStyle == PS_NULL)	{	return;	}
	// ペンの作成
	CLinePen pen;
	pen.CreatePen( lineStyle.iStyle, lineStyle.iSize, (IsMonochrome() ? IBLACK : lineStyle.color ) );

	// ペンの選択
	CPen *pOldPen = pDC->SelectObject( &pen );

	// 描画ポイントの計算
	CPoint start,end;

	if(lOrientation == 0 || lOrientation == 1800)	{//横
		start.x = rect.left;			
		end.x = rect.right;
		start.y = end.y = rect.CenterPoint().y;
	}	else if(lOrientation == 900 || lOrientation == -900)	{
		start.x = end.x = rect.CenterPoint().x;
		start.y = rect.top;
		end.y = rect.bottom;
	}	else	{
		// 各計算値の取得
		double dRad= ( M_PI / 180.0 ) * ( lOrientation / 10.0 );
		int iCosX = int(0.5 * rect.Width() * fabs(cos( dRad )));
		int iSinY = int(0.5 * rect.Height() * fabs(sin( dRad )));
		start.x = rect.CenterPoint().x - iCosX;			
		end.x = rect.CenterPoint().x + iCosX;
		start.y = rect.CenterPoint().y - iSinY;
		end.y = rect.CenterPoint().y + iSinY;
	}

	// 線描画
	pDC->MoveTo( start );
	pDC->LineTo( end );

	// ペンを戻す
	pDC->SelectObject( pOldPen );

	// ペンの破棄
	pen.DeleteObject();
}
///////////////////////////////////////
/**
 * 	マーカー描画
 * 
 * 	@param pDC			描画デバイスコンテキスト
 * 	@param rect			描画エリア
 * 	@param markStyle	描画マーカースタイル
 *	@param color		描画マーカーの色
 */
void CAXGDIFrame::DrawMarker( CDC *pDC, CPoint pos, const MARKERSTYLE &markStyle, COLORREF color )
{
	// マーカー無しなら復帰
	if( markStyle.iMarker == MARKNONE ) return;

	// ペンの作成
	CPen pen;
	pen.CreatePen( PS_SOLID, 0, (IsMonochrome() ? IBLACK : color ) );
	
	// ペンの選択
	CPen *pOldPen = pDC->SelectObject( &pen );
	
	// ブラシの作成
	CBrush	brush((IsMonochrome() ? IBLACK : color ));
	
	// ブラシの選択
	CBrush *oldBrush = NULL;
	//	brush.CreateSolidBrush( m_lineStyle.color );
	if( IsMonochrome() || markStyle.iBkStyle == 0 ) {
		oldBrush = (CBrush *)pDC->SelectStockObject( NULL_BRUSH );
	}	else	{
		oldBrush = pDC->SelectObject( &brush );
	}

	//マーカー描画
	::DrawMark( pDC, markStyle.iMarker, pos, markStyle.iMarkSize );

	// ブラシを戻す
	pDC->SelectObject( oldBrush );

	// ブラシの破棄
	brush.DeleteObject();

	// ペンを戻す
	pDC->SelectObject( pOldPen );

	// ペンの破棄
	pen.DeleteObject();
}
/////////////////////////////////////////////////////////////////////////////
// CAXColorString
//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////
CAXColorString::CAXColorString()
{
	m_colorData = GetSysColor( COLOR_BTNTEXT );		///<font color
	m_strData = _T("");			///<Display string
//	m_wStyle = 0x00000000L;		///<Display style

//	#define DT_TOP              0x00000000
//	#define DT_LEFT             0x00000000
	//Default
	m_nDTFormat = 0x00000000L;	///< DrawText Format

//	SetTextStyle();
}
///////////////////////////////////////
/**
 * 	コピーコンストラクタ
 * 		与えられたCAXColorStringをコピーする
 * 
 * 	@param org	コピー元CAXColorStringクラス
 */
CAXColorString::CAXColorString( const CAXColorString &org )
{
	operator = (org);
}
///////////////////////////////////////
//デストラクタ
CAXColorString::~CAXColorString()
{
}
///////////////////////////////////////
/**
 * 	draw string to static style
 * 	
 * 	@param	wStyle	描画スタイル
 * 	@param	rect	描画エリア
 * 	@return			元のスタイル
 */
WORD CAXColorString::SetTextStyle(WORD wStyle /*= (SS_CENTER | SS_CENTERIMAGE)*/)
{
	//WORD wOldStyle = m_wStyle;
	UINT nDTFormat = (0x0003 & wStyle);
	switch(nDTFormat)	{
	case SS_LEFT:	//0x00000000L
	case SS_CENTER:	//0x00000001L
	case SS_RIGHT:	//0x00000002L
//#define DT_LEFT             0x00000000
//#define DT_CENTER           0x00000001
//#define DT_RIGHT            0x00000002
		m_nDTFormat &= (0x0003 ^ 0xFFFFFFFF);
		m_nDTFormat = (m_nDTFormat | nDTFormat);
		break;
//	case SS_ICON:	//0x00000003L
//		m_wStyle = (0x0003 ^ m_wStyle);
//		break;
	default:
		break;
	}
	if(SS_CENTERIMAGE & wStyle)	{//     0x00000200L
	//	m_wStyle |= SS_CENTERIMAGE;
		m_nDTFormat &= (0xFFFFFFFF ^ DT_BOTTOM);
		m_nDTFormat |= DT_VCENTER;
	}	else	{
		m_nDTFormat &= (0xFFFFFFFF ^ DT_VCENTER);
		m_nDTFormat &= (0xFFFFFFFF ^ DT_BOTTOM);
	//	m_wStyle ^= SS_CENTERIMAGE;
	}

	return GetTextStyle();
}
WORD CAXColorString::GetTextStyle(void) const
{
	WORD wTextStyle = 0x0000;
	
	if(m_nDTFormat & DT_CENTER)	{	//DT_CENTER		0x00000001
		wTextStyle |= SS_CENTER;	//0x00000001L
	}	else if(m_nDTFormat & DT_RIGHT)	{//DT_RIGHT	0x00000002
		wTextStyle |= SS_RIGHT;	//0x00000002L
	}

	if( m_nDTFormat & DT_VCENTER )	{
		wTextStyle |= SS_CENTERIMAGE;
	}
	return wTextStyle;
}	///<Display style
///////////////////////////////////////
/**
 * 	draw string to static area
 * 	
 * 	@param pDC				描画デバイスコンテキスト
 * 	@param rect				描画エリア
 * 	@param font				描画Font
 * 	@param bMonochrome		モノクロ表示フラグ
 *	@param lfOrientation	表示角度
*/
void CAXColorString::TextDraw( CDC* pDC, CRect &rect, CFont &font, BOOL bMonochrome, long lfOrientation )
{
	if(m_strData.IsEmpty())	{	return;	}
	COLORREF textColor = (bMonochrome ? RGB(0,0,0) : GetStrColor());
	TextDraw( pDC, rect, font, m_strData, textColor , GetDTFormat(), lfOrientation );
}
///////////////////////////////////////
/**
 * 	draw string to static area
 * 	
 * 	@param pDC			描画デバイスコンテキスト
 * 	@param rect			描画エリア
 * 	@param font			描画Font
 * 	@param lpszString	表示文字列
 * 	@param textColor	表示文字色
 * 	@param wStyle		表示Style
*/
void CAXColorString::TextDraw( CDC* pDC, CRect &rect, CFont &font, LPCTSTR lpszString, const COLORREF textColor, UINT nDTFormat, long lfOrientation )
{
	CString str(lpszString);
#ifndef _DEBUG
	//set clip area
	pDC->IntersectClipRect( rect );
#endif //_DEBUG
	
	//text color設定
	COLORREF oldColor = pDC->SetTextColor( textColor );
	//font 設定
	CFont *pOldFont = pDC->SelectObject( &font );
	//バックグラウンド モード設定
	int nBkMode = pDC->SetBkMode(TRANSPARENT);
	//get text size
	CSize textSize = pDC->GetTextExtent( str );
	//text point の計算
	CPoint cpTextDraw;
	
	UINT nHPos = GetDTPosH(nDTFormat);
	UINT nVPos = GetDTPosV(nDTFormat);

	if(lfOrientation == 900 || lfOrientation == -900)	{
		if(DT_CENTER/*SS_CENTER*/ == nHPos)	{
			if(lfOrientation == -900)	{
				cpTextDraw.y = rect.top + ( rect.Height() - textSize.cx ) / 2;
			}	else	{
				cpTextDraw.y = rect.top + ( rect.Height() + textSize.cx ) / 2;
			}
			//cpTextDraw.x = rect.left + ( rect.Width() - textSize.cx ) / 2;
		}	else if(DT_RIGHT/*SS_RIGHT*/ == nHPos)	{
			//cpTextDraw.y = rect.right - textSize.cx ;
			if(lfOrientation == -900)	{
				cpTextDraw.y = rect.top + textSize.cx ;
			}	else	{
				cpTextDraw.y = rect.top +/*rect.bottom - */textSize.cx ;
			}
		}	else	{//SS_LEFT
			cpTextDraw.x = rect.left;// + ( - textSize.cx ) / 2;
			if(lfOrientation == -900)	{
				cpTextDraw.y = rect.top;
			}	else	{
				cpTextDraw.y = rect.bottom;
			}
		}
		if(DT_VCENTER/*SS_CENTERIMAGE*/ == nVPos){
			cpTextDraw.x = rect.left + ( rect.Width() - textSize.cy ) / 2;
		}	else if(DT_BOTTOM/*SS_CENTERIMAGE*/ == nVPos)	{
			if(lfOrientation == -900)	{	cpTextDraw.x = rect.left + textSize.cy;	}
			else						{	cpTextDraw.x = rect.right - textSize.cy;	}
		}	else	{
			if(lfOrientation == -900)	{	cpTextDraw.x = rect.right;	}
			else						{	cpTextDraw.x = rect.left;	}
		}
		
	}	else	{
		if(DT_CENTER/*SS_CENTER*/ == nHPos)	{
			cpTextDraw.x = rect.left + ( rect.Width() - textSize.cx ) / 2;
		}	else if(DT_RIGHT/*SS_RIGHT*/ == nHPos)	{
			cpTextDraw.x = rect.right - textSize.cx ;
		}	else	{//DT_LEFT/*SS_LEFT*/
			cpTextDraw.x = rect.left;// + ( - textSize.cx ) / 2;
		}
		if(DT_VCENTER/*SS_CENTERIMAGE*/ == nVPos)	{
			cpTextDraw.y = rect.top + ( rect.Height() - textSize.cy ) / 2;
		}	else if(DT_BOTTOM/*SS_CENTERIMAGE*/ == nVPos)	{
			cpTextDraw.y = rect.bottom - textSize.cy;
		}	else	{
			cpTextDraw.y = rect.top;
		}
	}

	//text draw
	pDC->TextOut( cpTextDraw.x, cpTextDraw.y, str );
	//バックグラウンド モード戻す
	pDC->SetBkMode(nBkMode);
	
	//font 戻す
	pDC->SelectObject( pOldFont );
	
	//text color 戻す
	pDC->SetTextColor( oldColor );
#ifndef _DEBUG
	//clip area free
	pDC->SelectClipRgn( NULL );
#endif //_DEBUG
}
/////////////////////////////////////////////////////////////////////////////
// CAXGDICtrl
//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////
CAXGDICtrl::CAXGDICtrl( UINT nKind /*= AXGCTRL_NONE*/, COLORREF bkColor /*= ICTRLCOLOR*/)
	: CAXGDIFrame( bkColor )
{
	///< 初期表示時のサイズ
	m_wndSize.cx = 0;
	m_wndSize.cy = 0;
	//ユーザーパラメータ設定.
	SetUserParam( 0, 0 );
	// アクティブ情報初期化
	ClearActiveInfo( &m_activeInfo );
	///< AXGDICtrlの種類（E_AXGDICTRL_KIND参照）
	m_nKind = nKind;
}
/**
 * 	コピーコンストラクタ
 * 		与えられたCAXGDICtrlをコピーする
 * 
 * 	@param org	コピー元CAXGDICtrlクラス
 */
CAXGDICtrl::CAXGDICtrl( const CAXGDICtrl &org )
{
	operator = (org);
}
/// デストラクタ
CAXGDICtrl::~CAXGDICtrl()
{
	DestroyWindow();
}

BEGIN_MESSAGE_MAP(CAXGDICtrl, CWnd)
	//{{AFX_MSG_MAP(CAXGDICtrl)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
//	ON_WM_ERASEBKGND()
	ON_NOTIFY_REFLECT( AXGCN_CHANGE_ACTIVE, OnChangeActive )
	ON_NOTIFY_REFLECT( AXGCN_CHANGE_STYLE, OnChangeStyle )
	ON_NOTIFY_REFLECT( AXGCN_CHANGE_SCALE, OnChangeScale )
	ON_NOTIFY_REFLECT( AXGCN_CHANGE_CURSOL, OnChangeCursol )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
////////////////////////////////////////////////////
/// ウィンドウ作成時のメッセージハンドラ
void CAXGDICtrl::PreSubclassWindow() 
{	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください

	///< 初期表示時のサイズ
	RecalcInitSize();
//	CRect rect;
//	CWnd::GetWindowRect( rect );
//	GetParent()->ScreenToClient( rect );
	
//	m_wndSize.cx = rect.Width();
//	m_wndSize.cy = rect.Height();
	BOOL bChkKind = ((m_nKind != AXGCTRL_NONE) ? TRUE : FALSE );
#ifdef _DEBUG
	if(!bChkKind)	{
		MessageBox("AXGDICtrl kind is not setting. this application exit now!!!");
	}
#endif
	ASSERT(bChkKind);

	CWnd::PreSubclassWindow();
}
////////////////////////////////////////////////////
/// ウィンドウ破棄時のメッセージハンドラ
void CAXGDICtrl::OnDestroy() 
{
	CWnd::OnDestroy();
	m_wndSize.cx = 0;
	m_wndSize.cy = 0;
}
////////////////////////////////////////////////////
// ウィンドウの描画
void CAXGDICtrl::OnPaint() 
{	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	// 描画用メッセージとして CStatic::OnPaint() を呼び出してはいけません
	CPaintDC dc(this); // 描画用のデバイス コンテキスト
	//get rect size
	CRect rectItem;
	GetClientRect( &rectItem );

	//以下の背景描画は20050929yotsutsu 用検討
	DrawBackground( &dc, rectItem );

	// フォントの取得
	LOGFONT logfont;
	GetParent()->GetFont()->GetLogFont( &logfont );
	// フォントの作成?選択
	CFont font;
	font.CreateFontIndirect( &logfont );
	CFont *pOldFont = dc.SelectObject( &font );
	//描画前処理
	BeginPaintDC( &dc, rectItem );
	//描画
	DrawDC( &dc, rectItem );
	//拡張描画
	DrawExDC( &dc, rectItem );
	//Activeな状態を描画
	DrawActiveState( &dc, rectItem );
	// 描画後処理
	EndPaintDC( &dc, rectItem );
	// フォントを戻す
	dc.SelectObject( pOldFont );
	font.DeleteObject();
}
///////////////////////////////////////
// 入力フォーカスを受け取り
void CAXGDICtrl::OnSetFocus(CWnd* pOldWnd)
{
	///< TRUE:選択/FALSE:非選択　状態
	CWnd::OnSetFocus(pOldWnd);
	if(IsEnableActivate())	{
		m_activeInfo.nActive = AXGCTRLACT_FRAME;		///< 1:全体
		NotifyToParent( AXGCN_CHANGE_ACTIVE, NULL );
	}
}
///////////////////////////////////////
// 入力フォーカスを失った
void CAXGDICtrl::OnKillFocus(CWnd* pNewWnd)
{
	if(pNewWnd && pNewWnd->GetSafeHwnd())	{
		if(pNewWnd->GetOwner() != this)	{
			if(IsEnableActivate())	{
				//m_activeInfo.nActive = AXGCTRLACT_FRAME;		///< 1:全体
				m_activeInfo.nActive = AXGCTRLACT_NONE;///< 0:非選択
			}
			Redraw();
		}
	}
	CWnd::OnKillFocus(pNewWnd);
}
///////////////////////////////////////
/// マウス左ボタン押下の時のメッセージハンドラ
void CAXGDICtrl::OnLButtonDown( UINT nFlags, CPoint point )
{
	if( GetSafeHwnd() )	{
		if(GetStyle() & SS_NOTIFY)	{
			if((GetFocus() != this))	{	this->SetFocus();	}
		}
	}

	CWnd::OnLButtonDown(nFlags, point);
}
///////////////////////////////////////
/// マウス左ボタン押下の時のメッセージハンドラ
void CAXGDICtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	if( GetSafeHwnd() )	{
		//if((GetFocus() != this))	{	this->SetFocus();	}
	}

	CWnd::OnRButtonDown(nFlags, point);
}
///////////////////////////////////////
//Activeなアイテムを変更する。
void CAXGDICtrl::OnChangeActive(NMHDR * pNotifyStruct, LRESULT* result )
{
	if(*result == TRUE)	{	return;	}
	AXGCNOTIFY *pNotifyMsg = (AXGCNOTIFY *)pNotifyStruct;
	if(OnChangeActive(pNotifyMsg))	{
		NotifyToParent(AXGCN_UPDATE_ACTIVE, NULL );
	}
	*result = TRUE;
}
///////////////////////////////////////
//Activeなアイテムのスタイルを変更する。
void CAXGDICtrl::OnChangeStyle(NMHDR * pNotifyStruct, LRESULT* result )
{
	if(*result == TRUE)	{	return;	}
	AXGCNOTIFY *pNotifyMsg = (AXGCNOTIFY *)pNotifyStruct;
	if(OnChangeStyle(pNotifyMsg))	{
		NotifyToParent(AXGCN_UPDATE_STYLE, NULL );
	}
	*result = TRUE;
}
///////////////////////////////////////
//Activeなアイテムのスケールを変更する。
void CAXGDICtrl::OnChangeScale(NMHDR * pNotifyStruct, LRESULT* result )
{
	if(*result == TRUE)	{	return;	}
	AXGCNOTIFY *pNotifyMsg = (AXGCNOTIFY *)pNotifyStruct;
	if(OnChangeScale(pNotifyMsg))	{
		NotifyToParent(AXGCN_UPDATE_SCALE, NULL );
	}
	*result = TRUE;
}
///////////////////////////////////////
//Activeなカーソルの位置を更新する。
void CAXGDICtrl::OnChangeCursol(NMHDR * pNotifyStruct, LRESULT* result )
{
	if(*result == TRUE)	{	return;	}
	AXGCNOTIFY *pNotifyMsg = (AXGCNOTIFY *)pNotifyStruct;
	if(OnChangeCursol(pNotifyMsg))	{
		NotifyToParent(AXGCN_UPDATE_CURSOL, NULL );
	}
	*result = TRUE;
}
///////////////////////////////////////
// protected
///////////////////////////////////////
/**
 * 親Wndクラスへの通知
 *	@param nCode		処理すべき通知メッセージのコード
 *	@param lpActiveInfo	通知に関連付けられたコントロールの情報
 *	@param nKey			押された仮想キー コードを指定します。
 *	@return
 */
void CAXGDICtrl::NotifyToParent( UINT nCode, AXGCACTINFO *lpActiveInfo /*= NULL*/, UINT nKey /*= 0x0000*/ )
{
	CWnd * pParent = GetParent();
	if(pParent)
	{
		HWND hWnd = pParent->GetSafeHwnd();
		if(pParent->GetSafeHwnd())
		{	
			AXGCNOTIFY ctrlNotify;
			ctrlNotify.hdr.hwndFrom = GetSafeHwnd();
			ctrlNotify.hdr.idFrom = GetDlgCtrlID();
			ctrlNotify.hdr.code = nCode;
			if(lpActiveInfo != NULL)	{	ctrlNotify.activeInfo = (*lpActiveInfo);	}
			else						{	ctrlNotify.activeInfo = m_activeInfo;	}
			ctrlNotify.activeInfo.nKind = GetCtrlKind();
			ctrlNotify.nKeyParam = nKey;
			::SendMessage(hWnd, WM_NOTIFY, GetDlgCtrlID(),(LPARAM)&ctrlNotify);
		}
	}
}
///////////////////////////////////////
/**
 * Activeなアイテムを変更する。(通知メッセージの処理)
 *	@param		pNotifyMsg	通知メッセージの情報
 *	@return		TRUE:処理した。/FALSE:未処理
 */
BOOL CAXGDICtrl::OnChangeActive(AXGCNOTIFY *pNotifyMsg )
{
	m_activeInfo = pNotifyMsg->activeInfo;	///< Active状態の情報
	Redraw();
	
	return TRUE;
}
///////////////////////////////////////
/**
 * Activeなアイテムのスタイルを変更する。(通知メッセージの処理)
 *	@param		pNotifyMsg	通知メッセージの情報
 *	@return		TRUE:処理した。/FALSE:未処理
 */
BOOL CAXGDICtrl::OnChangeStyle(AXGCNOTIFY *pNotifyMsg )
{
	return FALSE;
}
///////////////////////////////////////
/**
 * Activeなアイテムのスケールを変更する。(通知メッセージの処理)
 *	@param		pNotifyMsg	通知メッセージの情報
 *	@return		TRUE:処理した。/FALSE:未処理
 */
BOOL CAXGDICtrl::OnChangeScale(AXGCNOTIFY *pNotifyMsg )
{
	return FALSE;
}
///////////////////////////////////////
/**
 * Activeなカーソルの位置を更新する。(通知メッセージの処理)
 *	@param		pNotifyMsg	通知メッセージの情報
 *	@return		TRUE:処理した。/FALSE:未処理
 */
BOOL CAXGDICtrl::OnChangeCursol(AXGCNOTIFY *pNotifyMsg )
{
	return FALSE;
}
///////////////////////////////////////
// protected
///////////////////////////////////////
///////////////////////////////////////
// public
///////////////////////////////////////
/**
 * 	初期サイズを変更する。
 * 		現在のサイズに変更する
 *	@return 最新のサイズ
 */
const CSize & CAXGDICtrl::RecalcInitSize(void)
{
	CRect rect;
	GetClientRect( rect );
	//初期表示
	m_wndSize.cx = rect.Width();
	m_wndSize.cy = rect.Height();

	return m_wndSize;
}
///////////////////////////////////////
/**
 * 	Active状態の描画.
 * 		Active状態を表示する
 * 
 * 	@param pDC		描画するデバイスコンテキストのポインタ
 * 	@param rect		描画領域の範囲
 */
void CAXGDICtrl::DrawActiveState( CDC *pDC, const CRect &rect )
{
	if( !GetSafeHwnd())	{	return;	}
	if( (GetFocus() == this))	{
		// ブラシの作成	
		CBrush	brush;
		brush.CreateSolidBrush(GetBkColor());
	//	COLORREF bkColor = ~GetBkColor();
	//	COLORREF bkColor = ::Color2Gray(GetBkColor());
		int iOldRop = pDC->SetROP2( R2_NOT );
	//	brush.CreateSolidBrush(!bkColor);//::GetSysColor(COLOR_HIGHLIGHT));
		// ブラシの選択
		CBrush *pOldBrush = pDC->SelectObject( &brush );
		
		DrawActiveFrame( pDC, rect );

		pDC->SetROP2( iOldRop );
		// ブラシを戻す
		pDC->SelectObject( pOldBrush );
		// ブラシの破棄
		brush.DeleteObject();
	}
}
///////////////////////////////////////
/**
 * 	Active状態の描画.
 * 		Active状態を表示する
 * 
 * 	@param pDC		描画するデバイスコンテキストのポインタ
 * 	@param rect		描画領域の範囲
 */
void CAXGDICtrl::DrawActiveFrame( CDC *pDC, const CRect &rect, int size )
{
	CRect rectItem = rect;
	//フレーム
	//左上
	rectItem.bottom = rectItem.top + size;
	rectItem.right = rectItem.left + size;
	pDC->Rectangle( rectItem );
	//左中
	rectItem.top = ( rect.top + rect.bottom - size ) / 2;
	rectItem.bottom = rectItem.top + size;
	pDC->Rectangle( rectItem );
	//左下
	rectItem.top = rect.bottom - size;
	rectItem.bottom = rect.bottom;
	pDC->Rectangle( rectItem );
	//中下
	rectItem.left = (rect.left + rect.right - size ) / 2 ;
	rectItem.right = rectItem.left + size;
	pDC->Rectangle( rectItem );
	//右下
	rectItem.left = rect.right - size;
	rectItem.right = rect.right;
	pDC->Rectangle( rectItem );
	//右中
	rectItem.top = ( rect.top + rect.bottom - size ) / 2 ;
	rectItem.bottom = rectItem.top + size;
	pDC->Rectangle( rectItem );
	//右上
	rectItem.top = rect.top;
	rectItem.bottom = rectItem.top + size;
	pDC->Rectangle( rectItem );
	//中上
	rectItem.left = (rect.left + rect.right - size ) / 2 ;
	rectItem.right = rectItem.left + size;
	pDC->Rectangle( rectItem );
}
///////////////////////////////////////
/**
 * 	PrintDCに描画する.（印刷用）
 * 		指定されたDCに描画する
 * 
 * 	@param pDC			描画するDC
 * 	@param rect			描画する領域のRECT
 * 	@param bMonochrome	モノクローム印刷の有効/無効
 * 	@param bMonochrome	拡張描画の有効/無効
 */
void CAXGDICtrl::PrintDC( CDC *pDC, const CRect &rect, BOOL bMonochrome /*= FALSE*/, BOOL bDrawExFlag /*= FALSE*/ )
{
	// フォントの取得
	LOGFONT logfont;
	GetParent()->GetFont()->GetLogFont( &logfont );
	//Font size の調整
	if(GetInitSize().cx > 0 && GetInitSize().cy > 0)	{
		if( rect.Height() > rect.Width() )	{
			logfont.lfHeight = FtoL((double)logfont.lfHeight * rect.Width() / GetInitSize().cx  + 0.5) ;
		}	else	{
			logfont.lfHeight = FtoL((double)logfont.lfHeight * rect.Height() / GetInitSize().cy  + 0.5) ;
		}
	}	else	{
		logfont.lfHeight = -MulDiv( 9, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	}

	// フォントの作成?選択
	CFont font;
	font.CreateFontIndirect( &logfont );
	CFont *pOldFont = pDC->SelectObject( &font );

	//モノクローム印刷の有効/無効
	BOOL bOld = EnableMonochrome( bMonochrome );

	//描画
	DrawDC( pDC, rect );

	//拡張描画
	if(bDrawExFlag)	{	DrawExDC( pDC, rect );	}

	//モノクローム印刷の有効/無効
	EnableMonochrome( bOld );

	//fontを元に戻す & 削除
	pDC->SelectObject( pOldFont );
	font.DeleteObject();

}
/////////////////////////////////////////////////////////////////////////////
// CAXStringWnd
//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////
CAXStringWnd::CAXStringWnd( COLORREF bkColor /*= ICTRLCOLOR*/)
{
	m_strData = _T("");
	SetTextSizeAdjust(FALSE);	///< Test size adjust
	m_lfOrientation = 0;//描画方向
	SetBkColor(bkColor);
	m_nKind = AXGCTRL_STRING;
}
///////////////////////////////////////
/**
 * 	コピーコンストラクタ
 * 		与えられたCAXStringWndをコピーする
 * 
 * 	@param org	コピー元CAXStringWndクラス
 */
CAXStringWnd::CAXStringWnd( const CAXStringWnd &org )
{
	operator = (org);
}
///////////////////////////////////////
//デストラクタ
CAXStringWnd::~CAXStringWnd()
{
}
BEGIN_MESSAGE_MAP(CAXStringWnd, CAXGDICtrl)
	//{{AFX_MSG_MAP(CAXStringWnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
////////////////////////////////////////////////////
void CAXStringWnd::PreSubclassWindow() 
{	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	GetWindowText(m_strData);

//	m_wStyle = (WORD)(0x0000FFFFL & GetStyle());
	SetTextStyle((WORD)(0x0000FFFFL & GetStyle()));
	//TRACE("CAXStringDraw GetExStyle%d:%08X,%04X\n",this->GetDlgCtrlID(),GetStyle(),GetTextStyle());

	CAXGDICtrl::PreSubclassWindow();
}
////////////////////////////////////////////////////
void CAXStringWnd::DrawDC( CDC *pDC, CRect rect )
{
	DrawItem( pDC, rect );
}
////////////////////////////////////////////////////
void CAXStringWnd::DrawItem( CDC *pDC, CRect rect, CFont *pTextFont /*= NULL*/ )
{
	DrawFrame( pDC, rect );

	if(m_strData.IsEmpty())	return;
	 
	TextDraw( pDC, rect, pTextFont );	
}
////////////////////////////////////////////////////
void CAXStringWnd::TextDraw( CDC *pDC, CRect rect, CFont *pTextFont /*= NULL*/ )
{
	LOGFONT logFont;
	CFont font;

	if(pTextFont)	{
		pTextFont->GetLogFont( &logFont );
	}	else	{
		GetParent()->GetFont()->GetLogFont( &logFont );
		logFont.lfQuality = PROOF_QUALITY;
		//logFont.lfCharSet = lfCharSet;
		if(m_bTextSizeAdjust)	{	///< Test size adjust
			//文字自体がrect sizeを超えるので、spaceですこし小さめにしてある。
			if(m_lfOrientation == 900 || m_lfOrientation == -900)	{
				long lSpace = rect.Width() * 25 / 100;	//とりあえず25％
				logFont.lfHeight = rect.Width() - lSpace;
			}	else	{
				long lSpace = rect.Height() * 25 / 100;	//とりあえず25％
				logFont.lfHeight = rect.Height() - lSpace;
			}
		}
		logFont.lfWeight = FW_NORMAL;			//太さ defaultは FW_NORMALの400。FW_HEAVYは900
	//	logFont.lfWidth  = rect.Width() / 10 ;	//横幅取ると壊れるので注意
	}
	//	描画方向 文字の基線と x 軸との角度を (0.1 度単位で) 指定します。角度は y 方向が下向きの座標系では x 軸から反時計回りに、y 方向が上向きの座標系では時計回りに計測します。
	logFont.lfOrientation = m_lfOrientation;
	logFont.lfEscapement = m_lfOrientation;

	//font create
	font.CreateFontIndirect( &logFont );

	//COLORREF textColor = ( IsMonochrome() ? IBLACK : GetStrColor() );

	CAXColorString::TextDraw( pDC, rect , font, IsMonochrome(), m_lfOrientation );	

	font.DeleteObject();
}