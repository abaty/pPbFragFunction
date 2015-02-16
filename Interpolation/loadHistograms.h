#include "TFile.h"
#include "TH2D.h"
#include "TH1D.h"

TH1D * pp2_0_jet;
TH2D * pp2_0_track;
TH2D * pp2_0_trackUE;
TH2D * pp2_0_track_xi;
TH2D * pp2_0_trackUE_xi;

TH1D * pp7_0_jet;
TH2D * pp7_0_track;
TH2D * pp7_0_trackUE;
TH2D * pp7_0_track_xi;
TH2D * pp7_0_trackUE_xi;

TH1D * pPb5_0_jet;
TH2D * pPb5_0_track;
TH2D * pPb5_0_trackUE;
TH2D * pPb5_0_track_xi;
TH2D * pPb5_0_trackUE_xi;

TH1D *root_histogram_gluon_2tev;
TH1D *root_histogram_gluon_5tev;
TH1D *root_histogram_gluon_7tev;

void loadHistos()
{
  TFile * spectraFile = new TFile("spectra.root","read");

  pp2_0_jet = (TH1D*) spectraFile->Get("pp2_0_jet");
  pp2_0_track = (TH2D*) spectraFile->Get("pp2_0_track");
  pp2_0_trackUE = (TH2D*) spectraFile->Get("pp2_0_trackUE");
  pp2_0_track_xi = (TH2D*) spectraFile->Get("pp2_0_track_xi");
  pp2_0_trackUE_xi = (TH2D*) spectraFile->Get("pp2_0_trackUE_xi");

  pp7_0_jet = (TH1D*) spectraFile->Get("pp7_0_jet");
  pp7_0_track = (TH2D*) spectraFile->Get("pp7_0_track");
  pp7_0_trackUE = (TH2D*) spectraFile->Get("pp7_0_trackUE");
  pp7_0_track_xi = (TH2D*) spectraFile->Get("pp7_0_track_xi");
  pp7_0_trackUE_xi = (TH2D*) spectraFile->Get("pp7_0_trackUE_xi");

  pPb5_0_jet = (TH1D*) spectraFile->Get("pPb5_0_jet");
  pPb5_0_track = (TH2D*) spectraFile->Get("pPb5_0_track");
  pPb5_0_trackUE = (TH2D*) spectraFile->Get("pPb5_0_trackUE");
  pPb5_0_track_xi = (TH2D*) spectraFile->Get("pPb5_0_track_xi");
  pPb5_0_trackUE_xi = (TH2D*) spectraFile->Get("pPb5_0_trackUE_xi");

  TFile * gluonFracFile = new TFile("gluonFracs.root","read");
  root_histogram_gluon_2tev = (TH1D*) gluonFracFile->Get("gFrac2tev");
  root_histogram_gluon_5tev = (TH1D*) gluonFracFile->Get("gFrac5tev");
  root_histogram_gluon_7tev = (TH1D*) gluonFracFile->Get("gFrac7tev");
}
