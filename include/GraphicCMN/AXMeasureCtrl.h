// AXMasureCtrl.h : �إå��` �ե�����
//
/********************************************************
// ���饹�Υ��󥿩`�ե�����
// CAXGDIScaleData		:�����`��ǩ`�����֥��饹
// CAXMeasureStyle		:Ŀʢ���軭���饹
// CAXMeasureSpin		:Ŀʢ���å��ԥ�ܥ��󥯥饹
// CAXMeasureCtrl		:Ŀʢ���軭Wnd���饹
//											by YOTSUTSU
//	* History	:	date:2005,24,Mar.	��Ҏ����
ver.1.00	
********************************************************/
//////////////////////////////////////////////////////////////////////
#ifndef __AXMASURECTRL_H_INCLUDED__
#define __AXMASURECTRL_H_INCLUDED__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AXGdiCore.h"

//MeasureStyle

#define AMS_NONE			0x0000	///< �o	
#define AMS_XMODE			0x0001	///< X�Smode
#define AMS_YMODE			0x0002	///< Y�Smode
#define AMS_ZMODE			0x0004	///< Z�Smode
#define AMS_SHOW			0x0010L	///< ��ʾ/�Ǳ�ʾ�ե饰
#define AMS_SH_DETAIL		0x0020L	///< Ԕ��Ŀʢ��α�ʾ/�Ǳ�ʾ
#define AMS_SH_MIN			0x0040L	///< MINĿʢ��α�ʾ/�Ǳ�ʾ
#define AMS_SH_MAX			0x0080L	///< MAXĿʢ��α�ʾ/�Ǳ�ʾ
#define AMS_SH_DELTA		0x0100L	///< Ŀʢ��΂��α�ʾ/�Ǳ�ʾ
#define AMS_SH_VALMIN		0x0200L	///< MINĿʢ��΂��α�ʾ/�Ǳ�ʾ
#define AMS_SH_VALMAX		0x0400L	///< MAXĿʢ��΂��α�ʾ/�Ǳ�ʾ
#define AMS_SH_LOGZERO		0x0800L	///< LOG��ʾ ����α�ʾ/�Ǳ�ʾ
#define AMS_INSIDE			0x0000L	///< Scale inside			Ŀʢ������O��(AMS_INSIDE:�ڂ�/AMS_OUTSIDE:���/AMS_SIDEBOTH:����)
#define AMS_OUTSIDE			0x1000L	///< Scale outside			Ŀʢ������O��(AMS_INSIDE:�ڂ�/AMS_OUTSIDE:���/AMS_SIDEBOTH:����)
#define AMS_SIDEBOTH		0x2000L	///< Scale inside&outside	Ŀʢ������O��(AMS_INSIDE:�ڂ�/AMS_OUTSIDE:���/AMS_SIDEBOTH:����)
#define AMS_EN_ORG			0x00010000L	///< Ŀʢ��ԭ����Є�/�o��
#define AMS_ADJUST			0x00020000L	///< ����ʾ �{�����Є�/�o��
#define AMS_EN_DIVDELTA		0x00040000L	///< Ŀʢ��ηָ�ָ�����Є�/�o��
#define AMS_ALL				0x000FFFFFL	///< MeasureStyle All bit
//Scale Change type
#define AMS_RANGE_UP		VK_PRIOR	// VK_PAGE_UP:					��Delta�֥�󥸒���
#define AMS_RANGE_DOWN		VK_NEXT		// VK_PAGE_DOWN:				��Delta�֥�󥸿sС��
#define AMS_OFFSET_UP		VK_UP		// Process the UP ARROW key.��	��+Delta���ե��åȣ�
#define AMS_OFFSET_DOWN		VK_DOWN		// Process the DOWN ARROW key.	��-Delta���ե��åȣ�


/////////////////////////////////////////////////////////////////////////////
// ������
#pragma pack( push, 1 )

///< �����`��ǩ`��������
typedef struct tagGdiScaleInfo{	//16byte
	double		dRange;			///< �ǩ`������
	double		dOrg;			///< �ǩ`��ԭ��
} GDISCALEINFO;

///< MeasureStyle(Ŀʢ�ꥹ������)���
typedef struct tagMeasureStyle{		//64byte
	DWORD		dwSize;			///< Specifies the size, in bytes, of this structure.
	DWORD		dwMsStyle;		///< MeasureStyle
	double		dDelta;			///< Ŀʢ���g��(�ǩ`����/�ָ� ָ��)
	double		dDetailDelta;	///< Ԕ��Ŀʢ���g��(�ǩ`����/�ָ� ָ��)
	double		dOrgDelta;		///< Ŀʢ���g����ԭ��(�ǩ`����ָ��)
	short		sDetailRatio;	///< Ԕ��Ŀʢ���L������ָ��[%]
	short		sFontSize;		///< Ŀʢ��΂���ʾ�Υե���ȥ�����
	long		lAngle;			///< Ŀʢ������ֽǶ�
	long		lReserve1;		///< ���
	COLORREF	scaleColor;		///< �����`���ʾɫ
	COLORREF	measureColor;	///< Ŀʢ��΂�����ɫ
//	TCHAR		szFormat[12];	///< Ŀʢ�ꂎ�α�ʾ��ʽ
	BYTE		byteReserve[12];///< ���
} MEASURESTYLE;

#pragma pack( pop )
/////////////////////////////////////////////////////////////////////////////
// �v��

