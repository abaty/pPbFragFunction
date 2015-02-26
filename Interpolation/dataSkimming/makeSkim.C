#include "../HiForestAnalysis/hiForest.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TMath.h"
#include "TDatime.h"
#include <iostream>
#include "skimUtilities.h"

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

  TDatime * time = new TDatime();
  int date = time->GetDate();

  const int maxFileSize = 500;
  const int nFiles = 2;
  const char * fileList[nFiles] = {
                                "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pPb_5_02TeV_pA2013/PA2013_HiForest_PromptReco_JSonPPb_forestv72_HLT40_HLT60.root"
                                ,"/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pPb_5_02TeV_pA2013/PA2013_HiForest_PromptReco_JSonPPb_forestv77.root"}; 

  //setting up output skim trees 
  int outFileNum = 0;
  setupOutputFile(mode,trigger,isMC,date,outFileNum);  

  //looping over forests to skim out of
  for(int f = 0; f<nFiles; f++)
  { 
    openForestFile(fileList[f],mode,isMC);    
    int nEntries = h->GetEntries();
    nEntries = 1000;

    for(int i = 0; i<nEntries; i++)
    {
      if(i%10000==0) std::cout << i << "/" << nEntries << std::endl;
      h->GetEntry(i);

      //event and run selections (veto the other-going way as well as first 7 runs for misalignment)
      if(isMC == 0)
      {
        //if(strcmp(mode,"pPb5") == 0 && (h->evt.run<210676 || h->evt.run>=211313)) continue;
        if(strcmp(mode,"Pbp5") == 0 && h->evt.run<211313) continue;
        if(h->skim.pHBHENoiseFilter == 0) continue;
      }
      if(h->skim.pPAcollisionEventSelectionPA == 0 && h->skim.pcollisionEventSelection == 0) continue; 
 
      //trigger selection
      if(strcmp(trigger,"jet80") == 0 && h->hlt.HLT_PAJet80_NoJetID_v1 == 0) continue;
      if(strcmp(trigger,"jet40") == 0 && h->hlt.HLT_PAJet40_NoJetID_v1 == 0) continue;

      //Filling Trees
      h->hasTrackTree = true;
      h->hasAk3JetTree = true;
      h->hasSkimTree = false;    
      h->hasHltTree = false;

      h->GetEntry(i); 
      track->Fill();
      ak3PF->Fill();
      evt->Fill();
      fileSize++;    

      h->hasTrackTree = false;
      h->hasAk3JetTree = false;
      h->hasSkimTree = true;
      h->hasHltTree = true;
     
      if(fileSize>=maxFileSize)
      {
        closeOutputFile();
        outFileNum++;              
        setupOutputFile(mode,trigger,isMC,date,outFileNum);   
      }
    }
    //cleanup so we can open another forest if needed
    track->ResetBranchAddresses();
    ak3PF->ResetBranchAddresses();
    evt->ResetBranchAddresses();
    closeForestFile(); 
  }
  closeOutputFile();
}

