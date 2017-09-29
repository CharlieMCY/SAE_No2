// AXGDICore.h : �إå��` �ե�����
//
/********************************************************
// ���饹�Υ��󥿩`�ե�����
// CLinePen			:�饤���åڥ󥯥饹
// CAXLineStyle		:�饤�󥹥����륯�饹
// CAXMarkerStyle	:�ީ`���`�������륯�饹
// CAXPatternStyle	:�ѥ��`�󥹥����륯�饹
// CAXGDIFrame		:AXGDI�軭���饹
// CAXColorString	:ɫ����TEXT���饹
// CAXGDICtrl		:AXGDI�軭CWnd���饹
// CAXStringWnd		:ɫ����TEXTWnd���饹
//												by YOTSUTSU
//	* History	:	date:2005,24,Mar.	��Ҏ����
ver.1.00	
********************************************************/
//////////////////////////////////////////////////////////////////////

#if !defined(_AXGDICORE_H_INCLUDED_)
#define _AXGDICORE_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AxGdiDef.h"// ����

//AXColorStringStyle

/////////////////////////////////////////////////////////////////////////////
// ������
#pragma pack( push, 1 )
	/// �饤�󥹥����똋����
	typedef struct tagLineStyle{	//16Byte
		int 		iStyle;			///< ���N
		int			iSize;			///< ��������
		COLORREF	color;			///< ��ɫ
		int			iReserve1;		///< ���
	} LINESTYLE;

	/// �ީ`���`�����������
	typedef struct tagMarkerStyle{	//16Byte
		int			iMarker;		///< �ݥ��󥿥ީ`���`
		int			iMarkSize;		///< �ީ`���`������
		int			iBkStyle;		///< �ީ`���`�����軭
		int			iReserve1;		///< ���
	} MARKERSTYLE;

	/// �軭���ꥢ�Υѥ��`�󥹥��������
	typedef struct tagPatternStyle{	//16Byte
		int			iBStyle;		///< /* Brush Styles */BS_SOLID
		int			iHStyle;		///< /* Hatch Styles */HS_HORIZONTAL
		COLORREF	color;			///< ɫ
		int			iReserve1;		///< ���
	} PATTERNSTYLE;

	/// ����եǩ`��������
	typedef struct tagXYPoint{
		double		dX;			///< ����X
		double		dY;			///< ����Y
	} XYPOINT;

#pragma pack( pop )

/////////////////////////////////////////////////////////////////////////////
// �v��
//�ީ`���軭
extern void _stdcall DrawMark( CDC *pDC, int iStyle, CPoint pos, int iSize = 8 );
//���쥤����`��Q
extern COLORREF _stdcall Color2Gray( COLORREF color );
///////////////////////////////////////
/**
 * 	double->long��Q
 *		�����ȸ���С���㡡->��32 �ӥåȤη��Ÿ������� 
 * 
 * 	@param data	��������double:�����ȸ���С���㣩
 * 	@return		��������long:32 �ӥåȤη��Ÿ���������
 */
extern inline long _stdcall FtoL( double data )
{
	return (((data)>0.0)?(long)(data + 0.5):(long)(data - 0.5));
}
extern int _stdcall GetDecLength(double dRange);
/////////////////////////////////////////////////////////////////////////////
//�饤���åڥ󥯥饹
class CLinePen : public CPen
{
// ���󥹥ȥ饯�����
public:
	CLinePen(){};
	CLinePen( int nPenStyle, int nWidth, COLORREF crColor ){
		CreatePen( nPenStyle, nWidth, crColor );
	}

public:
	BOOL CreatePen( int nPenStyle, int nWidth, COLORREF crColor )
	{
		//return CPen::CreatePen( nPenStyle , nWidth, crColor );

		DWORD stDash[] = {10, 5	};
		DWORD stDot[]  = { 4, 4	};
		DWORD stDashDot[]    = { 10, 4, 2, 4	};
		DWORD stDashDotDOT[] = { 10, 4, 2, 4, 2, 4	};
		
		LOGBRUSH logBrush;
		logBrush.lbStyle = BS_SOLID;
		logBrush.lbColor = crColor;

		int iNum = 0;
		DWORD *pStyle;
		switch( nPenStyle ){
		case PS_DASH:		iNum = 2; pStyle = stDash;		break;
		case PS_DOT:		iNum = 2, pStyle = stDot;		break;
		case PS_DASHDOT:	iNum = 4, pStyle = stDashDot;	break;
		case PS_DASHDOTDOT:	iNum = 6, pStyle = stDashDotDOT;break;
		default:			return CPen::CreatePen( nPenStyle, nWidth, crColor );
		}

		if( nWidth <= 0 ) nWidth = 1;
		for( int i = 0; i < iNum; i++ ) pStyle[i] *= nWidth;
		return CPen::CreatePen( PS_USERSTYLE|PS_GEOMETRIC, nWidth, &logBrush, iNum, pStyle );
	}
};
/////////////////////////////////////////////////////////////////////////////
// CAXLineStyle
class CAXLineStyle
{
// ���󥹥ȥ饯�����
public:
	CAXLineStyle( int iStyle = PS_NULL , COLORREF color = IWHITE, int iSize = 0)
	{
		memset(&m_lineStyle, 0x00, sizeof(LINESTYLE) );
		SetLineStyle(iStyle, color, iSize);//�ǥե�����O��
	}
	CAXLineStyle( const LINESTYLE &lineStyle )
	{
		memset(&m_lineStyle, 0x00, sizeof(LINESTYLE) );
		SetLineDefault();//�ǥե�����O��
		SetLineStyle( lineStyle );
	}
	CAXLineStyle( const CAXLineStyle &org )
	{
		operator =(org);
	}
	virtual ~CAXLineStyle(){}
// ���ȥ�ӥ�`��
public:	
	///< �饤�����
	inline void SetLineStyle( const LINESTYLE &lineStyle );
	inline void SetLineStyle( int iStyle = PS_SOLID , COLORREF color = IWHITE, int iSize = -1);
	inline void SetLineColor( COLORREF color );

