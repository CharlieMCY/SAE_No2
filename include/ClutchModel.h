#include <math.h>
#include <float.h>

/*#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif*/

#define ERF_PI 3.141592653589793
#define ERF_N 100

//1.Function Block Parameters:Film Thickness
#define  Pr         196.2e6     //Pressure constant[Pa]
#define  z0         38          //Viscosity-pressure index
#define  s0         2           //Viscosity-temperature index
//#define  mu0        0.1         //Viscosity at ambient pressure[Pa.s]
#define  mumax      6.31e-5     //Viscosity constant[pa.s]
#define  Kper		2.3e-15		//permeability of material[m^2]
#define  E			27e6		//Young's elastic modulus[Pa]
#define  beta		5e-4		//asperity tip radius of wet friction meterial[m]
#define  AL			0.79		//landed area ratio[%]
#define  chi		0.2			//Beavars Joseph slip coefficient

//2.Function Block Parameters: ML&BL model
#define  E			27e6		//Young's elastic modulus[Pa]
#define  beta		5e-4		//asperity tip radius of wet friction meterial[m]
#define  c			1e12		//corrected factor for roughness and skewness
#define  delta		4			//shape factor of Weibull for skewness
#define  xir		14			//scale factor of Weibull for riughness

//3.Function Block Parameters: ML&HL&EHL model
#define  beta		5e-4		//asperity tip radius of wet friction meterial[m]

//4.Function Block Parameters: Clutch unlocked
#define  bm			0.02		//motor damping[Nm/(rad*sec)]
#define  mud		11.2		//engagement time scale factor
//#define  mu0        0.1         //Viscosity at ambient pressure[Pa.s]
#define  mumax      6.31e-5     //Viscosity constant[pa.s]
#define  Pr         196.2e6     //Pressure constant[Pa]
#define  z0         38          //Viscosity-pressure index
#define  s0         2           //Viscosity-temperature index

//5.Function Block Parameters: mu-v model

//6.Function Block Parameters: Piston setting
#define  Ap			0.01511		//Piston area[m^2]
//#define  Temp       80			//Temperature setting[OC]

class ClutchModel
{
public:
	double Temp0; 			//环境温度
	double ro;				//外径
	double ri;				//内径
	double sigma;			//表面粗糙度
	double h0;				//初始膜厚
	double d;				//摩擦材厚度
	double m;				//粗糙密度
	double mu0;				//粘度
	double mu;				//动力粘度
	double w0;				//初始转速
	double Jm;				//转动惯量
	double faces;			//摩擦片面数
	double Pre;				//设定面压
	double Papp;			//?
	double Temp;			//设定油温
	double Tc_k1;
	double wrel_k1;

	double WetClutchPistonSetting(double Finmin);
	double WetClutchFilmThickness(double Papp,double Temp,double h);
	double WetClutchUnlocked(double Temp,double Papp,double h,double Tc,double w_rel);
	double WetClutchMLandBLmode(double h,double w_rel,double Papp,double w0);
	double WetClutchMLandHLmode(double h,double w_rel,double w0);
	double WetClutchMuModel(double Fapp,double Tc);

private:
	double GSer(double x, double a);
	double Gcf(double x, double a);
	double gammainc(double x, double a);
	double gamma(double x);
	double gammLn(double xx);
	double erf(double x);

	double integ_s(double accel,double speed0,double samp_t);

	double WetClutchFilmThickness_Temperature(double Papp, double Temp);
	double WetClutchFilmThickness_ScalingFactor(double h);
	double WetClutchFilmThickness_FlowFactor(double h);
	double WetClutchFilmThickness_PermeabilityPaper(double h);
	double WetClutchFilmThickness_ForceBalance(double h,double Papp);
	double WetClutchFilmThickness_ReynoldsParameter(double Papp,double tmu);

	double FunIntegeritemIT();
	double FunSSAC(double h);
	double FunAsperityTorqueCoe(double mu,double w_0,double Papp);
	double FunFrictionCoe(double w_rel);

	double FunmLhLPHIF3(double h_sigma);
	double FunmLhLPHIF0(double h_sigma);
	double FunPHIFS(double h_sigma);
	double FunaCAn(double h_sigma);
	double FunREPH();
	double FunSSAn(double h,double w_rel,double w_0);

	double TestPieceArea(double ri,double ro);
	double TestPiece3Area(double ri,double ro);

};
