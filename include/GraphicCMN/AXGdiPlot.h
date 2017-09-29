// AXGDIPlot.h : �إå��` �ե�����
//
/********************************************************
// ���饹�Υ��󥿩`�ե�����
// CAXPlotStyle		:PLOT�������륯�饹
// CAXGDIPlotCtrl	:AXGDI�ץ�å����軭���饹
//												by YOTSUTSU
//	* History	:	date:2005,15,Jul.	��Ҏ����
ver.1.00	
********************************************************/
//////////////////////////////////////////////////////////////////////

#if !defined(_AXGDIPLOT_H_INCLUDED_)
#define _AXGDIPLOT_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "AXGDIWnd.h"
#include "AXMeasureCtrl.h"
#include <Float.h>

//CursorStyle
#define ACSRS_NONE			0x0000	///< ���`����o	
#define ACSRS_X				0x0001	///< X�S���`����
#define	ACSRS_Y				0x0002	///< Y�S���`����	
#define	ACSRS_XYCROSS		0x0003	///< ʮ�֥��`����
#define ACSRS_SHOW          0x0010	///< ��ʾ/�Ǳ�ʾ�ե饰
#define ACSRS_SHACT         0x0020	///< ACTIVE�ީ`����ʾ/�Ǳ�ʾ�ե饰
#define ACSRS_ALL           0xFFFF
/////////////////////////////////////////////////////////////////////////////
// ������
#pragma pack( push, 1 )
	///< ���`�������
	typedef struct tagAXCursorInfoA{	//40byte
		WORD		wSize;			///< Specifies the size, in bytes, of this structure.	
		WORD		wCusorStyle;	///< Cursor style
		int			iLayer;			///< DataLayer index ( -1:�ǩ`��ָ��/��������:�쥤��`ָ��)
		int			iPos;			///< ���`����λ�� �ǩ`���ݥ����ָ��
		int			iReserve1;		///< ���
		XYPOINT		xyValue;		///< ���`����λ�� ��ָ��
		CHAR		szName[8];		///< ���`�������ǰ
	} AXCURSORINFOA;
	///< ���`�������
	typedef struct tagAXCursorInfoW{	//48byte
		WORD		wSize;			///< Specifies the size, in bytes, of this structure.	
		WORD		wCusorStyle;	///< Cursor style
		int			iLayer;			///< DataLayer index ( -1:�ǩ`��ָ��/��������:�쥤��`ָ��)
		int			iPos;			///< ���`����λ�� �ǩ`���ݥ����ָ��
		int			iReserve1;		///< ���
		XYPOINT		xyValue;		///< ���`����λ�� ��ָ��
		WCHAR		szName[8];		///< ���`�������ǰ
	} AXCURSORINFOW;
#pragma pack( pop )


#ifdef UNICODE
typedef tagAXCursorInfoW	tagAXCursorInfo;
typedef AXCURSORINFOW		AXCURSORINFO;
#else
typedef tagAXCursorInfoA	tagAXCursorInfo;
typedef AXCURSORINFOA AXCURSORINFO;
#endif // UNICODE

/////////////////////////////////////////////////////////////////////////////
//CAXGDICursor
class CAXGDICursor //: public tagAXCursorInfo
{
// ���󥹥ȥ饯�����
public:
	CAXGDICursor( void );
	CAXGDICursor( const AXCURSORINFO & cursorInfo );
	//���ԩ`���󥹥ȥ饯��
	CAXGDICursor( const CAXGDICursor &org );
// ���ȥ�ӥ�`��
public:
	//���`�����`�ɤ�ȡ��
	inline virtual int GetCursorMode( void ) const ;//	{	return m_iMode;		}
	//���`����α�ʾ/�Ǳ�ʾ��ȡ��
	inline virtual BOOL IsShowCursor(void) const		{	return ( (m_cursorInfo.wCusorStyle & ACSRS_SHOW) ? TRUE : FALSE );		}
	//���`�����ACTIVE�ީ`����ʾ/�Ǳ�ʾ�ե饰
	inline virtual BOOL IsShowActiveMark(void) const	{	return ( (m_cursorInfo.wCusorStyle & ACSRS_SHACT) ? TRUE : FALSE );		}
	//���`����΂���ȡ�ã���ָ����
	inline virtual XYPOINT GetValue(void) const			{	return m_cursorInfo.xyValue;	}
	//���`����Υǩ`���쥤��`��ȡ�ã��ǩ`���쥤��`ָ����
	inline virtual int GetLayer( void ) const			{	return m_cursorInfo.iLayer;}
	//���`����Υǩ`���ݥ�������ȡ�ã��ǩ`���쥤��`ָ����
	inline virtual int GetPos( void ) const				{	return m_cursorInfo.iPos;		}
	
	//���`����α�ʾ/�Ǳ�ʾ���O��
	inline virtual void ShowCursor(BOOL bShow);
	//���`�����ACTIVE�ީ`����ʾ/�Ǳ�ʾ�ե饰���O��
	inline virtual void ShowActiveMark(BOOL bShow);
	//���`����΂����O������ָ����
	inline virtual void SetValue( XYPOINT xyValue);
	inline virtual void SetValue( double dX, double dY );
	//���`����Υǩ`���쥤��`���O�����ǩ`���쥤��`ָ����
	inline virtual void SetLayer( int iLayer, int iPos = -1);
	//���`����Υǩ`���ݥ��������O�����ǩ`���쥤��`ָ����
	inline virtual void SetPos( int iPos );
	//���`�������Ƥ�ȡ��
	inline virtual CString GetString( void )	{	return (CString(m_cursorInfo.szName));	}
	inline virtual int GetString( LPTSTR lpszStringBuf, int nMaxCount ) const {
		_tcsncpy( lpszStringBuf, m_cursorInfo.szName, nMaxCount );
		lpszStringBuf[nMaxCount - 1] = '\0';
		return ( 1 );//���Ȥ�ֱ����
	}
//	inline virtual void GetString( void )	{	return (CString(m_cursorInfo.szName));	}
	//���`�����`�ɤ��O��
	inline virtual int SetCursorMode( int iMode );
	//���`�������Ƥ��O��
	inline virtual void SetString( LPCTSTR lpszName );
// ����ץ���Ʃ`�����
public:
	//�ǥ��󥹥ȥ饯��
	virtual ~CAXGDICursor( void );

protected:
	virtual void Initialize( void );

protected:

	AXCURSORINFO	m_cursorInfo;

	//CAXGDICtrl *m_pAXGdiCtrl;	///< CAXGDICtrl�Υݥ���
// ���ڥ�`�����
public:
	CAXGDICursor & operator =( const CAXGDICursor &src );
	inline CAXGDICursor & Copy( const CAXGDICursor &src );

	// ���`�������Ƥ��軭
	static void DrawCursorName( CDC *pDC, const CRect &rect, CPoint point, int iCursorMode, LPCTSTR lpszName, COLORREF color );

};
///////////////////////////////////////
/**
 * 	���`�����`�ɤ�ȡ��
 * 
 * 	@return CURSORX:'X' X�S���`���� / CURSORY:'Y' Y�S���`���� / CURSORCROSS:'+' ʮ�֥��`����
 */
inline int CAXGDICursor::GetCursorMode( void ) const
{	
	if((m_cursorInfo.wCusorStyle & ACSRS_X) && (m_cursorInfo.wCusorStyle & ACSRS_Y))	{
		return CURSORCROSS;		///< ʮ�֥��`����
	}	else if((m_cursorInfo.wCusorStyle & ACSRS_Y))	{
		return CURSORY;			///< Y�S���`����
	}	else if((m_cursorInfo.wCusorStyle & ACSRS_X))	{
		return CURSORX;			///< X�S���`����
	}
	return CURSORNONE;			///< ���`����o	
}
///////////////////////////////////////
/**
 * 	���`����α�ʾ/�Ǳ�ʾ���O��
 * 
 * 	@param	bShow	TRUE:��ʾ/FALSE:�Ǳ�ʾ
 */
inline void CAXGDICursor::ShowCursor(BOOL bShow)
{
	if(bShow)	{	m_cursorInfo.wCusorStyle |= ACSRS_SHOW ;				}
	else		{	m_cursorInfo.wCusorStyle &= (ACSRS_ALL ^ ACSRS_SHOW) ;	}
}
///////////////////////////////////////
/**
 * 	���`�����ACTIVE�ީ`����ʾ/�Ǳ�ʾ�ե饰���O��
 * 
 * 	@param	bShow	TRUE:��ʾ/FALSE:�Ǳ�ʾ
 */
inline void CAXGDICursor::ShowActiveMark(BOOL bShow)
{
	if(bShow)	{	m_cursorInfo.wCusorStyle |= ACSRS_SHACT ;					}
	else		{	m_cursorInfo.wCusorStyle &= (ACSRS_ALL ^ ACSRS_SHACT) ;		}
}
///////////////////////////////////////
/**
 * 	���`�����`�ɤ��O��
 * 
 * 	@param iMode	���`�����`��
 *					CURSORX:'X' X�S���`���� / CURSORY:'Y' Y�S���`���� / CURSORCROSS:'+' ʮ�֥��`����
 *	@return	���ǰ�Υ��`�����`��
 */
inline int CAXGDICursor::SetCursorMode( int iMode )
{
	int iOld = GetCursorMode();
	/// ���`�����`��

	switch(iMode)	{
	case CURSORNONE:	///< ���`����o��
	case CURSORX:		// 'X'	///< X�S���`����
	case CURSORY:		// 'Y'	///< Y�S���`����
	case CURSORCROSS:	// '+'	///< ʮ�֥��`����
		m_cursorInfo.wCusorStyle &= (ACSRS_ALL ^ 0x0003) ;//�����ޤ���
		break;
	default:
		break;
	}
	switch(iMode)	{
	case CURSORNONE:	///< ���`����o��
		break;
	case CURSORX:		// 'X'	///< X�S���`����
		m_cursorInfo.wCusorStyle |= ACSRS_X;
		break;
	case CURSORY:		// 'Y'	///< Y�S���`����
		m_cursorInfo.wCusorStyle |= ACSRS_Y;
		break;
	case CURSORCROSS:	// '+'	///< ʮ�֥��`����
		m_cursorInfo.wCusorStyle |= ACSRS_XYCROSS;
		break;
	}

	return iOld;
}
///////////////////////////////////////
/**
 * 	���`��������Ƥ��O��
 * 
 * 	@param lpszName	���`���������
 *	@return
 */