	inline const LINESTYLE & GetLineStyle(void) const	{	return m_lineStyle;	}				///< �饤�����
	inline COLORREF GetLineColor(void) const			{	return m_lineStyle.color;	}		///< ��ɫ
	inline int GetPenStyle(void) const					{	return m_lineStyle.iStyle;	}		///< ���N
	inline int GetLineSize(void) const					{	return m_lineStyle.iSize;	}		///< ��������

	///<�ǥե�����O��
	inline void SetLineDefault( int iStyle = PS_NULL , COLORREF color = IWHITE, int iSize = 0)
	{
		SetLineStyle( iStyle, color, iSize );
	}
protected:
	LINESTYLE	m_lineStyle;	///< �饤�����
// ���ڥ�`�����
public:
	// ���ڻ�
	inline CAXLineStyle &operator =( const CAXLineStyle &src );
	inline CAXLineStyle & Copy( const CAXLineStyle &src )	{	operator =(src); return (*this);	}
// ���`�Щ`�饤��
public:
	///< ���軭
	virtual void Redraw(BOOL bErase = TRUE){}
};
/////////////////////////////////////////////////////////////////////////////
// CAXMarkerStyle
class CAXMarkerStyle
{
// ���󥹥ȥ饯�����
public:
	CAXMarkerStyle(int iMarker = MARKNONE, int iMarkSize = 8, int iBkStyle = 0)
	{
		memset(&m_markStyle, 0x00, sizeof(MARKERSTYLE) );
		SetMarkerStyle( iMarker, iMarkSize, iBkStyle );//�ǥե�����O��
	}
	CAXMarkerStyle( const MARKERSTYLE &markStyle )
	{
		memset(&m_markStyle, 0x00, sizeof(MARKERSTYLE) );
		SetMarkerDefault();
		SetMarkerStyle( markStyle );
	}
	CAXMarkerStyle( const CAXMarkerStyle &org )
	{
		operator =( org );
	}
	virtual ~CAXMarkerStyle(){};
// ���ȥ�ӥ�`��
public:
	///< �ީ`���`���
	inline void SetMarkerStyle( const MARKERSTYLE &markStyle );
	inline void SetMarkerStyle( int iMarker = MARKNONE, int iMarkSize = -1, int iBkStyle = -1 );
	inline int SetMarkerSize(int iMarkSize);
	
	inline const MARKERSTYLE & GetMarkerStyle(void) const {	return m_markStyle;	}		///< �ީ`���`���
	inline int GetMarkerKind(void) const		{	return m_markStyle.iMarker;		}	///< �ݥ��󥿥ީ`���`
	inline int GetMarkerSize(void) const		{	return m_markStyle.iMarkSize;	}	///< �ީ`���`������
	inline int GetMarkerBkStyle(void) const		{	return m_markStyle.iBkStyle;	}	///< �ީ`���`�����軭
	
	///<�ǥե�����O��
	inline void SetMarkerDefault(int iMarker = MARKNONE, int iMarkSize = 8, int iBkStyle = 0)
	{
		SetMarkerStyle( iMarker, iMarkSize, iBkStyle );
	}
protected:
	MARKERSTYLE	m_markStyle;	///< �ީ`���`���
// ���ڥ�`�����
public:
	// ���ڻ�
	inline CAXMarkerStyle &operator =( const CAXMarkerStyle &src );
	inline CAXMarkerStyle & Copy( const CAXMarkerStyle &src )	{	operator =(src); return (*this);	}
// ���`�Щ`�饤��
public:
	///< ���軭
	virtual void Redraw(BOOL bErase = TRUE){}
};
/////////////////////////////////////////////////////////////////////////////
// CAXPatternStyle
class CAXPatternStyle
{
// ���󥹥ȥ饯�����
public:
	CAXPatternStyle(int iBStyle = BS_SOLID, int iHStyle = HS_HORIZONTAL, COLORREF color = IPINK )
	{
		memset(&m_patternStyle, 0x00, sizeof(PATTERNSTYLE) );
		SetPatternStyle( iBStyle, iHStyle, color );//�ǥե�����O��
	}
	CAXPatternStyle( const PATTERNSTYLE &patternStyle )
	{
		memset(&m_patternStyle, 0x00, sizeof(PATTERNSTYLE) );
		SetPatternStyle( patternStyle.iBStyle, patternStyle.iHStyle, patternStyle.color );//�ǥե�����O��
	}
	CAXPatternStyle( const CAXPatternStyle &org )
	{
		operator =( org );
	}
	virtual ~CAXPatternStyle(){};
// ���ȥ�ӥ�`��
public:
	/// �軭���ꥢ�Υ֥饷���
	inline void SetPatternStyle( const PATTERNSTYLE &patternStyle );
	inline void SetPatternStyle( int iBStyle , int iHStyle , COLORREF color  );
	inline COLORREF SetPatternColor( COLORREF color );
	
