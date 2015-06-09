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

const char * files1[9] = {"pp2TeV_NoReweight","pPb5Pbp5TeV_fulldata","pp7TeV_NoReweight","pp5TeV_genMC","pp5TeV_genMC","pp7TeV_reco_NoReweight","pp2TeV_gen_NoReweight","pPb5Pbp5TeV_genMC","pp7TeV_gen_NoReweight"};
const char * files2[9] = {"pp2TeV_NoReweight","pPb5Pbp5TeV_fulldata","pp7TeV_NoReweight","pPb5Pbp5TeV_genMC","pPb5Pbp5TeV_genMC","pp7TeV_reco_NoReweight","pp2TeV_gen_NoReweight","pPb5Pbp5TeV_genMC","pp7TeV_gen_NoReweight"};

void getComparison(int mode, int UE)
{
  TH1::SetDefaultSumw2();
 
  TLatex * lat = new TLatex(0.1,0.1,"test");
  lat->SetTextSize(0.06);
   
  const int bins[6] = {60,80,100,120,140,200};

  TFile * infpPb = new TFile("../FragmentationFunctionsUE3.root","read"); 
  TFile * infPbp = new TFile(Form("../FragmentationFunctionsUE%d.root",UE),"read");

  TH1D * pPbFF[5];
  TH1D * PbpFF[5];
  for(int i = 0; i<5; i++)
  {
    if(mode==3) pPbFF[i] = (TH1D*)infPbp->Get(Form("%s_%d_%d",files1[mode],bins[i],bins[i+1]));
    //else if(mode==4) pPbFF[i] = (TH1D*)infpPb->Get(Form("%s_%d_%d",files1[mode],bins[i],bins[i+1]));
    else pPbFF[i] = (TH1D*)infpPb->Get(Form("%s_%d_%d",files1[mode],bins[i],bins[i+1]));
    PbpFF[i] = (TH1D*)infPbp->Get(Form("%s_%d_%d",files2[mode],bins[i],bins[i+1]));
    //PbpFF[i] = (TH1D*)infMC->Get(Form("pPb5TeV_data_%d_%d",bins[i],bins[i+1]));
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
  pPbFF[i]->SetMaximum(9);
  pPbFF[i]->SetMinimum(0.000001);
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
  PbpFF[i]->SetMaximum(5);
  PbpFF[i]->SetMinimum(0.00001);
  PbpFF[i]->GetYaxis()->SetTitleColor(1);
  PbpFF[i]->GetYaxis()->SetTitleSize(0.07);
  if(i!=0)  PbpFF[i]->GetYaxis()->SetTitleSize(0);
  PbpFF[i]->GetYaxis()->SetTitleOffset(1);
  PbpFF[i]->GetYaxis()->SetLabelColor(1);
  PbpFF[i]->GetYaxis()->SetLabelSize(0.04);
  if(i!=0) PbpFF[i]->GetYaxis()->SetLabelSize(0);

  pPbFF[i]->DrawCopy("e");
  PbpFF[i]->DrawCopy("same e");
  lat->DrawLatex(0.6,0.000002,Form("%d GeV/c < p_{T}^{jet} < %d GeV/c",(int)bins[i],(int)bins[i+1]));
  }
  c2->cd(1);
  TLegend * leg = new TLegend(0.2,0.1,0.8,0.5);
 // leg->AddEntry((TObject*)0, "140 < p_{t}^{jet} < 200 GeV/c", "");
  if(mode==0) leg->AddEntry((TObject*)0,"2.76 TeV pp","");
  if(mode==1) leg->AddEntry((TObject*)0,"5.02 TeV pPb","");
  if(mode==2) leg->AddEntry((TObject*)0,"7 TeV pp","");
  if(mode==3) leg->AddEntry((TObject*)0,"Gen MC","");
  if(mode==4) leg->AddEntry((TObject*)0,"Gen MC","");
  if(mode==5) leg->AddEntry((TObject*)0,"7 TeV reco PYTHIA","");
  if(mode==6) leg->AddEntry((TObject*)0,"2.76 TeV gen PYTHIA","");
  if(mode==7) leg->AddEntry((TObject*)0,"5.02 TeV gen PYTHIA+HIJING","");
  if(mode==8) leg->AddEntry((TObject*)0,"7 TeV gen PYTHIA","");
  if(mode!=3 && mode!=4) leg->AddEntry(pPbFF[0], "no UE subtr.", "p");
  else if(mode==4) leg->AddEntry(pPbFF[0], "no UE subtr. 5 TeV P", "p");
  else leg->AddEntry(pPbFF[0], "Cone UE subtr. 5 TeV P", "p");
  if(UE==0 && (mode!=3 && mode!=4)) leg->AddEntry(PbpFF[0], "90 degree UE subtr.", "p");
  if(UE==0 && (mode==3 || mode==4)) leg->AddEntry(PbpFF[0], "Cone UE subtr. P+H", "p");
  if(UE==2) leg->AddEntry(PbpFF[0], "MB mixing UE subtr.", "p");
  //leg->AddEntry(PbpFF[0],"pPb FF MC","p");
  leg->Draw();

  TLine * l = new TLine(0,1,220,1);
  l->SetLineColor(1);

  for(int i = 0 ; i<5; i++)
  {
  c2->cd(i+6);
  c2->cd(i+6)->SetLogx();
  PbpFF[i]->SetMaximum(1.2);
  if(mode!=3) PbpFF[i]->SetMinimum(0.4);
  else PbpFF[i]->SetMinimum(0.7);
  PbpFF[i]->Divide(pPbFF[i]);
  //pPbFF[i]->SetMaximum(1.5);
  //pPbFF[i]->SetMinimum(0.5);
  //pPbFF[i]->Divide(PbpFF[i]);

  PbpFF[i]->GetYaxis()->SetTitle("FF_{UE_subtracted}/FF");
  //pPbFF[i]->GetYaxis()->SetTitle("data/MC");

  PbpFF[i]->DrawCopy("e");
  //pPbFF[i]->DrawCopy("e");
  l->Draw("same");
  }
  c2->SaveAs(Form("../plots/UE%d_Comparison_%s%d.png",UE,files1[mode],mode));
  c2->SaveAs(Form("../plots/UE%d_Comparison_%s%d.pdf",UE,files1[mode],mode));
  delete l;
  delete lat;
  delete c2;
  infpPb->Close();
  infPbp->Close();
}

void UE_Comparison()
{
  getComparison(0,0);
  getComparison(1,0);
  getComparison(2,0);
  getComparison(3,0);
  getComparison(4,0);
  getComparison(0,2);
  getComparison(1,2);
  getComparison(2,2);
  //getComparison(3);
 // getComparison(4);
 // getComparison(5);
 // getComparison(6);
 // getComparison(7);
 // getComparison(8);
}
