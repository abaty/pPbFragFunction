/*
% & pp & PbPb 50--100\% & PbPb 30--50\% & PbPb 10--30\% & PbPb 0--10\% \\
% \hline
% Jet reco and selection & 0.8 & 0.8 & 1.0 & 2.5 & 3.0 \\
% Jet energy scale & 0.5 & 0.5 & 0.5 & 0.8 & 1.0 \\
% Tracking efficiency & 0.1--0.7 & 0.1--0.7 & 0.1--0.8 & 0.1--1.0 & 0.1-1.2 \\
% Event selection & $<0.1$ & $<0.1$ & $<0.1$ & $<0.1$ & $<0.1$ \\
% HCAL noise & $<0.1$ & $<0.1$ & $<0.1$ & $<0.1$ & $<0.1$ \\
% \hline
% \hline
% Total Systematics & 0.9--1.2 & 0.9--1.2 & 1.1--1.4 & 2.6--2.8 & 3.2--3.4 \\
*/

#include <iostream>
#include <iomanip>
#include "TFile.h"
#include "TH1D.h"
#include "TMath.h"
#include "math.h"

int flags = 0;

//interval should be between 0 to 2 (3 intervals)
void setMM(TH1D * h, int interval, int source, bool isXi, double * minmax)
{
  double min = 10000.0;
  double max = -10000.0;
  int lowBin,highBin;
  if(interval==0 && !isXi)
  {
    lowBin = 1;//0.5
    highBin = 9;//5.88
  }
  if(interval==1 && !isXi)
  {
    lowBin = 10;//5.88
    highBin = 16;//44.9
  }
  if(interval==2 && !isXi)
  {
    lowBin = 17;//44.9
    highBin = 23;//200
  }

  if(interval==0 && isXi)
  {
    lowBin = 1;//0
    highBin = 4;//1
  }
  if(interval==1 && isXi)
  {
    lowBin = 5;//1
    highBin = 12;//3
  }
  if(interval==2 && isXi)
  {
    lowBin = 13;//3
    highBin = 20;//5
  }

  if(source != 5 && source != 6)
  {
    for(int i = lowBin; i< highBin; i++)
    {
      if(TMath::Abs(h->GetBinContent(i)) < min && h->GetBinContent(i)!=0) min = TMath::Abs(h->GetBinContent(i));
      if(TMath::Abs(h->GetBinContent(i)) > max && h->GetBinContent(i)!=0) max = TMath::Abs(h->GetBinContent(i));
    }
  }
  else
  {
    for(int i = lowBin; i< highBin; i++)
    {
      if(h->GetBinContent(i) < min && h->GetBinContent(i)!=0) min = h->GetBinContent(i);
      if(h->GetBinContent(i) > max && h->GetBinContent(i)!=0) max = h->GetBinContent(i);
    }
  }

  double temp = 0;  
  if(source == 5)
  {
    temp = max;
    max  = -min;
    min  = -temp;
  }
  if(source == 4 || source == 8)
  {
    max = -max;
    min = -min;
  }


  if(TMath::Abs(min)<0.1)      minmax[0] = roundf(min*1000.0)/10;
  else if(TMath::Abs(min)<1)   minmax[0] = roundf(min*100.0)/1;
  else                         minmax[0] = roundf(min*10.0)*10;
  if(TMath::Abs(max)<0.1)      minmax[1] = roundf(max*1000.0)/10;
  else if(TMath::Abs(max)< 1)  minmax[1] = roundf(max*100.0)/1;
  else                         minmax[1] = roundf(max*10.0)*10;

  if(TMath::Abs(min) > 1000)
  {
    minmax[0] = 0;
    flags++;
  } 
  if(TMath::Abs(max) > 1000)
  {
     minmax[1] = 0;
     flags++;
  }
}

