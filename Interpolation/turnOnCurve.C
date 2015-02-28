#include "HiForestAnalysis/hiForest.h"
#include <iostream>
#include "TProfile.h"
#include "TH1D.h"
#include "TAttMarker.h"
#include "TStyle.h"
#include "TAttLine.h"
#include "TColor.h"
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TColor.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
//#include "JEC7tev/get7tevPt.h"

void turnOnCurve(int mode = 0)
{
  TH1::SetDefaultSumw2();

  const int nbins = 8; 
  float bins[nbins+2] = {15,30,50,80,120,170,220,280,10000,10000};

  //pp cross sections for 2.76 tev
  /*float crossSection[nbins+1] = {2.034E-01,1.075E-02,1.025E-03,9.865E-05,1.129E-05,1.465E-06,2.837E-07,5.323E-08,0};
  //pPb cross sections for 5.02 tev
  if(mode == 1)
  {
    crossSection[0] = 5.335E-01;
    crossSection[1] = 3.378E-02;
    crossSection[2] = 3.778E-03;
    crossSection[3] = 4.412E-04;
    crossSection[4] = 6.147E-05;
    crossSection[5] = 1.018E-05;
    crossSection[6] = 2.477E-06;
    crossSection[7] = 6.160E-07;
    crossSection[8] = 0;
  }*/
  
  HiForest * h[nbins];
  for(int file = 0; file<8; file++)
  {
    if(mode == 0)
    {
      h[file] = new HiForest(Form("/mnt/hadoop/cms/store/user/dgulhan/pp2013/P01/prod22/Signal_Pythia_pt%d/HiForest_v81_merged01/pt%d_pp2013_P01_prod22_v81_merged_forest_0.root",(int)bins[file], (int)bins[file]),"forest",cPP,1);
    }
    else if(mode==1)
    {
      h[file] = new HiForest(Form("/mnt/hadoop/cms/store/user/dgulhan/pPb/HP04/prod16/Hijing_Pythia_pt%d/HiForest_v77_merged01/pt%d_HP04_prod16_v77_merged_forest_0.root",(int)bins[file],(int)bins[file]),"forest",cPPb,1);
    }
    else if(mode == 2)
    {
      h[file] = new HiForest("/mnt/hadoop/cms/store/user/velicanu/mergedFF_forests/mc/pp_7TeV/0.root","forest",cPP,1);
    }
    h[file]->LoadNoTrees();
    h[file]->hasAk3JetTree = true;
    h[file]->hasSkimTree = true;
    h[file]->hasHltTree = true;
    
    if(mode == 2) 
    {
      h[file]->hasTrackTree = true;
      break;
    }
  }

  TH1D * turnon40 = new TH1D("turnon40","",40,0,200);
  TH1D * turnon80 = new TH1D("turnon80","",40,0,200);
  TH1D * turnon30 = new TH1D("turnon30","",40,0,200);
  TH1D * turnon60 = new TH1D("turnon60","",40,0,200);
  TH1D * turnon110 = new TH1D("turnon110","",40,0,200);
  TH1D * denom = new TH1D("denom","",40,0,200);

  int maxFile = nbins;
  if(mode ==2) maxFile = 1;
  for(int ifile = 0; ifile<maxFile; ifile++)
  {
    float nEntries = h[ifile]->GetEntries();
    for(int i = 0; i<nEntries; i++)
    {
      h[ifile]->GetEntry(i);
      if(i%10000 == 0) std::cout << i << "/" << nEntries << std::endl;
      
      if(!((h[ifile]->skim.pPAcollisionEventSelectionPA == 1 || !(mode==2)*h[ifile]->skim.pcollisionEventSelection == 1)) && h[ifile]->skim.pHBHENoiseFilter == 1) continue;   
      if(mode!=2)
      { 
        if(h[ifile]->hlt.HLT_PAJet40_NoJetID_v1 && TMath::Abs(h[ifile]->ak3PF.jteta[0])<2) turnon40->Fill(h[ifile]->ak3PF.jtpt[0]);//,crossSection[ifile]/nEntries);
        if(h[ifile]->hlt.HLT_PAJet80_NoJetID_v1 && TMath::Abs(h[ifile]->ak3PF.jteta[0])<2) turnon80->Fill(h[ifile]->ak3PF.jtpt[0]);//,crossSection[ifile]/nEntries);
        if(TMath::Abs(h[ifile]->ak3PF.jteta[0])<2) denom->Fill(h[ifile]->ak3PF.jtpt[0]);//,crossSection[ifile]/nEntries);
      }
      else
      {
        double jtpt[100] = {0};
        for(int j = 0; j<h[ifile]->ak3PF.nref; j++)
        {
          jtpt[j] = get7tevPt(h[ifile]->ak3PF.rawpt[j], h[ifile]->ak3PF.jteta[j], h[ifile]->track.nVtx);
        } 

        int leadIndx = 0;
        for(int j = 0; j<h[ifile]->ak3PF.nref; j++)
        {
          if(jtpt[j] > jtpt[leadIndx]) leadIndx = j;
        }

        if(h[ifile]->hlt.HLT_Jet30_v10 && TMath::Abs(h[ifile]->ak3PF.jteta[leadIndx])<2) turnon30->Fill(jtpt[leadIndx]);
        if(h[ifile]->hlt.HLT_Jet60_v10 && TMath::Abs(h[ifile]->ak3PF.jteta[leadIndx])<2) turnon60->Fill(jtpt[leadIndx]);
        if(h[ifile]->hlt.HLT_Jet80_v10 && TMath::Abs(h[ifile]->ak3PF.jteta[leadIndx])<2) turnon80->Fill(jtpt[leadIndx]);
        if(h[ifile]->hlt.HLT_Jet110_v10 && TMath::Abs(h[ifile]->ak3PF.jteta[leadIndx])<2) turnon110->Fill(jtpt[leadIndx]);
        if(TMath::Abs(h[ifile]->ak3PF.jteta[leadIndx])<2) denom->Fill(jtpt[leadIndx]); 
      }
    }
  }

  TGraphAsymmErrors * turnon40Asym;// = new TGraphAsymmErrors(turnon40);
  TGraphAsymmErrors * turnon80Asym;// = new TGraphAsymmErrors(turnon80);
  TGraphAsymmErrors * turnon30Asym;// = new TGraphAsymmErrors(turnon30);
  TGraphAsymmErrors * turnon60Asym;// = new TGraphAsymmErrors(turnon60);
  TGraphAsymmErrors * turnon110Asym;// = new TGraphAsymmErrors(turnon110);

  TCanvas * c2 = new TCanvas("c2","c2",800,600);
  TMultiGraph * mg = new TMultiGraph();
  mg->SetTitle(";lead jet p_{T}^{reco};Efficiency");

  if(mode !=2)
  {
    turnon40Asym = new TGraphAsymmErrors();
    turnon40Asym->SetName("turnon40Asym");
    turnon40Asym->BayesDivide(turnon40,denom);
    for(int i =1; i<41; i++)
    {
      turnon40Asym->SetPointEXlow(i,0);
      turnon40Asym->SetPointEXhigh(i,0);
    }
    turnon40Asym->SetLineColor(1);
    turnon40Asym->SetMarkerSize(0.8);

    turnon80Asym = new TGraphAsymmErrors();
    turnon80Asym->SetName("turnon80Asym");
    turnon80Asym->BayesDivide(turnon80,denom);
    for(int i =1; i<41; i++)
    {
      turnon80Asym->SetPointEXlow(i,0);
      turnon80Asym->SetPointEXhigh(i,0);
    }
    turnon80Asym->SetLineColor(kRed+1);
    turnon80Asym->SetMarkerColor(kRed+1);
    turnon80Asym->SetMarkerSize(0.8);
    mg->Add(turnon40Asym,"");
    mg->Add(turnon80Asym,"");
    mg->Draw("AP");  
    //TLegend * leg = (TLegend*)c2->BuildLegend(0.6,0.2,0.9,0.6);
    TLegend * leg = new TLegend(0.5,0.2,0.9,0.4);
    if(mode==0)leg->AddEntry((TObject*)0,"2.76 TeV PYTHIA","");
    if(mode==1)leg->AddEntry((TObject*)0,"5.02 TeV PYTHIA+HIJING","");
    leg->AddEntry(turnon40Asym,"Jet 40 Trigger","p");
    leg->AddEntry(turnon80Asym,"Jet 80 Trigger","p");
    leg->Draw("same");
    c2->SaveAs(Form("plots/TriggerTurnOn_%d_l1.png",mode));
    c2->SaveAs(Form("plots/TriggerTurnOn_%d_l1.pdf",mode));
  }
  else
  { 
    turnon30Asym = new TGraphAsymmErrors();
    turnon30Asym->SetName("turnon30Asym");
    turnon30Asym->BayesDivide(turnon30,denom);
    for(int i =1; i<41; i++)
    {
      turnon30Asym->SetPointEXlow(i,0);
      turnon30Asym->SetPointEXhigh(i,0);
    }
    turnon30Asym->SetLineColor(1);
    turnon30Asym->SetMarkerSize(0.8); 
    

    turnon60Asym = new TGraphAsymmErrors();
    turnon60Asym->SetName("turnon60Asym");
    turnon60Asym->BayesDivide(turnon60,denom);
    for(int i =1; i<41; i++)
    {
      turnon60Asym->SetPointEXlow(i,0);
      turnon60Asym->SetPointEXhigh(i,0);
    }
    turnon60Asym->SetLineColor(kGreen+1);
    turnon60Asym->SetMarkerColor(kGreen+1);
    turnon60Asym->SetMarkerSize(0.8);

    turnon80Asym = new TGraphAsymmErrors();
    turnon80Asym->SetName("turnon80Asym");
    turnon80Asym->BayesDivide(turnon80,denom);
    for(int i =1; i<41; i++)
    {
      turnon80Asym->SetPointEXlow(i,0);
      turnon80Asym->SetPointEXhigh(i,0);
    }
    turnon80Asym->SetLineColor(kRed+1);
    turnon80Asym->SetMarkerColor(kRed+1);
    turnon80Asym->SetMarkerSize(0.8);

    turnon110Asym = new TGraphAsymmErrors();
    turnon110Asym->SetName("turnon110Asym");
    turnon110Asym->BayesDivide(turnon110,denom);
    for(int i =1; i<41; i++)
    {
      turnon110Asym->SetPointEXlow(i,0);
      turnon110Asym->SetPointEXhigh(i,0);
    }
    turnon110Asym->SetLineColor(kBlue);
    turnon110Asym->SetMarkerColor(kBlue);
    turnon110Asym->SetMarkerSize(0.8);

    mg->Add(turnon30Asym,"");
    mg->Add(turnon60Asym,"");
//    mg->Add(turnon80Asym,"");
    mg->Add(turnon110Asym,"");
    mg->Draw("AP");  
    //TLegend * leg = (TLegend*)c2->BuildLegend(0.6,0.2,0.9,0.6);
    TLegend * leg = new TLegend(0.5,0.2,0.9,0.55);
    leg->AddEntry((TObject*)0,"7 TeV PYTHIA","");
    leg->AddEntry(turnon30Asym,"Jet 30 Trigger","p");
    leg->AddEntry(turnon60Asym,"Jet 60 Trigger","p");
//    leg->AddEntry(turnon80Asym,"Jet 80 Trigger","p");
    leg->AddEntry(turnon110Asym,"Jet 110 Trigger","p");
    leg->Draw("same");
    c2->SaveAs(Form("plots/TriggerTurnOn_%d.png",mode));
    c2->SaveAs(Form("plots/TriggerTurnOn_%d.pdf",mode));
  }
    return;
}
