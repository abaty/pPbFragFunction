#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLorentzVector.h"
#include "HiForestAnalysis/hiForest.h"
#include <iostream>

void skim()
{
  TH1D::SetDefaultSumw2();
  TH2D::SetDefaultSumw2();

  const int nbins = 9;
  float crossSection[nbins+1] = {2.034E-01,1.075E-02,1.025E-03,9.865E-05,1.129E-05,1.465E-06,2.837E-07,5.323E-08,5.934E-09,0};
  float bins[nbins+1] = {15,30,50,80,120,170,220,280,370,10000};

  HiForest *  h = new HiForest("/mnt/hadoop/cms/store/user/dgulhan/pPb/HP04/prod16/Signal_Pythia_pt80/HiForest_v77_v2_merged01/pt80_HP04_hiforest77_hiSignal.root","forest",cPP,1);
  h->LoadNoTrees();
  h->hasEvtTree = true;
  h->hasAk3JetTree = true;
  h->hasHltTree = true;
  h->hasSkimTree = true;

  TH1D * g2tev = new TH1D("g2tev","g2tev",100,0,300);
  TH1D * t2tev = new TH1D("t2tev","t2tev",100,0,300);
  TH1D * pthatDist = new TH1D("pthatDist","pthatDist",nbins,bins);
  TH1D * pthatDistFine = new TH1D("pthatDistFine","pthatDistFine",100,0,300);
  TH1D * weights = new TH1D("weights","weights",nbins,bins);


  int nEntries = h->GetEntries();

  for(int i = 1; i<nEntries; i++)
  {
    h->GetEntry(i);
    if(h->skim.pcollisionEventSelection ==0) continue;
    pthatDist->Fill(h->ak3PF.pthat);
  }
  
  for(int i = 4; i<nbins; i++)
  {
    weights->SetBinContent(i+1,(crossSection[i]-crossSection[i+1])*1000000/((float)pthatDist->GetBinContent(i+1)));
  }
  
  for(int i = 1; i<nEntries; i++)
  {
    h->GetEntry(i);
    
    if(h->skim.pcollisionEventSelection ==0 ) continue;
    pthatDistFine->Fill(h->ak3PF.pthat, weights->GetBinContent(weights->FindBin(h->ak3PF.pthat)));    

    for(int j =0; j < h->ak3PF.nref; j++)
    {
      if(h->ak3PF.refparton_flavor[j] > 0)
      {
        t2tev->Fill(h->ak3PF.refpt[j],weights->GetBinContent(weights->FindBin(h->ak3PF.pthat)));
        if(h->ak3PF.refparton_flavor[j] == 21) g2tev->Fill(h->ak3PF.refpt[j],weights->GetBinContent(weights->FindBin(h->ak3PF.pthat)));
      } 
    }    
  }

  TH1D * gFrac2tev = (TH1D*) g2tev->Clone("gFrac2tev");
  gFrac2tev->Divide(t2tev);
  return;
}
