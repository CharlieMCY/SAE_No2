// AXGdiWnd.cpp クラスのインプリメンテーション
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

#include "stdafx.h"
#include "AXGdiWnd.h"
#include "linestyledlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// CLineStyleDisp

CLineStyleDisp::CLineStyleDisp(COLORREF bkColor /*= ICTRLCOLOR*/)
{
//	memset(&m_lineStyle, 0x00, sizeof(LINESTYLE) );
//	m_lineStyle.iStyle = PS_NULL;
//	m_lineStyle.color  = RGB( 0xff,0xff,0xff );
//	m_lineStyle.iSize  = 0;

//	memset(&m_markStyle, 0x00, sizeof(MARKERINFO) );
	SetLineMargins();
	m_bSepareterVisible = FALSE;	///< セパレート枠表示フラグ
	SetSeparateRatio(0.5);
	SetBkColor(bkColor);
	m_nKind = AXGCTRL_LINESTYLE;
}

CLineStyleDisp::~CLineStyleDisp()
{
}

BEGIN_MESSAGE_MAP(CLineStyleDisp, CAXStringWnd)
	//{{AFX_MSG_MAP(CLineStyleDisp)
//	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
//	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineStyleDisp メッセージ ハンドラ
/////////////////////////////////////////////////////////////////////////////
// 初期化
void CLineStyleDisp::PreSubclassWindow() 
{
	CAXStringWnd::PreSubclassWindow();
}
/**
 * 	サンプル線描画
 * 
 *
void CLineStyleDisp::OnPaint() 
{
	CPaintDC dc(this); // 描画用のデバイス コンテキスト

	// RECTをCRectへ
	CRect rectItem;
	GetClientRect( rectItem );
	DrawItem( &dc, rectItem );
	//if(GetFocus())	{	dc.DrawFocusRect(rectItem);	}
}
/**
 * 	描画エリアダブルクリック時の処理
 * 
 * 	@param uFlags	....
 * 	@param point	クリック位置
 */
void CLineStyleDisp::OnLButtonDblClk(UINT nFlags, CPoint point) 
{

	NotifyToParent( AXGCN_CHANGE_STYLE, NULL );

	CWnd::OnLButtonDblClk(nFlags, point);
}
/////////////////////////////////////////////////////////////////////////////
/**
 * 	描画
 * 
 * 	@param *pDC		描画するデバイスコンテキスト
 * 	@param rect		描画するエリア
 */
void CLineStyleDisp::DrawItem( CDC *pDC, CRect rect, CFont *pTextFont /*= NULL*/ )
{
	CAXGDIFrame::DrawBackground( pDC, rect );
	CAXGDIFrame::DrawFrame( pDC, rect );

	double dSize = 0.0;
	CRect rectItems = rect;

	if(m_lfOrientation == 900 || m_lfOrientation == -900)	{
		dSize = ((double)rect.Height()) * GetSeparateRatio() ;	//Item 分解
		rectItems.bottom = (int)(dSize + 0.5 ) + rectItems.top;
		if(rectItems.Height() > (m_iMargin * 2) )	{
			rectItems.DeflateRect( 0, m_iMargin );
			// 線の描画
			if(m_lfOrientation == 900)	{
				TextDraw( pDC, rectItems, pTextFont );
			}	else	{
				DrawLineStyle( pDC, rectItems, GetLineStyle(), m_lfOrientation );
			}
			rectItems.InflateRect( 0, m_iMargin );
			if(m_lfOrientation != 900)	{
				// マーカー描画
				DrawMarker( pDC, rectItems.CenterPoint(), GetMarkerStyle(), GetLineStyle().color );
			}
			rectItems.top = rectItems.bottom;
			if(m_bSepareterVisible)	{	///< セパレート枠表示フラグ)
				DrawSeparater(pDC, rectItems);
			}
		}
		rectItems.top = rectItems.bottom;
		rectItems.bottom = rect.bottom;
		rectItems.DeflateRect( 0, m_iMargin );
		if(m_lfOrientation == 900)	{
			DrawLineStyle( pDC, rectItems, GetLineStyle(), m_lfOrientation );
		}	else	{
			TextDraw( pDC, rectItems, pTextFont );
		}
		rectItems.InflateRect( 0, m_iMargin );
		if(m_lfOrientation == 900)	{
			DrawMarker( pDC, rectItems.CenterPoint(), GetMarkerStyle(), GetLineStyle().color );
		}
	}	else	{
		dSize = ((double)rect.Width()) * GetSeparateRatio() ;	//Item 分解	
		rectItems.right = (int)(dSize + 0.5 ) + rectItems.left;
		if(rectItems.Width() > (m_iMargin * 2) )	{
			rectItems.DeflateRect( m_iMargin, 0 );
			// 線の描画
			DrawLineStyle( pDC, rectItems, GetLineStyle());

			rectItems.InflateRect( m_iMargin, 0 );
			// マーカー描画
			DrawMarker( pDC, rectItems.CenterPoint(), GetMarkerStyle(), GetLineStyle().color );

			rectItems.left = rectItems.right;
			if(m_bSepareterVisible)	{	///< セパレート枠表示フラグ)
				DrawSeparater(pDC, rectItems);
			}
		}	

		rectItems.left = rectItems.right;
		rectItems.right = rect.right;

		rectItems.DeflateRect( m_iMargin, 0 );
		TextDraw( pDC, rectItems, pTextFont );
		rectItems.InflateRect( m_iMargin, 0 );
	}
	//if(GetFocus() == this )	{	pDC->DrawFocusRect(rect);	}
}
/**
 * 	セパレート線描画
 * 
 * 	@param *pDC		描画するデバイスコンテキスト
 * 	@param rect		描画するエリア
 */
