#include "../HiForestAnalysis/hiForest.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TMath.h"
#include <iostream>

HiForest * h;

void makeSkim(const char * mode = "pp2", const char * trigger = "jet80",int isMC = 0)
{
  if(!(strcmp(mode,"pp2")==0 || strcmp(mode,"pp7")==0 || strcmp(mode,"pPb5")==0 || strcmp(mode,"Pbp5")==0))
  {
    std::cout << "invalid mode, terminating execution" << std::endl;
    return;
  }
  if(!((strcmp(trigger,"jet80") == 0 || strcmp(trigger,"jet40") == 0) && !(strcmp(mode,"pp7") == 0)))
  {
    std::cout << "invalid trigger, terminating execution" << std::endl;
    return;
  }

  const char * fileList[3] = {
                             
                             "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pPb_5_02TeV_pA2013/PA2013_HiForest_PromptReco_JSonPPb_forestv77.root",
                             "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pp_2_76TeV_pp2013/PP2013_HiForest_PromptReco_JSon_Jet40Jet60_ppTrack_forestv84.root"}; 

  //setting up output skim trees
  TFile * outf  = new TFile("/export/d00/scratch/abaty/skims/testSkim.root","recreate");
  TTree * track = new TTree("track","track");
  TTree * ak3PF = new TTree("ak3PF","ak3PF");
  TTree * evt   = new TTree("evt","evt");

  TBranch * b_nTrk =         track->Branch("nTrk",NULL,"nTrk/I");
  TBranch * b_trkPt =        track->Branch("trkPt",NULL,"trkPt[nTrk]/F");
  TBranch * b_trkEta =       track->Branch("trkEta",NULL,"trkEta[nTrk]/F");
  TBranch * b_trkPhi =       track->Branch("trkPhi",NULL,"trkPhi[nTrk]/F");
  TBranch * b_trkPtError =   track->Branch("trkPtError",NULL,"trkPtError[nTrk]/F");
  TBranch * b_trkDzError1 =  track->Branch("trkDzError1",NULL,"trkDzError1[nTrk]/F");
  TBranch * b_trkDz1 =       track->Branch("trkDz1",NULL,"trkDz1[nTrk]/F");
  TBranch * b_trkDxyError1 = track->Branch("trkDxyError1",NULL,"trkDxyError1[nTrk]/F");
  TBranch * b_trkDxy1 =      track->Branch("trkDxy1",NULL,"trkDxy1[nTrk]/F");
  TBranch * b_highPurity =   track->Branch("highPurity",NULL,"highPurity[nTrk]/O");
  TBranch * b_nVtx =         track->Branch("nVtx",NULL,"nVtx/I"); 

  TBranch * b_nref =       ak3PF->Branch("nref",NULL,"nref/I");
  TBranch * b_rawpt =      ak3PF->Branch("rawpt",NULL,"rawpt[nref]/F");
  TBranch * b_jtpt =       ak3PF->Branch("jtpt",NULL,"jtpt[nref]/F");
  TBranch * b_jteta =      ak3PF->Branch("jteta",NULL,"jteta[nref]/F");
  TBranch * b_jtphi =      ak3PF->Branch("jtphi",NULL,"jtphi[nref]/F");
  TBranch * b_chargedSum = ak3PF->Branch("chargedSum",NULL,"chargedSum[nref]/F");

  TBranch * b_run =       evt->Branch("run",NULL,"run/I");
  TBranch * b_vz =        evt->Branch("vz",NULL,"vz/F");
  TBranch * b_hiHFplus =  evt->Branch("hiHFplus",NULL,"hiHFplus/F");
  TBranch * b_hiHFminus = evt->Branch("hiHFminus",NULL,"hiHFminus/F");  

  //looping over forests to skim out of
  for(int f = 0; f<2; f++)
  {
    h = new HiForest(fileList[f],"forest",cPPb,0);
    h->LoadNoTrees();
    h->hasEvtTree = true;
    h->hasSkimTree = true;
    h->hasHltTree = true;
 
    //setting skim branch addresses
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

    b_nref->SetAddress(&(h->ak3PF.nref));
    b_rawpt->SetAddress(h->ak3PF.rawpt);
    b_jtpt->SetAddress(h->ak3PF.jtpt);
    b_jteta->SetAddress(h->ak3PF.jteta);
    b_jtphi->SetAddress(h->ak3PF.jtphi);
    b_chargedSum->SetAddress(h->ak3PF.chargedSum);

    b_run->SetAddress(&(h->evt.run));
    b_vz->SetAddress(&(h->evt.vz));
    b_hiHFplus->SetAddress(&(h->evt.hiHFplus));
    b_hiHFminus->SetAddress(&(h->evt.hiHFminus));

    for(int i = 0; i<30; i++)
    {
      h->GetEntry(i);
      //event and run selections (veto the other-going way as well as first 7 runs for misalignment)
      if(isMC == 0)
      {
        if(strcmp(mode,"pPb5") == 0 && (h->evt.run<210676 || h->evt.run>=211313)) continue;
        if(strcmp(mode,"Pbp5") == 0 && h->evt.run<211313) continue;
        if(h->skim.pHBHENoiseFilter == 0) continue;
      }
      std::cout << "passes run and noise filter" << std::endl;
      std::cout << h->skim.pPAcollisionEventSelectionPA<< " " <<h->skim.pcollisionEventSelection<< std::endl;
      if(h->skim.pPAcollisionEventSelectionPA == 0 && h->skim.pcollisionEventSelection == 0) continue;
      std::cout << "passes pPA collsiions" << std::endl;
 
      //trigger selection
      if(strcmp(trigger,"jet80") == 0 && h->hlt.HLT_PAJet80_NoJetID_v1 == 0) continue;
      if(strcmp(trigger,"jet40") == 0 && h->hlt.HLT_PAJet40_NoJetID_v1 == 0) continue;
      std::cout << "passes trigger" << std::endl;

      //Filling Trees
      h->hasTrackTree = true;
      h->hasAk3JetTree = true;
      h->hasSkimTree = false;    
      h->hasHltTree = false;

      h->GetEntry(i);
      track->Fill();
      ak3PF->Fill();
      evt->Fill();
    
      h->hasTrackTree = false;
      h->hasAk3JetTree = false;
      h->hasSkimTree = true;
      h->hasHltTree = true;
    }
 
    //cleaning up forest so that we can open another w/o memory leaks
    track->ResetBranchAddresses();
    h->~HiForest();
    h=NULL;
    delete h;
  }

  //writing output
  outf->cd();
  track->Write();
  ak3PF->Write();
  evt->Write(); 
}
