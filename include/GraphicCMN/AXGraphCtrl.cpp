// AXGraphCtrl.cpp : CAXGraphCtrlのインプリメンテーション
//
/********************************************************
// CAXGraphCtrl		:グラフ描画クラス
//												by YOTSUTSU
//	* History	:	date:2005,24,Mar.	新規作成
ver.1.00	
********************************************************/
#include "stdafx.h"
#include <math.h>
#include <float.h>
#include "AXGdiWnd.h"
#include "AXGraphCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CAXGraphCtrl
/////////////////////////////////////////////////////////////////////////////
/**
 * 	コンストラクタ
 * 
 * 	@param bkColor	グラフの背景
 */
CAXGraphCtrl::CAXGraphCtrl( COLORREF bkColor /*= IBLACK*/ )
	:CAXGDIPlotCtrl(bkColor)
{
if(1)	{
	size_t  sizeByte;
	sizeByte = sizeof(TCHAR);			TRACE("TCHAR	= %d, ", sizeByte);	
	sizeByte = sizeof(LINESTYLE);		TRACE("tagLineStyle	= %d, ", sizeByte);
	sizeByte = sizeof(MARKERSTYLE);		TRACE("tagMarkStyle	= %d, ", sizeByte);
	sizeByte = sizeof(AXCURSORINFOA);	TRACE("tagAXCursorInfoA	= %d, ", sizeByte);
	sizeByte = sizeof(AXCURSORINFOW);	TRACE("tagAXCursorInfoW	= %d, ", sizeByte);
	sizeByte = sizeof(AXCURSORINFO);	TRACE("tagAXCursorInfo	= %d, ", sizeByte);

	TRACE("\n");
}
	RemoveAllItem();
	m_nKind = AXGCTRL_GRAPH;
}

/**
 * 	コピーコンストラクタ
 * 
 * 	@param graphCtrl	コピー元グラフ
 */
CAXGraphCtrl::CAXGraphCtrl( CAXGraphCtrl &org )
{
	operator =( org );
}
/// デストラクタ
CAXGraphCtrl::~CAXGraphCtrl()
{
	DestroyWindow();
}

BEGIN_MESSAGE_MAP(CAXGraphCtrl, CAXGDIPlotCtrl)
	//{{AFX_MSG_MAP(CAXGraphCtrl)
