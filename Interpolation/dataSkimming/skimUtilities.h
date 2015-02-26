//Written by Austin Baty on 26/02/2015

HiForest * h;
TFile * outf;
TTree * track;
TTree * ak3PF;
TTree * evt;

TBranch * b1_nTrk;
TBranch * b1_trkPt;
TBranch * b1_trkEta;
TBranch * b1_trkPhi;
TBranch * b1_trkPtError;
TBranch * b1_trkDzError1;
TBranch * b1_trkDz1;
TBranch * b1_trkDxyError1;
TBranch * b1_trkDxy1;
TBranch * b1_highPurity;
TBranch * b1_nVtx; 

TBranch * b1_nref;
TBranch * b1_rawpt;
TBranch * b1_jtpt;
TBranch * b1_jteta;
TBranch * b1_jtphi;
TBranch * b1_chargedSum;

TBranch * b1_run;
TBranch * b1_vz;
TBranch * b1_hiHFplus;
TBranch * b1_hiHFminus; 
TBranch * b1_hiHFplusEta4;
TBranch * b1_hiHFminusEta4; 
TBranch * b1_evt;

int fileSize;

//matches up the existing outfile and forest file pointers
void setAddresses()
{  
  b1_nTrk->SetAddress(&(h->track.nTrk));
  b1_trkPt->SetAddress(h->track.trkPt);
  b1_trkEta->SetAddress(h->track.trkEta);
  b1_trkPhi->SetAddress(h->track.trkPhi);
  b1_trkPtError->SetAddress(h->track.trkPtError);
  b1_trkDzError1->SetAddress(h->track.trkDzError1);
  b1_trkDz1->SetAddress(h->track.trkDz1);
  b1_trkDxyError1->SetAddress(h->track.trkDxyError1);
  b1_trkDxy1->SetAddress(h->track.trkDxy1);
  b1_highPurity->SetAddress(h->track.highPurity);
  b1_nVtx->SetAddress(&(h->track.nVtx));

  b1_nref->SetAddress(&(h->ak3PF.nref));
  b1_rawpt->SetAddress(h->ak3PF.rawpt);
  b1_jtpt->SetAddress(h->ak3PF.jtpt);
  b1_jteta->SetAddress(h->ak3PF.jteta);
  b1_jtphi->SetAddress(h->ak3PF.jtphi);
  b1_chargedSum->SetAddress(h->ak3PF.chargedSum);

  b1_run->SetAddress(&(h->evt.run));
  b1_vz->SetAddress(&(h->evt.vz));
  b1_hiHFplus->SetAddress(&(h->evt.hiHFplus));
  b1_hiHFminus->SetAddress(&(h->evt.hiHFminus));
  b1_hiHFplusEta4->SetAddress(&(h->evt.hiHFplusEta4));
  b1_hiHFminusEta4->SetAddress(&(h->evt.hiHFminusEta4));
  b1_evt->SetAddress(&(h->evt.evt));
}

//makes new output file
void setupOutputFile(const char * mode, const char * trigger, int isMC, int date,int iteration)
{   
  outf = new TFile(Form("/export/d00/scratch/abaty/skims/%s%s_%d_%d_%d.root",mode,trigger,isMC,date,iteration),"recreate");
  track = new TTree("track","track");
  ak3PF = new TTree("ak3PF","ak3PF");
  evt   = new TTree("evt","evt");

  b1_nTrk =         track->Branch("nTrk",NULL,"nTrk/I");
  b1_trkPt =        track->Branch("trkPt",NULL,"trkPt[nTrk]/F");
  b1_trkEta =       track->Branch("trkEta",NULL,"trkEta[nTrk]/F");
  b1_trkPhi =       track->Branch("trkPhi",NULL,"trkPhi[nTrk]/F");
  b1_trkPtError =   track->Branch("trkPtError",NULL,"trkPtError[nTrk]/F");
  b1_trkDzError1 =  track->Branch("trkDzError1",NULL,"trkDzError1[nTrk]/F");
  b1_trkDz1 =       track->Branch("trkDz1",NULL,"trkDz1[nTrk]/F");
  b1_trkDxyError1 = track->Branch("trkDxyError1",NULL,"trkDxyError1[nTrk]/F");
  b1_trkDxy1 =      track->Branch("trkDxy1",NULL,"trkDxy1[nTrk]/F");
  b1_highPurity =   track->Branch("highPurity",NULL,"highPurity[nTrk]/O");
  b1_nVtx =         track->Branch("nVtx",NULL,"nVtx/I"); 

  b1_nref =       ak3PF->Branch("nref",NULL,"nref/I");
  b1_rawpt =      ak3PF->Branch("rawpt",NULL,"rawpt[nref]/F");
  b1_jtpt =       ak3PF->Branch("jtpt",NULL,"jtpt[nref]/F");
  b1_jteta =      ak3PF->Branch("jteta",NULL,"jteta[nref]/F");
  b1_jtphi =      ak3PF->Branch("jtphi",NULL,"jtphi[nref]/F");
  b1_chargedSum = ak3PF->Branch("chargedSum",NULL,"chargedSum[nref]/F");

  b1_run =           evt->Branch("run",NULL,"run/I");
  b1_vz =            evt->Branch("vz",NULL,"vz/F");
  b1_hiHFplus =      evt->Branch("hiHFplus",NULL,"hiHFplus/F");
  b1_hiHFminus =     evt->Branch("hiHFminus",NULL,"hiHFminus/F"); 
  b1_hiHFplusEta4 =  evt->Branch("hiHFplusEta4",NULL,"hiHFplusEta4/F");
  b1_hiHFminusEta4 = evt->Branch("hiHFminusEta4",NULL,"hiHFminusEta4/F"); 
  b1_evt =           evt->Branch("evt",NULL,"evt/I");

  fileSize = 0;
  setAddresses();
}

void closeOutputFile()
{   
  //writing output
  outf->cd();
  track->Write(); 
  ak3PF->Write();
  evt->Write();  
  delete track;
  delete ak3PF;
  delete evt;
  outf->Close();
  delete outf;
}

//opens new forest file for reading
void openForestFile(const char * name, const char * mode, int isMC)
{ 
  if((strcmp(mode,"pPb5") == 0 || strcmp(mode,"Pbp5") == 0)) h = new HiForest(name,"forest",cPPb,isMC);
  else h = new HiForest(name,"forest",cPP,isMC);
  h->LoadNoTrees();
  h->hasEvtTree = true;
  h->hasSkimTree = true;
  h->hasHltTree = true;
  
  track->ResetBranchAddresses();
  ak3PF->ResetBranchAddresses();
  evt->ResetBranchAddresses();
  setAddresses();
}

//closes forest file for reading
void closeForestFile()
{ 
  h->~HiForest();  
  h=NULL;
  delete h;
}
