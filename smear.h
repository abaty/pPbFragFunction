//written by Austin Baty to smear jet pt spectra by 5%
#include "TH1D.h"
#include "TAxis.h"
#include "TF1.h"
#include "TMath.h"
#include <iostream>

void smear(TH1D * h)
{
  TH1D *clone = (TH1D*)h->Clone("tempClone");
  TF1  *gausReso = new TF1("gausReso", "gaus(0)", -1,601);

  //h->Print("all");

  //clearing histogram
  for(int i = 1; i<=120; i++)
  {
    h->SetBinContent(i,0);
    h->SetBinError(i,0);
  }  

  for(int i = 1; i<=120; i++)
  {
    //give resolution as a % of total pt, here 5%
    float pt_resolution = 0.05;
    float mean = clone->GetXaxis()->GetBinCenter(i);
    float variance = pt_resolution*mean;

    float centralValue = clone->GetBinContent(i);
    float error = clone->GetBinError(i);
    
    //gaussian and normalization
    gausReso->SetParameters(1,mean,variance);
    float denom = gausReso->Integral(mean-variance*5,mean+variance*5);

    //actual smearing
    for(int j = 1; j<=120; j++)
    {
      float weight = gausReso->Integral(clone->GetXaxis()->GetBinLowEdge(j), clone->GetXaxis()->GetBinUpEdge(j))/denom;
      float oldBin = h->GetBinContent(j);
      float oldError = h->GetBinError(j);

      h->SetBinContent(j, centralValue*weight+oldBin);
      h->SetBinError(j, error*weight+oldError);
    }
  }
  //h->Print("all");
  delete gausReso;
  delete clone;
  return;
}
