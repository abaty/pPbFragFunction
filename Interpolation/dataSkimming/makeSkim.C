//written by Austin Baty, 2/27/2015
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
  if(!((strcmp(trigger,"jet80") == 0 || strcmp(trigger,"jet40") == 0 || strcmp(trigger,"MB") == 0) && !(strcmp(mode,"pp7") == 0)))
  {
    std::cout << "invalid trigger, terminating execution" << std::endl;
    return;
  }
  if(!((strcmp(trigger,"jet30") == 0 || strcmp(trigger,"jet60") == 0 || strcmp(trigger,"110") == 0 || strcmp(trigger,"MB")) && strcmp(mode,"pp7") == 0))
  {
    std::cout << "invalid trigger, terminating execution" << std::endl;
    return;
  }
  //event counters to check how many events we use/cut out
  int totalEvents =0, afterRunCut = 0, afterNoiseCut = 0, afterHLTCut = 0;

  //date execution started for labeling output files
  TDatime * time = new TDatime();
  int date = time->GetDate();

  //some parameters for  files
  //max output file size
  const int maxFileSize = 200000;
  int nFiles = 1;
  if(isMC)
  {
    if(strcmp(mode,"pp2")==0) nFiles = npp2MC;
    if(strcmp(mode,"pPb5")==0 || strcmp(mode,"Pbp5")==0) nFiles = npPb5MC;
  } 

//setting up files 
  const char * fileList[nFiles];
  if(isMC)
  {
    if(strcmp("pp2",mode)==0)
    {
      for(int file=0; file<nFiles; file++) fileList[file] = Form("/mnt/hadoop/cms/store/user/dgulhan/pp2013/P01/prod22/Signal_Pythia_pt%d/HiForest_v81_merged01/pt%d_pp2013_P01_prod22_v81_merged_forest_0.root",(int)pp2PthatBounds[file],(int)pp2PthatBounds[file]);
    }
    else if(strcmp("pPb5",mode)==0 || strcmp("Pbp5",mode)==0)
    {
      for(int file=0; file<nFiles; file++) fileList[file] = Form("/mnt/hadoop/cms/store/user/dgulhan/pPb/HP04/prod16/Hijing_Pythia_pt%d/HiForest_v77_merged01/pt%d_HP04_prod16_v77_merged_forest_0.root",(int)pPb5PthatBounds[file],(int)pPb5PthatBounds[file]);
    }
  }
  else 
  {
    if((strcmp("pPb5",mode)==0 || strcmp("Pbp5",mode)==0) && strcmp(trigger,"jet80")==0) fileList[0] = "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pPb_5_02TeV_pA2013/PA2013_HiForest_PromptReco_JSonPPb_forestv77.root"; 
    if((strcmp("pPb5",mode)==0 || strcmp("Pbp5",mode)==0) && strcmp(trigger,"jet40")==0) fileList[0] = "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pPb_5_02TeV_pA2013/PA2013_HiForest_PromptReco_JSonPPb_forestv72_HLT40_HLT60.root";
    if((strcmp("pPb5",mode)==0 || strcmp("Pbp5",mode)==0) && strcmp(trigger,"MB")==0) fileList[0] =  "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pPb_5_02TeV_pA2013/PA2013_HiForest_PromptReco_KrisztianMB_JSonPPb_forestv84.root";
    if(strcmp("pp2",mode)==0 && strcmp(trigger,"jet80")==0) fileList[0] =  "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pp_2_76TeV_pp2013/PP2013_HiForest_PromptReco_JsonPP_Jet80_PPReco_forestv82.root";
    if(strcmp("pp2",mode)==0 && strcmp(trigger,"jet40")==0) fileList[0] = "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pp_2_76TeV_pp2013/PP2013_HiForest_PromptReco_JSon_Jet40Jet60_ppTrack_forestv84.root";
    if(strcmp("pp2",mode)==0 && strcmp(trigger,"MB")==0) fileList[0] = "/mnt/hadoop/cms/store/user/luck/pp_minbiasSkim_forest_53x_2013-08-15-0155/pp_minbiasSkim_forest_53x_2013-08-15-0155.root";
  }


//start of skim here 
  int outFileNum = 0;
  //looping over forests to skim out of
  for(int f = 0; f<nFiles; f++)
  { 
    openInFile(fileList[f],mode,isMC);    
    if(f==0) openOutFile(mode,trigger,isMC,date,outFileNum);
    
    int nEntries = evtIn->GetEntries();
    //nEntries = 50;
    for(int i = 0; i<nEntries; i++)
    {
      totalEvents++;
      if(i%10000==0) std::cout <<"file: " << f << " event: " << i << "/" << nEntries << std::endl;
      evtIn->GetEntry(i);
      skimIn->GetEntry(i);

      //event and run selections (veto the other-going way as well as first 7 runs for misalignment)
      if(isMC == 0)
      {
        if(strcmp(mode,"pPb5") == 0 && (run<210676 || run>=211313)) continue;
        if(strcmp(mode,"Pbp5") == 0 && run<211313) continue;
        afterRunCut++;
        if(pHBHENoiseFilter == 0) continue;
        afterNoiseCut++
      }
      if(pPAcollisionEventSelectionPA == 0 && pcollisionEventSelection == 0) continue; 
 
      //trigger selection
      hltIn->GetEntry(i);
      if(strcmp(trigger,"jet80") == 0 && HLT_PAJet80_NoJetID_v1 == 0) continue;
      if(strcmp(trigger,"jet40") == 0 && HLT_PAJet40_NoJetID_v1 == 0) continue;
      if(strcmp(trigger,"MB") == 0 && HLT_PAZeroBiasPixel_SingleTrack_v1 == 0) continue;
      afterHLTCut++;

      //Filling Trees 
      trackIn->GetEntry(i);   
      ak3PFIn->GetEntry(i);

      if(isMC)
      {
        if(strcmp("pp2",mode)==0)
        {
          if(pthat > pp2PthatBounds[f+2]) continue;
          weight = crossSection2[f]/(float)nEntries;
        }
        if(strcmp("pPb5",mode)==0 || strcmp("Pbp5",mode)==0)
        {
          if(pthat > pPb5PthatBounds[f+2]) continue; 
          weight = crossSection5[f]/(float)nEntries;
        }
      }

      track->Fill();
      ak3PF->Fill();
      evt->Fill();
      fileSize++; 
      //open a new output file if the old one is "full"
      if(fileSize>=maxFileSize)
      {
        closeOutFile();
        std::cout << "Filled file " << outFileNum << ". Opening new file." << std::endl;
        outFileNum++;              
        openOutFile(mode,trigger,isMC,date,outFileNum);   
      }
    }
    //cleanup so we can open another
    closeInFile();  
  }
  closeOutFile();

  //output number of files used
  std::cout << "Total Events scanned: " << totalEvents << std::endl;
  std::cout << "Total Events after Run cuts " << afterRunCut << std::endl;
  std::cout << "Total Events after Noise cuts: " << afterNoiseCut << std::endl;
  std::cout << "Total Events after HLT cuts: " << afterHLTCut << std::endl;
}

