// AXGraphCtrl.h: CAXGraphCtrl ���饹�Υ��󥿩`�ե�����
//
/********************************************************
// CXYPlotData		:�ǩ`�����饹���ǩ`���������`�롢���`���뱣�֣�
// CAXGraphCtrl		:������軭���饹
//											by YOTSUTSU
//	* History	:	date:2005,24,Mar.	��Ҏ����
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
// CAXGraphCtrl ������ɥ�
/////////////////////////////////////////////////////////////////////////////
/// ����ե��饹
class CAXGraphCtrl : public CAXGDIPlotCtrl
{
// ���󥹥ȥ饯�����
public:
	CAXGraphCtrl( COLORREF bkColor = IBLACK );
	CAXGraphCtrl( CAXGraphCtrl &org );
	

// ���ȥ�ӥ�`��
public:

// ���ڥ�`�����
public:

// ���`�Щ`�饤��
	// ClassWizard �ρ����v���Υ��`�Щ`�饤�ɤ����ɤ��ޤ���
	//{{AFX_VIRTUAL(CAXGraphCtrl)
	protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow();
//	virtual BOOL OnChildNotify( UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult );
	//}}AFX_VIRTUAL

// ����ץ���Ʃ`�����
public:
	virtual ~CAXGraphCtrl();

	// ���ɤ��줿��å��`�� �ޥå��v��
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
	// ֪ͨ��å��`���΄I��
	virtual BOOL OnChangeActive( AXGCNOTIFY *pNotifyMsg );
	virtual BOOL OnChangeStyle( AXGCNOTIFY *pNotifyMsg );
	virtual BOOL OnChangeScale( AXGCNOTIFY *pNotifyMsg );
	virtual BOOL OnChangeCursol( AXGCNOTIFY *pNotifyMsg );
	
protected:
	// �軭ǰ�I��
	virtual void BeginPaintDC( CDC *pDC, const CRect &rect );
	// �軭
	virtual void DrawLayerData( CDC *pDC, const CRect &rect, CXYPlotData &data );
	// ���`�����軭
//	virtual void DrawLayerLineCursor( CDC *pDC, const CRect &rect, CXYPlotData &data );
//	virtual void DrawLineCursor( CDC *pDC, const CRect &rect, CXYPlotData &data, AXCURSORINFO &cursorInfo );
	// ���ꥢ���`�����軭
//	virtual void DrawLayerAreaCursor( CDC *pDC, const CRect &rect, CXYPlotData &data );
//	virtual void DrawAreaCursor( CDC *pDC, const CRect &rect, CXYPlotData &data, AXAREACSRINFO &areaInfo );
//	virtual void DrawLayerAreaCsrName( CDC *pDC, const CRect &rect, CXYPlotData &data );
//	virtual void DrawAreaCsrName( CDC *pDC, const CRect &rect, CXYPlotData &data, AXAREACSRINFO &areaInfo );

	virtual void DrawActiveState( CDC *pDC, const CRect &rect );

	// �ޥ�����ܥ���Ѻ�¤Εr��Activate
	virtual int MouseLBdownActivate( const CRect &rect, CPoint point, AXGCACTINFO *lpActiveInfo );


protected:
	/// �ǩ`��(�쥤���`�ǩ`��)
	CArray<CXYPlotData,CXYPlotData>	m_plotData;

public:
	// ���ڻ�
	inline CAXGraphCtrl& operator =( CAXGraphCtrl &src );
	inline virtual void RemoveAllItem(void);
	inline virtual void ClearAllItem(void);

	// �쥤���`׷��/����
	inline int AddLine( int iStyle = PS_SOLID, COLORREF color = 0x00ffffff, int iSize = 0, int nDataSize = 0 );
	inline int AddLine( const LINESTYLE &lineStyle, int nDataSize = 0  );
	inline int AddLine( const LINESTYLE &lineStyle, const MARKERSTYLE &markStyle, int nDataSize = 0  );
	inline int AddLine( const CAXLineStyle &axlineStyle, int nDataSize = 0  );
	inline int AddLine( const CAXLineStyle &axlineStyle, const CAXMarkerStyle &axmarkStyle, int nDataSize = 0  );
//	inline int AddLine( CAXPlotStyle &plotStyle, int nDataSize = 0  );
	// �ǩ`�����������O��
	inline void SetDataSize( int nDataSize );
	// �ǩ`��������
	inline void ClearAllData(void);
	inline void RemoveAllLine(void);
//200611 t.tachibana added start>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	inline void RemoveLine(int nIndex, int nCount = 1);
//200611 t.tachibana added end<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	// �ǩ`������Ҫ�ؤ�ȡ��
	inline CXYPlotData & operator []( int n );
	inline CXYPlotData & GetLine( int n );
	// �ǩ`��������
	inline int  GetLineNum(void);
	// ��ʾ�饤����
	inline int  GetShowLineNum(void);

	// �ǩ`����ʾ����
	void SetXScale( double dMin, double dMax, double dDelta = -1.0, double dDetailDelta = -1, BOOL bAllLayer = FALSE );
	void SetYScale( double dMin, double dMax, double dDelta = -1.0, double dDetailDelta = -1, BOOL bAllLayer = FALSE );
//200612 t.tachibana added start>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	void SetXScaleEx( double dMin, double dMax, double dDelta = -1.0, double dDetailDelta = -1, BOOL bAllLayer = FALSE, BOOL bRedraw = FALSE );
	void SetYScaleEx( double dMin, double dMax, double dDelta = -1.0, double dDetailDelta = -1, BOOL bAllLayer = FALSE, BOOL bRedraw = FALSE );
//200612 t.tachibana added end<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	//����������軭
	void SetXLogScale(BOOL bLog = TRUE, BOOL bScaleAuto = TRUE );
	void SetYLogScale(BOOL bLog = TRUE, BOOL bScaleAuto = TRUE );
	// ������`��
	void  Scroll( double dScrollX, double dScrollY );
	// �ǩ`����Min&Maxһ�����ꥢ
	void ClearMinMax( void );

//******** �����C�� ********//
	///< �ޥ�������C��
	// ����Ւ���
	virtual void Zoom( CRect rectZoom );

	// �軭
	virtual void DrawDC( CDC *pDC, CRect rect )				{	DrawGraph( pDC, rect );	}
	virtual void DrawExDC( CDC *pDC, const CRect &rect )	{	DrawLineCursor( pDC, rect );	}
	// ������軭	
	virtual void DrawGraph( CDC *pDC, const CRect &rect );
	// ���`�����軭
	virtual void DrawLineCursor( CDC *pDC, const CRect &rect );
	// �ٱ�ʾ
	inline void Redraw(BOOL bRedraw = FALSE);
};
/////////////////////////////////////////////////////////////////////////////
// inline finction
/////////////////////////////////////////////////////////////////////////////
// CAXGraphCtrl
///////////////////////////////////////
/**
 * 	���ԩ`.
 * 		�뤨��줿����դΥǩ`���򥳥ԩ`����
 * 
 * 	@param src	���ԩ`Ԫ�����
 * 	@return		���Υ��饹�Υݥ���
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
 * 	���٤Ƥ����Υ��ꥢ.
 *
 */