	inline const PATTERNSTYLE & GetPatternStyle(void) const {	return m_patternStyle;	}	///< �軭���ꥢ�Υ֥饷���
	inline int GetBrushStyle(void) const	{	return m_patternStyle.iBStyle;	}		///< /* Brush Styles */BS_SOLID
	inline int GetHatchStyle(void) const	{	return m_patternStyle.iHStyle;	}		///< /* Hatch Styles */HS_HORIZONTAL
	inline COLORREF GetPatternColor(void) const	{	return m_patternStyle.color;	}		///< ɫ
protected:
	PATTERNSTYLE	m_patternStyle;	///< �軭���ꥢ�Υ֥饷���
// ���ڥ�`�����
public:
	// ���ڻ�
	inline CAXPatternStyle &operator =( const CAXPatternStyle &src );
	inline CAXPatternStyle & Copy( const CAXPatternStyle &src )	{	operator =(src); return (*this);	}
// ���`�Щ`�饤��
public:
	///< ���軭
	virtual void Redraw(BOOL bErase = TRUE){}
};
/////////////////////////////////////////////////////////////////////////////
//CAXGDIFrame
class CAXGDIFrame
{
// ���󥹥ȥ饯�����
public:
	CAXGDIFrame( COLORREF bkColor = ICTRLCOLOR );
	//���ԩ`���󥹥ȥ饯��
	CAXGDIFrame( const CAXGDIFrame &org );
// ����ץ���Ʃ`�����
public:
	virtual ~CAXGDIFrame();
	//���ԩ`
	inline CAXGDIFrame & operator = ( const CAXGDIFrame &src );
	inline CAXGDIFrame & Copy( const CAXGDIFrame &src )	{	operator=(src);	return *this;	}

// ���ȥ�ӥ�`��
public:
	///< ����ɫ
	inline COLORREF SetBkColor( COLORREF color );
	inline COLORREF GetBkColor(void)	{	return m_bkColor;	}
	///< ����ʾɫ
	inline COLORREF SetFrameColor( COLORREF color );
	inline COLORREF GetFrameColor(void)	{	return m_frameColor;	}
	///< ����ʾ�ե饰
	inline void ShowFrame(BOOL bShow = TRUE)	{	m_bFrameVisible = bShow; Redraw();	}
	inline BOOL	IsFrameVisible(void)	{	return m_bFrameVisible;	}
	///< ��Υ���`���ʾ
	inline BOOL EnableMonochrome ( BOOL bEnable );
	inline BOOL IsMonochrome (void)	{	return m_bMonochrome;	}

protected:
	COLORREF	m_bkColor;			///< background color
	COLORREF	m_frameColor;		///< Frame line color
	BOOL		m_bMonochrome;		///< ��Υ���`���ʾ�ե饰
	BOOL		m_bFrameVisible;	///< ����ʾ�ե饰
// ���`�Щ`�饤��
public:
	///< �����軭
	inline virtual void DrawBackground( CDC *pDC, const CRect rect );
	///< ���軭
	inline virtual void DrawFrame( CDC *pDC, CRect rect );
// ���ڥ�`�����
public:
	///< �饤�󥹥������軭
	virtual void DrawLineStyle( CDC *pDC, const CRect &rect, const LINESTYLE &lineStyle, long lOrientation = 0 );
	///< �ީ`���`�軭
	virtual void DrawMarker( CDC *pDC, CPoint pos, const MARKERSTYLE &markStyle, COLORREF color );
	///< ���軭
	virtual void Redraw(BOOL bErase = TRUE){}
};
/////////////////////////////////////////////////////////////////////////////
//CAXColorString
class CAXColorString
{
// ���󥹥ȥ饯�����
public:
	CAXColorString(void);
	//���ԩ`���󥹥ȥ饯��
	CAXColorString( const CAXColorString &org );
// ����ץ���Ʃ`�����
public:
	virtual ~CAXColorString();
	//���ԩ`
	inline CAXColorString & operator = ( const CAXColorString &src );
	inline CAXColorString & Copy( const CAXColorString &src )	{	operator=(src);	return *this;	}
// ���ȥ�ӥ�`��
public:
	///< �����б�ʾɫ
	inline virtual COLORREF	SetStrColor( COLORREF color = COLOR_BTNTEXT );
	inline COLORREF GetStrColor(void) const {	return( m_colorData );	}
	///< ��ʾ������
	inline virtual CString GetString(void) const {	return ( m_strData );	}
	inline virtual int GetString( LPTSTR lpszStringBuf, int nMaxCount ) const {
		_tcsncpy( lpszStringBuf, m_strData, nMaxCount );
		lpszStringBuf[nMaxCount - 1] = '\0';
		return ( 1 );//���Ȥ�ֱ����
	}

	inline void SetString( LPCTSTR lpszString );
	///< ��ʾ��������
	virtual WORD SetTextStyle(WORD wStyle = (SS_CENTER | SS_CENTERIMAGE));
	virtual WORD GetTextStyle(void) const;
	///< �軭�ե��`�ޥå�
	inline UINT SetDTFormat( UINT nFormat /*= (DT_VCENTER | DT_CENTER)*/);///< DrawText Format
	inline UINT GetDTFormat(void) const		{	return m_nDTFormat;		}	///< DrawText Format
	inline UINT	GetDTPosV(void) const		{	return GetDTPosV(m_nDTFormat);	}
	inline UINT	GetDTPosH(void) const		{	return GetDTPosH(m_nDTFormat);	}

protected:
	inline static UINT	GetDTPosV( UINT nDTFormat )	{
		if(nDTFormat & DT_VCENTER)		{	return DT_VCENTER;	}
		else if(nDTFormat & DT_BOTTOM)	{	return DT_BOTTOM;	}
		return DT_TOP;
	}
	inline static UINT	GetDTPosH( UINT nDTFormat )	{
		if(nDTFormat & DT_CENTER)		{	return DT_CENTER;	}
		else if(nDTFormat & DT_RIGHT)	{	return DT_RIGHT;	}
		return DT_LEFT;
	}
protected:
	CString		m_strData;			///< Display string
	COLORREF	m_colorData;		///< string color
	UINT		m_nDTFormat;		///< DrawText Format

// ���ڥ�`�����
public:
	virtual void TextDraw( CDC* pDC, CRect &rect, CFont &font, BOOL bMonochrome, long lfOrientation );
	virtual void TextDraw( CDC* pDC, CRect &rect, CFont &font, LPCTSTR lpszString, const COLORREF textColor, UINT nDTFormat, long lfOrientation );
// ���`�Щ`�饤��
public:
	///< ���軭
	virtual void Redraw(BOOL bErase = TRUE){}
};
/////////////////////////////////////////////////////////////////////////////
//CAXGDICtrl
/*
 * CAXGDICtrl Control Mesages
 */
