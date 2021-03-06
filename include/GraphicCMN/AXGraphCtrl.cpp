// AXGraphCtrl.cpp : CAXGraphCtrlのインプリメンテ�`ション
//
/********************************************************
// CAXGraphCtrl		:グラフ宙鮫クラス
//												by YOTSUTSU
//	* History	:	date:2005,24,Mar.	仟�ﾗ�撹
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
 * 	@param bkColor	グラフの嘘尚
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
 * 	コピ�`コンストラクタ
 * 
 * 	@param graphCtrl	コピ�`圷グラフ
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
// CAXGraphCtrl メッセ�`ジ ハンドラ
/////////////////////////////////////////////////////////////////////////////
/// ウィンドウ恬撹�rのメッセ�`ジハンドラ
void CAXGraphCtrl::PreSubclassWindow() 
{
	CAXGDIPlotCtrl::PreSubclassWindow();
}
///////////////////////////////////////
/// ウィンドウ篤���rのメッセ�`ジハンドラ
void CAXGraphCtrl::OnDestroy() 
{
	CAXGDIPlotCtrl::OnDestroy();
	//
	RemoveAllItem();
}
///////////////////////////////////////
BOOL CAXGraphCtrl::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: この了崔に耕嗤の�I尖を弖紗するか、または児云クラスを柵び竃してください
	if( GetSafeHwnd() && (GetFocus() == this))	{
		switch(pMsg->message)	{
		case WM_KEYDOWN:
			if(m_activeInfo.nActive == AXGCTRLACT_CURSOL)	{///< 3:カ�`ソル
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
/// ウィンドウ宙鮫�rのメッセ�`ジハンドラ
void CAXGraphCtrl::BeginPaintDC( CDC *pDC, const CRect &rect )
{
	// 壅宙鮫秤�麋ゝ叩�リセット
	int iLineMax = m_plotData.GetUpperBound();
	for( int i = 0; i <= iLineMax; i++ ){
		m_bRedraw |= m_plotData[i].m_bRedraw;
		m_plotData[i].m_bRedraw = FALSE;
	}
}
///////////////////////////////////////
//Activeなアイテムを�筝�する。
BOOL CAXGraphCtrl::OnChangeActive( AXGCNOTIFY *pNotifyMsg )
{
	m_activeInfo = pNotifyMsg->activeInfo;	///< Active彜�Bの秤��
	Redraw();
	return TRUE;
}
///////////////////////////////////////
//Activeなアイテムのスタイルを�筝�する。
BOOL CAXGraphCtrl::OnChangeStyle( AXGCNOTIFY *pNotifyMsg )
{
	///< 0:掲�x�k/1:畠悶/2:デ�`タ/3:カ�`ソル/4:エリアカ�`ソル
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
//Activeなアイテムのスケ�`ルを�筝�する。
BOOL CAXGraphCtrl::OnChangeScale( AXGCNOTIFY *pNotifyMsg )
{
	return FALSE;
}
///////////////////////////////////////
//Activeなカ�`ソルの了崔を厚仟する。
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
/// マウス恣ボタン兀和の�rのActivate
int CAXGraphCtrl::MouseLBdownActivate( const CRect &rect, CPoint point, AXGCACTINFO *lpActiveInfo )
{
	AXGCACTINFO &tempActiveInfo = (*lpActiveInfo);

	///< 0:掲�x�k/1:畠悶/2:デ�`タ/3:カ�`ソル/4:エリアカ�`ソル
	tempActiveInfo.nActive = AXGCTRLACT_NONE;

	int iXp = -1;
	int iYp = -1;
	const int c_iChkPoint = 5;//クリックしたpointと宙鮫pointとのチェックする����
	
	if( rect.Width() <= 0 )		{	return AXGCTRLACT_NONE;	}
	if( rect.Height() <= 0 )	{	return AXGCTRLACT_NONE;	}
	CPoint ptData = point;
	for( int iLayer = 0; iLayer < GetLineNum(); iLayer++ ){
		///< 0:掲�x�k/1:畠悶/2:デ�`タ/3:カ�`ソル/4:エリアカ�`ソル
		if(tempActiveInfo.nActive != AXGCTRLACT_NONE)	{	break;	}
		tempActiveInfo.iLayer = iLayer;	///< Activeなカ�`ソルのレイヤ�`
		tempActiveInfo.iLine = 0;		///< Activeなレイヤ�`ライン桑催
		CXYPlotData &data = m_plotData[iLayer];
		ptData = point;
		//クリックポイントからXの�､鯒鵑瓩襦�
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
		///////////////////デ�`タに��して、Active辛嬬か�{べる。//////////////////////////////////
		for( int index = 1; index < m_plotData[iLayer].GetNum(); index++ ){
			if(!m_plotData[iLayer].IsVisible())							{	break;	}
			if( index >= m_plotData[iLayer].GetNum() )		{	break;	}
			tempActiveInfo.iIndex = index;	///< Activeなデ�`タのインデックス
			iXp = m_plotData[iLayer].GetXscale().Data2PointX( m_plotData[iLayer][index-1].dX, rect.Width() );
			iYp = m_plotData[iLayer].GetYscale().Data2PointY( m_plotData[iLayer][index-1].dY, rect.Height() );
			//恙�砲硫遒鯒鵑瓩襦�
			int iXCheck = iXp - ptData.x;
			int iYCheck = iYp - ptData.y;
			if(iXCheck >= -c_iChkPoint && iXCheck <= c_iChkPoint && iYCheck >= -c_iChkPoint && iYCheck <= c_iChkPoint)	{
				///< 0:掲�x�k/1:畠悶/2:デ�`タ/3:カ�`ソル/4:エリアカ�`ソル
				tempActiveInfo.nActive = AXGCTRLACT_DATA;	TRACE("LineActivate[index-1]:%d\n",index-1);
				tempActiveInfo.iIndex = -1;
				return tempActiveInfo.nActive;
			}
			iXp = m_plotData[iLayer].GetXscale().Data2PointX( m_plotData[iLayer][index].dX, rect.Width() );
			iYp = m_plotData[iLayer].GetYscale().Data2PointY( m_plotData[iLayer][index].dY, rect.Height() );
			//恙�砲硫遒鯒鵑瓩襦�
			iXCheck = iXp - ptData.x;
			iYCheck = iYp - ptData.y;
			if(iXCheck >= -c_iChkPoint && iXCheck <= c_iChkPoint && iYCheck >= -c_iChkPoint && iYCheck <= c_iChkPoint)	{
				///< 0:掲�x�k/1:畠悶/2:デ�`タ/3:カ�`ソル/4:エリアカ�`ソル
				tempActiveInfo.nActive = AXGCTRLACT_DATA;	TRACE("LineActivate[index]:%d\n",index);
				tempActiveInfo.iIndex = -1;
				return tempActiveInfo.nActive;
			}

			bInside = FALSE;
			//Xがデ�`タの念瘁の���貭擇任△譴弌�
			if(m_plotData[iLayer][index-1].dX < m_plotData[iLayer][index].dX)	{
				if((dValX >= m_plotData[iLayer][index-1].dX) && (dValX <= m_plotData[iLayer][index].dX))	{	bInside = TRUE;	}
			}	else	{
				if((dValX <= m_plotData[iLayer][index-1].dX) && (dValX >= m_plotData[iLayer][index].dX))	{	bInside = TRUE;	}
			}
			if(bInside)	{
				//XからYを箔める。
				dValue =  (m_plotData[iLayer][index].dY - m_plotData[iLayer][index-1].dY) / (m_plotData[iLayer][index].dX - m_plotData[iLayer][index-1].dX) * ( dValX - m_plotData[iLayer][index-1].dX) +  m_plotData[iLayer][index-1].dY;
				//YからY恙�砲鯒鵑瓩襦�
				iYp = m_plotData[iLayer].GetYscale().Data2PointY( dValue , rect.Height() );
				//恙�砲硫遒鯒鵑瓩襦�
				int iCheck = iYp - ptData.y;
				if(iCheck >= -c_iChkPoint && iCheck <= c_iChkPoint)	{
					///< 0:掲�x�k/1:畠悶/2:デ�`タ/3:カ�`ソル/4:エリアカ�`ソル
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
				//YからXを箔める。
				dValue = ( dValY - m_plotData[iLayer][index-1].dY ) / (m_plotData[iLayer][index].dY - m_plotData[iLayer][index-1].dY) * (m_plotData[iLayer][index].dX - m_plotData[iLayer][index-1].dX) + m_plotData[iLayer][index-1].dX;
				//XからX恙�砲鯒鵑瓩襦�
				iXp = m_plotData[iLayer].GetXscale().Data2PointX( dValue, rect.Width() );
				//恙�砲硫遒鯒鵑瓩襦�
				int iCheck = iXp - ptData.x;
				if(iCheck >= -c_iChkPoint && iCheck <= c_iChkPoint)	{
					///< 0:掲�x�k/1:畠悶/2:デ�`タ/3:カ�`ソル/4:エリアカ�`ソル
					tempActiveInfo.nActive = AXGCTRLACT_DATA;		TRACE("%f,%f,%d,%d",dValX,dValY,iXp,ptData.x);	TRACE("xLineActivate\n");
					tempActiveInfo.iIndex = -1;
					return tempActiveInfo.nActive;
				}
			}
		}
	}
	if(1)	{
		///////////////////カ�`ソルに��して、Active辛嬬か�{べる。//////////////////////////////////
		ptData = point;
		for( int index = 0; index < GetPlotCursorNum(); index++ ){
			if(!GetPlotCursor(index).IsShowCursor())	{	continue;	}
			int cursorMode = GetPlotCursor(index).GetCursorMode();
			int iLayer = GetPlotCursor(index).GetLayer();
			tempActiveInfo.iLayer = iLayer;		///< Activeなレイヤ�`桑催				-1:�o�� 0オリジン
			tempActiveInfo.iIndex = index;		///< Activeなカ�`ソルのインデックス
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
						///< 0:掲�x�k/1:畠悶/2:デ�`タ/3:カ�`ソル/4:エリアカ�`ソル
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
						///< 0:掲�x�k/1:畠悶/2:デ�`タ/3:カ�`ソル/4:エリアカ�`ソル
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
						///< 0:掲�x�k/1:畠悶/2:デ�`タ/3:カ�`ソル/4:エリアカ�`ソル
						tempActiveInfo.nActive = AXGCTRLACT_CURSOL;	TRACE("CursorActivate\n");
						return tempActiveInfo.nActive;
					}
				}
				//Y
				if( cursorMode == CURSORY || cursorMode == CURSORCROSS ){
					iYp = GetAxisY().Data2PointY( GetPlotCursor(index).GetValue().dY, rect.Height());
					iYp -= ptData.y;
					if(iYp >= -c_iChkPoint && iYp <= c_iChkPoint)	{
						///< 0:掲�x�k/1:畠悶/2:デ�`タ/3:カ�`ソル/4:エリアカ�`ソル
						tempActiveInfo.nActive = AXGCTRLACT_CURSOL;	TRACE("CursorActivate\n");
						return tempActiveInfo.nActive;
					}
				}
			}
		}
	}
	if(1)	{
		///////////////////エリアカ�`ソルに��して、Active辛嬬か�{べる。//////////////////////////////////
		for( int index = 0; index < GetAreaCursorNum(); index++ ){
			if(!GetAreaCursor( index ).IsShowCursor() )		{	continue;	}
			int iLayer = GetAreaCursor( index ).GetLayer();
			int cursorMode = GetAreaCursor( index ).GetCursorMode();
			tempActiveInfo.iIndex = index;		///< Activeなカ�`ソルのインデックス
			tempActiveInfo.iLayer = iLayer;		///< Activeなレイヤ�`桑催				-1:�o�� 0オリジン
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
	tempActiveInfo.iLine = -1;		///< Activeなレイヤ�`ライン桑催
	tempActiveInfo.iIndex = -1;

	return AXGCTRLACT_FRAME;
}
///////////////////////////////////////
// public
///////////////////////////////////////
/**
 * 	グラフを宙鮫する.
 * 		峺協されたDCにグラフを宙鮫する
 * 
 * 	@param pDC	宙鮫するDC
 * 	@param rect	宙鮫する�I囃のRECT
 */