void CLineStyleDisp::DrawSeparater( CDC *pDC, const CRect &rect )
{
	//pDC->FrameRect( rect, &CBrush((IsMonochrome() ? c_colorBlack : GetFrameColor())) );	}
	// ペンの作成
	CPen pen;
	pen.CreatePen( PS_SOLID, 0, (IsMonochrome() ? IBLACK : GetFrameColor() ) );

	// ペンの選択
	CPen *pOldPen = pDC->SelectObject( &pen );

	// 線描画
	pDC->MoveTo( rect.left, rect.top );
	pDC->LineTo( rect.right, rect.bottom );

	// ペンを戻す
	pDC->SelectObject( pOldPen );

	// ペンの破棄
	pen.DeleteObject();
}
/**
 * 	スタイルを変更する。
 * 
 *	@param		pNotifyMsg	通知メッセージの情報
 */
BOOL CLineStyleDisp::OnChangeStyle(AXGCNOTIFY *pNotifyMsg )
{
	CLineStyleDlg lineStyleDlg;

	lineStyleDlg.DoModal(GetLineStyle(),GetMarkerStyle());
	SetLineStyle(lineStyleDlg.GetLineStyle());
	SetMarkerStyle(lineStyleDlg.GetMarkerStyle());
	Redraw();

	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CLineButton
/// コンストラクタ
CLineButton::CLineButton()
{
	m_iCheck   = 0;
	m_bBtnDown = FALSE;

}

/// デストラクタ
CLineButton::~CLineButton()
{
}


BEGIN_MESSAGE_MAP(CLineButton, CButton)
	//{{AFX_MSG_MAP(CLineButton)
	ON_WM_LBUTTONUP()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineButton メッセージ ハンドラ

/// サブクラス化する前に呼ばれるメッセージハンドラ
void CLineButton::PreSubclassWindow() 
{
#ifdef _DEBUG
	// OwnerDraw設定されていたら警告
	if( GetButtonStyle()==BS_OWNERDRAW ){
		AfxMessageBox( "CLineButton リソース上のOwnerDrawチェックをはずして下さい" );
	}
#endif

	// スタイルの保持
	m_uiStyle = GetButtonStyle();

	// OwnerDrawに設定(ただしButton型以外のCheckBox非対応)
	if( !(GetButtonStyle()&BS_CHECKBOX && !(GetStyle()&BS_PUSHLIKE)) ){
		SetButtonStyle( GetButtonStyle()|BS_OWNERDRAW );
	}

	// OwnerDrawへ
	SetButtonStyle( GetButtonStyle()|BS_OWNERDRAW );

	CButton::PreSubclassWindow();
}

/**
 * 	オーナー描画の為に呼ばれるメッセージハンドラ
 * 
 * 	@param lpDrawItemStruct	描画する項目や描画種別に関する情報を指定します。
 * 
 */
void CLineButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC   dc;
	UINT  state = lpDrawItemStruct->itemState;	
	CRect rect	= lpDrawItemStruct->rcItem;
	dc.Attach( lpDrawItemStruct->hDC );

	// 押下中
	if( state&ODS_SELECTED||m_iCheck ){
		dc.DrawFrameControl( rect, DFC_BUTTON, DFCS_ADJUSTRECT|DFCS_BUTTONPUSH|DFCS_PUSHED );
		dc.FillSolidRect( rect, m_bkColor );

		// 文字を凹ませる
		if( state&ODS_SELECTED ){
			rect.OffsetRect( 0, 1 );
			rect.DeflateRect( 1, 0 );
		}
	// 通常
	} else{
		dc.DrawFrameControl( rect, DFC_BUTTON, DFCS_ADJUSTRECT|DFCS_BUTTONPUSH );
		dc.FillSolidRect( rect, m_bkColor );
	}

	// 線を描画
	DrawLineStyle( &dc, rect, m_lineStyle);
	// マーク描画
	DrawMarker( &dc, rect.CenterPoint(), GetMarkerStyle(), GetLineStyle().color );

	// 通常ボタン
	if( !(state&ODS_SELECTED||m_iCheck) ) dc.DrawEdge( rect, EDGE_RAISED, BF_RECT );

	// Focus有りならFocus枠描画
	rect = lpDrawItemStruct->rcItem;
	if( state&ODS_FOCUS ){
		// CheckBoxじゃない&Focus有りならボタン枠描画
		if( !(m_uiStyle&BS_CHECKBOX) ){
			FrameRect( dc.m_hDC, rect, (HBRUSH)GetStockObject( BLACK_BRUSH ) );
		}
		rect.DeflateRect( 4, 4 );
		dc.DrawFocusRect( rect );
	}

	// DCのデタッチ
	dc.Detach();
}