inline void CAXGDICursor::SetString( LPCTSTR lpszName )
{
	_tcsncpy( m_cursorInfo.szName, lpszName, sizeof(m_cursorInfo.szName) );
	m_cursorInfo.szName[sizeof(m_cursorInfo.szName)-1] = _T('\0');
}
///////////////////////////////////////
/**
 * 	���`����΂����O������ָ����
 * 
 * 	@param	xyValue	���`����΂�
 */
inline void CAXGDICursor::SetValue( XYPOINT xyValue )
{
	SetValue( xyValue.dX, xyValue.dY );
}
///////////////////////////////////////
/**
 * 	���`����΂����O������ָ����
 * 
 * 	@param	dX		���`�����X�΂�
 * 	@param	dY		���`�����Y�΂�
 */
inline void CAXGDICursor::SetValue( double dX, double dY )
{
	m_cursorInfo.iLayer = -1;		///< DataLayer index
	m_cursorInfo.xyValue.dX = dX;		///< ��ָ��
	m_cursorInfo.xyValue.dY = dY;		///< ��ָ��
}
///////////////////////////////////////
/**
 * 	���`����Υǩ`���쥤��`���O�����ǩ`���쥤��`ָ����
 * 
 * 	@param	iLayer		�ǩ`���쥤��`�΂�
 * 	@param	iPos		���`����Υݥ������
 */
inline void CAXGDICursor::SetLayer( int iLayer, int iPos /*= -1*/)
{
	if(iLayer >= 0)	{
		m_cursorInfo.iLayer = iLayer;
		if(iPos >= 0)	{	m_cursorInfo.iPos = iPos;	}
//		Redraw();
	}
}
///////////////////////////////////////
/**
 * 	���`����Υǩ`���ݥ��������O�����ǩ`���쥤��`ָ����
 * 
 * 	@param	iPos		���`����Υݥ������
 */
inline void CAXGDICursor::SetPos( int iPos )
{
	if(iPos >= 0)	{	
		m_cursorInfo.iPos = iPos;
//		Redraw();
	}
}
///////////////////////////////////////
/**
 * 	���ԩ`���ڥ�`��
 * 
 * 	@param org	���ԩ`ԪCAXGDICursor
 */
inline CAXGDICursor & CAXGDICursor::Copy( const CAXGDICursor &src )
{	
	operator =(src);
	return (*this);
}
/////////////////////////////////////////////////////////////////////////////
//CAXPlotCursor
class CAXPlotCursor : public CAXGDICursor, virtual public CAXLineStyle, virtual public CAXMarkerStyle
{
// ���󥹥ȥ饯�����
public:
	/**
	 * 	���B.
	 * 		���`���륹������򱣳֤���
	 *
	 * 	@param iMode	���`�����`��	
	 *					CURSORX:'X' X�S���`���� / CURSORY:'Y' Y�S���`���� / CURSORCROSS:'+' ʮ�֥��`����
	 * 	@param iStyle		���N
	 * 	@param color		��ɫ
	 * 	@param iSize		��������
	 */
	CAXPlotCursor( int iMode = CURSORCROSS, int iStyle = PS_SOLID, COLORREF color = 0x00FFFFFF, int iSize = 0)
		: CAXLineStyle( iStyle, color, iSize ), CAXMarkerStyle()
	{
		Initialize();
		SetCursorMode( iMode );
	}
	/**
	 * 	���B.
	 * 		�饤�󥹥������Ԫ�˘��B����
	 * 
	 * 	@param iMode	���`�����`��
	 *					CURSORX:'X' X�S���`���� / CURSORY:'Y' Y�S���`���� / CURSORCROSS:'+' ʮ�֥��`����
	 * 	@param lineStyle	�饤�󥹥�����
	 */
	CAXPlotCursor( int iMode, const LINESTYLE &lineStyle)
		: CAXLineStyle( lineStyle ), CAXMarkerStyle()
	{
		Initialize();
		SetCursorMode( iMode );
	}
	/**
	 * 	���B.
	 * 		�饤�󥹥������Ԫ�˘��B����
	 * 
	 * 	@param iMode	���`�����`��
	 *					CURSORX:'X' X�S���`���� / CURSORY:'Y' Y�S���`���� / CURSORCROSS:'+' ʮ�֥��`����
	 * 	@param axlineStyle	�饤�󥹥�����
	 */
	CAXPlotCursor( int iMode, const CAXLineStyle &axlineStyle )
		: CAXLineStyle( axlineStyle ), CAXMarkerStyle()
	{
		Initialize();
		SetCursorMode( iMode );
	}
	/**
	 * 	���B.
	 * 		�饤�󥹥����롢�ީ`���`���������Ԫ�˘��B����
	 * 
	 * 	@param iMode	���`�����`��
	 *					CURSORX:'X' X�S���`���� / CURSORY:'Y' Y�S���`���� / CURSORCROSS:'+' ʮ�֥��`����
	 * 	@param lineStyle	�饤�󥹥�����
	 * 	@param markStyle	�ީ`���`��������
	 */
	CAXPlotCursor( int iMode, const CAXLineStyle &lineStyle, const MARKERSTYLE &markStyle )
		: CAXLineStyle( lineStyle ), CAXMarkerStyle( markStyle )
	{
		Initialize();
		SetCursorMode( iMode );
	}
	/**
	 * 	���B.
	 * 		�饤�󥹥����롢�ީ`���`���������Ԫ�˘��B����
	 * 
	 * 	@param iMode	���`�����`��
	 *					CURSORX:'X' X�S���`���� / CURSORY:'Y' Y�S���`���� / CURSORCROSS:'+' ʮ�֥��`����
	 * 	@param axlineStyle	�饤�󥹥�����
	 * 	@param axmarkStyle	�ީ`���`��������
	 */
	CAXPlotCursor( int iMode, const CAXLineStyle &axlineStyle, const CAXMarkerStyle &axmarkStyle )
		: CAXLineStyle( axlineStyle ), CAXMarkerStyle( axmarkStyle )
	{
		Initialize();
		SetCursorMode( iMode );
	}
	/**
	 * 	���ԩ`���󥹥ȥ饯��
	 * 		Ԫ��CAXPlotCursor��Ԫ�˘��B����
	 * 
	 * 	@param org	���ԩ`ԪCAXPlotCursor
	 */
	CAXPlotCursor( const CAXPlotCursor &org )	{	operator=( org );	}
// ���ȥ�ӥ�`��
public:

	
// ����ץ���Ʃ`�����
public:
	//�ǥ��󥹥ȥ饯��
	virtual ~CAXPlotCursor() {};

protected:
	inline virtual void Initialize(void);
protected:
// ���ڥ�`�����
public:
	inline CAXPlotCursor & operator =( const CAXPlotCursor &src );
	inline CAXPlotCursor & Copy( const CAXPlotCursor &src );

	// ���`�����軭
	virtual void DrawCursor( CDC *pDC, const CRect &rect, CPoint point, BOOL bMonochrome );
	// ���`����ActiveMark�軭
	virtual void DrawActiveMark( CDC *pDC, const CRect &rect, CPoint pos, int iCursorMode, int iSize );
};
///////////////////////////////////////
/**
 * 	���ڻ��v��
 * 
 * 	@param
 */
inline void CAXPlotCursor::Initialize(void)
{
	CAXGDICursor::Initialize();
}
///////////////////////////////////////
/**
 * 	���ԩ`���ڥ�`��
 * 
 * 	@param src	���ԩ`ԪCAXPlotCursor
 */
inline CAXPlotCursor & CAXPlotCursor::operator =( const CAXPlotCursor &src )
{
	CAXGDICursor::Copy(src);
	CAXLineStyle::Copy(src);
	CAXLineStyle::Copy(src);

	return (*this);
}
///////////////////////////////////////
/**
 * 	���ԩ`���ڥ�`��
 * 
 * 	@param src	���ԩ`ԪCAXPlotCursor
 *	@return��
 */
inline CAXPlotCursor & CAXPlotCursor::Copy( const CAXPlotCursor &src )
{
	operator =(src); 
	return (*this);
}
/////////////////////////////////////////////////////////////////////////////
// CAXAreaCursor
class CAXAreaCursor : public CAXGDICursor, virtual public CAXPatternStyle
{
	// ���󥹥ȥ饯�����
public:
	/**
	 *	���B.
	 * 	�ѥ��`�󥹥������Ԫ�˘��B����.
	 * 
	 * 	@param	int iBStyle		Brush Styles BS_SOLID
	 * 	@param	int iHStyle		Hatch Styles HS_HORIZONTAL
	 * 	@param	COLORREF color	�軭ɫ
	 */
	CAXAreaCursor( int iMode = CURSORCROSS, int iBStyle = BS_SOLID, int iHStyle = HS_HORIZONTAL, COLORREF color = IPINK )
		: CAXPatternStyle( iBStyle , iHStyle , color )
	{
		Initialize();
		SetCursorMode( iMode );
	}
	/**
	 * 	���B.
	 * 		�ѥ��`�󥹥������Ԫ�˘��B����
	 * 
	 * 	@param patternStyle	�ѥ��`�󥹥�����
	 */
	CAXAreaCursor( int iMode, const PATTERNSTYLE &patternStyle )
		: CAXPatternStyle( patternStyle )
	{
		Initialize();
		SetCursorMode( iMode );
	}
	/**
	 * 	���B.
	 * 		�ѥ��`�󥹥������Ԫ�˘��B����
	 * 
	 * 	@param patternStyle	�ѥ��`�󥹥�����
	 */
	CAXAreaCursor( int iMode, const CAXPatternStyle &patternStyle )
		: CAXPatternStyle( patternStyle )
	{
		Initialize();
		SetCursorMode( iMode );
	}
	/**
	 * 	���ԩ`���󥹥ȥ饯��
	 * 		Ԫ��CAXAreaCursor��Ԫ�˘��B����
	 * 
	 * 	@param org	���ԩ`ԪCCAXAreaCursor
	 */
	CAXAreaCursor( const CAXAreaCursor &org )	{	operator=( org );	}
// ���ȥ�ӥ�`��
public:
	//���ꥢ���`����΂���ȡ�ã���ָ����
	inline virtual XYPOINT GetHeadValue(void)	{	return GetValue();	}
	//���ꥢ���`����Υǩ`���ݥ�������ȡ�ã��ǩ`���쥤��`ָ����
	inline virtual int GetHeadPos( void )		{	return m_cursorInfo.iPos;		}
	//���ꥢ���`����΂���ȡ�ã���ָ����
	inline virtual XYPOINT GetTailValue(void)	{	return m_xyTailValue;	}
	//���ꥢ���`����Υǩ`���ݥ�������ȡ�ã��ǩ`���쥤��`ָ����
	inline virtual int GetTailPos( void )		{	return m_iTailPos;		}

