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
  
  TLine * l = new TLine(0.5,1, pPb5TeV_data[1]->GetBinLowEdge(40),1);
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

      pPb5TeV_data[i-1]->GetXaxis()->SetRange(1,39);
      pPb5TeV_data[i-1]->GetYaxis()->SetTitleSize(0.06);
      

      pPb5TeV_data[i-1]->SetMarkerSize(0.8);
      pPb5TeV_data[i-1]->SetLineWidth(1);
      pPb5TeV_data[i-1]->SetMarkerStyle(21);
      pPb5TeV_data[i-1]->SetMarkerColor(kRed+1);
      pPb5TeV_data[i-1]->SetLineColor(kRed+1);
      pPb5TeV_data[i-1]->SetMaximum(10);
      pPb5TeV_data[i-1]->SetMinimum(0.00001);

      pPb5TeV_data_interp[i-1][0]->SetMarkerSize(0.8);
      pPb5TeV_data_interp[i-1][0]->SetLineWidth(1);

      pPb5TeV_data[i-1]->Draw();
      pPb5TeV_data_interp[i-1][0]->Draw("same"); 

      tlat->DrawLatex(0.6,0.00002,Form("%d GeV/c < p_{T}^{jet} < %d GeV/c",(int)FF_Bound[i-1],(int)FF_Bound[i]));
    }
    else
    {
      if(i!=6)
      {
        pPb_FF[i-6]->GetYaxis()->SetTitle("");
        pPb_FF[i-6]->GetYaxis()->SetLabelSize(0);
      }

      pPb_FF[i-6]->GetXaxis()->SetRange(1,39);
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
  leg->AddEntry(pPb5TeV_data_interp[1][0],"pp 5TeV interpolation");
  leg->Draw();

  c1->SaveAs("plots//pPb_FFs_UE3.png");
  c1->SaveAs("plots//pPb_FFs_UE3.pdf");

//Pbp  
  TCanvas * c2 = new TCanvas("c2","c2",1200,600);
  c2->SetLeftMargin(0.2);
  c2->Divide(5,2,0,0);
  
  TLine * l2 = new TLine(0.5,1, Pbp5TeV_data[1]->GetBinLowEdge(40),1);
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

      Pbp5TeV_data[i-1]->GetXaxis()->SetRange(1,39);
      Pbp5TeV_data[i-1]->GetYaxis()->SetTitleSize(0.06);     

      Pbp5TeV_data[i-1]->SetMarkerSize(0.8);
      Pbp5TeV_data[i-1]->SetLineWidth(1);
      Pbp5TeV_data[i-1]->SetMarkerStyle(21);
      Pbp5TeV_data[i-1]->SetMarkerColor(kRed+1);
      Pbp5TeV_data[i-1]->SetLineColor(kRed+1);
      Pbp5TeV_data[i-1]->SetMaximum(10);
      Pbp5TeV_data[i-1]->SetMinimum(0.00001);

      Pbp5TeV_data_interp[i-1][0]->SetMarkerSize(0.8);
      Pbp5TeV_data_interp[i-1][0]->SetLineWidth(1);

      Pbp5TeV_data[i-1]->Draw();
      Pbp5TeV_data_interp[i-1][0]->Draw("same"); 

      tlat->DrawLatex(0.6,0.00002,Form("%d GeV/c < p_{T}^{jet} < %d GeV/c",(int)FF_Bound[i-1],(int)FF_Bound[i]));
    }
    else
    {
      if(i!=6)
      {
        Pbp_FF[i-6]->GetYaxis()->SetTitle("");
        Pbp_FF[i-6]->GetYaxis()->SetLabelSize(0);
      }

      Pbp_FF[i-6]->GetXaxis()->SetRange(1,39);
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
  leg2->AddEntry(Pbp5TeV_data_interp[1][0],"pp 5TeV interpolation");
  leg2->Draw();

  c2->SaveAs("plots//Pbp_FFs_UE3.png");
  c2->SaveAs("plots//Pbp_FFs_UE3.pdf");


  //MC reco  
  TCanvas * c3 = new TCanvas("c3","c3",1200,600);
  c3->SetLeftMargin(0.2);
  c3->Divide(5,2,0,0);
  
  TLine * l3 = new TLine(0.5,1, pPb5TeV_recoMC[1]->GetBinLowEdge(40),1);
  l3->SetLineWidth(1);
  l3->SetLineStyle(2);
  l3->SetLineColor(1);

  for(int i=1; i<11; i++)
  {
    c3->cd(i);
    c3->cd(i)->SetLogx();

    if(i<6)
    {
      c3->cd(i)->SetLogy();

      if(i!=1)
      {
        pPb5TeV_recoMC[i-1]->GetYaxis()->SetTitle("");
        pPb5TeV_recoMC[i-1]->GetYaxis()->SetLabelSize(0);      
      }

      pPb5TeV_recoMC[i-1]->GetXaxis()->SetRange(1,39);
      pPb5TeV_recoMC[i-1]->GetYaxis()->SetTitleSize(0.06);     

      pPb5TeV_recoMC[i-1]->SetMarkerSize(0.8);
      pPb5TeV_recoMC[i-1]->SetLineWidth(1);
      pPb5TeV_recoMC[i-1]->SetMarkerStyle(21);
      pPb5TeV_recoMC[i-1]->SetMarkerColor(kRed+1);
      pPb5TeV_recoMC[i-1]->SetLineColor(kRed+1);
      pPb5TeV_recoMC[i-1]->SetMaximum(10);
      pPb5TeV_recoMC[i-1]->SetMinimum(0.00001);

      pPb5TeV_recoMC_interp[i-1][0]->SetMarkerSize(0.8);
      pPb5TeV_recoMC_interp[i-1][0]->SetLineWidth(1);

      pPb5TeV_recoMC[i-1]->Draw();
      pPb5TeV_recoMC_interp[i-1][0]->Draw("same"); 

      tlat->DrawLatex(0.6,0.00002,Form("%d GeV/c < p_{T}^{jet} < %d GeV/c",(int)FF_Bound[i-1],(int)FF_Bound[i]));
    }
    else
    {
      if(i!=6)
      {
        pPb_FF_recoMC[i-6]->GetYaxis()->SetTitle("");
        pPb_FF_recoMC[i-6]->GetYaxis()->SetLabelSize(0);
      }

      pPb_FF_recoMC[i-6]->GetXaxis()->SetRange(1,39);
      pPb_FF_recoMC[i-6]->GetXaxis()->SetTitleSize(0.06);
      pPb_FF_recoMC[i-6]->GetXaxis()->SetTitle("p_{T}^{track} (GeV/c)");
      if(i==6) pPb_FF_recoMC[i-6]->GetYaxis()->SetTitle("D_{pPb}/D_{pp}"); 
      pPb_FF_recoMC[i-6]->GetXaxis()->SetTitleOffset(1.2);
      pPb_FF_recoMC[i-6]->GetYaxis()->SetTitleSize(0.06);

      pPb_FF_recoMC[i-6]->SetMaximum(2);
      pPb_FF_recoMC[i-6]->SetMinimum(0);
      pPb_FF_recoMC[i-6]->SetMarkerSize(1);
      pPb_FF_recoMC[i-6]->SetLineWidth(1);

      pPb_FF_recoMC[i-6]->Draw();
      l3->Draw("same");
    }
  }
  c3->cd(1);
  TLegend * leg3 = new TLegend(0.3,0.2,0.9,0.3);
  leg3->AddEntry(pPb5TeV_recoMC[1],"5TeV PYTHIA+HIJING Reco");
  leg3->AddEntry(pPb5TeV_recoMC_interp[1][0],"PYTHIA Reco Interpolation");
  leg3->Draw();

  c3->SaveAs("plots//pPb_FF_recoMC_UE3.png");
  c3->SaveAs("plots//pPb_FF_recoMC_UE3.pdf");

   
  //MC gen 
  TCanvas * c4 = new TCanvas("c4","c4",1200,600);
  c4->SetLeftMargin(0.2);
  c4->Divide(5,2,0,0);
  
  TLine * l4 = new TLine(0.5,1, pPb5TeV_genMC[1]->GetBinLowEdge(40),1);
  l4->SetLineWidth(1);
  l4->SetLineStyle(2);
  l4->SetLineColor(1);

  for(int i=1; i<11; i++)
  {
    c4->cd(i);
    c4->cd(i)->SetLogx();

    if(i<6)
    {
      c4->cd(i)->SetLogy();

      if(i!=1)
      {
        pPb5TeV_genMC[i-1]->GetYaxis()->SetTitle("");
        pPb5TeV_genMC[i-1]->GetYaxis()->SetLabelSize(0);      
      }

      pPb5TeV_genMC[i-1]->GetXaxis()->SetRange(1,39);
      pPb5TeV_genMC[i-1]->GetYaxis()->SetTitleSize(0.06);     

      pPb5TeV_genMC[i-1]->SetMarkerSize(0.8);
      pPb5TeV_genMC[i-1]->SetLineWidth(1);
      pPb5TeV_genMC[i-1]->SetMarkerStyle(21);
      pPb5TeV_genMC[i-1]->SetMarkerColor(kRed+1);
      pPb5TeV_genMC[i-1]->SetLineColor(kRed+1);
      pPb5TeV_genMC[i-1]->SetMaximum(10);
      pPb5TeV_genMC[i-1]->SetMinimum(0.00001);

      pPb5TeV_genMC_interp[i-1][0]->SetMarkerSize(0.8);
      pPb5TeV_genMC_interp[i-1][0]->SetLineWidth(1);

      pPb5TeV_genMC[i-1]->Draw();
      pPb5TeV_genMC_interp[i-1][0]->Draw("same"); 

      tlat->DrawLatex(0.6,0.00002,Form("%d GeV/c < p_{T}^{jet} < %d GeV/c",(int)FF_Bound[i-1],(int)FF_Bound[i]));
    }
    else
    {
      if(i!=6)
      {
        pPb_FF_genMC[i-6]->GetYaxis()->SetTitle("");
        pPb_FF_genMC[i-6]->GetYaxis()->SetLabelSize(0);
      }

      pPb_FF_genMC[i-6]->GetXaxis()->SetRange(1,39);
      pPb_FF_genMC[i-6]->GetXaxis()->SetTitleSize(0.06);
      pPb_FF_genMC[i-6]->GetXaxis()->SetTitle("p_{T}^{track} (GeV/c)");
      if(i==6) pPb_FF_genMC[i-6]->GetYaxis()->SetTitle("D_{pPb}/D_{pp}"); 
      pPb_FF_genMC[i-6]->GetXaxis()->SetTitleOffset(1.2);
      pPb_FF_genMC[i-6]->GetYaxis()->SetTitleSize(0.06);

      pPb_FF_genMC[i-6]->SetMaximum(2);
      pPb_FF_genMC[i-6]->SetMinimum(0);
      pPb_FF_genMC[i-6]->SetMarkerSize(1);
      pPb_FF_genMC[i-6]->SetLineWidth(1);

      pPb_FF_genMC[i-6]->Draw();
      l4->Draw("same");
    }
  }
  c4->cd(1);
  TLegend * leg4 = new TLegend(0.3,0.2,0.9,0.3);
  leg4->AddEntry(pPb5TeV_genMC[1],"5TeV PYTHIA+HIJING Gen");
  leg4->AddEntry(pPb5TeV_genMC_interp[1][0],"PYTHIA Gen Interpolation");
  leg4->Draw();

  c4->SaveAs("plots//pPb_FF_genMC_UE3.png");
  c4->SaveAs("plots//pPb_FF_genMC_UE3.pdf"); 

//combined total plot

  TCanvas * c5 = new TCanvas("c5","c5",1200,600);
  c5->SetLeftMargin(0.2);
  c5->Divide(5,2,0,0);
  
  TLine * l5 = new TLine(0.5,1, pPb5Pbp5TeV_fulldata[1]->GetBinLowEdge(40),1);
  l5->SetLineWidth(1);
  l5->SetLineStyle(2);
  l5->SetLineColor(1);

  for(int i=1; i<11; i++)
  {
    c5->cd(i);
    c5->cd(i)->SetLogx();

    if(i<6)
    {
      c5->cd(i)->SetLogy();

      if(i!=1)
      {
        pPb5Pbp5TeV_fulldata[i-1]->GetYaxis()->SetTitle("");
        pPb5Pbp5TeV_fulldata[i-1]->GetYaxis()->SetLabelSize(0);      
      }

      pPb5Pbp5TeV_fulldata[i-1]->GetXaxis()->SetRange(1,39);
      pPb5Pbp5TeV_fulldata[i-1]->GetYaxis()->SetTitleSize(0.06);     

      pPb5Pbp5TeV_fulldata[i-1]->SetMarkerSize(0.8);
      pPb5Pbp5TeV_fulldata[i-1]->SetLineWidth(1);
      pPb5Pbp5TeV_fulldata[i-1]->SetMarkerStyle(21);
      pPb5Pbp5TeV_fulldata[i-1]->SetMarkerColor(kRed+1);
      pPb5Pbp5TeV_fulldata[i-1]->SetLineColor(kRed+1);
      pPb5Pbp5TeV_fulldata[i-1]->SetMaximum(10);
      pPb5Pbp5TeV_fulldata[i-1]->SetMinimum(0.00001);

      pPb5Pb5TeV_data_interp[i-1][0]->SetMarkerSize(0.8);
      pPb5Pb5TeV_data_interp[i-1][0]->SetLineWidth(1);

      pPb5Pbp5TeV_fulldata[i-1]->Draw();
      pPb5Pb5TeV_data_interp[i-1][0]->Draw("same"); 

      tlat->DrawLatex(0.6,0.00002,Form("%d GeV/c < p_{T}^{jet} < %d GeV/c",(int)FF_Bound[i-1],(int)FF_Bound[i]));
    }
    else
    {
      if(i!=6)
      {
        pPbPbp_FF[i-6]->GetYaxis()->SetTitle("");
        pPbPbp_FF[i-6]->GetYaxis()->SetLabelSize(0);
      }

      pPbPbp_FF[i-6]->GetXaxis()->SetRange(1,39);
      pPbPbp_FF[i-6]->GetXaxis()->SetTitleSize(0.06);
      pPbPbp_FF[i-6]->GetXaxis()->SetTitle("p_{T}^{track} (GeV/c)");
      if(i==6) pPbPbp_FF[i-6]->GetYaxis()->SetTitle("D_{pPb}/D_{pp}^{interp}"); 
      pPbPbp_FF[i-6]->GetXaxis()->SetTitleOffset(1.2);
      pPbPbp_FF[i-6]->GetYaxis()->SetTitleSize(0.06);

      pPbPbp_FF[i-6]->SetMaximum(2);
      pPbPbp_FF[i-6]->SetMinimum(0);
      pPbPbp_FF[i-6]->SetMarkerSize(1);
      pPbPbp_FF[i-6]->SetLineWidth(1);

      pPbPbp_FF[i-6]->Draw();
      l5->Draw("same");
    }
  }
  c5->cd(1);
  TLegend * leg5 = new TLegend(0.3,0.2,0.9,0.3);
  leg5->AddEntry(pPb5Pbp5TeV_fulldata[1],"pPb+Pbp 5.02TeV data");
  leg5->AddEntry(pPb5Pb5TeV_data_interp[1][0],"pp 5.02TeV interpolation");
  leg5->Draw();

  c5->SaveAs("plots//pPbPbp_FFs_UE3.png");
  c5->SaveAs("plots//pPbPbp_FFs_UE3.pdf");
}
 