/////////////////////////////////////////////////////////////////////////////
// CAXGDIScaleData	�軭�å����`�륯�饹
//������ϵԭ���left, top���Ȥ��� ����<=>�ǩ`�����Ф��롣��Log�����`��⌝�꣩
class CAXGDIScaleData
{
public:
	/**
	 * 	���B.
	 * 		�����`��ǩ`���򱣳֤���
	 * 
	 * 	@param dblMin	��С��
	 * 	@param dblMax	���
	 * 	@param bLog		������ʾ
	 */
	CAXGDIScaleData( double dblMin = 0.0, double dblMax = 100.0, BOOL bLog = FALSE )
	{
		memset(&m_scaleInfo,0x00,sizeof(GDISCALEINFO));
		
		m_scaleInfo.dRange = 100.0;				///< �ǩ`������
		m_scaleInfo.dOrg = 0.0;					///< �ǩ`��ԭ��
		SetScale( dblMin, dblMax );				///< �����`���O��
		SetLogMode( bLog, FALSE);				///< ������ʾ�Є�
	}
	CAXGDIScaleData(const GDISCALEINFO & scaleInfo ,BOOL bLog = FALSE )
	{	
		CAXGDIScaleData( scaleInfo.dOrg,  scaleInfo.dRange - scaleInfo.dOrg, bLog ) ;
	}
	//���ԩ`���󥹥ȥ饯��
	CAXGDIScaleData( const CAXGDIScaleData &org)
	{
		operator =( org );
		//m_bLog = FALSE;
		//m_scaleInfo = scaleSrc.m_scaleInfo;
		//SetLogMode( scaleSrc.m_bLog, FALSE);				///< ������ʾ�Є�
	}
// ����ץ���Ʃ`�����
public:
	virtual ~CAXGDIScaleData(){};
	
//	inline CAXGDIScaleData const GetAXGdiScale(void) const { 	return (*this);	}

// ���ȥ�ӥ�`��
public:
	//�����`���O��
	virtual const GDISCALEINFO & SetScale( double dblMin, double dblMax );
	virtual const GDISCALEINFO & SetLogScale(double dblMin , double dblMax, BOOL bScaleAuto );
	virtual const GDISCALEINFO & SetLogMode(BOOL bLog = TRUE,BOOL bScaleAuto = TRUE);
	inline void SetOrg( double dOrg )		{	m_scaleInfo.dOrg = dOrg;	}
	inline void SetRange( double dRange )	{	m_scaleInfo.dRange = dRange;	}
	//�����`�����ȡ��
	inline const GDISCALEINFO & GetScaleInfo( void )	{	return m_scaleInfo;	}
	inline double GetMin( void )	{	return m_scaleInfo.dOrg;	}
	inline double GetMax( void )	{	return (m_scaleInfo.dRange + m_scaleInfo.dOrg);	}
	inline double GetOrg( void )	{	return m_scaleInfo.dOrg;	}
	inline double GetRange( void )	{	return m_scaleInfo.dRange;	}
	//���������`��
	virtual inline BOOL	IsLogMode(void)		{	return ( m_bLog);		}

protected:
	GDISCALEINFO		m_scaleInfo;	///< �����`��ǩ`��
	BOOL				m_bLog;			///< ������ʾ�Є�
// ���ڥ�`�����
public:
	//����ϵ�v�B
	//Static
	//�軭�å����`��ȡ��
	static double GetDrawOrg( const CAXGDIScaleData &scale );
	static double GetDrawRange( const CAXGDIScaleData &scale );
	static double GetDrawMax( const CAXGDIScaleData &scale );
	//�ǩ`���������ˤ����롣
	static int Data2PointX( double dXdata, const CAXGDIScaleData &scale ,int width );
	static int Data2PointY( double dYdata, const CAXGDIScaleData &scale, int height );
	//���ˤ���ǩ`�����롣
	static double Point2DataX( int iXdata, const CAXGDIScaleData &scale ,int width );
	static double Point2DataY( int iYdata, const CAXGDIScaleData &scale, int height );

	//Non static
	//�軭�å����`��ȡ��
	inline double GetDrawOrg(void)		{	return GetDrawOrg(*this);	}
	inline double GetDrawRange(void)	{	return GetDrawRange(*this);	}
	inline double GetDrawMax(void)		{	return GetDrawMax(*this);	}
	//�ǩ`���������ˤ����롣
	inline int Data2PointX( double dXdata, int width )	{	return Data2PointX( dXdata, (*this), width);	}
	inline int Data2PointY( double dYdata, int height )	{	return Data2PointY( dYdata, (*this), height );	}
	//���ˤ���ǩ`�����롣
	inline double Point2DataX( int iXdata, int width )	{	return Point2DataX( iXdata, (*this), width );	}
	inline double Point2DataY( int iYdata, int height )	{	return Point2DataY( iYdata, (*this), height );	}

