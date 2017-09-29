// AXMasureCtrl.cpp : ����ץ���Ʃ`����� �ե�����
//
/********************************************************
// ���饹�Υ���ץ���Ʃ`�����
// CAXGDIScaleData		:�����`��ǩ`�����֥��饹
// CAXMeasureStyle		:Ŀʢ���軭���饹
// CAXMeasureSpin		:Ŀʢ���å��ԥ�ܥ��󥯥饹
// CAXMeasureCtrl		:Ŀʢ���軭Wnd���饹
//											by YOTSUTSU
//	* History	:	date:2005,24,Mar.	��Ҏ����
ver.1.00	
********************************************************/

#include "stdafx.h"
#include <math.h>
#include <float.h>

#include "AXMeasureCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAXGDIScaleData
///////////////////////////////////////
/**
 * 	�����`����󤫤��軭�����`���ԭ�������.
 * 
 * 	@param	scale		�����`�����
 *	@return �軭�����`���ԭ��
 */
double CAXGDIScaleData::GetDrawOrg( const CAXGDIScaleData &scale )
{
	double dOrg = 0.0;
	if(scale.m_bLog)	{	dOrg = log10( scale.m_scaleInfo.dOrg );	}
	else				{	dOrg = scale.m_scaleInfo.dOrg;			}
	return dOrg;
}
///////////////////////////////////////
/**
 * 	�����`����󤫤��軭�����`��Υ�󥸤�����.
 * 
 * 	@param	scale		�����`�����
 *	@return �軭�����`��Υ��
 */
double CAXGDIScaleData::GetDrawRange( const CAXGDIScaleData &scale )
{
	double dRange = 0.0;
	if(scale.m_bLog)	{
		dRange = log10( scale.m_scaleInfo.dRange + scale.m_scaleInfo.dOrg ) - log10( scale.m_scaleInfo.dOrg );
	}	else			{	
		dRange = scale.m_scaleInfo.dRange;
	}
	return dRange;
}
///////////////////////////////////////
/**
 * 	�����`����󤫤��軭�����`��Υ�󥸤�����.
 * 
 * 	@param	scale		�����`�����
 *	@return �軭�����`��Υ��
 */
double CAXGDIScaleData::GetDrawMax( const CAXGDIScaleData &scale )
{
	return (GetDrawRange(scale) + GetDrawOrg(scale));
}
///////////////////////////////////////
/**
 * 	�����`������X�Υǩ`�������軭�������˥ݥ����X������.
 *		����������ϵԭ��� left, top�Ǥ��뤳��
 * 	@param	dXdata		X�΂�
 * 	@param	scale		�����`�����
 * 	@param	width		�軭�η�
 *	@return X���軭���˥ݥ����
 */
int CAXGDIScaleData::Data2PointX( double dXdata, const CAXGDIScaleData &scale ,int width )
{
	double dXOrg = GetDrawOrg(scale);
	double dXRange = GetDrawRange(scale);
	double dXp;
	if(scale.m_bLog)	{
		//dXOrg = log10( scale.m_scaleInfo.dOrg );
		//dXRange = log10(scale.GetMax()) - dXOrg;
		//����`��ֹ
		if( dXdata > 0.0)	{	dXp = log10( dXdata );	}
		else				{	dXp = DBL_MIN_10_EXP;	}
	}	else	{
		//dXOrg = scale.m_scaleInfo.dOrg;
		//dXRange = scale.m_scaleInfo.dRange;
		dXp = dXdata;
	}
	int iX = FtoL( ( dXp - dXOrg ) / dXRange * width );

	return iX;
}
///////////////////////////////////////
/**
 * 	�����`������Y�Υǩ`�������軭�������˥ݥ����Y������.
 *		����������ϵԭ��� left, top�Ǥ��뤳��
 * 	@param	dYdata		Y�΂�
 * 	@param	scale		�����`�����
 * 	@param	height		�軭�θߤ�
 *	@return Y���軭���˥ݥ����
 */
int CAXGDIScaleData::Data2PointY( double dYdata, const CAXGDIScaleData &scale, int height )
{
	double dYOrg;
	double dYRange;
	double dYMax;
	double dYp;
	if(scale.m_bLog)	{
		dYOrg = log10( scale.m_scaleInfo.dOrg );
		dYMax = log10( scale.m_scaleInfo.dRange + scale.m_scaleInfo.dOrg );
		dYRange = dYMax - dYOrg;
		if( dYdata > 0.0)	{	dYp = log10( dYdata );	}
		else				{	dYp = DBL_MIN_10_EXP;	}
	}	else	{
		dYOrg = scale.m_scaleInfo.dOrg;
		dYMax = scale.m_scaleInfo.dRange + scale.m_scaleInfo.dOrg;
		dYRange = scale.m_scaleInfo.dRange;
		dYp = dYdata;
	}
	int iY = FtoL( ( dYMax - dYp ) / dYRange * height );
	return iY;
}
///////////////////////////////////////
/**
 * 	�����`���������˥ݥ����X����X�Υǩ`����������.
 *		����������ϵԭ��� left, top�Ǥ��뤳��
 * 	@param	iXdata		X�΂�	( point.x - rect.left )
 * 	@param	scale		�����`�����
 * 	@param	width		�軭�η�
 *	@return X�Υǩ`����
 */
double CAXGDIScaleData::Point2DataX( int iXdata, const CAXGDIScaleData &scale ,int width )
{
	double dValX;
	if(scale.m_bLog)	{
		if( scale.m_scaleInfo.dOrg < DBL_MIN )	{	return DBL_MIN;	}
		dValX = pow(((scale.m_scaleInfo.dRange + scale.m_scaleInfo.dOrg) / scale.m_scaleInfo.dOrg),((double)iXdata/width)) * scale.m_scaleInfo.dOrg;
	}	else	{
		dValX =  scale.m_scaleInfo.dRange * ( iXdata )  / width + scale.m_scaleInfo.dOrg;
	}
	return (dValX);
}
///////////////////////////////////////
/**
 * 	�����`���������˥ݥ����Y����Y�Υǩ`����������.
 *		����������ϵԭ��� left, top�Ǥ��뤳��
 * 	@param	dXdata		Y�΂�	( point.y - rect.top )
 * 	@param	scale		�����`�����
 * 	@param	height		�軭�θߤ�
 *	@return Y�Υǩ`����
 */
double CAXGDIScaleData::Point2DataY( int iYdata, const CAXGDIScaleData &scale, int height )
{
	double dValY;
	if(scale.m_bLog)	{
		if( scale.m_scaleInfo.dOrg < DBL_MIN )	{	return DBL_MIN;	}
		dValY = (scale.m_scaleInfo.dRange + scale.m_scaleInfo.dOrg) 
			/ pow( ((scale.m_scaleInfo.dRange + scale.m_scaleInfo.dOrg)/scale.m_scaleInfo.dOrg), ((double)iYdata/height));
	}	else	{
		dValY =  scale.m_scaleInfo.dRange * ( -iYdata ) / height + (scale.m_scaleInfo.dRange + scale.m_scaleInfo.dOrg);
	}
	return dValY;
}
///////////////////////////////////////
/**
 * 	�����`�낎���O������.
 *
 * 	@param	dblMin		��С��
 * 	@param	dblMax		���
 *	@return �����`�����
 */
const GDISCALEINFO & CAXGDIScaleData::SetScale( double dblMin, double dblMax )
{
	GDISCALEINFO scale;
	// ��Ҏ�����ƥ����`����O��
	if( dblMin < dblMax ){
		scale.dOrg = dblMin;
		scale.dRange = dblMax - dblMin;
	} else{
		scale.dOrg = dblMax;
		scale.dRange = dblMin - dblMax;
	}
	if(scale.dRange > 1.0e-38)	{
		if( m_bLog )	{	return SetLogScale( dblMin, dblMax, FALSE );	}
		m_scaleInfo = scale;
	}

	return GetScaleInfo();
}
///////////////////////////////////////
/**
 * 	�����`�낎���O������.�����������`�룩
 *
 * 	@param	dblMin		��С��
 * 	@param	dblMax		���
 * 	@param	bScaleAuto	�������`�ȥ����`��	TRUE:�Є�/FALSE:�o��
 *	@return �����`�����
 */
const GDISCALEINFO & CAXGDIScaleData::SetLogScale(double dblMin, double dblMax, BOOL bScaleAuto )
{
	if( dblMin < 0.0 && dblMax < 0.0 && (dblMin == dblMax))	{//Log�ˤϳ����ޤ���
		m_bLog = FALSE;
		return GetScaleInfo();
	}
	double dblDataMax;
	// ��Ҏ�����ƥ����`����O��
	if(dblMin > dblMax)	{
		dblDataMax = dblMin;
		m_scaleInfo.dOrg = dblMax;
	}	else	{
		dblDataMax = dblMax;
		m_scaleInfo.dOrg = dblMin;
	}
	if(bScaleAuto || m_scaleInfo.dOrg <= 0.0)	{
		double dblPwr = log10(dblDataMax);
		if( dblPwr < 0.0 )	{	dblPwr = (double)((int)(dblPwr - 0.5));	}
		else				{	dblPwr = (double)((int)(dblPwr + 0.5));	}
		m_scaleInfo.dOrg = pow( 10.0, dblPwr - 4.0 );
		if(bScaleAuto)		{	dblDataMax = pow( 10.0, dblPwr );		}
	}		
	m_scaleInfo.dRange = dblDataMax - m_scaleInfo.dOrg;
	
	return GetScaleInfo();
}
///////////////////////////////////////
/**
 * 	���������`����Є����o����������.
 *
 * 	@param	bLog		���������`��		TRUE:�Є�/FALSE:�o��
 * 	@param	bScaleAuto	�������`�ȥ����`��	TRUE:�Є�/FALSE:�o��
 *	@return �����`�����
 */
const GDISCALEINFO & CAXGDIScaleData::SetLogMode(BOOL bLog /*= TRUE*/,BOOL bScaleAuto /*= TRUE*/)
{
	if(m_bLog != bLog)	{
		m_bLog = bLog;
		if( bLog )	{	
			return SetLogScale( GetMin(), GetMax(), bScaleAuto );
		}	else	{
			m_scaleInfo.dRange += m_scaleInfo.dOrg;
			m_scaleInfo.dOrg = 0.0;
		}
	}

	return GetScaleInfo();
}
/////////////////////////////////////////////////////////////////////////////
// CAXMeasureStyle

#define	MEASURE_LINEMAX		200		// Ŀʢ���MAX����
#define	MEASURE_DETAILMAX	20		// Ԕ��Ŀʢ���MAX����
//////////////////////////////////////////////////////////////////////
// ���B/����
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////
/**
 * 	���󥹥ȥ饯��.
 * 
 * 	@param iMode	X:MEASUREX/Y:MEASUREY 
 * 	@param bAdjust	�軭�I���Ϥ߳����ʤ��褦�ˡ�FALSE:�{�����ʤ�/TRUE:�{������
 */
