//written by Austin Baty, 2/27/2015
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TMultiGraph.h"
#include "TTree.h"
#include "TBranch.h"
#include "TMath.h"
#include "TDatime.h"
#include "TH1D.h"
#include <iostream>
#include "skimUtilities.h"

const double pPbRapidity = 0.4654094531;

void makeTurnOnCurves(const char * mode = "pp2")
{
  TH1::SetDefaultSumw2();

  int nbinsFine = 28;
  TH1D * num40 = new TH1D("num40","",nbinsFine,0,140);
  TH1D * num80 = new TH1D("num80","",nbinsFine,0,140);
  TH1D * denom40 = new TH1D("denom40","",nbinsFine,0,140);
  TH1D * denom80 = new TH1D("denom80","",nbinsFine,0,140);
 
//setting up files 
  std::vector<std::string> fileList;
  if(strcmp("pp2",mode)==0) fileList.push_back("/mnt/hadoop/cms/store/user/luck/pp_minbiasSkim_forest_53x_2013-08-15-0155/pp_minbiasSkim_forest_53x_2013-08-15-0155.root");
  if(strcmp("pPb5",mode)==0) fileList.push_back("/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pPb_5_02TeV_pA2013/PA2013_HiForest_PromptReco_KrisztianMB_JSonPPb_forestv84.root");
  //if(strcmp("pp7",mode)==0) fileList = readInputFileList("pp7MCFiles.txt");
  int nFiles = fileList.size();

//start of skim here 
  //looping over forests to skim out of
  //change f= at 2 spots to change starting point, as well as skim outFileNum
  for(int f = 0; f<nFiles; f++)
  {   
    int isGoodFile = openInFile(fileList[f].data(),mode,0);
    if( isGoodFile == 0)
    {
      closeInFile(0);
      continue;
    }

    int nEntries = ak3PFIn->GetEntries();
   // nEntries = 5000000;
    for(int i = 0; i<nEntries; i++)
    {
      if(i%10000==0) std::cout <<"file: " << f << " event: " << i << "/" << nEntries << std::endl;
      skimIn->GetEntry(i);
      hltIn->GetEntry(i);
      if((pPAcollisionEventSelectionPA == 0 && pcollisionEventSelection == 0) || pHBHENoiseFilter==0) continue; 
   
      ak3PFIn->GetEntry(i);
      float boost = 0;
      if(strcmp("pPb5",mode)==0 || strcmp("Pbp5",mode)==0)
      {
        boost = pPbRapidity;
      }

      //only using prescale 1 data       
      /*if(nref>0 && HLT_PAJet40_NoJetID_v1==1 && HLT_PAJet40_NoJetID_v1_Prescl==1) num40->Fill(jtpt[0],HLT_PAJet40_NoJetID_v1_Prescl);
      if(nref>0 && HLT_PAJet80_NoJetID_v1==1 && HLT_PAJet80_NoJetID_v1_Prescl==1) num80->Fill(jtpt[0],HLT_PAJet80_NoJetID_v1_Prescl);
      if(nref>0 && HLT_PAJet40_NoJetID_v1_Prescl==1) denom40->Fill(jtpt[0]);
      if(nref>0 && HLT_PAJet80_NoJetID_v1_Prescl==1) denom80->Fill(jtpt[0]);
*/
      //weighting by prescale
      if(nref>0 && HLT_PAJet40_NoJetID_v1==1) num40->Fill(jtpt[0],HLT_PAJet40_NoJetID_v1_Prescl);
      if(nref>0 && HLT_PAJet80_NoJetID_v1==1) num80->Fill(jtpt[0],HLT_PAJet80_NoJetID_v1_Prescl);
      if(nref>0) denom40->Fill(jtpt[0]);
      if(nref>0) denom80->Fill(jtpt[0]);

    }
    //cleanup so we can open another
    closeInFile();  
  }
/*
  for(int i=1; i<num40->GetSize() ;i++)
  {
    if(num40->GetBinContent(i)>1.00001*denom40->GetBinContent(i))
    {
      num40->SetBinContent(i,0);
      denom40->SetBinContent(i,0);
      num40->SetBinError(i,0);
      denom40->SetBinError(i,0);
    }
  }*/

  TGraphAsymmErrors * turnon40Asym;
  TGraphAsymmErrors * turnon80Asym;
  TCanvas * c2 = new TCanvas("c2","c2",800,600);
  TMultiGraph * mg = new TMultiGraph();
  mg->SetTitle(";lead jet p_{T}^{reco};Efficiency");

  turnon40Asym = new TGraphAsymmErrors();
  turnon40Asym->SetName("turnon3Asym");
  turnon40Asym->BayesDivide(num40,denom40);
  for(int i =1; i<41; i++)
  {
    turnon40Asym->SetPointEXlow(i,0);
    turnon40Asym->SetPointEXhigh(i,0);
  }
  turnon40Asym->SetLineColor(kRed+1);
  turnon40Asym->SetMarkerColor(kRed+1);
  turnon40Asym->SetMarkerSize(0.8);

  turnon80Asym = new TGraphAsymmErrors();
  turnon80Asym->SetName("turnon4Asym");
  turnon80Asym->BayesDivide(num80,denom80);
  for(int i =1; i<41; i++)
  {
    turnon80Asym->SetPointEXlow(i,0);
    turnon80Asym->SetPointEXhigh(i,0);
  }
  turnon80Asym->SetLineColor(kBlue+1);
  turnon80Asym->SetMarkerColor(kBlue+1);
  turnon80Asym->SetMarkerSize(0.8);

  mg->Add(turnon40Asym,"");
  //mg->Add(turnon80Asym,"");

  mg->Draw("AP");

  TLegend * leg = new TLegend(0.55,0.2,0.9,0.4);
  if(strcmp(mode,"pp2")==0) leg->AddEntry((TObject*)0,"2.76 TeV MB pp","");
  if(strcmp(mode,"pPb5")==0) leg->AddEntry((TObject*)0,"5.02 TeV MB pPb","");
  if(strcmp(mode,"pp7")==0) leg->AddEntry((TObject*)0,"7 TeV MB pp","");
  leg->AddEntry(turnon40Asym,"Jet40 Trigger","p");
  //leg->AddEntry(turnon80Asym,"Jet80 Trigger","p");
  leg->Draw("same");

  c2->SaveAs(Form("../plots/TriggerTurnOnMB_allprescale%s.png",mode));
  c2->SaveAs(Form("../plots/TriggerTurnOnMB_allprescale%s.pdf",mode));
}
