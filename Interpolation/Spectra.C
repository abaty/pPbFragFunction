#include "HiForestAnalysis/hiForest.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TMath.h"
#include "TRandom.h"
#include "string.h"
#include <iostream>
#include <cmath>
//#include "get7tevPt.h"
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
double getXi(double jetPt, double jetEta, double jetPhi, double trkPt, double trkEta, double trkPhi)
{
  double xi = -2;
  xi = TMath::Log((jetPt/trkPt)*TMath::Power(TMath::CosH(jetEta),2)/(TMath::Cos(trkPhi-jetPhi) + TMath::SinH(jetEta)*TMath::SinH(trkEta)));
  return xi;
}

//modes are pp2,pp7,pPb5,Pbp5
void Spectra(const char* mode = "pp2", int typeUE = 0, double jetEtaMin = 0, double jetEtaMax = 1.5, bool isMC  = 0, int jobNum = 0, int nJobs = 1)
{
  if(strcmp(mode,"pp2") && strcmp(mode,"pp7") && strcmp(mode,"pPb5") && strcmp(mode,"Pbp5"))
  {
    std::cout << "Invalid mode, modes are pp2, pp7, pPb5, Pbp5" << std::endl;
    return;
  }

  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  TRandom * rand = new TRandom(23);
  const sampleType sType = kPPDATA;
  InitCorrFiles(sType);
  InitCorrHists(sType);
 
  int nFiles = 0;
  if(strcmp(mode,"pp2") == 0) nFiles = npp2Files;
  else if(strcmp(mode,"pPb5") == 0) nFiles = npPb5Files;
  else if(strcmp(mode,"Pbp5") == 0) nFiles = nPbp5Files;
  else if(strcmp(mode, "pp7") == 0) nFiles = npp7Files;
  for(int f = 0; f<nFiles; f++)
  {
    if(strcmp(mode,"pp2") == 0)       h[f] = new HiForest(pp2File[f],"forest",cPP,0);
    else if(strcmp(mode,"pPb5") == 0) h[f] = new HiForest(pPb5File[f],"forest",cPPb,0);
    else if(strcmp(mode,"Pbp5") == 0) h[f] = new HiForest(Pbp5File[f],"forest",cPPb,0);
    else if(strcmp(mode,"pp7") ==0 )  h[f] = new HiForest(pp7File[f],"forest",cPP,0);

    h[f]->LoadNoTrees();
    h[f]->hasAk3JetTree = true;
    h[f]->hasTrackTree = true;
    h[f]->hasHltTree = true;
    h[f]->hasSkimTree = true;
    h[f]->hasEvtTree = true;
  }

  if(typeUE==2)
  {
    if(strcmp(mode,"pPb5")==0 || strcmp(mode,"Pbp5")==0) mix = new HiForest("/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pPb_5_02TeV_pA2013/PA2013_HiForest_PromptReco_KrisztianMB_JSonPPb_forestv84.root","forest",cPPb,0);
    else if(strcmp(mode,"pp2")==0) mix = new HiForest("/mnt/hadoop/cms/store/user/luck/pp_minbiasSkim_forest_53x_2013-08-15-0155/pp_minbiasSkim_forest_53x_2013-08-15-0155.root","forest",cPP,0);
    mix->LoadNoTrees();
    mix->hasEvtTree = true;
    mix->hasSkimTree = true;
  }

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
  if(strcmp(mode, "Pbp5")==0) startMixEvt = 6743253;
  int lastMixEvt = startMixEvt;

  for(int f=0; f<nFiles; f++)
  {
    int nEntry = h[f]->GetEntries();
    int startNum = jobNum;
    //adding manual run no cuts to speed up pPb5/Pbp5 data parsing    
    if(strcmp(mode, "Pbp5")==0 && f==0) startNum += 5829747;
    if(strcmp(mode, "Pbp5")==0 && f==1) startNum += 2422139;
 
    if(strcmp(mode, "pPb5")==0 && f==0) nEntry = 5829747;
    if(strcmp(mode, "pPb5")==0 && f==1) nEntry = 2422139;
 
    //if(nEntry-startNum>500000) nEntry = startNum+500000;
    for(int i=startNum; i<nEntry; i+=nJobs)
    {
      h[f]->GetEntry(i);
      if(i%10000 == jobNum) std::cout << i << "/" << nEntry << std::endl;

      int trigger = 1;
      trigger = setTrigger(mode,f,h[f]); 
      if(!trigger) continue;
//!!!!!!
// remove the strcmp !((mode),pp7) when you get a pp7 forest w/ pcollisionEventSelection
//!!!!!!
      
      if(!((h[f]->skim.pPAcollisionEventSelectionPA == 1 || !(strcmp(mode,"pp7")*h[f]->skim.pcollisionEventSelection == 1)) && h[f]->skim.pHBHENoiseFilter == 1) || TMath::Abs(h[f]->evt.vz)>15) continue;

//!!!!!!!
////remove when new 7 pp jec is implemented in forest
////!!!!!!!!!
      double JEC[1000] = {0};
     /* if(strcmp(mode, "pp7") == 0)
      {
        for(int j = 0; j<h[f]->ak3PF.nref; j++)
        {
          JEC[j] = get7tevPt(h[f]->ak3PF.rawpt[j], h[f]->ak3PF.jteta[j], h[f]->track.nVtx)/h[f]->ak3PF.jtpt[j];
        }
      }
      else 
      { */
        if(JEC[0] == 0)
        {
          for(int j = 0; j<1000; j++) JEC[j] = 1;
        }
      //}
//!!!!!!end of part that needs to be removed for new JEC, get rid of JEC[j] below
       
      //finding a MB event to mix with if needed 
      if(typeUE==2)
      {
        int loopIter=0;
        int maxIter = 5000000;
        if(strcmp(mode,"pp2")==0) maxIter = mix->GetEntries()-1;
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
          mix->GetEntry(lastMixEvt); 
          if(!((mix->skim.pPAcollisionEventSelectionPA == 1 || !(strcmp(mode,"pp7")*mix->skim.pcollisionEventSelection == 1)) && mix->skim.pHBHENoiseFilter == 1) || TMath::Abs(mix->evt.vz)>15) continue;
          if(strcmp(mode,"pPb5")==0 && mix->evt.run<211313 && TMath::Floor(mix->evt.vz)==TMath::Floor(h[f]->evt.vz) && TMath::Abs(mix->evt.hiHFplus-h[f]->evt.hiHFplus)<5) break;
          else if(strcmp(mode,"Pbp5")==0 && mix->evt.run>=211313 && TMath::Floor(mix->evt.vz)==TMath::Floor(h[f]->evt.vz) && TMath::Abs(mix->evt.hiHFminus-h[f]->evt.hiHFminus)<5) break;
          else if(strcmp(mode,"pp2")==0 && TMath::Floor(mix->evt.vz)==TMath::Floor(h[f]->evt.vz)) break;
        }
      }

      //starting jet loop
      for(int j=0; j<h[f]->ak3PF.nref; j++)
      {
        if(TMath::Abs(h[f]->ak3PF.jteta[j]+boost) < jetEtaMin || TMath::Abs(h[f]->ak3PF.jteta[j]+boost) > jetEtaMax || h[f]->ak3PF.jtpt[j]*JEC[j]<lowBound || h[f]->ak3PF.jtpt[j]*JEC[j]>upBound) continue; 
        h_jet->Fill(h[f]->ak3PF.jtpt[j]*JEC[j]);
     
        for(int t=0; t<h[f]->track.nTrk; t++)
        {
          if(h[f]->track.trkPt[t] < 0.5 || h[f]->track.trkPt[t] > 1e+5 || !h[f]->track.highPurity[t] || TMath::Abs(h[f]->track.trkEta[t])>2.4 ) continue;
          if(TMath::Abs(h[f]->track.trkDxy1[t]/h[f]->track.trkDxyError1[t]) > 3 || TMath::Abs(h[f]->track.trkDz1[t]/h[f]->track.trkDzError1[t]) > 3 || h[f]->track.trkPtError[t]/h[f]->track.trkPt[t] > 0.1) continue;
        
          //calculating r_min for tracking correction
          double r_min = 9;
          for(int j2 = 0; j2<h[f]->ak3PF.nref; j2++)
          {
            if(TMath::Abs(h[f]->ak3PF.jteta[j2])>2 || TMath::Abs(h[f]->ak3PF.jtpt[j2]*JEC[j2]) < 50) continue;
            double r_min_temp = TMath::Power(getdR2(h[f]->ak3PF.jteta[j2],h[f]->ak3PF.jtphi[j2],h[f]->track.trkEta[t],h[f]->track.trkPhi[t]),0.5);
            if(r_min_temp < r_min) r_min = r_min_temp;
          }
 
          //Filling track spectrum in jet cone
          if(getdR2(h[f]->ak3PF.jteta[j]+boost,h[f]->ak3PF.jtphi[j],h[f]->track.trkEta[t]+boost,h[f]->track.trkPhi[t]) < 0.3*0.3)
          {
            double trkCorr = factorizedPtCorr(getPtBin(h[f]->track.trkPt[t], sType), 1, h[f]->track.trkPt[t], h[f]->track.trkPhi[t], h[f]->track.trkEta[t], r_min, sType);
            if(std::isfinite(trkCorr))
            {
              h_track->Fill(h[f]->ak3PF.jtpt[j]*JEC[j],h[f]->track.trkPt[t],trkCorr);
              h_track_xi->Fill(h[f]->ak3PF.jtpt[j]*JEC[j],getXi(h[f]->ak3PF.jtpt[j]*JEC[j],h[f]->ak3PF.jteta[j]+boost,h[f]->ak3PF.jtphi[j],h[f]->track.trkPt[t],h[f]->track.trkEta[t]+boost,h[f]->track.trkPhi[t]),trkCorr);
            }
          }
     
          //returns either +-1 to rotate clockwise or ccw randomly
          int rotationDirection = 2*(int)rand->Integer(2)-1;

          //Phi rotated UE subtraction
          if(typeUE==0 && getdR2(h[f]->ak3PF.jteta[j]+boost,h[f]->ak3PF.jtphi[j]+rotationDirection*TMath::PiOver2(),h[f]->track.trkEta[t]+boost,h[f]->track.trkPhi[t]) < 0.3*0.3)
          {
            double trkCorr = factorizedPtCorr(getPtBin(h[f]->track.trkPt[t], sType), 1, h[f]->track.trkPt[t], h[f]->track.trkPhi[t], h[f]->track.trkEta[t], r_min, sType);
            if(std::isfinite(trkCorr))
            {
              h_trackUE->Fill(h[f]->ak3PF.jtpt[j]*JEC[j],h[f]->track.trkPt[t],trkCorr);  
              h_trackUE_xi->Fill(h[f]->ak3PF.jtpt[j]*JEC[j],getXi(h[f]->ak3PF.jtpt[j]*JEC[j],h[f]->ak3PF.jteta[j]+boost,h[f]->ak3PF.jtphi[j]+rotationDirection*TMath::PiOver2(),h[f]->track.trkPt[t],h[f]->track.trkEta[t]+boost,h[f]->track.trkPhi[t]),trkCorr);
            }
          }

          //Eta Reflected UE subtraction
          if(typeUE==1 && getdR2(-1*(h[f]->ak3PF.jteta[j]+boost),h[f]->ak3PF.jtphi[j],h[f]->track.trkEta[t]+boost,h[f]->track.trkPhi[t]) < 0.3*0.3)
          {
            double trkCorr = factorizedPtCorr(getPtBin(h[f]->track.trkPt[t], sType), 1, h[f]->track.trkPt[t], h[f]->track.trkPhi[t], h[f]->track.trkEta[t], r_min, sType);
            if(std::isfinite(trkCorr))
            {
              h_trackUE->Fill(h[f]->ak3PF.jtpt[j]*JEC[j],h[f]->track.trkPt[t],trkCorr); 
              //need to fix xi UE calculation when you have time
              h_trackUE_xi->Fill(h[f]->ak3PF.jtpt[j]*JEC[j],getXi(h[f]->ak3PF.jtpt[j]*JEC[j],-1*(h[f]->ak3PF.jteta[j]+boost),h[f]->ak3PF.jtphi[j],h[f]->track.trkPt[t],h[f]->track.trkEta[t]+boost,h[f]->track.trkPhi[t]),trkCorr);
            }
          }
        }

        //UE subtraction w/ MB mixing
        if(typeUE==2)
        {        
          mix->hasTrackTree = true;
          mix->hasAk3JetTree = true;
          mix->GetEntry(lastMixEvt);
          for(int tmix = 0; tmix<mix->track.nTrk; tmix++)
          {
            if(mix->track.trkPt[tmix] < 0.5 || mix->track.trkPt[tmix] > 1e+5 || !mix->track.highPurity[tmix] || TMath::Abs(mix->track.trkEta[tmix])>2.4 ) continue;
            if(TMath::Abs(mix->track.trkDxy1[tmix]/mix->track.trkDxyError1[tmix]) > 3 || TMath::Abs(mix->track.trkDz1[tmix]/mix->track.trkDzError1[tmix]) > 3 || mix->track.trkPtError[tmix]/mix->track.trkPt[tmix] > 0.1) continue;

            //calculating r_min for tracking correction
            double r_min = 9;
            for(int j2 = 0; j2<mix->ak3PF.nref; j2++)
            {
              //may need to fix JEC later, 
              if(TMath::Abs(mix->ak3PF.jteta[j2])>2 || TMath::Abs(mix->ak3PF.jtpt[j2]) < 50) continue;
              double r_min_temp = TMath::Power(getdR2(mix->ak3PF.jteta[j2],mix->ak3PF.jtphi[j2],mix->track.trkEta[tmix],mix->track.trkPhi[tmix]),0.5);
              if(r_min_temp < r_min) r_min = r_min_temp;
            }                                                                          
            
            //Filling track spectrum in jet cone
            if(getdR2(h[f]->ak3PF.jteta[j]+boost,h[f]->ak3PF.jtphi[j],mix->track.trkEta[tmix]+boost,mix->track.trkPhi[tmix]) < 0.3*0.3)
            {
              double trkCorr = factorizedPtCorr(getPtBin(mix->track.trkPt[tmix], sType), 1, mix->track.trkPt[tmix], mix->track.trkPhi[tmix], mix->track.trkEta[tmix], r_min, sType);
              if(std::isfinite(trkCorr))
              {
                h_trackUE->Fill(h[f]->ak3PF.jtpt[j]*JEC[j],mix->track.trkPt[tmix],trkCorr);
                h_trackUE_xi->Fill(h[f]->ak3PF.jtpt[j]*JEC[j],getXi(h[f]->ak3PF.jtpt[j]*JEC[j],h[f]->ak3PF.jteta[j]+boost,h[f]->ak3PF.jtphi[j],mix->track.trkPt[tmix],mix->track.trkEta[tmix]+boost,mix->track.trkPhi[tmix]),trkCorr);
              }
            }
          }
          mix->hasTrackTree = false;
          mix->hasAk3JetTree = false;
        }
      }
    }
  }

  TFile * outf = new TFile(Form("spectra%s_%d_%d_%d_%d.root",mode,jobNum,(int)typeUE,(int)(10*jetEtaMin),(int)(10*jetEtaMax)),"recreate");
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

int main(int argc, char *argv[])
{
  if(argc != 4)
  {
    std::cout << "Usage: runcorr <condor_iter> <nJobs>" << std::endl;
    return 1;
  }
  int argument1 = std::atoi(argv[1]);
  int argument2 = std::atoi(argv[2]);
  int argument3 = std::atoi(argv[3]);
  /*if(argument==0) argument=27;
  else if(argument==1) argument=26;
  else if(argument==2) argument=27;*/
  
//for running on condor
/*  if(argument3 == 0) Spectra("pp2",true,0,1.5,0,argument1,argument2);
  if(argument3 == 1) Spectra("pPb5",true,0,1.5,0,argument1,argument2);
  if(argument3 == 2) Spectra("pp7",true,0,1.5,0,argument1,argument2);
  std::cout << "finished " << argument1 << argument2 << argument3 << std::endl;
  return 0;*/
}

void makeAll()
{
//for runnign interacively
  Spectra("pp2",false,0.3,1.5,0,0,1);
  Spectra("pPb5",false,0.3,1.5,0,0,1);
  Spectra("pp7",false,0.3,1.5,0,0,1);
}
