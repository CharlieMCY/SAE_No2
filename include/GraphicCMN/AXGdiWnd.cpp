// AXGdiWnd.cpp ���饹�Υ���ץ���Ʃ`�����
//
/********************************************************
// CLineStyleDisp	:�饤��&�ީ`���`�������룫ɫ����TEXTWnd���饹
// CLineButton		:�饤��&�ީ`���`��������ܥ��󥯥饹
// CLineStyleDlg	:�饤��&�ީ`���`������������������饹
//												by YOTSUTSU
//	* History	:	date:2005,24,Mar.	��Ҏ����
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
	m_bSepareterVisible = FALSE;	///< ���ѥ�`�Ȗ���ʾ�ե饰
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
// CLineStyleDisp ��å��`�� �ϥ�ɥ�
/////////////////////////////////////////////////////////////////////////////
// ���ڻ�
void CLineStyleDisp::PreSubclassWindow() 
{
	CAXStringWnd::PreSubclassWindow();
}
/**
 * 	����ץ뾀�軭
 * 
 *
void CLineStyleDisp::OnPaint() 
{
	CPaintDC dc(this); // �軭�äΥǥХ��� ����ƥ�����

	// RECT��CRect��
	CRect rectItem;
	GetClientRect( rectItem );
	DrawItem( &dc, rectItem );
	//if(GetFocus())	{	dc.DrawFocusRect(rectItem);	}
}
/**
 * 	�軭���ꥢ���֥륯��å��r�΄I��
 * 
 * 	@param uFlags	....
 * 	@param point	����å�λ��
 */
void CLineStyleDisp::OnLButtonDblClk(UINT nFlags, CPoint point) 
{

	NotifyToParent( AXGCN_CHANGE_STYLE, NULL );

	CWnd::OnLButtonDblClk(nFlags, point);
}
/////////////////////////////////////////////////////////////////////////////
/**
 * 	�軭
 * 
 * 	@param *pDC		�軭����ǥХ�������ƥ�����
 * 	@param rect		�軭���륨�ꥢ
 */