CAXMeasureStyle::CAXMeasureStyle(int iMode /*= MEASUREX*/, BOOL bAdjust /*= TRUE*/)
{
#ifdef _DEBUG
if(1)	{
	size_t  sizeByte;
	sizeByte = sizeof(GDISCALEINFO);		TRACE("tagGdiScaleInfo= %d, ", sizeByte);
	sizeByte = sizeof(MEASURESTYLE);		TRACE("tagMeasureInfo= %d, ", sizeByte);
	TRACE("\n");
}
#endif
	memset(&m_measureStyle,0x00,sizeof(MEASURESTYLE));

	///< ���Ƥα�ʾ������
	m_axstrName.SetDTFormat((DT_VCENTER | DT_CENTER));		///< ���Ƥα�ʾ������
	m_axstrName.SetString( _T("") );						///< Ŀʢ������
	m_axstrName.SetStrColor(GetSysColor( COLOR_BTNTEXT ));
	///< Up�Ȥα�ʾ������
	m_axstrMaxSide.SetDTFormat((DT_VCENTER | DT_SINGLELINE | DT_CENTER));
	///< Down�Ȥα�ʾ������
	m_axstrMinSide.SetDTFormat((DT_VCENTER | DT_SINGLELINE | DT_CENTER));	
	
	//m_strFormat;		///< Ŀʢ�ꂎ�α�ʾ��ʽ
	Format( "%.0f" );
	
	//m_strUnit;						///< �gλ�α�ʾ������
//	m_strUnit = _T("");					///< Ŀʢ�����΅gλ
//	m_strNameFormat = _T("%s %s");		///< Ŀʢ�����ƤΕ�ʽ

	m_measureStyle.dwMsStyle = 0;
	//CAXGDIScaleData::SetScale(0.0,100);
	SetScaleMode( iMode );
	

	m_measureStyle.dDelta = 10.0;			///< Ŀʢ���g��(�ǩ`����ָ��)
	m_measureStyle.dDetailDelta = 2.0;		///< Ԕ��Ŀʢ���g��(�ǩ`����ָ��)
	m_measureStyle.dOrgDelta = 0.0;			///< Ŀʢ���g����ԭ��(�ǩ`����ָ��)
	m_measureStyle.sDetailRatio = 75;		///< Ԕ��Ŀʢ���L������ָ��[%]
	m_measureStyle.sFontSize = -1;			///< Ŀʢ��΂���ʾ�Υե���ȥ�����
	m_measureStyle.lAngle = 0;				///< Ŀʢ������ֽǶ�
	m_measureStyle.scaleColor = GetSysColor( COLOR_BTNTEXT );			///< �����`������ɫ
	m_measureStyle.measureColor = GetSysColor( COLOR_BTNTEXT );	///< Ŀʢ��΂�����ɫ
	
	EnableDivDelta(TRUE);
	// ���ֽǶ�
	switch( GetScaleMode() ){
	case MEASUREX: m_measureStyle.lAngle = 0;	break;
	case MEASUREY: m_measureStyle.lAngle = 900;	break;
	}

	// ��ʾ/�Ǳ�ʾ���ڻ�
	ShowScale( TRUE, TRUE );
//	ShowScale(FALSE);
	///< ��С��/���
	// Ŀʢ���S
	ShowScaleMinMax( TRUE, TRUE );	
	// Ŀʢ�ꂎ
	ShowMeasureMinMax( FALSE, FALSE );
	//Ŀʢ��Υ�����
	SetScaleType(AMS_INSIDE);
//	SetScaleType(AMS_OUTSIDE);
//	SetScaleType(AMS_SIDEBOTH);
//	SetLogMode(FALSE);
//	SetScaleDelta(10,2);
	
	ShowMeasureDelta( TRUE );
	ShowLogZero(FALSE);
	SetLogMode(FALSE);

	// Ŀʢ��ζˤ��{��
	SetMeasureAdjust(bAdjust);
	
}
///////////////////////////////////////
//���ԩ`���󥹥ȥ饯��
CAXMeasureStyle::CAXMeasureStyle( const CAXMeasureStyle &org )
{
	operator=(org);
}
/////////////////////////////////////////////////////////////////////////////
CAXMeasureStyle::~CAXMeasureStyle()
{

}
///////////////////////////////////////
/**
 * 	Ŀʢ���O��.
 * 		Ŀʢ�����С��/���/Ŀʢ����O�����롣
 * 
 * 	@param dMin			��С��
 * 	@param dMax			���
 * 	@param dDelta		Ŀʢ���g��(�ǩ`����ָ��) 1Ŀʢ��΅gλ
 * 	@param dDetailDelta	Ԕ��Ŀʢ���g��(�ǩ`����ָ��) 1Ŀʢ��΅gλ
 */
void CAXMeasureStyle::SetScale( double dMin, double dMax, double dDelta /*= -1.0*/, double dDetailDelta /*= -1*/ )
{
	CAXGDIScaleData::SetScale( dMin, dMax );
	if( IsEnableDivDelta() )	{///< Ŀʢ��ηָ�ָ�����Є�/�o��
		if(dDelta >= 2.0 && dDelta <= 200.0)	{
			m_measureStyle.dDelta = dDelta;
		}
		if(dDetailDelta >= 2.0 && dDetailDelta <= 20.0)	{
			m_measureStyle.dDetailDelta = dDetailDelta;
		}
	}	else	{
		if(dDelta >= 0.0)		{
			m_measureStyle.dDelta = dDelta;
		}
		if(dDetailDelta >= 0.0)	{
			m_measureStyle.dDetailDelta = dDetailDelta;
		}
	}
	Redraw();
}
///////////////////////////////////////
/**
 * 	Ŀʢ���S���軭.
 * 		Ŀʢ����S���軭����
 * 
 * 	@param pDC		�軭��ʹ�ä���ǥХ�������ƥ�����
 * 	@param rect		Ŀʢ����軭���빠��
 */
void CAXMeasureStyle::DrawScale( CDC *pDC, const CRect &rect )
{
	if(!IsShowScale())	{	return;	}
	
	if(IsLogMode())	{
		DrawLogScale( pDC, rect, GetScaleMode(), GetScaleType(), GetMin(), GetMax(), ( IsShowDetailScale() ? GetScaleDetailRatio() : 0 ) );
	}	else	{
		if(IsEnableDivDelta())	{//�ָ�ָ��
			DrawDivScale( pDC, rect, GetScaleMode(), GetScaleType(), GetScaleDelta(), ( IsShowDetailScale() ? GetScaleDetailDelta() : 0.0), GetScaleDetailRatio() );
		}	else	{
			double dDeltaOrg = GetMin();
			if(IsDeltaOrgEnable())	{	dDeltaOrg = GetDeltaOrg();	}
			DrawScale( pDC, rect, GetScaleMode(), GetScaleType(), GetMin(), GetMax(), dDeltaOrg, GetScaleDelta(), ( IsShowDetailScale() ? GetScaleDetailDelta() : 0.0), GetScaleDetailRatio() );//GetScaleDetailDelta() );
		}
	}
	// Ŀʢ������(X)
	if( GetScaleMode() == MEASUREX ){
		int iAxis;
		if( AMS_SIDEBOTH == GetScaleType() )	{	iAxis = int(0.5 * rect.Height() + rect.top);	}
		else if( AMS_OUTSIDE == GetScaleType() ){	iAxis = rect.top;						}
		else									{	iAxis = rect.bottom;					}
		pDC->MoveTo( rect.left, iAxis );
		pDC->LineTo( rect.right+1,iAxis );
		// ��С��
		if( IsShowScaleMin() ){
			pDC->MoveTo( rect.left,   rect.top    );
			pDC->LineTo( rect.left,   rect.bottom );
		}
		// ���
		if( IsShowScaleMax() ){
			pDC->MoveTo( rect.right,rect.top    );
			pDC->LineTo( rect.right,rect.bottom );			
		}
	// Ŀʢ������(Y)
	}	else if( GetScaleMode() == MEASUREY ){
		int iAxis;
		if( AMS_SIDEBOTH == GetScaleType() )	{	iAxis = int(0.5 * rect.Width()) + rect.left;	}
		else if( AMS_OUTSIDE == GetScaleType() ){	iAxis = rect.right;						}
		else									{	iAxis = rect.left;						}
		pDC->MoveTo( iAxis,rect.top );
		pDC->LineTo( iAxis,rect.bottom+1 );
		// ��С��
		if( IsShowScaleMin() ){
			pDC->MoveTo( rect.left, rect.bottom );
			pDC->LineTo( rect.right,rect.bottom );		
		}
		// ���
		if( IsShowScaleMax() ){
			pDC->MoveTo( rect.left, rect.top );
			pDC->LineTo( rect.right,rect.top );
		}
	}
}
///////////////////////////////////////
/**
 * 	Ŀʢ���S���軭.
 * 		Ŀʢ����S���軭����
 * 
 * 	@param pDC		�軭��ʹ�ä���ǥХ�������ƥ�����
 * 	@param rect		Ŀʢ����軭���빠��
 * 	@param iMode	X:MEASUREX/Y:MEASUREY 
 * 	@param iType	Ŀʢ������O��(AMS_INSIDE:�ڂ�/AMS_OUTSIDE:���/AMS_SIDEBOTH:����)
 * 	@param dMin		Ŀʢ�����С��
 * 	@param dMax		Ŀʢ������
 * 	@param dDelta	Ŀʢ����g��
 * 	@param dDelta	Ԕ��Ŀʢ����g��
 */
void CAXMeasureStyle::DrawScale( CDC *pDC, const CRect &rect, int iMode, int iType, double dMin, double dMax, double dOrg, double dDelta ,double dDetailDelta, long lDetailRatio)
{
	// �����Ӌ��
	double dRange  = dMax - dMin;
	double dOffset = 0.0;
	if( dDelta > 0.0 && dRange > 0.0 && (dMin != dOrg) ){	//
		dOffset = -1.0 * (((int)(fabs(dMin) / dDelta + 1.0 )) * dDelta - fabs(dMin)) ;
	}
	// �軭ԭ���O��
	CPoint oldOrg = pDC->SetViewportOrg( rect.left, rect.top );

	// Ŀʢ������(X)
	if( iMode == MEASUREX ){
		if( dDelta > 0.0 && dRange > 0.0){
			int iX;
			double dblDelta;
			double dblDetailDelta;
			for( int i = 0; i < MEASURE_LINEMAX; i++ ){
				dblDelta = dMin + i * dDelta + dOffset;
				dblDetailDelta = dblDelta;
				if(dblDelta > dMax )	{	break;	}
				if(dblDelta >= dMin )		{
					iX = FtoL( ( dblDelta - dMin ) / dRange * rect.Width() );
					pDC->MoveTo( iX, 0 );
					pDC->LineTo( iX, rect.Height() );
				}
					
				if( dDetailDelta > 0.0 )	{
					CRect rectDetail( 0, 0, rect.Width(), rect.Height());
					GetDetailRect( rect, iMode, iType, lDetailRatio , &rectDetail );
					for( int j = 1; j < 10; j++ ){
						dblDetailDelta = dDetailDelta * j;
						if(dblDetailDelta >= dDelta)	{	break;	}
						dblDetailDelta = dblDelta + dblDetailDelta;
						if(dblDetailDelta > dMax )	{	break;		}
						if(dblDetailDelta < dMin )	{	continue;	}
						iX = FtoL( ( dblDetailDelta - dMin ) / dRange * rect.Width() );
						pDC->MoveTo( iX, rectDetail.top );
						pDC->LineTo( iX, rectDetail.bottom );
					}
				}
			}
		}
	// Ŀʢ������(Y)
	} else if( iMode == MEASUREY ){
		if( dDelta > 0.0 && dRange > 0.0){
			int iY;
			double dblDelta;
			double dblDetailDelta;
			for( int i = 0; i < MEASURE_LINEMAX; i++ ){
				dblDelta = dMin + i * dDelta + dOffset;
				dblDetailDelta = dblDelta;
				if(dblDelta > dMax )	{	break;	}
				if(dblDelta >= dMin )	{
					iY = FtoL( ( dMax - dblDetailDelta ) / dRange * rect.Height() );
					pDC->MoveTo( 0, iY );
					pDC->LineTo( rect.Width(),iY );
				}
				if( dDetailDelta > 0.0 )	{
					CRect rectDetail( 0, 0, rect.Width(), rect.Height());
					GetDetailRect( rect, iMode, iType, lDetailRatio , &rectDetail );
					for( int j = 1; j < 10; j++ ){
						dblDetailDelta = dDetailDelta * j;
						if(dblDetailDelta >= dDelta)	{	break;	}
						dblDetailDelta = dblDelta + dblDetailDelta;
						if(dblDetailDelta > dMax )	{	break;	}
						if(dblDetailDelta < dMin )	{	continue;	}
						iY = FtoL( ( dMax - dblDetailDelta )/ dRange * rect.Height() )  ;			
						pDC->MoveTo( rectDetail.left, iY );
						pDC->LineTo( rectDetail.right,iY );
					}
				}
			}
		}
	}
	// ԭ������
	pDC->SetViewportOrg( oldOrg );
}
///////////////////////////////////////
/**
 * 	Ŀʢ���S���軭.
 * 		Ŀʢ����S���軭����
 * 
 * 	@param pDC			�軭��ʹ�ä���ǥХ�������ƥ�����
 * 	@param rect			Ŀʢ����軭���빠��
 * 	@param iMode		X:MEASUREX/Y:MEASUREY 
 * 	@param iType		Ŀʢ������O��(AMS_INSIDE:�ڂ�/AMS_OUTSIDE:���/AMS_SIDEBOTH:����)		
 * 	@param dMin			Ŀʢ�����С��
 * 	@param dMax			Ŀʢ������
 * 	@param dDelta		Ŀʢ����g��
 * 	@param dDetailDelta	Ԕ��Ŀʢ����g��
 */