inline void CAXGraphCtrl::ClearAllItem(void)
{
	ClearAllData();
	CAXGDIPlotCtrl::ClearAllItem();
}
///////////////////////////////////////
/**
 * 	���٤Ƥ���������.
 *
 */
inline void CAXGraphCtrl::RemoveAllItem(void)
{
	//ClearActiveInfo(&m_activeInfo);	///< Active״�B�����Υ��ꥢ
	RemoveAllLine();					//�ǩ`���Υ��ꥢ
	CAXGDIPlotCtrl::RemoveAllItem();
}
///////////////////////////////////////
/**
 * 	����׷�Ӥ���.
 * 
 * 	@param	iStyle		���N
 * 	@param	color		��ɫ
 * 	@param	iSize		��������
 *	@param	nDataSize	�ǩ`��������
 * 	@return				׷�Ӥ������ξ����� 0��
 */
int CAXGraphCtrl::AddLine( int iStyle /*= PS_SOLID*/, COLORREF color /*= 0x00ffffff*/, int iSize /*= 0*/, int nDataSize /*= 0*/)
{
	int index = m_plotData.Add( CXYPlotData( iStyle, color, iSize ) );
	m_plotData[index].SetSize( nDataSize );
	return index;
}
///////////////////////////////////////
/**
 * 	����׷�Ӥ���.
 * 
 * 	@param lineStyle	�饤�󥹥�����
 * 	@param markStyle	�ީ`���`��������
 *	@param	nDataSize	�ǩ`��������
 * 	@return				׷�Ӥ������ξ����� 0��
 */
