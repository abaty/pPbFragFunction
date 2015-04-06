#include "TFile.h"
#include "TH1D.h"
#include "TPad.h"
#include "TCanvas.h"
#include "plottingStyles.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TAttPad.h"
#include "TAttText.h"

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

void q_g_MC_plots()
{
  TCanvas * c1 = new TCanvas("c1","",1200,600);
  c1->SetLeftMargin(0.2);
  c1->Divide(5,2,0,0);
  c1->cd(1);

  TLatex * tlat = new TLatex(0.1,0.1,"test");
  tlat->SetTextSize(0.06);

  for(int i = 1; i<11; i++) c1->cd(i)->SetLogy();
  for(int i = 1; i<11; i++) c1->cd(i)->SetLogx();

  const char * names[2] = {"genMC","recoMC"};
  TFile * inf = TFile::Open("../FragmentationFunctionsUE3.root","read");
  for(int m = 0; m<2;m++)
  {
    for(int i = 0; i<5; i++)
    {
      pp2Q[i] = (TH1D*)inf->Get(Form("pp2TeV_%s_Q_%d_%d",names[m],(int)bins[i],(int)bins[i+1]));
      pPb5Q[i] = (TH1D*)inf->Get(Form("pPb5Pbp5TeV_%s_Q_%d_%d",names[m],(int)bins[i],(int)bins[i+1]));
      pp7Q[i] = (TH1D*)inf->Get(Form("pp7TeV_%s_Q_%d_%d",names[m],(int)bins[i],(int)bins[i+1]));
      pp2G[i] = (TH1D*)inf->Get(Form("pp2TeV_%s_G_%d_%d",names[m],(int)bins[i],(int)bins[i+1]));
      pPb5G[i] = (TH1D*)inf->Get(Form("pPb5Pbp5TeV_%s_G_%d_%d",names[m],(int)bins[i],(int)bins[i+1]));
      pp7G[i] = (TH1D*)inf->Get(Form("pp7TeV_%s_G_%d_%d",names[m],(int)bins[i],(int)bins[i+1]));
      setColors(pp2Q[i],0,0);
      setColors(pPb5Q[i],1,0);
      setColors(pp7Q[i],2,0);
      setColors(pp2G[i],0,0);
      setColors(pPb5G[i],1,0);
      setColors(pp7G[i],2,0);
      pp2Q[i]->GetXaxis()->SetRangeUser(0.5,200);
      pp2G[i]->GetXaxis()->SetRangeUser(0.5,200);
      pp2Q[i]->SetMaximum(10);
      pp2G[i]->SetMaximum(10);
      pp2Q[i]->SetMinimum(0.0000001);
      pp2G[i]->SetMinimum(0.0000001);
      if(i!=0)
      {
        pp2Q[i]->GetYaxis()->SetTitleSize(0);
        pp2G[i]->GetYaxis()->SetTitleSize(0);
        pp2Q[i]->GetYaxis()->SetLabelSize(0);
        pp2G[i]->GetYaxis()->SetLabelSize(0);
      }
      else
      {
        pp2Q[i]->GetYaxis()->SetTitleOffset(1.8);
        pp2G[i]->GetYaxis()->SetTitleOffset(1.8);
      }
    }
    
    if(m==0)
    {
      leg1 = new TLegend(0.03,0.2,.97,0.5);
      leg1->AddEntry(pp2Q[0],"2.76 TeV PYTHIA Gen","p");
      leg1->AddEntry(pPb5Q[0],"5.02 TeV PYTHIA+HIJING Gen","p");
      leg1->AddEntry(pp7Q[0],"7 TeV PYTHIA Gen","p");
      leg1->SetTextSize(0.05);
    }
    if(m==1)
    {
      leg2 = new TLegend(0.03,0.2,0.97,0.5);
      leg2->AddEntry(pp2Q[0],"2.76 TeV PYTHIA Reco","p");
      leg2->AddEntry(pPb5Q[0],"5.02 TeV PYTHIA+HIJING Reco","p");
      leg2->AddEntry(pp7Q[0],"7 TeV PYTHIA Reco","p");
      leg2->SetTextSize(0.05);
    } 

    for(int i=1; i<6; i++)
    {
      c1->cd(i);
      pp2Q[i-1]->Draw();
      pPb5Q[i-1]->Draw("same");
      pp7Q[i-1]->Draw("same");
      
      tlat->DrawLatex(1,0.000001,"Quarks");
      tlat->DrawLatex(1,0.0000002,Form("%d GeV/c < p_{T}^{jet} < %d GeV/c",(int)bins[i-1],(int)bins[i]));
    
      if(m==0 && i==5) leg1->Draw();
      if(m==1 && i==5) leg2->Draw();
    }
    for(int i=1; i<6; i++)
    {
      c1->cd(i+5);
      pp2G[i-1]->Draw();
      pPb5G[i-1]->Draw("same");
      pp7G[i-1]->Draw("same");
      tlat->DrawLatex(1,0.0000002,"Gluons");
    }
    c1->SaveAs(Form("../plots/MC_Q_G_FFs_%s.png",names[m]));
    c1->SaveAs(Form("../plots/MC_Q_G_FFs_%s.pdf",names[m]));
    //c1->Clear(); 
  }

//ratio plots

  TCanvas * c2 = new TCanvas("c2","",1200,600);
  c2->SetLeftMargin(0.2);
  c2->Divide(5,2,0,0);
  c2->cd(1);

  for(int i = 1; i<11; i++) c2->cd(i)->SetLogx();
  for(int m = 0; m<2;m++)
  {
    for(int i = 0; i<5; i++)
    { 
      pp2Q[i] = (TH1D*)inf->Get(Form("pp2TeV_%s_Q_%d_%d",names[m],(int)bins[i],(int)bins[i+1]));
      pp7Q[i] = (TH1D*)inf->Get(Form("pp7TeV_%s_Q_%d_%d",names[m],(int)bins[i],(int)bins[i+1]));
      pp2G[i] = (TH1D*)inf->Get(Form("pp2TeV_%s_G_%d_%d",names[m],(int)bins[i],(int)bins[i+1]));
      pp7G[i] = (TH1D*)inf->Get(Form("pp7TeV_%s_G_%d_%d",names[m],(int)bins[i],(int)bins[i+1]));

      setColors(pp2Q[i],0,0);
      setColors(pp7Q[i],2,0);
      setColors(pp2G[i],0,0);
      setColors(pp7G[i],2,0);
      pp2Q[i]->GetXaxis()->SetRangeUser(0.5,200);
      pp2G[i]->GetXaxis()->SetRangeUser(0.5,200);
      if(m==0)
      {
        pp2Q[i]->SetMaximum(2);
        pp2G[i]->SetMaximum(2);
        pp2Q[i]->SetMinimum(0);
        pp2G[i]->SetMinimum(0);
      }
      else if(m==1)
      {
        pp2Q[i]->SetMaximum(2);
        pp2G[i]->SetMaximum(2);
        pp2Q[i]->SetMinimum(0);
        pp2G[i]->SetMinimum(0);
      }
      if(i==0)
      {
        pp2Q[0]->GetYaxis()->SetTitle("FF_{pp}/FF_{pPb}");
        pp2G[0]->GetYaxis()->SetTitle("F_{pp}/FF_{pPb}");
      }
    }
    
    if(m==0)
    {
      leg3 = new TLegend(0.04,0.6,.7,0.95);
      leg3->AddEntry(pp2Q[0],"2.76 TeV PYTHIA Gen","p");
      leg3->AddEntry(pp7Q[0],"7 TeV PYTHIA Gen","p");
      leg3->AddEntry((TObject*)0,"Divided by 5.02 TeV","");
      leg3->AddEntry((TObject*)0,"PYTHIA+HIJING Gen","");
      leg3->SetTextSize(0.05);
    }
    if(m==1)
    {
      leg4 = new TLegend(0.04,0.6,0.7,0.95);
      leg4->AddEntry(pp2Q[0],"2.76 TeV PYTHIA Reco","p");
      leg4->AddEntry(pp7Q[0],"7 TeV PYTHIA Reco","p");
      leg4->AddEntry((TObject*)0,"Divided by 5.02 TeV","");
      leg4->AddEntry((TObject*)0,"PYTHIA+HIJING Reco","");
      leg4->SetTextSize(0.05);
    } 

    for(int i=1; i<6; i++)
    {
      c2->cd(i);
      pp2Q[i-1]->Divide(pPb5Q[i-1]);
      pp2Q[i-1]->Draw();
      pp7Q[i-1]->Divide(pPb5Q[i-1]);
      pp7Q[i-1]->Draw("same");
      
      tlat->DrawLatex(1,0.4,"Quarks");
      tlat->DrawLatex(1,0.1,Form("%d GeV/c < p_{T}^{jet} < %d GeV/c",(int)bins[i-1],(int)bins[i]));
    
      if(m==0 && i==5) leg3->Draw();
      if(m==1 && i==5) leg4->Draw();
    }
    for(int i=1; i<6; i++)
    {
      c2->cd(i+5);
      pp2G[i-1]->Divide(pPb5G[i-1]);
      pp2G[i-1]->Draw();
      pp7G[i-1]->Divide(pPb5G[i-1]);
      pp7G[i-1]->Draw("same");
      tlat->DrawLatex(1,0.4,"Gluons");
    }
    c2->SaveAs(Form("../plots/MC_Q_G_FFs_Ratio_%s.png",names[m]));
    c2->SaveAs(Form("../plots/MC_Q_G_FFs_Ratio_%s.pdf",names[m]));
    //c2->Clear(); 
  }
  return;
}
