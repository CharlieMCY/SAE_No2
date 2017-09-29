/**
 * 	@file	FGridCtrlLU.h
 *	VSFlexGrid 7.0 (Lingh/Unicode)の派生クラス
 * 
 * 	@date	2003.03.19	   n_yoshizaki	初版
 * 	@date	2003.07.16	   n_yoshizaki	継承に変更
 *	@date	2005.06.14	s.yotsutsu OCXの自己登録関数追加
 *	@date	2005.06.20	s.yotsutsu ExcelのEnter keyをsimulate
 */

#ifndef	_FGRIDCTRL_LU_H_
#define	_FGRIDCTRL_LU_H_

#include <afxtempl.h>
#include "FGridDef.h"
#include "vsflexgridlu.h"


class CFGridCtrlLU : public CVSFlexGridLU
{

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CGridCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	//{{AFX_MSG(CGridCtrl)
	afx_msg void OnStartEdit( long lRow, long lCol, BOOL FAR* Cancel );
	afx_msg void OnChangeEdit();
	afx_msg void OnAfterEdit( long lRow, long lCol );
	afx_msg void OnKeyPressEdit( long Row, long Col, short FAR* KeyAscii );
	afx_msg void OnKeyPress( short FAR* KeyAscii ) ;
	afx_msg void OnKeyUp( short FAR* KeyCode, short Shift );
	afx_msg void OnBeforeEdit( long Row, long Col, BOOL FAR* Cancel ); 
	//}}AFX_MSG
	DECLARE_EVENTSINK_MAP()

public:	//コンストラクション
	CFGridCtrlLU();
	~CFGridCtrlLU();

public:
	///<Resize Kind
	typedef enum RESIZE_KIND{
		XY_RESIZE = 0,		///<X方向、Y方向の両方向をResize
		X_RESIZE,			///<X方向Resize
		Y_RESIZE,			///<Y方向Resize
	}ResizeKind;

protected:
private:
	///<Input Pattern
	typedef enum{
		FREE_INPUT   = -2,		///<Free Input( default )
		NO_CHANGE    = -1,		///<編集不可
		INPUT_BOOL   =  0,		///<BOOL型
		INPUT_INT    =  1,		///<int型
		INPUT_FLOAT  =  2,		///<float型
		INPUT_DOUBLE =  3,		///<double型
		INPUT_STRING =  4,		///<string型
	}INPUT_PTN;

	//Input Mode Setting
	typedef struct tagInputMode{
		int		iInputMode;	///<Input Mode
		long	lRow;		///<Input Mode対応行	（-1で全行対応）
		long	lCol;		///<Input Mode対応列
		int		istrNum;	///<文字数
		int		iIntNum;	///<整数桁数
		int		iDecNum;	///<小数点以下桁数
		BOOL	bMinus;		///<マイナス許可フラグ（ TRUE:許可 FALSE:不可 ）
	}INPUT_MODE;

	///Range Set
	typedef union tagRangeSet{
		int		iNum;
		float	fNum;
		double	dNum;
	}RANGE_SET;

	///Range type Structure
	typedef struct tagInputRange{
		int			iInputMode;	///<InputMode
		long		lRow;		///<Input Range 対応行
		long		lCol;		///<Input Range 対応列
		RANGE_SET	min;		///<range min
		RANGE_SET	max;		///<range max
	}INPUT_RANGE;

	CArray<INPUT_RANGE, INPUT_RANGE>	m_InputRange;	///<Cellの入力最大最小値を設定
	CArray<INPUT_MODE, INPUT_MODE>		m_InputMode;	///<Cellの入力Modeを指定する
	CArray<CString, CString>			m_CopyBuf;		///<Cell毎のLine Copyを行う場合はArrayを使用

	int				m_iInputMode;		///<Input Mode index

	int				m_iInputedLine;		///<入力されている最終行を保持

	BOOL			m_bMode;			///<編集時に既存文字を表示/非表示（ TRUE:表示 FALSE:非表示 ）
	CString			m_strBefore;		///<編集される前の文字列

	int				m_iSelect;			///<Copy 行数