void CAXMeasureStyle::DrawDivScale( CDC *pDC, const CRect &rect, int iMode, int iType, double dDelta, double dDetailDelta, long lDetailRatio )
{

	// �軭ԭ���O��
	CPoint oldOrg = pDC->SetViewportOrg( rect.left, rect.top );
	int nDelta = FtoL( dDelta );
	int nDetailDelta = FtoL( dDetailDelta );
	// Ŀʢ������(X)
	if( iMode == MEASUREX ){
		if( nDelta > 1 && rect.Width() > 1){
			int iX;
			double dblDelta = ((double)rect.Width()) / nDelta;
			double dblDetailDelta = -1.0;
			if( nDetailDelta > 1 )	{
				dblDetailDelta = dblDelta / nDetailDelta;
			}
			double dblPos = 0.0;
			for( int i = 1; i < MEASURE_LINEMAX; i++ ){
				if( dblDetailDelta > 0.0 )	{
					CRect rectDetail( 0, 0, rect.Width(), rect.Height());
					GetDetailRect( rect, iMode, iType, lDetailRatio , &rectDetail );
					for( int j = 1; j < MEASURE_DETAILMAX; j++ ){
						if( j >= nDetailDelta )	{	break;	}
						iX = FtoL( dblDetailDelta * j + dblPos );
						pDC->MoveTo( iX, rectDetail.top );
						pDC->LineTo( iX, rectDetail.bottom );
					}
				}
				if( i >= nDelta )	{	break;	}
				dblPos = dblDelta * i;
				iX = FtoL( dblPos );
				pDC->MoveTo( iX, 0 );
				pDC->LineTo( iX, rect.Height() );	
			}
		}
	// Ŀʢ������(Y)
	} else if( iMode == MEASUREY ){
		if( nDelta > 1 && rect.Height() > 1){
			int iY;
			double dblDelta = ((double)rect.Height()) / nDelta;
			double dblDetailDelta = -1.0;
			if( nDetailDelta > 1 )	{
				dblDetailDelta = dblDelta / nDetailDelta;
			}
			double dblPos = 0.0;
			for( int i = 1; i < MEASURE_LINEMAX; i++ ){
				if( dblDetailDelta > 0.0 )	{
					CRect rectDetail( 0, 0, rect.Width(), rect.Height());
					GetDetailRect( rect, iMode, iType, lDetailRatio , &rectDetail );
					for( int j = 1; j < MEASURE_DETAILMAX; j++ ){
						if( j >= nDetailDelta )	{	break;	}
						iY = FtoL( dblDetailDelta * j + dblPos );
						pDC->MoveTo( rectDetail.left, iY );
						pDC->LineTo( rectDetail.right,iY );
					}
				}
				if( i >= nDelta )	{	break;	}
				dblPos = dblDelta * i;
				iY = FtoL( dblPos );
				pDC->MoveTo( 0, iY );
				pDC->LineTo( rect.Width(),iY );
			}
		}
	}
	// ԭ������
	pDC->SetViewportOrg( oldOrg );

}
///////////////////////////////////////
/**
 * 	Ŀʢ���S���軭.
 * 		Ŀʢ����S���軭����
 * 
 * 	@param pDC		�軭��ʹ�ä���ǥХ�������ƥ�����
 * 	@param rect		Ŀʢ����軭���빠��
 * 	@param iMode	X:MEASUREX/Y:MEASUREY 
 * 	@param iType	Ŀʢ������O��(AMS_INSIDE:�ڂ�/AMS_OUTSIDE:���/AMS_SIDEBOTH:����)
 * 	@param dMin		Ŀʢ�����С��
 * 	@param dMax		Ŀʢ������
 * 	@param dDelta	Ŀʢ����g��
 */
void CAXMeasureStyle::DrawLogScale( CDC *pDC, const CRect &rect, int iMode, int iType, double dMin, double dMax, long lDetailRatio )
{
	// �����Ӌ��
	double dMinLog = log10( dMin );
	double dMaxLog = log10( dMax );
	double dRange  = dMaxLog - dMinLog;
	// �軭ԭ���O��
	CPoint oldOrg = pDC->SetViewportOrg( rect.left, rect.top );

	if( iMode == MEASUREX ){	// Ŀʢ������(X)
		int iX;
		for( int i = 0; i < MEASURE_LINEMAX; i++ ){
			double dblDelta = dMinLog + i;
			if(dblDelta > dMaxLog )	{	break;	}
			iX = FtoL( ( dblDelta - dMinLog ) / dRange * rect.Width() );
			pDC->MoveTo( iX, 0 );
			pDC->LineTo( iX, rect.Height() );	
			if(lDetailRatio > 0)	{// Ԕ��
				double dblDetailDelta;
				CRect rectDetail( 0, 0, rect.Width(), rect.Height());
				GetDetailRect( rect, iMode, iType, lDetailRatio , &rectDetail );				
				for( int j = 2; j < 10; j++ ){
					dblDetailDelta = log10( j );
					if(dblDetailDelta >= 1.0)	{	break;	}
					dblDetailDelta = dblDelta + dblDetailDelta;
					if(dblDetailDelta > dMaxLog)	{	break;	}
					iX = FtoL( ( dblDetailDelta - dMinLog ) / dRange * rect.Width() );
					pDC->MoveTo( iX, rectDetail.top );
					pDC->LineTo( iX, rectDetail.bottom );
				}
			}		
		}
	} else if( iMode == MEASUREY ){// Ŀʢ������(Y)
		int iY;
		for( int i = 0; i < MEASURE_LINEMAX; i++ ){
			double dblDelta = dMinLog + i;
			if(dblDelta > dMaxLog )	{	break;	}
			iY = FtoL( ( dMaxLog - dblDelta ) / dRange * rect.Height() );
			pDC->MoveTo( 0, iY );
			pDC->LineTo( rect.Width(),iY );
			if(lDetailRatio > 0)	{// Ԕ��
				double dblDetailDelta;
				CRect rectDetail( 0, 0, rect.Width(), rect.Height());
				GetDetailRect( rect , iMode, iType, lDetailRatio , &rectDetail );
				for( int j = 2; j < 10; j++ ){
					dblDetailDelta = log10( j );
					if(dblDetailDelta >= 1.0)		{	break;	}
					dblDetailDelta = dblDelta + dblDetailDelta;
					if(dblDetailDelta > dMaxLog)	{	break;	}
					iY = FtoL( dblDetailDelta / dRange * (rect.Height()) )  ;
					iY = FtoL( ( dMaxLog - dblDetailDelta ) / dRange * rect.Height() );
					pDC->MoveTo( rectDetail.left,  iY );
					pDC->LineTo( rectDetail.right, iY );
				}
			}
		}
	}
	// ԭ������
	pDC->SetViewportOrg( oldOrg );

}
///////////////////////////////////////
/**
 * 	�軭���빠��RECT������ʤ��軭
 * 		Ŀʢ��(��С��/���)���軭����
 * 
 * 	@param rect		Ŀʢ����軭���빠��
 * 	@param iMode	X:MEASUREX/Y:MEASUREY 
 * 	@param iType	Ŀʢ������O��(AMS_INSIDE:�ڂ�/AMS_OUTSIDE:���/AMS_SIDEBOTH:����)
 */
void CAXMeasureStyle::GetDetailRect(const CRect &rect, int iMode, int iType, long lRatio, LPRECT lpCalcRect )
{
	//(*lpCalcRect) = rect;

	long lCutLen = 0;
	if(lRatio >= 100)	{	return;	}
	if(lRatio <  0)		{	lRatio = 0;	}
	
	if( iMode == MEASUREX ){// Ŀʢ������(X)
		lCutLen = (int)((1.0 - 0.01 * lRatio) * rect.Height() + 0.5);
		if(lCutLen < 1)		{	lCutLen = 1;	}
		if( AMS_SIDEBOTH == iType )		{
			lCutLen = lCutLen / 2;
			if(lCutLen < 1)		{	lCutLen = 1;	}
			lpCalcRect->top += lCutLen;
			lpCalcRect->bottom -= lCutLen;
		}	else if( AMS_OUTSIDE == iType )	{
			lpCalcRect->bottom -= lCutLen;
		}	else	{
			lpCalcRect->top += lCutLen;
		}
	} else if( iMode == MEASUREY ){// Ŀʢ������(Y)
		lCutLen = (int)((1.0 - 0.01 * lRatio) * rect.Width() + 0.5);
		if(lCutLen < 1)		{	lCutLen = 1;	}
		if( AMS_SIDEBOTH == iType )		{
			lCutLen = lCutLen / 2;
			if(lCutLen < 1)		{	lCutLen = 1;	}
			lpCalcRect->left += lCutLen;
			lpCalcRect->right -= lCutLen;
		}	else if( AMS_OUTSIDE == iType )	{
			lpCalcRect->left += lCutLen;
		}	else	{
			lpCalcRect->right -= lCutLen;
		}
	}
}
///////////////////////////////////////
/**
 * 	Ŀʢ��(��С��/���)���軭
 * 		Ŀʢ��(��С��/���)���軭����
 * 
 * 	@param pDC			�軭��ʹ�ä���ǥХ�������ƥ�����
 * 	@param rect			Ŀʢ����軭���빠��
 */
