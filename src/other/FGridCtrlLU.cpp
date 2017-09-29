/**
 * 	@file	FGridCtrlLU.cpp
 *	VSFlexGrid 7.0 (Lingh/Unicode)の派生クラス
 * 
 * 	@date	2003.03.19	   n_yoshizaki	初版
 * 	@date	2003.07.16	   n_yoshizaki	継承に変更
 *	@date	2005.06.14	s.yotsutsu OCXの自己登録関数追加
 *	@date	2005.06.20	s.yotsutsu ExcelのEnter keyをsimulate
 */
#include "stdafx.h"
#include "FGridCtrlLU.h"

//Color
#define	BACK_COLOR	RGB( 0x00, 0x00, 0x00 )

//コンストラクタ
CFGridCtrlLU::CFGridCtrlLU()
{
	// OCXの自己登録
	RegisterMyself();

	//入力制限（入力されている次の行しか入力できない）時の行数を初期化
	m_iInputedLine = 0;

	//編集前に文字を表示判定するFlag（表示）
	m_bMode = TRUE;
	
	//入力前文字列
	m_strBefore = "";

	//Copy行数初期化
	m_iSelect = 0;

	//開始行番号初期化
	m_iLineNoStart = 1;

	//行番号描画フラグ初期化（行番号非描画）
	m_bLineNoDraw = FALSE;

	//行数、列数の初期化
	m_lTotalRow = 0;
	m_lTotalCol = 0;

	//default color setting
	m_BkColor = BACK_COLOR;

	m_nKeyCode = 0x0000;		///< key
	m_bExcelEnterMode = FALSE;	///< select next row after return key
}

//デストラクタ
CFGridCtrlLU::~CFGridCtrlLU()
{
}
/**
 * 	GridのSelf Registration
 * 	
 */
void CFGridCtrlLU::RegisterMyself(void)
{
	static BOOL s_bRegisterState = FALSE;	///<Registry登録情報 
	
	if(s_bRegisterState)	{	return;	}

	LPOLESTR szProgID[128] = { 0x00 };

	if(S_OK == ::ProgIDFromCLSID(GetClsid(), szProgID))	{
		s_bRegisterState = TRUE;
		return;
	}
	
	CString strFileName = _T("");
	strFileName.GetBufferSetLength(MAX_PATH);
	try	{
		if(GetModuleFileName( NULL, strFileName.GetBuffer(0), MAX_PATH ) == 0)	{
			throw -1;
		}

		int istrLen;
		int istrPos = strFileName.ReverseFind('\\');
		istrLen = strFileName.GetLength() - istrPos;
		strFileName.Delete(istrPos,istrLen);
		strFileName += _T("\\Vsflex7N.ocx");
#ifdef _DEBUG
		strFileName = _T("C:\\Program Files\\VSFLEX7\\Control\\Vsflex7N.ocx");
#endif	
		HRESULT (FAR STDAPICALLTYPE * lpDllEntryPoint)(void);
		OleInitialize( NULL );
		HINSTANCE hLib = LoadLibrary((LPCSTR)strFileName);
		if (hLib < (HINSTANCE)HINSTANCE_ERROR){
			throw -2;
		}
		(FARPROC&) lpDllEntryPoint = GetProcAddress(hLib,_T("DllRegisterServer"));
		if (lpDllEntryPoint == NULL)	{
			throw -3;
		}
		if (FAILED((*lpDllEntryPoint)())){
			throw -4;
		}
		OleUninitialize();
		FreeLibrary( hLib );
	}	catch( int error)	{
		CString strErrMsg = _T("");
		switch(error)	{
		case -1:	strErrMsg = _T("GetModuleFileName error!");	break;
		case -2:	strErrMsg = strFileName; strErrMsg += _T(" is can not find.");	break;
		case -3:	strErrMsg = _T("Not Dll Entry Point");	break;
		case -4:	strErrMsg = strFileName; strErrMsg += _T(" Registration error.");	break;
		default:	strErrMsg = _T("no error define.");	break;
		}
		MessageBox(strErrMsg,_T("Error!"));
		ASSERT(0);
		return;
	}
	
	s_bRegisterState = TRUE;
}
/**
 * 	process run after Instance create.
 * 		this process run after コンストラクタ
 * 	
 */
void CFGridCtrlLU::PreSubclassWindow() 
{
	//Initizalize Grid Settings
	Initialize();

	//必ず先頭行が表示されるように
	SetTopRow( 0 );

	//Girdのtotal行、列取得
	SetMaxRowCol();

	//入力制限行を固定行の次の行に設定
	m_iInputedLine = GetFixedRows();

	CVSFlexGridLU::PreSubclassWindow();
}

/**
 * 	GridのDefaultSetting
 * 	
 */
void CFGridCtrlLU::Initialize()
{
	//
}

/**
 *	SetされているInput Modeのindexを取得.
 *	
 *	@param		lRow	Input Mode 判定行
 *	@param		lCol	Input Mode 判定列
 *	@return				Input Mode Index（ 設定なしの場合はFREE_INPUT、FLEE編集不可の場合はNO_CHANGEを返す ）
 */
int CFGridCtrlLU::GetInputMode( long lRow, long lCol )
{
	int InputPtn = FREE_INPUT;	//default free input

	//separate mode to Input Mode0
	int iModeIndex = GetModeIndex( lRow, lCol );
	if( iModeIndex != -1 ){
		switch( ( INPUT_PTN )m_InputMode[iModeIndex].iInputMode ){
		case NO_CHANGE:		InputPtn = NO_CHANGE;	break;
		case INPUT_BOOL:
		case INPUT_INT:
		case INPUT_FLOAT:
		case INPUT_STRING:
		default:			InputPtn = iModeIndex;	break;	//Set Input Mode Index
		}
	}
	return( InputPtn );
}

/**
 * 	Input Range に指定Cellの登録情報があるかCheck.
 * 	
 * 	@param	lRow	Check Row
 * 	@param	lCol	Check Col
 * 	@return			登録Index（なければ-1を返す）
 */
int CFGridCtrlLU::GetModeIndex( long lRow, long lCol )
{
	for( int i = 0; i < m_InputMode.GetSize(); i++ ){
		if( lCol == m_InputMode.GetAt( i ).lCol && lRow == m_InputMode.GetAt( i ).lRow ){
			return( i );
		}
	}
	return( -1 );
}

/**
 * 	Input Mode に指定Cellの登録情報があるかCheck.
 * 	
 * 	@param	lRow	Check Row
 * 	@param	lCol	Check Col
 * 	@return			登録Index（なければ-1を返す）
 */
int CFGridCtrlLU::GetRangeIndex( long lRow, long lCol )
{
	for( int i = 0; i < m_InputRange.GetSize(); i++ ){
		if( lCol == m_InputRange.GetAt( i ).lCol && lRow == m_InputRange.GetAt( i ).lRow ){
			return( i );
		}
	}
	return( -1 );
}


BEGIN_EVENTSINK_MAP(CFGridCtrlLU, CVSFlexGridLU)
	//{{AFX_MSG_MAP(CFGridCtrlLU)
	ON_EVENT_REFLECT( CFGridCtrlLU, 21 /* BeforeEdit */, OnBeforeEdit, VTS_I4 VTS_I4 VTS_PBOOL )
	ON_EVENT_REFLECT( CFGridCtrlLU, 22 /* StartEdit */, OnStartEdit, VTS_I4 VTS_I4 VTS_PBOOL )
	ON_EVENT_REFLECT( CFGridCtrlLU, 24 /* AfterEdit */, OnAfterEdit, VTS_I4 VTS_I4 )
	ON_EVENT_REFLECT( CFGridCtrlLU, 25 /* KeyPressEdit */, OnKeyPressEdit, VTS_I4 VTS_I4 VTS_PI2)
	ON_EVENT_REFLECT( CFGridCtrlLU, 28 /* ChangeEdit */, OnChangeEdit, VTS_NONE )
	ON_EVENT_REFLECT( CFGridCtrlLU, -603 /* KeyPress */, OnKeyPress, VTS_PI2 )
	ON_EVENT_REFLECT( CFGridCtrlLU, -604 /* KeyUp */, OnKeyUp, VTS_PI2 VTS_I2)
	//}}AFX_MSG_MAP
END_EVENTSINK_MAP()
/**
 * 	編集前操作.
 * 
 * 	@param	lRow		選択行
 * 	@param	lCol		選択列
 *	@param	Cancel		TRUE:編集不可 FALSE:編集可能（ default:FALSE ）
 */
void CFGridCtrlLU::OnBeforeEdit( long Row, long Col, BOOL FAR* Cancel )
{
	if( NO_CHANGE != ( m_iInputMode = GetInputMode( Row, Col ) ) ){
		if(m_bExcelEnterMode)	{
			if(m_nKeyCode == VK_RETURN)	{
				long lSelRow = Row + 1;
				if(GetRows() != lSelRow)	{	///<Grid全行
					SetRow(lSelRow);
				//	keybd_event(VK_DOWN, 0, 0, 0) ;
				//	keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0) ;
				}
				*Cancel = TRUE;
			}
			m_nKeyCode = 0x0000;
		}
	}
	
	SendDlgItemMessage(this->GetDlgCtrlID(), 21 /* BeforeEdit */ );
}
/**
 * 	編集前文字列保存.
 * 
 * 	@param	lRow		選択行
 * 	@param	lCol		選択列
 *	@param	Cancel		TRUE:編集不可 FALSE:編集可能（ default:FALSE ）
 */
void CFGridCtrlLU::OnStartEdit( long lRow, long lCol, BOOL FAR* Cancel )
{
	//Get Input Mode Index
	if( NO_CHANGE == ( m_iInputMode = GetInputMode( lRow, lCol ) ) ){
		*Cancel = TRUE;
	}
	
	m_strBefore = GetString( lRow, lCol );
	//モードによって編集に移行する時に編集前の文字列を表示/非表示
	if( m_bMode ){
		//m_strBefore.TrimLeft();
		//this->SetEditText(m_strBefore);
		SetTextMatrix( lRow, lCol, m_strBefore );
	}	else	{
		SetTextMatrix( lRow, lCol, "" );
	}
//	SendMessage( 22 /* OnStartEdit */ );
	SendDlgItemMessage(this->GetDlgCtrlID(), 22 /* OnStartEdit */ );
}

/**
 * 	編集中文字列入力チェック.
 * 	
 */
void CFGridCtrlLU::OnChangeEdit()
{
	if( m_iInputMode != FREE_INPUT ){
		switch( ( INPUT_PTN )m_InputMode[m_iInputMode].iInputMode ){
		case INPUT_BOOL:	OnChangeEditBool  ();																											break;
		case INPUT_INT:		OnChangeEditInt   ( m_InputMode[m_iInputMode].iIntNum, m_InputMode[m_iInputMode].bMinus );										break;
		case INPUT_FLOAT:	OnChangeEditFloat ( m_InputMode[m_iInputMode].iIntNum, m_InputMode[m_iInputMode].iDecNum, m_InputMode[m_iInputMode].bMinus );	break;
		case INPUT_DOUBLE:	OnChangeEditDouble( m_InputMode[m_iInputMode].iIntNum, m_InputMode[m_iInputMode].iDecNum, m_InputMode[m_iInputMode].bMinus );	break;
		case INPUT_STRING:	OnChangeEditString( m_InputMode[m_iInputMode].iIntNum );																		break;
		default:																																			break;
		}
	}
//	SendMessage( 28 /* OnChangeEdit */ );
	SendDlgItemMessage(this->GetDlgCtrlID(), 28 /* OnChangeEdit */ );
}