typedef enum E_AXGDICTRL_NOTIFY{
//#define GCN_SETFOCUS			1	//
//#define GCN_KILLFOCUS			2	//
	AXGCN_CHANGE_ACTIVE = 1,	//Active�ʥ����ƥ�������롣(����ǰ��Message��Call)
	AXGCN_UPDATE_ACTIVE,		//Active�ʥ����ƥ����¤�����(�������Message��Call)
	AXGCN_CHANGE_STYLE,			//Active�ʥ����ƥ�Υ�������������롣(����ǰ��Message��Call)
	AXGCN_UPDATE_STYLE,			//Active�ʥ����ƥ�Υ����������¤�����(�������Message��Call)
	AXGCN_CHANGE_SCALE,			//Active�ʥ����ƥ�Υ����`��������롣(����ǰ��Message��Call)
	AXGCN_UPDATE_SCALE,			//Active�ʥ����ƥ�Υ����`�����¤�����(�������Message��Call)
	AXGCN_CHANGE_CURSOL,		//Active�ʥ��`�����λ�ä���¤��롣(����ǰ��Message��Call)
	AXGCN_UPDATE_CURSOL,		//Active�ʥ��`�����λ�ä���¤�����(�������Message��Call)
};

typedef enum E_AXGDICTRL_KIND{
	AXGCTRL_NONE = 0,		///< 0:���x�k
	AXGCTRL_GRAPH_WND,		///< 1:����ե���ȥ�`��
	AXGCTRL_CHART_WND,		///< 2:����`�ȥ���ȥ�`��
	AXGCTRL_GRAPH,			///< 1:����ե���ȥ�`��
	AXGCTRL_CHART,			///< 2:����`�ȥ���ȥ�`��

	AXGCTRL_MEASURE = 10,	///< 10:�᥸��`����ȥ�`��
	AXGCTRL_STRING,			///< 11:���ȥ�󥰥���ȥ�`��
	AXGCTRL_LINESTYLE,		///< 12:�饤�󥹥����륳��ȥ�`��
};

///< 0:���x�k/1:ȫ��/2:�ǩ`��/3:���`����/4:���ꥢ���`����
typedef enum E_AXGDICTRLACTIVE_TYPE{
	AXGCTRLACT_NONE = 0,	///< 0:���x�k
	AXGCTRLACT_FRAME,		///< 1:ȫ��
	AXGCTRLACT_DATA,		///< 2:�ǩ`��
	AXGCTRLACT_CURSOL,		///< 3:���`����
	AXGCTRLACT_AREACSL,		///< 4:���ꥢ���`����
};

typedef struct tagAXGCActiveInfo{
	UINT	nKind;			///< AXGDICtrl�ηN�E_AXGDICTRL_KIND���գ�
	UINT	nActive;		///< 0:���x�k/1:ȫ��/2:�ǩ`��/3:���`����/4:���ꥢ���`����/
	int		iLayer;			///< Active�ʥ쥤��`����				-1:�o�� 0���ꥸ��
	int		iLine;			///< Active�ʥ쥤��`�饤�󷬺�			-1:�o�� 0���ꥸ��
	int		iIndex;			///< Active�ʥ쥤��`�Υ���ǥå������	-1:�o�� 0���ꥸ��
}AXGCACTINFO;

typedef struct tagAXGDICtrlNotify{
	NMHDR		hdr;		///< ���٤Ƥ� WM_NOTIFY ��å��`���˹�ͨ�����
	AXGCACTINFO	activeInfo;	///< ֪ͨ���v�B������줿����ȥ�`������
	UINT		nKeyParam;	///< Keyboad Message
} AXGCNOTIFY, FAR* LPAXGCNOTIFY;

///<MouseZoomType �ޥ�������C��
typedef enum E_MOUSE_ZOOM{
	ZOOM_OFF = 0,	///< �o
	XY_ZOOM,		///< X����Y����΁I����򒈴�
	X_ZOOM,			///< X���򒈴�
	Y_ZOOM,			///< Y���򒈴�
};

