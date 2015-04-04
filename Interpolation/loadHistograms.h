#include "TFile.h"
#include "TH2D.h"
#include "TH1D.h"

const char* filePath = "tempRootFiles/processed_2015_04_02__16_46_39/";
const int variations = 26;
const char * variationTag[variations]= {"","_pp2JESUP3","_pp2JESDOWN3","_pp7JESUP3","_pp7JESDOWN3","_pPb5JESUP3","_pPb5JESDOWN3","_pp2JER5","_pp7JER5","_pPb5JER5","_pp2JER2","_pp7JER2","_pPb5JER2","_NoTrackCorr","_pp2JESUP1","_pp2JESDOWN1","_pp7JESUP1","_pp7JESDOWN1","_pPb5JESUP1","_pPb5JESDOWN1","_pp2JESUP2","_pp2JESDOWN2","_pp7JESUP2","_pp7JESDOWN2","_pPb5JESUP2","_pPb5JESDOWN2"};

// jet pt boundaries
const int FF_Bins = 5;
double FF_Bound[FF_Bins+1] = {60,80,100,120,140,200};

//interpolation histos
TH1D ** pPb5TeV_data_interp[FF_Bins];
TH1D ** Pbp5TeV_data_interp[FF_Bins];
TH1D ** pPb5Pb5TeV_data_interp[FF_Bins];
TH1D ** pPb5Pb5TeV_data_interp_genGluFrac[FF_Bins];
TH1D ** pPb5TeV_recoMC_interp[FF_Bins];
TH1D ** pPb5TeV_genMC_interp[FF_Bins];
TH1D ** pPb5TeV_rJgTMC_interp[FF_Bins];
TH1D ** pPb5TeV_gJrTMC_interp[FF_Bins];
TH1D ** Pbp5TeV_recoMC_interp[FF_Bins];
TH1D ** Pbp5TeV_genMC_interp[FF_Bins];
TH1D ** Pbp5TeV_rJgTMC_interp[FF_Bins];
TH1D ** Pbp5TeV_gJrTMC_interp[FF_Bins];

//plotting histos
TH1D * pp2TeV_data[FF_Bins];
TH1D * pp7TeV_data[FF_Bins];
TH1D * pPb5TeV_data[FF_Bins];

TH1D * pp2TeV_reverse_data[FF_Bins];
TH1D * pp7TeV_reverse_data[FF_Bins];
TH1D * Pbp5TeV_data[FF_Bins];

TH1D * pPb5Pbp5TeV_fulldata[FF_Bins];
TH1D * pp2TeV_fulldata[FF_Bins];
TH1D * pp7TeV_fulldata[FF_Bins];

TH1D * pp2TeV_recoMC[FF_Bins];
TH1D * pp7TeV_recoMC[FF_Bins];
TH1D * pPb5TeV_recoMC[FF_Bins];
TH1D * Pbp5TeV_recoMC[FF_Bins];
TH1D * pp5TeV_recoMC[FF_Bins];
TH1D * pp2TeV_recoMC_Q[FF_Bins];
TH1D * pp7TeV_recoMC_Q[FF_Bins];
TH1D * pPb5TeV_recoMC_Q[FF_Bins];
TH1D * Pbp5TeV_recoMC_Q[FF_Bins];
TH1D * pp5TeV_recoMC_Q[FF_Bins];
TH1D * pp2TeV_recoMC_G[FF_Bins];
TH1D * pp7TeV_recoMC_G[FF_Bins];
TH1D * pPb5TeV_recoMC_G[FF_Bins];
TH1D * Pbp5TeV_recoMC_G[FF_Bins];
TH1D * pp5TeV_recoMC_G[FF_Bins];

TH1D * pp2TeV_genMC[FF_Bins];
TH1D * pp7TeV_genMC[FF_Bins];
TH1D * pPb5TeV_genMC[FF_Bins];
TH1D * Pbp5TeV_genMC[FF_Bins];
TH1D * pp5TeV_genMC[FF_Bins];
TH1D * pp2TeV_genMC_Q[FF_Bins];
TH1D * pp7TeV_genMC_Q[FF_Bins];
TH1D * pPb5TeV_genMC_Q[FF_Bins];
TH1D * Pbp5TeV_genMC_Q[FF_Bins];
TH1D * pp5TeV_genMC_Q[FF_Bins];
TH1D * pp2TeV_genMC_G[FF_Bins];
TH1D * pp7TeV_genMC_G[FF_Bins];
TH1D * pPb5TeV_genMC_G[FF_Bins];
TH1D * Pbp5TeV_genMC_G[FF_Bins];
TH1D * pp5TeV_genMC_G[FF_Bins];

TH1D * pp2TeV_rJgTMC[FF_Bins];
TH1D * pp7TeV_rJgTMC[FF_Bins];
TH1D * pPb5TeV_rJgTMC[FF_Bins];
TH1D * Pbp5TeV_rJgTMC[FF_Bins];
TH1D * pp5TeV_rJgTMC[FF_Bins];
TH1D * pp2TeV_gJrTMC[FF_Bins];
TH1D * pp7TeV_gJrTMC[FF_Bins];
TH1D * pPb5TeV_gJrTMC[FF_Bins];
TH1D * Pbp5TeV_gJrTMC[FF_Bins];
TH1D * pp5TeV_gJrTMC[FF_Bins];

TH1D * pPb_FF[FF_Bins];
TH1D * Pbp_FF[FF_Bins];
TH1D * pPb_FF_recoMC[FF_Bins];
TH1D * pPb_FF_genMC[FF_Bins];
TH1D * pPb_FF_rJgTMC[FF_Bins];
TH1D * pPb_FF_gJrTMC[FF_Bins];
TH1D * Pbp_FF_recoMC[FF_Bins];
TH1D * Pbp_FF_genMC[FF_Bins];
TH1D * Pbp_FF_rJgTMC[FF_Bins];
TH1D * Pbp_FF_gJrTMC[FF_Bins];
TH1D * pPbPbp_FF[FF_Bins];
TH1D * pPbPbp_FF_genGluFrac[FF_Bins];

TH1D * pp2TeV_data_NoReweight[FF_Bins];
TH1D * pp2TeV_reco_NoReweight[FF_Bins];
TH1D * pp2TeV_rJgT_NoReweight[FF_Bins];
TH1D * pp2TeV_gJrT_NoReweight[FF_Bins];
TH1D * pp2TeV_gen_NoReweight[FF_Bins];

TH1D * pp7TeV_data_NoReweight[FF_Bins];
TH1D * pp7TeV_reco_NoReweight[FF_Bins];
TH1D * pp7TeV_rJgT_NoReweight[FF_Bins];
TH1D * pp7TeV_gJrT_NoReweight[FF_Bins];
TH1D * pp7TeV_gen_NoReweight[FF_Bins];

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

