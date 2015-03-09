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

void getGlu(const char * mode = "pp2")
{
  int nbinsFine = 28;
  TH1D * recoGlu = new TH1D("recoGlu","",nbinsFine,60,200);
  TH1D * recoTot = new TH1D("recoTot","",nbinsFine,60,200);
  TH1D * genGlu = new TH1D("genGlu","",nbinsFine,60,200);
  TH1D * genTot = new TH1D("genTot","",nbinsFine,60,200);
 
//setting up files 
  std::vector<std::string> fileList;
  if(strcmp("pp2",mode)==0) fileList = readInputFileList("pp2MCFiles.txt");
  if(strcmp("pPb5",mode)==0) fileList = readInputFileList("pPb5MCFiles.txt");
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
        if(pthat > pp2PthatBounds[f+2]) continue;
        weight = crossSection2[f]/(float)nEntries;
      }
      if(strcmp("pPb5",mode)==0 || strcmp("Pbp5",mode)==0)
      {
        boost = pPbRapidity;
        if(pthat > pPb5PthatBounds[f+2]) continue; 
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
        if(TMath::Abs(refparton_flavor[j]) < 901)
        {
          recoTot->Fill(jtpt[j],weight);
          if(refparton_flavor[j] == 21) recoGlu->Fill(jtpt[j],weight);
          genTot->Fill(refpt[j],weight);
          if(refparton_flavor[j] == 21) genGlu->Fill(refpt[j],weight);
        }
      } 
    }
    //cleanup so we can open another
    closeInFile();  
  }
  recoGlu->Divide(recoTot);
  genGlu->Divide(genTot);
  recoGlu->SetDirectory(0);
  genGlu->SetDirectory(0);
  TFile * outputFile = new TFile("gluonFracs.root","update");
  recoGlu->SetName(Form("%s_gFrac_recoMC",mode));
  genGlu->SetName(Form("%s_gFrac_genMC",mode));
  recoGlu->Write();
  genGlu->Write();
  outputFile->Close();
  delete recoGlu;
  delete genGlu;
  delete recoTot;
  delete genTot; 
}

void getGluFracs()
{
 // getGlu("pp2");
  getGlu("pPb5");
  getGlu("pp7");
}
