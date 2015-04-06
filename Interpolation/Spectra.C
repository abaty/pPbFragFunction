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
#include "residualJEC.h"
#include "jetSmearing.h"
#include "getJEC_2nd.h"

const double pPbRapidity = 0.4654094531;
const int nJetBins = 120;
const int ntrackBins=23;
const double axis[ntrackBins] = {0.5, 0.63, 0.77,  1.03,1.38, 1.84, 2.46, 3.29,  4.40, 5.88,  7.87,  10.52, 14.06,  18.8, 25.13,  33.58,  44.89,  60, 80, 100, 120, 140, 200};


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

//modes are pp2,pp7,pPb5,Pbp5,pp5
void Spectra(const char* inputJets, const char* inputMB, const char* mode = "pp2", const char* trigger = "jet80", bool isMC = 0,int  jobNum = -1, int typeUE = 3, double jetEtaMin = 0, double jetEtaMax = 1.5)
{
  if(strcmp(mode,"pp2") && strcmp(mode,"pp7") && strcmp(mode,"pPb5") && strcmp(mode,"Pbp5") && strcmp(mode,"pp5"))
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

  //different nonzero variations are used for systematics checks, variation 0 is for the basic calculation
  for(int v = 0; v<variations; v++)
  {
    if(strcmp(mode,"pp2")==0 && !(v==0 || v==1 || v==2 || v==7 || v==10 || v==13 || v==14 || v==15 || v==20 || v==21)) continue;
    if(strcmp(mode,"pp7")==0 && !(v==0 || v==3 || v==4 || v==8 ||v==11 || v==13 || v==16 || v==17 || v==22 || v==23)) continue;
    if((strcmp(mode,"pPb5")==0 || strcmp(mode,"Pbp5")==0 || strcmp(mode,"pp5")==0) && !(v==0 || v==5 || v==6 || v==9 || v==12 || v==13 || v==18 || v==19 || v==24 || v==25)) continue;
    if(typeUE!=0 && v==26) continue;

    //reco
    h_jet = new TH1D("h_jet","",nJetBins,0,300); 
    h_track = new TH2D("h_track","",nJetBins,0,300,ntrackBins-1,axis);
    h_trackUE = new TH2D("h_trackUE","",nJetBins,0,300,ntrackBins-1,axis);
    h_track_xi = new TH2D("h_track_xi","",nJetBins,0,300,28,-1.5,5.5);
    h_trackUE_xi = new TH2D("h_trackUE_xi","",nJetBins,0,300,28,-1.5,5.5);
  
    //gen/reco combinations  
    h_track_rJgT = new TH2D("h_track_rJgT","",nJetBins,0,300,ntrackBins-1,axis);
    h_trackUE_rJgT = new TH2D("h_trackUE_rJgT","",nJetBins,0,300,ntrackBins-1,axis);
    h_track_xi_rJgT = new TH2D("h_track_xi_rJgT","",nJetBins,0,300,28,-1.5,5.5);
    h_trackUE_xi_rJgT = new TH2D("h_trackUE_xi_rJgT","",nJetBins,0,300,28,-1.5,5.5);
  
    h_track_gJrT = new TH2D("h_track_gJrT","",nJetBins,0,300,ntrackBins-1,axis);
    h_trackUE_gJrT = new TH2D("h_trackUE_gJrT","",nJetBins,0,300,ntrackBins-1,axis);
    h_track_xi_gJrT = new TH2D("h_track_xi_gJrT","",nJetBins,0,300,28,-1.5,5.5);
    h_trackUE_xi_gJrT = new TH2D("h_trackUE_xi_gJrT","",nJetBins,0,300,28,-1.5,5.5);
  
    //gen
    h_jet_gen = new TH1D("h_jet_gen","",nJetBins,0,300);
    h_track_gen = new TH2D("h_track_gen","",nJetBins,0,300,ntrackBins-1,axis);
    h_trackUE_gen = new TH2D("h_trackUE_gen","",nJetBins,0,300,ntrackBins-1,axis);
    h_track_xi_gen = new TH2D("h_track_xi_gen","",nJetBins,0,300,28,-1.5,5.5);
    h_trackUE_xi_gen = new TH2D("h_trackUE_xi_gen","",nJetBins,0,300,28,-1.5,5.5);   
  
    //Quark Gluons checks 
    h_jet_Q = new TH1D("h_jet_Q","",nJetBins,0,300);
    h_track_Q = new TH2D("h_track_Q","",nJetBins,0,300,ntrackBins-1,axis);
    h_trackUE_Q = new TH2D("h_trackUE_Q","",nJetBins,0,300,ntrackBins-1,axis);
    h_track_xi_Q = new TH2D("h_track_xi_Q","",nJetBins,0,300,28,-1.5,5.5);
    h_trackUE_xi_Q = new TH2D("h_trackUE_xi_Q","",nJetBins,0,300,28,-1.5,5.5);
    h_jet_G = new TH1D("h_jet_G","",nJetBins,0,300);
    h_track_G = new TH2D("h_track_G","",nJetBins,0,300,ntrackBins-1,axis);
    h_trackUE_G = new TH2D("h_trackUE_G","",nJetBins,0,300,ntrackBins-1,axis);
    h_track_xi_G = new TH2D("h_track_xi_G","",nJetBins,0,300,28,-1.5,5.5);
    h_trackUE_xi_G = new TH2D("h_trackUE_xi_G","",nJetBins,0,300,28,-1.5,5.5);
    h_jet_gen_Q = new TH1D("h_jet_gen_Q","",nJetBins,0,300);
    h_track_gen_Q = new TH2D("h_track_gen_Q","",nJetBins,0,300,ntrackBins-1,axis);
    h_trackUE_gen_Q = new TH2D("h_trackUE_gen_Q","",nJetBins,0,300,ntrackBins-1,axis);
    h_track_xi_gen_Q = new TH2D("h_track_xi_gen_Q","",nJetBins,0,300,28,-1.5,5.5);
    h_trackUE_xi_gen_Q = new TH2D("h_trackUE_xi_gen_Q","",nJetBins,0,300,28,-1.5,5.5);
    h_jet_gen_G = new TH1D("h_jet_gen_G","",nJetBins,0,300);
    h_track_gen_G = new TH2D("h_track_gen_G","",nJetBins,0,300,ntrackBins-1,axis);
    h_trackUE_gen_G = new TH2D("h_trackUE_gen_G","",nJetBins,0,300,ntrackBins-1,axis);
    h_track_xi_gen_G = new TH2D("h_track_xi_gen_G","",nJetBins,0,300,28,-1.5,5.5);
    h_trackUE_xi_gen_G = new TH2D("h_trackUE_xi_gen_G","",nJetBins,0,300,28,-1.5,5.5); 
  
    //boosting
    double boost = 0;
    if(strcmp(mode,"pPb5") == 0 || strcmp(mode,"pp5") == 0) boost = pPbRapidity;
    else if(strcmp(mode,"Pbp5") == 0) boost = -pPbRapidity;
    std::cout << mode << " mode is specified; using a boost of: " << boost << std::endl;
  
    //variables for mixing
    int startMixEvt = 0;
    int lastMixEvt = 1;
    //if(strcmp(mode, "Pbp5")==0) startMixEvt = 6743253;
    if(typeUE==2) lastMixEvt = trackMix->GetEntries();
  
    int nEntry = track->GetEntries();
    //nEntry = 10;
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
  
      //starting jet loop Reco
      for(int j=0; j<nref; j++)
      {
        totalJetsHist->Fill(1,weight);
        if(rawpt[j]<30) continue;
        totalJetsRawPtCut->Fill(1,weight);
        if(TMath::Abs(jteta[j]+boost) < jetEtaMin || TMath::Abs(jteta[j]+boost) > jetEtaMax) continue;
        totalJetsEtaCutHist->Fill(1,weight);
  
      //residual JEC correction applied
        jtpt[j] = getCorrectedJetPt(mode,isMC,jtpt[j],jteta[j]);
        jtpt[j] = getJEC_2nd(jtpt[j],jteta[j],mode);
        if(v==1 || v==3 || v==5)jtpt[j] = jtpt[j]*1.03;
        if(v==20 || v==22 || v==24)jtpt[j] = jtpt[j]*1.02;
        if(v==14 || v==16 || v==18)jtpt[j] = jtpt[j]*1.01;
        if(v==2 || v==4 || v==6)jtpt[j] = jtpt[j]*0.97;
        if(v==21 || v==23 || v==25)jtpt[j] = jtpt[j]*0.98;
        if(v==15 || v==17 || v==19)jtpt[j] = jtpt[j]*0.99;
        if(v==7 || v==8 || v==9)jtpt[j] = getJERCorrected(mode,jtpt[j],0.05);
        if(v==10 || v==11 || v==12)jtpt[j] = getJERCorrected(mode,jtpt[j],0.02);
       
        if(jtpt[j]<lowJetPtBound || jtpt[j]>=upJetPtBound) continue;      
        totalJetsPtCutHist->Fill(1,weight);    
        h_jet->Fill(jtpt[j],weight);
  
      //quark or gluon only contributions for MC
        bool isQ = false;
        bool isG = false;
        if(isMC && TMath::Abs(refparton_flavor[j])<901 && TMath::Abs(refparton_flavor[j])!=21) isQ=true;
        if(isMC && TMath::Abs(refparton_flavor[j])==21) isG=true;
        if(isQ) h_jet_Q->Fill(jtpt[j],weight);
        if(isG) h_jet_G->Fill(jtpt[j],weight);
       
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
            double trkCorr = factorizedPtCorr(getPtBin(trkPt[t], sType), 1, trkPt[t], trkPhi[t], trkEta[t], r_min, sType);         
            if(v==13) trkCorr=1; 
            if(std::isfinite(trkCorr))
            {
              h_track->Fill(jtpt[j],trkPt[t],trkCorr*weight);
              h_track_xi->Fill(jtpt[j],getXi(jtpt[j],jteta[j]+boost,jtphi[j],trkPt[t],trkEta[t]+boost,trkPhi[t]),trkCorr*weight);
              if(isQ)
              {
                h_track_Q->Fill(jtpt[j],trkPt[t],trkCorr*weight);
                h_track_xi_Q->Fill(jtpt[j],getXi(jtpt[j],jteta[j]+boost,jtphi[j],trkPt[t],trkEta[t]+boost,trkPhi[t]),trkCorr*weight);
              }
              if(isG)
              {
                h_track_G->Fill(jtpt[j],trkPt[t],trkCorr*weight);
                h_track_xi_G->Fill(jtpt[j],getXi(jtpt[j],jteta[j]+boost,jtphi[j],trkPt[t],trkEta[t]+boost,trkPhi[t]),trkCorr*weight);
              }
            }
          }
       
          //Phi rotated UE subtraction
          //returns either +-1 to rotate clockwise or ccw randomly
          double rotationDirection = 2*(int)rand->Integer(2)-1;
          if(v==26) rotationDirection = rotationDirection*2.0/3.0;
  
          if(typeUE==0 && getdR2(jteta[j]+boost,jtphi[j]+rotationDirection*TMath::PiOver2(),trkEta[t]+boost,trkPhi[t]) < 0.3*0.3)
          {
            double trkCorr = factorizedPtCorr(getPtBin(trkPt[t], sType), 1, trkPt[t], trkPhi[t], trkEta[t], r_min, sType);
            if(v==13) trkCorr=1;
            if(std::isfinite(trkCorr))
            {
              h_trackUE->Fill(jtpt[j],trkPt[t],trkCorr*weight);  
              h_trackUE_xi->Fill(jtpt[j],getXi(jtpt[j],jteta[j]+boost,jtphi[j]+rotationDirection*TMath::PiOver2(),trkPt[t],trkEta[t]+boost,trkPhi[t]),trkCorr*weight);
              if(isQ)
              {
                h_trackUE_Q->Fill(jtpt[j],trkPt[t],trkCorr*weight);
                h_trackUE_xi_Q->Fill(jtpt[j],getXi(jtpt[j],jteta[j]+boost,jtphi[j]+rotationDirection*TMath::PiOver2(),trkPt[t],trkEta[t]+boost,trkPhi[t]),trkCorr*weight);
              }
              if(isG)
              {
                h_trackUE_G->Fill(jtpt[j],trkPt[t],trkCorr*weight);
                h_trackUE_xi_G->Fill(jtpt[j],getXi(jtpt[j],jteta[j]+boost,jtphi[j]+rotationDirection*TMath::PiOver2(),trkPt[t],trkEta[t]+boost,trkPhi[t]),trkCorr*weight);
              }
            }
          }
  
          //Eta Reflected UE subtraction
          if(typeUE==1 && getdR2(-1*(jteta[j]+boost),jtphi[j],trkEta[t]+boost,trkPhi[t]) < 0.3*0.3)
          {
            double trkCorr = factorizedPtCorr(getPtBin(trkPt[t], sType), 1, trkPt[t], trkPhi[t], trkEta[t], r_min, sType);
            if(v==13) trkCorr=1;
            if(std::isfinite(trkCorr))
            {
              h_trackUE->Fill(jtpt[j],trkPt[t],trkCorr*weight); 
              h_trackUE_xi->Fill(jtpt[j],getXi(jtpt[j],-1*(jteta[j]+boost),jtphi[j],trkPt[t],trkEta[t]+boost,trkPhi[t]),trkCorr*weight);
              if(isG)
              {
                h_trackUE_G->Fill(jtpt[j],trkPt[t],trkCorr*weight);
                h_trackUE_xi_G->Fill(jtpt[j],getXi(jtpt[j],-1*(jteta[j]+boost),jtphi[j],trkPt[t],trkEta[t]+boost,trkPhi[t]),trkCorr*weight);
              }
              if(isQ)
              {
                h_trackUE_Q->Fill(jtpt[j],trkPt[t],trkCorr*weight);
                h_trackUE_xi_Q->Fill(jtpt[j],getXi(jtpt[j],-1*(jteta[j]+boost),jtphi[j],trkPt[t],trkEta[t]+boost,trkPhi[t]),trkCorr*weight);
              } 
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
              if(TMath::Abs(jtetaMix[j2])>2 || TMath::Abs(jtptMix[j2]) < 50) continue;
              double r_min_temp = TMath::Power(getdR2(jtetaMix[j2],jtphiMix[j2],trkEtaMix[t],trkPhiMix[t]),0.5);
              if(r_min_temp < r_min) r_min = r_min_temp;
            }                                                                          
              
            //Filling track spectrum in jet cone
            if(getdR2(jteta[j]+boost,jtphi[j],trkEtaMix[t]+boost,trkPhiMix[t]) < 0.3*0.3)
            {
              double trkCorr = factorizedPtCorr(getPtBin(trkPtMix[t], sType), 1, trkPtMix[t], trkPhiMix[t], trkEtaMix[t], r_min, sType);
              if(v==13) trkCorr=1;
              if(std::isfinite(trkCorr))
              {
                h_trackUE->Fill(jtpt[j],trkPtMix[t],trkCorr*weight);
                h_trackUE_xi->Fill(jtpt[j],getXi(jtpt[j],jteta[j]+boost,jtphi[j],trkPtMix[t],trkEtaMix[t]+boost,trkPhiMix[t]),trkCorr*weight);
                if(isG)
                {
                  h_trackUE_G->Fill(jtpt[j],trkPtMix[t],trkCorr*weight);
                  h_trackUE_xi_G->Fill(jtpt[j],getXi(jtpt[j],jteta[j]+boost,jtphi[j],trkPtMix[t],trkEtaMix[t]+boost,trkPhiMix[t]),trkCorr*weight);
                }
                if(isQ)
                {
                  h_trackUE_Q->Fill(jtpt[j],trkPtMix[t],trkCorr*weight);
                  h_trackUE_xi_Q->Fill(jtpt[j],getXi(jtpt[j],jteta[j]+boost,jtphi[j],trkPtMix[t],trkEtaMix[t]+boost,trkPhiMix[t]),trkCorr*weight);
                }
              }
            }
          }
        }
  
        //reco jet gen particle 
        if(isMC)
        {
          for(int t=0; t<nParticle; t++)
          { 
            if(pPt[t] < 0.5 || pPt[t] > 1e+5 || TMath::Abs(pEta[t])>2.4 ) continue;
            //Filling track spectrum in jet cone
            if(getdR2(jteta[j]+boost,jtphi[j],pEta[t]+boost,pPhi[t]) < 0.3*0.3)
            {
              h_track_rJgT->Fill(jtpt[j],pPt[t],weight);
              h_track_xi_rJgT->Fill(jtpt[j],getXi(jtpt[j],jteta[j]+boost,jtphi[j],pPt[t],pEta[t]+boost,pPhi[t]),weight);
   
              //Phi rotated UE subtraction
              //returns either +-1 to rotate clockwise or ccw randomly
              double rotationDirection = 2*(int)rand->Integer(2)-1;
              if(v==26) rotationDirection = rotationDirection*2.0/3.0;

              if(typeUE==0 && getdR2(jteta[j]+boost,jtphi[j]+rotationDirection*TMath::PiOver2(),pEta[t]+boost,pPhi[t]) < 0.3*0.3)
              {
                h_trackUE_rJgT->Fill(jtpt[j],pPt[t],weight);  
                h_trackUE_xi_rJgT->Fill(jtpt[j],getXi(jtpt[j],jteta[j]+boost,jtphi[j]+rotationDirection*TMath::PiOver2(),pPt[t],pEta[t]+boost,pPhi[t]),weight);
              }
  
              //Eta Reflected UE subtraction
              if(typeUE==1 && getdR2(-1*(jteta[j]+boost),jtphi[j],pEta[t]+boost,pPhi[t]) < 0.3*0.3)
              {
                h_trackUE_rJgT->Fill(jtpt[j],pPt[t],weight); 
                h_trackUE_xi_rJgT->Fill(jtpt[j],getXi(jtpt[j],-1*(jteta[j]+boost),jtphi[j],pPt[t],pEta[t]+boost,pPhi[t]),weight);
              }
            }
          }
          //UE subtraction w/ MB mixing
          if(typeUE==2)
          {        
            getInputEntryMix(lastMixEvt);
            for(int t = 0; t < nParticleMix; t++)
            {
              if(pPtMix[t] < 0.5 || pPtMix[t] > 1e+5 || TMath::Abs(pEtaMix[t])>2.4 ) continue;
            
              //Filling track spectrum in jet cone
              if(getdR2(jteta[j]+boost,jtphi[j],pEtaMix[t]+boost,pPhiMix[t]) < 0.3*0.3)
              {
                h_trackUE_rJgT->Fill(jtpt[j],pPtMix[t],weight);
                h_trackUE_xi_rJgT->Fill(jtpt[j],getXi(jtpt[j],jteta[j]+boost,jtphi[j],pPtMix[t],pEtaMix[t]+boost,pPhiMix[t]),weight);
              }
            }
          }
        }
      }
  
  
      //starting jet loop Gen
      if(isMC)
      {  
        for(int j=0; j<ngen; j++)
        {   
          if(v==1 || v==3 || v==5)genpt[j] = genpt[j]*1.03;
          if(v==20 || v==22 || v==24)genpt[j] = genpt[j]*1.02;
          if(v==14 || v==16 || v==18)genpt[j] = genpt[j]*1.01;
          if(v==2 || v==4 || v==6)genpt[j] = genpt[j]*0.97; 
          if(v==21 || v==23 || v==25)genpt[j] = genpt[j]*0.98;
          if(v==15 || v==17 || v==19)genpt[j] = genpt[j]*0.99;
          if(v==7 || v==8 || v==9)genpt[j] = getJERCorrected(mode,genpt[j],0.05);
          if(v==10 || v==11 || v==12)genpt[j] = getJERCorrected(mode,genpt[j],0.02);
          if(TMath::Abs(geneta[j]+boost) < jetEtaMin || TMath::Abs(geneta[j]+boost) > jetEtaMax || genpt[j]<lowJetPtBound || genpt[j]>=upJetPtBound) continue;
          
          //getting jet flavor (a bit convoluted because genMatchedID is not filled in forest correctly)
          bool isQ=false;
          bool isG=false;
          for(int j2=0; j2<nref; j2++)
          {
             if(TMath::Abs(refpt[j2] - genpt[j])==0 && TMath::Abs(refeta[j2] - geneta[j])==0 && refparton_flavor[j2]==21) isG = true;
             if(TMath::Abs(refpt[j2] - genpt[j])==0 && TMath::Abs(refeta[j2] - geneta[j])==0 && refparton_flavor[j2]!=21 && TMath::Abs(refparton_flavor[j2])<901) isQ = true; 
             if(isQ || isG) break;
          }
            
          h_jet_gen->Fill(genpt[j], weight);  
          if(isQ) h_jet_gen_Q->Fill(genpt[j],weight);
          if(isG) h_jet_gen_G->Fill(genpt[j],weight);
       
          for(int t=0; t<nParticle; t++)
          { 
            if(pPt[t] < 0.5 || pPt[t] > 1e+5 || TMath::Abs(pEta[t])>2.4 ) continue;
  
            //Filling track spectrum in jet cone
            if(getdR2(geneta[j]+boost,genphi[j],pEta[t]+boost,pPhi[t]) < 0.3*0.3)
            {
              h_track_gen->Fill(genpt[j],pPt[t],weight);
              h_track_xi_gen->Fill(genpt[j],getXi(genpt[j],geneta[j]+boost,genphi[j],pPt[t],pEta[t]+boost,pPhi[t]),weight);
   
              if(isQ)
              {
                h_track_gen_Q->Fill(genpt[j], pPt[t],weight);
                h_track_xi_gen_Q->Fill(genpt[j],getXi(genpt[j],geneta[j]+boost,genphi[j],pPt[t],pEta[t]+boost,pPhi[t]),weight);
              }
              if(isG)
              {
                h_track_gen_G->Fill(genpt[j],pPt[t],weight);
                h_track_xi_gen_G->Fill(genpt[j],getXi(genpt[j],geneta[j]+boost,genphi[j],pPt[t],pEta[t]+boost,pPhi[t]),weight);
              }
            }
       
            //Phi rotated UE subtraction
            //returns either +-1 to rotate clockwise or ccw randomly
            double rotationDirection = 2*(int)rand->Integer(2)-1; 
            if(v==26) rotationDirection = rotationDirection*2.0/3.0;

            if(typeUE==0 && getdR2(geneta[j]+boost,genphi[j]+rotationDirection*TMath::PiOver2(),pEta[t]+boost,pPhi[t]) < 0.3*0.3)
            {
              h_trackUE_gen->Fill(genpt[j],pPt[t],weight);  
              h_trackUE_xi_gen->Fill(genpt[j],getXi(genpt[j],geneta[j]+boost,genphi[j]+rotationDirection*TMath::PiOver2(),pPt[t],pEta[t]+boost,pPhi[t]),weight);
   
              if(isQ)
              {
                h_trackUE_gen_Q->Fill(genpt[j], pPt[t],weight);
                h_trackUE_xi_gen_Q->Fill(genpt[j],getXi(genpt[j],geneta[j]+boost,genphi[j]+rotationDirection*TMath::PiOver2(),pPt[t],pEta[t]+boost,pPhi[t]),weight);
              }
              if(isG)
              {
                h_trackUE_gen_G->Fill(genpt[j],pPt[t],weight);
                h_trackUE_xi_gen_G->Fill(genpt[j],getXi(genpt[j],geneta[j]+boost,genphi[j]+rotationDirection*TMath::PiOver2(),pPt[t],pEta[t]+boost,pPhi[t]),weight);
              }
            }
  
            //Eta Reflected UE subtraction
            if(typeUE==1 && getdR2(-1*(geneta[j]+boost),genphi[j],pEta[t]+boost,pPhi[t]) < 0.3*0.3)
            {
              h_trackUE_gen->Fill(genpt[j],pPt[t],weight); 
              h_trackUE_xi_gen->Fill(genpt[j],getXi(genpt[j],-1*(geneta[j]+boost),genphi[j],pPt[t],pEta[t]+boost,pPhi[t]),weight);
  
              if(isQ)
              {
                h_trackUE_gen_Q->Fill(genpt[j],pPt[t],weight);
                h_trackUE_xi_gen_Q->Fill(genpt[j],getXi(genpt[j],-1*(geneta[j]+boost),genphi[j],pPt[t],pEta[t]+boost,pPhi[t]),weight);
              }
              if(isG)
              {
                h_trackUE_gen_G->Fill(genpt[j],pPt[t],weight);
                h_trackUE_xi_gen_G->Fill(genpt[j],getXi(genpt[j],-1*(geneta[j]+boost),genphi[j],pPt[t],pEta[t]+boost,pPhi[t]),weight);
              }
            }
          }
  
          //UE subtraction w/ MB mixing
          if(typeUE==2)
          {        
            getInputEntryMix(lastMixEvt);
            for(int t = 0; t < nParticleMix; t++)
            {
              if(pPtMix[t] < 0.5 || pPtMix[t] > 1e+5 || TMath::Abs(pEtaMix[t])>2.4 ) continue;
              
              //Filling track spectrum in jet cone
              if(getdR2(geneta[j]+boost,genphi[j],pEtaMix[t]+boost,pPhiMix[t]) < 0.3*0.3)
              {
                h_trackUE_gen->Fill(genpt[j],pPtMix[t],weight);
                h_trackUE_xi_gen->Fill(genpt[j],getXi(genpt[j],geneta[j]+boost,genphi[j],pPtMix[t],pEtaMix[t]+boost,pPhiMix[t]),weight);
                
                if(isQ)
                {
                  h_trackUE_gen_Q->Fill(genpt[j],pPtMix[t],weight);
                  h_trackUE_xi_gen_Q->Fill(genpt[j],getXi(genpt[j],geneta[j]+boost,genphi[j],pPtMix[t],pEtaMix[t]+boost,pPhiMix[t]),weight);
                }
                if(isG)
                {
                  h_trackUE_gen_G->Fill(genpt[j],pPtMix[t],weight);
                  h_trackUE_xi_gen_G->Fill(genpt[j],getXi(genpt[j],geneta[j]+boost,genphi[j],pPtMix[t],pEtaMix[t]+boost,pPhiMix[t]),weight);
                }
              }
            }
          }
          
          //gen jet reco track
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
            if(getdR2(geneta[j]+boost,genphi[j],trkEta[t]+boost,trkPhi[t]) < 0.3*0.3)
            {
              double trkCorr = factorizedPtCorr(getPtBin(trkPt[t], sType), 1, trkPt[t], trkPhi[t], trkEta[t], r_min, sType);
              if(v==13) trkCorr=1;          
              if(std::isfinite(trkCorr))
              {
                h_track_gJrT->Fill(genpt[j],trkPt[t],trkCorr*weight);
                h_track_xi_gJrT->Fill(genpt[j],getXi(genpt[j],geneta[j]+boost,genphi[j],trkPt[t],trkEta[t]+boost,trkPhi[t]),trkCorr*weight);
              }
            }
       
            //Phi rotated UE subtraction
            //returns either +-1 to rotate clockwise or ccw randomly
            double rotationDirection = 2*(int)rand->Integer(2)-1;
            if(v==26) rotationDirection = rotationDirection*2.0/3.0;

            if(typeUE==0 && getdR2(geneta[j]+boost,genphi[j]+rotationDirection*TMath::PiOver2(),trkEta[t]+boost,trkPhi[t]) < 0.3*0.3)
            {
              double trkCorr = factorizedPtCorr(getPtBin(trkPt[t], sType), 1, trkPt[t], trkPhi[t], trkEta[t], r_min, sType);
              if(v==13) trkCorr=1;
              if(std::isfinite(trkCorr))
              {
                h_trackUE_gJrT->Fill(genpt[j],trkPt[t],trkCorr*weight);  
                h_trackUE_xi_gJrT->Fill(genpt[j],getXi(genpt[j],geneta[j]+boost,genphi[j]+rotationDirection*TMath::Pi(),trkPt[t],trkEta[t]+boost,trkPhi[t]),trkCorr*weight);
              }
            }
  
            //Eta Reflected UE subtraction
            if(typeUE==1 && getdR2(-1*(geneta[j]+boost),genphi[j],trkEta[t]+boost,trkPhi[t]) < 0.3*0.3)
            {
              double trkCorr = factorizedPtCorr(getPtBin(trkPt[t], sType), 1, trkPt[t], trkPhi[t], trkEta[t], r_min, sType);
              if(v==13) trkCorr=1;
              if(std::isfinite(trkCorr))
              {
                h_trackUE_gJrT->Fill(genpt[j],trkPt[t],trkCorr*weight); 
                h_trackUE_xi_gJrT->Fill(genpt[j],getXi(genpt[j],-1*(geneta[j]+boost),genphi[j],trkPt[t],trkEta[t]+boost,trkPhi[t]),trkCorr*weight); 
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
                if(TMath::Abs(jtetaMix[j2])>2 || TMath::Abs(jtptMix[j2]) < 50) continue;
                double r_min_temp = TMath::Power(getdR2(jtetaMix[j2],jtphiMix[j2],trkEtaMix[t],trkPhiMix[t]),0.5);
                if(r_min_temp < r_min) r_min = r_min_temp;
              }                                                                          
              
              //Filling track spectrum in jet cone
              if(getdR2(geneta[j]+boost,genphi[j],trkEtaMix[t]+boost,trkPhiMix[t]) < 0.3*0.3)
              {
                double trkCorr = factorizedPtCorr(getPtBin(trkPtMix[t], sType), 1, trkPtMix[t], trkPhiMix[t], trkEtaMix[t], r_min, sType);
                if(v==13) trkCorr=1;
                if(std::isfinite(trkCorr))
                {
                  h_trackUE_gJrT->Fill(genpt[j],trkPtMix[t],trkCorr*weight);
                  h_trackUE_xi_gJrT->Fill(genpt[j],getXi(genpt[j],geneta[j]+boost,genphi[j],trkPtMix[t],trkEtaMix[t]+boost,trkPhiMix[t]),trkCorr*weight);
                }
              }
            }
          }
        }
      }
    }
    TFile * outf = new TFile(Form("spectra%s%s_%d_%d_UE%d_%d_%d.root",mode,trigger,jobNum,(int)isMC,(int)typeUE,(int)(10*jetEtaMin),(int)(10*jetEtaMax)),"update");
    h_jet->SetDirectory(0);
    h_track->SetDirectory(0);
    h_trackUE->SetDirectory(0);
    h_track_xi->SetDirectory(0);
    h_trackUE_xi->SetDirectory(0);
    h_track_rJgT->SetDirectory(0);
    h_trackUE_rJgT->SetDirectory(0);
    h_track_xi_rJgT->SetDirectory(0);
    h_trackUE_xi_rJgT->SetDirectory(0);
    h_track_gJrT->SetDirectory(0);
    h_trackUE_gJrT->SetDirectory(0);
    h_track_xi_gJrT->SetDirectory(0);
    h_trackUE_xi_gJrT->SetDirectory(0);
    h_jet_gen->SetDirectory(0);
    h_track_gen->SetDirectory(0);
    h_trackUE_gen->SetDirectory(0);
    h_track_xi_gen->SetDirectory(0);
    h_trackUE_xi_gen->SetDirectory(0);
    h_jet_Q->SetDirectory(0);
    h_track_Q->SetDirectory(0);
    h_trackUE_Q->SetDirectory(0);
    h_track_xi_Q->SetDirectory(0);
    h_trackUE_xi_Q->SetDirectory(0);
    h_jet_G->SetDirectory(0);
    h_track_G->SetDirectory(0);
    h_trackUE_G->SetDirectory(0);
    h_track_xi_G->SetDirectory(0);
    h_trackUE_xi_G->SetDirectory(0);
    h_jet_gen_Q->SetDirectory(0);
    h_track_gen_Q->SetDirectory(0);
    h_trackUE_gen_Q->SetDirectory(0);
    h_track_xi_gen_Q->SetDirectory(0);
    h_trackUE_xi_gen_Q->SetDirectory(0);
    h_jet_gen_G->SetDirectory(0);
    h_track_gen_G->SetDirectory(0);
    h_trackUE_gen_G->SetDirectory(0);
    h_track_xi_gen_G->SetDirectory(0);
    h_trackUE_xi_gen_G->SetDirectory(0);
  
    h_jet->Write(Form("%s_reco_jet%s",mode,variationTag[v]));
    h_track->Write(Form("%s_reco_track%s",mode,variationTag[v]));
    h_trackUE->Write(Form("%s_reco_trackUE%s",mode,variationTag[v]));
    h_track_xi->Write(Form("%s_reco_track_xi%s",mode,variationTag[v]));
    h_trackUE_xi->Write(Form("%s_reco_trackUE_xi%s",mode,variationTag[v]));  
    h_track_rJgT->Write(Form("%s_rJgT_track%s",mode,variationTag[v]));
    h_trackUE_rJgT->Write(Form("%s_rJgT_trackUE%s",mode,variationTag[v]));
    h_track_xi_rJgT->Write(Form("%s_rJgT_track_xi%s",mode,variationTag[v]));
    h_trackUE_xi_rJgT->Write(Form("%s_rJgT_trackUE_xi%s",mode,variationTag[v]));
    h_track_gJrT->Write(Form("%s_gJrT_track%s",mode,variationTag[v]));
    h_trackUE_gJrT->Write(Form("%s_gJrT_trackUE%s",mode,variationTag[v]));
    h_track_xi_gJrT->Write(Form("%s_gJrT_track_xi%s",mode,variationTag[v]));
    h_trackUE_xi_gJrT->Write(Form("%s_gJrT_trackUE_xi%s",mode,variationTag[v]));
    h_jet_gen->Write(Form("%s_gen_jet%s",mode,variationTag[v]));
    h_track_gen->Write(Form("%s_gen_track%s",mode,variationTag[v]));
    h_trackUE_gen->Write(Form("%s_gen_trackUE%s",mode,variationTag[v]));
    h_track_xi_gen->Write(Form("%s_gen_track_xi%s",mode,variationTag[v]));
    h_trackUE_xi_gen->Write(Form("%s_gen_trackUE_xi%s",mode,variationTag[v]));
    h_jet_Q->Write(Form("%s_reco_jet_Q%s",mode,variationTag[v]));
    h_track_Q->Write(Form("%s_reco_track_Q%s",mode,variationTag[v]));
    h_trackUE_Q->Write(Form("%s_reco_trackUE_Q%s",mode,variationTag[v]));
    h_track_xi_Q->Write(Form("%s_reco_track_xi_Q%s",mode,variationTag[v]));
    h_trackUE_xi_Q->Write(Form("%s_reco_trackUE_xi_Q%s",mode,variationTag[v]));
    h_jet_G->Write(Form("%s_reco_jet_G%s",mode,variationTag[v]));
    h_track_G->Write(Form("%s_reco_track_G%s",mode,variationTag[v]));
    h_trackUE_G->Write(Form("%s_reco_trackUE_G%s",mode,variationTag[v]));
    h_track_xi_G->Write(Form("%s_reco_track_xi_G%s",mode,variationTag[v]));
    h_trackUE_xi_G->Write(Form("%s_reco_trackUE_xi_G%s",mode,variationTag[v]));
    h_jet_gen_Q->Write(Form("%s_gen_jet_Q%s",mode,variationTag[v]));
    h_track_gen_Q->Write(Form("%s_gen_track_Q%s",mode,variationTag[v]));
    h_trackUE_gen_Q->Write(Form("%s_gen_trackUE_Q%s",mode,variationTag[v]));
    h_track_xi_gen_Q->Write(Form("%s_gen_track_xi_Q%s",mode,variationTag[v]));
    h_trackUE_xi_gen_Q->Write(Form("%s_gen_trackUE_xi_Q%s",mode,variationTag[v]));
    h_jet_gen_G->Write(Form("%s_gen_jet_G%s",mode,variationTag[v]));
    h_track_gen_G->Write(Form("%s_gen_track_G%s",mode,variationTag[v]));
    h_trackUE_gen_G->Write(Form("%s_gen_trackUE_G%s",mode,variationTag[v]));
    h_track_xi_gen_G->Write(Form("%s_gen_track_xi_G%s",mode,variationTag[v]));
    h_trackUE_xi_gen_G->Write(Form("%s_gen_trackUE_xi_G%s",mode,variationTag[v]));
    if(v==0)
    {
      totalJetsHist->Write();
      totalJetsRawPtCut->Write();
      totalJetsEtaCutHist->Write();
      totalJetsPtCutHist->Write();
    } 
    outf->Close();
  }
}

