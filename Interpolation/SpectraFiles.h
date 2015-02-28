TH1D * h_jet;
TH2D * h_track;
TH2D * h_trackUE;
TH2D * h_track_xi;
TH2D * h_trackUE_xi;

TFile * inf, *infMix;
TTree * track, *trackMix;
TTree * ak3PF, *ak3PFMix;
TTree * evt, *evtMix;

const int maxTrack = 25000;
int nTrk, nTrkMix;
int nVtx, nVtxMix;
float trkPt[maxTrack], trkPtMix[maxTrack];
float trkEta[maxTrack], trkEtaMix[maxTrack];
float trkPhi[maxTrack], trkPhiMix[maxTrack];
float trkPtError[maxTrack], trkPtErrorMix[maxTrack];
float trkDzError1[maxTrack], trkDzError1Mix[maxTrack];
float trkDz1[maxTrack], trkDz1Mix[maxTrack];
float trkDxyError1[maxTrack], trkDxyError1Mix[maxTrack];
float trkDxy1[maxTrack], trkDxy1Mix[maxTrack];
bool highPurity[maxTrack], highPurityMix[maxTrack];
//float trkRmin[maxTrack], trkRminMix[maxTrack];

const int maxJet = 500;
int nref, nrefMix;
float rawpt[maxJet], rawptMix[maxJet];
float jtpt[maxJet], jtptMix[maxJet];
float jteta[maxJet],jtetaMix[maxJet];
float jtphi[maxJet],jtphiMix[maxJet];
float chargedSum[maxJet],chargedSumMix[maxJet];

int run, runMix;
int event, eventMix;
float vz, vzMix;
float hiHFplus, hiHFplusMix;
float hiHFminus, hiHFminusMix;
float hiHFplusEta4, hiHFplusEta4Mix;
float hiHFminusEta4, hiHFminusEta4Mix;
float hiHFhitPlus, hiHFhitPlusMix;
float hiHFhitMinus, hiHFhitMinusMix;

double lowJetPtBound;
double upJetPtBound;

void setJetPtRange(const char * mode, const char* trigger)
{
  if((strcmp(mode,"pPb5")==0 || strcmp(mode,"Pbp5")==0 || strcmp(mode,"pp2")==0) && strcmp(trigger,"jet80")==0)
  {
    lowJetPtBound = 100; 
    upJetPtBound  = 200;
  }
  if((strcmp(mode,"pPb5")==0 || strcmp(mode,"Pbp5")==0 || strcmp(mode,"pp2")==0) && strcmp(trigger,"jet40")==0)
  {
    lowJetPtBound = 60;
    upJetPtBound  = 100;
  }
  if(strcmp(mode,"pp7")==0 && strcmp(trigger,"jet30")==0)
  {
    lowJetPtBound = 60;
    upJetPtBound  = 80;
  }
  if(strcmp(mode,"pp7")==0 && strcmp(trigger,"jet60")==0)
  {
    lowJetPtBound = 80;
    upJetPtBound  = 140;
  }
  if(strcmp(mode,"pp7")==0 && strcmp(trigger,"jet110")==0)
  {
    lowJetPtBound = 140;
    upJetPtBound  = 200;
  }
  return;
}