/**
 * 	入力後のチェック.
 * 
 * 	@param lRow		選択行
 * 	@param lCol		選択列
 */
void CFGridCtrlLU::OnAfterEdit( long lRow, long lCol )
{
	//Range Check
	int iRangeIndex = GetRangeIndex( lRow, lCol );
	if( iRangeIndex != -1 ){
		switch( ( INPUT_PTN )m_InputRange.GetAt( iRangeIndex ).iInputMode ){
		case INPUT_INT:		IntRangeChk   ( lRow, lCol, m_InputRange.GetAt( iRangeIndex ).min.iNum, m_InputRange.GetAt( iRangeIndex ).max.iNum );	break;
		case INPUT_FLOAT:	FloatRangeChk ( lRow, lCol, m_InputRange.GetAt( iRangeIndex ).min.fNum, m_InputRange.GetAt( iRangeIndex ).max.fNum );	break;
		case INPUT_DOUBLE:	DoubleRangeChk( lRow, lCol, m_InputRange.GetAt( iRangeIndex ).min.dNum, m_InputRange.GetAt( iRangeIndex ).max.dNum );	break;
		default:			break;
		}
	}

	if( m_iInputMode != FREE_INPUT ){
		switch( ( INPUT_PTN )m_InputMode[m_iInputMode].iInputMode ){
		case INPUT_BOOL:	OnAfterEditBool  ( lRow, lCol );									break;
		case INPUT_INT:		OnAfterEditInt   ( lRow, lCol );									break;
		case INPUT_FLOAT:	OnAfterEditFloat ( lRow, lCol, m_InputMode[m_iInputMode].iDecNum );	break;
		case INPUT_DOUBLE:	OnAfterEditDouble( lRow, lCol, m_InputMode[m_iInputMode].iDecNum );	break;
		case INPUT_STRING:	OnAfterEditString( lRow, lCol );									break;
		default:	break;
		}
	}
//	SendMessage( 24 /* OnAfterEdit */ );
	SendDlgItemMessage(this->GetDlgCtrlID(), 24 /* OnAfterEdit */);
}
/*
 * 
 * 	@param lRow		選択行
 * 	@param lCol		選択列
 */
void CFGridCtrlLU::OnKeyPressEdit( long Row, long Col, short FAR* KeyAscii)
{
	m_nKeyCode = (*KeyAscii);
	//SendMessage( 25 /* KeyPressEdit */ );
	SendDlgItemMessage(this->GetDlgCtrlID(), 25 /* KeyPressEdit */ );
}
/*
 * 
 */
void CFGridCtrlLU::OnKeyPress( short FAR* KeyAscii ) 
{
	m_nKeyCode = (*KeyAscii);
	SendDlgItemMessage(this->GetDlgCtrlID(), -603 /* KeyPress */ );
}
/*
 * 
 */
void CFGridCtrlLU::OnKeyUp( short FAR* KeyCode, short Shift )
{
//	if(m_bExcelEnterMode)	{
//		if( (*KeyCode == VK_RETURN) && (m_nKeyCode == VK_RETURN))	{
//			long lSelRow = GetRow() + 1;
//			if(GetRows() != lSelRow)	{	///<Grid全行
//				SetRow(lSelRow);
//			//	keybd_event(VK_DOWN, 0, 0, 0) ;
//			//	keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0) ;
///			}
//		}
//		m_nKeyCode = 0x0000;
//	}
	//
	SendDlgItemMessage(this->GetDlgCtrlID(), -604 /* KeyUp */);
}
/**
 * 	BOOL型入力チェック.
 * 		未使用
 * 
 */
void CFGridCtrlLU::OnChangeEditBool()
{
	long lRow = GetRowSel();
	long lCol = GetColSel();
	CString str = GetEditText();

	int iBool = atoi( str );

	if( iBool == 0 ){	//pending BOOL型チェックない
		
	}else{
		
	}
}

/**
 * 	int型入力チェック.
 * 
 * 	@param iIntNum		入力最大桁数
 * 	@param bMinus		マイナス許可フラグ（TRUE = 許可, FALSE = 不可）
 */
void CFGridCtrlLU::OnChangeEditInt( int iIntNum, BOOL bMinus )
{
	long lRow = GetRowSel();
	long lCol = GetColSel();
	CString str = GetEditText();
	int iStrLength = str.GetLength();

	char ch;
	for( int i = 0; i < iStrLength; i++ ){
		ch = str.GetAt( i );
		//マイナスチェック
		if( i == 0 && ch == '-' && bMinus ){
			iIntNum++;	//先頭がマイナスの時はマイナス分を桁数から除くため
			continue;
		}
		//桁数チェック
		if( iStrLength > iIntNum ){
			DelOverString( str, iIntNum );
			break;
		}
		//入力チェック
		if( !NumChk( ch ) ){
			DelOverString( str, i );
			break;
		}
	}
}

/**
 * 	float型入力チェック.
 * 
 * 	@param iIntNum		整数部入力最大桁数
 * 	@param iDecNum		小数部入力最大桁数
 * 	@param bMinus		マイナス許可フラグ（TRUE = 許可, FALSE = 不可）
 */
void CFGridCtrlLU::OnChangeEditFloat( int iIntNum, int iDecNum, BOOL bMinus )
{
	OnChangeEditDouble( iIntNum, iDecNum, bMinus );
}

/**
 * 	double型入力チェック.
 * 
 * 	@param iIntNum		整数部入力最大桁数
 * 	@param iDecNum		小数部入力最大桁数
 * 	@param bMinus		マイナス許可フラグ（TRUE = 許可, FALSE = 不可）
 */
void CFGridCtrlLU::OnChangeEditDouble( int iIntNum, int iDecNum, BOOL bMinus )
{
	long lRow = GetRowSel();
	long lCol = GetColSel();
	CString str = GetEditText();
	int iStrLength = str.GetLength();

	int iIntCnt = 0;
	int iDecCnt = 0;
	BOOL bDecFlg = FALSE;
	char ch;

	if( iDecNum <= 0 ){	//小数点以下が無い場合
		OnChangeEditInt( iIntNum, bMinus );
		return;
	}

	for( int i = 0; i < iStrLength; i++ ){
		ch = str.GetAt( i );
		//マイナスチェック
		if( i == 0 && ch == '-' && bMinus ){
			iIntNum++;	//先頭がマイナスの時はマイナス分を桁数から除くため
			iIntCnt++;	//文字カウントも進める
			continue;
		}
		//小数点チェック
		if( ch == '.' ){
			//1文字目に小数点は入力不可
			if( i == 0 ){
				SetEditText( "" );
				break;
			}
			//小数点が複数入った場合
			if( bDecFlg ){
				DelOverString( str, i );
				break;
			}
			bDecFlg = TRUE;
			continue;
		}
		//少数部桁数チェック
		if( bDecFlg ){
			iDecCnt++;
			if( iDecCnt > iDecNum ){
				DelOverString( str, iIntCnt + 1 + iDecNum );	//+1は小数点分
				break;
			}
		//整数部桁数チェック
		}else{
			iIntCnt++;
			if( iIntCnt > iIntNum ){
				DelOverString( str, iIntNum );
				break;
			}
		}
		//入力チェック
		if( !NumChk( ch ) ){
			DelOverString( str, i );
			break;
		}
	}
}

/**
 * 	string型入力チェック.
 * 
 * 	@param iLength	入力最大文字数
 */
void CFGridCtrlLU::OnChangeEditString( int iLength )
{
	long lRow = GetRowSel();
	long lCol = GetColSel();
	CString str = GetEditText();
	int iStrLength = str.GetLength();

	//文字数チェック
	if( iStrLength > iLength  ){
		DelOverString( str, iLength );
	}
}

/**
 * 	入力後BOOL型のチェック.
 * 		未使用
 * 	
 * 	@param lRow		選択行
 * 	@param lCol		選択列
 */
void CFGridCtrlLU::OnAfterEditBool( long lRow, long lCol )
{
	CString str = GetString( lRow, lCol );

	//pending BOOL型ない
}

/**
 * 	入力後int型のチェック.
 * 
 * 	@param lRow		選択行
 * 	@param lCol		選択列
 */
void CFGridCtrlLU::OnAfterEditInt( long lRow, long lCol )
{
	CString str = GetString( lRow, lCol );

	//入力なし
	if( str.GetLength() == 0 ){
		SetTextMatrix( lRow, lCol, m_strBefore );
		return;
	}
	//000とかの複数0を0にする
	int iNum = atoi( str );
	CString strTemp;
	strTemp.Format( "%d", iNum );
	SetTextMatrix( lRow, lCol, strTemp );
}

/**
 * 	入力後float型のチェック.
 * 
 * 	@param lRow		選択行
 * 	@param lCol		選択列
 * 	@param iDecNum	小数点以下桁数
 */
void CFGridCtrlLU::OnAfterEditFloat( long lRow, long lCol, int iDecNum )
{
	OnAfterEditDouble( lRow, lCol, iDecNum );
}

/**
 * 	入力後double型のチェック.
 * 
 * 	@param lRow		選択行
 * 	@param lCol		選択列
 * 	@param iDecNum	小数点以下桁数
 */
void CFGridCtrlLU::OnAfterEditDouble( long lRow, long lCol, int iDecNum )
{
	CString str = GetString( lRow, lCol );

	//入力なし
	if( str.GetLength() == 0 ){
		SetTextMatrix( lRow, lCol, m_strBefore );
		return;
	}
	//桁数を揃える
	float fNum = ( float )atof( str );
	CString strTemp;
	strTemp.Format( "%.*f", iDecNum, fNum );
	SetTextMatrix( lRow, lCol, strTemp );
}

/**
 * 	入力後string型のチェック.
 * 
 * 	@param lRow		選択行
 * 	@param lCol		選択列
 */
void CFGridCtrlLU::OnAfterEditString( long lRow, long lCol )
{
	CString str = GetString( lRow, lCol );

#if 0	//文字列の場合は空も許可
	//入力なし
	if( str.GetLength() == 0 ){
		SetTextMatrix( lRow, lCol, m_strBefore );
		return;
	}
#endif
}

/**
 * int値の範囲チェック.
 * 		OnChangeEditから呼ぶ
 * 	
 * @param	lRow	CheckするSelの行
 * @param	lCol	CheckするSelの列
 * @param	iMin	最小値
 * @param	iMax	最大値
 * @return			TRUE:範囲内 FALSE:範囲外
 */