void CAXMeasureStyle::DrawMeasure( CDC *pDC, const CRect &rect )
{
	// �ե���Ȥ�����
	LOGFONT logfont;
	pDC->GetCurrentFont()->GetLogFont( &logfont );
	logfont.lfEscapement = GetMeasureAngle();
	logfont.lfOrientation= GetMeasureAngle();

	if(GetMeasureFontSize() > 0)	{
		logfont.lfHeight = -MulDiv( GetMeasureFontSize(), pDC->GetDeviceCaps(LOGPIXELSY), 72);
	}

	CFont font;
	font.CreateFontIndirect( &logfont );

	// �ե����?����ɫ���x�k
	CFont   *pOldFont = pDC->SelectObject( &font );
	COLORREF oldColor = pDC->SetTextColor( GetMeasureColor() );

	if( IsShowMeasureDelta() )	{
		if(IsLogMode())	{
			CString strFormat = GetFormat();
			if(!IsShowLogZero())	{	strFormat = _T("");	}
			DrawLogMeasure( pDC, rect, GetScaleMode(), GetMin(), GetMax(), 10.0/*m_dDelta*/ , strFormat , 2 );
		}	else	{
			if(IsEnableDivDelta())	{
				DrawDivMeasure( pDC, rect, GetScaleMode(), GetMin(), GetMax(), GetScaleDelta(), GetFormat(), 2 );
			}	else	{
				double dDeltaOrg = GetMin();
				if(IsDeltaOrgEnable())	{	dDeltaOrg = GetDeltaOrg();	}
				DrawMeasure( pDC, rect, GetScaleMode(), GetMin(), GetMax(), dDeltaOrg, GetScaleDelta(), GetFormat(), 2 );
			}
		}
	}
	// ��С��/���
	if( IsShowMeasureMin() )	{
		CString strData;
		CString strFormat = GetFormat();
		int iPower = FtoL(log10( GetMin() ));
		if(IsLogMode() && (!IsShowLogZero()))	{
			if( iPower >= 0)	{	strFormat.Format( "%%.%df", 0 );				}
			else				{	strFormat.Format( "%%.%df", abs( iPower ) );	}
		}
		strData.Format( strFormat, GetMin() );
		// Ŀʢ������(X)
		if( GetScaleMode() == MEASUREX ){
			TextDraw( pDC, rect, GetScaleMode(), rect.left, rect.top, strData, (IsMeasureAdjust() ? 1 : 0));
		// Ŀʢ������(Y)
		}	else if( GetScaleMode() == MEASUREY ){
			TextDraw( pDC, rect, GetScaleMode(), rect.right, rect.bottom, strData, (IsMeasureAdjust() ? 1 : 0) );
		}
	}

	// ��С��/���
	if( IsShowMeasureMax() )	{
		CString strData;
		CString strFormat = GetFormat();
		int iPower = (int)(log10( GetMax() ));
		if(IsLogMode() && (!IsShowLogZero()))	{
			if( iPower >= 0)	{	strFormat.Format( "%%.%df", 0 );				}
			else				{	strFormat.Format( "%%.%df", abs( iPower ) );	}
		}
		strData.Format( strFormat, GetMax() );
		// Ŀʢ������(X)
		if( GetScaleMode() == MEASUREX ){
			TextDraw( pDC, rect, GetScaleMode(), rect.right,rect.top, strData, (IsMeasureAdjust() ? 1 : 0) );
		// Ŀʢ������(Y)
		}	else if( GetScaleMode() == MEASUREY ){
			TextDraw( pDC, rect, GetScaleMode(), rect.right, rect.top,   strData, (IsMeasureAdjust() ? 1 : 0) );
		}
	}

	// ����ɫ�����
	pDC->SetTextColor( oldColor );

	// �ե���Ȥ����
	pDC->SelectObject( pOldFont );

	// �ե���Ȥ��Ɨ�
	font.DeleteObject();
}
///////////////////////////////////////
/**
 * 	Ŀʢ������Ƥ��軭
 * 		Ŀʢ������Ƥ��軭����
 * 
 * 	@param pDC			�軭��ʹ�ä���ǥХ�������ƥ�����
 * 	@param rect			Ŀʢ����軭���빠��
 *	@param nFontSize	Font Size
 */