int main(int argc, const char* argv[])
{
  if(argc != 5)
  {
    std::cout << "Usage: Spectra <fileListJets> <fileListMB> <job> <UEMode>" << std::endl;
    return 1;
  }
  
  std::string fList = argv[1];
  std::string fListMB = argv[2];
  int job = std::atoi(argv[3]);
  int UEMode = std::atoi(argv[4]);

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
  if(listOfFilesJets[job].find("pp5") != std::string::npos) parsedMode = "pp5";

  if(listOfFilesJets[job].find("jet80_") != std::string::npos) parsedTrigger = "jet80";
  if(listOfFilesJets[job].find("jet40_") != std::string::npos) parsedTrigger = "jet40";
  if(listOfFilesJets[job].find("jet30_") != std::string::npos) parsedTrigger = "jet30";
  if(listOfFilesJets[job].find("jet60_") != std::string::npos) parsedTrigger = "jet60";
  if(listOfFilesJets[job].find("jet110_") != std::string::npos) parsedTrigger = "jet110";

  int MCStatus = 0;
  if(listOfFilesJets[job].find("/MC/") != std::string::npos) MCStatus = 1;

  std::cout << "Results of parsing input files for mode and trigger used:" << std::endl;
  std::cout << "Mode: " <<  parsedMode.data() << "  Trigger: " << parsedTrigger.data() << "  Is MC:" << MCStatus << std::endl;
  
  Spectra(listOfFilesJets[job].data(),listOfFilesMB[job].data(),parsedMode.data(),parsedTrigger.data(),MCStatus,job,UEMode,0,1.5);
  return 0;
}

