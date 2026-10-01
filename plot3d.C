void plot3d(const char *filename = "scanth13dcp.dat")
{
    TGraph2D *g = new TGraph2D(filename);
    g->SetTitle("#chi^{2} scan;x;y;#chi^{2}");
    TCanvas *c = new TCanvas("c", "3D plot", 1000, 800);
    g->Draw("SURF1");
    c->Update();
    c->SaveAs("scan.png");
}
