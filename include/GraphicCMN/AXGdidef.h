/**
 * 	@file	拡張GDI定数定義ファイル
 * 
 * 	@date	2005-03-23		s.yotsutsu 新規作成
 */

#ifndef __AX_GDIDEF_H_INCLUDED__
#define __AX_GDIDEF_H_INCLUDED__

/////////////////////////////////////////////////////////////////////////////
// 定数
// Color 
#ifndef _AX_COLOR_DEFINE
#define _AX_COLOR_DEFINE
#define	IBLACK		(RGB(  0,  0,  0))	//Black
#define	IWHITE		(RGB(255,255,255))	//White
#define IBLUE		(RGB(  0,  0,255))	//Blue
#define IRED		(RGB(255,  0,  0))	//Red
#define IGREEN		(RGB(  0,255,  0))	//Green
#define IPINK		(RGB(255,  0,255))	//Pink
#define IYELLOW		(RGB(255,255,  0))	//Yellow
#define ILIGHTBLUE	(RGB(  0,128,255))	//LightBlue
#define ILIGHTGREEN	(RGB(128,255,  0))	//LightGreen
#define ILIGHTPINK	(RGB(255,128,255))	//LightPink
#define ISKYBLUE	(RGB(  0,255,255))  //SkyBlue
#define	IORANGE		(RGB(255,128,  0))	//Orange
#define IGRAY		(RGB(128,128,128))  //Gray
#define ILIGHTGRAY	(RGB(192,192,192))  //LightGray
#define ICTRLCOLOR	GetSysColor(COLOR_3DFACE)
#endif // !defined _AX_COLOR_DEFINE

// グラフマーカー
#define	MARKNONE		(0x00)	///< マーカー無し
#define	MARKCIRCLE		'○'	///< ○マーカー
#define	MARKCROSS		'×'	///< ×マーカー
#define	MARKSQUARE		'□'	///< □マーカー
#define	MARKTRYANGLE	'△'	///< △マーカー
#define	MARKRTRYANGLE	'▽'	///< ▽マーカー
#define	MARKDIAMOND		'◇'	///< ◇マーカー
#define	MARKASTERISK	'＊'	///< ＊マーカー
#define	MARKPLUS		'＋'	///< ＋マーカー

#define	AX_GDINOMODE 		0x00		///< X軸モード
#define	AX_GDIXMODE 		0x01		///< X軸モード
#define	AX_GDIYMODE			0x02		///< Y軸モード
#define	AX_GDIXYMODE		0x03		///< XY軸モード
#define	AX_GDIZMODE			0x04		///< Z軸モード
#define	AX_GDIXZMODE		0x05		///< XZ軸モード
#define	AX_GDIYZMODE		0x06		///< YZ軸モード
#define	AX_GDIALLMODE		0x0F		///< YZ軸モード
#define	AX_GDISHOW			0x10		///< 表示有効
/// カーソルタイプ
#define	CURSORNONE		(0x00)			///< カーソル無し
#define	CURSORX			AX_GDIXMODE		///< X軸カーソル
#define	CURSORY			AX_GDIYMODE		///< Y軸カーソル
#define	CURSORCROSS		AX_GDIXYMODE	///< 十字カーソル

/// グリッドタイプ
#define	GRIDX			AX_GDIXMODE		///< X軸グリッド
#define	GRIDY			AX_GDIYMODE		///< Y軸グリッド

// 目盛りタイプ
#define	MEASUREX		AX_GDIXMODE		///< X軸目盛り
#define	MEASUREY		AX_GDIYMODE		///< Y軸目盛り

#ifndef _AX_MATH_DEFINE
#define _AX_MATH_DEFINE
//計算用定数値 //引用BorlandC++3.1
#define M_PI			( 3.14159265358979323846 )		// π

#endif // !defined _AX_MATH_DEFINE

#endif // __AX_GDIDEF_H_INCLUDED__