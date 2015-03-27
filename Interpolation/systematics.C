#include "TFile.h"
#include "TH1D.h"
#include "TLine.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TPad.h"
#include "TAttMarker.h"
#include "TAttLine.h"
#include "TBox.h"
#include "TF1.h"
#include "TMath.h"

const int variations = 20;
const char * variationTag[variations]= {"","_pp2JESUP4","_pp2JESDOWN4","_pp7JESUP4","_pp7JESDOWN4","_pPb5JESUP4","_pPb5JESDOWN4","_pp2JER10","_pp7JER10","_pPb5JER10","_pp2JER2","_pp7JER2","_pPb5JER2","_NoTrackCorr","_pp2JESUP1","_pp2JESDOWN1","_pp7JESUP1","_pp7JESDOWN1","_pPb5JESUP1","_pPb5JESDOWN1"};

const int FF_Bins = 5;
double FF_Bound[FF_Bins+1] = {60,80,100,120,140,200};


TH1D** getRatio(const char * mode = "pp2", int v=0)
{
  TH1D** ratioArray = new TH1D*[FF_Bins];

  TFile * inf1 = TFile::Open(Form("FragmentationFunctions%sUE3.root",variationTag[v]),"read");
  TFile * inf2 = TFile::Open("FragmentationFunctionsUE3.root","read");
  for(int i =0; i<FF_Bins; i++)
  {
    if(strcmp(mode,"pPb5")==0)
    {
      ratioArray[i] = (TH1D*)inf1->Get(Form("pPb5Pbp5TeV_fulldata_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]));
      ratioArray[i]->Divide((TH1D*)inf2->Get(Form("pPb5Pbp5TeV_fulldata_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1])));
      ratioArray[i]->SetName(Form("%s%s_Ratio%d",mode,variationTag[v],i));
      ratioArray[i]->SetDirectory(0);
    }
    if(strcmp(mode,"pp2")==0)
    {
      ratioArray[i] = (TH1D*)inf1->Get(Form("pp2TeV_NoReweight_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]));
      ratioArray[i]->Divide((TH1D*)inf2->Get(Form("pp2TeV_NoReweight_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1])));
      ratioArray[i]->SetName(Form("%s%s_Ratio%d",mode,variationTag[v],i));
      ratioArray[i]->SetDirectory(0);
    }
    if(strcmp(mode,"pp7")==0)
    {
      ratioArray[i] = (TH1D*)inf1->Get(Form("pp7TeV_NoReweight_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]));
      ratioArray[i]->Divide((TH1D*)inf2->Get(Form("pp7TeV_NoReweight_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1])));
      ratioArray[i]->SetName(Form("%s%s_Ratio%d",mode,variationTag[v],i));
      ratioArray[i]->SetDirectory(0);
    }
  }  
  inf1->Close();
  inf2->Close();
  return ratioArray;
}

void FFSystematics(const char * mode)
{
  //getting sources of error as ratios
   TH1D** JESUP;
   TH1D** JESDOWN;
   TH1D** JER;

   //estimating 5% tracking errors
   double track = 0.05;

  if(strcmp(mode,"pPb5")==0)
  {
    JESUP = getRatio(mode,5);
    JESDOWN = getRatio(mode,6);
    JER = getRatio(mode,12);
  }
  if(strcmp(mode,"pp2")==0)
  {
    JESUP = getRatio(mode,1);
    JESDOWN = getRatio(mode,2);
    JER = getRatio(mode,10);
  }
  if(strcmp(mode,"pp7")==0)
  {
    JESUP = getRatio(mode,3);
    JESDOWN = getRatio(mode,4);
    JER = getRatio(mode,11);
  }

  TFile * output;
  if(strcmp("pPb5",mode)==0) output = new TFile("SystematicsUE3.root","recreate");
  else output = new TFile("SystematicsUE3.root","update");

  //doing asymmetric JES errors
  TH1D* JESTotUP[FF_Bins];
  TH1D* JESTotDOWN[FF_Bins];
  for(int i = 0; i<FF_Bins; i++)
  {
    JESTotUP[i] = (TH1D*)JESUP[i]->Clone(Form("%sJESTotUP%d",mode,i));
    JESTotDOWN[i] = (TH1D*)JESDOWN[i]->Clone(Form("%sJESTotDOWN%d",mode,i));

    for(int j = 0; j<JESTotUP[0]->GetSize(); j++)
    {
      if(JESTotUP[i]->GetBinContent(j)<JESDOWN[i]->GetBinContent(j)) JESTotUP[i]->SetBinContent(j,JESDOWN[i]->GetBinContent(j));
      JESTotUP[i]->SetBinContent(j,JESTotUP[i]->GetBinContent(j)-1);
      if(JESTotUP[i]->GetBinContent(j)<0) JESTotUP[i]->SetBinContent(j,0);

      if(JESTotDOWN[i]->GetBinContent(j)>JESUP[i]->GetBinContent(j)) JESTotDOWN[i]->SetBinContent(j,JESUP[i]->GetBinContent(j));
      JESTotDOWN[i]->SetBinContent(j,JESTotDOWN[i]->GetBinContent(j)-1);
      if(JESTotDOWN[i]->GetBinContent(j)>0) JESTotDOWN[i]->SetBinContent(j,0);
    }
  }

  //adding JES and JER together in quadrature
  TH1D* TotUP[FF_Bins];
  TH1D* TotDOWN[FF_Bins];
  for(int i = 0; i<FF_Bins; i++)
  {
    TotUP[i] = (TH1D*)JESTotUP[i]->Clone(Form("%sTotUP%d",mode,i)); 
    TotDOWN[i] = (TH1D*)JESTotDOWN[i]->Clone(Form("%sTotDOWN%d",mode,i));
  
    for(int j = 0; j<TotUP[0]->GetSize(); j++)
    {
      //if empty bins
      if(JER[i]->GetBinContent(j)==0 || JESTotUP[i]->GetBinContent(j)==-1 || JESTotDOWN[i]->GetBinContent(j)==-1)
      {
        TotUP[i]->SetBinContent(j,99999);
        TotDOWN[i]->SetBinContent(j,99999);
      }
      else 
      {
        TotUP[i]->SetBinContent(j,TMath::Power(TMath::Power(TotUP[i]->GetBinContent(j),2)+TMath::Power(JER[i]->GetBinContent(j)-1,2)+track*track,0.5));
        TotDOWN[i]->SetBinContent(j,TMath::Power(TMath::Power(TotDOWN[i]->GetBinContent(j),2)+TMath::Power(JER[i]->GetBinContent(j)-1,2)+track*track,0.5));
      }
    } 
    JESUP[i]->Write();
    JESDOWN[i]->Write();
    JER[i]->Write();
    JESTotUP[i]->Write();
    JESTotDOWN[i]->Write();
    TotUP[i]->Write();
    TotDOWN[i]->Write();
  }
  output->Close();
}

void InterpolationSystematics()
{

}

void RatioSystematics()
{

}

void systematics()
{
  TH1::SetDefaultSumw2();
  FFSystematics("pPb5");
  FFSystematics("pp2");
  FFSystematics("pp7");
}
