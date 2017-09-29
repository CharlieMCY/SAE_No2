// AXMasureCtrl.cpp : インプリメンテーション ファイル
//
/********************************************************
// クラスのインプリメンテーション
// CAXGDIScaleData		:スケールデータ保持クラス
// CAXMeasureStyle		:目盛り描画クラス
// CAXMeasureSpin		:目盛り用スピンボタンクラス
// CAXMeasureCtrl		:目盛り描画Wndクラス
//											by YOTSUTSU
//	* History	:	date:2005,24,Mar.	新規作成
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
 * 	スケール情報から描画スケールの原点を求める.
 * 
 * 	@param	scale		スケール情報
 *	@return 描画スケールの原点
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
 * 	スケール情報から描画スケールのレンジを求める.
 * 
 * 	@param	scale		スケール情報
 *	@return 描画スケールのレンジ
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
 * 	スケール情報から描画スケールのレンジを求める.
 * 
 * 	@param	scale		スケール情報
 *	@return 描画スケールのレンジ
 */
double CAXGDIScaleData::GetDrawMax( const CAXGDIScaleData &scale )
{
	return (GetDrawRange(scale) + GetDrawOrg(scale));
}
///////////////////////////////////////
/**
 * 	スケール情報とXのデータから描画する座標ポイントXを求める.
 *		但し、座標系原点は left, topであること
 * 	@param	dXdata		Xの値
 * 	@param	scale		スケール情報
 * 	@param	width		描画の幅
 *	@return Xの描画座標ポイント
 */