class CAXGDICtrl : public CWnd, virtual public CAXGDIFrame
{
	//DECLARE_DYNAMIC(CAXGDICtrl)
public:
	/// ��`���`�ѥ��`��
	typedef struct tagUserParam{
		DWORD		m_dwParam1;		///< ��`���`�ѥ��`����
		DWORD		m_dwParam2;		///< ��`���`�ѥ��`����
	} USERPARAM;
// ���󥹥ȥ饯�����
public:
	CAXGDICtrl( UINT nKind = AXGCTRL_NONE, COLORREF bkColor = ICTRLCOLOR );
	//���ԩ`���󥹥ȥ饯��
	CAXGDICtrl( const CAXGDICtrl &org );

// ����ץ���Ʃ`�����
public:
	virtual ~CAXGDICtrl();
	inline CAXGDICtrl & operator = ( const CAXGDICtrl &src );
	inline CAXGDICtrl & Copy( const CAXGDICtrl &src );
// ���ȥ�ӥ�`��
public:
	// ���ڥ�������ȡ�ä��롣
	inline const CSize & GetInitSize( void ) const	{	return m_wndSize;	}	///< ����դ�Rect
	///< AXGDICtrl�ηN�E_AXGDICTRL_KIND���գ�
	inline UINT GetCtrlKind(void) const	{	return m_nKind;	}
	//******** �����C�� ********//
	//Activate
	inline void EnableActivate( BOOL bEnable );
	inline BOOL IsEnableActivate( void );

	// ��`���`�ѥ��`��
	inline void  SetUserParam( DWORD dwParam1, DWORD dwParam2 );
	inline USERPARAM &GetUserParam( void );
// ���ڥ�`�����
public:
	// ӡˢ��
	virtual void PrintDC( CDC *pDC, const CRect &rect, BOOL bMonochrome = FALSE, BOOL bDrawExFlag = FALSE );

// ���`�Щ`�饤��
	// ClassWizard �ρ����v���Υ��`�Щ`�饤�ɤ����ɤ��ޤ���
	//{{AFX_VIRTUAL(CAXGDICtrl)
	public:
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
protected:
	// �HWnd���饹�ؤ�֪ͨ
	virtual void NotifyToParent(UINT nCode, AXGCACTINFO *lpActiveInfo = NULL, UINT nKey = 0x0000);
	// ֪ͨ��å��`���΄I��
	virtual BOOL OnChangeActive( AXGCNOTIFY *pNotifyMsg );
	virtual BOOL OnChangeStyle( AXGCNOTIFY *pNotifyMsg );
	virtual BOOL OnChangeScale( AXGCNOTIFY *pNotifyMsg );
	virtual BOOL OnChangeCursol( AXGCNOTIFY *pNotifyMsg );
	// �x�k״�B�軭
	virtual void DrawActiveState( CDC *pDC, const CRect &rect );
	virtual void DrawActiveFrame( CDC *pDC, const CRect &rect, int size = 7 );
	// �軭ǰ�I��
	virtual void BeginPaintDC( CDC *pDC, const CRect &rect ){};
	// �軭��I��
	virtual void EndPaintDC( CDC *pDC, const CRect &rect ){};

public:
	// ���ڥ������������롣
	virtual const CSize & RecalcInitSize(void);
	// �軭
	///< �����軭
//	virtual void DrawBackground( CDC *pDC, const CRect rect );
	virtual void DrawDC( CDC *pDC, CRect rect ){};
	virtual void DrawExDC( CDC *pDC, const CRect &rect ){};
	virtual void Redraw(BOOL bErase = TRUE){
		if( IsWindow( m_hWnd ) ){
			Invalidate(bErase);
			UpdateWindow();
		}
	};

	// ���ɤ��줿��å��`�� �ޥå��v��
protected:
	//{{AFX_MSG(CAXGDICtrl)
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//afx_msg BOOL OnEraseBkgnd( CDC* pDC );

	afx_msg void OnChangeActive(NMHDR * pNotifyStruct, LRESULT* result );
	afx_msg void OnChangeStyle(NMHDR * pNotifyStruct, LRESULT* result );
	afx_msg void OnChangeScale(NMHDR * pNotifyStruct, LRESULT* result );
	afx_msg void OnChangeCursol(NMHDR * pNotifyStruct, LRESULT* result );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	UINT		m_nKind;		///< AXGDICtrl�ηN�E_AXGDICTRL_KIND���գ�
	CSize		m_wndSize;		///< ���ڱ�ʾ�r�Υ�����
	AXGCACTINFO	m_activeInfo;	///< Active״�B�����
	USERPARAM	m_userParam;	///< ��`���`�ѥ��`��
protected:
	// �����ƥ��������ڻ�
	inline void ClearActiveInfo( AXGCACTINFO *lpActiveInfo );
};
/////////////////////////////////////////////////////////////////////////////
//CAXStringWnd
class CAXStringWnd : public CAXGDICtrl, virtual public CAXColorString
{
// ���󥹥ȥ饯�����
public:
	CAXStringWnd( COLORREF bkColor = ICTRLCOLOR );
	//���ԩ`���󥹥ȥ饯��
	CAXStringWnd( const CAXStringWnd &org );

// ����ץ���Ʃ`�����
public:
	virtual ~CAXStringWnd();
	inline CAXStringWnd & operator = ( const CAXStringWnd &src );
	inline CAXStringWnd & Copy( const CAXStringWnd &src );
// ���ȥ�ӥ�`��
public:
	///< Test size adjust
	inline void SetTextSizeAdjust(BOOL bAdjust = TRUE)	{	m_bTextSizeAdjust = bAdjust;	}
	///< �軭�Ƕ�
	inline void SetTextOrientation(long nOrientation)	{	m_lfOrientation = nOrientation;	}

// ���ڥ�`�����
public:
	virtual void DrawDC( CDC *pDC, CRect rect );
	virtual void DrawItem( CDC *pDC, CRect rect, CFont *pTextFont = NULL );
	virtual void TextDraw( CDC* pDC, CRect rect, CFont *pTextFont = NULL );


// ���`�Щ`�饤��
public:
	// ClassWizard �ρ����v���Υ��`�Щ`�饤�ɤ����ɤ��ޤ���
	//{{AFX_VIRTUAL(CAXStringWnd)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	virtual void Redraw(BOOL bErase = TRUE){
		if( IsWindow( m_hWnd ) ){	Invalidate(bErase);	UpdateWindow();	}
	};
	// ���ɤ��줿��å��`�� �ޥå��v��
protected:
	//{{AFX_MSG(CAXStringWnd)
	//afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	BOOL		m_bTextSizeAdjust;	///< Test size adjust
	long		m_lfOrientation;	///< �軭�Ƕ�
	
};
/////////////////////////////////////////////////////////////////////////////
// inline finction
/////////////////////////////////////////////////////////////////////////////
// CAXLineStyle
///////////////////////////////////////
/**
 * 	���O��
 * 
 * 	@param lineStyle	����Style
 */
inline void CAXLineStyle::SetLineStyle( const LINESTYLE &lineStyle )
{
	SetLineStyle(lineStyle.iStyle, lineStyle.color, lineStyle.iSize );
}
///////////////////////////////////////
/**
 * 	���O��
 * 
 * 	@param iStyle	���ηN�
 * 	@param color	����ɫ
 * 	@param iSize	���Υ�����
 */
inline void CAXLineStyle::SetLineStyle( int iStyle, COLORREF color, int iSize )
{
	m_lineStyle.iStyle = iStyle;
	m_lineStyle.color  = color;
	if(iSize >= 0)	{	m_lineStyle.iSize = iSize;	}
	m_lineStyle.iReserve1 = 0;
	Redraw();
}
///////////////////////////////////////
/**
 * 	����ɫ�O��
 * 
 * 	@param color	����ɫ
 */
inline void CAXLineStyle::SetLineColor( COLORREF color )
{
	m_lineStyle.color  = color;
	Redraw();
}
///////////////////////////////////////
/**
 * 	�饤�󥹥�����Υ��ԩ`.
 * 
 * 	@param src	���ԩ`Ԫ�饤�󥹥�����
 * 	@return		���Υ��饹�Υݥ���
 */
inline CAXLineStyle & CAXLineStyle::operator =( const CAXLineStyle &src )
{
	m_lineStyle  = src.m_lineStyle;
	Redraw();
	return *this;
}
/////////////////////////////////////////////////////////////////////////////
// CAXMarkerStyle
///////////////////////////////////////
/**
 * 	�ީ`���`����������O������.
 * 
 * 	@param markStyle		�ީ`���`�����
 */
inline void CAXMarkerStyle::SetMarkerStyle( const MARKERSTYLE &markStyle )
{
	SetMarkerStyle( markStyle.iMarker, markStyle.iMarkSize, markStyle.iBkStyle );
}
///////////////////////////////////////
/**
 * 	�ީ`���`����������O������.
 * 
 * 	@param iMarker		�ީ`���`��������
 * 	@param iMarkSize	�ީ`��������
 * 	@param iBkStyle		�ީ`���`������0:�o/1:��/-1:������ʤ�
 */
inline void CAXMarkerStyle::SetMarkerStyle( int iMarker /*= MARKNONE*/, int iMarkSize /*= -1*/, int iBkStyle /*= -1*/ )
{
	m_markStyle.iMarker = iMarker;
	if( iMarkSize  >=  0 ) m_markStyle.iMarkSize  = iMarkSize;
	if( iBkStyle >=  0 ) m_markStyle.iBkStyle = iBkStyle;
//	m_markStyle.iReserve1 = 0;
	Redraw();
}
///////////////////////////////////////
/**
 * 	�ީ`���`���������O������.
 * 
 * 	@param iMarkSize	�ީ`��������
 * 	@return ���ǰ�Υީ`��������
 */
inline int CAXMarkerStyle::SetMarkerSize(int iMarkSize)
{	
	int iOld = m_markStyle.iMarkSize;
	if( iMarkSize  >  0 ) m_markStyle.iMarkSize  = iMarkSize;
	return iOld;
}
///////////////////////////////////////
/**
 * 	�ީ`���`��������Υ��ԩ`.
 * 
 * 	@param src	���ԩ`Ԫ�ީ`���`��������
 * 	@return		���Υ��饹�Υݥ���
 */
inline CAXMarkerStyle & CAXMarkerStyle::operator =( const CAXMarkerStyle &src )
{
	m_markStyle = src.m_markStyle;
	Redraw();
	return *this;
}
/////////////////////////////////////////////////////////////////////////////
// CAXPatternStyle
///////////////////////////////////////
/**
 * 	�軭���ꥢ�Υ֥饷����������O������.
 * 
 * 	@param patternStyle		�軭���ꥢ�Υ֥饷��������
 */
inline void CAXPatternStyle::SetPatternStyle( const PATTERNSTYLE &patternStyle )
{
	SetPatternStyle( patternStyle.iBStyle, patternStyle.iHStyle, patternStyle.color );//�ǥե�����O��
}
///////////////////////////////////////
/**
 * 	�軭���ꥢ�Υ֥饷����������O������.
 * 
 * 	@param	int iBStyle		Brush Styles BS_SOLID
 * 	@param	int iHStyle		Hatch Styles HS_HORIZONTAL
 * 	@param	COLORREF color	�軭ɫ
 */
inline void CAXPatternStyle::SetPatternStyle( int iBStyle , int iHStyle , COLORREF color  )
{
	m_patternStyle.iBStyle = iBStyle;		///<  Brush Styles BS_SOLID
	m_patternStyle.iHStyle = iHStyle;		///<  Hatch Styles HS_HORIZONTAL
	m_patternStyle.color = color;			///< ɫ
	m_patternStyle.iReserve1 = 0;
	Redraw();
}
///////////////////////////////////////
/**
 * 	�軭���ꥢ�Υ֥饷ɫ���O������.
 * 
 * 	@param color	�֥饷ɫ
 * 	@return ���ǰ�Υ֥饷ɫ
 */