	//���ꥢ���`����΂����O������ָ����
	inline virtual void SetAreaValue( XYPOINT xyHeadValue, XYPOINT xyTailValue );
	inline virtual void SetHeadValue( double dHeadX, double dHeadY );
	inline virtual void SetTailValue( double dTailX, double dTailY );
	//���ꥢ���`����Υǩ`���쥤��`���O�����ǩ`���쥤��`ָ����
	inline virtual void SetLayer( int iLayer, int iHeadPos = -1, int iTailPos = -1 );
	//���ꥢ���`����Υǩ`���ݥ��������O�����ǩ`���쥤��`�ݥ������ָ����
	inline virtual void SetPos( int iHeadPos, int iTailPos );
	
	//���ꥢ���`����λ�ä򥪥ե��åȤ��롣����ָ����
	inline virtual void OffsetValue( XYPOINT xyDelta );
	inline virtual void OffsetValue( double dDeltaX, double dDeltaY );
	//���ꥢ���`����λ�ä򥪥ե��åȤ��롣���ݥ������ָ����
	inline virtual void OffsetPos( int iDeltaPos );


// ����ץ���Ʃ`�����
public:
	//�ǥ��󥹥ȥ饯��
	virtual ~CAXAreaCursor() {};

protected:
	inline virtual void Initialize( void );
protected:

	int			m_iTailPos;			///< ���`����λ�� �ǩ`���ݥ����ָ��
	XYPOINT		m_xyTailValue;		///< ���`����λ�� ��ָ��
// ���ڥ�`�����
public:
	inline CAXAreaCursor & operator =( const CAXAreaCursor &src );
	inline CAXAreaCursor & Copy( const CAXAreaCursor &src );

	// ���ꥢ���`�������Ƥ��軭
	virtual void DrawAreaCursorName( CDC *pDC, const CRect &rect, BOOL bMonochrome );
	// ���ꥢ���`����Υѥ��`���軭
	virtual void DrawPattern( CDC *pDC, const CRect &rect, BOOL bMonochrome );
};
///////////////////////////////////////
/**
 * 	���ڻ��v��
 * 
 * 	@param
 */
void CAXAreaCursor::Initialize( void )
{
	m_iTailPos = -1;			///< ���`����λ�� �ǩ`���ݥ����ָ��
	m_xyTailValue.dX = 0.0;		///< ���`����λ�� ��ָ��
	m_xyTailValue.dY = 0.0;		///< ���`����λ�� ��ָ��
	CAXGDICursor::Initialize();
}
///////////////////////////////////////
/**
 * 	���`����΂����O������ָ����
 * 
 * 	@param	xyHeadValue	���`��������^�΂�
 * 	@param	xyTailValue	���`���������΂�
 */
inline void CAXAreaCursor::SetAreaValue( XYPOINT xyHeadValue, XYPOINT xyTailValue )
{
	SetHeadValue( xyHeadValue.dX, xyHeadValue.dY );
	SetTailValue( xyTailValue.dX, xyTailValue.dY );
}
///////////////////////////////////////
/**
 * 	���`��������^�΂����O������ָ����
 * 
 * 	@param	dHeadX		���`��������^��X��
 * 	@param	dHeadY		���`��������^��Y��
 */
inline void CAXAreaCursor::SetHeadValue( double dHeadX, double dHeadY )
{
	SetValue( dHeadX, dHeadY );
}
///////////////////////////////////////
/**
 * 	���`���������΂����O������ָ����
 * 
 * 	@param	dTailX		���`����������X��
 * 	@param	dTailY		���`����������Y��
 */
inline void CAXAreaCursor::SetTailValue( double dTailX, double dTailY )
{
	m_cursorInfo.iLayer = -1;		///< DataLayer index
	m_xyTailValue.dX = dTailX;		///< ��ָ��
	m_xyTailValue.dY = dTailY;		///< ��ָ��
}
///////////////////////////////////////
/**
 * 	���`����Υǩ`���쥤��`���O�����ǩ`���쥤��`ָ����
 * 
 * 	@param	iLayer		�ǩ`���쥤��`�΂�
 * 	@param	iPos		���`��������^�ݥ������
 * 	@param	iPos		���`���������ݥ������
 */
inline void CAXAreaCursor::SetLayer( int iLayer, int iHeadPos /*= -1*/, int iTailPos /*= -1*/ )
{
	if(iLayer >= 0)	{
		m_cursorInfo.iLayer = iLayer;
		SetPos( iHeadPos, iTailPos );
//		Redraw();
	}
}
///////////////////////////////////////
/**
 * 	���`����Υǩ`���ݥ��������O�����ǩ`���쥤��`ָ����
 * 
 * 	@param	iHeadPos		���`��������^�ݥ������
 * 	@param	iTailPos		���`���������ݥ������
 */
inline void CAXAreaCursor::SetPos( int iHeadPos, int iTailPos )
{
	if(iHeadPos >= 0)	{	m_cursorInfo.iPos = iHeadPos;	}
	if(iTailPos >= 0)	{	m_iTailPos = iTailPos;	}
}
///////////////////////////////////////
/**
 * 	���ꥢ���`����λ�ä򥪥ե��åȤ��롣����ָ����
 * 
 * 	@param xyDelta		���ե��åȤ���XY��
 *
 */
inline void CAXAreaCursor::OffsetValue( XYPOINT xyDelta )
{
	OffsetValue( xyDelta.dX, xyDelta.dY );
}
///////////////////////////////////////
/**
 * 	���ꥢ���`����λ�ä򥪥ե��åȤ��롣����ָ����
 * 
 * 	@param dDeltaX		���ե��åȤ���X��
 *	@param dDeltaY		���ե��åȤ���Y��
 */
inline void CAXAreaCursor::OffsetValue( double dDeltaX, double dDeltaY )
{
	SetHeadValue( GetHeadValue().dX + dDeltaX, GetHeadValue().dY + dDeltaY );
	SetTailValue( GetTailValue().dX + dDeltaX, GetTailValue().dY + dDeltaY );
}
///////////////////////////////////////
/**
 * 	���ꥢ���`����λ�ä򥪥ե��åȤ��롣���ݥ������ָ����
 * 
 * 	@param iDeltaPos	���ե��åȤ���ݥ������
 */
inline void CAXAreaCursor::OffsetPos( int iDeltaPos )
{
	SetPos( GetHeadPos() + iDeltaPos, GetTailPos() + iDeltaPos );
}
///////////////////////////////////////
/**
 * 	���ԩ`���ڥ�`��
 * 
 * 	@param src	���ԩ`ԪCAXAreaCursor
 */
inline CAXAreaCursor & CAXAreaCursor::operator =( const CAXAreaCursor &src )
{
	CAXGDICursor::Copy(src);
	CAXPatternStyle::Copy(src);
	m_iTailPos = src.m_iTailPos;			///< ���`����λ�� �ǩ`���ݥ����ָ��
	m_xyTailValue = src.m_xyTailValue;		///< ���`����λ�� ��ָ��

	return (*this);
}
///////////////////////////////////////
/**
 * 	���ԩ`���ڥ�`��
 * 
 * 	@param src	���ԩ`ԪCAXAreaCursor
 */
inline CAXAreaCursor & CAXAreaCursor::Copy( const CAXAreaCursor &src )
{
	operator =(src); 
	return (*this);
}
/////////////////////////////////////////////////////////////////////////////
// CAXPlotData
///< memory type 0:�Ω`�ޥ루MEMNORMAL��/1:��󥰥��꣨MEMRING��
typedef enum E_MEMORY_TYPE{
	MEMNORMAL = 0,	///< �Ω`�ޥ루MEMNORMAL��
	MEMRING,		///< ��󥰥��꣨MEMRING��
};

