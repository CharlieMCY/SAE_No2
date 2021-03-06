// AXGdiWnd.cpp クラスのインプリメンテ�`ション
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
	m_bSepareterVisible = FALSE;	///< セパレ�`ト��燕幣フラグ
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
// CLineStyleDisp メッセ�`ジ ハンドラ
/////////////////////////////////////////////////////////////////////////////
// 兜豚晒
void CLineStyleDisp::PreSubclassWindow() 
{
	CAXStringWnd::PreSubclassWindow();
}
/**
 * 	サンプル��宙鮫
 * 
 *
void CLineStyleDisp::OnPaint() 
{
	CPaintDC dc(this); // 宙鮫喘のデバイス コンテキスト

	// RECTをCRectへ
	CRect rectItem;
	GetClientRect( rectItem );
	DrawItem( &dc, rectItem );
	//if(GetFocus())	{	dc.DrawFocusRect(rectItem);	}
}
/**
 * 	宙鮫エリアダブルクリック�rの�I尖
 * 
 * 	@param uFlags	....
 * 	@param point	クリック了崔
 */
void CLineStyleDisp::OnLButtonDblClk(UINT nFlags, CPoint point) 
{

	NotifyToParent( AXGCN_CHANGE_STYLE, NULL );

	CWnd::OnLButtonDblClk(nFlags, point);
}
/////////////////////////////////////////////////////////////////////////////
/**
 * 	宙鮫
 * 
 * 	@param *pDC		宙鮫するデバイスコンテキスト
 * 	@param rect		宙鮫するエリア
 */
