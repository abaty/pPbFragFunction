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
  
  const int bins[6] = {60,80,100,120,140,200};

  TFile * infpPb = new TFile("../FragmentationFunctions.root","read"); 

  TH1D * pPbFF[5];
  TH1D * PbpFF[5];
  for(int i = 0; i<5; i++)
  {
    pPbFF[i] = (TH1D*)infpPb->Get(Form("pPb5TeV_data_%d_%d",bins[i],bins[i+1]));
    PbpFF[i] = (TH1D*)infpPb->Get(Form("Pbp5TeV_data_%d_%d",bins[i],bins[i+1]));
  }  

  TCanvas * c2 = new TCanvas("c2","",1500,600);
  c2->SetLeftMargin(0.15);
  c2->SetTopMargin(0.15);

  c2->Divide(5,2,0,0);
  for(int i = 0; i<5; i++)
  {
  c2->cd(i+1);

  c2->cd(i+1)->SetLogx();
  c2->cd(i+1)->SetLogy();
  pPbFF[i]->SetMarkerStyle(20);
  pPbFF[i]->SetMarkerSize(0.8);
  pPbFF[i]->SetMarkerColor(1);
  pPbFF[i]->SetLineColor(1);
  pPbFF[i]->SetLineWidth(2);
  pPbFF[i]->SetLineStyle(1);
  pPbFF[i]->SetMaximum(10);
  pPbFF[i]->SetMinimum(0.001);
  pPbFF[i]->GetYaxis()->SetTitle("#frac{1}{N_{jet}} #frac{N}{p_{t}^{track}}");
  pPbFF[i]->GetYaxis()->SetTitleColor(1);
  pPbFF[i]->GetYaxis()->SetTitleSize(0.07);
  if(i!=0) pPbFF[i]->GetYaxis()->SetTitleSize(0);
  pPbFF[i]->GetYaxis()->SetTitleOffset(0.9);
  pPbFF[i]->GetYaxis()->SetLabelColor(1);
  pPbFF[i]->GetYaxis()->SetLabelSize(0.06);  
  if(i!=0) pPbFF[i]->GetYaxis()->SetLabelSize(0);

  PbpFF[i]->GetXaxis()->SetTitle("p_{t}^{track}");
  PbpFF[i]->GetXaxis()->SetTitleColor(1);
  PbpFF[i]->GetXaxis()->SetTitleSize(0.05);
  PbpFF[i]->GetXaxis()->SetLabelColor(1);
  PbpFF[i]->GetXaxis()->SetLabelSize(0.05);
  PbpFF[i]->GetXaxis()->SetTitleOffset(1.2); 

  PbpFF[i]->SetMarkerStyle(25);
  PbpFF[i]->SetMarkerSize(0.8);
  PbpFF[i]->SetMarkerColor(kRed+1);

  PbpFF[i]->SetLineColor(kRed+1);
  PbpFF[i]->SetLineWidth(1);
  PbpFF[i]->SetLineStyle(1);
  PbpFF[i]->SetMaximum(10);
  PbpFF[i]->SetMinimum(0.001);
  PbpFF[i]->GetYaxis()->SetTitleColor(1);
  PbpFF[i]->GetYaxis()->SetTitleSize(0.07);
  if(i!=0)  PbpFF[i]->GetYaxis()->SetTitleSize(0);
  PbpFF[i]->GetYaxis()->SetTitleOffset(1);
  PbpFF[i]->GetYaxis()->SetLabelColor(1);
  PbpFF[i]->GetYaxis()->SetLabelSize(0.04);
  if(i!=0) PbpFF[i]->GetYaxis()->SetLabelSize(0);

  pPbFF[i]->DrawCopy("e");
  PbpFF[i]->DrawCopy("same e");
  }
  c2->cd(1);
  TLegend * leg = new TLegend(0.2,0.1,0.5,0.5);
 // leg->AddEntry((TObject*)0, "140 < p_{t}^{jet} < 200 GeV/c", "");
  leg->AddEntry(pPbFF[0], "pPb FF", "p");
  leg->AddEntry(PbpFF[0], "Pbp FF", "p");
  leg->Draw();

  TLine * l = new TLine(0,1,220,1);
  l->SetLineColor(1);

  for(int i = 0 ; i<5; i++)
  {
  c2->cd(i+6);
  c2->cd(i+6)->SetLogx();
  PbpFF[i]->SetMaximum(1.5);
  PbpFF[i]->SetMinimum(0.5);
  PbpFF[i]->Divide(pPbFF[i]);

  PbpFF[i]->GetYaxis()->SetTitle("Pbp/pPb");

  PbpFF[i]->DrawCopy("e");
  l->Draw("same");
  }
  c2->SaveAs("Pbp_Comparison.png");
}