void getInputFile(const char * name, int isMC)
{
  inf = new TFile(name,"read");  
  
  track = (TTree*)inf->Get("track"); 
  ak3PF = (TTree*)inf->Get("ak3PF");
  evt = (TTree*)inf->Get("evt");


  //Setting addresses
  track->SetBranchAddress("nTrk",&nTrk); 
  track->SetBranchAddress("trkPt",&trkPt);
  track->SetBranchAddress("trkEta",&trkEta);
  track->SetBranchAddress("trkPhi",&trkPhi);
  track->SetBranchAddress("trkPtError",&trkPtError);
  track->SetBranchAddress("trkDzError1",&trkDzError1);
  track->SetBranchAddress("trkDz1",&trkDz1);
  track->SetBranchAddress("trkDxyError1",&trkDxyError1);
  track->SetBranchAddress("trkDxy1",&trkDxy1);
  track->SetBranchAddress("highPurity",&highPurity);
  track->SetBranchAddress("nVtx",&nVtx);

  ak3PF->SetBranchAddress("nref",&nref);
  ak3PF->SetBranchAddress("rawpt",&rawpt);
  ak3PF->SetBranchAddress("jtpt",&jtpt);
  ak3PF->SetBranchAddress("jteta",&jteta);
  ak3PF->SetBranchAddress("jtphi",&jtphi);
  ak3PF->SetBranchAddress("chargedSum",&chargedSum);

  evt->SetBranchAddress("run",&run);
  evt->SetBranchAddress("vz",&vz);
  evt->SetBranchAddress("hiHFplus",&hiHFplus);
  evt->SetBranchAddress("hiHFminus",&hiHFminus);
  evt->SetBranchAddress("hiHFplusEta4",&hiHFplusEta4);
  evt->SetBranchAddress("hiHFminusEta4",&hiHFminusEta4);
  evt->SetBranchAddress("hiHFhitPlus",&hiHFhitPlus);
  evt->SetBranchAddress("hiHFhitMinus",&hiHFhitMinus);
  evt->SetBranchAddress("evt",&event);

  return;
}

void getInputEntry(int i)
{
  track->GetEntry(i);
  ak3PF->GetEntry(i);
  evt->GetEntry(i);
  return;
}

void getInputFileMix(const char * name, int isMC)
{
  infMix = new TFile(name,"read");  
  
  trackMix = (TTree*)infMix->Get("track"); 
  ak3PFMix = (TTree*)infMix->Get("ak3PF");
  evtMix = (TTree*)infMix->Get("evt");


  //Setting addresses
  trackMix->SetBranchAddress("nTrk",&nTrkMix); 
  trackMix->SetBranchAddress("trkPt",&trkPtMix);
  trackMix->SetBranchAddress("trkEta",&trkEtaMix);
  trackMix->SetBranchAddress("trkPhi",&trkPhiMix);
  trackMix->SetBranchAddress("trkPtError",&trkPtErrorMix);
  trackMix->SetBranchAddress("trkDzError1",&trkDzError1Mix);
  trackMix->SetBranchAddress("trkDz1",&trkDz1Mix);
  trackMix->SetBranchAddress("trkDxyError1",&trkDxyError1Mix);
  trackMix->SetBranchAddress("trkDxy1",&trkDxy1Mix);
  trackMix->SetBranchAddress("highPurity",&highPurityMix);
  trackMix->SetBranchAddress("nVtx",&nVtxMix);

  ak3PFMix->SetBranchAddress("nref",&nrefMix);
  ak3PFMix->SetBranchAddress("rawpt",&rawptMix);
  ak3PFMix->SetBranchAddress("jtpt",&jtptMix);
  ak3PFMix->SetBranchAddress("jteta",&jtetaMix);
  ak3PFMix->SetBranchAddress("jtphi",&jtphiMix);
  ak3PFMix->SetBranchAddress("chargedSum",&chargedSumMix);

  evtMix->SetBranchAddress("run",&runMix);
  evtMix->SetBranchAddress("vz",&vzMix);
  evtMix->SetBranchAddress("hiHFplus",&hiHFplusMix);
  evtMix->SetBranchAddress("hiHFminus",&hiHFminusMix);
  evtMix->SetBranchAddress("hiHFplusEta4",&hiHFplusEta4Mix);
  evtMix->SetBranchAddress("hiHFminusEta4",&hiHFminusEta4Mix);
  evtMix->SetBranchAddress("hiHFhitPlus",&hiHFhitPlusMix);
  evtMix->SetBranchAddress("hiHFhitMinus",&hiHFhitMinusMix);
  evtMix->SetBranchAddress("evt",&eventMix);

  return;
}

