#include "TH1D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TAttMarker.h"
#include "TColor.h"
#include "TAttPad.h"
#include "TAttLine.h"
#include "TAxis.h"
#include "TLegend.h"

void plotGluonFraction(const char * tag)
{
  TCanvas * cg1 = new TCanvas("cg1","",800,600);
  cg1->SetLeftMargin(0.2);

  gluon_2tev_reco->SetLineWidth(2);
  gluon_5tev_reco->SetLineWidth(2);
  gluon_7tev_reco->SetLineWidth(2);
  gluon_2tev_reco->SetLineColor(1);
  gluon_5tev_reco->SetLineColor(kRed+1);
  gluon_7tev_reco->SetLineColor(kBlue+1);
  gluon_2tev_gen->SetLineWidth(1);
  gluon_5tev_gen->SetLineWidth(1);
  gluon_7tev_gen->SetLineWidth(1);
 
  gluon_2tev_reco->SetMarkerColor(1); 
  gluon_5tev_reco->SetMarkerColor(kRed+1);
  gluon_7tev_reco->SetMarkerColor(kBlue+1);
  gluon_2tev_reco->SetMarkerStyle(20);
  gluon_5tev_reco->SetMarkerStyle(20);
  gluon_7tev_reco->SetMarkerStyle(20);
 
  gluon_2tev_gen->SetLineColor(1);
  gluon_5tev_gen->SetLineColor(kRed+1);
  gluon_7tev_gen->SetLineColor(kBlue+1);

  gluon_2tev_reco->SetMarkerSize(0.8);
  gluon_5tev_reco->SetMarkerSize(0.8);
  gluon_7tev_reco->SetMarkerSize(0.8);
  gluon_2tev_gen->SetMarkerSize(0);
  gluon_5tev_gen->SetMarkerSize(0);
  gluon_7tev_gen->SetMarkerSize(0);

  gluon_2tev_reco->SetMaximum(0.75);
  gluon_2tev_reco->SetMinimum(0.3);
  gluon_2tev_reco->GetXaxis()->SetRangeUser(60,200);
  gluon_2tev_reco->GetXaxis()->SetTitle("p_{t}^{jet}");
  gluon_2tev_reco->GetYaxis()->SetTitle("Gluon Fraction");
  gluon_2tev_reco->GetYaxis()->SetTitleOffset(1.5);

  gluon_2tev_reco->Draw("p");
  gluon_5tev_reco->Draw("p same");
  gluon_7tev_reco->Draw("p same");
  gluon_2tev_gen->Draw("h same");
  gluon_5tev_gen->Draw("h same");
  gluon_7tev_gen->Draw("h same");

  TLegend * gleg = new TLegend(0.25,0.17,0.55,0.47);
  gleg->SetBorderSize(0);
  gleg->AddEntry((TObject*)0,"CMS Preliminary","");
  gleg->AddEntry(gluon_2tev_reco,"2.76 TeV reco PYTHIA","p");
  gleg->AddEntry(gluon_2tev_gen,"2.76 TeV gen PYTHIA","l");
  gleg->AddEntry(gluon_7tev_reco,"7 TeV reco PYTHIA","p");
  gleg->AddEntry(gluon_7tev_gen,"7 TeV gen PYTHIA","l");
  gleg->AddEntry(gluon_5tev_reco,"5.02 TeV reco PYTHIA+HIJING","p");
  gleg->AddEntry(gluon_5tev_gen,"5.02 TeV gen PYTHIA+HIJING","l");

  gleg->Draw("same");
  cg1->SaveAs(Form("plots/GluonFractionsMC_%s.png",tag)); 
  cg1->SaveAs(Form("plots/GluonFractionsMC_%s.pdf",tag));
}