	///////////////////////////////////////
	/**
	 * 	�����`�����Υ��ԩ`.
	 *
	 * 	@param	scaleSrc	�����`�����
	 *	@return �����`�����
	 */
	inline CAXGDIScaleData & operator =( const CAXGDIScaleData &src )
	{
		m_scaleInfo = src.m_scaleInfo;
		m_bLog = src.m_bLog;
		SetLogMode(src.m_bLog,FALSE);	
		return (*this);
	}
	inline CAXGDIScaleData & Copy( const CAXGDIScaleData &src )
	{
		operator = (src);
		return (*this);
	}
	//�����`��Υ��ե��å�
	inline const GDISCALEINFO &  SetOffset( double dOffset );
	//�����`��Β���
	inline const GDISCALEINFO &  SetZoom( double dDeltaStt, double dDeltaEnd );
// ���`�Щ`�饤��
public:

//���Љ���
protected:

};
/////////////////////////////////////////////////////////////////////////////
// CAXScaleStyle
class CAXScaleStyle  : public CAXGDIScaleData
{
// ���󥹥ȥ饯�����
public:
	CAXScaleStyle( double dblMin = 0.0, double dblMax = 100.0, BOOL bLog = FALSE )//;
		: CAXGDIScaleData( dblMin, dblMax , bLog )
	{

	}
	//���ԩ`���󥹥ȥ饯��
//	CAXScaleStyle( const CAXScaleStyle &org );  

// ����ץ���Ʃ`�����
public:
	virtual ~CAXScaleStyle();
	// �����`�륹������Υ��ԩ`
//	inline CAXScaleStyle & operator =( const CAXScaleStyle &src );
// ���ȥ�ӥ�`��
public:
	CString			m_strTitle;		//����
	CString			m_strFormat;	//Scale�ե��`�ޥå�
// ���ڥ�`�����
public:
};
/////////////////////////////////////////////////////////////////////////////
// CAXMeasureStyle
class CAXMeasureStyle  : public CAXGDIScaleData
{
// ���󥹥ȥ饯�����
public:
	CAXMeasureStyle(int iMode = MEASUREX, BOOL bAdjust = TRUE);
	//���ԩ`���󥹥ȥ饯��
	CAXMeasureStyle( const CAXMeasureStyle &org );  

// ����ץ���Ʃ`�����
public:
	virtual ~CAXMeasureStyle();
	// �����`�륹������Υ��ԩ`
	inline CAXMeasureStyle & operator =( const CAXMeasureStyle &src );
private:
	//
static void GetDetailRect(const CRect &rect, int iMode, int iType, long lRatio, LPRECT lpCalcRect );

// ���ȥ�ӥ�`��
public:
//�����O��
	///< �����`���`���O��
	inline void SetScaleMode( int iMode = MEASUREX ) ;
	///< Ŀʢ������O��(AMS_INSIDE:�ڂ�/AMS_OUTSIDE:���/AMS_SIDEBOTH:����)
	inline int SetScaleType( int iType = AMS_INSIDE);
	///< Ŀʢ��α�ʾ/�Ǳ�ʾ
	inline BOOL ShowScale( BOOL bShow = TRUE, BOOL bDetailShow = TRUE);
	///< ��С��/��󂎤α�ʾ/�Ǳ�ʾ
	inline void ShowScaleMinMax( BOOL bShowMin, BOOL bShowMax );	
	///< Ŀʢ��΂��α�ʾ/�Ǳ�ʾ
	inline void ShowMeasureDelta( BOOL bShow );
	///< ��С��/��󂎤΂��α�ʾ/�Ǳ�ʾ
	inline void ShowMeasureMinMax( BOOL bShowMin, BOOL bShowMax );
	///< Ŀʢ��ԭ����Є�/�o��
	inline BOOL SetDeltaOrg( BOOL bEnable = TRUE, double dOrg = 0.0 );
	///< Ŀʢ��ηָ�ָ�����Є�/�o��
	inline void EnableDivDelta( BOOL bEnableDiv );
	///< LOG��ʾ ����α�ʾ/�Ǳ�ʾ
	inline void ShowLogZero(BOOL bShow = TRUE);
	///< ����ʾ �{�����Є�/�o��
	inline void SetMeasureAdjust(BOOL bAdjust = TRUE);
	///< Ԕ��Ŀʢ���L������ָ��[%]
	inline void	SetScaleDetailRaio( short sRatio );
	///< Ŀʢ���S�Υե���ȥ�����
	///< Ŀʢ��/Ŀʢ�ꂎ�α�ʾ�ե��`�ޥå�
	inline void	Format( LPCTSTR format, short sFontSize = -1 );
	///< Ŀʢ��/Ŀʢ���S��ɫ
	inline COLORREF SetScaleColor( COLORREF color );
	///< Ŀʢ��/Ŀʢ�ꂎ��ɫ
	inline COLORREF SetMeasureColor( COLORREF color);
	///< Ŀʢ�����ֽǶ�
	inline void SetMeasureAngle( long lAngle );
	// Ŀʢ�����΅gλ
	//inline void	SetUnit( LPCSTR strUnit, LPCSTR format = NULL);
//����ȡ��
	///< MeasureStyle
	inline const MEASURESTYLE & GetStyleInfo(void)		{	return m_measureStyle;	}
	///< MeasureStyle style
	inline const DWORD	GetMsStyle(void)	{	return m_measureStyle.dwMsStyle;	}
	///< �����`���`��
	inline int GetScaleMode(void) const		{	return ((m_measureStyle.dwMsStyle & AMS_YMODE) ? MEASUREY : MEASUREX);	}
	///< Ŀʢ�����(0:�ڂ�/1:���/2:����)
	inline int GetScaleType(void) const		{	return (0x3000 & m_measureStyle.dwMsStyle);	}
	///< Ŀʢ��ԭ����Є�/�o��
	inline BOOL IsDeltaOrgEnable(void) const{	return ((m_measureStyle.dwMsStyle & AMS_EN_ORG) ? TRUE : FALSE);	}
	///< Ŀʢ��α�ʾ/�Ǳ�ʾ
	inline BOOL IsShowScale(void) const		{	return ((m_measureStyle.dwMsStyle & AMS_SHOW) ? TRUE : FALSE);	}
	///< Ԕ��Ŀʢ��α�ʾ/�Ǳ�ʾ
	inline BOOL IsShowDetailScale()	{	return ((m_measureStyle.dwMsStyle & AMS_SH_DETAIL) ? TRUE : FALSE);	}
	///< ��С��/��󂎤α�ʾ/�Ǳ�ʾ
	inline BOOL IsShowScaleMin()	{	return ((m_measureStyle.dwMsStyle & AMS_SH_MIN) ? TRUE : FALSE);	}
	inline BOOL IsShowScaleMax()	{	return ((m_measureStyle.dwMsStyle & AMS_SH_MAX) ? TRUE : FALSE);	}
	///< Ŀʢ��΂��α�ʾ/�Ǳ�ʾ
	inline BOOL IsShowMeasureDelta()	{	return ((m_measureStyle.dwMsStyle & AMS_SH_DELTA) ? TRUE : FALSE);	}
	// ��С��/��󂎤΂��α�ʾ/�Ǳ�ʾ
	inline BOOL IsShowMeasureMin()	{	return ((m_measureStyle.dwMsStyle & AMS_SH_VALMIN) ? TRUE : FALSE);	}
	inline BOOL IsShowMeasureMax()	{	return ((m_measureStyle.dwMsStyle & AMS_SH_VALMAX) ? TRUE : FALSE);	}
	///< LOG��ʾ ����α�ʾ/�Ǳ�ʾ
	inline BOOL IsShowLogZero()	{	return ((m_measureStyle.dwMsStyle & AMS_SH_LOGZERO) ? TRUE : FALSE);	}
	///< ����ʾ �{�����Є�/�o��
	inline BOOL IsMeasureAdjust()	{	return ((m_measureStyle.dwMsStyle & AMS_ADJUST) ? TRUE : FALSE);	}
	///< Ŀʢ���g��(�ǩ`����/�ָ���)
	inline double GetScaleDelta( void )			{	return m_measureStyle.dDelta;				}
	///< Ԕ��Ŀʢ���g��(�ǩ`����/�ָ���)
	inline double GetScaleDetailDelta( void )	{	return m_measureStyle.dDetailDelta;			}
	//Range UP/DOWN�����ǤΉ��p����ȡ��.
	inline double GetScaleRangeDelta( void );
	///< Ŀʢ���g����ԭ��(�ǩ`����ָ��)
	inline double GetDeltaOrg( void )		{	return m_measureStyle.dOrgDelta;	}
	///< Ŀʢ��ηָ�ָ�����Є�/�o��
	inline BOOL IsEnableDivDelta( void )	{	return ((m_measureStyle.dwMsStyle & AMS_EN_DIVDELTA) ? TRUE : FALSE);	}
	///< Ԕ��Ŀʢ���L������ָ��[%]
	inline short   GetScaleDetailRatio( void )	{	return m_measureStyle.sDetailRatio;			}
	///< Ŀʢ���S�Υե���ȥ�����
	inline short GetMeasureFontSize( void );
	///< Ŀʢ��/Ŀʢ���S��ɫ
	inline COLORREF GetScaleColor( void );
	///< Ŀʢ��/Ŀʢ�ꂎ��ɫ
	inline COLORREF GetMeasureColor( void );
	///< Ŀʢ�����ֽǶ�
	inline long GetMeasureAngle( void );
	///< Ŀʢ��/Ŀʢ�ꂎ�α�ʾ�ե��`�ޥå�
	inline LPCTSTR GetFormat( void )	{	return ((LPCTSTR)(m_strFormat));			}
	// Ŀʢ�����΅gλ
//	inline LPCTSTR	GetUnit( void );
	
