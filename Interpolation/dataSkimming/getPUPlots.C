//written by Austin Baty, 2/27/2015
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TMath.h"
#include "TH1D.h"
#include "TDatime.h"
#include <iostream>
#include "skimUtilities.h"

void getPU(const char * mode = "pp7", int isMC = 0)
{
//setting up files
  std::vector<std::string> fileList;
  if(strcmp("pp7",mode)==0) fileList = readInputFileList("pp7Files.txt");
  int nFiles = fileList.size();

  TH1D * nVtx30 = new TH1D("nVtx30",":nVtx:",25,0,25);
  TH1D * nVtx60 = new TH1D("nVtx60",":nVtx:",25,0,25);
  TH1D * nVtx110 = new TH1D("nVtx110",":nVtx:",25,0,25);
  TH1D * nVtxAll = new TH1D("nVtxAll",":nVtx:",25,0,25);
  
//start of skim here 
  //looping over forests to skim out of
  //change f= at 2 spots to change starting point, as well as skim outFileNum
  for(int f = 0; f<5; f++)
  {   
    int isGoodFile = openInFile(fileList[f].data(),mode,isMC);
    if( isGoodFile == 0)
    {
      closeInFile(0);
      continue;
    }

    int nEntries = trackIn->GetEntries();
    //nEntries = 50;
    for(int i = 0; i<nEntries; i++)
    {
      if(i%10000==0) std::cout <<"file: " << f << " event: " << i << "/" << nEntries << std::endl;
      if(strcmp(mode,"pp7")!=0 || !isMC) evtIn->GetEntry(i);
      skimIn->GetEntry(i);

      //event and run selections (veto the other-going way as well as first 7 runs for misalignment)
      if(isMC == 0)
      {
        if(pHBHENoiseFilter == 0) continue;
      }
      if(pPAcollisionEventSelectionPA == 0 && pcollisionEventSelection == 0) continue; 
     
 
      //trigger selection
      hltIn->GetEntry(i);
      trackIn->GetEntry(i);
      if(strcmp(mode,"pp5")!=0)
      {
        if(HLT_Jet30 == 1) nVtx30->Fill(nVtx);
        if(HLT_Jet60 == 1) nVtx60->Fill(nVtx);
        if(HLT_Jet110 == 1) nVtx110->Fill(nVtx);
        if(HLT_Jet30 == 1 || HLT_Jet60 == 1 || HLT_Jet110 == 1) nVtxAll->Fill(nVtx); 
      }
    }
    //cleanup so we can open another
    closeInFile();  
  }
  
  TFile * outputFile = TFile::Open("nVtxDists.root","recreate");
  nVtx30->SetDirectory(0);
  nVtx60->SetDirectory(0);
  nVtx110->SetDirectory(0);
  nVtxAll->SetDirectory(0);
  nVtx30->Write();
  nVtx60->Write();
  nVtx110->Write();
  nVtxAll->Write();
}

