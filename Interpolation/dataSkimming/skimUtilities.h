
TFile * outf;
TTree * track;
TTree * ak3PF;
TTree * evt;

TFile * inf;
TTree * trackIn;
TTree * ak3PFIn;
TTree * skimIn;
TTree * evtIn;
TTree * hltIn;

//variables to be written
const int maxTrack = 25000;
int nTrk;
int nVtx;
double trkPt[maxTrack];
double trkEta[maxTrack];
double trkPhi[maxTrack];
double trkPtError[maxTrack];
double trkDzError1[maxTrack];
double trkDz1[maxTrack];
double trkDxyError1[maxTrack];
double trkDxy1[maxTrack];
int highPurity[maxTrack];
//double trkRmin[maxTrack];

const int maxJet = 500;
int nref;
double rawpt[maxJet];
double jtpt[maxJet];
double jteta[maxJet];
double jtphi[maxJet];
double chargedSum[maxJet];

int run;
int event;
float vz;
float hiHFplus;
float hiHFminus;
float hiHFplusEta4;
float hiHFminusEta4;
float hiHFhitPlus;
float hiHFhitMinus;


//unwritten variables cut on
int pcollisionEventSelection;
int pPAcollisionEventSelectionPA;
int HLT_PAJet80_NoJetID_v1;
int HLT_PAJet40_NoJetID_v1;
int HLT_PAZeroBiasPixel_SingleTrack_v1;
int pHBHENoiseFilter;

int fileSize;

void openOutFile(const char * mode, const char * trigger, int isMC, int date,int iteration)
{
  //outf = new TFile(Form("/mnt/hadoop/cms/store/user/abaty/FF_forests/skims/%s/%s%s_%d_%d_%d.root",mode,mode,trigger,isMC,date,iteration),"recreate");
  outf = new TFile(Form("/export/d00/scratch/abaty/skims/%s%s_%d_%d_%d.root",mode,trigger,isMC,date,iteration),"recreate");
  track = new TTree("track","track");
  ak3PF = new TTree("ak3PF","ak3PF");
  evt   = new TTree("evt","evt");

  track->Branch("nTrk",&nTrk,"nTrk/I");
  track->Branch("trkPt",&trkPt,"trkPt[nTrk]/F");
  track->Branch("trkEta",&trkEta,"trkEta[nTrk]/F");
  track->Branch("trkPhi",&trkPhi,"trkPhi[nTrk]/F");
  track->Branch("trkPtError",&trkPtError,"trkPtError[nTrk]/F");
  track->Branch("trkDzError1",&trkDzError1,"trkDzError1[nTrk]/F");
  track->Branch("trkDz1",&trkDz1,"trkDz1[nTrk]/F");
  track->Branch("trkDxyError1",&trkDxyError1,"trkDxyError1[nTrk]/F");
  track->Branch("trkDxy1",&trkDxy1,"trkDxy1[nTrk]/F");
  track->Branch("highPurity",&highPurity,"highPurity[nTrk]/O");
  track->Branch("nVtx",&nVtx,"nVtx/I"); 
  //track->Branch("trkRmin",&trkRmin,"trkRmin[nTrk]/F");

  ak3PF->Branch("nref",&nref,"nref/I");
  ak3PF->Branch("rawpt",&rawpt,"rawpt[nref]/F");
  ak3PF->Branch("jtpt",&jtpt,"jtpt[nref]/F");
  ak3PF->Branch("jteta",&jteta,"jteta[nref]/F");
  ak3PF->Branch("jtphi",&jtphi,"jtphi[nref]/F");
  ak3PF->Branch("chargedSum",&chargedSum,"chargedSum[nref]/F");

  evt->Branch("run",&run,"run/I");
  evt->Branch("vz",&vz,"vz/F");
  evt->Branch("hiHFplus",&hiHFplus,"hiHFplus/F");
  evt->Branch("hiHFminus",&hiHFminus,"hiHFminus/F"); 
  evt->Branch("hiHFplusEta4",&hiHFplusEta4,"hiHFplusEta4/F");
  evt->Branch("hiHFminusEta4",&hiHFminusEta4,"hiHFminusEta4/F"); 
  evt->Branch("hiHFhitPlus",&hiHFhitPlus,"hiHFhitPlus/F");
  evt->Branch("hiHFhitMinus",&hiHFhitMinus,"hiHFhitMinus/F"); 
  evt->Branch("evt",&event,"evt/I");

  if(isMC)
  {
    //placeholder
  }

  fileSize = 0;
  return;
}