	inline CAXColorString & GetNameAXString( void )		{	return m_axstrName;		}	///< ���Ƥα�ʾ������
	inline CAXColorString & GetMaxSideAXString( void )	{	return m_axstrMaxSide;	}	///< Max�Ȥα�ʾ������
	inline CAXColorString & GetMinSideAXString( void )	{	return m_axstrMinSide;	}	///< Min�Ȥα�ʾ������
	
	//< ��ʾ������
	inline virtual void SetString( LPCTSTR lpszString )		{	m_axstrName.SetString( lpszString );		}
	inline virtual COLORREF	SetStrColor( COLORREF color )	{	return m_axstrName.SetStrColor( color );	}
	inline virtual CString GetString(void) const			{	return( m_axstrName.GetString() );			}
	inline virtual COLORREF GetStrColor(void) const			{	return( m_axstrName.GetStrColor() );		}

//���Љ���
protected:
	MEASURESTYLE			m_measureStyle;		///< MeasureStyle(Ŀʢ�ꥹ������)���
	CString					m_strFormat;		///< Ŀʢ�ꂎ�α�ʾ��ʽ
	CAXColorString			m_axstrName;		///< ���Ƥα�ʾ������
	CAXColorString			m_axstrMaxSide;		///< MAX�Ȥα�ʾ������
	CAXColorString			m_axstrMinSide;		///< MIN�Ȥα�ʾ������
//	CString					m_strUnit;			///< �gλ�α�ʾ������
//	CString					m_strNameFormat;	///< Ŀʢ�����ƤΕ�ʽ
// ���ڥ�`�����
public:
	// Ŀʢ���O��
	virtual void SetScale( double dMin, double dMax, double dDelta = -1.0, double dDetailDelta = -1.0 );
	// Ŀʢ����S���軭.
	virtual	void DrawScale( CDC *pDC, const CRect &rect );
	// Ŀʢ��΂����軭.
	virtual	void DrawMeasure( CDC *pDC, const CRect &rect );
	// Ŀʢ������Ƥ��軭.
	virtual	void DrawMeasureName( CDC *pDC, const CRect &rect, int nFontSize );
	// Ŀʢ��������Ф��軭.
	virtual	void DrawMeasureMaxString( CDC *pDC, const CRect &rect, BOOL bMonochrome );
	virtual	void DrawMeasureMinString( CDC *pDC, const CRect &rect, BOOL bMonochrome );
	// Ŀʢ����S���軭.	
	static void DrawScale( CDC *pDC, const CRect &rect, int iMode, int iType, double dMin, double dMax, double dOrg, double dDelta, double dDetailDelta, long lDetailRatio );
	static void DrawDivScale( CDC *pDC, const CRect &rect, int iMode, int iType, double dDelta, double dDetailDelta, long lDetailRatio );
	static void DrawLogScale( CDC *pDC, const CRect &rect, int iMode, int iType, double dMin, double dMax, long lDetailRatio );
	// Ŀʢ��΂����軭.
	static void DrawMeasure( CDC *pDC, const CRect &rect, int iMode, double dMin, double dMax, double dOrg, double dDelta, LPCTSTR lpszFormat, BOOL bAdjust );
	static void DrawDivMeasure( CDC *pDC, const CRect &rect, int iMode, double dMin, double dMax, double dDelta, LPCTSTR lpszFormat, BOOL bAdjust );
	static void DrawLogMeasure( CDC *pDC, const CRect &rect, int iMode, double dMin, double dMax, double dDelta, LPCTSTR lpszFormat, BOOL bAdjust );
	// �����`�������軭
	static void TextDraw( CDC *pDC, CRect rect, int iMode, int iX, int iY, LPCTSTR lpszData, int iAdjust);
	// �����`�륹������Υ����`��Υ��ԩ`
	const GDISCALEINFO & CopyScale( const CAXMeasureStyle &src );
	// �����`�륹������Υ��ԩ`
	CAXMeasureStyle & Copy( const CAXMeasureStyle &src );
	// ���軭
	virtual void Redraw(BOOL bErase = TRUE){}
};

