//SAE_No2Cmn.cpp

#include "stdafx.h"
#include "SAE_No2Cmn.h"

///////////////////////////////////////////////////////
//

CGlobalData	g_data;

CGlobalData::CGlobalData()
{
	Init();
	ReadConfig();

	fWaveGraphPara.grp.bDispCursor = FALSE;
}

CGlobalData::~CGlobalData()
{
	SaveConfig();
}

void CGlobalData::Init()
{
	InitGraphPara();
	InitWaveGraphPara();
	memset(&fCond, 0, sizeof(fCond));
	fCond.Initvelocity = 0;
	fCond.Surfpressure = 0;
	fCond.Inertiamoment = 0.01;
	fCond.diskpieces = 0;
}

BOOL CGlobalData::SetCond(COND* pCond)
{
	BOOL bResult = TRUE;
	memcpy(&fCond, pCond, sizeof(COND));
	return bResult;
}

COND* CGlobalData::Cond() const
{
	return const_cast<COND*> (&fCond);
}

void CGlobalData::InitGraphPara()
{
	memset(&fGraphPara, '\0', sizeof(fGraphPara));

	fGraphPara.grp.clBgColor		= IWHITE;	//Graph 背景色
	fGraphPara.grp.clScaleColor		= IGRAY;	//Scale Color
	fGraphPara.grp.fScale			= 1.0;		//Grid Scale
	fGraphPara.grp.bDispGrid		= TRUE;		//Grid 表示有無
	fGraphPara.grp.lsGrid.color		= IGRAY;	//Grid Color
	fGraphPara.grp.lsGrid.iStyle	= PS_DOT;	//Grid Line Pen Style
	fGraphPara.grp.lsGrid.iSize		= -1;		//Grid Line Size
	fGraphPara.grp.bDispCursor		= FALSE;	//Cursor 表示有無
	fGraphPara.grp.iCursorMode		= CURSORX;	//Cursor 表示Mode CURSORX/CURSORY/CURSORCROSS
	fGraphPara.grp.lsCursor.color	= IRED;		//Cursor Color
	fGraphPara.grp.lsCursor.iStyle	= PS_SOLID;	//Cursor Line Pen Style
	fGraphPara.grp.lsCursor.iSize	= -1;		//Cursor Line Size
	fGraphPara.grp.clMasureColor	= IGRAY;	//Masure Line/Text Color

	for (int i = 0; i < WAVE_CH_MAX; i++)
	{
		fGraphPara.chp[i].bDisp					= TRUE;			//CH Line 表示有無
		fGraphPara.chp[i].bUseAutoScale			= FALSE;		//CH AutoScale 使用有無
		fGraphPara.chp[i].fMaximum				= 100;			//CH Scale Max
		fGraphPara.chp[i].fMinimum				= 0;			//CH Scale Min
		fGraphPara.chp[i].markerStyle.iMarker	= MARKNONE;		//Marker無し
		fGraphPara.chp[i].markerStyle.iMarkSize	= 8;			//Mark Size Default 8
		fGraphPara.chp[i].markerStyle.iBkStyle	= 0;			//Default 0
		fGraphPara.chp[i].lineStyle.iStyle		= PS_SOLID;		//CH Line Pen Style
		fGraphPara.chp[i].lineStyle.iSize		= 2;			//CH Line Size
		switch (i)
		{
		case 0:
			fGraphPara.chp[i].lineStyle.color = IBLUE;
			break;
		case 1:
			fGraphPara.chp[i].lineStyle.color = IRED;
			break;
		case 2:
			fGraphPara.chp[i].lineStyle.color = IGREEN;
			break;
		case 3:
			fGraphPara.chp[i].lineStyle.color = IYELLOW;
			break;
		}
	}

}

