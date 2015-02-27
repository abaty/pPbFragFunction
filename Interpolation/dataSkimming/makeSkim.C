#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TMath.h"
#include "TDatime.h"
#include <iostream>
#include "skimUtilities2.h"

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

  const int maxFileSize = 50;
  const int nFiles = 2;
  const char * fileList[nFiles] = {
                                "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pPb_5_02TeV_pA2013/PA2013_HiForest_PromptReco_JSonPPb_forestv72_HLT40_HLT60.root"
                                ,"/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pPb_5_02TeV_pA2013/PA2013_HiForest_PromptReco_JSonPPb_forestv77.root"}; 

  //setting up output skim trees 
  int outFileNum = 0;

  //looping over forests to skim out of
  for(int f = 0; f<3; f++)
  { 
    openInFile(fileList[f%2],mode,isMC);    
    if(f==0) openOutFile(mode,trigger,isMC,date,outFileNum);
    int nEntries = evtIn->GetEntries();
    nEntries = 200;

    for(int i = 0; i<nEntries; i++)
    {
      if(i%10000==0) std::cout << i << "/" << nEntries << std::endl;
      evtIn->GetEntry(i);
      skimIn->GetEntry(i);
      std::cout << f << " " << i << " " << fileSize<< std::endl;
      //event and run selections (veto the other-going way as well as first 7 runs for misalignment)
      if(isMC == 0)
      {
        //if(strcmp(mode,"pPb5") == 0 && (run<210676 || run>=211313)) continue;
        if(strcmp(mode,"Pbp5") == 0 && run<211313) continue;
        if(pHBHENoiseFilter == 0) continue;
      }
      if(pPAcollisionEventSelectionPA == 0 && pcollisionEventSelection == 0) continue; 
 
      //trigger selection
      hltIn->GetEntry(i);
      if(strcmp(trigger,"jet80") == 0 && HLT_PAJet80_NoJetID_v1 == 0) continue;
      if(strcmp(trigger,"jet40") == 0 && HLT_PAJet40_NoJetID_v1 == 0) continue;

      //Filling Trees
      trackIn->GetEntry(i); 
      ak3PFIn->GetEntry(i);
      track->Fill();
      ak3PF->Fill();
      evt->Fill();
      fileSize++; 

      if(fileSize>=maxFileSize)
      {
        closeOutFile();
        outFileNum++;              
        openOutFile(mode,trigger,isMC,date,outFileNum);   
      }
    }
    //cleanup so we can open another forest if needed
    closeInFile();  
  }
  closeOutFile();
}