template<class TYPE, class ARG_TYPE>
class CAXPlotData : public CAXLineStyle, public CAXMarkerStyle//, public CAXItemName 
{
// ���󥹥ȥ饯�����
public:
	/**
	 * 	���B.
	 * 		�ץ�åȥ�������򱣳֤���
	 * 
	 * 	@param iStyle		���N
	 * 	@param color		��ɫ
	 * 	@param iSize		��������
	 */
	CAXPlotData(int iStyle = PS_SOLID, COLORREF color = 0x00FFFFFF, int iSize = 0)
		: CAXLineStyle( iStyle, color, iSize ), CAXMarkerStyle()
	{
		Initialize();
	}
	/**
	 * 	���B.
	 * 		�饤�󥹥������Ԫ�˘��B����
	 * 
	 * 	@param lineStyle	�饤�󥹥�����
	 */
	CAXPlotData( const LINESTYLE &lineStyle)
		: CAXLineStyle( lineStyle ), CAXMarkerStyle()
	{
		Initialize();
	}
	/**
	 * 	���B.
	 * 		�饤�󥹥������Ԫ�˘��B����
	 * 
	 * 	@param axlineStyle	�饤�󥹥�����
	 */
	CAXPlotData( const CAXLineStyle &axlineStyle )
		: CAXLineStyle( axlineStyle ), CAXMarkerStyle()
	{
		Initialize();
	}
	/**
	 * 	���B.
	 * 		�饤�󥹥����롢�ީ`���`���������Ԫ�˘��B����
	 * 
	 * 	@param lineStyle	�饤�󥹥�����
	 * 	@param markStyle	�ީ`���`��������
	 */
	CAXPlotData( const LINESTYLE &lineStyle, const MARKERSTYLE &markStyle )
		: CAXLineStyle( lineStyle ), CAXMarkerStyle( markStyle )
	{
		Initialize();
	}
	/**
	 * 	���B.
	 * 		�饤�󥹥����롢�ީ`���`���������Ԫ�˘��B����
	 * 
	 * 	@param axlineStyle	�饤�󥹥�����
	 * 	@param axmarkStyle	�ީ`���`��������
	 */
	CAXPlotData( const CAXLineStyle &axlineStyle, const CAXMarkerStyle &axmarkStyle )
		: CAXLineStyle( axlineStyle ), CAXMarkerStyle( axmarkStyle )
	{
		Initialize();
	}
	/**
	 * 	���ԩ`���󥹥ȥ饯��
	 * 		Ԫ��CAXPlotData��Ԫ�˘��B����
	 * 
	 * 	@param org	���ԩ`ԪCAXPlotData
	 */
	CAXPlotData( const CAXPlotData &org )	{	operator=( org );	}
// ����ץ���Ʃ`�����
public:
	//�ǥ��󥹥ȥ饯��
	virtual ~CAXPlotData() {	RemoveAllItem();	};
	///////////////////////////////////////
	/**
	 * 	�ץ�åȥǩ`���Υ��ԩ`.
	 * 	@param src	���ԩ`Ԫ�Υץ�åȥ�������
	 * 	@return		�ץ�åȥ�������Υݥ���
	 */
	inline CAXPlotData & operator =( const CAXPlotData &src )
	{
//		CAXItemName::Copy(src);
		m_strItemName = src.m_strItemName;	///< �ǩ`������

		m_lineStyle = src.m_lineStyle;		///< �饤�󥹥�����
		m_markStyle = src.m_markStyle;		///< �ީ`���`��������
		m_iMarkDelta = src.m_iMarkDelta;	///< �ީ`���g��(����ǥå���ָ��)
		m_iMarkEdge = src.m_iMarkEdge;		///< �ީ`��ʼ��K��(����ǥå���ָ��)
		m_bVisible = src.m_bVisible;		///< ��ʾ�ե饰

		m_byReversalX = src.m_byReversalX;	///< X�ǩ`����ܞ
		m_byReversalY = src.m_byReversalY;	///< Y�ǩ`����ܞ
		
		m_nIndex = -1;						///< �ǩ`������ǥå���
		SetSize( src.m_nSize );	//m_nSize;	///< �ǩ`��������

		m_plotData.Copy( src.m_plotData );
		m_nIndex = src.m_nIndex;			///< �ǩ`������ǥå���
		m_nHead = src.m_nHead;				///< �ǩ`�������^

		m_Xscale = src.m_Xscale;			//X�S�����`��
		m_Yscale = src.m_Yscale;			//Y�S�����`��

		m_dataMin = src.m_dataMin;			///< �ǩ`����С��
		m_dataMax = src.m_dataMax;			///< �ǩ`�����
		///< memory type 0:�Ω`�ޥ루MEMNORMAL��/1:��󥰥��꣨MEMRING��
		m_nMemType = src.m_nMemType;
		m_bRedraw = TRUE;

		return *this;
	}
	inline CAXPlotData & Copy( const CAXPlotData &src )
	{
		operator=(src);
		return *this;
	}
	///////////////////////////////////////
	/**
	 * 	�����ƥ�ȫ����.
	 * 
	 *	
	 */
	virtual void RemoveAllItem( void )
	{	
//		CAXItemName::ClearName();
		m_strItemName.Empty();	///< �ǩ`������
		RemoveAllPoint();//�ǩ`��������
	}
//���Љ���
public:
	BOOL			m_bRedraw;		///< ���軭�ե饰
protected:
	BOOL			m_bVisible;		///< ��ʾ�ե饰
	BYTE			m_byReversalX;	///< X�ǩ`����ܞ
	BYTE			m_byReversalY;	///< Y�ǩ`����ܞ
	int				m_iMarkDelta;	///< �ީ`���g��(����ǥå���ָ��)
	int				m_iMarkEdge;	///< �ީ`��ʼ��K��(����ǥå���ָ��)
	
	int				m_nMemType;		///< memory type 0:�Ω`�ޥ루MEMNORMAL��/1:��󥰥��꣨MEMRING��
	int				m_nSize;		///< �ǩ`��������
	int				m_nIndex;		///< �ǩ`������ǥå���
	int				m_nHead;		///< �ǩ`�������^

	CAXGDIScaleData	m_Xscale;		///< Xaxis
	CAXGDIScaleData	m_Yscale;		///< Yaxis

	ARG_TYPE			m_dataMin;		///< �ǩ`����С��
	ARG_TYPE			m_dataMax;		///< �ǩ`�����
	CString				m_strItemName;	///< �ǩ`������

	/// �ץ�åȥǩ`��
	CArray<TYPE,ARG_TYPE>	m_plotData;
private:
	
protected:
	inline virtual void CompareMinMax( ARG_TYPE checkData ) {}
	virtual void Initialize( void )
	{
		RemoveAllItem();		///< �����ƥ�ȫ����
		m_bRedraw = TRUE;		///< ���軭�ե饰
		m_bVisible = TRUE;		///< ��ʾ�ե饰
		m_byReversalX = 0;		///< X�ǩ`����ܞ
		m_byReversalY = 0;		///< Y�ǩ`����ܞ
		m_iMarkDelta = 1;		///< �ީ`���g��(����ǥå���ָ��)
		m_iMarkEdge = 0;		///< �ީ`��ʼ��K��(����ǥå���ָ��)
		m_nSize = -1;			///< �ǩ`��������
		m_nMemType = MEMNORMAL;	///< memory type 0:�Ω`�ޥ루MEMNORMAL��/1:��󥰥��꣨MEMRING��
	}
public:
	inline virtual void ClearMinMax( void ) {}
	///////////////////////////////////////
	/**
	 * 	�ץ�åȥǩ`���α�ʾ/�Ǳ�ʾ���O������.
	 * 
	 * 	@param bVisible	�ץ�åȥǩ`�����ʾ���뤫�Υե饰(TRUE:��ʾ FALSE:�Ǳ�ʾ)
	 * 	@return			��ǰ�α�ʾ/�Ǳ�ʾ״�B�򷵤���
	 */
	inline BOOL Visible( BOOL bVisible )
	{
		m_bRedraw = TRUE;
		BOOL bOld = m_bVisible;
		m_bVisible = bVisible;
		return bOld;
	}
	///////////////////////////////////////
	/**
	 * 	�ץ�åȥǩ`���α�ʾ/�Ǳ�ʾ��ȡ�ä���.
	 * 
	 * 	@return			��ʾ/�Ǳ�ʾ״�B�򷵤���
	 */
	inline BOOL IsVisible(void)	{	return m_bVisible;	}

	/// ��ʾ�����Ф��O��
	inline virtual void SetName(LPCTSTR lpszName)	{	m_strItemName = lpszName;		}
	///< ��ʾ������
	inline virtual CString GetName(void)			{	return m_strItemName;	}
	
//�ީ`���`��ʾ�g�����O������.
	///////////////////////////////////////
	/**
	 * 	�ީ`���`��ʾ�g�����O������.
	 * 
	 * 	@param iMarkDelta	�ީ`����ʾ�g��
	 * 	@param iMarkEdge	�ǩ`���ζˤ���Υީ`���Ǳ�ʾ����
	 * 
	 */
	void SetMarkerDelta( int iMarkDelta, int iMarkEdge )
	{
		if( iMarkDelta <  0 ) {	return;	}
		m_iMarkDelta = iMarkDelta;
		m_iMarkEdge = iMarkEdge;
		m_bRedraw = TRUE;
	}
	inline int	GetMarkerDelta( void )	{	return m_iMarkDelta;	}
	inline int	GetMarkerEdge( void )	{	return m_iMarkEdge;		}

	//��ܞ��ʾ
	///////////////////////////////////////
	/**
	 * 	�ץ�åȥǩ`���η�ܞ��ʾ���O������.
	 * 
	 * 	@param iRvsX	�ץ�åȥǩ`��X�S��ܞ��ʾ���뤫�Υե饰(1:��ܞ / 0:�Ƿ�ܞ / ��������:������ʤ�)
	 * 	@param iRvsY	�ץ�åȥǩ`��Y�S��ܞ��ʾ���뤫�Υե饰(1:��ܞ / 0:�Ƿ�ܞ / ��������:������ʤ�)
	 * 	@return
	 */
	inline virtual void EnableReversal( int iRvsX, int iRvsY )
	{
		if(iRvsX == 0)			{	m_byReversalX = 0;	}
		else	if(iRvsX == 1)	{	m_byReversalX = 1;	}
		if(iRvsY == 0)			{	m_byReversalY = 0;	}
		else	if(iRvsY == 1)	{	m_byReversalY = 1;	}
	}
	inline BOOL IsReversalX(void)		{	return (m_byReversalX == 1 ? TRUE : FALSE);	}
	inline BOOL IsReversalY(void)		{	return (m_byReversalY == 1 ? TRUE : FALSE);	}
	