void CAXGraphCtrl::DrawGraph( CDC *pDC, const CRect &rect )
{
	// 嘘尚弼の隠隔
	COLORREF orgBkColor = pDC->GetBkColor();
	
	// 嘘尚の宙鮫
	pDC->FillSolidRect( rect, (pDC->IsPrinting() ? IWHITE : GetBkColor()) );

	// クリッピング�I囃の隠贋
	CRect clipRect;
	pDC->GetClipBox( clipRect );

	// クリッピング�I囃の�O協
	pDC->IntersectClipRect( rect );

	// 嘘尚モ�`ドの�筝�
	int iBkMode = pDC->SetBkMode( TRANSPARENT );

	// グリッド��(畠悶)の宙鮫
	CRect rectGraph = rect;
	rectGraph.right -= 1;
	rectGraph.bottom -= 1;

	int iLineMax = m_plotData.GetUpperBound();
	if(1)	{
	// エリアカ�`ソル宙鮫
	for( int i = 0; i < GetAreaCursorNum(); i++ ){
		int nLayer = GetAreaCursor(i).GetLayer();
		if( nLayer >= 0 && nLayer < GetLineNum())	{
			CAXGDIPlotCtrl::DrawAreaCursor( pDC, rectGraph, m_plotData[nLayer], GetAreaCursor(i) );
		}	else	{
			CAXGDIPlotCtrl::DrawAreaCursor( pDC, rectGraph, GetAreaCursor(i) );
		}
	}
	}

	if(m_bShowGridX)	{	///< 燕幣嗤�殖�X�S��
		DrawGrid( pDC, GRIDX, rectGraph, m_gridX.GetLineStyle() );
	}
	if(m_bShowGridY)	{	///< 燕幣嗤�殖�Y�S��
		DrawGrid( pDC, GRIDY, rectGraph, m_gridY.GetLineStyle() );
	}

	// フォントの函誼
	LOGFONT logfont;
	pDC->GetCurrentFont()->GetLogFont( &logfont );
	// FontSize
	if(GetAreaCsrFontSize() > 0)	{
		logfont.lfHeight = -MulDiv(GetAreaCsrFontSize(), pDC->GetDeviceCaps(LOGPIXELSY), 72);
	}	
	// フォントの恬撹?�x�k
	CFont font;
	font.CreateFontIndirect( &logfont );
	CFont *pOldFont = pDC->SelectObject( &font );

	if(1)	{
	// エリアカ�`ソル宙鮫
	for( int i = 0; i < GetAreaCursorNum(); i++ ){
		int nLayer = GetAreaCursor(i).GetLayer();
		if( nLayer >= 0 && nLayer < GetLineNum())	{
			CAXGDIPlotCtrl::DrawAreaCursor( pDC, rectGraph, m_plotData[nLayer], GetAreaCursor(i), TRUE );
		}	else	{
			CAXGDIPlotCtrl::DrawAreaCursor( pDC, rectGraph, GetAreaCursor(i), TRUE );
		}
	}
	}
	// フォントを��す
	pDC->SelectObject( pOldFont );
	font.DeleteObject();

	if(IsShowPlotScaleX())	{///< プロットデ�`タのスケ�`ルを燕幣嗤�殖�X�S��
		int index = 0;
		int showLine = GetShowLineNum();
		for( int i = 0; i <= iLineMax; i++ ){
			if( GetLine(i).IsVisible() ) {
				DrawPlotScale( pDC, rectGraph, AX_GDIXMODE, index, showLine,GetLine(i).GetLineColor(), GetLine(i).GetXscale().GetMin(), GetLine(i).GetXscale().GetMax() );
				index++;
			}
		}
	}
	if(IsShowPlotScaleY())	{///< プロットデ�`タのスケ�`ルを燕幣嗤�殖�X�S��
		int index = 0;
		int showLine = GetShowLineNum();
		for( int i = 0; i <= iLineMax; i++ ){
			if( GetLine(i).IsVisible() ) {
				DrawPlotScale( pDC, rectGraph, AX_GDIYMODE, index, showLine,GetLine(i).GetLineColor(), GetLine(i).GetYscale().GetMin(), GetLine(i).GetYscale().GetMax() );
				index++;
			}
		}
	}
	if(IsShowPlotName())	{///< プロットデ�`タ兆各の燕幣嗤��
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

	//X axis 朕腹り宙鮫
	if(GetAxisX().IsShowScale())	{
		DrawMeasure( pDC, rectGraph , GetAxisX() );
	}
	//Y axis 朕腹り宙鮫
	if(GetAxisY().IsShowScale())	{
		DrawMeasure( pDC, rectGraph , GetAxisY() );
	}

	//フレ�`ムの宙鮫
	if(IsFrameVisible())	{
		CBrush brush( (IsMonochrome() ? RGB(0,0,0) : GetFrameColor()) );
		pDC->FrameRect( rect, &brush );
	}
	
	// デ�`タ宙鮫
	for( int i = 0; i <= iLineMax; i++ ){
		if( m_plotData[i].IsVisible() ) {
			int iMarkerSize;
			if(pDC->IsPrinting())	{//咫泡�rの�a屎
				if(GetInitSize().cy > 0)	{
					iMarkerSize = FtoL(m_plotData[i].GetMarkerSize() * rect.Height() / GetInitSize().cy);
					iMarkerSize = m_plotData[i].SetMarkerSize(iMarkerSize);
				}	else	{
					iMarkerSize = m_plotData[i].GetMarkerSize();
				}
			}
			DrawLayerData( pDC, rectGraph, m_plotData[i] );

			if(pDC->IsPrinting())	{//咫泡�rの�a屎��し
				m_plotData[i].SetMarkerSize(iMarkerSize);
			}
		}
	}

	// 嘘尚弼を��す
	pDC->SetBkColor( orgBkColor );

	// 嘘尚モ�`ドを��す
	pDC->SetBkMode( iBkMode );

	// クリップ�I囃を圷に��す
	pDC->SelectClipRgn( NULL );
	pDC->IntersectClipRect( clipRect );
}
///////////////////////////////////////
/**
 * 	デ�`タの燕幣���贅O協.
 * 		グラフ畠悶のデ�`タの燕幣���譴鰓O協する。\n
 * 
 * 	@param dMin			デ�`タのX燕幣Min����
 * 	@param dMax			デ�`タのX燕幣Max����
 * 	@param dDelta		グラフの朕腹り/グリッドの�g侯(デ�`タ�ﾖ原�)
 * 	@param dDetailDelta	グラフの����朕腹り�g侯(デ�`タ�ﾖ原�)
 * 	@param bAllLayer	TRUE:畠デ�`タレイヤ�`に��して/FALSE:畠悶グラフのスケ�`ルのみ
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
 * 	デ�`タの燕幣���贅O協.
 * 		グラフ畠悶のデ�`タの燕幣���譴鰓O協する。\n
 * 
 * 	@param dMin			デ�`タのY燕幣Min����
 * 	@param dMax			デ�`タのY燕幣Max����
 * 	@param dDelta		グラフの朕腹り/グリッドの�g侯(デ�`タ�ﾖ原�)
 * 	@param dDetailDelta	グラフの����朕腹り�g侯(デ�`タ�ﾖ原�)
 * 	@param bAllLayer	TRUE:畠デ�`タレイヤ�`に��してスケ�`ル�O協/FALSE:畠悶グラフのスケ�`ルのみ�O協
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
 * 	グラフ畠悶のX�Sの��方グラフの燕幣�O協.
 * 		グラフ畠悶のX�Sの��方グラフ燕幣を�O協する。\n
 * 
 * 	@param	bLog		��方スケ�`ル		TRUE:嗤��/FALSE:�o��
 * 	@param	bScaleAuto	��方オ�`トスケ�`ル	TRUE:嗤��/FALSE:�o��
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
 * 	グラフ畠悶のX�Sの��方グラフの燕幣�O協.
 * 		グラフ畠悶のX�Sの��方グラフ燕幣を�O協する。\n
 * 
 * 	@param	bLog		��方スケ�`ル		TRUE:嗤��/FALSE:�o��
 * 	@param	bScaleAuto	��方オ�`トスケ�`ル	TRUE:嗤��/FALSE:�o��
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
 * 	スクロ�`ルする.
 * 		グラフ畠悶をスクロ�`ルする。
 * 
 * 	@param iScrollX	Xスクロ�`ル楚
 * 	@param iScrollY	Yスクロ�`ル楚
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
 * 	畠デ�`タレイヤ�`の恷弌�｣ψ邊��､鬟�リアする.
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
 * 	オ�`トスクロ�`ル�C嬬をON/OFFする.
 * 
 * 	@param bEnable	オ�`トスクロ�`ルを嗤�燭砲垢襪�のフラグ(TRUE:ON FALSE:OFF)
 * 	@return			參念の�S辛彜�Bを卦す。
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
 * 	オ�`トスケ�`ル�C嬬をON/OFFする.
 * 
 * 	@param bEnable	オ�`トスケ�`ルを嗤�燭砲垢襪�のフラグ(TRUE:ON FALSE:OFF)
 * 	@return			參念の�S辛彜�Bを卦す。
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
 * 	グラフを��寄する.
 * 		rectZoomで嚥えられた�I囃を��寄する
 * 
 * 	@param rectZoom	��寄する�I囃
 */
void CAXGraphCtrl::Zoom( CRect rectZoom )
{
	// グラフの����
	CRect graphRect;
	GetClientRect( graphRect );

	// 屎�ｻ�
	rectZoom.NormalizeRect();
	rectZoom &= graphRect;

	// �S方を箔める
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
	// ���阿���寄
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
 * 	レイヤ�`デ�`タの宙鮫.
 * 		嚥えられたレイヤ�`のデ�`タを宙鮫する
 * 
 * 	@param pDC		宙鮫するデバイスコンテキストのポインタ
 * 	@param rect		宙鮫�I囃の����
 * 	@param data		プロットするレイヤ�`デ�`タ
 */
void CAXGraphCtrl::DrawLayerData( CDC *pDC, const CRect &rect, CXYPlotData &data )
{
	// デ�`タ宙鮫
	int iDataMax = data.GetNum() - 1;
	if( iDataMax >= 0 ){
		// 宙鮫圻泣�O協
		CPoint oldOrg = pDC->SetViewportOrg( rect.left, rect.top );

		// 嫌と互さを函誼
		double dWidth = (double)rect.Width();
		double dHeight= (double)rect.Height();

		// デ�`タ圻泣�O協
		double dXOrg = data.GetXscale().GetDrawOrg();
		double dXRange = data.GetXscale().GetDrawRange();
		double dYOrg = data.GetYscale().GetDrawOrg();
		double dYRange = data.GetYscale().GetDrawRange();
		double dYMax = dYRange + dYOrg;
	
		//宙鮫弼
		COLORREF	color = data.GetLineStyle().color;
		//モノクロ
		if(IsMonochrome())	{ color = IBLACK;	} 
		// ペンの恬撹
		CLinePen pen;
		int penStyle = data.GetLineStyle().iStyle;
		if(data.GetLineStyle().iStyle == PS_NULL && MARKNONE != data.GetMarkerStyle().iMarker)	{
			penStyle = PS_SOLID;
		}
		pen.CreatePen( penStyle, data.GetLineStyle().iSize, color );
		// ペンの�x�k
		CPen *pOldPen = pDC->SelectObject( &pen );
		//モノクロ
		if(IsMonochrome())	{ color = Color2Gray( data.GetLineStyle().color );	} 
		// ブラシの恬撹
		CBrush	brush( color );
		// ブラシの�x�k
		CBrush *oldBrush = NULL;
		if(data.GetMarkerBkStyle() == 0 ) {
			oldBrush = (CBrush *)pDC->SelectStockObject( NULL_BRUSH );
		}	else	{
			oldBrush = pDC->SelectObject( &brush );
		}

		// デ�`タ宙鮫
		POINT *pDataPnt = NULL;
		if(data.GetLineStyle().iStyle != PS_NULL)	{
			pDataPnt = new POINT[iDataMax+1];
		}

		double dXp;
		double dYp;
		if(data.GetXscale().IsLogMode())	{
			//エラ�`契峭
			if( data[0].dX > 0.0)	{	dXp = log10( data[0].dX );	}
			else					{	dXp = DBL_MIN_10_EXP;		}

		}
		else						{	
			dXp = data[0].dX;
			if(data.IsReversalX())		{	dXp *= -1.0;	}
		}
		if(data.GetYscale().IsLogMode())	{
			//エラ�`契峭
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
	
		// マ�`カ�`竃薦
		if( data.GetMarkerEdge() == 0 ){
			::DrawMark( pDC, data.GetMarkerStyle().iMarker, CPoint( iX, iY ), data.GetMarkerStyle().iMarkSize );
		}
		
		int iMarkEnd = iDataMax - data.GetMarkerEdge();// マ�`カ�`竃薦
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
			// マ�`カ�`竃薦
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

		// ブラシを��す
		pDC->SelectObject( oldBrush );
		// ブラシの篤��
		brush.DeleteObject();

		// ペンを��す�ζ���
		pDC->SelectObject( pOldPen );
		pen.DeleteObject();

		// 圻泣を��す
		pDC->SetViewportOrg( oldOrg );
	}
}
/**
 * 	カ�`ソルの宙鮫.
 * 		カ�`ソルを宙鮫する
 * 
 * 	@param pDC		宙鮫するデバイスコンテキストのポインタ
 * 	@param rect		宙鮫�I囃の����
  */
void CAXGraphCtrl::DrawLineCursor( CDC *pDC, const CRect &rect )
{
	// クリッピング�I囃の隠贋
	CRect clipRect;
	pDC->GetClipBox( clipRect );
	// クリッピング�I囃の�O協
	pDC->IntersectClipRect( rect );

	CRect itemRect = rect;
	// サイズの�筝�
	itemRect.right -= 1;
	itemRect.bottom -= 1;

	// フォントの函誼
	LOGFONT logfont;
	pDC->GetCurrentFont()->GetLogFont( &logfont );
	// FontSize
	if(GetCursorFontSize() > 0)	{
		logfont.lfHeight = -MulDiv(GetCursorFontSize(), pDC->GetDeviceCaps(LOGPIXELSY), 72);
	}

	// フォントの恬撹?�x�k
	CFont font;
	font.CreateFontIndirect( &logfont );
	CFont *pOldFont = pDC->SelectObject( &font );

	if(1)	{
	// カ�`ソル宙鮫
	for( int i = 0; i < m_plotCursor.GetSize(); i++ ){
		int nLayer = m_plotCursor[ i ].GetLayer();
		if( nLayer >= 0 && nLayer < GetLineNum())	{
			CAXGDIPlotCtrl::DrawPlotCursor( pDC, itemRect, m_plotData[nLayer], m_plotCursor[ i ]);
		}	else	{
			CAXGDIPlotCtrl::DrawPlotCursor( pDC, itemRect, m_plotCursor[ i ]);
		}
	}
	
	}

	// フォントを��す
	pDC->SelectObject( pOldFont );
	font.DeleteObject();
	// サイズを��す。
	itemRect.right += 1;
	itemRect.bottom += 1;

	// クリップ�I囃を圷に��す
	pDC->SelectClipRgn( NULL );
	pDC->IntersectClipRect( clipRect );
}
/**
 * 	Active彜�Bの宙鮫.
 * 		Active彜�Bを燕幣する
 * 
 * 	@param pDC		宙鮫するデバイスコンテキストのポインタ
 * 	@param rect		宙鮫�I囃の����
 */
void CAXGraphCtrl::DrawActiveState( CDC *pDC, const CRect &rect )
{
	if(m_activeInfo.nActive == AXGCTRLACT_NONE)	{	return;	}	///< 0:掲�x�k
	if( !GetSafeHwnd() )						{	return;	}
	if( GetFocus() == this || 1 )	{//フォ�`カスがある�r。
		const int c_size = 7;
		// ブラシの恬撹
		CBrush	brush;
		brush.CreateSolidBrush(GetBkColor());
		// ブラシの�x�k
		CBrush *pOldBrush = pDC->SelectObject( &brush );
		// 宙鮫モ�`ドを�筝�
		int iOldRop = pDC->SetROP2( R2_NOT );
		///< 0:掲�x�k/1:畠悶/2:デ�`タ/3:カ�`ソル/4:エリアカ�`ソル
		if(m_activeInfo.nActive == AXGCTRLACT_DATA)	{
			//ラインスタイルを�筝�
			LINESTYLE lineStyle = m_plotData[m_activeInfo.iLayer].GetLineStyle();
			m_plotData[m_activeInfo.iLayer].SetLineStyle(PS_NULL,~GetBkColor());
			//マ�`カ�`スタイルを�筝�
			MARKERSTYLE markStyle = m_plotData[m_activeInfo.iLayer].GetMarkerStyle();
			m_plotData[m_activeInfo.iLayer].SetMarkerStyle(MARKSQUARE, 9, 1);
			//マ�`カ�`デルタを�筝�
			int iMarkDelta = m_plotData[m_activeInfo.iLayer].GetMarkerDelta();
			int iMarkEdge = m_plotData[m_activeInfo.iLayer].GetMarkerEdge();
			m_plotData[m_activeInfo.iLayer].SetMarkerDelta((int)(m_plotData[m_activeInfo.iLayer].GetNum() / 40), 0);
			
			//宙鮫
			DrawLayerData( pDC, rect, m_plotData[m_activeInfo.iLayer] );
		
			//マ�`カ�`デルタを��す
			m_plotData[m_activeInfo.iLayer].SetMarkerDelta( iMarkDelta, iMarkEdge );
			//マ�`カ�`スタイルを��す
			m_plotData[m_activeInfo.iLayer].SetMarkerStyle( markStyle );
			//ラインスタイルを��す
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
				//嶄貧
				rectItem.top = rect.top;
				rectItem.bottom = rectItem.top + c_size;
				rectItem.left = iXp - c_size / 2;
				rectItem.right = rectItem.left + c_size;
				pDC->Rectangle( rectItem );
				//嶄和
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
				//恣嶄
				rectItem.left = rect.left;
				rectItem.right = rect.left + c_size;
				pDC->Rectangle( rectItem );
				//嘔嶄
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
				// Xエリアカ�`ソル宙鮫
				if( cursorMode == CURSORX || cursorMode == CURSORCROSS ){
					double dXrvs = 1.0;
					if(data.IsReversalX() && (!data.GetXscale().IsLogMode()))		{	dXrvs = -1.0;	}
					rectItem.left = rect.left + data.GetXscale().Data2PointX( data.dataX(iHeadPos) * dXrvs, rect.Width() );
					rectItem.right = rect.left + data.GetXscale().Data2PointX( data.dataX(iTailPos) * dXrvs, rect.Width() );
				}
				// Yエリアカ�`ソル宙鮫
				if( cursorMode == CURSORY || cursorMode == CURSORCROSS ){
					double dYrvs = 1.0;
					if(data.IsReversalY() && (!data.GetYscale().IsLogMode()))		{	dYrvs = -1.0;	}
					rectItem.top = rect.top + data.GetYscale().Data2PointY( data.dataY(iHeadPos) * dYrvs, rect.Height() );
					rectItem.bottom = rect.top + data.GetYscale().Data2PointY( data.dataY(iTailPos) * dYrvs, rect.Height() );
				}
			}	else	{
				// Xエリアカ�`ソル宙鮫
				if( cursorMode == CURSORX || cursorMode == CURSORCROSS ){
					rectItem.left = rect.left + GetAxisX().Data2PointX( cursor.GetHeadValue().dX, rect.Width() );
					rectItem.right = rect.left + GetAxisX().Data2PointX( cursor.GetTailValue().dX, rect.Width() );
				}
				// Yエリアカ�`ソル宙鮫
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
		// 宙鮫モ�`ドを��す
		pDC->SetROP2( iOldRop );
		// ブラシを��す
		pDC->SelectObject( pOldBrush );
		// ブラシの篤��
		brush.DeleteObject();
	}
}
//200612 t.tachibana added start>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
///////////////////////////////////////
/**
 * 	WM_ERASEBKGND�r�I尖
 * 		tachibana 200612	
 * 
 * 	@param pDC		宙鮫するデバイスコンテキストのポインタ
 */
BOOL CAXGraphCtrl::OnEraseBkgnd(CDC *pDC)
{
	return 0;
}
///////////////////////////////////////
/**
 * 	デ�`タの燕幣���贅O協.
 * 		グラフ畠悶のデ�`タの燕幣���譴鰓O協する。\n
 *		tachibana 200612
 * 
 * 	@param dMin			デ�`タのX燕幣Min����
 * 	@param dMax			デ�`タのX燕幣Max����
 * 	@param dDelta		グラフの朕腹り/グリッドの�g侯(デ�`タ�ﾖ原�)
 * 	@param dDetailDelta	グラフの����朕腹り�g侯(デ�`タ�ﾖ原�)
 * 	@param bAllLayer	TRUE:畠デ�`タレイヤ�`に��して/FALSE:畠悶グラフのスケ�`ルのみ
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
 * 	デ�`タの燕幣���贅O協.
 * 		グラフ畠悶のデ�`タの燕幣���譴鰓O協する。\n
 *		tachibana 200612
 * 
 * 	@param dMin			デ�`タのY燕幣Min����
 * 	@param dMax			デ�`タのY燕幣Max����
 * 	@param dDelta		グラフの朕腹り/グリッドの�g侯(デ�`タ�ﾖ原�)
 * 	@param dDetailDelta	グラフの����朕腹り�g侯(デ�`タ�ﾖ原�)
 * 	@param bAllLayer	TRUE:畠デ�`タレイヤ�`に��してスケ�`ル�O協/FALSE:畠悶グラフのスケ�`ルのみ�O協
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
