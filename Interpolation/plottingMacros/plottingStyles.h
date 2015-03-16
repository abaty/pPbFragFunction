#include "TH1D.h"
#include "TColor.h"
#include "TAttMarker.h"
#include "TAttLine.h"
#include "TAttAxis.h"

void setColors(TH1D* h, int color = 0, int isHist=0)
{
  if(color==1)
  {
    h->SetMarkerColor(kRed+1);
    h->SetLineColor(kRed+1);
  }
  else if(color==2)
  {
    h->SetMarkerColor(kBlue+1);
    h->SetLineColor(kBlue+1);
  }
  else if(color==3)
  {
    h->SetMarkerColor(kGreen+1);
    h->SetLineColor(kGreen+1);
  }
  else if(color==4)
  {
    h->SetMarkerColor(kViolet);
    h->SetLineColor(kViolet);
  }
  else
  {
    h->SetMarkerColor(1);
    h->SetLineColor(1);
  }
  h->SetLineWidth(1);
  if(isHist) h->SetMarkerSize(0);
  else h->SetMarkerSize(0.5);
  return;
}