	//�ǩ`�����꥿����
	inline	int GetMemType( void )	{	return m_nMemType;	}
	inline	BOOL SetMemType( int type = MEMRING )
	{	
		if(m_nSize > 0)	{	return FALSE;	}
		m_nMemType = type;
		return TRUE;
	}

//�ǩ`����������
	///////////////////////////////////////
	/**
	 * 	�ǩ`�����������O������.
	 * 		�O�������ǩ`�����������I���_�����롣
	 *	
	 *	@param		nSize	�O������ǩ`��������
	 * 	@return		�I���_�������ǩ`��������
	 */
	virtual int SetSize( int nSize )
	{
		m_nIndex = -1;		///< �ǩ`������ǥå���
		m_nHead = -1;		///< �ǩ`�������^

		if( nSize > 0)	{
			if(m_nSize != nSize)	{
				m_plotData.RemoveAll();
				m_plotData.SetSize( nSize );
				m_nSize = m_plotData.GetSize();		///< �ǩ`��������
				if(m_nSize != nSize)	{	ASSERT(FALSE);	}
			}
		}	else	{
			m_plotData.RemoveAll();
			m_nSize = m_plotData.GetSize();
		}
		
		return m_nSize;
	}
	inline virtual int GetSize( void ) const	{	return m_plotData.GetSize();	}
	///////////////////////////////////////
	/**
	 * 	�ǩ`��ȡ��.
	 * 	@param nIndex	���^����Υ���ǥå�������
	 * 	@return			�ǩ`���Υݥ���
	 */
	inline virtual TYPE & operator [] ( int nIndex )
	{
		if( nIndex < 0 || nIndex >= GetSize())	{	ASSERT(FALSE);	}
		
		int index = nIndex;
		///< memory type 0:�Ω`�ޥ루MEMNORMAL��/1:��󥰥��꣨MEMRING��
		if(m_nMemType == MEMRING)	{
			if(m_nHead < 0)	{	return m_plotData[ index ];	}
			index = m_nHead + nIndex;
			if( index >= GetSize())	{	index -= (GetSize());	}
		}	
		
		return m_plotData[ index ];
	}
	///////////////////////////////////////
	/**
	 * 	�ǩ`����ȡ��.
	 * 		�O������Ƥ���ǩ`���ݥ���Ȥ�����ȡ�ä��롣
	 * 
	 * 	@return		�O������Ƥ���ǩ`���ݥ������
	 */
	inline virtual int GetNum( void )
	{
		///< memory type 0:�Ω`�ޥ루MEMNORMAL��/1:��󥰥��꣨MEMRING��
		if(m_nMemType == MEMRING)	{
			if( m_nHead < 0)	{	return	(m_nIndex + 1);	}
		}	else	{
			if( m_nSize > 0 )	{	return	(m_nIndex + 1);	}
		}
		return m_plotData.GetUpperBound()+1;
	}
	///////////////////////////////////////
	/**
	 * 	�ǩ`���Υ��ꥢ.
	 * 
	 */
	virtual void ClearAllPoint( void )
	{
		m_nIndex = -1;			///< �ǩ`������ǥå���
		m_nHead = -1;			///< �ǩ`������
		///< memory type 0:�Ω`�ޥ루MEMNORMAL��/1:��󥰥��꣨MEMRING��
		if(m_nMemType != MEMRING)	{
			if( m_nSize <= 0)	{	///< �ǩ`��������
				m_plotData.RemoveAll();
			}
		}
		m_bRedraw = TRUE;
	}
	///////////////////////////////////////
	/**
	 * 	�ǩ`�����I������.
	 * 
	 */
	virtual void RemoveAllPoint( void )
	{
		m_nIndex = -1;		///< �ǩ`������ǥå���
		m_nHead = -1;		///< �ǩ`�������^
		m_nSize = -1;		///< �ǩ`��������
		m_plotData.RemoveAll();
		m_bRedraw = TRUE;
	}
	///////////////////////////////////////
	/**
	 * 	�ǩ`����׷��.
	 * 
	 * 	@param newData	׷�Ӥ���ǩ`��
	 *	@return �ǩ`����׷�Ӥ�������ǥå����򷵤���
	 */
	inline virtual int AddPoint( ARG_TYPE newData )
	{
		CompareMinMax(newData);
		///< memory type 0:�Ω`�ޥ루MEMNORMAL��/1:��󥰥��꣨MEMRING��
		m_bRedraw = TRUE;
		if(m_nMemType == MEMRING)	{
			if(++m_nIndex >= GetSize())	{
				m_nIndex = 0;
				m_nHead = 0;
			}
			m_plotData.SetAt( m_nIndex, newData );
			//m_bRedraw = TRUE;
			if(m_nHead < 0)				{	return m_nIndex;	}
			if(++m_nHead >= GetSize())	{	m_nHead = 0;		}
		}	else	{
			if( ++m_nIndex >= m_nSize)	{
				return m_plotData.Add( newData );
			}	else	{		
				m_plotData.SetAt( m_nIndex, newData );
			}
		}
		return m_nIndex;
	}
	///////////////////////////////////////
	/**
	 * 	�ǩ`���ꥹ�Ȥβ���.
	 * 		�ǩ`���ꥹ�ȥ��饹�β��դ򷵤���
	 * 
	 * 	@return		�ǩ`���ꥹ�Ȥ��{���Ƥ���CArray���饹�Υݥ���
	 */
	inline virtual CArray<TYPE,ARG_TYPE> *operator *()
	{
		return &m_plotData;
	}

	// �ǩ`�����
	inline const TYPE &GetMin(void)	{	return m_dataMin;	}	///< �ǩ`����С��
	inline const TYPE &GetMax(void)	{	return m_dataMax;	}	///< �ǩ`�����

	// �ǩ`����ʾ����
	inline CAXGDIScaleData & GetXscale(void)	{	return m_Xscale;	}	//Xaxis
	inline CAXGDIScaleData & GetYscale(void)	{	return m_Yscale;	}	//Yaxis
	///////////////////////////////////////
	/**
	 * 	�ǩ`���α�ʾ�����O��.
	 * 		�ǩ`���α�ʾ������O�����롣\n
	 * 
	 * 	@param dMin	�ǩ`����ʾ����(MIN)
	 * 	@param dMax	�ǩ`����ʾ����(MAX)
	 */
	inline void  SetXScale( double dMin, double dMax)
	{
		m_Xscale.SetScale( dMin, dMax);
		m_bRedraw = TRUE;
	}
	inline void  SetYScale( double dMin, double dMax)
	{
		m_Yscale.SetScale( dMin, dMax);
		m_bRedraw = TRUE;
	}
	// ������`��
	inline void  Scroll( double dScrollX, double dScrollY )
	{
		if( dScrollX != 0.0 ) m_Xscale.SetOffset( dScrollX );
		if( dScrollY != 0.0 ) m_Yscale.SetOffset( dScrollY );
		m_bRedraw = TRUE;
	}
// ���`�Щ`�饤��
public:
	///< ���軭
	virtual void Redraw(BOOL bErase = TRUE)	{ m_bRedraw = TRUE; }
//�ǥХå���
	inline virtual void DebugDataSet( void ) {};


//061120 tachibana modified start>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	void UpdateStyle(const LINESTYLE &lineStyle, const MARKERSTYLE &markStyle);
//061120 tachibana modified end<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
};
/////////////////////////////////////////////////////////////////////////////
// inline finction
/////////////////////////////////////////////////////////////////////////////
// CAXPlotData

/////////////////////////////////////////////////////////////////////////////
// CXYPlotData
class CXYPlotData : public CAXPlotData<XYPOINT,XYPOINT>
{
public:
	/**
	 * 	���B.
	 * 		�ץ�åȥǩ`���򱣳֤���
	 * 
	 * 	@param iStyle		���N
	 * 	@param color		��ɫ
	 * 	@param iSize		��������
	 */
	CXYPlotData( int iStyle = PS_SOLID, COLORREF color = 0x00FFFFFF, int iSize = 0 )
		: CAXPlotData<XYPOINT,XYPOINT>( iStyle, color, iSize )
	{
		ClearMinMax();
	}
	/**
	 * 	���B.
	 * 		�饤�󥹥������Ԫ�˘��B����
	 * 
	 * 	@param lineStyle	�饤�󥹥�����
	 */
	CXYPlotData( const LINESTYLE &lineStyle )
		: CAXPlotData<XYPOINT,XYPOINT>( lineStyle )
	{
		ClearMinMax();
	}
	/**
	 * 	���B.
	 * 		�饤�󥹥������Ԫ�˘��B����
	 * 
	 * 	@param lineStyle	�饤�󥹥�����
	 */
	CXYPlotData( const CAXLineStyle &axlineStyle )
		: CAXPlotData<XYPOINT,XYPOINT>( axlineStyle )
	{
		ClearMinMax();
	}	
	/**
	 * 	���B.
	 * 		�饤�󥹥����롢�ީ`���`���������Ԫ�˘��B����
	 * 
	 * 	@param lineStyle	�饤�󥹥�����
	 * 	@param markStyle	�ީ`���`��������
	 */
	CXYPlotData( const LINESTYLE &lineStyle, const MARKERSTYLE &markStyle )
		: CAXPlotData<XYPOINT,XYPOINT>( lineStyle, markStyle )
	{
		ClearMinMax();
	}
	/**
	 * 	���B.
	 * 		�饤�󥹥����롢�ީ`���`���������Ԫ�˘��B����
	 * 
	 * 	@param lineStyle	�饤�󥹥�����
	 * 	@param markStyle	�ީ`���`��������
	 */
	CXYPlotData( const CAXLineStyle &axlineStyle, const CAXMarkerStyle &axmarkStyle )
		: CAXPlotData<XYPOINT,XYPOINT>( axlineStyle, axmarkStyle )
	{
		ClearMinMax();
	}
	/**
	 * 	���B.
	 * 		Ԫ��CXYPlotData��Ԫ�˘��B����
	 * 
	 * 	@param org	���ԩ`ԪCXYPlotData
	 */
	CXYPlotData( const CXYPlotData &org )
	{
		operator=( org );
	}