void getInputEntryMix(int i)
{
  evtMix->GetEntry(i);
  trackMix->GetEntry(i);
  ak3PFMix->GetEntry(i);
  return;
}


/*HiForest * h[5];
HiForest * mix;
const int npp2Files = 2;
const char * pp2File[npp2Files] = {
  "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pp_2_76TeV_pp2013/PP2013_HiForest_PromptReco_JSon_Jet40Jet60_ppTrack_forestv84.root",
  "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pp_2_76TeV_pp2013/PP2013_HiForest_PromptReco_JsonPP_Jet80_PPReco_forestv82.root" };
const double pp2Bound[npp2Files+1] = {60,100,200};

const int npPb5Files = 2;
const char * pPb5File[npPb5Files] = {
  "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pPb_5_02TeV_pA2013/PA2013_HiForest_PromptReco_JSonPPb_forestv72_HLT40_HLT60.root",
  "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pPb_5_02TeV_pA2013/PA2013_HiForest_PromptReco_JSonPPb_forestv77.root"};
const double pPb5Bound[npPb5Files+1] = {60,120,200};

const int nPbp5Files = 2;
const char * Pbp5File[nPbp5Files] = {
  "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pPb_5_02TeV_pA2013/PA2013_HiForest_PromptReco_JSonPPb_forestv72_HLT40_HLT60.root",
  "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pPb_5_02TeV_pA2013/PA2013_HiForest_PromptReco_JSonPPb_forestv77.root"};
const double Pbp5Bound[nPbp5Files+1] = {60,120,200};

const int npp7Files = 3;
const char * pp7File[npp7Files] = {
  "/mnt/hadoop/cms/store/user/velicanu/mergedFF_forests/data/pp_7TeV_2011A_12Oct2013-v1/0.root ",
  "/mnt/hadoop/cms/store/user/velicanu/mergedFF_forests/data/pp_7TeV_2011A_12Oct2013-v1/0.root ",
  "/mnt/hadoop/cms/store/user/velicanu/mergedFF_forests/data/pp_7TeV_2011A_12Oct2013-v1/0.root "};
const double pp7Bound[npp7Files+1] = {60,80,140,200};


int setTrigger(const char* mode, int f, HiForest * h1)
{
  int trigger = 0;
  if(strcmp(mode,"pp2")==0)
  {
    if(f==0) trigger = h1->hlt.HLT_PAJet40_NoJetID_v1;
    if(f==1) trigger = h1->hlt.HLT_PAJet80_NoJetID_v1;
    lowBound = pp2Bound[f];
    upBound = pp2Bound[f+1];
  }


  if(strcmp(mode,"pPb5")==0)
  {
    if(f==0) trigger = h1->hlt.HLT_PAJet40_NoJetID_v1*(int)(h1->track.nRun<211313 && h1->track.nRun>=210676);
    if(f==1) trigger = h1->hlt.HLT_PAJet80_NoJetID_v1*(int)(h1->track.nRun<211313 && h1->track.nRun>=210676);
    lowBound = pPb5Bound[f];
    upBound = pPb5Bound[f+1];
  }

  if(strcmp(mode,"Pbp5")==0)
  {
    if(f==0) trigger = h1->hlt.HLT_PAJet40_NoJetID_v1*(int)(h1->track.nRun>=211313);
    if(f==1) trigger = h1->hlt.HLT_PAJet80_NoJetID_v1*(int)(h1->track.nRun>=211313);;
    lowBound = Pbp5Bound[f];
    upBound = Pbp5Bound[f+1];
  }


  if(strcmp(mode,"pp7")==0)
  {
    if(f==0) trigger = h1->hlt.HLT_Jet30_v1;
    if(f==1) trigger = h1->hlt.HLT_Jet60_v1;
    if(f==2) trigger = h1->hlt.HLT_Jet110_v1;
    lowBound = pp7Bound[f];
    upBound = pp7Bound[f+1];
  }

  return trigger;
}*/

