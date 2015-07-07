#include <vector>
#include <cstdio>
#include <string> 

using namespace std;

/*

  Usage:

.x Plot_Commissioning.C("NJet")
.x Plot_Commissioning.C("NBtag")
.x Plot_Commissioning.C("HT")
.x Plot_Commissioning.C("MHT")

 */

//Plot_Commissioning(string histname="MHT",int choice=0){
Plot_Commissioning(string histname="MHT",int choice=0){

  ///////////////////////////////////////////////////////////////////////////////////////////
  ////Some cosmetic work for official documents.
  //
  // Set basic style
  //
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();
  gStyle->SetPalette(1) ; // for better color output
  gROOT->LoadMacro("CMS_lumi_v2.C");

  int W = 600;
  int H = 600;
  int H_ref = 600;
  int W_ref = 800;
  float T = 0.08*H_ref;
  float B = 0.12*H_ref;
  float L = 0.12*W_ref;
  float R = 0.08*W_ref;

  double xtext_top;
  double ymax_top;
  double ymin_top;
  double xmax;
  double xmin;
  
  ///////////////////////////////////////////////////////////////////////////////////////////
  //
  // More specific style set, opening input files etc

  gStyle->SetOptStat(0);  ///to avoid the stat. on the plots
  char tempname[200];
  char xtitlename[200];
  char ytitlename[200];


  TFile * PreTT = new TFile("HadTauEstimation_TTbar_.root","R");
  TFile * PreWJ12 = new TFile("HadTauEstimation_WJet_100_200_.root","R");
  TFile * PreWJ24 = new TFile("HadTauEstimation_WJet_200_400_.root","R");
  TFile * PreWJ46 = new TFile("HadTauEstimation_WJet_400_600_.root","R");
  TFile * PreWJ6I = new TFile("HadTauEstimation_WJet_600_inf_.root","R");
  TFile * ExpTT = new TFile("GenInfo_HadTauEstimation_TTbar_stacked.root","R");
  TFile * ExpWJ = new TFile("GenInfo_HadTauEstimation_WJet_stacked.root","R");

  //
  // Define legend
  //
  Float_t legendX1 = .40; //.50;
  Float_t legendX2 = .85; //.70;
  Float_t legendY1 = .65; //.65;
  Float_t legendY2 = .85;

  TLegend* catLeg1 = new TLegend(legendX1,legendY1,legendX2,legendY2);
  catLeg1->SetTextSize(0.032);
  catLeg1->SetTextFont(42);

  catLeg1->SetTextSize(0.042);
  catLeg1->SetTextFont(42);
  catLeg1->SetFillColor(0);
  catLeg1->SetLineColor(0);
  catLeg1->SetBorderSize(0);

  //
  // Define canvas
  //
  TCanvas *canvas = new TCanvas("canvas","canvas",10,10,W,H);

  canvas->SetFillColor(0);
  canvas->SetBorderMode(0);
  canvas->SetFrameFillStyle(0);
  canvas->SetFrameBorderMode(0);
  canvas->SetLeftMargin( L/W );
  canvas->SetRightMargin( R/W );
  canvas->SetRightMargin( 0.2 );
  canvas->SetTopMargin( T/H*3.0 );
  canvas->SetBottomMargin( B/H );
  canvas->SetTickx(0);
  canvas->SetTicky(0);

  canvas->Divide(1, 2);
  canvas_1->SetTopMargin(0.1);
  canvas_2->SetBottomMargin(1.8);

  //
  // Define pads
  //
  TPad* canvas_up = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_1");
  TPad* canvas_dw = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_2");
 
  // define the size
  double up_height     = 0.8;  // please tune so that the upper figures size will meet your requirement
  double dw_correction = 1.30; // please tune so that the smaller canvas size will work in your environment
  double font_size_dw  = 0.1;  // please tune the font size parameter for bottom figure
  double dw_height    = (1. - up_height) * dw_correction;
  double dw_height_offset = 0.040; // KH, added to put the bottom one closer to the top panel
 
  // set pad size
  canvas_up->SetPad(0., 1 - up_height, 0.97, 1.);
  canvas_dw->SetPad(0., dw_height_offset, 0.97, dw_height+dw_height_offset);
  canvas_up->SetFrameFillColor(0);
  canvas_up->SetFillColor(0);
  canvas_dw->SetFillColor(0);
  canvas_dw->SetFrameFillColor(0);
  canvas_dw->SetBottomMargin(0.30);
  
  // set top margin 0 for bottom figure
  canvas_dw->SetTopMargin(0);
  
  // draw top figure
  canvas_up->cd();

  TH1D * hExpTT, * hExpWJ, * hPreTT, * hPreWJ12, * hPreWJ24, * hPreWJ46, * hPreWJ6I;
  TH1D * histTemplate;
  THStack * tempstack, * ExpStack;
  ExpStack = new THStack("","");

  double HT_x_max=2500.;
  double HT_x_min=400.;
  double MHT_x_max=1000.;
  double NJet_x_max=15.;
  double NBtag_x_max=4.;
  double search_x_max=19.;
  double search_x_min=1.;

  sprintf(tempname,"allEvents/delphi/%s_delphi_allEvents",histname.c_str());
  tempstack=(THStack*)ExpTT->Get(tempname)->Clone();
  hExpTT=(TH1D*) tempstack->GetStack()->Last();
  tempstack=(THStack*)ExpWJ->Get(tempname)->Clone();   
  hExpWJ=(TH1D*) tempstack->GetStack()->Last();
  
  hPreTT  =(TH1D*) PreTT->Get(tempname)->Clone();
  hPreWJ12=(TH1D*) PreWJ12->Get(tempname)->Clone();
  hPreWJ24=(TH1D*) PreWJ24->Get(tempname)->Clone();
  hPreWJ46=(TH1D*) PreWJ46->Get(tempname)->Clone();
  hPreWJ6I=(TH1D*) PreWJ6I->Get(tempname)->Clone();

  TH1D * hPre = static_cast<TH1D*>(hPreTT->Clone("hPre"));
  
  hPreWJ6I->Add(hPreWJ46);
  hPreWJ6I->Add(hPreWJ24);
  hPreWJ6I->Add(hPreWJ12);
  hPre->Add(hPreWJ6I);
  hPre->SetMarkerSize(1.2);
  hPre->SetMarkerStyle(20);

  hExpTT->Scale(1/100.);
  hExpTT->SetFillColor(kRed);
  hExpWJ->Scale(1/100.);
  hExpWJ->SetFillColor(kBlue);
  
  TH1D * hExp = static_cast<TH1D*>(hExpTT->Clone("hExp"));
  hExp->Add(hExpWJ);

  ExpStack->Add(hExpTT);
  ExpStack->Add(hExpWJ);
  
  if(histname=="MHT"){
    xtext_top = 1800.;
    //y_legend  = 2000.;
    ymax_top = 300.;
    ymin_top = 0.015;
    xmax = 1000.;
    xmin = 100;
    sprintf(xtitlename,"#slash{H}_{T} (GeV)");
    sprintf(ytitlename,"Events / 50 GeV");
    gPad->SetLogy();
  }
  if(histname=="NBtag"){
    xtext_top = 1800.;
    //y_legend  = 2000.;
    ymax_top = 1000.;
    ymin_top = 0.15;
    xmax = 4.;
    xmin = 0;
    sprintf(xtitlename,"N_{b-tags}");
    sprintf(ytitlename,"Events");
    gPad->SetLogy();
  }
  if(histname=="NJet"){
    xtext_top = 1800.;
    //y_legend  = 2000.;
    ymax_top = 1000.;
    ymin_top = 0.15;
    xmax = 10.;
    xmin = 3;
    sprintf(xtitlename,"N_{jets}");
    sprintf(ytitlename,"Events");
    gPad->SetLogy();
  }

  // Actually draw plots
  
  hPre->GetXaxis()->SetTitleSize(0.06);
  hPre->GetXaxis()->SetTitleOffset(1.9);
  hPre->GetXaxis()->SetTitleFont(42);
  hPre->GetXaxis()->SetLabelSize(0.04);
  hPre->GetXaxis()->SetLabelOffset(1.9);
  //hPre->GetYaxis()->SetLabelFont(42);
  //hPre->GetYaxis()->SetLabelOffset(0.007);
  //hPre->GetYaxis()->SetLabelSize(0.04);
  hPre->GetYaxis()->SetTitleSize(0.06);
  hPre->GetYaxis()->SetTitleOffset(1.2);
  hPre->GetYaxis()->SetTitleFont(42);
  hPre->GetYaxis()->SetLabelSize(0.04);

  hPre->GetXaxis()->SetTitle(xtitlename);
  hPre->GetYaxis()->SetTitle(ytitlename);
  hPre->SetLineColor(1);
  hPre->SetMaximum(ymax_top);
  hPre->SetMinimum(ymin_top);
  hPre->GetXaxis()->SetRangeUser(xmin,xmax);
  hPre->SetTitle("");
  hPre->DrawCopy("e");
  
  ExpStack->Draw("same hist");

  hPre->DrawCopy("e same");

  sprintf(tempname,"#tau_{h} MC expectation from W + jets");
  catLeg1->AddEntry(hExpWJ,tempname,"f");  
  sprintf(tempname,"#tau_{h} MC expectation from t#bar{t}");
  catLeg1->AddEntry(hExpTT,tempname,"f");
  sprintf(tempname,"Prediction from #mu CS");
  catLeg1->AddEntry(hPre,tempname);
  catLeg1->Draw();

  TLatex * ttext = new TLatex(xmin, ymax_top*1.3,"CMS Preliminary, 0.1 fb^{-1}, #sqrt{s} = 13 TeV");
  ttext->SetTextFont(42);
  ttext->SetTextSize(0.050);
  ttext->SetTextAlign(11);
  ttext->Draw();

  /*
  GenHist->SetLineColor(2);
  EstHist->SetLineColor(4);
  //GenHist->GetXaxis()->SetLabelFont(42);
  //GenHist->GetXaxis()->SetLabelOffset(0.007);
  //GenHist->GetXaxis()->SetLabelSize(0.04);
  GenHist->GetXaxis()->SetTitleSize(0.05);
  GenHist->GetXaxis()->SetTitleOffset(0.9);
  GenHist->GetXaxis()->SetTitleFont(42);
  //GenHist->GetYaxis()->SetLabelFont(42);
  //GenHist->GetYaxis()->SetLabelOffset(0.007);
  //GenHist->GetYaxis()->SetLabelSize(0.04);
  GenHist->GetYaxis()->SetTitleSize(0.05);
  GenHist->GetYaxis()->SetTitleOffset(1.25);
  GenHist->GetYaxis()->SetTitleFont(42);

  //EstHist->GetXaxis()->SetLabelFont(42);
  //EstHist->GetXaxis()->SetLabelOffset(0.007);
  //EstHist->GetXaxis()->SetLabelSize(0.04);
  EstHist->GetXaxis()->SetTitleSize(0.05);
  EstHist->GetXaxis()->SetTitleOffset(0.9);
  EstHist->GetXaxis()->SetTitleFont(42);
  //EstHist->GetYaxis()->SetLabelFont(42);
  //EstHist->GetYaxis()->SetLabelOffset(0.007);
  //EstHist->GetYaxis()->SetLabelSize(0.04);
  EstHist->GetYaxis()->SetTitleSize(0.05);
  EstHist->GetYaxis()->SetTitleOffset(1.25);
  EstHist->GetYaxis()->SetTitleFont(42);
  sprintf(xtitlename,"search bins");
  sprintf(ytitlename,"Events");
  gPad->SetLogy();
  GenHist->SetMaximum(200000);
  GenHist->SetMinimum(0.1);
  GenHist->GetXaxis()->SetRangeUser(search_x_min,search_x_max);

  GenHist->SetFillStyle(3004);
  GenHist->SetFillColor(kGreen-3);
  GenHist->SetTitle("");
  GenHist->Draw("e2");
  //KH GenHist->Draw("same");
  EstHist->Draw("same");

  */

  //
  // Bottom ratio plot
  //
  // ----------

  if(choice==0){
      //KH -- flip the numerator and denominator
      TH1D * hPreOverExp = (TH1D*) hPre->Clone();
      hPreOverExp->Divide(hExp);
      hPre->Print("all");
      hPreTT->Print("all");
      hPreWJ12->Print("all");
      hPreWJ24->Print("all");
      hPreWJ46->Print("all");
      hPreWJ6I->Print("all");
      hExp->Print("all");
      hPreOverExp->Print("all");
      
      // draw bottom figure
      canvas_dw->cd();
      // font size
      hPreOverExp->GetXaxis()->SetLabelSize(font_size_dw);
      hPreOverExp->GetXaxis()->SetTitleSize(font_size_dw);
      hPreOverExp->GetYaxis()->SetLabelSize(font_size_dw);
      hPreOverExp->GetYaxis()->SetTitleSize(font_size_dw);
      
      //
      // Common to all bottom plots
      //
      sprintf(ytitlename,"#frac{Prediction}{Expectation}");
      hPreOverExp->GetYaxis()->SetTitle(ytitlename);
      hPreOverExp->SetMaximum(2.65);
      hPreOverExp->SetMinimum(0.0);

      //
      // Specific to each bottom plot
      //
      //sprintf(xtitlename,"search bin");
      hPreOverExp->GetXaxis()->SetRangeUser(xmin,xmax);
      TLine *tline = new TLine(xmin,1.,xmax,1.);

      // Setting style
      //hPreOverExp->SetMaximum(1.4);
      //hPreOverExp->GetXaxis()->SetLabelFont(42);
      hPreOverExp->GetXaxis()->SetLabelOffset(0.007);
      hPreOverExp->GetXaxis()->SetLabelSize(0.12);
      hPreOverExp->GetXaxis()->SetTitleSize(0.16);
      hPreOverExp->GetXaxis()->SetTitleOffset(0.80);
      hPreOverExp->GetXaxis()->SetTitleFont(42);
      //hPreOverExp->GetYaxis()->SetLabelFont(42);
      //hPreOverExp->GetYaxis()->SetLabelOffset(0.007);
      hPreOverExp->GetYaxis()->SetLabelSize(0.12);
      hPreOverExp->GetYaxis()->SetTitleSize(0.16);
      hPreOverExp->GetYaxis()->SetTitleOffset(0.4);
      hPreOverExp->GetYaxis()->SetTitleFont(42);
      hPreOverExp->GetXaxis()->SetTickSize(0.08);

      hPreOverExp->SetTitle("");
      hPreOverExp->Draw();
      tline->SetLineStyle(2);
      tline->Draw();
  }

  if(choice==1){

      TH1D * denominator = static_cast<TH1D*>(EstHist->Clone("denominator"));
      //EstHistD->Add(GenHistD,-1);
      denominator->Divide(GenHistD,EstHistD,1,1,"");

      // draw bottom figure
      canvas_dw->cd();
      // font size
      denominator->GetXaxis()->SetLabelSize(font_size_dw);
      denominator->GetXaxis()->SetTitleSize(font_size_dw);
      denominator->GetYaxis()->SetLabelSize(font_size_dw);
      denominator->GetYaxis()->SetTitleSize(font_size_dw);
      
      TLine *tline = new TLine(search_x_min,1.,search_x_max,1.);

      //
      // Common to all bottom plots
      //
      //sprintf(ytitlename,"#frac{Estimate - #tau_{had} BG}{#tau_{had} BG} ");
      sprintf(ytitlename,"#frac{Expectation}{Prediction} ");
      denominator->SetMaximum(2.65);
      denominator->SetMinimum(0.0);

      //
      // Specific to each bottom plot
      //
      // Setting style
      //denominator->SetMaximum(1.4);
      //denominator->GetXaxis()->SetLabelFont(42);
      //denominator->GetXaxis()->SetLabelOffset(0.007);
      //denominator->GetXaxis()->SetLabelSize(0.04);
      denominator->GetXaxis()->SetTitleSize(0.12);
      denominator->GetXaxis()->SetTitleOffset(0.9);
      denominator->GetXaxis()->SetTitleFont(42);
      //denominator->GetYaxis()->SetLabelFont(42);
      //denominator->GetYaxis()->SetLabelOffset(0.007);
      //denominator->GetYaxis()->SetLabelSize(0.04);
      denominator->GetYaxis()->SetTitleSize(0.13);
      denominator->GetYaxis()->SetTitleOffset(0.5);
      denominator->GetYaxis()->SetTitleFont(42);

      denominator->GetXaxis()->SetTitle(xtitlename);
      denominator->GetYaxis()->SetTitle(ytitlename);

      denominator->SetTitle("");
      denominator->Draw();
      tline->SetLineStyle(2);
      tline->Draw();
  }

  sprintf(tempname,"Commissioning_hadtau_%s_Plot.png",histname.c_str());
  canvas->Print(tempname);
  sprintf(tempname,"Commissioning_hadtau_%s_Plot.pdf",histname.c_str());
  canvas->Print(tempname);

}
