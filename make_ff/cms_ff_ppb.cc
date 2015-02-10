#include <cmath>

#define STANDALONE
#include <TROOT.h>
#include <TSystem.h>
#include <TMath.h>
#include <TFile.h>
#include <TTree.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TH2D.h>
#include "factorizedPtCorr.h"
#include "lorentz.h"

//need to enable this here and below at the JEC flag to run on 7tev
//#include "JEC7tev/get7tevPt.h"

void cms_ff_ppb(const char *filename_list, const char *trigger_name, const int is_mc = 0, const int perp_track = 1, const double pseudorapidity_min = 0, const double pseudorapidity_max = 1, const double boost_ppb = 1, const long select_index_jet = -1, const unsigned long reflect_type = 0, const unsigned long parallel_offset = 0, const unsigned long parallel_stride = 1)
{
	char *filename = strdup(filename_list);
	fprintf(stderr, "%s:%d:\n", __FILE__, __LINE__);

	const sampleType sType = kPPDATA;

	InitCorrFiles(sType);
	InitCorrHists(sType);

	TApplication application();
	TCanvas canvas("canvas", "", 720 + 4, 720 + 28);

	TH1D root_histogram_jet("root_histogram_jet", "", 15 * 8, 0, 300);
	root_histogram_jet.Sumw2();

	TH1D root_histogram_jet_reflected("root_histogram_jet_reflected", "", 15 * 8, 0, 300);
	root_histogram_jet_reflected.Sumw2();
	

	TH2D root_histogram_track("root_histogram_track", "", 15 * 8, 0, 300, perp_track ? 39 : 28, -1.5, 5.5);
	TH2D root_histogram_track_reflected("root_histogram_track_reflected", "", 15 * 8, 0, 300, perp_track ? 39 : 28, -1.5, 5.5);

	if (perp_track) {
		const double axis[40] = {
			0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8,
			2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4,
			19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6,
			120.8, 138, 155.2, 172.4, 189.6, 206.8
		};

		root_histogram_track.GetYaxis()->Set(39, axis);
		root_histogram_track_reflected.GetYaxis()->Set(39, axis);
	}
	root_histogram_track.Sumw2();
	root_histogram_track_reflected.Sumw2();

	TH2D root_histogram_pf("root_histogram_pf", "", 15 * 8, 0, 300, perp_track ? 39 : 28, -1.5, 5.5);
	TH2D root_histogram_pf_reflected("root_histogram_pf_reflected", "", 15 * 8, 0, 300, perp_track ? 39 : 28, -1.5, 5.5);

	if (perp_track) {
		const double axis[40] = {
			0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8,
			2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4,
			19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6,
			120.8, 138, 155.2, 172.4, 189.6, 206.8
		};

		root_histogram_pf.GetYaxis()->Set(39, axis);
		root_histogram_pf_reflected.GetYaxis()->Set(39, axis);
	}
	root_histogram_pf.Sumw2();
	root_histogram_pf_reflected.Sumw2();

	while (filename[0] != '\0') {
		fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, filename);

		char *colon = NULL;

		if (strncmp(filename, "root::", 6) == 0) {
			colon = strchr(filename + 7, ':');
		}
		else if (strncmp(filename, "root:", 5) == 0) {
			colon = strchr(filename + 6, ':');
		}
		else {
			colon = strchr(filename, ':');
		}

		if (colon == NULL && strlen(filename) > 0) {
			colon = filename + strlen(filename);
		}

		if (colon != NULL) {
			fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, filename);
			*colon = '\0';
			fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, filename);

	TFile *f = TFile::Open(filename);
	if (colon - filename < strlen(filename)) {
	filename = colon + 1;
	}
	else {
	*filename = '\0';
	}

	TTree *pfTree = dynamic_cast<TTree *>(gDirectory->Get("pfcandAnalyzer/pfTree"));

	Int_t nPFpart;
	Int_t pfId[32768];
	Float_t pfPt[32768];
	Float_t pfEta[32768];
	Float_t pfPhi[32768];

	if (pfTree != NULL) {
		pfTree->SetBranchAddress("nPFpart", &nPFpart);
		pfTree->SetBranchAddress("pfId", pfId);
		pfTree->SetBranchAddress("pfPt", pfPt);
		pfTree->SetBranchAddress("pfEta", pfEta);
		pfTree->SetBranchAddress("pfPhi", pfPhi);
	}

	fprintf(stderr, "%s:%d:\n", __FILE__, __LINE__);

	TTree *hiTree = dynamic_cast<TTree *>(gDirectory->Get("hiEvtAnalyzer/HiTree"));

	Int_t run;
	Int_t lumi;
	Float_t vx;
	Float_t vy;
	Float_t vz;
	Int_t hiBin;
	Float_t hiHF;
	Float_t hiHFplus;
	Float_t hiHFminus;
	Float_t hiZDC;
	Float_t hiZDCplus;
	Float_t hiZDCminus;
	Float_t hiHFhit;
	Float_t hiHFhitPlus;
	Float_t hiHFhitMinus;
	Float_t hiET;
	Float_t hiEE;
	Float_t hiEB;
	Float_t hiEEplus;
	Float_t hiEEminus;
	Int_t hiNpix;
	Int_t hiNpixelTracks;
	Int_t hiNtracks;
	Int_t hiNtracksPtCut;
	Int_t hiNtracksEtaCut;
	Int_t hiNtracksEtaPtCut;
	Int_t hiNevtPlane;
	Float_t hiEvtPlanes[38];