//	ON_WM_DESTROY()
//	ON_WM_PAINT()
//	ON_WM_SIZE()
//	ON_WM_LBUTTONUP()
//	ON_WM_MOUSEMOVE()
//	ON_WM_LBUTTONDOWN()
//	ON_WM_LBUTTONDBLCLK() 
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAXGraphCtrl メッセージ ハンドラ
/////////////////////////////////////////////////////////////////////////////
/// ウィンドウ作成時のメッセージハンドラ
void CAXGraphCtrl::PreSubclassWindow() 
{
	CAXGDIPlotCtrl::PreSubclassWindow();
}
///////////////////////////////////////
/// ウィンドウ破棄時のメッセージハンドラ
void CAXGraphCtrl::OnDestroy() 
{
	CAXGDIPlotCtrl::OnDestroy();
	//
	RemoveAllItem();
}
///////////////////////////////////////
BOOL CAXGraphCtrl::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	if( GetSafeHwnd() && (GetFocus() == this))	{
		switch(pMsg->message)	{
		case WM_KEYDOWN:
			if(m_activeInfo.nActive == AXGCTRLACT_CURSOL)	{///< 3:カーソル
				switch(pMsg->wParam)	{
				case VK_ESCAPE:		break;
				case VK_PRIOR:	//VK_PAGE_UP:
					break;
				case VK_NEXT:	//VK_PAGE_DOWN:
					break;
				case VK_LEFT:	// Process the LEFT ARROW key. 
					NotifyToParent( AXGCN_CHANGE_CURSOL, NULL, pMsg->wParam);
					break;
				case VK_RIGHT:	// Process the RIGHT ARROW key.
					NotifyToParent( AXGCN_CHANGE_CURSOL, NULL, pMsg->wParam);
					break;
				case VK_UP:		// Process the UP ARROW key. 
					break;
				case VK_DOWN:	// Process the DOWN ARROW key.
					break;
				}
			}
			break;
		}
	}

	return CAXGDIPlotCtrl::PreTranslateMessage(pMsg);
}
///////////////////////////////////////
/// ウィンドウ描画時のメッセージハンドラ
void CAXGraphCtrl::BeginPaintDC( CDC *pDC, const CRect &rect )
{
	// 再描画情報取得→リセット
	int iLineMax = m_plotData.GetUpperBound();
	for( int i = 0; i <= iLineMax; i++ ){
		m_bRedraw |= m_plotData[i].m_bRedraw;
		m_plotData[i].m_bRedraw = FALSE;
	}
}
///////////////////////////////////////
//Activeなアイテムを変更する。
BOOL CAXGraphCtrl::OnChangeActive( AXGCNOTIFY *pNotifyMsg )
{
	m_activeInfo = pNotifyMsg->activeInfo;	///< Active状態の情報
	Redraw();
	return TRUE;
}
///////////////////////////////////////
//Activeなアイテムのスタイルを変更する。
BOOL CAXGraphCtrl::OnChangeStyle( AXGCNOTIFY *pNotifyMsg )
{
	///< 0:非選択/1:全体/2:データ/3:カーソル/4:エリアカーソル
	if(m_activeInfo.nActive == AXGCTRLACT_DATA)	{
		CLineStyleDlg lineStyleDlg;
		lineStyleDlg.DoModal(m_plotData[m_activeInfo.iLayer].GetLineStyle(),m_plotData[m_activeInfo.iLayer].GetMarkerStyle());
		m_activeInfo.nActive = AXGCTRLACT_DATA;
		m_plotData[m_activeInfo.iLayer].SetLineStyle(lineStyleDlg.GetLineStyle());
		m_plotData[m_activeInfo.iLayer].SetMarkerStyle(lineStyleDlg.GetMarkerStyle());
		m_plotData[m_activeInfo.iLayer].Redraw();
		Redraw();
		return TRUE;
	}	else if(m_activeInfo.nActive == AXGCTRLACT_CURSOL)	{
		CAXPlotCursor &cursor = GetPlotCursor(m_activeInfo.iIndex);
		CLineStyleDlg lineStyleDlg;
		if(IDOK == lineStyleDlg.DoModal(cursor.GetLineStyle(),cursor.GetMarkerStyle()))	{
			cursor.SetLineStyle(lineStyleDlg.GetLineStyle());
			cursor.SetMarkerStyle(lineStyleDlg.GetMarkerStyle());
		}			
		m_activeInfo.nActive = AXGCTRLACT_CURSOL;
		Redraw();
		return TRUE;
	}

	return FALSE;
}
///////////////////////////////////////
//Activeなアイテムのスケールを変更する。
BOOL CAXGraphCtrl::OnChangeScale( AXGCNOTIFY *pNotifyMsg )
{
	return FALSE;
}
///////////////////////////////////////
//Activeなカーソルの位置を更新する。
BOOL CAXGraphCtrl::OnChangeCursol( AXGCNOTIFY *pNotifyMsg )
{
	int index;
	switch(pNotifyMsg->nKeyParam)	{
	case VK_ESCAPE:		break;
	case VK_PRIOR:	//VK_PAGE_UP:
		break;
	case VK_NEXT:	//VK_PAGE_DOWN:
		break;
	case VK_LEFT:	// Process the LEFT ARROW key.
		if( GetPlotCursor(m_activeInfo.iIndex).GetLayer() >= 0)	{
			index = GetPlotCursor(m_activeInfo.iIndex).GetPos();
			if(GetKeyState(VK_SHIFT) & 0x8000)	{//Shift key
				int val = (m_plotData[m_activeInfo.iLayer].GetNum() / 10);
				if(val <= 0)	{	val = 1;	}
				index -= val;
			}	else	{
				index--;
			}
			if(index < 0)	{	index = 0;	}
			if(index != GetPlotCursor(m_activeInfo.iIndex).GetPos())	{
				GetPlotCursor(m_activeInfo.iIndex).SetPos( index );
				Redraw();
				return TRUE;
			}
		}
		break;
	case VK_RIGHT:	// Process the RIGHT ARROW key.
		if( GetPlotCursor(m_activeInfo.iIndex).GetLayer() >= 0)	{
			index = GetPlotCursor(m_activeInfo.iIndex).GetPos();
			if(GetKeyState(VK_SHIFT) & 0x8000)	{//Shift key
				int val = (m_plotData[m_activeInfo.iLayer].GetNum() / 10);
				if(val <= 0)	{	val = 1;	}
				index += val;
			}	else	{
				index++;
			}
			if(index >= m_plotData[m_activeInfo.iLayer].GetNum())	{
				index = m_plotData[m_activeInfo.iLayer].GetNum() - 1;
			}				
			if(index != GetPlotCursor(m_activeInfo.iIndex).GetPos())	{
				GetPlotCursor(m_activeInfo.iIndex).SetPos( index );
				Redraw();
				return TRUE;
			}
		}
		break;
	case VK_UP:		// Process the UP ARROW key. 
		break;
	case VK_DOWN:	// Process the DOWN ARROW key.
		break;
	}
	return FALSE;
}
///////////////////////////////////////
/// マウス左ボタン押下の時のActivate
int CAXGraphCtrl::MouseLBdownActivate( const CRect &rect, CPoint point, AXGCACTINFO *lpActiveInfo )
{
	AXGCACTINFO &tempActiveInfo = (*lpActiveInfo);

	///< 0:非選択/1:全体/2:データ/3:カーソル/4:エリアカーソル
	tempActiveInfo.nActive = AXGCTRLACT_NONE;

	int iXp = -1;
	int iYp = -1;
	const int c_iChkPoint = 5;//クリックしたpointと描画pointとのチェックする範囲
	
	if( rect.Width() <= 0 )		{	return AXGCTRLACT_NONE;	}
	if( rect.Height() <= 0 )	{	return AXGCTRLACT_NONE;	}
	CPoint ptData = point;
	for( int iLayer = 0; iLayer < GetLineNum(); iLayer++ ){
		///< 0:非選択/1:全体/2:データ/3:カーソル/4:エリアカーソル
		if(tempActiveInfo.nActive != AXGCTRLACT_NONE)	{	break;	}
		tempActiveInfo.iLayer = iLayer;	///< Activeなカーソルのレイヤー
		tempActiveInfo.iLine = 0;		///< Activeなレイヤーライン番号
		CXYPlotData &data = m_plotData[iLayer];
		ptData = point;
		//クリックポイントからXの値を求める。
		double dValX =  m_plotData[iLayer].GetXscale().Point2DataX( ( point.x ), rect.Width() );
		double dValY =  m_plotData[iLayer].GetYscale().Point2DataY( ( point.y ), rect.Height() );
		
		if(data.IsReversalX() && (!data.GetXscale().IsLogMode()))	{
			dValX *= -1.0;
			ptData.x = data.GetXscale().Data2PointX( dValX, rect.Width() );
		}
		if(data.IsReversalY() && (!data.GetYscale().IsLogMode()))	{
			dValY *= -1.0;
			ptData.y = data.GetYscale().Data2PointY( dValY, rect.Height() );
		}

		double dValue;
		TRACE("point x:%f,y:%f\n",dValX,dValY);
		BOOL bInside = FALSE;
		///////////////////データに対して、Active可能か調べる。//////////////////////////////////
		for( int index = 1; index < m_plotData[iLayer].GetNum(); index++ ){
			if(!m_plotData[iLayer].IsVisible())							{	break;	}
			if( index >= m_plotData[iLayer].GetNum() )		{	break;	}
			tempActiveInfo.iIndex = index;	///< Activeなデータのインデックス
			iXp = m_plotData[iLayer].GetXscale().Data2PointX( m_plotData[iLayer][index-1].dX, rect.Width() );
			iYp = m_plotData[iLayer].GetYscale().Data2PointY( m_plotData[iLayer][index-1].dY, rect.Height() );
			//座標の差を求める。
			int iXCheck = iXp - ptData.x;
			int iYCheck = iYp - ptData.y;
			if(iXCheck >= -c_iChkPoint && iXCheck <= c_iChkPoint && iYCheck >= -c_iChkPoint && iYCheck <= c_iChkPoint)	{
				///< 0:非選択/1:全体/2:データ/3:カーソル/4:エリアカーソル
				tempActiveInfo.nActive = AXGCTRLACT_DATA;	TRACE("LineActivate[index-1]:%d\n",index-1);
				tempActiveInfo.iIndex = -1;
				return tempActiveInfo.nActive;
			}
			iXp = m_plotData[iLayer].GetXscale().Data2PointX( m_plotData[iLayer][index].dX, rect.Width() );
			iYp = m_plotData[iLayer].GetYscale().Data2PointY( m_plotData[iLayer][index].dY, rect.Height() );
			//座標の差を求める。
			iXCheck = iXp - ptData.x;
			iYCheck = iYp - ptData.y;
			if(iXCheck >= -c_iChkPoint && iXCheck <= c_iChkPoint && iYCheck >= -c_iChkPoint && iYCheck <= c_iChkPoint)	{
				///< 0:非選択/1:全体/2:データ/3:カーソル/4:エリアカーソル
				tempActiveInfo.nActive = AXGCTRLACT_DATA;	TRACE("LineActivate[index]:%d\n",index);
				tempActiveInfo.iIndex = -1;
				return tempActiveInfo.nActive;
			}

			bInside = FALSE;
			//Xがデータの前後の範囲内であれば、
			if(m_plotData[iLayer][index-1].dX < m_plotData[iLayer][index].dX)	{
				if((dValX >= m_plotData[iLayer][index-1].dX) && (dValX <= m_plotData[iLayer][index].dX))	{	bInside = TRUE;	}
			}	else	{
				if((dValX <= m_plotData[iLayer][index-1].dX) && (dValX >= m_plotData[iLayer][index].dX))	{	bInside = TRUE;	}
			}
			if(bInside)	{
				//XからYを求める。
				dValue =  (m_plotData[iLayer][index].dY - m_plotData[iLayer][index-1].dY) / (m_plotData[iLayer][index].dX - m_plotData[iLayer][index-1].dX) * ( dValX - m_plotData[iLayer][index-1].dX) +  m_plotData[iLayer][index-1].dY;
				//YからY座標を求める。
				iYp = m_plotData[iLayer].GetYscale().Data2PointY( dValue , rect.Height() );
				//座標の差を求める。
				int iCheck = iYp - ptData.y;
				if(iCheck >= -c_iChkPoint && iCheck <= c_iChkPoint)	{
					///< 0:非選択/1:全体/2:データ/3:カーソル/4:エリアカーソル
					tempActiveInfo.nActive = AXGCTRLACT_DATA;		TRACE("%f,%f,%d,%d",dValX,dValY,iYp,ptData.y);	TRACE("yLineActivate\n");
					tempActiveInfo.iIndex = -1;
					return tempActiveInfo.nActive;
				}
			}
			bInside = FALSE;
			if(m_plotData[iLayer][index-1].dY < m_plotData[iLayer][index].dY)	{
				if((dValY >= m_plotData[iLayer][index-1].dY) && (dValY <= m_plotData[iLayer][index].dY))	{	bInside = TRUE;	}
			}	else	{
				if((dValY <= m_plotData[iLayer][index-1].dY) && (dValY >= m_plotData[iLayer][index].dY))	{	bInside = TRUE;	}
			}
			if(bInside)	{
				//YからXを求める。
				dValue = ( dValY - m_plotData[iLayer][index-1].dY ) / (m_plotData[iLayer][index].dY - m_plotData[iLayer][index-1].dY) * (m_plotData[iLayer][index].dX - m_plotData[iLayer][index-1].dX) + m_plotData[iLayer][index-1].dX;
				//XからX座標を求める。
				iXp = m_plotData[iLayer].GetXscale().Data2PointX( dValue, rect.Width() );
				//座標の差を求める。
				int iCheck = iXp - ptData.x;
				if(iCheck >= -c_iChkPoint && iCheck <= c_iChkPoint)	{
					///< 0:非選択/1:全体/2:データ/3:カーソル/4:エリアカーソル
					tempActiveInfo.nActive = AXGCTRLACT_DATA;		TRACE("%f,%f,%d,%d",dValX,dValY,iXp,ptData.x);	TRACE("xLineActivate\n");
					tempActiveInfo.iIndex = -1;
					return tempActiveInfo.nActive;
				}
			}
		}
	}
	if(1)	{
		///////////////////カーソルに対して、Active可能か調べる。//////////////////////////////////
		ptData = point;
		for( int index = 0; index < GetPlotCursorNum(); index++ ){
			if(!GetPlotCursor(index).IsShowCursor())	{	continue;	}
			int cursorMode = GetPlotCursor(index).GetCursorMode();
			int iLayer = GetPlotCursor(index).GetLayer();
			tempActiveInfo.iLayer = iLayer;		///< Activeなレイヤー番号				-1:無効 0オリジン
			tempActiveInfo.iIndex = index;		///< Activeなカーソルのインデックス
			if( iLayer >= 0 )	{//Pos
				CXYPlotData &data = m_plotData[iLayer];
				int iPos = GetPlotCursor(index).GetPos();
				if(  0 > iPos || iPos >= data.GetNum() )	{	continue;	}
				if( GetPlotCursor(index).GetPenStyle() == PS_NULL )		{	continue;	}
				//X
				if( cursorMode == CURSORX || cursorMode == CURSORCROSS ){
					double dRvsX = 1.0;
					if(data.IsReversalX() && (!data.GetXscale().IsLogMode()))	{
						dRvsX = -1.0;
					}
					iXp =  m_plotData[iLayer].GetXscale().Data2PointX( m_plotData[iLayer].dataX( iPos ) * dRvsX, rect.Width());
					iXp -= ptData.x;
					if(iXp >= -c_iChkPoint && iXp <= c_iChkPoint)	{
						///< 0:非選択/1:全体/2:データ/3:カーソル/4:エリアカーソル
						tempActiveInfo.nActive = AXGCTRLACT_CURSOL;	TRACE("CursorActivate\n");
						return tempActiveInfo.nActive;
					}
				}
				//Y
				if( cursorMode == CURSORY || cursorMode == CURSORCROSS ){
					double dRvsY = 1.0;
					if(data.IsReversalY() && (!data.GetYscale().IsLogMode()))	{
						dRvsY = -1.0;
					}
					iYp = m_plotData[iLayer].GetYscale().Data2PointY( m_plotData[iLayer].dataY( iPos ) * dRvsY, rect.Height());
					iYp -= ptData.y;
					if(iYp >= -c_iChkPoint && iYp <= c_iChkPoint)	{
						///< 0:非選択/1:全体/2:データ/3:カーソル/4:エリアカーソル
						tempActiveInfo.nActive = AXGCTRLACT_CURSOL;	TRACE("CursorActivate\n");
						return tempActiveInfo.nActive;
					}
				}
			}	else	{
				if(GetPlotCursor(index).GetPenStyle() == PS_NULL)	{	continue;	}
				//X
				if( cursorMode == CURSORX || cursorMode == CURSORCROSS ){
					iXp =  GetAxisX().Data2PointX( GetPlotCursor(index).GetValue().dX, rect.Width());
					iXp -= ptData.x;
					if(iXp >= -c_iChkPoint && iXp <= c_iChkPoint)	{
						///< 0:非選択/1:全体/2:データ/3:カーソル/4:エリアカーソル
						tempActiveInfo.nActive = AXGCTRLACT_CURSOL;	TRACE("CursorActivate\n");
						return tempActiveInfo.nActive;
					}
				}
				//Y
				if( cursorMode == CURSORY || cursorMode == CURSORCROSS ){
					iYp = GetAxisY().Data2PointY( GetPlotCursor(index).GetValue().dY, rect.Height());
					iYp -= ptData.y;
					if(iYp >= -c_iChkPoint && iYp <= c_iChkPoint)	{
						///< 0:非選択/1:全体/2:データ/3:カーソル/4:エリアカーソル
						tempActiveInfo.nActive = AXGCTRLACT_CURSOL;	TRACE("CursorActivate\n");
						return tempActiveInfo.nActive;
					}
				}
			}
		}
	}
	if(1)	{
		///////////////////エリアカーソルに対して、Active可能か調べる。//////////////////////////////////
		for( int index = 0; index < GetAreaCursorNum(); index++ ){
			if(!GetAreaCursor( index ).IsShowCursor() )		{	continue;	}
			int iLayer = GetAreaCursor( index ).GetLayer();
			int cursorMode = GetAreaCursor( index ).GetCursorMode();
			tempActiveInfo.iIndex = index;		///< Activeなカーソルのインデックス
			tempActiveInfo.iLayer = iLayer;		///< Activeなレイヤー番号				-1:無効 0オリジン
			CRect rectArea(CPoint(0,0),m_wndSize);
			if( iLayer >= 0 )	{//Pos
				int iHead = GetAreaCursor( index ).GetHeadPos();
				if( 0 > iHead || iHead >= m_plotData[iLayer].GetNum() )	{	continue;	}
				int iTail = GetAreaCursor( index ).GetTailPos();
				if( 0 > iTail || iTail >= m_plotData[iLayer].GetNum() )		{	continue;	}
						
				//X
				if( cursorMode == CURSORX || cursorMode == CURSORCROSS ){
					rectArea.left =  m_plotData[iLayer].GetXscale().Data2PointX( m_plotData[iLayer].dataX( iHead ), rect.Width());
					rectArea.right = m_plotData[iLayer].GetXscale().Data2PointX( m_plotData[iLayer].dataX( iTail ), rect.Width());
				}
				//Y
				if( cursorMode == CURSORY || cursorMode == CURSORCROSS ){
					rectArea.top = m_plotData[iLayer].GetYscale().Data2PointY( m_plotData[iLayer].dataY( iHead ), rect.Height());
					rectArea.bottom = m_plotData[iLayer].GetYscale().Data2PointY( m_plotData[iLayer].dataY( iTail ), rect.Height());
				}
				
			}	else	{
				//X
				if( cursorMode == CURSORX || cursorMode == CURSORCROSS ){
					rectArea.left =  GetAxisX().Data2PointX( GetAreaCursor( index ).GetHeadValue().dX, rect.Width());
					rectArea.right = GetAxisX().Data2PointX( GetAreaCursor( index ).GetTailValue().dX, rect.Width());
				}
				//Y
				if( cursorMode == CURSORY || cursorMode == CURSORCROSS ){
					rectArea.top = GetAxisY().Data2PointY( GetAreaCursor( index ).GetHeadValue().dY, rect.Height());
					rectArea.bottom = GetAxisY().Data2PointY( GetAreaCursor( index ).GetTailValue().dY, rect.Height());
				}
			}
			rectArea.NormalizeRect();
			rectArea.InflateRect(1,1);
			if( rectArea.PtInRect(point))	{	
				tempActiveInfo.nActive = AXGCTRLACT_AREACSL;	TRACE("AreaCursorActivate\n");
				return tempActiveInfo.nActive;
			}
		}
	}

	tempActiveInfo.nActive =AXGCTRLACT_FRAME;
	tempActiveInfo.iLayer = -1;
	tempActiveInfo.iLine = -1;		///< Activeなレイヤーライン番号
	tempActiveInfo.iIndex = -1;

	return AXGCTRLACT_FRAME;
}
///////////////////////////////////////
// public
///////////////////////////////////////
/**
 * 	グラフを描画する.
 * 		指定されたDCにグラフを描画する
 * 
 * 	@param pDC	描画するDC
 * 	@param rect	描画する領域のRECT
 */
