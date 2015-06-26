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

void rawFFs(int UEtype)
{ 
  TLatex * tlat = new TLatex(0.6,0.6,"test");
  tlat->SetTextFont(42);

  TFile * inf1 = TFile::Open(Form("../../FragmentationFunctionsUE%d.root",UEtype),"read");
  TH1D * hist[15];
  for(int i = 0; i<15; i++)
  {
    if(i<5)       hist[i] = (TH1D*)inf1->Get(Form("pp2TeV_NoReweight_%d_%d",(int)FF_Bound[i%5],(int)FF_Bound[i%5+1]));
    else if(i<10) hist[i] = (TH1D*)inf1->Get(Form("pp7TeV_NoReweight_%d_%d",(int)FF_Bound[i%5],(int)FF_Bound[i%5+1]));
    else          hist[i] = (TH1D*)inf1->Get(Form("pPb5Pbp5TeV_fulldata_%d_%d",(int)FF_Bound[i%5],(int)FF_Bound[i%5+1]));
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
      sysU[i] = (TH1D*)inf2->Get(Form("pp2_TotUP%d",i%5));
      sysD[i] = (TH1D*)inf2->Get(Form("pp2_TotDOWN%d",i%5));
    }   
    else if(i<10) 
    {
      sysU[i] = (TH1D*)inf2->Get(Form("pp7_TotUP%d",i%5));
      sysD[i] = (TH1D*)inf2->Get(Form("pp7_TotDOWN%d",i%5));
    }    
    else 
    { 
      sysU[i] = (TH1D*)inf2->Get(Form("pPb5_TotUP%d",i%5));
      sysD[i] = (TH1D*)inf2->Get(Form("pPb5_TotDOWN%d",i%5));
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

  TCanvas * c = new TCanvas("rawFFs","rawFFs",1200,600);
  c->SetLeftMargin(0.23);
  c->Divide(5,2,0,0);

  for(int i = 0; i<10; i++)
  {
    c->cd(i+1)->SetLogx();
    c->cd(i+1)->SetLogy();

    hist[i]->SetMaximum(9);
    hist[i]->SetMinimum(0.00000101);
    
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

    hist[i]->SetMarkerColor(1);

    if(i%5==0)
    {
      hist[i]->GetYaxis()->SetTitle("#frac{1}{N_{jet}} #frac{dN^{trk}}{dp_{T}^{trk}} (GeV^{-1}c)");
      hist[i]->GetYaxis()->SetTitleOffset(1.6);
      hist[i]->GetYaxis()->SetTitleSize(0.07);
      hist[i]->GetYaxis()->SetLabelOffset(0.003);
      hist[i]->GetYaxis()->SetLabelSize(0.06);
      hist[i]->GetYaxis()->SetNdivisions(505,true);
      tlat->SetTextSize(0.068);
      if(i==5)
      {
        hist[i]->GetYaxis()->SetLabelSize(0.054);
        hist[i]->GetYaxis()->SetTitleSize(0.062);
        hist[i]->GetYaxis()->SetTitleOffset(1.8);
        tlat->SetTextSize(0.06);
      }
    } 
    else 
    {
      hist[i]->GetYaxis()->SetTitleSize(0);
      hist[i]->GetYaxis()->SetLabelSize(0);
      tlat->SetTextSize(0.085);
    } 
    if(i>4)
    {
      hist[i]->GetXaxis()->SetTitle("p_{T}^{track} (GeV/c)");
      hist[i]->GetXaxis()->CenterTitle();
      hist[i]->GetXaxis()->SetLabelOffset(0.0001);
      hist[i]->GetXaxis()->SetLabelSize(0.07);
      hist[i]->GetXaxis()->SetTitleOffset(1.0);
      hist[i]->GetXaxis()->SetTitleSize(0.07);
      if(i==5)
      {
        hist[i]->GetXaxis()->SetLabelSize(0.058);
        hist[i]->GetXaxis()->SetTitleSize(0.055);
        hist[i]->GetXaxis()->SetTitleOffset(1.24);
        hist[i]->GetXaxis()->SetLabelOffset(0.012);
      }
    }
    
    hist[i]->Draw();
    for(int j=1; j<hist[i]->GetSize()-1; j++)
    { 
      if(boxArray[i][j]->GetY2()!=0) boxArray[i][j]->Draw("l");
    }
    hist[i]->Draw("same");
    if(i<5) tlat->DrawLatex(0.7,0.000004,Form("%d < p_{T}^{jet} < %d GeV/c",(int)FF_Bound[i],(int)FF_Bound[i+1]));
    if(i==0) tlat->DrawLatex(2,2,"5.3 pb^{-1} (2.76 TeV pp)");
    if(i==1) tlat->DrawLatex(1.2,2,"anti-k_{t} particle flow jets");
    if(i==2) tlat->DrawLatex(20,2,"R=0.3");
    if(i==3) tlat->DrawLatex(20,2,"|#eta_{CM}^{jet}|<1.5");
    if(i==6 && UEtype==3)
    { 
      tlat->DrawLatex(2,2,"No Underlying Event");
      tlat->DrawLatex(12,0.7,"Subtraction");
    }
    //if(i==3 && UEtype==0) tlat->DrawLatex(1,1.5,"With Underlying Event Subtraction");
    if(i==4)
    {
      tlat->SetTextFont(61);
      tlat->SetTextSize(1.0/0.76*tlat->GetTextSize());
      tlat->DrawLatex(36,1.8,"CMS");
      tlat->SetTextFont(52);
      tlat->SetTextSize(0.76*tlat->GetTextSize());
      tlat->DrawLatex(14,0.7,"Preliminary");
      tlat->SetTextFont(42);
    }
    if(i==5) tlat->DrawLatex(4,2,"2.5 fb^{-1} (7 TeV pp)");
    
//    if(i==0) tlat->DrawLatex(0.8,0.000015,"#int_{2.76 TeV pp}Ldt = 5.3 pb^{-1}");

   // tlat->SetTextSize(0.057);
//    if(i==5) tlat->DrawLatex(0.8,0.000002,"#int_{7 TeV pp}Ldt = 2.5 fb^{-1}");
    TLegend * leg;
    TLegend * leg2;
    if(i==0)
    {
      leg = new TLegend(0.28,0.23,0.7,0.5);
      leg->AddEntry(hist[0],"2.76 TeV pp","p");
      /*if(UEtype==3)
      { 
        leg->AddEntry((TObject*)0,"No Underlying","");
        leg->AddEntry((TObject*)0,"Event Subtraction","");
      }*/
      //leg->AddEntry(hist[5],"7 TeV pp","p");
      //leg->AddEntry(hist[10],"5.02 TeV pPb","p");
      leg->SetTextSize(tlat->GetTextSize());
      leg->SetBorderSize(0);
      leg->SetTextFont(tlat->GetTextFont());
      leg->Draw();
    }
    else if(i==5)
    {
      leg2 = new TLegend(0.28,0.4,0.7,0.5);
      //leg2->AddEntry(hist[0],"2.76 TeV pp","p");
      leg2->AddEntry(hist[5],"7 TeV pp","p");
      /*if(UEtype==3)
      { 
        leg2->AddEntry((TObject*)0,"No Underlying","");
        leg2->AddEntry((TObject*)0,"Event Subtraction","");
      }*/
      //leg->AddEntry(hist[10],"5.02 TeV pPb","p");
      leg2->SetTextSize(tlat->GetTextSize());
      leg2->SetBorderSize(0);
      leg2->SetTextFont(tlat->GetTextFont());
      leg2->Draw();
    }
  }
  c->SaveAs(Form("../../plots/prettyRawFFs_UE%d.png",UEtype));
  c->SaveAs(Form("../../plots/prettyRawFFs_UE%d.pdf",UEtype));
  //c->SaveAs(Form("../../plots/prettyRawFFs_UE%d.C",UEtype));
}