/**
 * 	マウス左ボタンを押したときに呼ばれるメッセージハンドラ
 * 
 * 	@param nFlags	どの種類の仮想キーが押されているかを示します。
 * 	@param point	カーソルの x 座標と y 座標を指定します。座標は、常にウィンドウの左上隅からの相対位置になります
 */
void CLineButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect rect;
	GetClientRect( rect );
	if( rect.PtInRect( point ) ) m_bBtnDown = TRUE;
	
	CButton::OnLButtonDown(nFlags, point);
}

/**
 * 	マウス左ボタンをダブルクリックしたときに呼ばれるメッセージハンドラ
 * 
 * 	@param nFlags	どの種類の仮想キーが押されているかを示します。
 * 	@param point	カーソルの x 座標と y 座標を指定します。座標は、常にウィンドウの左上隅からの相対位置になります
 */
void CLineButton::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CRect rect;
	GetClientRect( rect );
	if( rect.PtInRect( point ) ) m_bBtnDown = TRUE;
	
	CButton::OnLButtonDblClk(nFlags, point);
}

/**
 * 	マウス左ボタンを離したときに呼ばれるメッセージハンドラ
 * 
 * 	@param nFlags	どの種類の仮想キーが押されているかを示します。
 * 	@param point	カーソルの x 座標と y 座標を指定します。座標は、常にウィンドウの左上隅からの相対位置になります
 */
void CLineButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CRect rect;
	GetClientRect( rect );
	if( m_bBtnDown && rect.PtInRect( point ) ){
		SetCheck( m_iCheck? 0: 1 );
		Invalidate();
		UpdateWindow();
	}
	m_bBtnDown = FALSE;
	CButton::OnLButtonUp(nFlags, point);
}