void CAXMeasureStyle::DrawMeasureName( CDC *pDC, const CRect &rect, int nFontSize )
{
	CString strMeasureName = GetString();
//	if(!m_strUnit.IsEmpty())	{			///< Ŀʢ�����΅gλ
//		strMeasureName.Format(m_strNameFormat,GetString(),m_strUnit);
//	}

	if(strMeasureName.IsEmpty())	{	return;	}

	// �ե���Ȥ�����
	LOGFONT logfont;
	pDC->GetCurrentFont()->GetLogFont( &logfont );
	if( GetScaleMode() == MEASUREY ){
		logfont.lfEscapement = 900;
		logfont.lfOrientation= 900;
	}
	// FontSize
	if(nFontSize > 0)	{
		logfont.lfHeight = -MulDiv(nFontSize, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	}

	CFont font;
	font.CreateFontIndirect( &logfont );

	// �ե����?����ɫ���x�k
	CFont   *pOldFont = pDC->SelectObject( &font );
	COLORREF oldColor = pDC->SetTextColor( GetStrColor() );

	// �軭���֤ι���
	CSize drawSize = pDC->GetTextExtent( strMeasureName );

	// Ŀʢ�����軭(X)
	int iX = 0, iY = 0;
	CRect rectText = rect;
	if( GetScaleMode() == MEASUREX ){
		iX = rect.left + rect.Width() / 2 - drawSize.cx / 2;
		iY = rect.bottom - drawSize.cy;
		if( iY < rect.top ) iY = rect.top;
	// Ŀʢ�����軭(Y)
	} else if( GetScaleMode() == MEASUREY ){
		iX = rect.left;
		iY = rect.top + rect.Height() / 2 + drawSize.cx / 2;
	}
	//pDC->TextOut( iX, iY, strMeasureName );
	GetNameAXString().TextDraw( pDC, rectText, font, strMeasureName, GetStrColor(), GetNameAXString().GetDTFormat(), logfont.lfOrientation  );

	// ����ɫ�����
	pDC->SetTextColor( oldColor );

	// �ե���Ȥ����&�Ɨ�
	pDC->SelectObject( pOldFont );
	font.DeleteObject();
}
///////////////////////////////////////
/**
 * 	Ŀʢ���MAX�������Ф��軭
 * 		Ŀʢ���MAX�������Ф��軭����
 * 
 * 	@param pDC			�軭��ʹ�ä���ǥХ�������ƥ�����
 * 	@param rect			Ŀʢ����軭���빠��
 *	@param bMonochrome	��Υ����ʾ�ե饰
 */
void CAXMeasureStyle::DrawMeasureMaxString( CDC *pDC, const CRect &rect, BOOL bMonochrome )
{
	if( GetMaxSideAXString().GetString().IsEmpty() )	{	return;	}
	// �ե���Ȥ�����
	LOGFONT logfont;
	pDC->GetCurrentFont()->GetLogFont( &logfont );
	if( GetScaleMode() == MEASUREX ){
		logfont.lfEscapement = 0;
		logfont.lfOrientation= 0;
	}	else if( GetScaleMode() == MEASUREY ){
		logfont.lfEscapement = 900;
		logfont.lfOrientation= 900;
	}

	// �ե����?����ɫ���x�k
	CFont font;
	font.CreateFontIndirect( &logfont );
	CFont   *pOldFont = pDC->SelectObject( &font );
	COLORREF oldColor = pDC->SetTextColor( m_axstrMaxSide.GetStrColor() );

	CRect rectText = rect;
	if(GetScaleMode() == MEASUREX )	{
		rectText.left = rect.left + FtoL(rect.Width() / 2);
	}	else if(GetScaleMode() == MEASUREY )	{
		rectText.bottom = rect.top + FtoL(rect.Height() / 2);
	}
	//pDC->DrawText(strText1,rectText,m_axstrMaxSide.GetDTFormat() );
	GetMaxSideAXString().TextDraw( pDC, rectText, font, bMonochrome, logfont.lfOrientation  );
	
	// ����ɫ�����
	pDC->SetTextColor( oldColor );

	// �ե���Ȥ����&�Ɨ�
	pDC->SelectObject( pOldFont );
	font.DeleteObject();
}
///////////////////////////////////////
/**
 * 	Ŀʢ���MIN�������Ф��軭
 * 		Ŀʢ���MIN�������Ф��軭����
 * 
 * 	@param pDC			�軭��ʹ�ä���ǥХ�������ƥ�����
 * 	@param rect			Ŀʢ����軭���빠��
 *	@param bMonochrome	��Υ����ʾ�ե饰
 */
void CAXMeasureStyle::DrawMeasureMinString( CDC *pDC, const CRect &rect, BOOL bMonochrome )
{
	//CString strText1 = ;	///< Up�Ȥα�ʾ������
	//CString strText2 = ;	///< Down�Ȥα�ʾ������
	if( GetMaxSideAXString().GetString().IsEmpty() )	{	return;	}

	// �ե���Ȥ�����
	LOGFONT logfont;
	pDC->GetCurrentFont()->GetLogFont( &logfont );
	if( GetScaleMode() == MEASUREX ){
		logfont.lfEscapement = 0;
		logfont.lfOrientation= 0;
	}	else if( GetScaleMode() == MEASUREY ){
		logfont.lfEscapement = 900;
		logfont.lfOrientation= 900;
	}
	
	CFont font;
	font.CreateFontIndirect( &logfont );

	// �ե����?����ɫ���x�k
	CFont   *pOldFont = pDC->SelectObject( &font );
	COLORREF oldColor = pDC->SetTextColor( m_axstrMinSide.GetStrColor() );
	// �軭���֤ι���
	//CSize drawSize = pDC->GetTextExtent( strText1 );
	CRect rectText = rect;
	if(GetScaleMode() == MEASUREX )	{
		rectText.right = rect.left + FtoL(rect.Width() / 2);
	}	else if(GetScaleMode() == MEASUREY )	{
		rectText.top = rect.top + FtoL(rect.Height() / 2);
	}
	//pDC->DrawText(strText2,rectText,m_axstrMinSide.GetDTFormat() );
	GetMinSideAXString().TextDraw( pDC, rectText, font, bMonochrome, logfont.lfOrientation  );

	// ����ɫ�����
	pDC->SetTextColor( oldColor );

	// �ե���Ȥ����&�Ɨ�
	pDC->SelectObject( pOldFont );
	font.DeleteObject();
	
}
///////////////////////////////////////
/**
 * 	Ŀʢ��(��С��/���)���軭
 * 		Ŀʢ��(��С��/���)���軭����
 * 
 * 	@param pDC			�軭��ʹ�ä���ǥХ�������ƥ�����
 * 	@param rect			Ŀʢ����軭���빠��
 * 	@param iMode		X:MEASUREX/Y:MEASUREY
 * 	@param dMin			�軭������С��
 * 	@param dMax			�軭�������
 * 	@param dOrg			�軭����Ŀʢ��ԭ��
 * 	@param dDelta		Ŀʢ���g��(0.0����)
 * 	@param lpszFormat	Ŀʢ��Υե��`�ޥå�
 * 	@param bAdjust		�軭�I���Ϥ߳����ʤ��褦�ˡ�FALSE:�{�����ʤ�/TRUE:�{������
 */
void CAXMeasureStyle::DrawMeasure( CDC *pDC, const CRect &rect, int iMode, double dMin, double dMax, double dOrg, double dDelta, LPCTSTR lpszFormat, BOOL bAdjust )
{
	// �����Ӌ��
	double dRange  = dMax - dMin;
	double dOffset = 0.0;
	if( dDelta > 0.0 && dRange > 0.0 && (dMin != dOrg) ){	//
		dOffset = -1.0 * (((int)(fabs(dMin) / dDelta + 1.0 )) * dDelta - fabs(dMin)) ;
			//(((int)(( dMin - dOrg) / dDelta  + 1.0)) * dDelta + (dMin - dOrg));
	}
	CString strData;
	// Ŀʢ���g�����{��
	 //dDelta *= (double)m_iMeasureSpan;

	// X
	if( iMode == MEASUREX ){
		if( dDelta > 0.0 && dRange > 0.0){
			int iX;
			double dData = 0.0;
			for( int i = 0; i < MEASURE_LINEMAX; i++ ){
				dData = dMin + dDelta * i + dOffset;
				if(dData > dMax )	{	break;	}
				if(dData < dMin )	{	continue;	}
				iX = rect.left + FtoL( ( dDelta * i + dOffset) / dRange * (rect.Width() - 1) )  ;
				strData.Format( lpszFormat, dData );
				TextDraw( pDC, rect, iMode, iX, rect.top, strData, bAdjust );
			}
		}
	// Y
	} else if( iMode == MEASUREY )	{
		if( dDelta > 0.0 && dRange > 0.0){
			int iY;
			double dData = 0.0;
			for( int i = 0; i < MEASURE_LINEMAX; i++ ){
				dData = dMin + dDelta * i + dOffset;
				if(dData > dMax )	{	break;	}
				if(dData < dMin )	{	continue;	}
				iY = rect.bottom - 1 - FtoL( ( dDelta * i + dOffset ) / dRange * (rect.Height() - 1) )  ;
				strData.Format( lpszFormat, dData );
				TextDraw( pDC, rect, iMode, rect.right, iY, strData, bAdjust );
			}
		}
	}
}
///////////////////////////////////////
/**
 * 	Ŀʢ��(��С��/���)���軭
 * 		Ŀʢ��(��С��/���)���軭����
 * 
 * 	@param pDC			�軭��ʹ�ä���ǥХ�������ƥ�����
 * 	@param rect			Ŀʢ����軭���빠��
 * 	@param iMode		X:MEASUREX/Y:MEASUREY
 * 	@param dMin			�軭������С��
 * 	@param dMax			�軭�������
 * 	@param dDelta		Ŀʢ���g��(0.0����)
 * 	@param lpszFormat	Ŀʢ��Υե��`�ޥå�
 * 	@param bAdjust		�軭�I���Ϥ߳����ʤ��褦�ˡ�FALSE:�{�����ʤ�/TRUE:�{������
 */
void CAXMeasureStyle::DrawDivMeasure( CDC *pDC, const CRect &rect, int iMode, double dMin, double dMax, double dDelta, LPCTSTR lpszFormat, BOOL bAdjust )
{
	CString strData;
	// Ŀʢ���g�����{��
	//dDelta *= (double)m_iMeasureSpan;
	int nDelta = FtoL( dDelta );
	// X
	if( iMode == MEASUREX ){
		if( nDelta > 1 && rect.Width() > 1){
			int iX;
			double dblDelta = ((double)rect.Width() - 1) / nDelta;
			double dData = 0.0;
			for( int i = 1; i < MEASURE_LINEMAX; i++ ){
				if( i >= nDelta )	{	break;	}
				dData = dMin + (dMax - dMin) / nDelta * i;
				iX = rect.left + FtoL( dblDelta * i )  ;
				strData.Format( lpszFormat, dData );
				TextDraw( pDC, rect, iMode, iX, rect.top, strData, bAdjust );
			}
		}
	// Y
	} else if( iMode == MEASUREY )	{
		if( nDelta > 1 && rect.Height() > 1){
			int iY;
			double dblDelta = ((double)rect.Height() - 1) / nDelta;
			double dData = 0.0;
			for( int i = 1; i < MEASURE_LINEMAX; i++ ){
				if( i >= nDelta )	{	break;	}
				dData = dMin + (dMax - dMin) / nDelta * i;
				iY = rect.bottom - 1 - FtoL( dblDelta * i ) ;
				strData.Format( lpszFormat, dData );
				TextDraw( pDC, rect, iMode, rect.right, iY, strData, bAdjust );
			}
		}
	}
}
///////////////////////////////////////
/**
 * 	Ŀʢ��(��С��/���)���軭
 * 		Ŀʢ��(��С��/���)���軭����
 * 
 * 	@param pDC			�軭��ʹ�ä���ǥХ�������ƥ�����
 * 	@param rect			Ŀʢ����軭���빠��
 * 	@param iMode		X:MEASUREX/Y:MEASUREY
 * 	@param dMin			�軭������С��
 * 	@param dMax			�軭�������
 * 	@param dDelta		Ŀʢ���g��(0.0����)
 * 	@param lpszFormat	Ŀʢ��Υե��`�ޥå�
 * 	@param bAdjust		�軭�I���Ϥ߳����ʤ��褦�ˡ�FALSE:�{�����ʤ�/TRUE:�{������
 */
void CAXMeasureStyle::DrawLogMeasure( CDC *pDC, const CRect &rect, int iMode, double dMin, double dMax, double dDelta, LPCTSTR lpszFormat, BOOL bAdjust )
{
	// �����Ӌ��
	double dMinLog = log10( dMin );
	double dMaxLog = log10( dMax );
	double dRange  = dMaxLog - dMinLog;
	CString strData;
	CString strFormat = lpszFormat;
	if( iMode == MEASUREX ){// X
		int iX;
		int iValLog = 0;
		for( int i = 0; i < MEASURE_LINEMAX; i++ ){
			iX = rect.left + FtoL( ((double) i ) / dRange * (rect.Width() - 1) )  ;
			if(iX < rect.left)									{	continue;	}
			else if(iX > (rect.right-1)	)						{	break;		}
			// ���Υǩ`��
			//DELL20050711 iValLog = (int)dMinLog + i;
			iValLog = FtoL(dMinLog + i);//yotsutsu20050711
			double dVal = pow( 10, iValLog );
			// ���֥ե��`�ޥå�����
			if(_tcslen(lpszFormat) < 2)	{
				if(iValLog >= 0.1)	{
					strFormat.Format( "%%.%df", 0 );
				}	else	{
					strFormat.Format( "%%.%df", abs( iValLog ) );
				}
			}
			strData.Format( strFormat, dVal );
			TextDraw( pDC, rect, iMode, iX, rect.top, strData, bAdjust );
		}
	} else if( iMode == MEASUREY )	{// Y
		int iY;
		int iValLog = 0;
		for( int i = 0; i < MEASURE_LINEMAX; i++ ){
			iY = rect.bottom - 1 - FtoL( ((double) i ) / dRange * (rect.Height() - 1) )  ;
			if(iY > (rect.bottom - 1))								{	continue;	}
			else if(iY < rect.top )									{	break;		}
			// ���Υǩ`��
			//DELL20050711 iValLog = (int)dMinLog + i;
			iValLog = FtoL(dMinLog + i);//yotsutsu20050711
			double dVal = pow( 10, iValLog );
			// ���֥ե��`�ޥå�����
			if(_tcslen(lpszFormat) < 2)	{
				if(iValLog >= 0.1)	{
					strFormat.Format( "%%.%df", 0 );
				}	else	{
					strFormat.Format( "%%.%df", abs( iValLog ) );
				}
			}
			strData.Format( strFormat, dVal );
			TextDraw( pDC, rect, iMode, rect.right, iY, strData, bAdjust );	
		}
	}
}
///////////////////////////////////////////
/**
 * 	�����`�����֤򹠇��ڤ��軭����.
 * 
 * 	@param pDC		�軭��ʹ�ä���ǥХ�������ƥ�����
 * 	@param rect		�軭����
 * 	@param iMode	X:MEASUREX/Y:MEASUREY 
 * 	@param iX		�軭λ��X
 * 	@param iY		�軭λ��Y
 * 	@param lpszData	�軭������
 * 	@param iAdjust	0:�{�����ʤ�/1:�{������/2:�Ϥ߳��������ʾ���ʤ�
 */
void CAXMeasureStyle::TextDraw( CDC *pDC, CRect rect, int iMode, int iX, int iY, LPCTSTR lpszData, int iAdjust )
{
	int iMargin = 0;
	CSize sizeData = pDC->GetTextExtent( lpszData );

	LOGFONT logfont;
	pDC->GetCurrentFont()->GetLogFont( &logfont );
	// ��Ӌ�ゎ��ȡ��
	double dRad= ( M_PI / 180.0 ) * ( logfont.lfOrientation / 10.0 );
	double dSinX = sizeData.cx * sin( dRad );
	double dSinY = sizeData.cy * sin( dRad );
	double dCosX = sizeData.cx * cos( dRad );
	double dCosY = sizeData.cy * cos( dRad );
	double dWidth, dHeigth;
	
	// X�軭λ��
	if( iMode == MEASUREX ){
		dWidth  = dCosX;
		dWidth += dSinY;
		dHeigth = dSinX;
		iX -= FtoL( dWidth ) / 2;
		iY += FtoL( dHeigth );

		// �ˤ��{��
		int iWidth = FtoL( dWidth );
		if( iX < (rect.left - iMargin) )	{
			if(iAdjust == 1)		{	iX = rect.left - iMargin + 1;	}
			else if(iAdjust == 2)	{	return;	}
		}
		if( (iX + iWidth) > (rect.right + iMargin )){
			if(iAdjust == 1)		{	iX = rect.right + iMargin - iWidth;	}
			else if(iAdjust == 2)	{	return;	}
		}
	// Y�軭λ��
	} else{
		dWidth  = dCosX;
		dWidth += dSinY;
		dHeigth = dSinX;
		dHeigth-= dCosY;
		iX -= FtoL( dWidth );
		iY += FtoL( dHeigth ) / 2;

		// �ˤ��{��
		if( (iY - (int)dSinX < rect.top - iMargin )){
			if(iAdjust == 1)		{	iY = rect.top - iMargin + 1 + (int)dSinX;	}
			else if(iAdjust == 2)	{	return;	}
		}
		if(( iY + (int)dCosY > rect.bottom + iMargin )){
			if(iAdjust == 1)		{	iY = rect.bottom + iMargin - (int)dCosY;	}
			else if(iAdjust == 2)	{	return;	}
		}
	}
	int nBkMode = pDC->SetBkMode( TRANSPARENT );
	pDC->TextOut( iX, iY, lpszData );
	pDC->SetBkMode( nBkMode );
}
///////////////////////////////////////
/**
 * 	CAXMeasureStyle�Υ����`����� + ���򥳥ԩ`����.
 * 
 * 	@param src		���ԩ`Ԫ��CAXMeasureStyle
 * 	@return			�����`�����Υݥ���
 */
const GDISCALEINFO & CAXMeasureStyle::CopyScale( const CAXMeasureStyle &src )
{
	///< Ŀʢ��ηָ�ָ�����Є�/�o��
	EnableDivDelta((src.m_measureStyle.dwMsStyle & AMS_EN_DIVDELTA));
	//< Ŀʢ���g����ԭ��(�ǩ`����ָ��)
	SetDeltaOrg((src.m_measureStyle.dwMsStyle & AMS_EN_ORG) ,src.m_measureStyle.dOrgDelta);			
	
	m_measureStyle.dDelta = src.m_measureStyle.dDelta;				///< Ŀʢ���g��(�ǩ`����ָ��)
	m_measureStyle.dDetailDelta = src.m_measureStyle.dDetailDelta;	///< Ԕ��Ŀʢ���g��(�ǩ`����ָ��)
	
	CAXGDIScaleData::Copy(src);

	return GetScaleInfo();
}
///////////////////////////////////////
/**
 * 	�����`�륹�����루CAXMeasureStyle���򥳥ԩ`����.
 * 
 * 	@param src		���ԩ`Ԫ��CAXMeasureStyle
 * 	@return			�����`�륹������Υݥ���
 */
CAXMeasureStyle & CAXMeasureStyle::Copy( const CAXMeasureStyle &src )
{
	operator = (src);
	return (*this);
}
/////////////////////////////////////////////////////////////////////////////
// CAXMeasureSpin
/////////////////////////////////////////////////////////////////////////////
#define	MEASURESIZE		10		// Ŀʢ��νŤ��L��
#define	MEASUREMARGIN	2		// Ŀʢ�����ǰ�Υީ`����
#define IDUPSPIN		1		// ���ԥ��ID(��)
#define IDDWSPIN		2		// ���ԥ��ID(��)

const int CAXMeasureCtrl::c_iMeasureSise = 10;

BEGIN_MESSAGE_MAP(CAXMeasureSpin, CSpinButtonCtrl)
	ON_WM_CREATE()
END_MESSAGE_MAP()
///////////////////////////////////////
/**
 * 	���ڻ�.
 * 
 * 	@param lpCreateStruct	���ڻ����
 * 	@return					0:�ɹ� -1:ʧ��
 */
int CAXMeasureSpin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CSpinButtonCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect, rgnRect;
	CWnd::GetClientRect( rect );
	rgnRect = rect;

	// X���ԥ�
	if( GetStyle() & UDS_HORZ ){
		switch( GetDlgCtrlID() ){
		case IDDWSPIN:	rect.right += rect.Width();	break;	// ��
		case IDUPSPIN:	rect.left  -= rect.Width();			// ��
						rgnRect.OffsetRect( rgnRect.Width(), 0 );
						break;
		}
	// Y���ԥ�
	} else{
		switch( GetDlgCtrlID() ){
		case IDUPSPIN:	rect.bottom += rect.Height();	break;	// ��
		case IDDWSPIN:	rect.top    -= rect.Height();			// ��
						rgnRect.OffsetRect( 0, rgnRect.Height() );
						break;
		}
	}

	// ������ɥ����������
	ClientToScreen( rect );
	GetParent()->ScreenToClient( rect );
	MoveWindow( rect );

	// ������ɥ�����
	CRgn  rgn;
	rgn.CreateRectRgnIndirect( rgnRect );
	SetWindowRgn( rgn, TRUE );
	rgn.DeleteObject();

	// �����O��
	SetRange( 0, 1 );

	return 0;
}
/////////////////////////////////////////////////////////////////////////////
// CAXMeasureCtrl
/////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////
/**
 * 	���󥹥ȥ饯��
 * 
 * 	@param iMode	X:MEASUREX/Y:MEASUREY 
 * 	@param iMargin	����(����)�ީ`����
 * 	@param bAdjust	�軭�I���Ϥ߳����ʤ��褦�ˡ�FALSE:�{�����ʤ�/TRUE:�{������
 */