void CGlobalData::InitWaveGraphPara()
{
	memset(&fWaveGraphPara, '\0', sizeof(fWaveGraphPara));

	fWaveGraphPara.grp.clBgColor		= IWHITE;	//Graph 背景色
	fWaveGraphPara.grp.clScaleColor		= IGRAY;	//Scale Color
	fWaveGraphPara.grp.fScale			= 1.0;		//Grid Scale
	fWaveGraphPara.grp.bDispGrid		= TRUE;		//Grid 表示有無
	fWaveGraphPara.grp.lsGrid.color		= IGRAY;	//Grid Color
	fWaveGraphPara.grp.lsGrid.iStyle	= PS_DOT;	//Grid Line Pen Style
	fWaveGraphPara.grp.lsGrid.iSize		= -1;		//Grid Line Size
	fWaveGraphPara.grp.bDispCursor		= FALSE;	//Cursor 表示有無
	fWaveGraphPara.grp.iCursorMode		= CURSORX;	//Cursor 表示Mode CURSORX/CURSORY/CURSORCROSS
	fWaveGraphPara.grp.lsCursor.color	= IRED;		//Cursor Color
	fWaveGraphPara.grp.lsCursor.iStyle	= PS_SOLID;	//Cursor Line Pen Style
	fWaveGraphPara.grp.lsCursor.iSize	= -1;		//Cursor Line Size
	fWaveGraphPara.grp.clMasureColor	= IGRAY;	//Masure Line/Text Color

	for (int i = 0; i < WAVE_CH_MAX; i++)
	{
		fWaveGraphPara.chp[i].bDisp					= TRUE;			//CH Line 表示有無
		fWaveGraphPara.chp[i].bUseAutoScale			= FALSE;		//CH AutoScale 使用有無
		fWaveGraphPara.chp[i].fMaximum				= 100;			//CH Scale Max
		fWaveGraphPara.chp[i].fMinimum				= 0;			//CH Scale Min
		fWaveGraphPara.chp[i].markerStyle.iMarker	= MARKNONE;		//Marker無し
		fWaveGraphPara.chp[i].markerStyle.iMarkSize	= 8;			//Mark Size Default 8
		fWaveGraphPara.chp[i].markerStyle.iBkStyle	= 0;			//Default 0
		fWaveGraphPara.chp[i].lineStyle.iStyle		= PS_SOLID;		//CH Line Pen Style
		fWaveGraphPara.chp[i].lineStyle.iSize		= -1;			//CH Line Size
		switch (i)
		{
		case 0:
			fWaveGraphPara.chp[i].lineStyle.color = IBLUE;
			break;
		case 1:
			fWaveGraphPara.chp[i].lineStyle.color = IRED;
			break;
		case 2:
			fWaveGraphPara.chp[i].lineStyle.color = IGREEN;
			break;
		case 3:
			fWaveGraphPara.chp[i].lineStyle.color = IPINK;
			break;
		}
	}

}

BOOL CGlobalData::ReadConfig()
{
	BOOL bResult = FALSE;
	CFG_DATA cfg = {0};
	CString dirname, filename;

	GetModuleFilePath(dirname.GetBufferSetLength(MAX_PATH));
	filename.Format("%s%s", dirname, FILE_NAME_CONFIG);

	if (ReadConfigFile(filename, &cfg))
	{
		memcpy(&fCond, &cfg.Cond, sizeof(COND));
		memcpy(&fGraphPara, &cfg.GraphPara, sizeof(SAE_PARA));
		memcpy(&fWaveGraphPara, &cfg.WaveGraphPara, sizeof(SAE_PARA));
		bResult = TRUE;
	}
	return bResult;
}

BOOL CGlobalData::SaveConfig()
{
	BOOL bResult = FALSE;
	CFG_DATA cfg = {0};
	CString dirname, filename;

	GetModuleFilePath(dirname.GetBufferSetLength(MAX_PATH));
	filename.Format("%s%s", dirname, FILE_NAME_CONFIG);

	//data set
	memcpy(&cfg.Cond, &fCond, sizeof(COND));
	memcpy(&cfg.GraphPara, &fGraphPara, sizeof(SAE_PARA));
	memcpy(&cfg.WaveGraphPara, &fWaveGraphPara, sizeof(SAE_PARA));

	bResult = SaveConfigFile(filename, &cfg);

	return bResult;
}

SAE_PARA* CGlobalData::GraphPara() const
{
	return const_cast<SAE_PARA*> (&fGraphPara);
}

BOOL CGlobalData::SetGraphPara(SAE_PARA* pPara)
{
	BOOL bResult = TRUE;
	memcpy(&fGraphPara, pPara, sizeof(SAE_PARA));
	return bResult;
}

float CGlobalData::GetGraphYMax()
{
	int i = 0;
	float fResult = fGraphPara.chp[i].fMaximum;
	while (++i < WAVE_CH_MAX)
	{
		if (fResult < fGraphPara.chp[i].fMaximum)
		{
			fResult = fGraphPara.chp[i].fMaximum;
		}
	}
	return fResult;
}

float CGlobalData::GetGraphYMin()
{
	int i = 0;
	float fResult = fGraphPara.chp[i].fMinimum;
	while (++i < WAVE_CH_MAX)
	{
		if (fResult > fGraphPara.chp[i].fMinimum)
		{
			fResult = fGraphPara.chp[i].fMinimum;
		}
	}
	return fResult;
}

SAE_PARA* CGlobalData::WaveGraphPara() const
{
	return const_cast<SAE_PARA*> (&fWaveGraphPara);
}

BOOL CGlobalData::SetWaveGraphPara(SAE_PARA* pPara)
{
	BOOL bResult = TRUE;
	memcpy(&fWaveGraphPara, pPara, sizeof(SAE_PARA));
	return bResult;
}