int CAXGraphCtrl::AddLine( const LINESTYLE &lineStyle, int nDataSize /*= 0*/)
{
	int index = m_plotData.Add( CXYPlotData( lineStyle ) );
	m_plotData[index].SetSize( nDataSize );
	return index;
}
///////////////////////////////////////
/**
 * 	����׷�Ӥ���.
 * 
 * 	@param lineStyle	�饤�󥹥�����
 * 	@param markStyle	�ީ`���`��������
 *	@param	nDataSize	�ǩ`��������
 * 	@return				׷�Ӥ������ξ����� 0��
 */
int CAXGraphCtrl::AddLine( const LINESTYLE &lineStyle, const MARKERSTYLE &markStyle, int nDataSize /*= 0*/ )
{
	int index = m_plotData.Add( CXYPlotData( lineStyle, markStyle ) );
	m_plotData[index].SetSize( nDataSize );
	return index;
}
///////////////////////////////////////
/**
 * 	����׷�Ӥ���.
 * 
 * 	@param axlineStyle	�饤�󥹥����륯�饹
 *	@param	nDataSize	�ǩ`��������
 * 	@return				׷�Ӥ������ξ����� 0��
 */
int CAXGraphCtrl::AddLine( const CAXLineStyle &axlineStyle, int nDataSize /*= 0*/  )
{
	int index = m_plotData.Add( CXYPlotData( axlineStyle ) );
	m_plotData[index].SetSize( nDataSize );
	return index;
}
///////////////////////////////////////
/**
 * 	����׷�Ӥ���.
 * 
 * 	@param axlineStyle	�饤�󥹥����륯�饹
 * 	@param axmarkStyle	�ީ`���`�������륯�饹
 *	@param	nDataSize	�ǩ`��������
 * 	@return				׷�Ӥ������ξ����� 0��
 */
int CAXGraphCtrl::AddLine( const CAXLineStyle &axlineStyle, const CAXMarkerStyle &axmarkStyle, int nDataSize /*= 0*/  )
{
	int index = m_plotData.Add( CXYPlotData( axlineStyle, axmarkStyle ) );
	m_plotData[index].SetSize( nDataSize );
	return index;
}
///////////////////////////////////////
/**
 * 	�ǩ`�����������O������.
 * 		�O�������ǩ`�����������I���_�����롣
 *	
 *	@param		nDataSize	�O������ǩ`��������
 * 	@return		�I���_�������ǩ`��������
 */
inline void CAXGraphCtrl::SetDataSize( int nDataSize )
{
	//for(int index = 0; index < GetLineNum(); index++ )	{
		m_plotData/*[index].*/.SetSize( nDataSize );
	//}
}
///////////////////////////////////////
/**
 * 	���٤Ƥξ���ǩ`���򥯥ꥢ����.
 * 		���٤Ƥξ����ӥǩ`���򥯥ꥢ���ޤ���
 */
void CAXGraphCtrl::ClearAllData(void)
{
	for(int index = 0; index < GetLineNum(); index++ )	{
		m_plotData[index].ClearAllPoint();
	}
}
///////////////////////////////////////
/**
 * 	���٤Ƥξ�����������.
 * 		���٤Ƥξ����ӥǩ`�����������ޤ�����ޤ�׷�Ӥ����饤�󷬺Ť�ȫ�Ɵo���ˤʤ�ޤ���
 */
