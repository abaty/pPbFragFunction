#include "TFile.h"
#include "TH2D.h"
#include "TH1D.h"

// jet pt boundaries
const int FF_Bins = 5;
double FF_Bound[FF_Bins+1] = {60,80,100,120,140,200};

//plotting histos
TH1D * pp2TeV_data[FF_Bins];
TH1D * pp7TeV_data[FF_Bins];
TH1D * pPb5TeV_data[FF_Bins];
TH1D * Pbp5TeV_data[FF_Bins];

TH1D * pp2TeV_recoMC[FF_Bins];
TH1D * pp7TeV_recoMC[FF_Bins];
TH1D * pPb5TeV_recoMC[FF_Bins];
TH1D * pp5TeV_recoMC[FF_Bins];
TH1D * pp2TeV_recoMC_Q[FF_Bins];
TH1D * pp7TeV_recoMC_Q[FF_Bins];
TH1D * pPb5TeV_recoMC_Q[FF_Bins];
TH1D * pp5TeV_recoMC_Q[FF_Bins];
TH1D * pp2TeV_recoMC_G[FF_Bins];
TH1D * pp7TeV_recoMC_G[FF_Bins];
TH1D * pPb5TeV_recoMC_G[FF_Bins];
TH1D * pp5TeV_recoMC_G[FF_Bins];

TH1D * pp2TeV_genMC[FF_Bins];
TH1D * pp7TeV_genMC[FF_Bins];
TH1D * pPb5TeV_genMC[FF_Bins];
TH1D * pp5TeV_genMC[FF_Bins];

TH1D * pp5TeV_interp[FF_Bins];
TH1D * pp5TeV_interp_swap[FF_Bins];
TH1D * pp5TeV_interp_recoMC[FF_Bins];
TH1D * pp5TeV_interp_genMC[FF_Bins];
TH1D * pp5TeV_Q_interp[FF_Bins];
TH1D * pp5TeV_G_interp[FF_Bins];
TH1D * pp5TeV_Q_interp_swap[FF_Bins];
TH1D * pp5TeV_G_interp_swap[FF_Bins];
TH1D * pp5TeV_Q_interp_recoMC[FF_Bins];
TH1D * pp5TeV_G_interp_recoMC[FF_Bins];
TH1D * pp5TeV_Q_interp_genMC[FF_Bins];
TH1D * pp5TeV_G_interp_genMC[FF_Bins];

TH1D * pPb_FF[FF_Bins];
TH1D * Pbp_FF[FF_Bins];
TH1D * pPb_FF_recoMC[FF_Bins];
TH1D * pPb_FF_genMC[FF_Bins];

//input histos
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

TH1D * pp2_1_jet_reco_Q;
TH2D * pp2_1_track_reco_Q;
TH2D * pp2_1_trackUE_reco_Q;
TH2D * pp2_1_track_xi_reco_Q;
TH2D * pp2_1_trackUE_xi_reco_Q;

TH1D * pp2_1_jet_reco_G;
TH2D * pp2_1_track_reco_G;
TH2D * pp2_1_trackUE_reco_G;
TH2D * pp2_1_track_xi_reco_G;
TH2D * pp2_1_trackUE_xi_reco_G;

TH1D * pp7_1_jet_reco;
TH2D * pp7_1_track_reco;
TH2D * pp7_1_trackUE_reco;
TH2D * pp7_1_track_xi_reco;
TH2D * pp7_1_trackUE_xi_reco;

TH1D * pp7_1_jet_reco_Q;
TH2D * pp7_1_track_reco_Q;
TH2D * pp7_1_trackUE_reco_Q;
TH2D * pp7_1_track_xi_reco_Q;
TH2D * pp7_1_trackUE_xi_reco_Q;

TH1D * pp7_1_jet_reco_G;
TH2D * pp7_1_track_reco_G;
TH2D * pp7_1_trackUE_reco_G;
TH2D * pp7_1_track_xi_reco_G;
TH2D * pp7_1_trackUE_xi_reco_G;