/////////////////////////////////////////////////////////////////////////////
// CAXMeasureSpin
class CAXMeasureSpin : public CSpinButtonCtrl
{
public:
	CAXMeasureSpin(){};

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAXMeasureCtrl ������ɥ�
class CAXMeasureCtrl : public CAXGDICtrl, public CAXMeasureStyle
{
// ���󥹥ȥ饯�����
public:
	CAXMeasureCtrl( int iMode = MEASUREX, int iMargin = 0 ,BOOL bAdjust = TRUE);
	// ���ԩ`���󥹥ȥ饯��
	CAXMeasureCtrl( const CAXMeasureCtrl &org );
// ���ȥ�ӥ�`��
public:
	static const int c_iMeasureSise;				// Ŀʢ��νŤ��L��

// ���ڥ�`�����
public:

// ���`�Щ`�饤��
	// ClassWizard �ρ����v���Υ��`�Щ`�饤�ɤ����ɤ��ޤ���
	//{{AFX_VIRTUAL(CAXMeasureCtrl)
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// ����ץ���Ʃ`�����
public:
	virtual ~CAXMeasureCtrl();
	// CAXMeasureCtrl�Υ��ԩ`
	inline CAXMeasureCtrl & operator =( const CAXMeasureCtrl &src );
	inline CAXMeasureCtrl & operator =( const CAXMeasureStyle &src );
	inline CAXMeasureCtrl & operator =( const CAXGDIScaleData &src );

	inline CAXMeasureCtrl & Copy( const CAXMeasureCtrl &src )	{	operator=(src);	return *this;	}
	inline CAXMeasureCtrl & CopyStyle( const CAXMeasureStyle &src )
	{
		CAXMeasureStyle::Copy(src);
		return *this;
	}
	// �軭�I��ȡ��
	//virtual void GetDrawRect(LPRECT lpRect) const;
	// ���ɤ��줿��å��`�� �ޥå��v��
protected:
	//{{AFX_MSG(CAXMeasureCtrl)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	// ֪ͨ��å��`���΄I��
	virtual BOOL OnChangeActive( AXGCNOTIFY *pNotifyMsg );
	virtual BOOL OnChangeStyle( AXGCNOTIFY *pNotifyMsg );
	virtual BOOL OnChangeScale( AXGCNOTIFY *pNotifyMsg );
//	virtual BOOL OnChangeCursol( AXGCNOTIFY *pNotifyMsg );

protected:
	BOOL		m_bErase;			///< WM_ERASEBKGND�軭
	int			m_iMargin;			///< �ީ`����(+:��ȣ�
//	int			m_iMeasureSpan;		///< Ŀʢ���g��
	CSize		m_spinSize;			///< ���ԥ󥵥���
//	CSize		m_measureSize;		///< ���ڱ�ʾ�r�Υ�����

	int			m_iFontSize;		///< �������軭������

	CAXMeasureSpin	m_spinCtrl[2];	///< ���ԥ�ܥ���

public:
	// ��`�ɉ��
	void SetMode(int iMode = MEASUREX, int iMargin = 0 ,BOOL bAdjust = TRUE);
	// ������ɥ����������
	void MoveWindow( int x, int y, int nWidth, int nHeight, BOOL bRepaint = TRUE );
	void MoveWindow( LPCRECT lpRect, BOOL bRepaint = TRUE );
	BOOL SetWindowPos( const CWnd* pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags );

	// ������ɥ�������ȡ��
	void GetClientRect(LPRECT lpRect);
	void GetWindowRect(LPRECT lpRect);

	///< �������軭������ 
	inline void	SetFontSize( int iSize = -1 );
	inline int	GetFontSize( void ) const ;

	// ���ԥ�α�ʾ/�Ǳ�ʾ
	BOOL ShowSpin( BOOL bShow );
	BOOL IsShowSpin(void) const ;

	// Ŀʢ���軭
	virtual void DrawDC( CDC *pDC, CRect rect );
	
	// ����
	inline void Redraw( void );

protected:
	// �軭�ީ`�����ȡ�ä��롣
	inline const int GetWindowMargin( void ) const		{	return m_iMargin;	}	///< �軭�ީ`����

	// ������Ӌ��
	virtual void CalcRect( CRect &rect );
	virtual void SubcalcRect( CRect &rect );

	// ���ԥ���ڻ�
	void CreateSpin();

