#include "TH2D.h"
#include "TH1D.h"
#include "TMath.h"
#include "TRandom.h"
#include "string.h"
#include "TDatime.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include "factorizedPtCorr.h"
#include "SpectraFiles.h"

const double pPbRapidity = 0.4654094531;
const int nJetBins = 120;
const double axis[40] = {
                        0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8,
                        2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4,
                        19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6,
                        120.8, 138, 155.2, 172.4, 189.6, 206.8
                        };

//calculates dr^2 to avoid the slow TMath() Sqrt function
double getdR2(double jet_eta, double jet_phi, double track_eta, double track_phi)
{
  return TMath::Power(jet_eta-track_eta,2)+TMath::Power(acos(cos(jet_phi-track_phi)),2);
}

//calculation of Xi
double getXi(double jet_pt, double jet_eta, double jet_phi, double track_pt, double track_eta, double track_phi)
{
  double xi = -2;
  xi = TMath::Log((jet_pt/track_pt)*TMath::Power(TMath::CosH(jet_eta),2)/(TMath::Cos(track_phi-jet_phi) + TMath::SinH(jet_eta)*TMath::SinH(track_eta)));
  return xi;
}

//modes are pp2,pp7,pPb5,Pbp5
void Spectra(const char* inputJets, const char* inputMB, const char* mode = "pp2", const char* trigger = "jet80", bool isMC = 0,int  jobNum = -1, int typeUE = 2, double jetEtaMin = 0, double jetEtaMax = 1.5)
{
  if(strcmp(mode,"pp2") && strcmp(mode,"pp7") && strcmp(mode,"pPb5") && strcmp(mode,"Pbp5"))
  {
    std::cout << "Invalid mode, modes are pp2, pp7, pPb5, Pbp5" << std::endl;
    return;
  }

  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2(); 
  TDatime * dateTime = new TDatime();
  TRandom * rand = new TRandom(dateTime->GetTime());
  setJetPtRange(mode,trigger);
  const sampleType sType = kPPDATA;
  InitCorrFiles(sType);
  InitCorrHists(sType);

  //for testing code in interactive mode only
  if(jobNum == -1)
  {
    getInputFile("/mnt/hadoop/cms/store/user/abaty/FF_forests/skims/pPb5/data/pPb5jet80_0_20150227_0.root",0);
    if(typeUE==2) getInputFileMix("/mnt/hadoop/cms/store/user/abaty/FF_forests/skims/pPb5/data/pPb5MB_0_20150227_0.root",0);
  }

  getInputFile(inputJets,isMC);
  if(typeUE==2) getInputFileMix(inputMB,isMC);

  h_jet = new TH1D("h_jet","",nJetBins,0,300); 
  h_track = new TH2D("h_track","",nJetBins,0,300,39,axis);
  h_trackUE = new TH2D("h_trackUE","",nJetBins,0,300,39,axis);
  h_track_xi = new TH2D("h_track_xi","",nJetBins,0,300,28,-1.5,5.5);
  h_trackUE_xi = new TH2D("h_trackUE_xi","",nJetBins,0,300,28,-1.5,5.5);

  //boosting
  double boost = 0;
  if(strcmp(mode,"pPb5") == 0) boost = pPbRapidity;
  else if(strcmp(mode,"Pbp5") == 0) boost = -pPbRapidity;
  std::cout << mode << " mode is specified; using a boost of: " << boost << std::endl;

  //variables for mixing
  int startMixEvt = 0;
  int lastMixEvt = 1;
  //if(strcmp(mode, "Pbp5")==0) startMixEvt = 6743253;
  if(typeUE==2) lastMixEvt = trackMix->GetEntries();

  int nEntry = track->GetEntries();
  //nEntry = 20000;
  for(int i=0; i<nEntry; i++)
  {
    getInputEntry(i);
    if(i%10000 == 0) std::cout << i << "/" << nEntry << std::endl;
       
    //finding a MB event to mix with if needed 
    if(typeUE==2)
    {
      int loopIter=0;
      int maxIter = trackMix->GetEntries(); 
      while(true)
      {
        //preventing infinite loop
        loopIter++; 
        if(loopIter == maxIter)
        {
          std::cout << "error finding matching MB event, using random MB event" << std::endl;
          break;
        }            
 
        //finding matching event
        lastMixEvt++;
        if(lastMixEvt>startMixEvt+maxIter) lastMixEvt = startMixEvt;
        evtMix->GetEntry(lastMixEvt);  
        if(strcmp(mode,"pPb5")==0 && TMath::Floor(vzMix)==TMath::Floor(vz) && TMath::Abs(hiHFplusMix-hiHFplus)<5) break;
        else if(strcmp(mode,"Pbp5")==0 && TMath::Floor(vzMix)==TMath::Floor(vz) && TMath::Abs(hiHFminusMix-hiHFminus)<5) break;
        else if(strcmp(mode,"pp2")==0 && TMath::Floor(vzMix)==TMath::Floor(vz)) break;
      }
    }

    //starting jet loop
    for(int j=0; j<nref; j++)
    { 
      if(TMath::Abs(jteta[j]+boost) < jetEtaMin || TMath::Abs(jteta[j]+boost) > jetEtaMax || jtpt[j]<lowJetPtBound || jtpt[j]>=upJetPtBound) continue;          
      h_jet->Fill(jtpt[j]);
     
      for(int t=0; t<nTrk; t++)
      {
        if(trkPt[t] < 0.5 || trkPt[t] > 1e+5 || !highPurity[t] || TMath::Abs(trkEta[t])>2.4 ) continue;
        if(TMath::Abs(trkDxy1[t]/trkDxyError1[t]) > 3 || TMath::Abs(trkDz1[t]/trkDzError1[t]) > 3 || trkPtError[t]/trkPt[t] > 0.1) continue;
        
        //calculating r_min for tracking correction
        double r_min = 9;
        for(int j2 = 0; j2<nref; j2++)
        {
          if(TMath::Abs(jteta[j2])>2 || TMath::Abs(jtpt[j2]) < 50) continue;
          double r_min_temp = TMath::Power(getdR2(jteta[j2],jtphi[j2],trkEta[t],trkPhi[t]),0.5);
          if(r_min_temp < r_min) r_min = r_min_temp;
        }
 
        //Filling track spectrum in jet cone
        if(getdR2(jteta[j]+boost,jtphi[j],trkEta[t]+boost,trkPhi[t]) < 0.3*0.3)
        {
          double trkCorr = factorizedPtCorr(getPtBin(trkPt[t], sType), 1, trkPt[t], trkPhi[t], trkEta[t], r_min, sType);          if(std::isfinite(trkCorr))
          {
            h_track->Fill(jtpt[j],trkPt[t],trkCorr);
            h_track_xi->Fill(jtpt[j],getXi(jtpt[j],jteta[j]+boost,jtphi[j],trkPt[t],trkEta[t]+boost,trkPhi[t]),trkCorr);
          }
        }
     
        //Phi rotated UE subtraction
        //returns either +-1 to rotate clockwise or ccw randomly
        int rotationDirection = 2*(int)rand->Integer(2)-1;

        if(typeUE==0 && getdR2(jteta[j]+boost,jtphi[j]+rotationDirection*TMath::PiOver2(),trkEta[t]+boost,trkPhi[t]) < 0.3*0.3)
        {
          double trkCorr = factorizedPtCorr(getPtBin(trkPt[t], sType), 1, trkPt[t], trkPhi[t], trkEta[t], r_min, sType);
          if(std::isfinite(trkCorr))
          {
            h_trackUE->Fill(jtpt[j],trkPt[t],trkCorr);  
            h_trackUE_xi->Fill(jtpt[j],getXi(jtpt[j],jteta[j]+boost,jtphi[j]+rotationDirection*TMath::PiOver2(),trkPt[t],trkEta[t]+boost,trkPhi[t]),trkCorr);
          }
        }

        //Eta Reflected UE subtraction
        if(typeUE==1 && getdR2(-1*(jteta[j]+boost),jtphi[j],trkEta[t]+boost,trkPhi[t]) < 0.3*0.3)
        {
          double trkCorr = factorizedPtCorr(getPtBin(trkPt[t], sType), 1, trkPt[t], trkPhi[t], trkEta[t], r_min, sType);
          if(std::isfinite(trkCorr))
          {
            h_trackUE->Fill(jtpt[j],trkPt[t],trkCorr); 
            //need to fix xi UE calculation when you have time
            h_trackUE_xi->Fill(jtpt[j],getXi(jtpt[j],-1*(jteta[j]+boost),jtphi[j],trkPt[t],trkEta[t]+boost,trkPhi[t]),trkCorr);
          }
        }
      }

      //UE subtraction w/ MB mixing
      if(typeUE==2)
      {        
        getInputEntryMix(lastMixEvt);
        for(int t = 0; t < nTrkMix; t++)
        {
          if(trkPtMix[t] < 0.5 || trkPtMix[t] > 1e+5 || !highPurityMix[t] || TMath::Abs(trkEtaMix[t])>2.4 ) continue;
          if(TMath::Abs(trkDxy1Mix[t]/trkDxyError1Mix[t]) > 3 || TMath::Abs(trkDz1Mix[t]/trkDzError1Mix[t]) > 3 || trkPtErrorMix[t]/trkPtMix[t] > 0.1) continue;

          //calculating r_min for tracking correction
          double r_min = 9;
          for(int j2 = 0; j2<nrefMix; j2++)
          {
            //may need to fix JEC later, 
            if(TMath::Abs(jtetaMix[j2])>2 || TMath::Abs(jtptMix[j2]) < 50) continue;
            double r_min_temp = TMath::Power(getdR2(jtetaMix[j2],jtphiMix[j2],trkEtaMix[t],trkPhiMix[t]),0.5);
            if(r_min_temp < r_min) r_min = r_min_temp;
          }                                                                          
            
          //Filling track spectrum in jet cone
          if(getdR2(jteta[j]+boost,jtphi[j],trkEtaMix[t]+boost,trkPhiMix[t]) < 0.3*0.3)
          {
            double trkCorr = factorizedPtCorr(getPtBin(trkPtMix[t], sType), 1, trkPtMix[t], trkPhiMix[t], trkEtaMix[t], r_min, sType);
            if(std::isfinite(trkCorr))
            {
              h_trackUE->Fill(jtpt[j],trkPtMix[t],trkCorr);
              h_trackUE_xi->Fill(jtpt[j],getXi(jtpt[j],jteta[j]+boost,jtphi[j],trkPtMix[t],trkEtaMix[t]+boost,trkPhiMix[t]),trkCorr);
            }
          }
        }
      }
    }
  }

  TFile * outf = new TFile(Form("spectra%s%s_%d_%d_%d_%d_%d.root",mode,trigger,jobNum,(int)isMC,(int)typeUE,(int)(10*jetEtaMin),(int)(10*jetEtaMax)),"recreate");
  h_jet->SetDirectory(0);
  h_track->SetDirectory(0);
  h_trackUE->SetDirectory(0);
  h_track_xi->SetDirectory(0);
  h_trackUE_xi->SetDirectory(0);

  h_jet->Write(Form("%s_%d_jet",mode,isMC));
  h_track->Write(Form("%s_%d_track",mode,isMC));
  h_trackUE->Write(Form("%s_%d_trackUE",mode,isMC));
  h_track_xi->Write(Form("%s_%d_track_xi",mode,isMC));
  h_trackUE_xi->Write(Form("%s_%d_trackUE_xi",mode,isMC));
  outf->Close();
}