	long			m_lTotalRow;		///<Grid全行
	long			m_lTotalCol;		///<Grid前列
	int				m_iLineNoStart;		///<描画開始行番号
	BOOL			m_bLineNoDraw;		///<行番号描画フラグ（ TRUE:描画 FALSE:非描画 ）

	//grid a kind of color
	COLORREF		m_BkColor;			///<default background color
	COLORREF		m_FontColor;		///<default font color
	COLORREF		m_FixedFontColor;	///<default fixed row/col font color
	COLORREF		m_FixedBkColor;		///<default fixed row/col backgroud color
	COLORREF		m_borderColor;		///<default border color

	UINT			m_nKeyCode;			///< key
	BOOL			m_bExcelEnterMode;	///< select next row after return key
private:
	// OCXの自己登録
	void RegisterMyself(void);
	// 初期化
	void Initialize();

	//内部配列のIndex取得
	int GetInputMode ( long lRow, long lCol );
	int GetModeIndex ( long lRow, long lCol );
	int GetRangeIndex( long lRow, long lCol );

	//Edit 関係
	void OnChangeEditBool  ();
	void OnChangeEditInt   ( int iIntNum, BOOL bMinus );
	void OnChangeEditFloat ( int iIntNum, int iDecNum, BOOL bMinus );
	void OnChangeEditDouble( int iIntNum, int iDecNum, BOOL bMinus );
	void OnChangeEditString( int iLength );

	void OnAfterEditBool  ( long lRow, long lCol );
	void OnAfterEditInt   ( long lRow, long lCol );
	void OnAfterEditFloat ( long lRow, long lCol, int iDecNum );
	void OnAfterEditDouble( long lRow, long lCol, int iDecNum );
	void OnAfterEditString( long lRow, long lCol );

	//標準Color設定
	void SetDefaultFontColor();
	void SetDefaultBkColor();
	void SetDefaultFixedFontColor();
	void SetDefaultFixedBkColor();
	void SetDefaultBorderColor();

	//check 関係
	BOOL NumChk( char cCh );
	void DelOverString( CString str, int iDelIdx );

	void SetMaxRowCol();
	void DrawLineNum();
	void UndoGrid();

	//InputMode
	BOOL SetInputMode( int iMode, long lRow, long lCol, int iIntNum = 1, int iDecNum = 0, BOOL bMinus = FALSE );

protected:
	void CopyOneLine( long lRow );
	void PasteOneLine( long lRow, int iIndex );

	//range check関係
	BOOL IntRangeChk   ( long lRow, long lCol, int iMin,    int iMax    );
	BOOL FloatRangeChk ( long lRow, long lCol, float fMin,  float fMax  );
	BOOL DoubleRangeChk( long lRow, long lCol, double dMin, double dMax );

public:
	void EditCell( long lRow, long lCol );					//Cellを編集中に設定
	void SetCurCell( long lRow = 0 , long lCol = 0 );		//Select Cellを設定
	void GetCurCell( long& lRow, long& lCol );				//Select Cellを取得

	//標準Color設定
	void SetDefaultFontColor     ( COLORREF defaultFontColor      );
	void SetDefaultBkColor       ( COLORREF defaultBkColor        );
	void SetDefaultFixedFontColor( COLORREF defaultFixedFontColor );
	void SetDefaultFixedBkColor  ( COLORREF defaultFixedBkColor   );
	void SetDefaultBorderColor   ( COLORREF defaultBorderColor    );

	COLORREF GetDefaultFontColor();
	COLORREF GetDefaultBkColor();
	COLORREF GetDefaultFixedFontColor();
	COLORREF GetDefaultFixedBkColor();
	COLORREF GetDefaultBorderColor();