CAXMeasureCtrl::CAXMeasureCtrl( int iMode /*= MEASUREX*/, int iMargin /*= 0*/ ,BOOL bAdjust /*= TRUE*/)
	: m_spinSize( 0, 0 ) , CAXMeasureStyle( iMode , bAdjust)
{
	// ����(����)�ީ`����
	m_iMargin = iMargin;
	// ��ʾ/�Ǳ�ʾ���ڻ�
	ShowMeasureMinMax( TRUE, TRUE );

	// Ŀʢ���g�����ڻ�
//	m_iMeasureSpan = 1;
	///< �������軭������
	m_iFontSize = -1;		

	// ���ڂ�
	SetBkColor  ( GetSysColor( COLOR_3DFACE ) );

	m_bErase = FALSE;	///< WM_ERASEBKGND�軭
	
	//SetStrColor( GetSysColor( COLOR_BTNTEXT ) );
	
	m_nKind = AXGCTRL_MEASURE;
}
///////////////////////////////////////
/**
 * 	���ԩ`���󥹥ȥ饯��
 * 		�뤨��줿CAXMeasureCtrl�򥳥ԩ`����
 * 
 * 	@param org	���ԩ`ԪCAXMeasureCtrl���饹
 */
CAXMeasureCtrl::CAXMeasureCtrl( const CAXMeasureCtrl &org )
{
	operator=(org);
}
///////////////////////////////////////
//�ǥ��ȥ饯��
CAXMeasureCtrl::~CAXMeasureCtrl()
{
	DestroyWindow();
}

BEGIN_MESSAGE_MAP(CAXMeasureCtrl, CAXGDICtrl)
	//{{AFX_MSG_MAP(CAXMeasureCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAXMeasureCtrl ��å��`�� �ϥ�ɥ�
/// ���ڻ�
void CAXMeasureCtrl::PreSubclassWindow() 
{
	CAXGDICtrl::PreSubclassWindow();

	// ���ԥ󥵥����O��
	m_spinSize.cx = m_spinSize.cy = MEASURESIZE + MEASUREMARGIN;;
	
	switch( GetScaleMode() ){
	case MEASUREX:
		GetNameAXString().SetDTFormat(DT_CENTER | DT_BOTTOM );
		if(IsMeasureAdjust())	{
			//m_spinSize.cx = GetSystemMetrics( SM_CXHSCROLL );
			m_spinSize.cy = GetSystemMetrics( SM_CYHSCROLL );
		}
		break;
	case MEASUREY:
		GetNameAXString().SetDTFormat(DT_CENTER | DT_TOP );
		if(IsMeasureAdjust())	{
			m_spinSize.cx = GetSystemMetrics( SM_CXVSCROLL );
			//m_spinSize.cy = GetSystemMetrics( SM_CYVSCROLL );
		}
		break;
	}

	CRect rect;
	CWnd::GetWindowRect( rect );
	// �ީ`����֥�����ɥ�����������
	switch( GetScaleMode() ){
	case MEASUREX:	
		if( m_spinSize.cx >= m_iMargin )	{	m_iMargin = m_spinSize.cx;	}
		//else							{	m_iMargin = m_spinSize.cx ;			}
		rect.InflateRect( m_iMargin, 0 );
		break;
	case MEASUREY:
		if( m_spinSize.cy >= m_iMargin )	{	m_iMargin = m_spinSize.cy ;	}
		//else							{	m_iMargin = m_spinSize.cy ;			}
		rect.InflateRect( 0, m_iMargin );
		break;
	}
	GetParent()->ScreenToClient( rect );
	CWnd::MoveWindow( rect );
	// ���ԥ�γ��ڻ�
	CreateSpin();
	//RecalcLayoutSpin();
}
///////////////////////////////////////
/**
 * 	������ɥ�����֪ͨ.
 * 
 * 	@param lpCreateStruct	���ɤ���� CWnd ���֥������ȤˤĤ��Ƥ����
 * 	@return					TRUE:0 FALSE:-1
 */
int CAXMeasureCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// ���ԥ�γ��ڻ�
	CreateSpin();
	
	return 0;
}
/// �����軭
BOOL CAXMeasureCtrl::OnEraseBkgnd(CDC* pDC)
{
	if(m_bErase)	{		///< WM_ERASEBKGND�軭
		m_bErase = FALSE;	///< WM_ERASEBKGND�軭
		return FALSE;
	}
	return CWnd::OnEraseBkgnd( pDC );
}

/// �軭
void CAXMeasureCtrl::OnPaint() 
{
	// TODO: ����λ�ä˥�å��`�� �ϥ�ɥ��äΥ��`�ɤ�׷�Ӥ��Ƥ�������
	// �軭�å�å��`���Ȥ��� CStatic::OnPaint() ����ӳ����ƤϤ����ޤ���
	CPaintDC dc(this); // �軭�äΥǥХ��� ����ƥ�����
	//get rect size
	CRect rectItem;
	GetClientRect( &rectItem );

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
/**
 * 	���¥��ԥ�.
 * 
 * 	@param nSBCode		������`��Ҫ���ʾ��������`�� �Щ`�Υ��`�ɤ�ָ�����ޤ�
 * 	@param nPos			������`�� �ܥå����άF��λ�ä�ָ�����ޤ�
 * 	@param pScrollBar	pScrollBar �ϥ���ȥ�`��ؤΥݥ��󥿤ˤʤ�ޤ�
 */
void CAXMeasureCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if( nSBCode == SB_THUMBPOSITION ){
		//DELLswitch( pScrollBar->GetDlgCtrlID() ){
		//DELLcase IDUPSPIN: nPos = 1;	SetOffset(m_measureStyle.dDelta);			break;	// ��
		//DELLcase IDDWSPIN: nPos = -1;	SetOffset(-1.0 * m_measureStyle.dDelta);	break;	// ��
		//DELL}
		//DELLInvalidate();
		//DELLGetParent()->SendMessage( WM_VSCROLL, MAKEWPARAM(nSBCode, nPos), (LPARAM)this->m_hWnd );
		UINT nKeyParam = 0;
		switch( pScrollBar->GetDlgCtrlID() ){
		case IDUPSPIN: nKeyParam = AMS_OFFSET_UP;		break;	// ��
		case IDDWSPIN: nKeyParam = AMS_OFFSET_DOWN;		break;	// ��
		default:	return;
		}
		if(GetKeyState(VK_SHIFT) & 0x8000)	{//Shift key
			if(nKeyParam == AMS_OFFSET_UP)			{	nKeyParam = AMS_RANGE_UP;	}
			else if(nKeyParam == AMS_OFFSET_DOWN)	{	nKeyParam = AMS_RANGE_DOWN;	}
		}	
		NotifyToParent( AXGCN_CHANGE_SCALE, NULL, nKeyParam );
	}
}
///////////////////////////////////////
/**
 * 	���ҥ��ԥ�.
 * 
 * 	@param nSBCode		������`��Ҫ���ʾ��������`�� �Щ`�Υ��`�ɤ�ָ�����ޤ�
 * 	@param nPos			������`�� �ܥå����άF��λ�ä�ָ�����ޤ�
 * 	@param pScrollBar	pScrollBar �ϥ���ȥ�`��ؤΥݥ��󥿤ˤʤ�ޤ�
 */
void CAXMeasureCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if( nSBCode == SB_THUMBPOSITION ){
		//DELLswitch( pScrollBar->GetDlgCtrlID() ){
		//DELLcase IDUPSPIN: nPos = 1;	SetOffset(m_measureStyle.dDelta);			break;	// ��
		//DELLcase IDDWSPIN: nPos = -1;	SetOffset(-1.0 * m_measureStyle.dDelta);	break;	// ��
		//DELL}
		//DELLInvalidate();
		//DELLGetParent()->SendMessage( WM_HSCROLL, MAKEWPARAM(nSBCode, nPos), (LPARAM)this->m_hWnd );
		UINT nKeyParam = 0;
		switch( pScrollBar->GetDlgCtrlID() ){
		case IDUPSPIN: nKeyParam = AMS_OFFSET_UP;		break;	// ��
		case IDDWSPIN: nKeyParam = AMS_OFFSET_DOWN;		break;	// ��
		default:	return;
		}
		if(GetKeyState(VK_SHIFT) & 0x8000)	{//Shift key
			if(nKeyParam == AMS_OFFSET_UP)			{	nKeyParam = AMS_RANGE_UP;	}
			else if(nKeyParam == AMS_OFFSET_DOWN)	{	nKeyParam = AMS_RANGE_DOWN;	}
		}	
		NotifyToParent( AXGCN_CHANGE_SCALE, NULL, nKeyParam );
	}
}
///////////////////////////////////////
/// �ޥ�����ܥ���Ѻ�¤Εr�Υ�å��`���ϥ�ɥ�
void CAXMeasureCtrl::OnLButtonDown( UINT nFlags, CPoint point )
{
	if( GetSafeHwnd() && IsEnableActivate())	{
		CRect measureRect;
		GetClientRect( measureRect );
		if(PtInRect( measureRect, point))	{
			if((GetFocus() != this))	{	this->SetFocus();	}
		}
	}

	CWnd::OnLButtonDown(nFlags, point);
}
///////////////////////////////////////
/// �ޥ�����ܥ���Ѻ�¤Εr�Υ�å��`���ϥ�ɥ�
void CAXMeasureCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	if( GetSafeHwnd() )	{
		//if((GetFocus() != this))	{	this->SetFocus();	}
	}

	CWnd::OnRButtonDown(nFlags, point);
}
///////////////////////////////////////
//Active�ʥ����ƥ�������롣
BOOL CAXMeasureCtrl::OnChangeActive( AXGCNOTIFY *pNotifyMsg )
{
	m_activeInfo = pNotifyMsg->activeInfo;	///< Active״�B�����
	Redraw();
	return TRUE;
}
///////////////////////////////////////
//Active�ʥ����ƥ�Υ�������������롣
BOOL CAXMeasureCtrl::OnChangeStyle( AXGCNOTIFY *pNotifyMsg )
{
	///< 0:���x�k/1:ȫ��/2:�ǩ`��/3:���`����/4:���ꥢ���`����
	if(m_activeInfo.nActive == AXGCTRLACT_DATA)	{
	}

	return FALSE;
}
///////////////////////////////////////
//Active�ʥ����ƥ�Υ����`��������롣
BOOL CAXMeasureCtrl::OnChangeScale( AXGCNOTIFY *pNotifyMsg )
{
	//Scale Change type
	switch(pNotifyMsg->nKeyParam)	{
	case AMS_RANGE_UP:		//Delta�֥�󥸒���
		SetScale(GetMin() - GetScaleRangeDelta(), GetMax() + GetScaleRangeDelta());
		if(IsEnableDivDelta())	{	m_measureStyle.dDelta += 2.0;	}
		Redraw();
		return TRUE;
	case AMS_RANGE_DOWN:	//Delta�֥�󥸿sС
		SetScale(GetMin() + GetScaleRangeDelta(), GetMax() - GetScaleRangeDelta());
		if(IsEnableDivDelta())	{	m_measureStyle.dDelta -= 2.0;	}
		Redraw();
		return TRUE;
	case AMS_OFFSET_UP:		//+Delta���ե��å�
		SetOffset(GetScaleRangeDelta());
		Redraw();
		return TRUE;
	case AMS_OFFSET_DOWN:	//-Delta���ե��å�
		SetOffset(-1.0 * GetScaleRangeDelta());
		Redraw();
		return TRUE;
	default:
		break;
	}
	return FALSE;
}
///////////////////////////////////////
/**
 * 	CAXMeasureCtrl�Υ�`�ɉ��
 * 
 * 	@param iMode	X:MEASUREX/Y:MEASUREY 
 * 	@param iMargin	����(����)�ީ`����
 * 	@param bAdjust	�軭�I���Ϥ߳����ʤ��褦�ˡ�FALSE:�{�����ʤ�/TRUE:�{������
 */
void CAXMeasureCtrl::SetMode(int iMode /*= MEASUREX*/, int iMargin /*= 0*/, BOOL bAdjust /*= TRUE*/)
{	
//	if(!this->GetSafeHwnd())	{
	//	TRACE("Window�����ɤ���ǰ�ˤ��Ǥ�\n");
	//	return;
//	}
	SetScaleMode( iMode );/*m_iMode = iMode;*/	
	m_iMargin = iMargin;
	SetMeasureAdjust(bAdjust);
}
///////////////////////////////////////
/**
 * 	MoveWindow�Υ�åץ��饹.
 * 		����������r�˥��ԥ󥵥����򿼑]�����˥�åԥ󥰤��ޤ�
 * 
 * 	@param x		���x���¤���λ�ä�ָ�����ޤ���
 * 	@param y		���x���¤���λ�ä�ָ�����ޤ���
 * 	@param nWidth	�¤�������ָ�����ޤ���
 * 	@param nHeight	�¤����ߤ���ָ�����ޤ���
 * 	@param bRepaint	���軭���뤫�ɤ�����ָ�����ޤ�
 */
void CAXMeasureCtrl::MoveWindow( int x, int y, int nWidth, int nHeight, BOOL bRepaint /*= TRUE*/ )
{
	CRect rect( CPoint( x, y ), CSize( nWidth, nHeight ) );
	MoveWindow( &rect, bRepaint );
}
///////////////////////////////////////
/**
 * 	MoveWindow�Υ�åץ��饹.
 * 		����������r�˥��ԥ󥵥����򿼑]�����˥�åԥ󥰤��ޤ�
 * 
 * 	@param lpRect	�¤�����������λ�ä�ָ������ CRect ���֥������Ȥޤ��� RECT �������ָ�����ޤ�
 * 	@param bRepaint	���軭���뤫�ɤ�����ָ�����ޤ�
 */
void CAXMeasureCtrl::MoveWindow( LPCRECT lpRect, BOOL bRepaint /*= TRUE*/ )
{
	CRect rect = *lpRect;
	CalcRect( rect );
	CWnd::MoveWindow( &rect, bRepaint );
	RecalcLayoutSpin();
}
///////////////////////////////////////
/**
 * 	SetWindowPos�Υ�åץ��饹.
 * 		����������r�˥��ԥ󥵥����򿼑]�����˥�åԥ󥰤��ޤ�
 * 
 * 	@param pWndInsertAfter	Z 혤Ǥ��� CWnd ���֥������Ȥ��ǰ�����ä���� CWnd ���֥������Ȥ��R�e���ޤ���
 * 	@param x				������ɥ����¤������x��λ�ä�ָ�����ޤ���
 * 	@param y				������ɥ����¤������x��λ�ä�ָ�����ޤ���
 * 	@param cx				������ɥ����¤�������ָ�����ޤ���
 * 	@param cy				������ɥ����¤����ߤ���ָ�����ޤ���
 * 	@param nFlags			��������λ�äΉ���r�Υ��ץ�����ָ�����ޤ���
 * 	@return					TRUE:�ɹ� FALSE:ʧ��
 */
BOOL CAXMeasureCtrl::SetWindowPos( const CWnd* pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags )
{
	CRect rect( CPoint( x, y ), CSize( cx, cy ) );
	CalcRect( rect );
	BOOL bRet = CWnd::SetWindowPos( pWndInsertAfter, rect.left, rect.top, rect.Width(), rect.Height(), nFlags );
	RecalcLayoutSpin();
	return bRet;
}
///////////////////////////////////////
/**
 * 	GetClientRect�Υ�åץ��饹.
 * 		������ȡ�Õr�˥��ԥ󥵥����򿼑]�����˥�åԥ󥰤��ޤ�
 * 
 * 	@param lpRect	���饤��������ˤ��ܤ�ȡ��RECT������
 */
void CAXMeasureCtrl::GetClientRect(LPRECT lpRect)
{
	CRect rect;
	CWnd::GetClientRect( rect );
	SubcalcRect( rect );
	*lpRect = rect;
}
///////////////////////////////////////
/**
 * 	GetWindowRect�Υ�åץ��饹.
 * 		������ȡ�Õr�˥��ԥ󥵥����򿼑]�����˥�åԥ󥰤��ޤ�
 * 
 * 	@param lpRect	������ɥ����ˤ��ܤ�ȡ��RECT������
 */
void CAXMeasureCtrl::GetWindowRect(LPRECT lpRect)
{
	CRect rect;
	CWnd::GetWindowRect( rect );
	SubcalcRect( rect );
	*lpRect = rect;
}
/////////////////////////////////////////////////////////////////////////////
/// ���ԥ���ڻ�
void CAXMeasureCtrl::CreateSpin()
{
#ifndef _AFXDLL//???
	if( _afxThreadState.GetData()->m_pWndInit == this ) return;
#endif
	switch( GetScaleMode() ){
	case MEASUREX:
		m_spinCtrl[0].Create( UDS_HORZ, CRect( 0, 0, m_spinSize.cx, m_spinSize.cy ), this, IDUPSPIN );
		m_spinCtrl[1].Create( UDS_HORZ, CRect( 0, 0, m_spinSize.cx, m_spinSize.cy ), this, IDDWSPIN );
		break;
	case MEASUREY:
		m_spinCtrl[0].Create( 0, CRect( 0, 0, m_spinSize.cx, m_spinSize.cy ), this, IDUPSPIN );
		m_spinCtrl[1].Create( 0, CRect( 0, 0, m_spinSize.cx, m_spinSize.cy ), this, IDDWSPIN );
		break;
	}

	RecalcLayoutSpin();
}
///////////////////////////////////////
/**
 * 	���ԥ�Υ������{��.
 * 		�F�ڤΥ��饤������I�򤫤饹�ԥ��������λ�ä��{�����ޤ���
 */
void CAXMeasureCtrl::RecalcLayoutSpin()
{
	CRect rect;
	CWnd::GetClientRect( rect );
	GetClientRect( rect );
	switch( GetScaleMode() ){
	case MEASUREX:	rect.InflateRect( m_spinSize.cx, 0 );	break;
	case MEASUREY:	rect.InflateRect( 0, m_spinSize.cy );	break;
	}

	//TRACE("RecalcLayoutSpin: Top:%d,Left:%d,Bottom:%d,Right:%d\n",rect.top,rect.left,rect.bottom,rect.right);

	// ��`�ɤ��Ȥ˳��ڂ�Ӌ��
	CRect rectUpSpin = rect, rectDwSpin = rect;
	switch( GetScaleMode() ){	
	case MEASUREX:			// Ŀʢ��X
		rectUpSpin.left   = rectUpSpin.right - m_spinSize.cx * 2;
		rectUpSpin.bottom = rectUpSpin.top   + m_spinSize.cy;
		rectDwSpin.right  = rectDwSpin.left  + m_spinSize.cx * 2;
		rectDwSpin.bottom = rectDwSpin.top   + m_spinSize.cy;
		break;
	case MEASUREY:			// Ŀʢ��Y
		rectUpSpin.left   = rectUpSpin.right - m_spinSize.cx;
		rectUpSpin.bottom = rectUpSpin.top   + m_spinSize.cy * 2;
		rectDwSpin.top    = rectDwSpin.bottom- m_spinSize.cy * 2;
		rectDwSpin.left   = rectDwSpin.right - m_spinSize.cx;
		break;
	default: return;
	}
	if( IsWindow( m_spinCtrl[0].m_hWnd ) ) m_spinCtrl[0].MoveWindow( rectUpSpin );
	if( IsWindow( m_spinCtrl[1].m_hWnd ) ) m_spinCtrl[1].MoveWindow( rectDwSpin );
}
///////////////////////////////////////
/**
 * 	������Ӌ��.
 * 		�뤨��줿RECT�򥹥ԥ󥵥���/�ީ`���󥵥����򿼑]�����������ˉ�����ޤ���
 * 
 * 	@param rect		Ԫ�Υ�����
 */
void CAXMeasureCtrl::CalcRect( CRect &rect )
{
	CSize spinSize( 0, 0 );
	int iMargin = m_iMargin;
	if( IsShowSpin() ) {	spinSize = m_spinSize;	}

	switch( GetScaleMode() ){
	case MEASUREX:
		if(spinSize.cx > m_iMargin)	{	iMargin = spinSize.cx;	}
		//rect.InflateRect( spinSize.cx, 0 );
		rect.InflateRect( iMargin, 0 );
		break;
	case MEASUREY:
		if(spinSize.cy > m_iMargin)	{	iMargin = spinSize.cy;	}
		//rect.InflateRect( 0, spinSize.cy );
		rect.InflateRect( 0, iMargin );
		break;
	}
}
///////////////////////////////////////
/**
 * 	������Ӌ��.
 * 		�뤨��줿RECT���饹�ԥ󥵥���/�ީ`���󥵥������������������ˉ�����ޤ���
 * 
 * 	@param rect		Ԫ�Υ�����
 */