void CAXGraphCtrl::DrawGraph( CDC *pDC, const CRect &rect )
{
	// 背景色の保持
	COLORREF orgBkColor = pDC->GetBkColor();
	
	// 背景の描画
	pDC->FillSolidRect( rect, (pDC->IsPrinting() ? IWHITE : GetBkColor()) );

	// クリッピング領域の保存
	CRect clipRect;
	pDC->GetClipBox( clipRect );

	// クリッピング領域の設定
	pDC->IntersectClipRect( rect );

	// 背景モードの変更
	int iBkMode = pDC->SetBkMode( TRANSPARENT );

	// グリッド線(全体)の描画
	CRect rectGraph = rect;
	rectGraph.right -= 1;
	rectGraph.bottom -= 1;

	int iLineMax = m_plotData.GetUpperBound();
	if(1)	{
	// エリアカーソル描画
	for( int i = 0; i < GetAreaCursorNum(); i++ ){
		int nLayer = GetAreaCursor(i).GetLayer();
		if( nLayer >= 0 && nLayer < GetLineNum())	{
			CAXGDIPlotCtrl::DrawAreaCursor( pDC, rectGraph, m_plotData[nLayer], GetAreaCursor(i) );
		}	else	{
			CAXGDIPlotCtrl::DrawAreaCursor( pDC, rectGraph, GetAreaCursor(i) );
		}
	}
	}

	if(m_bShowGridX)	{	///< 表示有効（X軸）
		DrawGrid( pDC, GRIDX, rectGraph, m_gridX.GetLineStyle() );
	}
	if(m_bShowGridY)	{	///< 表示有効（Y軸）
		DrawGrid( pDC, GRIDY, rectGraph, m_gridY.GetLineStyle() );
	}

	// フォントの取得
	LOGFONT logfont;
	pDC->GetCurrentFont()->GetLogFont( &logfont );
	// FontSize
	if(GetAreaCsrFontSize() > 0)	{
		logfont.lfHeight = -MulDiv(GetAreaCsrFontSize(), pDC->GetDeviceCaps(LOGPIXELSY), 72);
	}	
	// フォントの作成?選択
	CFont font;
	font.CreateFontIndirect( &logfont );
	CFont *pOldFont = pDC->SelectObject( &font );

	if(1)	{
	// エリアカーソル描画
	for( int i = 0; i < GetAreaCursorNum(); i++ ){
		int nLayer = GetAreaCursor(i).GetLayer();
		if( nLayer >= 0 && nLayer < GetLineNum())	{
			CAXGDIPlotCtrl::DrawAreaCursor( pDC, rectGraph, m_plotData[nLayer], GetAreaCursor(i), TRUE );
		}	else	{
			CAXGDIPlotCtrl::DrawAreaCursor( pDC, rectGraph, GetAreaCursor(i), TRUE );
		}
	}
	}
	// フォントを戻す
	pDC->SelectObject( pOldFont );
	font.DeleteObject();

	if(IsShowPlotScaleX())	{///< プロットデータのスケールを表示有効（X軸）
		int index = 0;
		int showLine = GetShowLineNum();
		for( int i = 0; i <= iLineMax; i++ ){
			if( GetLine(i).IsVisible() ) {
				DrawPlotScale( pDC, rectGraph, AX_GDIXMODE, index, showLine,GetLine(i).GetLineColor(), GetLine(i).GetXscale().GetMin(), GetLine(i).GetXscale().GetMax() );
				index++;
			}
		}
	}
	if(IsShowPlotScaleY())	{///< プロットデータのスケールを表示有効（X軸）
		int index = 0;
		int showLine = GetShowLineNum();
		for( int i = 0; i <= iLineMax; i++ ){
			if( GetLine(i).IsVisible() ) {
				DrawPlotScale( pDC, rectGraph, AX_GDIYMODE, index, showLine,GetLine(i).GetLineColor(), GetLine(i).GetYscale().GetMin(), GetLine(i).GetYscale().GetMax() );
				index++;
			}
		}
	}
	if(IsShowPlotName())	{///< プロットデータ名称の表示有効
		int index = 0;
		int showLine = GetShowLineNum();
		for( int i = 0; i <= iLineMax; i++ ){
			if( GetLine(i).IsVisible() ) {
				if(!GetLine(i).GetName().IsEmpty())	{
					DrawPlotName( pDC, rectGraph, GetShowModePlotName(), index, showLine,GetLine(i).GetLineColor(), GetLine(i).GetName() );
				}
				index++;
			}
		}
	}

	//X axis 目盛り描画
	if(GetAxisX().IsShowScale())	{
		DrawMeasure( pDC, rectGraph , GetAxisX() );
	}
	//Y axis 目盛り描画
	if(GetAxisY().IsShowScale())	{
		DrawMeasure( pDC, rectGraph , GetAxisY() );
	}

	//フレームの描画
	if(IsFrameVisible())	{
		CBrush brush( (IsMonochrome() ? RGB(0,0,0) : GetFrameColor()) );
		pDC->FrameRect( rect, &brush );
	}
	
	// データ描画
	for( int i = 0; i <= iLineMax; i++ ){
		if( m_plotData[i].IsVisible() ) {
			int iMarkerSize;
			if(pDC->IsPrinting())	{//印刷時の補正
				if(GetInitSize().cy > 0)	{
					iMarkerSize = FtoL(m_plotData[i].GetMarkerSize() * rect.Height() / GetInitSize().cy);
					iMarkerSize = m_plotData[i].SetMarkerSize(iMarkerSize);
				}	else	{
					iMarkerSize = m_plotData[i].GetMarkerSize();
				}
			}
			DrawLayerData( pDC, rectGraph, m_plotData[i] );

			if(pDC->IsPrinting())	{//印刷時の補正戻し
				m_plotData[i].SetMarkerSize(iMarkerSize);
			}
		}
	}

	// 背景色を戻す
	pDC->SetBkColor( orgBkColor );

	// 背景モードを戻す
	pDC->SetBkMode( iBkMode );

	// クリップ領域を元に戻す
	pDC->SelectClipRgn( NULL );
	pDC->IntersectClipRect( clipRect );
}
///////////////////////////////////////
/**
 * 	データの表示範囲設定.
 * 		グラフ全体のデータの表示範囲を設定する。\n
 * 
 * 	@param dMin			データのX表示Min範囲
 * 	@param dMax			データのX表示Max範囲
 * 	@param dDelta		グラフの目盛り/グリッドの間隔(データ値指定)
 * 	@param dDetailDelta	グラフの詳細目盛り間隔(データ値指定)
 * 	@param bAllLayer	TRUE:全データレイヤーに対して/FALSE:全体グラフのスケールのみ
 */