float CGlobalData::GetWaveGraphYMin()
{
	int i = 0;
	float fResult = fWaveGraphPara.chp[i].fMinimum;
	while (++i < WAVE_CH_MAX)
	{
		if (fResult > fWaveGraphPara.chp[i].fMinimum)
		{
			fResult = fWaveGraphPara.chp[i].fMinimum;
		}
	}
	return fResult;
}

float CGlobalData::GetWaveGraphYMax()
{
	int i = 0;
	float fResult = fWaveGraphPara.chp[i].fMaximum;
	while (++i < WAVE_CH_MAX)
	{
		if (fResult < fWaveGraphPara.chp[i].fMaximum)
		{
			fResult = fWaveGraphPara.chp[i].fMaximum;
		}
	}
	return fResult;
}

double GetLogXMaxScale(double dblScaleMax)
{
#if 0
	double dblPwr = log(dblScaleMax);
	double dblTmp = floor(dblPwr + 0.5);
	if (dblPwr > dblTmp)
	{
		dblPwr = dblTmp;
	}
	else
	{
		dblPwr = floor(dblPwr - 0.5);
	}
	dblScaleMax = floor(exp(dblPwr));
	return dblScaleMax;
#else
	return CalcLowerLogScale(dblScaleMax);
#endif
}

double CalcLowerLogScale(double fi)
{
	short	sx ,ssign;
	double	fx , fy , fz ,fa ,fw;
	fa = 0.0 ;
	ssign = 1 ;
	if(fi < 0)
		ssign = -1 ;

	if(fi == 0.0) {
		fa = 0.0 ;
	} else {
		fx = fabs(fi) ;
		fw = log10(fx) ;

		if((short)fw < fw)
			sx = (short)fw;
		else
			sx = (short)log10(fx) - 1;
		fz = pow(10.0,(double)(sx) );
		fa = fz;
		fy = fz / fx;
		if(fy < 1.0)
			fa = 1.0 * fz * (double)ssign ;
		if(fy < 0.5)
			fa = (1.0 / 0.5) * fz * (double)ssign ;
		if(fy < 0.2)
			fa = (1.0 / 0.2) * fz * (double)ssign ;
	}
	return fa;
}

BOOL GetModuleFilePath(char *szPath)
{
	BOOL bResult = FALSE;
	DWORD dwRet;
	TCHAR sz[_MAX_PATH];
	TCHAR szDrive[_MAX_DRIVE];
	TCHAR szDir[_MAX_DIR];

	// 実行モジュールのフルパスの取得
	dwRet = GetModuleFileName(NULL, sz, sizeof(sz));
	if(dwRet)
	{
		// フルパスを分解
		_tsplitpath(sz, szDrive, szDir, NULL, NULL);

		// szPathに実行モジュールのパスを作成
		_tcscpy(szPath, szDrive);
		_tcscat(szPath, szDir);
		bResult = TRUE;
	}
	return bResult;
}

BOOL ReadConfigFile(CString strFileName, CFG_DATA* pCfg)
{
	BOOL bResult = FALSE;

	bResult = sysReadFile(strFileName, (char *)pCfg, sizeof(CFG_DATA));

	return bResult;
}

BOOL SaveConfigFile(CString strFileName, CFG_DATA* pCfg)
{
	BOOL bResult = FALSE;

	bResult = sysSaveFile(strFileName, (char *)pCfg, sizeof(CFG_DATA));

	return bResult;
}

BOOL sysSaveFile( CString strFileName, char *pData, int iSize)
{
	CFile			f;
	CFileException	e;
	CString			name,sNo;
	HFILE			hFile;
	OFSTRUCT		ofstruct;
	BOOL			stat;

	name = strFileName;

	hFile = OpenFile( name, &ofstruct, OF_EXIST );
	if(hFile == HFILE_ERROR) {
		stat = f.Open( name, CFile::modeCreate | CFile::modeWrite, &e);
	}
	else {
		stat = FALSE;
		MessageBeep(MB_OK);
		stat = f.Open( name, CFile::modeWrite, &e);
	}
	if (stat == TRUE)
	{
		try
		{
			f.Write( (char *)pData, iSize );
		}
		catch(CFileException* e)
		{
			f.Abort();
			e->Delete();
			return FALSE;
		}
		f.Close();
	}
	return( stat );
}

BOOL sysReadFile( CString strFileName, char *pData, int iSize)
{
	FILE *fp;
	char path[256];
	BOOL bRet=FALSE;

	memset( pData, 0, iSize );

	sprintf( path, "%s", strFileName );
	fp = fopen( path, "rb" );
	if( fp != NULL ){
		if( fread( pData, iSize, 1, fp ) == 1 ){
			// ＴＰデータの更新
			bRet = TRUE;
		}
		fclose( fp );
	}

	return( bRet );
}