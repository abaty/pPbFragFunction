#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TPad.h"
#include "TText.h"
#include "TAttFill.h"
#include "TLine.h"
#include "TColor.h"
#include "TMathText.h"
#include "TMath.h"
#include "TStyle.h"
#include "rawHistograms.h"
#include "smear.h"
#include "makeComparisonPlot.h"

void makeHistos()
{
//=========Macro generated from canvas: canvas/
//=========  (Fri May 23 11:33:37 2014) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "",0,0,1680+4,800+33);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->Range(0,0,1,1);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(0);
   canvas->SetTickx(1);
   canvas->SetTicky(1);
   canvas->SetLeftMargin(0.0625 * 0.75);
   canvas->SetRightMargin(0.0078125);
   canvas->SetBottomMargin(0.0625 * 1.5);
   canvas->SetFrameLineColor(0);
   canvas->SetFrameBorderMode(0);

   Double_t yAxis[40] = {0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6, 120.8, 138, 155.2, 172.4, 189.6, 206.8}; 

   baseHistos();

// additions here
   TH1D * tev5_mbjets_smeared = (TH1D*)root_histogram_data5tevmb_jet->Clone("tev5_mbjets_smeared");
   tev5_mbjets_smeared->Scale(34.990*33.514);
   TH1D * tev5_40jets_smeared = (TH1D*)root_histogram_data5tev40_jet->Clone("tev5_40jets_smeared");
   tev5_40jets_smeared->Scale(34.99);
   TH1D * tev5_80jets_smeared = (TH1D*)root_histogram_data5tev80_jet->Clone("tev5_80jets_smeared");

   TH1D *combined_5tev_jets = new TH1D("combined_5tev_jets","combined_5tev_jets", 120,0,300);
   for(int n=1; n<121; n++)
   {
     int bin = combined_5tev_jets->GetXaxis()->GetBinLowEdge(n);
     if(bin < 80)
     {
       combined_5tev_jets->SetBinContent(n,tev5_mbjets_smeared->GetBinContent(n));
       combined_5tev_jets->SetBinError(n,tev5_mbjets_smeared->GetBinError(n));
     }
     else if(bin < 140)
     {
       combined_5tev_jets->SetBinContent(n,tev5_40jets_smeared->GetBinContent(n));
       combined_5tev_jets->SetBinError(n,tev5_40jets_smeared->GetBinError(n));
     }
     else
     {
       combined_5tev_jets->SetBinContent(n,tev5_80jets_smeared->GetBinContent(n));
       combined_5tev_jets->SetBinError(n,tev5_80jets_smeared->GetBinError(n));
     }
   }
   
   TH1D *combined_5tev_jets_smeared = (TH1D*)combined_5tev_jets->Clone("combined_5tev_jets_smeared");   
   smear(combined_5tev_jets_smeared);   
   makeComparisonPlot(combined_5tev_jets, combined_5tev_jets_smeared);

   for(int n=1; n<121; n++)
   {
     int bin = combined_5tev_jets_smeared->GetXaxis()->GetBinLowEdge(n);
     if(bin < 80)
     {
       combined_5tev_jets_smeared->SetBinContent(n,combined_5tev_jets_smeared->GetBinContent(n)/(34.990*33.514));
       combined_5tev_jets_smeared->SetBinError(n,combined_5tev_jets_smeared->GetBinError(n)/(34.990*33.514));
     }
     else if(bin < 140)
     {
       combined_5tev_jets_smeared->SetBinContent(n,combined_5tev_jets_smeared->GetBinContent(n)/34.990);
       combined_5tev_jets_smeared->SetBinError(n,combined_5tev_jets_smeared->GetBinError(n)/34.990);
     }
   }

   TH1D *root_histogram_data_5tev_temp_2[15];

   for (size_t i = 3; i < 15; i++) {
	   char buf[4096];

	   snprintf(buf, 4096, "root_histogram_data_5tev_temp_2_%lu", i);

	   root_histogram_data_5tev_temp_2[i] = new TH1D(buf, "", 39, yAxis);
	   root_histogram_data_5tev_temp_2[i]->SetLineStyle(0);
	   root_histogram_data_5tev_temp_2[i]->SetMarkerStyle(25);
	   root_histogram_data_5tev_temp_2[i]->GetXaxis()->SetLabelFont(42);
	   root_histogram_data_5tev_temp_2[i]->GetXaxis()->SetLabelOffset(0.01);
	   root_histogram_data_5tev_temp_2[i]->GetXaxis()->SetLabelSize(0.0625);
	   root_histogram_data_5tev_temp_2[i]->GetXaxis()->SetTitleSize(0.0625);
	   root_histogram_data_5tev_temp_2[i]->GetXaxis()->SetTitleFont(42);
	   root_histogram_data_5tev_temp_2[i]->GetYaxis()->SetLabelFont(42);
	   root_histogram_data_5tev_temp_2[i]->GetYaxis()->SetLabelOffset(0.01);
	   root_histogram_data_5tev_temp_2[i]->GetYaxis()->SetLabelSize(0.0625);
	   root_histogram_data_5tev_temp_2[i]->GetYaxis()->SetTitleSize(0.0625);
	   root_histogram_data_5tev_temp_2[i]->GetYaxis()->SetTitleOffset(1.5);
	   root_histogram_data_5tev_temp_2[i]->GetYaxis()->SetTitleFont(42);
	   root_histogram_data_5tev_temp_2[i]->GetZaxis()->SetLabelFont(42);
	   root_histogram_data_5tev_temp_2[i]->GetZaxis()->SetLabelOffset(0.01);
	   root_histogram_data_5tev_temp_2[i]->GetZaxis()->SetLabelSize(0.045);
	   root_histogram_data_5tev_temp_2[i]->GetZaxis()->SetTitleSize(0.035);
	   root_histogram_data_5tev_temp_2[i]->GetZaxis()->SetTitleFont(42);

	   const double perp_jet = root_histogram_data5tevmb_jet->GetXaxis()->GetBinLowEdge(i * 8 + 1);
	   TH1D *hj = NULL;
	   TH2D *ht = NULL;
	   TH2D *hts = NULL;
	   TH1D *hjr = NULL;

	   if (perp_jet < 80) {
		   hj = root_histogram_data5tevmb_jet;
		   ht = root_histogram_data5tevmb_track;
		   hts = root_histogram_data5tevmb_track_reflected;
		   hjr = root_histogram_data5tevmb_jet;
	   }
	   else if (perp_jet < 140) {
		   hj = root_histogram_data5tev40_jet;
		   ht = root_histogram_data5tev40_track;
		   hts = root_histogram_data5tev40_track_reflected;
		   hjr = root_histogram_data5tev40_jet;
	   }
	   else {
		   hj = root_histogram_data5tev80_jet;
		   ht = root_histogram_data5tev80_track;
		   hts = root_histogram_data5tev80_track_reflected;
		   hjr = root_histogram_data5tev80_jet;
	   }

           hj = combined_5tev_jets_smeared;
           hjr= combined_5tev_jets_smeared;

	   for (size_t j = 0; j < 39; j++) {
		   double sum_content = 0;
		   double sum_error = 0;
		   double sum_denominator = 0;


//testing here
		   for (size_t k = 0; k < (i == 7 ? 24 : 8); k++) {

			   if (hj->GetBinContent(i * 8 + k + 1) > 0 && hjr->GetBinContent(i * 8 + k + 1) > 0) {
				   const double weight = hjr->GetBinContent(i * 8 + k + 1) / hj->GetBinContent(i * 8 + k + 1);
				   const int root_bin = ht->GetBin(i * 8 + k + 1, j + 1);

				   sum_content = 0;
				   sum_error = 0;
				   if (hts != NULL) {
					   sum_content += hts->GetBinContent(root_bin) * weight;
					   sum_error += hts->GetBinError(root_bin) * hts->GetBinError(root_bin) * weight * weight;
				   }
				   sum_denominator += hj->GetBinContent(i * 8 + k + 1) * weight;
			   }
		   }
		   sum_denominator *= ht->GetYaxis()->GetBinWidth(j + 1);

		   root_histogram_data_5tev_temp_2[i]->SetBinContent(j + 1, sum_content / sum_denominator);
		   root_histogram_data_5tev_temp_2[i]->SetBinError(j + 1, sqrt(sum_error) / sum_denominator);
	   }
   }

   TH1D *root_histogram_data_5tev_temp[15];

   for (size_t i = 3; i < 15; i++) {
	   char buf[4096];

	   snprintf(buf, 4096, "root_histogram_data_5tev_temp_%lu", i);

	   root_histogram_data_5tev_temp[i] = new TH1D(buf, "", 39, yAxis);
	   root_histogram_data_5tev_temp[i]->SetLineStyle(0);
	   root_histogram_data_5tev_temp[i]->SetMarkerStyle(25);
	   root_histogram_data_5tev_temp[i]->GetXaxis()->SetLabelFont(42);
	   root_histogram_data_5tev_temp[i]->GetXaxis()->SetLabelOffset(0.01);
	   root_histogram_data_5tev_temp[i]->GetXaxis()->SetLabelSize(0.0625);
	   root_histogram_data_5tev_temp[i]->GetXaxis()->SetTitleSize(0.0625);
	   root_histogram_data_5tev_temp[i]->GetXaxis()->SetTitleFont(42);
	   root_histogram_data_5tev_temp[i]->GetYaxis()->SetLabelFont(42);
	   root_histogram_data_5tev_temp[i]->GetYaxis()->SetLabelOffset(0.01);
	   root_histogram_data_5tev_temp[i]->GetYaxis()->SetLabelSize(0.0625);
	   root_histogram_data_5tev_temp[i]->GetYaxis()->SetTitleSize(0.0625);
	   root_histogram_data_5tev_temp[i]->GetYaxis()->SetTitleOffset(1.5);
	   root_histogram_data_5tev_temp[i]->GetYaxis()->SetTitleFont(42);
	   root_histogram_data_5tev_temp[i]->GetZaxis()->SetLabelFont(42);
	   root_histogram_data_5tev_temp[i]->GetZaxis()->SetLabelOffset(0.01);
	   root_histogram_data_5tev_temp[i]->GetZaxis()->SetLabelSize(0.045);
	   root_histogram_data_5tev_temp[i]->GetZaxis()->SetTitleSize(0.035);
	   root_histogram_data_5tev_temp[i]->GetZaxis()->SetTitleFont(42);



	   const double perp_jet = root_histogram_data5tevmb_jet->GetXaxis()->GetBinLowEdge(i * 8 + 1);
	   TH1D *hj = NULL;
	   TH2D *ht = NULL;
	   TH2D *hts = NULL;
	   TH1D *hjr = NULL;

	   if (perp_jet < 80) {
		   hj = root_histogram_data5tevmb_jet;
		   ht = root_histogram_data5tevmb_track;
		   hts = root_histogram_data5tevmb_track_reflected;
		   hjr = root_histogram_data5tevmb_jet;
	   }
	   else if (perp_jet < 140) {
		   hj = root_histogram_data5tev40_jet;
		   ht = root_histogram_data5tev40_track;
		   hts = root_histogram_data5tev40_track_reflected;
		   hjr = root_histogram_data5tev40_jet;
	   }
	   else {
		   hj = root_histogram_data5tev80_jet;
		   ht = root_histogram_data5tev80_track;
		   hts = root_histogram_data5tev80_track_reflected;
		   hjr = root_histogram_data5tev80_jet;
	   }

           hj = combined_5tev_jets_smeared;
           hjr = combined_5tev_jets_smeared;

	   for (size_t j = 0; j < 39; j++) {
		   double sum_content = 0;
		   double sum_error = 0;
		   double sum_denominator = 0;


//testing here
		   for (size_t k = 0; k < (i == 7 ? 24 : 8); k++) {

			   if (hj->GetBinContent(i * 8 + k + 1) > 0 && hjr->GetBinContent(i * 8 + k + 1) > 0) {
				   const double weight = hjr->GetBinContent(i * 8 + k + 1) / hj->GetBinContent(i * 8 + k + 1);
				   const int root_bin = ht->GetBin(i * 8 + k + 1, j + 1);

				   sum_content += ht->GetBinContent(root_bin) * weight;
				   sum_error += ht->GetBinError(root_bin) * ht->GetBinError(root_bin) * weight * weight;
				   if (hts != NULL) {
					   sum_content -= hts->GetBinContent(root_bin) * weight;
					   sum_error += hts->GetBinError(root_bin) * hts->GetBinError(root_bin) * weight * weight;
				   }
				   sum_denominator += hj->GetBinContent(i * 8 + k + 1) * weight;
			   }
		   }
		   sum_denominator *= ht->GetYaxis()->GetBinWidth(j + 1);

		   root_histogram_data_5tev_temp[i]->SetBinContent(j + 1, sum_content / sum_denominator);
		   root_histogram_data_5tev_temp[i]->SetBinError(j + 1, sqrt(sum_error) / sum_denominator);
	   }
   }

   TH1D *root_histogram_data_7tev_temp[15];

   for (size_t i = 0; i < 15; i++) {
	   char buf[4096];

	   snprintf(buf, 4096, "root_histogram_data_7tev_temp_%lu", i);

	   root_histogram_data_7tev_temp[i] = new TH1D(buf, "", 39, yAxis);
	   root_histogram_data_7tev_temp[i]->SetLineStyle(0);
	   root_histogram_data_7tev_temp[i]->SetMarkerStyle(25);
	   root_histogram_data_7tev_temp[i]->GetXaxis()->SetLabelFont(42);
	   root_histogram_data_7tev_temp[i]->GetXaxis()->SetLabelOffset(0.01);
	   root_histogram_data_7tev_temp[i]->GetXaxis()->SetLabelSize(0.0625);
	   root_histogram_data_7tev_temp[i]->GetXaxis()->SetTitleSize(0.0625);
	   root_histogram_data_7tev_temp[i]->GetXaxis()->SetTitleFont(42);
	   root_histogram_data_7tev_temp[i]->GetYaxis()->SetLabelFont(42);
	   root_histogram_data_7tev_temp[i]->GetYaxis()->SetLabelOffset(0.01);
	   root_histogram_data_7tev_temp[i]->GetYaxis()->SetLabelSize(0.0625);
	   root_histogram_data_7tev_temp[i]->GetYaxis()->SetTitleSize(0.0625);
	   root_histogram_data_7tev_temp[i]->GetYaxis()->SetTitleOffset(1.5);
	   root_histogram_data_7tev_temp[i]->GetYaxis()->SetTitleFont(42);
	   root_histogram_data_7tev_temp[i]->GetZaxis()->SetLabelFont(42);
	   root_histogram_data_7tev_temp[i]->GetZaxis()->SetLabelOffset(0.01);
	   root_histogram_data_7tev_temp[i]->GetZaxis()->SetLabelSize(0.045);
	   root_histogram_data_7tev_temp[i]->GetZaxis()->SetTitleSize(0.035);
	   root_histogram_data_7tev_temp[i]->GetZaxis()->SetTitleFont(42);

	   const double perp_jet = root_histogram_data5tevmb_jet->GetXaxis()->GetBinLowEdge(i * 8 + 1);
	   TH1D *hj = NULL;
	   TH2D *ht = NULL;
	   TH2D *hts = NULL;
	   TH1D *hjr = NULL;

	   if (perp_jet < 80) {
		   hj = root_histogram_data7tev30_jet1;
		   ht = root_histogram_data7tev30_track2;
		   hts = root_histogram_data7tev30_track_reflected3;
		   hjr = root_histogram_data5tevmb_jet;
	   }
	   else if (perp_jet < 80) {
		   hj = root_histogram_data7tev30_jet1;
		   ht = root_histogram_data7tev30_track2;
		   hts = root_histogram_data7tev30_track_reflected3;
		   hjr = root_histogram_data5tev40_jet;
	   }
	   else if (perp_jet < 140) {
		   hj = root_histogram_data7tev60_jet1;
		   ht = root_histogram_data7tev60_track2;
		   hts = root_histogram_data7tev60_track_reflected3;
		   hjr = root_histogram_data5tev40_jet;
	   }
	   else {
		   hj = root_histogram_data7tev110_jet1;
		   ht = root_histogram_data7tev110_track2;
		   hts = root_histogram_data7tev110_track_reflected3;
		   hjr = root_histogram_data5tev80_jet;
	   }

           hjr = combined_5tev_jets_smeared;

	   for (size_t j = 0; j < 39; j++) {
		   double sum_content = 0;
		   double sum_error = 0;
		   double sum_denominator = 0;

//testing here
		   for (size_t k = 0; k < (i == 7 ? 24 : 8); k++) {
			   if (hj->GetBinContent(i * 8 + k + 1) > 0 && hjr->GetBinContent(i * 8 + k + 1) > 0) {
				   const double weight = hjr->GetBinContent(i * 8 + k + 1) / hj->GetBinContent(i * 8 + k + 1);
				   const int root_bin = ht->GetBin(i * 8 + k + 1, j + 1);

				   sum_content += ht->GetBinContent(root_bin) * weight;
				   sum_error += ht->GetBinError(root_bin) * ht->GetBinError(root_bin) * weight * weight;
				   if (hts != NULL) {
					   sum_content -= hts->GetBinContent(root_bin) * weight;
					   sum_error += hts->GetBinError(root_bin) * hts->GetBinError(root_bin) * weight * weight;
				   }
				   sum_denominator += hj->GetBinContent(i * 8 + k + 1) * weight;
			   }
		   }
		   //fprintf(stderr, "%f %f %f\n", sum_content, sum_error, sum_denominator);
		   sum_denominator *= ht->GetYaxis()->GetBinWidth(j + 1);

		   root_histogram_data_7tev_temp[i]->SetBinContent(j + 1, sum_content / sum_denominator);
		   root_histogram_data_7tev_temp[i]->SetBinError(j + 1, sqrt(sum_content) / sum_denominator);
	   }
   }

   TH1D *root_histogram_data_7tev_temp_2[15];

   for (size_t i = 0; i < 15; i++) {
	   char buf[4096];

	   snprintf(buf, 4096, "root_histogram_data_7tev_temp_2_%lu", i);

	   root_histogram_data_7tev_temp_2[i] = new TH1D(buf, "", 39, yAxis);
	   root_histogram_data_7tev_temp_2[i]->SetLineStyle(0);
	   root_histogram_data_7tev_temp_2[i]->SetMarkerStyle(25);
	   root_histogram_data_7tev_temp_2[i]->GetXaxis()->SetLabelFont(42);
	   root_histogram_data_7tev_temp_2[i]->GetXaxis()->SetLabelOffset(0.01);
	   root_histogram_data_7tev_temp_2[i]->GetXaxis()->SetLabelSize(0.0625);
	   root_histogram_data_7tev_temp_2[i]->GetXaxis()->SetTitleSize(0.0625);
	   root_histogram_data_7tev_temp_2[i]->GetXaxis()->SetTitleFont(42);
	   root_histogram_data_7tev_temp_2[i]->GetYaxis()->SetLabelFont(42);
	   root_histogram_data_7tev_temp_2[i]->GetYaxis()->SetLabelOffset(0.01);
	   root_histogram_data_7tev_temp_2[i]->GetYaxis()->SetLabelSize(0.0625);
	   root_histogram_data_7tev_temp_2[i]->GetYaxis()->SetTitleSize(0.0625);
	   root_histogram_data_7tev_temp_2[i]->GetYaxis()->SetTitleOffset(1.5);
	   root_histogram_data_7tev_temp_2[i]->GetYaxis()->SetTitleFont(42);
	   root_histogram_data_7tev_temp_2[i]->GetZaxis()->SetLabelFont(42);
	   root_histogram_data_7tev_temp_2[i]->GetZaxis()->SetLabelOffset(0.01);
	   root_histogram_data_7tev_temp_2[i]->GetZaxis()->SetLabelSize(0.045);
	   root_histogram_data_7tev_temp_2[i]->GetZaxis()->SetTitleSize(0.035);
	   root_histogram_data_7tev_temp_2[i]->GetZaxis()->SetTitleFont(42);

	   const double perp_jet = root_histogram_data5tevmb_jet->GetXaxis()->GetBinLowEdge(i * 8 + 1);
	   TH1D *hj = NULL;
	   TH2D *ht = NULL;
	   TH2D *hts = NULL;
	   TH1D *hjr = NULL;

	   if (perp_jet < 80) {
		   hj = root_histogram_data7tev30_jet1;
		   ht = root_histogram_data7tev30_track2;
		   hts = root_histogram_data7tev30_track_reflected3;
		   hjr = root_histogram_data5tevmb_jet;
	   }
	   else if (perp_jet < 80) {
		   hj = root_histogram_data7tev30_jet1;
		   ht = root_histogram_data7tev30_track2;
		   hts = root_histogram_data7tev30_track_reflected3;
		   hjr = root_histogram_data5tev40_jet;
	   }
	   else if (perp_jet < 140) {
		   hj = root_histogram_data7tev60_jet1;
		   ht = root_histogram_data7tev60_track2;
		   hts = root_histogram_data7tev60_track_reflected3;
		   hjr = root_histogram_data5tev40_jet;
	   }
	   else {
		   hj = root_histogram_data7tev110_jet1;
		   ht = root_histogram_data7tev110_track2;
		   hts = root_histogram_data7tev110_track_reflected3;
		   hjr = root_histogram_data5tev80_jet;
	   }

           hjr = combined_5tev_jets_smeared;

	   for (size_t j = 0; j < 39; j++) {
		   double sum_content = 0;
		   double sum_error = 0;
		   double sum_denominator = 0;

//testing
		   for (size_t k = 0; k < (i == 7 ? 24 : 8); k++) {
			   if (hj->GetBinContent(i * 8 + k + 1) > 0 && hjr->GetBinContent(i * 8 + k + 1) > 0) {
				   const double weight = hjr->GetBinContent(i * 8 + k + 1) / hj->GetBinContent(i * 8 + k + 1);
				   const int root_bin = ht->GetBin(i * 8 + k + 1, j + 1);

				   sum_content = 0;
				   sum_error = 0;
				   if (hts != NULL) {
					   sum_content += hts->GetBinContent(root_bin) * weight;
					   sum_error += hts->GetBinError(root_bin) * hts->GetBinError(root_bin) * weight * weight;
				   }
				   sum_denominator += hj->GetBinContent(i * 8 + k + 1) * weight;
			   }
		   }
		   //fprintf(stderr, "%f %f %f\n", sum_content, sum_error, sum_denominator);
		   sum_denominator *= ht->GetYaxis()->GetBinWidth(j + 1);

		   root_histogram_data_7tev_temp_2[i]->SetBinContent(j + 1, sum_content / sum_denominator);
		   root_histogram_data_7tev_temp_2[i]->SetBinError(j + 1, sqrt(sum_content) / sum_denominator);
	   }
   }

   TH1D *root_histogram_data_2tev_temp[15];

   for (size_t i = 0; i < 15; i++) {
	   char buf[4096];

	   snprintf(buf, 4096, "root_histogram_data_2tev_temp_%lu", i);

	   root_histogram_data_2tev_temp[i] = new TH1D(buf, "", 39, yAxis);
	   root_histogram_data_2tev_temp[i]->SetLineStyle(0);
	   root_histogram_data_2tev_temp[i]->SetMarkerStyle(25);
	   root_histogram_data_2tev_temp[i]->GetXaxis()->SetLabelFont(42);
	   root_histogram_data_2tev_temp[i]->GetXaxis()->SetLabelOffset(0.01);
	   root_histogram_data_2tev_temp[i]->GetXaxis()->SetLabelSize(0.0625);
	   root_histogram_data_2tev_temp[i]->GetXaxis()->SetTitleSize(0.0625);
	   root_histogram_data_2tev_temp[i]->GetXaxis()->SetTitleFont(42);
	   root_histogram_data_2tev_temp[i]->GetYaxis()->SetLabelFont(42);
	   root_histogram_data_2tev_temp[i]->GetYaxis()->SetLabelOffset(0.01);
	   root_histogram_data_2tev_temp[i]->GetYaxis()->SetLabelSize(0.0625);
	   root_histogram_data_2tev_temp[i]->GetYaxis()->SetTitleSize(0.0625);
	   root_histogram_data_2tev_temp[i]->GetYaxis()->SetTitleOffset(1.5);
	   root_histogram_data_2tev_temp[i]->GetYaxis()->SetTitleFont(42);
	   root_histogram_data_2tev_temp[i]->GetZaxis()->SetLabelFont(42);
	   root_histogram_data_2tev_temp[i]->GetZaxis()->SetLabelOffset(0.01);
	   root_histogram_data_2tev_temp[i]->GetZaxis()->SetLabelSize(0.045);
	   root_histogram_data_2tev_temp[i]->GetZaxis()->SetTitleSize(0.035);
	   root_histogram_data_2tev_temp[i]->GetZaxis()->SetTitleFont(42);

	   const double perp_jet = root_histogram_data2tev40_jet->GetXaxis()->GetBinLowEdge(i * 8 + 1);
	   TH1D *hj = NULL;
	   TH2D *ht = NULL;
	   TH2D *hts = NULL;
	   TH1D *hjr = NULL;

	   if (perp_jet < 80) {
		   hj = root_histogram_data2tev40_jet;
		   ht = root_histogram_data2tev40_track;
		   hts = root_histogram_data2tev40_track_reflected;
		   hjr = root_histogram_data5tevmb_jet;
	   }
	   else if (perp_jet < 80) {
		   hj = root_histogram_data2tev40_jet;
		   ht = root_histogram_data2tev40_track;
		   hts = root_histogram_data2tev40_track_reflected;
		   hjr = root_histogram_data5tev40_jet;
	   }
	   else if (perp_jet < 160) {
		   hj = root_histogram_data2tev40_jet;
		   ht = root_histogram_data2tev40_track;
		   hts = root_histogram_data2tev40_track_reflected;
		   hjr = root_histogram_data5tev40_jet;
	   }
	   else {
		   hj = root_histogram_data2tev80_jet;
		   ht = root_histogram_data2tev80_track;
		   hts = root_histogram_data2tev80_track_reflected;
		   hjr = root_histogram_data5tev80_jet;
	   }

           hjr = combined_5tev_jets_smeared;

	   for (size_t j = 0; j < 39; j++) {
		   double sum_content = 0;
		   double sum_error = 0;
		   double sum_denominator = 0;

//testing
		   for (size_t k = 0; k < (i == 7 ? 24 : 8); k++) {

			   if (hj->GetBinContent(i * 8 + k + 1) > 0 && hjr->GetBinContent(i * 8 + k + 1) > 0) {
				   const double weight = hjr->GetBinContent(i * 8 + k + 1) / hj->GetBinContent(i * 8 + k + 1);
				   const int root_bin = ht->GetBin(i * 8 + k + 1, j + 1);

				   sum_content += ht->GetBinContent(root_bin) * weight;
				   sum_error += ht->GetBinError(root_bin) * ht->GetBinError(root_bin) * weight * weight;
				   if (hts != NULL) {
					   sum_content -= hts->GetBinContent(root_bin) * weight;
					   sum_error += hts->GetBinError(root_bin) * hts->GetBinError(root_bin) * weight * weight;
				   }
				   sum_denominator += hj->GetBinContent(i * 8 + k + 1) * weight;
			   }
		   }
		   //fprintf(stderr, "%f %f %f\n", sum_content, sum_error, sum_denominator);
		   sum_denominator *= ht->GetYaxis()->GetBinWidth(j + 1);

		   root_histogram_data_2tev_temp[i]->SetBinContent(j + 1, sum_content / sum_denominator);
		   root_histogram_data_2tev_temp[i]->SetBinError(j + 1, sqrt(sum_content) / sum_denominator);
	   }
   }

#if 0
   TH1D *root_histogram_mc_7tev_temp[15];

   for (size_t i = 0; i < 15; i++) {
	   char buf[4096];

	   snprintf(buf, 4096, "root_histogram_mc_7tev_temp_%lu", i);

	   root_histogram_mc_7tev_temp[i] = new TH1D(buf, "", 39, yAxis);
	   root_histogram_mc_7tev_temp[i]->SetLineStyle(0);
	   root_histogram_mc_7tev_temp[i]->SetMarkerStyle(25);
	   root_histogram_mc_7tev_temp[i]->GetXaxis()->SetLabelFont(42);
	   root_histogram_mc_7tev_temp[i]->GetXaxis()->SetLabelOffset(0.01);
	   root_histogram_mc_7tev_temp[i]->GetXaxis()->SetLabelSize(0.0625);
	   root_histogram_mc_7tev_temp[i]->GetXaxis()->SetTitleSize(0.0625);
	   root_histogram_mc_7tev_temp[i]->GetXaxis()->SetTitleFont(42);
	   root_histogram_mc_7tev_temp[i]->GetYaxis()->SetLabelFont(42);
	   root_histogram_mc_7tev_temp[i]->GetYaxis()->SetLabelOffset(0.01);
	   root_histogram_mc_7tev_temp[i]->GetYaxis()->SetLabelSize(0.0625);
	   root_histogram_mc_7tev_temp[i]->GetYaxis()->SetTitleSize(0.0625);
	   root_histogram_mc_7tev_temp[i]->GetYaxis()->SetTitleOffset(1.5);
	   root_histogram_mc_7tev_temp[i]->GetYaxis()->SetTitleFont(42);
	   root_histogram_mc_7tev_temp[i]->GetZaxis()->SetLabelFont(42);
	   root_histogram_mc_7tev_temp[i]->GetZaxis()->SetLabelOffset(0.01);
	   root_histogram_mc_7tev_temp[i]->GetZaxis()->SetLabelSize(0.045);
	   root_histogram_mc_7tev_temp[i]->GetZaxis()->SetTitleSize(0.035);
	   root_histogram_mc_7tev_temp[i]->GetZaxis()->SetTitleFont(42);

	   const double perp_jet = root_histogram_mc7tev30_jet1->GetXaxis()->GetBinLowEdge(i * 8 + 1);
	   TH1D *hj = NULL;
	   TH2D *ht = NULL;
	   TH2D *hts = NULL;

	   TH1D *hjr = NULL;

	   if (perp_jet < 60) {
		   hj = root_histogram_mc7tev30_jet1;
		   ht = root_histogram_mc7tev30_track2;
		   hts = root_histogram_mc7tev30_track_reflected3;
		   hjr = root_histogram_mc5tev50_jet;
	   }
	   else if (perp_jet < 80) {
		   hj = root_histogram_mc7tev30_jet1;
		   ht = root_histogram_mc7tev30_track2;
		   hts = root_histogram_mc7tev30_track_reflected3;
		   hjr = root_histogram_mc5tev50_jet;
	   }
	   else if (perp_jet < 120) {
		   hj = root_histogram_mc7tev80_jet1;
		   ht = root_histogram_mc7tev80_track2;
		   hts = root_histogram_mc7tev80_track_reflected3;
		   hjr = root_histogram_mc5tev80_jet;
	   }
	   else {
		   hj = root_histogram_mc7tev120_jet1;
		   ht = root_histogram_mc7tev120_track2;
		   hts = root_histogram_mc7tev120_track_reflected3;
		   hjr = root_histogram_mc5tev80_jet;
	   }

	   for (size_t j = 0; j < 39; j++) {
		   double sum_content = 0;
		   double sum_error = 0;
		   double sum_denominator = 0;

		   for (size_t k = 0; k < (j == 7 ? 24 : 8); k++) {
			   const int root_bin = ht->GetBin(i * 8 + k + 1, j + 1);

			   if (hj->GetBinContent(i * 8 + k + 1) > 0 && hjr->GetBinContent(i * 8 + k + 1) > 0) {
				   const double weight = hjr->GetBinContent(i * 8 + k + 1) / hj->GetBinContent(i * 8 + k + 1);

				   sum_content += ht->GetBinContent(root_bin) * weight;
				   sum_error += ht->GetBinError(root_bin) * ht->GetBinError(root_bin) * weight * weight;
				   if (hts != NULL) {
					   sum_content -= hts->GetBinContent(root_bin) * weight;
					   sum_error += hts->GetBinError(root_bin) * hts->GetBinError(root_bin) * weight * weight;
				   }
				   sum_denominator += hj->GetBinContent(i * 8 + k + 1) * weight;
			   }
		   }
		   //fprintf(stderr, "%f %f %f\n", sum_content, sum_error, sum_denominator);
		   sum_denominator *= ht->GetYaxis()->GetBinWidth(j + 1);

		   root_histogram_mc_7tev_temp[i]->SetBinContent(j + 1, sum_content / sum_denominator);
		   root_histogram_mc_7tev_temp[i]->SetBinError(j + 1, sqrt(sum_content) / sum_denominator);
	   }
   }
#endif

   TH1D *root_histogram_mc_5tev_temp[15];

   for (size_t i = 0; i < 15; i++) {
	   char buf[4096];

	   snprintf(buf, 4096, "root_histogram_mc_5tev_temp_%lu", i);

	   root_histogram_mc_5tev_temp[i] = new TH1D(buf, "", 39, yAxis);
	   root_histogram_mc_5tev_temp[i]->SetLineStyle(0);
	   root_histogram_mc_5tev_temp[i]->SetMarkerStyle(25);
	   root_histogram_mc_5tev_temp[i]->GetXaxis()->SetLabelFont(42);
	   root_histogram_mc_5tev_temp[i]->GetXaxis()->SetLabelOffset(0.01);
	   root_histogram_mc_5tev_temp[i]->GetXaxis()->SetLabelSize(0.0625);
	   root_histogram_mc_5tev_temp[i]->GetXaxis()->SetTitleSize(0.0625);
	   root_histogram_mc_5tev_temp[i]->GetXaxis()->SetTitleFont(42);
	   root_histogram_mc_5tev_temp[i]->GetYaxis()->SetLabelFont(42);
	   root_histogram_mc_5tev_temp[i]->GetYaxis()->SetLabelOffset(0.01);
	   root_histogram_mc_5tev_temp[i]->GetYaxis()->SetLabelSize(0.0625);
	   root_histogram_mc_5tev_temp[i]->GetYaxis()->SetTitleSize(0.0625);
	   root_histogram_mc_5tev_temp[i]->GetYaxis()->SetTitleOffset(1.5);
	   root_histogram_mc_5tev_temp[i]->GetYaxis()->SetTitleFont(42);
	   root_histogram_mc_5tev_temp[i]->GetZaxis()->SetLabelFont(42);
	   root_histogram_mc_5tev_temp[i]->GetZaxis()->SetLabelOffset(0.01);
	   root_histogram_mc_5tev_temp[i]->GetZaxis()->SetLabelSize(0.045);
	   root_histogram_mc_5tev_temp[i]->GetZaxis()->SetTitleSize(0.035);
	   root_histogram_mc_5tev_temp[i]->GetZaxis()->SetTitleFont(42);

//	   const double perp_jet = root_histogram_mc5tev50_jet->GetXaxis()->GetBinLowEdge(i * 8 + 1);
	   TH1D *hj = NULL;
	   TH2D *ht = NULL;
	   TH2D *hts = NULL;

	   TH1D *hjr = NULL;

/*	   if (perp_jet < 60) {
		   hj = root_histogram_mc5tev50_jet;
		   ht = root_histogram_mc5tev50_track;
		   hts = root_histogram_mc5tev50_track_reflected;
		   hjr = root_histogram_mc5tev50_jet;
	   }
	   else if (perp_jet < 80) {
		   hj = root_histogram_mc5tev50_jet;
		   ht = root_histogram_mc5tev50_track;
		   hts = root_histogram_mc5tev50_track_reflected;
		   hjr = root_histogram_mc5tev50_jet;
	   }
	   else if (perp_jet < 100) {
		   hj = root_histogram_mc5tev50_jet;
		   ht = root_histogram_mc5tev50_track;
		   hts = root_histogram_mc5tev50_track_reflected;
		   hjr = root_histogram_mc5tev50_jet;
	   }
	   else {
		   hj = root_histogram_mc5tev80_jet;
		   ht = root_histogram_mc5tev80_track;
		   hts = root_histogram_mc5tev80_track_reflected;
		   hjr = root_histogram_mc5tev80_jet;
	   }*/

		   hj = root_histogram_mc5tev50_jet;
		   ht = root_histogram_mc5tev50_track;
		   hts = root_histogram_mc5tev50_track_reflected;
		   hjr = root_histogram_mc5tev50_jet;

	   for (size_t j = 0; j < 39; j++) {
		   double sum_content = 0;
		   double sum_error = 0;
		   double sum_denominator = 0;
//testing
		   for (size_t k = 0; k < (i == 7 ? 24 : 8); k++) {

			   if (hj->GetBinContent(i * 8 + k + 1) > 0 && hjr->GetBinContent(i * 8 + k + 1) > 0) {
				   const double weight = hjr->GetBinContent(i * 8 + k + 1) / hj->GetBinContent(i * 8 + k + 1);
				   const int root_bin = ht->GetBin(i * 8 + k + 1, j + 1);

				   sum_content += ht->GetBinContent(root_bin) * weight;
				   sum_error += ht->GetBinError(root_bin) * ht->GetBinError(root_bin) * weight * weight;
				   if (hts != NULL) {
					   sum_content -= hts->GetBinContent(root_bin) * weight;
					   sum_error += hts->GetBinError(root_bin) * hts->GetBinError(root_bin) * weight * weight;
				   }
				   sum_denominator += hj->GetBinContent(i * 8 + k + 1) * weight;
			   }
		   }
		   //fprintf(stderr, "%f %f %f\n", sum_content, sum_error, sum_denominator);
		   sum_denominator *= ht->GetYaxis()->GetBinWidth(j + 1);

		   root_histogram_mc_5tev_temp[i]->SetBinContent(j + 1, sum_content / sum_denominator);
		   root_histogram_mc_5tev_temp[i]->SetBinError(j + 1, sqrt(sum_content) / sum_denominator);
	   }
   }


#if 0
   TH1D *root_histogram_mc_2tev_temp[15];

   for (size_t i = 0; i < 15; i++) {
	   char buf[4096];

	   snprintf(buf, 4096, "root_histogram_mc_2tev_temp_%lu", i);

	   root_histogram_mc_2tev_temp[i] = new TH1D(buf, "", 39, yAxis);
	   root_histogram_mc_2tev_temp[i]->SetLineStyle(0);
	   root_histogram_mc_2tev_temp[i]->SetMarkerStyle(25);
	   root_histogram_mc_2tev_temp[i]->GetXaxis()->SetLabelFont(42);
	   root_histogram_mc_2tev_temp[i]->GetXaxis()->SetLabelOffset(0.01);
	   root_histogram_mc_2tev_temp[i]->GetXaxis()->SetLabelSize(0.0625);
	   root_histogram_mc_2tev_temp[i]->GetXaxis()->SetTitleSize(0.0625);
	   root_histogram_mc_2tev_temp[i]->GetXaxis()->SetTitleFont(42);
	   root_histogram_mc_2tev_temp[i]->GetYaxis()->SetLabelFont(42);
	   root_histogram_mc_2tev_temp[i]->GetYaxis()->SetLabelOffset(0.01);
	   root_histogram_mc_2tev_temp[i]->GetYaxis()->SetLabelSize(0.0625);
	   root_histogram_mc_2tev_temp[i]->GetYaxis()->SetTitleSize(0.0625);
	   root_histogram_mc_2tev_temp[i]->GetYaxis()->SetTitleOffset(1.5);
	   root_histogram_mc_2tev_temp[i]->GetYaxis()->SetTitleFont(42);
	   root_histogram_mc_2tev_temp[i]->GetZaxis()->SetLabelFont(42);
	   root_histogram_mc_2tev_temp[i]->GetZaxis()->SetLabelOffset(0.01);
	   root_histogram_mc_2tev_temp[i]->GetZaxis()->SetLabelSize(0.045);
	   root_histogram_mc_2tev_temp[i]->GetZaxis()->SetTitleSize(0.035);
	   root_histogram_mc_2tev_temp[i]->GetZaxis()->SetTitleFont(42);

	   const double perp_jet = root_histogram_mc2tev50_jet->GetXaxis()->GetBinLowEdge(i * 8 + 1);
	   TH1D *hj = NULL;
	   TH2D *ht = NULL;
	   TH2D *hts = NULL;

	   TH1D *hjr = NULL;

	   if (perp_jet < 60) {
		   hj = root_histogram_mc2tev50_jet;
		   ht = root_histogram_mc2tev50_track;
		   hts = root_histogram_mc2tev50_track_reflected;
		   hjr = root_histogram_mc5tev50_jet;
	   }
	   else if (perp_jet < 80) {
		   hj = root_histogram_mc2tev50_jet;
		   ht = root_histogram_mc2tev50_track;
		   hts = root_histogram_mc2tev50_track_reflected;
		   hjr = root_histogram_mc5tev50_jet;
	   }
	   else if (perp_jet < 100) {
		   hj = root_histogram_mc2tev50_jet;
		   ht = root_histogram_mc2tev50_track;
		   hts = root_histogram_mc2tev50_track_reflected;
		   hjr = root_histogram_mc5tev50_jet;
	   }
	   else {
		   hj = root_histogram_mc2tev80_jet;
		   ht = root_histogram_mc2tev80_track;
		   hts = root_histogram_mc2tev80_track_reflected;
		   hjr = root_histogram_mc5tev80_jet;
	   }

	   for (size_t j = 0; j < 39; j++) {
		   double sum_content = 0;
		   double sum_error = 0;
		   double sum_denominator = 0;

		   for (size_t k = 0; k < (j == 7 ? 24 : 8); k++) {

			   if (hj->GetBinContent(i * 8 + k + 1) > 0 && hjr->GetBinContent(i * 8 + k + 1) > 0) {
				   const double weight = hjr->GetBinContent(i * 8 + k + 1) / hj->GetBinContent(i * 8 + k + 1);
				   const int root_bin = ht->GetBin(i * 8 + k + 1, j + 1);

				   sum_content += ht->GetBinContent(root_bin) * weight;
				   sum_error += ht->GetBinError(root_bin) * ht->GetBinError(root_bin) * weight * weight;
				   if (hts != NULL) {
					   sum_content -= hts->GetBinContent(root_bin) * weight;
					   sum_error += hts->GetBinError(root_bin) * hts->GetBinError(root_bin) * weight * weight;
				   }
				   sum_denominator += hj->GetBinContent(i * 8 + k + 1) * weight;
			   }
		   }
		   //fprintf(stderr, "%f %f %f\n", sum_content, sum_error, sum_denominator);
		   sum_denominator *= ht->GetYaxis()->GetBinWidth(j + 1);

		   root_histogram_mc_2tev_temp[i]->SetBinContent(j + 1, sum_content / sum_denominator);
		   root_histogram_mc_2tev_temp[i]->SetBinError(j + 1, sqrt(sum_content) / sum_denominator);
	   }
   }
#endif

/////////////////////////////////////////////////////////////////////

   TH1D *root_histogram_data_interp_temp[15];

   for (size_t i = 0; i < 15; i++) {
	   char buf[4096];

	   snprintf(buf, 4096, "root_histogram_data_interp_temp_%lu", i);

	   root_histogram_data_interp_temp[i] = new TH1D(buf, "", 39, yAxis);
	   root_histogram_data_interp_temp[i]->SetLineStyle(0);
	   root_histogram_data_interp_temp[i]->SetMarkerStyle(25);
	   root_histogram_data_interp_temp[i]->GetXaxis()->SetLabelFont(42);
	   root_histogram_data_interp_temp[i]->GetXaxis()->SetLabelOffset(0.01);
	   root_histogram_data_interp_temp[i]->GetXaxis()->SetLabelSize(0.0625);
	   root_histogram_data_interp_temp[i]->GetXaxis()->SetTitleSize(0.0625);
	   root_histogram_data_interp_temp[i]->GetXaxis()->SetTitleFont(42);
	   root_histogram_data_interp_temp[i]->GetYaxis()->SetLabelFont(42);
	   root_histogram_data_interp_temp[i]->GetYaxis()->SetLabelOffset(0.01);
	   root_histogram_data_interp_temp[i]->GetYaxis()->SetLabelSize(0.0625);
	   root_histogram_data_interp_temp[i]->GetYaxis()->SetTitleSize(0.0625);
	   root_histogram_data_interp_temp[i]->GetYaxis()->SetTitleOffset(1.5);
	   root_histogram_data_interp_temp[i]->GetYaxis()->SetTitleFont(42);
	   root_histogram_data_interp_temp[i]->GetZaxis()->SetLabelFont(42);
	   root_histogram_data_interp_temp[i]->GetZaxis()->SetLabelOffset(0.01);
	   root_histogram_data_interp_temp[i]->GetZaxis()->SetLabelSize(0.045);
	   root_histogram_data_interp_temp[i]->GetZaxis()->SetTitleSize(0.035);
	   root_histogram_data_interp_temp[i]->GetZaxis()->SetTitleFont(42);

           const double perp_jet = root_histogram_data5tevmb_jet->GetXaxis()->GetBinLowEdge(i * 8 + 1);

	   TH1D *hjr = NULL;

	   if (perp_jet < 80) {
		   hjr = root_histogram_data5tevmb_jet;
	   }
	   else if (perp_jet < 140) {
		   hjr = root_histogram_data5tev40_jet;
	   }
	   else {
		   hjr = root_histogram_data5tev80_jet;
	   }

           hjr = combined_5tev_jets_smeared;

	   double sum_2tev = 0;
	   double sum_5tev = 0;
	   double sum_7tev = 0;


//here Austin here!
	   for (size_t k = 0; k < (i == 7 ? 24 : 8); k++) {
		   const double weight = hjr->GetBinContent(i * 8 + k + 1);

		   sum_2tev += root_histogram_gluon_2tev->GetBinContent(i * 8 + k + 1) * weight;
		   sum_5tev += root_histogram_gluon_5tev->GetBinContent(i * 8 + k + 1) * weight;
		   sum_7tev += root_histogram_gluon_7tev->GetBinContent(i * 8 + k + 1) * weight;
	   }

	   double u = (sum_5tev - sum_7tev) / (sum_2tev - sum_7tev);

#if 0
	   if (u < 0) {
		   u = 0;
	   }
	   else if (u >= 1) {
		   u = 1;
	   }
#endif

	   for (size_t j = 0; j < 39; j++) {
		   root_histogram_data_interp_temp[i]->SetBinContent(j + 1, u * root_histogram_data_2tev_temp[i]->GetBinContent(j + 1) + (1 - u) * root_histogram_data_7tev_temp[i]->GetBinContent(j + 1));
		   root_histogram_data_interp_temp[i]->SetBinError(j + 1, sqrt(u * u * root_histogram_data_2tev_temp[i]->GetBinError(j + 1) * root_histogram_data_2tev_temp[i]->GetBinError(j + 1) + (1 - u) * (1 - u) * root_histogram_data_7tev_temp[i]->GetBinError(j + 1) * root_histogram_data_7tev_temp[i]->GetBinError(j + 1)));
	   }
   }

   TH1D *root_histogram_mc_interp_temp[15];

   for (size_t i = 0; i < 15; i++) {
	   char buf[4096];

	   snprintf(buf, 4096, "root_histogram_mc_interp_temp_%lu", i);

	   root_histogram_mc_interp_temp[i] = new TH1D(buf, "", 39, yAxis);
	   root_histogram_mc_interp_temp[i]->SetLineStyle(0);
	   root_histogram_mc_interp_temp[i]->SetMarkerStyle(25);
	   root_histogram_mc_interp_temp[i]->GetXaxis()->SetLabelFont(42);
	   root_histogram_mc_interp_temp[i]->GetXaxis()->SetLabelOffset(0.01);
	   root_histogram_mc_interp_temp[i]->GetXaxis()->SetLabelSize(0.0625);
	   root_histogram_mc_interp_temp[i]->GetXaxis()->SetTitleSize(0.0625);
	   root_histogram_mc_interp_temp[i]->GetXaxis()->SetTitleFont(42);
	   root_histogram_mc_interp_temp[i]->GetYaxis()->SetLabelFont(42);
	   root_histogram_mc_interp_temp[i]->GetYaxis()->SetLabelOffset(0.01);
	   root_histogram_mc_interp_temp[i]->GetYaxis()->SetLabelSize(0.0625);
	   root_histogram_mc_interp_temp[i]->GetYaxis()->SetTitleSize(0.0625);
	   root_histogram_mc_interp_temp[i]->GetYaxis()->SetTitleOffset(1.5);
	   root_histogram_mc_interp_temp[i]->GetYaxis()->SetTitleFont(42);
	   root_histogram_mc_interp_temp[i]->GetZaxis()->SetLabelFont(42);
	   root_histogram_mc_interp_temp[i]->GetZaxis()->SetLabelOffset(0.01);
	   root_histogram_mc_interp_temp[i]->GetZaxis()->SetLabelSize(0.045);
	   root_histogram_mc_interp_temp[i]->GetZaxis()->SetTitleSize(0.035);
	   root_histogram_mc_interp_temp[i]->GetZaxis()->SetTitleFont(42);

	   double sum_2tev = 0;
	   double sum_5tev = 0;
	   double sum_7tev = 0;
/*
	   for (size_t k = 0; k < (j == 7 ? 24 : 8); k++) {
		   const double weight = hjr->GetBinContent(i * 8 + k + 1);

		   sum_2tev += root_histogram_gluon_2tev->GetBinContent(i * 8 + k + 1) * weight;
		   sum_5tev += root_histogram_gluon_5tev->GetBinContent(i * 8 + k + 1) * weight;
		   sum_7tev += root_histogram_gluon_7tev->GetBinContent(i * 8 + k + 1) * weight;
*/	   }

// commented out by Austin (currently unneeded?)
 	   ///double u = (sum_5tev - sum_7tev) / (sum_2tev - sum_7tev);

#if 0
	   if (u < 0) {
		   u = 0;
	   }
	   else if (u >= 1) {
		   u = 1;
	   }
#endif

#if 0
	   for (size_t j = 0; j < 39; j++) {
		   root_histogram_mc_interp_temp[i]->SetBinContent(j + 1, u * root_histogram_mc_2tev_temp[i]->GetBinContent(j + 1) + (1 - u) * root_histogram_mc_7tev_temp[i]->GetBinContent(j + 1));
		   root_histogram_mc_interp_temp[i]->SetBinError(j + 1, sqrt(u * u * root_histogram_mc_2tev_temp[i]->GetBinError(j + 1) * root_histogram_mc_2tev_temp[i]->GetBinError(j + 1) + (1 - u) * (1 - u) * root_histogram_mc_7tev_temp[i]->GetBinError(j + 1) * root_histogram_mc_7tev_temp[i]->GetBinError(j + 1)));
	   }
#endif
   

/////////////////////////////////////////////////////////////////////

   const double left_margin = canvas->GetLeftMargin();
   const double right_margin = canvas->GetRightMargin();
   const double top_margin = canvas->GetRightMargin() / canvas->GetWindowHeight() * canvas->GetWindowWidth();
   const double bottom_margin = canvas->GetBottomMargin();
   const size_t npanel_x = 5;
   const size_t npanel_y = 2;
   TPad *pad[npanel_x * npanel_y];

   for (size_t i = 0; i < 10; i++) {
	   const double lr = left_margin + right_margin;
	   const double tb = top_margin + bottom_margin;
	   const double dx = (1 - lr) / npanel_x;
	   const double dy = (1 - tb) / npanel_y;
	   const double x0 = dx * (i % 5);
	   const double y0 = dy * (i / 5);
	   const double x1 = lr + dx * ((i % 5) + 1);
	   const double y1 = tb + dy * ((i / 5) + 1);

	   char buf[4096];

	   snprintf(buf, 4096, "pad_%lu", i);

	   canvas->cd();
	   pad[i] = new TPad(buf, buf, x0, y0, x1, y1);
	   pad[i]->SetLeftMargin(left_margin / (lr + dx));
	   pad[i]->SetRightMargin(right_margin / (lr + dx));
	   pad[i]->SetTopMargin(top_margin / (tb + dy));
	   pad[i]->SetBottomMargin(bottom_margin / (tb + dy));
	   pad[i]->SetFillStyle(0);
	   pad[i]->SetFillColor(0);
	   pad[i]->SetTickx(1);
	   pad[i]->SetTicky(1);
	   pad[i]->Draw();
	   pad[i]->cd();
   }

   int color_2 = TColor::GetColor("#ca1c2c");
   int color_1 = TColor::GetColor("#4a0a7e");
   int color_3 = TColor::GetColor("#3e7c27");

   TH1D *root_histogram_ratio_track[10];
   TH1D *root_histogram_ratio_track_2tev[10];
   TH1D *root_histogram_ratio_track_7tev[10];
   TH1D *root_histogram_ratio_track_mc[10];
   TH1D *root_histogram_ratio_track_mc_2tev[10];
   TH1D *root_histogram_ratio_track_mc_7tev[10];
   TLine *line_1[10];
   TMathText *tex_perp_jet[10];
   TMathText *tex_reco[2];

   for (size_t i = 0; i < 5; i++) {
	   char buf[4096];

	   snprintf(buf, 4096, "root_histogram_ratio_track_%lu", i);

	   root_histogram_ratio_track[i] = new TH1D(buf, "", 39, yAxis);

	   const size_t index_perp_jet = i + 3;

	   root_histogram_ratio_track[i]->Divide(root_histogram_data_5tev_temp[index_perp_jet], root_histogram_data_interp_temp[index_perp_jet], 1, 1);
	   root_histogram_ratio_track[i]->SetLineStyle(0);
	   root_histogram_ratio_track[i]->SetMarkerStyle(20);
	   root_histogram_ratio_track[i]->GetXaxis()->SetLabelFont(42);
	   root_histogram_ratio_track[i]->GetXaxis()->SetLabelOffset(0.01);
	   root_histogram_ratio_track[i]->GetXaxis()->SetLabelSize(0.0625);
	   root_histogram_ratio_track[i]->GetXaxis()->SetTitleSize(0.0625);
	   root_histogram_ratio_track[i]->GetXaxis()->SetTitleFont(42);
	   root_histogram_ratio_track[i]->GetYaxis()->SetLabelFont(42);
	   root_histogram_ratio_track[i]->GetYaxis()->SetLabelOffset(0.01);
	   root_histogram_ratio_track[i]->GetYaxis()->SetLabelSize(i % 5 == 0 ? 0.0625 : 0);
	   root_histogram_ratio_track[i]->GetYaxis()->SetTitleSize(i % 5 == 0 ? 0.0625 : 0);
	   root_histogram_ratio_track[i]->GetYaxis()->SetTitleOffset(1.5);
	   root_histogram_ratio_track[i]->GetYaxis()->SetTitleFont(42);
	   root_histogram_ratio_track[i]->GetZaxis()->SetLabelFont(42);
	   root_histogram_ratio_track[i]->GetZaxis()->SetLabelOffset(0.01);
	   root_histogram_ratio_track[i]->GetZaxis()->SetLabelSize(0.045);
	   root_histogram_ratio_track[i]->GetZaxis()->SetTitleSize(0.035);
	   root_histogram_ratio_track[i]->GetZaxis()->SetTitleFont(42);

	   root_histogram_ratio_track[i]->SetLineColor(kBlack);
	   root_histogram_ratio_track[i]->GetXaxis()->SetRangeUser(0, 95);
	   root_histogram_ratio_track[i]->GetYaxis()->SetRangeUser(0.5, 2.0 - 1e-4);
	   root_histogram_ratio_track[i]->GetXaxis()->SetTitle("p_T^\\mathrm{track}\\:(\\mathrm{GeV}/c)");
	   root_histogram_ratio_track[i]->GetYaxis()->SetTitle("D_\\mathrm{pPb}(p_T^\\mathrm{track})/D_\\mathrm{pp}(p_T^\\mathrm{track})");
	   root_histogram_ratio_track[i]->GetXaxis()->SetTitleOffset(1.25);

	   snprintf(buf, 4096, "root_histogram_ratio_track_mc_%lu", i);

	   root_histogram_ratio_track_mc[i] = new TH1D(buf, "", 39, yAxis);

	   root_histogram_ratio_track_mc[i]->Divide(root_histogram_mc_5tev_temp[index_perp_jet], root_histogram_mc_interp_temp[index_perp_jet], 1, 1);
	   root_histogram_ratio_track_mc[i]->SetLineColor(kBlack);
	   root_histogram_ratio_track_mc[i]->GetXaxis()->SetLabelFont(42);
	   root_histogram_ratio_track_mc[i]->GetXaxis()->SetLabelOffset(0.01);
	   root_histogram_ratio_track_mc[i]->GetXaxis()->SetLabelSize(0.0625);
	   root_histogram_ratio_track_mc[i]->GetXaxis()->SetTitleSize(0.0625);
	   root_histogram_ratio_track_mc[i]->GetXaxis()->SetTitleFont(42);
	   root_histogram_ratio_track_mc[i]->GetYaxis()->SetLabelFont(42);
	   root_histogram_ratio_track_mc[i]->GetYaxis()->SetLabelOffset(0.01);
	   root_histogram_ratio_track_mc[i]->GetYaxis()->SetLabelSize(i % 5 == 0 ? 0.0625 : 0);
	   root_histogram_ratio_track_mc[i]->GetYaxis()->SetTitleSize(i % 5 == 0 ? 0.0625 : 0);
	   root_histogram_ratio_track_mc[i]->GetYaxis()->SetTitleOffset(1.5);
	   root_histogram_ratio_track_mc[i]->GetYaxis()->SetTitleFont(42);
	   root_histogram_ratio_track_mc[i]->GetZaxis()->SetLabelFont(42);
	   root_histogram_ratio_track_mc[i]->GetZaxis()->SetLabelOffset(0.01);
	   root_histogram_ratio_track_mc[i]->GetZaxis()->SetLabelSize(0.045);
	   root_histogram_ratio_track_mc[i]->GetZaxis()->SetTitleSize(0.035);
	   root_histogram_ratio_track_mc[i]->GetZaxis()->SetTitleFont(42);

	   root_histogram_ratio_track_mc[i]->SetLineColor(kBlack);
	   root_histogram_ratio_track_mc[i]->GetXaxis()->SetRangeUser(0, 95);
	   root_histogram_ratio_track_mc[i]->GetYaxis()->SetRangeUser(0.5, 2.0 - 1e-4);
	   root_histogram_ratio_track_mc[i]->GetXaxis()->SetTitle("\\xi = \\ln(1/z)");
	   root_histogram_ratio_track_mc[i]->GetYaxis()->SetTitle("D_\\mathrm{pPb}(\\xi)/D_\\mathrm{pp}(\\xi)");

#if 0
	   snprintf(buf, 4096, "root_histogram_ratio_track_mc_2tev_%lu", i);

	   root_histogram_ratio_track_mc_2tev[i] = new TH1D(buf, "", 39, yAxis);

	   root_histogram_ratio_track_mc_2tev[i]->Divide(root_histogram_mc_2tev_temp[index_perp_jet], root_histogram_mc_interp_temp[index_perp_jet], 1, 1);
	   root_histogram_ratio_track_mc_2tev[i]->SetLineColor(kBlack);
	   root_histogram_ratio_track_mc_2tev[i]->GetXaxis()->SetLabelFont(42);
	   root_histogram_ratio_track_mc_2tev[i]->GetXaxis()->SetLabelOffset(0.01);
	   root_histogram_ratio_track_mc_2tev[i]->GetXaxis()->SetLabelSize(0.0625);
	   root_histogram_ratio_track_mc_2tev[i]->GetXaxis()->SetTitleSize(0.0625);
	   root_histogram_ratio_track_mc_2tev[i]->GetXaxis()->SetTitleFont(42);
	   root_histogram_ratio_track_mc_2tev[i]->GetYaxis()->SetLabelFont(42);
	   root_histogram_ratio_track_mc_2tev[i]->GetYaxis()->SetLabelOffset(0.01);
	   root_histogram_ratio_track_mc_2tev[i]->GetYaxis()->SetLabelSize(i % 5 == 0 ? 0.0625 : 0);
	   root_histogram_ratio_track_mc_2tev[i]->GetYaxis()->SetTitleSize(i % 5 == 0 ? 0.0625 : 0);
	   root_histogram_ratio_track_mc_2tev[i]->GetYaxis()->SetTitleOffset(1.5);
	   root_histogram_ratio_track_mc_2tev[i]->GetYaxis()->SetTitleFont(42);
	   root_histogram_ratio_track_mc_2tev[i]->GetZaxis()->SetLabelFont(42);
	   root_histogram_ratio_track_mc_2tev[i]->GetZaxis()->SetLabelOffset(0.01);
	   root_histogram_ratio_track_mc_2tev[i]->GetZaxis()->SetLabelSize(0.045);
	   root_histogram_ratio_track_mc_2tev[i]->GetZaxis()->SetTitleSize(0.035);
	   root_histogram_ratio_track_mc_2tev[i]->GetZaxis()->SetTitleFont(42);

	   root_histogram_ratio_track_mc_2tev[i]->SetLineColor(kBlack);
	   root_histogram_ratio_track_mc_2tev[i]->GetXaxis()->SetRangeUser(0, 95);
	   root_histogram_ratio_track_mc_2tev[i]->GetYaxis()->SetRangeUser(0.5, 2.0 - 1e-4);
	   root_histogram_ratio_track_mc_2tev[i]->GetXaxis()->SetTitle("\\xi = \\ln(1/z)");
	   root_histogram_ratio_track_mc_2tev[i]->GetYaxis()->SetTitle("D_\\mathrm{pPb}(\\xi)/D_\\mathrm{pp}(\\xi)");

	   snprintf(buf, 4096, "root_histogram_ratio_track_mc_7tev_%lu", i);

	   root_histogram_ratio_track_mc_7tev[i] = new TH1D(buf, "", 39, yAxis);

	   root_histogram_ratio_track_mc_7tev[i]->Divide(root_histogram_mc_7tev_temp[index_perp_jet], root_histogram_mc_interp_temp[index_perp_jet], 1, 1);
	   root_histogram_ratio_track_mc_7tev[i]->SetLineColor(kBlack);
	   root_histogram_ratio_track_mc_7tev[i]->GetXaxis()->SetLabelFont(42);
	   root_histogram_ratio_track_mc_7tev[i]->GetXaxis()->SetLabelOffset(0.01);
	   root_histogram_ratio_track_mc_7tev[i]->GetXaxis()->SetLabelSize(0.0625);
	   root_histogram_ratio_track_mc_7tev[i]->GetXaxis()->SetTitleSize(0.0625);
	   root_histogram_ratio_track_mc_7tev[i]->GetXaxis()->SetTitleFont(42);
	   root_histogram_ratio_track_mc_7tev[i]->GetYaxis()->SetLabelFont(42);
	   root_histogram_ratio_track_mc_7tev[i]->GetYaxis()->SetLabelOffset(0.01);
	   root_histogram_ratio_track_mc_7tev[i]->GetYaxis()->SetLabelSize(i % 5 == 0 ? 0.0625 : 0);
	   root_histogram_ratio_track_mc_7tev[i]->GetYaxis()->SetTitleSize(i % 5 == 0 ? 0.0625 : 0);
	   root_histogram_ratio_track_mc_7tev[i]->GetYaxis()->SetTitleOffset(1.5);
	   root_histogram_ratio_track_mc_7tev[i]->GetYaxis()->SetTitleFont(42);
	   root_histogram_ratio_track_mc_7tev[i]->GetZaxis()->SetLabelFont(42);
	   root_histogram_ratio_track_mc_7tev[i]->GetZaxis()->SetLabelOffset(0.01);
	   root_histogram_ratio_track_mc_7tev[i]->GetZaxis()->SetLabelSize(0.045);
	   root_histogram_ratio_track_mc_7tev[i]->GetZaxis()->SetTitleSize(0.035);
	   root_histogram_ratio_track_mc_7tev[i]->GetZaxis()->SetTitleFont(42);

	   root_histogram_ratio_track_mc_7tev[i]->SetLineColor(kBlack);
	   root_histogram_ratio_track_mc_7tev[i]->GetXaxis()->SetRangeUser(0, 95);
	   root_histogram_ratio_track_mc_7tev[i]->GetYaxis()->SetRangeUser(0.5, 2.0 - 1e-4);
	   root_histogram_ratio_track_mc_7tev[i]->GetXaxis()->SetTitle("\\xi = \\ln(1/z)");
	   root_histogram_ratio_track_mc_7tev[i]->GetYaxis()->SetTitle("D_\\mathrm{pPb}(\\xi)/D_\\mathrm{pp}(\\xi)");
#endif

	   snprintf(buf, 4096, "root_histogram_ratio_track_2tev_%lu", i);

	   root_histogram_ratio_track_2tev[i] = new TH1D(buf, "", 39, yAxis);

	   root_histogram_ratio_track_2tev[i]->Divide(root_histogram_data_2tev_temp[index_perp_jet], root_histogram_data_interp_temp[index_perp_jet], 1, 1);
	   root_histogram_ratio_track_2tev[i]->SetLineColor(kBlack);
	   root_histogram_ratio_track_2tev[i]->GetXaxis()->SetLabelFont(42);
	   root_histogram_ratio_track_2tev[i]->GetXaxis()->SetLabelOffset(0.01);
	   root_histogram_ratio_track_2tev[i]->GetXaxis()->SetLabelSize(0.0625);
	   root_histogram_ratio_track_2tev[i]->GetXaxis()->SetTitleSize(0.0625);
	   root_histogram_ratio_track_2tev[i]->GetXaxis()->SetTitleFont(42);
	   root_histogram_ratio_track_2tev[i]->GetYaxis()->SetLabelFont(42);
	   root_histogram_ratio_track_2tev[i]->GetYaxis()->SetLabelOffset(0.01);
	   root_histogram_ratio_track_2tev[i]->GetYaxis()->SetLabelSize(i % 5 == 0 ? 0.0625 : 0);
	   root_histogram_ratio_track_2tev[i]->GetYaxis()->SetTitleSize(i % 5 == 0 ? 0.0625 : 0);
	   root_histogram_ratio_track_2tev[i]->GetYaxis()->SetTitleOffset(1.5);
	   root_histogram_ratio_track_2tev[i]->GetYaxis()->SetTitleFont(42);
	   root_histogram_ratio_track_2tev[i]->GetZaxis()->SetLabelFont(42);
	   root_histogram_ratio_track_2tev[i]->GetZaxis()->SetLabelOffset(0.01);
	   root_histogram_ratio_track_2tev[i]->GetZaxis()->SetLabelSize(0.045);
	   root_histogram_ratio_track_2tev[i]->GetZaxis()->SetTitleSize(0.035);
	   root_histogram_ratio_track_2tev[i]->GetZaxis()->SetTitleFont(42);

	   root_histogram_ratio_track_2tev[i]->SetLineColor(kBlack);
	   root_histogram_ratio_track_2tev[i]->GetXaxis()->SetRangeUser(0, 95);
	   root_histogram_ratio_track_2tev[i]->GetYaxis()->SetRangeUser(0.5, 2.0 - 1e-4);
	   root_histogram_ratio_track_2tev[i]->GetXaxis()->SetTitle("\\xi = \\ln(1/z)");
	   root_histogram_ratio_track_2tev[i]->GetYaxis()->SetTitle("D_\\mathrm{pPb}(\\xi)/D_\\mathrm{pp}(\\xi)");

	   snprintf(buf, 4096, "root_histogram_ratio_track_7tev_%lu", i);

	   root_histogram_ratio_track_7tev[i] = new TH1D(buf, "", 39, yAxis);

	   root_histogram_ratio_track_7tev[i]->Divide(root_histogram_data_7tev_temp[index_perp_jet], root_histogram_data_interp_temp[index_perp_jet], 1, 1);
	   root_histogram_ratio_track_7tev[i]->SetLineColor(kBlack);
	   root_histogram_ratio_track_7tev[i]->GetXaxis()->SetLabelFont(42);
	   root_histogram_ratio_track_7tev[i]->GetXaxis()->SetLabelOffset(0.01);
	   root_histogram_ratio_track_7tev[i]->GetXaxis()->SetLabelSize(0.0625);
	   root_histogram_ratio_track_7tev[i]->GetXaxis()->SetTitleSize(0.0625);
	   root_histogram_ratio_track_7tev[i]->GetXaxis()->SetTitleFont(42);
	   root_histogram_ratio_track_7tev[i]->GetYaxis()->SetLabelFont(42);
	   root_histogram_ratio_track_7tev[i]->GetYaxis()->SetLabelOffset(0.01);
	   root_histogram_ratio_track_7tev[i]->GetYaxis()->SetLabelSize(i % 5 == 0 ? 0.0625 : 0);
	   root_histogram_ratio_track_7tev[i]->GetYaxis()->SetTitleSize(i % 5 == 0 ? 0.0625 : 0);
	   root_histogram_ratio_track_7tev[i]->GetYaxis()->SetTitleOffset(1.5);
	   root_histogram_ratio_track_7tev[i]->GetYaxis()->SetTitleFont(42);
	   root_histogram_ratio_track_7tev[i]->GetZaxis()->SetLabelFont(42);
	   root_histogram_ratio_track_7tev[i]->GetZaxis()->SetLabelOffset(0.01);
	   root_histogram_ratio_track_7tev[i]->GetZaxis()->SetLabelSize(0.045);
	   root_histogram_ratio_track_7tev[i]->GetZaxis()->SetTitleSize(0.035);
	   root_histogram_ratio_track_7tev[i]->GetZaxis()->SetTitleFont(42);

	   root_histogram_ratio_track_7tev[i]->SetLineColor(kBlack);
	   root_histogram_ratio_track_7tev[i]->GetXaxis()->SetRangeUser(0, 95);
	   root_histogram_ratio_track_7tev[i]->GetYaxis()->SetRangeUser(0.5, 2.0 - 1e-4);
	   root_histogram_ratio_track_7tev[i]->GetXaxis()->SetTitle("\\xi = \\ln(1/z)");
	   root_histogram_ratio_track_7tev[i]->GetYaxis()->SetTitle("D_\\mathrm{pPb}(\\xi)/D_\\mathrm{pp}(\\xi)");

	   pad[5 + (i % 5)]->cd();
	   pad[5 + (i % 5)]->SetLogx();
	   pad[5 + (i % 5)]->SetLogy();

	   root_histogram_data_5tev_temp[index_perp_jet]->GetXaxis()->SetRangeUser(0.5, 100);
	   root_histogram_data_5tev_temp[index_perp_jet]->GetYaxis()->SetRangeUser(1e-6, 10);
	   root_histogram_data_5tev_temp[index_perp_jet]->GetXaxis()->SetLabelSize(0);
	   root_histogram_data_5tev_temp[index_perp_jet]->GetXaxis()->SetTitleSize(0);
	   root_histogram_data_5tev_temp[index_perp_jet]->GetYaxis()->SetLabelSize(i % 5 == 0 ? 0.0625 : 0);
	   root_histogram_data_5tev_temp[index_perp_jet]->GetYaxis()->SetTitleSize(i % 5 == 0 ? 0.0625 : 0);
	   root_histogram_data_5tev_temp[index_perp_jet]->GetYaxis()->SetTitle("D(p_T^\\mathrm{track})\\:(\\mathrm{GeV}^{-1}c)");
	   root_histogram_data_5tev_temp[index_perp_jet]->SetMarkerStyle(20);
	   root_histogram_data_5tev_temp[index_perp_jet]->SetMarkerColor(color_1);
	   root_histogram_data_5tev_temp[index_perp_jet]->SetLineColor(color_1);
	   root_histogram_data_5tev_temp[index_perp_jet]->Draw("e1x0");
	   root_histogram_data_7tev_temp[index_perp_jet]->SetMarkerColor(color_2);
	   root_histogram_data_7tev_temp[index_perp_jet]->SetLineColor(color_2);
	   root_histogram_data_7tev_temp[index_perp_jet]->Draw("e1x0same");
	   //root_histogram_data_5tev_temp_2[index_perp_jet]->Draw("e1x0same");

	   root_histogram_data_2tev_temp[index_perp_jet]->SetMarkerStyle(27);
	   root_histogram_data_2tev_temp[index_perp_jet]->SetMarkerSize(1.75);
	   root_histogram_data_2tev_temp[index_perp_jet]->SetMarkerColor(color_3);
	   root_histogram_data_2tev_temp[index_perp_jet]->SetLineColor(color_3);
	   root_histogram_data_2tev_temp[index_perp_jet]->Draw("e1x0same");

#if 0
	   root_histogram_mc_7tev_temp[index_perp_jet]->SetMarkerStyle(0);
	   root_histogram_mc_7tev_temp[index_perp_jet]->SetLineColor(kBlack);
	   root_histogram_mc_7tev_temp[index_perp_jet]->SetLineStyle(7);
	   root_histogram_mc_7tev_temp[index_perp_jet]->Draw("hsame");

	   root_histogram_mc_5tev_temp[index_perp_jet]->SetMarkerStyle(0);
	   root_histogram_mc_5tev_temp[index_perp_jet]->SetLineColor(kBlack);
	   root_histogram_mc_5tev_temp[index_perp_jet]->Draw("hsame");

	   root_histogram_mc_2tev_temp[index_perp_jet]->SetMarkerStyle(0);
	   root_histogram_mc_2tev_temp[index_perp_jet]->SetLineColor(kRed + 1);
	   root_histogram_mc_2tev_temp[index_perp_jet]->Draw("hsame");
#endif

	   snprintf(buf, 4096, "%g \\le p_T^\\mathrm{jet} < %g\\:\\mathrm{GeV}/c", index_perp_jet * 20.0, (index_perp_jet + (index_perp_jet == 7 ? 3 : 1)) * 20.0);

	   tex_perp_jet[i] = new TMathText(0.95, 0.95, buf);	   
	   tex_perp_jet[i]->SetNDC();
	   tex_perp_jet[i]->SetTextAlign(33);
	   tex_perp_jet[i]->SetTextSize(0.0625);
	   tex_perp_jet[i]->Draw();

	   pad[5 + (i % 5)]->Update();

	   pad[0 + (i % 5)]->cd();
	   pad[0 + (i % 5)]->SetLogx();

	   root_histogram_ratio_track[i]->GetXaxis()->SetRangeUser(0.5, 100);
	   root_histogram_ratio_track[i]->GetYaxis()->SetRangeUser(0, 2.0 - 1e-5);
	   root_histogram_ratio_track[i]->SetMarkerStyle(20);
	   root_histogram_ratio_track[i]->SetMarkerColor(color_1);
	   root_histogram_ratio_track[i]->SetLineColor(color_1);
	   root_histogram_ratio_track[i]->Draw("e1x0");

	   // root_histogram_ratio_track_7tev[i]->SetMarkerStyle(25);
	   // root_histogram_ratio_track_7tev[i]->SetMarkerColor(color_2);
	   // root_histogram_ratio_track_7tev[i]->SetLineColor(color_2);
	   // root_histogram_ratio_track_7tev[i]->Draw("e1x0same");

	   // root_histogram_ratio_track_2tev[i]->SetMarkerStyle(27);
	   // root_histogram_ratio_track_2tev[i]->SetMarkerSize(1.75);
	   // root_histogram_ratio_track_2tev[i]->SetMarkerColor(color_3);
	   // root_histogram_ratio_track_2tev[i]->SetLineColor(color_3);
	   // root_histogram_ratio_track_2tev[i]->Draw("e1x0same");

#if 0
	   root_histogram_ratio_track_mc[i]->Draw("hsame");

	   root_histogram_ratio_track_mc_7tev[i]->SetMarkerStyle(0);
	   root_histogram_ratio_track_mc_7tev[i]->SetLineColor(kBlack);
	   root_histogram_ratio_track_mc_7tev[i]->SetLineStyle(7);
	   root_histogram_ratio_track_mc_7tev[i]->Draw("hsame");

	   root_histogram_ratio_track_mc_2tev[i]->SetMarkerStyle(0);
	   root_histogram_ratio_track_mc_2tev[i]->SetLineColor(kRed + 1);
	   root_histogram_ratio_track_mc_2tev[i]->Draw("hsame");
#endif

	   line_1[i] = new TLine(0.4, 1, 206.8, 1);
	   line_1[i]->SetLineStyle(7);
           line_1[i]->SetLineColor(1);
	   line_1[i]->Draw();

	   pad[0 + (i % 5)]->Update();
   }

   pad[5 + 4]->cd();

   TLegend *leg = new TLegend(0.35,0.2,0.85,0.4,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.0625*0.75);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   leg->AddEntry(root_histogram_data_2tev_temp[7], "\\text{pp, }\\sqrt{s} = 2.76\\:\\mathrm{TeV}", "p");
   leg->AddEntry(root_histogram_data_5tev_temp[7], "\\text{pPb, }\\sqrt{s_{NN}} = 5.02\\:\\mathrm{TeV}", "p");
   leg->AddEntry(root_histogram_data_7tev_temp[7], "\\text{pp, }\\sqrt{s} = 7\\:\\mathrm{TeV}", "p");
   leg->Draw();


#if 0
   // canvas->SetLogy();

   TLine *line = new TLine(0.4, 1, 206.8, 1);
   line->SetLineStyle(7);
   line->Draw();

#if 0
   TLegend *leg = new TLegend(0.5,0.7,0.9,0.95,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04101562);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   leg->AddEntry(root_histogram_ratio_track, "\\mathrm{AK3PF}", "");
   leg->AddEntry(root_histogram_ratio_track, "|\\eta_\\mathrm{CM}^\\mathrm{jet}| < 1", "");
   leg->AddEntry(root_histogram_ratio_track, "\\text{Tracks}", "p");
   leg->AddEntry(root_histogram_ratio_pf, "\\text{PF charged}", "p");
   leg->AddEntry(root_histogram_ratio_track, "\\text{pPb only}", "");
   leg->Draw();
#endif
#endif

   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
   canvas->SaveAs("plots/FFs_vs_trackpt_smeared.png");

   return;
}