/**
 * 	非システム キーが離されたときに呼ばれるメッセージハンドラ
 * 
 * 	@param nChar	指定されたキーの仮想キー コード
 * 	@param nRepCnt	リピート カウント
 * 	@param nFlags	スキャン コード、キー変換コード、直前のキー状態、コンテキスト コード
 */
void CLineButton::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( nChar == VK_SPACE ){
		SetCheck( m_iCheck? 0: 1 );
	}
	CButton::OnKeyUp(nChar, nRepCnt, nFlags);
}

/////////////////////////////////////////////////////////////////////////////
/// 再表示
void CLineButton::Redraw(BOOL bErase /*= FALSE*/)
{
	if( IsWindow( m_hWnd ) ){
		Invalidate(bErase);
		UpdateWindow();
	}
}

/////////////////////////////////////////////////////////////////////////////
/**
 * 	チェック状態を取得します.
 * 
 * 	@return		0:チェックオフ	1:チェックオン
 */
int CLineButton::GetCheck()
{
	return m_iCheck;
}

/**
 * 	チェック状態を設定します.
 * 
 * 	@param	iCheck	0:チェックオフ	1:チェックオン
 * 
 * 	@warning		ボタンスタイルがチェックスタイルでない時には何もしません。
 */
void CLineButton::SetCheck( int iCheck )
{
	if( m_uiStyle&BS_CHECKBOX ){
		m_iCheck = iCheck;
		
		// 表示更新
		Redraw();
	}
}
/////////////////////////////////////////////////////////////////////////////
#define	LINE_STYLE		5
#define	LINE_SIZE		5
#define	MARK_STYLE		9
#define	MARK_SIZE		9
#define	MARK_BKSTYLE	2
const int CLineStyleDlg::c_iLineStyle[LINE_STYLE] = {	PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT };
const int CLineStyleDlg::c_iMarkStyle[MARK_STYLE] = {	0,
										MARKCIRCLE,
										MARKCROSS,
										MARKSQUARE,
										MARKTRYANGLE,
										MARKRTRYANGLE,
										MARKDIAMOND,
										MARKASTERISK,
										MARKPLUS };

const char * CLineStyleDlg::c_cLineSize[LINE_SIZE]  = { "0", "1", "2", "3", "4" };
const char * CLineStyleDlg::c_cMarkSize[MARK_SIZE]  = { "5", "6", "7", "8", "9", "10", "11", "12", "13" };
const char * CLineStyleDlg::c_cMarkBkStyle[MARK_BKSTYLE]  = { "OFF", "ON" };

/////////////////////////////////////////////////////////////////////////////
// CLineStyleDlg

IMPLEMENT_DYNAMIC(CLineStyleDlg, CColorDialog)

CLineStyleDlg::CLineStyleDlg(COLORREF clrInit, DWORD dwFlags, CWnd* pParentWnd) :
	CColorDialog(clrInit, dwFlags, pParentWnd)
{
	m_cc.hInstance	 = (HWND)AfxGetResourceHandle();
	m_cc.Flags		|= CC_ENABLETEMPLATE;
	m_cc.lpTemplateName = "ChooseLineStyle";

	m_iShowLineType = SW_SHOW;
	m_iShowLineSize = SW_SHOW;
	m_iShowMarkType = SW_SHOW;
	m_iShowMarkSize = SW_SHOW;
	m_iShowMarkBkStyle = SW_SHOW;

}

void CLineStyleDlg::DoDataExchange(CDataExchange* pDX)
{
	CColorDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLineStyleDlg)
	DDX_Control(pDX, IDC_CMB_LINESTYLE, m_lineTypeCombo);
	DDX_Control(pDX, IDC_CMB_LINESIZE, m_lineSizeCombo);
	DDX_Control(pDX, IDC_CMB_MARKSTYLE, m_markTypeCombo);
	DDX_Control(pDX, IDC_CMB_MARKSIZE, m_markSizeCombo);
	DDX_Control(pDX, IDC_CMB_MARKBKSTYLE, m_markBkStyleCombo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLineStyleDlg, CColorDialog)
	//{{AFX_MSG_MAP(CLineStyleDlg)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////