void CAXGraphCtrl::SetXScale( double dMin, double dMax, double dDelta /*= -1.0*/, double dDetailDelta /*= -1*/, BOOL bAllLayer /*= FALSE*/ )
{
	if(bAllLayer)	{
		int iLineMax = m_plotData.GetUpperBound();
		for( int i = 0; i <= iLineMax; i++ ){
			m_plotData[i].GetXscale().SetScale( dMin, dMax );
		}
	}
	GetAxisX().SetScale( dMin, dMax, dDelta, dDetailDelta );
	Redraw(TRUE);
}
///////////////////////////////////////
/**
 * 	データの表示範囲設定.
 * 		グラフ全体のデータの表示範囲を設定する。\n
 * 
 * 	@param dMin			データのY表示Min範囲
 * 	@param dMax			データのY表示Max範囲
 * 	@param dDelta		グラフの目盛り/グリッドの間隔(データ値指定)
 * 	@param dDetailDelta	グラフの詳細目盛り間隔(データ値指定)
 * 	@param bAllLayer	TRUE:全データレイヤーに対してスケール設定/FALSE:全体グラフのスケールのみ設定
 */
void CAXGraphCtrl::SetYScale( double dMin, double dMax, double dDelta /*= -1.0*/, double dDetailDelta /*= -1*/, BOOL bAllLayer /*= FALSE*/ )
{
	if(bAllLayer)	{
		int iLineMax = m_plotData.GetUpperBound();
		for( int i = 0; i <= iLineMax; i++ ){
			m_plotData[i].GetYscale().SetScale( dMin, dMax );
		}
	}
	GetAxisY().SetScale( dMin, dMax, dDelta, dDetailDelta );
	Redraw(TRUE);
}
///////////////////////////////////////
/**
 * 	グラフ全体のX軸の対数グラフの表示設定.
 * 		グラフ全体のX軸の対数グラフ表示を設定する。\n
 * 
 * 	@param	bLog		対数スケール		TRUE:有効/FALSE:無効
 * 	@param	bScaleAuto	対数オートスケール	TRUE:有効/FALSE:無効
 */