	/**
	 * 	�Ɨ�.
	 * 		�ץ�åȥǩ`�����Ɨ����롣
	 */
	virtual ~CXYPlotData()
	{
		RemoveAllItem();
	}
private:

//���`�Щ`�饤��
protected:
	void Initialize( void )
	{
		CAXPlotData<XYPOINT,XYPOINT>::Initialize();
	}
public:
	inline virtual void CompareMinMax( XYPOINT checkData )
	{
		// ���/��С������
		m_dataMin.dX = __min(m_dataMin.dX,checkData.dX);		///< �ǩ`����С��
		m_dataMin.dY = __min(m_dataMin.dY,checkData.dY);		///< �ǩ`����С��
		m_dataMax.dX = __max(m_dataMax.dX,checkData.dX);		///< �ǩ`�����
		m_dataMax.dY = __max(m_dataMax.dY,checkData.dY);		///< �ǩ`�����
	}
public:
	virtual void ClearMinMax( void )
	{
		m_dataMin.dX = DBL_MAX;		///< �ǩ`����С��
		m_dataMin.dY = DBL_MAX;		///< �ǩ`����С��
		m_dataMax.dX = -DBL_MAX;	///< �ǩ`�����
		m_dataMax.dY = -DBL_MAX;	///< �ǩ`�����
	}
	///////////////////////////////////////
	/**
	 * 	�ǩ`��׷��.
	 * 		�ǩ`���Υݥ���Ȥ�׷�Ӥ��롣
	 * 
	 * 	@param dX	�ǩ`���ݥ����X
	 * 	@param dY	�ǩ`���ݥ����Y
	 * 	@return		׷�Ӥ���Ҫ�ؤΥ���ǥå���
	 */
	inline int AddPoint( double dX, double dY )
	{
		XYPOINT pnt;
		pnt.dX = dX;
		pnt.dY = dY;
		return (CAXPlotData<XYPOINT,XYPOINT>::AddPoint(pnt));
	}
	virtual void ClearAllPoint( void )
	{
		ClearMinMax();
		CAXPlotData<XYPOINT,XYPOINT>::ClearAllPoint();
	}
	virtual void RemoveAllPoint( void )
	{
		ClearMinMax();
		CAXPlotData<XYPOINT,XYPOINT>::RemoveAllPoint();
	}
	virtual void RemoveAllItem( void )
	{
		ClearMinMax();
		CAXPlotData<XYPOINT,XYPOINT>::RemoveAllItem();
	}
	inline double dataX( int index )
	{
		return (CAXPlotData<XYPOINT,XYPOINT>::operator[](index)).dX;
	}
	inline double dataY( int index )
	{
		return (CAXPlotData<XYPOINT,XYPOINT>::operator[](index)).dY;
	}
};
/////////////////////////////////////////////////////////////////////////////
// CDBLPlotData
///< ScrollMode 0:INCREMENT/1:DECREMENT
typedef enum E_SCROLL_MODE{
	INC_SCROLL = 0,	///< 0:INCREMENT
	DEC_SCROLL,		///< 1:DECREMENT
};
class CDBLPlotData : public CAXPlotData<double,double>
{
public:
	/**
	 * 	���B.
	 * 		�ץ�åȥǩ`���򱣳֤���
	 * 
	 * 	@param iStyle		���N
	 * 	@param color		��ɫ
	 * 	@param iSize		��������
	 */
	CDBLPlotData( int iStyle = PS_SOLID, COLORREF color = 0x00FFFFFF, int iSize = 0 )
		: CAXPlotData<double,double>( iStyle, color, iSize )
	{
		LocalInitialize();
	}
	/**
	 * 	���B.
	 * 		�饤�󥹥������Ԫ�˘��B����
	 * 
	 * 	@param lineStyle	�饤�󥹥�����
	 */
	CDBLPlotData( const LINESTYLE &lineStyle )
		: CAXPlotData<double,double>( lineStyle )
	{
		LocalInitialize();
	}
	/**
	 * 	���B.
	 * 		�饤�󥹥������Ԫ�˘��B����
	 * 
	 * 	@param lineStyle	�饤�󥹥�����
	 */
	CDBLPlotData( const CAXLineStyle &axlineStyle )
		: CAXPlotData<double,double>( axlineStyle )
	{
		LocalInitialize();
	}
	/**
	 * 	���B.
	 * 		�饤�󥹥����롢�ީ`���`���������Ԫ�˘��B����
	 * 
	 * 	@param lineStyle	�饤�󥹥�����
	 * 	@param markStyle	�ީ`���`��������
	 */
	CDBLPlotData( const LINESTYLE &lineStyle, const MARKERSTYLE &markStyle )
		: CAXPlotData<double,double>( lineStyle, markStyle )
	{
		LocalInitialize();
	}
	/**
	 * 	���B.
	 * 		�饤�󥹥����롢�ީ`���`���������Ԫ�˘��B����
	 * 
	 * 	@param lineStyle	�饤�󥹥�����
	 * 	@param markStyle	�ީ`���`��������
	 */
	CDBLPlotData( const CAXLineStyle &axlineStyle, const CAXMarkerStyle &axmarkStyle )
		: CAXPlotData<double,double>( axlineStyle, axmarkStyle )
	{
		LocalInitialize();
	}
	/**
	 * 	���B.
	 * 		Ԫ��CDBLPlotData��Ԫ�˘��B����
	 * 
	 * 	@param org	���ԩ`ԪCDBLPlotData
	 */
	CDBLPlotData( const CDBLPlotData &org )
	{
		operator=( org );
	}
	/**
	 * 	�Ɨ�.
	 * 		�����ͥ�ǩ`�����Ɨ����롣
	 */
	virtual ~CDBLPlotData()
	{
		RemoveAllItem();
	}
private:
//���Љ���
protected:
	double			m_dXdelta;		///< �ǩ`��1�㤢�����X�S�Ή��ւ�
	double			m_dXoffset;		///< X�S�Υ��ե��å�
	int				m_scrollMode;	///< ScrollMode 0:INC_SCROLL/1:DEC_SCROLL
//���`�Щ`�饤��
protected:
	inline virtual void CompareMinMax( double checkData )
	{	// ���/��С������
		m_dataMin = __min(m_dataMin,checkData);		///< �ǩ`����С��
		m_dataMax = __max(m_dataMax,checkData);		///< �ǩ`�����
	}
	virtual void LocalInitialize( void )
	{
		m_dXdelta = 1.0;		///< �ǩ`��1�㤢�����X�S�Ή��ւ�
		m_dXoffset = 0.0;		///< X�S�Υ��ե��å�
		m_scrollMode = INC_SCROLL;	///< ScrollMode 0:INC_SCROLL/1:DEC_SCROLL
		ClearMinMax();
	}
	virtual void Initialize( void )
	{
		ClearMinMax();
		CAXPlotData<double,double>::Initialize();
	}
public:
	// ���ڻ�
	inline CDBLPlotData &operator =( const CDBLPlotData &src )
	{
		CAXPlotData<double,double>::Copy(src);
		m_dXdelta = src.m_dXdelta;		///< �ǩ`��1�㤢�����X�S�Ή��ւ�
		m_dXoffset = src.m_dXoffset;	///< X�S�Υ��ե��å�
		m_scrollMode = src.m_scrollMode;	///< ScrollMode 0:INC_SCROLL/1:DEC_SCROLL
		return *this;
	}
	inline CDBLPlotData &Copy( const CDBLPlotData &src )
	{
		operator=(src);
		return *this;
	}
	virtual void ClearMinMax( void )
	{
		m_dataMin = DBL_MAX;		///< �ǩ`����С��
		m_dataMax = -DBL_MAX;	///< �ǩ`�����
	}
	virtual void ClearAllPoint( void )
	{
		ClearMinMax();
		CAXPlotData<double,double>::ClearAllPoint();
	}
	virtual void RemoveAllPoint( void )
	{
		ClearMinMax();
		CAXPlotData<double,double>::RemoveAllPoint();
	}
	inline void SetXdelta( double Delta );
	inline void SetXoffset( double Offset );
	inline int	SetScrollMode( int scrollMode = DEC_SCROLL );
	inline double GetXdelta( void )		{	return m_dXdelta;	}		///< �ǩ`��1�㤢�����X�S�Ή��ւ�
	inline double GetXoffset( void )	{	return 	m_dXoffset;	}		///< X�S�Υ��ե��å�
	inline int GetScrollMode( void )	{	return m_scrollMode;	}	///< ScrollMode 0:INC_SCROLL/1:DEC_SCROLL
	inline double dataX( int index )
	{
		if(m_scrollMode == DEC_SCROLL)	{///< ScrollMode 0:INC_SCROLL/1:DEC_SCROLL)
			return (GetXoffset() + GetXdelta() * (index - GetNum()));
		}
		return (GetXoffset() + GetXdelta() * index);
	}
	inline double dataY( int index )
	{
		return (operator[](index));
	//	return (m_plotData[index]);
	}
};
///////////////////////////////////////
/**
 * 	�ǩ`��1�㤢�����X�S�Ή��ւ����O������.
 * 
 * 	@param Delta	///< �O������ǩ`��1�㤢�����X�S�Ή��ւ�
 */
inline void CDBLPlotData::SetXdelta( double Delta )
{
	if(Delta > 1.0e-38)	{
		m_dXdelta = Delta;
		Redraw(TRUE);
	}	
}
///////////////////////////////////////
/**
 * 	X�S�Υ��ե��åȤ��O������.
 * 
 * 	@param Offset	///< X�S�Υ��ե��å�
 */
inline void CDBLPlotData::SetXoffset( double Offset )
{
	m_dXoffset = Offset;
	Redraw(TRUE);
}
///////////////////////////////////////
/**
 * 	X�S��Scroll��`�ɤ��O������.
 * 
 * 	@param scrollMode	0:INC_SCROLL/1:DEC_SCROLL
 *	@return ���ǰ��Scroll��`��
 */
