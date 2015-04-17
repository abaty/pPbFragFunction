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

TBox* makeBox(double x1, double y1, double x2, double y2)
{
  TBox * box = new TBox(x1,y1,x2,y2);
  box->SetLineColor(1);
  box->SetLineWidth(1);
  box->SetLineStyle(1);
  box->SetFillStyle(1001);
  box->SetFillColor(kOrange);
  return box;
}

void interpRatio(int UEtype, int turnOffPoints = 0)
{  
  TLatex * tlat = new TLatex(0.6,0.6,"test");

  TFile * inf1 = TFile::Open(Form("../../FragmentationFunctionsUE%d.root",UEtype),"read");
  TH1D * hist[15];
  for(int i = 0; i<15; i++)
  {
    if(i<5)       hist[i] = (TH1D*)inf1->Get(Form("pPb5Pbp5TeV_fulldata_%d_%d",(int)FF_Bound[i%5],(int)FF_Bound[i%5+1]));
    else if(i<10) hist[i] = (TH1D*)inf1->Get(Form("pPb5Pbp5TeV_data_interp_%d_%d",(int)FF_Bound[i%5],(int)FF_Bound[i%5+1]));
    else          hist[i] = (TH1D*)inf1->Get(Form("pPbPbp_FF_%d_%d",(int)FF_Bound[i%5],(int)FF_Bound[i%5+1]));
    hist[i]->SetDirectory(0);
  }
  inf1->Close();

  TFile * inf2 = TFile::Open(Form("../../SystematicsUE%d.root",UEtype),"read");
  TH1D * sysU[15];
  TH1D * sysD[15];
  for(int i = 0; i<15; i++)
  {
    if(i<5)
    {     
      sysU[i] = (TH1D*)inf2->Get(Form("pPb5_TotUP%d",i%5));
      sysD[i] = (TH1D*)inf2->Get(Form("pPb5_TotDOWN%d",i%5));
    }   
    else if(i<10) 
    {
      sysU[i] = (TH1D*)inf2->Get(Form("interp_TotUP%d",i%5));
      sysD[i] = (TH1D*)inf2->Get(Form("interp_TotDOWN%d",i%5));
    }    
    else 
    { 
      sysU[i] = (TH1D*)inf2->Get(Form("FFratio_TotUP%d",i%5));
      sysD[i] = (TH1D*)inf2->Get(Form("FFratio_TotDOWN%d",i%5));
    }
    sysU[i]->SetDirectory(0);
    sysD[i]->SetDirectory(0);
  }
  inf2->Close();

  TBox* boxArray[15][30];
  for(int i=0; i<15; i++)
  {
    for(int j=1; j<hist[i]->GetSize()-1; j++)
    {
      boxArray[i][j] = makeBox(hist[i]->GetXaxis()->GetBinLowEdge(j),hist[i]->GetBinContent(j)*(1-sysD[i]->GetBinContent(j)),hist[i]->GetXaxis()->GetBinUpEdge(j),hist[i]->GetBinContent(j)*(1+sysU[i]->GetBinContent(j)));
    }
  }

  TCanvas * c = new TCanvas("rawFFs","rawFFs",1200,900);
  c->SetLeftMargin(0.23);
  c->Divide(5,3,0,0);

  for(int i = 0; i<15; i++)
  {
    c->cd(i+1)->SetLogx();
    if(i<10) c->cd(i+1)->SetLogy();

    hist[i]->SetMaximum(4);
    hist[i]->SetMinimum(0.0000015);
    
    if(i>9)
    {
      hist[i]->SetMaximum(2.4);
      hist[i]->SetMinimum(0.1);
    }

    hist[i]->SetLineWidth(1);
    hist[i]->SetLineColor(1);
    if(i<5)
    { 
      hist[i]->SetMarkerStyle(8);
      hist[i]->SetMarkerSize(0.7);
    }
    else if(i<10)
    {
      hist[i]->SetMarkerStyle(24);
      hist[i]->SetMarkerSize(0.7);
    }
    else
    {
      hist[i]->SetMarkerStyle(8);
      hist[i]->SetMarkerSize(0.7);
    }
    hist[i]->SetMarkerColor(1);

    if(i%5==0)
    {
      hist[i]->GetYaxis()->SetTitle("#frac{1}{N_{jet}} #frac{dN^{trk}}{dp_{T}^{trk}} (GeV^{-1}c)");
      if(i==10)hist[i]->GetYaxis()->SetTitle("FF_{pPb}/FF_{pp}^{interpolation}");
      hist[i]->GetYaxis()->SetTitleOffset(1.6);
      hist[i]->GetYaxis()->SetTitleSize(0.07);
      hist[i]->GetYaxis()->SetLabelOffset(0.003);
      hist[i]->GetYaxis()->SetLabelSize(0.05);

      tlat->SetTextSize(0.058);
    } 
    else 
    {
      hist[i]->GetYaxis()->SetTitleSize(0);
      hist[i]->GetYaxis()->SetLabelSize(0);

      tlat->SetTextSize(0.07);
    } 
    if(i>9)
    {
      hist[i]->GetXaxis()->SetTitle("p_{T}^{track} (GeV/c)");
      hist[i]->GetXaxis()->CenterTitle();
      hist[i]->GetXaxis()->SetLabelOffset(0.0001);
      hist[i]->GetXaxis()->SetLabelSize(0.07);
      hist[i]->GetXaxis()->SetTitleOffset(1.0);
      hist[i]->GetXaxis()->SetTitleSize(0.07);
      if(i==10)
      {
        hist[i]->GetXaxis()->SetLabelSize(0.058);
        hist[i]->GetXaxis()->SetTitleSize(0.058);
        hist[i]->GetXaxis()->SetTitleOffset(1.2);
        hist[i]->GetXaxis()->SetLabelOffset(0.01);
      }
    }

    
    hist[i]->Draw();
    for(int j=1; j<hist[i]->GetSize()-1; j++)
    { 
      if(turnOffPoints && i==13 && j==21)
      {
        hist[i]->SetBinContent(j,0);
        hist[i]->SetBinError(j,0);
        continue;
      } 
      if(turnOffPoints && i==8 && j==21)
      {
        hist[i]->SetBinContent(j,0);
        hist[i]->SetBinError(j,0);
        continue;
      }
      if(boxArray[i][j]->GetY2()!=0) boxArray[i][j]->Draw("l");
    }
    hist[i]->Draw("same");
    if(i<5) tlat->DrawLatex(0.8,0.000008,Form("%d < p_{T}^{jet} < %d GeV/c",(int)FF_Bound[i],(int)FF_Bound[i+1]));
    if(i==5) tlat->DrawLatex(1.05,0.00002,"#int_{pPb}Ldt = 30.9 nb^{-1}");
    if(i==6) tlat->DrawLatex(0.8,0.00002,"#int_{2.76 TeV pp}Ldt = 5.3 pb^{-1}");
    if(i==7) tlat->DrawLatex(1,0.00002,"#int_{7 TeV pp}Ldt = 2.5 fb^{-1}");
    if(i==2) tlat->DrawLatex(20,1,"ak3PF jets");
    if(i==3) tlat->DrawLatex(20,1,"|#eta_{CM}^{jet}|<1.5");
    if(i==4) tlat->DrawLatex(8,1,"CMS Preliminary");

    if(i>9)
    {
      TLine * l = new TLine(0.5,1, hist[i]->GetBinLowEdge(40),1);
      l->SetLineWidth(1);
      l->SetLineStyle(3);
      l->SetLineColor(1);
      l->Draw("same");
    }

    if(i==0)
    {
      TLegend * leg = new TLegend(0.31,0.18,0.5,0.5);
      leg->AddEntry(hist[0],"5.02 TeV pPb","p");
      leg->AddEntry(hist[5],"pp interpolation","p");
      //leg->AddEntry(hist[10],"Fragmentation Function Ratio","p");
      leg->SetTextSize(0.058);
      leg->SetBorderSize(0);
      leg->SetTextFont(tlat->GetTextFont());
      leg->Draw();
    }
  }
  c->SaveAs(Form("../../plots/prettyInterpRatio_UE%d.png",UEtype));
  c->SaveAs(Form("../../plots/prettyInterpRatio_UE%d.pdf",UEtype));
}