void CLineStyleDisp::DrawItem( CDC *pDC, CRect rect, CFont *pTextFont /*= NULL*/ )
{
	CAXGDIFrame::DrawBackground( pDC, rect );
	CAXGDIFrame::DrawFrame( pDC, rect );

	double dSize = 0.0;
	CRect rectItems = rect;

	if(m_lfOrientation == 900 || m_lfOrientation == -900)	{
		dSize = ((double)rect.Height()) * GetSeparateRatio() ;	//Item �ֽ�
		rectItems.bottom = (int)(dSize + 0.5 ) + rectItems.top;
		if(rectItems.Height() > (m_iMargin * 2) )	{
			rectItems.DeflateRect( 0, m_iMargin );
			// �����軭
			if(m_lfOrientation == 900)	{
				TextDraw( pDC, rectItems, pTextFont );
			}	else	{
				DrawLineStyle( pDC, rectItems, GetLineStyle(), m_lfOrientation );
			}
			rectItems.InflateRect( 0, m_iMargin );
			if(m_lfOrientation != 900)	{
				// �ީ`���`�軭
				DrawMarker( pDC, rectItems.CenterPoint(), GetMarkerStyle(), GetLineStyle().color );
			}
			rectItems.top = rectItems.bottom;
			if(m_bSepareterVisible)	{	///< ���ѥ�`�Ȗ���ʾ�ե饰)
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
		dSize = ((double)rect.Width()) * GetSeparateRatio() ;	//Item �ֽ�	
		rectItems.right = (int)(dSize + 0.5 ) + rectItems.left;
		if(rectItems.Width() > (m_iMargin * 2) )	{
			rectItems.DeflateRect( m_iMargin, 0 );
			// �����軭
			DrawLineStyle( pDC, rectItems, GetLineStyle());

			rectItems.InflateRect( m_iMargin, 0 );
			// �ީ`���`�軭
			DrawMarker( pDC, rectItems.CenterPoint(), GetMarkerStyle(), GetLineStyle().color );

			rectItems.left = rectItems.right;
			if(m_bSepareterVisible)	{	///< ���ѥ�`�Ȗ���ʾ�ե饰)
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
 * 	���ѥ�`�Ⱦ��軭
 * 
 * 	@param *pDC		�軭����ǥХ�������ƥ�����
 * 	@param rect		�軭���륨�ꥢ
 */
void CLineStyleDisp::DrawSeparater( CDC *pDC, const CRect &rect )
{
	//pDC->FrameRect( rect, &CBrush((IsMonochrome() ? c_colorBlack : GetFrameColor())) );	}
	// �ڥ������
	CPen pen;
	pen.CreatePen( PS_SOLID, 0, (IsMonochrome() ? IBLACK : GetFrameColor() ) );

	// �ڥ���x�k
	CPen *pOldPen = pDC->SelectObject( &pen );

	// ���軭
	pDC->MoveTo( rect.left, rect.top );
	pDC->LineTo( rect.right, rect.bottom );

	// �ڥ�����
	pDC->SelectObject( pOldPen );

	// �ڥ���Ɨ�
	pen.DeleteObject();
}
/**
 * 	��������������롣
 * 
 *	@param		pNotifyMsg	֪ͨ��å��`�������
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
/// ���󥹥ȥ饯��
CLineButton::CLineButton()
{
	m_iCheck   = 0;
	m_bBtnDown = FALSE;

}

/// �ǥ��ȥ饯��
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
// CLineButton ��å��`�� �ϥ�ɥ�

/// ���֥��饹������ǰ�˺��Ф���å��`���ϥ�ɥ�
void CLineButton::PreSubclassWindow() 
{
#ifdef _DEBUG
	// OwnerDraw�O������Ƥ����龯��
	if( GetButtonStyle()==BS_OWNERDRAW ){
		AfxMessageBox( "CLineButton �꥽�`���Ϥ�OwnerDraw�����å���Ϥ������¤���" );
	}
#endif

	// ��������α���
	m_uiStyle = GetButtonStyle();

	// OwnerDraw���O��(������Button�������CheckBox�ǌ���)
	if( !(GetButtonStyle()&BS_CHECKBOX && !(GetStyle()&BS_PUSHLIKE)) ){
		SetButtonStyle( GetButtonStyle()|BS_OWNERDRAW );
	}

	// OwnerDraw��
	SetButtonStyle( GetButtonStyle()|BS_OWNERDRAW );

	CButton::PreSubclassWindow();
}

/**
 * 	���`�ʩ`�軭�Ξ�˺��Ф���å��`���ϥ�ɥ�
 * 
 * 	@param lpDrawItemStruct	�軭�����Ŀ���軭�N�e���v��������ָ�����ޤ���
 * 
 */
void CLineButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC   dc;
	UINT  state = lpDrawItemStruct->itemState;	
	CRect rect	= lpDrawItemStruct->rcItem;
	dc.Attach( lpDrawItemStruct->hDC );

	// Ѻ����
	if( state&ODS_SELECTED||m_iCheck ){
		dc.DrawFrameControl( rect, DFC_BUTTON, DFCS_ADJUSTRECT|DFCS_BUTTONPUSH|DFCS_PUSHED );
		dc.FillSolidRect( rect, m_bkColor );

		// ���֤򰼤ޤ���
		if( state&ODS_SELECTED ){
			rect.OffsetRect( 0, 1 );
			rect.DeflateRect( 1, 0 );
		}
	// ͨ��
	} else{
		dc.DrawFrameControl( rect, DFC_BUTTON, DFCS_ADJUSTRECT|DFCS_BUTTONPUSH );
		dc.FillSolidRect( rect, m_bkColor );
	}

	// �����軭
	DrawLineStyle( &dc, rect, m_lineStyle);
	// �ީ`���軭
	DrawMarker( &dc, rect.CenterPoint(), GetMarkerStyle(), GetLineStyle().color );

	// ͨ���ܥ���
	if( !(state&ODS_SELECTED||m_iCheck) ) dc.DrawEdge( rect, EDGE_RAISED, BF_RECT );

	// Focus�Ф�ʤ�Focus���軭
	rect = lpDrawItemStruct->rcItem;
	if( state&ODS_FOCUS ){
		// CheckBox����ʤ�&Focus�Ф�ʤ�ܥ����軭
		if( !(m_uiStyle&BS_CHECKBOX) ){
			FrameRect( dc.m_hDC, rect, (HBRUSH)GetStockObject( BLACK_BRUSH ) );
		}
		rect.DeflateRect( 4, 4 );
		dc.DrawFocusRect( rect );
	}

	// DC�Υǥ��å�
	dc.Detach();
}

/**
 * 	�ޥ�����ܥ����Ѻ�����Ȥ��˺��Ф���å��`���ϥ�ɥ�
 * 
 * 	@param nFlags	�ɤηN΁��륭�`��Ѻ����Ƥ��뤫��ʾ���ޤ���
 * 	@param point	���`����� x ���ˤ� y ���ˤ�ָ�����ޤ������ˤϡ����˥�����ɥ��������礫�������λ�äˤʤ�ޤ�
 */
void CLineButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect rect;
	GetClientRect( rect );
	if( rect.PtInRect( point ) ) m_bBtnDown = TRUE;
	
	CButton::OnLButtonDown(nFlags, point);
}

/**
 * 	�ޥ�����ܥ������֥륯��å������Ȥ��˺��Ф���å��`���ϥ�ɥ�
 * 
 * 	@param nFlags	�ɤηN΁��륭�`��Ѻ����Ƥ��뤫��ʾ���ޤ���
 * 	@param point	���`����� x ���ˤ� y ���ˤ�ָ�����ޤ������ˤϡ����˥�����ɥ��������礫�������λ�äˤʤ�ޤ�
 */
void CLineButton::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CRect rect;
	GetClientRect( rect );
	if( rect.PtInRect( point ) ) m_bBtnDown = TRUE;
	
	CButton::OnLButtonDblClk(nFlags, point);
}

/**
 * 	�ޥ�����ܥ�����x�����Ȥ��˺��Ф���å��`���ϥ�ɥ�
 * 
 * 	@param nFlags	�ɤηN΁��륭�`��Ѻ����Ƥ��뤫��ʾ���ޤ���
 * 	@param point	���`����� x ���ˤ� y ���ˤ�ָ�����ޤ������ˤϡ����˥�����ɥ��������礫�������λ�äˤʤ�ޤ�
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
 * 	�ǥ����ƥ� ���`���x���줿�Ȥ��˺��Ф���å��`���ϥ�ɥ�
 * 
 * 	@param nChar	ָ�����줿���`�΁��륭�` ���`��
 * 	@param nRepCnt	��ԩ`�� �������
 * 	@param nFlags	������� ���`�ɡ����`��Q���`�ɡ�ֱǰ�Υ��`״�B������ƥ����� ���`��
 */
void CLineButton::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( nChar == VK_SPACE ){
		SetCheck( m_iCheck? 0: 1 );
	}
	CButton::OnKeyUp(nChar, nRepCnt, nFlags);
}

/////////////////////////////////////////////////////////////////////////////
/// �ٱ�ʾ
void CLineButton::Redraw(BOOL bErase /*= FALSE*/)
{
	if( IsWindow( m_hWnd ) ){
		Invalidate(bErase);
		UpdateWindow();
	}
}

/////////////////////////////////////////////////////////////////////////////
/**
 * 	�����å�״�B��ȡ�ä��ޤ�.
 * 
 * 	@return		0:�����å�����	1:�����å�����
 */
int CLineButton::GetCheck()
{
	return m_iCheck;
}

/**
 * 	�����å�״�B���O�����ޤ�.
 * 
 * 	@param	iCheck	0:�����å�����	1:�����å�����
 * 
 * 	@warning		�ܥ��󥹥����뤬�����å���������Ǥʤ��r�ˤϺΤ⤷�ޤ���
 */
void CLineButton::SetCheck( int iCheck )
{
	if( m_uiStyle&BS_CHECKBOX ){
		m_iCheck = iCheck;
		
		// ��ʾ����
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
	// ��ʾ/�Ǳ�ʾ�O��
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

	// ���N�ǩ`�����å�
	int iLineHeight = m_lineSizeCombo.GetItemHeight( -1 );
	m_lineTypeCombo.SetItemHeight( -1, iLineHeight );
	for( i = 0; i < LINE_STYLE; i++ ){
		int iIndx = m_lineTypeCombo.InsertString( -1, "dmy" );
		m_lineTypeCombo.SetItemData( iIndx, c_iLineStyle[i] );
		m_lineTypeCombo.SetItemHeight( i, iLineHeight );

		// ���ڂ��O��
		if( GetPenStyle() == c_iLineStyle[i] ) m_lineTypeCombo.SetCurSel( i );
	}
	// ���������ǩ`�����å�
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

	// �ީ`���N�ǩ`�����å�
	int iMarkHeight = m_markSizeCombo.GetItemHeight( -1 );
	m_markTypeCombo.SetItemHeight( -1, iLineHeight );
	for( i = 0; i < MARK_STYLE; i++ ){
		int iIndx = m_markTypeCombo.InsertString( -1, "dmy" );
		m_markTypeCombo.SetItemData( iIndx, c_iMarkStyle[i] );
		m_markTypeCombo.SetItemHeight( i, iMarkHeight );

		// ���ڂ��O��
		if( GetMarkerKind() == c_iMarkStyle[i] ) m_markTypeCombo.SetCurSel( i );		
	}

	// �ީ`���������ǩ`�����å�
	for( i = 0; i < MARK_SIZE; i++ ){
		m_markSizeCombo.InsertString( -1, c_cMarkSize[i] );
		if( GetMarkerSize() == atoi( c_cMarkSize[i] ) ) m_markSizeCombo.SetCurSel( i );
	}
	
	// �ީ`���`�����ǩ`�����å�
	for( i = 0; i < MARK_BKSTYLE; i++ ){
		m_markBkStyleCombo.InsertString( -1, c_cMarkBkStyle[i] );
		if( GetMarkerBkStyle() == i )	m_markBkStyleCombo.SetCurSel( i );
	}

	return TRUE;  // ����ȥ�`��˥ե��`�������O�����ʤ��Ȥ������ꂎ�� TRUE �Ȥʤ�ޤ�
	              // ����: OCX �ץ�ѥƥ� �ک`���Α��ꂎ�� FALSE �Ȥʤ�ޤ�
}

/**
 * 	OK�ܥ���Ѻ�r�I��.
 * 		�O���α���
 * 
 */
void CLineStyleDlg::OnOK()
{
	int iIndx;
	CString strTemp;

	// �饤��N�e
	iIndx = m_lineTypeCombo.GetCurSel();
	if( iIndx != CB_ERR ) m_lineStyle.iStyle = m_lineTypeCombo.GetItemData( iIndx );

	// ��������
	m_lineSizeCombo.GetWindowText( strTemp );
	m_lineStyle.iSize = atoi( strTemp );

	// �ީ`���N�e
	iIndx = m_markTypeCombo.GetCurSel();
	if( iIndx != CB_ERR ) m_markStyle.iMarker = m_markTypeCombo.GetItemData( iIndx );

	//�ީ`��������
	m_markSizeCombo.GetWindowText( strTemp );
	m_markStyle.iMarkSize = atoi( strTemp );

	// �ީ`���`����
	iIndx = m_markBkStyleCombo.GetCurSel();
	if( iIndx != CB_ERR ) m_markStyle.iBkStyle = iIndx;


	CColorDialog::OnOK();

	// ����ɫ
	m_lineStyle.color = GetColor();
}

/**
 * 	�w�ƕr���O���N�e���ж�����.
 * 
 * 	@param	iStyle		���N
 * 	@param	iSize		��������
 * 	@param	iMarker		�ީ`���N
 * 	@param	iMarkSize	�ީ`��������
 *	@return	int		IDOK, IDCANCEL
 */
int CLineStyleDlg::DoModal( int iStyle /*= PS_SOLID*/, int iSize /*= 0*/, int iMarker /*= 0*/, int iMarkSize /*= 8*/ )
{
	m_lineStyle.iStyle = iStyle;		// ���N
	m_lineStyle.iSize = iSize;			// ��������
	m_markStyle.iMarker = iMarker;		// �ީ`���N
	m_markStyle.iMarkSize = iMarkSize;	// �ީ`��������

	return CColorDialog::DoModal();
}

/**
 * 	���`���軭����ȥ�`����軭.
 * 		���N�O��?�ީ`���N�O���Υ���ܥܥå������軭�����˺��Ф�ޤ���
 * 
 * 	@param nIDCtl			�軭�����ƥ��ID
 * 	@param lpDrawItemStruct	�軭���
 */
void CLineStyleDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// DCȡ��
	CDC *pDC = CDC::FromHandle( lpDrawItemStruct->hDC );

	// Rectȡ��
	CRect rect = lpDrawItemStruct->rcItem;

	// ����ɫ
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
	// ����̫��
	/*} else if( nIDCtl == IDC_CMB_LINESIZE )	{
		if( (int)lpDrawItemStruct->itemID >= 0 ){
			CPen pen( PS_SOLID, lpDrawItemStruct->itemID , textColor );
			pDC->SelectObject( pen );
			pDC->MoveTo( rect.left, rect.top + rect.Height()/2 );
			pDC->LineTo( rect.right,rect.top + rect.Height()/2 );
		}*/
	// �ީ`��
	} else if( nIDCtl == IDC_CMB_MARKSTYLE ){
		// �ڥ������
		CPen pen( PS_SOLID, 0, textColor );
		pDC->SelectObject( pen );

		int iMarkStyle = m_markTypeCombo.GetItemData( lpDrawItemStruct->itemID );
		CRect rect = lpDrawItemStruct->rcItem;
		::DrawMark( pDC, iMarkStyle, rect.CenterPoint() );

	} else{
		CColorDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
	}
}