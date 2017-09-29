//SAE_No2Cmn.h : Global Data

#ifndef _SAE_NO2CMNH_
#define _SAE_NO2CMNH_

#include "SAE_No2defs.h"
#include "SerialPort.h"
#include <math.h>

///////////////////////////////////////////////////////
//

double	GetLogXMaxScale(double dblScaleMax);
double	CalcLowerLogScale(double fi);
BOOL	ReadConfigFile(CString strFileName, CFG_DATA* pCfg);
BOOL	SaveConfigFile(CString strFileName, CFG_DATA* pCfg);
BOOL	GetModuleFilePath(char *szPath);
BOOL	sysReadFile( CString strFileName, char *pData, int iSize);
BOOL	sysSaveFile( CString strFileName, char *pData, int iSize);

class CGlobalData
{
public:
	CGlobalData();
	~CGlobalData();
	void		Init();
	void		InitGraphPara();
	void		InitWaveGraphPara();
	BOOL		SaveConfig();
	BOOL		ReadConfig();
	BOOL		SetCond(COND* pCond);
	BOOL		SetCom(COM* pCom);
	COND*		Cond() const;
	SAE_PARA*	GraphPara() const;
	BOOL		SetGraphPara(SAE_PARA* pPara);
	float GetGraphYMax();
	float GetGraphYMin();
	SAE_PARA*	WaveGraphPara() const;
	BOOL		SetWaveGraphPara(SAE_PARA* pPara);
	float		GetWaveGraphYMin();
	float		GetWaveGraphYMax();
private:
	COND		fCond;
	SAE_PARA	fGraphPara;
	SAE_PARA	fWaveGraphPara;
};


extern CGlobalData g_data;


#endif