void CAXGraphCtrl::SetXLogScale( BOOL bLog /*= TRUE*/, BOOL bScaleAuto /*= TRUE*/ )
{
	for(int iLine = 0;iLine < GetLineNum();iLine++)	{
		m_plotData[iLine].GetXscale().SetLogMode( bLog, bScaleAuto );
	}
	m_axisX.SetLogMode( bLog, bScaleAuto );
	Redraw(TRUE);
}
///////////////////////////////////////
/**
 * 	グラフ全体のX軸の対数グラフの表示設定.
 * 		グラフ全体のX軸の対数グラフ表示を設定する。\n
 * 
 * 	@param	bLog		対数スケール		TRUE:有効/FALSE:無効
 * 	@param	bScaleAuto	対数オートスケール	TRUE:有効/FALSE:無効
 */
void CAXGraphCtrl::SetYLogScale( BOOL bLog /*= TRUE*/, BOOL bScaleAuto /*= TRUE*/ )
{
	for(int iLine = 0;iLine < GetLineNum();iLine++)	{
		m_plotData[iLine].GetYscale().SetLogMode( bLog, bScaleAuto );
	}
	m_axisY.SetLogMode( bLog, bScaleAuto );
	Redraw(TRUE);
}
///////////////////////////////////////
/**
 * 	スクロールする.
 * 		グラフ全体をスクロールする。
 * 
 * 	@param iScrollX	Xスクロール量
 * 	@param iScrollY	Yスクロール量
 */
void CAXGraphCtrl::Scroll( double dScrollX, double dScrollY )
{
	for( int i = 0; i < GetLineNum(); i++ ){
		m_plotData[i].Scroll( dScrollX, dScrollY );
	}
	m_axisX.SetOffset(dScrollX);
	m_axisY.SetOffset(dScrollY);
	Redraw(TRUE);
}
///////////////////////////////////////
/**
 * 	全データレイヤーの最小値＆最大値をクリアする.
 * 
 */
