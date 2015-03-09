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

TH1D * pp2_1_jet_reco;
TH2D * pp2_1_track_reco;
TH2D * pp2_1_trackUE_reco;
TH2D * pp2_1_track_xi_reco;
TH2D * pp2_1_trackUE_xi_reco;

TH1D * pp7_1_jet_reco;
TH2D * pp7_1_track_reco;
TH2D * pp7_1_trackUE_reco;
TH2D * pp7_1_track_xi_reco;
TH2D * pp7_1_trackUE_xi_reco;

TH1D * pPb5_1_jet_reco;
TH2D * pPb5_1_track_reco;
TH2D * pPb5_1_trackUE_reco;
TH2D * pPb5_1_track_xi_reco;
TH2D * pPb5_1_trackUE_xi_reco;

TH1D * pp2_1_jet_reco;
TH2D * pp2_1_track_reco;
TH2D * pp2_1_trackUE_reco;
TH2D * pp2_1_track_xi_reco;
TH2D * pp2_1_trackUE_xi_reco;

TH1D * pp7_1_jet_reco;
TH2D * pp7_1_track_reco;
TH2D * pp7_1_trackUE_reco;
TH2D * pp7_1_track_xi_reco;
TH2D * pp7_1_trackUE_xi_reco;

TH1D * pPb5_1_jet_reco;
TH2D * pPb5_1_track_reco;
TH2D * pPb5_1_trackUE_reco;
TH2D * pPb5_1_track_xi_reco;
TH2D * pPb5_1_trackUE_xi_reco;

TH1D *root_histogram_gluon_2tev;
TH1D *root_histogram_gluon_5tev;
TH1D *root_histogram_gluon_7tev;

