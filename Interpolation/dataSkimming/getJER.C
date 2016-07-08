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

void getJER(const char * mode = "pp2")
{
  TH1::SetDefaultSumw2();

  int nbinsFine = 28;
  TH1D * recoJER = new TH1D("recoGlu","",104,40,300);
  TH1D * denom = new TH1D("denom","",104,40,300);
//setting up files 
  std::vector<std::string> fileList;
  if(strcmp("pp2",mode)==0) fileList = readInputFileList("pp2MCFiles.txt");
  if(strcmp("pPb5",mode)==0) fileList = readInputFileList("pPbMCFiles.txt");
  if(strcmp("pp7",mode)==0) fileList = readInputFileList("pp7MCFiles.txt");
  int nFiles = fileList.size();

  //pp7 MC reweighting
  int totalEntriesForWeighting[7] = {0};
  if(strcmp(mode, "pp7")==0)
  {
    for(int f=0; f<nFiles; f++)
    { 
      if(f%100 == 0) std::cout << "tabulating entries; file " << f << "/" << nFiles <<std::endl;
      int isGoodFile = openInFileFast(fileList[f].data(),mode,1);
      if( isGoodFile == 0)
      { 
        closeInFileFast(0);
        continue;
      }

      for(int i = 0; i<7; i++)
      {
        if(fileList[f].find(Form("%dto%d",(int)pp7PthatBounds[i],(int)pp7PthatBounds[i+1])) != std::string::npos) totalEntriesForWeighting[i] += trackIn->GetEntries();
      }
      closeInFileFast();
    }
    for(int i = 0 ; i<7; i++) std::cout << pp7PthatBounds[i] << " has " << totalEntriesForWeighting[i] << " entries." <<std::endl;
  }

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
    //nEntries = 50;
    for(int i = 0; i<nEntries; i++)
    {
      if(i%10000==0) std::cout <<"file: " << f << " event: " << i << "/" << nEntries << std::endl;
      skimIn->GetEntry(i);
      if(pPAcollisionEventSelectionPA == 0 && pcollisionEventSelection == 0) continue; 
   
      ak3PFIn->GetEntry(i);
      float boost = 0;
      if(strcmp("pp2",mode)==0)
      {
        if(pthat > pp2PthatBounds[f+1]) continue;
        weight = crossSection2[f]/(float)nEntries;
      }
      if(strcmp("pPb5",mode)==0 || strcmp("Pbp5",mode)==0)
      {
        boost = pPbRapidity;
        if(pthat > pPb5PthatBounds[f+1]) continue; 
        weight = crossSection5[f]/(float)nEntries;
      }
      if(strcmp("pp7",mode)==0)
      {
        for(int k = 0; k<7; k++)
        {
          if(fileList[f].find(Form("%dto%d",(int)pp7PthatBounds[k],(int)pp7PthatBounds[k+1])) != std::string::npos) weight = crossSection7[k]/(float)totalEntriesForWeighting[k];
        }    
      }
       
      for(int j =0; j < nref; j++)
      {  
        if(TMath::Abs(jteta[j]+boost)>1.5) continue;
        double sigma2;
        if(refpt[j]>0 && TMath::Abs(refpt[j]-jtpt[j])<refpt[j])
        {
          sigma2 = TMath::Power((jtpt[j]-refpt[j])/jtpt[j],2);
          recoJER->Fill(jtpt[j],sigma2*weight);
          denom->Fill(jtpt[j],weight);
        }
      } 
    }
    //cleanup so we can open another
    closeInFile();  
  }
  recoJER->Divide(denom);
  recoJER->SetDirectory(0);
  TFile * outputFile = new TFile("jetJER.root","update");
  recoJER->SetName(Form("%s_JER",mode));
  recoJER->Write();
  outputFile->Close();
  delete recoJER;
  delete denom;
}

void getJERs()
{
  getJER("pp2");
  getJER("pPb5");
  getJER("pp7");
}
