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

/*const int variations = 20;
const char * variationTag[variations]= {"","_pp2JESUP4","_pp2JESDOWN4","_pp7JESUP4","_pp7JESDOWN4","_pPb5JESUP4","_pPb5JESDOWN4","_pp2JER10","_pp7JER10","_pPb5JER10","_pp2JER2","_pp7JER2","_pPb5JER2","_NoTrackCorr","_pp2JESUP1","_pp2JESDOWN1","_pp7JESUP1","_pp7JESDOWN1","_pPb5JESUP1","_pPb5JESDOWN1"};

const int FF_Bins = 5;
double FF_Bound[FF_Bins+1] = {60,80,100,120,140,200};*/


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
    if(strcmp(mode,"interp")==0)
    {
      ratioArray[i] = (TH1D*)inf1->Get(Form("pPb5Pbp5TeV_data_interp_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]));
      ratioArray[i]->Divide((TH1D*)inf2->Get(Form("pPb5Pbp5TeV_data_interp_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1])));
      ratioArray[i]->SetName(Form("%s%s_Ratio%d",mode,variationTag[v],i));
      ratioArray[i]->SetDirectory(0);
    }
    if(strcmp(mode,"FFratio")==0)
    {
      ratioArray[i] = (TH1D*)inf1->Get(Form("pPbPbp_FF_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1]));
      ratioArray[i]->Divide((TH1D*)inf2->Get(Form("pPbPbp_FF_%d_%d",(int)FF_Bound[i],(int)FF_Bound[i+1])));
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
        TotUP[i]->SetBinContent(j,0);
        TotDOWN[i]->SetBinContent(j,0);
        TotUP[i]->SetBinError(j,0);
        TotDOWN[i]->SetBinError(j,0);
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

void Interpolation_and_Ratio_Systematics(const char * mode = "interp")
{
  //getting sources of error as ratios
  TH1D** pp2JESUP;
  TH1D** pp2JESDOWN;
  TH1D** pp2JER; 
  TH1D** pp7JESUP;
  TH1D** pp7JESDOWN;
  TH1D** pp7JER;
  TH1D** pPb5JESUP;
  TH1D** pPb5JESDOWN;
  TH1D** pPb5JER;

  //estimating 5% tracking errors
  double track = 0.05;
  
  pp2JESUP = getRatio(mode,1);
  pp2JESDOWN = getRatio(mode,2);
  pp2JER = getRatio(mode,10);
  pp7JESUP = getRatio(mode,3);
  pp7JESDOWN = getRatio(mode,4);
  pp7JER = getRatio(mode,11);
  pPb5JESUP = getRatio(mode,5);
  pPb5JESDOWN = getRatio(mode,6);
  pPb5JER = getRatio(mode,12);

  TFile * output = new TFile("SystematicsUE3.root","update");

  TH1D* pp2JESTotUP[FF_Bins];
  TH1D* pp2JESTotDOWN[FF_Bins];
  TH1D* pp7JESTotUP[FF_Bins];
  TH1D* pp7JESTotDOWN[FF_Bins];
  TH1D* pPb5JESTotUP[FF_Bins];
  TH1D* pPb5JESTotDOWN[FF_Bins];

  for(int i = 0; i<FF_Bins; i++)
  {
    pp2JESTotUP[i] = (TH1D*)pp2JESUP[i]->Clone(Form("%s_pp2JESTotUP%d",mode,i));
    pp2JESTotDOWN[i] = (TH1D*)pp2JESDOWN[i]->Clone(Form("%s_pp2JESTotDOWN%d",mode,i));
    pp7JESTotUP[i] = (TH1D*)pp7JESUP[i]->Clone(Form("%s_pp7JESTotUP%d",mode,i));
    pp7JESTotDOWN[i] = (TH1D*)pp7JESDOWN[i]->Clone(Form("%s_pp7JESTotDOWN%d",mode,i));
    pPb5JESTotUP[i] = (TH1D*)pPb5JESUP[i]->Clone(Form("%s_pPb5JESTotUP%d",mode,i));
    pPb5JESTotDOWN[i] = (TH1D*)pPb5JESDOWN[i]->Clone(Form("%s_pPb5JESTotDOWN%d",mode,i));

    for(int j = 0; j<pp2JESTotUP[0]->GetSize(); j++)
    {
      if(pp2JESTotUP[i]->GetBinContent(j)<pp2JESDOWN[i]->GetBinContent(j)) pp2JESTotUP[i]->SetBinContent(j,pp2JESDOWN[i]->GetBinContent(j));
      pp2JESTotUP[i]->SetBinContent(j,pp2JESTotUP[i]->GetBinContent(j)-1);
      if(pp2JESTotUP[i]->GetBinContent(j)<0) pp2JESTotUP[i]->SetBinContent(j,0);

      if(pp2JESTotDOWN[i]->GetBinContent(j)>pp2JESUP[i]->GetBinContent(j)) pp2JESTotDOWN[i]->SetBinContent(j,pp2JESUP[i]->GetBinContent(j));
      pp2JESTotDOWN[i]->SetBinContent(j,pp2JESTotDOWN[i]->GetBinContent(j)-1);
      if(pp2JESTotDOWN[i]->GetBinContent(j)>0) pp2JESTotDOWN[i]->SetBinContent(j,0);
 
      if(pp7JESTotUP[i]->GetBinContent(j)<pp7JESDOWN[i]->GetBinContent(j)) pp7JESTotUP[i]->SetBinContent(j,pp7JESDOWN[i]->GetBinContent(j));
      pp7JESTotUP[i]->SetBinContent(j,pp7JESTotUP[i]->GetBinContent(j)-1);
      if(pp7JESTotUP[i]->GetBinContent(j)<0) pp7JESTotUP[i]->SetBinContent(j,0);

      if(pp7JESTotDOWN[i]->GetBinContent(j)>pp7JESUP[i]->GetBinContent(j)) pp7JESTotDOWN[i]->SetBinContent(j,pp7JESUP[i]->GetBinContent(j));
      pp7JESTotDOWN[i]->SetBinContent(j,pp7JESTotDOWN[i]->GetBinContent(j)-1);   
      if(pp7JESTotDOWN[i]->GetBinContent(j)>0) pp7JESTotDOWN[i]->SetBinContent(j,0);

      if(pPb5JESTotUP[i]->GetBinContent(j)<pPb5JESDOWN[i]->GetBinContent(j)) pPb5JESTotUP[i]->SetBinContent(j,pPb5JESDOWN[i]->GetBinContent(j));
      pPb5JESTotUP[i]->SetBinContent(j,pPb5JESTotUP[i]->GetBinContent(j)-1);
      if(pPb5JESTotUP[i]->GetBinContent(j)<0) pPb5JESTotUP[i]->SetBinContent(j,0);

      if(pPb5JESTotDOWN[i]->GetBinContent(j)>pPb5JESUP[i]->GetBinContent(j)) pPb5JESTotDOWN[i]->SetBinContent(j,pPb5JESUP[i]->GetBinContent(j));
      pPb5JESTotDOWN[i]->SetBinContent(j,pPb5JESTotDOWN[i]->GetBinContent(j)-1);
      if(pPb5JESTotDOWN[i]->GetBinContent(j)>0) pPb5JESTotDOWN[i]->SetBinContent(j,0);
    }
  }

  //adding JES and JER together in quadrature
  TH1D* TotUP[FF_Bins];
  TH1D* TotDOWN[FF_Bins];
  for(int i = 0; i<FF_Bins; i++)
  {
    TotUP[i] = (TH1D*)pp2JESTotUP[i]->Clone(Form("%s_TotUP%d",mode,i)); 
    TotDOWN[i] = (TH1D*)pp2JESTotDOWN[i]->Clone(Form("%s_TotDOWN%d",mode,i));
  
    for(int j = 0; j<TotUP[0]->GetSize(); j++)
    {
      //if empty bins
      if(pp2JER[i]->GetBinContent(j)==0 || pp2JESTotUP[i]->GetBinContent(j)==-1 || pp2JESTotDOWN[i]->GetBinContent(j)==-1 || pp7JER[i]->GetBinContent(j)==0 || pp7JESTotUP[i]->GetBinContent(j)==-1 || pp7JESTotDOWN[i]->GetBinContent(j)==-1 || pPb5JER[i]->GetBinContent(j)==0 || pPb5JESTotUP[i]->GetBinContent(j)==-1 || pPb5JESTotDOWN[i]->GetBinContent(j)==-1)
      {
        TotUP[i]->SetBinContent(j,0);
        TotDOWN[i]->SetBinContent(j,0);
        TotUP[i]->SetBinError(j,0);
        TotDOWN[i]->SetBinError(j,0);
      }
      else 
      {
        TotUP[i]->SetBinContent(j,TMath::Power(TMath::Power(TotUP[i]->GetBinContent(j),2)+TMath::Power(pp7JESTotUP[i]->GetBinContent(j),2)+TMath::Power(pPb5JESTotUP[i]->GetBinContent(j),2)+TMath::Power(pp7JER[i]->GetBinContent(j)-1,2)+TMath::Power(pp2JER[i]->GetBinContent(j)-1,2)+TMath::Power(pPb5JER[i]->GetBinContent(j)-1,2)+track*track,0.5));
        TotDOWN[i]->SetBinContent(j,TMath::Power(TMath::Power(TotDOWN[i]->GetBinContent(j),2)+TMath::Power(pp7JESTotDOWN[i]->GetBinContent(j),2)+TMath::Power(pPb5JESTotDOWN[i]->GetBinContent(j),2)+TMath::Power(pp7JER[i]->GetBinContent(j)-1,2)+TMath::Power(pp2JER[i]->GetBinContent(j)-1,2)+TMath::Power(pPb5JER[i]->GetBinContent(j)-1,2)+track*track,0.5));
      }
    }
    pp2JESUP[i]->Write();
    pp2JESDOWN[i]->Write();
    pp2JER[i]->Write(); 
    pp7JESUP[i]->Write();
    pp7JESDOWN[i]->Write();
    pp7JER[i]->Write();
    pPb5JESUP[i]->Write();
    pPb5JESDOWN[i]->Write();
    pPb5JER[i]->Write(); 
    pp2JESTotUP[i]->Write();
    pp2JESTotDOWN[i]->Write(); 
    pp7JESTotUP[i]->Write();
    pp7JESTotDOWN[i]->Write();
    pPb5JESTotUP[i]->Write();
    pPb5JESTotDOWN[i]->Write();
    TotUP[i]->Write();
    TotDOWN[i]->Write();
  }
  output->Close(); 
}

void systematics()
{
  TH1::SetDefaultSumw2();
  FFSystematics("pPb5");
  FFSystematics("pp2");
  FFSystematics("pp7");
  Interpolation_and_Ratio_Systematics("interp");
  Interpolation_and_Ratio_Systematics("FFratio");
}
