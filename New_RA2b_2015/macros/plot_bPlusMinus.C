#include <cstdio>
using namespace std;

void plot_bPlusMinus(string cutName="delphi"){

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

  Float_t legendX1 = .70; //.50;
  Float_t legendX2 = .90; //.70;
  Float_t legendY1 = .68; //.65;
  Float_t legendY2 = .85;
  TLegend* catLeg1 = new TLegend(legendX1,legendY1,legendX2,legendY2);
  catLeg1->SetTextSize(0.032);
  catLeg1->SetTextFont(42);
  catLeg1->SetFillColor(0);
  catLeg1->SetLineColor(0);
  catLeg1->SetBorderSize(0);

  TFile * file = new TFile("TauHad2/HadTauEstimation_TTbar_bPlusMinus.root","R");
  sprintf(tempname,"allEvents/%s/NBtag_%s_allEvents",cutName.c_str(),cutName.c_str());
  TH1D * bH = (TH1D *) file->Get(tempname)->Clone();
  sprintf(tempname,"BMistagPlus/%s/NBtag_%s_BMistagPlus",cutName.c_str(),cutName.c_str());
  TH1D * bHplus = (TH1D *) file->Get(tempname)->Clone();
  sprintf(tempname,"BMistagMinus/%s/NBtag_%s_BMistagMinus",cutName.c_str(),cutName.c_str());
  TH1D * bHminus = (TH1D *) file->Get(tempname)->Clone();
  
  bH->SetLineColor(4);
//  bH->SetMaximum(2);
  if(cutName=="delphi")bH->SetTitle("baseline selection");
  else if(cutName=="isoPion")bH->SetTitle("baseline minus #Delta#Phi selection");
  else if(cutName=="mht_200")bH->SetTitle("baseline minus #Delta#Phi and isoTrk selections");
  else bH->SetTitle("");
  bH->GetXaxis()->SetRangeUser(0.,4.);
  bH->GetXaxis()->SetTitle("#b");
  bH->GetYaxis()->SetTitle("Events");
  bH->GetYaxis()->SetTitleOffset(1.7);
  bHplus->SetLineColor(1);
  bHminus->SetLineColor(2);
  
  bH->Draw("hist");
  bHplus->Draw("hist, same");
  bHminus->Draw("hist, same");
  
  catLeg1->AddEntry(bH," b","l");
  catLeg1->AddEntry(bHplus," b+","l");
  catLeg1->AddEntry(bHminus," b-","l");
  catLeg1->Draw();
  
  sprintf(tempname,"BMistagPropagation_%s.png",cutName.c_str());
  canvas->Print(tempname);
  
  
  
  










}