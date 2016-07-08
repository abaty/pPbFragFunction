//written by Austin Baty, 2/27/2015
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TMath.h"
#include "TDatime.h"
#include "TH1D.h"
#include <iostream>
#include "skimUtilities.h"

const double pPbRapidity = 0.4654094531;

void getGlu(const char * mode = "pp2", const char * trigger ="jet40")
{
  TH1::SetDefaultSumw2();

  int nbinsFine = 50;
  TH1D * jet40pPb = new TH1D("jet40pPb","",nbinsFine,0,200);
  TH1D * jet40Pbp = new TH1D("jet40Pbp","",nbinsFine,0,200);
  TH1D * jet80pPb = new TH1D("jet80pPb","",nbinsFine,0,200);
  TH1D * jet80Pbp = new TH1D("jet80Pbp","",nbinsFine,0,200);
 
//setting up files 
  std::vector<std::string> fileList;
  if((strcmp("pPb5",mode)==0 || strcmp("Pbp5",mode)==0) && strcmp(trigger,"jet80")==0) fileList = readInputFileList("pPb5Pbp5_jet80_data_files.txt");
  if((strcmp("pPb5",mode)==0) && strcmp(trigger,"jet40")==0) fileList = readInputFileList("pPb5Pbp5_jet40_data_files.txt");
  if((strcmp("Pbp5",mode)==0) && strcmp(trigger,"jet40")==0) fileList = readInputFileList("pPb5Pbp5_jet40_data_files.txt");
  int nFiles = fileList.size();

//start of skim here 
  //looping over forests to skim out of
  //change f= at 2 spots to change starting point, as well as skim outFileNum
  for(int f = 0; f<nFiles; f++)
  {   
    int isGoodFile = openInFile(fileList[f].data(),mode,1);
    if( isGoodFile == 0)
    {
      closeInFile(0);
      continue;
    }

    int nEntries = ak3PFIn->GetEntries();
    //nEntries = 1;
    for(int i = 0; i<nEntries; i++)
    {
      if(i%10000==0) std::cout <<"file: " << f << " event: " << i << "/" << nEntries << std::endl;
      skimIn->GetEntry(i);
      if((pPAcollisionEventSelectionPA == 0 && pcollisionEventSelection == 0) || pHBHENoiseFilter==0) continue;  
      evtIn->GetEntry(i);
      hltIn->GetEntry(i);
      std::cout << hiHFminus << " " << hiHFplus<< " " << HLT_PAJet40_NoJetID_v1 << std::endl;
      if(run>=211313 && HLT_PAJet40_NoJetID_v1==1) jet40Pbp->Fill(hiHFminus);
      else if(run<211313 && HLT_PAJet40_NoJetID_v1==1) jet40pPb->Fill(hiHFplus);
      if(run>=211313 && HLT_PAJet80_NoJetID_v1==1) jet80Pbp->Fill(hiHFminus);
      else if(run<211313 && HLT_PAJet80_NoJetID_v1==1) jet80pPb->Fill(hiHFplus);
    }
    //cleanup so we can open another
    closeInFile();  
  }
  jet40pPb->SetDirectory(0);
  jet40Pbp->SetDirectory(0);
  jet80pPb->SetDirectory(0);
  jet80Pbp->SetDirectory(0);
  TFile * outfile;
  if(strcmp(trigger,"jet40")==0)
  {
    outfile = TFile::Open("pPbHFDists.root","recreate");
    jet40pPb->Write();
    jet40Pbp->Write();
  }  
  else
  { 
    outfile = TFile::Open("pPbHFDists.root","update");
    jet80pPb->Write();
    jet80Pbp->Write();
  }

  outfile->Close();
}

void getHFPlots()
{
  getGlu("pPb5","jet40");
  getGlu("pPb5","jet80");
}