BOOL CFGridCtrlLU::IntRangeChk( long lRow, long lCol, int iMin, int iMax )
{
	int iNum = GetInt( lRow, lCol );

	//最小、最大が逆で入ってきたら、反転する
	if( iMin > iMax ){
		int temp = iMax;
		iMax = iMin;
		iMin = temp;
	}

	if( iNum < iMin || iNum > iMax ){
		SetString( lRow, lCol, m_strBefore );
		return( FALSE );
	}
	return( TRUE );
}

/**
 * float値の範囲チェック.
 * 		OnChangeEditから呼ぶ
 * 	
 * @param	lRow	CheckするSelの行
 * @param	lCol	CheckするSelの列
 * @param	fMin	最小値
 * @param	fMax	最大値
 * @return			TRUE:範囲内 FALSE:範囲外
 */
BOOL CFGridCtrlLU::FloatRangeChk( long lRow, long lCol, float fMin, float fMax )
{
	float fNum = GetFloat( lRow, lCol );

	//最小、最大が逆で入ってきたら、反転する
	if( fMin > fMax ){
		float temp = fMax;
		fMax = fMin;
		fMin = temp;
	}

	if( fNum < fMin || fNum > fMax ){
		SetString( lRow, lCol, m_strBefore );
		return( FALSE );
	}
	return( TRUE );
}

/**
 * double値の範囲チェック.
 * 		OnChangeEditから呼ぶ
 * 	
 * @param	lRow	CheckするSelの行
 * @param	lCol	CheckするSelの列
 * @param	dMin	最小値
 * @param	dMax	最大値
 * @return			TRUE:範囲内 FALSE:範囲外
 */
BOOL CFGridCtrlLU::DoubleRangeChk( long lRow, long lCol, double dMin, double dMax )
{
	double dNum = GetDouble( lRow, lCol );

	//最小、最大が逆で入ってきたら、反転する
	if( dMin > dMax ){
		double temp = dMax;
		dMax = dMin;
		dMin = temp;
	}

	if( dNum < dMin || dNum > dMax ){
		SetString( lRow, lCol, m_strBefore );
		return( FALSE );
	}
	return( TRUE );
}

/**
 * 入力文字が数字かどうかcheck
 * 
 * 	@param	cCh		check charactor
 *	@return			TRUE:number FALSE:not number
 */
BOOL CFGridCtrlLU::NumChk( char cCh )
{
	if( cCh < '0' || cCh > '9' ){
		return( FALSE );
	}
	return( TRUE );
}

/**
 * 入力が指定を超えた場合、入力errorの場合はその文字を削除して再表示する
 * 
 * 	@param	str		文字列
 *	@param	iDelIdx	削除される先頭文字Index
 */
void CFGridCtrlLU::DelOverString( CString str, int iDelIdx )
{
	str.Delete( iDelIdx, str.GetLength() - iDelIdx );
	SetEditText( str );
}

/**
 * セルを編集中にする
 * 
 * 	@param lRow		選択行
 * 	@param lCol		選択列
 */
void CFGridCtrlLU::EditCell( long lRow, long lCol )
{
	COleVariant row, col;
	row = ( long )lRow;
	col = ( long )lCol;

	Select( lRow, lCol, row, col );

	CVSFlexGridLU::EditCell();
}

/**
 * 	カレントセルを設定
 * 
 * 	@param lRow		選択行
 * 	@param lCol		選択列
 */
void CFGridCtrlLU::SetCurCell( long lRow /* = 0 */, long lCol /* = 0 */ )
{
	COleVariant RowEnd, ColEnd;	//選択終了行,列
	//選択開始行,列と一致
	if( lRow > GetRows() ){	lRow = GetRows();	}
	if( lCol > GetCols() ){	lCol = GetCols();	}

	RowEnd = ( long )lRow;
	ColEnd = ( long )lCol;

	Select( lRow, lCol, RowEnd, ColEnd );
}

/**
 * 	カレントセルを取得
 * 
 * 	@param lRow		選択行
 * 	@param lCol		選択列
 */
void CFGridCtrlLU::GetCurCell( long& lRow, long& lCol )
{
	lRow = GetRow();
	lCol = GetCol();
}

/**
 *	default font Color set
 *	
 * 	@param	defaultColor	Default Font Color
 */
void CFGridCtrlLU::SetDefaultFontColor( COLORREF defaultColor )
{
	long Row = GetRow();	//現在設定されている選択行を保存
	long Col = GetCol();

	COleVariant row, col;
	row = (long)( GetRows() - 1 );	//indexなので-1
	col = (long)( GetCols() - 1 );	//

	SetFillStyle( 1 );	//選択行の全てを影響範囲にする
	Select( GetFixedRows(), GetFixedCols(), row, col );
	SetCellForeColor( defaultColor );
	SetFillStyle( 0 );	//カレントセルのみ影響範囲にする

	SetCurCell( Row, Col );	//選択範囲を戻す
}

/**
 *	Line Color Change.
 * 		Row以下の行の文字色を変更
 *	
 *	@param	lRow		文字色変更判定行
 * 	@param	noUseColor	No Use line Font Color
 */
void CFGridCtrlLU::ChangeUnderRowColor( long lRow, COLORREF noUseColor )
{
	long Row = GetRow();	//現在設定されている選択行を保存
	long Col = GetCol();

	COleVariant row, col;
	row = (long)( GetRows() - 1 );	//indexなので-1
	col = (long)( GetCols() - 1 );	//

	SetFillStyle( 1 );	//選択行の全てを影響範囲にする
	if( lRow < GetRows() ){
		Select( lRow, GetFixedCols(), row, col );
		SetCellForeColor( noUseColor );
	}
	SetFillStyle( 0 );	//カレントセルのみ影響範囲にする

	SetCurCell( Row, Col );	//選択範囲を戻す
}

/**
 * 	Cellのfont Color Change.
 * 	
 * 	@param	lRow			Color Change Row
 * 	@param	lCol			Color Change Col
 * 	@param	fixedFontColor	Fixed lRow Font Color
 */
void CFGridCtrlLU::SetCellFontColor( long lRow, long lCol, COLORREF fixedFontColor )
{
	long Row = GetRow();	//現在設定されている選択行を保存
	long Col = GetCol();

	SetRow( lRow );
	SetCol( lCol );

	SetCellForeColor( fixedFontColor );

	SetCurCell( Row, Col );	//選択範囲を戻す
}

/**
 * 	行のfont Color Change.
 * 	
 * 	@param	lRow			Color Change Row
 * 	@param	fixedFontColor	Fixed lRow Font Color
 */
void CFGridCtrlLU::SetRowFontColor( long lRow, COLORREF fixedFontColor )
{
	long Row = GetRow();	//現在設定されている選択行を保存
	long Col = GetCol();

	COleVariant row, col;
	row = (long)lRow;
	col = (long)( GetCols() - 1 );

	SetFillStyle( 1 );	//選択行の全てを影響範囲にする
	Select( lRow, GetFixedCols(), row, col );
	SetCellForeColor( fixedFontColor );
	SetFillStyle( 0 );	//カレントセルのみ影響範囲にする

	SetCurCell( Row, Col );	//選択範囲を戻す
}

/**
 * 	行のfont Color Change.
 * 	
 * 	@param	lRowStart		Color Change Row Start
 * 	@param	lRowEnd			Color Change Row End
 * 	@param	fixedFontColor	Fixed lRow Font Color
 */
void CFGridCtrlLU::SetRowFontColor( long lRowStart, long lRowEnd, COLORREF fixedFontColor )
{
	long Row = GetRow();	//現在設定されている選択行を保存
	long Col = GetCol();

	COleVariant row, col;
	row = (long)lRowEnd;
	col = (long)( GetCols() - 1 );

	SetFillStyle( 1 );	//選択行の全てを影響範囲にする
	Select( lRowStart, GetFixedCols(), row, col );
	SetCellForeColor( fixedFontColor );
	SetFillStyle( 0 );	//カレントセルのみ影響範囲にする

	SetCurCell( Row, Col );	//選択範囲を戻す
}

/**
 * 	列のfont Color Change.
 * 	
 * 	@param	lCol			Color Change Col
 * 	@param	fixedFontColor	Fixed Col Font Color
 */
void CFGridCtrlLU::SetColFontColor( long lCol, COLORREF fixedFontColor )
{
	long Row = GetRow();	//現在設定されている選択行を保存
	long Col = GetCol();

	COleVariant row, col;
	row = (long)( GetRows() - 1 );
	col = (long)lCol;

	SetFillStyle( 1 );	//選択行の全てを影響範囲にする
	Select( GetFixedRows(), lCol, row, col );
	SetCellForeColor( fixedFontColor );
	SetFillStyle( 0 );	//カレントセルのみ影響範囲にする

	SetCurCell( Row, Col );	//選択範囲を戻す
}

/**
 * 	列のfont Color Change.
 * 	
 * 	@param	lColStart		Color Change Col Start
 * 	@param	lColEnd			Color Change Col End
 * 	@param	fixedFontColor	Fixed Col Font Color
 */
void CFGridCtrlLU::SetColFontColor( long lColStart, long lColEnd, COLORREF fixedFontColor )
{
	long Row = GetRow();	//現在設定されている選択行を保存
	long Col = GetCol();

	COleVariant row, col;
	row = (long)( GetRows() - 1 );
	col = (long)lColEnd;

	SetFillStyle( 1 );	//選択行の全てを影響範囲にする
	Select( GetFixedRows(), lColStart, row, col );
	SetCellForeColor( fixedFontColor );
	SetFillStyle( 0 );	//カレントセルのみ影響範囲にする

	SetCurCell( Row, Col );	//選択範囲を戻す
}

/**
 * 	CellのBackground Color Change.
 * 	
 * 	@param	lRow			Color Change Row
 * 	@param	lCol			Color Change Col
 * 	@param	fixedBkColor	Fixed lRow Background Color
 */
void CFGridCtrlLU::SetCellBkColor( long lRow, long lCol, COLORREF fixedBkColor )
{
	//6	flexcpBackColor	
	SetCell( 6, COleVariant(lRow), COleVariant(lCol), COleVariant(lRow), COleVariant(lCol), COleVariant((long)fixedBkColor) );

//DELL	long Row = GetRow();	//現在設定されている選択行を保存
//DELL	long Col = GetCol();

//DELL	COleVariant row, col;
//DELL	row = (long)lRow;
//DELL	col = (long)lCol;

//DELL	SetFillStyle( 1 );	//選択行の全てを影響範囲にする
//DELL	Select( lRow, lCol, row, col );
//DELL	SetCellBackColor( fixedBkColor );
//DELL	SetFillStyle( 0 );	//カレントセルのみ影響範囲にする

//DELL	SetCurCell( Row, Col );	//選択範囲を戻す
}

/**
 * 	行のBackground Color Change.
 * 	
 * 	@param	lRow			Color Change Row
 * 	@param	fixedBkColor	Fixed lRow Background Color
 */
