#include <cstdio>
using namespace std;

void plot_BGEst_trigger_individual123(string cutname="delphi", string histname="NJet"){

  ///////////////////////////////////////////////////////////////////////////////////////////
  ////Some cosmetic work for official documents. 
  gStyle->SetOptStat(0);  ///to avoid the stat. on the plots 
//  gROOT->LoadMacro("tdrstyle.C");
//  setTDRStyle();
//  gROOT->LoadMacro("CMS_lumi_v2.C");
  gStyle->SetPalette(1) ; // for better color output

  char tempname[200];
  char tempname2[200];
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

  canvas->Divide(1, 2);
  //
  // Define pads
  //
  TPad* canvas_up = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_1");
  TPad* canvas_dw = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_2");
 
  // define the size
  double up_height     = 0.8;  // please tune so that the upper figures size will meet your requirement
  double dw_correction = 1.30; // please tune so that the smaller canvas size will work in your environment
  double font_size_dw  = 0.15;  // please tune the font size parameter for bottom figure
  double dw_height    = (1. - up_height) * dw_correction;
  double dw_height_offset = - 0.04; // KH, added to put the bottom one closer to the top panel
  double x_min=0.0, x_max=.97;
  // set pad size
  canvas_up->SetPad(0., .25, 0.97, 1.);

  canvas_dw->SetPad(0., 0.07, 0.97, 0.25);
  canvas_up->SetFrameFillColor(0);
  canvas_up->SetFillColor(0);
  canvas_dw->SetFillColor(0);
  canvas_dw->SetFrameFillColor(0);
  canvas_dw->SetBottomMargin(0.3);
  // set top margin 0 for bottom figure
  canvas_dw->SetTopMargin(0);
 
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
  
  //string input="data_SingleMuon_v14g";
  //string input="TTbar";
  string input="data_HTMHT_v14g";
 
  sprintf(tempname,"InputRootFiles/HadTauEstimation_%s_NoTrig_.root",input.c_str());
  TFile *file_NoTrig = new TFile(tempname,"R");
  sprintf(tempname,"InputRootFiles/HadTauEstimation_%s_trig1_.root",input.c_str());
  TFile *file_trig1 = new TFile(tempname,"R");
  sprintf(tempname,"InputRootFiles/HadTauEstimation_%s_trig2_.root",input.c_str());
  TFile *file_trig2 = new TFile(tempname,"R"); 
  sprintf(tempname,"InputRootFiles/HadTauEstimation_%s_trig3_.root",input.c_str());
  TFile *file_trig3   = new TFile(tempname,"R");

  
  // set colors
  int Color1 =4;
  int Color2 =1;
  int Color3 =2;
  int Color1_5 =6;
  int Color1_8 =7;
  sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname.c_str(),histname.c_str(),cutname.c_str());
  TH1D * NoTrigHist = (TH1D*)file_NoTrig->Get(tempname)->Clone();
  NoTrigHist->SetLineColor(41);
  NoTrigHist->SetLineWidth(2);
  TH1D * Hist1 = (TH1D*)file_trig1->Get(tempname)->Clone();
  Hist1->SetLineColor(4);
  Hist1->SetLineWidth(2);
  TH1D * Hist2 = (TH1D*)file_trig2->Get(tempname)->Clone();
  Hist2->SetLineColor(Color2);
  Hist2->SetLineWidth(2);
  Hist2->SetLineStyle(2);
  TH1D * Hist3 = (TH1D*)file_trig3->Get(tempname)->Clone();
  Hist3->SetLineColor(Color3);
  Hist3->SetLineWidth(2);
  Hist3->SetLineStyle(3);
  /*
  TH1D * Hist1_5 = (TH1D*)file_1_5->Get(tempname)->Clone();
  Hist1_5->SetLineColor(Color1_5);
  Hist1_5->SetLineWidth(2);
  Hist1_5->SetLineStyle(4);
  TH1D * Hist1_8 = (TH1D*)file_1_8->Get(tempname)->Clone();
  Hist1_8->SetLineColor(Color1_8);
  Hist1_8->SetLineWidth(2);
  Hist1_8->SetLineStyle(5);
  */
  
  Hist1->SetMaximum(10.);
  double MaxX = 1000.;
  if(histname=="MHT"){
	  if(input=="TTbar")Hist1->SetMaximum(2000.);
	  if(input=="data_SingleMuon_v14g")Hist1->SetMaximum(10.);
	  Hist1->GetXaxis()->SetRangeUser(0.0,1000.);
	  MaxX = 1000.;
  }
   if(histname=="origMHT" || histname=="origMET"){
	   MaxX = 500.;
	   if(input=="TTbar")Hist1->SetMaximum(2000.);
	   if(input=="data_SingleMuon_v14g")Hist1->SetMaximum(10.);
	   Hist1->GetXaxis()->SetRangeUser(0.0,MaxX);
  }
  if(histname=="HT" || histname=="origHT"){
	  MaxX = 1500.;
	  if(input=="data_SingleMuon_v14g")Hist1->SetMaximum(10.);
	  if(input=="TTbar")Hist1->SetMaximum(2000.);
	  Hist1->GetXaxis()->SetRangeUser(0.0,MaxX);
  }
  if(histname=="NJet"){
	  if(input=="data_SingleMuon_v14g")Hist1->SetMaximum(10.);
	  if(input=="TTbar")Hist1->SetMaximum(1500.);
	  Hist1->GetXaxis()->SetRangeUser(3.0,10.);
	  MaxX = 10.;
  }
  if(histname=="NBtag"){
	  if(input=="data_SingleMuon_v14g")Hist1->SetMaximum(15.);
	  if(input=="TTbar")Hist1->SetMaximum(2500.);
	  Hist1->GetXaxis()->SetRangeUser(0.0,4.);
	  MaxX = 4.;
  }
  Hist1->SetTitle("");
  Hist1->GetXaxis()->SetLabelFont(42);
  Hist1->GetXaxis()->SetLabelOffset(0.007);
  Hist1->GetXaxis()->SetLabelSize(0.032);
  Hist1->GetXaxis()->SetTitleSize(0.036);
  Hist1->GetXaxis()->SetTitleOffset(0.9);
  Hist1->GetXaxis()->SetTitleFont(42);
  Hist1->GetYaxis()->SetLabelFont(42);
  Hist1->GetYaxis()->SetLabelOffset(0.007);
  Hist1->GetYaxis()->SetLabelSize(0.032);
  Hist1->GetYaxis()->SetTitleSize(0.036);
  Hist1->GetYaxis()->SetTitleOffset(1.25);
  Hist1->GetYaxis()->SetTitleFont(42);
  sprintf(tempname,"%s",histname.c_str());
  Hist1->GetXaxis()->SetTitle(tempname);
  Hist1->GetYaxis()->SetTitle("#event");

  // draw bottom figure 
  canvas_dw->cd();
  TH1D * nulH = new TH1D("nulH","",1,0,MaxX);
  // X axis
  nulH->GetXaxis()->SetTitle(tempname);
  nulH->GetXaxis()->SetTitleSize(0.15);
  nulH->GetXaxis()->SetLabelSize(0.15);
  // Y axis 
  nulH->GetYaxis()->SetLabelSize(0.15);
  nulH->GetYaxis()->SetRangeUser(0.1,1.05);
  nulH->GetYaxis()->SetTitleSize(0.15);
  nulH->GetYaxis()->SetTitleFont(42);
  nulH->GetYaxis()->SetTitleOffset(0.3);
  nulH->GetYaxis()->SetTitle("WRT PD   ");
  nulH->GetYaxis()->SetNdivisions(5,kTRUE);
  // Draw
  nulH->Draw();
  
  // Real efficiency plot
  TEfficiency * eff1_2 = new TEfficiency(*Hist1,*NoTrigHist);
  eff1_2->SetLineColor(Color1);
  eff1_2->Draw("same");
  TEfficiency * eff1_2 = new TEfficiency(*Hist2,*NoTrigHist);
  eff1_2->SetLineColor(Color2);
  eff1_2->Draw("same");
  TEfficiency * eff1_3 = new TEfficiency(*Hist3,*NoTrigHist);
  eff1_3->SetLineColor(Color3);
  eff1_3->Draw("same");
  /*
  TEfficiency * eff1_5 = new TEfficiency(*Hist1_5,*Hist1);
  eff1_5->SetLineColor(Color1_5);
  eff1_5->Draw("same");
  TEfficiency * eff1_8 = new TEfficiency(*Hist1_8,*Hist1);
  eff1_8->SetLineColor(Color1_8);
  eff1_8->Draw("same");
  */
  
  // draw top figure
  canvas_up->cd();

 
    catLeg1->SetHeader("Triggers:");
  
    Hist1->Draw("same,hist");	
	sprintf(tempname,"1");
    catLeg1->AddEntry(Hist1,tempname,"l");

    Hist2->Draw("same,hist");
    sprintf(tempname,"2");
    catLeg1->AddEntry(Hist2,tempname,"l");
	
	Hist3->Draw("same,hist");
	sprintf(tempname,"3");
	catLeg1->AddEntry(Hist3,tempname,"l");
	
	NoTrigHist->Draw("same,hist");
	if(input=="data_SingleMuon_v14g")sprintf(tempname,"Single Muon PD");
	if(input=="data_HTMHT_v14g")sprintf(tempname,"HTMHT PD");
	if(input=="TTbar")sprintf(tempname,"TTbar MC");
	catLeg1->AddEntry(NoTrigHist,tempname,"l");
	
/*	
    Hist1_5->Draw("same,hist");
	sprintf(tempname,"1_5");
	catLeg1->AddEntry(Hist1_5,tempname,"l");
	
	Hist1_8->Draw("same,hist");
	sprintf(tempname,"1_8");
	catLeg1->AddEntry(Hist1_8,tempname,"l");
	*/
  
  catLeg1->Draw();

  sprintf(tempname,"%s_BGEstWithTriggers_%s_%s.png",input.c_str(),cutname.c_str(),histname.c_str());
  canvas->Print(tempname);














 
}
