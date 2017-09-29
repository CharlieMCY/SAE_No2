// AXGDIPlot.cpp : �إå��` �ե�����
//
/********************************************************
// ���饹�Υ��󥿩`�ե�����
// CAXPlotStyle		:PLOT�������륯�饹
// CAXGDIPlotCtrl	:AXGDI�ץ�å����軭���饹
//												by YOTSUTSU
//	* History	:	date:2005,15,Jul.	��Ҏ����
ver.1.00	
********************************************************/
#include "stdafx.h"
#include "AXGDIPlot.h"

/////////////////////////////////////////////////////////////////////////////
// CAXGDIPlotCtrl
//////////////////////////////////////////////////////////////////////
// ���B/����
//////////////////////////////////////////////////////////////////////
// ���󥹥ȥ饯�����
CAXGDICursor::CAXGDICursor( void )
{
	Initialize();
}
///////////////////////////////////////
/**
 * 	���󥹥ȥ饯��
 * 		AXCURSORINFO������Ԫ�˘��B����
 * 
 * 	@param org	���ԩ`ԪCAXGDICursor
 */
CAXGDICursor::CAXGDICursor( const AXCURSORINFO & cursorInfo )
{
	Initialize();
	m_cursorInfo.wCusorStyle = cursorInfo.wCusorStyle; ///< Cursor style
	m_cursorInfo.iLayer = cursorInfo.iLayer;			///< DataLayer index
	m_cursorInfo.iPos = cursorInfo.iPos;				///< ���`����λ��
	m_cursorInfo.xyValue = cursorInfo.xyValue;			///< ��ָ��
	SetString(cursorInfo.szName);						///< ����
}	
///////////////////////////////////////
/**
 * 	���ԩ`���󥹥ȥ饯��
 * 		Ԫ��CAXGDICursor��Ԫ�˘��B����
 * 
 * 	@param org	���ԩ`ԪCAXGDICursor
 */
CAXGDICursor::CAXGDICursor( const CAXGDICursor &org )
{	
	operator=( org );
}
///////////////////////////////////////
//�ǥ��󥹥ȥ饯��
CAXGDICursor::~CAXGDICursor( void )
{
}
///////////////////////////////////////
/**
 * 	���ڻ��v��
 * 
 * 	@param
 */
void CAXGDICursor::Initialize( void )
{
	size_t size = sizeof(AXCURSORINFO);
	memset(&m_cursorInfo,0x00,size);
	m_cursorInfo.wSize = size;///< Specifies the size, in bytes, of this structure.
	SetCursorMode( CURSORNONE );		///< ���`����o��
	ShowCursor(TRUE);					///< ��ʾ/�Ǳ�ʾ�ե饰
	m_cursorInfo.iLayer = -1;				///< DataLayer index
	m_cursorInfo.iPos = -1;					///< ���`����λ��
	m_cursorInfo.xyValue.dX = 0.0;			///< ��ָ��
	m_cursorInfo.xyValue.dY = 0.0;			///< ��ָ��
	
	memset( m_cursorInfo.szName, _T('\0') ,sizeof(m_cursorInfo.szName));	///< ���`�������ǰ

//	m_pAXGdiCtrl = NULL;	///< CAXGDICtrl�Υݥ���
}
///////////////////////////////////////
/**
 * 	���ԩ`���ڥ�`��
 * 
 * 	@param org	���ԩ`ԪCAXGDICursor
 */
CAXGDICursor & CAXGDICursor::operator=( const CAXGDICursor &src )
{
	m_cursorInfo.iLayer = src.m_cursorInfo.iLayer;		///< DataLayer index
	m_cursorInfo.iPos = src.m_cursorInfo.iPos;				///< ���`����λ��
	m_cursorInfo.xyValue = src.m_cursorInfo.xyValue;		///< ��ָ��
	///< ���`�����`�� CURSORX:'X' X�S���`���� / CURSORY:'Y' Y�S���`���� / CURSORCROSS:'+' ʮ�֥��`����
	//m_cursorInfo.wCusorStyle = src.m_cursorInfo.wCusorStyle;
	SetCursorMode(src.GetCursorMode());
	ShowCursor(src.IsShowCursor());
	ShowActiveMark(src.IsShowActiveMark());

	SetString(src.m_cursorInfo.szName);		///< ���`�������ǰ

	return (*this);
}
///////////////////////////////////////
/**
 * 	���`�������Ƥ��軭
 * 
 * 	@param pDC			�軭����ǥХ�������ƥ����ȤΥݥ���
 * 	@param rect			�軭�I��ι���
 *	@param point		�軭��������
 *	@param iCursorMode�����`�����`�� CURSORX:'X' X�S���`���� / CURSORY:'Y' Y�S���`���� / CURSORCROSS:'+' ʮ�֥��`����
 *	@param lpszName		�軭����������
 *	@param color		�軭����ƥ����ȥ���`
 */
void CAXGDICursor::DrawCursorName( CDC *pDC, const CRect &rect, CPoint point, int iCursorMode, LPCTSTR lpszName, COLORREF color )
{
	if(lpszName == NULL)	{	return;	}
	if(0 < _tcslen(lpszName))	{//���֤����åȤ���Ƥ���С�
		// ������`�ɤΉ��
		int iBkMode = pDC->SetBkMode( TRANSPARENT );
		// ����`���O��
		COLORREF oldTextColor = pDC->SetTextColor( color );
		// ���_���軭λ�ä�ȡ��
		CSize strSize = pDC->GetTextExtent( lpszName );
		// ���`���������軭
		if( CURSORX == iCursorMode )	{
			pDC->TextOut( point.x/*iX*/ - strSize.cx / 2, point.y/*0*/, lpszName );
		}	else if( CURSORY == iCursorMode )	{
			pDC->TextOut( point.x/*rect.right*/ - strSize.cx , point.y/*iY*/ - strSize.cy , lpszName );
		}	else	{
			pDC->TextOut( point.x/*iX*/ - strSize.cx / 2, point.y/*0*/, lpszName );
		}	
		// ����`�����
		pDC->SetTextColor( oldTextColor );
		// ������`�ɤ����
		pDC->SetBkMode( iBkMode );
	}
}
/////////////////////////////////////////////////////////////////////////////
// CAXPlotCursor
///////////////////////////////////////
/**
 * 	���`������軭
 * 
 * 	@param pDC			�軭����ǥХ�������ƥ����ȤΥݥ���
 * 	@param rect			�軭�I��ι���
 *	@param point		�軭��������
 *	@param bMonochrome	��Υ���`���軭�ե饰
 */
