/**
 * 	@file	����GDI�������x�ե�����
 * 
 * 	@date	2005-03-23		s.yotsutsu ��Ҏ����
 */

#ifndef __AX_GDIDEF_H_INCLUDED__
#define __AX_GDIDEF_H_INCLUDED__

/////////////////////////////////////////////////////////////////////////////
// ����
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

// ����եީ`���`
#define	MARKNONE		(0x00)	///< �ީ`���`�o��
#define	MARKCIRCLE		'��'	///< ��ީ`���`
#define	MARKCROSS		'��'	///< ���ީ`���`
#define	MARKSQUARE		'��'	///< ���ީ`���`
#define	MARKTRYANGLE	'��'	///< ���ީ`���`
#define	MARKRTRYANGLE	'��'	///< ���ީ`���`
#define	MARKDIAMOND		'��'	///< ��ީ`���`
#define	MARKASTERISK	'��'	///< ���ީ`���`
#define	MARKPLUS		'��'	///< ���ީ`���`

#define	AX_GDINOMODE 		0x00		///< X�S��`��
#define	AX_GDIXMODE 		0x01		///< X�S��`��
#define	AX_GDIYMODE			0x02		///< Y�S��`��
#define	AX_GDIXYMODE		0x03		///< XY�S��`��
#define	AX_GDIZMODE			0x04		///< Z�S��`��
#define	AX_GDIXZMODE		0x05		///< XZ�S��`��
#define	AX_GDIYZMODE		0x06		///< YZ�S��`��
#define	AX_GDIALLMODE		0x0F		///< YZ�S��`��
#define	AX_GDISHOW			0x10		///< ��ʾ�Є�
/// ���`���륿����
#define	CURSORNONE		(0x00)			///< ���`����o��
#define	CURSORX			AX_GDIXMODE		///< X�S���`����
#define	CURSORY			AX_GDIYMODE		///< Y�S���`����
#define	CURSORCROSS		AX_GDIXYMODE	///< ʮ�֥��`����

/// ����åɥ�����
#define	GRIDX			AX_GDIXMODE		///< X�S����å�
#define	GRIDY			AX_GDIYMODE		///< Y�S����å�

// Ŀʢ�꥿����
#define	MEASUREX		AX_GDIXMODE		///< X�SĿʢ��
#define	MEASUREY		AX_GDIYMODE		///< Y�SĿʢ��

#ifndef _AX_MATH_DEFINE
#define _AX_MATH_DEFINE
//Ӌ���ö����� //����BorlandC++3.1
#define M_PI			( 3.14159265358979323846 )		// ��

#endif // !defined _AX_MATH_DEFINE

#endif // __AX_GDIDEF_H_INCLUDED__