inline int CDBLPlotData::SetScrollMode( int scrollMode /*= DEC_SCROLL*/ )
{
	int iMode = GetScrollMode();
	if(scrollMode == INC_SCROLL || scrollMode == DEC_SCROLL )	{
		m_scrollMode = scrollMode;
	}
	return iMode;
}
/////////////////////////////////////////////////////////////////////////////
//CAXGDIPlotCtrl
class CAXGDIPlotCtrl : public CAXGDICtrl
{
// ���󥹥ȥ饯�����
public:
	CAXGDIPlotCtrl( COLORREF bkColor = IBLACK );
	CAXGDIPlotCtrl( CAXGDIPlotCtrl &org );

// ���ȥ�ӥ�`��
public:
	// ����åɥ饤�󥯥饹��ȡ�ä���(X).
	inline CAXLineStyle & GetGridXStyle(void)	{	return	m_gridX;	}		///< ����åɥ饤�󥹥�����
	// ����åɥ饤�󥯥饹��ȡ�ä���(Y).
	inline CAXLineStyle & GetGridYStyle(void)	{	return 	m_gridY;	}		///< ����åɥ饤�󥹥�����
	//Ŀʢ���ʾ 
	inline CAXMeasureStyle & GetAxisX()	{	return m_axisX;	}	///< X�SĿʢ�ꥹ���`��
	inline CAXMeasureStyle & GetAxisY()	{	return m_axisY;	}	///< Y�SĿʢ�ꥹ���`��
	///< �S�����O����(0:Min/1:Max/2:Center/3:�ǩ`����ָ��)
	inline BYTE GetStyleXCross(void) const	{	return m_byStyleXCross;	}
	inline BYTE GetStyleYCross(void) const	{	return m_byStyleYCross;	}
	///< �ץ�åȥǩ`���Υ����`����ʾ�Є���X�S��
	inline BOOL IsShowPlotScaleX( void ) const 
	{
		return ( m_byShowPlotScaleX ? TRUE : FALSE );
	}
	///< �ץ�åȥǩ`���Υ����`����ʾ�Є���Y�S��
	inline BOOL IsShowPlotScaleY( void ) const 
	{
		return ( m_byShowPlotScaleY ? TRUE : FALSE );
	}
	///< �ץ�åȥǩ`�����Ƥα�ʾ�Є�
	inline BOOL IsShowPlotName( void ) const 
	{
		return ( (m_byPlotNameShowMode & AX_GDISHOW) ? TRUE : FALSE );
	}
	///< �ץ�åȥǩ`�����Ƥα�ʾ��`��ȡ��
	inline int GetShowModePlotName( void ) const {		return ( AX_GDIALLMODE & m_byPlotNameShowMode );	}
	//
	void SetAxisXCross( BYTE byCrossStyle, double dCross = 0.0 )
	{
		m_byStyleXCross = byCrossStyle;	///< �S�����Є�(0:Min/1:Max/2:Center/3:�ǩ`����ָ��)
		m_dAxisXCross = dCross;		///< �S����ݥ����(�ǩ`����ָ��)
	}
	void SetAxisYCross( BYTE byCrossStyle, double dCross = 0.0 )
	{
		m_byStyleYCross = byCrossStyle;	///< �S�����Є�(0:Min/1:Max/2:Center/3:�ǩ`����ָ��)
		m_dAxisYCross = dCross;		///< �S����ݥ����(�ǩ`����ָ��)
	}
	inline void ShowPlotScaleX( BOOL bShow )///< �ץ�åȥǩ`���Υ����`����ʾ�Є���X�S��
	{
		m_byShowPlotScaleX = ( bShow ? 1 : 0 );
	}
	inline void ShowPlotScaleY( BOOL bShow )///< �ץ�åȥǩ`���Υ����`����ʾ�Є���Y�S��
	{
		m_byShowPlotScaleY = ( bShow ? 1 : 0 );
	}
	///< �ץ�åȥǩ`�����Ƥα�ʾ�Є�
	inline void ShowPlotName( BOOL bShow )
	{
		if(bShow)	{	m_byPlotNameShowMode |= AX_GDISHOW;	}
		else		{	m_byPlotNameShowMode &= (0xff ^ AX_GDISHOW);	}
	}
	inline int SetShowModePlotName( int iMode = AX_GDIXMODE )
	{
		int iOldMode = GetShowModePlotName();
		m_byPlotNameShowMode &= (0xff ^ AX_GDIALLMODE);
		m_byPlotNameShowMode |= iMode;
		return iOldMode;
	}
	//���`����Υե���ȥ��������O�����롣
	inline void	SetCursorFontSize( int iFontSize )	{	m_iCursorFontSize = iFontSize;	}
	inline int	GetCursorFontSize( void )			{	return m_iCursorFontSize;		}
	//���`����Υե���ȥ��������O�����롣
	inline void	SetAreaCsrFontSize( int iFontSize )	{	m_iAreaCsrFontSize = iFontSize;	}
	inline int	GetAreaCsrFontSize( void )			{	return m_iAreaCsrFontSize;		}

/*	double SetMeasureRatio(double dRatio)	{
		if( dRatio > 0.0 && dRatio <= 100.0)	{
			m_dMeasureRatio = dRatio;	///< �SĿʢ���ȫ��ˌ��������
			Redraw(TRUE);
		}
		return m_dMeasureRatio;	///< �SĿʢ���ȫ��ˌ��������
	}*/
	// ����åɾ�
	inline void	ShowGridX( BOOL bShow, const LINESTYLE &lineStyle );
	inline void	ShowGridY( BOOL bShow, const LINESTYLE &lineStyle );
	inline void	ShowGridX( BOOL bShow, int iStyle = -1, COLORREF color = IGRAY, int iSize = -1 );
	inline void	ShowGridY( BOOL bShow, int iStyle = -1, COLORREF color = IGRAY, int iSize = -1 );


// ���ڥ�`�����
public:
	inline CAXGDIPlotCtrl & Copy( const CAXGDIPlotCtrl &src )	{	operator=(src);	return *this;	}
	inline CAXGDIPlotCtrl & operator=( const CAXGDIPlotCtrl &src );

	inline virtual void RemoveAllItem(void);
	inline virtual void ClearAllItem(void);
// ���`�Щ`�饤��
public:
	// ClassWizard �ρ����v���Υ��`�Щ`�饤�ɤ����ɤ��ޤ���
	//{{AFX_VIRTUAL(CAXGDIPlotCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

protected:

// ����ץ���Ʃ`�����
public:
	virtual ~CAXGDIPlotCtrl();

	// ���ɤ��줿��å��`�� �ޥå��v��
protected:
	//{{AFX_MSG(CAXGDIPlotCtrl)
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk( UINT nFlags, CPoint point );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void Initialize( void );	//���ڻ�
	// �軭
	virtual void DrawGrid( CDC *pDC, int iType, const CRect &rect,const LINESTYLE &gridLine );
	virtual void DrawMeasure( CDC *pDC, const CRect &rect, CAXMeasureStyle &measure );
	virtual void DrawPlotName( CDC *pDC, const CRect &rect, int iXYMode, int nIndex, int nShowLine, COLORREF color, LPCTSTR lpszString );
	virtual void DrawPlotScale( CDC *pDC, const CRect &rect, int iXYMode, int nIndex, int nShowLine, COLORREF color, double dblMin, double dblMax );

	// ���`������軭
	virtual void DrawPlotCursor( CDC *pDC, const CRect &rect, CAXPlotCursor &plotCursor );
	virtual void DrawPlotCursor( CDC *pDC, const CRect &rect, CXYPlotData &data, CAXPlotCursor &plotCursor );
	virtual void DrawPlotCursor( CDC *pDC, const CRect &rect, CDBLPlotData &data, CAXPlotCursor &plotCursor );
	// ���ꥢ���`������軭
	virtual void DrawAreaCursor( CDC *pDC, const CRect &rect, CAXAreaCursor &areaCursor, BOOL bDrawName = FALSE );
	virtual void DrawAreaCursor( CDC *pDC, const CRect &rect, CXYPlotData &data, CAXAreaCursor &areaCursor, BOOL bDrawName = FALSE );
	virtual void DrawAreaCursor( CDC *pDC, const CRect &rect, CDBLPlotData &data, CAXAreaCursor &areaCursor, BOOL bDrawName = FALSE );

	// �ޥ�����ܥ���Ѻ�¤Εr��Activate
	virtual int MouseLBdownActivate( const CRect &rect, CPoint point, AXGCACTINFO *lpActiveInfo ){ return AXGCTRLACT_NONE;};

protected:
	CDC				m_bmpDC;			///< �ӥåȥޥå�DC
	CBitmap			m_bitmap;			///< ����ӥåȥޥå�
//	RECT			m_rectMargin;		///< �軭�ީ`����
	BOOL			m_bRedraw;			///< ���軭�ե饰

	//����å� 
	BOOL			m_bShowGridX;	///< ����åɱ�ʾ�Є���X�S��
	BOOL			m_bShowGridY;	///< ����åɱ�ʾ�Є���Y�S��
	CAXLineStyle	m_gridX;		///< ����åɥ饤�󥹥�����
	CAXLineStyle	m_gridY;		///< ����åɥ饤�󥹥�����

	//Ŀʢ���ʾ 
	CAXMeasureStyle	m_axisX;			///< X�SĿʢ�ꥹ���`��
	CAXMeasureStyle	m_axisY;			///< Y�SĿʢ�ꥹ���`��
	BYTE			m_byStyleXCross;	///< �S�����Є�(0:Min/1:Max/2:Center/3:�ǩ`����ָ��)
	BYTE			m_byStyleYCross;	///< �S�����Є�(0:Min/1:Max/2:Center/3:�ǩ`����ָ��)
	double			m_dAxisXCross;		///< �S����ݥ����(�ǩ`����ָ��)
	double			m_dAxisYCross;		///< �S����ݥ����(�ǩ`����ָ��)

	BYTE			m_byShowPlotScaleX;		///< �ץ�åȥǩ`���Υ����`��α�ʾ�Є���X�S��
	BYTE			m_byShowPlotScaleY;		///< �ץ�åȥǩ`���Υ����`��α�ʾ�Є���Y�S��
	BYTE			m_byPlotNameShowMode;	///< �ץ�åȥǩ`�����Ƥα�ʾ��`��

	int				m_iCursorFontSize;	// ���`����ե���ȥ�����
	int				m_iAreaCsrFontSize;	// ���ꥢ���`����ե���ȥ�����

//	double			m_dMeasureRatio;	///< �SĿʢ���ȫ��ˌ��������

	CArray<CAXPlotCursor,CAXPlotCursor> m_plotCursor;	//���`����
	CArray<CAXAreaCursor,CAXAreaCursor> m_areaCursor;	//���ꥢ���`����

public:
	//���`�����׷�Ӥ��ޤ���
	int AddPlotCursor( int iMode = CURSORCROSS, int iStyle = PS_SOLID, COLORREF color = 0x00FFFFFF, int iSize = 0 )
	{
		CAXPlotCursor plotCursor( iMode, iStyle, color, iSize );
		return m_plotCursor.Add( plotCursor );
	}
	//���`�����׷�Ӥ��ޤ���
	int AddPlotCursor( int iMode, const LINESTYLE &lineStyle )
	{
		CAXPlotCursor plotCursor( iMode, lineStyle );
		return m_plotCursor.Add( plotCursor );
	}
	
	inline int GetPlotCursorNum(void)	{	return m_plotCursor.GetSize();	}

