#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TColor.h"
#include "TAttLine.h"
#include "TAttMarker.h"
#include "TLine.h"
#include "TLatex.h"
#include "TAttAxis.h"

void Pbp_Comparison()
{
  TH1::SetDefaultSumw2();
  
  TFile * infpPb = new TFile("../rootFiles/pPbFF_80triggeredOnly.root","read");
  TFile * infPbp = new TFile("../rootFiles/PbpFF_80triggeredOnly.root","read");

  TH1D * pPbFF = (TH1D*)infpPb->Get("root_histogram_data_5tev_temp_7");
  TH1D * PbpFF = (TH1D*)infPbp->Get("root_histogram_data_5tev_temp_7");

  TCanvas * c2 = new TCanvas("c2","",500,600);
  c2->SetLeftMargin(0.15);
  c2->SetTopMargin(0.15);

  c2->Divide(1,2,0,0);
  c2->cd(1);

  c2->cd(1)->SetLogx();
  c2->cd(1)->SetLogy();
  pPbFF->SetMarkerStyle(20);
  pPbFF->SetMarkerSize(0.8);
  pPbFF->SetMarkerColor(1);
  pPbFF->SetLineColor(1);
  pPbFF->SetLineWidth(2);
  pPbFF->SetLineStyle(1);
  pPbFF->SetMaximum(10);
  pPbFF->SetMinimum(0.001);
  pPbFF->GetYaxis()->SetTitle("#frac{1}{N_{jet}} #frac{N}{p_{t}^{track}}");
  pPbFF->GetYaxis()->SetTitleColor(1);
  pPbFF->GetYaxis()->SetTitleSize(0.07);
  pPbFF->GetYaxis()->SetTitleOffset(0.9);
  pPbFF->GetYaxis()->SetLabelColor(1);
  pPbFF->GetYaxis()->SetLabelSize(0.06);  
  

  PbpFF->GetXaxis()->SetTitle("p_{t}^{track}");
  PbpFF->GetXaxis()->SetTitleColor(1);
  PbpFF->GetXaxis()->SetTitleSize(0.05);
  PbpFF->GetXaxis()->SetLabelColor(1);
  PbpFF->GetXaxis()->SetLabelSize(0.05);
  PbpFF->GetXaxis()->SetTitleOffset(1.2); 

  PbpFF->SetMarkerStyle(25);
  PbpFF->SetMarkerSize(0.8);
  PbpFF->SetMarkerColor(kRed+1);

  PbpFF->SetLineColor(kRed+1);
  PbpFF->SetLineWidth(1);
  PbpFF->SetLineStyle(1);
  PbpFF->SetMaximum(10);
  PbpFF->SetMinimum(0.001);
  PbpFF->GetYaxis()->SetTitleColor(1);
  PbpFF->GetYaxis()->SetTitleSize(0.07);
  PbpFF->GetYaxis()->SetTitleOffset(1);
  PbpFF->GetYaxis()->SetLabelColor(1);
  PbpFF->GetYaxis()->SetLabelSize(0.04);

  pPbFF->DrawCopy("e");
  PbpFF->DrawCopy("same e");

  TLegend * leg = new TLegend(0.2,0.1,0.5,0.5);
  leg->AddEntry((TObject*)0, "140 < p_{t}^{jet} < 200 GeV/c", "");
  leg->AddEntry(pPbFF, "pPb FF", "p");
  leg->AddEntry(PbpFF, "Pbp FF", "p");
  leg->Draw();

  TLine * l = new TLine(0,1,220,1);
  l->SetLineColor(1);

  c2->cd(2);
  c2->cd(2)->SetLogx();
  PbpFF->SetMaximum(1.2);
  PbpFF->SetMinimum(0.8);
  PbpFF->Divide(pPbFF);

  PbpFF->GetYaxis()->SetTitle("Pbp/pPb");

  PbpFF->DrawCopy("e");
  l->Draw("same");

  c2->SaveAs("Pbp_Comparison_80Triggered.png");

}
