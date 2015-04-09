#include "TPaveStats.h"
#include "TF1.h"
#include "TH1D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TAttMarker.h"
#include "TColor.h"
#include "TAttPad.h"
#include "TAttLine.h"
#include "TAxis.h"
#include "TLegend.h"

void plotGluonFraction(const char * tag,int UEtype)
{
  TF1 *pp5GluonFitGen = new TF1("pp5GluonFitGen","pol2",60,200);
  TF1 *pp5SignalGluonFitGen = new TF1("pp5SignalGluonFitGen","pol2",60,200);

  TCanvas * cg1 = new TCanvas("cg1","",800,600);
  cg1->SetLeftMargin(0.2);

  gluon_2tev_reco->SetLineWidth(2);
  gluon_5tev_reco->SetLineWidth(2);
  gluon_5tevSignal_reco->SetLineWidth(2);
  gluon_7tev_reco->SetLineWidth(2);
  gluon_2tev_reco->SetLineColor(1);
  gluon_5tev_reco->SetLineColor(kRed+1);
  gluon_5tevSignal_reco->SetLineColor(kRed+1);
  gluon_7tev_reco->SetLineColor(kBlue+1);
  gluon_2tev_gen->SetLineWidth(1);
  gluon_5tev_gen->SetLineWidth(1);
  gluon_5tevSignal_gen->SetLineWidth(1);
  gluon_7tev_gen->SetLineWidth(1);

  gluon_5tevSignal_reco->GetXaxis()->SetRangeUser(60,200);
  gluon_7tev_reco->GetXaxis()->SetRangeUser(60,200);
  gluon_5tev_reco->GetXaxis()->SetRangeUser(60,200);
 
  gluon_2tev_reco->SetMarkerColor(1); 
  gluon_5tev_reco->SetMarkerColor(kRed+1);
  gluon_5tevSignal_reco->SetMarkerColor(kRed+1);
  gluon_7tev_reco->SetMarkerColor(kBlue+1);
  gluon_2tev_reco->SetMarkerStyle(20);
  gluon_5tev_reco->SetMarkerStyle(20);
  gluon_5tevSignal_reco->SetMarkerStyle(20);
  gluon_7tev_reco->SetMarkerStyle(20);
 
  gluon_2tev_gen->SetLineColor(1);
  gluon_5tev_gen->SetLineColor(kRed+1);
  gluon_5tevSignal_gen->SetLineColor(kRed+1);
  gluon_7tev_gen->SetLineColor(kBlue+1);

  gluon_2tev_reco->SetMarkerSize(0.8);
  gluon_5tev_reco->SetMarkerSize(0.8);
  gluon_5tevSignal_reco->SetMarkerSize(0.8);
  gluon_7tev_reco->SetMarkerSize(0.8);
  gluon_2tev_gen->SetMarkerSize(0);
  gluon_5tev_gen->SetMarkerSize(0);
  gluon_5tevSignal_gen->SetMarkerSize(0);
  gluon_7tev_gen->SetMarkerSize(0);

  gluon_2tev_reco->SetMaximum(0.75);
  gluon_2tev_reco->SetMinimum(0.3);
  gluon_2tev_reco->GetXaxis()->SetRangeUser(60,200);
  gluon_2tev_reco->GetXaxis()->SetTitle("p_{t}^{jet}");
  gluon_2tev_reco->GetYaxis()->SetTitle("Gluon Fraction");
  gluon_2tev_reco->GetYaxis()->SetTitleOffset(1.5);
  gluon_5tev_reco->GetXaxis()->SetTitle("p_{t}^{jet}");
  gluon_5tev_reco->GetYaxis()->SetTitle("Gluon Fraction");
  gluon_5tev_reco->GetYaxis()->SetTitleOffset(1.5);
  gluon_5tevSignal_reco->GetXaxis()->SetTitle("p_{t}^{jet}");
  gluon_5tevSignal_reco->GetYaxis()->SetTitle("Gluon Fraction");
  gluon_5tevSignal_reco->GetYaxis()->SetTitleOffset(1.5);
  gluon_7tev_reco->GetXaxis()->SetTitle("p_{t}^{jet}");
  gluon_7tev_reco->GetYaxis()->SetTitle("Gluon Fraction");
  gluon_7tev_reco->GetYaxis()->SetTitleOffset(1.5);
  gluon_5tev_gen->GetXaxis()->SetTitle("p_{t}^{jet}");
  gluon_5tev_gen->GetYaxis()->SetTitle("Gluon Fraction");
  gluon_5tev_gen->GetYaxis()->SetTitleOffset(1.5);
  gluon_5tevSignal_gen->GetXaxis()->SetTitle("p_{t}^{jet}");
  gluon_5tevSignal_gen->GetYaxis()->SetTitle("Gluon Fraction");
  gluon_5tevSignal_gen->GetYaxis()->SetTitleOffset(1.5);


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
  cg1->SaveAs(Form("plots/GluonFractionsMC_UE%d_%s.png",UEtype,tag)); 
  cg1->SaveAs(Form("plots/GluonFractionsMC_UE%d_%s.pdf",UEtype,tag));

  
  gluon_2tev_reco->Rebin(4);
  gluon_2tev_gen->Rebin(4);
  gluon_2tev_reco->Scale(0.25);
  gluon_2tev_gen->Scale(0.25);
  gluon_2tev_reco->GetXaxis()->SetRangeUser(60,200);
  gluon_2tev_reco->SetMinimum(0.3);
  gluon_2tev_reco->Draw("p");
  gluon_2tev_gen->Draw("h same ][");
  gleg->Clear();
  gleg->AddEntry((TObject*)0,"CMS Preliminary","");
  gleg->AddEntry(gluon_2tev_reco,"2.76 TeV reco PYTHIA","p");
  gleg->AddEntry(gluon_2tev_gen,"2.76 TeV gen PYTHIA","l");
  gleg->Draw("same");
  cg1->SaveAs(Form("plots/pp2GluonFractionsMC_UE%d_%s.png",UEtype,tag));
  cg1->SaveAs(Form("plots/pp2GluonFractionsMC_UE%d_%s.pdf",UEtype,tag));

  gluon_7tev_reco->Rebin(4);
  gluon_7tev_gen->Rebin(4);
  gluon_7tev_reco->Scale(0.25);
  gluon_7tev_gen->Scale(0.25);
  gluon_7tev_reco->GetXaxis()->SetRangeUser(60,200);
  gluon_7tev_reco->SetMinimum(0.3);
  gluon_7tev_reco->Draw("");
  gluon_7tev_gen->Draw("h same ][");
  gleg->Clear();
  gleg->AddEntry((TObject*)0,"CMS Preliminary","");
  gleg->AddEntry(gluon_7tev_reco,"7 TeV reco PYTHIA","p");
  gleg->AddEntry(gluon_7tev_gen,"7 TeV gen PYTHIA","l");
  gleg->Draw("same");
  cg1->SaveAs(Form("plots/pp7GluonFractionsMC_UE%d_%s.png",UEtype,tag));
  cg1->SaveAs(Form("plots/pp7GluonFractionsMC_UE%d_%s.pdf",UEtype,tag));

  gluon_5tevSignal_reco->Rebin(4);
  gluon_5tevSignal_gen->Rebin(4);
  gluon_5tevSignal_reco->Scale(0.25);
  gluon_5tevSignal_gen->Scale(0.25);
  gluon_5tevSignal_reco->GetXaxis()->SetRangeUser(60,200);
  gluon_5tevSignal_reco->SetMinimum(0.3);
  gluon_5tevSignal_reco->Draw("");
  gluon_5tevSignal_gen->Draw("h same ][");
  gleg->Clear();
  gleg->AddEntry((TObject*)0,"CMS Preliminary","");
  gleg->AddEntry(gluon_5tevSignal_reco,"5.02 TeV reco PYTHIA","p");
  gleg->AddEntry(gluon_5tevSignal_gen,"5.02 TeV gen PYTHIA","l");
  gleg->Draw("same");
  cg1->SaveAs(Form("plots/pp5SignalGluonFractionsMC_UE%d_%s.png",UEtype,tag));
  cg1->SaveAs(Form("plots/pp5SignalGluonFractionsMC_UE%d_%s.pdf",UEtype,tag));

  gluon_5tev_reco->Rebin(4);
  gluon_5tev_gen->Rebin(4);
  gluon_5tev_reco->Scale(0.25);
  gluon_5tev_gen->Scale(0.25);
  gluon_5tev_reco->GetXaxis()->SetRangeUser(60,200);
  gluon_5tev_reco->SetMinimum(0.3);
  gluon_5tev_reco->Draw("");
  gluon_5tev_gen->Draw("h same ][");
  gleg->Clear();
  gleg->AddEntry((TObject*)0,"CMS Preliminary","");
  gleg->AddEntry(gluon_5tev_reco,"5.02 TeV reco PYTHIA+HIJING","p");
  gleg->AddEntry(gluon_5tev_gen,"5.02 TeV gen PYTHIA+HIJING","l");
  gleg->Draw("same");
  cg1->SaveAs(Form("plots/pp5GluonFractionsMC_UE%d_%s.png",UEtype,tag));
  cg1->SaveAs(Form("plots/pp5GluonFractionsMC_UE%d_%s.pdf",UEtype,tag));
 
  gluon_5tevSignal_gen->Fit("pp5SignalGluonFitGen","0");
  gluon_5tev_gen->Fit("pp5GluonFitGen","0");
  gluon_5tev_gen->GetXaxis()->SetRangeUser(60,200);
  gluon_5tev_gen->SetMinimum(0.5);
  gluon_5tev_gen->SetMaximum(0.75);
  cg1->Clear();
  gluon_5tev_gen->SetMarkerSize(0.8);
  gluon_5tevSignal_gen->SetMarkerSize(0.8);
  gluon_5tev_gen->SetMarkerStyle(20);
  gluon_5tevSignal_gen->SetMarkerStyle(20);
  pp5GluonFitGen->SetLineWidth(2);
  pp5GluonFitGen->SetLineColor(kRed+1);
  gluon_5tev_gen->SetMarkerColor(kRed+1);
  gluon_5tev_gen->SetLineWidth(2);
  gluon_5tev_gen->SetStats(1);
  gluon_5tev_gen->Draw("");
  pp5GluonFitGen->Draw("same");
  pp5SignalGluonFitGen->SetLineWidth(2);
  pp5SignalGluonFitGen->SetLineColor(1);
  gluon_5tevSignal_gen->SetMarkerColor(1);
  gluon_5tevSignal_gen->SetLineColor(1);
  gluon_5tevSignal_gen->SetStats(1);
  gluon_5tevSignal_gen->Draw("sames");
  pp5SignalGluonFitGen->Draw("same");
  gPad->Update();
  TPaveStats *st = (TPaveStats*)gluon_5tev_gen->FindObject("stats");
  st->SetX1NDC(0.6);
  st->SetY1NDC(0.55);
  st->SetY2NDC(0.7);
  st->SetX2NDC(0.9);
  TPaveStats *st2 = (TPaveStats*)gluon_5tevSignal_gen->FindObject("stats");
  st2->SetX1NDC(0.6);
  st2->SetY1NDC(0.75);
  st2->SetX2NDC(0.9);
  st2->SetY2NDC(0.9);

  gleg->Clear();
  gleg->AddEntry((TObject*)0,"CMS Preliminary","");
  gleg->AddEntry(gluon_5tevSignal_gen,"5.02 TeV gen PYTHIA","p");
  gleg->AddEntry(gluon_5tev_gen,"5.02 TeV gen PYTHIA+HIJING","p");
  gleg->Draw("same");
  cg1->Update();  
  cg1->SaveAs(Form("plots/pp5vspPb5GluonFractionsMC_UE%d_%s.png",UEtype,tag));
  cg1->SaveAs(Form("plots/pp5vspPb5GluonFractionsMC_UE%d_%s.pdf",UEtype,tag));

  if(strcmp(tag,"")==0)
  {
    TFile * gluout = TFile::Open("gluonFractions5TeV.root","recreate");
    gluon_5tevSignal_gen->SetDirectory(0);
    gluon_5tev_gen->SetDirectory(0);
    gluon_5tevSignal_gen->Write();
    gluon_5tev_gen->Write();
  }
  delete pp5GluonFitGen;
  delete pp5SignalGluonFitGen;
}
