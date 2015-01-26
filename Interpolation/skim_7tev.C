#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLorentzVector.h"
#include "HiForestAnalysis/hiForest_gluonfrac7tev.h"
#include <iostream>
#include "JEC7tev/get7tevPt.h"

void skim2()
{
  TH1D::SetDefaultSumw2();
  TH2D::SetDefaultSumw2();

  const int nbinsFine = 28;

  HiForest * h = new HiForest("/mnt/hadoop/cms/store/user/velicanu/mergedFF_forests/mc/pp_7TeV/0.root","forest",cPP,1);
  h->LoadNoTrees();
  h->hasAk3JetTree = true;
  h->hasSkimTree = true;
  h->hasTrackTree = true;

  TH1D * g7tev = new TH1D("g7tev","g7tev",nbinsFine,60,200);
  TH1D * t7tev = new TH1D("t7tev","t7tev",nbinsFine,60,200);

  int nEntries = h->GetEntries();
  for(int i = 1; i<nEntries; i++)
  {
    h->GetEntry(i);

    for(int j =0; j < h->ak3PF.nref; j++)
    { 
      if(TMath::Abs(h->ak3PF.jteta[j]) > 1) continue;
      if(TMath::Abs(h->ak3PF.refparton_flavor[j]) < 901)
      { 
        double jtpt = get7tevPt(h->ak3PF.rawpt[j], h->ak3PF.jteta[j], h->track.nVtx);

        t7tev->Fill(jtpt);
        if(h->ak3PF.refparton_flavor[j] == 21) g7tev->Fill(jtpt);
      }
    }
  }
  
  TFile * fout = new TFile("gluonFracs.root","update");
  TH1D *  gFrac7tev = (TH1D*) g7tev->Clone("gFrac7tev");
  gFrac7tev->Divide(t7tev);
  gFrac7tev->Write();

  return;
}
