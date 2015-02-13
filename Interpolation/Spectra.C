#include "HiForestAnalysis/hiForest.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TMath.h"
#include "TRandom.h"
#include <iostream>
#include <cmath>
//#include "JEC7tev/get7tevPt.h"
#include "factorizedPtCorr.h"

TH1D * data2_jet;
TH2D * data2_track;
TH2D * data2_trackUE;
TH2D * data2_track_xi;
TH2D * data2_trackUE_xi;


/* TODOS
Track Selection
Track Correction
7 TEV JEC
Triggers
Boosts
Xi Stuff
Different UE
*/

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

void Spectra(bool doPhiUE = false, double jetEtaMin = 0, double jetEtaMax = 1)
{
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  TRandom * rand = new TRandom(23);

  HiForest * h = new HiForest("/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pp_2_76TeV_pp2013/PP2013_HiForest_PromptReco_JsonPP_Jet80_PPReco_forestv82.root","forest",cPP,0);

  h->LoadNoTrees();
  h->hasAk3JetTree = true;
  h->hasTrackTree = true;
  h->hasHltTree = true;
  h->hasSkimTree = true;

  data2_jet = new TH1D("data2_jet","",nJetBins,0,300); 
  data2_track = new TH2D("data2_track","",nJetBins,0,300,39,axis);
  data2_trackUE = new TH2D("data2_trackUE","",nJetBins,0,300,39,axis);
  data2_track_xi = new TH2D("data2_track_xi","",nJetBins,0,300,28,-1.5,5.5);
  data2_trackUE_xi = new TH2D("data2_trackUE_xi","",nJetBins,0,300,28,-1.5,5.5);

  //int nEntry = h->GetEntries();
  int nEntry = 50000;
  for(int i=0; i<nEntry; i++)
  {
    h->GetEntry(i);
    if(i%10000 == 0) std::cout << i << "/" << nEntry << std::endl;
    if(!((h->skim.pPAcollisionEventSelectionPA == 1 || h->skim.pcollisionEventSelection) && h->skim.pHBHENoiseFilter == 1)) continue;

    for(int j=0; j<h->ak3PF.nref; j++)
    {
      if(TMath::Abs(h->ak3PF.jteta[j]) < jetEtaMin || TMath::Abs(h->ak3PF.jteta[j]) > jetEtaMax) continue; 
      data2_jet->Fill(h->ak3PF.jtpt[j]);
     
      for(int t=0; t<h->track.nTrk; t++)
      {
        if(getdR2(h->ak3PF.jteta[j],h->ak3PF.jtphi[j],h->track.trkEta[t],h->track.trkPhi[t]) < 0.3*0.3)
        {
          data2_track->Fill(h->ak3PF.jtpt[j],h->track.trkPt[t]);
        }
     
        //returns either +-1 to rotate clockwise or ccw randomly
        int rotationDirection = 2*(int)rand->Integer(2)-1;
        //Phi rotated UE subtraction
        if(doPhiUE && getdR2(h->ak3PF.jteta[j],h->ak3PF.jtphi[j]+rotationDirection*TMath::PiOver2(),h->track.trkEta[t],h->track.trkPhi[t]) < 0.3*0.3)
        {
          data2_trackUE->Fill(h->ak3PF.jtpt[j],h->track.trkPt[t]);
        }
        //Eta Reflected UE subtraction
        if(!doPhiUE && getdR2(-1*h->ak3PF.jteta[j],h->ak3PF.jtphi[j],h->track.trkEta[t],h->track.trkPhi[t]) < 0.3*0.3)
        {
          data2_trackUE->Fill(h->ak3PF.jtpt[j],h->track.trkPt[t]);
        }



      }
    }
  }
}
