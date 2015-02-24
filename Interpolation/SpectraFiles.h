TH1D * h_jet;
TH2D * h_track;
TH2D * h_trackUE;
TH2D * h_track_xi;
TH2D * h_trackUE_xi;

double lowBound;
double upBound;

HiForest * h[5];
HiForest * mix;
const int npp2Files = 2;
const char * pp2File[npp2Files] = {
  "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pp_2_76TeV_pp2013/PP2013_HiForest_PromptReco_JSon_Jet40Jet60_ppTrack_forestv84.root",
  "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pp_2_76TeV_pp2013/PP2013_HiForest_PromptReco_JsonPP_Jet80_PPReco_forestv82.root" };
const double pp2Bound[npp2Files+1] = {60,100,200};

/*const int npPb5Files = 3;
const char * pPb5File[npPb5Files] = {
  "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pPb_5_02TeV_pA2013/PA2013_HiForest_PromptReco_KrisztianMB_JSonPPb_forestv84.root",
  "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pPb_5_02TeV_pA2013/PA2013_HiForest_PromptReco_JSonPPb_forestv72_HLT40_HLT60.root",
  "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pPb_5_02TeV_pA2013/PA2013_HiForest_PromptReco_JSonPPb_forestv77.root"};
const double pPb5Bound[npPb5Files+1] = {60,80,120,200};

const int nPbp5Files = 3;
const char * Pbp5File[nPbp5Files] = {
  "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pPb_5_02TeV_pA2013/PA2013_HiForest_PromptReco_KrisztianMB_JSonPPb_forestv84.root",
  "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pPb_5_02TeV_pA2013/PA2013_HiForest_PromptReco_JSonPPb_forestv72_HLT40_HLT60.root",
  "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pPb_5_02TeV_pA2013/PA2013_HiForest_PromptReco_JSonPPb_forestv77.root"};
const double Pbp5Bound[nPbp5Files+1] = {60,80,120,200};*/

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
/*
  if(strcmp(mode,"pPb5")==0)
  {
    if(f==0) trigger = (int)(h1->track.nRun<211313 && h1->track.nRun>=210676);
    if(f==1) trigger = h1->hlt.HLT_PAJet40_NoJetID_v1*(int)(h1->track.nRun<211313 && h1->track.nRun>=210676);
    if(f==2) trigger = h1->hlt.HLT_PAJet80_NoJetID_v1*(int)(h1->track.nRun<211313 && h1->track.nRun>=210676);
    lowBound = pPb5Bound[f];
    upBound = pPb5Bound[f+1];
  }

  if(strcmp(mode,"Pbp5")==0)
  {
    if(f==0) trigger = (int)(h1->track.nRun>=211313);
    if(f==1) trigger = h1->hlt.HLT_PAJet40_NoJetID_v1*(int)(h1->track.nRun>=211313);
    if(f==2) trigger = h1->hlt.HLT_PAJet80_NoJetID_v1*(int)(h1->track.nRun>=211313);;
    lowBound = Pbp5Bound[f];
    upBound = Pbp5Bound[f+1];
  }
*/

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
}