	// ���ԥ��������
	void RecalcLayoutSpin();
	// Ŀʢ�������軭
//	virtual void DrawMeasureName( CDC *pDC, const CRect &rect, LPCSTR strName );
	// �軭ǰ�I��
	virtual void BeginPaintDC( CDC *pDC, const CRect &rect );
	// �軭��I��
	virtual void EndPaintDC( CDC *pDC, const CRect &rect );
	virtual void DrawActiveFrame( CDC *pDC, const CRect &rect, int size = 7 );
	//virtual void DrawBackground( CDC *pDC, const CRect rect );
};
/////////////////////////////////////////////////////////////////////////////
// inline finction
/////////////////////////////////////////////////////////////////////////////
// CAXGDIScaleData
///////////////////////////////////////
/**
 * 	�����`��Υ��ե��å�.
 *
 * 	@param	dOffset		���ե��åȂ�
 *	@return �����`�����
 */
inline const GDISCALEINFO & CAXGDIScaleData::SetOffset( double dOffset )
{	
	m_scaleInfo.dOrg += dOffset; return (m_scaleInfo);
}
///////////////////////////////////////
/**
 * 	�����`��Β���.
 *
 * 	@param	dDeltaStt		����ʼ��
 * 	@param	dDeltaEnd		����K��
 *	@return �����`�����
 */
inline const GDISCALEINFO & CAXGDIScaleData::SetZoom( double dDeltaStt, double dDeltaEnd )
{
	SetScale( dDeltaStt * m_scaleInfo.dRange + m_scaleInfo.dOrg,
			dDeltaEnd * m_scaleInfo.dRange + m_scaleInfo.dOrg);

	return (m_scaleInfo);
}
/////////////////////////////////////////////////////////////////////////////
// CAXMeasureStyle
///////////////////////////////////////
/**
 * 	CAXMeasureStyle���饹�Υ��ԩ`.
 * 		�뤨��줿�����`�륹������򥳥ԩ`����
 * 
 * 	@param src	���ԩ`Ԫ�����`�륹������
 * 	@return		���Υ��饹�Υݥ���
 */
inline CAXMeasureStyle & CAXMeasureStyle::operator =( const CAXMeasureStyle &src )
{
	CAXGDIScaleData::Copy(src);

//	CopyScale(src);
//	m_measureStyle = src.GetStyleInfo();
	///< Style
//	DWORD dwNewStyle = (AMS_ALL & src.GetMsStyle());
//	m_measureStyle.dwMsStyle = dwNewStyle;

	m_measureStyle = src.m_measureStyle;	///< MeasureStyle(Ŀʢ�ꥹ������)���

	m_axstrName = src.m_axstrName;			///< ���Ƥα�ʾ������
	m_axstrMaxSide = src.m_axstrMaxSide;	///< Up�Ȥα�ʾ������
	m_axstrMinSide = src.m_axstrMinSide;	///< Down�Ȥα�ʾ������
//	m_strUnit = src.m_strUnit;				///< �gλ�α�ʾ������
	m_strFormat = src.m_strFormat;			///< Ŀʢ�ꂎ�α�ʾ��ʽ
//	m_strNameFormat = src.m_strNameFormat;	///< Ŀʢ�����ƤΕ�ʽ

	Redraw();

	return *this;
}
///////////////////////////////////////
/**
 * 	�����`���`���O��.
 *
 * 	@param	iMode		MEASUREX/MEASUREY
 *	@return 
 */
inline void CAXMeasureStyle::SetScaleMode( int iMode /*= MEASUREX*/ )
{
	if(iMode == MEASUREY)	{	m_measureStyle.dwMsStyle |= AMS_YMODE ;				}
	else					{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_YMODE) ;	}
}
///////////////////////////////////////
/**
 * 	Ŀʢ������O��.
 *
 * 	@param	iType		�ڂ�:AMS_INSIDE / ���:AMS_OUTSIDE / ����:AMS_SIDEBOTH
 *						Ŀʢ������O��(0:�ڂ�/1:���/2:����)
 *	@return ���ǰ��Ŀʢ�����
 */
inline int CAXMeasureStyle::SetScaleType( int iType /*= AMS_INSIDE*/)
{
	int iOld = GetScaleType();	
	if(iType >= 0 && iType < 0x3000)	{
		m_measureStyle.dwMsStyle &= (AMS_ALL ^ 0x3000) ;//�����ޤ���
		m_measureStyle.dwMsStyle |= iType;
	}
	return iOld;
}
//////////////////////////////////////
/**
 * 	Ŀʢ����軭ԭ����Є�/�o�����O��. (�ǩ`����ָ��)
 *
 * 	@param	bEnable		TREU:�Є�/FALSE:�o��
 * 	@param	dOrg		Ŀʢ���g����ԭ��(�ǩ`����ָ��)
 *						dOrg�΂�����ʤ��軭���롣
 *	@return	���ǰ��״�B
 */
inline BOOL CAXMeasureStyle::SetDeltaOrg( BOOL bEnable /*= TRUE*/, double dOrg /*= 0.0*/ )
{
	BOOL bOld = IsDeltaOrgEnable();

	if(bEnable)	{	m_measureStyle.dwMsStyle |= AMS_EN_ORG ;				}
	else		{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_EN_ORG) ;	}

	m_measureStyle.dOrgDelta = dOrg;

	return bOld;
}
//////////////////////////////////////
/**
 * 	Ŀʢ��ηָ�ָ�����Є�/�o�����O��. (�ָ�/�ǩ`������ָ��)
 *
 * 	@param	bEnableDiv		TREU:�Є����ָ�ָ����/FALSE:�o�����ǩ`����ָ����
 *						
 *	@return
 */
inline void CAXMeasureStyle::EnableDivDelta( BOOL bEnableDiv )
{
	if(bEnableDiv)	{	m_measureStyle.dwMsStyle |= AMS_EN_DIVDELTA ;				}
	else			{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_EN_DIVDELTA) ;	}
}
//////////////////////////////////////
/**
 * 	Ŀʢ��α�ʾ/�Ǳ�ʾ���O��.
 *
 * 	@param	bShow		��ʾ/�Ǳ�ʾ
 * 	@param	bDetailShow	Ԕ��Ŀʢ��α�ʾ/�Ǳ�ʾ
 *
 *	@return ���ǰ��״�B
 */
inline BOOL CAXMeasureStyle::ShowScale( BOOL bShow /*= TRUE*/,BOOL bDetailShow /*= TRUE*/)
{
	BOOL bOld = IsShowScale();
	if(bShow)					{	m_measureStyle.dwMsStyle |= AMS_SHOW ;				}
	else						{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_SHOW) ;	}

	if(bShow && bDetailShow)	{	m_measureStyle.dwMsStyle |= AMS_SH_DETAIL ;				}
	else						{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_SH_DETAIL) ;	}

	return bOld;
}
//////////////////////////////////////
/**
 * 	��С��/��󂎤�Ŀʢ��α�ʾ/�Ǳ�ʾ���O��.
 *
 * 	@param	bShowMin	��С������ʾ/�Ǳ�ʾ
 *��@param	bShowMax	��󂎡���ʾ/�Ǳ�ʾ
 *	@return 
 */
