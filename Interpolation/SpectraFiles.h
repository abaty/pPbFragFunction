TH1D * h_jet;
TH2D * h_track;
TH2D * h_trackUE;
TH2D * h_track_xi;
TH2D * h_trackUE_xi;

double lowBound;
double upBound;

HiForest * h[5];

const int npp2Files = 2;
const char * pp2File[npp2Files] = {
  "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pp_2_76TeV_pp2013/PP2013_HiForest_PromptReco_JSon_Jet40Jet60_ppTrack_forestv84.root",
  "/mnt/hadoop/cms/store/user/abaty/FF_forests/data/pp_2_76TeV_pp2013/PP2013_HiForest_PromptReco_JsonPP_Jet80_PPReco_forestv82.root" };
const double pp2Bound[npp2Files+1] = {60,100,200};

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