void CAXPlotCursor::DrawCursor( CDC *pDC, const CRect &rect, CPoint point, BOOL bMonochrome )
{
	//�軭ɫ
	COLORREF	color = GetLineColor();
	//��Υ���
	if(bMonochrome)	{ color = IBLACK;	} 
	// �ڥ������
	CLinePen pen;
	int penStyle = GetLineStyle().iStyle;
	if( GetLineStyle().iStyle == PS_NULL && MARKNONE !=  GetMarkerStyle().iMarker)	{
		penStyle = PS_SOLID;
	}
	pen.CreatePen( penStyle, GetLineSize(), color );
	// �ڥ���x�k
	CPen *pOldPen = pDC->SelectObject( &pen );
	
	// �֥饷������
	CBrush	brush( color );
	
	if( GetPenStyle() != PS_NULL )	{
		const int c_iActiveMarkSize = 6;
		// X���`�����軭
		if( GetCursorMode() == CURSORX || GetCursorMode() == CURSORCROSS ){
			pDC->MoveTo( point.x, 0 );
			pDC->LineTo( point.x, rect.Height() + 1 );
			int iSize = 0;
			if(IsShowActiveMark())	{
				// �֥饷���x�k
				CBrush *oldBrush = pDC->SelectObject( &brush );
				if(pDC->IsPrinting())	{	//ӡˢ��
					iSize = MulDiv(c_iActiveMarkSize, pDC->GetDeviceCaps(LOGPIXELSY), 72);
				}	else	{
					iSize = c_iActiveMarkSize;
				}
				DrawActiveMark( pDC, rect, point, CURSORX, iSize );
				// �֥饷�����
				pDC->SelectObject( oldBrush );
			}
			DrawCursorName( pDC, rect, CPoint(point.x, iSize ), CURSORX, GetString(), color );
		}
		// Y���`�����軭
		if( GetCursorMode() == CURSORY || GetCursorMode() == CURSORCROSS ){
			pDC->MoveTo( 0, point.y );
			pDC->LineTo( rect.Width() + 1, point.y );
			int iSize = 0;
			if(IsShowActiveMark())	{
				// �֥饷���x�k
				CBrush *oldBrush = pDC->SelectObject( &brush );
				if(pDC->IsPrinting())	{	//ӡˢ��
					iSize = MulDiv(c_iActiveMarkSize, pDC->GetDeviceCaps(LOGPIXELSY), 72);
				}	else	{
					iSize = c_iActiveMarkSize;
				}
				DrawActiveMark( pDC, rect, point, CURSORY, iSize );
				// �֥饷�����
				pDC->SelectObject( oldBrush );
			}
			if( GetCursorMode() == CURSORY )	{	
				DrawCursorName( pDC, rect, CPoint(rect.Width() - iSize, point.y), CURSORY, GetString(), color );
			}
		}
	}

	if(GetMarkerKind() != MARKNONE )	{
		// �֥饷���x�k
		CBrush *oldBrush = NULL;
		if( GetMarkerBkStyle() == 0 ) {
			oldBrush = (CBrush *)pDC->SelectStockObject( NULL_BRUSH );
		}	else	{
			oldBrush = pDC->SelectObject( &brush );
		}

		//�������ΛQ��
		int iSize = GetMarkerSize();

		if(pDC->IsPrinting())	{	//ӡˢ��
			iSize = MulDiv(iSize, pDC->GetDeviceCaps(LOGPIXELSY), 72);
		}
		//�ީ`���`�軭
		::DrawMark( pDC, GetMarkerKind(), point, iSize );

		// �֥饷�����
		pDC->SelectObject( oldBrush );
	}

	// �֥饷���Ɨ�
	brush.DeleteObject();

	// �ڥ�����
	pDC->SelectObject( pOldPen );

	// �ڥ���Ɨ�
	pen.DeleteObject();

}
/**
 * 	���`����ActiveMark�軭
 * 
 * 	@param pDC			�軭����ǥХ�������ƥ����ȤΥݥ���
 * 	@param rect			�軭�I��ι���
 *	@param pos			�軭��������
 *	@param iCursorMode	X:CURSORX/Y:CURSORY
 *	@param iSize		ActiveMark�Υ�����
 */
