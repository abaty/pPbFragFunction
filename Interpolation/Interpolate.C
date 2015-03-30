#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TPad.h"
#include "TText.h"
#include "TAttFill.h"
#include "TLine.h"
#include "TColor.h"
#include "TMathText.h"
#include "TMath.h"
#include "TStyle.h"
#include "loadHistograms.h"
#include "makePlots.h"
#include "plotGluonFraction.C"
#include "interpolationErrors.h"
#include "systematics.C"
#include <iostream>
#include <string>

//forward declarations
TH1D* getFF_pp(double jetPt_low, double jetPt_high, const char* histTitle, int mode = 0);
TH1D** getInterpolation(double jetPt_low, double jetPt_high, const char* histTitle, int ReweightMode, TH1D * hist2, TH1D * hist7, int doGenGluFrac=0);
void getSpectra(int mode);
void Interpolate();

TH1D * jet;
TH2D * trk;
TH2D * trkUE;
TH1D * jet_pPb;

//trk pt bins

const int trkBins=22;
const double yAxis[trkBins+1] = {0.5, 0.63, 0.77,  1.03,1.38, 1.84, 2.46, 3.29,  4.40, 5.88,  7.87,  10.52, 14.06,  18.8, 25.13,  33.58,  44.89,  60, 80, 100, 120, 140, 200};

//const int trkBins = 40;
//double yAxis[trkBins+1] = {0.5, 0.58, 0.67, 0.77, 0.89, 1.03, 1.19,1.38, 1.59, 1.84, 2.13, 2.46, 2.85, 3.29, 3.81, 4.40, 5.09, 5.88, 6.80, 7.87, 9.10, 10.52, 12.16, 14.06, 16.2, 18.8, 21.7, 25.13, 29.05, 33.58, 38.83, 44.89, 51.9, 60, 70, 80, 100, 120, 140, 160, 200};

