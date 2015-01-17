#include <cstdio>
#include <map>
#include <string>
#include "TFile.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TLegend.h"
#include "TFrame.h"

using namespace std;

//drawPlot(string cutname="RA2nocut", string histname="NJet", string scale="log"){
void drawPlot(){

string scale="log";
map<int, string> histname;
map<int, string> cutname;

  histname[0]="HT";
  histname[1]="MHT";
  histname[2]="NJet";
  histname[3]="NBtag";


cutname[0]="RA2nocut";cutname[1]="RA23Jetcut";cutname[2]="RA2HT500cut";
cutname[3]="RA2MHT200cut" ;cutname[4]="RA2delphicut";
cutname[5]="RA2noleptoncut";
cutname[6]="RA24Jetcut";cutname[7]="RA25Jetcut";
cutname[8]="RA26Jetcut" ;cutname[9]="RA2allbutHT2500cut";
cutname[10]="RA2allbutMHT1000cut";cutname[11]= "RA2allcut";

cutname[12]="RA2noleptoncut_isoTrk" ;
cutname[13]="RA24Jetcut_isoTrk" ;cutname[14]="RA25Jetcut_isoTrk" ;
cutname[15]="RA26Jetcut_isoTrk" ;cutname[16]="RA2allbutHT2500cut_isoTrk" ;
cutname[17]="RA2allbutMHT1000cut_isoTrk";cutname[18]= "RA2allcut_isoTrk";

cutname[19]="2b";cutname[20]="b2_3Jetcut";cutname[21]="b2_HT500cut" ;
cutname[22]="b2_MHT200cut" ;cutname[23]="b2_delphicut" ;cutname[24]="b2_noleptoncut" ;
cutname[25]="b2_4Jetcut" ;cutname[26]="b2_5Jetcut" ;cutname[27]="b2_6Jetcut" ;
cutname[28]="b2_allbutHT2500cut" ;cutname[29]="b2_allbutMHT1000cut";cutname[30]= "b2_allcut";

cutname[31]="b2_noleptoncut_isoTrk" ;
cutname[32]="b2_4Jetcut_isoTrk" ;cutname[33]="b2_5Jetcut_isoTrk" ;cutname[34]="b2_6Jetcut_isoTrk" ;
cutname[35]="b2_allbutHT2500cut_isoTrk" ;cutname[36]="b2_allbutMHT1000cut_isoTrk";cutname[37]= "b2_allcut_isoTrk";

  //------------------------------
  // Signal
  TFile * Sigfile =new TFile("../T1tttt_1200_mLSP_800_00.root","R");

  //
  TFile * BJfile  =new TFile("../WJets_PU20bx25.root","R");
  TFile * TTfile  =new TFile("../TTJets_PU20bx25.root","R");
/*
  TFile * Bfile   =new TFile("../PhaseII4_B_14TEV_140PileUp.root","R");  
  TFile * BBfile  =new TFile("../PhaseII4_BB_14TEV_140PileUp.root","R");
  TFile * BBBfile =new TFile("../PhaseII4_BBB_14TEV_140PileUp.root","R");
  TFile * BJJfile =new TFile("../PhaseII4_BJJ_14TEV_140PileUp.root","R");
  TFile * Hfile   =new TFile("../PhaseII4_H_14TEV_140PileUp.root","R");
  TFile * LLfile  =new TFile("../PhaseII4_LL_14TEV_140PileUp.root","R");
  TFile * LLBfile =new TFile("../PhaseII4_LLB_14TEV_140PileUp.root","R");
  TFile * TBfile  =new TFile("../PhaseII4_TB_14TEV_140PileUp.root","R");
  TFile * TJfile  =new TFile("../PhaseII4_TJ_14TEV_140PileUp.root","R");
  TFile * TTBfile =new TFile("../PhaseII4_TTB_14TEV_140PileUp.root","R");
*/

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////Some cosmetic work for official documents. 
//  gROOT->LoadMacro("tdrstyle.C");
//  setTDRStyle();

//  gROOT->LoadMacro("CMS_lumi_v2.C");

bool  writeExtraText = false;       // if extra text
string  extraText  = "Preliminary";  // default extra text is "Preliminary"
string  lumi_8TeV  = "19.1 fb^{-1}"; // default is "19.7 fb^{-1}"
string  lumi_7TeV  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"

  int iPeriod = 14;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 14= PU=140,14TeV 
  int iPos = 33;       // left-aligned
  
  int W = 600;
  int H = 600;

  // 
  // Simple example of macro: plot with CMS name and lumi text
  //  (this script does not pretend to work in all configurations)
  // iPeriod = 1*(0/1 7 TeV) + 2*(0/1 8 TeV)  + 4*(0/1 13 TeV) 
  // For instance: 
  //               iPeriod = 3 means: 7 TeV + 8 TeV
  //               iPeriod = 7 means: 7 TeV + 8 TeV + 13 TeV 
  // Initiated by: Gautier Hamel de Monchenault (Saclay)
  //
  int H_ref = 600; 
  int W_ref = 800; 

  // references for T, B, L, R
  float T = 0.08*H_ref;
  float B = 0.12*H_ref; 
  float L = 0.12*W_ref;
  float R = 0.04*W_ref;

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TFile * file; 
TDirectory * cdtoit;

file = new TFile("Plots.root","RECREATE");

for(int ic=0; ic < cutname.size(); ic++){
cdtoit = file->mkdir(cutname[ic].c_str());
cdtoit->cd();
for(int ih=0; ih < histname.size(); ih++){


  //
  THStack * tempstack;
  THStack * finalstack = new THStack("finalstack","");
//  TH1D * temphist, * VJhist, * Thist, * Otherhist, * TThist, * VVhist;
  TH1D * temphist, * VJhist, * TThist;
  char tempname[200];
  char xtitlename[200];
  char ytitlename[200];

  //
  // Define canvas
  // TCanvas * c1 = new TCanvas("c1", "c1", 800, 800); 
  // KH-added  
  char canvName[200];
  sprintf(canvName,"%s_%s",cutname[ic].c_str(), histname[ih].c_str());
  TCanvas* c1 = new TCanvas(canvName,canvName,10,10,W,H);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin( L/W );
  c1->SetRightMargin( R/W );
  c1->SetTopMargin( T/H );
  c1->SetBottomMargin( B/H );
  c1->SetTickx(0);
  c1->SetTicky(0);
  // KH-added

  //
  // Define TLegend
  Float_t legendX1 = .60;  //.50;
  Float_t legendX2 = .90;  //.70;
  Float_t legendY1 = .45;  //.65;
  Float_t legendY2 = .80;
  TLegend* catLeg1 = new TLegend(legendX1,legendY1,legendX2,legendY2);
  catLeg1->SetTextSize(0.032);
  catLeg1->SetTextFont(42);

  //
  // Define rebinning
  int rebin_MHT=2;
  int rebin_HT=2;

  /*
  ///add TTB to the finalstack
  sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname[ic].c_str(),histname[ih].c_str(),cutname[ic].c_str());
  tempstack = (THStack *)TTBfile->Get(tempname)->Clone();
  temphist = (TH1D *) tempstack->GetStack()->Last();
  temphist->SetFillColor(7);
  catLeg1->AddEntry(temphist,"t#bar{t} + V","f");
  finalstack->Add(temphist);
  */

  /////////All Other Backgrounds
  //
  // Otherhist: TTB,BBB,H,LL,LLB
  // Thist:  TJ+TB
  // VVhist: BB
  // VJhist: B+BJ+BJJ
  // TThist: TT
  // 
/*
  ///add BBB to the finalstack
  sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname[ic].c_str(),histname[ih].c_str(),cutname[ic].c_str());
  tempstack = (THStack *)BBBfile->Get(tempname)->Clone();
  Otherhist = (TH1D *) tempstack->GetStack()->Last();

  ///add TTB to the finalstack
  sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname[ic].c_str(),histname[ih].c_str(),cutname[ic].c_str());
  tempstack = (THStack *)TTBfile->Get(tempname)->Clone();
  temphist = (TH1D *) tempstack->GetStack()->Last();
  Otherhist->Add(temphist);

  ///add H to the finalstack
  sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname[ic].c_str(),histname[ih].c_str(),cutname[ic].c_str());
  tempstack = (THStack *)Hfile->Get(tempname)->Clone();
  temphist = (TH1D *) tempstack->GetStack()->Last();
  Otherhist->Add(temphist);

  ///add LL to the finalstack
  sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname[ic].c_str(),histname[ih].c_str(),cutname[ic].c_str());
  tempstack = (THStack *)LLfile->Get(tempname)->Clone();
  temphist = (TH1D *) tempstack->GetStack()->Last();
  Otherhist->Add(temphist);

  ///add LLB to the finalstack
  sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname[ic].c_str(),histname[ih].c_str(),cutname[ic].c_str());
  tempstack = (THStack *)LLBfile->Get(tempname)->Clone();
  temphist = (TH1D *) tempstack->GetStack()->Last();
  Otherhist->Add(temphist);
  Otherhist->SetFillColor(4);  
  if(histname[ih]=="MHT" && rebin_MHT!=1) Otherhist->Rebin(rebin_MHT);
  if(histname[ih]=="HT"  && rebin_HT!=1)  Otherhist->Rebin(rebin_HT);
  finalstack->Add(Otherhist);

  /////endl of other backgrounds

  ///add BB to the finalstack
  sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname[ic].c_str(),histname[ih].c_str(),cutname[ic].c_str());
  tempstack = (THStack *)BBfile->Get(tempname)->Clone();
  VVhist = (TH1D *) tempstack->GetStack()->Last();
  VVhist->SetFillColor(6);
  if(histname[ih]=="MHT" && rebin_MHT!=1) VVhist->Rebin(rebin_MHT);
  if(histname[ih]=="HT"  && rebin_HT!=1)  VVhist->Rebin(rebin_HT);
  finalstack->Add(VVhist);

  ///add TB to the finalstack
  sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname[ic].c_str(),histname[ih].c_str(),cutname[ic].c_str());
  tempstack = (THStack *)TBfile->Get(tempname)->Clone();
  Thist = (TH1D *) tempstack->GetStack()->Last();

  ///add TJ to the finalstack
  sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname[ic].c_str(),histname[ih].c_str(),cutname[ic].c_str());
  tempstack = (THStack *)TJfile->Get(tempname)->Clone();
  temphist = (TH1D *) tempstack->GetStack()->Last();
  Thist->Add(temphist);
  Thist->SetFillColor(9);
  if(histname[ih]=="MHT" && rebin_MHT!=1) Thist->Rebin(rebin_MHT);
  if(histname[ih]=="HT"  && rebin_HT!=1)  Thist->Rebin(rebin_HT);
  finalstack->Add(Thist);

  ///add B to the finalstack
  sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname[ic].c_str(),histname[ih].c_str(),cutname[ic].c_str());
  tempstack = (THStack *)Bfile->Get(tempname)->Clone();
  VJhist = (TH1D *) tempstack->GetStack()->Last();


  ///add BJJ to the finalstack
  sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname[ic].c_str(),histname[ih].c_str(),cutname[ic].c_str());
  tempstack = (THStack *)BJJfile->Get(tempname)->Clone();
  temphist = (TH1D *) tempstack->GetStack()->Last();
  VJhist->Add(temphist);
  VJhist->SetFillColor(46);
*/

  ///add BJ to the finalstack
  sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname[ic].c_str(),histname[ih].c_str(),cutname[ic].c_str());
  tempstack = (THStack *)BJfile->Get(tempname)->Clone();
  VJhist = (TH1D *) tempstack->GetStack()->Last();
  VJhist->SetFillColor(46);
  if(histname[ih]=="MHT" && rebin_MHT!=1) VJhist->Rebin(rebin_MHT);
  if(histname[ih]=="HT"  && rebin_HT!=1)  VJhist->Rebin(rebin_HT);
  finalstack->Add(VJhist);

  ///add TTbar to the finalstack
  sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname[ic].c_str(),histname[ih].c_str(),cutname[ic].c_str());
  tempstack = (THStack *)TTfile->Get(tempname)->Clone();
  TThist = (TH1D *) tempstack->GetStack()->Last();
  TThist->SetFillColor(8);
  if(histname[ih]=="MHT" && rebin_MHT!=1) TThist->Rebin(rebin_MHT);
  if(histname[ih]=="HT"  && rebin_HT!=1)  TThist->Rebin(rebin_HT);
  finalstack->Add(TThist);

  ///
  catLeg1->AddEntry(TThist,"t#bar{t}","f");
  catLeg1->AddEntry(VJhist,"V + jets","f");
//  catLeg1->AddEntry(Thist,"Single Top","f");
//  catLeg1->AddEntry(VVhist,"VV","f");
//  catLeg1->AddEntry(Otherhist,"Other BG","f");
  //

  ///Draw the background stack
  finalstack->Draw();
//  finalstack->SetMinimum(200.);
  //  finalstack->GetHistogram()->GetXaxis()->SetTitle("p_{T}(jet1) [GeV]");

  //
  if(histname[ih]=="NBtagLoose"){
    sprintf(xtitlename,"Number of b-tags");
    sprintf(ytitlename,"Events");
    finalstack->GetXaxis()->SetLimits(0., 10.);
    if (scale=="log"){
      gPad->SetLogy();
 //     finalstack->SetMaximum(1000.);    
      finalstack->SetMinimum(0.1);    
    }
  }
  //
  else if(histname[ih]=="NJet"){
    //gPad->SetLogy();
    sprintf(xtitlename,"Number of jets");
    sprintf(ytitlename,"Events");
    finalstack->GetXaxis()->SetLimits(0., 20.);
//    finalstack->SetMaximum(7.);
    if (cutname[ic]=="RA2noleptoncutht2500mht1300") finalstack->SetMaximum(100.);
  }
  //
  else if(histname[ih]=="MHT"){
    //gPad->SetLogy();
    sprintf(xtitlename,"#slash{H}_{T} (GeV)");
    sprintf(ytitlename,"Events / 100 GeV");
    finalstack->GetXaxis()->SetLimits(500., 3000.);
    if (scale=="log"){
      gPad->SetLogy();
 //     finalstack->SetMaximum(1000.);    
      finalstack->SetMinimum(0.3);    
    }
  }
  //
  else if(histname[ih]=="HT"){
    sprintf(xtitlename,"H_{T} (GeV)");
    sprintf(ytitlename,"Events / 200 GeV");
    finalstack->GetXaxis()->SetLimits(1000., 5000.);
    finalstack->GetXaxis()->SetNdivisions(505);
//    finalstack->SetMaximum(15.);
    if (scale=="log"){
      gPad->SetLogy();
 //     finalstack->SetMaximum(1000.);    
      finalstack->SetMinimum(0.3);    
    }
  }
  //
  else{
    sprintf(xtitlename,"%s",histname[ih].c_str());
    sprintf(ytitlename,"Events");
  }

  finalstack->GetHistogram()->GetXaxis()->SetTitle(xtitlename);
  finalstack->GetHistogram()->GetYaxis()->SetTitle(ytitlename);
  if(histname[ih]=="MHT"){
  }
  else if(histname[ih]=="HT"){
  }
  else{
  }
  //  c1->Modified();
 

  //Draw the signal on the same canvas
  sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname[ic].c_str(),histname[ih].c_str(),cutname[ic].c_str());

  tempstack = (THStack *) Sigfile->Get(tempname)->Clone();
  temphist = (TH1D *) tempstack->GetStack()->Last();
  temphist->SetLineColor(4);
  temphist->SetLineWidth(2);
  //temphist->SetLineStyle(2);
  temphist->SetFillStyle(0);
  if(histname[ih]=="MHT" && rebin_MHT!=1) temphist->Rebin(rebin_MHT);
  if(histname[ih]=="HT"  && rebin_HT!=1)  temphist->Rebin(rebin_HT);
  temphist->Draw("SAME");
//  std::cout << temphist->GetSumOfWeights() << std::endl;
  catLeg1->AddEntry(temphist,"Signal","l");

  gPad->RedrawAxis();

  //
  catLeg1->SetFillColor(kWhite);
  catLeg1->SetBorderSize(0);
  catLeg1->Draw();


  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //For official documents
  // writing the lumi information and the CMS "logo"
  //
/*
  {
    CMS_lumi_v2( c1, iPeriod, iPos );
  }
*/

  c1->Update();
  c1->RedrawAxis();
  c1->GetFrame()->Draw();
//  sprintf(tempname,"%s_%s.pdf",cutname[ic].c_str(), histname[ih].c_str());
//  c1->Print(tempname,".pdf");
//  sprintf(tempname,"%s_%s.png",cutname[ic].c_str(), histname[ih].c_str());
//  c1->Print(tempname,".png");

sprintf(tempname,"%s_%s",cutname[ic].c_str(), histname[ih].c_str());
c1->Write();
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}//end of loop over histname
}//end of loop over cutname
file->Close();
}

int main(){
drawPlot();
}