int CAXGDIScaleData::Data2PointX( double dXdata, const CAXGDIScaleData &scale ,int width )
{
	double dXOrg = GetDrawOrg(scale);
	double dXRange = GetDrawRange(scale);
	double dXp;
	if(scale.m_bLog)	{
		//dXOrg = log10( scale.m_scaleInfo.dOrg );
		//dXRange = log10(scale.GetMax()) - dXOrg;
		//エラー防止
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
 * 	スケール情報とYのデータから描画する座標ポイントYを求める.
 *		但し、座標系原点は left, topであること
 * 	@param	dYdata		Yの値
 * 	@param	scale		スケール情報
 * 	@param	height		描画の高さ
 *	@return Yの描画座標ポイント
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
 * 	スケール情報と座標ポイントXからXのデータ値を求める.
 *		但し、座標系原点は left, topであること
 * 	@param	iXdata		Xの値	( point.x - rect.left )
 * 	@param	scale		スケール情報
 * 	@param	width		描画の幅
 *	@return Xのデータ値
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
 * 	スケール情報と座標ポイントYからYのデータ値を求める.
 *		但し、座標系原点は left, topであること
 * 	@param	dXdata		Yの値	( point.y - rect.top )
 * 	@param	scale		スケール情報
 * 	@param	height		描画の高さ
 *	@return Yのデータ値
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
 * 	スケール値を設定する.
 *
 * 	@param	dblMin		最小値
 * 	@param	dblMax		最大値
 *	@return スケール情報
 */
const GDISCALEINFO & CAXGDIScaleData::SetScale( double dblMin, double dblMax )
{
	GDISCALEINFO scale;
	// 正規化してスケールを設定
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
 * 	スケール値を設定する.（対数スケール）
 *
 * 	@param	dblMin		最小値
 * 	@param	dblMax		最大値
 * 	@param	bScaleAuto	対数オートスケール	TRUE:有効/FALSE:無効
 *	@return スケール情報
 */
const GDISCALEINFO & CAXGDIScaleData::SetLogScale(double dblMin, double dblMax, BOOL bScaleAuto )
{
	if( dblMin < 0.0 && dblMax < 0.0 && (dblMin == dblMax))	{//Logには出来ません。
		m_bLog = FALSE;
		return GetScaleInfo();
	}
	double dblDataMax;
	// 正規化してスケールを設定
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
 * 	対数スケールの有効、無効を変更する.
 *
 * 	@param	bLog		対数スケール		TRUE:有効/FALSE:無効
 * 	@param	bScaleAuto	対数オートスケール	TRUE:有効/FALSE:無効
 *	@return スケール情報
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

#define	MEASURE_LINEMAX		200		// 目盛りのMAX本数
#define	MEASURE_DETAILMAX	20		// 詳細目盛りのMAX本数
//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////
/**
 * 	コンストラクタ.
 * 
 * 	@param iMode	X:MEASUREX/Y:MEASUREY 
 * 	@param bAdjust	描画領域をはみ出さないように　FALSE:調整しない/TRUE:調整する
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

	///< 名称の表示文字列
	m_axstrName.SetDTFormat((DT_VCENTER | DT_CENTER));		///< 名称の表示文字列
	m_axstrName.SetString( _T("") );						///< 目盛り名称
	m_axstrName.SetStrColor(GetSysColor( COLOR_BTNTEXT ));
	///< Up側の表示文字列
	m_axstrMaxSide.SetDTFormat((DT_VCENTER | DT_SINGLELINE | DT_CENTER));
	///< Down側の表示文字列
	m_axstrMinSide.SetDTFormat((DT_VCENTER | DT_SINGLELINE | DT_CENTER));	
	
	//m_strFormat;		///< 目盛り値の表示書式
	Format( "%.0f" );
	
	//m_strUnit;						///< 単位の表示文字列
//	m_strUnit = _T("");					///< 目盛り名の単位
//	m_strNameFormat = _T("%s %s");		///< 目盛り名称の書式

	m_measureStyle.dwMsStyle = 0;
	//CAXGDIScaleData::SetScale(0.0,100);
	SetScaleMode( iMode );
	

	m_measureStyle.dDelta = 10.0;			///< 目盛り間隔(データ値指定)
	m_measureStyle.dDetailDelta = 2.0;		///< 詳細目盛り間隔(データ値指定)
	m_measureStyle.dOrgDelta = 0.0;			///< 目盛り間隔の原点(データ値指定)
	m_measureStyle.sDetailRatio = 75;		///< 詳細目盛り長さ比率指定[%]
	m_measureStyle.sFontSize = -1;			///< 目盛りの値表示のフォントサイズ
	m_measureStyle.lAngle = 0;				///< 目盛りの文字角度
	m_measureStyle.scaleColor = GetSysColor( COLOR_BTNTEXT );			///< スケール文字色
	m_measureStyle.measureColor = GetSysColor( COLOR_BTNTEXT );	///< 目盛りの値文字色
	
	EnableDivDelta(TRUE);
	// 文字角度
	switch( GetScaleMode() ){
	case MEASUREX: m_measureStyle.lAngle = 0;	break;
	case MEASUREY: m_measureStyle.lAngle = 900;	break;
	}

	// 表示/非表示初期化
	ShowScale( TRUE, TRUE );
//	ShowScale(FALSE);
	///< 最小値/最大値
	// 目盛り軸
	ShowScaleMinMax( TRUE, TRUE );	
	// 目盛り値
	ShowMeasureMinMax( FALSE, FALSE );
	//目盛りのタイプ
	SetScaleType(AMS_INSIDE);
//	SetScaleType(AMS_OUTSIDE);
//	SetScaleType(AMS_SIDEBOTH);
//	SetLogMode(FALSE);
//	SetScaleDelta(10,2);
	
	ShowMeasureDelta( TRUE );
	ShowLogZero(FALSE);
	SetLogMode(FALSE);

	// 目盛りの端の調整
	SetMeasureAdjust(bAdjust);
	
}
///////////////////////////////////////
//コピーコンストラクタ
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
 * 	目盛り設定.
 * 		目盛りの最小値/最大値/目盛りを設定する。
 * 
 * 	@param dMin			最小値
 * 	@param dMax			最大値
 * 	@param dDelta		目盛り間隔(データ値指定) 1目盛りの単位
 * 	@param dDetailDelta	詳細目盛り間隔(データ値指定) 1目盛りの単位
 */
void CAXMeasureStyle::SetScale( double dMin, double dMax, double dDelta /*= -1.0*/, double dDetailDelta /*= -1*/ )
{
	CAXGDIScaleData::SetScale( dMin, dMax );
	if( IsEnableDivDelta() )	{///< 目盛りの分割指定の有効/無効
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
 * 	目盛り軸の描画.
 * 		目盛りの軸を描画する
 * 
 * 	@param pDC		描画に使用するデバイスコンテキスト
 * 	@param rect		目盛りを描画する範囲
 */
void CAXMeasureStyle::DrawScale( CDC *pDC, const CRect &rect )
{
	if(!IsShowScale())	{	return;	}
	
	if(IsLogMode())	{
		DrawLogScale( pDC, rect, GetScaleMode(), GetScaleType(), GetMin(), GetMax(), ( IsShowDetailScale() ? GetScaleDetailRatio() : 0 ) );
	}	else	{
		if(IsEnableDivDelta())	{//分割指定
			DrawDivScale( pDC, rect, GetScaleMode(), GetScaleType(), GetScaleDelta(), ( IsShowDetailScale() ? GetScaleDetailDelta() : 0.0), GetScaleDetailRatio() );
		}	else	{
			double dDeltaOrg = GetMin();
			if(IsDeltaOrgEnable())	{	dDeltaOrg = GetDeltaOrg();	}
			DrawScale( pDC, rect, GetScaleMode(), GetScaleType(), GetMin(), GetMax(), dDeltaOrg, GetScaleDelta(), ( IsShowDetailScale() ? GetScaleDetailDelta() : 0.0), GetScaleDetailRatio() );//GetScaleDetailDelta() );
		}
	}
	// 目盛りを書く(X)
	if( GetScaleMode() == MEASUREX ){
		int iAxis;
		if( AMS_SIDEBOTH == GetScaleType() )	{	iAxis = int(0.5 * rect.Height() + rect.top);	}
		else if( AMS_OUTSIDE == GetScaleType() ){	iAxis = rect.top;						}
		else									{	iAxis = rect.bottom;					}
		pDC->MoveTo( rect.left, iAxis );
		pDC->LineTo( rect.right+1,iAxis );
		// 最小値
		if( IsShowScaleMin() ){
			pDC->MoveTo( rect.left,   rect.top    );
			pDC->LineTo( rect.left,   rect.bottom );
		}
		// 最大値
		if( IsShowScaleMax() ){
			pDC->MoveTo( rect.right,rect.top    );
			pDC->LineTo( rect.right,rect.bottom );			
		}
	// 目盛りを書く(Y)
	}	else if( GetScaleMode() == MEASUREY ){
		int iAxis;
		if( AMS_SIDEBOTH == GetScaleType() )	{	iAxis = int(0.5 * rect.Width()) + rect.left;	}
		else if( AMS_OUTSIDE == GetScaleType() ){	iAxis = rect.right;						}
		else									{	iAxis = rect.left;						}
		pDC->MoveTo( iAxis,rect.top );
		pDC->LineTo( iAxis,rect.bottom+1 );
		// 最小値
		if( IsShowScaleMin() ){
			pDC->MoveTo( rect.left, rect.bottom );
			pDC->LineTo( rect.right,rect.bottom );		
		}
		// 最大値
		if( IsShowScaleMax() ){
			pDC->MoveTo( rect.left, rect.top );
			pDC->LineTo( rect.right,rect.top );
		}
	}
}
///////////////////////////////////////
/**
 * 	目盛り軸の描画.
 * 		目盛りの軸を描画する
 * 
 * 	@param pDC		描画に使用するデバイスコンテキスト
 * 	@param rect		目盛りを描画する範囲
 * 	@param iMode	X:MEASUREX/Y:MEASUREY 
 * 	@param iType	目盛りの向き設定(AMS_INSIDE:内側/AMS_OUTSIDE:外側/AMS_SIDEBOTH:交差)
 * 	@param dMin		目盛りの最小値
 * 	@param dMax		目盛りの最大値
 * 	@param dDelta	目盛りの間隔
 * 	@param dDelta	詳細目盛りの間隔
 */
void CAXMeasureStyle::DrawScale( CDC *pDC, const CRect &rect, int iMode, int iType, double dMin, double dMax, double dOrg, double dDelta ,double dDetailDelta, long lDetailRatio)
{
	// 範囲を計算
	double dRange  = dMax - dMin;
	double dOffset = 0.0;
	if( dDelta > 0.0 && dRange > 0.0 && (dMin != dOrg) ){	//
		dOffset = -1.0 * (((int)(fabs(dMin) / dDelta + 1.0 )) * dDelta - fabs(dMin)) ;
	}
	// 描画原点設定
	CPoint oldOrg = pDC->SetViewportOrg( rect.left, rect.top );

	// 目盛りを書く(X)
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
	// 目盛りを書く(Y)
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
	// 原点を戻す
	pDC->SetViewportOrg( oldOrg );
}
///////////////////////////////////////
/**
 * 	目盛り軸の描画.
 * 		目盛りの軸を描画する
 * 
 * 	@param pDC			描画に使用するデバイスコンテキスト
 * 	@param rect			目盛りを描画する範囲
 * 	@param iMode		X:MEASUREX/Y:MEASUREY 
 * 	@param iType		目盛りの向き設定(AMS_INSIDE:内側/AMS_OUTSIDE:外側/AMS_SIDEBOTH:交差)		
 * 	@param dMin			目盛りの最小値
 * 	@param dMax			目盛りの最大値
 * 	@param dDelta		目盛りの間隔
 * 	@param dDetailDelta	詳細目盛りの間隔
 */
void CAXMeasureStyle::DrawDivScale( CDC *pDC, const CRect &rect, int iMode, int iType, double dDelta, double dDetailDelta, long lDetailRatio )
{

	// 描画原点設定
	CPoint oldOrg = pDC->SetViewportOrg( rect.left, rect.top );
	int nDelta = FtoL( dDelta );
	int nDetailDelta = FtoL( dDetailDelta );
	// 目盛りを書く(X)
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
	// 目盛りを書く(Y)
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
	// 原点を戻す
	pDC->SetViewportOrg( oldOrg );

}
///////////////////////////////////////
/**
 * 	目盛り軸の描画.
 * 		目盛りの軸を描画する
 * 
 * 	@param pDC		描画に使用するデバイスコンテキスト
 * 	@param rect		目盛りを描画する範囲
 * 	@param iMode	X:MEASUREX/Y:MEASUREY 
 * 	@param iType	目盛りの向き設定(AMS_INSIDE:内側/AMS_OUTSIDE:外側/AMS_SIDEBOTH:交差)
 * 	@param dMin		目盛りの最小値
 * 	@param dMax		目盛りの最大値
 * 	@param dDelta	目盛りの間隔
 */
void CAXMeasureStyle::DrawLogScale( CDC *pDC, const CRect &rect, int iMode, int iType, double dMin, double dMax, long lDetailRatio )
{
	// 範囲を計算
	double dMinLog = log10( dMin );
	double dMaxLog = log10( dMax );
	double dRange  = dMaxLog - dMinLog;
	// 描画原点設定
	CPoint oldOrg = pDC->SetViewportOrg( rect.left, rect.top );

	if( iMode == MEASUREX ){	// 目盛りを書く(X)
		int iX;
		for( int i = 0; i < MEASURE_LINEMAX; i++ ){
			double dblDelta = dMinLog + i;
			if(dblDelta > dMaxLog )	{	break;	}
			iX = FtoL( ( dblDelta - dMinLog ) / dRange * rect.Width() );
			pDC->MoveTo( iX, 0 );
			pDC->LineTo( iX, rect.Height() );	
			if(lDetailRatio > 0)	{// 詳細
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
	} else if( iMode == MEASUREY ){// 目盛りを書く(Y)
		int iY;
		for( int i = 0; i < MEASURE_LINEMAX; i++ ){
			double dblDelta = dMinLog + i;
			if(dblDelta > dMaxLog )	{	break;	}
			iY = FtoL( ( dMaxLog - dblDelta ) / dRange * rect.Height() );
			pDC->MoveTo( 0, iY );
			pDC->LineTo( rect.Width(),iY );
			if(lDetailRatio > 0)	{// 詳細
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
	// 原点を戻す
	pDC->SetViewportOrg( oldOrg );

}
///////////////////////////////////////
/**
 * 	描画する範囲RECTから比率で描画
 * 		目盛り(最小値/最大値)を描画する
 * 
 * 	@param rect		目盛りを描画する範囲
 * 	@param iMode	X:MEASUREX/Y:MEASUREY 
 * 	@param iType	目盛りの向き設定(AMS_INSIDE:内側/AMS_OUTSIDE:外側/AMS_SIDEBOTH:交差)
 */
void CAXMeasureStyle::GetDetailRect(const CRect &rect, int iMode, int iType, long lRatio, LPRECT lpCalcRect )
{
	//(*lpCalcRect) = rect;

	long lCutLen = 0;
	if(lRatio >= 100)	{	return;	}
	if(lRatio <  0)		{	lRatio = 0;	}
	
	if( iMode == MEASUREX ){// 目盛りを書く(X)
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
	} else if( iMode == MEASUREY ){// 目盛りを書く(Y)
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
 * 	目盛り(最小値/最大値)の描画
 * 		目盛り(最小値/最大値)を描画する
 * 
 * 	@param pDC			描画に使用するデバイスコンテキスト
 * 	@param rect			目盛りを描画する範囲
 */
void CAXMeasureStyle::DrawMeasure( CDC *pDC, const CRect &rect )
{
	// フォントの作成
	LOGFONT logfont;
	pDC->GetCurrentFont()->GetLogFont( &logfont );
	logfont.lfEscapement = GetMeasureAngle();
	logfont.lfOrientation= GetMeasureAngle();

	if(GetMeasureFontSize() > 0)	{
		logfont.lfHeight = -MulDiv( GetMeasureFontSize(), pDC->GetDeviceCaps(LOGPIXELSY), 72);
	}

	CFont font;
	font.CreateFontIndirect( &logfont );

	// フォント?文字色の選択
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
	// 最小値/最大値
	if( IsShowMeasureMin() )	{
		CString strData;
		CString strFormat = GetFormat();
		int iPower = FtoL(log10( GetMin() ));
		if(IsLogMode() && (!IsShowLogZero()))	{
			if( iPower >= 0)	{	strFormat.Format( "%%.%df", 0 );				}
			else				{	strFormat.Format( "%%.%df", abs( iPower ) );	}
		}
		strData.Format( strFormat, GetMin() );
		// 目盛りを書く(X)
		if( GetScaleMode() == MEASUREX ){
			TextDraw( pDC, rect, GetScaleMode(), rect.left, rect.top, strData, (IsMeasureAdjust() ? 1 : 0));
		// 目盛りを書く(Y)
		}	else if( GetScaleMode() == MEASUREY ){
			TextDraw( pDC, rect, GetScaleMode(), rect.right, rect.bottom, strData, (IsMeasureAdjust() ? 1 : 0) );
		}
	}

	// 最小値/最大値
	if( IsShowMeasureMax() )	{
		CString strData;
		CString strFormat = GetFormat();
		int iPower = (int)(log10( GetMax() ));
		if(IsLogMode() && (!IsShowLogZero()))	{
			if( iPower >= 0)	{	strFormat.Format( "%%.%df", 0 );				}
			else				{	strFormat.Format( "%%.%df", abs( iPower ) );	}
		}
		strData.Format( strFormat, GetMax() );
		// 目盛りを書く(X)
		if( GetScaleMode() == MEASUREX ){
			TextDraw( pDC, rect, GetScaleMode(), rect.right,rect.top, strData, (IsMeasureAdjust() ? 1 : 0) );
		// 目盛りを書く(Y)
		}	else if( GetScaleMode() == MEASUREY ){
			TextDraw( pDC, rect, GetScaleMode(), rect.right, rect.top,   strData, (IsMeasureAdjust() ? 1 : 0) );
		}
	}

	// 文字色を戻す
	pDC->SetTextColor( oldColor );

	// フォントを戻す
	pDC->SelectObject( pOldFont );

	// フォントの破棄
	font.DeleteObject();
}
///////////////////////////////////////
/**
 * 	目盛りの名称の描画
 * 		目盛りの名称を描画する
 * 
 * 	@param pDC			描画に使用するデバイスコンテキスト
 * 	@param rect			目盛りを描画する範囲
 *	@param nFontSize	Font Size
 */
void CAXMeasureStyle::DrawMeasureName( CDC *pDC, const CRect &rect, int nFontSize )
{
	CString strMeasureName = GetString();
//	if(!m_strUnit.IsEmpty())	{			///< 目盛り名の単位
//		strMeasureName.Format(m_strNameFormat,GetString(),m_strUnit);
//	}

	if(strMeasureName.IsEmpty())	{	return;	}

	// フォントの作成
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

	// フォント?文字色の選択
	CFont   *pOldFont = pDC->SelectObject( &font );
	COLORREF oldColor = pDC->SetTextColor( GetStrColor() );

	// 描画文字の範囲
	CSize drawSize = pDC->GetTextExtent( strMeasureName );

	// 目盛り名描画(X)
	int iX = 0, iY = 0;
	CRect rectText = rect;
	if( GetScaleMode() == MEASUREX ){
		iX = rect.left + rect.Width() / 2 - drawSize.cx / 2;
		iY = rect.bottom - drawSize.cy;
		if( iY < rect.top ) iY = rect.top;
	// 目盛り名描画(Y)
	} else if( GetScaleMode() == MEASUREY ){
		iX = rect.left;
		iY = rect.top + rect.Height() / 2 + drawSize.cx / 2;
	}
	//pDC->TextOut( iX, iY, strMeasureName );
	GetNameAXString().TextDraw( pDC, rectText, font, strMeasureName, GetStrColor(), GetNameAXString().GetDTFormat(), logfont.lfOrientation  );

	// 文字色を戻す
	pDC->SetTextColor( oldColor );

	// フォントを戻す&破棄
	pDC->SelectObject( pOldFont );
	font.DeleteObject();
}
///////////////////////////////////////
/**
 * 	目盛りのMAX側文字列の描画
 * 		目盛りのMAX側文字列を描画する
 * 
 * 	@param pDC			描画に使用するデバイスコンテキスト
 * 	@param rect			目盛りを描画する範囲
 *	@param bMonochrome	モノクロ表示フラグ
 */
void CAXMeasureStyle::DrawMeasureMaxString( CDC *pDC, const CRect &rect, BOOL bMonochrome )
{
	if( GetMaxSideAXString().GetString().IsEmpty() )	{	return;	}
	// フォントの作成
	LOGFONT logfont;
	pDC->GetCurrentFont()->GetLogFont( &logfont );
	if( GetScaleMode() == MEASUREX ){
		logfont.lfEscapement = 0;
		logfont.lfOrientation= 0;
	}	else if( GetScaleMode() == MEASUREY ){
		logfont.lfEscapement = 900;
		logfont.lfOrientation= 900;
	}

	// フォント?文字色の選択
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
	
	// 文字色を戻す
	pDC->SetTextColor( oldColor );

	// フォントを戻す&破棄
	pDC->SelectObject( pOldFont );
	font.DeleteObject();
}
///////////////////////////////////////
/**
 * 	目盛りのMIN側文字列の描画
 * 		目盛りのMIN側文字列を描画する
 * 
 * 	@param pDC			描画に使用するデバイスコンテキスト
 * 	@param rect			目盛りを描画する範囲
 *	@param bMonochrome	モノクロ表示フラグ
 */
void CAXMeasureStyle::DrawMeasureMinString( CDC *pDC, const CRect &rect, BOOL bMonochrome )
{
	//CString strText1 = ;	///< Up側の表示文字列
	//CString strText2 = ;	///< Down側の表示文字列
	if( GetMaxSideAXString().GetString().IsEmpty() )	{	return;	}

	// フォントの作成
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

	// フォント?文字色の選択
	CFont   *pOldFont = pDC->SelectObject( &font );
	COLORREF oldColor = pDC->SetTextColor( m_axstrMinSide.GetStrColor() );
	// 描画文字の範囲
	//CSize drawSize = pDC->GetTextExtent( strText1 );
	CRect rectText = rect;
	if(GetScaleMode() == MEASUREX )	{
		rectText.right = rect.left + FtoL(rect.Width() / 2);
	}	else if(GetScaleMode() == MEASUREY )	{
		rectText.top = rect.top + FtoL(rect.Height() / 2);
	}
	//pDC->DrawText(strText2,rectText,m_axstrMinSide.GetDTFormat() );
	GetMinSideAXString().TextDraw( pDC, rectText, font, bMonochrome, logfont.lfOrientation  );

	// 文字色を戻す
	pDC->SetTextColor( oldColor );

	// フォントを戻す&破棄
	pDC->SelectObject( pOldFont );
	font.DeleteObject();
	
}
///////////////////////////////////////
/**
 * 	目盛り(最小値/最大値)の描画
 * 		目盛り(最小値/最大値)を描画する
 * 
 * 	@param pDC			描画に使用するデバイスコンテキスト
 * 	@param rect			目盛りを描画する範囲
 * 	@param iMode		X:MEASUREX/Y:MEASUREY
 * 	@param dMin			描画する最小値
 * 	@param dMax			描画する最大値
 * 	@param dOrg			描画する目盛り原点
 * 	@param dDelta		目盛り間隔(0.0基準)
 * 	@param lpszFormat	目盛りのフォーマット
 * 	@param bAdjust		描画領域をはみ出さないように　FALSE:調整しない/TRUE:調整する
 */
void CAXMeasureStyle::DrawMeasure( CDC *pDC, const CRect &rect, int iMode, double dMin, double dMax, double dOrg, double dDelta, LPCTSTR lpszFormat, BOOL bAdjust )
{
	// 範囲を計算
	double dRange  = dMax - dMin;
	double dOffset = 0.0;
	if( dDelta > 0.0 && dRange > 0.0 && (dMin != dOrg) ){	//
		dOffset = -1.0 * (((int)(fabs(dMin) / dDelta + 1.0 )) * dDelta - fabs(dMin)) ;
			//(((int)(( dMin - dOrg) / dDelta  + 1.0)) * dDelta + (dMin - dOrg));
	}
	CString strData;
	// 目盛り間隔に調整
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
 * 	目盛り(最小値/最大値)の描画
 * 		目盛り(最小値/最大値)を描画する
 * 
 * 	@param pDC			描画に使用するデバイスコンテキスト
 * 	@param rect			目盛りを描画する範囲
 * 	@param iMode		X:MEASUREX/Y:MEASUREY
 * 	@param dMin			描画する最小値
 * 	@param dMax			描画する最大値
 * 	@param dDelta		目盛り間隔(0.0基準)
 * 	@param lpszFormat	目盛りのフォーマット
 * 	@param bAdjust		描画領域をはみ出さないように　FALSE:調整しない/TRUE:調整する
 */
void CAXMeasureStyle::DrawDivMeasure( CDC *pDC, const CRect &rect, int iMode, double dMin, double dMax, double dDelta, LPCTSTR lpszFormat, BOOL bAdjust )
{
	CString strData;
	// 目盛り間隔に調整
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
 * 	目盛り(最小値/最大値)の描画
 * 		目盛り(最小値/最大値)を描画する
 * 
 * 	@param pDC			描画に使用するデバイスコンテキスト
 * 	@param rect			目盛りを描画する範囲
 * 	@param iMode		X:MEASUREX/Y:MEASUREY
 * 	@param dMin			描画する最小値
 * 	@param dMax			描画する最大値
 * 	@param dDelta		目盛り間隔(0.0基準)
 * 	@param lpszFormat	目盛りのフォーマット
 * 	@param bAdjust		描画領域をはみ出さないように　FALSE:調整しない/TRUE:調整する
 */
void CAXMeasureStyle::DrawLogMeasure( CDC *pDC, const CRect &rect, int iMode, double dMin, double dMax, double dDelta, LPCTSTR lpszFormat, BOOL bAdjust )
{
	// 範囲を計算
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
			// 値のデータ
			//DELL20050711 iValLog = (int)dMinLog + i;
			iValLog = FtoL(dMinLog + i);//yotsutsu20050711
			double dVal = pow( 10, iValLog );
			// 文字フォーマット作成
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
			// 値のデータ
			//DELL20050711 iValLog = (int)dMinLog + i;
			iValLog = FtoL(dMinLog + i);//yotsutsu20050711
			double dVal = pow( 10, iValLog );
			// 文字フォーマット作成
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
 * 	スケール文字を範囲内に描画する.
 * 
 * 	@param pDC		描画に使用するデバイスコンテキスト
 * 	@param rect		描画範囲
 * 	@param iMode	X:MEASUREX/Y:MEASUREY 
 * 	@param iX		描画位置X
 * 	@param iY		描画位置Y
 * 	@param lpszData	描画文字列
 * 	@param iAdjust	0:調整しない/1:調整する/2:はみ出したら表示しない
 */
void CAXMeasureStyle::TextDraw( CDC *pDC, CRect rect, int iMode, int iX, int iY, LPCTSTR lpszData, int iAdjust )
{
	int iMargin = 0;
	CSize sizeData = pDC->GetTextExtent( lpszData );

	LOGFONT logfont;
	pDC->GetCurrentFont()->GetLogFont( &logfont );
	// 各計算値の取得
	double dRad= ( M_PI / 180.0 ) * ( logfont.lfOrientation / 10.0 );
	double dSinX = sizeData.cx * sin( dRad );
	double dSinY = sizeData.cy * sin( dRad );
	double dCosX = sizeData.cx * cos( dRad );
	double dCosY = sizeData.cy * cos( dRad );
	double dWidth, dHeigth;
	
	// X描画位置
	if( iMode == MEASUREX ){
		dWidth  = dCosX;
		dWidth += dSinY;
		dHeigth = dSinX;
		iX -= FtoL( dWidth ) / 2;
		iY += FtoL( dHeigth );

		// 端の調整
		int iWidth = FtoL( dWidth );
		if( iX < (rect.left - iMargin) )	{
			if(iAdjust == 1)		{	iX = rect.left - iMargin + 1;	}
			else if(iAdjust == 2)	{	return;	}
		}
		if( (iX + iWidth) > (rect.right + iMargin )){
			if(iAdjust == 1)		{	iX = rect.right + iMargin - iWidth;	}
			else if(iAdjust == 2)	{	return;	}
		}
	// Y描画位置
	} else{
		dWidth  = dCosX;
		dWidth += dSinY;
		dHeigth = dSinX;
		dHeigth-= dCosY;
		iX -= FtoL( dWidth );
		iY += FtoL( dHeigth ) / 2;

		// 端の調整
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
 * 	CAXMeasureStyleのスケール情報 + αをコピーする.
 * 
 * 	@param src		コピー元のCAXMeasureStyle
 * 	@return			スケール情報のポインタ
 */
const GDISCALEINFO & CAXMeasureStyle::CopyScale( const CAXMeasureStyle &src )
{
	///< 目盛りの分割指定の有効/無効
	EnableDivDelta((src.m_measureStyle.dwMsStyle & AMS_EN_DIVDELTA));
	//< 目盛り間隔の原点(データ値指定)
	SetDeltaOrg((src.m_measureStyle.dwMsStyle & AMS_EN_ORG) ,src.m_measureStyle.dOrgDelta);			
	
	m_measureStyle.dDelta = src.m_measureStyle.dDelta;				///< 目盛り間隔(データ値指定)
	m_measureStyle.dDetailDelta = src.m_measureStyle.dDetailDelta;	///< 詳細目盛り間隔(データ値指定)
	
	CAXGDIScaleData::Copy(src);

	return GetScaleInfo();
}
///////////////////////////////////////
/**
 * 	スケールスタイル（CAXMeasureStyle）をコピーする.
 * 
 * 	@param src		コピー元のCAXMeasureStyle
 * 	@return			スケールスタイルのポインタ
 */
CAXMeasureStyle & CAXMeasureStyle::Copy( const CAXMeasureStyle &src )
{
	operator = (src);
	return (*this);
}
/////////////////////////////////////////////////////////////////////////////
// CAXMeasureSpin
/////////////////////////////////////////////////////////////////////////////
#define	MEASURESIZE		10		// 目盛りの脚の長さ
#define	MEASUREMARGIN	2		// 目盛りと名前のマージン
#define IDUPSPIN		1		// スピンのID(上)
#define IDDWSPIN		2		// スピンのID(下)

const int CAXMeasureCtrl::c_iMeasureSise = 10;

BEGIN_MESSAGE_MAP(CAXMeasureSpin, CSpinButtonCtrl)
	ON_WM_CREATE()
END_MESSAGE_MAP()
///////////////////////////////////////
/**
 * 	初期化.
 * 
 * 	@param lpCreateStruct	初期化情報
 * 	@return					0:成功 -1:失敗
 */
int CAXMeasureSpin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CSpinButtonCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect, rgnRect;
	CWnd::GetClientRect( rect );
	rgnRect = rect;

	// Xスピン
	if( GetStyle() & UDS_HORZ ){
		switch( GetDlgCtrlID() ){
		case IDDWSPIN:	rect.right += rect.Width();	break;	// 左
		case IDUPSPIN:	rect.left  -= rect.Width();			// 右
						rgnRect.OffsetRect( rgnRect.Width(), 0 );
						break;
		}
	// Yスピン
	} else{
		switch( GetDlgCtrlID() ){
		case IDUPSPIN:	rect.bottom += rect.Height();	break;	// 上
		case IDDWSPIN:	rect.top    -= rect.Height();			// 下
						rgnRect.OffsetRect( 0, rgnRect.Height() );
						break;
		}
	}

	// ウインドウサイズ変更
	ClientToScreen( rect );
	GetParent()->ScreenToClient( rect );
	MoveWindow( rect );

	// ウインドウ変形
	CRgn  rgn;
	rgn.CreateRectRgnIndirect( rgnRect );
	SetWindowRgn( rgn, TRUE );
	rgn.DeleteObject();

	// 範囲設定
	SetRange( 0, 1 );

	return 0;
}
/////////////////////////////////////////////////////////////////////////////
// CAXMeasureCtrl
/////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////
/**
 * 	コンストラクタ
 * 
 * 	@param iMode	X:MEASUREX/Y:MEASUREY 
 * 	@param iMargin	左右(上下)マージン
 * 	@param bAdjust	描画領域をはみ出さないように　FALSE:調整しない/TRUE:調整する
 */
CAXMeasureCtrl::CAXMeasureCtrl( int iMode /*= MEASUREX*/, int iMargin /*= 0*/ ,BOOL bAdjust /*= TRUE*/)
	: m_spinSize( 0, 0 ) , CAXMeasureStyle( iMode , bAdjust)
{
	// 左右(上下)マージン
	m_iMargin = iMargin;
	// 表示/非表示初期化
	ShowMeasureMinMax( TRUE, TRUE );

	// 目盛り間隔初期化
//	m_iMeasureSpan = 1;
	///< 文字列描画サイズ
	m_iFontSize = -1;		

	// 初期値
	SetBkColor  ( GetSysColor( COLOR_3DFACE ) );

	m_bErase = FALSE;	///< WM_ERASEBKGND描画
	
	//SetStrColor( GetSysColor( COLOR_BTNTEXT ) );
	
	m_nKind = AXGCTRL_MEASURE;
}
///////////////////////////////////////
/**
 * 	コピーコンストラクタ
 * 		与えられたCAXMeasureCtrlをコピーする
 * 
 * 	@param org	コピー元CAXMeasureCtrlクラス
 */
CAXMeasureCtrl::CAXMeasureCtrl( const CAXMeasureCtrl &org )
{
	operator=(org);
}
///////////////////////////////////////
//デストラクタ
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
// CAXMeasureCtrl メッセージ ハンドラ
/// 初期化
void CAXMeasureCtrl::PreSubclassWindow() 
{
	CAXGDICtrl::PreSubclassWindow();

	// スピンサイズ設定
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
	// マージン分ウィンドウサイズ拡大
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
	// スピンの初期化
	CreateSpin();
	//RecalcLayoutSpin();
}
///////////////////////////////////////
/**
 * 	ウインドウ作成通知.
 * 
 * 	@param lpCreateStruct	作成される CWnd オブジェクトについての情報
 * 	@return					TRUE:0 FALSE:-1
 */
int CAXMeasureCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// スピンの初期化
	CreateSpin();
	
	return 0;
}
/// 背景描画
BOOL CAXMeasureCtrl::OnEraseBkgnd(CDC* pDC)
{
	if(m_bErase)	{		///< WM_ERASEBKGND描画
		m_bErase = FALSE;	///< WM_ERASEBKGND描画
		return FALSE;
	}
	return CWnd::OnEraseBkgnd( pDC );
}

/// 描画
void CAXMeasureCtrl::OnPaint() 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	// 描画用メッセージとして CStatic::OnPaint() を呼び出してはいけません
	CPaintDC dc(this); // 描画用のデバイス コンテキスト
	//get rect size
	CRect rectItem;
	GetClientRect( &rectItem );

	DrawBackground( &dc, rectItem );

	// フォントの取得
	LOGFONT logfont;
	GetParent()->GetFont()->GetLogFont( &logfont );
	// フォントの作成?選択
	CFont font;
	font.CreateFontIndirect( &logfont );
	CFont *pOldFont = dc.SelectObject( &font );
	//描画前処理
	BeginPaintDC( &dc, rectItem );
	//描画
	DrawDC( &dc, rectItem );
	//拡張描画
	DrawExDC( &dc, rectItem );
	//Activeな状態を描画
	DrawActiveState( &dc, rectItem );
	// 描画後処理
	EndPaintDC( &dc, rectItem );
	// フォントを戻す
	dc.SelectObject( pOldFont );
	font.DeleteObject();
}
///////////////////////////////////////
/**
 * 	上下スピン.
 * 
 * 	@param nSBCode		スクロール要求を示すスクロール バーのコードを指定します
 * 	@param nPos			スクロール ボックスの現在位置を指定します
 * 	@param pScrollBar	pScrollBar はコントロールへのポインタになります
 */
void CAXMeasureCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if( nSBCode == SB_THUMBPOSITION ){
		//DELLswitch( pScrollBar->GetDlgCtrlID() ){
		//DELLcase IDUPSPIN: nPos = 1;	SetOffset(m_measureStyle.dDelta);			break;	// 上
		//DELLcase IDDWSPIN: nPos = -1;	SetOffset(-1.0 * m_measureStyle.dDelta);	break;	// 下
		//DELL}
		//DELLInvalidate();
		//DELLGetParent()->SendMessage( WM_VSCROLL, MAKEWPARAM(nSBCode, nPos), (LPARAM)this->m_hWnd );
		UINT nKeyParam = 0;
		switch( pScrollBar->GetDlgCtrlID() ){
		case IDUPSPIN: nKeyParam = AMS_OFFSET_UP;		break;	// 上
		case IDDWSPIN: nKeyParam = AMS_OFFSET_DOWN;		break;	// 下
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
 * 	左右スピン.
 * 
 * 	@param nSBCode		スクロール要求を示すスクロール バーのコードを指定します
 * 	@param nPos			スクロール ボックスの現在位置を指定します
 * 	@param pScrollBar	pScrollBar はコントロールへのポインタになります
 */
void CAXMeasureCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if( nSBCode == SB_THUMBPOSITION ){
		//DELLswitch( pScrollBar->GetDlgCtrlID() ){
		//DELLcase IDUPSPIN: nPos = 1;	SetOffset(m_measureStyle.dDelta);			break;	// 上
		//DELLcase IDDWSPIN: nPos = -1;	SetOffset(-1.0 * m_measureStyle.dDelta);	break;	// 下
		//DELL}
		//DELLInvalidate();
		//DELLGetParent()->SendMessage( WM_HSCROLL, MAKEWPARAM(nSBCode, nPos), (LPARAM)this->m_hWnd );
		UINT nKeyParam = 0;
		switch( pScrollBar->GetDlgCtrlID() ){
		case IDUPSPIN: nKeyParam = AMS_OFFSET_UP;		break;	// 上
		case IDDWSPIN: nKeyParam = AMS_OFFSET_DOWN;		break;	// 下
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
/// マウス左ボタン押下の時のメッセージハンドラ
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
/// マウス左ボタン押下の時のメッセージハンドラ
void CAXMeasureCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	if( GetSafeHwnd() )	{
		//if((GetFocus() != this))	{	this->SetFocus();	}
	}

	CWnd::OnRButtonDown(nFlags, point);
}
///////////////////////////////////////
//Activeなアイテムを変更する。
BOOL CAXMeasureCtrl::OnChangeActive( AXGCNOTIFY *pNotifyMsg )
{
	m_activeInfo = pNotifyMsg->activeInfo;	///< Active状態の情報
	Redraw();
	return TRUE;
}
///////////////////////////////////////
//Activeなアイテムのスタイルを変更する。
BOOL CAXMeasureCtrl::OnChangeStyle( AXGCNOTIFY *pNotifyMsg )
{
	///< 0:非選択/1:全体/2:データ/3:カーソル/4:エリアカーソル
	if(m_activeInfo.nActive == AXGCTRLACT_DATA)	{
	}

	return FALSE;
}
///////////////////////////////////////
//Activeなアイテムのスケールを変更する。
BOOL CAXMeasureCtrl::OnChangeScale( AXGCNOTIFY *pNotifyMsg )
{
	//Scale Change type
	switch(pNotifyMsg->nKeyParam)	{
	case AMS_RANGE_UP:		//Delta分レンジ拡大
		SetScale(GetMin() - GetScaleRangeDelta(), GetMax() + GetScaleRangeDelta());
		if(IsEnableDivDelta())	{	m_measureStyle.dDelta += 2.0;	}
		Redraw();
		return TRUE;
	case AMS_RANGE_DOWN:	//Delta分レンジ縮小
		SetScale(GetMin() + GetScaleRangeDelta(), GetMax() - GetScaleRangeDelta());
		if(IsEnableDivDelta())	{	m_measureStyle.dDelta -= 2.0;	}
		Redraw();
		return TRUE;
	case AMS_OFFSET_UP:		//+Deltaオフセット
		SetOffset(GetScaleRangeDelta());
		Redraw();
		return TRUE;
	case AMS_OFFSET_DOWN:	//-Deltaオフセット
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
 * 	CAXMeasureCtrlのモード変更
 * 
 * 	@param iMode	X:MEASUREX/Y:MEASUREY 
 * 	@param iMargin	左右(上下)マージン
 * 	@param bAdjust	描画領域をはみ出さないように　FALSE:調整しない/TRUE:調整する
 */
void CAXMeasureCtrl::SetMode(int iMode /*= MEASUREX*/, int iMargin /*= 0*/, BOOL bAdjust /*= TRUE*/)
{	
//	if(!this->GetSafeHwnd())	{
	//	TRACE("Windowを作成する前によんでね\n");
	//	return;
//	}
	SetScaleMode( iMode );/*m_iMode = iMode;*/	
	m_iMargin = iMargin;
	SetMeasureAdjust(bAdjust);
}
///////////////////////////////////////
/**
 * 	MoveWindowのラップクラス.
 * 		サイズ変更時にスピンサイズを考慮する為にラッピングします
 * 
 * 	@param x		左辺の新しい位置を指定します。
 * 	@param y		上辺の新しい位置を指定します。
 * 	@param nWidth	新しい幅を指定します。
 * 	@param nHeight	新しい高さを指定します。
 * 	@param bRepaint	再描画するかどうかを指定します
 */
void CAXMeasureCtrl::MoveWindow( int x, int y, int nWidth, int nHeight, BOOL bRepaint /*= TRUE*/ )
{
	CRect rect( CPoint( x, y ), CSize( nWidth, nHeight ) );
	MoveWindow( &rect, bRepaint );
}
///////////////////////////////////////
/**
 * 	MoveWindowのラップクラス.
 * 		サイズ変更時にスピンサイズを考慮する為にラッピングします
 * 
 * 	@param lpRect	新しいサイズと位置を指定した CRect オブジェクトまたは RECT 構造体を指定します
 * 	@param bRepaint	再描画するかどうかを指定します
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
 * 	SetWindowPosのラップクラス.
 * 		サイズ変更時にスピンサイズを考慮する為にラッピングします
 * 
 * 	@param pWndInsertAfter	Z 順でこの CWnd オブジェクトより前に配置される CWnd オブジェクトを識別します。
 * 	@param x				ウィンドウの新しい左辺の位置を指定します。
 * 	@param y				ウィンドウの新しい上辺の位置を指定します。
 * 	@param cx				ウィンドウの新しい幅を指定します。
 * 	@param cy				ウィンドウの新しい高さを指定します。
 * 	@param nFlags			サイズと位置の変更時のオプションを指定します。
 * 	@return					TRUE:成功 FALSE:失敗
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
 * 	GetClientRectのラップクラス.
 * 		サイズ取得時にスピンサイズを考慮する為にラッピングします
 * 
 * 	@param lpRect	クライアント座標を受け取るRECT構造体
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
 * 	GetWindowRectのラップクラス.
 * 		サイズ取得時にスピンサイズを考慮する為にラッピングします
 * 
 * 	@param lpRect	ウィンドウ座標を受け取るRECT構造体
 */
void CAXMeasureCtrl::GetWindowRect(LPRECT lpRect)
{
	CRect rect;
	CWnd::GetWindowRect( rect );
	SubcalcRect( rect );
	*lpRect = rect;
}
/////////////////////////////////////////////////////////////////////////////
/// スピン初期化
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
 * 	スピンのサイズ調整.
 * 		現在のクライアント領域からスピンを正しい位置に調整します。
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

	// モードごとに初期値計算
	CRect rectUpSpin = rect, rectDwSpin = rect;
	switch( GetScaleMode() ){	
	case MEASUREX:			// 目盛りX
		rectUpSpin.left   = rectUpSpin.right - m_spinSize.cx * 2;
		rectUpSpin.bottom = rectUpSpin.top   + m_spinSize.cy;
		rectDwSpin.right  = rectDwSpin.left  + m_spinSize.cx * 2;
		rectDwSpin.bottom = rectDwSpin.top   + m_spinSize.cy;
		break;
	case MEASUREY:			// 目盛りY
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
 * 	サイズ計算.
 * 		与えられたRECTをスピンサイズ/マージンサイズを考慮したサイズに変更します。
 * 
 * 	@param rect		元のサイズ
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
 * 	サイズ計算.
 * 		与えられたRECTからスピンサイズ/マージンサイズを引いたサイズに変更します。
 * 
 * 	@param rect		元のサイズ
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
 * 	目盛りを描画する
 * 
 * 	@param pDC			描画に使用するデバイスコンテキスト
 * 	@param rect			目盛りを描画する範囲
 */
void CAXMeasureCtrl::DrawDC( CDC *pDC, CRect rect )
{
	// 各表示エリア
	CRect scaleRect  = rect;		// 目盛り軸表示エリア
	CRect nameRect   = rect;		// 目盛り名表示エリア
	
	int iMeasureSize = MEASURESIZE;//
	if(pDC->IsPrinting())	{
		iMeasureSize = MulDiv(MEASURESIZE, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	}
	// 目盛り軸表示エリアの取得
	switch( GetScaleMode() ){
	case MEASUREX: scaleRect.bottom = scaleRect.top  + iMeasureSize;	break;
	case MEASUREY: scaleRect.left   = scaleRect.right- iMeasureSize;	break;
	default: return;
	}

	int iMeasureMargin = MEASUREMARGIN;//
	if(pDC->IsPrinting())	{
		iMeasureMargin = MulDiv( MEASUREMARGIN, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	}
	// 目盛り/目盛り名表示エリアの取得
	if( IsShowScale())	{
		nameRect.SubtractRect( rect, scaleRect );
		switch( GetScaleMode() ){
		case MEASUREX:	nameRect.top += iMeasureMargin;		break;
		case MEASUREY:	nameRect.right -= iMeasureMargin;	break;
		default: return;
		}
	}
	// 目盛り/目盛り名表示エリアのマージン分の背景を描画する。
	if((!(pDC->IsPrinting())) && (!IsMeasureAdjust()) )	{//WMPINATの時
		int iDrawResize = m_iMargin;//描画領域変更サイズ
		//if(m_iMargin == 0 IsShowSpin())	{
		//	switch( GetScaleMode() ){
		//	case MEASUREX: iDrawResize += m_spinSize.cx;	break;
		//	case MEASUREY: iDrawResize += m_spinSize.cy;	break;
		//	}
		//}
		// マージン分縮小
		switch( GetScaleMode() ){
		case MEASUREX: nameRect.InflateRect( iDrawResize, 0 );	break;
		case MEASUREY: nameRect.InflateRect( 0, iDrawResize );	break;
		}
		// 背景の描画
		pDC->FillSolidRect( nameRect, GetBkColor() );
		// マージン分縮小
		switch( GetScaleMode() ){
		case MEASUREX: nameRect.DeflateRect( iDrawResize, 0 );	break;
		case MEASUREY: nameRect.DeflateRect( 0, iDrawResize );	break;
		}
	}

	// 背景モードの変更
	int iBkMode = pDC->SetBkMode( TRANSPARENT );

	// 目盛り軸の描画
	if( IsShowScale())	{
		// ペンの作成
		CPen pen;
		pen.CreatePen( PS_SOLID, 0, (IsMonochrome() ? RGB(0,0,0) : GetScaleColor()) );
		// ペンの選択
		CPen *pOldPen = pDC->SelectObject( &pen );
		//ラインをきれいに引けるように描画領域を小さくする
		scaleRect.bottom -= 1;
		scaleRect.right -= 1;
		DrawScale( pDC, scaleRect );
		// ペンを戻す
		pDC->SelectObject( pOldPen );
		// ペンの破棄
		pen.DeleteObject();
	}
	// 文字列の描画
	DrawMeasureMaxString( pDC, nameRect, IsMonochrome() );
	DrawMeasureMinString( pDC, nameRect, IsMonochrome() );

	if( IsShowMeasureDelta() || IsShowMeasureMin() || IsShowMeasureMax() )	{
		// 目盛りの描画
		DrawMeasure( pDC, nameRect );
	}

	// 目盛り名の描画
	DrawMeasureName( pDC, nameRect, GetFontSize() );//, strMeasureName );

	// 背景モードを戻す
	pDC->SetBkMode( iBkMode );
}
///////////////////////////////////////
/**
 * 	スピンの表示/非表示設定.
 * 		スピンの表示/非表示を切り替える
 * 
 * 	@param bShow	TRUE:表示 FALSE:非表示
 * 	@return			前回の表示状態
 */
BOOL CAXMeasureCtrl::ShowSpin( BOOL bShow )
{
	BOOL bRtn = FALSE;
	bRtn  = m_spinCtrl[0].ShowWindow( bShow ? SW_SHOW: SW_HIDE );
	bRtn |= m_spinCtrl[1].ShowWindow( bShow ? SW_SHOW: SW_HIDE );
	
	// ウィンドウサイズ変更
	CRect rect;
	if( !bRtn && bShow ){			// 非表示→表示
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
	} else if( bRtn && !bShow ){	// 表示→非表示
		m_bErase = TRUE;	///< WM_ERASEBKGND描画
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
 * 	スピンの表示/非表示取得.
 * 		スピンの表示/非表示を取得する.
 * 
 * 	@return			TRUE:表示 FALSE:非表示
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
 * 	描画前処理
 * 
 * 	@param pDC			描画に使用するデバイスコンテキスト
 * 	@param rect			描画する範囲
 */
void CAXMeasureCtrl::BeginPaintDC( CDC *pDC, const CRect &rect )
{
}
///////////////////////////////////////
/**
 *	描画後処理
 * 
 * 	@param pDC			描画に使用するデバイスコンテキスト
 * 	@param rect			描画する範囲
 */
void CAXMeasureCtrl::EndPaintDC( CDC *pDC, const CRect &rect )
{
}
///////////////////////////////////////
/**
 * 	Active状態の描画.
 * 		Active状態を表示する
 * 
 * 	@param pDC		描画するデバイスコンテキストのポインタ
 * 	@param rect		描画領域の範囲
 */
void CAXMeasureCtrl::DrawActiveFrame( CDC *pDC, const CRect &rect, int size )
{
	CRect rectItem = rect;

/*	int iDrawResize = 0;//描画領域変更サイズ
	iDrawResize = m_iMargin;
	if(IsShowSpin())	{
		switch( GetScaleMode() ){
		case MEASUREX: iDrawResize += m_spinSize.cx;	break;
		case MEASUREY: iDrawResize += m_spinSize.cy;	break;
		}
	}
	if( iDrawResize != 0 )	{
		// マージン分縮小
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