void CLineStyleDisp::DrawItem( CDC *pDC, CRect rect, CFont *pTextFont /*= NULL*/ )
{
	CAXGDIFrame::DrawBackground( pDC, rect );
	CAXGDIFrame::DrawFrame( pDC, rect );

	double dSize = 0.0;
	CRect rectItems = rect;

	if(m_lfOrientation == 900 || m_lfOrientation == -900)	{
		dSize = ((double)rect.Height()) * GetSeparateRatio() ;	//Item 蛍盾
		rectItems.bottom = (int)(dSize + 0.5 ) + rectItems.top;
		if(rectItems.Height() > (m_iMargin * 2) )	{
			rectItems.DeflateRect( 0, m_iMargin );
			// ��の宙鮫
			if(m_lfOrientation == 900)	{
				TextDraw( pDC, rectItems, pTextFont );
			}	else	{
				DrawLineStyle( pDC, rectItems, GetLineStyle(), m_lfOrientation );
			}
			rectItems.InflateRect( 0, m_iMargin );
			if(m_lfOrientation != 900)	{
				// マ�`カ�`宙鮫
				DrawMarker( pDC, rectItems.CenterPoint(), GetMarkerStyle(), GetLineStyle().color );
			}
			rectItems.top = rectItems.bottom;
			if(m_bSepareterVisible)	{	///< セパレ�`ト��燕幣フラグ)
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
		dSize = ((double)rect.Width()) * GetSeparateRatio() ;	//Item 蛍盾	
		rectItems.right = (int)(dSize + 0.5 ) + rectItems.left;
		if(rectItems.Width() > (m_iMargin * 2) )	{
			rectItems.DeflateRect( m_iMargin, 0 );
			// ��の宙鮫
			DrawLineStyle( pDC, rectItems, GetLineStyle());

			rectItems.InflateRect( m_iMargin, 0 );
			// マ�`カ�`宙鮫
			DrawMarker( pDC, rectItems.CenterPoint(), GetMarkerStyle(), GetLineStyle().color );

			rectItems.left = rectItems.right;
			if(m_bSepareterVisible)	{	///< セパレ�`ト��燕幣フラグ)
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
 * 	セパレ�`ト��宙鮫
 * 
 * 	@param *pDC		宙鮫するデバイスコンテキスト
 * 	@param rect		宙鮫するエリア
 */
void CLineStyleDisp::DrawSeparater( CDC *pDC, const CRect &rect )
{
	//pDC->FrameRect( rect, &CBrush((IsMonochrome() ? c_colorBlack : GetFrameColor())) );	}
	// ペンの恬撹
	CPen pen;
	pen.CreatePen( PS_SOLID, 0, (IsMonochrome() ? IBLACK : GetFrameColor() ) );

	// ペンの�x�k
	CPen *pOldPen = pDC->SelectObject( &pen );

	// ��宙鮫
	pDC->MoveTo( rect.left, rect.top );
	pDC->LineTo( rect.right, rect.bottom );

	// ペンを��す
	pDC->SelectObject( pOldPen );

	// ペンの篤��
	pen.DeleteObject();
}
/**
 * 	スタイルを�筝�する。
 * 
 *	@param		pNotifyMsg	宥岑メッセ�`ジの秤��
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
// CLineButton メッセ�`ジ ハンドラ

/// サブクラス晒する念に柵ばれるメッセ�`ジハンドラ
void CLineButton::PreSubclassWindow() 
{
#ifdef _DEBUG
	// OwnerDraw�O協されていたら少御
	if( GetButtonStyle()==BS_OWNERDRAW ){
		AfxMessageBox( "CLineButton リソ�`ス貧のOwnerDrawチェックをはずして和さい" );
	}
#endif

	// スタイルの隠隔
	m_uiStyle = GetButtonStyle();

	// OwnerDrawに�O協(ただしButton侏參翌のCheckBox掲����)
	if( !(GetButtonStyle()&BS_CHECKBOX && !(GetStyle()&BS_PUSHLIKE)) ){
		SetButtonStyle( GetButtonStyle()|BS_OWNERDRAW );
	}

	// OwnerDrawへ
	SetButtonStyle( GetButtonStyle()|BS_OWNERDRAW );

	CButton::PreSubclassWindow();
}

/**
 * 	オ�`ナ�`宙鮫の�蕕忘瑤个譴襯瓮奪皐`ジハンドラ
 * 
 * 	@param lpDrawItemStruct	宙鮫する��朕や宙鮫�N�eに�vする秤�鵑鰆原┐靴泙后�
 * 
 */
void CLineButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC   dc;
	UINT  state = lpDrawItemStruct->itemState;	
	CRect rect	= lpDrawItemStruct->rcItem;
	dc.Attach( lpDrawItemStruct->hDC );

	// 兀和嶄
	if( state&ODS_SELECTED||m_iCheck ){
		dc.DrawFrameControl( rect, DFC_BUTTON, DFCS_ADJUSTRECT|DFCS_BUTTONPUSH|DFCS_PUSHED );
		dc.FillSolidRect( rect, m_bkColor );

		// 猟忖を絢ませる
		if( state&ODS_SELECTED ){
			rect.OffsetRect( 0, 1 );
			rect.DeflateRect( 1, 0 );
		}
	// 宥械
	} else{
		dc.DrawFrameControl( rect, DFC_BUTTON, DFCS_ADJUSTRECT|DFCS_BUTTONPUSH );
		dc.FillSolidRect( rect, m_bkColor );
	}

	// ��を宙鮫
	DrawLineStyle( &dc, rect, m_lineStyle);
	// マ�`ク宙鮫
	DrawMarker( &dc, rect.CenterPoint(), GetMarkerStyle(), GetLineStyle().color );

	// 宥械ボタン
	if( !(state&ODS_SELECTED||m_iCheck) ) dc.DrawEdge( rect, EDGE_RAISED, BF_RECT );

	// Focus嗤りならFocus��宙鮫
	rect = lpDrawItemStruct->rcItem;
	if( state&ODS_FOCUS ){
		// CheckBoxじゃない&Focus嗤りならボタン��宙鮫
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
 * 	マウス恣ボタンを兀したときに柵ばれるメッセ�`ジハンドラ
 * 
 * 	@param nFlags	どの�N��の�∀襯��`が兀されているかを幣します。
 * 	@param point	カ�`ソルの x 恙�砲� y 恙�砲鰆原┐靴泙后Ｗ��砲蓮�械にウィンドウの恣貧嚊からの����了崔になります
 */
void CLineButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect rect;
	GetClientRect( rect );
	if( rect.PtInRect( point ) ) m_bBtnDown = TRUE;
	
	CButton::OnLButtonDown(nFlags, point);
}

/**
 * 	マウス恣ボタンをダブルクリックしたときに柵ばれるメッセ�`ジハンドラ
 * 
 * 	@param nFlags	どの�N��の�∀襯��`が兀されているかを幣します。
 * 	@param point	カ�`ソルの x 恙�砲� y 恙�砲鰆原┐靴泙后Ｗ��砲蓮�械にウィンドウの恣貧嚊からの����了崔になります
 */
void CLineButton::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CRect rect;
	GetClientRect( rect );
	if( rect.PtInRect( point ) ) m_bBtnDown = TRUE;
	
	CButton::OnLButtonDblClk(nFlags, point);
}

/**
 * 	マウス恣ボタンを�xしたときに柵ばれるメッセ�`ジハンドラ
 * 
 * 	@param nFlags	どの�N��の�∀襯��`が兀されているかを幣します。
 * 	@param point	カ�`ソルの x 恙�砲� y 恙�砲鰆原┐靴泙后Ｗ��砲蓮�械にウィンドウの恣貧嚊からの����了崔になります
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
 * 	掲システム キ�`が�xされたときに柵ばれるメッセ�`ジハンドラ
 * 
 * 	@param nChar	峺協されたキ�`の�∀襯��` コ�`ド
 * 	@param nRepCnt	リピ�`ト カウント
 * 	@param nFlags	スキャン コ�`ド、キ�`���Qコ�`ド、岷念のキ�`彜�B、コンテキスト コ�`ド
 */
void CLineButton::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( nChar == VK_SPACE ){
		SetCheck( m_iCheck? 0: 1 );
	}
	CButton::OnKeyUp(nChar, nRepCnt, nFlags);
}

/////////////////////////////////////////////////////////////////////////////
/// 壅燕幣
void CLineButton::Redraw(BOOL bErase /*= FALSE*/)
{
	if( IsWindow( m_hWnd ) ){
		Invalidate(bErase);
		UpdateWindow();
	}
}

/////////////////////////////////////////////////////////////////////////////
/**
 * 	チェック彜�Bを函誼します.
 * 
 * 	@return		0:チェックオフ	1:チェックオン
 */
int CLineButton::GetCheck()
{
	return m_iCheck;
}

/**
 * 	チェック彜�Bを�O協します.
 * 
 * 	@param	iCheck	0:チェックオフ	1:チェックオン
 * 
 * 	@warning		ボタンスタイルがチェックスタイルでない�rには採もしません。
 */
void CLineButton::SetCheck( int iCheck )
{
	if( m_uiStyle&BS_CHECKBOX ){
		m_iCheck = iCheck;
		
		// 燕幣厚仟
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
	// 燕幣/掲燕幣�O協
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

	// ���Nデ�`タセット
	int iLineHeight = m_lineSizeCombo.GetItemHeight( -1 );
	m_lineTypeCombo.SetItemHeight( -1, iLineHeight );
	for( i = 0; i < LINE_STYLE; i++ ){
		int iIndx = m_lineTypeCombo.InsertString( -1, "dmy" );
		m_lineTypeCombo.SetItemData( iIndx, c_iLineStyle[i] );
		m_lineTypeCombo.SetItemHeight( i, iLineHeight );

		// 兜豚�ﾔO協
		if( GetPenStyle() == c_iLineStyle[i] ) m_lineTypeCombo.SetCurSel( i );
	}
	// ��サイズデ�`タセット
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

	// マ�`ク�Nデ�`タセット
	int iMarkHeight = m_markSizeCombo.GetItemHeight( -1 );
	m_markTypeCombo.SetItemHeight( -1, iLineHeight );
	for( i = 0; i < MARK_STYLE; i++ ){
		int iIndx = m_markTypeCombo.InsertString( -1, "dmy" );
		m_markTypeCombo.SetItemData( iIndx, c_iMarkStyle[i] );
		m_markTypeCombo.SetItemHeight( i, iMarkHeight );

		// 兜豚�ﾔO協
		if( GetMarkerKind() == c_iMarkStyle[i] ) m_markTypeCombo.SetCurSel( i );		
	}

	// マ�`クサイズデ�`タセット
	for( i = 0; i < MARK_SIZE; i++ ){
		m_markSizeCombo.InsertString( -1, c_cMarkSize[i] );
		if( GetMarkerSize() == atoi( c_cMarkSize[i] ) ) m_markSizeCombo.SetCurSel( i );
	}
	
	// マ�`カ�`嘘尚デ�`タセット
	for( i = 0; i < MARK_BKSTYLE; i++ ){
		m_markBkStyleCombo.InsertString( -1, c_cMarkBkStyle[i] );
		if( GetMarkerBkStyle() == i )	m_markBkStyleCombo.SetCurSel( i );
	}

	return TRUE;  // コントロ�`ルにフォ�`カスを�O協しないとき、��り�､� TRUE となります
	              // 箭翌: OCX プロパティ ペ�`ジの��り�､� FALSE となります
}

/**
 * 	OKボタン兀和�r�I尖.
 * 		�O協の隠贋
 * 
 */
void CLineStyleDlg::OnOK()
{
	int iIndx;
	CString strTemp;

	// ライン�N�e
	iIndx = m_lineTypeCombo.GetCurSel();
	if( iIndx != CB_ERR ) m_lineStyle.iStyle = m_lineTypeCombo.GetItemData( iIndx );

	// ��サイズ
	m_lineSizeCombo.GetWindowText( strTemp );
	m_lineStyle.iSize = atoi( strTemp );

	// マ�`ク�N�e
	iIndx = m_markTypeCombo.GetCurSel();
	if( iIndx != CB_ERR ) m_markStyle.iMarker = m_markTypeCombo.GetItemData( iIndx );

	//マ�`クサイズ
	m_markSizeCombo.GetWindowText( strTemp );
	m_markStyle.iMarkSize = atoi( strTemp );

	// マ�`カ�`嘘尚
	iIndx = m_markBkStyleCombo.GetCurSel();
	if( iIndx != CB_ERR ) m_markStyle.iBkStyle = iIndx;


	CColorDialog::OnOK();

	// ��の弼
	m_lineStyle.color = GetColor();
}

/**
 * 	�w卞�rに�O協�N�eを登協する.
 * 
 * 	@param	iStyle		���N
 * 	@param	iSize		��サイズ
 * 	@param	iMarker		マ�`ク�N
 * 	@param	iMarkSize	マ�`クサイズ
 *	@return	int		IDOK, IDCANCEL
 */
int CLineStyleDlg::DoModal( int iStyle /*= PS_SOLID*/, int iSize /*= 0*/, int iMarker /*= 0*/, int iMarkSize /*= 8*/ )
{
	m_lineStyle.iStyle = iStyle;		// ���N
	m_lineStyle.iSize = iSize;			// ��サイズ
	m_markStyle.iMarker = iMarker;		// マ�`ク�N
	m_markStyle.iMarkSize = iMarkSize;	// マ�`クサイズ

	return CColorDialog::DoModal();
}

/**
 * 	オ�`ナ宙鮫コントロ�`ルの宙鮫.
 * 		���N�O協?マ�`ク�N�O協のコンボボックスを宙鮫する�蕕忘瑤个譴泙后�
 * 
 * 	@param nIDCtl			宙鮫アイテムのID
 * 	@param lpDrawItemStruct	宙鮫秤��
 */
void CLineStyleDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// DC函誼
	CDC *pDC = CDC::FromHandle( lpDrawItemStruct->hDC );

	// Rect函誼
	CRect rect = lpDrawItemStruct->rcItem;

	// 嘘尚弼
	COLORREF textColor;
	if( lpDrawItemStruct->itemState & ODS_SELECTED ){
		pDC->FillSolidRect( rect, GetSysColor( COLOR_HIGHLIGHT ) );
		textColor = GetSysColor( COLOR_HIGHLIGHTTEXT );
	} else{
		pDC->FillSolidRect( rect, GetSysColor( COLOR_WINDOW ) );
		textColor = GetSysColor( COLOR_WINDOWTEXT );
	}

	// ���N
	if( nIDCtl == IDC_CMB_LINESTYLE ){
		// ��
		if( (int)lpDrawItemStruct->itemID >= 0 ){
			CPen pen( c_iLineStyle[lpDrawItemStruct->itemID], 0, textColor );
			pDC->SelectObject( pen );
			pDC->MoveTo( rect.left, rect.top + rect.Height()/2 );
			pDC->LineTo( rect.right,rect.top + rect.Height()/2 );
		}
	// ��の湊さ
	/*} else if( nIDCtl == IDC_CMB_LINESIZE )	{
		if( (int)lpDrawItemStruct->itemID >= 0 ){
			CPen pen( PS_SOLID, lpDrawItemStruct->itemID , textColor );
			pDC->SelectObject( pen );
			pDC->MoveTo( rect.left, rect.top + rect.Height()/2 );
			pDC->LineTo( rect.right,rect.top + rect.Height()/2 );
		}*/
	// マ�`ク
	} else if( nIDCtl == IDC_CMB_MARKSTYLE ){
		// ペンの恬撹
		CPen pen( PS_SOLID, 0, textColor );
		pDC->SelectObject( pen );

		int iMarkStyle = m_markTypeCombo.GetItemData( lpDrawItemStruct->itemID );
		CRect rect = lpDrawItemStruct->rcItem;
		::DrawMark( pDC, iMarkStyle, rect.CenterPoint() );

	} else{
		CColorDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
	}
}