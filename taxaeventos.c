#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>

#include <globes/globes.h>

using namespace std;

string OUTFILE1 = "test2.dat";

FILE *out1 = NULL;

char AEDLFILE[] = "DUNE_GLoBES.glb";

int main(int argc, char *argv[])
{
    /* Initialize */
    glbInit(argv[0]);

    glbInitExperiment(
        AEDLFILE,
        &glb_experiment_list[0],
        &glb_num_of_exps
    );

    /* Output file */
    out1 = fopen(
        OUTFILE1.c_str(),
        "w"
    );

    if (out1 == NULL)
    {
        printf("Error opening output file.\n");
        return -1;
    }

    /* Oscillation parameters */
    double theta12 = asin(sqrt(0.8)) / 2.0;
    double theta13 = asin(sqrt(0.001)) / 2.0;
    double theta23 = M_PI / 4.0;
    double deltacp = M_PI / 2.0;

    double sdm = 7e-5;
    double ldm = 2e-3;

    /* True values */
    glb_params true_values =
        glbAllocParams();

    glbDefineParams(
        true_values,
        theta12,
        theta13,
        theta23,
        deltacp,
        sdm,
        ldm
    );

    glbSetDensityParams(
        true_values,
        1.0,
        GLB_ALL
    );

    glbSetOscillationParameters(
        true_values
    );

    glbSetRates();

    /* Find AEDL rule by name */
    int ruleosc =
        glbNameToValue(
            0,
            "rule",
            "#Nu_Mu_Appearance"
        );

    /* Print binned event rates */
    glbShowRuleRates(
        out1,
        0,
        ruleosc,
        GLB_ALL,
        GLB_W_EFF,
        GLB_W_BG,
        GLB_W_COEFF,
        GLB_SIG
    );

    fclose(out1);

    glbFreeParams(true_values);

    return 0;
}