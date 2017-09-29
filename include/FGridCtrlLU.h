/**
 * 	@file	FGridCtrlLU.h
 *	VSFlexGrid 7.0 (Lingh/Unicode)���������饹
 * 
 * 	@date	2003.03.19	   n_yoshizaki	����
 * 	@date	2003.07.16	   n_yoshizaki	�@�Фˉ��
 *	@date	2005.06.14	s.yotsutsu OCX���Լ����h�v��׷��
 *	@date	2005.06.20	s.yotsutsu Excel��Enter key��simulate
 */

#ifndef	_FGRIDCTRL_LU_H_
#define	_FGRIDCTRL_LU_H_

#include <afxtempl.h>
#include "FGridDef.h"
#include "vsflexgridlu.h"


class CFGridCtrlLU : public CVSFlexGridLU
{

// ���`�Щ`�饤��
	// ClassWizard �ρ����v���Υ��`�Щ`�饤�ɤ����ɤ��ޤ���
	//{{AFX_VIRTUAL(CGridCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// ����ץ���Ʃ`�����
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

public:	//���󥹥ȥ饯�����
	CFGridCtrlLU();
	~CFGridCtrlLU();

public:
	///<Resize Kind
	typedef enum RESIZE_KIND{
		XY_RESIZE = 0,		///<X����Y����΁I�����Resize
		X_RESIZE,			///<X����Resize
		Y_RESIZE,			///<Y����Resize
	}ResizeKind;

protected:
private:
	///<Input Pattern
	typedef enum{
		FREE_INPUT   = -2,		///<Free Input( default )
		NO_CHANGE    = -1,		///<��������
		INPUT_BOOL   =  0,		///<BOOL��
		INPUT_INT    =  1,		///<int��
		INPUT_FLOAT  =  2,		///<float��
		INPUT_DOUBLE =  3,		///<double��
		INPUT_STRING =  4,		///<string��
	}INPUT_PTN;

	//Input Mode Setting
	typedef struct tagInputMode{
		int		iInputMode;	///<Input Mode
		long	lRow;		///<Input Mode������	��-1��ȫ�Ќ��꣩
		long	lCol;		///<Input Mode������
		int		istrNum;	///<������
		int		iIntNum;	///<��������
		int		iDecNum;	///<С������������
		BOOL	bMinus;		///<�ޥ��ʥ��S�ɥե饰�� TRUE:�S�� FALSE:���� ��
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
		long		lRow;		///<Input Range ������
		long		lCol;		///<Input Range ������
		RANGE_SET	min;		///<range min
		RANGE_SET	max;		///<range max
	}INPUT_RANGE;

	CArray<INPUT_RANGE, INPUT_RANGE>	m_InputRange;	///<Cell�����������С�����O��
	CArray<INPUT_MODE, INPUT_MODE>		m_InputMode;	///<Cell������Mode��ָ������
	CArray<CString, CString>			m_CopyBuf;		///<Cell����Line Copy���Ф����Ϥ�Array��ʹ��

	int				m_iInputMode;		///<Input Mode index

	int				m_iInputedLine;		///<��������Ƥ�����K�Ф򱣳�

	BOOL			m_bMode;			///<�����r�˼ȴ����֤��ʾ/�Ǳ�ʾ�� TRUE:��ʾ FALSE:�Ǳ�ʾ ��
	CString			m_strBefore;		///<���������ǰ��������

	int				m_iSelect;			///<Copy ����

	long			m_lTotalRow;		///<Gridȫ��
	long			m_lTotalCol;		///<Gridǰ��
	int				m_iLineNoStart;		///<�軭�_ʼ�з���
	BOOL			m_bLineNoDraw;		///<�з����軭�ե饰�� TRUE:�軭 FALSE:���軭 ��

	//grid a kind of color
	COLORREF		m_BkColor;			///<default background color
	COLORREF		m_FontColor;		///<default font color
	COLORREF		m_FixedFontColor;	///<default fixed row/col font color
	COLORREF		m_FixedBkColor;		///<default fixed row/col backgroud color
	COLORREF		m_borderColor;		///<default border color

	UINT			m_nKeyCode;			///< key
	BOOL			m_bExcelEnterMode;	///< select next row after return key
private:
	// OCX���Լ����h
	void RegisterMyself(void);
	// ���ڻ�
	void Initialize();