void CAXGraphCtrl::ClearMinMax( void )
{
	for( int i = 0; i < GetLineNum(); i++ ){
		m_plotData[i].ClearMinMax();
	}
}
///////////////////////////////////////
/**
 * 	オートスクロール機能をON/OFFする.
 * 
 * 	@param bEnable	オートスクロールを有効にするかのフラグ(TRUE:ON FALSE:OFF)
 * 	@return			以前の許可状態を返す。
 *
void CAXGraphCtrl::EnableAutoScroll( BOOL bEnable )
{
	int iLineMax = m_plotData.GetUpperBound();
	for( int i = 0; i <= iLineMax; i++ ){
		m_plotData[i].EnableAutoScroll( bEnable );
	}
}
///////////////////////////////////////
/**
 * 	オートスケール機能をON/OFFする.
 * 
 * 	@param bEnable	オートスケールを有効にするかのフラグ(TRUE:ON FALSE:OFF)
 * 	@return			以前の許可状態を返す。
 *
void CAXGraphCtrl::EnableAutoScale( BOOL bEnable )
{
	int iLineMax = m_plotData.GetUpperBound();
	for( int i = 0; i <= iLineMax; i++ ){
		m_plotData[i].EnableAutoScale( bEnable );
	}
}
///////////////////////////////////////
/**
 * 	グラフを拡大する.
 * 		rectZoomで与えられた領域を拡大する
 * 
 * 	@param rectZoom	拡大する領域
 */
void CAXGraphCtrl::Zoom( CRect rectZoom )
{
	// グラフの範囲
	CRect graphRect;
	GetClientRect( graphRect );

	// 正規化
	rectZoom.NormalizeRect();
	rectZoom &= graphRect;

	// 係数を求める
	double dDeltaSX = 0.0;
	double dDeltaEX = 1.0;
	double dDeltaSY = 1.0;
	double dDeltaEY = 0.0;
	
	if(Y_ZOOM != GetMouseZoom())	{			
		dDeltaSX = (double)rectZoom.left  / (double)graphRect.Width();
		dDeltaEX = (double)rectZoom.right / (double)graphRect.Width();
	}
	if(X_ZOOM != GetMouseZoom())	{
		dDeltaSY = 1.0 - (double)rectZoom.top   / (double)graphRect.Height();
		dDeltaEY = 1.0 - (double)rectZoom.bottom/ (double)graphRect.Height();
	}
	// 線毎に拡大
	int iLineMax = m_plotData.GetUpperBound();
	for( int i = 0; i <= iLineMax; i++ ){
		m_plotData[i].GetXscale().SetZoom(dDeltaSX,dDeltaEX);
		m_plotData[i].GetYscale().SetZoom(dDeltaSY,dDeltaEY);
	}
		
	GetAxisX().SetZoom(dDeltaSX,dDeltaEX);
	GetAxisY().SetZoom(dDeltaSY,dDeltaEY);

	Redraw(TRUE);
}
/**
 * 	レイヤーデータの描画.
 * 		与えられたレイヤーのデータを描画する
 * 
 * 	@param pDC		描画するデバイスコンテキストのポインタ
 * 	@param rect		描画領域の範囲
 * 	@param data		プロットするレイヤーデータ
 */
void CAXGraphCtrl::DrawLayerData( CDC *pDC, const CRect &rect, CXYPlotData &data )
{
	// データ描画
	int iDataMax = data.GetNum() - 1;
	if( iDataMax >= 0 ){
		// 描画原点設定
		CPoint oldOrg = pDC->SetViewportOrg( rect.left, rect.top );

		// 幅と高さを取得
		double dWidth = (double)rect.Width();
		double dHeight= (double)rect.Height();

		// データ原点設定
		double dXOrg = data.GetXscale().GetDrawOrg();
		double dXRange = data.GetXscale().GetDrawRange();
		double dYOrg = data.GetYscale().GetDrawOrg();
		double dYRange = data.GetYscale().GetDrawRange();
		double dYMax = dYRange + dYOrg;
	
		//描画色
		COLORREF	color = data.GetLineStyle().color;
		//モノクロ
		if(IsMonochrome())	{ color = IBLACK;	} 
		// ペンの作成
		CLinePen pen;
		int penStyle = data.GetLineStyle().iStyle;
		if(data.GetLineStyle().iStyle == PS_NULL && MARKNONE != data.GetMarkerStyle().iMarker)	{
			penStyle = PS_SOLID;
		}
		pen.CreatePen( penStyle, data.GetLineStyle().iSize, color );
		// ペンの選択
		CPen *pOldPen = pDC->SelectObject( &pen );
		//モノクロ
		if(IsMonochrome())	{ color = Color2Gray( data.GetLineStyle().color );	} 
		// ブラシの作成
		CBrush	brush( color );
		// ブラシの選択
		CBrush *oldBrush = NULL;
		if(data.GetMarkerBkStyle() == 0 ) {
			oldBrush = (CBrush *)pDC->SelectStockObject( NULL_BRUSH );
		}	else	{
			oldBrush = pDC->SelectObject( &brush );
		}

		// データ描画
		POINT *pDataPnt = NULL;
		if(data.GetLineStyle().iStyle != PS_NULL)	{
			pDataPnt = new POINT[iDataMax+1];
		}

		double dXp;
		double dYp;
		if(data.GetXscale().IsLogMode())	{
			//エラー防止
			if( data[0].dX > 0.0)	{	dXp = log10( data[0].dX );	}
			else					{	dXp = DBL_MIN_10_EXP;		}

		}
		else						{	
			dXp = data[0].dX;
			if(data.IsReversalX())		{	dXp *= -1.0;	}
		}
		if(data.GetYscale().IsLogMode())	{
			//エラー防止
			if( data[0].dY > 0.0)	{	dYp = log10( data[0].dY );	}
			else					{	dYp = DBL_MIN_10_EXP;		}
		}
		else						{
			dYp = data[0].dY;
			if(data.IsReversalY())		{	dYp *= -1.0;	}
		}
	
		int iX = FtoL( ( dXp - dXOrg ) / dXRange * rect.Width() );
		int iY = FtoL( ( dYMax - dYp ) / dYRange * rect.Height() );
		if(pDataPnt != NULL)	{
			pDataPnt[0].x = iX;
			pDataPnt[0].y = iY;
		}
	
		// マーカー出力
		if( data.GetMarkerEdge() == 0 ){
			::DrawMark( pDC, data.GetMarkerStyle().iMarker, CPoint( iX, iY ), data.GetMarkerStyle().iMarkSize );
		}
		
		int iMarkEnd = iDataMax - data.GetMarkerEdge();// マーカー出力
		for( int i = 1; i <= iDataMax; i++ ){
			if(data.GetXscale().IsLogMode())	{	
				if( data[i].dX > 0.0)	{	dXp = log10( data[i].dX );	}
				else					{	dXp = DBL_MIN_10_EXP;		}
			}	else					{
				dXp = data[i].dX;
				if(data.IsReversalX())		{	dXp *= -1.0;	}
			}
			if(data.GetYscale().IsLogMode())	{
				if( data[i].dY > 0.0)	{	dYp = log10( data[i].dY );	}
				else					{	dYp = DBL_MIN_10_EXP;		}
			}	else					{	
				dYp = data[i].dY;
				if(data.IsReversalY())		{	dYp *= -1.0;	}
			}
			iX = FtoL( ( dXp - dXOrg ) / dXRange * rect.Width() );
			iY = FtoL( ( dYMax - dYp ) / dYRange * rect.Height() );
			if(pDataPnt != NULL)	{
				pDataPnt[i].x = iX;
				pDataPnt[i].y = iY;
			}
			// マーカー出力
			if( MARKNONE != data.GetMarkerStyle().iMarker )	{
				if(i >= data.GetMarkerEdge() && i <= iMarkEnd)	{
					if(i == data.GetMarkerEdge() || i == iMarkEnd)	{
						::DrawMark( pDC, data.GetMarkerStyle().iMarker, CPoint( iX, iY ), data.GetMarkerStyle().iMarkSize );
					}	else	{
						if( (data.GetMarkerDelta() > 0 ) && (i%data.GetMarkerDelta()) == 0 ){
							::DrawMark( pDC, data.GetMarkerStyle().iMarker, CPoint( iX, iY ), data.GetMarkerStyle().iMarkSize );
						}
					}
				}
			}
		}
		if(pDataPnt != NULL)	{
			pDC->Polyline( pDataPnt, iDataMax+1 );
			delete[] pDataPnt;
		}

		// ブラシを戻す
		pDC->SelectObject( oldBrush );
		// ブラシの破棄
		brush.DeleteObject();

		// ペンを戻す＆破棄
		pDC->SelectObject( pOldPen );
		pen.DeleteObject();

		// 原点を戻す
		pDC->SetViewportOrg( oldOrg );
	}
}
/**
 * 	カーソルの描画.
 * 		カーソルを描画する
 * 
 * 	@param pDC		描画するデバイスコンテキストのポインタ
 * 	@param rect		描画領域の範囲
  */