inline COLORREF CAXPatternStyle::SetPatternColor( COLORREF color )
{	
	int iOld = m_patternStyle.color;
	m_patternStyle.color  = color;
	return iOld;
}
///////////////////////////////////////
/**
 * 	�軭���ꥢ�Υ֥饷��������Υ��ԩ`.
 * 
 * 	@param src	���ԩ`Ԫ�֥饷��������
 * 	@return		���Υ��饹�Υݥ���
 */
inline CAXPatternStyle & CAXPatternStyle::operator =( const CAXPatternStyle &src )
{
	m_patternStyle = src.m_patternStyle;
	Redraw();
	return *this;
}
/////////////////////////////////////////////////////////////////////////////
// CAXGDIFrame
///////////////////////////////////////
/**
 * 	CAXGDIFrame���饹�Υ��ԩ`.
 * 		�뤨��줿CAXGDIFrame���饹�򥳥ԩ`����
 * 
 * 	@param src	���ԩ`Ԫ��CAXGDIFrame���饹
 * 	@return		���Υ��饹�Υݥ���
 */
inline CAXGDIFrame & CAXGDIFrame::operator = ( const CAXGDIFrame &src )
{
	m_bkColor = src.m_bkColor;				///< background color
	m_frameColor = src.m_frameColor;		///< Frame line color
	m_bMonochrome = src.m_bMonochrome;		///< ��Υ���`���ʾ�ե饰
	m_bFrameVisible = src.m_bFrameVisible;	///< ����ʾ�ե饰
	Redraw();
	return (*this);
}
///////////////////////////////////////
/**
 * 	����ɫ�O��.
 * 	@param color	����ɫ
 */
inline COLORREF CAXGDIFrame::SetBkColor( COLORREF color )
{
	COLORREF oldColor = m_bkColor;
	m_bkColor = color;
	Redraw();
	return oldColor;
}
///////////////////////////////////////
/**
 * 	��ɫ�O��.
 * 	@param color	��ɫ
 * 	@return		���ǰ�Ζ�ɫ
 */
inline COLORREF CAXGDIFrame::SetFrameColor( COLORREF color )
{
	COLORREF oldColor = m_frameColor;		///<Frame line color
	m_frameColor = color;
	Redraw();
	return oldColor;
}
///////////////////////////////////////
/**
 * 	��Υ���`���ʾ�O��.
 * 	@param bEnable	TRUE:�Є�/FALSE:�o��
 * 	@return		���ǰ�α�ʾ�O��
 */
inline BOOL CAXGDIFrame::EnableMonochrome ( BOOL bEnable )
{	
	BOOL bOld = m_bMonochrome;
	m_bMonochrome = bEnable;
	return bOld;
}
///////////////////////////////////////
/**
 * 	�������軭���롣
 * 	@param	pDC			�軭�ǥХ�������ƥ�����
 * 	@param	rect		�軭���ꥢ
 */
inline void CAXGDIFrame::DrawBackground( CDC *pDC, const CRect rect )
{
	//background draw
	pDC->FillSolidRect( rect, (IsMonochrome() ? IWHITE : GetBkColor()) );
}
///////////////////////////////////////
/**
 * 	�����軭���롣
 * 	@param	pDC			�軭�ǥХ�������ƥ�����
 * 	@param	rect		�軭���ꥢ
 */
inline void CAXGDIFrame::DrawFrame( CDC *pDC, CRect rect )
{
	//Frame draw
	if(IsFrameVisible())	{	
		pDC->FrameRect( rect, &CBrush((IsMonochrome() ? IBLACK : GetFrameColor())) );
	}
}
/////////////////////////////////////////////////////////////////////////////
// CAXColorString
///////////////////////////////////////
/**
 * 	CAXColorString���饹�Υ��ԩ`.
 * 		�뤨��줿CAXColorString���饹�򥳥ԩ`����
 * 
 * 	@param src	���ԩ`Ԫ��CAXColorString���饹
 * 	@return		���Υ��饹�Υݥ���
 */
inline CAXColorString & CAXColorString::operator = ( const CAXColorString &src )
{
	m_colorData = src.m_colorData;		///< font color
	m_strData = src.m_strData;			///< Display string
	m_nDTFormat = src.m_nDTFormat;		///< Display style
	Redraw();

	return *this;
}
///////////////////////////////////////
/**
 *	set draw string
 *	
 *	@param	lpszString		draw string
 */
inline void CAXColorString::SetString( LPCTSTR lpszString )
{
	m_strData = lpszString;
	Redraw();
}
///////////////////////////////////////
/**
 *	set font color
 *	
 *	@param	color	font color
 *	@return	Old Value
 */
inline COLORREF	CAXColorString::SetStrColor( COLORREF color )
{
	COLORREF oldColor = m_colorData;
	m_colorData = color;
	Redraw();
	return oldColor;
}
///////////////////////////////////////
/**
 *	set draw text format
 *	
 *	@param	nFormat	draw text format: DT_TOP / DT_LEFT / DT_CENTER / DT_RIGHT / DT_VCENTER / DT_BOTTOM   
 *	@return	Old Value
 */