	//�ڲ����Ф�Indexȡ��
	int GetInputMode ( long lRow, long lCol );
	int GetModeIndex ( long lRow, long lCol );
	int GetRangeIndex( long lRow, long lCol );

	//Edit �v�S
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

	//�˜�Color�O��
	void SetDefaultFontColor();
	void SetDefaultBkColor();
	void SetDefaultFixedFontColor();
	void SetDefaultFixedBkColor();
	void SetDefaultBorderColor();

	//check �v�S
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

	//range check�v�S
	BOOL IntRangeChk   ( long lRow, long lCol, int iMin,    int iMax    );
	BOOL FloatRangeChk ( long lRow, long lCol, float fMin,  float fMax  );
	BOOL DoubleRangeChk( long lRow, long lCol, double dMin, double dMax );

public:
	void EditCell( long lRow, long lCol );					//Cell�򾎼��Ф��O��
	void SetCurCell( long lRow = 0 , long lCol = 0 );		//Select Cell���O��
	void GetCurCell( long& lRow, long& lCol );				//Select Cell��ȡ��

	//�˜�Color�O��
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

	//ɫ�䤨�v�S
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

	//ɫȡ��ϵ
	COLORREF GetCellFontColor( long lRow, long lCol );
	COLORREF GetCellBkColor  ( long lRow, long lCol );

	//Cell Bar graph
	void SetBar( long lRow, long lCol, int iValue, COLORREF barColor = RGB( 0x00, 0xff, 0x00 ) );

	//data setϵ
	void SetBool  ( long lRow, long lCol, BOOL    bBool                      );
	void SetInt   ( long lRow, long lCol, int     iNum, CString form = "%d"  );
	void SetFloat ( long lRow, long lCol, float   fNum, CString form = "%f"  );
	void SetDouble( long lRow, long lCol, double  dNum, CString form = "%f"  );
	void SetString( long lRow, long lCol, CString str, ...                   );
	void SetCheck( long lRow, long lCol, BOOL bChecked );	// for Check Box

	//data getϵ
	BOOL    GetBool  ( long lRow, long lCol );
	int     GetInt   ( long lRow, long lCol );
	float   GetFloat ( long lRow, long lCol );
	double  GetDouble( long lRow, long lCol );
	CString GetString( long lRow, long lCol );
	BOOL	GetCheck( long lRow, long lCol );	// for Check Box


	//Copy�v�S
	virtual int CopyLine();
	virtual int InsertLine();
	virtual int PasteLine();
	virtual int DeleteLine();

	inline BOOL HasCopyBuffer(){	return( m_iSelect );	}	//CopyLine�����ڤ���

	void AddLine( long lRow );
	void DeleteLine( long lRow );

	//Sort
	void SortSel( long lCol, short FAR* Order );
	void SortSel( long lRowStart, long lRowEnd, long lCol, short FAR* Order );

	//Scroll
	long PageUp  ( long lSize );
	long PageDown( long lSize );

	//size���
	void Resize( int iKind = XY_RESIZE, BOOL bVertical = FALSE, BOOL bHorizontal = FALSE );

	//initialize�v�S
	void SetMaxRowCol( long lRow, long lCol );
	void SetLineNum( int iStart = 1, BOOL bMode = TRUE );
	inline BOOL GetLineNum(){	return( m_bLineNoDraw );	};

	//data delete�v�S
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

	//�����r������ǰ�����б�ʾ/�Ǳ�ʾ�O��
	inline void SetEditDispMode( BOOL bMode ){	m_bMode = bMode;	}
	inline BOOL GetEditDispMode(){	return( m_bMode );	}

	//Excel��Enter key��simulate
	inline void EnableExcelEnterMode( BOOL bEnable )	{	m_bExcelEnterMode = bEnable;	}
	inline BOOL IsEnableExcelEnterMode( void )			{	return m_bExcelEnterMode;		}

	inline UINT GetInputEditKey(void)	{	return m_nKeyCode;	}

	//backgroud color �O��
	inline void SetBkColor( COLORREF color ){	m_BkColor = color;	}
	inline COLORREF GetBkColor(){	return( m_BkColor );	}
};

#endif	/* _FGRIDCTRL_LU_H_ */