TH1D * pPb5_1_jet_reco;
TH2D * pPb5_1_track_reco;
TH2D * pPb5_1_trackUE_reco;
TH2D * pPb5_1_track_xi_reco;
TH2D * pPb5_1_trackUE_xi_reco;

TH1D * pPb5_1_jet_reco_Q;
TH2D * pPb5_1_track_reco_Q;
TH2D * pPb5_1_trackUE_reco_Q;
TH2D * pPb5_1_track_xi_reco_Q;
TH2D * pPb5_1_trackUE_xi_reco_Q;

TH1D * pPb5_1_jet_reco_G;
TH2D * pPb5_1_track_reco_G;
TH2D * pPb5_1_trackUE_reco_G;
TH2D * pPb5_1_track_xi_reco_G;
TH2D * pPb5_1_trackUE_xi_reco_G;

TH1D * pp2_1_jet_gen;
TH2D * pp2_1_track_gen;
TH2D * pp2_1_trackUE_gen;
TH2D * pp2_1_track_xi_gen;
TH2D * pp2_1_trackUE_xi_gen;

TH1D * pp7_1_jet_gen;
TH2D * pp7_1_track_gen;
TH2D * pp7_1_trackUE_gen;
TH2D * pp7_1_track_xi_gen;
TH2D * pp7_1_trackUE_xi_gen;

TH1D * pPb5_1_jet_gen;
TH2D * pPb5_1_track_gen;
TH2D * pPb5_1_trackUE_gen;
TH2D * pPb5_1_track_xi_gen;
TH2D * pPb5_1_trackUE_xi_gen;

TH1D * pp5_1_jet_reco;
TH2D * pp5_1_track_reco;
TH2D * pp5_1_trackUE_reco;
TH2D * pp5_1_track_xi_reco;
TH2D * pp5_1_trackUE_xi_reco;

TH1D * pp5_1_jet_reco_Q;
TH2D * pp5_1_track_reco_Q;
TH2D * pp5_1_trackUE_reco_Q;
TH2D * pp5_1_track_xi_reco_Q;
TH2D * pp5_1_trackUE_xi_reco_Q;

TH1D * pp5_1_jet_reco_G;
TH2D * pp5_1_track_reco_G;
TH2D * pp5_1_trackUE_reco_G;
TH2D * pp5_1_track_xi_reco_G;
TH2D * pp5_1_trackUE_xi_reco_G;

TH1D * pp5_1_jet_gen;
TH2D * pp5_1_track_gen;
TH2D * pp5_1_trackUE_gen;
TH2D * pp5_1_track_xi_gen;
TH2D * pp5_1_trackUE_xi_gen;

TH1D *gluon_2tev_reco;
TH1D *gluon_5tev_reco;
TH1D *gluon_7tev_reco;
TH1D *gluon_2tev_gen;
TH1D *gluon_5tev_gen;
TH1D *gluon_7tev_gen;

