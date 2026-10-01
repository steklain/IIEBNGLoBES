#ifndef MYIO_H
#define MYIO_H

#include <stdio.h>
#include <stdlib.h>
#include <globes/globes.h>

/*
 * Salva as taxas do DUNE em três colunas:
 *
 *   E [GeV]    FHC    RHC
 *
 * exp_fhc : índice do experimento FHC
 * exp_rhc : índice do experimento RHC
 * rule    : rule a ser mostrada
 */

void save_dune_rates(const char *filename,
                     int exp_fhc,
                     int exp_rhc,
                     int rule)
{
    FILE *fp;
    int i;
    int n_bins_fhc, n_bins_rhc;
    double emin, emax;
    double *fhc;
    double *rhc;

    fp = fopen(filename, "w");

    if (fp == NULL)
    {
        fprintf(stderr,
                "Error: cannot open %s\n",
                filename);
        exit(EXIT_FAILURE);
    }

    /* Número de bins */
    n_bins_fhc = glbGetNumberOfBins(exp_fhc);
    n_bins_rhc = glbGetNumberOfBins(exp_rhc);

    if (n_bins_fhc != n_bins_rhc)
    {
        fprintf(stderr,
                "Error: FHC and RHC have different numbers of bins\n");

        fclose(fp);
        exit(EXIT_FAILURE);
    }

    /* Intervalo de energia */
    glbGetEminEmax(exp_fhc, &emin, &emax);

    /* Event rates */
    fhc = glbGetRuleRatePtr(exp_fhc, rule);
    rhc = glbGetRuleRatePtr(exp_rhc, rule);

    fprintf(fp, "# E_GeV   FHC   RHC\n");

    for (i = 0; i < n_bins_fhc; i++)
    {
        double E;

        E = emin +
            (i + 0.5) *
            (emax - emin) /
            n_bins_fhc;

        fprintf(fp,
                "%.6f  %.8e  %.8e\n",
                E,
                fhc[i],
                rhc[i]);
    }

    fclose(fp);
}

#endif