inline UINT CAXColorString::SetDTFormat( UINT nFormat )
{	
	UINT nOld = m_nDTFormat;

	UINT nNewDTFormat = (m_nDTFormat & ~0x000F) | nFormat;
	m_nDTFormat = nNewDTFormat;
	return 	nOld;
}
/////////////////////////////////////////////////////////////////////////////
// CAXGDICtrl
///////////////////////////////////////
/**
 * 	CAXGDICtrl���饹�Υ��ԩ`.
 * 		�뤨��줿CAXGDICtrl���饹�򥳥ԩ`����
 * 
 * 	@param src	���ԩ`Ԫ��CAXGDICtrl���饹
 * 	@return		���Υ��饹�Υݥ���
 */
inline CAXGDICtrl & CAXGDICtrl::operator = ( const CAXGDICtrl &src )
{
	CAXGDIFrame::Copy(src);
	
	ClearActiveInfo( &m_activeInfo );	///< Active״�B�����
	m_userParam = src.m_userParam;	///< ��`���`�ѥ��`��
	Redraw();
	return *this;
}
///////////////////////////////////////
/**
 * 	CAXGDICtrl���饹�Υ��ԩ`.
 * 		�뤨��줿CAXGDICtrl���饹�򥳥ԩ`����
 * 
 * 	@param src	���ԩ`Ԫ��CAXGDICtrl���饹
 * 	@return		���Υ��饹�Υݥ���
 */
inline CAXGDICtrl & CAXGDICtrl::Copy( const CAXGDICtrl &src )
{
	operator=(src);
	return *this;
}
///////////////////////////////////////
/**
 * 	����ȥ�`����x�k�Є��C�ܤ�ON/OFF����.
 * 
 * 	@param bEnable	�x�k�C�ܤ��Є��ˤ��뤫�Υե饰(TRUE:ON FALSE:OFF)
 * 	@return			
 */
inline void CAXGDICtrl::EnableActivate( BOOL bEnable )
{
	if( bEnable )	{
		if(GetSafeHwnd())	{	ModifyStyle( 0, SS_NOTIFY|WS_CHILD );	}//<<<<��Ҫ
	}	else	{
		if(GetSafeHwnd())	{	ModifyStyle( SS_NOTIFY, 0 );	}//<<<<��Ҫ
	}
}
///////////////////////////////////////
/**
 * 	����ȥ�`����x�k�Є��C�ܤ�ȡ�ä���.
 * 
 * 	@return��TRUE:�Є� FALSE:�o��			
 */
inline BOOL CAXGDICtrl::IsEnableActivate( void )
{
	if(GetSafeHwnd())	{
		if( (GetStyle() & SS_NOTIFY) && (GetStyle() & WS_CHILD) )	{	return TRUE;	}
	}
	return FALSE;
}
///////////////////////////////////////
/**
 * 	��`���`�ѥ��`���O��.
 * 
 * 	@param dwParam1	��`���`�ѥ��`��1
 * 	@param dwParam2	��`���`�ѥ��`��2
 */
inline void CAXGDICtrl::SetUserParam( DWORD dwParam1, DWORD dwParam2 )
{
	m_userParam.m_dwParam1 = dwParam1;
	m_userParam.m_dwParam2 = dwParam2;
}
///////////////////////////////////////
/**
 * 	��`���`�ѥ��`��ȡ��.
 * 
 * 	@return		��`���`�ѥ��`��
 */
inline CAXGDICtrl::USERPARAM & CAXGDICtrl::GetUserParam()
{
	return m_userParam;
}
///////////////////////////////////////
/**
 * 	Active�����Υ��ꥢ.
 *
 */
inline void CAXGDICtrl::ClearActiveInfo( AXGCACTINFO *lpActiveInfo )
{
	///< Active״�B�����Υ��ꥢ
	memset(lpActiveInfo, 0x00, sizeof(AXGCACTINFO));

	
	///< AXGDICtrl�ηN�E_AXGDICTRL_KIND���գ�
	lpActiveInfo->nKind = AXGCTRL_NONE;
	///< 0:���x�k/1:ȫ��/2:�ǩ`��/3:���`����/4:���ꥢ���`����
	lpActiveInfo->nActive = AXGCTRLACT_NONE;
	lpActiveInfo->iLayer = -1;	///< Active�ʥ쥤��`����
	lpActiveInfo->iLine = -1;	///< Active�ʥ쥤��`�饤�󷬺�
	lpActiveInfo->iIndex = -1;	///< Active�ʥ쥤��`�Υ���ǥå������
}
/////////////////////////////////////////////////////////////////////////////
// CAXStringWnd
///////////////////////////////////////
/**
 * 	CAXStringWnd���饹�Υ��ԩ`.
 * 		�뤨��줿CAXStringWnd���饹�򥳥ԩ`����
 * 
 * 	@param src	���ԩ`ԪCAXStringWnd���饹
 * 	@return		���Υ��饹�Υݥ���
 */
inline CAXStringWnd & CAXStringWnd::operator = ( const CAXStringWnd &src )
{
	CAXGDICtrl::Copy(src);
	CAXColorString::Copy(src);
	m_bTextSizeAdjust = src.m_bTextSizeAdjust;	///< Test size adjust
	m_lfOrientation = src.m_lfOrientation;	///< �軭�Ƕ�

	Redraw();
	return *this;
}
///////////////////////////////////////
/**
 * 	CAXStringWnd���饹�Υ��ԩ`.
 * 		�뤨��줿CAXStringWnd���饹�򥳥ԩ`����
 * 
 * 	@param src	���ԩ`ԪCAXStringWnd���饹
 * 	@return		���Υ��饹�Υݥ���
 */
inline CAXStringWnd & CAXStringWnd::Copy( const CAXStringWnd &src )
{
	operator=(src);
	return *this;
}
#endif // !defined(_AXGDICORE_H_INCLUDED_)