void CAXGraphCtrl::DrawLineCursor( CDC *pDC, const CRect &rect )
{
	// クリッピング領域の保存
	CRect clipRect;
	pDC->GetClipBox( clipRect );
	// クリッピング領域の設定
	pDC->IntersectClipRect( rect );

	CRect itemRect = rect;
	// サイズの変更
	itemRect.right -= 1;
	itemRect.bottom -= 1;

	// フォントの取得
	LOGFONT logfont;
	pDC->GetCurrentFont()->GetLogFont( &logfont );
	// FontSize
	if(GetCursorFontSize() > 0)	{
		logfont.lfHeight = -MulDiv(GetCursorFontSize(), pDC->GetDeviceCaps(LOGPIXELSY), 72);
	}

	// フォントの作成?選択
	CFont font;
	font.CreateFontIndirect( &logfont );
	CFont *pOldFont = pDC->SelectObject( &font );

	if(1)	{
	// カーソル描画
	for( int i = 0; i < m_plotCursor.GetSize(); i++ ){
		int nLayer = m_plotCursor[ i ].GetLayer();
		if( nLayer >= 0 && nLayer < GetLineNum())	{
			CAXGDIPlotCtrl::DrawPlotCursor( pDC, itemRect, m_plotData[nLayer], m_plotCursor[ i ]);
		}	else	{
			CAXGDIPlotCtrl::DrawPlotCursor( pDC, itemRect, m_plotCursor[ i ]);
		}
	}
	
	}

	// フォントを戻す
	pDC->SelectObject( pOldFont );
	font.DeleteObject();
	// サイズを戻す。
	itemRect.right += 1;
	itemRect.bottom += 1;

	// クリップ領域を元に戻す
	pDC->SelectClipRgn( NULL );
	pDC->IntersectClipRect( clipRect );
}
/**
 * 	Active状態の描画.
 * 		Active状態を表示する
 * 
 * 	@param pDC		描画するデバイスコンテキストのポインタ
 * 	@param rect		描画領域の範囲
 */
