#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLorentzVector.h"
#include "HiForestAnalysis/hiForest_gluonfrac7tev.h"
#include <iostream>

void skim2()
{
  TH1D::SetDefaultSumw2();
  TH2D::SetDefaultSumw2();

  const int nbinsFine = 120;

  HiForest * h = new HiForest("/mnt/hadoop/cms/store/user/velicanu/mergedFF_forests/mc/pp_7TeV/0.root","forest",cPP,1);
  h->LoadNoTrees();
  h->hasAk3JetTree = true;
  h->hasSkimTree = true;
  h->hasTrackTree = true;

  TH1D * g7tev = new TH1D("g7tev","g7tev",nbinsFine,0,300);
  TH1D * t7tev = new TH1D("t7tev","t7tev",nbinsFine,0,300);

  int nEntries = h->GetEntries();
  for(int i = 1; i<nEntries; i++)
  {
    h->GetEntry(i);

    for(int j =0; j < h->ak3PF.nref; j++)
    { 
      if(TMath::Abs(h->ak3PF.jteta[j]) > 1) continue;
      if(TMath::Abs(h->ak3PF.refparton_flavor[j]) < 901)
      { 
        double perp = h->ak3PF.rawpt[j];
        double pseudorapidity = h->ak3PF.jteta[j];
        double perp_scale = 1; 

        switch(h->track.nVtx){
          case 1:
          #include "jec_pp7tev_pu1.h"
          break;
          case 2:
          #include "jec_pp7tev_pu2.h"
          break;
          case 3:
          #include "jec_pp7tev_pu3.h"
          break;
          case 4:
          #include "jec_pp7tev_pu4.h"
          break;
          case 5:
          #include "jec_pp7tev_pu5.h"
          break;
          case 6:
          #include "jec_pp7tev_pu6.h"
          break;
          case 7:
          #include "jec_pp7tev_pu7.h"
          break;
          case 8:
          #include "jec_pp7tev_pu8.h"
          break;
          case 9:
          #include "jec_pp7tev_pu9.h"
          break;
          case 10:
          #include "jec_pp7tev_pu10.h"
          break;
          case 11:
          #include "jec_pp7tev_pu11.h"
          break;
          case 12:
          #include "jec_pp7tev_pu12.h"
          break;
        }
        
        double jtpt = perp * perp_scale;

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