TH1D * pPb5Pbp5_0_jet;
TH2D * pPb5Pbp5_0_track;
TH2D * pPb5Pbp5_0_trackUE;
TH2D * pPb5Pbp5_0_track_xi;
TH2D * pPb5Pbp5_0_trackUE_xi;

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

TH2D * pp2_1_track_rJgT;
TH2D * pp2_1_trackUE_rJgT;
TH2D * pp2_1_track_xi_rJgT;
TH2D * pp2_1_trackUE_xi_rJgT;
TH2D * pp2_1_track_gJrT;
TH2D * pp2_1_trackUE_gJrT;
TH2D * pp2_1_track_xi_gJrT;
TH2D * pp2_1_trackUE_xi_gJrT;

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

TH2D * pp7_1_track_rJgT;
TH2D * pp7_1_trackUE_rJgT;
TH2D * pp7_1_track_xi_rJgT;
TH2D * pp7_1_trackUE_xi_rJgT;
TH2D * pp7_1_track_gJrT;
TH2D * pp7_1_trackUE_gJrT;
TH2D * pp7_1_track_xi_gJrT;
TH2D * pp7_1_trackUE_xi_gJrT;

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

TH2D * pPb5_1_track_rJgT;
TH2D * pPb5_1_trackUE_rJgT;
TH2D * pPb5_1_track_xi_rJgT;
TH2D * pPb5_1_trackUE_xi_rJgT;
TH2D * pPb5_1_track_gJrT;
TH2D * pPb5_1_trackUE_gJrT;
TH2D * pPb5_1_track_xi_gJrT;
TH2D * pPb5_1_trackUE_xi_gJrT;

TH1D * Pbp5_1_jet_reco;
TH2D * Pbp5_1_track_reco;
TH2D * Pbp5_1_trackUE_reco;
TH2D * Pbp5_1_track_xi_reco;
TH2D * Pbp5_1_trackUE_xi_reco;

TH1D * Pbp5_1_jet_reco_Q;
TH2D * Pbp5_1_track_reco_Q;
TH2D * Pbp5_1_trackUE_reco_Q;
TH2D * Pbp5_1_track_xi_reco_Q;
TH2D * Pbp5_1_trackUE_xi_reco_Q;

TH1D * Pbp5_1_jet_reco_G;
TH2D * Pbp5_1_track_reco_G;
TH2D * Pbp5_1_trackUE_reco_G;
TH2D * Pbp5_1_track_xi_reco_G;
TH2D * Pbp5_1_trackUE_xi_reco_G;

TH2D * Pbp5_1_track_rJgT;
TH2D * Pbp5_1_trackUE_rJgT;
TH2D * Pbp5_1_track_xi_rJgT;
TH2D * Pbp5_1_trackUE_xi_rJgT;
TH2D * Pbp5_1_track_gJrT;
TH2D * Pbp5_1_trackUE_gJrT;
TH2D * Pbp5_1_track_xi_gJrT;
TH2D * Pbp5_1_trackUE_xi_gJrT;

TH1D * pp2_1_jet_gen;
TH2D * pp2_1_track_gen;
TH2D * pp2_1_trackUE_gen;
TH2D * pp2_1_track_xi_gen;
TH2D * pp2_1_trackUE_xi_gen;

TH1D * pp2_1_jet_gen_Q;
TH2D * pp2_1_track_gen_Q;
TH2D * pp2_1_trackUE_gen_Q;
TH2D * pp2_1_track_xi_gen_Q;
TH2D * pp2_1_trackUE_xi_gen_Q;
TH1D * pp2_1_jet_gen_G;
TH2D * pp2_1_track_gen_G;
TH2D * pp2_1_trackUE_gen_G;
TH2D * pp2_1_track_xi_gen_G;
TH2D * pp2_1_trackUE_xi_gen_G;

TH1D * pp7_1_jet_gen;
TH2D * pp7_1_track_gen;
TH2D * pp7_1_trackUE_gen;
TH2D * pp7_1_track_xi_gen;
TH2D * pp7_1_trackUE_xi_gen;

TH1D * pp7_1_jet_gen_Q;
TH2D * pp7_1_track_gen_Q;
TH2D * pp7_1_trackUE_gen_Q;
TH2D * pp7_1_track_xi_gen_Q;
TH2D * pp7_1_trackUE_xi_gen_Q;
TH1D * pp7_1_jet_gen_G;
TH2D * pp7_1_track_gen_G;
TH2D * pp7_1_trackUE_gen_G;
TH2D * pp7_1_track_xi_gen_G;
TH2D * pp7_1_trackUE_xi_gen_G;

TH1D * pPb5_1_jet_gen;
TH2D * pPb5_1_track_gen;
TH2D * pPb5_1_trackUE_gen;
TH2D * pPb5_1_track_xi_gen;
TH2D * pPb5_1_trackUE_xi_gen;

TH1D * pPb5_1_jet_gen_Q;
TH2D * pPb5_1_track_gen_Q;
TH2D * pPb5_1_trackUE_gen_Q;
TH2D * pPb5_1_track_xi_gen_Q;
TH2D * pPb5_1_trackUE_xi_gen_Q;
TH1D * pPb5_1_jet_gen_G;
TH2D * pPb5_1_track_gen_G;
TH2D * pPb5_1_trackUE_gen_G;
TH2D * pPb5_1_track_xi_gen_G;
TH2D * pPb5_1_trackUE_xi_gen_G;

TH1D * Pbp5_1_jet_gen;
TH2D * Pbp5_1_track_gen;
TH2D * Pbp5_1_trackUE_gen;
TH2D * Pbp5_1_track_xi_gen;
TH2D * Pbp5_1_trackUE_xi_gen;

TH1D * Pbp5_1_jet_gen_Q;
TH2D * Pbp5_1_track_gen_Q;
TH2D * Pbp5_1_trackUE_gen_Q;
TH2D * Pbp5_1_track_xi_gen_Q;
TH2D * Pbp5_1_trackUE_xi_gen_Q;
TH1D * Pbp5_1_jet_gen_G;
TH2D * Pbp5_1_track_gen_G;
TH2D * Pbp5_1_trackUE_gen_G;
TH2D * Pbp5_1_track_xi_gen_G;
TH2D * Pbp5_1_trackUE_xi_gen_G;

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

TH2D * pp5_1_track_rJgT;
TH2D * pp5_1_trackUE_rJgT;
TH2D * pp5_1_track_xi_rJgT;
TH2D * pp5_1_trackUE_xi_rJgT;
TH2D * pp5_1_track_gJrT;
TH2D * pp5_1_trackUE_gJrT;
TH2D * pp5_1_track_xi_gJrT;
TH2D * pp5_1_trackUE_xi_gJrT;

