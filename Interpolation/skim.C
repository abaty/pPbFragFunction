#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLorentzVector.h"
#include "HiForestAnalysis/hiForest_gluonfrac.h"
#include <iostream>

//mode 0 - 2.76 tev pp
//mode 1 - 5.02 tev pPb

void skim(int mode = 0)
{
  TH1D::SetDefaultSumw2();
  TH2D::SetDefaultSumw2();

  const int nbins = 8;
  const int nbinsFine = 28;
  float bins[nbins+1] = {15,30,50,80,120,170,220,280,10000};

  //pp cross sections for 2.76 tev
  float crossSection[nbins+1] = {2.034E-01,1.075E-02,1.025E-03,9.865E-05,1.129E-05,1.465E-06,2.837E-07,5.323E-08,0};
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
  }

  HiForest * h[nbins];

  for(int file = 0; file < nbins; file++)
  {
    if(mode == 0)
    { 
      h[file] = new HiForest(Form("/mnt/hadoop/cms/store/user/dgulhan/pp2013/P01/prod22/Signal_Pythia_pt%d/HiForest_v81_merged01/pt%d_pp2013_P01_prod22_v81_merged_forest_0.root",(int)bins[file], (int)bins[file]),"forest",cPP,1);
    }
    else
    {
      h[file] = new HiForest(Form("/mnt/hadoop/cms/store/user/dgulhan/pPb/HP04/prod16/Hijing_Pythia_pt%d/HiForest_v77_merged01/pt%d_HP04_prod16_v77_merged_forest_0.root",(int)bins[file],(int)bins[file]),"forest",cPPb,1);
    }
    h[file]->LoadNoTrees();
    h[file]->hasAk3JetTree = true;
    h[file]->hasSkimTree = true;
  }

  TH1D * g2tev = new TH1D("g2tev","g2tev",nbinsFine,60,200);
  TH1D * t2tev = new TH1D("t2tev","t2tev",nbinsFine,60,200);
  TH1D * g2tevgen = new TH1D("g2tevgen","g2tevgen",nbinsFine,60,200);
  TH1D * t2tevgen = new TH1D("t2tevgen","t2tevgen",nbinsFine,60,200);

  TH1D * pthatDistFine = new TH1D("pthatDistFine","pthatDistFine",nbinsFine,60,200);

  for(int file = 0; file<nbins; file++)
  {
    int nEntries = h[file]->GetEntries();
    for(int i = 1; i<nEntries; i++)
    {
      h[file]->GetEntry(i);
      if(h[file]->ak3PF.pthat > bins[file+1]) continue;
      pthatDistFine->Fill(h[file]->ak3PF.pthat, crossSection[file]/(float)nEntries);    

      if(h[file]->skim.pcollisionEventSelection ==0 && mode ==0) continue;
      if(h[file]->skim.pPAcollisionEventSelectionPA ==0 && mode ==1) continue;

      for(int j =0; j < h[file]->ak3PF.nref; j++)
      {     
         
        if(TMath::Abs(h[file]->ak3PF.refparton_flavor[j]) < 901)
        {
          t2tev->Fill(h[file]->ak3PF.jtpt[j],crossSection[file]/(float)nEntries);
          if(h[file]->ak3PF.refparton_flavor[j] == 21) g2tev->Fill(h[file]->ak3PF.jtpt[j],crossSection[file]/(float)nEntries);
          t2tevgen->Fill(h[file]->ak3PF.refpt[j],crossSection[file]/(float)nEntries);
          if(h[file]->ak3PF.refparton_flavor[j] == 21) g2tevgen->Fill(h[file]->ak3PF.refpt[j],crossSection[file]/(float)nEntries);
        } 
      }    
    }
  }

  TFile * fout = new TFile("gluonFracs1.root","update");
  TH1D * gFrac2tev;
  TH1D * gFrac5tev;
  TH1D * gFrac2tevgen;
  TH1D * gFrac5tevgen;
  
  if (mode == 0)
  {
    gFrac2tev = (TH1D*) g2tev->Clone("gFrac2tev_reco");
    gFrac2tev->Divide(t2tev);
    gFrac2tev->Write();
    
    gFrac2tevgen = (TH1D*) g2tevgen->Clone("gFrac2tev_gen");
    gFrac2tevgen->Divide(t2tevgen);
    gFrac2tevgen->Write();
  }
  else 
  {
    gFrac5tev = (TH1D*) g2tev->Clone("gFrac5tev_reco");
    gFrac5tev->Divide(t2tev);
    gFrac5tev->Write();

    gFrac5tevgen = (TH1D*) g2tevgen->Clone("gFrac5tev_gen");
    gFrac5tevgen->Divide(t2tevgen);
    gFrac5tevgen->Write();
  }
  return;
}

