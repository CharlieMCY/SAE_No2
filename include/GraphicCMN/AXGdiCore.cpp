// AXGDICore.cpp ���饹�Υ���ץ���Ʃ`�����
//
/********************************************************
// CAXGDIFrame		:AXGDI�軭���饹
// CAXColorString	:ɫ����TEXT���饹
// CAXStringWnd		:ɫ����TEXTWnd���饹
//												by YOTSUTSU
//	* History	:	date:2005,24,Mar.	��Ҏ����
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
 * 	�ީ`���軭.
 * 		�ީ`�����軭����
 * 
 * 	@param pDC		�軭����ǥХ�������ƥ�����
 * 	@param iStyle	�ީ`���N�e
 * 	@param pos		�軭λ��
 * 	@param iSize	�ީ`��������
 */
void _stdcall DrawMark( CDC *pDC, int iStyle, CPoint pos, int iSize /*= 2*/ )
{
	int		iHalfSize = iSize / 2;
	CPoint	oldPoint;
	// �ީ`��
	POINT point[4];
	switch( iStyle ){
	case MARKCIRCLE:		// ��
		pDC->Ellipse( pos.x - iHalfSize, pos.y - iHalfSize, pos.x + (iHalfSize + 1), pos.y + (iHalfSize + 1) );
		break;
	case MARKCROSS:			// ��
		oldPoint = pDC->GetCurrentPosition();
		pDC->MoveTo( pos.x - iHalfSize, pos.y - iHalfSize );
		pDC->LineTo( pos.x + (iHalfSize + 1), pos.y + (iHalfSize + 1) );
		pDC->MoveTo( pos.x - iHalfSize, pos.y + iHalfSize );
		pDC->LineTo( pos.x + (iHalfSize + 1), pos.y - (iHalfSize + 1) );
		pDC->MoveTo( oldPoint );
		break;
	case MARKSQUARE:		// ��
		pDC->Rectangle( pos.x - iHalfSize, pos.y - iHalfSize,
						pos.x + iHalfSize, pos.y + iHalfSize );
		break;
	case MARKTRYANGLE:		// ��
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
	case MARKDIAMOND:		//��
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
 * 	���쥤����`��ȡ�ã�COLORREF������`���Ȥ���ʹ���� 32 �ӥåȂ���
 *		�ե륫��`�����饰�쥤����`��Q��΂���ȡ�� 
 * 
 * 	@param data	�ե륫��`��
 * 	@return		���쥤����`��Q��
 */
COLORREF _stdcall Color2Gray( COLORREF color )
{
	COLORREF grayColor = color;
//�������� = (0.299 * R + 0.587 * G + 0.114 * B) * 256 / 256
//����������������������= (77 * R + 150 * G + 29 * B) >> 8
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

	//if(dVal >= 10000.0)		{	sZero = 0;	}//�ɤä��������Τ�
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
 * 	���ԩ`���󥹥ȥ饯��
 * 		�뤨��줿CAXGDIFrame�򥳥ԩ`����
 * 
 * 	@param org	���ԩ`ԪCAXGDIFrame���饹
 */
CAXGDIFrame::CAXGDIFrame( const CAXGDIFrame &org )
{
	operator = (org);
}
///////////////////////////////////////
//�ǥ��ȥ饯��
CAXGDIFrame::~CAXGDIFrame()
{
}
///////////////////////////////////////
/**
 * 	�饤�󥹥������軭
 * 
 * 	@param pDC			�軭�ǥХ�������ƥ�����
 * 	@param rect			�軭���ꥢ
 * 	@param lineStyle	�軭�饤�󥹥�����
 *	@param lOrientation �軭�饤��νǶȣ�0.1��)
 */
void CAXGDIFrame::DrawLineStyle( CDC *pDC, const CRect &rect, const LINESTYLE &lineStyle, long lOrientation /*= 0*/ )
{
	if(lineStyle.iStyle == PS_NULL)	{	return;	}
	// �ڥ������
	CLinePen pen;
	pen.CreatePen( lineStyle.iStyle, lineStyle.iSize, (IsMonochrome() ? IBLACK : lineStyle.color ) );

	// �ڥ���x�k
	CPen *pOldPen = pDC->SelectObject( &pen );

	// �軭�ݥ���Ȥ�Ӌ��
	CPoint start,end;

	if(lOrientation == 0 || lOrientation == 1800)	{//��
		start.x = rect.left;			
		end.x = rect.right;
		start.y = end.y = rect.CenterPoint().y;
	}	else if(lOrientation == 900 || lOrientation == -900)	{
		start.x = end.x = rect.CenterPoint().x;
		start.y = rect.top;
		end.y = rect.bottom;
	}	else	{
		// ��Ӌ�ゎ��ȡ��
		double dRad= ( M_PI / 180.0 ) * ( lOrientation / 10.0 );
		int iCosX = int(0.5 * rect.Width() * fabs(cos( dRad )));
		int iSinY = int(0.5 * rect.Height() * fabs(sin( dRad )));
		start.x = rect.CenterPoint().x - iCosX;			
		end.x = rect.CenterPoint().x + iCosX;
		start.y = rect.CenterPoint().y - iSinY;
		end.y = rect.CenterPoint().y + iSinY;
	}

	// ���軭
	pDC->MoveTo( start );
	pDC->LineTo( end );

	// �ڥ�����
	pDC->SelectObject( pOldPen );

	// �ڥ���Ɨ�
	pen.DeleteObject();
}
///////////////////////////////////////
/**
 * 	�ީ`���`�軭
 * 
 * 	@param pDC			�軭�ǥХ�������ƥ�����
 * 	@param rect			�軭���ꥢ
 * 	@param markStyle	�軭�ީ`���`��������
 *	@param color		�軭�ީ`���`��ɫ
 */
void CAXGDIFrame::DrawMarker( CDC *pDC, CPoint pos, const MARKERSTYLE &markStyle, COLORREF color )
{
	// �ީ`���`�o���ʤ�͎�
	if( markStyle.iMarker == MARKNONE ) return;

	// �ڥ������
	CPen pen;
	pen.CreatePen( PS_SOLID, 0, (IsMonochrome() ? IBLACK : color ) );
	
	// �ڥ���x�k
	CPen *pOldPen = pDC->SelectObject( &pen );
	
	// �֥饷������
	CBrush	brush((IsMonochrome() ? IBLACK : color ));
	
	// �֥饷���x�k
	CBrush *oldBrush = NULL;
	//	brush.CreateSolidBrush( m_lineStyle.color );
	if( IsMonochrome() || markStyle.iBkStyle == 0 ) {
		oldBrush = (CBrush *)pDC->SelectStockObject( NULL_BRUSH );
	}	else	{
		oldBrush = pDC->SelectObject( &brush );
	}

	//�ީ`���`�軭
	::DrawMark( pDC, markStyle.iMarker, pos, markStyle.iMarkSize );

	// �֥饷�����
	pDC->SelectObject( oldBrush );

	// �֥饷���Ɨ�
	brush.DeleteObject();

	// �ڥ�����
	pDC->SelectObject( pOldPen );

	// �ڥ���Ɨ�
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
 * 	���ԩ`���󥹥ȥ饯��
 * 		�뤨��줿CAXColorString�򥳥ԩ`����
 * 
 * 	@param org	���ԩ`ԪCAXColorString���饹
 */
CAXColorString::CAXColorString( const CAXColorString &org )
{
	operator = (org);
}
///////////////////////////////////////
//�ǥ��ȥ饯��
CAXColorString::~CAXColorString()
{
}
///////////////////////////////////////
/**
 * 	draw string to static style
 * 	
 * 	@param	wStyle	�軭��������
 * 	@param	rect	�軭���ꥢ
 * 	@return			Ԫ�Υ�������
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
 * 	@param pDC				�軭�ǥХ�������ƥ�����
 * 	@param rect				�軭���ꥢ
 * 	@param font				�軭Font
 * 	@param bMonochrome		��Υ����ʾ�ե饰
 *	@param lfOrientation	��ʾ�Ƕ�
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
 * 	@param pDC			�軭�ǥХ�������ƥ�����
 * 	@param rect			�軭���ꥢ
 * 	@param font			�軭Font
 * 	@param lpszString	��ʾ������
 * 	@param textColor	��ʾ����ɫ
 * 	@param wStyle		��ʾStyle
*/
void CAXColorString::TextDraw( CDC* pDC, CRect &rect, CFont &font, LPCTSTR lpszString, const COLORREF textColor, UINT nDTFormat, long lfOrientation )
{
	CString str(lpszString);
#ifndef _DEBUG
	//set clip area
	pDC->IntersectClipRect( rect );
#endif //_DEBUG
	
	//text color�O��
	COLORREF oldColor = pDC->SetTextColor( textColor );
	//font �O��
	CFont *pOldFont = pDC->SelectObject( &font );
	//�Хå����饦��� ��`���O��
	int nBkMode = pDC->SetBkMode(TRANSPARENT);
	//get text size
	CSize textSize = pDC->GetTextExtent( str );
	//text point ��Ӌ��
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
	//�Хå����饦��� ��`�ɑ���
	pDC->SetBkMode(nBkMode);
	
	//font ����
	pDC->SelectObject( pOldFont );
	
	//text color ����
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
	///< ���ڱ�ʾ�r�Υ�����
	m_wndSize.cx = 0;
	m_wndSize.cy = 0;
	//��`���`�ѥ��`���O��.
	SetUserParam( 0, 0 );
	// �����ƥ��������ڻ�
	ClearActiveInfo( &m_activeInfo );
	///< AXGDICtrl�ηN�E_AXGDICTRL_KIND���գ�
	m_nKind = nKind;
}
/**
 * 	���ԩ`���󥹥ȥ饯��
 * 		�뤨��줿CAXGDICtrl�򥳥ԩ`����
 * 
 * 	@param org	���ԩ`ԪCAXGDICtrl���饹
 */
CAXGDICtrl::CAXGDICtrl( const CAXGDICtrl &org )
{
	operator = (org);
}
/// �ǥ��ȥ饯��
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
/// ������ɥ����ɕr�Υ�å��`���ϥ�ɥ�
void CAXGDICtrl::PreSubclassWindow() 
{	// TODO: ����λ�ä˹��Ф΄I���׷�Ӥ��뤫���ޤ��ϻ������饹����ӳ����Ƥ�������

	///< ���ڱ�ʾ�r�Υ�����
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
/// ������ɥ��Ɨ��r�Υ�å��`���ϥ�ɥ�
void CAXGDICtrl::OnDestroy() 
{
	CWnd::OnDestroy();
	m_wndSize.cx = 0;
	m_wndSize.cy = 0;
}
////////////////////////////////////////////////////
// ������ɥ����軭
void CAXGDICtrl::OnPaint() 
{	// TODO: ����λ�ä˥�å��`�� �ϥ�ɥ��äΥ��`�ɤ�׷�Ӥ��Ƥ�������
	// �軭�å�å��`���Ȥ��� CStatic::OnPaint() ����ӳ����ƤϤ����ޤ���
	CPaintDC dc(this); // �軭�äΥǥХ��� ����ƥ�����
	//get rect size
	CRect rectItem;
	GetClientRect( &rectItem );

	//���¤α����軭��20050929yotsutsu �×�ӑ
	DrawBackground( &dc, rectItem );

	// �ե���Ȥ�ȡ��
	LOGFONT logfont;
	GetParent()->GetFont()->GetLogFont( &logfont );
	// �ե���Ȥ�����?�x�k
	CFont font;
	font.CreateFontIndirect( &logfont );
	CFont *pOldFont = dc.SelectObject( &font );
	//�軭ǰ�I��
	BeginPaintDC( &dc, rectItem );
	//�軭
	DrawDC( &dc, rectItem );
	//�����軭
	DrawExDC( &dc, rectItem );
	//Active��״�B���軭
	DrawActiveState( &dc, rectItem );
	// �軭��I��
	EndPaintDC( &dc, rectItem );
	// �ե���Ȥ����
	dc.SelectObject( pOldFont );
	font.DeleteObject();
}
///////////////////////////////////////
// �����ե��`�������ܤ�ȡ��
void CAXGDICtrl::OnSetFocus(CWnd* pOldWnd)
{
	///< TRUE:�x�k/FALSE:���x�k��״�B
	CWnd::OnSetFocus(pOldWnd);
	if(IsEnableActivate())	{
		m_activeInfo.nActive = AXGCTRLACT_FRAME;		///< 1:ȫ��
		NotifyToParent( AXGCN_CHANGE_ACTIVE, NULL );
	}
}
///////////////////////////////////////
// �����ե��`������ʧ�ä�
void CAXGDICtrl::OnKillFocus(CWnd* pNewWnd)
{
	if(pNewWnd && pNewWnd->GetSafeHwnd())	{
		if(pNewWnd->GetOwner() != this)	{
			if(IsEnableActivate())	{
				//m_activeInfo.nActive = AXGCTRLACT_FRAME;		///< 1:ȫ��
				m_activeInfo.nActive = AXGCTRLACT_NONE;///< 0:���x�k
			}
			Redraw();
		}
	}
	CWnd::OnKillFocus(pNewWnd);
}
///////////////////////////////////////
/// �ޥ�����ܥ���Ѻ�¤Εr�Υ�å��`���ϥ�ɥ�
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
/// �ޥ�����ܥ���Ѻ�¤Εr�Υ�å��`���ϥ�ɥ�
void CAXGDICtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	if( GetSafeHwnd() )	{
		//if((GetFocus() != this))	{	this->SetFocus();	}
	}

	CWnd::OnRButtonDown(nFlags, point);
}
///////////////////////////////////////
//Active�ʥ����ƥ�������롣
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
//Active�ʥ����ƥ�Υ�������������롣
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
//Active�ʥ����ƥ�Υ����`��������롣
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
//Active�ʥ��`�����λ�ä���¤��롣
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
 * �HWnd���饹�ؤ�֪ͨ
 *	@param nCode		�I���٤�֪ͨ��å��`���Υ��`��
 *	@param lpActiveInfo	֪ͨ���v�B������줿����ȥ�`������
 *	@param nKey			Ѻ���줿���륭�` ���`�ɤ�ָ�����ޤ���
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
 * Active�ʥ����ƥ�������롣(֪ͨ��å��`���΄I��)
 *	@param		pNotifyMsg	֪ͨ��å��`�������
 *	@return		TRUE:�I������/FALSE:δ�I��
 */
BOOL CAXGDICtrl::OnChangeActive(AXGCNOTIFY *pNotifyMsg )
{
	m_activeInfo = pNotifyMsg->activeInfo;	///< Active״�B�����
	Redraw();
	
	return TRUE;
}
///////////////////////////////////////
/**
 * Active�ʥ����ƥ�Υ�������������롣(֪ͨ��å��`���΄I��)
 *	@param		pNotifyMsg	֪ͨ��å��`�������
 *	@return		TRUE:�I������/FALSE:δ�I��
 */
BOOL CAXGDICtrl::OnChangeStyle(AXGCNOTIFY *pNotifyMsg )
{
	return FALSE;
}
///////////////////////////////////////
/**
 * Active�ʥ����ƥ�Υ����`��������롣(֪ͨ��å��`���΄I��)
 *	@param		pNotifyMsg	֪ͨ��å��`�������
 *	@return		TRUE:�I������/FALSE:δ�I��
 */
BOOL CAXGDICtrl::OnChangeScale(AXGCNOTIFY *pNotifyMsg )
{
	return FALSE;
}
///////////////////////////////////////
/**
 * Active�ʥ��`�����λ�ä���¤��롣(֪ͨ��å��`���΄I��)
 *	@param		pNotifyMsg	֪ͨ��å��`�������
 *	@return		TRUE:�I������/FALSE:δ�I��
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
 * 	���ڥ������������롣
 * 		�F�ڤΥ������ˉ������
 *	@return ���¤Υ�����
 */
const CSize & CAXGDICtrl::RecalcInitSize(void)
{
	CRect rect;
	GetClientRect( rect );
	//���ڱ�ʾ
	m_wndSize.cx = rect.Width();
	m_wndSize.cy = rect.Height();

	return m_wndSize;
}
///////////////////////////////////////
/**
 * 	Active״�B���軭.
 * 		Active״�B���ʾ����
 * 
 * 	@param pDC		�軭����ǥХ�������ƥ����ȤΥݥ���
 * 	@param rect		�軭�I��ι���
 */
void CAXGDICtrl::DrawActiveState( CDC *pDC, const CRect &rect )
{
	if( !GetSafeHwnd())	{	return;	}
	if( (GetFocus() == this))	{
		// �֥饷������	
		CBrush	brush;
		brush.CreateSolidBrush(GetBkColor());
	//	COLORREF bkColor = ~GetBkColor();
	//	COLORREF bkColor = ::Color2Gray(GetBkColor());
		int iOldRop = pDC->SetROP2( R2_NOT );
	//	brush.CreateSolidBrush(!bkColor);//::GetSysColor(COLOR_HIGHLIGHT));
		// �֥饷���x�k
		CBrush *pOldBrush = pDC->SelectObject( &brush );
		
		DrawActiveFrame( pDC, rect );

		pDC->SetROP2( iOldRop );
		// �֥饷�����
		pDC->SelectObject( pOldBrush );
		// �֥饷���Ɨ�
		brush.DeleteObject();
	}
}
///////////////////////////////////////
/**
 * 	Active״�B���軭.
 * 		Active״�B���ʾ����
 * 
 * 	@param pDC		�軭����ǥХ�������ƥ����ȤΥݥ���
 * 	@param rect		�軭�I��ι���
 */
void CAXGDICtrl::DrawActiveFrame( CDC *pDC, const CRect &rect, int size )
{
	CRect rectItem = rect;
	//�ե�`��
	//����
	rectItem.bottom = rectItem.top + size;
	rectItem.right = rectItem.left + size;
	pDC->Rectangle( rectItem );
	//����
	rectItem.top = ( rect.top + rect.bottom - size ) / 2;
	rectItem.bottom = rectItem.top + size;
	pDC->Rectangle( rectItem );
	//����
	rectItem.top = rect.bottom - size;
	rectItem.bottom = rect.bottom;
	pDC->Rectangle( rectItem );
	//����
	rectItem.left = (rect.left + rect.right - size ) / 2 ;
	rectItem.right = rectItem.left + size;
	pDC->Rectangle( rectItem );
	//����
	rectItem.left = rect.right - size;
	rectItem.right = rect.right;
	pDC->Rectangle( rectItem );
	//����
	rectItem.top = ( rect.top + rect.bottom - size ) / 2 ;
	rectItem.bottom = rectItem.top + size;
	pDC->Rectangle( rectItem );
	//����
	rectItem.top = rect.top;
	rectItem.bottom = rectItem.top + size;
	pDC->Rectangle( rectItem );
	//����
	rectItem.left = (rect.left + rect.right - size ) / 2 ;
	rectItem.right = rectItem.left + size;
	pDC->Rectangle( rectItem );
}
///////////////////////////////////////
/**
 * 	PrintDC���軭����.��ӡˢ�ã�
 * 		ָ�����줿DC���軭����
 * 
 * 	@param pDC			�軭����DC
 * 	@param rect			�軭�����I���RECT
 * 	@param bMonochrome	��Υ���`��ӡˢ���Є�/�o��
 * 	@param bMonochrome	�����軭���Є�/�o��
 */
void CAXGDICtrl::PrintDC( CDC *pDC, const CRect &rect, BOOL bMonochrome /*= FALSE*/, BOOL bDrawExFlag /*= FALSE*/ )
{
	// �ե���Ȥ�ȡ��
	LOGFONT logfont;
	GetParent()->GetFont()->GetLogFont( &logfont );
	//Font size ���{��
	if(GetInitSize().cx > 0 && GetInitSize().cy > 0)	{
		if( rect.Height() > rect.Width() )	{
			logfont.lfHeight = FtoL((double)logfont.lfHeight * rect.Width() / GetInitSize().cx  + 0.5) ;
		}	else	{
			logfont.lfHeight = FtoL((double)logfont.lfHeight * rect.Height() / GetInitSize().cy  + 0.5) ;
		}
	}	else	{
		logfont.lfHeight = -MulDiv( 9, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	}

	// �ե���Ȥ�����?�x�k
	CFont font;
	font.CreateFontIndirect( &logfont );
	CFont *pOldFont = pDC->SelectObject( &font );

	//��Υ���`��ӡˢ���Є�/�o��
	BOOL bOld = EnableMonochrome( bMonochrome );

	//�軭
	DrawDC( pDC, rect );

	//�����軭
	if(bDrawExFlag)	{	DrawExDC( pDC, rect );	}

	//��Υ���`��ӡˢ���Є�/�o��
	EnableMonochrome( bOld );

	//font��Ԫ�ˑ��� & ����
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
	m_lfOrientation = 0;//�軭����
	SetBkColor(bkColor);
	m_nKind = AXGCTRL_STRING;
}
///////////////////////////////////////
/**
 * 	���ԩ`���󥹥ȥ饯��
 * 		�뤨��줿CAXStringWnd�򥳥ԩ`����
 * 
 * 	@param org	���ԩ`ԪCAXStringWnd���饹
 */
CAXStringWnd::CAXStringWnd( const CAXStringWnd &org )
{
	operator = (org);
}
///////////////////////////////////////
//�ǥ��ȥ饯��
CAXStringWnd::~CAXStringWnd()
{
}
BEGIN_MESSAGE_MAP(CAXStringWnd, CAXGDICtrl)
	//{{AFX_MSG_MAP(CAXStringWnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
////////////////////////////////////////////////////
void CAXStringWnd::PreSubclassWindow() 
{	// TODO: ����λ�ä˹��Ф΄I���׷�Ӥ��뤫���ޤ��ϻ������饹����ӳ����Ƥ�������
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
			//�������夬rect size�򳬤���Τǡ�space�Ǥ�����С����ˤ��Ƥ��롣
			if(m_lfOrientation == 900 || m_lfOrientation == -900)	{
				long lSpace = rect.Width() * 25 / 100;	//�Ȥꤢ����25��
				logFont.lfHeight = rect.Width() - lSpace;
			}	else	{
				long lSpace = rect.Height() * 25 / 100;	//�Ȥꤢ����25��
				logFont.lfHeight = rect.Height() - lSpace;
			}
		}
		logFont.lfWeight = FW_NORMAL;			//̫�� default�� FW_NORMAL��400��FW_HEAVY��900
	//	logFont.lfWidth  = rect.Width() / 10 ;	//���ȡ��ȉ����Τ�ע��
	}
	//	�軭���� ���֤λ����� x �S�ȤνǶȤ� (0.1 �ȅgλ��) ָ�����ޤ����ǶȤ� y �������򤭤�����ϵ�Ǥ� x �S���鷴�rӋ�ؤ�ˡ�y �������򤭤�����ϵ�ǤϕrӋ�ؤ��Ӌ�y���ޤ���
	logFont.lfOrientation = m_lfOrientation;
	logFont.lfEscapement = m_lfOrientation;

	//font create
	font.CreateFontIndirect( &logFont );

	//COLORREF textColor = ( IsMonochrome() ? IBLACK : GetStrColor() );

	CAXColorString::TextDraw( pDC, rect , font, IsMonochrome(), m_lfOrientation );	

	font.DeleteObject();
}