void CAXGraphCtrl::DrawActiveState( CDC *pDC, const CRect &rect )
{
	if(m_activeInfo.nActive == AXGCTRLACT_NONE)	{	return;	}	///< 0:非選択
	if( !GetSafeHwnd() )						{	return;	}
	if( GetFocus() == this || 1 )	{//フォーカスがある時。
		const int c_size = 7;
		// ブラシの作成
		CBrush	brush;
		brush.CreateSolidBrush(GetBkColor());
		// ブラシの選択
		CBrush *pOldBrush = pDC->SelectObject( &brush );
		// 描画モードを変更
		int iOldRop = pDC->SetROP2( R2_NOT );
		///< 0:非選択/1:全体/2:データ/3:カーソル/4:エリアカーソル
		if(m_activeInfo.nActive == AXGCTRLACT_DATA)	{
			//ラインスタイルを変更
			LINESTYLE lineStyle = m_plotData[m_activeInfo.iLayer].GetLineStyle();
			m_plotData[m_activeInfo.iLayer].SetLineStyle(PS_NULL,~GetBkColor());
			//マーカースタイルを変更
			MARKERSTYLE markStyle = m_plotData[m_activeInfo.iLayer].GetMarkerStyle();
			m_plotData[m_activeInfo.iLayer].SetMarkerStyle(MARKSQUARE, 9, 1);
			//マーカーデルタを変更
			int iMarkDelta = m_plotData[m_activeInfo.iLayer].GetMarkerDelta();
			int iMarkEdge = m_plotData[m_activeInfo.iLayer].GetMarkerEdge();
			m_plotData[m_activeInfo.iLayer].SetMarkerDelta((int)(m_plotData[m_activeInfo.iLayer].GetNum() / 40), 0);
			
			//描画
			DrawLayerData( pDC, rect, m_plotData[m_activeInfo.iLayer] );
		
			//マーカーデルタを戻す
			m_plotData[m_activeInfo.iLayer].SetMarkerDelta( iMarkDelta, iMarkEdge );
			//マーカースタイルを戻す
			m_plotData[m_activeInfo.iLayer].SetMarkerStyle( markStyle );
			//ラインスタイルを戻す
			m_plotData[m_activeInfo.iLayer].SetLineStyle(lineStyle);

		}	else if(m_activeInfo.nActive == AXGCTRLACT_CURSOL)	{
			CRect rectItem = rect;
			CAXPlotCursor &cursor = GetPlotCursor(m_activeInfo.iIndex);
			int cursorMode = cursor.GetCursorMode();
			//X
			if( cursorMode == CURSORX || cursorMode == CURSORCROSS ){
				int iXp;
				if(cursor.GetLayer() >= 0)	{
					CXYPlotData &data = m_plotData[m_activeInfo.iLayer];
					int index = cursor.GetPos();
					double dXrvs = 1.0;
					if(data.IsReversalX() && (!data.GetXscale().IsLogMode()))		{	dXrvs = -1.0;	}
					iXp = rect.left + data.GetXscale().Data2PointX( data.dataX(index) * dXrvs, rect.Width());
				}	else	{
					iXp = rect.left + GetAxisX().Data2PointX( cursor.GetValue().dX, rect.Width() );
				}
				//中上
				rectItem.top = rect.top;
				rectItem.bottom = rectItem.top + c_size;
				rectItem.left = iXp - c_size / 2;
				rectItem.right = rectItem.left + c_size;
				pDC->Rectangle( rectItem );
				//中下
				rectItem.top = rect.bottom - c_size;
				rectItem.bottom = rect.bottom;
				pDC->Rectangle( rectItem );
			}
			//Y
			if( cursorMode == CURSORY || cursorMode == CURSORCROSS ){
				int iYp;
				if(cursor.GetLayer() >= 0)	{
					CXYPlotData &data = m_plotData[m_activeInfo.iLayer];
					int index = cursor.GetPos();
					double dYrvs = 1.0;
					if(data.IsReversalY() && (!data.GetYscale().IsLogMode()))		{	dYrvs = -1.0;	}
					iYp = rect.top + data.GetYscale().Data2PointY( data.dataY(index) * dYrvs, rect.Height());
				}	else	{
					iYp = rect.top + GetAxisY().Data2PointY( cursor.GetValue().dY, rect.Height());
				}
				rectItem.top =  iYp - c_size / 2;
				rectItem.bottom = rectItem.top + c_size;
				//左中
				rectItem.left = rect.left;
				rectItem.right = rect.left + c_size;
				pDC->Rectangle( rectItem );
				//右中
				rectItem.left = rect.right - c_size;
				rectItem.right = rect.right;
				pDC->Rectangle( rectItem );
			}
		}	else if(m_activeInfo.nActive == AXGCTRLACT_AREACSL)	{
			CRect rectItem = rect;
			CAXAreaCursor &cursor = GetAreaCursor(m_activeInfo.iIndex);
			int cursorMode = cursor.GetCursorMode();
			if(cursor.GetLayer() >= 0)	{
				CXYPlotData &data = m_plotData[m_activeInfo.iLayer];
				int iHeadPos = cursor.GetHeadPos();
				int iTailPos = cursor.GetTailPos();
				// Xエリアカーソル描画
				if( cursorMode == CURSORX || cursorMode == CURSORCROSS ){
					double dXrvs = 1.0;
					if(data.IsReversalX() && (!data.GetXscale().IsLogMode()))		{	dXrvs = -1.0;	}
					rectItem.left = rect.left + data.GetXscale().Data2PointX( data.dataX(iHeadPos) * dXrvs, rect.Width() );
					rectItem.right = rect.left + data.GetXscale().Data2PointX( data.dataX(iTailPos) * dXrvs, rect.Width() );
				}
				// Yエリアカーソル描画
				if( cursorMode == CURSORY || cursorMode == CURSORCROSS ){
					double dYrvs = 1.0;
					if(data.IsReversalY() && (!data.GetYscale().IsLogMode()))		{	dYrvs = -1.0;	}
					rectItem.top = rect.top + data.GetYscale().Data2PointY( data.dataY(iHeadPos) * dYrvs, rect.Height() );
					rectItem.bottom = rect.top + data.GetYscale().Data2PointY( data.dataY(iTailPos) * dYrvs, rect.Height() );
				}
			}	else	{
				// Xエリアカーソル描画
				if( cursorMode == CURSORX || cursorMode == CURSORCROSS ){
					rectItem.left = rect.left + GetAxisX().Data2PointX( cursor.GetHeadValue().dX, rect.Width() );
					rectItem.right = rect.left + GetAxisX().Data2PointX( cursor.GetTailValue().dX, rect.Width() );
				}
				// Yエリアカーソル描画
				if( cursorMode == CURSORY || cursorMode == CURSORCROSS ){
					rectItem.top = rect.top + GetAxisY().Data2PointY( cursor.GetHeadValue().dY, rect.Height() );
					rectItem.bottom = rect.top + GetAxisY().Data2PointY( cursor.GetTailValue().dY, rect.Height() );
				}
			}
			rectItem.NormalizeRect();
			//rectItem.top += 1;
			//rectItem.right += 1;
			DrawActiveFrame( pDC, rectItem, c_size);
		}	else if(m_activeInfo.nActive == AXGCTRLACT_FRAME)	{
			DrawActiveFrame( pDC, rect, c_size );
		}
		// 描画モードを戻す
		pDC->SetROP2( iOldRop );
		// ブラシを戻す
		pDC->SelectObject( pOldBrush );
		// ブラシの破棄
		brush.DeleteObject();
	}
}
//200612 t.tachibana added start>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
///////////////////////////////////////
/**
 * 	WM_ERASEBKGND時処理
 * 		tachibana 200612	
 * 
 * 	@param pDC		描画するデバイスコンテキストのポインタ
 */
BOOL CAXGraphCtrl::OnEraseBkgnd(CDC *pDC)
{
	return 0;
}
///////////////////////////////////////
/**
 * 	データの表示範囲設定.
 * 		グラフ全体のデータの表示範囲を設定する。\n
 *		tachibana 200612
 * 
 * 	@param dMin			データのX表示Min範囲
 * 	@param dMax			データのX表示Max範囲
 * 	@param dDelta		グラフの目盛り/グリッドの間隔(データ値指定)
 * 	@param dDetailDelta	グラフの詳細目盛り間隔(データ値指定)
 * 	@param bAllLayer	TRUE:全データレイヤーに対して/FALSE:全体グラフのスケールのみ
 */
void CAXGraphCtrl::SetXScaleEx( double dMin, double dMax, double dDelta /*= -1.0*/, double dDetailDelta /*= -1*/, BOOL bAllLayer /*= FALSE*/, BOOL bRedraw)
{
	if(bAllLayer)	{
		int iLineMax = m_plotData.GetUpperBound();
		for( int i = 0; i <= iLineMax; i++ ){
			m_plotData[i].GetXscale().SetScale( dMin, dMax );
		}
	}
	GetAxisX().SetScale( dMin, dMax, dDelta, dDetailDelta );
	if (bRedraw) Redraw(TRUE);
}
///////////////////////////////////////
/**
 * 	データの表示範囲設定.
 * 		グラフ全体のデータの表示範囲を設定する。\n
 *		tachibana 200612
 * 
 * 	@param dMin			データのY表示Min範囲
 * 	@param dMax			データのY表示Max範囲
 * 	@param dDelta		グラフの目盛り/グリッドの間隔(データ値指定)
 * 	@param dDetailDelta	グラフの詳細目盛り間隔(データ値指定)
 * 	@param bAllLayer	TRUE:全データレイヤーに対してスケール設定/FALSE:全体グラフのスケールのみ設定
 */
void CAXGraphCtrl::SetYScaleEx( double dMin, double dMax, double dDelta /*= -1.0*/, double dDetailDelta /*= -1*/, BOOL bAllLayer /*= FALSE*/, BOOL bRedraw)
{
	if(bAllLayer)	{
		int iLineMax = m_plotData.GetUpperBound();
		for( int i = 0; i <= iLineMax; i++ ){
			m_plotData[i].GetYscale().SetScale( dMin, dMax );
		}
	}
	GetAxisY().SetScale( dMin, dMax, dDelta, dDetailDelta );
	if (bRedraw) Redraw(TRUE);
}
//200612 t.tachibana added end<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
