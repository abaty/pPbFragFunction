#include "../HiForestAnalysis/hiForest.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include <iostream>

HiForest * h;

void makeSkim()
{
  const char * fileList[2] = {
                             "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pPb_5_02TeV_pA2013/PA2013_HiForest_PromptReco_JSonPPb_forestv77.root",
                             "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pp_2_76TeV_pp2013/PP2013_HiForest_PromptReco_JSon_Jet40Jet60_ppTrack_forestv84.root"}; 

  TFile * outf = new TFile("/export/d00/scratch/abaty/skims/testSkim.root","recreate");
  TTree * track = new TTree("track","track");

  TBranch * b_nTrk = track->Branch("nTrk",NULL,"nTrk/I");
  TBranch * b_trkPt = track->Branch("trkPt",NULL,"trkPt[nTrk]/F");
  TBranch * b_trkEta = track->Branch("trkEta",NULL,"trkEta[nTrk]/F");
  TBranch * b_trkPhi = track->Branch("trkPhi",NULL,"trkPhi[nTrk]/F");
  TBranch * b_trkPtError = track->Branch("trkPtError",NULL,"trkPtError[nTrk]/F");
  TBranch * b_trkDzError1 = track->Branch("trkDzError1",NULL,"trkDzError1[nTrk]/F");
  TBranch * b_trkDz1 = track->Branch("trkDz1",NULL,"trkDz1[nTrk]/F");
  TBranch * b_trkDxyError1 = track->Branch("trkDxyError1",NULL,"trkDxyError1[nTrk]/F");
  TBranch * b_trkDxy1 = track->Branch("trkDxy1",NULL,"trkDxy1[nTrk]/F");
  TBranch * b_highPurity = track->Branch("highPurity",NULL,"highPurity[nTrk]/O");
  TBranch * b_nVtx = track->Branch("nVtx",NULL,"nVtx/I"); 

  
for(int f = 0; f<2; f++)
{
  h = new HiForest(fileList[f],"forest",cPPb,0);
  h->LoadNoTrees();
  h->hasTrackTree = true;

  b_nTrk->SetAddress(&(h->track.nTrk));
  b_trkPt->SetAddress(h->track.trkPt);
  b_trkEta->SetAddress(h->track.trkEta);
  b_trkPhi->SetAddress(h->track.trkPhi);
  b_trkPtError->SetAddress(h->track.trkPtError);
  b_trkDzError1->SetAddress(h->track.trkDzError1);
  b_trkDz1->SetAddress(h->track.trkDz1);
  b_trkDxyError1->SetAddress(h->track.trkDxyError1);
  b_trkDxy1->SetAddress(h->track.trkDxy1);
  b_highPurity->SetAddress(h->track.highPurity);
  b_nVtx->SetAddress(&(h->track.nVtx));

  for(int i = 0; i<3; i++)
  {
    h->GetEntry(i);
    track->Fill();
  }
  track->ResetBranchAddresses();
  h->~HiForest();
  h=NULL;
  delete h;
}
  outf->cd();
  track->Write(); 
}