inline void CAXMeasureStyle::ShowScaleMinMax( BOOL bShowMin, BOOL bShowMax )
{
	if(bShowMin)	{	m_measureStyle.dwMsStyle |= AMS_SH_MIN ;				}
	else			{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_SH_MIN) ;	}
	if(bShowMax)	{	m_measureStyle.dwMsStyle |= AMS_SH_MAX ;				}
	else			{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_SH_MAX) ;	}
}
//////////////////////////////////////
/**
 * 	Ŀʢ��΂��α�ʾ/�Ǳ�ʾ���O��.
 *
 * 	@param	bShow		��ʾ/�Ǳ�ʾ
 *
 *	@return 
 */
inline void CAXMeasureStyle::ShowMeasureDelta( BOOL bShow )
{
	if(bShow)	{	m_measureStyle.dwMsStyle |= AMS_SH_DELTA ;				}
	else		{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_SH_DELTA) ;	}
}
//////////////////////////////////////
/**
 * 	Ŀʢ��΂�����С��/��󂎤α�ʾ/�Ǳ�ʾ���O��.
 *
 * 	@param	bShowMin	��С������ʾ/�Ǳ�ʾ
 *��@param	bShowMax	��󂎡���ʾ/�Ǳ�ʾ
 *	@return 
 */
inline void CAXMeasureStyle::ShowMeasureMinMax( BOOL bShowMin, BOOL bShowMax )
{
	if(bShowMin)	{	m_measureStyle.dwMsStyle |= AMS_SH_VALMIN ;				}
	else			{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_SH_VALMIN) ;	}
	if(bShowMax)	{	m_measureStyle.dwMsStyle |= AMS_SH_VALMAX ;				}
	else			{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_SH_VALMAX) ;	}
}
//////////////////////////////////////
/**
 * 	���������`��r��Ŀʢ��΂��Υ���α�ʾ/�Ǳ�ʾ���O��.
 *
 * 	@param	bShow		��ʾ/�Ǳ�ʾ
 *	@return 
 */
inline void CAXMeasureStyle::ShowLogZero(BOOL bShow /*= TRUE*/)
{
	if(bShow)	{	m_measureStyle.dwMsStyle |= AMS_SH_LOGZERO ;				}
	else		{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_SH_LOGZERO ) ;	}
}
//////////////////////////////////////
/**
 * 	Ŀʢ��΂����軭�I�ˤ��{�����Є�/�o�����O��.
 *
 * 	@param	bAdjust		TRUE:�Є�/FALSE���o��
 *	@return 
 */
inline void CAXMeasureStyle::SetMeasureAdjust(BOOL bAdjust /*= TRUE*/)
{
	if(bAdjust)	{	m_measureStyle.dwMsStyle |= AMS_ADJUST ;				}
	else		{	m_measureStyle.dwMsStyle &= (AMS_ALL ^ AMS_ADJUST ) ;	}
}
//////////////////////////////////////
/**
 * 	Ŀʢ���L���ˌ�����Ԕ��Ŀʢ���L������ָ��[%].
 *
 * 	@param	lRatio		0��100��0��100%
 *	@return 
 */
inline void	CAXMeasureStyle::SetScaleDetailRaio( short sRatio )
{
	if(sRatio >= 0 || sRatio <= 100)		{	m_measureStyle.sDetailRatio = sRatio;		}
}
//////////////////////////////////////
/**
 * 	Range UP/DOWN�����ǤΉ��p����ȡ��.
 *
 *	@return Range UP/DOWN�����ǤΉ��p��
 */
inline double CAXMeasureStyle::GetScaleRangeDelta( void )
{	
	if(IsEnableDivDelta())	{
		if(m_measureStyle.dDelta >= 2.0)	{
			return (GetRange() / m_measureStyle.dDelta);
		}	else	{
			return 0.0;
		}
	}
	return m_measureStyle.dDelta;
}
//////////////////////////////////////
/**
 * 	Ŀʢ���S�Υե���ȥ�������ȡ��.
 *
 *	@return �ե���ȥ�����
 */
inline short CAXMeasureStyle::GetMeasureFontSize( void )
{
	return m_measureStyle.sFontSize;		///< Ŀʢ��΂���ʾ�Υե���ȥ�����
}
///////////////////////////////////////
/**
 * 	Ŀʢ���S��ɫ���O��.
 * 		Ŀʢ���S��ɫ���O������
 * 
 * 	@param color	�O������Ŀʢ���ɫ
 * 	@return			Ԫ��Ŀʢ��ɫ
 */
inline COLORREF CAXMeasureStyle::SetScaleColor( COLORREF color )
{
	COLORREF oldColor = m_measureStyle.scaleColor;
	m_measureStyle.scaleColor = color;
	Redraw();
	return oldColor;
}
///////////////////////////////////////
/**
 * 	Ŀʢ���S��ɫ��ȡ��.
 * 		�F�ڤ�Ŀʢ���S��ɫ��ȡ�ä���
 * 
 * 	@return			�F�ڤ�Ŀʢ��ɫ
 */
inline COLORREF CAXMeasureStyle::GetScaleColor()
{
	return m_measureStyle.scaleColor;
}
///////////////////////////////////////
/**
 * 	Ŀʢ�ꂎ�α�ʾɫ���O��.
 * 		Ŀʢ�ꂎ�α�ʾɫ���O������
 * 
 * 	@param color	�O������Ŀʢ���ɫ
 * 	@return			Ԫ��Ŀʢ��ɫ
 */
inline COLORREF CAXMeasureStyle::SetMeasureColor( COLORREF color )
{
	COLORREF oldColor = m_measureStyle.measureColor;
	m_measureStyle.measureColor = color;
	Redraw();
	return oldColor;
}
///////////////////////////////////////
/**
 * 	Ŀʢ�ꂎ�α�ʾɫ��ȡ��.
 * 		�F�ڤ�Ŀʢ�ꂎ�α�ʾɫ��ȡ�ä���
 * 
 * 	@return			�F�ڤ�Ŀʢ��ɫ
 */