void CAXPlotCursor::DrawActiveMark( CDC *pDC, const CRect &rect, CPoint pos, int iCursorMode, int iSize )
{
	// �ީ`��
	POINT point[3];
	if(iCursorMode == CURSORX)	{
		// ��
		point[0].x = pos.x;			point[0].y = iSize;
		point[1].x = pos.x - iSize;	point[1].y = 0;
		point[2].x = pos.x + iSize;	point[2].y = 0;
		pDC->Polygon( point, 3 );
		// ��
		point[0].x = pos.x;			point[0].y = rect.Height() - iSize;
		point[1].x = pos.x - iSize;	point[1].y = rect.Height();
		point[2].x = pos.x + iSize;	point[2].y = rect.Height();
		pDC->Polygon( point, 3 );

	}	else
	if(iCursorMode == CURSORY)	{
		// ��
		point[0].x = iSize;		point[0].y = pos.y;
		point[1].x = 0;			point[1].y = pos.y + iSize;
		point[2].x = 0;			point[2].y = pos.y - iSize;
		pDC->Polygon( point, 3 );
		// ��
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
 * 	���ꥢ���`�������Ƥ��軭
 * 
 * 	@param pDC			�軭����ǥХ�������ƥ����ȤΥݥ���
 * 	@param rect			�軭�I��ι���
 *	@param bMonochrome	��Υ���`���軭�ե饰
 */
void CAXAreaCursor::DrawAreaCursorName( CDC *pDC, const CRect &rect, BOOL bMonochrome )
{
	//if(0 < _tcslen(GetString()))	{//���֤����åȤ���Ƥ���С�
	if(!GetString().IsEmpty())	{//���֤����åȤ���Ƥ���С�
		// �ե����ɫ���O��
		COLORREF TextColor = GetPatternColor();

		switch(GetBrushStyle())	{
		case BS_HATCHED:	break;
		case BS_SOLID:
		default:
			TextColor = ~GetPatternColor();//GetBkColor();
			break;
		}

		//��Υ���
		if(bMonochrome)	{ 	TextColor = IBLACK;	}
	
		// ������`�ɤΉ��
		int iBkMode = pDC->SetBkMode( TRANSPARENT );
		// ����`���O��
		COLORREF oldTextColor = pDC->SetTextColor( TextColor );
		// ���_���軭λ�ä�ȡ��
		CSize strSize = pDC->GetTextExtent( GetString() );
		// ���`���������軭
		if( GetCursorMode() == CURSORX ){
			pDC->TextOut( (rect.left + rect.right - strSize.cx) / 2, rect.top, GetString() );
		}	else if( GetCursorMode() == CURSORY )	{
			pDC->TextOut( rect.right - strSize.cx, (rect.top + rect.bottom - strSize.cy) / 2, GetString() );
		}	else if( GetCursorMode() == CURSORCROSS)	{
			pDC->TextOut( (rect.left + rect.right - strSize.cx) / 2, 
				(rect.top + rect.bottom - strSize.cy) / 2, GetString() );
		}
		// ����`�����
		pDC->SetTextColor( oldTextColor );
		// ������`�ɤ����
		pDC->SetBkMode( iBkMode );
	}
}
///////////////////////////////////////
/**
 * 	���ꥢ���`������軭
 * 
 * 	@param pDC			�軭����ǥХ�������ƥ����ȤΥݥ���
 * 	@param rect			�軭�I��ι���
 *	@param bMonochrome	��Υ���`���軭�ե饰
 */
void CAXAreaCursor::DrawPattern( CDC *pDC, const CRect &rect, BOOL bMonochrome )
{
	//�軭ɫ
	COLORREF	color = GetPatternColor();
	//��Υ���
	if(bMonochrome)	{ color = Color2Gray( GetPatternColor() );	} 

	// �ڥ������
	CPen pen;
	pen.CreatePen( PS_SOLID, 0, color );
	// �ڥ���x�k
	CPen *pOldPen = pDC->SelectObject( &pen );
	// �֥饷������
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

	// �֥饷���x�k
	CBrush *pOldBrush = pDC->SelectObject( &brush );

	pDC->Rectangle( rect );

	// �֥饷�����
	pDC->SelectObject( pOldBrush );
	// �֥饷���Ɨ�
	brush.DeleteObject();
		// �ڥ�����
	pDC->SelectObject( pOldPen );
	// �ڥ���Ɨ�
	pen.DeleteObject();

}
/////////////////////////////////////////////////////////////////////////////
// CAXGDIPlotCtrl
//////////////////////////////////////////////////////////////////////
// ���B/����
//////////////////////////////////////////////////////////////////////
CAXGDIPlotCtrl::CAXGDIPlotCtrl(COLORREF bkColor /*= IBLACK*/)
	: m_axisX(MEASUREX), m_axisY(MEASUREY)
{
	SetBkColor(bkColor);
	
	///< ��Υ���`���ʾ�ե饰
	EnableMonochrome(FALSE);

	m_axisX.ShowMeasureMinMax(FALSE,FALSE);
	m_axisY.ShowMeasureMinMax(FALSE,FALSE);

	m_axisY.SetMeasureAngle(0);

//	m_dMeasureRatio = 0.02;		///< �SĿʢ���ȫ��ˌ��������
	m_byStyleXCross = 0;		///< �S�����Є�(0:Min/1:Max/2:Center/3:�ǩ`����ָ��)
	m_byStyleYCross = 0;		///< �S�����Є�(0:Min/1:Max/2:Center/3:�ǩ`����ָ��)
	m_dAxisXCross = 0.0;		///< �S����ݥ����(�ǩ`����ָ��)
	m_dAxisYCross = 0.0;		///< �S����ݥ����(�ǩ`����ָ��)

	m_byShowPlotScaleX = 0;	///< �ץ�åȥǩ`���Υ����`����ʾ�Є���X�S��
	m_byShowPlotScaleY = 0;	///< �ץ�åȥǩ`���Υ����`����ʾ�Є���Y�S��
	m_byPlotNameShowMode = 0;	///< �ץ�åȥǩ`�����Ƥα�ʾ�Є�
	SetShowModePlotName(AX_GDIXMODE);

	m_iCursorFontSize = -1;		// ���`����ե���ȥ�����
	m_iAreaCsrFontSize = -1;	// ���ꥢ���`����ե���ȥ�����

	ShowGridX( FALSE, PS_SOLID, ~bkColor, 0 );
	ShowGridY( FALSE, PS_SOLID, ~bkColor, 0 );

	Initialize();	//���ڻ�

	m_bRedraw = TRUE;///< ���軭�ե饰

}
/**
 * 	���ԩ`���󥹥ȥ饯��
 * 
 * 	@param org	���ԩ`ԪCAXGDIPlotCtrl���饹
 */
CAXGDIPlotCtrl::CAXGDIPlotCtrl( CAXGDIPlotCtrl &org )
{
	operator=( org );
}
/// �ǥ��ȥ饯��
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
// CAXGDIPlotCtrl ��å��`�� �ϥ�ɥ�
///////////////////////////////////////
/// ������ɥ����ɕr�Υ�å��`���ϥ�ɥ�
void CAXGDIPlotCtrl::PreSubclassWindow() 
{
	CAXGDICtrl::PreSubclassWindow();

	// ����ӥåȥޥå�&�ӥåȥޥå�DC������
    CDC* pDC = GetDC();
	m_bitmap.CreateCompatibleBitmap( pDC, m_wndSize.cx, m_wndSize.cy );
	m_bmpDC.CreateCompatibleDC( pDC );
	m_bmpDC.SelectObject( m_bitmap );
	ReleaseDC( pDC );

	m_zoomScale.RemoveAll();

//	ModifyStyle( 0, SS_NOTIFY|WS_CHILD );
}
///////////////////////////////////////
/// ������ɥ��Ɨ��r�Υ�å��`���ϥ�ɥ�
void CAXGDIPlotCtrl::OnDestroy() 
{
	CAXGDICtrl::OnDestroy();

	// ����ӥåȥޥå�&�ӥåȥޥå�DC���Ɨ�
	m_bmpDC.DeleteDC();
	m_bitmap.DeleteObject();
	m_zoomScale.RemoveAll();
}
///////////////////////////////////////
/// ����������Υ�å��`���ϥ�ɥ�
void CAXGDIPlotCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CAXGDICtrl::OnSize(nType, cx, cy);

	// ����ӥåȥޥå�&�ӥåȥޥå�DC���Ɨ�
	m_bmpDC.DeleteDC();
	m_bitmap.DeleteObject();

	// ����ӥåȥޥå�&�ӥåȥޥå�DC��������
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
	CPaintDC dc(this); // �軭�äΥǥХ��� ����ƥ�����
	// TODO: ����λ�ä˥�å��`�� �ϥ�ɥ��äΥ��`�ɤ�׷�Ӥ��Ƥ�������
	// �軭�å�å��`���Ȥ��� CStatic::OnPaint() ����ӳ����ƤϤ����ޤ���
	//get rect size
//	CRect rectWnd;
	CRect rectItem;
	GetClientRect( &rectItem );
//	GetClientRect( &rectWnd );
	//rectItem = rectWnd;
//	SubcalcRect(rectItem);;
	// �軭ԭ���O��
	// ����Ǥ��ޤ������褦����MSDN���Ǥ��`�狼���
	CPoint oldWndOrg = dc.SetWindowOrg( 0,0 );//rectItem.left, rectItem.top );
	// �ե���Ȥ�ȡ��
	LOGFONT logfont;
	GetParent()->GetFont()->GetLogFont( &logfont );

	// �ե���Ȥ�����?�x�k
	CFont font;
	font.CreateFontIndirect( &logfont );
	CFont *pOldFont = dc.SelectObject( &font );

	// ����åԥ�
	CRect clipRect;
	dc.GetClipBox( clipRect );
	dc.IntersectClipRect( rectItem );

	//�軭ǰ�I��
	BeginPaintDC( &dc, rectItem );

	if( m_bRedraw ) {
		//if(!IsMarginRectNull())	{
		//	m_bmpDC.FillSolidRect( rectWnd, ICTRLCOLOR );
		//}
		CFont *pOldbmpFont = m_bmpDC.SelectObject( &font );
		DrawDC( &m_bmpDC, rectItem );
		m_bmpDC.SelectObject( pOldbmpFont );
	}
	// ????????�軭
	//dc.BitBlt( -rectWnd.left, -rectWnd.top, rectWnd.Width(), rectWnd.Height(), &m_bmpDC, 0, 0, SRCCOPY );
	dc.BitBlt( rectItem.left, rectItem.top, rectItem.Width(), rectItem.Height(), &m_bmpDC, 0, 0, SRCCOPY );

	//�����軭
	DrawExDC( &dc, rectItem );
	
	//Active��״�B���軭
	DrawActiveState( &dc, rectItem );

	// �軭��I��
	EndPaintDC( &dc, rectItem );

	// ����å��I���Ԫ�ˑ���
	dc.SelectClipRgn( NULL );
	dc.IntersectClipRect( clipRect );

	// �ե���Ȥ����
	dc.SelectObject( pOldFont );
	font.DeleteObject();
	
	// ԭ������
	dc.SetWindowOrg( oldWndOrg );
	// Draw�ե饰�ꥻ�å�
	m_bRedraw = FALSE;
}
////////////////////////////////////////////////////
/// �ޥ�����ܥ���Ѻ�¤Εr�Υ�å��`���ϥ�ɥ�(����Ւ����I���軭ʼ����)
void CAXGDIPlotCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// �����I������
	m_guideRect.left  = point.x;
	m_guideRect.top   = point.y;
	m_guideRect.right = point.x;
	m_guideRect.bottom= point.y;

	// �ޥ�������ɣ�
	m_bZooming = IsMouseZoom();

	// �ޥ������Ƅ��I�������
	if( m_bZooming ){
		CRect graphRect;
		GetWindowRect( graphRect );
		ClipCursor( graphRect );
		// �����I���ʼ����ʾ
		if(XY_ZOOM != GetMouseZoom())	{
			// �����I��Ζ����軭
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
				///< 0:���x�k/1:ȫ��/2:�ǩ`��/3:���`����/4:���ꥢ���`����
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
// �ޥ�����ܥ�����֥륯��å�Ѻ�¤Εr�Υ�å��`���ϥ�ɥ�
void CAXGDIPlotCtrl::OnLButtonDblClk( UINT nFlags, CPoint point )
{
	if( GetSafeHwnd() && (GetFocus() == this))	{
		///< 0:���x�k/1:ȫ��/2:�ǩ`��/3:���`����/4:���ꥢ���`����
		if(m_activeInfo.nActive == AXGCTRLACT_DATA)	{
			NotifyToParent( AXGCN_CHANGE_STYLE );
		}	else if(m_activeInfo.nActive == AXGCTRLACT_CURSOL)	{
			NotifyToParent( AXGCN_CHANGE_STYLE );
		}
	}
	CAXGDICtrl::OnLButtonDblClk(nFlags, point);
}
///////////////////////////////////////
/// �ޥ�����ܥ����x�����r�Υ�å��`���ϥ�ɥ�(����Ւ����軭��)
void CAXGDIPlotCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// �ޥ��������ޤ���
	ClipCursor( NULL );
	if( m_bZooming ){
		// �����I������
		m_guideRect.right = point.x;
		m_guideRect.bottom= point.y;
		m_guideRect.NormalizeRect();
		if(m_guideRect.Height() > 2 && m_guideRect.Width() > 2)	{
			// ����
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
/// �ޥ����Ƅ��ФΥ�å��`���ϥ�ɥ�(����Ւ����I���軭��)
void CAXGDIPlotCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( nFlags == MK_LBUTTON){//�ޥ�������ܥ���Ѻ����Ƥ�����Ϥ˥��åȤ��ޤ���
		if( m_bZooming){
			CRect beforeRect = m_guideRect;
			
			// �����I������
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

			// �����I��Ζ����軭
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
 * 	���ڻ�.
 */
void CAXGDIPlotCtrl::Initialize( void )
{
	m_bZooming = FALSE;			///< �����Хե饰
	m_iMouseZoom = ZOOM_OFF;	///< �ޥ�������C��
	m_guideRect.SetRectEmpty();	///< �����I��

}
/////////////////////////////////////////////////////////////////////////////
// protected
/**
 * 	����åɤ����.
 * 		X�ޤ���Y�Υ���åɤ��軭����
 * 
 * 	@param pDC		�軭����ǥХ�������ƥ����ȤΥݥ���
 * 	@param iType	�軭���륰��åɤΥ�����\n
 * 					GRIDX:X�S��	GRIDY:Y�S
 * 	@param rect		�軭�I��ι���
 * 	@param gridInfo	�軭���륰��åɤΥ���å����
 */
void CAXGDIPlotCtrl::DrawGrid( CDC *pDC, int iType, const CRect &rect, const LINESTYLE &gridLine )
{
	// �ڥ������
	CLinePen pen;
	pen.CreatePen( gridLine.iStyle, gridLine.iSize,	(IsMonochrome() ? RGB(0,0,0) : gridLine.color) );

	// �ڥ���x�k
	CPen *pOldPen = pDC->SelectObject( &pen );

	CAXMeasureStyle *pAxis = NULL;
	int iMode = 0;
	// Ŀʢ������(X)
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
	// ����å��軭
	if(pAxis)	{
		if(pAxis->IsLogMode())	{
			pAxis->DrawLogScale( pDC, rect, iMode, pAxis->GetScaleType(), pAxis->GetMin(), pAxis->GetMax(), 100 );
		}	else	{
			if(pAxis->IsEnableDivDelta())	{//�ָ�ָ��
				pAxis->DrawDivScale( pDC, rect, iMode, pAxis->GetScaleType(), pAxis->GetScaleDelta(), 0.0 , 0);
			}	else	{
				double dDeltaOrg = pAxis->GetMin();
				if(pAxis->IsDeltaOrgEnable())	{	dDeltaOrg = pAxis->GetDeltaOrg();	}
				pAxis->DrawScale( pDC, rect, iMode, pAxis->GetScaleType(), pAxis->GetMin(), pAxis->GetMax(), dDeltaOrg, pAxis->GetScaleDelta(), 0.0 , 0);//GetScaleDetailDelta() );
			}
		}
	}	
	// �ڥ�����
	pDC->SelectObject( pOldPen );

	// �ڥ���Ɨ�
	pen.DeleteObject();
}
///////////////////////////////////////
/**
 * 	�S��Ŀʢ������.
 * 		X�ޤ���Y�S��Ŀʢ����軭����
 * 
 * 	@param pDC		�軭����ǥХ�������ƥ����ȤΥݥ���
 * 	@param rect		�軭�I��ι���
 * 	@param measure	�軭����Ŀʢ�ꥯ�饹��CAXMeasureStyle���饹��
 */
void CAXGDIPlotCtrl::DrawMeasure( CDC *pDC, const CRect &rect, CAXMeasureStyle &measure )
{
	if(!measure.IsShowScale())	{	return;	}
	//��СĿʢ���L��
//	const int c_iMinLen = 6;
	// �ڥ������
	CPen pen;
	pen.CreatePen( PS_SOLID, 1, (IsMonochrome() ? RGB(0,0,0) : measure.GetScaleColor()) );
	// �ڥ���x�k
	CPen *pOldPen = pDC->SelectObject( &pen );

	//�������ΛQ��
	long length = CAXMeasureCtrl::c_iMeasureSise;
	const int c_iMargin = 2;
	long margin = length + c_iMargin;
//	if(GetInitSize().cx > GetInitSize().cy)	{
//		length = (long)(m_dMeasureRatio * GetInitSize().cx);
//	}	else	{
//		length = (long)(m_dMeasureRatio * GetInitSize().cy);
//	}	

//	if(length < c_iMinLen)	{	length = c_iMinLen;	}

	if(pDC->IsPrinting())	{	//ӡˢ��
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
		//Ŀʢ���S�軭
		measure.DrawScale( pDC, rectScale );


		if(GetStyleXCross() == 2 || GetStyleXCross() == 3)	{
			//Ŀʢ�ꂎ�軭
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
		//Ŀʢ���軭
		measure.DrawScale( pDC, rectScale );

		if(GetStyleYCross() == 2 || GetStyleYCross() == 3)	{
			//Ŀʢ�ꂎ�軭
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
	// �ڥ�����
	pDC->SelectObject( pOldPen );
	// �ڥ���Ɨ�
	pen.DeleteObject();
}
///////////////////////////////////////
/**
 * 	�ץ�åȥǩ`���Υ����`������.
 * 		�뤨��줿���ǥץ�åȥǩ`���Υ����`����軭���롣
 * 
 * 	@param pDC			�軭����ǥХ�������ƥ����ȤΥݥ���
 * 	@param rect			�軭�I��ι���
 *	@param iXYMode		AX_XMODE:'X'X�S/AX_YMODE:'Y'Y�S
 * 	@param nIndex		�軭����index
 * 	@param nShowLine	�軭����饤����
 *	@param color		�軭ɫ
 *	@param lpszString	��ʾ������
 */
void CAXGDIPlotCtrl::DrawPlotName( CDC *pDC, const CRect &rect, int iXYMode, int nIndex, int nShowLine, COLORREF color, LPCTSTR lpszString )
{
	CString strData = lpszString;
	if(strData.IsEmpty())	{	return;	}
	// �ե���Ȥ�����
	LOGFONT logfont;
	pDC->GetCurrentFont()->GetLogFont( &logfont );
	if(iXYMode == AX_GDIYMODE)	{
		logfont.lfEscapement = GetAxisY().GetMeasureAngle();
		logfont.lfOrientation = GetAxisY().GetMeasureAngle();
	}
	// ������`�ɤΉ��
	int iBkMode = pDC->SetBkMode( TRANSPARENT );
	// �ե����?����ɫ���x�k
	CFont font;
	font.CreateFontIndirect( &logfont );
	CFont   *pOldFont = pDC->SelectObject( &font );
	COLORREF oldColor = pDC->SetTextColor( color );
	// ���_���軭λ�ä�ȡ��
	CSize strSize = pDC->GetTextExtent( strData );

	if(iXYMode == AX_GDIXMODE)	{
		// ���`���������軭
		CPoint point;
		point.x = rect.right - strSize.cx;//(nShowLine - nIndex) * strSize.cy;
		point.y = rect.top + nIndex * strSize.cy + 1;
		pDC->TextOut(  point.x , point.y , strData);
	}	else if(iXYMode == AX_GDIYMODE)	{
		// ���`���������軭
		CPoint point;
		point.x = rect.right - (nShowLine - nIndex) * strSize.cy;
		point.y = rect.top + strSize.cx;
		pDC->TextOut(  point.x , point.y , strData);
	}
	// ����ɫ�����
	pDC->SetTextColor( oldColor );
	// �ե���Ȥ����&�Ɨ�
	pDC->SelectObject( pOldFont );
	font.DeleteObject();
	// ������`�ɤ����
	pDC->SetBkMode( iBkMode );
}
///////////////////////////////////////
/**
 * 	�ץ�åȥǩ`���Υ����`������.
 * 		�뤨��줿���ǥץ�åȥǩ`���Υ����`����軭���롣
 * 
 * 	@param pDC			�軭����ǥХ�������ƥ����ȤΥݥ���
 * 	@param rect			�軭�I��ι���
 *	@param iXYMode		AX_XMODE:'X'X�S/AX_YMODE:'Y'Y�S
 * 	@param nIndex		�軭����index
 * 	@param nShowLine	�軭����饤����
 *	@param color		�軭ɫ
 *	@param dblMin		�����`�����С��
 *	@param dblMax		�����`������
 */
void CAXGDIPlotCtrl::DrawPlotScale( CDC *pDC, const CRect &rect, int iXYMode, int nIndex, int nShowLine, COLORREF color, double dblMin, double dblMax )
{
	// �ե���Ȥ�����
	LOGFONT logfont;
	pDC->GetCurrentFont()->GetLogFont( &logfont );
	if(iXYMode == AX_GDIYMODE)	{
		logfont.lfEscapement = GetAxisY().GetMeasureAngle();
		logfont.lfOrientation = GetAxisY().GetMeasureAngle();
	}
	// ������`�ɤΉ��
	int iBkMode = pDC->SetBkMode( TRANSPARENT );
	// �ե����?����ɫ���x�k
	CFont font;
	font.CreateFontIndirect( &logfont );
	CFont   *pOldFont = pDC->SelectObject( &font );
	COLORREF oldColor = pDC->SetTextColor( color );
	
	if(iXYMode == AX_GDIXMODE)	{
		CString strData = _T("");
		strData.Format(_T("%-0.*f"),GetDecLength(dblMax - dblMin),dblMin);
		// ���_���軭λ�ä�ȡ��
		CSize strSize = pDC->GetTextExtent( strData );
		CPoint point;
		// ���`���������軭
		point.x = rect.left + 1;//+ nIndex * strSize.cy;
		point.y = rect.bottom - (nShowLine - nIndex) * strSize.cy;	
		pDC->TextOut(  point.x  , point.y , strData );

		strData.Format(_T("%-0.*f"),GetDecLength(dblMax - dblMin),dblMax);
		// ���_���軭λ�ä�ȡ��
		strSize = pDC->GetTextExtent( strData );
		// ���`���������軭
		point.x = rect.right - strSize.cx;
		point.y = rect.bottom - (nShowLine - nIndex) * strSize.cy;	
		pDC->TextOut(  point.x , point.y , strData );
	}	else	{
		CString strData = _T("");
		strData.Format(_T("%-0.*f"),GetDecLength(dblMax - dblMin),dblMin);
		// ���_���軭λ�ä�ȡ��
		CSize strSize = pDC->GetTextExtent( strData );
		CPoint point;
		// ���`���������軭
		if( logfont.lfOrientation == 900 || logfont.lfOrientation == -900 )	{
			point.x = rect.left + nIndex * strSize.cy;
			point.y = rect.bottom;// - strSize.cx;
		}	else	{		
			point.x = rect.left;//+ nIndex * strSize.cy;
			point.y = rect.bottom - (nShowLine - nIndex) * strSize.cy;	
		}
		pDC->TextOut(  point.x , point.y , strData );

		strData.Format(_T("%-0.*f"),GetDecLength(dblMax - dblMin),dblMax);
		// ���_���軭λ�ä�ȡ��
		strSize = pDC->GetTextExtent( strData );
		// ���`���������軭
		if( logfont.lfOrientation == 900 || logfont.lfOrientation == -900 )	{
			point.x = rect.left + nIndex * strSize.cy;
			point.y = rect.top + strSize.cx;
		}	else	{		
			point.x = rect.left;//+ nIndex * strSize.cy;
			point.y = rect.top + nIndex * strSize.cy;	
		}
		pDC->TextOut(  point.x , point.y , strData );
	}
	// ����ɫ�����
	pDC->SetTextColor( oldColor );
	// �ե���Ȥ����&�Ɨ�
	pDC->SelectObject( pOldFont );
	font.DeleteObject();
	// ������`�ɤ����
	pDC->SetBkMode( iBkMode );
}
///////////////////////////////////////
/**
 * 	���`��������.
 * 		�뤨��줿���`���륯�饹�����ǥ��`������軭���롣
 * 
 * 	@param pDC			�軭����ǥХ�������ƥ����ȤΥݥ���
 * 	@param rect			�軭�I��ι���
 * 	@param plotCursor	�軭���륫�`���륯�饹��CAXPlotCursor���饹��
 */
void CAXGDIPlotCtrl::DrawPlotCursor( CDC *pDC, const CRect &rect, CAXPlotCursor &plotCursor )
{
	if(!plotCursor.IsShowCursor())			{	return;	}
	if(plotCursor.GetLayer() >= 0)	{	return;	}

	// �o������ǥå����ʤ�͎�
	BOOL bDraw = FALSE;
	//���`�����`��	CURSORX:'X' X�S���`���� / CURSORY:'Y' Y�S���`���� / CURSORCROSS:'+' ʮ�֥��`����
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

	// �軭ԭ���O��
	CPoint oldOrg = pDC->SetViewportOrg( rect.left, rect.top );

	// �ǩ`���軭λ���O��
	CPoint cpData;
	cpData.x = GetAxisX().Data2PointX(plotCursor.GetValue().dX, rect.Width());
	cpData.y = GetAxisY().Data2PointY(plotCursor.GetValue().dY, rect.Height());

	// ���`�����軭
	plotCursor.DrawCursor( pDC, rect, cpData, IsMonochrome() );

	// ԭ������
	pDC->SetViewportOrg( oldOrg );
}
///////////////////////////////////////
/**
 * 	���`��������.
 * 		�뤨��줿�ǩ`�����饹�����`���륯�饹�����ǥ��`������軭���롣
 * 
 * 	@param pDC			�軭����ǥХ�������ƥ����ȤΥݥ���
 * 	@param rect			�軭�I��ι���
 *	@param data			���`���륯�饹��ָ�������ǩ`���쥤��`
 * 	@param plotCursor	�軭���륫�`���륯�饹��CAXPlotCursor���饹��
 */
void CAXGDIPlotCtrl::DrawPlotCursor( CDC *pDC, const CRect &rect, CXYPlotData &data, CAXPlotCursor &plotCursor )
{
	// �Ǳ�ʾ�ʤ�͎�
	if(!plotCursor.IsShowCursor())				{	return;	}
	// �o���쥤��`�ʤ�͎�
	if(plotCursor.GetLayer() < 0)			{	return;	}
	// �o������ǥå����ʤ�͎�
	int index = plotCursor.GetPos();
	if(  0 > index || index >= data.GetNum() )	{	return;	}
	
	// �軭ԭ���O��
	CPoint oldOrg = pDC->SetViewportOrg( rect.left, rect.top );

	// �ǩ`���軭λ���O��
	CPoint cpData;
	double dXrvs = 1.0;
	if(data.IsReversalX() && (!data.GetXscale().IsLogMode()))		{	dXrvs = -1.0;	}
	cpData.x = data.GetXscale().Data2PointX( data.dataX(index)/*data[index].dX*/ * dXrvs, rect.Width() );
	double dYrvs = 1.0;
	if(data.IsReversalY() && (!data.GetYscale().IsLogMode()))		{	dYrvs = -1.0;	}
	cpData.y = data.GetYscale().Data2PointY( data.dataY(index)/*data[index].dY*/ * dYrvs, rect.Height() );

	// ���`�����軭
	plotCursor.DrawCursor( pDC, rect, cpData, IsMonochrome() );

	// ԭ������
	pDC->SetViewportOrg( oldOrg );
}
///////////////////////////////////////
/**
 * 	���`��������.
 * 		�뤨��줿�ǩ`�����饹�����`���륯�饹�����ǥ��`������軭���롣
 * 
 * 	@param pDC			�軭����ǥХ�������ƥ����ȤΥݥ���
 * 	@param rect			�軭�I��ι���
 *	@param data			���`���륯�饹��ָ�������ǩ`���쥤��`
 * 	@param plotCursor	�軭���륫�`���륯�饹��CAXPlotCursor���饹��
 */
void CAXGDIPlotCtrl::DrawPlotCursor( CDC *pDC, const CRect &rect, CDBLPlotData &data, CAXPlotCursor &plotCursor )
{
	// �Ǳ�ʾ�ʤ�͎�
	if(!plotCursor.IsShowCursor())				{	return;	}
	// �o���쥤��`�ʤ�͎�
	if(plotCursor.GetLayer() < 0)			{	return;	}
	// �o������ǥå����ʤ�͎�
	int index = plotCursor.GetPos();
	if(  0 > index || index >= data.GetNum() )	{	return;	}

	// �軭ԭ���O��
	CPoint oldOrg = pDC->SetViewportOrg( rect.left, rect.top );

	// �ǩ`���軭λ���O��
	CPoint cpData;
	double dXrvs = 1.0;
	if(data.IsReversalX() && (!data.GetXscale().IsLogMode()))		{	dXrvs = -1.0;	}
	cpData.x = data.GetXscale().Data2PointX( data.dataX(index)/*data[index].dX*/ * dXrvs, rect.Width() );
	double dYrvs = 1.0;
	if(data.IsReversalY() && (!data.GetYscale().IsLogMode()))		{	dYrvs = -1.0;	}
	cpData.y = data.GetYscale().Data2PointY( data.dataY(index)/*data[index].dY*/ * dYrvs, rect.Height() );
	
	// ���`�����軭
	plotCursor.DrawCursor( pDC, rect, cpData, IsMonochrome() );

	// ԭ������
	pDC->SetViewportOrg( oldOrg );
}
///////////////////////////////////////
/**
 * 	���ꥢ���`���롢�ޤ��ϡ����ꥢ���`�������Ƥ����.
 * 		�뤨��줿�ǩ`�����饹�����`���륯�饹�����ǥ��ꥢ���`������軭���롣
 * 
 * 	@param pDC			�軭����ǥХ�������ƥ����ȤΥݥ���
 * 	@param rect			�軭�I��ι���
 * 	@param areaCursor	�軭���륫�`���륯�饹��CAXAreaCursor���饹��
 * 	@param bDrawName	���ꥢ���`�������Ƥ��軭�ե饰
 */
void CAXGDIPlotCtrl::DrawAreaCursor( CDC *pDC, const CRect &rect, CAXAreaCursor &areaCursor, BOOL bDrawName /*= FALSE*/ )
{
	// �Ǳ�ʾ�ʤ�͎�
	if( !areaCursor.IsShowCursor() )		{	return;	}
	// �쥤��`���O������Ƥ���С���ɤ롣
	if( areaCursor.GetLayer() >= 0)	{	return;	}

	// �o������ǥå����ʤ�͎�
	BOOL bDraw = FALSE;
	double dXhead,dXtail;
	if( areaCursor.GetValue().dX <= areaCursor.GetTailValue().dX )	{
		dXhead = areaCursor.GetValue().dX;
		dXtail = areaCursor.GetTailValue().dX;
	}	else	{
		dXhead = areaCursor.GetTailValue().dX;
		dXtail = areaCursor.GetValue().dX;
	}

	//���`�����`��	CURSORX:'X' X�S���`���� / CURSORY:'Y' Y�S���`���� / CURSORCROSS:'+' ʮ�֥��`����
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

	// �軭ԭ���O��
	CPoint oldOrg = pDC->SetViewportOrg( rect.left, rect.top );

	// �軭���륨�ꥢ
	CRect rectDraw( 0, 0, rect.Width(), rect.Height() );

	// X���ꥢ���`�����軭
	if( areaCursor.GetCursorMode() == CURSORX || areaCursor.GetCursorMode() == CURSORCROSS ){
		rectDraw.left = GetAxisX().Data2PointX( dXhead, rect.Width() );
		rectDraw.right = GetAxisX().Data2PointX( dXtail, rect.Width() );
	}
	// Y���ꥢ���`�����軭
	if( areaCursor.GetCursorMode() == CURSORY || areaCursor.GetCursorMode() == CURSORCROSS ){
		rectDraw.top = GetAxisY().Data2PointY( dYhead, rect.Height() );
		rectDraw.bottom = GetAxisY().Data2PointY( dYtail, rect.Height() );
	}
	rectDraw.NormalizeRect();//��Ҏ��
	if(bDrawName)	{
		areaCursor.DrawAreaCursorName( pDC, rectDraw, IsMonochrome() );
	}	else	{
		rectDraw.bottom += 1;
		rectDraw.right += 1;
		areaCursor.DrawPattern( pDC, rectDraw, IsMonochrome() );
	}

	// ԭ������
	pDC->SetViewportOrg( oldOrg );
}
///////////////////////////////////////
/**
 * 	���ꥢ���`���롢�ޤ��ϡ����ꥢ���`�������Ƥ����.
 * 		�뤨��줿�ǩ`�����饹�����`���륯�饹�����ǥ��ꥢ���`������軭���롣
 * 
 * 	@param pDC			�軭����ǥХ�������ƥ����ȤΥݥ���
 * 	@param rect			�軭�I��ι���
 *	@param data			���`���륯�饹��ָ�������ǩ`���쥤��`
 * 	@param areaCursor	�軭���륫�`���륯�饹��CAXAreaCursor���饹��
 * 	@param bDrawName	���ꥢ���`�������Ƥ��軭�ե饰
 */
void CAXGDIPlotCtrl::DrawAreaCursor( CDC *pDC, const CRect &rect, CXYPlotData &data, CAXAreaCursor &areaCursor, BOOL bDrawName /*= FALSE*/ )
{
	// �Ǳ�ʾ�ʤ�͎�
	if(!areaCursor.IsShowCursor())				{	return;	}
	// �o���쥤��`�ʤ�͎�
	if(areaCursor.GetLayer() < 0)			{	return;	}
	// �o������ǥå����ʤ�͎�
	int iPosHead = areaCursor.GetPos();
	if(  0 > iPosHead || iPosHead >= data.GetNum() )	{	return;	}
	int iPosTail = areaCursor.GetTailPos();
	if(  0 > iPosTail || iPosTail >= data.GetNum() )	{	return;	}

	// �軭ԭ���O��
	CPoint oldOrg = pDC->SetViewportOrg( rect.left, rect.top );

	// �軭���륨�ꥢ
	CRect rectDraw( 0, 0, rect.Width(), rect.Height() );

	// X���ꥢ���`�����軭
	if( areaCursor.GetCursorMode() == CURSORX || areaCursor.GetCursorMode() == CURSORCROSS ){
		double dXrvs = 1.0;
		if(data.IsReversalX() && (!data.GetXscale().IsLogMode()))		{	dXrvs = -1.0;	}
		rectDraw.left = data.GetXscale().Data2PointX( data.dataX(iPosHead) * dXrvs, rect.Width() );
		rectDraw.right = data.GetXscale().Data2PointX( data.dataX(iPosTail) * dXrvs, rect.Width() );
	}
	// Y���ꥢ���`�����軭
	if( areaCursor.GetCursorMode() == CURSORY || areaCursor.GetCursorMode() == CURSORCROSS ){
		double dYrvs = 1.0;
		if(data.IsReversalY() && (!data.GetYscale().IsLogMode()))		{	dYrvs = -1.0;	}
		rectDraw.top = data.GetYscale().Data2PointY( data.dataY(iPosHead) * dYrvs, rect.Height() );
		rectDraw.bottom = data.GetYscale().Data2PointY( data.dataY(iPosTail) * dYrvs, rect.Height() );
	}
	rectDraw.NormalizeRect();//��Ҏ��
	if(bDrawName)	{
		areaCursor.DrawAreaCursorName( pDC, rectDraw, IsMonochrome() );
	}	else	{
		rectDraw.bottom += 1;
		rectDraw.right += 1;
		areaCursor.DrawPattern( pDC, rectDraw, IsMonochrome() );
	}

	// ԭ������
	pDC->SetViewportOrg( oldOrg );
}
///////////////////////////////////////
/**
 * 	���ꥢ���`���롢�ޤ��ϡ����ꥢ���`�������Ƥ����.
 * 		�뤨��줿�ǩ`�����饹�����`���륯�饹�����ǥ��ꥢ���`������軭���롣
 * 
 * 	@param pDC			�軭����ǥХ�������ƥ����ȤΥݥ���
 * 	@param rect			�軭�I��ι���
 *	@param data			���`���륯�饹��ָ�������ǩ`���쥤��`
 * 	@param areaCursor	�軭���륫�`���륯�饹��CAXAreaCursor���饹��
 * 	@param bDrawName	���ꥢ���`�������Ƥ��軭�ե饰
 */
void CAXGDIPlotCtrl::DrawAreaCursor( CDC *pDC, const CRect &rect, CDBLPlotData &data, CAXAreaCursor &areaCursor, BOOL bDrawName /*= FALSE*/ )
{
	// �Ǳ�ʾ�ʤ�͎�
	if(!areaCursor.IsShowCursor())				{	return;	}
	// �o���쥤��`�ʤ�͎�
	if(areaCursor.GetLayer() < 0)			{	return;	}
	// �o������ǥå����ʤ�͎�
	int iPosHead = areaCursor.GetPos();
	if(  0 > iPosHead || iPosHead >= data.GetNum() )	{	return;	}
	int iPosTail = areaCursor.GetTailPos();
	if(  0 > iPosTail || iPosTail >= data.GetNum() )	{	return;	}

	// �軭ԭ���O��
	CPoint oldOrg = pDC->SetViewportOrg( rect.left, rect.top );

	// �軭���륨�ꥢ
	CRect rectDraw( 0, 0, rect.Width(), rect.Height() );

	// X���ꥢ���`�����軭
	if( areaCursor.GetCursorMode() == CURSORX || areaCursor.GetCursorMode() == CURSORCROSS ){
		double dXrvs = 1.0;
		if(data.IsReversalX() && (!data.GetXscale().IsLogMode()))		{	dXrvs = -1.0;	}
		rectDraw.left = data.GetXscale().Data2PointX( data.dataX(iPosHead) * dXrvs, rect.Width() );
		rectDraw.right = data.GetXscale().Data2PointX( data.dataX(iPosTail) * dXrvs, rect.Width() );
	}
	// Y���ꥢ���`�����軭
	if( areaCursor.GetCursorMode() == CURSORY || areaCursor.GetCursorMode() == CURSORCROSS ){
		double dYrvs = 1.0;
		if(data.IsReversalY() && (!data.GetYscale().IsLogMode()))		{	dYrvs = -1.0;	}
		rectDraw.top = data.GetYscale().Data2PointY( data.dataY(iPosHead) * dYrvs, rect.Height() );
		rectDraw.bottom = data.GetYscale().Data2PointY( data.dataY(iPosTail) * dYrvs, rect.Height() );
	}
	rectDraw.NormalizeRect();//��Ҏ��	
	if(bDrawName)	{
		areaCursor.DrawAreaCursorName( pDC, rectDraw, IsMonochrome() );
	}	else	{
		rectDraw.bottom += 1;
		rectDraw.right += 1;
		areaCursor.DrawPattern( pDC, rectDraw, IsMonochrome() );
	}

	// ԭ������
	pDC->SetViewportOrg( oldOrg );

}
//************************ �����C�� ************************///
///////////////////////////////////////
/**
 * 	�ޥ����ǤΥ���Ւ���C�ܤ��O������.
 * 
 * 	@param iZoom	����C�ܤ��O������
 *		ZOOM_OFF = 0,	///<�o��
 *		XY_ZOOM,		///<X����Y����΁I����򒈴�
 *		X_ZOOM,			///<X���򒈴�
 *		Y_ZOOM,			///<Y���򒈴�
 * 	@return			�S��״�B�򷵤���
 */
int CAXGDIPlotCtrl::EnableMouseZoom ( int iZoom /*= XY_ZOOM*/ )
{
	if(IsEnableActivate())	{
		if(iZoom == XY_ZOOM || iZoom == X_ZOOM || iZoom == Y_ZOOM  )	{
			m_iMouseZoom = iZoom;	///< �ޥ�������C��ON/OFF�ե饰
		}
	}
	return m_iMouseZoom;
}