	//色変え関係
	void ChangeUnderRowColor( long lRow,                    COLORREF noUseColor     );
	void SetCellFontColor   ( long lRow,      long lCol,    COLORREF fixedFontColor );
	void SetRowFontColor    ( long lRow,                    COLORREF fixedFontColor );
	void SetRowFontColor    ( long lRowStart, long lRowEnd, COLORREF fixedFontColor );
	void SetColFontColor    ( long lCol,                    COLORREF fixedFontColor );
	void SetColFontColor    ( long lColStart, long lColEnd, COLORREF fixedFontColor );
	void SetCellBkColor     ( long lRow,      long lCol,    COLORREF fixedBkColor   );
	void SetRowBkColor      ( long lRow,                    COLORREF fixedBkColor   );
	void SetRowBkColor      ( long lRowStart, long lRowEnd, COLORREF fixedBkColor   );
	void SetColBkColor      ( long lCol,                    COLORREF fixedBkColor   );
	void SetColBkColor      ( long lColStart, long lColEnd, COLORREF fixedBkColor   );
	void SetCellBorderColor ( long lRowStart, long lColStart, long lRowEnd = -1, long lColEnd = -1, BOOL bMode = TRUE, COLORREF borederColor = RGB( 0x00, 0x00, 0x00 ) );

	//色取得系
	COLORREF GetCellFontColor( long lRow, long lCol );
	COLORREF GetCellBkColor  ( long lRow, long lCol );

	//Cell Bar graph
	void SetBar( long lRow, long lCol, int iValue, COLORREF barColor = RGB( 0x00, 0xff, 0x00 ) );

	//data set系
	void SetBool  ( long lRow, long lCol, BOOL    bBool                      );
	void SetInt   ( long lRow, long lCol, int     iNum, CString form = "%d"  );
	void SetFloat ( long lRow, long lCol, float   fNum, CString form = "%f"  );
	void SetDouble( long lRow, long lCol, double  dNum, CString form = "%f"  );
	void SetString( long lRow, long lCol, CString str, ...                   );
	void SetCheck( long lRow, long lCol, BOOL bChecked );	// for Check Box

	//data get系
	BOOL    GetBool  ( long lRow, long lCol );
	int     GetInt   ( long lRow, long lCol );
	float   GetFloat ( long lRow, long lCol );
	double  GetDouble( long lRow, long lCol );
	CString GetString( long lRow, long lCol );
	BOOL	GetCheck( long lRow, long lCol );	// for Check Box


	//Copy関係
	virtual int CopyLine();
	virtual int InsertLine();
	virtual int PasteLine();
	virtual int DeleteLine();

	inline BOOL HasCopyBuffer(){	return( m_iSelect );	}	//CopyLineが存在する

	void AddLine( long lRow );
	void DeleteLine( long lRow );

	//Sort
	void SortSel( long lCol, short FAR* Order );
	void SortSel( long lRowStart, long lRowEnd, long lCol, short FAR* Order );

	//Scroll
	long PageUp  ( long lSize );
	long PageDown( long lSize );

	//size変更
	void Resize( int iKind = XY_RESIZE, BOOL bVertical = FALSE, BOOL bHorizontal = FALSE );

	//initialize関係
	void SetMaxRowCol( long lRow, long lCol );
	void SetLineNum( int iStart = 1, BOOL bMode = TRUE );
	inline BOOL GetLineNum(){	return( m_bLineNoDraw );	};

	//data delete関係
	void DeleteGridData   (            BOOL bDelFixedCell = FALSE );
	void DeleteGridRowData( long lRow, BOOL bDelFixedCol  = FALSE );
	void DeleteGridColData( long lCol, BOOL bDelFixedRow  = FALSE );

	//input mode setting
	BOOL SetNoEditCell( long lRow, long lCol );
	BOOL SetNoEditRow ( long lRow );
	BOOL SetNoEditCol ( long lCol );
	BOOL SetNoEditRows( long lRowStart, long lRowEnd );
	BOOL SetNoEditCols( long lColStart, long lRowEnd );

	BOOL SetBoolCell( long lRow, long lCol );
	BOOL SetBoolRow ( long lRow );
	BOOL SetBoolCol ( long lCol );
	BOOL SetBoolRows( long lRowStart, long lRowEnd );
	BOOL SetBoolCols( long lColStart, long lColEnd );

	BOOL SetIntCell( long lRow,      long lCol,    int iIntNum = 1, BOOL bMinus = TRUE );
	BOOL SetIntRow ( long lRow,                    int iIntNum = 1, BOOL bMinus = TRUE );
	BOOL SetIntCol ( long lCol,                    int iIntNum = 1, BOOL bMinus = TRUE );
	BOOL SetIntRows( long lRowStart, long lRowEnd, int iIntNum = 1, BOOL bMinus = TRUE );
	BOOL SetIntCols( long lColStart, long lColEnd, int iIntNum = 1, BOOL bMinus = TRUE );

