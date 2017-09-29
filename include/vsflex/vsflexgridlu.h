#if !defined(AFX_VSFLEXGRIDLU_H__9D7A5ABB_C38E_4B43_9C6C_8B2AB381452B__INCLUDED_)
#define AFX_VSFLEXGRIDLU_H__9D7A5ABB_C38E_4B43_9C6C_8B2AB381452B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//  Microsoft Visual C++ によって自動生成された IDispatch ラップ クラス

// メモ: このファイルの内容を編集しないでください。 このクラスが再度
//  Microsoft Visual C++ で生成された場合、変更を上書きします。


// このインターフェイスによって参照されるディスパッチ インターフェイス。
class CPicture;
class COleFont;
class CVSFlexDataSourceLU;
class CVSFlexNodeLU;

/////////////////////////////////////////////////////////////////////////////
// CVSFlexGridLU ラップ クラス

class CVSFlexGridLU : public CWnd
{
protected:
	DECLARE_DYNCREATE(CVSFlexGridLU)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x429f6265, 0xb945, 0x11d3, { 0x9a, 0x1f, 0x9e, 0x67, 0x7, 0x13, 0x85, 0x31 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// アトリビュート
public:

// オペレーション
public:
	CString GetFontName();
	void SetFontName(LPCTSTR lpszNewValue);
	float GetFontSize();
	void SetFontSize(float newValue);
	BOOL GetFontBold();
	void SetFontBold(BOOL bNewValue);
	BOOL GetFontItalic();
	void SetFontItalic(BOOL bNewValue);
	BOOL GetFontStrikethru();
	void SetFontStrikethru(BOOL bNewValue);
	BOOL GetFontUnderline();
	void SetFontUnderline(BOOL bNewValue);
	long GetRows();
	void SetRows(long nNewValue);
	long GetCols();
	void SetCols(long nNewValue);
	short GetVersion();
	void SetVersion(short nNewValue);
	CString GetFormatString();
	void SetFormatString(LPCTSTR lpszNewValue);
	long GetFixedRows();
	void SetFixedRows(long nNewValue);
	long GetFixedCols();
	void SetFixedCols(long nNewValue);
	long GetTopRow();
	void SetTopRow(long nNewValue);
	long GetLeftCol();
	void SetLeftCol(long nNewValue);
	long GetRowSel();
	void SetRowSel(long nNewValue);
	long GetColSel();
	void SetColSel(long nNewValue);
	long GetRow();
	void SetRow(long nNewValue);
	long GetCol();
	void SetCol(long nNewValue);
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	unsigned long GetBackColor();
	void SetBackColor(unsigned long newValue);
	unsigned long GetForeColor();
	void SetForeColor(unsigned long newValue);
	unsigned long GetBackColorFixed();
	void SetBackColorFixed(unsigned long newValue);
	unsigned long GetForeColorFixed();
	void SetForeColorFixed(unsigned long newValue);
	unsigned long GetBackColorSel();
	void SetBackColorSel(unsigned long newValue);
	unsigned long GetForeColorSel();
	void SetForeColorSel(unsigned long newValue);
	unsigned long GetBackColorBkg();
	void SetBackColorBkg(unsigned long newValue);
	BOOL GetWordWrap();
	void SetWordWrap(BOOL bNewValue);
	long GetTextStyle();
	void SetTextStyle(long nNewValue);
	long GetTextStyleFixed();
	void SetTextStyleFixed(long nNewValue);
	BOOL GetScrollTrack();
	void SetScrollTrack(BOOL bNewValue);
	long GetFocusRect();
	void SetFocusRect(long nNewValue);
	long GetHighLight();
	void SetHighLight(long nNewValue);
	long GetRedraw();
	void SetRedraw(long nNewValue);
	long GetScrollBars();
	void SetScrollBars(long nNewValue);
	long GetMouseRow();
	long GetMouseCol();
	long GetCellLeft();
	long GetCellTop();
	long GetCellWidth();
	long GetCellHeight();
	long GetRowHeightMin();
	void SetRowHeightMin(long nNewValue);
	long GetFillStyle();
	void SetFillStyle(long nNewValue);
	long GetGridLines();
	void SetGridLines(long nNewValue);
	long GetGridLinesFixed();
	void SetGridLinesFixed(long nNewValue);
	unsigned long GetGridColor();
	void SetGridColor(unsigned long newValue);
	unsigned long GetGridColorFixed();
	void SetGridColorFixed(unsigned long newValue);
	unsigned long GetCellBackColor();
	void SetCellBackColor(unsigned long newValue);
	unsigned long GetCellForeColor();
	void SetCellForeColor(unsigned long newValue);
	long GetCellAlignment();
	void SetCellAlignment(long nNewValue);
	long GetCellTextStyle();
	void SetCellTextStyle(long nNewValue);
	CPicture GetCellPicture();
	void SetCellPicture(LPDISPATCH newValue);
	void SetRefCellPicture(LPDISPATCH newValue);
	long GetCellPictureAlignment();
	void SetCellPictureAlignment(long nNewValue);
	CString GetCellFontName();
	void SetCellFontName(LPCTSTR lpszNewValue);
	float GetCellFontSize();
	void SetCellFontSize(float newValue);
	BOOL GetCellFontBold();
	void SetCellFontBold(BOOL bNewValue);
	BOOL GetCellFontItalic();
	void SetCellFontItalic(BOOL bNewValue);
	float GetCellFontWidth();
	void SetCellFontWidth(float newValue);
	BOOL GetCellFontUnderline();
	void SetCellFontUnderline(BOOL bNewValue);
	BOOL GetCellFontStrikethru();
	void SetCellFontStrikethru(BOOL bNewValue);
	float GetFontWidth();
	void SetFontWidth(float newValue);
	CString GetClip();
	void SetClip(LPCTSTR lpszNewValue);
	void SetSort(long nNewValue);
	long GetSelectionMode();
	void SetSelectionMode(long nNewValue);
	long GetMergeCells();
	void SetMergeCells(long nNewValue);
	CPicture GetPicture();
	long GetPictureType();
	void SetPictureType(long nNewValue);
	BOOL GetAllowBigSelection();
	void SetAllowBigSelection(BOOL bNewValue);
	long GetAllowUserResizing();
	void SetAllowUserResizing(long nNewValue);
	long GetMousePointer();
	void SetMousePointer(long nNewValue);
	CPicture GetMouseIcon();
	void SetMouseIcon(LPDISPATCH newValue);
	void SetRefMouseIcon(LPDISPATCH newValue);
	BOOL GetVirtualData();
	void SetVirtualData(BOOL bNewValue);
	long GetEditable();
	void SetEditable(long nNewValue);
	CString GetComboList();
	void SetComboList(LPCTSTR lpszNewValue);
	double GetValue();
	unsigned long GetFloodColor();
	void SetFloodColor(unsigned long newValue);
	short GetCellFloodPercent();
	void SetCellFloodPercent(short nNewValue);
	unsigned long GetCellFloodColor();
	void SetCellFloodColor(unsigned long newValue);
	long GetSubtotalPosition();
	void SetSubtotalPosition(long nNewValue);
	long GetBorderStyle();
	void SetBorderStyle(long nNewValue);
	COleFont GetFont();
	void SetFont(LPDISPATCH newValue);
	void SetRefFont(LPDISPATCH newValue);
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	long GetAppearance();
	void SetAppearance(long nNewValue);
	long GetOutlineBar();
	void SetOutlineBar(long nNewValue);
	unsigned long GetTreeColor();
	void SetTreeColor(unsigned long newValue);
	short GetGridLineWidth();
	void SetGridLineWidth(short nNewValue);
	BOOL GetAutoResize();
	void SetAutoResize(BOOL bNewValue);
	long GetBottomRow();
	long GetRightCol();
	BOOL GetExtendLastCol();
	void SetExtendLastCol(BOOL bNewValue);
	long GetClientWidth();
	long GetClientHeight();
	CString GetEditText();
	void SetEditText(LPCTSTR lpszNewValue);
	long GetHWnd();
	long GetAutoSizeMode();
	void SetAutoSizeMode(long nNewValue);
	BOOL GetRightToLeft();
	void SetRightToLeft(BOOL bNewValue);
	BOOL GetMultiTotals();
	void SetMultiTotals(BOOL bNewValue);
	unsigned long GetBackColorAlternate();
	void SetBackColorAlternate(unsigned long newValue);
	long GetOwnerDraw();
	void SetOwnerDraw(long nNewValue);
	long GetDataMode();
	void SetDataMode(long nNewValue);
	long GetOLEDragMode();
	void SetOLEDragMode(long nNewValue);
	long GetOLEDropMode();
	void SetOLEDropMode(long nNewValue);
	long GetTabBehavior();
	void SetTabBehavior(long nNewValue);
	unsigned long GetSheetBorder();
	void SetSheetBorder(unsigned long newValue);
	BOOL GetAllowSelection();
	void SetAllowSelection(BOOL bNewValue);
	BOOL GetPicturesOver();
	void SetPicturesOver(BOOL bNewValue);
	long GetCellChecked();
	void SetCellChecked(long nNewValue);
	long GetMergeCompare();
	void SetMergeCompare(long nNewValue);
	long GetEllipsis();
	void SetEllipsis(long nNewValue);
	long GetOutlineCol();
	void SetOutlineCol(long nNewValue);
	long GetRowHeightMax();
	void SetRowHeightMax(long nNewValue);
	long GetAutoSearch();
	void SetAutoSearch(long nNewValue);
	long GetExplorerBar();
	void SetExplorerBar(long nNewValue);
	CString GetEditMask();
	void SetEditMask(LPCTSTR lpszNewValue);
	long GetEditSelStart();
	void SetEditSelStart(long nNewValue);
	long GetEditSelLength();
	void SetEditSelLength(long nNewValue);
	CString GetEditSelText();
	void SetEditSelText(LPCTSTR lpszNewValue);
	long GetEditMaxLength();
	void SetEditMaxLength(long nNewValue);
	long GetComboIndex();
	void SetComboIndex(long nNewValue);
	long GetComboCount();
	long GetColAlignment(long Col);
	void SetColAlignment(long Col, long nNewValue);
	long GetColWidth(long Col);
	void SetColWidth(long Col, long nNewValue);
	long GetRowHeight(long Row);
	void SetRowHeight(long Row, long nNewValue);
	BOOL GetMergeRow(long Row);
	void SetMergeRow(long Row, BOOL bNewValue);
	BOOL GetMergeCol(long Col);
	void SetMergeCol(long Col, BOOL bNewValue);
	void SetRowPosition(long Row, long nNewValue);
	void SetColPosition(long Col, long nNewValue);
	VARIANT GetRowData(long Row);
	void SetRowData(long Row, const VARIANT& newValue);
	VARIANT GetColData(long Col);
	void SetColData(long Col, const VARIANT& newValue);
	void AddItem(LPCTSTR Item, const VARIANT& Row);
	void RemoveItem(const VARIANT& Row);
	CString GetTextMatrix(long Row, long Col);
	void SetTextMatrix(long Row, long Col, LPCTSTR lpszNewValue);
	void Clear(const VARIANT& Where, const VARIANT& What);
	void EditCell();
	double GetValueMatrix(long Row, long Col);
	BOOL GetIsSubtotal(long Row);
	void SetIsSubtotal(long Row, BOOL bNewValue);
	void Subtotal(long Function, const VARIANT& GroupOn, const VARIANT& TotalOn, const VARIANT& Format, const VARIANT& BackColor, const VARIANT& ForeColor, const VARIANT& FontBold, const VARIANT& Caption, const VARIANT& MatchFrom, 
		const VARIANT& TotalOnly);
	void Refresh();
	void Outline(short Level);
	long GetFixedAlignment(long Col);
	void SetFixedAlignment(long Col, long nNewValue);
	BOOL GetRowIsVisible(long Row);
	BOOL GetColIsVisible(long Col);
	long GetRowPos(long Row);
	long GetColPos(long Col);
	BOOL GetIsSelected(long Row);
	void SetIsSelected(long Row, BOOL bNewValue);
	long GetIsCollapsed(long Row);
	void SetIsCollapsed(long Row, long nNewValue);
	void Select(long Row, long Col, const VARIANT& RowSel, const VARIANT& ColSel);
	void AutoSize(long Col1, const VARIANT& Col2, const VARIANT& Equal, const VARIANT& ExtraSpace);
	void CellBorder(unsigned long Color, short Left, short Top, short Right, short Bottom, short Vertical, short Horizontal);
	void OLEDrag();
	void SaveGrid(LPCTSTR FileName, long SaveWhat, const VARIANT& FixedCells);
	void LoadGrid(LPCTSTR FileName, long LoadWhat, const VARIANT& FixedCells);
	void Archive(LPCTSTR ArcFileName, LPCTSTR FileName, long Action);
	VARIANT GetArchiveInfo(LPCTSTR ArcFileName, long InfoType, const VARIANT& Index);
	long GetColSort(long Col);
	void SetColSort(long Col, long nNewValue);
	CString GetColFormat(long Col);
	void SetColFormat(long Col, LPCTSTR lpszNewValue);
	long GetColDataType(long Col);
	void SetColDataType(long Col, long nNewValue);
	VARIANT GetCell(long Setting, const VARIANT& Row1, const VARIANT& Col1, const VARIANT& Row2, const VARIANT& Col2);
	void SetCell(long Setting, const VARIANT& Row1, const VARIANT& Col1, const VARIANT& Row2, const VARIANT& Col2, const VARIANT& newValue);
	void SetRefCell(long Setting, const VARIANT& Row1, const VARIANT& Col1, const VARIANT& Row2, const VARIANT& Col2, const VARIANT& newValue);
	long GetRowStatus(long Row);
	void SetRowStatus(long Row, long nNewValue);
	long GetFindRow(const VARIANT& Item, const VARIANT& Row, const VARIANT& Col, const VARIANT& CaseSensitive, const VARIANT& FullMatch);
	CString GetComboItem(const VARIANT& Index);
	CString GetComboData(const VARIANT& Index);
	void BindToArray(const VARIANT& VariantArray, const VARIANT& RowDim, const VARIANT& ColDim, const VARIANT& PageDim, const VARIANT& CurrentPage);
	CString GetColEditMask(long Col);
	void SetColEditMask(long Col, LPCTSTR lpszNewValue);
	CString GetColComboList(long Col);
	void SetColComboList(long Col, LPCTSTR lpszNewValue);
	short GetRowOutlineLevel(long Row);
	void SetRowOutlineLevel(long Row, short nNewValue);
	long GetSelectedRows();
	long GetSelectedRow(long Index);
	BOOL GetScrollTips();
	void SetScrollTips(BOOL bNewValue);
	CString GetScrollTipText();
	void SetScrollTipText(LPCTSTR lpszNewValue);
	BOOL GetRowHidden(long Row);
	void SetRowHidden(long Row, BOOL bNewValue);
	BOOL GetColHidden(long Col);
	void SetColHidden(long Col, BOOL bNewValue);
	long GetColWidthMin();
	void SetColWidthMin(long nNewValue);
	long GetColWidthMax();
	void SetColWidthMax(long nNewValue);
	void GetMergedRange(long Row, long Col, long* R1, long* C1, long* R2, long* C2);
	BOOL GetShowComboButton();
	void SetShowComboButton(BOOL bNewValue);
	CPicture GetCellButtonPicture();
	void SetCellButtonPicture(LPDISPATCH newValue);
	void SetRefCellButtonPicture(LPDISPATCH newValue);
	long GetComboSearch();
	void SetComboSearch(long nNewValue);
	void LoadArray(const VARIANT& VariantArray, const VARIANT& RowDim, const VARIANT& ColDim, const VARIANT& PageDim, const VARIANT& CurrentPage);
	BOOL GetAutoSizeMouse();
	void SetAutoSizeMouse(BOOL bNewValue);
	void GetSelection(long* Row1, long* Col1, long* Row2, long* Col2);
	CString GetClipSeparators();
	void SetClipSeparators(LPCTSTR lpszNewValue);
	void PrintGrid(const VARIANT& DocName, const VARIANT& ShowDialog, const VARIANT& Orientation, const VARIANT& MarginLR, const VARIANT& MarginTB);
	long GetColImageList(long Col);
	void SetColImageList(long Col, long nNewValue);
	CString GetColKey(long Col);
	void SetColKey(long Col, LPCTSTR lpszNewValue);
	long GetColIndex(LPCTSTR Key);
	long GetFrozenRows();
	void SetFrozenRows(long nNewValue);
	long GetFrozenCols();
	void SetFrozenCols(long nNewValue);
	long GetAllowUserFreezing();
	void SetAllowUserFreezing(long nNewValue);
	unsigned long GetBackColorFrozen();
	void SetBackColorFrozen(unsigned long newValue);
	unsigned long GetForeColorFrozen();
	void SetForeColorFrozen(unsigned long newValue);
	CVSFlexDataSourceLU GetFlexDataSource();
	void SetFlexDataSource(LPDISPATCH newValue);
	long GetNodeRow(long Row, long Which);
	CString BuildComboList(LPDISPATCH rs, LPCTSTR FieldList, const VARIANT& KeyField, const VARIANT& BackColor);
	CPicture GetNodeOpenPicture();
	void SetNodeOpenPicture(LPDISPATCH newValue);
	void SetRefNodeOpenPicture(LPDISPATCH newValue);
	CPicture GetNodeClosedPicture();
	void SetNodeClosedPicture(LPDISPATCH newValue);
	void SetRefNodeClosedPicture(LPDISPATCH newValue);
	void ShowCell(long Row, long Col);
	float GetAutoSearchDelay();
	void SetAutoSearchDelay(float newValue);
	long GetEditWindow();
	CPicture GetWallPaper();
	void SetWallPaper(LPDISPATCH newValue);
	void SetRefWallPaper(LPDISPATCH newValue);
	long GetWallPaperAlignment();
	void SetWallPaperAlignment(long nNewValue);
	double GetAggregate(long Aggregate, long Row1, long Col1, long Row2, long Col2);
	long DragRow(long Row);
	CVSFlexNodeLU GetNode(const VARIANT& Row);
	long GetColIndent(long Col);
	void SetColIndent(long Col, long nNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_VSFLEXGRIDLU_H__9D7A5ABB_C38E_4B43_9C6C_8B2AB381452B__INCLUDED_)