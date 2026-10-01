#include "TH1.h"
#include "TH2.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TStyle.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

#include "TROOT.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TH2S.h"
#include "TLegend.h"
#include "TLine.h"

void make_plot(){

    gROOT->SetBatch(true);

    TCanvas *canvas = new TCanvas("canvas", "Probability", 800, 600);

    auto grnp  = new TGraph("probability_vac_mu_e.dat");

    grnp->GetXaxis()->SetRangeUser(0,2.0);
    grnp->GetYaxis()->SetRangeUser(0,10);

    grnp->SetTitle("#Delta#chi^{2} for Statistics only and systematics;|a_{#mu e}| (10^{-23}GeV);#Delta#chi^{2}");
    grnp->GetXaxis()->CenterTitle();
    grnp->GetYaxis()->CenterTitle();
    grnp->GetYaxis()->SetNdivisions(505);

    grnp->SetLineColor(kBlue);

    // Engrossar as linhas
    grnp->SetLineWidth(3);

    grnp->Draw("AL");
    //grant->Draw("L SAME");

    // Linha horizontal pontilhada em y=3.84
    TLine *line = new TLine(0, 3.84, 2.0, 3.84);
    line->SetLineStyle(2); // pontilhada
    line->SetLineWidth(2);
    line->SetLineColor(kBlack);
    line->Draw();

    auto legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(grnp,"Projection","l");
    legend->Draw();

    canvas->SaveAs("probability_vac_mu_e.png");
}