void CFGridCtrlLU::SetRowBkColor( long lRow, COLORREF fixedBkColor )
{
	long Row = GetRow();	//現在設定されている選択行を保存
	long Col = GetCol();

	COleVariant row, col;
	row = (long)lRow;
	col = (long)( GetCols() - 1 );

	SetFillStyle( 1 );	//選択行の全てを影響範囲にする
	Select( lRow, GetFixedCols(), row, col );
	SetCellBackColor( fixedBkColor );
	SetFillStyle( 0 );	//カレントセルのみ影響範囲にする

	SetCurCell( Row, Col );	//選択範囲を戻す
}

/**
 * 	行のBackground Color Change.
 * 	
 * 	@param	lRowStart		Color Change Row Start
 * 	@param	lRowEnd			Color Change Row End
 * 	@param	fixedBkColor	Fixed lRow Background Color
 */
void CFGridCtrlLU::SetRowBkColor( long lRowStart, long lRowEnd, COLORREF fixedBkColor )
{
	long Row = GetRow();	//現在設定されている選択行を保存
	long Col = GetCol();

	COleVariant row, col;
	row = (long)lRowEnd;
	col = (long)( GetCols() - 1 );

	SetFillStyle( 1 );	//選択行の全てを影響範囲にする
	Select( lRowStart, GetFixedCols(), row, col );
	SetCellBackColor( fixedBkColor );
	SetFillStyle( 0 );	//カレントセルのみ影響範囲にする

	SetCurCell( Row, Col );	//選択範囲を戻す
}

/**
 * 	列のBackground Color Change.
 * 	
 * 	@param	lCol			Color Change Col
 * 	@param	fixedBkColor	Fixed lRow Background Color
 */
void CFGridCtrlLU::SetColBkColor( long lCol, COLORREF fixedBkColor )
{
	long Row = GetRow();	//現在設定されている選択行を保存
	long Col = GetCol();

	COleVariant row, col;
	row = (long)( GetRows() - 1 );
	col = (long)lCol;

	SetFillStyle( 1 );	//選択行の全てを影響範囲にする
	Select( GetFixedRows(), lCol, row, col );
	SetCellBackColor( fixedBkColor );
	SetFillStyle( 0 );	//カレントセルのみ影響範囲にする

	SetCurCell( Row, Col );	//選択範囲を戻す
}

/**
 * 	列のBackground Color Change.
 * 	
 * 	@param	lRowStart		Color Change Row Start
 * 	@param	lRowEnd			Color Change Row End
 * 	@param	fixedBkColor	Fixed lRow Background Color
 */
void CFGridCtrlLU::SetColBkColor( long lColStart, long lColEnd, COLORREF fixedBkColor )
{
	long Row = GetRow();	//現在設定されている選択行を保存
	long Col = GetCol();

	COleVariant row, col;
	row = (long)( GetRows() - 1 );
	col = (long)lColEnd;

	SetFillStyle( 1 );	//選択行の全てを影響範囲にする
	Select( GetFixedRows(), lColStart, row, col );
	SetCellBackColor( fixedBkColor );
	SetFillStyle( 0 );	//カレントセルのみ影響範囲にする

	SetCurCell( Row, Col );	//選択範囲を戻す
}

/**
 * 	指定CellのBorder color change.
 *		実はこの関数はあんまりいけてないので?????要修正
 * 	
 * 	@param	lRowStart		Border Color Change Start Row
 * 	@param	lColStart		Border Color Change Start Col
 * 	@param	lRowEnd			Border Color Change End Row
 * 	@param	lColEnd			Border Color Change End Col
 * 	@param	bMode			TRUE:全境界線を色換え FALSE:枠のみ色換え
 * 	@param	borederColor	Border Color
 */
void CFGridCtrlLU::SetCellBorderColor( long lRowStart, long lColStart, long lRowEnd /* = -1 */, long lColEnd /* = -1 */, BOOL bMode /* = TRUE */, COLORREF borederColor /* = RGB( 0x00, 0x00, 0x00 ) */ )
{
	long Row = GetRow();	//現在設定されている選択行を保存
	long Col = GetCol();

	//Select lRow/lCol Error
	if( ( lRowStart < 0  || lRowStart >= GetRows() ) ||
		( lRowEnd   < -1 || lRowEnd   >= GetRows() ) ||	//Endが-1の時はStart = EndとするのでOK
		( lColStart < 0  || lColStart >= GetCols() ) ||
		( lColEnd   < -1 || lColEnd   >= GetCols() ) ){
		return;
	}

	COleVariant row, col;
	row = ( long )lRowEnd;
	col = ( long )lColEnd;

	//if End lRow/lCol become default, End lRow/lCol is made the same as Start lRow/lCol
	if( lRowEnd == -1 ){	row = ( long )lRowStart;	}
	if( lColEnd == -1 ){	col = ( long )lColStart;	}

	//border line size
	const short c_sLeft       = 1;
	const short c_sRight      = 1;
	const short c_sTop        = 1;
	const short c_sBottom     = 1;
	const short c_sHorizontal = 1;
	const short c_sVertical   = 1;

	SetFillStyle( 1 );	//選択行の全てを影響範囲にする
	Select( lRowStart, lColStart, row, col );
	if( bMode ){
		CellBorder( borederColor, c_sLeft, c_sTop, c_sRight, c_sBottom, c_sVertical, c_sHorizontal );
	}else{
		CellBorder( borederColor, c_sLeft, c_sTop, c_sRight, c_sBottom, 0, 0 );
	}
	SetFillStyle( 0 );	//カレントセルのみ影響範囲にする

	SetCurCell( Row, Col );	//選択範囲を戻す
}

/**
 * 	Cellのfont Colorを取得.
 * 	
 * 	@param	lRow	取得したいRow
 * 	@param	lCol	取得したいCol
 *	@return			Font Color
 */
COLORREF CFGridCtrlLU::GetCellFontColor( long lRow, long lCol )
{
	//7	flexcpForeColor
	COleVariant varData = GetCell( 7, COleVariant(lRow), COleVariant(lCol), COleVariant(lRow), COleVariant(lCol) );
	COLORREF fontColor = RGB( 255,255,255 );

//DELL	long Row = GetRow();	//現在設定されている選択行を保存
//DELL	long Col = GetCol();

//DELL	COleVariant row, col;
//DELL	row = (long)lRow;
//DELL	col = (long)lCol;

//DELL	SetFillStyle( 1 );	//選択行の全てを影響範囲にする
//DELL	Select( lRow, lCol, row, col );

//DELL	COLORREF fontColor = GetCellForeColor();
//DELL	SetFillStyle( 0 );	//カレントセルのみ影響範囲にする

//DELL	SetCurCell( Row, Col );	//選択範囲を戻す

	if(varData.vt == VT_I4)	{	fontColor = varData.intVal;	}

	return( fontColor );
}

/**
 * 	CellのBackground Colorを取得.
 * 	
 * 	@param	lRow	取得したいRow
 * 	@param	lCol	取得したいCol
 *	@return			CellのBackground Color
 */
COLORREF CFGridCtrlLU::GetCellBkColor( long lRow, long lCol )
{
	//6	flexcpBackColor	
	COleVariant varData = GetCell( 6, COleVariant(lRow), COleVariant(lCol), COleVariant(lRow), COleVariant(lCol) );

//DELL	long Row = GetRow();	//現在設定されている選択行を保存
//DELL	long Col = GetCol();

//DELL	COleVariant row, col;
//DELL	row = (long)lRow;
//DELL	col = (long)lCol;
//
//DELL	SetFillStyle( 1 );	//選択行の全てを影響範囲にする
//DELL	Select( lRow, lCol, row, col );
	COLORREF bkColor = RGB( 255,255,255 );
//DELL	GetCellBackColor();
//DELL	SetFillStyle( 0 );	//カレントセルのみ影響範囲にする

//DELL	SetCurCell( Row, Col );	//選択範囲を戻す

	if(varData.vt == VT_I4)	{	bkColor = varData.intVal;	}

	return( bkColor );
}

/**
 * 	CellにBar Graphを描画する.
 * 	
 * 	@param	lRow	選択行
 * 	@param	lCol	選択列
 * 	@param	iValue	Barの値（ -100～100 ）
 */
void CFGridCtrlLU::SetBar( long lRow, long lCol, int iValue, COLORREF barColor /* = RGB( 0x00, 0xff, 0x00 ) */ )
{
	long Row = GetRow();	//現在設定されている選択行を保存
	long Col = GetCol();

	if( iValue < -100 || iValue > 100 ){
		return;
	}

	SetCurCell( lRow, lCol );
	SetCellFloodColor( barColor );
	SetCellFloodPercent( iValue );

	SetCurCell( Row, Col );	//選択範囲を戻す
}

/**
 * 	BOOL型 SetTextMatrix.
 * 	
 * 	@param	lRow	選択行
 * 	@param	lCol	選択列
 * 	@param	bBool	入力BOOL値
 */
void CFGridCtrlLU::SetBool( long lRow, long lCol, BOOL bBool )
{
	CString strTemp;

	strTemp.Format( "%d", bBool );
	SetTextMatrix( lRow, lCol, strTemp );
}

/**
 * 	int型 SetTextMatrix.
 * 	
 * 	@param	lRow	選択行
 * 	@param	lCol	選択列
 * 	@param	iNum	入力int値
 * 	@param	form	入力書式
 */
void CFGridCtrlLU::SetInt( long lRow, long lCol, int iNum, CString form /* = "%d" */ )
{
	CString strTemp;

	strTemp.Format( form, iNum );
	SetTextMatrix( lRow, lCol, strTemp );
}

/**
 * 	float型 SetTextMatrix.
 * 	
 * 	@param	lRow	選択行
 * 	@param	lCol	選択列
 * 	@param	fNum	入力float値
 * 	@param	form	入力書式
 */
void CFGridCtrlLU::SetFloat( long lRow, long lCol, float fNum, CString form /* = "%f" */ )
{
	SetDouble( lRow, lCol, fNum, form );
}

/**
 * 	double型 SetTextMatrix.
 * 	
 * 	@param	lRow	選択行
 * 	@param	lCol	選択列
 * 	@param	fNum	入力float値
 * 	@param	form	入力書式
 */
void CFGridCtrlLU::SetDouble( long lRow, long lCol, double dNum, CString form /* = "%f" */ )
{
	CString strTemp;

	strTemp.Format( form, dNum );
	SetTextMatrix( lRow, lCol, strTemp );
}

/**
 * 	String型 SetTextMatrix.
 * 	
 * 	@param	lRow	選択行
 * 	@param	lCol	選択列
 * 	@param	str		入力String
 */
void CFGridCtrlLU::SetString( long lRow, long lCol, CString str, ... )
{
	CString strData = str;
//	%をいれるとエラーになる????
//DEL	yotsutsu	va_list argList;
//DEL	yotsutsu	va_start( argList, str );
//DEL	yotsutsu	strData.FormatV( str, argList );
//DEL	yotsutsu	va_end( argList );

	SetTextMatrix( lRow, lCol, strData );
}
/**
 * 	int型 SetTextMatrix.
 * 	
 * 	@param	lRow		選択行
 * 	@param	lCol		選択列
 * 	@param	bChecked	入力int値
 */