BOOL CLineStyleDlg::OnInitDialog() 
{
	CColorDialog::OnInitDialog();

	if(GetColor() != m_lineStyle.color)	{
		SetCurrentColor(m_lineStyle.color);
	}

	int i;
	// 表示/非表示設定
	GetDlgItem( IDC_TITL_LINESTYLE )->ShowWindow( m_iShowLineType );
	GetDlgItem( IDC_TITL_LINESIZE  )->ShowWindow( m_iShowLineSize );
	GetDlgItem( IDC_TITL_MARKSTYLE )->ShowWindow( m_iShowMarkType );
	GetDlgItem( IDC_TITL_MARKSIZE  )->ShowWindow( m_iShowMarkSize );
	GetDlgItem( IDC_TITL_MARKBKSTYLE  )->ShowWindow( m_iShowMarkBkStyle );
	m_lineTypeCombo.ShowWindow( m_iShowLineType );
	m_lineSizeCombo.ShowWindow( m_iShowLineSize );
	m_markTypeCombo.ShowWindow( m_iShowMarkType );
	m_markSizeCombo.ShowWindow( m_iShowMarkSize );
	m_markBkStyleCombo.ShowWindow( m_iShowMarkBkStyle );

	// 線種データセット
	int iLineHeight = m_lineSizeCombo.GetItemHeight( -1 );
	m_lineTypeCombo.SetItemHeight( -1, iLineHeight );
	for( i = 0; i < LINE_STYLE; i++ ){
		int iIndx = m_lineTypeCombo.InsertString( -1, "dmy" );
		m_lineTypeCombo.SetItemData( iIndx, c_iLineStyle[i] );
		m_lineTypeCombo.SetItemHeight( i, iLineHeight );

		// 初期値設定
		if( GetPenStyle() == c_iLineStyle[i] ) m_lineTypeCombo.SetCurSel( i );
	}
	// 線サイズデータセット
	int iLineSizeHeight = m_lineSizeCombo.GetItemHeight( -1 );
	m_lineSizeCombo.SetItemHeight( -1, iLineSizeHeight );
	for( i = 0; i < LINE_SIZE; i++ ){
		int iIndx = m_lineSizeCombo.InsertString( -1, c_cLineSize[i] );
		//int iIndx = m_lineSizeCombo.InsertString( -1, "dmy" );
		m_lineSizeCombo.SetItemData( iIndx, i );
		m_lineSizeCombo.SetItemHeight( i, iLineSizeHeight );
	//DELL	m_lineSizeCombo.InsertString( -1, c_cLineSize[i] );
		if( GetLineSize() == atoi( c_cLineSize[i] ) ) m_lineSizeCombo.SetCurSel( i );
	}

	// マーク種データセット
	int iMarkHeight = m_markSizeCombo.GetItemHeight( -1 );
	m_markTypeCombo.SetItemHeight( -1, iLineHeight );
	for( i = 0; i < MARK_STYLE; i++ ){
		int iIndx = m_markTypeCombo.InsertString( -1, "dmy" );
		m_markTypeCombo.SetItemData( iIndx, c_iMarkStyle[i] );
		m_markTypeCombo.SetItemHeight( i, iMarkHeight );

		// 初期値設定
		if( GetMarkerKind() == c_iMarkStyle[i] ) m_markTypeCombo.SetCurSel( i );		
	}

	// マークサイズデータセット
	for( i = 0; i < MARK_SIZE; i++ ){
		m_markSizeCombo.InsertString( -1, c_cMarkSize[i] );
		if( GetMarkerSize() == atoi( c_cMarkSize[i] ) ) m_markSizeCombo.SetCurSel( i );
	}
	
	// マーカー背景データセット
	for( i = 0; i < MARK_BKSTYLE; i++ ){
		m_markBkStyleCombo.InsertString( -1, c_cMarkBkStyle[i] );
		if( GetMarkerBkStyle() == i )	m_markBkStyleCombo.SetCurSel( i );
	}

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

/**
 * 	OKボタン押下時処理.
 * 		設定の保存
 * 
 */
void CLineStyleDlg::OnOK()
{
	int iIndx;
	CString strTemp;

	// ライン種別
	iIndx = m_lineTypeCombo.GetCurSel();
	if( iIndx != CB_ERR ) m_lineStyle.iStyle = m_lineTypeCombo.GetItemData( iIndx );

	// 線サイズ
	m_lineSizeCombo.GetWindowText( strTemp );
	m_lineStyle.iSize = atoi( strTemp );

	// マーク種別
	iIndx = m_markTypeCombo.GetCurSel();
	if( iIndx != CB_ERR ) m_markStyle.iMarker = m_markTypeCombo.GetItemData( iIndx );

	//マークサイズ
	m_markSizeCombo.GetWindowText( strTemp );
	m_markStyle.iMarkSize = atoi( strTemp );

	// マーカー背景
	iIndx = m_markBkStyleCombo.GetCurSel();
	if( iIndx != CB_ERR ) m_markStyle.iBkStyle = iIndx;


	CColorDialog::OnOK();

	// 線の色
	m_lineStyle.color = GetColor();
}

/**
 * 	遷移時に設定種別を判定する.
 * 
 * 	@param	iStyle		線種
 * 	@param	iSize		線サイズ
 * 	@param	iMarker		マーク種
 * 	@param	iMarkSize	マークサイズ
 *	@return	int		IDOK, IDCANCEL
 */
int CLineStyleDlg::DoModal( int iStyle /*= PS_SOLID*/, int iSize /*= 0*/, int iMarker /*= 0*/, int iMarkSize /*= 8*/ )
{
	m_lineStyle.iStyle = iStyle;		// 線種
	m_lineStyle.iSize = iSize;			// 線サイズ
	m_markStyle.iMarker = iMarker;		// マーク種
	m_markStyle.iMarkSize = iMarkSize;	// マークサイズ

	return CColorDialog::DoModal();
}

/**
 * 	オーナ描画コントロールの描画.
 * 		線種設定?マーク種設定のコンボボックスを描画する為に呼ばれます。
 * 
 * 	@param nIDCtl			描画アイテムのID
 * 	@param lpDrawItemStruct	描画情報
 */
void CLineStyleDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// DC取得
	CDC *pDC = CDC::FromHandle( lpDrawItemStruct->hDC );

	// Rect取得
	CRect rect = lpDrawItemStruct->rcItem;

	// 背景色
	COLORREF textColor;
	if( lpDrawItemStruct->itemState & ODS_SELECTED ){
		pDC->FillSolidRect( rect, GetSysColor( COLOR_HIGHLIGHT ) );
		textColor = GetSysColor( COLOR_HIGHLIGHTTEXT );
	} else{
		pDC->FillSolidRect( rect, GetSysColor( COLOR_WINDOW ) );
		textColor = GetSysColor( COLOR_WINDOWTEXT );
	}

	// 線種
	if( nIDCtl == IDC_CMB_LINESTYLE ){
		// 線
		if( (int)lpDrawItemStruct->itemID >= 0 ){
			CPen pen( c_iLineStyle[lpDrawItemStruct->itemID], 0, textColor );
			pDC->SelectObject( pen );
			pDC->MoveTo( rect.left, rect.top + rect.Height()/2 );
			pDC->LineTo( rect.right,rect.top + rect.Height()/2 );
		}
	// 線の太さ
	/*} else if( nIDCtl == IDC_CMB_LINESIZE )	{
		if( (int)lpDrawItemStruct->itemID >= 0 ){
			CPen pen( PS_SOLID, lpDrawItemStruct->itemID , textColor );
			pDC->SelectObject( pen );
			pDC->MoveTo( rect.left, rect.top + rect.Height()/2 );
			pDC->LineTo( rect.right,rect.top + rect.Height()/2 );
		}*/
	// マーク
	} else if( nIDCtl == IDC_CMB_MARKSTYLE ){
		// ペンの作成
		CPen pen( PS_SOLID, 0, textColor );
		pDC->SelectObject( pen );

		int iMarkStyle = m_markTypeCombo.GetItemData( lpDrawItemStruct->itemID );
		CRect rect = lpDrawItemStruct->rcItem;
		::DrawMark( pDC, iMarkStyle, rect.CenterPoint() );

	} else{
		CColorDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
	}
}