if (hiTree != NULL) {
	// Set branch addresses.
	hiTree->SetBranchAddress("run",&run);
	hiTree->SetBranchAddress("lumi",&lumi);
	hiTree->SetBranchAddress("vx",&vx);
	hiTree->SetBranchAddress("vy",&vy);
	hiTree->SetBranchAddress("vz",&vz);
	hiTree->SetBranchAddress("hiBin",&hiBin);
	hiTree->SetBranchAddress("hiHF",&hiHF);
	hiTree->SetBranchAddress("hiHFplus",&hiHFplus);
	hiTree->SetBranchAddress("hiHFminus",&hiHFminus);
	hiTree->SetBranchAddress("hiZDC",&hiZDC);
	hiTree->SetBranchAddress("hiZDCplus",&hiZDCplus);
	hiTree->SetBranchAddress("hiZDCminus",&hiZDCminus);
	hiTree->SetBranchAddress("hiHFhit",&hiHFhit);
	hiTree->SetBranchAddress("hiHFhitPlus",&hiHFhitPlus);
	hiTree->SetBranchAddress("hiHFhitMinus",&hiHFhitMinus);
	hiTree->SetBranchAddress("hiET",&hiET);
	hiTree->SetBranchAddress("hiEE",&hiEE);
	hiTree->SetBranchAddress("hiEB",&hiEB);
	hiTree->SetBranchAddress("hiEEplus",&hiEEplus);
	hiTree->SetBranchAddress("hiEEminus",&hiEEminus);
	hiTree->SetBranchAddress("hiNpix",&hiNpix);
	hiTree->SetBranchAddress("hiNpixelTracks",&hiNpixelTracks);
	hiTree->SetBranchAddress("hiNtracks",&hiNtracks);
	hiTree->SetBranchAddress("hiNtracksPtCut",&hiNtracksPtCut);
	hiTree->SetBranchAddress("hiNtracksEtaCut",&hiNtracksEtaCut);
	hiTree->SetBranchAddress("hiNtracksEtaPtCut",&hiNtracksEtaPtCut);
	hiTree->SetBranchAddress("hiNevtPlane",&hiNevtPlane);
	hiTree->SetBranchAddress("hiEvtPlanes",hiEvtPlanes);
}

	fprintf(stderr, "%s:%d:\n", __FILE__, __LINE__);

	TTree *t = dynamic_cast<TTree *>(gDirectory->Get("ak3PFJetAnalyzer/t"));

	Int_t evt;
	// Float_t b;
	Int_t nref;
	Float_t rawpt[32768];
	Float_t jtpt[32768];
	Float_t jteta[32768];
	Float_t jty[32768];
	Float_t jtphi[32768];
	Float_t jtpu[32768];
	Int_t beamId1;
	Int_t beamId2;
	Float_t pthat;
	Float_t refpt[32768];
	Float_t refeta[32768];
	Float_t refy[32768];
	Float_t refphi[32768];
	Float_t refdphijt[32768];
	Float_t refdrjt[32768];
	Float_t refparton_pt[32768];
	Int_t refparton_flavor[32768];
	Int_t refparton_flavorForB[32768];
	Int_t subid[32768];

	// Set branch addresses.
	t->SetBranchAddress("evt", &evt);
	// t->SetBranchAddress("b", &b);
	t->SetBranchAddress("nref", &nref);
	t->SetBranchAddress("rawpt", rawpt);
	t->SetBranchAddress("jtpt", jtpt);
	t->SetBranchAddress("jteta", jteta);
	t->SetBranchAddress("jty", jty);
	t->SetBranchAddress("jtphi", jtphi);
	t->SetBranchAddress("jtpu", jtpu);
	t->SetBranchAddress("beamId1", &beamId1);
	t->SetBranchAddress("beamId2", &beamId2);
	t->SetBranchAddress("pthat", &pthat);
	t->SetBranchAddress("refpt", refpt);
	t->SetBranchAddress("refeta", refeta);
	t->SetBranchAddress("refy", refy);
	t->SetBranchAddress("refphi", refphi);
	t->SetBranchAddress("refdphijt", refdphijt);
	t->SetBranchAddress("refdrjt", refdrjt);
	t->SetBranchAddress("refparton_pt", refparton_pt);
	t->SetBranchAddress("refparton_flavor", refparton_flavor);
	t->SetBranchAddress("refparton_flavorForB", refparton_flavorForB);
	t->SetBranchAddress("subid", subid);

	fprintf(stderr, "%s:%d:\n", __FILE__, __LINE__);

	TTree *trackTree = dynamic_cast<TTree *>(gDirectory->Get("ppTrack/trackTree"));
	if (trackTree == NULL) {
		trackTree = dynamic_cast<TTree *>(gDirectory->Get("anaTrack/trackTree"));
	}