void CFGridCtrlLU::SetCheck( long lRow, long lCol, BOOL bChecked )
{
	SetCell(5,COleVariant(lRow),COleVariant(lCol),COleVariant(lRow),COleVariant(lCol),COleVariant((long)(bChecked ? 1 : 2 )));
}
/**
 * 	BOOL型 GetString.
 * 	
 * 	@param	lRow	選択行
 * 	@param	lCol	選択列
 * 	@return			取得BOOL値
 */
BOOL CFGridCtrlLU::GetBool( long lRow, long lCol )
{
	CString strTemp = GetString( lRow, lCol );
	BOOL bBool = atoi( strTemp );
	if( !bBool ){
		bBool = 0;
	}else{
		bBool = 1;
	}
	return( bBool );
}

/**
 * 	int型 GetString.
 * 	
 * 	@param	lRow	選択行
 * 	@param	lCol	選択列
 * 	@return			取得int値
 */
int CFGridCtrlLU::GetInt( long lRow, long lCol )
{
	CString strTemp = GetString( lRow, lCol );
	return( atoi( strTemp ) );
}

/**
 * 	float型 GetString.
 * 	
 * 	@param	lRow	選択行
 * 	@param	lCol	選択列
 * 	@return			取得float値
 */
float CFGridCtrlLU::GetFloat( long lRow, long lCol )
{
	CString strTemp = GetString( lRow, lCol );
	return( ( float )atof( strTemp ) );
}

/**
 * 	double型 GetString.
 * 	
 * 	@param	lRow	選択行
 * 	@param	lCol	選択列
 * 	@return			取得double値
 */
double CFGridCtrlLU::GetDouble( long lRow, long lCol )
{
	CString strTemp = GetString( lRow, lCol );
	return( atof( strTemp ) );
}

/**
 * 	String型 GetString.
 * 	
 * 	@param	lRow	選択行
 * 	@param	lCol	選択列
 * 	@return			取得String
 */
CString CFGridCtrlLU::GetString( long lRow, long lCol )
{
	return( GetTextMatrix( lRow, lCol ) );
}
/**
 * 	int型 GetCheck.for Check Box
 * 	
 * 	@param	lRow	選択行
 * 	@param	lCol	選択列
 * 	@return			取得int値	1:チェック有/0：チェック無
 */
BOOL CFGridCtrlLU::GetCheck( long lRow, long lCol )
{
	COleVariant	varDefault;		//VARIANT
	varDefault = GetCell(5,COleVariant(lRow),COleVariant(lCol),COleVariant(lRow),COleVariant(lCol));
	if(varDefault.iVal == 1 || varDefault.iVal == 3)	{	return TRUE;	}
	return (FALSE);
}
/**
 * 	Copy line.
 * 		Copy Selected Rows
 * 	
 * 	@return			CopyされたLine数
 */
int CFGridCtrlLU::CopyLine()
{
	int iHeaderLine = GetFixedRows();	//Grid Header lRow
	int iSelect = GetSelectedRows();	//Copy Line Number
	m_iSelect = 0;						//Initialize

	//copy line not selected
	if( iSelect <= 0 ){
		AfxMessageBox("copy line is not select" );
		return( 0 );
	}

	if( m_CopyBuf.GetSize() != 0 ){
		m_CopyBuf.RemoveAll();
	}

	long *lRows = new long[iSelect];	//new
	if( lRows == NULL ){
		AfxMessageBox("cannot memory alloc" );
		return( 0 );
	}

	//選択されている行の範囲check
	for( int i = 0; i < iSelect; i++ ){
		lRows[i] = GetSelectedRow( i );
		if( lRows[i] >= GetRows() || lRows[i] < iHeaderLine ){
			AfxMessageBox("The line is not chosen" );
			return( 0 );
		}
		CopyOneLine( lRows[i] );
	}

	if( lRows != NULL ){		//delete
		delete[] lRows;
		lRows = NULL;
	}
	m_iSelect = iSelect;
	return( m_iSelect );
}

/**
 * 	Insert line.
 * 		Insert Selected Row
 * 	
 */
int CFGridCtrlLU::InsertLine()
{
	int iHeaderLine = GetFixedRows();	//Grid Header lRow

	//複数行選択されていると、貼り付ける位置があいまいになるので、
	//単一行選択でなければ、貼り付けられないようにする
	if( GetSelectedRows() != 1 ){
		AfxMessageBox("paste is one line at a time" );
		return( 0 );
	}
	//copy data がない場合
	if( m_CopyBuf.GetSize() == 0 ){
		AfxMessageBox("paste data is non" );
		return( 0 );
	}

	SetMaxRowCol();		//現在の行数、列数を保存
	long lRow = GetSelectedRow( 0 );
	long lCol = GetCol();

	//選択行にCopy行を挿入
	//Copy行が複数の場合は選択行の下の行を追加。順次挿入する。
	COleVariant addRow;
	for( int iCp = 0; iCp < m_iSelect; iCp++ ){
		addRow = ( long )( lRow + iCp );
		AddItem( "", addRow );
		PasteOneLine( lRow + iCp, iCp );
	}

	UndoGrid();		//insertによって増えた行をinsert前に戻す
	long newRow = lRow + m_iSelect;
	if( newRow > GetRows() ){	newRow = GetRows();	}
	SetCurCell( newRow - 1, lCol );
	return( m_iSelect );
}

/**
 * 	Paste line.
 * 		Paste Selected Row
 * 	
 */
int CFGridCtrlLU::PasteLine()
{
	int iHeaderLine = GetFixedRows();	//Grid Header lRow

	//複数行選択されていると、貼り付ける位置があいまいになるので、
	//単一行選択でなければ、貼り付けられないようにする
	if( GetSelectedRows() != 1 ){
		AfxMessageBox("paste is one line at a time" );
		return( 0 );
	}
	//copy data がない場合
	if( m_CopyBuf.GetSize() == 0 ){
		AfxMessageBox("paste data is non" );
		return( 0 );
	}

	long lRow = GetSelectedRow( 0 );
	long lCol = GetCol();

	//選択行にCopy行を上書き
	//Copy行が複数の場合は選択行の下の行に順次上書き
	for( int iCp = 0; iCp < m_iSelect; iCp++ ){
		if( lRow + iCp >= GetRows() ){	break;	}	//最大行を超える部分に上書きは不可
		PasteOneLine( lRow + iCp, iCp );
	}

	SetCurCell( lRow, lCol );
	return( m_iSelect );
}

/**
 * 	Delete line.
 * 		Delete Selected Rows
 * 	
 */
int CFGridCtrlLU::DeleteLine()
{
	int iHeaderLine = GetFixedRows();	//Grid Header lRow
	int iSelect = GetSelectedRows();	//Copy Line Number

	//delete line not selected
	if( iSelect <= 0 ){
		AfxMessageBox("delete line is not select" );
		return( 0 );
	}
	long *lRows = new long[iSelect];	//new
	if( lRows == NULL ){
		AfxMessageBox("cannot memory alloc" );
		return NULL;
	}
	long lCol = GetCol();

	//選択されている行の範囲check
	for( int i = 0; i < iSelect; i++ ){
		lRows[i] = GetSelectedRow( i );	//delete line set
		if( lRows[i] >= GetRows() || lRows[i] < iHeaderLine ){
			AfxMessageBox("The line is not chosen" );
			return( 0 );
		}
	}
	SetMaxRowCol();

	//1行ずつ消す
	COleVariant deleteRow;
	for( i = 0; i < iSelect; i++ ){
		deleteRow = ( long )( lRows[i] - i );
		RemoveItem( deleteRow );
	}

	UndoGrid();
	SetCurCell( lRows[0], lCol );		//current selを戻す

	if( lRows != NULL ){		//delete
		delete[] lRows;
	}
	return( iSelect );
}

/**
 * 	1行分のDataをCopyする
 * 	
 * 	@param	lRow	Copy行
 */
void CFGridCtrlLU::CopyOneLine( long lRow )
{
	for( int j = 0; j < GetCols(); j++ ){
		m_CopyBuf.Add( GetString( lRow, j ) );
	}
}

/**
 * 	1行分のDataを貼り付ける
 * 	
 * 	@param	lRow	Paste行
 * 	@prama	iIndex	Copy DataのIndex
 */
void CFGridCtrlLU::PasteOneLine( long lRow, int iIndex )
{
	for( int i = 0; i < GetCols(); i++ ){
		SetString( lRow, i, m_CopyBuf.GetAt( i + iIndex * GetCols() ) );
	}
}

/**
 * 	行を追加します.
 *		Gridの最終行に追加されます
 * 	
 * 	@param	lRow	追加する行（Insert）
 */
void CFGridCtrlLU::AddLine( long lRow )
{
	COleVariant addRow = ( long )lRow;
	AddItem( "", addRow );
}

/**
 * 	行を削除します.
 * 	
 * 	@param	lRow	削除する行
 */
void CFGridCtrlLU::DeleteLine( long lRow )
{
	COleVariant delRow = ( long )lRow;
	RemoveItem( delRow );
}

/**
 * 	sort.
 * 		固定行を除いた全ての行をSort
 * 	
 * 	@param	lCol	sort判定列
 * 	@param	Order	sort kind ( 0:sortしない 1:昇順sort 2:降順sort )
 */
void CFGridCtrlLU::SortSel( long lCol, short FAR* Order )
{
	SortSel( GetFixedRows(), GetFixedRows(), lCol, Order );
}

/**
 * 	sort.
 * 		Explore Bar sortが使いたくない人へ
 * 	
 * 	@param	lRowStart	sort対象行先頭
 * 	@param	lRowEnd		sort対象行末尾
 * 	@param	lCol		sort判定列
 * 	@param	Order		sort kind ( 0:sortしない 1:昇順sort 2:降順sort )
 */
void CFGridCtrlLU::SortSel( long lRowStart, long lRowEnd, long lCol, short FAR* Order )
{
	long lRow = GetRow();

	//ソート列指定
	SetCol( lCol );
	SetColSel( lCol );

	//ソート対象行指定
	SetRow( lRowStart );
	SetRowSel( lRowEnd );

	SetSort( ( short )*Order );

	//SetRowSelのリセット
	SetRow( lRow );
}

/**
 * 	Scroll ( Page Up ).
 * 	
 * 	@param	iSize	Row Up Size
 * 	@return			Scroll後の先頭行
 */
long CFGridCtrlLU::PageUp( long lSize )
{
	long lTop = GetTopRow();

	//一番上が、GetFixedRows()で合うように調整する
	if( lTop - lSize < GetFixedRows() ){
		SetTopRow( GetFixedRows() );
	}else{
		SetTopRow( lTop - lSize );
	}
	return( GetTopRow() );
}

/**
 * 	Scroll ( Page Down ).
 * 	
 * 	@param	iSize	Row Down Size
 * 	@return			Scroll後の先頭行
 */