TH1D * pp5_1_jet_gen;
TH2D * pp5_1_track_gen;
TH2D * pp5_1_trackUE_gen;
TH2D * pp5_1_track_xi_gen;
TH2D * pp5_1_trackUE_xi_gen;

TH1D * pp5_1_jet_gen_Q;
TH2D * pp5_1_track_gen_Q;
TH2D * pp5_1_trackUE_gen_Q;
TH2D * pp5_1_track_xi_gen_Q;
TH2D * pp5_1_trackUE_xi_gen_Q;
TH1D * pp5_1_jet_gen_G;
TH2D * pp5_1_track_gen_G;
TH2D * pp5_1_trackUE_gen_G;
TH2D * pp5_1_track_xi_gen_G;
TH2D * pp5_1_trackUE_xi_gen_G;

TH1D *gluon_2tev_reco;
TH1D *gluon_5tev_reco;
TH1D *gluon_7tev_reco;
TH1D *gluon_2tev_gen;
TH1D *gluon_5tev_gen;
TH1D *gluon_7tev_gen;

void loadHistos(int v, int UEtype)
{
  TFile * spectraFilepp2 = new TFile(Form("%s/pp2_UE%d_0_15.root",filePath,UEtype),"read");
  TFile * spectraFilepPb5 = new TFile(Form("%s/pPb5_UE%d_0_15.root",filePath,UEtype),"read");
  TFile * spectraFilePbp5 = new TFile(Form("%s/Pbp5_UE%d_0_15.root",filePath,UEtype),"read");
  TFile * spectraFilepp7 = new TFile(Form("%s/pp7_UE%d_0_15.root",filePath,UEtype),"read");
  TFile * MCFilepp2 = new TFile(Form("%s/pp2MC_UE%d_0_15.root",filePath,UEtype),"read");
  TFile * MCFilepPb5 = new TFile(Form("%s/pPb5MC_UE%d_0_15.root",filePath,UEtype),"read");
  TFile * MCFilePbp5 = new TFile(Form("%s/Pbp5MC_UE%d_0_15.root",filePath,UEtype),"read");
  TFile * MCFilepp7 = new TFile(Form("%s/pp7MC_UE%d_0_15.root",filePath,UEtype),"read");
  TFile * MCFilepp5 = new TFile(Form("%s/pp5MC_UE%d_0_15.root",filePath,UEtype),"read");

  std::string pp2Tag = "", pp7Tag = "", pPb5Tag = "";
  if(v==1 || v==2 || v==7 || v==10 || v==13 || v==14 || v==15 || v==20 || v==21) pp2Tag = variationTag[v];
  if(v==3 || v==4 || v==8 || v==11 || v==13 || v==16 || v==17 || v==22 || v==23) pp7Tag = variationTag[v];
  if(v==5 || v==6 || v==9 || v==12 || v==13 || v==18 || v==19 || v==24 || v==25) pPb5Tag = variationTag[v];

//2.76 pp
  pp2_0_jet = (TH1D*) spectraFilepp2->Get(Form("pp2_reco_jet%s",pp2Tag.data()));
  pp2_0_track = (TH2D*) spectraFilepp2->Get(Form("pp2_reco_track%s",pp2Tag.data()));
  pp2_0_trackUE = (TH2D*) spectraFilepp2->Get(Form("pp2_reco_trackUE%s",pp2Tag.data()));
  pp2_0_track_xi = (TH2D*) spectraFilepp2->Get(Form("pp2_reco_track_xi%s",pp2Tag.data()));
  pp2_0_trackUE_xi = (TH2D*) spectraFilepp2->Get(Form("pp2_reco_trackUE_xi%s",pp2Tag.data()));

  pp2_1_jet_reco = (TH1D*) MCFilepp2->Get(Form("pp2_reco_jet%s",pp2Tag.data()));
  pp2_1_track_reco = (TH2D*) MCFilepp2->Get(Form("pp2_reco_track%s",pp2Tag.data()));
  pp2_1_trackUE_reco = (TH2D*) MCFilepp2->Get(Form("pp2_reco_trackUE%s",pp2Tag.data()));
  pp2_1_track_xi_reco = (TH2D*) MCFilepp2->Get(Form("pp2_reco_track_xi%s",pp2Tag.data()));
  pp2_1_trackUE_xi_reco = (TH2D*) MCFilepp2->Get(Form("pp2_reco_trackUE_xi%s",pp2Tag.data()));

  pp2_1_jet_reco_Q = (TH1D*) MCFilepp2->Get(Form("pp2_reco_jet_Q%s",pp2Tag.data()));
  pp2_1_track_reco_Q = (TH2D*) MCFilepp2->Get(Form("pp2_reco_track_Q%s",pp2Tag.data()));
  pp2_1_trackUE_reco_Q = (TH2D*) MCFilepp2->Get(Form("pp2_reco_trackUE_Q%s",pp2Tag.data()));
  pp2_1_track_xi_reco_Q = (TH2D*) MCFilepp2->Get(Form("pp2_reco_track_xi_Q%s",pp2Tag.data()));
  pp2_1_trackUE_xi_reco_Q = (TH2D*) MCFilepp2->Get(Form("pp2_reco_trackUE_xi_Q%s",pp2Tag.data()));
  pp2_1_jet_reco_G = (TH1D*) MCFilepp2->Get(Form("pp2_reco_jet_G%s",pp2Tag.data()));
  pp2_1_track_reco_G = (TH2D*) MCFilepp2->Get(Form("pp2_reco_track_G%s",pp2Tag.data()));
  pp2_1_trackUE_reco_G = (TH2D*) MCFilepp2->Get(Form("pp2_reco_trackUE_G%s",pp2Tag.data()));
  pp2_1_track_xi_reco_G = (TH2D*) MCFilepp2->Get(Form("pp2_reco_track_xi_G%s",pp2Tag.data()));
  pp2_1_trackUE_xi_reco_G = (TH2D*) MCFilepp2->Get(Form("pp2_reco_trackUE_xi_G%s",pp2Tag.data()));

  pp2_1_track_rJgT = (TH2D*) MCFilepp2->Get(Form("pp2_rJgT_track%s",pp2Tag.data()));
  pp2_1_trackUE_rJgT = (TH2D*) MCFilepp2->Get(Form("pp2_rJgT_trackUE%s",pp2Tag.data()));
  pp2_1_track_xi_rJgT = (TH2D*) MCFilepp2->Get(Form("pp2_rJgT_track_xi%s",pp2Tag.data()));
  pp2_1_trackUE_xi_rJgT = (TH2D*) MCFilepp2->Get(Form("pp2_rJgT_trackUE_xi%s",pp2Tag.data()));
  pp2_1_track_gJrT = (TH2D*) MCFilepp2->Get(Form("pp2_gJrT_track%s",pp2Tag.data()));
  pp2_1_trackUE_gJrT = (TH2D*) MCFilepp2->Get(Form("pp2_gJrT_trackUE%s",pp2Tag.data()));
  pp2_1_track_xi_gJrT = (TH2D*) MCFilepp2->Get(Form("pp2_gJrT_track_xi%s",pp2Tag.data()));
  pp2_1_trackUE_xi_gJrT = (TH2D*) MCFilepp2->Get(Form("pp2_gJrT_trackUE_xi%s",pp2Tag.data()));
  
  pp2_1_jet_gen = (TH1D*) MCFilepp2->Get(Form("pp2_gen_jet%s",pp2Tag.data()));
  pp2_1_track_gen = (TH2D*) MCFilepp2->Get(Form("pp2_gen_track%s",pp2Tag.data()));
  pp2_1_trackUE_gen = (TH2D*) MCFilepp2->Get(Form("pp2_gen_trackUE%s",pp2Tag.data()));
  pp2_1_track_xi_gen = (TH2D*) MCFilepp2->Get(Form("pp2_gen_track_xi%s",pp2Tag.data()));
  pp2_1_trackUE_xi_gen = (TH2D*) MCFilepp2->Get(Form("pp2_gen_trackUE_xi%s",pp2Tag.data()));

  pp2_1_jet_gen_Q = (TH1D*) MCFilepp2->Get(Form("pp2_gen_jet_Q%s",pp2Tag.data()));
  pp2_1_track_gen_Q = (TH2D*) MCFilepp2->Get(Form("pp2_gen_track_Q%s",pp2Tag.data()));
  pp2_1_trackUE_gen_Q = (TH2D*) MCFilepp2->Get(Form("pp2_gen_trackUE_Q%s",pp2Tag.data()));
  pp2_1_track_xi_gen_Q = (TH2D*) MCFilepp2->Get(Form("pp2_gen_track_xi_Q%s",pp2Tag.data()));
  pp2_1_trackUE_xi_gen_Q = (TH2D*) MCFilepp2->Get(Form("pp2_gen_trackUE_xi_Q%s",pp2Tag.data()));
  pp2_1_jet_gen_G = (TH1D*) MCFilepp2->Get(Form("pp2_gen_jet_G%s",pp2Tag.data()));
  pp2_1_track_gen_G = (TH2D*) MCFilepp2->Get(Form("pp2_gen_track_G%s",pp2Tag.data()));
  pp2_1_trackUE_gen_G = (TH2D*) MCFilepp2->Get(Form("pp2_gen_trackUE_G%s",pp2Tag.data()));
  pp2_1_track_xi_gen_G = (TH2D*) MCFilepp2->Get(Form("pp2_gen_track_xi_G%s",pp2Tag.data()));
  pp2_1_trackUE_xi_gen_G = (TH2D*) MCFilepp2->Get(Form("pp2_gen_trackUE_xi_G%s",pp2Tag.data()));
  
  pp7_0_jet = (TH1D*) spectraFilepp7->Get(Form("pp7_reco_jet%s",pp7Tag.data()));
  pp7_0_track = (TH2D*) spectraFilepp7->Get(Form("pp7_reco_track%s",pp7Tag.data()));
  pp7_0_trackUE = (TH2D*) spectraFilepp7->Get(Form("pp7_reco_trackUE%s",pp7Tag.data()));
  pp7_0_track_xi = (TH2D*) spectraFilepp7->Get(Form("pp7_reco_track_xi%s",pp7Tag.data()));
  pp7_0_trackUE_xi = (TH2D*) spectraFilepp7->Get(Form("pp7_reco_trackUE_xi%s",pp7Tag.data()));

  pp7_1_jet_reco = (TH1D*) MCFilepp7->Get(Form("pp7_reco_jet%s",pp7Tag.data()));
  pp7_1_track_reco = (TH2D*) MCFilepp7->Get(Form("pp7_reco_track%s",pp7Tag.data()));
  pp7_1_trackUE_reco = (TH2D*) MCFilepp7->Get(Form("pp7_reco_trackUE%s",pp7Tag.data()));
  pp7_1_track_xi_reco = (TH2D*) MCFilepp7->Get(Form("pp7_reco_track_xi%s",pp7Tag.data()));
  pp7_1_trackUE_xi_reco = (TH2D*) MCFilepp7->Get(Form("pp7_reco_trackUE_xi%s",pp7Tag.data()));

  pp7_1_jet_reco_Q = (TH1D*) MCFilepp7->Get(Form("pp7_reco_jet_Q%s",pp7Tag.data()));
  pp7_1_track_reco_Q = (TH2D*) MCFilepp7->Get(Form("pp7_reco_track_Q%s",pp7Tag.data()));
  pp7_1_trackUE_reco_Q = (TH2D*) MCFilepp7->Get(Form("pp7_reco_trackUE_Q%s",pp7Tag.data()));
  pp7_1_track_xi_reco_Q = (TH2D*) MCFilepp7->Get(Form("pp7_reco_track_xi_Q%s",pp7Tag.data()));
  pp7_1_trackUE_xi_reco_Q = (TH2D*) MCFilepp7->Get(Form("pp7_reco_trackUE_xi_Q%s",pp7Tag.data()));
  pp7_1_jet_reco_G = (TH1D*) MCFilepp7->Get(Form("pp7_reco_jet_G%s",pp7Tag.data()));
  pp7_1_track_reco_G = (TH2D*) MCFilepp7->Get(Form("pp7_reco_track_G%s",pp7Tag.data()));
  pp7_1_trackUE_reco_G = (TH2D*) MCFilepp7->Get(Form("pp7_reco_trackUE_G%s",pp7Tag.data()));
  pp7_1_track_xi_reco_G = (TH2D*) MCFilepp7->Get(Form("pp7_reco_track_xi_G%s",pp7Tag.data()));
  pp7_1_trackUE_xi_reco_G = (TH2D*) MCFilepp7->Get(Form("pp7_reco_trackUE_xi_G%s",pp7Tag.data()));

  pp7_1_track_rJgT = (TH2D*) MCFilepp7->Get(Form("pp7_rJgT_track%s",pp7Tag.data()));
  pp7_1_trackUE_rJgT = (TH2D*) MCFilepp7->Get(Form("pp7_rJgT_trackUE%s",pp7Tag.data()));
  pp7_1_track_xi_rJgT = (TH2D*) MCFilepp7->Get(Form("pp7_rJgT_track_xi%s",pp7Tag.data()));
  pp7_1_trackUE_xi_rJgT = (TH2D*) MCFilepp7->Get(Form("pp7_rJgT_trackUE_xi%s",pp7Tag.data()));
  pp7_1_track_gJrT = (TH2D*) MCFilepp7->Get(Form("pp7_gJrT_track%s",pp7Tag.data()));
  pp7_1_trackUE_gJrT = (TH2D*) MCFilepp7->Get(Form("pp7_gJrT_trackUE%s",pp7Tag.data()));
  pp7_1_track_xi_gJrT = (TH2D*) MCFilepp7->Get(Form("pp7_gJrT_track_xi%s",pp7Tag.data()));
  pp7_1_trackUE_xi_gJrT = (TH2D*) MCFilepp7->Get(Form("pp7_gJrT_trackUE_xi%s",pp7Tag.data()));

  pp7_1_jet_gen = (TH1D*) MCFilepp7->Get(Form("pp7_gen_jet%s",pp7Tag.data()));
  pp7_1_track_gen = (TH2D*) MCFilepp7->Get(Form("pp7_gen_track%s",pp7Tag.data()));
  pp7_1_trackUE_gen = (TH2D*) MCFilepp7->Get(Form("pp7_gen_trackUE%s",pp7Tag.data()));
  pp7_1_track_xi_gen = (TH2D*) MCFilepp7->Get(Form("pp7_gen_track_xi%s",pp7Tag.data()));
  pp7_1_trackUE_xi_gen = (TH2D*) MCFilepp7->Get(Form("pp7_gen_trackUE_xi%s",pp7Tag.data()));
 
  pp7_1_jet_gen_Q = (TH1D*) MCFilepp7->Get(Form("pp7_gen_jet_Q%s",pp7Tag.data()));
  pp7_1_track_gen_Q = (TH2D*) MCFilepp7->Get(Form("pp7_gen_track_Q%s",pp7Tag.data()));
  pp7_1_trackUE_gen_Q = (TH2D*) MCFilepp7->Get(Form("pp7_gen_trackUE_Q%s",pp7Tag.data()));
  pp7_1_track_xi_gen_Q = (TH2D*) MCFilepp7->Get(Form("pp7_gen_track_xi_Q%s",pp7Tag.data()));
  pp7_1_trackUE_xi_gen_Q = (TH2D*) MCFilepp7->Get(Form("pp7_gen_trackUE_xi_Q%s",pp7Tag.data())); 
  pp7_1_jet_gen_G = (TH1D*) MCFilepp7->Get(Form("pp7_gen_jet_G%s",pp7Tag.data()));
  pp7_1_track_gen_G = (TH2D*) MCFilepp7->Get(Form("pp7_gen_track_G%s",pp7Tag.data()));
  pp7_1_trackUE_gen_G = (TH2D*) MCFilepp7->Get(Form("pp7_gen_trackUE_G%s",pp7Tag.data()));
  pp7_1_track_xi_gen_G = (TH2D*) MCFilepp7->Get(Form("pp7_gen_track_xi_G%s",pp7Tag.data()));
  pp7_1_trackUE_xi_gen_G = (TH2D*) MCFilepp7->Get(Form("pp7_gen_trackUE_xi_G%s",pp7Tag.data()));

  pPb5_0_jet = (TH1D*) spectraFilepPb5->Get(Form("pPb5_reco_jet%s",pPb5Tag.data()));
  pPb5_0_track = (TH2D*) spectraFilepPb5->Get(Form("pPb5_reco_track%s",pPb5Tag.data()));
  pPb5_0_trackUE = (TH2D*) spectraFilepPb5->Get(Form("pPb5_reco_trackUE%s",pPb5Tag.data()));
  pPb5_0_track_xi = (TH2D*) spectraFilepPb5->Get(Form("pPb5_reco_track_xi%s",pPb5Tag.data()));
  pPb5_0_trackUE_xi = (TH2D*) spectraFilepPb5->Get(Form("pPb5_reco_trackUE_xi%s",pPb5Tag.data()));

  Pbp5_0_jet = (TH1D*) spectraFilePbp5->Get(Form("Pbp5_reco_jet%s",pPb5Tag.data()));
  Pbp5_0_track = (TH2D*) spectraFilePbp5->Get(Form("Pbp5_reco_track%s",pPb5Tag.data()));
  Pbp5_0_trackUE = (TH2D*) spectraFilePbp5->Get(Form("Pbp5_reco_trackUE%s",pPb5Tag.data()));
  Pbp5_0_track_xi = (TH2D*) spectraFilePbp5->Get(Form("Pbp5_reco_track_xi%s",pPb5Tag.data()));
  Pbp5_0_trackUE_xi = (TH2D*) spectraFilePbp5->Get(Form("Pbp5_reco_trackUE_xi%s",pPb5Tag.data()));

  pPb5Pbp5_0_jet = (TH1D*)pPb5_0_jet->Clone("pPb5Pbp5_reco_jet");
  pPb5Pbp5_0_track = (TH2D*)pPb5_0_track->Clone("pPb5Pbp5_reco_track");
  pPb5Pbp5_0_trackUE = (TH2D*)pPb5_0_trackUE->Clone("pPb5Pbp5_reco_trackUE");
  pPb5Pbp5_0_track_xi = (TH2D*)pPb5_0_track_xi->Clone("pPb5Pbp5_reco_track_xi");
  pPb5Pbp5_0_trackUE_xi = (TH2D*)pPb5_0_trackUE_xi->Clone("pPb5Pbp5_reco_trackUE_xi");
  pPb5Pbp5_0_jet->Add(Pbp5_0_jet);
  pPb5Pbp5_0_track->Add(Pbp5_0_track);
  pPb5Pbp5_0_trackUE->Add(Pbp5_0_trackUE);
  pPb5Pbp5_0_track_xi->Add(Pbp5_0_track_xi);
  pPb5Pbp5_0_trackUE_xi->Add(Pbp5_0_trackUE_xi);

  pPb5_1_jet_reco = (TH1D*) MCFilepPb5->Get(Form("pPb5_reco_jet%s",pPb5Tag.data()));
  pPb5_1_track_reco = (TH2D*) MCFilepPb5->Get(Form("pPb5_reco_track%s",pPb5Tag.data()));
  pPb5_1_trackUE_reco = (TH2D*) MCFilepPb5->Get(Form("pPb5_reco_trackUE%s",pPb5Tag.data()));
  pPb5_1_track_xi_reco = (TH2D*) MCFilepPb5->Get(Form("pPb5_reco_track_xi%s",pPb5Tag.data()));
  pPb5_1_trackUE_xi_reco = (TH2D*)MCFilepPb5->Get(Form("pPb5_reco_trackUE_xi%s",pPb5Tag.data()));

  pPb5_1_jet_reco_Q = (TH1D*) MCFilepPb5->Get(Form("pPb5_reco_jet_Q%s",pPb5Tag.data()));
  pPb5_1_track_reco_Q = (TH2D*) MCFilepPb5->Get(Form("pPb5_reco_track_Q%s",pPb5Tag.data()));
  pPb5_1_trackUE_reco_Q = (TH2D*) MCFilepPb5->Get(Form("pPb5_reco_trackUE_Q%s",pPb5Tag.data()));
  pPb5_1_track_xi_reco_Q = (TH2D*) MCFilepPb5->Get(Form("pPb5_reco_track_xi_Q%s",pPb5Tag.data()));
  pPb5_1_trackUE_xi_reco_Q = (TH2D*)MCFilepPb5->Get(Form("pPb5_reco_trackUE_xi_Q%s",pPb5Tag.data()));

  pPb5_1_jet_reco_G = (TH1D*) MCFilepPb5->Get(Form("pPb5_reco_jet_G%s",pPb5Tag.data()));
  pPb5_1_track_reco_G = (TH2D*) MCFilepPb5->Get(Form("pPb5_reco_track_G%s",pPb5Tag.data()));
  pPb5_1_trackUE_reco_G = (TH2D*) MCFilepPb5->Get(Form("pPb5_reco_trackUE_G%s",pPb5Tag.data()));
  pPb5_1_track_xi_reco_G = (TH2D*) MCFilepPb5->Get(Form("pPb5_reco_track_xi_G%s",pPb5Tag.data()));
  pPb5_1_trackUE_xi_reco_G = (TH2D*)MCFilepPb5->Get(Form("pPb5_reco_trackUE_xi_G%s",pPb5Tag.data()));

  pPb5_1_track_rJgT = (TH2D*) MCFilepPb5->Get(Form("pPb5_rJgT_track%s",pPb5Tag.data()));
  pPb5_1_trackUE_rJgT = (TH2D*) MCFilepPb5->Get(Form("pPb5_rJgT_trackUE%s",pPb5Tag.data()));
  pPb5_1_track_xi_rJgT = (TH2D*) MCFilepPb5->Get(Form("pPb5_rJgT_track_xi%s",pPb5Tag.data()));
  pPb5_1_trackUE_xi_rJgT = (TH2D*)MCFilepPb5->Get(Form("pPb5_rJgT_trackUE_xi%s",pPb5Tag.data()));
  pPb5_1_track_gJrT = (TH2D*) MCFilepPb5->Get(Form("pPb5_gJrT_track%s",pPb5Tag.data()));
  pPb5_1_trackUE_gJrT = (TH2D*) MCFilepPb5->Get(Form("pPb5_gJrT_trackUE%s",pPb5Tag.data()));
  pPb5_1_track_xi_gJrT = (TH2D*) MCFilepPb5->Get(Form("pPb5_gJrT_track_xi%s",pPb5Tag.data()));
  pPb5_1_trackUE_xi_gJrT = (TH2D*)MCFilepPb5->Get(Form("pPb5_gJrT_trackUE_xi%s",pPb5Tag.data()));

  Pbp5_1_jet_reco = (TH1D*) MCFilePbp5->Get(Form("Pbp5_reco_jet%s",pPb5Tag.data()));
  Pbp5_1_track_reco = (TH2D*) MCFilePbp5->Get(Form("Pbp5_reco_track%s",pPb5Tag.data()));
  Pbp5_1_trackUE_reco = (TH2D*) MCFilePbp5->Get(Form("Pbp5_reco_trackUE%s",pPb5Tag.data()));
  Pbp5_1_track_xi_reco = (TH2D*) MCFilePbp5->Get(Form("Pbp5_reco_track_xi%s",pPb5Tag.data()));
  Pbp5_1_trackUE_xi_reco = (TH2D*)MCFilePbp5->Get(Form("Pbp5_reco_trackUE_xi%s",pPb5Tag.data()));

  Pbp5_1_jet_reco_Q = (TH1D*) MCFilePbp5->Get(Form("Pbp5_reco_jet_Q%s",pPb5Tag.data()));
  Pbp5_1_track_reco_Q = (TH2D*) MCFilePbp5->Get(Form("Pbp5_reco_track_Q%s",pPb5Tag.data()));
  Pbp5_1_trackUE_reco_Q = (TH2D*) MCFilePbp5->Get(Form("Pbp5_reco_trackUE_Q%s",pPb5Tag.data()));
  Pbp5_1_track_xi_reco_Q = (TH2D*) MCFilePbp5->Get(Form("Pbp5_reco_track_xi_Q%s",pPb5Tag.data()));
  Pbp5_1_trackUE_xi_reco_Q = (TH2D*)MCFilePbp5->Get(Form("Pbp5_reco_trackUE_xi_Q%s",pPb5Tag.data()));

  Pbp5_1_jet_reco_G = (TH1D*) MCFilePbp5->Get(Form("Pbp5_reco_jet_G%s",pPb5Tag.data()));
  Pbp5_1_track_reco_G = (TH2D*) MCFilePbp5->Get(Form("Pbp5_reco_track_G%s",pPb5Tag.data()));
  Pbp5_1_trackUE_reco_G = (TH2D*) MCFilePbp5->Get(Form("Pbp5_reco_trackUE_G%s",pPb5Tag.data()));
  Pbp5_1_track_xi_reco_G = (TH2D*) MCFilePbp5->Get(Form("Pbp5_reco_track_xi_G%s",pPb5Tag.data()));
  Pbp5_1_trackUE_xi_reco_G = (TH2D*)MCFilePbp5->Get(Form("Pbp5_reco_trackUE_xi_G%s",pPb5Tag.data()));

  Pbp5_1_track_rJgT = (TH2D*) MCFilePbp5->Get(Form("Pbp5_rJgT_track%s",pPb5Tag.data()));
  Pbp5_1_trackUE_rJgT = (TH2D*) MCFilePbp5->Get(Form("Pbp5_rJgT_trackUE%s",pPb5Tag.data()));
  Pbp5_1_track_xi_rJgT = (TH2D*) MCFilePbp5->Get(Form("Pbp5_rJgT_track_xi%s",pPb5Tag.data()));
  Pbp5_1_trackUE_xi_rJgT = (TH2D*)MCFilePbp5->Get(Form("Pbp5_rJgT_trackUE_xi%s",pPb5Tag.data()));
  Pbp5_1_track_gJrT = (TH2D*) MCFilePbp5->Get(Form("Pbp5_gJrT_track%s",pPb5Tag.data()));
  Pbp5_1_trackUE_gJrT = (TH2D*) MCFilePbp5->Get(Form("Pbp5_gJrT_trackUE%s",pPb5Tag.data()));
  Pbp5_1_track_xi_gJrT = (TH2D*) MCFilePbp5->Get(Form("Pbp5_gJrT_track_xi%s",pPb5Tag.data()));
  Pbp5_1_trackUE_xi_gJrT = (TH2D*)MCFilePbp5->Get(Form("Pbp5_gJrT_trackUE_xi%s",pPb5Tag.data()));

  pp5_1_jet_reco = (TH1D*) MCFilepp5->Get(Form("pp5_reco_jet%s",pPb5Tag.data()));
  pp5_1_track_reco = (TH2D*) MCFilepp5->Get(Form("pp5_reco_track%s",pPb5Tag.data()));
  pp5_1_trackUE_reco = (TH2D*) MCFilepp5->Get(Form("pp5_reco_trackUE%s",pPb5Tag.data()));
  pp5_1_track_xi_reco = (TH2D*) MCFilepp5->Get(Form("pp5_reco_track_xi%s",pPb5Tag.data()));
  pp5_1_trackUE_xi_reco = (TH2D*) MCFilepp5->Get(Form("pp5_reco_trackUE_xi%s",pPb5Tag.data()));

  pp5_1_jet_reco_Q = (TH1D*) MCFilepp5->Get(Form("pp5_reco_jet_Q%s",pPb5Tag.data()));
  pp5_1_track_reco_Q = (TH2D*) MCFilepp5->Get(Form("pp5_reco_track_Q%s",pPb5Tag.data()));
  pp5_1_trackUE_reco_Q = (TH2D*) MCFilepp5->Get(Form("pp5_reco_trackUE_Q%s",pPb5Tag.data()));
  pp5_1_track_xi_reco_Q = (TH2D*) MCFilepp5->Get(Form("pp5_reco_track_xi_Q%s",pPb5Tag.data()));
  pp5_1_trackUE_xi_reco_Q = (TH2D*) MCFilepp5->Get(Form("pp5_reco_trackUE_xi_Q%s",pPb5Tag.data()));

  pp5_1_jet_reco_G = (TH1D*) MCFilepp5->Get(Form("pp5_reco_jet_G%s",pPb5Tag.data()));
  pp5_1_track_reco_G = (TH2D*) MCFilepp5->Get(Form("pp5_reco_track_G%s",pPb5Tag.data()));
  pp5_1_trackUE_reco_G = (TH2D*) MCFilepp5->Get(Form("pp5_reco_trackUE_G%s",pPb5Tag.data()));
  pp5_1_track_xi_reco_G = (TH2D*) MCFilepp5->Get(Form("pp5_reco_track_xi_G%s",pPb5Tag.data()));
  pp5_1_trackUE_xi_reco_G = (TH2D*) MCFilepp5->Get(Form("pp5_reco_trackUE_xi_G%s",pPb5Tag.data()));

  pp5_1_track_rJgT = (TH2D*) MCFilepp5->Get(Form("pp5_rJgT_track%s",pPb5Tag.data()));
  pp5_1_trackUE_rJgT = (TH2D*) MCFilepp5->Get(Form("pp5_rJgT_trackUE%s",pPb5Tag.data()));
  pp5_1_track_xi_rJgT = (TH2D*) MCFilepp5->Get(Form("pp5_rJgT_track_xi%s",pPb5Tag.data()));
  pp5_1_trackUE_xi_rJgT = (TH2D*) MCFilepp5->Get(Form("pp5_rJgT_trackUE_xi%s",pPb5Tag.data()));
  pp5_1_track_gJrT = (TH2D*) MCFilepp5->Get(Form("pp5_gJrT_track%s",pPb5Tag.data()));
  pp5_1_trackUE_gJrT = (TH2D*) MCFilepp5->Get(Form("pp5_gJrT_trackUE%s",pPb5Tag.data()));
  pp5_1_track_xi_gJrT = (TH2D*) MCFilepp5->Get(Form("pp5_gJrT_track_xi%s",pPb5Tag.data()));
  pp5_1_trackUE_xi_gJrT = (TH2D*) MCFilepp5->Get(Form("pp5_gJrT_trackUE_xi%s",pPb5Tag.data()));

  pPb5_1_jet_gen = (TH1D*) MCFilepPb5->Get(Form("pPb5_gen_jet%s",pPb5Tag.data()));
  pPb5_1_track_gen = (TH2D*) MCFilepPb5->Get(Form("pPb5_gen_track%s",pPb5Tag.data()));
  pPb5_1_trackUE_gen = (TH2D*) MCFilepPb5->Get(Form("pPb5_gen_trackUE%s",pPb5Tag.data()));
  pPb5_1_track_xi_gen = (TH2D*) MCFilepPb5->Get(Form("pPb5_gen_track_xi%s",pPb5Tag.data()));
  pPb5_1_trackUE_xi_gen = (TH2D*)MCFilepPb5->Get(Form("pPb5_gen_trackUE_xi%s",pPb5Tag.data()));
 
  pPb5_1_jet_gen_Q = (TH1D*) MCFilepPb5->Get(Form("pPb5_gen_jet_Q%s",pPb5Tag.data()));
  pPb5_1_track_gen_Q = (TH2D*) MCFilepPb5->Get(Form("pPb5_gen_track_Q%s",pPb5Tag.data()));
  pPb5_1_trackUE_gen_Q = (TH2D*) MCFilepPb5->Get(Form("pPb5_gen_trackUE_Q%s",pPb5Tag.data()));
  pPb5_1_track_xi_gen_Q = (TH2D*) MCFilepPb5->Get(Form("pPb5_gen_track_xi_Q%s",pPb5Tag.data()));
  pPb5_1_trackUE_xi_gen_Q = (TH2D*)MCFilepPb5->Get(Form("pPb5_gen_trackUE_xi_Q%s",pPb5Tag.data()));
  pPb5_1_jet_gen_G = (TH1D*) MCFilepPb5->Get(Form("pPb5_gen_jet_G%s",pPb5Tag.data()));
  pPb5_1_track_gen_G = (TH2D*) MCFilepPb5->Get(Form("pPb5_gen_track_G%s",pPb5Tag.data()));
  pPb5_1_trackUE_gen_G = (TH2D*) MCFilepPb5->Get(Form("pPb5_gen_trackUE_G%s",pPb5Tag.data()));
  pPb5_1_track_xi_gen_G= (TH2D*) MCFilepPb5->Get(Form("pPb5_gen_track_xi_G%s",pPb5Tag.data()));
  pPb5_1_trackUE_xi_gen_G = (TH2D*)MCFilepPb5->Get(Form("pPb5_gen_trackUE_xi_G%s",pPb5Tag.data()));

  Pbp5_1_jet_gen = (TH1D*) MCFilePbp5->Get(Form("Pbp5_gen_jet%s",pPb5Tag.data()));
  Pbp5_1_track_gen = (TH2D*) MCFilePbp5->Get(Form("Pbp5_gen_track%s",pPb5Tag.data()));
  Pbp5_1_trackUE_gen = (TH2D*) MCFilePbp5->Get(Form("Pbp5_gen_trackUE%s",pPb5Tag.data()));
  Pbp5_1_track_xi_gen = (TH2D*) MCFilePbp5->Get(Form("Pbp5_gen_track_xi%s",pPb5Tag.data()));
  Pbp5_1_trackUE_xi_gen = (TH2D*)MCFilePbp5->Get(Form("Pbp5_gen_trackUE_xi%s",pPb5Tag.data()));
 
  Pbp5_1_jet_gen_Q = (TH1D*) MCFilePbp5->Get(Form("Pbp5_gen_jet_Q%s",pPb5Tag.data()));
  Pbp5_1_track_gen_Q = (TH2D*) MCFilePbp5->Get(Form("Pbp5_gen_track_Q%s",pPb5Tag.data()));
  Pbp5_1_trackUE_gen_Q = (TH2D*) MCFilePbp5->Get(Form("Pbp5_gen_trackUE_Q%s",pPb5Tag.data()));
  Pbp5_1_track_xi_gen_Q = (TH2D*) MCFilePbp5->Get(Form("Pbp5_gen_track_xi_Q%s",pPb5Tag.data()));
  Pbp5_1_trackUE_xi_gen_Q = (TH2D*)MCFilePbp5->Get(Form("Pbp5_gen_trackUE_xi_Q%s",pPb5Tag.data()));
  Pbp5_1_jet_gen_G = (TH1D*) MCFilePbp5->Get(Form("Pbp5_gen_jet_G%s",pPb5Tag.data()));
  Pbp5_1_track_gen_G = (TH2D*) MCFilePbp5->Get(Form("Pbp5_gen_track_G%s",pPb5Tag.data()));
  Pbp5_1_trackUE_gen_G = (TH2D*) MCFilePbp5->Get(Form("Pbp5_gen_trackUE_G%s",pPb5Tag.data()));
  Pbp5_1_track_xi_gen_G= (TH2D*) MCFilePbp5->Get(Form("Pbp5_gen_track_xi_G%s",pPb5Tag.data()));
  Pbp5_1_trackUE_xi_gen_G = (TH2D*)MCFilePbp5->Get(Form("Pbp5_gen_trackUE_xi_G%s",pPb5Tag.data()));

  pp5_1_jet_gen = (TH1D*) MCFilepp5->Get(Form("pp5_gen_jet%s",pPb5Tag.data()));
  pp5_1_track_gen = (TH2D*) MCFilepp5->Get(Form("pp5_gen_track%s",pPb5Tag.data()));
  pp5_1_trackUE_gen = (TH2D*) MCFilepp5->Get(Form("pp5_gen_trackUE%s",pPb5Tag.data()));
  pp5_1_track_xi_gen = (TH2D*) MCFilepp5->Get(Form("pp5_gen_track_xi%s",pPb5Tag.data()));
  pp5_1_trackUE_xi_gen = (TH2D*) MCFilepp5->Get(Form("pp5_gen_trackUE_xi%s",pPb5Tag.data()));

  pp5_1_jet_gen_Q = (TH1D*) MCFilepp5->Get(Form("pp5_gen_jet_Q%s",pPb5Tag.data()));
  pp5_1_track_gen_Q = (TH2D*) MCFilepp5->Get(Form("pp5_gen_track_Q%s",pPb5Tag.data()));
  pp5_1_trackUE_gen_Q = (TH2D*) MCFilepp5->Get(Form("pp5_gen_trackUE_Q%s",pPb5Tag.data()));
  pp5_1_track_xi_gen_Q = (TH2D*) MCFilepp5->Get(Form("pp5_gen_track_xi_Q%s",pPb5Tag.data()));
  pp5_1_trackUE_xi_gen_Q = (TH2D*) MCFilepp5->Get(Form("pp5_gen_trackUE_xi_Q%s",pPb5Tag.data()));
  pp5_1_jet_gen_G = (TH1D*) MCFilepp5->Get(Form("pp5_gen_jet_G%s",pPb5Tag.data()));
  pp5_1_track_gen_G = (TH2D*) MCFilepp5->Get(Form("pp5_gen_track_G%s",pPb5Tag.data()));
  pp5_1_trackUE_gen_G = (TH2D*) MCFilepp5->Get(Form("pp5_gen_trackUE_G%s",pPb5Tag.data()));
  pp5_1_track_xi_gen_G = (TH2D*) MCFilepp5->Get(Form("pp5_gen_track_xi_G%s",pPb5Tag.data()));
  pp5_1_trackUE_xi_gen_G = (TH2D*) MCFilepp5->Get(Form("pp5_gen_trackUE_xi_G%s",pPb5Tag.data()));

//gluon fractions for interpolation
  gluon_2tev_reco = (TH1D*)pp2_1_jet_reco_G->Clone("pp2_gFrac_recoMC");
  gluon_5tev_reco = (TH1D*)pPb5_1_jet_reco_G->Clone("pPb5_gFrac_recoMC");
  gluon_7tev_reco = (TH1D*)pp7_1_jet_reco_G->Clone("pp7_gFrac_recoMC");
  gluon_2tev_gen = (TH1D*)pp2_1_jet_gen_G->Clone("pp2_gFrac_genMC");
  gluon_5tev_gen = (TH1D*)pPb5_1_jet_gen_G->Clone("pPb5_gFrac_genMC");
  gluon_7tev_gen = (TH1D*)pp7_1_jet_gen_G->Clone("pp7_gFrac_genMC");

  TH1D * denom2 = (TH1D*)pp2_1_jet_reco_G->Clone("recoDenom2");
  denom2->Add(pp2_1_jet_reco_Q);
  TH1D * denom5 = (TH1D*)pPb5_1_jet_reco_G->Clone("recoDenom5");
  denom5->Add(pPb5_1_jet_reco_Q);
  TH1D * denom7 = (TH1D*)pp7_1_jet_reco_G->Clone("recoDenom7");
  denom7->Add(pp7_1_jet_reco_Q);
  TH1D * gendenom2 = (TH1D*)pp2_1_jet_gen_G->Clone("genDenom2");
  gendenom2->Add(pp2_1_jet_gen_Q);
  TH1D * gendenom5 = (TH1D*)pPb5_1_jet_gen_G->Clone("genDenom5");
  gendenom5->Add(pPb5_1_jet_gen_Q);
  TH1D * gendenom7 = (TH1D*)pp7_1_jet_gen_G->Clone("genDenom7");
  gendenom7->Add(pp7_1_jet_gen_Q); 
  
  gluon_2tev_reco->Divide(denom2); 
  gluon_5tev_reco->Divide(denom5); 
  gluon_7tev_reco->Divide(denom7);
  gluon_2tev_gen->Divide(gendenom2); 
  gluon_5tev_gen->Divide(gendenom5); 
  gluon_7tev_gen->Divide(gendenom7);
}