void openInFile(const char * name, const char * mode, int isMC)
{
  inf = new TFile(name,"read");  
  
  trackIn = (TTree*)inf->Get("anaTrack/trackTree");
  if(trackIn == 0) trackIn = (TTree*) inf->Get("ppTrack/trackTree");
  ak3PFIn = (TTree*)inf->Get("ak3PFJetAnalyzer/t");
  skimIn = (TTree*)inf->Get("skimanalysis/HltTree");
  evtIn = (TTree*)inf->Get("hiEvtAnalyzer/HiTree");
  hltIn = (TTree*)inf->Get("hltanalysis/HltTree"); 
  
  if(isMC)
  {
    //place holder
  }

  //Setting addresses
  trackIn->SetBranchAddress("nTrk",&nTrk); 
  trackIn->SetBranchAddress("trkPt",&trkPt);
  trackIn->SetBranchAddress("trkEta",&trkEta);
  trackIn->SetBranchAddress("trkPhi",&trkPhi);
  trackIn->SetBranchAddress("trkPtError",&trkPtError);
  trackIn->SetBranchAddress("trkDzError1",&trkDzError1);
  trackIn->SetBranchAddress("trkDz1",&trkDz1);
  trackIn->SetBranchAddress("trkDxyError1",&trkDxyError1);
  trackIn->SetBranchAddress("trkDxy1",&trkDxy1);
  trackIn->SetBranchAddress("highPurity",&highPurity);
  trackIn->SetBranchAddress("nVtx",&nVtx);

  ak3PFIn->SetBranchAddress("nref",&nref);
  ak3PFIn->SetBranchAddress("rawpt",&rawpt);
  ak3PFIn->SetBranchAddress("jtpt",&jtpt);
  ak3PFIn->SetBranchAddress("jteta",&jteta);
  ak3PFIn->SetBranchAddress("jtphi",&jtphi);
  ak3PFIn->SetBranchAddress("chargedSum",&chargedSum);

  evtIn->SetBranchAddress("run",&run);
  evtIn->SetBranchAddress("vz",&vz);
  evtIn->SetBranchAddress("hiHFplus",&hiHFplus);
  evtIn->SetBranchAddress("hiHFminus",&hiHFminus);
  evtIn->SetBranchAddress("hiHFplusEta4",&hiHFplusEta4);
  evtIn->SetBranchAddress("hiHFminusEta4",&hiHFminusEta4);
  evtIn->SetBranchAddress("hiHFhitPlus",&hiHFhitPlus);
  evtIn->SetBranchAddress("hiHFhitMinus",&hiHFhitMinus);
  evtIn->SetBranchAddress("evt",&event);

  skimIn->SetBranchAddress("pcollisionEventSelection",&pcollisionEventSelection);
  skimIn->SetBranchAddress("pPAcollisionEventSelectionPA",&pPAcollisionEventSelectionPA);
  skimIn->SetBranchAddress("pHBHENoiseFilter",&pHBHENoiseFilter);

  hltIn->SetBranchAddress("HLT_PAJet80_NoJetID_v1",&HLT_PAJet80_NoJetID_v1);
  hltIn->SetBranchAddress("HLT_PAJet40_NoJetID_v1",&HLT_PAJet40_NoJetID_v1);
  hltIn->SetBranchAddress("HLT_PAZeroBiasPixel_SingleTrack_v1",&HLT_PAZeroBiasPixel_SingleTrack_v1);

  if(!(trackIn->GetEntries() == ak3PFIn->GetEntries() &&
       trackIn->GetEntries() == evtIn->GetEntries() &&
       trackIn->GetEntries() == skimIn->GetEntries() &&
       trackIn->GetEntries() == hltIn->GetEntries())) std::cout << "\n\nWarning, input files have missmatched number of entries!!!\n\n" << std::endl;

  return;
}

void closeOutFile()
{
  outf->cd();
  track->Write(); 
  ak3PF->Write();
  evt->Write();  
  outf->Close();
  delete outf;
  return;
}

void closeInFile()
{
  inf->cd();
  delete trackIn;
  delete evtIn;
  delete ak3PFIn;
  delete skimIn;
  delete hltIn;
  inf->Close();
  delete inf;
  return;
}

