#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <globes/globes.h>

#include "myio.h"

char MYFILE[] = "test1.dat";

int main(int argc, char *argv[])
{
    /* Initialize GLoBES */
    glbInit(argv[0]);

    glbInitExperiment(
        "NFstandard.glb",
        &glb_experiment_list[0],
        &glb_num_of_exps
    );

    /* Oscillation parameters */
   double dm21 = 7.55e-5;
	double dm31 = 2.50e-3;
	double theta12 = asin(sqrt(0.320));
	double theta23 = asin(sqrt(0.547));
	double theta13 = asin(sqrt(0.02160));
	double deltacp = -0.68 * M_PI;

    /* TRUE parameters */
    glb_params true_values = glbAllocParams();

    glbDefineParams(
        true_values,
        theta12,
        theta13,
        theta23,
        deltacp,
        dm21,
        dm31
    );

    glbSetDensityParams(
        true_values,
        1.0,
        GLB_ALL
    );

    /* TEST parameters */
    glb_params test_values = glbAllocParams();

    glbDefineParams(
        test_values,
        theta12,
        theta13,
        theta23,
        deltacp,
        sdm,
        ldm
    );

    glbSetDensityParams(
        test_values,
        1.0,
        GLB_ALL
    );

    /* Generate simulated data at true values */
    glbSetOscillationParameters(true_values);

    glbSetRates();

    InitOutput(
        MYFILE,
        "Format: th13 deltacp chi^2\n"
    );

    double x;
    double y;
    double chi;

    int i;
    int j;

    /* Scan theta13 and delta_CP */
    for (i = 1; i < 101; i++)
    {
        for (j = 1; j < 101; j++)
        {
            x = 0.122
                + i * (0.175 - 0.122) / 100.0;

            y = 0.0
                + j * (2.0 * M_PI) / 100.0;

            glbSetOscParams(
                test_values,
                x,
                GLB_THETA_13
            );

            glbSetOscParams(
                test_values,
                y,
                GLB_DELTA_CP
            );

            chi = glbChiSys(
                test_values,
                GLB_ALL,
                GLB_ALL
            );

            AddToOutput(
                x,
                y,
                chi
            );
        }
    }

    glbFreeParams(true_values);
    glbFreeParams(test_values);

    return 0;
}