//Declaration of leaves types
   Int_t           nEv;
   Int_t           nLumi;
   Int_t           nBX;
   Int_t           nRun;
   Int_t           nv;
   Int_t           nTrk;
   Float_t         trkPt[32768];
   Float_t         trkPtError[32768];
   Int_t           trkNHit[32768];
   Int_t           trkNlayer[32768];
   Float_t         trkEta[32768];
   Float_t         trkPhi[32768];
   Bool_t          highPurity[32768];
   Float_t         trkChi2[32768];
   Float_t         trkNdof[32768];
   Float_t         trkDxy1[32768];
   Float_t         trkDxyError1[32768];
   Float_t         trkDz1[32768];
   Float_t         trkDzError1[32768];
   Bool_t          trkFake[32768];
   Float_t         trkAlgo[32768];
   Int_t           pfType[32768];
   Float_t         pfCandPt[32768];
   Float_t         pfSumEcal[32768];
   Float_t         pfSumHcal[32768];
   Int_t           nVtx;

   // Set branch addresses.
   trackTree->SetBranchAddress("nEv",&nEv);
   trackTree->SetBranchAddress("nLumi",&nLumi);
   trackTree->SetBranchAddress("nBX",&nBX);
   trackTree->SetBranchAddress("nRun",&nRun);
   trackTree->SetBranchAddress("nv",&nv);
   trackTree->SetBranchAddress("nTrk",&nTrk);
   trackTree->SetBranchAddress("trkPt",trkPt);
   trackTree->SetBranchAddress("trkPtError",trkPtError);
   trackTree->SetBranchAddress("trkNHit",trkNHit);
   trackTree->SetBranchAddress("trkNlayer",trkNlayer);
   trackTree->SetBranchAddress("trkEta",trkEta);
   trackTree->SetBranchAddress("trkPhi",trkPhi);
   trackTree->SetBranchAddress("highPurity",highPurity);
   trackTree->SetBranchAddress("trkChi2",trkChi2);
   trackTree->SetBranchAddress("trkNdof",trkNdof);
   trackTree->SetBranchAddress("trkDxy1",trkDxy1);
   trackTree->SetBranchAddress("trkDxyError1",trkDxyError1);
   trackTree->SetBranchAddress("trkDz1",trkDz1);
   trackTree->SetBranchAddress("trkDzError1",trkDzError1);
   trackTree->SetBranchAddress("trkFake",trkFake);
   trackTree->SetBranchAddress("trkAlgo",trkAlgo);
   trackTree->SetBranchAddress("pfType",pfType);
   trackTree->SetBranchAddress("pfCandPt",pfCandPt);
   trackTree->SetBranchAddress("pfSumEcal",pfSumEcal);
   trackTree->SetBranchAddress("pfSumHcal",pfSumHcal);
   trackTree->SetBranchAddress("nVtx",&nVtx);

	fprintf(stderr, "%s:%d:\n", __FILE__, __LINE__);

	TTree *HltTree = dynamic_cast<TTree *>(gDirectory->Get("hltanalysis/HltTree"));

	fprintf(stderr, "%s:%d: HltTree = %p\n", __FILE__, __LINE__, HltTree);

