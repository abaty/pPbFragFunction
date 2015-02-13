#include "HiForestAnalysis/hiForest.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TMath.h"
#include "TRandom.h"
#include "string.h"
#include <iostream>
#include <cmath>
//#include "JEC7tev/get7tevPt.h"
#include "factorizedPtCorr.h"

const double pPbRapidity = 0.4654094531;
const int nJetBins = 120;
const double axis[40] = {
                        0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8,
                        2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4,
                        19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6,
                        120.8, 138, 155.2, 172.4, 189.6, 206.8
                        };

TH1D * data2_jet;
TH2D * data2_track;
TH2D * data2_trackUE;
TH2D * data2_track_xi;
TH2D * data2_trackUE_xi;

HiForest * h[5];

const int npp2Files = 2;
const char * pp2File[npp2Files] = {
  "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pp_2_76TeV_pp2013/PP2013_HiForest_PromptReco_JSon_Jet40Jet60_ppTrack_forestv84.root",
  "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pp_2_76TeV_pp2013/PP2013_HiForest_PromptReco_JsonPP_Jet80_PPReco_forestv82.root" };
const double pp2Bound[npp2Files+1] = {60,100,200};

double lowBound;
double upBound;

int setTrigger(const char* mode, int f, HiForest * h)
{
  int trigger;
  if(strcmp(mode,"pp2")==0);
  {
    if(f==0) trigger = h->hlt.HLT_PAJet40_NoJetID_v1;
    if(f==1) trigger = h->hlt.HLT_PAJet80_NoJetID_v1;
    lowBound = pp2Bound[f];
    upBound = pp2Bound[f+1];
  }
  return trigger;
}

//calculates dr^2 to avoid the slow TMath() Sqrt function
double getdR2(double jet_eta, double jet_phi, double track_eta, double track_phi)
{
  return TMath::Power(jet_eta-track_eta,2)+TMath::Power(acos(cos(jet_phi-track_phi)),2);
}

double getXi(double jetPt, double jetEta, double jetPhi, double trkPt, double trkEta, double trkPhi)
{
  double xi = -2;
  xi = TMath::Log((jetPt/trkPt)*TMath::Power(TMath::CosH(jetEta),2)/(TMath::Cos(trkPhi-jetPhi) + TMath::SinH(jetEta)*TMath::SinH(trkEta)));
  return xi;
}

