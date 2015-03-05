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

TH1D * Pbp5_0_jet;
TH2D * Pbp5_0_track;
TH2D * Pbp5_0_trackUE;
TH2D * Pbp5_0_track_xi;
TH2D * Pbp5_0_trackUE_xi;

TH1D *root_histogram_gluon_2tev;
TH1D *root_histogram_gluon_5tev;
TH1D *root_histogram_gluon_7tev;

void loadHistos()
{
  TFile * spectraFilepp2 = new TFile("tempRootFiles/03_02_2015_MC_processing/spectra_pp2MC_3_0_15.root","read");
  TFile * spectraFilepPb5 = new TFile("tempRootFiles/03_02_2015_MC_processing/spectra_pPb5MC_3_0_15.root","read");
  //remember to change this back to Pbp5
  TFile * spectraFilePbp5 = new TFile("tempRootFiles/03_02_2015_MC_processing/spectra_pPb5MC_3_0_15.root","read");
  TFile * spectraFilepp7 = new TFile("spectrapp7_0_0_0_15.root","read");

  pp2_0_jet = (TH1D*) spectraFilepp2->Get("pp2_1_jet");
  pp2_0_track = (TH2D*) spectraFilepp2->Get("pp2_1_track");
  pp2_0_trackUE = (TH2D*) spectraFilepp2->Get("pp2_1_trackUE");
  pp2_0_track_xi = (TH2D*) spectraFilepp2->Get("pp2_1_track_xi");
  pp2_0_trackUE_xi = (TH2D*) spectraFilepp2->Get("pp2_1_trackUE_xi");

  pp7_0_jet = (TH1D*) spectraFilepp7->Get("pp7_0_jet");
  pp7_0_track = (TH2D*) spectraFilepp7->Get("pp7_0_track");
  pp7_0_trackUE = (TH2D*) spectraFilepp7->Get("pp7_0_trackUE");
  pp7_0_track_xi = (TH2D*) spectraFilepp7->Get("pp7_0_track_xi");
  pp7_0_trackUE_xi = (TH2D*) spectraFilepp7->Get("pp7_0_trackUE_xi");

  pPb5_0_jet = (TH1D*) spectraFilepPb5->Get("pPb5_1_jet");
  pPb5_0_track = (TH2D*) spectraFilepPb5->Get("pPb5_1_track");
  pPb5_0_trackUE = (TH2D*) spectraFilepPb5->Get("pPb5_1_trackUE");
  pPb5_0_track_xi = (TH2D*) spectraFilepPb5->Get("pPb5_1_track_xi");
  pPb5_0_trackUE_xi = (TH2D*) spectraFilepPb5->Get("pPb5_1_trackUE_xi");

//remember to change this back to Pbp5
  Pbp5_0_jet = (TH1D*) spectraFilePbp5->Get("pPb5_1_jet");
  Pbp5_0_track = (TH2D*) spectraFilePbp5->Get("pPb5_1_track");
  Pbp5_0_trackUE = (TH2D*) spectraFilePbp5->Get("pPb5_1_trackUE");
  Pbp5_0_track_xi = (TH2D*) spectraFilePbp5->Get("pPb5_1_track_xi");
  Pbp5_0_trackUE_xi = (TH2D*) spectraFilePbp5->Get("pPb5_1_trackUE_xi");

  TFile * gluonFracFile = new TFile("gluonFracs.root","read");
  root_histogram_gluon_2tev = (TH1D*) gluonFracFile->Get("gFrac2tev");
  root_histogram_gluon_5tev = (TH1D*) gluonFracFile->Get("gFrac5tev");
  root_histogram_gluon_7tev = (TH1D*) gluonFracFile->Get("gFrac7tev");
}
