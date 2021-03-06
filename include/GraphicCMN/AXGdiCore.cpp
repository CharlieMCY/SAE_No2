// AXGDICore.cpp クラスのインプリメンテ�`ション
//
/********************************************************
// CAXGDIFrame		:AXGDI宙鮫クラス
// CAXColorString	:弼原きTEXTクラス
// CAXStringWnd		:弼原きTEXTWndクラス
//												by YOTSUTSU
//	* History	:	date:2005,24,Mar.	仟�ﾗ�撹
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
 * 	マ�`ク宙鮫.
 * 		マ�`クを宙鮫する
 * 
 * 	@param pDC		宙鮫するデバイスコンテキスト
 * 	@param iStyle	マ�`ク�N�e
 * 	@param pos		宙鮫了崔
 * 	@param iSize	マ�`クサイズ
 */
void _stdcall DrawMark( CDC *pDC, int iStyle, CPoint pos, int iSize /*= 2*/ )
{
	int		iHalfSize = iSize / 2;
	CPoint	oldPoint;
	// マ�`ク
	POINT point[4];
	switch( iStyle ){
	case MARKCIRCLE:		// ＄
		pDC->Ellipse( pos.x - iHalfSize, pos.y - iHalfSize, pos.x + (iHalfSize + 1), pos.y + (iHalfSize + 1) );
		break;
	case MARKCROSS:			// 〜
		oldPoint = pDC->GetCurrentPosition();
		pDC->MoveTo( pos.x - iHalfSize, pos.y - iHalfSize );
		pDC->LineTo( pos.x + (iHalfSize + 1), pos.y + (iHalfSize + 1) );
		pDC->MoveTo( pos.x - iHalfSize, pos.y + iHalfSize );
		pDC->LineTo( pos.x + (iHalfSize + 1), pos.y - (iHalfSize + 1) );
		pDC->MoveTo( oldPoint );
		break;
	case MARKSQUARE:		// ＆
		pDC->Rectangle( pos.x - iHalfSize, pos.y - iHalfSize,
						pos.x + iHalfSize, pos.y + iHalfSize );
		break;
	case MARKTRYANGLE:		// ＠
		point[0].x = pos.x;				point[0].y = pos.y - iHalfSize;
		point[1].x = pos.x - iHalfSize;	point[1].y = pos.y + iHalfSize;
		point[2].x = pos.x + iHalfSize;	point[2].y = pos.y + iHalfSize;
		pDC->Polygon( point, 3 );
		break;
	case MARKRTRYANGLE:		// ��
		point[0].x = pos.x;				point[0].y = pos.y + iHalfSize;
		point[1].x = pos.x - iHalfSize;	point[1].y = pos.y - iHalfSize;
		point[2].x = pos.x + iHalfSize;	point[2].y = pos.y - iHalfSize;
		pDC->Polygon( point, 3 );
		break;
	case MARKASTERISK:		// ��
		oldPoint = pDC->GetCurrentPosition();
		pDC->MoveTo( pos.x - iHalfSize, pos.y - iHalfSize );
		pDC->LineTo( pos.x + (iHalfSize + 1), pos.y + (iHalfSize + 1) );
		pDC->MoveTo( pos.x - iHalfSize, pos.y + iHalfSize );
		pDC->LineTo( pos.x + (iHalfSize + 1), pos.y - (iHalfSize + 1) );
		pDC->MoveTo( pos.x,				pos.y - iHalfSize );
		pDC->LineTo( pos.x,				pos.y + (iHalfSize + 1) );
		pDC->MoveTo( oldPoint );
		break;
	case MARKPLUS:			// ��
		oldPoint = pDC->GetCurrentPosition();
		pDC->MoveTo( pos.x, pos.y - iHalfSize );
		pDC->LineTo( pos.x, pos.y + (iHalfSize + 1) );
		pDC->MoveTo( pos.x - iHalfSize, pos.y );
		pDC->LineTo( pos.x + (iHalfSize + 1), pos.y );
		pDC->MoveTo( oldPoint );
		break;
	case MARKDIAMOND:		//％
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
 * 	グレイカラ�`�ﾈゝ達�COLORREF�坤�ラ�`�､箸靴栃垢錣譴� 32 ビット�｣�
 *		フルカラ�`�､�らグレイカラ�`���Q瘁の�､鯣ゝ� 
 * 
 * 	@param data	フルカラ�`��
 * 	@return		グレイカラ�`���Q��
 */
COLORREF _stdcall Color2Gray( COLORREF color )
{
	COLORREF grayColor = color;
//竃薦鮫殆 = (0.299 * R + 0.587 * G + 0.114 * B) * 256 / 256
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
// ���B/����
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
 * 	コピ�`コンストラクタ
 * 		嚥えられたCAXGDIFrameをコピ�`する
 * 
 * 	@param org	コピ�`圷CAXGDIFrameクラス
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
 * 	ラインスタイル宙鮫
 * 
 * 	@param pDC			宙鮫デバイスコンテキスト
 * 	@param rect			宙鮫エリア
 * 	@param lineStyle	宙鮫ラインスタイル
 *	@param lOrientation 宙鮫ラインの叔業��0.1＜)
 */
void CAXGDIFrame::DrawLineStyle( CDC *pDC, const CRect &rect, const LINESTYLE &lineStyle, long lOrientation /*= 0*/ )
{
	if(lineStyle.iStyle == PS_NULL)	{	return;	}
	// ペンの恬撹
	CLinePen pen;
	pen.CreatePen( lineStyle.iStyle, lineStyle.iSize, (IsMonochrome() ? IBLACK : lineStyle.color ) );

	// ペンの�x�k
	CPen *pOldPen = pDC->SelectObject( &pen );

	// 宙鮫ポイントの��麻
	CPoint start,end;

	if(lOrientation == 0 || lOrientation == 1800)	{//罪
		start.x = rect.left;			
		end.x = rect.right;
		start.y = end.y = rect.CenterPoint().y;
	}	else if(lOrientation == 900 || lOrientation == -900)	{
		start.x = end.x = rect.CenterPoint().x;
		start.y = rect.top;
		end.y = rect.bottom;
	}	else	{
		// 光��麻�､糧ゝ�
		double dRad= ( M_PI / 180.0 ) * ( lOrientation / 10.0 );
		int iCosX = int(0.5 * rect.Width() * fabs(cos( dRad )));
		int iSinY = int(0.5 * rect.Height() * fabs(sin( dRad )));
		start.x = rect.CenterPoint().x - iCosX;			
		end.x = rect.CenterPoint().x + iCosX;
		start.y = rect.CenterPoint().y - iSinY;
		end.y = rect.CenterPoint().y + iSinY;
	}

	// ��宙鮫
	pDC->MoveTo( start );
	pDC->LineTo( end );

	// ペンを��す
	pDC->SelectObject( pOldPen );

	// ペンの篤��
	pen.DeleteObject();
}
///////////////////////////////////////
/**
 * 	マ�`カ�`宙鮫
 * 
 * 	@param pDC			宙鮫デバイスコンテキスト
 * 	@param rect			宙鮫エリア
 * 	@param markStyle	宙鮫マ�`カ�`スタイル
 *	@param color		宙鮫マ�`カ�`の弼
 */
void CAXGDIFrame::DrawMarker( CDC *pDC, CPoint pos, const MARKERSTYLE &markStyle, COLORREF color )
{
	// マ�`カ�`�oしなら��｢
	if( markStyle.iMarker == MARKNONE ) return;

	// ペンの恬撹
	CPen pen;
	pen.CreatePen( PS_SOLID, 0, (IsMonochrome() ? IBLACK : color ) );
	
	// ペンの�x�k
	CPen *pOldPen = pDC->SelectObject( &pen );
	
	// ブラシの恬撹
	CBrush	brush((IsMonochrome() ? IBLACK : color ));
	
	// ブラシの�x�k
	CBrush *oldBrush = NULL;
	//	brush.CreateSolidBrush( m_lineStyle.color );
	if( IsMonochrome() || markStyle.iBkStyle == 0 ) {
		oldBrush = (CBrush *)pDC->SelectStockObject( NULL_BRUSH );
	}	else	{
		oldBrush = pDC->SelectObject( &brush );
	}

	//マ�`カ�`宙鮫
	::DrawMark( pDC, markStyle.iMarker, pos, markStyle.iMarkSize );

	// ブラシを��す
	pDC->SelectObject( oldBrush );

	// ブラシの篤��
	brush.DeleteObject();

	// ペンを��す
	pDC->SelectObject( pOldPen );

	// ペンの篤��
	pen.DeleteObject();
}
/////////////////////////////////////////////////////////////////////////////
// CAXColorString
//////////////////////////////////////////////////////////////////////
// ���B/����
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
 * 	コピ�`コンストラクタ
 * 		嚥えられたCAXColorStringをコピ�`する
 * 
 * 	@param org	コピ�`圷CAXColorStringクラス
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
 * 	@param	wStyle	宙鮫スタイル
 * 	@param	rect	宙鮫エリア
 * 	@return			圷のスタイル
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
 * 	@param pDC				宙鮫デバイスコンテキスト
 * 	@param rect				宙鮫エリア
 * 	@param font				宙鮫Font
 * 	@param bMonochrome		モノクロ燕幣フラグ
 *	@param lfOrientation	燕幣叔業
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
 * 	@param pDC			宙鮫デバイスコンテキスト
 * 	@param rect			宙鮫エリア
 * 	@param font			宙鮫Font
 * 	@param lpszString	燕幣猟忖双
 * 	@param textColor	燕幣猟忖弼
 * 	@param wStyle		燕幣Style
*/
void CAXColorString::TextDraw( CDC* pDC, CRect &rect, CFont &font, LPCTSTR lpszString, const COLORREF textColor, UINT nDTFormat, long lfOrientation )
{
	CString str(lpszString);
#ifndef _DEBUG
	//set clip area
	pDC->IntersectClipRect( rect );
#endif //_DEBUG
	
	//text color�O協
	COLORREF oldColor = pDC->SetTextColor( textColor );
	//font �O協
	CFont *pOldFont = pDC->SelectObject( &font );
	//バックグラウンド モ�`ド�O協
	int nBkMode = pDC->SetBkMode(TRANSPARENT);
	//get text size
	CSize textSize = pDC->GetTextExtent( str );
	//text point の��麻
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
	//バックグラウンド モ�`ド��す
	pDC->SetBkMode(nBkMode);
	
	//font ��す
	pDC->SelectObject( pOldFont );
	
	//text color ��す
	pDC->SetTextColor( oldColor );
#ifndef _DEBUG
	//clip area free
	pDC->SelectClipRgn( NULL );
#endif //_DEBUG
}
/////////////////////////////////////////////////////////////////////////////
// CAXGDICtrl
//////////////////////////////////////////////////////////////////////
// ���B/����
//////////////////////////////////////////////////////////////////////
CAXGDICtrl::CAXGDICtrl( UINT nKind /*= AXGCTRL_NONE*/, COLORREF bkColor /*= ICTRLCOLOR*/)
	: CAXGDIFrame( bkColor )
{
	///< 兜豚燕幣�rのサイズ
	m_wndSize.cx = 0;
	m_wndSize.cy = 0;
	//ユ�`ザ�`パラメ�`タ�O協.
	SetUserParam( 0, 0 );
	// アクティブ秤�鶻�豚晒
	ClearActiveInfo( &m_activeInfo );
	///< AXGDICtrlの�N����E_AXGDICTRL_KIND歌孚��
	m_nKind = nKind;
}
/**
 * 	コピ�`コンストラクタ
 * 		嚥えられたCAXGDICtrlをコピ�`する
 * 
 * 	@param org	コピ�`圷CAXGDICtrlクラス
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
/// ウィンドウ恬撹�rのメッセ�`ジハンドラ
void CAXGDICtrl::PreSubclassWindow() 
{	// TODO: この了崔に耕嗤の�I尖を弖紗するか、または児云クラスを柵び竃してください

	///< 兜豚燕幣�rのサイズ
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
/// ウィンドウ篤���rのメッセ�`ジハンドラ
void CAXGDICtrl::OnDestroy() 
{
	CWnd::OnDestroy();
	m_wndSize.cx = 0;
	m_wndSize.cy = 0;
}
////////////////////////////////////////////////////
// ウィンドウの宙鮫
void CAXGDICtrl::OnPaint() 
{	// TODO: この了崔にメッセ�`ジ ハンドラ喘のコ�`ドを弖紗してください
	// 宙鮫喘メッセ�`ジとして CStatic::OnPaint() を柵び竃してはいけません
	CPaintDC dc(this); // 宙鮫喘のデバイス コンテキスト
	//get rect size
	CRect rectItem;
	GetClientRect( &rectItem );

	//參和の嘘尚宙鮫は20050929yotsutsu 喘�篇�
	DrawBackground( &dc, rectItem );

	// フォントの函誼
	LOGFONT logfont;
	GetParent()->GetFont()->GetLogFont( &logfont );
	// フォントの恬撹?�x�k
	CFont font;
	font.CreateFontIndirect( &logfont );
	CFont *pOldFont = dc.SelectObject( &font );
	//宙鮫念�I尖
	BeginPaintDC( &dc, rectItem );
	//宙鮫
	DrawDC( &dc, rectItem );
	//����宙鮫
	DrawExDC( &dc, rectItem );
	//Activeな彜�Bを宙鮫
	DrawActiveState( &dc, rectItem );
	// 宙鮫瘁�I尖
	EndPaintDC( &dc, rectItem );
	// フォントを��す
	dc.SelectObject( pOldFont );
	font.DeleteObject();
}
///////////////////////////////////////
// 秘薦フォ�`カスを鞭け函り
void CAXGDICtrl::OnSetFocus(CWnd* pOldWnd)
{
	///< TRUE:�x�k/FALSE:掲�x�k　彜�B
	CWnd::OnSetFocus(pOldWnd);
	if(IsEnableActivate())	{
		m_activeInfo.nActive = AXGCTRLACT_FRAME;		///< 1:畠悶
		NotifyToParent( AXGCN_CHANGE_ACTIVE, NULL );
	}
}
///////////////////////////////////////
// 秘薦フォ�`カスを払った
void CAXGDICtrl::OnKillFocus(CWnd* pNewWnd)
{
	if(pNewWnd && pNewWnd->GetSafeHwnd())	{
		if(pNewWnd->GetOwner() != this)	{
			if(IsEnableActivate())	{
				//m_activeInfo.nActive = AXGCTRLACT_FRAME;		///< 1:畠悶
				m_activeInfo.nActive = AXGCTRLACT_NONE;///< 0:掲�x�k
			}
			Redraw();
		}
	}
	CWnd::OnKillFocus(pNewWnd);
}
///////////////////////////////////////
/// マウス恣ボタン兀和の�rのメッセ�`ジハンドラ
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
/// マウス恣ボタン兀和の�rのメッセ�`ジハンドラ
void CAXGDICtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	if( GetSafeHwnd() )	{
		//if((GetFocus() != this))	{	this->SetFocus();	}
	}

	CWnd::OnRButtonDown(nFlags, point);
}
///////////////////////////////////////
//Activeなアイテムを�筝�する。
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
//Activeなアイテムのスタイルを�筝�する。
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
//Activeなアイテムのスケ�`ルを�筝�する。
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
//Activeなカ�`ソルの了崔を厚仟する。
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
 * �HWndクラスへの宥岑
 *	@param nCode		�I尖すべき宥岑メッセ�`ジのコ�`ド
 *	@param lpActiveInfo	宥岑に�v�B原けられたコントロ�`ルの秤��
 *	@param nKey			兀された�∀襯��` コ�`ドを峺協します。
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
 * Activeなアイテムを�筝�する。(宥岑メッセ�`ジの�I尖)
 *	@param		pNotifyMsg	宥岑メッセ�`ジの秤��
 *	@return		TRUE:�I尖した。/FALSE:隆�I尖
 */
BOOL CAXGDICtrl::OnChangeActive(AXGCNOTIFY *pNotifyMsg )
{
	m_activeInfo = pNotifyMsg->activeInfo;	///< Active彜�Bの秤��
	Redraw();
	
	return TRUE;
}
///////////////////////////////////////
/**
 * Activeなアイテムのスタイルを�筝�する。(宥岑メッセ�`ジの�I尖)
 *	@param		pNotifyMsg	宥岑メッセ�`ジの秤��
 *	@return		TRUE:�I尖した。/FALSE:隆�I尖
 */
BOOL CAXGDICtrl::OnChangeStyle(AXGCNOTIFY *pNotifyMsg )
{
	return FALSE;
}
///////////////////////////////////////
/**
 * Activeなアイテムのスケ�`ルを�筝�する。(宥岑メッセ�`ジの�I尖)
 *	@param		pNotifyMsg	宥岑メッセ�`ジの秤��
 *	@return		TRUE:�I尖した。/FALSE:隆�I尖
 */
BOOL CAXGDICtrl::OnChangeScale(AXGCNOTIFY *pNotifyMsg )
{
	return FALSE;
}
///////////////////////////////////////
/**
 * Activeなカ�`ソルの了崔を厚仟する。(宥岑メッセ�`ジの�I尖)
 *	@param		pNotifyMsg	宥岑メッセ�`ジの秤��
 *	@return		TRUE:�I尖した。/FALSE:隆�I尖
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
 * 	兜豚サイズを�筝�する。
 * 		�F壓のサイズに�筝�する
 *	@return 恷仟のサイズ
 */
const CSize & CAXGDICtrl::RecalcInitSize(void)
{
	CRect rect;
	GetClientRect( rect );
	//兜豚燕幣
	m_wndSize.cx = rect.Width();
	m_wndSize.cy = rect.Height();

	return m_wndSize;
}
///////////////////////////////////////
/**
 * 	Active彜�Bの宙鮫.
 * 		Active彜�Bを燕幣する
 * 
 * 	@param pDC		宙鮫するデバイスコンテキストのポインタ
 * 	@param rect		宙鮫�I囃の����
 */
void CAXGDICtrl::DrawActiveState( CDC *pDC, const CRect &rect )
{
	if( !GetSafeHwnd())	{	return;	}
	if( (GetFocus() == this))	{
		// ブラシの恬撹	
		CBrush	brush;
		brush.CreateSolidBrush(GetBkColor());
	//	COLORREF bkColor = ~GetBkColor();
	//	COLORREF bkColor = ::Color2Gray(GetBkColor());
		int iOldRop = pDC->SetROP2( R2_NOT );
	//	brush.CreateSolidBrush(!bkColor);//::GetSysColor(COLOR_HIGHLIGHT));
		// ブラシの�x�k
		CBrush *pOldBrush = pDC->SelectObject( &brush );
		
		DrawActiveFrame( pDC, rect );

		pDC->SetROP2( iOldRop );
		// ブラシを��す
		pDC->SelectObject( pOldBrush );
		// ブラシの篤��
		brush.DeleteObject();
	}
}
///////////////////////////////////////
/**
 * 	Active彜�Bの宙鮫.
 * 		Active彜�Bを燕幣する
 * 
 * 	@param pDC		宙鮫するデバイスコンテキストのポインタ
 * 	@param rect		宙鮫�I囃の����
 */
void CAXGDICtrl::DrawActiveFrame( CDC *pDC, const CRect &rect, int size )
{
	CRect rectItem = rect;
	//フレ�`ム
	//恣貧
	rectItem.bottom = rectItem.top + size;
	rectItem.right = rectItem.left + size;
	pDC->Rectangle( rectItem );
	//恣嶄
	rectItem.top = ( rect.top + rect.bottom - size ) / 2;
	rectItem.bottom = rectItem.top + size;
	pDC->Rectangle( rectItem );
	//恣和
	rectItem.top = rect.bottom - size;
	rectItem.bottom = rect.bottom;
	pDC->Rectangle( rectItem );
	//嶄和
	rectItem.left = (rect.left + rect.right - size ) / 2 ;
	rectItem.right = rectItem.left + size;
	pDC->Rectangle( rectItem );
	//嘔和
	rectItem.left = rect.right - size;
	rectItem.right = rect.right;
	pDC->Rectangle( rectItem );
	//嘔嶄
	rectItem.top = ( rect.top + rect.bottom - size ) / 2 ;
	rectItem.bottom = rectItem.top + size;
	pDC->Rectangle( rectItem );
	//嘔貧
	rectItem.top = rect.top;
	rectItem.bottom = rectItem.top + size;
	pDC->Rectangle( rectItem );
	//嶄貧
	rectItem.left = (rect.left + rect.right - size ) / 2 ;
	rectItem.right = rectItem.left + size;
	pDC->Rectangle( rectItem );
}
///////////////////////////////////////
/**
 * 	PrintDCに宙鮫する.��咫泡喘��
 * 		峺協されたDCに宙鮫する
 * 
 * 	@param pDC			宙鮫するDC
 * 	@param rect			宙鮫する�I囃のRECT
 * 	@param bMonochrome	モノクロ�`ム咫泡の嗤��/�o��
 * 	@param bMonochrome	����宙鮫の嗤��/�o��
 */
void CAXGDICtrl::PrintDC( CDC *pDC, const CRect &rect, BOOL bMonochrome /*= FALSE*/, BOOL bDrawExFlag /*= FALSE*/ )
{
	// フォントの函誼
	LOGFONT logfont;
	GetParent()->GetFont()->GetLogFont( &logfont );
	//Font size の�{屁
	if(GetInitSize().cx > 0 && GetInitSize().cy > 0)	{
		if( rect.Height() > rect.Width() )	{
			logfont.lfHeight = FtoL((double)logfont.lfHeight * rect.Width() / GetInitSize().cx  + 0.5) ;
		}	else	{
			logfont.lfHeight = FtoL((double)logfont.lfHeight * rect.Height() / GetInitSize().cy  + 0.5) ;
		}
	}	else	{
		logfont.lfHeight = -MulDiv( 9, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	}

	// フォントの恬撹?�x�k
	CFont font;
	font.CreateFontIndirect( &logfont );
	CFont *pOldFont = pDC->SelectObject( &font );

	//モノクロ�`ム咫泡の嗤��/�o��
	BOOL bOld = EnableMonochrome( bMonochrome );

	//宙鮫
	DrawDC( pDC, rect );

	//����宙鮫
	if(bDrawExFlag)	{	DrawExDC( pDC, rect );	}

	//モノクロ�`ム咫泡の嗤��/�o��
	EnableMonochrome( bOld );

	//fontを圷に��す & ��茅
	pDC->SelectObject( pOldFont );
	font.DeleteObject();

}
/////////////////////////////////////////////////////////////////////////////
// CAXStringWnd
//////////////////////////////////////////////////////////////////////
// ���B/����
//////////////////////////////////////////////////////////////////////
CAXStringWnd::CAXStringWnd( COLORREF bkColor /*= ICTRLCOLOR*/)
{
	m_strData = _T("");
	SetTextSizeAdjust(FALSE);	///< Test size adjust
	m_lfOrientation = 0;//宙鮫圭��
	SetBkColor(bkColor);
	m_nKind = AXGCTRL_STRING;
}
///////////////////////////////////////
/**
 * 	コピ�`コンストラクタ
 * 		嚥えられたCAXStringWndをコピ�`する
 * 
 * 	@param org	コピ�`圷CAXStringWndクラス
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
{	// TODO: この了崔に耕嗤の�I尖を弖紗するか、または児云クラスを柵び竃してください
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
			//猟忖徭悶がrect sizeを階えるので、spaceですこし弌さめにしてある。
			if(m_lfOrientation == 900 || m_lfOrientation == -900)	{
				long lSpace = rect.Width() * 25 / 100;	//とりあえず25��
				logFont.lfHeight = rect.Width() - lSpace;
			}	else	{
				long lSpace = rect.Height() * 25 / 100;	//とりあえず25��
				logFont.lfHeight = rect.Height() - lSpace;
			}
		}
		logFont.lfWeight = FW_NORMAL;			//湊さ defaultは FW_NORMALの400。FW_HEAVYは900
	//	logFont.lfWidth  = rect.Width() / 10 ;	//罪嫌函ると�欧譴襪里牌�吭
	}
	//	宙鮫圭�� 猟忖の児��と x �Sとの叔業を (0.1 業�g了で) 峺協します。叔業は y 圭�鬚�和�鬚�の恙�墨気任� x �Sから郡�r��指りに、y 圭�鬚�貧�鬚�の恙�墨気任��r��指りに���yします。
	logFont.lfOrientation = m_lfOrientation;
	logFont.lfEscapement = m_lfOrientation;

	//font create
	font.CreateFontIndirect( &logFont );

	//COLORREF textColor = ( IsMonochrome() ? IBLACK : GetStrColor() );

	CAXColorString::TextDraw( pDC, rect , font, IsMonochrome(), m_lfOrientation );	

	font.DeleteObject();
}