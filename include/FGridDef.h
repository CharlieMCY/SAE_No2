/**
 * 	@file	FGridDef.h
 *	VSFlexGrid 7.0 用の定数定義ファイル
 * 
 *	@date	2005.07.27	s.yotsutsu 作成
 */

#ifndef	_FGRIDDEF_H_
#define	_FGRIDDEF_H_

	typedef enum RESIZE_KIND{
		XY_RESIZE = 0,		///<X方向、Y方向の両方向をResize
		X_RESIZE,			///<X方向Resize
		Y_RESIZE,			///<Y方向Resize
	}ResizeKind;

	typedef enum MERGE_KIND{
		MERGE_NEVER = 0,	// 0	flexMergeNever	マージしない（デフォルト）
		MERGE_FREE,			// 1	flexMergeFree	セル単位同一内容を持つ隣接したセルをマージします（MergeRowまたはMergeColのいずれかがTrueに設定されている場合）。
		MERGE_ROWS,			// 2	flexMergeRestrictRows	列方向左のセルがマージされる場合のみ、列をマージします。
		MERGE_COLS,			// 3	flexMergeRestrictColumns	行方向上のセルがマージされる場合のみ、行をマージします。
		MERGE_ALL,			// 4	flexMergeRestrictAll	行と列上あるいは左のセルがマージされる場合のみ、セルをマージします。
		MERGE_FIXED,		// 5	flexMergeFixedOnly	固定セルのみ
		MERGE_SPILL,		// 6	flexMergeSpill	隣へはみだす隣のセルが空である限り、長いエントリも隣のセルにはみ出して表示できます。
		MERGE_OUTLINE,		// 7	flexMergeOutline	小計行を隣へはみだす小計行の値を、隣接する空白セル上にはみだして表示できます。この設定値を使用すると、アウトラインノード上にはノード名だけを、通常の行（ノードではない行）にはデータを表示できます。
	}MergeKind;

#endif	/* _FGRIDDEF_H_*/