//main execution starts here
void makeFF(int v)
{ 
  TH1D::SetDefaultSumw2();
  TH2D::SetDefaultSumw2();

  //initializing histograms for analysis
  loadHistos(v);

  for(int i = 0; i < FF_Bins; i++)
  {
    //pPb direction
    pp2TeV_data[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp2TeV_data_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),0);
    pp7TeV_data[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp7TeV_data_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),1);
    pPb5TeV_data[i]= getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pPb5TeV_data_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),2);

    //Pbpdirection
    pp2TeV_reverse_data[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp2TeV_reverse_data_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),31);
    pp7TeV_reverse_data[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp7TeV_reverse_data_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),32);
    Pbp5TeV_data[i]= getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("Pbp5TeV_data_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),3);
    
    //Reco MC
    pp2TeV_recoMC[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp2TeV_recoMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),4);
    pp7TeV_recoMC[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp7TeV_recoMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),5);
    pPb5TeV_recoMC[i]= getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pPb5TeV_recoMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),6);
    pp5TeV_recoMC[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp5TeV_recoMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),11);
    
    //Gen MC
    pp2TeV_genMC[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp2TeV_genMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),7);
    pp7TeV_genMC[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp7TeV_genMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),8);
    pPb5TeV_genMC[i]= getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pPb5TeV_genMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),9);    
    pp5TeV_genMC[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp5TeV_genMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),10); 

    //Reco Gen Combinations
    pp2TeV_rJgTMC[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp2TeV_rJgTMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),33);
    pp7TeV_rJgTMC[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp7TeV_rJgTMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),34);
    pPb5TeV_rJgTMC[i]= getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pPb5TeV_rJgTMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),35);
    pp5TeV_rJgTMC[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp5TeV_rJgTMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),36);
    pp2TeV_gJrTMC[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp2TeV_gJrTMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),37);
    pp7TeV_gJrTMC[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp7TeV_gJrTMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),38);
    pPb5TeV_gJrTMC[i]= getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pPb5TeV_gJrTMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),39);
    pp5TeV_gJrTMC[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp5TeV_gJrTMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),40); 

    //reco MC Q/G study
    pp2TeV_recoMC_Q[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp2TeV_recoMC_Q_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),12);
    pp2TeV_recoMC_G[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp2TeV_recoMC_G_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),13);
    pp7TeV_recoMC_Q[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp7TeV_recoMC_Q_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),14);
    pp7TeV_recoMC_G[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp7TeV_recoMC_G_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),15);
    pPb5TeV_recoMC_Q[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pPb5TeV_recoMC_Q_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),16);
    pPb5TeV_recoMC_G[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pPb5TeV_recoMC_G_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),17);
    pp5TeV_recoMC_Q[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp5TeV_recoMC_Q_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),18);
    pp5TeV_recoMC_G[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp5TeV_recoMC_G_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),19);

    //gen MC Q/G study
    pp2TeV_genMC_Q[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp2TeV_genMC_Q_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),20);
    pp2TeV_genMC_G[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp2TeV_genMC_G_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),21);
    pp7TeV_genMC_Q[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp7TeV_genMC_Q_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),22);
    pp7TeV_genMC_G[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp7TeV_genMC_G_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),23);
    pPb5TeV_genMC_Q[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pPb5TeV_genMC_Q_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),24);
    pPb5TeV_genMC_G[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pPb5TeV_genMC_G_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),25);
    pp5TeV_genMC_Q[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp5TeV_genMC_Q_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),26);
    pp5TeV_genMC_G[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp5TeV_genMC_G_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),27);

    //full data set
    pPb5Pbp5TeV_fulldata[i]=getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pPb5Pbp5TeV_fulldata_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),28);
    pp2TeV_fulldata[i]=getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp2TeV_fulldata_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),29);
    pp7TeV_fulldata[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp7TeV_fulldata_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),30);

    //2 and 7 tev pp FF's with no reweighting
    pp2TeV_data_NoReweight[i]=getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp2TeV_NoReweight_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),41);
    pp2TeV_reco_NoReweight[i]=getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp2TeV_reco_NoReweight_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),43);
    pp2TeV_rJgT_NoReweight[i]=getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp2TeV_rJgT_NoReweight_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),44);
    pp2TeV_gJrT_NoReweight[i]=getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp2TeV_gJrT_NoReweight_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),45);
    pp2TeV_gen_NoReweight[i]=getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp2TeV_gen_NoReweight_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),46);

    pp7TeV_data_NoReweight[i]=getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp7TeV_NoReweight_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),42); 
    pp7TeV_reco_NoReweight[i]=getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp7TeV_reco_NoReweight_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),47); 
    pp7TeV_rJgT_NoReweight[i]=getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp7TeV_rJgT_NoReweight_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),48); 
    pp7TeV_gJrT_NoReweight[i]=getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp7TeV_gJrT_NoReweight_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),49); 
    pp7TeV_gen_NoReweight[i]=getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp7TeV_gen_NoReweight_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),50); 

    //interpolations
    pPb5TeV_data_interp[i]    = getInterpolation(FF_Bound[i],FF_Bound[i+1],"pPb5TeV_data_interp",2,pp2TeV_data[i],pp7TeV_data[i],0);
    Pbp5TeV_data_interp[i]    = getInterpolation(FF_Bound[i],FF_Bound[i+1],"Pbp5TeV_data_interp",3,pp2TeV_reverse_data[i],pp7TeV_reverse_data[i],0);
    pPb5Pb5TeV_data_interp[i] = getInterpolation(FF_Bound[i],FF_Bound[i+1],"pPb5Pbp5TeV_data_interp",28,pp2TeV_fulldata[i],pp7TeV_fulldata[i],0);
    pPb5Pb5TeV_data_interp_genGluFrac[i] = getInterpolation(FF_Bound[i],FF_Bound[i+1],"pPb5Pbp5TeV_data_interp_genGluFrac",28,pp2TeV_fulldata[i],pp7TeV_fulldata[i],1);
    pPb5TeV_recoMC_interp[i]  = getInterpolation(FF_Bound[i],FF_Bound[i+1],"pPb5TeV_recoMC_interp",6,pp2TeV_recoMC[i],pp7TeV_recoMC[i],0);
    pPb5TeV_genMC_interp[i]   = getInterpolation(FF_Bound[i],FF_Bound[i+1],"pPb5TeV_genMC_interp",9,pp2TeV_genMC[i],pp7TeV_genMC[i],1);
    pPb5TeV_rJgTMC_interp[i]    = getInterpolation(FF_Bound[i],FF_Bound[i+1],"pPb5TeV_rJgTMC_interp",35,pp2TeV_rJgTMC[i],pp7TeV_rJgTMC[i],0);
    pPb5TeV_gJrTMC_interp[i]    = getInterpolation(FF_Bound[i],FF_Bound[i+1],"pPb5TeV_gJrTMC_interp",39,pp2TeV_gJrTMC[i],pp7TeV_gJrTMC[i],1);
  }
 
  for(int i = 0; i < FF_Bins; i++)
  {
    pPb_FF[i] = (TH1D*) pPb5TeV_data[i]->Clone(Form("pPb_FF_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]));
    pPb_FF[i]->Divide(pPb5TeV_data_interp[i][0]);
    Pbp_FF[i] = (TH1D*) Pbp5TeV_data[i]->Clone(Form("Pbp_FF_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]));
    Pbp_FF[i]->Divide(Pbp5TeV_data_interp[i][0]);
    pPb_FF_recoMC[i] = (TH1D*) pPb5TeV_recoMC[i]->Clone(Form("pPb_FF_recoMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]));
    pPb_FF_recoMC[i]->Divide(pPb5TeV_recoMC_interp[i][0]);
    pPb_FF_genMC[i] = (TH1D*) pPb5TeV_genMC[i]->Clone(Form("pPb_FF_genMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]));
    pPb_FF_genMC[i]->Divide(pPb5TeV_genMC_interp[i][0]);
    pPbPbp_FF[i] = (TH1D*) pPb5Pbp5TeV_fulldata[i]->Clone(Form("pPbPbp_FF_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]));
    pPbPbp_FF[i]->Divide(pPb5Pb5TeV_data_interp[i][0]); 
    pPbPbp_FF_genGluFrac[i] = (TH1D*) pPb5Pbp5TeV_fulldata[i]->Clone(Form("pPbPbp_FF_genGluFrac_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]));
    pPbPbp_FF_genGluFrac[i]->Divide(pPb5Pb5TeV_data_interp_genGluFrac[i][0]); 
    pPb_FF_rJgTMC[i] = (TH1D*) pPb5TeV_rJgTMC[i]->Clone(Form("pPb_FF_rJgTMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]));
    pPb_FF_rJgTMC[i]->Divide(pPb5TeV_rJgTMC_interp[i][0]);
    pPb_FF_gJrTMC[i] = (TH1D*) pPb5TeV_gJrTMC[i]->Clone(Form("pPb_FF_gJrTMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]));
    pPb_FF_gJrTMC[i]->Divide(pPb5TeV_gJrTMC_interp[i][0]);
  }
 
  TFile * outfile = new TFile(Form("FragmentationFunctions%sUE3.root",variationTag[v]),"recreate");
  for(int i = 0; i < FF_Bins; i++)
  {
    pp2TeV_data[i]->Write();
    pp7TeV_data[i]->Write();
    pPb5TeV_data[i]->Write();
    pp2TeV_reverse_data[i]->Write();
    pp7TeV_reverse_data[i]->Write();
    Pbp5TeV_data[i]->Write();
    pPb5Pbp5TeV_fulldata[i]->Write();
    pp2TeV_fulldata[i]->Write();
    pp7TeV_fulldata[i]->Write();

    pp2TeV_recoMC[i]->Write();
    pp7TeV_recoMC[i]->Write();
    pPb5TeV_recoMC[i]->Write();
    pp5TeV_recoMC[i]->Write();

    pp2TeV_rJgTMC[i]->Write();
    pp7TeV_rJgTMC[i]->Write();
    pPb5TeV_rJgTMC[i]->Write();
    pp5TeV_rJgTMC[i]->Write();
    pp2TeV_gJrTMC[i]->Write();
    pp7TeV_gJrTMC[i]->Write();
    pPb5TeV_gJrTMC[i]->Write();
    pp5TeV_gJrTMC[i]->Write();
 
    pp2TeV_recoMC_Q[i]->Write();
    pp2TeV_recoMC_G[i]->Write();
    pp7TeV_recoMC_Q[i]->Write();
    pp7TeV_recoMC_G[i]->Write();
    pPb5TeV_recoMC_Q[i]->Write();
    pPb5TeV_recoMC_G[i]->Write();
    pp5TeV_recoMC_Q[i]->Write();
    pp5TeV_recoMC_G[i]->Write();

    pp2TeV_genMC[i]->Write();
    pp7TeV_genMC[i]->Write();
    pPb5TeV_genMC[i]->Write();
    pp5TeV_genMC[i]->Write(); 
    pp2TeV_genMC_Q[i]->Write();
    pp2TeV_genMC_G[i]->Write();
    pp7TeV_genMC_Q[i]->Write();
    pp7TeV_genMC_G[i]->Write();
    pPb5TeV_genMC_Q[i]->Write();
    pPb5TeV_genMC_G[i]->Write();
    pp5TeV_genMC_Q[i]->Write();
    pp5TeV_genMC_G[i]->Write();

    pp2TeV_data_NoReweight[i]->Write();
    pp2TeV_reco_NoReweight[i]->Write();
    pp2TeV_rJgT_NoReweight[i]->Write();
    pp2TeV_gJrT_NoReweight[i]->Write();
    pp2TeV_gen_NoReweight[i]->Write();
    pp7TeV_data_NoReweight[i]->Write();
    pp7TeV_reco_NoReweight[i]->Write();
    pp7TeV_rJgT_NoReweight[i]->Write();
    pp7TeV_gJrT_NoReweight[i]->Write();
    pp7TeV_gen_NoReweight[i]->Write();

    for(int indx = 0; indx<3; indx++)
    {
      pPb5TeV_data_interp[i][indx]->Write();
      Pbp5TeV_data_interp[i][indx]->Write();
      pPb5Pb5TeV_data_interp[i][indx]->Write();
      pPb5Pb5TeV_data_interp_genGluFrac[i][indx]->Write();
      pPb5TeV_recoMC_interp[i][indx]->Write();
      pPb5TeV_genMC_interp[i][indx]->Write();
      pPb5TeV_rJgTMC_interp[i][indx]->Write();
      pPb5TeV_gJrTMC_interp[i][indx]->Write();
    } 

    pPb_FF[i]->Write();
    Pbp_FF[i]->Write();  
    pPbPbp_FF[i]->Write(); 
    pPbPbp_FF_genGluFrac[i]->Write(); 
    pPb_FF_recoMC[i]->Write();
    pPb_FF_genMC[i]->Write();
    pPb_FF_rJgTMC[i]->Write();
    pPb_FF_gJrTMC[i]->Write();
  }
  //handing it over to a plotting macro
  makePlots(variationTag[v]); 
  plotGluonFraction(variationTag[v]);
  outfile->Close(); 
}

TH1D* getFF_pp(double jetPt_low, double jetPt_high, const char* histTitle, int mode)
{
  TH1D * FF = new TH1D(histTitle,";p_{T trk};#frac{1}{N_{jet}} #frac{dN_{trk}}{dp_{t trk}}",trkBins ,yAxis);

  getSpectra(mode);

  //looping over bins in Trk pt
    for(int t = 1; t < trk->GetYaxis()->FindBin(jetPt_high); t++)
    {
      double sum   = 0;
      double error = 0;
      double norm  = 0;        

      //looping over jet pt
      for(int j = jet->FindBin(jetPt_low); j < jet->FindBin(jetPt_high); j++)
      {
        //reweighting factor to 5 TeV pPb
        //for (mode 2) 5TeV pPb jet_pPb = jet so this is by definition one
        double w = jet_pPb->GetBinContent(j)/jet->GetBinContent(j);

        //adding up contributions to the FF from each track and jet bin
        sum   += w*(trk->GetBinContent(j,t) - trkUE->GetBinContent(j,t));
        error += w*w*(TMath::Power(trk->GetBinError(j,t),2) + TMath::Power(trkUE->GetBinError(j,t),2));
        norm  += jet_pPb->GetBinContent(j);
      }

      if(norm!=0)
      {   
        sum   = sum/(norm*FF->GetBinWidth(t));
        error = TMath::Power(error,0.5)/(norm*FF->GetBinWidth(t));
        FF->SetBinContent(t,sum);
        FF->SetBinError(t,error);
      }
    }
  return FF;
}

TH1D** getInterpolation(double jetPt_low, double jetPt_high, const char* histTitle, int ReweightMode, TH1D * hist2, TH1D * hist7, int doGenGluFrac)
{
  TH1D * tmp_interp = new TH1D(Form("%s_%d_%d",histTitle,(int)jetPt_low,(int)jetPt_high),";p_{T trk};#frac{1}{N_{jet}} #frac{dN_{trk}}{dp_{t trk}}",trkBins,yAxis);
  TH1D * tmp_Q_interp = new TH1D(Form("%s_Q_%d_%d",histTitle,(int)jetPt_low,(int)jetPt_high),";p_{T trk};#frac{1}{N_{jet}} #frac{dN_{trk}}{dp_{t trk}}",trkBins,yAxis);
  TH1D * tmp_G_interp = new TH1D(Form("%s_G_%d_%d",histTitle,(int)jetPt_low,(int)jetPt_high),";p_{T trk};#frac{1}{N_{jet}} #frac{dN_{trk}}{dp_{t trk}}",trkBins,yAxis);    

  //setting jet spectrum to 5TeV for use in the interpolation weighting (only "jet" is used)
  getSpectra(ReweightMode);
    
  for(int t = 1; t < trkBins+1; t++)
  {
    //number of gluon jets for 2/5/7 MC (proportional to the jet fraction because jet spectra are all reweighted to 5TeV)
    double glu2 = 0;
    double glu5 = 0;
    double glu7 = 0;
    double totalJets = 0;    
    double glu2Err = 0;
    double glu5Err = 0;
    double glu7Err = 0;

    for(int j = jet->FindBin(jetPt_low); j < jet->FindBin(jetPt_high); j++)
    {
      double nJet = jet->GetBinContent(j);
      double nJetErr = jet->GetBinError(j); 

      if(doGenGluFrac==0)
      {
        glu2 += gluon_2tev_reco->GetBinContent(j)*nJet;
        glu5 += gluon_5tev_reco->GetBinContent(j)*nJet;
        glu7 += gluon_7tev_reco->GetBinContent(j)*nJet;
        glu2Err += TMath::Power(gluon_2tev_reco->GetBinError(j)*nJet,2)+ TMath::Power(gluon_2tev_reco->GetBinContent(j)*nJetErr,2);
        glu5Err += TMath::Power(gluon_5tev_reco->GetBinError(j)*nJet,2)+ TMath::Power(gluon_5tev_reco->GetBinContent(j)*nJetErr,2);
        glu7Err += TMath::Power(gluon_7tev_reco->GetBinError(j)*nJet,2)+ TMath::Power(gluon_7tev_reco->GetBinContent(j)*nJetErr,2);
      }
      else
      {
        glu2 += gluon_2tev_gen->GetBinContent(j)*nJet;
        glu5 += gluon_5tev_gen->GetBinContent(j)*nJet;
        glu7 += gluon_7tev_gen->GetBinContent(j)*nJet;
        glu2Err += TMath::Power(gluon_2tev_gen->GetBinError(j)*nJet,2)+ TMath::Power(gluon_2tev_gen->GetBinContent(j)*nJetErr,2);
        glu5Err += TMath::Power(gluon_5tev_gen->GetBinError(j)*nJet,2)+ TMath::Power(gluon_5tev_gen->GetBinContent(j)*nJetErr,2);
        glu7Err += TMath::Power(gluon_7tev_gen->GetBinError(j)*nJet,2)+ TMath::Power(gluon_7tev_gen->GetBinContent(j)*nJetErr,2);
      }
      totalJets += nJet;
    }
    glu2Err = TMath::Power(glu2Err,0.5);
    glu5Err = TMath::Power(glu5Err,0.5);
    glu7Err = TMath::Power(glu7Err,0.5);   
 
    double average = ((glu5 - glu7)*hist2->GetBinContent(t)+(glu2-glu5)*hist7->GetBinContent(t))/(glu2-glu7);
    double error = getInterpolationError(glu2,glu2Err,glu5,glu5Err,glu7,glu7Err,hist2->GetBinContent(t),hist2->GetBinError(t),hist7->GetBinContent(t),hist7->GetBinError(t));
    //double error = TMath::Power(TMath::Power((glu5 - glu7)*pp2TeV_data[i]->GetBinError(t)/(glu2-glu7),2)+TMath::Power((glu2-glu5)*pp7TeV_data[i]->GetBinError(t)/(glu2-glu7),2),0.5);
    double averageQ = (glu2*hist7->GetBinContent(t)-glu7*hist2->GetBinContent(t))/(glu2-glu7);
    double errorQ = TMath::Power(TMath::Power(glu2*hist7->GetBinError(t)/(glu2-glu7),2)+TMath::Power(glu7*hist2->GetBinError(t)/(glu2-glu7),2),0.5);
    double averageG = ((totalJets-glu7)*hist2->GetBinContent(t)-(totalJets-glu2)*hist7->GetBinContent(t))/(glu2-glu7);
    double errorG = TMath::Power(TMath::Power((totalJets-glu7)*hist2->GetBinError(t)/(glu2-glu7),2)+TMath::Power((totalJets-glu2)*hist7->GetBinError(t)/(glu2-glu7),2),0.5);     
 
    tmp_interp->SetBinContent(t, average);
    tmp_interp->SetBinError(t, error);
    tmp_Q_interp->SetBinContent(t, averageQ);
    tmp_Q_interp->SetBinError(t, errorQ);
    tmp_G_interp->SetBinContent(t, averageG);
    tmp_G_interp->SetBinError(t, errorG);
  }

  TH1D** outputArray = new TH1D*[3];
  outputArray[0]=tmp_interp;
  outputArray[1]=tmp_Q_interp;
  outputArray[2]=tmp_G_interp;
  return outputArray;
}

void Interpolate()
{
  for(int v = 0; v<variations; v++) 
  {
    makeFF(v);
  }
  systematics();
}

//tells the getFF_pp exactly which spectra to use in which jetPt range
//Numbers here in the if statements are hard-coded for triggers atm
//to do: combine the spectra before so I can remove this step
void getSpectra(int mode)
{
  if(mode == 0)
  {
    jet     = pp2_0_jet;
    jet_pPb = pPb5_0_jet;
    trk     = pp2_0_track;
    trkUE   = pp2_0_trackUE;
  }
  
  if(mode == 1)
  {
    jet     = pp7_0_jet;
    jet_pPb = pPb5_0_jet;
    trk     = pp7_0_track;
    trkUE   = pp7_0_trackUE;
  }

  if(mode == 2)
  {
    jet     = pPb5_0_jet;
    jet_pPb = pPb5_0_jet;
    trk     = pPb5_0_track;
    trkUE   = pPb5_0_trackUE;
  }
  if(mode == 3)
  {
    jet     = Pbp5_0_jet;
    jet_pPb = Pbp5_0_jet;
    trk     = Pbp5_0_track;
    trkUE   = Pbp5_0_trackUE;
  }
  if(mode == 4)
  {
    jet     = pp2_1_jet_reco;
    jet_pPb = pPb5_1_jet_reco;
    trk     = pp2_1_track_reco;
    trkUE   = pp2_1_trackUE_reco;
  }

  if(mode == 5)
  {
    jet     = pp7_1_jet_reco;
    jet_pPb = pPb5_1_jet_reco;
    trk     = pp7_1_track_reco;
    trkUE   = pp7_1_trackUE_reco;
  }

  if(mode == 6)
  {
    jet     = pPb5_1_jet_reco;
    jet_pPb = pPb5_1_jet_reco;
    trk     = pPb5_1_track_reco;
    trkUE   = pPb5_1_trackUE_reco;
  }
  if(mode == 7)
  {
    jet     = pp2_1_jet_gen;
    jet_pPb = pPb5_1_jet_gen;
    trk     = pp2_1_track_gen;
    trkUE   = pp2_1_trackUE_gen;
  }

  if(mode == 8)
  {
    jet     = pp7_1_jet_gen;
    jet_pPb = pPb5_1_jet_gen;
    trk     = pp7_1_track_gen;
    trkUE   = pp7_1_trackUE_gen;
  }

  if(mode == 9)
  {
    jet     = pPb5_1_jet_gen;
    jet_pPb = pPb5_1_jet_gen;
    trk     = pPb5_1_track_gen;
    trkUE   = pPb5_1_trackUE_gen;
  }
  
  if(mode == 10)
  {
    jet     = pp5_1_jet_gen;
    jet_pPb = pp5_1_jet_gen;
    trk     = pp5_1_track_gen;
    trkUE   = pp5_1_trackUE_gen;
  }

  if(mode == 11)
  {
    jet     = pp5_1_jet_reco;
    jet_pPb = pp5_1_jet_reco;
    trk     = pp5_1_track_reco;
    trkUE   = pp5_1_trackUE_reco;
  }
  
  if(mode == 12)
  {
    jet     = pp2_1_jet_reco_Q;
    jet_pPb = pPb5_1_jet_reco_Q;
    trk     = pp2_1_track_reco_Q;
    trkUE   = pp2_1_trackUE_reco_Q;
  }
  if(mode == 13)
  {
    jet     = pp2_1_jet_reco_G;
    jet_pPb = pPb5_1_jet_reco_G;
    trk     = pp2_1_track_reco_G;
    trkUE   = pp2_1_trackUE_reco_G;
  }
  if(mode == 14)
  {
    jet     = pp7_1_jet_reco_Q;
    jet_pPb = pPb5_1_jet_reco_Q;
    trk     = pp7_1_track_reco_Q;
    trkUE   = pp7_1_trackUE_reco_Q;
  }
  if(mode == 15)
  {
    jet     = pp7_1_jet_reco_G;
    jet_pPb = pPb5_1_jet_reco_G;
    trk     = pp7_1_track_reco_G;
    trkUE   = pp7_1_trackUE_reco_G;
  }
  if(mode == 16)
  {
    jet     = pPb5_1_jet_reco_Q;
    jet_pPb = pPb5_1_jet_reco_Q;
    trk     = pPb5_1_track_reco_Q;
    trkUE   = pPb5_1_trackUE_reco_Q;
  }
  if(mode == 17)
  {
    jet     = pPb5_1_jet_reco_G;
    jet_pPb = pPb5_1_jet_reco_G;
    trk     = pPb5_1_track_reco_G;
    trkUE   = pPb5_1_trackUE_reco_G;
  }
  if(mode == 18)
  {
    jet     = pp5_1_jet_reco_Q;
    jet_pPb = pp5_1_jet_reco_Q;
    trk     = pp5_1_track_reco_Q;
    trkUE   = pp5_1_trackUE_reco_Q;
  }
  if(mode == 19)
  {
    jet     = pp5_1_jet_reco_G;
    jet_pPb = pp5_1_jet_reco_G;
    trk     = pp5_1_track_reco_G;
    trkUE   = pp5_1_trackUE_reco_G;
  }

  if(mode == 20)
  {
    jet     = pp2_1_jet_gen_Q;
    jet_pPb = pPb5_1_jet_gen_Q;
    trk     = pp2_1_track_gen_Q;
    trkUE   = pp2_1_trackUE_gen_Q;
  }
  if(mode == 21)
  {
    jet     = pp2_1_jet_gen_G;
    jet_pPb = pPb5_1_jet_gen_G;
    trk     = pp2_1_track_gen_G;
    trkUE   = pp2_1_trackUE_gen_G;
  }
  if(mode == 22)
  {
    jet     = pp7_1_jet_gen_Q;
    jet_pPb = pPb5_1_jet_gen_Q;
    trk     = pp7_1_track_gen_Q;
    trkUE   = pp7_1_trackUE_gen_Q;
  }
  if(mode == 23)
  {
    jet     = pp7_1_jet_gen_G;
    jet_pPb = pPb5_1_jet_gen_G;
    trk     = pp7_1_track_gen_G;
    trkUE   = pp7_1_trackUE_gen_G;
  }
  if(mode == 24)
  {
    jet     = pPb5_1_jet_gen_Q;
    jet_pPb = pPb5_1_jet_gen_Q;
    trk     = pPb5_1_track_gen_Q;
    trkUE   = pPb5_1_trackUE_gen_Q;
  }
  if(mode == 25)
  {
    jet     = pPb5_1_jet_gen_G;
    jet_pPb = pPb5_1_jet_gen_G;
    trk     = pPb5_1_track_gen_G;
    trkUE   = pPb5_1_trackUE_gen_G;
  }
  if(mode == 26)
  {
    jet     = pp5_1_jet_gen_Q;
    jet_pPb = pp5_1_jet_gen_Q;
    trk     = pp5_1_track_gen_Q;
    trkUE   = pp5_1_trackUE_gen_Q;
  }
  if(mode == 27)
  {
    jet     = pp5_1_jet_reco_G;
    jet_pPb = pp5_1_jet_reco_G;
    trk     = pp5_1_track_reco_G;
    trkUE   = pp5_1_trackUE_reco_G;
  }
  if(mode==28)
  {
    jet     = pPb5Pbp5_0_jet;
    jet_pPb = pPb5Pbp5_0_jet;
    trk     = pPb5Pbp5_0_track;
    trkUE   = pPb5Pbp5_0_trackUE;
  }
  if(mode==29)
  {
    jet     = pp2_0_jet;
    jet_pPb = pPb5Pbp5_0_jet;
    trk     = pp2_0_track;
    trkUE   = pp2_0_trackUE;
  }
  if(mode==30)
  {
    jet     = pp7_0_jet;
    jet_pPb = pPb5Pbp5_0_jet;
    trk     = pp7_0_track;
    trkUE   = pp7_0_trackUE;
  }
  if(mode == 31)
  {
    jet     = pp2_0_jet;
    jet_pPb = Pbp5_0_jet;
    trk     = pp2_0_track;
    trkUE   = pp2_0_trackUE;
  }

  if(mode == 32)
  {
    jet     = pp7_0_jet;
    jet_pPb = Pbp5_0_jet;
    trk     = pp7_0_track;
    trkUE   = pp7_0_trackUE;
  }
  if(mode == 33)
  {
    jet     = pp2_1_jet_reco;
    jet_pPb = pPb5_1_jet_reco;
    trk     = pp2_1_track_rJgT;
    trkUE   = pp2_1_trackUE_rJgT;
  } 
  if(mode == 34)
  {
    jet     = pp7_1_jet_reco;
    jet_pPb = pPb5_1_jet_reco;
    trk     = pp7_1_track_rJgT;
    trkUE   = pp7_1_trackUE_rJgT;
  } 
  if(mode == 35)
  {
    jet     = pPb5_1_jet_reco;
    jet_pPb = pPb5_1_jet_reco;
    trk     = pPb5_1_track_rJgT;
    trkUE   = pPb5_1_trackUE_rJgT;
  } 
  if(mode == 36)
  {
    jet     = pp5_1_jet_reco;
    jet_pPb = pp5_1_jet_reco;
    trk     = pp5_1_track_rJgT;
    trkUE   = pp5_1_trackUE_rJgT;
  }
  if(mode == 37)
  {
    jet     = pp2_1_jet_gen;
    jet_pPb = pPb5_1_jet_gen;
    trk     = pp2_1_track_gJrT;
    trkUE   = pp2_1_trackUE_gJrT;
  } 
  if(mode == 38)
  {
    jet     = pp7_1_jet_gen;
    jet_pPb = pPb5_1_jet_gen;
    trk     = pp7_1_track_gJrT;
    trkUE   = pp7_1_trackUE_gJrT;
  } 
  if(mode == 39)
  {
    jet     = pPb5_1_jet_gen;
    jet_pPb = pPb5_1_jet_gen;
    trk     = pPb5_1_track_gJrT;
    trkUE   = pPb5_1_trackUE_gJrT;
  } 
  if(mode == 40)
  {
    jet     = pp5_1_jet_gen;
    jet_pPb = pp5_1_jet_gen;
    trk     = pp5_1_track_gJrT;
    trkUE   = pp5_1_trackUE_gJrT;
  } 
  if(mode == 41)
  {
    jet     = pp2_0_jet;
    jet_pPb = pp2_0_jet;
    trk     = pp2_0_track;
    trkUE   = pp2_0_trackUE;
  }
  if(mode == 42)
  {
    jet     = pp7_0_jet;
    jet_pPb = pp7_0_jet;
    trk     = pp7_0_track;
    trkUE   = pp7_0_trackUE;
  }
  if(mode == 43)
  {
    jet     = pp2_1_jet_reco;
    jet_pPb = pp2_1_jet_reco;
    trk     = pp2_1_track_reco;
    trkUE   = pp2_1_trackUE_reco;
  }
  if(mode == 44)
  {
    jet     = pp2_1_jet_reco;
    jet_pPb = pp2_1_jet_reco;
    trk     = pp2_1_track_rJgT;
    trkUE   = pp2_1_trackUE_rJgT;
  }
  if(mode == 45)
  {
    jet     = pp2_1_jet_gen;
    jet_pPb = pp2_1_jet_gen;
    trk     = pp2_1_track_gJrT;
    trkUE   = pp2_1_trackUE_gJrT;
  }
  if(mode == 46)
  {
    jet     = pp2_1_jet_gen;
    jet_pPb = pp2_1_jet_gen;
    trk     = pp2_1_track_gen;
    trkUE   = pp2_1_trackUE_gen;
  }
  if(mode == 47)
  {
    jet     = pp7_1_jet_reco;
    jet_pPb = pp7_1_jet_reco;
    trk     = pp7_1_track_reco;
    trkUE   = pp7_1_trackUE_reco;
  }
  if(mode == 48)
  {
    jet     = pp7_1_jet_reco;
    jet_pPb = pp7_1_jet_reco;
    trk     = pp7_1_track_rJgT;
    trkUE   = pp7_1_trackUE_rJgT;
  }
  if(mode == 49)
  {
    jet     = pp7_1_jet_gen;
    jet_pPb = pp7_1_jet_gen;
    trk     = pp7_1_track_gJrT;
    trkUE   = pp7_1_trackUE_gJrT;
  }
  if(mode == 50)
  {
    jet     = pp7_1_jet_gen;
    jet_pPb = pp7_1_jet_gen;
    trk     = pp7_1_track_gen;
    trkUE   = pp7_1_trackUE_gen;
  }
  return;
}