	BOOL SetFloatCell( long lRow,      long lCol,    int iIntNum = 1, int iDecNum = 0, BOOL bMinus = TRUE );
	BOOL SetFloatRow ( long lRow,                    int iIntNum = 1, int iDecNum = 0, BOOL bMinus = TRUE );
	BOOL SetFloatCol ( long lCol,                    int iIntNum = 1, int iDecNum = 0, BOOL bMinus = TRUE );
	BOOL SetFloatRows( long lRowStart, long lRowEnd, int iIntNum = 1, int iDecNum = 0, BOOL bMinus = TRUE );
	BOOL SetFloatCols( long lColStart, long lColEnd, int iIntNum = 1, int iDecNum = 0, BOOL bMinus = TRUE );

	BOOL SetDoubleCell( long lRow,      long lCol,    int iIntNum = 1, int iDecNum = 0, BOOL bMinus = TRUE );
	BOOL SetDoubleRow ( long lRow,                    int iIntNum = 1, int iDecNum = 0, BOOL bMinus = TRUE );
	BOOL SetDoubleCol ( long lCol,                    int iIntNum = 1, int iDecNum = 0, BOOL bMinus = TRUE );
	BOOL SetDoubleRows( long lRowStart, long lRowEnd, int iIntNum = 1, int iDecNum = 0, BOOL bMinus = TRUE );
	BOOL SetDoubleCols( long lColStart, long lColEnd, int iIntNum = 1, int iDecNum = 0, BOOL bMinus = TRUE );

	BOOL SetStringCell( long lRow,      long lCol,    int iIntNum = 1 );
	BOOL SetStringRow ( long lRow,                    int iIntNum = 1 );
	BOOL SetStringCol ( long lCol,                    int iIntNum = 1 );
	BOOL SetStringRows( long lRowStart, long lRowEnd, int iIntNum = 1 );
	BOOL SetStringCols( long lColStart, long lColEnd, int iIntNum = 1 );

	//input range setting
	BOOL SetCellRange( long lRow, long lCol, int    iMin, int    iMax );
	BOOL SetCellRange( long lRow, long lCol, float  fMin, float  fMax );
	BOOL SetCellRange( long lRow, long lCol, double dMin, double dMax );

	BOOL SetRowRange( long lRow, int    iMin, int    iMax );
	BOOL SetRowRange( long lRow, float  fMin, float  fMax );
	BOOL SetRowRange( long lRow, double dMin, double dMax );

	BOOL SetColRange( long lCol, int    iMin, int    iMax );
	BOOL SetColRange( long lCol, float  fMin, float  fMax );
	BOOL SetColRange( long lCol, double dMin, double dMax );

	BOOL SetRowRange( long lRowStart, long lRowEnd, int    iMin, int    iMax );
	BOOL SetRowRange( long lRowStart, long lRowEnd, float  fMin, float  fMax );
	BOOL SetRowRange( long lRowStart, long lRowEnd, double dMin, double dMax );

	BOOL SetColRange( long lColStart, long lColEnd, int    iMin, int    iMax );
	BOOL SetColRange( long lColStart, long lColEnd, float  fMin, float  fMax );
	BOOL SetColRange( long lColStart, long lColEnd, double dMin, double dMax );

	//編集時、編集前文字列表示/非表示設定
	inline void SetEditDispMode( BOOL bMode ){	m_bMode = bMode;	}
	inline BOOL GetEditDispMode(){	return( m_bMode );	}

	//ExcelのEnter keyをsimulate
	inline void EnableExcelEnterMode( BOOL bEnable )	{	m_bExcelEnterMode = bEnable;	}
	inline BOOL IsEnableExcelEnterMode( void )			{	return m_bExcelEnterMode;		}

	inline UINT GetInputEditKey(void)	{	return m_nKeyCode;	}

	//backgroud color 設定
	inline void SetBkColor( COLORREF color ){	m_BkColor = color;	}
	inline COLORREF GetBkColor(){	return( m_BkColor );	}
};

#endif	/* _FGRIDCTRL_LU_H_ */