//modes are pp2,pp7,pPb5,Pbp5
void Spectra(const char* mode = "pp2", bool doPhiUE = false, double jetEtaMin = 0, double jetEtaMax = 1.5, bool isMC  = 0)
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
 
  for(int f = 0; f<npp2Files; f++)
  {
    h[f] = new HiForest(pp2File[f],"forest",cPP,0);

    h[f]->LoadNoTrees();
    h[f]->hasAk3JetTree = true;
    h[f]->hasTrackTree = true;
    h[f]->hasHltTree = true;
    h[f]->hasSkimTree = true;
  }

  data2_jet = new TH1D("data2_jet","",nJetBins,0,300); 
  data2_track = new TH2D("data2_track","",nJetBins,0,300,39,axis);
  data2_trackUE = new TH2D("data2_trackUE","",nJetBins,0,300,39,axis);
  data2_track_xi = new TH2D("data2_track_xi","",nJetBins,0,300,28,-1.5,5.5);
  data2_trackUE_xi = new TH2D("data2_trackUE_xi","",nJetBins,0,300,28,-1.5,5.5);

  //boosting
  double boost = 0;
  if(strcmp(mode,"pPb5") == 0) boost = pPbRapidity;
  else if(strcmp(mode,"Pbp5") == 0) boost = -pPbRapidity;
  std::cout << mode << " mode is specified; using a boost of: " << boost << std::endl;

  for(int f=0; f<npp2Files; f++)
  {
    //int nEntry = h[f]->GetEntries();
    int nEntry = 50000;
   for(int i=0; i<nEntry; i++)
    {
      h[f]->GetEntry(i);
      if(i%10000 == 0) std::cout << i << "/" << nEntry << std::endl;

      int trigger = setTrigger(mode,f,h[f]); 
      if(!trigger) continue;
      if(!((h[f]->skim.pPAcollisionEventSelectionPA == 1 || h[f]->skim.pcollisionEventSelection) && h[f]->skim.pHBHENoiseFilter == 1)) continue;

      for(int j=0; j<h[f]->ak3PF.nref; j++)
      {
        if(TMath::Abs(h[f]->ak3PF.jteta[j]+boost) < jetEtaMin || TMath::Abs(h[f]->ak3PF.jteta[j]+boost) > jetEtaMax || h[f]->ak3PF.jtpt[j]<lowBound || h[f]->ak3PF.jtpt[j]>upBound) continue; 
        data2_jet->Fill(h[f]->ak3PF.jtpt[j]);
     
        for(int t=0; t<h[f]->track.nTrk; t++)
        {
          if(h[f]->track.trkPt[t] < 0.5 || h[f]->track.trkPt[t] > 1e+5 || !h[f]->track.highPurity[t] || TMath::Abs(h[f]->track.trkEta[t])>2.4 ) continue;
          if(TMath::Abs(h[f]->track.trkDxy1[t]/h[f]->track.trkDxyError1[t]) > 3 || TMath::Abs(h[f]->track.trkDz1[t]/h[f]->track.trkDzError1[t]) > 3 || h[f]->track.trkPtError[t]/h[f]->track.trkPt[t] > 0.1) continue;
        
          //calculating r_min for tracking correction
          double r_min = 9;
          for(int j2 = 0; j2<h[f]->ak3PF.nref; j2++)
          {
            if(TMath::Abs(h[f]->ak3PF.jteta[j2])>2 || TMath::Abs(h[f]->ak3PF.jtpt[j2]) < 50) continue;
            double r_min_temp = TMath::Power(getdR2(h[f]->ak3PF.jteta[j2],h[f]->ak3PF.jtphi[j2],h[f]->track.trkEta[t],h[f]->track.trkPhi[t]),0.5);
            if(r_min_temp < r_min) r_min = r_min_temp;
          }
 
          //Filling track spectrum in jet cone
          if(getdR2(h[f]->ak3PF.jteta[j]+boost,h[f]->ak3PF.jtphi[j],h[f]->track.trkEta[t]+boost,h[f]->track.trkPhi[t]) < 0.3*0.3)
          {
            double trkCorr = factorizedPtCorr(getPtBin(h[f]->track.trkPt[t], sType), 1, h[f]->track.trkPt[t], h[f]->track.trkPhi[t], h[f]->track.trkEta[t], r_min, sType);
            if(std::isfinite(trkCorr))
            {
              data2_track->Fill(h[f]->ak3PF.jtpt[j],h[f]->track.trkPt[t],trkCorr);
              data2_track_xi->Fill(h[f]->ak3PF.jtpt[j],getXi(h[f]->ak3PF.jtpt[j],h[f]->ak3PF.jteta[j]+boost,h[f]->ak3PF.jtphi[j],h[f]->track.trkPt[t],h[f]->track.trkEta[t]+boost,h[f]->track.trkPhi[t]),trkCorr);
            }
          }
     
          //returns either +-1 to rotate clockwise or ccw randomly
          int rotationDirection = 2*(int)rand->Integer(2)-1;

          //Phi rotated UE subtraction
          if(doPhiUE && getdR2(h[f]->ak3PF.jteta[j]+boost,h[f]->ak3PF.jtphi[j]+rotationDirection*TMath::PiOver2(),h[f]->track.trkEta[t]+boost,h[f]->track.trkPhi[t]) < 0.3*0.3)
          {
            double trkCorr = factorizedPtCorr(getPtBin(h[f]->track.trkPt[t], sType), 1, h[f]->track.trkPt[t], h[f]->track.trkPhi[t], h[f]->track.trkEta[t], r_min, sType);
            if(std::isfinite(trkCorr))
            {
              data2_trackUE->Fill(h[f]->ak3PF.jtpt[j],h[f]->track.trkPt[t],trkCorr); 
              data2_trackUE_xi->Fill(h[f]->ak3PF.jtpt[j],getXi(h[f]->ak3PF.jtpt[j],h[f]->ak3PF.jteta[j]+boost,h[f]->ak3PF.jtphi[j],h[f]->track.trkPt[t],h[f]->track.trkEta[t]+boost,h[f]->track.trkPhi[t]),trkCorr);
            }
          }

          //Eta Reflected UE subtraction
          if(!doPhiUE && getdR2(-1*(h[f]->ak3PF.jteta[j]+boost),h[f]->ak3PF.jtphi[j],h[f]->track.trkEta[t]+boost,h[f]->track.trkPhi[t]) < 0.3*0.3)
          {
            double trkCorr = factorizedPtCorr(getPtBin(h[f]->track.trkPt[t], sType), 1, h[f]->track.trkPt[t], h[f]->track.trkPhi[t], h[f]->track.trkEta[t], r_min, sType);
            if(std::isfinite(trkCorr))
            {
              data2_trackUE->Fill(h[f]->ak3PF.jtpt[j],h[f]->track.trkPt[t],trkCorr); 
              data2_trackUE_xi->Fill(h[f]->ak3PF.jtpt[j],getXi(h[f]->ak3PF.jtpt[j],h[f]->ak3PF.jteta[j]+boost,h[f]->ak3PF.jtphi[j],h[f]->track.trkPt[t],h[f]->track.trkEta[t]+boost,h[f]->track.trkPhi[t]),trkCorr);
            }
          }
        }
      }
    }
  }
}