int main(int argc, const char* argv[])
{
  if(argc != 5)
  {
    std::cout << "Usage: Spectra <fileListJets> <fileListMB> <MCStatus> <job>" << std::endl;
    return 1;
  }
  
  std::string fList = argv[1];
  std::string fListMB = argv[2];
  int MCStatus = std::atoi(argv[3]);
  int job = std::atoi(argv[4]);

  /*if(job==0) job=27;
  else if(job==1) job=26;
  else if(job==2) job=27;*/
 
  std::string buffer, bufferMB;
  std::vector<std::string> listOfFilesJets;
  std::vector<std::string> listOfFilesMB;  

  ifstream inFile(fList.data());
  ifstream inFileMB(fListMB.data());
  std::cout << fList << std::endl;
  std::cout << fListMB << std::endl;
  std::cout << inFile.is_open() << std::endl;
  std::cout << inFileMB.is_open() << std::endl;

  if(!inFile.is_open())
  {
    std::cout << "Error opening jet file. Exiting." <<std::endl;
    return 1;
  }
  else if (!inFileMB.is_open())
  {
    std::cout << "Error opening MB file. Exiting." <<std::endl;
    return 1;
  }
  else
  {
    while(true)
    {
      inFile >> buffer;
      inFileMB >> bufferMB;
      if(inFile.eof()) break;
      if(inFileMB.eof()) break;
      listOfFilesJets.push_back(buffer);
      listOfFilesMB.push_back(bufferMB);
    }
  }

  std::cout << "FileListJets Loaded" << std::endl;
  std::cout << "FileJobJets: " << listOfFilesJets[job] << std::endl;
  std::cout << "FileListMB Loaded" << std::endl;
  std::cout << "FileJobMB: " << listOfFilesMB[job] << std::endl;

  std::string  parsedMode;
  std::string  parsedTrigger;
  if(listOfFilesJets[job].find("pp2") != std::string::npos) parsedMode = "pp2";
  if(listOfFilesJets[job].find("pp7") != std::string::npos) parsedMode = "pp7";
  if(listOfFilesJets[job].find("pPb5") != std::string::npos) parsedMode = "pPb5"; 
  if(listOfFilesJets[job].find("Pbp5") != std::string::npos) parsedMode = "Pbp5";

  if(listOfFilesJets[job].find("jet80_") != std::string::npos) parsedTrigger = "jet80";
  if(listOfFilesJets[job].find("jet40_") != std::string::npos) parsedTrigger = "jet40";
  if(listOfFilesJets[job].find("jet30_") != std::string::npos) parsedTrigger = "jet30";
  if(listOfFilesJets[job].find("jet60_") != std::string::npos) parsedTrigger = "jet60";
  if(listOfFilesJets[job].find("jet110_") != std::string::npos) parsedTrigger = "jet110";

  std::cout << "Results of parsing input files for mode and trigger used:" << std::endl;
  std::cout << "Mode: " <<  parsedMode.data() << "  Trigger: " << parsedTrigger.data() << std::endl;
  
  Spectra(listOfFilesJets[job].data(),listOfFilesMB[job].data(),parsedMode.data(),parsedTrigger.data(),MCStatus,job,3,0,1.5);
  return 0;
}

