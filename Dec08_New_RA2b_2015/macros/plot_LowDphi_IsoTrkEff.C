#include <cstdio>
using namespace std;

void plot_LowDphi_IsoTrkEff(){

  gStyle->SetOptStat(0);
  gStyle->SetPalette(1) ; // for better color output
  char tempname[200];
  int W = 600;
  int H = 600;
  int H_ref = 600;
  int W_ref = 800;
  float T = 0.08*H_ref;
  float B = 0.12*H_ref;
  float L = 0.12*W_ref;
  float R = 0.04*W_ref;

  TCanvas* canvas = new TCanvas("canvas","canvas",10,10,W,H);
  canvas->SetFillColor(0);
  canvas->SetBorderMode(0);
  canvas->SetFrameFillStyle(0);
  canvas->SetFrameBorderMode(0);
  canvas->SetLeftMargin( L/W );
  canvas->SetRightMargin( R/W );
  canvas->SetTopMargin( T/H );
  canvas->SetBottomMargin( B/H );
  canvas->SetTickx(0);
  canvas->SetTicky(0);

  Float_t legendX1 = .20; //.50;
  Float_t legendX2 = .90; //.70;
  Float_t legendY1 = .68; //.65;
  Float_t legendY2 = .85;
  TLegend* catLeg1 = new TLegend(legendX1,legendY1,legendX2,legendY2);
  catLeg1->SetTextSize(0.032);
  catLeg1->SetTextFont(42);
  catLeg1->SetFillColor(0);
  catLeg1->SetLineColor(0);
  catLeg1->SetBorderSize(0);

  TFile * file = new TFile("InputRootFiles/IsoEfficiencies_TTbar_stacked.root","R");
  TH1D * IsoEff = (TH1D *) file->Get("IsoEff")->Clone();
  TH1D * IsoEff_lowDelphi = (TH1D *) file->Get("IsoEff_lowDphi")->Clone();
  
  IsoEff->SetLineColor(4);
  IsoEff->SetMaximum(1.5);
  IsoEff->GetXaxis()->SetTitle("search bin");
  IsoEff->GetYaxis()->SetTitle("isolated track efficiency");
  IsoEff->SetTitle("");
  IsoEff_lowDelphi->SetLineColor(1);
  
  
  IsoEff->Draw();
  IsoEff_lowDelphi->Draw("same");
  
  catLeg1->AddEntry(IsoEff,"delphi","l");
  catLeg1->AddEntry(IsoEff_lowDelphi,"low delphi","l");
  catLeg1->Draw();
  
  canvas->Print("IsoTrkEfficiency_TTbar_plusLowDphi.png");
  
  
  
  
  










}