long CFGridCtrlLU::PageDown( long lSize )
{
	long lTop = GetTopRow();

	//一番下が、GetRows()で合うように調整する
	if( lTop - lSize >= GetRows() ){
		SetTopRow( GetRows() - lSize );
	}else{
		SetTopRow( lTop + lSize );
	}
	return( GetTopRow() );
}

/**
 * 	Grid Area Resize.
 * 	
 * 	@param	iKind			Resize Kind（ 0: 両方向 1:x方向 2:y方向 ）
 * 	@param	bVertical		縦Scroll Barの有無（ TRUE:有 FALSE:無 ）
 * 	@param	bHorizonta		横Scroll Barの有無（ TRUE:有 FALSE:無 ）
 */
void CFGridCtrlLU::Resize( int iKind /* = XY_RESIZE */, BOOL bVertical /* = FALSE */, BOOL bHorizontal /* = FALSE */ )
{
	const int INCH_TO_TWIPS = 1440;					//インチをtwipsに変換する定数
	int pic = GetDC()->GetDeviceCaps(LOGPIXELSX);	//１インチあたりのピクセル数
	long width = 0, height = 0;
	CRect rect;

	GetClientRect( rect );
	ClientToScreen( &rect );
	GetParent()->ScreenToClient( &rect );

	//x
	if( iKind == X_RESIZE || iKind == XY_RESIZE ){
		//get total Col size
		for( int iCol = 0; iCol < GetCols(); iCol++ ){
			if( !GetColHidden( iCol ) ){	width += GetColWidth( iCol );	}
		}
		width = width * pic / INCH_TO_TWIPS;	//twipsをピクセルに変換
	}else{
		width = rect.Width();
	}

	//y
	if( iKind == Y_RESIZE || iKind == XY_RESIZE ){
		//get total row size
		for( int iRow = 0; iRow < GetRows(); iRow++ ){
			if( !GetRowHidden( iRow ) ){	height += GetRowHeight( iRow );	}
		}
		height = height * pic / INCH_TO_TWIPS;	//twipsをピクセルに変換
	}else{
		height = rect.Height();
	}

	//resize rect
	rect.right	= rect.left + width + GetSystemMetrics( SM_CXEDGE );
	if( bVertical ){	rect.right += GetSystemMetrics( SM_CXVSCROLL );	}
	rect.left	-= GetSystemMetrics( SM_CXEDGE );
	rect.bottom	= rect.top + height + GetSystemMetrics( SM_CYEDGE );
	if( bHorizontal ){	rect.bottom += GetSystemMetrics( SM_CYVSCROLL );	}
	rect.top	-= GetSystemMetrics( SM_CYEDGE );

	//resize
	MoveWindow( rect );
}

/**
 * 	GirdのRow数、Col数を設定.
 * 		this method call then grid initialize
 * 
 * 	@param	lRow	Row数
 * 	@param	lCol	Col数
 */
void CFGridCtrlLU::SetMaxRowCol( long lRow, long lCol )
{
	if( lRow > 0 ){
		SetRows( lRow );
		m_lTotalRow = lRow;
	}
	if( lCol > 0 ){
		SetCols( lCol );
		m_lTotalCol = lCol;
	}
}

/**
 * 	GirdのRow数、Col数を設定
 * 	
 */
void CFGridCtrlLU::SetMaxRowCol()
{
	m_lTotalRow = GetRows();
	m_lTotalCol = GetCols();
}

/**
 * 	Line Number Draw.
 * 		Line Number Draw時は0列を固定列にする
 * 	
 * 	@param	iStart		Start Line Number
 * 	@param	bMode		Line Number Draw Flag( TRUE:描画 FALSE:非描画 )
 */
void CFGridCtrlLU::SetLineNum( int iStart /* = 1 */, BOOL bMode /* = TRUE */ )
{
	m_iLineNoStart = iStart;

	if( bMode ){
		SetFixedCols( 1 );
		DrawLineNum();
	}else{
		SetFixedCols( 0 );	//pending	行番号を表示しない時は固定列なし
	}
	m_bLineNoDraw = bMode;
}

/**
 * 	Line No Draw
 * 	
 */
void CFGridCtrlLU::DrawLineNum()
{
	CString strTemp;
	for( int i = 0; i < GetRows() - GetFixedRows(); i++ ){
		strTemp.Format( "%d", m_iLineNoStart + i );
		SetTextMatrix( i + GetFixedRows(), 0, strTemp );
	}
}

/**
 * 	GirdのRow数、Col数を元に戻す.
 *		Paste, Insert, Delete の時に有効かな～と
 * 	
 */
void CFGridCtrlLU::UndoGrid()
{
	//Undo row & col
	SetRows( m_lTotalRow );
	SetCols( m_lTotalCol );

	//line No draw
	if( m_bLineNoDraw ){
		DrawLineNum();
	}
}

/**
 *	Gridに表示されている全DataをDeleteする.
 *	
 *	@param	bDelFixedCell	Fixed Cell Delete Flag ( TRUE:Delete FALSE:not Delete )
 */
void CFGridCtrlLU::DeleteGridData( BOOL bDelFixedCell /* = FALSE */ )
{
	long lFixedRow = 0;
	if( !bDelFixedCell ){	lFixedRow = GetFixedRows();	}

	for( long lRow = lFixedRow; lRow < GetRows(); lRow++ ){
		DeleteGridRowData( lRow, bDelFixedCell );
	}
}

/**
 *	Gridの1行分のDataをDelete
 *	
 *	@param	lRow			Delete Row
 *	@param	bDelFixedCol	Fixed lCol Delete Flag ( TRUE:Delete FALSE:not Delete )
 */
void CFGridCtrlLU::DeleteGridRowData( long lRow, BOOL bDelFixedCol /* = FALSE */ )
{
	long lFixedCol = 0;
	if( !bDelFixedCol ){	lFixedCol = GetFixedCols();	}

	for( long lCol = lFixedCol; lCol < GetCols(); lCol++ ){
		SetTextMatrix( lRow, lCol, "" );
	}
}

/**
 *	Gridの1列分のDataをDelete
 *	
 *	@param	lCol			Delete Col
 *	@param	bDelFixedRow	Fixed lRow Delete Flag ( TRUE:Delete FALSE:not Delete )
 */
void CFGridCtrlLU::DeleteGridColData( long lCol, BOOL bDelFixedRow /* = FALSE */ )
{
	long lFixedRow = 0;
	if( !bDelFixedRow ){	lFixedRow = GetFixedRows();	}

	for( long lRow = lFixedRow; lRow < GetRows(); lRow++ ){
		SetTextMatrix( lRow, lCol, "" );
	}
}

/**
 * 	Input Mode Setting
 * 	
 * 	@param	iMode		Input Mode
 * 	@param	lRow		Input Mode Row
 * 	@param	lCol		Input Mode Col
 * 	@param	iIntNum		Number of Input Digit
 * 	@param	iDecNum		Number of Input DEC Digit
 * 	@param	bMinus		Minus Use/No Use Flag( TRUE:Use Use FALSE:No Use )
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetInputMode( int iMode, long lRow, long lCol, int iIntNum, int iDecNum, BOOL bMinus )
{
	if( lCol > GetCols() ){	return( FALSE );	}
	if( lRow > GetRows() ){	return( FALSE );	}

	//既に要素が登録されている場合は、現在登録されているのを削除
	int iModeIndex = GetModeIndex( lRow, lCol );
	if( iModeIndex != -1 ){	m_InputMode.RemoveAt( iModeIndex );	}

	INPUT_MODE mode;

	mode.iInputMode	= iMode;
	mode.lRow		= lRow;
	mode.lCol		= lCol;
	mode.iIntNum	= iIntNum;
	mode.iDecNum	= iDecNum;
	mode.bMinus		= bMinus;

	m_InputMode.Add( mode );	//追加

	return( TRUE );
}

/**
 * 	Not Edit Cell Setting
 * 	
 * 	@param	lRow		Use Input Mode Row
 * 	@param	lCol		Use Input Mode Col
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetNoEditCell( long lRow, long lCol )
{
	if( !SetInputMode( NO_CHANGE, lRow, lCol, 0, 0, 0 ) ){
		return( FALSE );
	}
	return( TRUE );
}

/**
 * 	Not Edit Row Setting
 * 	
 * 	@param	lRow		Use Input Mode Row
 * 	@param	lCol		Use Input Mode Col
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetNoEditRow( long lRow )
{
	for( long lCol = GetFixedCols(); lCol < GetCols(); lCol++ ){
		if( !SetNoEditCell( lRow, lCol ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	Not Edit Col Setting
 * 	
 * 	@param	lRow		Use Input Mode Row
 * 	@param	lCol		Use Input Mode Col
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetNoEditCol( long lCol )
{
	for( long lRow = GetFixedRows(); lRow < GetRows(); lRow++ ){
		if( !SetNoEditCell( lRow, lCol ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	Not Edit Row Setting
 * 	
 * 	@param	lRowStart	Use Input Mode Row Start
 * 	@param	lRowEnd		Use Input Mode Row End
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetNoEditRows( long lRowStart, long lRowEnd )
{
	for( long lRow = lRowStart; lRow <= lRowEnd; lRow++ ){
		if( !SetNoEditRow( lRow ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	Not Edit Col Setting
 * 	
 * 	@param	lCol		Use Input Mode Col Start
 * 	@param	lCol		Use Input Mode Col End
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetNoEditCols( long lColStart, long lColEnd )
{
	for( long lCol = lColStart; lCol <= lColEnd; lCol++ ){
		if( !SetNoEditCol( lCol ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	BOOL Cell Setting
 * 	
 * 	@param	lRow		Use Input Mode Row
 * 	@param	lCol		Use Input Mode Col
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetBoolCell( long lRow, long lCol )
{
	if( !SetInputMode( INPUT_BOOL, lRow, lCol, 0, 0, 0 ) ){
		return( FALSE );
	}
	return( TRUE );
}

/**
 * 	BOOL Row Setting
 * 	
 * 	@param	lRow		Use Input Mode Row
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetBoolRow( long lRow )
{
	for( long lCol = GetFixedCols(); lCol < GetCols(); lCol++ ){
		if( !SetBoolCell( lRow, lCol ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	BOOL Col Setting
 * 	
 * 	@param	lCol		Use Input Mode Col
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetBoolCol( long lCol )
{
	for( long lRow = GetFixedRows(); lRow < GetRows(); lRow++ ){
		if( !SetBoolCell( lRow, lCol ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	BOOL Row Setting
 * 	
 * 	@param	lRowStart	Use Input Mode Row Start
 * 	@param	lRowEnd		Use Input Mode Row End
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetBoolRows( long lRowStart, long lRowEnd )
{
	for( long lRow = lRowStart; lRow <= lRowEnd; lRow++ ){
		if( !SetBoolRow( lRow ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	BOOL Col Setting
 * 	
 * 	@param	lCol		Use Input Mode Col Start
 * 	@param	lCol		Use Input Mode Col End
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetBoolCols( long lColStart, long lColEnd )
{
	for( long lCol = lColStart; lCol <= lColEnd; lCol++ ){
		if( !SetBoolCol( lCol ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	Int Cell Setting
 * 	
 * 	@param	lRow		Use Input Mode lRow
 * 	@param	lCol		Use Input Mode Col
 * 	@param	iIntNum		Number of Input Digit
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetIntCell( long lRow, long lCol, int iIntNum /* = 1 */, BOOL bMinus /* = TRUE */  )
{
	if( !SetInputMode( INPUT_INT, lRow, lCol, iIntNum, 0, bMinus ) ){
		return( FALSE );
	}
	return( TRUE );
}

