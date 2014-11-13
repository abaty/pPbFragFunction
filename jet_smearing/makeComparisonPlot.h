#include "TCanvas.h"
#include "TAxis.h"
#include "TH1D.h"
#include "TAttMarker.h"
#include "TAttLine.h"
#include "TAttAxis.h"
#include "TLegend.h"
#include "TAttText.h"
#include "TLine.h"

void makeComparisonPlot(TH1D* h1in, TH1D* h2in)
{
  TH1D *h1 = (TH1D*)h1in->Clone("h1");
  TH1D *h2 = (TH1D*)h2in->Clone("h2");

  TCanvas * c10 = new TCanvas("c10","c10",1200,800);
  c10->SetLogy();
//plotting spectra  
  TLegend *l = new TLegend(0.6,0.6,0.8,0.8);
  l->AddEntry((TObject*)0, "CMS Preliminary","");
  l->AddEntry((TObject*)0, "5.02 TeV pPb Data","");
  l->AddEntry(h1, "Unsmeared", "l");
  l->AddEntry(h2, "Smeared by 5%", "l");

  l->SetTextSize(0.03);

  h1->GetYaxis()->SetTickLength(0.005);
  h1->GetXaxis()->SetTitle("jet p_{t}");
  h1->GetYaxis()->SetTitle("N");
  h1->SetMarkerStyle(1);
  h1->SetLineWidth(1);

  h2->SetMarkerColor(1);
  h2->SetMarkerStyle(1);
  //h2->SetMarkerSize();
  h2->SetLineWidth(1);
  h2->SetLineColor(2); 

  h1->GetXaxis()->SetRangeUser(50,320);
  h2->GetXaxis()->SetRangeUser(50,320);
  h1->GetXaxis()->SetLabelSize(0.03);
  h1->GetYaxis()->SetLabelSize(0.03);
  h1->GetXaxis()->SetTitleSize(0.03);
  h1->GetYaxis()->SetTitleSize(0.03);
  h1->GetXaxis()->SetTitleOffset(1);
  h1->GetYaxis()->SetTitleOffset(1);

  
  h1->DrawCopy("hist ");
  h2->DrawCopy("same E1");
  l->Draw("same");

  c10->SaveAs("plots/jet_pt_spectra_comparison.png");
  c10->SaveAs("plots/jet_pt_spectra_comparison.pdf");
  
  //plotting ratios
  
  TLine * line = new TLine(60,1,200,1);
  line->SetLineStyle(2);
  line->SetLineColor(1);
  
  c10->SetLogy(0);
  h2->Divide(h1);
  h2->GetXaxis()->SetRangeUser(60,200);
  h2->GetXaxis()->SetTitle("jet p_{t}");
  h2->GetYaxis()->SetRangeUser(0.8,1.4);
  h2->SetMarkerColor(4);
  h2->SetMarkerStyle(8);
  h2->SetLineColor(4);

  h2->GetYaxis()->SetTitle("N_{smeared}/N_{unsmeared}");
  l->Clear();
  l->AddEntry((TObject*)0, "CMS Preliminary","");
  l->AddEntry((TObject*)0, "5.02 TeV pPb Data","");

  h2->GetYaxis()->SetTickLength(0.005);
  h2->GetXaxis()->SetLabelSize(0.03);
  h2->GetYaxis()->SetLabelSize(0.03);
  h2->GetXaxis()->SetTitleSize(0.03);
  h2->GetYaxis()->SetTitleSize(0.03);
  h2->GetXaxis()->SetTitleOffset(1);
  h2->GetYaxis()->SetTitleOffset(1);

  h2->Draw();
  line->Draw();
  line->DrawLine(80,0.8,80,1.4);
  line->DrawLine(100,0.8,100,1.4);
  line->DrawLine(120,0.8,120,1.4);
  line->DrawLine(140,0.8,140,1.4);
  l->Draw();

  c10->SaveAs("plots/jet_pt_spectra_comparison_ratio.png");
  c10->SaveAs("plots/jet_pt_spectra_comparison_ratio.pdf");
  return;
}
