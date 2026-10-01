#include <iostream>
#include <cmath>
#include <string.h>
#include <float.h>
#include <complex.h>
#include <vector>
#include<gsl/gsl_complex.h>
#include<gsl/gsl_complex_math.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_blas.h>
#include <globes/globes.h>
#include<fstream>

using namespace std;

int main(int argc, char * argv[])
{
	glbInit(argv[0]);
	ofstream pmue, pmumu, pmutau;

	pmue.open("probability_vac_mu_e.dat");
    pmumu.open("probability_vac_mu_mu.dat");
    pmutau.open("probability_vac_mu_tau.dat");
	
	double dm21 = 7.55e-5;
	double dm31 = 2.50e-3;
	double theta12 = asin(sqrt(0.320));
	double theta23 = asin(sqrt(0.547));
	double theta13 = asin(sqrt(0.02160));
	double deltacp = -0.68 * M_PI;

	glb_params true_values = glbAllocParams();
    glbDefineParams(true_values,theta12,theta13,theta23,deltacp,dm21,dm31);
	glbSetOscillationParameters(true_values);
	glbSetRates();

	double energy,probmue,probmumu,probmutau; 
	double emin= 0.25 ; //GeV
	double emax=10 ; //GeV
	double step= 3000;
	[[maybe_unused]] double L = 300;// km

	for (energy=emin;energy<=emax;energy+=(emax-emin)/step)
	{
	  probmue=glbVacuumProbability(2,1,+1,energy,L);
      probmumu=glbVacuumProbability(2,2,+1,energy,L);       
      probmutau=glbVacuumProbability(2,3,+1,energy,L); 
	  
	  pmue<<energy<<"  "<<probmue<<endl;
	  pmutau<<energy<<"  "<<probmutau<<endl;
	  pmumu<<energy<<"  "<<probmumu<<endl; 
	}

	pmue.close();
    pmumu.close();
    pmutau.close();
	glbFreeParams(true_values);
 	return 0;
}