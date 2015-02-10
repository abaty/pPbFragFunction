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
}

void gluFrac()
{
  TFile * inf = new TFile("gluonFracs.root","read");
} 