void loadHistos()
{
  TFile * spectraFilepp2 = new TFile("tempRootFiles/processed_2015_03_12__20_27_41/pp2_3_0_15.root","read");
  TFile * spectraFilepPb5 = new TFile("tempRootFiles/processed_2015_03_12__20_27_41/pPb5_3_0_15.root","read");
  TFile * spectraFilePbp5 = new TFile("tempRootFiles/processed_2015_03_12__20_27_41/Pbp5_3_0_15.root","read");
  TFile * spectraFilepp7 = new TFile("tempRootFiles/processed_2015_03_12__20_27_41/pp7_3_0_15.root","read");
  TFile * MCFilepp2 = new TFile("tempRootFiles/processed_2015_03_12__20_27_41/pp2MC_3_0_15.root","read");
  TFile * MCFilepPb5 = new TFile("tempRootFiles/processed_2015_03_12__20_27_41/pPb5MC_3_0_15.root","read");
  TFile * MCFilepp7 = new TFile("tempRootFiles/processed_2015_03_12__20_27_41/pp7MC_3_0_15.root","read");
  TFile * MCFilepp5 = new TFile("tempRootFiles/processed_2015_03_12__20_27_41/pp5MC_3_0_15.root","read");

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

  pp2_1_jet_reco_Q = (TH1D*) MCFilepp2->Get("pp2_reco_jet_Q");
  pp2_1_track_reco_Q = (TH2D*) MCFilepp2->Get("pp2_reco_track_Q");
  pp2_1_trackUE_reco_Q = (TH2D*) MCFilepp2->Get("pp2_reco_trackUE_Q");
  pp2_1_track_xi_reco_Q = (TH2D*) MCFilepp2->Get("pp2_reco_track_xi_Q");
  pp2_1_trackUE_xi_reco_Q = (TH2D*) MCFilepp2->Get("pp2_reco_trackUE_xi_Q");

  pp2_1_jet_reco_G = (TH1D*) MCFilepp2->Get("pp2_reco_jet_G");
  pp2_1_track_reco_G = (TH2D*) MCFilepp2->Get("pp2_reco_track_G");
  pp2_1_trackUE_reco_G = (TH2D*) MCFilepp2->Get("pp2_reco_trackUE_G");
  pp2_1_track_xi_reco_G = (TH2D*) MCFilepp2->Get("pp2_reco_track_xi_G");
  pp2_1_trackUE_xi_reco_G = (TH2D*) MCFilepp2->Get("pp2_reco_trackUE_xi_G");

  pp7_1_jet_reco = (TH1D*) MCFilepp7->Get("pp7_reco_jet");
  pp7_1_track_reco = (TH2D*) MCFilepp7->Get("pp7_reco_track");
  pp7_1_trackUE_reco = (TH2D*) MCFilepp7->Get("pp7_reco_trackUE");
  pp7_1_track_xi_reco = (TH2D*) MCFilepp7->Get("pp7_reco_track_xi");
  pp7_1_trackUE_xi_reco = (TH2D*) MCFilepp7->Get("pp7_reco_trackUE_xi");

  pp7_1_jet_reco_Q = (TH1D*) MCFilepp7->Get("pp7_reco_jet_Q");
  pp7_1_track_reco_Q = (TH2D*) MCFilepp7->Get("pp7_reco_track_Q");
  pp7_1_trackUE_reco_Q = (TH2D*) MCFilepp7->Get("pp7_reco_trackUE_Q");
  pp7_1_track_xi_reco_Q = (TH2D*) MCFilepp7->Get("pp7_reco_track_xi_Q");
  pp7_1_trackUE_xi_reco_Q = (TH2D*) MCFilepp7->Get("pp7_reco_trackUE_xi_Q");

  pp7_1_jet_reco_G = (TH1D*) MCFilepp7->Get("pp7_reco_jet_G");
  pp7_1_track_reco_G = (TH2D*) MCFilepp7->Get("pp7_reco_track_G");
  pp7_1_trackUE_reco_G = (TH2D*) MCFilepp7->Get("pp7_reco_trackUE_G");
  pp7_1_track_xi_reco_G = (TH2D*) MCFilepp7->Get("pp7_reco_track_xi_G");
  pp7_1_trackUE_xi_reco_G = (TH2D*) MCFilepp7->Get("pp7_reco_trackUE_xi_G");

  pPb5_1_jet_reco = (TH1D*) MCFilepPb5->Get("pPb5_reco_jet");
  pPb5_1_track_reco = (TH2D*) MCFilepPb5->Get("pPb5_reco_track");
  pPb5_1_trackUE_reco = (TH2D*) MCFilepPb5->Get("pPb5_reco_trackUE");
  pPb5_1_track_xi_reco = (TH2D*) MCFilepPb5->Get("pPb5_reco_track_xi");
  pPb5_1_trackUE_xi_reco = (TH2D*)MCFilepPb5->Get("pPb5_reco_trackUE_xi");

  pPb5_1_jet_reco_Q = (TH1D*) MCFilepPb5->Get("pPb5_reco_jet_Q");
  pPb5_1_track_reco_Q = (TH2D*) MCFilepPb5->Get("pPb5_reco_track_Q");
  pPb5_1_trackUE_reco_Q = (TH2D*) MCFilepPb5->Get("pPb5_reco_trackUE_Q");
  pPb5_1_track_xi_reco_Q = (TH2D*) MCFilepPb5->Get("pPb5_reco_track_xi_Q");
  pPb5_1_trackUE_xi_reco_Q = (TH2D*)MCFilepPb5->Get("pPb5_reco_trackUE_xi_Q");

  pPb5_1_jet_reco_G = (TH1D*) MCFilepPb5->Get("pPb5_reco_jet_G");
  pPb5_1_track_reco_G = (TH2D*) MCFilepPb5->Get("pPb5_reco_track_G");
  pPb5_1_trackUE_reco_G = (TH2D*) MCFilepPb5->Get("pPb5_reco_trackUE_G");
  pPb5_1_track_xi_reco_G = (TH2D*) MCFilepPb5->Get("pPb5_reco_track_xi_G");
  pPb5_1_trackUE_xi_reco_G = (TH2D*)MCFilepPb5->Get("pPb5_reco_trackUE_xi_G");

  pp5_1_jet_reco = (TH1D*) MCFilepp5->Get("pp5_reco_jet");
  pp5_1_track_reco = (TH2D*) MCFilepp5->Get("pp5_reco_track");
  pp5_1_trackUE_reco = (TH2D*) MCFilepp5->Get("pp5_reco_trackUE");
  pp5_1_track_xi_reco = (TH2D*) MCFilepp5->Get("pp5_reco_track_xi");
  pp5_1_trackUE_xi_reco = (TH2D*) MCFilepp5->Get("pp5_reco_trackUE_xi");

  pp5_1_jet_reco_Q = (TH1D*) MCFilepp5->Get("pp5_reco_jet_Q");
  pp5_1_track_reco_Q = (TH2D*) MCFilepp5->Get("pp5_reco_track_Q");
  pp5_1_trackUE_reco_Q = (TH2D*) MCFilepp5->Get("pp5_reco_trackUE_Q");
  pp5_1_track_xi_reco_Q = (TH2D*) MCFilepp5->Get("pp5_reco_track_xi_Q");
  pp5_1_trackUE_xi_reco_Q = (TH2D*) MCFilepp5->Get("pp5_reco_trackUE_xi_Q");

  pp5_1_jet_reco_G = (TH1D*) MCFilepp5->Get("pp5_reco_jet_G");
  pp5_1_track_reco_G = (TH2D*) MCFilepp5->Get("pp5_reco_track_G");
  pp5_1_trackUE_reco_G = (TH2D*) MCFilepp5->Get("pp5_reco_trackUE_G");
  pp5_1_track_xi_reco_G = (TH2D*) MCFilepp5->Get("pp5_reco_track_xi_G");
  pp5_1_trackUE_xi_reco_G = (TH2D*) MCFilepp5->Get("pp5_reco_trackUE_xi_G");

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

  pp5_1_jet_gen = (TH1D*) MCFilepp5->Get("pp5_gen_jet");
  pp5_1_track_gen = (TH2D*) MCFilepp5->Get("pp5_gen_track");
  pp5_1_trackUE_gen = (TH2D*) MCFilepp5->Get("pp5_gen_trackUE");
  pp5_1_track_xi_gen = (TH2D*) MCFilepp5->Get("pp5_gen_track_xi");
  pp5_1_trackUE_xi_gen = (TH2D*) MCFilepp5->Get("pp5_gen_trackUE_xi");

  TFile * gluonFracFile = new TFile("gluonFracs.root","read");
  gluon_2tev_reco = (TH1D*) gluonFracFile->Get("pp2_gFrac_recoMC");
  gluon_5tev_reco = (TH1D*) gluonFracFile->Get("pPb5_gFrac_recoMC");
  gluon_7tev_reco = (TH1D*) gluonFracFile->Get("pp7_gFrac_recoMC");
  gluon_2tev_gen = (TH1D*) gluonFracFile->Get("pp2_gFrac_genMC");
  gluon_5tev_gen = (TH1D*) gluonFracFile->Get("pPb5_gFrac_genMC");
  gluon_7tev_gen = (TH1D*) gluonFracFile->Get("pp7_gFrac_genMC");
}