//Declaration of leaves types
   Int_t           NL1IsolEm;
   Float_t         L1IsolEmEt[4];
   Float_t         L1IsolEmE[4];
   Float_t         L1IsolEmEta[4];
   Float_t         L1IsolEmPhi[4];
   Int_t           NL1NIsolEm;
   Float_t         L1NIsolEmEt[4];
   Float_t         L1NIsolEmE[4];
   Float_t         L1NIsolEmEta[4];
   Float_t         L1NIsolEmPhi[4];
   Int_t           NL1Mu;
   Float_t         L1MuPt[4];
   Float_t         L1MuE[4];
   Float_t         L1MuEta[4];
   Float_t         L1MuPhi[4];
   Int_t           L1MuIsol[4];
   Int_t           L1MuMip[4];
   Int_t           L1MuFor[4];
   Int_t           L1MuRPC[4];
   Int_t           L1MuQal[4];
   Int_t           L1MuChg[4];
   Int_t           NL1CenJet;
   Float_t         L1CenJetEt[4];
   Float_t         L1CenJetE[4];
   Float_t         L1CenJetEta[4];
   Float_t         L1CenJetPhi[4];
   Int_t           NL1ForJet;
   Float_t         L1ForJetEt[4];
   Float_t         L1ForJetE[4];
   Float_t         L1ForJetEta[4];
   Float_t         L1ForJetPhi[4];
   Int_t           NL1Tau;
   Float_t         L1TauEt[4];
   Float_t         L1TauE[4];
   Float_t         L1TauEta[4];
   Float_t         L1TauPhi[4];
   Float_t         L1Met;
   Float_t         L1MetPhi;
   Float_t         L1EtTot;
   Float_t         L1Mht;
   Float_t         L1MhtPhi;
   Float_t         L1EtHad;
   Int_t           L1HfRing1EtSumPositiveEta;
   Int_t           L1HfRing2EtSumPositiveEta;
   Int_t           L1HfRing1EtSumNegativeEta;
   Int_t           L1HfRing2EtSumNegativeEta;
   Int_t           L1HfTowerCountPositiveEtaRing1;
   Int_t           L1HfTowerCountNegativeEtaRing1;
   Int_t           L1HfTowerCountPositiveEtaRing2;
   Int_t           L1HfTowerCountNegativeEtaRing2;
   Int_t           Run;
   Int_t           Event;
   Int_t           LumiBlock;
   Int_t           Bx;
   Int_t           Orbit;
   Double_t        AvgInstDelLumi;
   Int_t           trigger_scaled;
   Int_t           trigger_prescale;

   if (HltTree != NULL) {
   // Set branch addresses.
   HltTree->SetBranchAddress("NL1IsolEm",&NL1IsolEm);
   HltTree->SetBranchAddress("L1IsolEmEt",L1IsolEmEt);
   HltTree->SetBranchAddress("L1IsolEmE",L1IsolEmE);
   HltTree->SetBranchAddress("L1IsolEmEta",L1IsolEmEta);
   HltTree->SetBranchAddress("L1IsolEmPhi",L1IsolEmPhi);
   HltTree->SetBranchAddress("NL1NIsolEm",&NL1NIsolEm);
   HltTree->SetBranchAddress("L1NIsolEmEt",L1NIsolEmEt);
   HltTree->SetBranchAddress("L1NIsolEmE",L1NIsolEmE);
   HltTree->SetBranchAddress("L1NIsolEmEta",L1NIsolEmEta);
   HltTree->SetBranchAddress("L1NIsolEmPhi",L1NIsolEmPhi);
   HltTree->SetBranchAddress("NL1Mu",&NL1Mu);
   HltTree->SetBranchAddress("L1MuPt",L1MuPt);
   HltTree->SetBranchAddress("L1MuE",L1MuE);
   HltTree->SetBranchAddress("L1MuEta",L1MuEta);
   HltTree->SetBranchAddress("L1MuPhi",L1MuPhi);
   HltTree->SetBranchAddress("L1MuIsol",L1MuIsol);
   HltTree->SetBranchAddress("L1MuMip",L1MuMip);
   HltTree->SetBranchAddress("L1MuFor",L1MuFor);
   HltTree->SetBranchAddress("L1MuRPC",L1MuRPC);
   HltTree->SetBranchAddress("L1MuQal",L1MuQal);
   HltTree->SetBranchAddress("L1MuChg",L1MuChg);
   HltTree->SetBranchAddress("NL1CenJet",&NL1CenJet);
   HltTree->SetBranchAddress("L1CenJetEt",L1CenJetEt);
   HltTree->SetBranchAddress("L1CenJetE",L1CenJetE);
   HltTree->SetBranchAddress("L1CenJetEta",L1CenJetEta);
   HltTree->SetBranchAddress("L1CenJetPhi",L1CenJetPhi);
   HltTree->SetBranchAddress("NL1ForJet",&NL1ForJet);
   HltTree->SetBranchAddress("L1ForJetEt",L1ForJetEt);
   HltTree->SetBranchAddress("L1ForJetE",L1ForJetE);
   HltTree->SetBranchAddress("L1ForJetEta",L1ForJetEta);
   HltTree->SetBranchAddress("L1ForJetPhi",L1ForJetPhi);
   HltTree->SetBranchAddress("NL1Tau",&NL1Tau);
   HltTree->SetBranchAddress("L1TauEt",L1TauEt);
   HltTree->SetBranchAddress("L1TauE",L1TauE);
   HltTree->SetBranchAddress("L1TauEta",L1TauEta);
   HltTree->SetBranchAddress("L1TauPhi",L1TauPhi);
   HltTree->SetBranchAddress("L1Met",&L1Met);
   HltTree->SetBranchAddress("L1MetPhi",&L1MetPhi);
   HltTree->SetBranchAddress("L1EtTot",&L1EtTot);
   HltTree->SetBranchAddress("L1Mht",&L1Mht);
   HltTree->SetBranchAddress("L1MhtPhi",&L1MhtPhi);
   HltTree->SetBranchAddress("L1EtHad",&L1EtHad);
   HltTree->SetBranchAddress("L1HfRing1EtSumPositiveEta",&L1HfRing1EtSumPositiveEta);
   HltTree->SetBranchAddress("L1HfRing2EtSumPositiveEta",&L1HfRing2EtSumPositiveEta);
   HltTree->SetBranchAddress("L1HfRing1EtSumNegativeEta",&L1HfRing1EtSumNegativeEta);
   HltTree->SetBranchAddress("L1HfRing2EtSumNegativeEta",&L1HfRing2EtSumNegativeEta);
   HltTree->SetBranchAddress("L1HfTowerCountPositiveEtaRing1",&L1HfTowerCountPositiveEtaRing1);
   HltTree->SetBranchAddress("L1HfTowerCountNegativeEtaRing1",&L1HfTowerCountNegativeEtaRing1);
   HltTree->SetBranchAddress("L1HfTowerCountPositiveEtaRing2",&L1HfTowerCountPositiveEtaRing2);
   HltTree->SetBranchAddress("L1HfTowerCountNegativeEtaRing2",&L1HfTowerCountNegativeEtaRing2);
   HltTree->SetBranchAddress("Run",&Run);
   HltTree->SetBranchAddress("Event",&Event);
   HltTree->SetBranchAddress("LumiBlock",&LumiBlock);
   HltTree->SetBranchAddress("Bx",&Bx);
   HltTree->SetBranchAddress("Orbit",&Orbit);
   HltTree->SetBranchAddress("AvgInstDelLumi",&AvgInstDelLumi);
   }

	fprintf(stderr, "%s:%d:\n", __FILE__, __LINE__);

   if (trigger_name[0] != '\0') {
	   char buf[4096];

	   for (char c = '0'; c <= '9'; c++) {
		   snprintf(buf, 4096, "%s", trigger_name);
		   if (c != '0' && buf[strlen(buf) - 2] == 'v') {
			   buf[strlen(buf) - 1] = c;
		   }

		   const int r1 = HltTree->SetBranchAddress(buf, &trigger_scaled);

		   snprintf(buf, 4096, "%s_Prescl", trigger_name);
		   if (c != '0' && buf[strlen(buf) - 9] == 'v') {
			   buf[strlen(buf) - 8] = c;
		   }

		   const int r2 = HltTree->SetBranchAddress(buf, &trigger_prescale);

		   if (r1 != -5 && r2 != -5) {
			   fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, buf);
			   break;
		   }
	   }
   }

	fprintf(stderr, "%s:%d:\n", __FILE__, __LINE__);

	TTree *HltTree2 = dynamic_cast<TTree *>(gDirectory->Get("skimanalysis/HltTree"));