void CAXGraphCtrl::RemoveAllLine(void)
{
	m_plotData.RemoveAll();
}
//200611 t.tachibana added start>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
///////////////////////////////////////
/**
 * 	index��ָ������������������.
 *		!!!!����Ҫ�����Υ����å��ϡ����饹����Ȥ����R�����Ҫ���Ф�!!!!
 * 	@param nIndex	0 ���Ϥǡ�GetUpperBound �����������¤������Υ���ǥå�����
 * 	@param nCount	��������Ҫ������
 *	
 */
inline void CAXGraphCtrl::RemoveLine(int nIndex, int nCount/* = 1*/)
{
	m_plotData.RemoveAt(nIndex, nCount);
}
//200611 t.tachibana added end<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///////////////////////////////////////
/**
 * 	�ץ�åȥǩ`��ȡ��.
 * 	@param n	������
 * 	@return		�ץ�åȥǩ`�����饹�Υݥ���
 */
inline CXYPlotData & CAXGraphCtrl::operator []( int n )
{
	return m_plotData[n];
}
///////////////////////////////////////
/**
 * 	�ץ�åȥǩ`��ȡ��.
 * 	@param n	������
 * 	@return		�ץ�åȥǩ`�����饹�Υݥ���
 */
inline CXYPlotData & CAXGraphCtrl::GetLine( int n )
{
	return m_plotData[n];
}
///////////////////////////////////////
/**
 * 	������ȡ��.
 * 		�O������Ƥ��뾀������ȡ�ä���
 * 
 * 	@return	�O������Ƥ��뾀����
 */
inline int CAXGraphCtrl::GetLineNum( void )
{
	return m_plotData.GetUpperBound()+1;
}
///////////////////////////////////////
/**
 * 	��ʾ�Фξ�����ȡ��.
 * 		�O������Ƥ����ʾ�Фξ�������ȡ�ä���
 * 
 * 	@return	�O������Ƥ����ʾ�Фξ�����
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
 * 	�ٱ�ʾ.
 * 		����դ��ٱ�ʾ���롣
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
 * 	�ޥ����ǤΥ���Ւ���C�ܤ��O������.
 * 
 * 	@param iZoom	����C�ܤ��O������
 *		ZOOM_OFF = 0,
 *		XY_ZOOM,		///<X����Y����΁I����򒈴�
 *		X_ZOOM,			///<X���򒈴�
 *		Y_ZOOM,			///<Y���򒈴�
 * 	@return			�S��״�B�򷵤���
 */
//inline int CAXGraphCtrl::EnableMouseZoom ( int iZoom /*= XY_ZOOM*/ )
/*
{
	if(IsEnableActivate())	{
		if(m_iMouseZoom == XY_ZOOM || m_iMouseZoom == X_ZOOM || m_iMouseZoom == Y_ZOOM  )	{
			m_iMouseZoom = iZoom;	///< �ޥ�������C��ON/OFF�ե饰
		}
	}
	return m_iMouseZoom;
}
///////////////////////////////////////
/**
 * 	�ޥ����ǤΥ���Ւ���C�ܤ�ON/OFF����.
 * 
 * 	@return			����Ւ���C���S��״�B�򷵤���
 *
inline int CAXGraphCtrl::GetMouseZoom ( void )
{
	return m_iMouseZoom;
}
///////////////////////////////////////
/**
 * 	�ޥ����ǤΥ���Ւ���C��ON/OFF��ȡ�ä���.
 * 
 * 	@return		����C�ܤ��Є��ե饰
 *
inline BOOL CAXGraphCtrl::IsMouseZoom ()
{
	return	( m_iMouseZoom == ZOOM_OFF  ? FALSE : TRUE) ; 
}
*/
#endif // __GRAPHCTRL_H_INCLUDED__