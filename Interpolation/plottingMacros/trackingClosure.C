#include "TH1D.h"
#include "TColor.h"
#include "TAttAxis.h"
#include "TAttLine.h"
#include "TLine.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TAttMarker.h"
#include "TFile.h"
#include "TLatex.h"
#include "TLegend.h"
#include "../loadHistograms.h"

void trackingClosure()
{
  TH1::SetDefaultSumw2();
  TLatex * lat = new TLatex(0.1,0.1,"test");
  lat->SetTextSize(0.06);
  
  TFile * inFilepp2 = TFile::Open(Form("../%s/pp2MC_UE3_0_15.root",filePath));  
  TFile * inFilepp7 = TFile::Open(Form("../%s/pp7MC_UE3_0_15.root",filePath));
  TFile * inFilepPb5 = TFile::Open(Form("../%s/pPb5MC_UE3_0_15.root",filePath));
  TFile * inFilePbp5 = TFile::Open(Form("../%s/Pbp5MC_UE3_0_15.root",filePath));

  TH1D * pp2Reco[4];
  TH1D * pp7Reco[4];
  TH1D * pPb5Reco[4];
  TH1D * Pbp5Reco[4];
  TH1D * pp2Gen[4];
  TH1D * pp7Gen[4];
  TH1D * pPb5Gen[4];
  TH1D * Pbp5Gen[4];

  const char * suffix[4] = {"","_largeEta","_eta","_largePt"}; 

  for(int i = 0; i<4; i++)
  {
    if(i==2) continue;
    pp2Reco[i] = (TH1D*) inFilepp2->Get(Form("totalRecoTRecoJ_Tracking%s",suffix[i]));
    pp7Reco[i] = (TH1D*) inFilepp7->Get(Form("totalRecoTRecoJ_Tracking%s",suffix[i]));
    pPb5Reco[i] = (TH1D*) inFilepPb5->Get(Form("totalRecoTRecoJ_Tracking%s",suffix[i]));
    Pbp5Reco[i] = (TH1D*) inFilePbp5->Get(Form("totalRecoTRecoJ_Tracking%s",suffix[i]));

    pp2Gen[i] = (TH1D*) inFilepp2->Get(Form("totalGenTRecoJ_Tracking%s",suffix[i]));
    pp7Gen[i] = (TH1D*) inFilepp7->Get(Form("totalGenTRecoJ_Tracking%s",suffix[i]));
    pPb5Gen[i] = (TH1D*) inFilepPb5->Get(Form("totalGenTRecoJ_Tracking%s",suffix[i]));
    Pbp5Gen[i] = (TH1D*) inFilePbp5->Get(Form("totalGenTRecoJ_Tracking%s",suffix[i]));

    pp2Reco[i]->Divide(pp2Gen[i]);
    pp7Reco[i]->Divide(pp7Gen[i]);
    pPb5Reco[i]->Add(Pbp5Reco[i]);
    pPb5Gen[i]->Add(Pbp5Gen[i]);
    pPb5Reco[i]->Divide(pPb5Gen[i]);
    
    pp2Reco[i]->SetMaximum(1.3);
    pPb5Reco[i]->SetMaximum(1.3);
    pp7Reco[i]->SetMaximum(1.3);
    pp2Reco[i]->SetMinimum(0.7);
    pPb5Reco[i]->SetMinimum(0.7);
    pp7Reco[i]->SetMinimum(0.7);

    pp2Reco[i]->SetLineWidth(2);
    pPb5Reco[i]->SetLineWidth(2);
    pp7Reco[i]->SetLineWidth(2);
    pp2Reco[i]->SetLineColor(kBlack);
    pPb5Reco[i]->SetLineColor(kBlack);
    pp7Reco[i]->SetLineColor(kBlack);
 
    pp2Reco[i]->SetMarkerStyle(8);
    pPb5Reco[i]->SetMarkerStyle(8);
    pp7Reco[i]->SetMarkerStyle(8);
    pp2Reco[i]->SetMarkerColor(kBlack);
    pPb5Reco[i]->SetMarkerColor(kBlack);
    pp7Reco[i]->SetMarkerColor(kBlack);
    
    pp2Reco[i]->GetYaxis()->SetTitle("N_{trk}^{Reco}/N_{trk}^{Gen}}");
    if(i<2)
    {
      pp2Reco[i]->GetXaxis()->SetTitle("p_{T}^{trk}");
      pPb5Reco[i]->GetXaxis()->SetTitle("p_{T}^{trk}");
      pp7Reco[i]->GetXaxis()->SetTitle("p_{T}^{trk}");
    }
    else
    {
      pp2Reco[i]->GetXaxis()->SetTitle("#eta");
      pPb5Reco[i]->GetXaxis()->SetTitle("#eta");
      pp7Reco[i]->GetXaxis()->SetTitle("#eta");
    }
  }
 
  TCanvas * c1[4];
  for(int i =0; i<4; i++)
  {
    if(i==2) continue;
    if(i!=1)
    {
      c1[i] = new TCanvas(Form("c%d",i),Form("c%d",i),900,400); 
      c1[i]->Divide(3,1,0,0);
      c1[i]->cd(1);
      if(i<2) c1[i]->cd(1)->SetLogx();
      pp2Reco[i]->Draw();
      c1[i]->cd(2);
      if(i<2) c1[i]->cd(2)->SetLogx();
      pPb5Reco[i]->Draw();
      c1[i]->cd(3);
      if(i<2) c1[i]->cd(3)->SetLogx();
      pp7Reco[i]->Draw(); 
    }
    if(i==1)
    {
      c1[i] = new TCanvas(Form("c%d",i),Form("c%d",i),400,400); 
      c1[i]->cd(1);
      if(i<2) c1[i]->cd(1)->SetLogx();
      pPb5Reco[i]->Draw();
    }
  }

  /*inFilepp2->Close();
  inFilepp7->Close();
  inFilepPb5->Close();
  inFilePbp5->Close();*/
}
