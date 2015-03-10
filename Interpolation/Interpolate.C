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
#include "interpolationErrors.h"
#include <iostream>

//forward declarations
TH1D* getFF_pp(double jetPt_low, double jetPt_high, const char* histTitle, int mode = 0);
void getSpectra(int mode);

TH1D * jet;
TH2D * trk;
TH2D * trkUE;
TH1D * jet_pPb;

//trk pt bins
const int trkBins = 39;
double yAxis[trkBins+1] = {0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6, 120.8, 138, 155.2, 172.4, 189.6, 206.8};

//main execution starts here
void makeFF()
{ 
  TH1D::SetDefaultSumw2();
  TH2D::SetDefaultSumw2();

  //initializing histograms for analysis
  loadHistos();

  for(int i = 0; i < FF_Bins; i++)
  {
    pp2TeV_data[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp2TeV_data_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),0);
    pp7TeV_data[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp7TeV_data_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),1);
    pPb5TeV_data[i]= getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pPb5TeV_data_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),2);
    Pbp5TeV_data[i]= getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("Pbp5TeV_data_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),3);
    pp2TeV_recoMC[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp2TeV_recoMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),4);
    pp7TeV_recoMC[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp7TeV_recoMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),5);
    pPb5TeV_recoMC[i]= getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pPb5TeV_recoMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),6);
    pp2TeV_genMC[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp2TeV_genMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),7);
    pp7TeV_genMC[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp7TeV_genMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),8);
    pPb5TeV_genMC[i]= getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pPb5TeV_genMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),9);    
    pp5TeV_genMC[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp5TeV_genMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),10); 
    pp5TeV_recoMC[i] = getFF_pp(FF_Bound[i],FF_Bound[i+1],Form("pp5TeV_recoMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),11); 
  }
   
  for(int i = 0; i < FF_Bins; i++)
  {
    pp5TeV_interp[i] = new TH1D(Form("pp5TeV_interp_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),";p_{T trk};#frac{1}{N_{jet}} #frac{dN_{trk}}{dp_{t trk}}",trkBins,yAxis);

    //setting jet spectrum to 5TeV for use in the interpolation weighting (only "jet" is used)
    getSpectra(2);
    
    for(int t = 1; t < trkBins+1; t++)
    {
      //number of gluon jets for 2/5/7 MC (proportional to the jet fraction because jet spectra are all reweighted to 5TeV)
      double glu2 = 0;
      double glu5 = 0;
      double glu7 = 0;    
      //double glu2Err = 0;
      //double glu5Err = 0;
      //double glu7Err = 0;

      for(int j = jet->FindBin(FF_Bound[i]); j < jet->FindBin(FF_Bound[i+1]); j++)
      {
        double nJet = jet->GetBinContent(j);
       //double nJetErr = jet->GetBinError(j); 

        glu2 += gluon_2tev_reco->GetBinContent(j)*nJet;
        glu5 += gluon_5tev_reco->GetBinContent(j)*nJet;
        glu7 += gluon_7tev_reco->GetBinContent(j)*nJet;
        //glu2Err += TMath::Power(gluon_2tev_reco->GetBinError(j)*nJet,2)+ TMath::Power(gluon_2tev_reco->GetBinContent(j)*nJetErr,2);
        //glu5Err += TMath::Power(gluon_5tev_reco->GetBinError(j)*nJet,2)+ TMath::Power(gluon_5tev_reco->GetBinContent(j)*nJetErr,2);
        //glu7Err += TMath::Power(gluon_7tev_reco->GetBinError(j)*nJet,2)+ TMath::Power(gluon_7tev_reco->GetBinContent(j)*nJetErr,2);
      }
      //glu2Err = TMath::Power(glu2Err,0.5);
      //glu5Err = TMath::Power(glu5Err,0.5);
      //glu7Err = TMath::Power(glu7Err,0.5);   
 
      double average = ((glu5 - glu7)*pp2TeV_data[i]->GetBinContent(t)+(glu2-glu5)*pp7TeV_data[i]->GetBinContent(t))/(glu2-glu7);
      //double error = getInterpolationError(glu2,glu2Err,glu5,glu5Err,glu7,glu7Err,pp2TeV_data[i]->GetBinContent(t),pp2TeV_data[i]->GetBinError(t),pp7TeV_data[i]->GetBinContent(t),pp7TeV_data[i]->GetBinError(t));
      double error = TMath::Power(TMath::Power((glu5 - glu7)*pp2TeV_data[i]->GetBinError(t)/(glu2-glu7),2)+TMath::Power((glu2-glu5)*pp7TeV_data[i]->GetBinError(t)/(glu2-glu7),2),0.5);
      
      pp5TeV_interp[i]->SetBinContent(t, average);
      pp5TeV_interp[i]->SetBinError(t, error);
    }
  }

  //reversing for Pbp side   
  for(int i = 0; i < FF_Bins; i++)
  {
    pp5TeV_interp_swap[i] = new TH1D(Form("pp5TeV_interp_swap_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),";p_{T trk};#frac{1}{N_{jet}} #frac{dN_{trk}}{dp_{t trk}}",trkBins,yAxis);

    //setting jet spectrum to 5TeV for use in the interpolation weighting (only "jet" is used)
    getSpectra(3);
    
    for(int t = 1; t < trkBins+1; t++)
    {
      //number of gluon jets for 2/5/7 MC (proportional to the jet fraction because jet spectra are all reweighted to 5TeV)
      double glu2 = 0;
      double glu5 = 0;
      double glu7 = 0;    

      for(int j = jet->FindBin(FF_Bound[i]); j < jet->FindBin(FF_Bound[i+1]); j++)
      {
        double nJet = jet->GetBinContent(j); 

        glu2 += gluon_2tev_reco->GetBinContent(j)*nJet;
        glu5 += gluon_5tev_reco->GetBinContent(j)*nJet;
        glu7 += gluon_7tev_reco->GetBinContent(j)*nJet;
      }
    
      double average = ((glu5 - glu7)*pp2TeV_data[i]->GetBinContent(t)+(glu2-glu5)*pp7TeV_data[i]->GetBinContent(t))/(glu2-glu7);
      double error = TMath::Power(TMath::Power((glu5 - glu7)*pp2TeV_data[i]->GetBinError(t)/(glu2-glu7),2)+TMath::Power((glu2-glu5)*pp7TeV_data[i]->GetBinError(t)/(glu2-glu7),2),0.5);
      pp5TeV_interp_swap[i]->SetBinContent(t, average);
      pp5TeV_interp_swap[i]->SetBinError(t, error);
    }
  }

  //MC reco interpolation
  for(int i = 0; i < FF_Bins; i++)
  {
    pp5TeV_interp_recoMC[i] = new TH1D(Form("pp5TeV_interp_recoMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),";p_{T trk};#frac{1}{N_{jet}} #frac{dN_{trk}}{dp_{t trk}}",trkBins,yAxis);

    //setting jet spectrum to 5TeV for use in the interpolation weighting (only "jet" is used)
    getSpectra(6);
    
    for(int t = 1; t < trkBins+1; t++)
    {
      //number of gluon jets for 2/5/7 MC (proportional to the jet fraction because jet spectra are all reweighted to 5TeV)
      double glu2 = 0;
      double glu5 = 0;
      double glu7 = 0;    

      for(int j = jet->FindBin(FF_Bound[i]); j < jet->FindBin(FF_Bound[i+1]); j++)
      {
        double nJet = jet->GetBinContent(j); 

        glu2 += gluon_2tev_reco->GetBinContent(j)*nJet;
        glu5 += gluon_5tev_reco->GetBinContent(j)*nJet;
        glu7 += gluon_7tev_reco->GetBinContent(j)*nJet;
      }
    
      double average = ((glu5 - glu7)*pp2TeV_recoMC[i]->GetBinContent(t)+(glu2-glu5)*pp7TeV_recoMC[i]->GetBinContent(t))/(glu2-glu7);
      double error = TMath::Power(TMath::Power((glu5 - glu7)*pp2TeV_recoMC[i]->GetBinError(t)/(glu2-glu7),2)+TMath::Power((glu2-glu5)*pp7TeV_recoMC[i]->GetBinError(t)/(glu2-glu7),2),0.5);
      pp5TeV_interp_recoMC[i]->SetBinContent(t, average);
      pp5TeV_interp_recoMC[i]->SetBinError(t, error);
    }
  }

   
  //MCgen interpolation
  for(int i = 0; i < FF_Bins; i++)
  {
    pp5TeV_interp_genMC[i] = new TH1D(Form("pp5TeV_interp_genMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]),";p_{T trk};#frac{1}{N_{jet}} #frac{dN_{trk}}{dp_{t trk}}",trkBins,yAxis);

    //setting jet spectrum to 5TeV for use in the interpolation weighting (only "jet" is used)
    getSpectra(9);
    
    for(int t = 1; t < trkBins+1; t++)
    {
      //number of gluon jets for 2/5/7 MC (proportional to the jet fraction because jet spectra are all reweighted to 5TeV)
      double glu2 = 0;
      double glu5 = 0;
      double glu7 = 0;    

      for(int j = jet->FindBin(FF_Bound[i]); j < jet->FindBin(FF_Bound[i+1]); j++)
      {
        double nJet = jet->GetBinContent(j); 

        glu2 += gluon_2tev_gen->GetBinContent(j)*nJet;
        glu5 += gluon_5tev_gen->GetBinContent(j)*nJet;
        glu7 += gluon_7tev_gen->GetBinContent(j)*nJet;
      }
    
      double average = ((glu5 - glu7)*pp2TeV_genMC[i]->GetBinContent(t)+(glu2-glu5)*pp7TeV_genMC[i]->GetBinContent(t))/(glu2-glu7);
      double error = TMath::Power(TMath::Power((glu5 - glu7)*pp2TeV_genMC[i]->GetBinError(t)/(glu2-glu7),2)+TMath::Power((glu2-glu5)*pp7TeV_genMC[i]->GetBinError(t)/(glu2-glu7),2),0.5);
      pp5TeV_interp_genMC[i]->SetBinContent(t, average);
      pp5TeV_interp_genMC[i]->SetBinError(t, error);
    }
  }

  for(int i = 0; i < FF_Bins; i++)
  {
    pPb_FF[i] = (TH1D*) pPb5TeV_data[i]->Clone(Form("pPb_FF_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]));
    pPb_FF[i]->Divide(pp5TeV_interp[i]);
    Pbp_FF[i] = (TH1D*) Pbp5TeV_data[i]->Clone(Form("Pbp_FF_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]));
    Pbp_FF[i]->Divide(pp5TeV_interp_swap[i]);
    pPb_FF_recoMC[i] = (TH1D*) pPb5TeV_recoMC[i]->Clone(Form("pPb_FF_recoMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]));
    pPb_FF_recoMC[i]->Divide(pp5TeV_interp_recoMC[i]);
    pPb_FF_genMC[i] = (TH1D*) pPb5TeV_genMC[i]->Clone(Form("pPb_FF_genMC_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]));
    pPb_FF_genMC[i]->Divide(pp5TeV_interp_genMC[i]);
  }
 
  TFile * outfile = new TFile("FragmentationFunctionsUE3.root","recreate");
  for(int i = 0; i < FF_Bins; i++)
  {
    pp2TeV_data[i]->Write();
    pp7TeV_data[i]->Write();
    pPb5TeV_data[i]->Write();
    Pbp5TeV_data[i]->Write();

    pp2TeV_recoMC[i]->Write();
    pp7TeV_recoMC[i]->Write();
    pPb5TeV_recoMC[i]->Write();
    pp2TeV_genMC[i]->Write();
    pp7TeV_genMC[i]->Write();
    pPb5TeV_genMC[i]->Write();

    pp5TeV_interp[i]->Write();
    pp5TeV_interp_swap[i]->Write();
    pp5TeV_interp_recoMC[i]->Write();
    pp5TeV_interp_genMC[i]->Write();

    pp5TeV_genMC[i]->Write();
    pp5TeV_recoMC[i]->Write();

    pPb_FF[i]->Write();
    Pbp_FF[i]->Write();   
    pPb_FF_recoMC[i]->Write();
    pPb_FF_genMC[i]->Write();
  }

  //handing it over to a plotting macro
  makePlots();  
}


//modes: 0 - 2.76 TeV Data
//       1 - 7    TeV Data
//       2 - 5    TeV pPb Data
TH1D* getFF_pp(double jetPt_low, double jetPt_high, const char* histTitle, int mode)
{
  TH1D * FF = new TH1D(histTitle,";p_{T trk};#frac{1}{N_{jet}} #frac{dN_{trk}}{dp_{t trk}}",trkBins ,yAxis);

  getSpectra(mode);

  //looping over bins in Trk pt
    for(int t = 1; t < trkBins+1; t++)
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
  return;
}

