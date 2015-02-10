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

void cms_ff_ppb(const char *filename_list, const char *trigger_name, const int is_mc = 0, const int perp_track = 1, const double pseudorapidity_min = 0, const double pseudorapidity_max = 1, const double boost_ppb = 1, const long select_index_jet = -1, const unsigned long reflect_type = 0, const unsigned long parallel_offset = 0, const unsigned long parallel_stride = 1)
{
	char *filename = strdup(filename_list);
	fprintf(stderr, "%s:%d:\n", __FILE__, __LINE__);

	gROOT->Reset();
	gStyle->SetCanvasColor(kWhite);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetPadBorderMode(0);
    gStyle->SetOptStat(0);
    gStyle->SetPadTopMargin(0.0234375);
    gStyle->SetPadLeftMargin(0.125);
    gStyle->SetPadBottomMargin(0.140625);
    gStyle->SetPadRightMargin(0.0234375);


	const sampleType sType = kPPDATA;

	InitCorrFiles(sType);
	InitCorrHists(sType);

	TApplication application();
	TCanvas canvas("canvas", "", 720 + 4, 720 + 28);

	TH1D root_histogram_jet("root_histogram_jet", "", 15 * 8, 0, 300);

	root_histogram_jet.Sumw2();
	root_histogram_jet.SetMarkerStyle(24);
	root_histogram_jet.SetMarkerColor(kBlack);
	root_histogram_jet.SetLineColor(kBlack);
	root_histogram_jet.GetXaxis()->SetLabelSize(0.0625);
	root_histogram_jet.GetXaxis()->SetTitleSize(0.0625);
	root_histogram_jet.GetYaxis()->SetLabelSize(0.0625);
	root_histogram_jet.GetYaxis()->SetTitleSize(0.0625);

	TH1D root_histogram_jet_reflected("root_histogram_jet_reflected", "", 15 * 8, 0, 300);

	root_histogram_jet_reflected.Sumw2();
	root_histogram_jet_reflected.SetMarkerStyle(24);
	root_histogram_jet_reflected.SetMarkerColor(kBlack);
	root_histogram_jet_reflected.SetLineColor(kBlack);
	root_histogram_jet_reflected.GetXaxis()->SetLabelSize(0.0625);
	root_histogram_jet_reflected.GetXaxis()->SetTitleSize(0.0625);
	root_histogram_jet_reflected.GetYaxis()->SetLabelSize(0.0625);
	root_histogram_jet_reflected.GetYaxis()->SetTitleSize(0.0625);

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
	root_histogram_track.SetMarkerStyle(24);
	root_histogram_track.SetMarkerColor(kBlack);
	root_histogram_track.SetLineColor(kBlack);
	root_histogram_track.GetXaxis()->SetLabelSize(0.0625);
	root_histogram_track.GetXaxis()->SetTitleSize(0.0625);
	root_histogram_track.GetYaxis()->SetLabelSize(0.0625);
	root_histogram_track.GetYaxis()->SetTitleSize(0.0625);

	root_histogram_track_reflected.Sumw2();
	root_histogram_track_reflected.SetMarkerStyle(24);
	root_histogram_track_reflected.SetMarkerColor(kBlack);
	root_histogram_track_reflected.SetLineColor(kBlack);
	root_histogram_track_reflected.GetXaxis()->SetLabelSize(0.0625);
	root_histogram_track_reflected.GetXaxis()->SetTitleSize(0.0625);
	root_histogram_track_reflected.GetYaxis()->SetLabelSize(0.0625);
	root_histogram_track_reflected.GetYaxis()->SetTitleSize(0.0625);

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
	root_histogram_pf.SetMarkerStyle(25);
	root_histogram_pf.SetMarkerColor(kBlack);
	root_histogram_pf.SetLineColor(kBlack);
	root_histogram_pf.GetXaxis()->SetLabelSize(0.0625);
	root_histogram_pf.GetXaxis()->SetTitleSize(0.0625);
	root_histogram_pf.GetYaxis()->SetLabelSize(0.0625);
	root_histogram_pf.GetYaxis()->SetTitleSize(0.0625);

	root_histogram_pf_reflected.Sumw2();
	root_histogram_pf_reflected.SetMarkerStyle(25);
	root_histogram_pf_reflected.SetMarkerColor(kBlack);
	root_histogram_pf_reflected.SetLineColor(kBlack);
	root_histogram_pf_reflected.GetXaxis()->SetLabelSize(0.0625);
	root_histogram_pf_reflected.GetXaxis()->SetTitleSize(0.0625);
	root_histogram_pf_reflected.GetYaxis()->SetLabelSize(0.0625);
	root_histogram_pf_reflected.GetYaxis()->SetTitleSize(0.0625);

	if (strcmp(filename, "builtin") == 0) {
		filename = strdup(
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/000D4260-D23E-E311-A850-02163E008D77.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/00E41BFD-D93E-E311-A91D-0025901D5DEC.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/022B6AEB-173F-E311-B17D-0025904A90CA.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/02484AF2-E63E-E311-A3F6-003048D2BEE6.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/024E0F96-B93E-E311-8A3C-02163E008DA1.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/027308C4-C73E-E311-8A0C-003048F23FA8.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/02751E29-D73E-E311-B249-02163E00CD78.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0278353F-F23E-E311-AEED-02163E00C482.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/02C290BF-E03E-E311-913B-C860001BD86A.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/02D19806-DD3E-E311-BC8A-002481E0D1F2.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/02E16C94-0B3F-E311-9F2F-02163E00C4FA.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/02E91997-EF3E-E311-8520-0025901AF660.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0420D5E4-B23E-E311-9F88-02163E00BF97.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0422E58A-A53E-E311-9A3E-02163E00ADFE.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/04446C4B-183F-E311-AB6F-02163E008D93.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0444C885-EB3E-E311-AD67-C860001BD834.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0471E862-D03E-E311-B57D-02163E00A38A.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/04A4EED5-053F-E311-A2AF-003048F1B904.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/04CD866D-EE3E-E311-B148-003048F23676.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/04D9EECE-F03E-E311-910B-02163E0079DA.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/04DE8625-BC3E-E311-8E8B-003048F1C9AC.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/04FC376C-053F-E311-9BAC-02163E0079D5.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/06318261-F83E-E311-B60D-003048CF92B8.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/06E59C16-0A40-E311-B387-02163E008D9F.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/06EA1332-D83E-E311-84BD-02163E00BA2B.root:"
#if 0
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0811F6D0-F63E-E311-8119-003048F0E3E2.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0821EF2C-F13E-E311-82A6-0025901AF58A.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/083338D7-C83E-E311-A6BA-BCAEC518FF52.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/083FB350-E13E-E311-BA07-003048F1B904.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0870B2A1-0F3F-E311-8D3A-0025901D6284.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0875B156-063F-E311-99FE-003048D462BA.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/087BD0EE-073F-E311-84CD-02163E00ADFE.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/08CD351F-DF3E-E311-B4AD-003048F2377E.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/08F80CDC-FC3E-E311-9275-003048FEAF14.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0A00A5BE-D73E-E311-AE52-02163E00A313.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0A0408EF-EA3E-E311-8501-003048FEAECC.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0A046A87-043F-E311-B19F-02163E00CE1C.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0A07557B-043F-E311-A05E-02163E008D9E.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0A41D176-F33E-E311-9E3C-02163E00CAC5.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0A4C2BB0-EB3E-E311-9238-02163E00AD22.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0A6E33A9-E63E-E311-8E0E-C860001BD8BC.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0A73DA1F-FB3E-E311-9D96-02163E00CDF6.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0A817C2C-E43E-E311-823C-003048F1C1A0.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0A909CE8-E43E-E311-A769-02163E00AE41.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0A9FFC83-DA3E-E311-AD1C-003048FEAF90.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0AC9521D-AD3E-E311-BC7B-003048F1182C.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0AD989E0-E33E-E311-AEF9-02163E00CC4F.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0C5B7776-D23E-E311-ACB7-002481E0D1F2.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0C9638EB-CA3E-E311-9D83-0025B32441FA.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0CADD1C9-C33E-E311-892C-003048F01074.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0CCF68F1-E73E-E311-A1EE-003048FEAFA0.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0CD213C3-E03E-E311-88B4-002590494DE8.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0E00131B-D73E-E311-9FBF-0025901D6286.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0E38FEF9-103F-E311-81A2-0025901D5C7E.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0E53E0E6-EA3E-E311-8ACC-02163E008D96.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0E5E5D99-AB3E-E311-ACE7-003048F236DE.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0E721DD8-F23E-E311-96C9-02163E00C09C.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0EB3C1F1-C13E-E311-87F6-C860001BD89E.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0EBF2796-D83E-E311-A794-5404A63886EC.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0EC296FC-E63E-E311-83D0-003048F179C2.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/0ED83F55-063F-E311-96B0-003048F24354.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/10426894-D33E-E311-BEEC-02163E008D96.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/107DEEF2-C73E-E311-8AE2-02163E008D83.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/107E130C-ED3E-E311-BE60-02163E00A1F2.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/10AE0E26-023F-E311-8861-02163E00C7E1.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/10B2D1EE-F43E-E311-B3BC-5404A63886B1.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/10C529FC-EA3E-E311-B0E1-003048F236DA.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/10D9B1AE-E23E-E311-92BE-0030486730E6.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/10EDF04B-A23E-E311-8D99-003048F02C5A.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/122CFC9F-063F-E311-8719-02163E00CACA.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/123F921D-B33E-E311-844D-C860001BD868.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/124D4CF9-0E3F-E311-B402-02163E00B1AA.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/125206EC-C63E-E311-B48E-002590496FE6.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/12C0AED0-B23E-E311-A9E7-003048F1C764.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/140CAFBD-033F-E311-B5B9-0030486730BE.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/140CFF35-CD3E-E311-93CD-02163E008DB1.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/14444AA8-DC3E-E311-9AEE-0025901AF344.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/1463F0BE-C93E-E311-BBB4-003048FEB9C2.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/1475CD2D-113F-E311-A514-00237DDBE8CC.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/147929CD-DA3E-E311-ACDD-003048F01146.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/14792B5E-CA3E-E311-B877-003048F1C9A6.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/1488213F-D03E-E311-B09B-003048FEAEB0.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/14997B2C-AF3E-E311-B1A0-0025904B2C5A.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/14A72041-143F-E311-A4C3-002481E0D1F2.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/14AE996A-FC3E-E311-8ACE-02163E00C010.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/14E46207-D93E-E311-9321-003048CF9AE0.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/14F5FBD5-F63E-E311-8480-3C4A9279B99C.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/14F720D9-EA3E-E311-8540-02163E00BFED.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/16A08478-BF3E-E311-9C70-BCAEC5329720.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/18146DB6-D73E-E311-828B-003048F1C570.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/187A3C72-043F-E311-BBE7-003048F1B952.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/1880FB04-0C3F-E311-A832-003048F02D3A.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/189297B5-163F-E311-83D3-003048FE4C1E.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/18ABE119-FF3E-E311-935B-003048F1C41C.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/34FA4B80-5D40-E311-84A1-02163E008F4B.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/4AEA1386-5740-E311-8A90-003048FEB98E.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/86D25C78-E840-E311-BD36-003048FEAF84.root:"
"/mnt/by-uuid/5ef92110-4bac-4a68-aa2f-7ad2d84192a9/scratch/data/F6080CC5-A842-E311-AD37-0025904B0568.root:"
#endif
);
	}

	fprintf(stderr, "%s:%d:\n", __FILE__, __LINE__);

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
#if 0
   Float_t         vx[2];
   Float_t         vy[2];
   Float_t         vz[2];
#endif
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
#if 0
   trackTree->SetBranchAddress("vx",vx);
   trackTree->SetBranchAddress("vy",vy);
   trackTree->SetBranchAddress("vz",vz);
#endif
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
	   // HltTree->SetBranchAddress("HLT_Jet30_v9",&HLT_Jet30_v9);
	   // HltTree->SetBranchAddress("HLT_Jet30_v9_Prescl",&HLT_Jet30_v9_Prescl);
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

	fprintf(stderr, "%s:%d:\n", __FILE__, __LINE__);

	//size_t nentries = trackTree->GetEntries();
	size_t nentries = 100000;

	fprintf(stderr, "%s:%d: offset = %lu, stride = %lu\n", __FILE__, __LINE__, parallel_offset, parallel_stride);
	fprintf(stderr, "%s:%d: pfTree = %p\n", __FILE__, __LINE__, pfTree);
	fprintf(stderr, "%s:%d: hiTree = %p\n", __FILE__, __LINE__, hiTree);
	fprintf(stderr, "%s:%d: t = %p\n", __FILE__, __LINE__, t);
	fprintf(stderr, "%s:%d: trackTree = %p\n", __FILE__, __LINE__, trackTree);

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

		//const double boost_pseudorapidity = 0;

		if (((pcollisionEventSelection != 0 ||
			  pPAcollisionEventSelectionPA != 0) &&
			 (is_mc || pHBHENoiseFilter != 0)) &&
			(trigger_name[0] == '\0' || trigger_scaled != 0)
#if 0
			&& nVtx >= 2 && nVtx <= 12
#endif
			&& jtpt[0] >= 15
		) {
			event_count++;
			for (int j = 0; j < nref; j++) {
				jteta[j] += boost_pseudorapidity;

#if 0
				const double perp = rawpt[j];
				const double pseudorapidity = jteta[j];
				double perp_scale = 1;

				switch (nVtx) {
case 1:
#include "jec_pp7tev_pu1.h"
break;
case 2:
#include "jec_pp7tev_pu2.h"
break;
case 3:
#include "jec_pp7tev_pu3.h"
break;
case 4:
#include "jec_pp7tev_pu4.h"
break;
case 5:
#include "jec_pp7tev_pu5.h"
break;
case 6:
#include "jec_pp7tev_pu6.h"
break;
case 7:
#include "jec_pp7tev_pu7.h"
break;
case 8:
#include "jec_pp7tev_pu8.h"
break;
case 9:
#include "jec_pp7tev_pu9.h"
break;
case 10:
#include "jec_pp7tev_pu10.h"
break;
case 11:
#include "jec_pp7tev_pu11.h"
break;
case 12:
#include "jec_pp7tev_pu12.h"
break;
				}
				jtpt[j] = rawpt[j] * perp_scale;
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
//				fprintf(stderr, "%s:%d: %d %d %d %d %d %d %d %d %d %d %d %d %.8e %.8e %.8e %.8e\n", __FILE__, __LINE__, i, j, HLT_Jet30_v9, HLT_Jet30_v9_Prescl, HLT_Jet60_v9, HLT_Jet60_v9_Prescl, HLT_Jet110_v9, HLT_Jet110_v9_Prescl, HLT_Jet190_v9, HLT_Jet190_v9_Prescl, HLT_Jet240_v9, HLT_Jet240_v9_Prescl, rawpt[j], jtpt[j], jteta[j], jtphi[j]);
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
										//fprintf(stderr, "%s:%d: %d %d %d %.8e %.8e %.8e %.8e %.8e %.8e %.8e\n", __FILE__, __LINE__, run, lumi, evt, jtpt[j], jteta[j], jtphi[j], trkPt[k], trkEta[k], trkPhi[k], factorizedPtCorr(getPtBin(trkPt[k], sType), hiBin, trkPt[k], trkPhi[k], trkEta[k], sqrtf(dr_square), sType));
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
#if 0
		}
	}

	f->Close();
		}
	}
#endif

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

	//char output_filename[4096];

	//snprintf(output_filename, 4096, "%s_%s_%d_%g_%g_%g_%ld_%lu_%lu_%lu.C", gSystem->BaseName(filename_list), trigger_name, perp_track, pseudorapidity_min, pseudorapidity_max, boost_ppb, select_index_jet, reflect_type, parallel_offset, parallel_stride);

//	fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, output_filename);

	//canvas.SaveAs(output_filename);
	fprintf(stderr, "%s:%d:\n", __FILE__, __LINE__);

                }
        }

        //f->Close();
                }
        }
}
