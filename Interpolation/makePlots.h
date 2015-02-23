#include "TAttMarker.h"
#include "TAttLine.h"
#include "TLine.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TPad.h"
#include "TColor.h"
#include "TAttText.h"
#include "TAttAxis.h"
#include "TLatex.h"

// jet pt boundaries

const int FF_Bins = 5;
double FF_Bound[FF_Bins+1] = {60,80,100,120,140,200};

TH1D * pp2TeV_data[FF_Bins];
TH1D * pp7TeV_data[FF_Bins];
TH1D * pPb5TeV_data[FF_Bins];
TH1D * Pbp5TeV_data[FF_Bins];
TH1D * pp5TeV_interp[FF_Bins];
TH1D * pp5TeV_interp_swap[FF_Bins];
TH1D * pPb_FF[FF_Bins];
TH1D * Pbp_FF[FF_Bins];

void makePlots()
{
  TCanvas * c1 = new TCanvas("c1","c1",1200,600);
  c1->SetLeftMargin(0.2);
  c1->Divide(5,2,0,0);
  
  TLine * l = new TLine(0.5,1, pPb5TeV_data[1]->GetBinLowEdge(34),1);
  l->SetLineWidth(1);
  l->SetLineStyle(2);
  l->SetLineColor(1);

  TLatex * tlat = new TLatex(0.1,0.1,"test");
  tlat->SetTextSize(0.06);

  for(int i=1; i<11; i++)
  {
    c1->cd(i);
    c1->cd(i)->SetLogx();

    if(i<6)
    {
      c1->cd(i)->SetLogy();

      if(i!=1)
      {
        pPb5TeV_data[i-1]->GetYaxis()->SetTitle("");
        pPb5TeV_data[i-1]->GetYaxis()->SetLabelSize(0);      
      }

      pPb5TeV_data[i-1]->GetXaxis()->SetRange(1,33);
      pPb5TeV_data[i-1]->GetYaxis()->SetTitleSize(0.06);
      

      pPb5TeV_data[i-1]->SetMarkerSize(0.8);
      pPb5TeV_data[i-1]->SetLineWidth(1);
      pPb5TeV_data[i-1]->SetMarkerStyle(21);
      pPb5TeV_data[i-1]->SetMarkerColor(kRed+1);
      pPb5TeV_data[i-1]->SetLineColor(kRed+1);
      pPb5TeV_data[i-1]->SetMaximum(10);
      pPb5TeV_data[i-1]->SetMinimum(0.00001);

      pp5TeV_interp[i-1]->SetMarkerSize(0.8);
      pp5TeV_interp[i-1]->SetLineWidth(1);

      pPb5TeV_data[i-1]->Draw();
      pp5TeV_interp[i-1]->Draw("same"); 

      tlat->DrawLatex(0.6,0.00002,Form("%d GeV/c < p_{T}^{jet} < %d GeV/c",(int)FF_Bound[i-1],(int)FF_Bound[i]));
    }
    else
    {
      if(i!=6)
      {
        pPb_FF[i-6]->GetYaxis()->SetTitle("");
        pPb_FF[i-6]->GetYaxis()->SetLabelSize(0);
      }

      pPb_FF[i-6]->GetXaxis()->SetRange(1,33);
      pPb_FF[i-6]->GetXaxis()->SetTitleSize(0.06);
      pPb_FF[i-6]->GetXaxis()->SetTitle("p_{T}^{track} (GeV/c)");
      if(i==6) pPb_FF[i-6]->GetYaxis()->SetTitle("D_{pPb}/D_{pp}^{interp}"); 
      pPb_FF[i-6]->GetXaxis()->SetTitleOffset(1.2);
      pPb_FF[i-6]->GetYaxis()->SetTitleSize(0.06);

      pPb_FF[i-6]->SetMaximum(2);
      pPb_FF[i-6]->SetMinimum(0);
      pPb_FF[i-6]->SetMarkerSize(1);
      pPb_FF[i-6]->SetLineWidth(1);

      pPb_FF[i-6]->Draw();
      l->Draw("same");
    }
  }
  c1->cd(1);
  TLegend * leg = new TLegend(0.3,0.2,0.9,0.3);
  leg->AddEntry(pPb5TeV_data[1],"pPb 5TeV data");
  leg->AddEntry(pp5TeV_interp[1],"pp 5TeV interpolation");
  leg->Draw();

  c1->SaveAs("plots/pPb_FFs.png");
  c1->SaveAs("plots/pPb_FFs.pdf");

//Pbp
  
  TCanvas * c2 = new TCanvas("c2","c2",1200,600);
  c2->SetLeftMargin(0.2);
  c2->Divide(5,2,0,0);
  
  TLine * l2 = new TLine(0.5,1, Pbp5TeV_data[1]->GetBinLowEdge(34),1);
  l2->SetLineWidth(1);
  l2->SetLineStyle(2);
  l2->SetLineColor(1);

  for(int i=1; i<11; i++)
  {
    c2->cd(i);
    c2->cd(i)->SetLogx();

    if(i<6)
    {
      c2->cd(i)->SetLogy();

      if(i!=1)
      {
        Pbp5TeV_data[i-1]->GetYaxis()->SetTitle("");
        Pbp5TeV_data[i-1]->GetYaxis()->SetLabelSize(0);      
      }

      Pbp5TeV_data[i-1]->GetXaxis()->SetRange(1,33);
      Pbp5TeV_data[i-1]->GetYaxis()->SetTitleSize(0.06);
      

      Pbp5TeV_data[i-1]->SetMarkerSize(0.8);
      Pbp5TeV_data[i-1]->SetLineWidth(1);
      Pbp5TeV_data[i-1]->SetMarkerStyle(21);
      Pbp5TeV_data[i-1]->SetMarkerColor(kRed+1);
      Pbp5TeV_data[i-1]->SetLineColor(kRed+1);
      Pbp5TeV_data[i-1]->SetMaximum(10);
      Pbp5TeV_data[i-1]->SetMinimum(0.00001);

      pp5TeV_interp_swap[i-1]->SetMarkerSize(0.8);
      pp5TeV_interp_swap[i-1]->SetLineWidth(1);

      Pbp5TeV_data[i-1]->Draw();
      pp5TeV_interp_swap[i-1]->Draw("same"); 

      tlat->DrawLatex(0.6,0.00002,Form("%d GeV/c < p_{T}^{jet} < %d GeV/c",(int)FF_Bound[i-1],(int)FF_Bound[i]));
    }
    else
    {
      if(i!=6)
      {
        Pbp_FF[i-6]->GetYaxis()->SetTitle("");
        Pbp_FF[i-6]->GetYaxis()->SetLabelSize(0);
      }

      Pbp_FF[i-6]->GetXaxis()->SetRange(1,33);
      Pbp_FF[i-6]->GetXaxis()->SetTitleSize(0.06);
      Pbp_FF[i-6]->GetXaxis()->SetTitle("p_{T}^{track} (GeV/c)");
      if(i==6) Pbp_FF[i-6]->GetYaxis()->SetTitle("D_{pPb}/D_{pp}^{interp_swap}"); 
      Pbp_FF[i-6]->GetXaxis()->SetTitleOffset(1.2);
      Pbp_FF[i-6]->GetYaxis()->SetTitleSize(0.06);

      Pbp_FF[i-6]->SetMaximum(2);
      Pbp_FF[i-6]->SetMinimum(0);
      Pbp_FF[i-6]->SetMarkerSize(1);
      Pbp_FF[i-6]->SetLineWidth(1);

      Pbp_FF[i-6]->Draw();
      l2->Draw("same");
    }
  }
  c2->cd(1);
  TLegend * leg2 = new TLegend(0.3,0.2,0.9,0.3);
  leg2->AddEntry(Pbp5TeV_data[1],"Pbp 5TeV data");
  leg2->AddEntry(pp5TeV_interp_swap[1],"pp 5TeV interpolation");
  leg2->Draw();

  c2->SaveAs("plots/Pbp_FFs.png");
  c2->SaveAs("plots/Pbp_FFs.pdf");
  
}
 
