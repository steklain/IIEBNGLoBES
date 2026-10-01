#include <iostream>
#include <cmath>
#include <string.h>
#include<float.h>
#include<complex.h>
#include <vector>
#include<gsl/gsl_complex.h>
#include<gsl/gsl_complex_math.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_blas.h>
#include <globes/globes.h>
#include<fstream>

using namespace std;

char AEDLFILE[] = "DUNE_GLoBES.glb";

int main(int argc, char * argv[])
{

	glbInit(argv[0]);
	glbInitExperiment(AEDLFILE, &glb_experiment_list[0], &glb_num_of_exps);

	ofstream outstdmu,outstde,outstdtau;

	outstdmu.open("stdprob_mumu.dat");
	outstde.open("stdprob_mue.dat");
    outstdtau.open("stdprob_mutau.dat");
	
	double dm21 = 8.0e-5;
	double dm31 = 2.50e-3;
	double theta12 = 34*M_PI/180;
	double theta23 = 45*M_PI/180;
	double theta13 = 0;
	double deltacp = 0;

	glb_params true_values = glbAllocParams();
    glbDefineParams(true_values,theta12,theta13,theta23,deltacp,dm21,dm31);
	glbSetDensityParams(true_values, 0.0, GLB_ALL);
	glbSetOscillationParameters(true_values);
	glbSetRates();

	double energy,prob_mumu,prob_mue,prob_mutau;
	double step= 30000;
	[[maybe_unused]] double L = 1300;// km
    glbSetBaselineInExperiment(0, L);
    double emin= 0.5;//L/1e4 ; //GeV
	double emax= 10; //L/1e1 ; //GeV


	for (energy=emin;energy<=emax;energy+=(emax-emin)/step)
	{
    
    //prob_mumu=glbVacuumProbability(2,2,+1,energy,L);
	//prob_mue=glbVacuumProbability(2,1,+1,energy,L);
    //prob_mutau=glbVacuumProbability(2,3,+1,energy,L);

    prob_mumu=glbProfileProbability(0,2,2,+1,energy);
	prob_mue=glbProfileProbability(0,2,1,+1,energy);
	prob_mutau=glbProfileProbability(0,2,3,+1,energy);

	outstde<<energy<<"  "<<prob_mue<<endl; //*3e-13
	outstdmu<<energy<<"  "<<prob_mumu<<endl; //*3e-13
    outstdtau<<energy<<"  "<<prob_mutau<<endl; //*3e-13
	}


	outstdmu.close();
	outstde.close();
    outstdtau.close();
	glbFreeParams(true_values);
 	return 0;

}