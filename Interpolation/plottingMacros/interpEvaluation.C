#include "TFile.h"
#include "TH1D.h"
#include "TPad.h"
#include "TCanvas.h"
#include "plottingStyles.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TAttPad.h"
#include "TAttText.h"
#include "TLine.h"
#include "TAttLine.h"

TH1D* pp2Q[5];
TH1D* pPb5Q[5];
TH1D* pp7Q[5];
TH1D* pp2G[5];
TH1D* pPb5G[5];
TH1D* pp7G[5];

TLegend * leg1;
TLegend * leg2;
TLegend * leg3;
TLegend * leg4;


const int bins[6] = {60,80,100,120,140,200};

void interpEvaluation()
{
  TCanvas * c1 = new TCanvas("c1","",1200,600);
  c1->SetLeftMargin(0.2);
  c1->Divide(5,2,0,0);
  c1->cd(1);

  TLine * l = new TLine(0,1,220,1);
  l->SetLineColor(1);
  l->SetLineStyle(2);
  TLatex * tlat = new TLatex(0.1,0.1,"test");
  tlat->SetTextSize(0.06);

  for(int i = 1; i<6; i++) c1->cd(i)->SetLogy();
  for(int i = 1; i<11; i++) c1->cd(i)->SetLogx();

  const char * names[3] = {"data","genMC","recoMC"};
  TFile * inf = TFile::Open("../FragmentationFunctionsUE3.root","read");
  for(int m = 0; m<3;m++)
  {
    for(int i = 0; i<5; i++)
    {
      if(m!=0) pp2Q[i] = (TH1D*)inf->Get(Form("pp2TeV_%s_%d_%d",names[m],(int)bins[i],(int)bins[i+1]));
      else pp2Q[i] = (TH1D*)inf->Get(Form("pp2TeV_full%s_%d_%d",names[m],(int)bins[i],(int)bins[i+1]));
      if(m!=0) pPb5Q[i] = (TH1D*)inf->Get(Form("pPb5Pbp5TeV_%s_interp_%d_%d",names[m],(int)bins[i],(int)bins[i+1]));
      else pPb5Q[i] = (TH1D*)inf->Get(Form("pPb5Pbp5TeV_%s_interp_%d_%d",names[m],(int)bins[i],(int)bins[i+1]));
      if(m!=0) pp7Q[i] = (TH1D*)inf->Get(Form("pp7TeV_%s_%d_%d",names[m],(int)bins[i],(int)bins[i+1]));
      else pp7Q[i] = (TH1D*)inf->Get(Form("pp7TeV_full%s_%d_%d",names[m],(int)bins[i],(int)bins[i+1]));

      setColors(pp2Q[i],0,0);
      setColors(pPb5Q[i],1,0);
      setColors(pp7Q[i],2,0);
      pp2Q[i]->GetXaxis()->SetRangeUser(0.5,200);
      pp2Q[i]->SetMaximum(10);
      pp2Q[i]->SetMinimum(0.0000001);
      if(i!=0)
      {
        pp2Q[i]->GetYaxis()->SetTitleSize(0);
        pp2Q[i]->GetYaxis()->SetLabelSize(0);
      }
      else
      {
        pp2Q[i]->GetYaxis()->SetTitleOffset(1.8);
      }
    }
    
    if(m==0)
    {
      leg1 = new TLegend(0.03,0.2,.97,0.5);
      leg1->AddEntry(pp2Q[0],"2.76 TeV pp","p");
      leg1->AddEntry(pPb5Q[0],"5.02 TeV Interpolation","p");
      leg1->AddEntry(pp7Q[0],"7 TeV pp","p");
      leg1->SetTextSize(0.05);
    }
    if(m==1)
    {
      leg2 = new TLegend(0.03,0.2,0.97,0.5);
      leg2->AddEntry(pp2Q[0],"2.76 TeV PYTHIA Gen","p");
      leg2->AddEntry(pPb5Q[0],"5.02 TeV Interpolation","p");
      leg2->AddEntry(pp7Q[0],"7 TeV PYTHIA Gen","p");
      leg2->SetTextSize(0.05);
    } 
    if(m==2)
    {
      leg3 = new TLegend(0.03,0.2,0.97,0.5);
      leg3->AddEntry(pp2Q[0],"2.76 TeV PYTHIA Reco","p");
      leg3->AddEntry(pPb5Q[0],"5.02 TeV Interpolation","p");
      leg3->AddEntry(pp7Q[0],"7 TeV PYTHIA Reco","p");
      leg3->SetTextSize(0.05);
    }

    for(int i=1; i<6; i++)
    {
      c1->cd(i);
     
      pp2Q[i-1]->DrawCopy();
      pp7Q[i-1]->DrawCopy("same");
      pPb5Q[i-1]->DrawCopy("same");
      tlat->DrawLatex(0.75,0.0000002,Form("%d GeV/c < p_{T}^{jet} < %d GeV/c",(int)bins[i-1],(int)bins[i]));
      if(m==0 && i==5) leg1->Draw();
      if(m==1 && i==5) leg2->Draw();
      if(m==2 && i==5) leg3->Draw();
    }
    for(int i=0; i<5; i++)
    {
      c1->cd(i+6); 
     
      TH1D * ratio1 = (TH1D*)pPb5Q[i]->Clone(Form("%d%d1",m,i));
      ratio1->Divide(pp2Q[i]);
      TH1D * ratio2 = (TH1D*)pPb5Q[i]->Clone(Form("%d%d2",m,i));
      ratio2->Divide(pp7Q[i]);
      ratio1->SetMaximum(2);
      ratio1->SetMinimum(0);
      ratio1->GetXaxis()->SetRangeUser(0.5,200);
      if(i!=0)
      {
        ratio1->GetYaxis()->SetTitleSize(0);
        ratio1->GetYaxis()->SetLabelSize(0);
      }
      setColors(ratio1,0,0);
      setColors(ratio2,2,0);
      if(i==0)
      {
        ratio1->GetYaxis()->SetTitle("FF_{interpolation}/FF_{pp}");
      }
      ratio1->Draw();
      ratio2->Draw("same");
      l->Draw();
    }
    c1->SaveAs(Form("../plots/interpEval_%s.png",names[m]));
    c1->SaveAs(Form("../plots/interpEval_%s.pdf",names[m]));
    //c1->Clear(); 
  }
}
