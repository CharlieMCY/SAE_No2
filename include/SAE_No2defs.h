//SAE_No2defs.h : The defs of variables and structs.

#ifndef _SAE_NO2DEFSH_
#define _SAE_NO2DEFSH_

#include ".\GraphicCMN\AXGdiCore.h"

#define	FILE_NAME_CONFIG	"SAE_No2.cfg"

#define	FORM_POINT		"%.2lf"
#define	FORM_POINT_TL	"%.1lf"
#define FORM_POINT_TM	"%.6lf"
#define FORM_POINT_TB	"%.5lf"

#define	NOTE_WAVE_NUM	200

#define	MAX_RI_CH	8
#define MAX_UI_CH	6

#define DEFAULT_INT_DIGIT	5		//floatフォーマット時のデフォルト整数部桁数
#define DEFAULT_DEC_DIGIT	1		//floatフォーマット時のデフォ

typedef enum WAVE_DLG_KIND {
	WAVE_DLG_KIND_MAIN = 0,
	WAVE_DLG_KIND_FILE,
};

typedef enum WAVE_CH {
	WAVE_CH_1	= 0,	//CH1
	WAVE_CH_2,			//CH2
	WAVE_CH_3,			//CH3
	WAVE_CH_4,			//CH4
	WAVE_CH_MAX,		//MAX of CH
};

///////////////////////////////////////////////////////
//Test Conditions struct

typedef struct CONDITION {
	int		Initvelocity;
	double	Surfpressure;
	double	Inertiamoment;
	int	diskpieces;
} COND;

///////////////////////////////////////////////////////
//Defs of the Graph
//

typedef struct GRAPH_CH_PARA {
	int			iAxis;
	bool		bDisp;
	bool		bUseAutoScale;		//Auto Scale
	float		fMinimum;			//Y軸物理値最小値
	float		fMaximum;			//Y軸物理値最大値
	LINESTYLE	lineStyle;			//Line Style
	MARKERSTYLE	markerStyle;		//Marker Style
} CH_PARA;

typedef struct GRAPH_PARA {
	COLORREF 	clBgColor;
	COLORREF 	clScaleColor;
	float		fScale;				//Scale: 1.0/2.0/5.0
	BOOL		bDispGrid;
	LINESTYLE	lsGrid;				//Grid X Line Style
	BOOL		bDispCursor;
	int			iCursorMode;		//Cursor Mode default: CURSORX
	LINESTYLE	lsCursor;
	COLORREF 	clMasureColor;
} G_PARA;

typedef struct SAE_GRAPH_PARA {
	CH_PARA chp[WAVE_CH_MAX];		//0:rotation velocity/1:force/2:torque/3:film thicking
	G_PARA	grp;
} SAE_PARA;

///////////////////////////////////////////////////////
//Config Parameter

typedef struct _CFG_DATA{
	COND		Cond;
	SAE_PARA	GraphPara;
	SAE_PARA	WaveGraphPara;
} CFG_DATA;

///////////////////////////////////////////////////////
//Defs of the Measure Data

typedef struct SAENo2_MINI {
	float	fRotavelocity;
	float	fPreforce;
	float	fTorque;
	float	fFlimthick;
	float	fCoe;
	float	fTHL;
	float	fTBL;
} SAE_MINI;

typedef struct SAENo2_IN {
	float	fTemperature;
	float	fInner;
	float	fOuter;
	float	fThicklining;
	float	fViscosity;
	double	fFilmthick;
	float	fSurfroughness;
	float	fAsperityden;
}SAE_IN;

typedef struct SAE_No2 {
	float		fCoefriction;
	float		fTimestop;
	COND		cond;
	SAE_IN		saein;
	SAE_MINI	*saem;
} SAE;

typedef struct COM_SET {
	int		PortNO;
	int		BaudRate;
	char	Parity;
	int		DataBits;
	int		StopBits;
} COM;

#endif