/**
 * 	Int lRow Setting
 * 	
 * 	@param	lRow		Use Input Mode lRow
 * 	@param	iIntNum		Number of Input Digit
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetIntRow( long lRow, int iIntNum /* = 1 */, BOOL bMinus /* = TRUE */  )
{
	for( long lCol = GetFixedCols(); lCol < GetCols(); lCol++ ){
		if( !SetIntCell( lRow, lCol, iIntNum, bMinus ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	Int Col Setting
 * 	
 * 	@param	lCol		Use Input Mode Col
 * 	@param	iIntNum		Number of Input Digit
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetIntCol( long lCol, int iIntNum /* = 1 */, BOOL bMinus /* = TRUE */  )
{
	for( long lRow = GetFixedRows(); lRow < GetRows(); lRow++ ){
		if( !SetIntCell( lRow, lCol, iIntNum, bMinus ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	Int Row Setting
 * 	
 * 	@param	lRowStart	Use Input Mode Row Start
 * 	@param	lRowEnd		Use Input Mode Row End
 * 	@param	iIntNum		Number of Input Digit
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetIntRows( long lRowStart, long lRowEnd, int iIntNum /* = 1 */, BOOL bMinus /* = TRUE */  )
{
	for( long lRow = lRowStart; lRow <= lRowEnd; lRow++ ){
		if( !SetIntRow( lRow, iIntNum, bMinus ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	Int Col Setting
 * 	
 * 	@param	lCol		Use Input Mode Col Start
 * 	@param	lCol		Use Input Mode Col End
 * 	@param	iIntNum		Number of Input Digit
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetIntCols( long lColStart, long lColEnd, int iIntNum /* = 1 */, BOOL bMinus /* = TRUE */  )
{
	for( long lCol = lColStart; lCol <= lColEnd; lCol++ ){
		if( !SetIntCol( lCol, iIntNum, bMinus ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	Float Cell Setting
 * 	
 * 	@param	lRow		Use Input Mode lRow
 * 	@param	lCol		Use Input Mode Col
 * 	@param	iIntNum		Number of Input Digit
 * 	@param	iDecNum		Number of Input DEC Digit
 * 	@param	bMinus		Minus Use/No Use Flag( TRUE:Use Use FALSE:No Use )
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetFloatCell( long lRow, long lCol, int iIntNum /* = 1 */, int iDecNum /* = 0 */, BOOL bMinus /* = TRUE */ )
{
	if( !SetInputMode( INPUT_FLOAT, lRow, lCol, iIntNum, iDecNum, bMinus ) ){
		return( FALSE );
	}
	return( TRUE );
}

/**
 * 	Float lRow Setting
 * 	
 * 	@param	lRow		Use Input Mode lRow
 * 	@param	iIntNum		Number of Input Digit
 * 	@param	iDecNum		Number of Input DEC Digit
 * 	@param	bMinus		Minus Use/No Use Flag( TRUE:Use Use FALSE:No Use )
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetFloatRow( long lRow, int iIntNum /* = 1 */, int iDecNum /* = 0 */, BOOL bMinus /* = TRUE */ )
{
	for( long lCol = GetFixedCols(); lCol < GetCols(); lCol++ ){
		if( !SetFloatCell( lRow, lCol, iIntNum, iDecNum, bMinus ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	Float Col Setting
 * 	
 * 	@param	lCol		Use Input Mode Col
 * 	@param	iIntNum		Number of Input Digit
 * 	@param	iDecNum		Number of Input DEC Digit
 * 	@param	bMinus		Minus Use/No Use Flag( TRUE:Use Use FALSE:No Use )
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetFloatCol( long lCol, int iIntNum /* = 1 */, int iDecNum /* = 0 */, BOOL bMinus /* = TRUE */ )
{
	for( long lRow = GetFixedRows(); lRow < GetRows(); lRow++ ){
		if( !SetFloatCell( lRow, lCol, iIntNum, iDecNum, bMinus ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	Float Row Setting
 * 	
 * 	@param	lRowStart	Use Input Mode Row Start
 * 	@param	lRowEnd		Use Input Mode Row End
 * 	@param	iIntNum		Number of Input Digit
 * 	@param	iDecNum		Number of Input DEC Digit
 * 	@param	bMinus		Minus Use/No Use Flag( TRUE:Use Use FALSE:No Use )
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetFloatRows( long lRowStart, long lRowEnd, int iIntNum /* = 1 */, int iDecNum /* = 0 */, BOOL bMinus /* = TRUE */ )
{
	for( long lRow = lRowStart; lRow <= lRowEnd; lRow++ ){
		if( !SetFloatRow( lRow, iIntNum, iDecNum, bMinus ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	Float Col Setting
 * 	
 * 	@param	lCol		Use Input Mode Col Start
 * 	@param	lCol		Use Input Mode Col End
 * 	@param	iIntNum		Number of Input Digit
 * 	@param	iDecNum		Number of Input DEC Digit
 * 	@param	bMinus		Minus Use/No Use Flag( TRUE:Use Use FALSE:No Use )
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetFloatCols( long lColStart, long lColEnd, int iIntNum /* = 1 */, int iDecNum /* = 0 */, BOOL bMinus /* = TRUE */ )
{
	for( long lCol = lColStart; lCol <= lColEnd; lCol++ ){
		if( !SetFloatCol( lCol, iIntNum, iDecNum, bMinus ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	Double Cell Setting
 * 	
 * 	@param	lRow		Use Input Mode lRow
 * 	@param	lCol		Use Input Mode Col
 * 	@param	iIntNum		Number of Input Digit
 * 	@param	iDecNum		Number of Input DEC Digit
 * 	@param	bMinus		Minus Use/No Use Flag( TRUE:Use Use FALSE:No Use )
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetDoubleCell( long lRow, long lCol, int iIntNum /* = 1 */, int iDecNum /* = 0 */, BOOL bMinus /* = TRUE */ )
{
	if( !SetInputMode( INPUT_DOUBLE, lRow, lCol, iIntNum, iDecNum, 0 ) ){
		return( FALSE );
	}
	return( TRUE );
}

/**
 * 	Double lRow Setting
 * 	
 * 	@param	lRow		Use Input Mode lRow
 * 	@param	iIntNum		Number of Input Digit
 * 	@param	iDecNum		Number of Input DEC Digit
 * 	@param	bMinus		Minus Use/No Use Flag( TRUE:Use Use FALSE:No Use )
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetDoubleRow( long lRow, int iIntNum /* = 1 */, int iDecNum /* = 0 */, BOOL bMinus /* = TRUE */ )
{
	for( long lCol = GetFixedCols(); lCol < GetCols(); lCol++ ){
		if( !SetDoubleCell( lRow, lCol, iIntNum, iDecNum, bMinus ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	Double Col Setting
 * 	
 * 	@param	lCol		Use Input Mode Col
 * 	@param	iIntNum		Number of Input Digit
 * 	@param	iDecNum		Number of Input DEC Digit
 * 	@param	bMinus		Minus Use/No Use Flag( TRUE:Use Use FALSE:No Use )
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetDoubleCol( long lCol, int iIntNum /* = 1 */, int iDecNum /* = 0 */, BOOL bMinus /* = TRUE */ )
{
	for( long lRow = GetFixedRows(); lRow < GetRows(); lRow++ ){
		if( !SetDoubleCell( lRow, lCol, iIntNum, iDecNum, bMinus ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	Double Row Setting
 * 	
 * 	@param	lRowStart	Use Input Mode Row Start
 * 	@param	lRowEnd		Use Input Mode Row End
 * 	@param	iIntNum		Number of Input Digit
 * 	@param	iDecNum		Number of Input DEC Digit
 * 	@param	bMinus		Minus Use/No Use Flag( TRUE:Use Use FALSE:No Use )
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetDoubleRows( long lRowStart, long lRowEnd, int iIntNum /* = 1 */, int iDecNum /* = 0 */, BOOL bMinus /* = TRUE */ )
{
	for( long lRow = lRowStart; lRow <= lRowEnd; lRow++ ){
		if( !SetDoubleRow( lRow, iIntNum, iDecNum, bMinus ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	Double Col Setting
 * 	
 * 	@param	lCol		Use Input Mode Col Start
 * 	@param	lCol		Use Input Mode Col End
 * 	@param	iIntNum		Number of Input Digit
 * 	@param	iDecNum		Number of Input DEC Digit
 * 	@param	bMinus		Minus Use/No Use Flag( TRUE:Use Use FALSE:No Use )
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetDoubleCols( long lColStart, long lColEnd, int iIntNum /* = 1 */, int iDecNum /* = 0 */, BOOL bMinus /* = TRUE */ )
{
	for( long lCol = lColStart; lCol <= lColEnd; lCol++ ){
		if( !SetDoubleCol( lCol, iIntNum, iDecNum, bMinus ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	String Cell Setting
 * 	
 * 	@param	lRow		Use Input Mode lRow
 * 	@param	lCol		Use Input Mode Col
 * 	@param	iIntNum		Number of Input Digit
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetStringCell( long lRow, long lCol, int iIntNum /* = 1 */ )
{
	if( !SetInputMode( INPUT_STRING, lRow, lCol, iIntNum, 0, 0 ) ){
		return( FALSE );
	}
	return( TRUE );
}

/**
 * 	String lRow Setting
 * 	
 * 	@param	lRow		Use Input Mode lRow
 * 	@param	iIntNum		Number of Input Digit
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetStringRow( long lRow, int iIntNum /* = 1 */ )
{
	for( long lCol = GetFixedCols(); lCol < GetCols(); lCol++ ){
		if( !SetStringCell( lRow, lCol, iIntNum ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	String Col Setting
 * 	
 * 	@param	lCol		Use Input Mode Col
 * 	@param	iIntNum		Number of Input Digit
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetStringCol( long lCol, int iIntNum /* = 1 */ )
{
	for( long lRow = GetFixedRows(); lRow < GetRows(); lRow++ ){
		if( !SetStringCell( lRow, lCol, iIntNum ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	String Row Setting
 * 	
 * 	@param	lRowStart	Use Input Mode Row Start
 * 	@param	lRowEnd		Use Input Mode Row End
 * 	@param	iIntNum		Number of Input Digit
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetStringRows( long lRowStart, long lRowEnd, int iIntNum /* = 1 */ )
{
	for( long lRow = lRowStart; lRow <= lRowEnd; lRow++ ){
		if( !SetStringRow( lRow, iIntNum ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	String Col Setting
 * 	
 * 	@param	lCol		Use Input Mode Col Start
 * 	@param	lCol		Use Input Mode Col End
 * 	@param	iIntNum		Number of Input Digit
 * 	@return				TRUE:Success FALSE:Failed
 */
BOOL CFGridCtrlLU::SetStringCols( long lColStart, long lColEnd, int iIntNum /* = 1 */ )
{
	for( long lCol = lColStart; lCol <= lColEnd; lCol++ ){
		if( !SetStringCol( lCol, iIntNum ) ){
			return( FALSE );
		}
	}
	return( TRUE );
}

/**
 * 	セルの入力上下限値を設定
 * 
 * 	@param lRow		上下限値設定行
 * 	@param lCol		上下限値設定列
 * 	@param iMin		下限値
 * 	@param iMax		上限値
 * 	@return			TRUE:成功 FALSE:失敗
 */
BOOL CFGridCtrlLU::SetCellRange( long lRow, long lCol, int iMin, int iMax )
{
	if( lRow > GetRows() || lRow < 0 ){	return( FALSE );	}
	if( lCol > GetCols() || lCol < 0 ){	return( FALSE );	}

	//既に要素が登録されている場合は、現在登録されているのを削除
	int iRangeIndex = GetRangeIndex( lRow, lCol );
	if( iRangeIndex != -1 ){	m_InputRange.RemoveAt( iRangeIndex );	}

	INPUT_RANGE range;

	range.iInputMode = INPUT_INT;
	range.lRow       = lRow;
	range.lCol       = lCol;
	range.min.iNum   = iMin;
	range.max.iNum   = iMax;

	m_InputRange.Add( range );

	return( TRUE );
}

/**
 * 	セルの入力上下限値を設定
 * 
 * 	@param lRow		上下限値設定行
 * 	@param lCol		上下限値設定列
 * 	@param fMin		下限値
 * 	@param fMax		上限値
 * 	@return			TRUE:成功 FALSE:失敗
 */
BOOL CFGridCtrlLU::SetCellRange( long lRow, long lCol, float fMin, float fMax )
{
	if( lRow > GetRows() || lRow < 0 ){	return( FALSE );	}
	if( lCol > GetCols() || lCol < 0 ){	return( FALSE );	}

	//既に要素が登録されている場合は、現在登録されているのを削除
	int iRangeIndex = GetRangeIndex( lRow, lCol );
	if( iRangeIndex != -1 ){	m_InputRange.RemoveAt( iRangeIndex );	}

	INPUT_RANGE range;

	range.iInputMode = INPUT_FLOAT;
	range.lRow       = lRow;
	range.lCol       = lCol;
	range.min.fNum   = fMin;
	range.max.fNum   = fMax;

	m_InputRange.Add( range );

	return( TRUE );
}

/**
 * 	セルの入力上下限値を設定
 * 
 * 	@param lRow		上下限値設定行
 * 	@param lCol		上下限値設定列
 * 	@param dMin		下限値
 * 	@param dMax		上限値
 * 	@return			TRUE:成功 FALSE:失敗
 */
BOOL CFGridCtrlLU::SetCellRange( long lRow, long lCol, double dMin, double dMax )
{
	if( lRow > GetRows() || lRow < 0 ){	return( FALSE );	}
	if( lCol > GetCols() || lCol < 0 ){	return( FALSE );	}

	//既に要素が登録されている場合は、現在登録されているのを削除
	int iRangeIndex = GetRangeIndex( lRow, lCol );
	if( iRangeIndex != -1 ){	m_InputRange.RemoveAt( iRangeIndex );	}

	INPUT_RANGE range;

	range.iInputMode = INPUT_DOUBLE;
	range.lRow       = lRow;
	range.lCol       = lCol;
	range.min.dNum   = dMin;
	range.max.dNum   = dMax;

	m_InputRange.Add( range );

	return( TRUE );
}

/**
 * 	行の入力上下限値を設定
 * 
 * 	@param lRow		上下限値設定行
 * 	@param iMin		下限値
 * 	@param iMax		上限値
 * 	@return			TRUE:成功 FALSE:失敗
 */
BOOL CFGridCtrlLU::SetRowRange( long lRow, int iMin, int iMax )
{
	for( long lCol = GetFixedCols(); lCol < GetCols(); lCol++ ){
		if( !SetCellRange( lRow, lCol, iMin, iMax ) ){	return( FALSE );	}
	}
	return( TRUE );
}

/**
 * 	行の入力上下限値を設定
 * 
 * 	@param lRow		上下限値設定行
 * 	@param fMin		下限値
 * 	@param fMax		上限値
 * 	@return			TRUE:成功 FALSE:失敗
 */
BOOL CFGridCtrlLU::SetRowRange( long lRow, float fMin, float fMax )
{
	for( long lCol = GetFixedCols(); lCol < GetCols(); lCol++ ){
		if( !SetCellRange( lRow, lCol, fMin, fMax ) ){	return( FALSE );	}
	}
	return( TRUE );
}

/**
 * 	行の入力上下限値を設定
 * 
 * 	@param lRow		上下限値設定行
 * 	@param dMin		下限値
 * 	@param dMax		上限値
 * 	@return			TRUE:成功 FALSE:失敗
 */
BOOL CFGridCtrlLU::SetRowRange( long lRow, double dMin, double dMax )
{
	for( long lCol = GetFixedCols(); lCol < GetCols(); lCol++ ){
		if( !SetCellRange( lRow, lCol, dMin, dMax ) ){	return( FALSE );	}
	}
	return( TRUE );
}

/**
 * 	行の入力上下限値を設定
 * 
 * 	@param lRow		上下限値設定行
 * 	@param iMin		下限値
 * 	@param iMax		上限値
 * 	@return			TRUE:成功 FALSE:失敗
 */
BOOL CFGridCtrlLU::SetRowRange( long lRowStart, long lRowEnd, int iMin, int iMax )
{
	for( long lRow = lRowStart; lRow <= lRowEnd; lRow++ ){
		if( !SetRowRange( lRow, iMin, iMax ) ){	return( FALSE );	}
	}
	return( TRUE );
}

/**
 * 	行の入力上下限値を設定
 * 
 * 	@param lRow		上下限値設定行
 * 	@param fMin		下限値
 * 	@param fMax		上限値
 * 	@return			TRUE:成功 FALSE:失敗
 */
BOOL CFGridCtrlLU::SetRowRange( long lRowStart, long lRowEnd, float fMin, float fMax )
{
	for( long lRow = lRowStart; lRow <= lRowEnd; lRow++ ){
		if( !SetRowRange( lRow, fMin, fMax ) ){	return( FALSE );	}
	}
	return( TRUE );
}

/**
 * 	行の入力上下限値を設定
 * 
 * 	@param lRow		上下限値設定行
 * 	@param dMin		下限値
 * 	@param dMax		上限値
 * 	@return			TRUE:成功 FALSE:失敗
 */
BOOL CFGridCtrlLU::SetRowRange( long lRowStart, long lRowEnd, double dMin, double dMax )
{
	for( long lRow = lRowStart; lRow <= lRowEnd; lRow++ ){
		if( !SetRowRange( lRow, dMin, dMax ) ){	return( FALSE );	}
	}
	return( TRUE );
}

/**
 * 	列の入力上下限値を設定
 * 
 * 	@param lCol		上下限値設定列
 * 	@param iMin		下限値
 * 	@param iMax		上限値
 * 	@return			TRUE:成功 FALSE:失敗
 */
BOOL CFGridCtrlLU::SetColRange( long lCol, int iMin, int iMax )
{
	for( long lRow = GetFixedRows(); lRow < GetRows(); lRow++ ){
		if( !SetCellRange( lRow, lCol, iMin, iMax ) ){	return( FALSE );	}
	}
	return( TRUE );
}

/**
 * 	列の入力上下限値を設定
 * 
 * 	@param lCol		上下限値設定列
 * 	@param fMin		下限値
 * 	@param fMax		上限値
 * 	@return			TRUE:成功 FALSE:失敗
 */
BOOL CFGridCtrlLU::SetColRange( long lCol, float fMin, float fMax )
{
	for( long lRow = GetFixedRows(); lRow < GetRows(); lRow++ ){
		if( !SetCellRange( lRow, lCol, fMin, fMax ) ){	return( FALSE );	}
	}
	return( TRUE );
}

/**
 * 	列の入力上下限値を設定
 * 
 * 	@param lCol		上下限値設定列
 * 	@param dMin		下限値
 * 	@param dMax		上限値
 * 	@return			TRUE:成功 FALSE:失敗
 */
BOOL CFGridCtrlLU::SetColRange( long lCol, double dMin, double dMax )
{
	for( long lRow = GetFixedRows(); lRow < GetRows(); lRow++ ){
		if( !SetCellRange( lRow, lCol, dMin, dMax ) ){	return( FALSE );	}
	}
	return( TRUE );
}

/**
 * 	列範囲の入力上下限値を設定.
 * 		連続列の時のみ
 * 
 * 	@param lColStart	上下限値設定開始列
 * 	@param lColEnd		上下限値設定終了列
 * 	@param iMin			下限値
 * 	@param iMax			上限値
 * 	@return				TRUE:成功 FALSE:失敗
 */
BOOL CFGridCtrlLU::SetColRange( long lColStart, long lColEnd, int iMin, int iMax )
{
	for( long lCol = lColStart; lCol <= lColEnd; lCol++ ){
		if( !SetColRange( lCol, iMin, iMax ) ){	return( FALSE );	}
	}
	return( TRUE );
}

/**
 * 	列範囲の入力上下限値を設定.
 * 		連続列の時のみ
 * 
 * 	@param lColStart	上下限値設定開始列
 * 	@param lColEnd		上下限値設定終了列
 * 	@param fMin			下限値
 * 	@param fMax			上限値
 * 	@return				TRUE:成功 FALSE:失敗
 */
BOOL CFGridCtrlLU::SetColRange( long lColStart, long lColEnd, float fMin, float fMax )
{
	for( long lCol = lColStart; lCol <= lColEnd; lCol++ ){
		if( !SetColRange( lCol, fMin, fMax ) ){	return( FALSE );	}
	}
	return( TRUE );
}

/**
 * 	列範囲の入力上下限値を設定.
 * 		連続列の時のみ
 * 
 * 	@param lColStart	上下限値設定開始列
 * 	@param lColEnd		上下限値設定終了列
 * 	@param dMin			下限値
 * 	@param dMax			上限値
 * 	@return				TRUE:成功 FALSE:失敗
 */
BOOL CFGridCtrlLU::SetColRange( long lColStart, long lColEnd, double dMin, double dMax )
{
	for( long lCol = lColStart; lCol <= lColEnd; lCol++ ){
		if( !SetColRange( lCol, dMin, dMax ) ){	return( FALSE );	}
	}
	return( TRUE );
}