void getTable(int UE = 0)
{
  TFile * input = TFile::Open(Form("SystematicsUE%d.root",UE),"read");
  
  //first index is system, pp2,pp7,pPb5,interp,FFratio
  //second index is jet bin 60-80,140-200,60-80 vs xi, 140-200 vs xi
  //third index is UE subtracion 0-none, 1-rotated
  //fourth index is each source of error
  //Total JES Upward
  //Total JES Downward
  //Total JER
  //Reco/Gen MC difference
  //Charge Fraction Cut
  //Pbp/pPb difference
  //UE subtaction systematic
  //total up
  //total down
  TH1D * h[5][4][9];

  const char * prefix[5] = {"pp2_","pp7_","pPb5_","interp_","FFratio_"};
  const char * suffix[4] = {"0","4","5_xi","9_xi"};
  const char * middle[9] = {"JERTot","pPbPbpDiff","60DegreeCone_Ratio","JESTotUP","JESTotDOWN","NoChargeCut_MCDiff","ChargeCutDiff","TotUP","TotDOWN"};
  const char * source[9] = {"JER","pPb/Pbp Difference","UE Subtraction","JES (Upwards Error)","JES (Downwards Error)","Reco/Gen Difference","Jet Charge Fraction Cut","Total (Upwards Error)","Total (Downwards Error)"};

  for(int i = 0; i<5; i++)
  {
    for(int j = 0; j<4; j++)
    {
      for(int k = 0; k<9; k++)
      {
        if(i<2 && k==1) continue;
        if(UE!=0 && k==2) continue;
        h[i][j][k] = (TH1D*)input->Get(Form("%s%s%s",prefix[i],middle[k],suffix[j]));
      }
    }
  }  
  using namespace std;
  
  const char * caption[5] = {" 2.76 TeV pp fragmentation function"," 7 TeV pp fragmentation function"," 5.02 TeV pPb fragmentation function"," pp interpolation"," fragmentation function ratio"};
  const char * label[5] = {"pp2","pp7","pPb5","interp","FFratio"};

  for(int i = 0; i<5; i++)
  {
    for(int j = 0; j<2; j++)
    {
      cout << "\\begin{table}[h!]\n" 
      <<"\\begin{center}\n"
      <<"\\caption{Summary of the systematic uncertainies in the"<<caption[i];
      if(UE==0) cout << " with a 90-degree phi rotated underlying event subtraction";
      if(j==1)   cout << " as a function of $\\xi$";
      else      cout << " as a function of track $\\pt$";
      cout <<". $\\pt$s are given in units of $\\GeVc$.}\n"
      <<"\\label{" << label[i] << i << j << "_syst"<<UE<<"}\n \\resizebox{\\textwidth}{!}{ \n\\begin{tabular}{|l|c|c|c|c|c|c|}\n"
      <<"\\hline\n"
      <<"& \\multicolumn{3}{|c|}{$60<p_{T}^{jet}<80$} & \\multicolumn{3}{|c|}{$140<p_{T}^{jet}<200$} \\\\\n"
      <<"\\hline\n";
        
      if(j==0) cout << "&$0.5<p_{T}^{track}<5.9$&$5.9<p_{T}^{track}<45$&$45<p_{T}^{track}<200$&$0.5<p_{T}^{track}<5.9$&$5.9<p_{T}^{track}<45$&$45<p_{T}^{track}<200$\\\\\n";
      else    cout << "&$0<\\xi<1$ & $1<\\xi<3$&$3<\\xi<5$ & $0<\\xi<1$&$1<\\xi<3$&$3<\\xi<5$\\\\\n"; 
     
      cout << "\\hline \n"
      << "Symmetric Error Source&&&&&& \\\\ \n"
      << "\\hline \n";
      if(i!=4) cout << "Tracking & 3.9\\%& 3.9\\%& 3.9\\%& 3.9\\%& 3.9\\%& 3.9\\% \\\\ \n";
      else cout << "Tracking & 5.5\\%& 5.5\\%& 5.5\\%& 5.5\\%& 5.5\\%& 5.5\\% \\\\ \n";
      cout << "\\hline \n";
      if(i!=3 || i!=4)cout << "PDF + Gen Interpolation & 0.5\\%& 0.5\\%& 0.5\\%& 0.5\\%& 0.5\\%& 0.5\\% \\\\ \n";
      for(int k = 0; k<9; k++)
      {
        if(i<2 && k==1) continue;
        if(UE!=0 && k==2) continue; 
        double mm[6][2];
        if(j==0)
        {
          setMM(h[i][0][k],0,k,0,mm[0]);
          setMM(h[i][0][k],1,k,0,mm[1]);
          setMM(h[i][0][k],2,k,0,mm[2]);
          setMM(h[i][1][k],0,k,0,mm[3]);
          setMM(h[i][1][k],1,k,0,mm[4]);
          setMM(h[i][1][k],2,k,0,mm[5]);
        }
        if(j==1)
        {
          setMM(h[i][2][k],0,k,1,mm[0]);
          setMM(h[i][2][k],1,k,1,mm[1]);
          setMM(h[i][2][k],2,k,1,mm[2]);
          setMM(h[i][3][k],0,k,1,mm[3]);
          setMM(h[i][3][k],1,k,1,mm[4]);
          setMM(h[i][3][k],2,k,1,mm[5]);
        }

        if(k==7 || k==3) cout<< "\\hline\n &&&&&& \\\\ \n";
        if(k==3) cout<< "\\hline\n Asymmetric Error Source&&&&&& \\\\ \n";
        cout << "\\hline\n" << source[k];
        for(int t = 0; t<6; t++)
        {
          cout <<"&"<< mm[t][0] << " -- " << mm[t][1] << "\\%";
        }
        cout << "\\\\\n";
      }
      cout << "\\hline\n"
      <<"\\end{tabular}}\n"
      <<"\\end{center}\n"
      <<"\\end{table}\n" << endl;
    }
  }
  input->Close();
}

void makeSystematicsTable()
{
  getTable(0);
  getTable(3);

  for(int f = 0; f<flags; f++) std::cout << "\n\n\n THERE WAS AN ISSUE WITH THE CODE GIVING HUGE ERRORS, I HAVE SET IT TO ZERO BUT YOU SHOULD CHECK WHAT IS GOING ON IN THE CODE \n\n\n\n" << std::endl;
}