//Declaration of leaves types
   Int_t           superFilterPath;
   Int_t           reco_extra;
   Int_t           reco_extra_jet;
   Int_t           pat_step;
   Int_t           ana_step;
   Int_t           pcollisionEventSelection;
   Int_t           pHBHENoiseFilter;
   Int_t           phiEcalRecHitSpikeFilter;
   Int_t           pPAcollisionEventSelectionPA;
   Int_t           phfPosFilter3;
   Int_t           phfNegFilter3;
   Int_t           phfPosFilter2;
   Int_t           phfNegFilter2;
   Int_t           phfPosFilter1;
   Int_t           phfNegFilter1;
   Int_t           phltPixelClusterShapeFilter;
   Int_t           pprimaryvertexFilter;
   Int_t           pBeamScrapingFilter;
   Int_t           pVertexFilterCutG;
   Int_t           pVertexFilterCutGloose;
   Int_t           pVertexFilterCutGtight;
   Int_t           pVertexFilterCutGplus;
   Int_t           pVertexFilterCutE;
   Int_t           pVertexFilterCutEandG;
   Int_t           hltAna;

   if (HltTree2 != NULL) {
   // Set branch addresses.
   HltTree2->SetBranchAddress("superFilterPath",&superFilterPath);
   HltTree2->SetBranchAddress("reco_extra",&reco_extra);
   HltTree2->SetBranchAddress("reco_extra_jet",&reco_extra_jet);
   HltTree2->SetBranchAddress("pat_step",&pat_step);
   HltTree2->SetBranchAddress("ana_step",&ana_step);
   HltTree2->SetBranchAddress("pcollisionEventSelection",&pcollisionEventSelection);
   HltTree2->SetBranchAddress("pHBHENoiseFilter",&pHBHENoiseFilter);
   HltTree2->SetBranchAddress("phiEcalRecHitSpikeFilter",&phiEcalRecHitSpikeFilter);
   HltTree2->SetBranchAddress("pPAcollisionEventSelectionPA",&pPAcollisionEventSelectionPA);
   HltTree2->SetBranchAddress("phfPosFilter3",&phfPosFilter3);
   HltTree2->SetBranchAddress("phfNegFilter3",&phfNegFilter3);
   HltTree2->SetBranchAddress("phfPosFilter2",&phfPosFilter2);
   HltTree2->SetBranchAddress("phfNegFilter2",&phfNegFilter2);
   HltTree2->SetBranchAddress("phfPosFilter1",&phfPosFilter1);
   HltTree2->SetBranchAddress("phfNegFilter1",&phfNegFilter1);
   HltTree2->SetBranchAddress("phltPixelClusterShapeFilter",&phltPixelClusterShapeFilter);
   HltTree2->SetBranchAddress("pprimaryvertexFilter",&pprimaryvertexFilter);
   HltTree2->SetBranchAddress("pBeamScrapingFilter",&pBeamScrapingFilter);
   HltTree2->SetBranchAddress("pVertexFilterCutG",&pVertexFilterCutG);
   HltTree2->SetBranchAddress("pVertexFilterCutGloose",&pVertexFilterCutGloose);
   HltTree2->SetBranchAddress("pVertexFilterCutGtight",&pVertexFilterCutGtight);
   HltTree2->SetBranchAddress("pVertexFilterCutGplus",&pVertexFilterCutGplus);
   HltTree2->SetBranchAddress("pVertexFilterCutE",&pVertexFilterCutE);
   HltTree2->SetBranchAddress("pVertexFilterCutEandG",&pVertexFilterCutEandG);
   HltTree2->SetBranchAddress("hltAna",&hltAna);
   }

	//size_t nentries = trackTree->GetEntries();
	size_t nentries = 100000;

	size_t event_count = 0;
	size_t jet_count = 0;

	for (size_t i = parallel_offset; i < nentries; i += parallel_stride) {
		if (pfTree != NULL) {
			pfTree->GetEntry(i);
		}
		else {
			nPFpart = 0;
		}
		if (hiTree != NULL) {
			hiTree->GetEntry(i);
		}
		else {
			hiBin = 199;
		}
		t->GetEntry(i);
		trackTree->GetEntry(i);
		if (HltTree != NULL) {
			HltTree->GetEntry(i);
		}
		if (HltTree2 != NULL) {
			HltTree2->GetEntry(i);
		}

		const double boost_pseudorapidity = 0.4654094531 * boost_ppb;

		if (i == 0) {
			fprintf(stderr, "%s:%d: boost_pseudorapidity = %f\n", __FILE__, __LINE__, boost_pseudorapidity);
		}

		if (((pcollisionEventSelection != 0 ||
			  pPAcollisionEventSelectionPA != 0) &&
			 (is_mc || pHBHENoiseFilter != 0)) &&
			(trigger_name[0] == '\0' || trigger_scaled != 0)
//JEC Flag
#if 0
			&& nVtx >= 2 && nVtx <= 12
#endif
			&& jtpt[0] >= 15
		) {
			event_count++;
			for (int j = 0; j < nref; j++) {
				jteta[j] += boost_pseudorapidity;
//JEC Flag
#if 0
       			jtpt[j] = get7tevPt(rawpt[j], jteta[j],nVtx);
#endif
			}
			for (int j = 0; j < nTrk; j++) {
				trkEta[j] += boost_pseudorapidity;
			}
			for (int j = 0; j < nPFpart; j++) {
				pfEta[j] += boost_pseudorapidity;
			}

			long index_jet = 0;

			for (int j = 0; j < nref; j++) {
				if (fabs(jteta[j]) >= pseudorapidity_min && fabs(jteta[j]) < pseudorapidity_max) {
					if (select_index_jet == -1 || select_index_jet == index_jet) {
						root_histogram_jet.Fill(jtpt[j]);

						snowmass_vector_t
							pjs(0, jtpt[j], jteta[j], jtphi[j]);

						pjs.set_lightlike_time();

						lorentz_vector_t pjl(pjs);

						snowmass_vector_t pjsr;

						if (reflect_type == 1) {
							pjsr = snowmass_vector_t(0, jtpt[j], jteta[j], angular_range_reduce(jtphi[j] + 0.5 * M_PI));
						}
						else {
							pjsr = snowmass_vector_t(0, jtpt[j], -jteta[j], jtphi[j]);
						}

						pjsr.set_lightlike_time();

						lorentz_vector_t pjlr(pjsr);

						for (int k = 0; k < nref; k++) {
							snowmass_vector_t
								pts(0, jtpt[k], jteta[k], jtphi[k]);

							pts.set_lightlike_time();

							lorentz_vector_t ptl(pts);

							const float dr_square = pts.radial_distance_square(pjs);

							if (dr_square < 0.3 * 0.3 && root_histogram_jet_reflected.GetXaxis()->FindBin(jtpt[k]) >= root_histogram_jet_reflected.GetXaxis()->FindBin(jtpt[j])) {
								root_histogram_jet_reflected.Fill(jtpt[j]);
							}
						}

						for (int k = 0; k < nTrk; k++) {
							snowmass_vector_t
								pts(0, trkPt[k], trkEta[k], trkPhi[k]);

							pts.set_lightlike_time();

							lorentz_vector_t ptl(pts);

							const float dr_square = pts.radial_distance_square(pjs);
							const float z = ptl.longitudinal_fraction_of(pjl);

							if (dr_square < 0.3 * 0.3 && trkPt[k] > 0.5 && trkPt[k] < 1e+5 && highPurity[k] && fabsf(trkDxy1[k]) / trkDxyError1[k] < 3 && fabsf(trkDz1[k]) / trkDzError1[k] < 3 && trkPtError[k] /trkPt[k] < 0.1) {
								float correction = factorizedPtCorr(getPtBin(trkPt[k], sType), hiBin, trkPt[k], trkPhi[k], trkEta[k], sqrtf(dr_square), sType);
								if (std::isfinite(correction)) {
									if (jtpt[j] >= 100 && z > log(1.0 / 0.5)) {
						
									}
									if (perp_track) {
										root_histogram_track.Fill(jtpt[j], trkPt[k], correction);
									}
									else {
										root_histogram_track.Fill(jtpt[j], log(1.0 / z), correction);
									}
								}
							}
						}
						for (int k = 0; k < nTrk; k++) {
							snowmass_vector_t
								pts(0, trkPt[k], -trkEta[k], trkPhi[k]);

							pts.set_lightlike_time();

							lorentz_vector_t ptl(pts);

							const float dr_square = pts.radial_distance_square(pjs);
							const float z = ptl.longitudinal_fraction_of(pjl);

							if (dr_square < 0.3 * 0.3 && trkPt[k] > 0.5 && trkPt[k] < 1e+5 && highPurity[k] && fabsf(trkDxy1[k]) / trkDxyError1[k] < 3 && fabsf(trkDz1[k]) / trkDzError1[k] < 3 && trkPtError[k] /trkPt[k] < 0.1) {
								float correction = factorizedPtCorr(getPtBin(trkPt[k], sType), hiBin, trkPt[k], trkPhi[k], trkEta[k], sqrtf(dr_square), sType);
								if (std::isfinite(correction)) {
									if (perp_track) {
										root_histogram_track_reflected.Fill(jtpt[j], trkPt[k], correction);
									}
									else {
										root_histogram_track_reflected.Fill(jtpt[j], log(1.0 / z), correction);
									}
								}
							}
						}

						for (int k = 0; k < nPFpart; k++) {
							if (pfId[k] >= 1 && pfId[k] <= 3) {
								snowmass_vector_t
									pps(0, pfPt[k], pfEta[k], pfPhi[k]);

								pps.set_lightlike_time();

								lorentz_vector_t ppl(pps);

								const float dr_square = pps.radial_distance_square(pjs);
								const float z = ppl.longitudinal_fraction_of(pjl);

								if (dr_square < 0.3 * 0.3) {
									if (perp_track) {
										root_histogram_pf.Fill(jtpt[j], perp_track);
									}
									else {
										root_histogram_pf.Fill(jtpt[j], log(1.0 / z));
									}
								}
							}
						}

						jet_count++;
					}
					index_jet++;
				}
			}
		}
		if (i % 25000 == 0) {
			fprintf(stderr, "%s:%d: %lu/%lu %lu %lu\n", __FILE__, __LINE__, i, nentries, jet_count, event_count);

	fprintf(stderr, "%s:%d: \n", __FILE__, __LINE__);
        root_histogram_jet.SetDirectory(0);
        root_histogram_track.SetDirectory(0);
        root_histogram_track_reflected.SetDirectory(0);
        root_histogram_pf.SetDirectory(0);

	root_histogram_jet.Draw("");
	root_histogram_track.Draw("same");
	root_histogram_track_reflected.Draw("same");
	root_histogram_pf.Draw("same");

        TFile * outf = new TFile("pPb_jet80.root","recreate");
        root_histogram_jet.Write();
        root_histogram_track.Write();
        root_histogram_track_reflected.Write();
        root_histogram_pf.Write();
                }
        }
        f->Close();
                }
        }
}