void CAXMeasureCtrl::SubcalcRect( CRect &rect )
{
	CSize spinSize( 0, 0 );
	int iMargin = m_iMargin;
	if( IsShowSpin() ) {	spinSize = m_spinSize;	}

	switch( GetScaleMode() ){
	case MEASUREX:
		if(spinSize.cx > m_iMargin)	{	iMargin = spinSize.cx;	}
		rect.DeflateRect( iMargin, 0 );
		//rect.DeflateRect( spinSize.cx, 0 );
		break;
	case MEASUREY:
		if(spinSize.cy > m_iMargin)	{	iMargin = spinSize.cy;	}
		rect.DeflateRect( 0, iMargin );
		//rect.DeflateRect( 0, spinSize.cy );
		break;
	}
}
///////////////////////////////////////
/**
 * 	Ŀʢ����軭����
 * 
 * 	@param pDC			�軭��ʹ�ä���ǥХ�������ƥ�����
 * 	@param rect			Ŀʢ����軭���빠��
 */
void CAXMeasureCtrl::DrawDC( CDC *pDC, CRect rect )
{
	// ����ʾ���ꥢ
	CRect scaleRect  = rect;		// Ŀʢ���S��ʾ���ꥢ
	CRect nameRect   = rect;		// Ŀʢ������ʾ���ꥢ
	
	int iMeasureSize = MEASURESIZE;//
	if(pDC->IsPrinting())	{
		iMeasureSize = MulDiv(MEASURESIZE, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	}
	// Ŀʢ���S��ʾ���ꥢ��ȡ��
	switch( GetScaleMode() ){
	case MEASUREX: scaleRect.bottom = scaleRect.top  + iMeasureSize;	break;
	case MEASUREY: scaleRect.left   = scaleRect.right- iMeasureSize;	break;
	default: return;
	}

	int iMeasureMargin = MEASUREMARGIN;//
	if(pDC->IsPrinting())	{
		iMeasureMargin = MulDiv( MEASUREMARGIN, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	}
	// Ŀʢ��/Ŀʢ������ʾ���ꥢ��ȡ��
	if( IsShowScale())	{
		nameRect.SubtractRect( rect, scaleRect );
		switch( GetScaleMode() ){
		case MEASUREX:	nameRect.top += iMeasureMargin;		break;
		case MEASUREY:	nameRect.right -= iMeasureMargin;	break;
		default: return;
		}
	}
	// Ŀʢ��/Ŀʢ������ʾ���ꥢ�Υީ`����֤α������軭���롣
	if((!(pDC->IsPrinting())) && (!IsMeasureAdjust()) )	{//WMPINAT�Εr
		int iDrawResize = m_iMargin;//�軭�I����������
		//if(m_iMargin == 0 IsShowSpin())	{
		//	switch( GetScaleMode() ){
		//	case MEASUREX: iDrawResize += m_spinSize.cx;	break;
		//	case MEASUREY: iDrawResize += m_spinSize.cy;	break;
		//	}
		//}
		// �ީ`����ֿsС
		switch( GetScaleMode() ){
		case MEASUREX: nameRect.InflateRect( iDrawResize, 0 );	break;
		case MEASUREY: nameRect.InflateRect( 0, iDrawResize );	break;
		}
		// �������軭
		pDC->FillSolidRect( nameRect, GetBkColor() );
		// �ީ`����ֿsС
		switch( GetScaleMode() ){
		case MEASUREX: nameRect.DeflateRect( iDrawResize, 0 );	break;
		case MEASUREY: nameRect.DeflateRect( 0, iDrawResize );	break;
		}
	}

	// ������`�ɤΉ��
	int iBkMode = pDC->SetBkMode( TRANSPARENT );

	// Ŀʢ���S���軭
	if( IsShowScale())	{
		// �ڥ������
		CPen pen;
		pen.CreatePen( PS_SOLID, 0, (IsMonochrome() ? RGB(0,0,0) : GetScaleColor()) );
		// �ڥ���x�k
		CPen *pOldPen = pDC->SelectObject( &pen );
		//�饤��򤭤줤��������褦���軭�I���С��������
		scaleRect.bottom -= 1;
		scaleRect.right -= 1;
		DrawScale( pDC, scaleRect );
		// �ڥ�����
		pDC->SelectObject( pOldPen );
		// �ڥ���Ɨ�
		pen.DeleteObject();
	}
	// �����Ф��軭
	DrawMeasureMaxString( pDC, nameRect, IsMonochrome() );
	DrawMeasureMinString( pDC, nameRect, IsMonochrome() );

	if( IsShowMeasureDelta() || IsShowMeasureMin() || IsShowMeasureMax() )	{
		// Ŀʢ����軭
		DrawMeasure( pDC, nameRect );
	}

	// Ŀʢ�������軭
	DrawMeasureName( pDC, nameRect, GetFontSize() );//, strMeasureName );

	// ������`�ɤ����
	pDC->SetBkMode( iBkMode );
}
///////////////////////////////////////
/**
 * 	���ԥ�α�ʾ/�Ǳ�ʾ�O��.
 * 		���ԥ�α�ʾ/�Ǳ�ʾ���Ф��椨��
 * 
 * 	@param bShow	TRUE:��ʾ FALSE:�Ǳ�ʾ
 * 	@return			ǰ�ؤα�ʾ״�B
 */
BOOL CAXMeasureCtrl::ShowSpin( BOOL bShow )
{
	BOOL bRtn = FALSE;
	bRtn  = m_spinCtrl[0].ShowWindow( bShow ? SW_SHOW: SW_HIDE );
	bRtn |= m_spinCtrl[1].ShowWindow( bShow ? SW_SHOW: SW_HIDE );
	
	// ������ɥ����������
	CRect rect;
	if( !bRtn && bShow ){			// �Ǳ�ʾ����ʾ
		CWnd::GetWindowRect( rect );
		//TRACE("ShowSpin ON1: Top:%d,Left:%d,Bottom:%d,Right:%d\n",rect.top,rect.left,rect.bottom,rect.right);
		GetParent()->ScreenToClient( rect );
		//int iMargin = m_iMargin;
		switch( GetScaleMode() ){
		case MEASUREX:
			if( m_spinSize.cx > m_iMargin )	{	rect.InflateRect( m_spinSize.cx, 0 );	}
		//	else								{	rect.InflateRect( m_iMargin, 0 );		}
			break;
		case MEASUREY:
			if( m_spinSize.cy > m_iMargin )	{	rect.InflateRect( 0, m_spinSize.cy );	}
		//	else								{	rect.InflateRect( 0, m_iMargin );		}
			break;
		}
		//CalcRect( rect );
		//TRACE("ShowSpin ON1: Top:%d,Left:%d,Bottom:%d,Right:%d\n",rect.top,rect.left,rect.bottom,rect.right);
		//MoveWindow( rect );
		CWnd::MoveWindow( rect );
		CWnd::GetWindowRect( rect );
		GetParent()->ScreenToClient( rect );
		
		//TRACE("ShowSpin ON2: Top:%d,Left:%d,Bottom:%d,Right:%d\n",rect.top,rect.left,rect.bottom,rect.right);
		RecalcLayoutSpin();
		//Redraw();
	} else if( bRtn && !bShow ){	// ��ʾ���Ǳ�ʾ
		m_bErase = TRUE;	///< WM_ERASEBKGND�軭
		CWnd::GetWindowRect( rect );
		GetParent()->ScreenToClient( rect );
		//CWnd::MoveWindow( rect );

		GetParent()->InvalidateRect(rect);
		//GetParent()->
		
		//RedrawWindow(rect,NULL,RDW_INVALIDATE | RDW_ERASE );
		//Redraw();
	
		switch( GetScaleMode() ){
		case MEASUREX:
			if( m_spinSize.cx > m_iMargin )	{	rect.DeflateRect( m_spinSize.cx, 0 );	}
		//	else								{	rect.DeflateRect( m_iMargin, 0 );		}
			break;
		case MEASUREY:
			if( m_spinSize.cy > m_iMargin )	{	rect.DeflateRect( 0, m_spinSize.cy );	}
		//	else								{	rect.DeflateRect( 0, m_iMargin );		}
			break;
		}
		
		//TRACE("ShowSpin OFF1: Top:%d,Left:%d,Bottom:%d,Right:%d\n",rect.top,rect.left,rect.bottom,rect.right);
		//GetWindowRect( rect );
		

		//GetParent()->ScreenToClient( rect );
	//	TRACE("ShowSpin OFF2: Top:%d,Left:%d,Bottom:%d,Right:%d\n",rect.top,rect.left,rect.bottom,rect.right);
		
		CWnd::MoveWindow( rect );
		
	}

	

	return bRtn;
}
///////////////////////////////////////
/**
 * 	���ԥ�α�ʾ/�Ǳ�ʾȡ��.
 * 		���ԥ�α�ʾ/�Ǳ�ʾ��ȡ�ä���.
 * 
 * 	@return			TRUE:��ʾ FALSE:�Ǳ�ʾ
 */
BOOL CAXMeasureCtrl::IsShowSpin() const
{
	if(m_spinCtrl[0].GetSafeHwnd())	{
		if(( m_spinCtrl[0].GetStyle() & WS_VISIBLE ) 
			|| ( m_spinCtrl[1].GetStyle() & WS_VISIBLE ))	{
			return TRUE;
		}
	}
	return FALSE;
}
///////////////////////////////////////
/**
 * 	�軭ǰ�I��
 * 
 * 	@param pDC			�軭��ʹ�ä���ǥХ�������ƥ�����
 * 	@param rect			�軭���빠��
 */
void CAXMeasureCtrl::BeginPaintDC( CDC *pDC, const CRect &rect )
{
}
///////////////////////////////////////
/**
 *	�軭��I��
 * 
 * 	@param pDC			�軭��ʹ�ä���ǥХ�������ƥ�����
 * 	@param rect			�軭���빠��
 */
void CAXMeasureCtrl::EndPaintDC( CDC *pDC, const CRect &rect )
{
}
///////////////////////////////////////
/**
 * 	Active״�B���軭.
 * 		Active״�B���ʾ����
 * 
 * 	@param pDC		�軭����ǥХ�������ƥ����ȤΥݥ���
 * 	@param rect		�軭�I��ι���
 */
void CAXMeasureCtrl::DrawActiveFrame( CDC *pDC, const CRect &rect, int size )
{
	CRect rectItem = rect;

/*	int iDrawResize = 0;//�軭�I����������
	iDrawResize = m_iMargin;
	if(IsShowSpin())	{
		switch( GetScaleMode() ){
		case MEASUREX: iDrawResize += m_spinSize.cx;	break;
		case MEASUREY: iDrawResize += m_spinSize.cy;	break;
		}
	}
	if( iDrawResize != 0 )	{
		// �ީ`����ֿsС
		switch( GetScaleMode() ){
		case MEASUREX: rectItem.DeflateRect( iDrawResize, 0 );	break;
		case MEASUREY: rectItem.DeflateRect( 0, iDrawResize );	break;
		}
	}*/
	if(IsShowSpin())	{
		switch( GetScaleMode() ){
		case MEASUREX: rectItem.InflateRect(m_spinSize.cx,0);	break;
		case MEASUREY: rectItem.InflateRect(0,m_spinSize.cy);	break;
		}
	}
	CAXGDICtrl::DrawActiveFrame( pDC, rectItem );
}