	inline CAXPlotCursor & GetPlotCursor(int index)	{	return m_plotCursor[index];	}
	///////////////////////////////////////
	/**
	 * 	���`����ȫ����
	 * 		���`����򥯥ꥢ���롣
	 */
	inline void ClearPlotCursor( void )	{	m_plotCursor.RemoveAll();	}
/////////////
	int AddAreaCursor( int iMode = CURSORCROSS, int iBStyle = BS_SOLID, int iHStyle = HS_HORIZONTAL, COLORREF color = ILIGHTPINK )
	{
		CAXAreaCursor areaCursor( iMode, iBStyle, iHStyle, color );
		return m_areaCursor.Add( areaCursor );
	}
	
	int AddAreaCursor( int iMode, const PATTERNSTYLE &patternStyle )
	{
		CAXAreaCursor areaCursor( iMode, patternStyle );
		return m_areaCursor.Add( areaCursor );
	}

	inline int GetAreaCursorNum(void)	{	return m_areaCursor.GetSize();	}

	inline CAXAreaCursor & GetAreaCursor(int index)	{	return m_areaCursor[index];	}
	///////////////////////////////////////
	/**
	 * 	���ꥢ���`����ȫ����.
	 * 		���ꥢ���`����򥯥ꥢ���롣
	 */
	inline void ClearAreaCursor( void )		{	m_areaCursor.RemoveAll();	}

	//************************ �����C�� ************************//
protected:
	BOOL			m_bZooming;		///< �����Хե饰
	int				m_iMouseZoom;	///< �ޥ�������C��ON/OFF�ե饰
	CRect			m_guideRect;	///< �����I��
	
	/// ����sС�����`��
	CArray<CAXGDIScaleData,CAXGDIScaleData>	m_zoomScale;

	// ����Ւ���
	virtual void Zoom( CRect rectZoom ){};
public:
	///< �ޥ�������C��
	virtual int EnableMouseZoom ( int iZoom = XY_ZOOM );
	inline virtual int GetMouseZoom ( void );
	inline virtual BOOL IsMouseZoom ( void );
};
/////////////////////////////////////////////////////////////////////////////
// CAXGDIPlotCtrl
///////////////////////////////////////
/**
 * 	����åɾ��α�ʾ/�Ǳ�ʾ(X).
 * 		X�S�Υ���åɾ��ξ��N��ָ������ʾ/�Ǳ�ʾ���롣
 * 
 * 	@param bShow	TRUE:��ʾ FALSE:�Ǳ�ʾ
 * 	@param iStyle	����åɾ��N
 * 	@param color	����åɾ�ɫ
 * 	@param iSize	����åɾ�������
 */
inline void CAXGDIPlotCtrl::ShowGridX( BOOL bShow, int iStyle /*= -1*/, COLORREF color /*= -1*/, int iSize /*= -1*/ )
{
	m_bShowGridX = bShow;
	if(iStyle >= PS_SOLID)	{	m_gridX.SetLineStyle( iStyle, color, iSize );	}
	Redraw(TRUE);
}
///////////////////////////////////////
/**
 * 	����åɾ��α�ʾ/�Ǳ�ʾ(Y).
 * 		Y�S�Υ���åɾ��ξ��N��ָ������ʾ/�Ǳ�ʾ���롣
 * 
 * 	@param bShow	TRUE:��ʾ FALSE:�Ǳ�ʾ
 * 	@param iStyle	����åɾ��N
 * 	@param color	����åɾ�ɫ
 * 	@param iSize	����åɾ�������
 */
inline void CAXGDIPlotCtrl::ShowGridY( BOOL bShow, int iStyle /*= -1*/, COLORREF color /*= -1*/, int iSize /*= -1*/ )
{
	m_bShowGridY = bShow;
	if(iStyle >= PS_SOLID)	{	m_gridY.SetLineStyle( iStyle, color, iSize );	}
	Redraw(TRUE);
}
///////////////////////////////////////
/**
 * 	����åɾ��α�ʾ/�Ǳ�ʾ(X).
 * 		X�S�Υ���åɾ��ξ��N��ָ������ʾ/�Ǳ�ʾ���롣
 * 
 * 	@param bShow	TRUE:��ʾ FALSE:�Ǳ�ʾ
 * 	@param lineStyle	�饤�󥹥�����
 */
inline void	CAXGDIPlotCtrl::ShowGridX( BOOL bShow, const LINESTYLE &lineStyle )
{
	m_bShowGridX = bShow;
	m_gridX.SetLineStyle( lineStyle );
	Redraw(TRUE);
}
///////////////////////////////////////
/**
 * 	����åɾ��α�ʾ/�Ǳ�ʾ(Y).
 * 		Y�S�Υ���åɾ��ξ��N��ָ������ʾ/�Ǳ�ʾ���롣
 * 
 * 	@param bShow	TRUE:��ʾ FALSE:�Ǳ�ʾ
 * 	@param lineStyle	�饤�󥹥�����
 */
inline void	CAXGDIPlotCtrl::ShowGridY( BOOL bShow, const LINESTYLE &lineStyle )
{
	m_bShowGridY = bShow;
	m_gridY.SetLineStyle( lineStyle );
	Redraw(TRUE);
}
///////////////////////////////////////
/**
 * 	CAXGDIPlotCtrl�Υ��ԩ`.
 * 	@param src	���ԩ`Ԫ��CAXGDIPlotCtrl
 * 	@return		CAXGDIPlotCtrl�Υݥ���
 */
inline CAXGDIPlotCtrl & CAXGDIPlotCtrl::operator=( const CAXGDIPlotCtrl &src )
{
	m_bkColor = src.m_bkColor;

	m_axisX = src.m_axisX;
	m_axisY = src.m_axisY;

	m_bShowGridX = src.m_bShowGridX;	///< ����åɱ�ʾ�Є���X�S��
	m_bShowGridY = src.m_bShowGridY;	///< ����åɱ�ʾ�Є���Y�S��
	m_gridX = src.m_gridX;		///< ����åɥ饤�󥹥�����
	m_gridY = src.m_gridY;		///< ����åɥ饤�󥹥�����

//	m_dMeasureRatio = src.m_dMeasureRatio;		///< �SĿʢ���ȫ��ˌ��������
	m_byStyleXCross = src.m_byStyleXCross;		///< �S�����Є�(0:Min/1:Max/2:Center/3:�ǩ`����ָ��)
	m_byStyleYCross = src.m_byStyleYCross;		///< �S�����Є�(0:Min/1:Max/2:Center/3:�ǩ`����ָ��)
	m_dAxisXCross = src.m_dAxisXCross;		///< �S����ݥ����(�ǩ`����ָ��)
	m_dAxisYCross = src.m_dAxisYCross;		///< �S����ݥ����(�ǩ`����ָ��)
	ShowPlotScaleX(src.IsShowPlotScaleX());///< �ץ�åȥǩ`���Υ����`����ʾ�Є���X�S��
	ShowPlotScaleY(src.IsShowPlotScaleY());///< �ץ�åȥǩ`���Υ����`����ʾ�Є���X�S��
	ShowPlotName(src.IsShowPlotName());	///< �ץ�åȥǩ`�����Ƥα�ʾ�Є�
	SetShowModePlotName(src.GetShowModePlotName());

	if(0)	{
		double dRatio = (double)(GetInitSize().cy) / src.GetInitSize().cy;		///< ����դ�Rect
		if(src.m_iCursorFontSize > 0)	{
		m_iCursorFontSize = FtoL(src.m_iCursorFontSize * dRatio);		// ���`����ե���ȥ�����
		if(m_iCursorFontSize < 6)	{	m_iCursorFontSize = 6;	}
		}
		if(src.m_iAreaCsrFontSize > 0)	{
			m_iAreaCsrFontSize = FtoL(src.m_iAreaCsrFontSize * dRatio);	// ���ꥢ���`����ե���ȥ�����
			if(m_iAreaCsrFontSize < 6)	{	m_iAreaCsrFontSize = 6;	}
		}
	}	else	{
		m_iCursorFontSize = src.m_iCursorFontSize;		// ���`����ե���ȥ�����
		m_iAreaCsrFontSize = src.m_iAreaCsrFontSize;	// ���ꥢ���`����ե���ȥ�����
	}

	m_plotCursor.RemoveAll();
	if( src.m_plotCursor.GetSize() > 0 )	{
		m_plotCursor.Copy( src.m_plotCursor );
	}

	m_areaCursor.RemoveAll();
	if( src.m_areaCursor.GetSize() > 0 )	{
		m_areaCursor.Copy( src.m_areaCursor );
	}

	CAXGDICtrl::Copy(src);
	Initialize();

	return *this;
}
///////////////////////////////////////
/**
 * 	���٤Ƥ����Υ��ꥢ.
 *
 */
inline void CAXGDIPlotCtrl::ClearAllItem(void)
{
	ClearActiveInfo(&m_activeInfo);	///< Active״�B�����Υ��ꥢ
	m_zoomScale.RemoveAll();
	m_plotCursor.RemoveAll();
	m_areaCursor.RemoveAll();
	m_iMouseZoom = ZOOM_OFF;
}
///////////////////////////////////////
/**
 * 	���٤Ƥ����Υ��ꥢ.
 *
 */
inline void CAXGDIPlotCtrl::RemoveAllItem(void)
{
	ClearAllItem();
}
///////////////////////////////////////
/**
 * 	�ޥ����ǤΥ���Ւ���C�ܤ�ON/OFF����.
 * 
 * 	@return			����Ւ���C���S��״�B�򷵤���
 */
inline int CAXGDIPlotCtrl::GetMouseZoom ( void )
{
	return m_iMouseZoom;
}
///////////////////////////////////////
/**
 * 	�ޥ����ǤΥ���Ւ���C��ON/OFF��ȡ�ä���.
 * 
 * 	@return		����C�ܤ��Є��ե饰
 */
inline BOOL CAXGDIPlotCtrl::IsMouseZoom ( void )
{
	return	( m_iMouseZoom == ZOOM_OFF  ? FALSE : TRUE) ; 
}
/////////////////////////////////////////////////////////////////////////////
// inline finction
/////////////////////////////////////////////////////////////////////////////
// CDBLPlotData
///////////////////////////////////////


#endif // !defined(_AXGDIPLOT_H_INCLUDED_)