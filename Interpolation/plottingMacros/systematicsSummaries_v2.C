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

//const int FF_Bins = 5;
//double FF_Bound[FF_Bins+1] = {60,80,100,120,140,200};

const int errorSources = 9;
const char * sources[errorSources] = {"TotUP","TotDOWN","JESTotUP","JESTotDOWN","JERTot","NoChargeCut_MCDiff","pPbPbpDiff","Ratio","ChargeCutDiff"};  
const char * prettySources[errorSources] = 
  {"Total Upwards Error",
   "Total Downwards Error",
   "Upwards JES Error",
   "Downwards JES Error",
   "JER Error",
   "MC Difference Error",
   "pPb vs Pbp Error",
   "UE Subtraction Error",
   "Jet Charge Cut Error"};

void makeSummaries(int UEtype=3, double maxY=240, int a = 0)
{ 
  TLatex * tlat = new TLatex(0.6,0.6,"test"); 

  TFile * inf2 = TFile::Open(Form("../SystematicsUE%d.root",UEtype),"read");
  TH1D * sys[25][9];
for(int v = 0; v<errorSources; v++)
{
  if(v==7 && UEtype==3) continue;
  for(int i = 0; i<25; i++)
  {
    if(v==6 && i<10)
    {
      sys[i][v] = (TH1D*)inf2->Get(Form("pp2_%s%d",sources[0],i%5));
      sys[i][v]->SetDirectory(0);
      sys[i][v]->Reset();
      continue;
    } 
    if(i<5)        sys[i][v] = (TH1D*)inf2->Get(Form("pp2_%s%d",sources[v],i%5));
    else if(i<10)  sys[i][v] = (TH1D*)inf2->Get(Form("pp7_%s%d",sources[v],i%5));
    else if(i<15)  sys[i][v] = (TH1D*)inf2->Get(Form("pPb5_%s%d",sources[v],i%5));
    else if(i<20)  sys[i][v] = (TH1D*)inf2->Get(Form("interp_%s%d",sources[v],i%5));
    else           sys[i][v] = (TH1D*)inf2->Get(Form("FFratio_%s%d",sources[v],i%5));
    sys[i][v]->Scale(100);
    sys[i][v]->SetDirectory(0);
    std::cout << i << " " << v << std::endl; 
  }
  for(int i=0; i<25; i++)
  {    
    for(int j=0; j<sys[i][v]->GetSize(); j++) 
    {
      if(sys[i][v]->GetBinContent(j)<0) sys[i][v]->SetBinContent(j,-sys[i][v]->GetBinContent(j));
      sys[i][v]->SetBinError(j,0);
      if(j==0 || j==sys[i][v]->GetSize()) sys[i][v]->SetBinContent(j,0);
      if(i%5==0 && sys[i][v]->GetBinCenter(j)>70) sys[i][v]->SetBinContent(j,0);
      if(i%5==1 && i>=5 && sys[i][v]->GetBinCenter(j)>90) sys[i][v]->SetBinContent(j,0);
      if(i%5==2 && i>=10 && sys[i][v]->GetBinCenter(j)>110) sys[i][v]->SetBinContent(j,0);
      if(i%5==3 && i>=15 && sys[i][v]->GetBinCenter(j)>130) sys[i][v]->SetBinContent(j,0);
      if(i%5==4 && i>=20 && sys[i][v]->GetBinCenter(j)>170) sys[i][v]->SetBinContent(j,0);
    }
  }
}
inf2->Close();  
double tracking=3.9;
if(a==4) tracking=5.5;
double pdf = 0;
if(a>2) pdf = 0.5;
TLine * trkLine = new TLine(0.55,tracking,190,tracking);
TLine * pdfLine = new TLine(0.55,pdf,190,pdf);
  TCanvas * c[5];
  //for(int a = 0; a<1; a++)
  //{
  c[a] = new TCanvas(Form("sysSummaries%d",a),Form("sysSummaries%d",a),1600,800);
  c[a]->SetLeftMargin(0.23);
  c[a]->Divide(2,1,0,0);
  for(int i = 0; i<2; i++)
  {
  c[a]->cd(i+1)->SetLogx(); 

  for(int v = 0; v<9; v++)
  {
    if((a<2 || a==3) && v==6) continue;
    if(v==7 && UEtype==3) continue;
    if(i==0) sys[5*a+4*i][v]->GetXaxis()->SetRangeUser(0.5,80);
    sys[5*a+4*i][v]->SetMaximum(maxY);
    sys[5*a+4*i][v]->SetMinimum(0);
 
    sys[5*a+4*i][v]->SetLineWidth(2);
    sys[5*a+4*i][v]->SetLineColor(1);
    sys[5*a+4*i][v]->SetMarkerStyle(24);
    sys[5*a+4*i][v]->SetMarkerSize(1);
    sys[5*a+4*i][v]->SetMarkerColor(1);
    if(v==1)
    {
      sys[5*a+4*i][v]->SetMarkerStyle(25);
    }
    if(v==2)
    {
      sys[5*a+4*i][v]->SetLineColor(kRed+1);
      sys[5*a+4*i][v]->SetLineStyle(7);
      sys[5*a+4*i][v]->SetLineWidth(2);
    }
    if(v==3) 
    {
      sys[5*a+4*i][v]->SetLineColor(kRed+1);
      sys[5*a+4*i][v]->SetLineStyle(3);
    }
    if(v==4)
    {
      sys[5*a+4*i][v]->SetLineColor(kCyan+1);
      sys[5*a+4*i][v]->SetLineWidth(1);
    }
    if(v==5)
    {
      sys[5*a+4*i][v]->SetLineColor(kGreen+1);
      sys[5*a+4*i][v]->SetLineStyle(7);
    }
    if(v==6)
    {
      sys[5*a+4*i][v]->SetLineColor(kOrange-3);
      sys[5*a+4*i][v]->SetLineWidth(1);
    }
    if(v==7)
    {
      sys[5*a+4*i][v]->SetLineColor(kMagenta+1);
      sys[5*a+4*i][v]->SetLineWidth(1);
    }
    if(v==8)
    {
      sys[5*a+4*i][v]->SetLineColor(kBlue);
      sys[5*a+4*i][v]->SetLineStyle(7);
    }

    if(i==0)
    {
      sys[5*a+4*i][v]->GetYaxis()->SetTitle("|\% Syst. Error|");
      sys[5*a+4*i][v]->GetYaxis()->SetTitleOffset(1.6);
      sys[5*a+4*i][v]->GetYaxis()->SetTitleSize(0.07);
      sys[5*a+4*i][v]->GetYaxis()->SetLabelOffset(0.003);
      sys[5*a+4*i][v]->GetYaxis()->SetLabelSize(0.03);
      sys[5*a+4*i][v]->GetYaxis()->SetNdivisions(505,true);
      //tlat->SetTextSize(0.07);
      /*if(i==20)
      {
        sys[5*a+4*i][v]->GetYaxis()->SetLabelSize(0.054);
        sys[5*a+4*i][v]->GetYaxis()->SetTitleSize(0.062);
        sys[5*a+4*i][v]->GetYaxis()->SetTitleOffset(1.8);
        
        //tlat->SetTextSize(0.057);
      }*/
    } 
    else 
    {
      sys[5*a+4*i][v]->GetYaxis()->SetTitleSize(0);
      sys[5*a+4*i][v]->GetYaxis()->SetLabelSize(0);
      //tlat->SetTextSize(0.07);
    } 
    /*if(i>4)
    {
      sys[5*a+4*i][v]->GetXaxis()->SetTitle("p_{T}^{track} (GeV/c)");
      sys[5*a+4*i][v]->GetXaxis()->CenterTitle();
      sys[5*a+4*i][v]->GetXaxis()->SetLabelOffset(0.0001);
      sys[5*a+4*i][v]->GetXaxis()->SetLabelSize(0.07);
      sys[5*a+4*i][v]->GetXaxis()->SetTitleOffset(1.0);
      sys[5*a+4*i][v]->GetXaxis()->SetTitleSize(0.07);
      if(i==20)
      {
        sys[5*a+4*i][v]->GetXaxis()->SetLabelSize(0.058);
        sys[5*a+4*i][v]->GetXaxis()->SetTitleSize(0.055);
        sys[5*a+4*i][v]->GetXaxis()->SetTitleOffset(1.24);
        sys[5*a+4*i][v]->GetXaxis()->SetLabelOffset(0.012);
      }
    }*/
    if(v==0 || v==1)
    {
      sys[5*a+4*i][v]->Draw("hist same p");
    }
    else
    {
      sys[5*a+4*i][v]->Draw("hist same C");
    }
    trkLine->SetLineWidth(1);
    pdfLine->SetLineWidth(1);
    trkLine->SetLineColor(kOrange);
    pdfLine->SetLineColor(kGray+1);
    trkLine->Draw("same");
    pdfLine->Draw("same");
    
    //tlat->SetNDC();
   /* double xmin = 0.05;
    if(i%5==0) xmin = 0.3;
    */
    tlat->SetTextSize(0.04);
    if(i==0) tlat->DrawLatex(0.6,0.9*maxY,"60 < p_{T}^{jet} < 80 GeV/c");
    if(i==1) tlat->DrawLatex(0.7,0.9*maxY,"140 < p_{T}^{jet} < 200 GeV/c");

    TLegend * leg = new TLegend(0.1,0.2,0.8,0.9);
    if(a==0) leg->AddEntry((TObject*)0,"2.76 TeV pp FF","");
    if(a==2) leg->AddEntry((TObject*)0,"5.02 TeV pPb FF","");
    if(a==1) leg->AddEntry((TObject*)0,"7 TeV pp FF","");
    if(a==3) leg->AddEntry((TObject*)0,"pp Interpolation","");
    if(a==4) leg->AddEntry((TObject*)0,"FF Ratio","");
    /*
    if(i==1) tlat->DrawLatex(xmin,0.6,"ak3PF jets");
    if(i==1) tlat->DrawLatex(xmin,0.7,"|#eta_{CM}^{jet}|<1.5");
    if(i==1) tlat->DrawLatex(xmin,0.8,"CMS Preliminary");
    if(i==0) tlat->DrawLatex(xmin,0.8,"2.76 TeV pp FF");
    if(i==5) tlat->DrawLatex(xmin,0.8,"7 TeV pp FF");
    if(i==10) tlat->DrawLatex(xmin,0.8,"5.02 TeV pPb FF");
    if(i==15) tlat->DrawLatex(xmin,0.8,"pp Interpolation");
    if(i==20) tlat->DrawLatex(xmin,0.8,"FF ratio");
    if(i==2) tlat->DrawLatex(xmin,0.8,prettySources[v]);*/
  }
  }
    TLegend * leg = new TLegend(0.05,0.4,0.9,0.9);
    if(a==0) leg->AddEntry((TObject*)0,"2.76 TeV pp FF","");
    if(a==2) leg->AddEntry((TObject*)0,"5.02 TeV pPb FF","");
    if(a==1) leg->AddEntry((TObject*)0,"7 TeV pp FF","");
    if(a==3) leg->AddEntry((TObject*)0,"pp Interpolation","");
    if(a==4) leg->AddEntry((TObject*)0,"FF Ratio","");
    leg->AddEntry(sys[5*a][0],"Total Error (Up)","p");
    leg->AddEntry(sys[5*a][1],"Total Error (Down)","p");
    leg->AddEntry(sys[5*a][2],"JES (Up)","l");
    leg->AddEntry(sys[5*a][3],"JES (Down)","l"); 
    leg->AddEntry(sys[5*a][5],"MC Difference","l");
    leg->AddEntry(sys[5*a][8],"Jet Charge Cut","l");
    leg->AddEntry(sys[5*a][4],"JER","l");
    if(a>1 && a!=3) leg->AddEntry(sys[5*a][6],"pPb vs Pbp","l");
    if(UEtype!=3)leg->AddEntry(sys[5*a][7],"UE Subtraction","l");
    leg->AddEntry(trkLine,"Tracking","l");
    leg->AddEntry(pdfLine,"pdf Uncertainty","l");
    //c[a]->cd(1);
    leg->Draw("same");


  const char * outputType[5] = {"pp2","pp7","pPb5","ppInterp","FFRatio"};
  c[a]->SaveAs(Form("../plots/systematicsSummaries_v2_UE%d_%s.png",UEtype,outputType[a]));
  c[a]->SaveAs(Form("../plots/systematicsSummaries_v2_UE%d_%s.pdf",UEtype,outputType[a]));
  //}
}