inline COLORREF CAXMeasureStyle::GetMeasureColor()
{
	return m_measureStyle.measureColor;
}
///////////////////////////////////////
/**
 * 	Ŀʢ�����ֽǶȤ��O������.
 * 		Ŀʢ������ֽǶȤ��O������
 * 
 * 	@param lAngle	���ֽǶ�(1/10�ȅgλ)
 */
inline void CAXMeasureStyle::SetMeasureAngle( long lAngle )
{
	m_measureStyle.lAngle = lAngle;
}
///////////////////////////////////////
/**
 * 	Ŀʢ�����ֽǶȤ�ȡ�ä���.
 * 		Ŀʢ������ֽǶȤ�ȡ�ä���
 * 
 * 	@return ���ֽǶ�(1/10�ȅgλ)
 */
inline long CAXMeasureStyle::GetMeasureAngle( void )
{
	return ( m_measureStyle.lAngle );
}
///////////////////////////////////////
/**
 * 	Ŀʢ��ե��`�ޥå� & �ե���ȥ�����.
 * 		Ŀʢ��Υե��`�ޥåȤ�printf��ʽ��ָ������
 * 
 * 	@param format		Ŀʢ��Υե��`�ޥå�
 * 	@param sFontSize	Ŀʢ��Υե���ȥ�����
 */
inline void	CAXMeasureStyle::Format( LPCTSTR format, short sFontSize /*= -1*//*, int iSpan /*= 1*/ )
{
//	m_iMeasureSpan = ( iSpan > 0 )? iSpan: 1;
//	m_strFormat = format;

//	size_t size = sizeof(m_measureStyle.szFormat)/sizeof(TCHAR);
	m_strFormat = format;
//	_tcsncpy( m_measureStyle.szFormat, format, size);
//	m_measureStyle.szFormat[size-1] = _T('\0');

	if(sFontSize > 0)	{	m_measureStyle.sFontSize = sFontSize;	}
}
///////////////////////////////////////
/**
 * 	�S�΅gλ�����O������.
 * 		�gλ�����O������
 * 
 * 	@param color	�O������gλ��
 * 	@param format	�ե��`�ޥåȡ�����%s [%s]
 *
inline void CAXMeasureStyle::SetUnit( LPCSTR strUnit, LPCSTR format )
{
	m_strUnit = strUnit;
	if(format != NULL)	{	m_strNameFormat = format;	}
	Redraw();
}
///////////////////////////////////////
/**
 * 	Ŀʢ�����΅gλ��ȡ�ä���.
 * 		Ŀʢ�����΅gλ��ȡ�ä���
 * 
 * 	@return color	ȡ�ä���Ŀʢ�����΅gλ
 *
inline LPCTSTR CAXMeasureStyle::GetUnit(void)
{
	return (LPCTSTR)m_strUnit;			///< Ŀʢ�����΅gλ
}
/////////////////////////////////////////////////////////////////////////////
// CAXMeasureCtrl
///////////////////////////////////////
/**
 * 	CAXMeasureCtrl�Υ��ԩ`.
 *		�뤨��줿CAXMeasureCtrl�򥳥ԩ`����
 *
 * 	@param src	���ԩ`ԪCAXMeasureCtrl
 * 	@return		���Υ��饹�Υݥ���
 */
inline CAXMeasureCtrl & CAXMeasureCtrl::operator =( const CAXMeasureCtrl &src )
{
	CAXMeasureStyle::Copy(src);
	CAXGDICtrl::Copy(src);

	m_iFontSize = src.m_iFontSize;			///< �������軭������
//	m_strUnit = src.m_strUnit;				///< Ŀʢ�����΅gλ
//	m_strNameFormat = src.m_strNameFormat;	///< Ŀʢ�����ƤΕ�ʽ
	Redraw();
	return *this;
}
///////////////////////////////////////
/**
 * 	CAXMeasureStyle�Υ��ԩ`.
 * 		�뤨��줿�����`�륹������򥳥ԩ`����
 * 
 * 	@param src	���ԩ`Ԫ�����`�륹������
 * 	@return		���Υ��饹�Υݥ���
 */
inline CAXMeasureCtrl & CAXMeasureCtrl::operator =( const CAXMeasureStyle &src )
{
	CAXMeasureStyle::Copy(src);

	Redraw();
	return *this;
}
///////////////////////////////////////
/**
 * 	CAXGDIScaleData�Υ��ԩ`.
 * 		�뤨��줿�����`�����򥳥ԩ`����
 * 
 * 	@param src	���ԩ`Ԫ�����`�����
 * 	@return		���Υ��饹�Υݥ���
 */
inline CAXMeasureCtrl & CAXMeasureCtrl::operator =( const CAXGDIScaleData &src )
{
	CAXGDIScaleData::Copy(src);

	Redraw();
	return *this;
}
///////////////////////////////////////
/**
 * 	�S�������ФΥե���ȥ��������O������.
 * 		�ե���ȥ��������O������
 * 
 * 	@param iSize	�ե���ȥ�����
 * 	@return
 */
inline void CAXMeasureCtrl::SetFontSize( int iSize /*= -1*/ )
{
	m_iFontSize = iSize;
}
///////////////////////////////////////
/**
 * 	�S�������ФΥե���ȥ�������ȡ�ä���.
 * 		�ե���ȥ�������ȡ�ä���.
 * 
 * 	@param
 * 	@return���ե���ȥ�����
 */
inline int CAXMeasureCtrl::GetFontSize(void) const
{
	return m_iFontSize;
}
/**
 *	�������.
 */
inline void CAXMeasureCtrl::Redraw(void)
{
	if( IsWindow( m_hWnd ) ){
		Invalidate();
		UpdateWindow();
	}
}
/////////////////////////////////////////////////////////////////////////////

#endif // __AXMASURECTRL_H_INCLUDED__