void loadHistos()
{
  TFile * spectraFilepp2 = new TFile("tempRootFiles/processed_2015_03_09__05_54_36/pp2_3_0_15.root","read");
  TFile * spectraFilepPb5 = new TFile("tempRootFiles/processed_2015_03_09__05_54_36/pPb5_3_0_15.root","read");
  TFile * spectraFilePbp5 = new TFile("tempRootFiles/processed_2015_03_09__05_54_36/Pbp5_3_0_15.root","read");
  TFile * spectraFilepp7 = new TFile("tempRootFiles/processed_2015_03_09__05_54_36/pp7_3_0_15.root","read");
  TFile * MCFilepp2 = new TFile("tempRootFiles/processed_2015_03_09__05_54_36/pp2MC_3_0_15.root","read");
  TFile * MCFilepPb5 = new TFile("tempRootFiles/processed_2015_03_09__05_54_36/pPb5_3_0_15.root","read");
  TFile * MCFilepp7 = new TFile("tempRootFiles/processed_2015_03_09__05_54_36/pp7MC_3_0_15.root","read");

  pp2_0_jet = (TH1D*) spectraFilepp2->Get("pp2_reco_jet");
  pp2_0_track = (TH2D*) spectraFilepp2->Get("pp2_reco_track");
  pp2_0_trackUE = (TH2D*) spectraFilepp2->Get("pp2_reco_trackUE");
  pp2_0_track_xi = (TH2D*) spectraFilepp2->Get("pp2_reco_track_xi");
  pp2_0_trackUE_xi = (TH2D*) spectraFilepp2->Get("pp2_reco_trackUE_xi");

  pp7_0_jet = (TH1D*) spectraFilepp7->Get("pp7_reco_jet");
  pp7_0_track = (TH2D*) spectraFilepp7->Get("pp7_reco_track");
  pp7_0_trackUE = (TH2D*) spectraFilepp7->Get("pp7_reco_trackUE");
  pp7_0_track_xi = (TH2D*) spectraFilepp7->Get("pp7_reco_track_xi");
  pp7_0_trackUE_xi = (TH2D*) spectraFilepp7->Get("pp7_reco_trackUE_xi");

  pPb5_0_jet = (TH1D*) spectraFilepPb5->Get("pPb5_reco_jet");
  pPb5_0_track = (TH2D*) spectraFilepPb5->Get("pPb5_reco_track");
  pPb5_0_trackUE = (TH2D*) spectraFilepPb5->Get("pPb5_reco_trackUE");
  pPb5_0_track_xi = (TH2D*) spectraFilepPb5->Get("pPb5_reco_track_xi");
  pPb5_0_trackUE_xi = (TH2D*) spectraFilepPb5->Get("pPb5_reco_trackUE_xi");

  Pbp5_0_jet = (TH1D*) spectraFilePbp5->Get("Pbp5_reco_jet");
  Pbp5_0_track = (TH2D*) spectraFilePbp5->Get("Pbp5_reco_track");
  Pbp5_0_trackUE = (TH2D*) spectraFilePbp5->Get("Pbp5_reco_trackUE");
  Pbp5_0_track_xi = (TH2D*) spectraFilePbp5->Get("Pbp5_reco_track_xi");
  Pbp5_0_trackUE_xi = (TH2D*) spectraFilePbp5->Get("Pbp5_reco_trackUE_xi");

  pp2_1_jet_reco = (TH1D*) MCFilepp2->Get("pp2_reco_jet");
  pp2_1_track_reco = (TH2D*) MCFilepp2->Get("pp2_reco_track");
  pp2_1_trackUE_reco = (TH2D*) MCFilepp2->Get("pp2_reco_trackUE");
  pp2_1_track_xi_reco = (TH2D*) MCFilepp2->Get("pp2_reco_track_xi");
  pp2_1_trackUE_xi_reco = (TH2D*) MCFilepp2->Get("pp2_reco_trackUE_xi");

  pp7_1_jet_reco = (TH1D*) MCFilepp7->Get("pp7_reco_jet");
  pp7_1_track_reco = (TH2D*) MCFilepp7->Get("pp7_reco_track");
  pp7_1_trackUE_reco = (TH2D*) MCFilepp7->Get("pp7_reco_trackUE");
  pp7_1_track_xi_reco = (TH2D*) MCFilepp7->Get("pp7_reco_track_xi");
  pp7_1_trackUE_xi_reco = (TH2D*) MCFilepp7->Get("pp7_reco_trackUE_xi");

  pPb5_1_jet_reco = (TH1D*) MCFilepPb5->Get("pPb5_reco_jet");
  pPb5_1_track_reco = (TH2D*) MCFilepPb5->Get("pPb5_reco_track");
  pPb5_1_trackUE_reco = (TH2D*) MCFilepPb5->Get("pPb5_reco_trackUE");
  pPb5_1_track_xi_reco = (TH2D*) MCFilepPb5->Get("pPb5_reco_track_xi");
  pPb5_1_trackUE_xi_reco = (TH2D*)MCFilepPb5->Get("pPb5_reco_trackUE_xi");

  pp2_1_jet_gen = (TH1D*) MCFilepp2->Get("pp2_gen_jet");
  pp2_1_track_gen = (TH2D*) MCFilepp2->Get("pp2_gen_track");
  pp2_1_trackUE_gen = (TH2D*) MCFilepp2->Get("pp2_gen_trackUE");
  pp2_1_track_xi_gen = (TH2D*) MCFilepp2->Get("pp2_gen_track_xi");
  pp2_1_trackUE_xi_gen = (TH2D*) MCFilepp2->Get("pp2_gen_trackUE_xi");

  pp7_1_jet_gen = (TH1D*) MCFilepp7->Get("pp7_gen_jet");
  pp7_1_track_gen = (TH2D*) MCFilepp7->Get("pp7_gen_track");
  pp7_1_trackUE_gen = (TH2D*) MCFilepp7->Get("pp7_gen_trackUE");
  pp7_1_track_xi_gen = (TH2D*) MCFilepp7->Get("pp7_gen_track_xi");
  pp7_1_trackUE_xi_gen = (TH2D*) MCFilepp7->Get("pp7_gen_trackUE_xi");

  pPb5_1_jet_gen = (TH1D*) MCFilepPb5->Get("pPb5_gen_jet");
  pPb5_1_track_gen = (TH2D*) MCFilepPb5->Get("pPb5_gen_track");
  pPb5_1_trackUE_gen = (TH2D*) MCFilepPb5->Get("pPb5_gen_trackUE");
  pPb5_1_track_xi_gen = (TH2D*) MCFilepPb5->Get("pPb5_gen_track_xi");
  pPb5_1_trackUE_xi_gen = (TH2D*)MCFilepPb5->Get("pPb5_gen_trackUE_xi");

  TFile * gluonFracFile = new TFile("gluonFracs.root","read");
  root_histogram_gluon_2tev = (TH1D*) gluonFracFile->Get("gFrac2tev");
  root_histogram_gluon_5tev = (TH1D*) gluonFracFile->Get("gFrac5tev");
  root_histogram_gluon_7tev = (TH1D*) gluonFracFile->Get("gFrac7tev");
}
