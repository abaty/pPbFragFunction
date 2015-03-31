#include "TH1D.h"
#include "TFile.h"
#include "TAttFill.h"
#include "TLegend.h"
#include "TLine.h"
#include "TBox.h"
#include "TColor.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TAttPad.h"
#include "TAttLine.h"
#include "TAttMarker.h" 
#include "TAxis.h"
#include "TAttAxis.h"
#include "TAttText.h"
#include <iostream>

const int FF_Bins = 5;
double FF_Bound[FF_Bins+1] = {60,80,100,120,140,200};

void systematicsSummaries()
{
  const int errorSources = 8
  const char * sources[errorSources] = {"TotUP","TotDOWN","MCDiff","pPbPbpDiff"};  
 
  TLatex * tlat = new TLatex(0.6,0.6,"test"); 

  TFile * inf2 = TFile::Open("../../SystematicsUE3.root"),"read");
  TH1D * sys[25];
  for(int i = 0; i<25; i++)
  {
    if(i<5)        sys[i] = (TH1D*)inf2->Get(Form("pp2_%s%d",sources[v],i%5));
    else if(i<10)  sys[i] = (TH1D*)inf2->Get(Form("pp7_%s%d",sources[v],i%5));
    else if(i<15)  sys[i] = (TH1D*)inf2->Get(Form("pPb5_%s%d",sources[v],i%5));
    else if(i<20)  sys[i] = (TH1D*)inf2->Get(Form("interp_%s%d",sources[v],i%5));
    else           sys[i] = (TH1D*)inf2->Get(Form("FFratio_%s%d",sources[v],i%5));
    sys[i]->SetDirectory(0); 
  }
  inf2->Close();

  TCanvas * c = new TCanvas("sysSummaries","sysSummaries",1200,1200);
  c->SetLeftMargin(0.23);
  c->Divide(5,5,0,0);

  for(int i = 0; i<25; i++)
  {
    c->cd(i+1)->SetLogx();

    sys[i]->SetMaximum(2.3);
    sys[i]->SetMinimum(0);
    
    sys[i]->SetLineWidth(1);
    sys[i]->SetLineColor(1);
    sys[i]->SetMarkerStyle(8);
    sys[i]->SetMarkerSize(0.7);
    sys[i]->SetMarkerColor(1);

    if(i%5==0)
    {
      sys[i]->GetYaxis()->SetTitle("Relative Sys. error (%)");
      sys[i]->GetYaxis()->SetTitleOffset(1.6);
      sys[i]->GetYaxis()->SetTitleSize(0.07);
      sys[i]->GetYaxis()->SetLabelOffset(0.003);
      sys[i]->GetYaxis()->SetLabelSize(0.06);
      sys[i]->GetYaxis()->SetNdivisions(505,true);
      if(i==20)
      {
        sys[i]->GetYaxis()->SetLabelSize(0.054);
        sys[i]->GetYaxis()->SetTitleSize(0.062);
        sys[i]->GetYaxis()->SetTitleOffset(1.8);
      }

      tlat->SetTextSize(0.058);
    } 
    else 
    {
      sys[i]->GetYaxis()->SetTitleSize(0);
      sys[i]->GetYaxis()->SetLabelSize(0);
      tlat->SetTextSize(0.07);
    } 
    if(i>4)
    {
      sys[i]->GetXaxis()->SetTitle("p_{T}^{track} (GeV/c)");
      sys[i]->GetXaxis()->CenterTitle();
      sys[i]->GetXaxis()->SetLabelOffset(0.0001);
      sys[i]->GetXaxis()->SetLabelSize(0.07);
      sys[i]->GetXaxis()->SetTitleOffset(1.0);
      sys[i]->GetXaxis()->SetTitleSize(0.07);
      if(i==20)
      {
        sys[i]->GetXaxis()->SetLabelSize(0.058);
        sys[i]->GetXaxis()->SetTitleSize(0.055);
        sys[i]->GetXaxis()->SetTitleOffset(1.24);
        sys[i]->GetXaxis()->SetLabelOffset(0.012);
      }
    }
    
    sys[i]->Draw();
    if(i<5) tlat->DrawLatex(0.8,0.0000007,Form("%d < p_{T}^{jet} < %d GeV/c",(int)FF_Bound[i],(int)FF_Bound[i+1]));
    if(i==2) tlat->DrawLatex(20,1,"ak3PF jets");
    if(i==3) tlat->DrawLatex(20,1,"|#eta_{CM}^{jet}|<1.5");
    if(i==4) tlat->DrawLatex(8,1,"CMS Preliminary");
  }
  c->SaveAs("../../plots/systematicsSummaries.png");
  c->SaveAs("../../plots/systematicsSummaries.pdf");
}
