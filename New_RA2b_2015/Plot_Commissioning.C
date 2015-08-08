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
.x Plot_Commissioning.C("HT2")
.x Plot_Commissioning.C("MHT2")

Please note that the root files for the expectation code is 
expected to be normalized to 10/fb already. If not, the
lumi scaling needs to be adjusted in this room macro.
The following two lines should be adjusted.
  hExpTT->Scale(lumi/(10000));
  hExpWJ->Scale(lumi/(10000));

 */

Plot_Commissioning(string histname="MHT", string cutname="delphi", double lumi=43.1, bool normalize=false, int rebin=0){

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


  TFile * PreData = new TFile("HadTauEstimation_data_SingleMuon_08.root","R");
  //TFile * PreData = new TFile("HadTauEstimation_data_SingleMuon_08.root","R");
  //TFile * PreTT = new TFile("HadTauEstimation_TTbar_.root","R");
  //TFile * PreWJ12 = new TFile("HadTauEstimation_WJet_100_200_.root","R");
  //TFile * PreWJ24 = new TFile("HadTauEstimation_WJet_200_400_.root","R");
  //TFile * PreWJ46 = new TFile("HadTauEstimation_WJet_400_600_.root","R");
  //TFile * PreWJ6I = new TFile("HadTauEstimation_WJet_600_inf_.root","R");
  TFile * ExpTT = new TFile("GenInfo_HadTauEstimation_TTbar_stacked.root","R");
  TFile * ExpWJ = new TFile("GenInfo_HadTauEstimation_WJet_stacked.root","R");
  TFile * ExpT  = new TFile("GenInfo_HadTauEstimation_T_stacked.root","R");
  //TFile * ExpTT = new TFile("Elog265KHStack_GenInfo_HadTauEstimation_TTbar_stacked.root","R");
  //TFile * ExpWJ = new TFile("Elog265KHStack_GenInfo_HadTauEstimation_WJet_stacked.root","R");

  //
  // Define legend
  //
  Float_t legendX1 = .38; //.50;
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

  TH1D * hExpTT, * hExpWJ, * hPreTT, * hPreWJ12, * hPreWJ24, * hPreWJ46, * hPreWJ6I, hPreData;
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

  sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname.c_str(),histname.c_str(),cutname.c_str());
  
  hPreData  =(TH1D*) PreData->Get(tempname)->Clone();
  //hPreTT  =(TH1D*) PreTT->Get(tempname)->Clone();
  //hPreWJ12=(TH1D*) PreWJ12->Get(tempname)->Clone();
  //hPreWJ24=(TH1D*) PreWJ24->Get(tempname)->Clone();
  //hPreWJ46=(TH1D*) PreWJ46->Get(tempname)->Clone();
  //hPreWJ6I=(TH1D*) PreWJ6I->Get(tempname)->Clone();

  tempstack=(THStack*)ExpTT->Get(tempname)->Clone();
  hExpTT=(TH1D*) tempstack->GetStack()->Last();
  tempstack=(THStack*)ExpWJ->Get(tempname)->Clone();   
  hExpWJ=(TH1D*) tempstack->GetStack()->Last();
  tempstack=(THStack*)ExpT->Get(tempname)->Clone();   
  hExpT=(TH1D*) tempstack->GetStack()->Last();
  
  //TH1D * hPre = static_cast<TH1D*>(hPreTT->Clone("hPre"));
  TH1D * hPre = static_cast<TH1D*>(hPreData.Clone("hPre"));

  TH1D * hExp = static_cast<TH1D*>(hExpTT->Clone("hExp"));
  hExp->Add(hExpWJ);
  hExp->Add(hExpT);

  //hPre->Add(hPreWJ46);
  //hPre->Add(hPreWJ24);
  //hPre->Add(hPreWJ12);
  //hPre->Add(hPreWJ6I);
  hPre->SetMarkerSize(1.2);
  hPre->SetMarkerStyle(20);

  double scale = hPre->GetSumOfWeights()/hExp->GetSumOfWeights();
  printf("data prediction: %8.2f\n",hPre->GetSumOfWeights());
  printf("MC expectation:  %8.2f\n",hExp->GetSumOfWeights()*lumi/10000.);
  printf("scale to match exp to pre = %10.5f, and %10.5f from lumi info\n",
	 scale,lumi/(10000));
  
  //hExpTT->Scale(1/100.);
  if (normalize) hExpTT->Scale(scale);
  else           hExpTT->Scale(lumi/(10000));
  hExpTT->SetFillColor(kRed);

  //hExpWJ->Scale(1/100.);
  if (normalize) hExpWJ->Scale(scale);
  else           hExpWJ->Scale(lumi/(10000));
  hExpWJ->SetFillColor(kBlue);
  
  if (normalize) hExpT->Scale(scale);
  else           hExpT->Scale(lumi/(10000));

  TH1D * hExp = static_cast<TH1D*>(hExpTT->Clone("hExp"));
  hExp->Add(hExpWJ);
  hExp->Add(hExpT);

  if (rebin==1 && histname=="MHT"){
    Double_t mht_bins[13] = {
      //        0., 50.,100.,150.,200.,250.,300.,350.,400.,450.,
      //	500.,600.,1000.,5000.};
          0., 50.,100.,150.,200.,250.,300.,350.,400.,500.,
	700.,1000.,5000.};
    TH1D *hExpTT_Rebin = hExpTT->Rebin(12,"hExpTT_Rebin",mht_bins);
    TH1D *hExpWJ_Rebin = hExpWJ->Rebin(12,"hExpWJ_Rebin",mht_bins);
    TH1D *hPre_Rebin   = hPre->Rebin(12,"hPre_Rebin",mht_bins);
    TH1D *hExp_Rebin   = hExp->Rebin(12,"hExp_Rebin",mht_bins);
    hPre_Rebin->Print("all");
    hExp_Rebin->Print("all");
    hExp_Rebin->SetBinContent(11,hExp->GetBinContent(11)+hExp->GetBinContent(12));
    hExp_Rebin->SetBinError(11,hExp->GetBinError(11)+hExp->GetBinError(12));
    hExp_Rebin->SetBinContent(12,hExp->GetBinContent(13)+hExp->GetBinContent(14)
				+hExp->GetBinContent(15)+hExp->GetBinContent(16));
    hExp_Rebin->SetBinError(12,hExp->GetBinError(13)+hExp->GetBinError(14)
				+hExp->GetBinError(15)+hExp->GetBinError(16));
    hPre_Rebin->SetBinContent(11,hPre->GetBinContent(11)+hPre->GetBinContent(12));
    hPre_Rebin->SetBinError(11,hPre->GetBinError(11)+hPre->GetBinError(12));
    hPre_Rebin->SetBinContent(12,hPre->GetBinContent(13)+hPre->GetBinContent(14)
				+hPre->GetBinContent(15)+hPre->GetBinContent(16));
    hPre_Rebin->SetBinError(12,hPre->GetBinError(13)+hPre->GetBinError(14)
				+hPre->GetBinError(15)+hPre->GetBinError(16));
    hPre_Rebin->Print("all");
    hExp_Rebin->Print("all");
    hPre   = hPre_Rebin;
    hExp   = hExp_Rebin;
    hExpTT = hExpTT_Rebin;
    hExpWJ = hExpWJ_Rebin;
  }
  
  ExpStack->Add(hExpT);
  ExpStack->Add(hExpTT);
  ExpStack->Add(hExpWJ);

  if(histname=="MHT"){
    xtext_top = 1800.;
    //y_legend  = 2000.;
    ymax_top = 300.;
    ymin_top = 0.15;
    xmax = 700.;
    xmin = 100;
    sprintf(xtitlename,"#slash{H}_{T} (GeV)");
    sprintf(ytitlename,"Events");
    gPad->SetLogy();
  }
  if(histname=="MHT2"){
    //xtext_top = 1800.;
    //xtext_top = 1800.;
    //y_legend  = 2000.;
    ymax_top = 200.;
    ymin_top = 0.1;
    //xmax = 1000.;
    xmax = 700.;
    //xmax = 500.;
    xmin = 150;
    sprintf(xtitlename,"#slash{H}_{T} (GeV)");
    sprintf(ytitlename,"Events");
    gPad->SetLogy();
  }
  if(histname=="HT"){
    xtext_top = 1800.;
    //y_legend  = 2000.;
    ymax_top = 300.;
    ymin_top = 0.15;
    xmax = 1500.;
    xmin = 400;
    sprintf(xtitlename,"H_{T} (GeV)");
    sprintf(ytitlename,"Events");
    gPad->SetLogy();
  }
  if(histname=="HT2"){
    xtext_top = 1800.;
    //y_legend  = 2000.;
    ymax_top = 300.;
    ymin_top = 0.15;
    //xmax = 2000.;
    //xmax = 1500.;
    xmax = 1200.;
    xmin = 400;
    sprintf(xtitlename,"H_{T} (GeV)");
    sprintf(ytitlename,"Events");
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
    ymin_top = 0.10;
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
  sprintf(tempname,"#tau_{h} MC expectation from single top");
  catLeg1->AddEntry(hExpT,tempname,"f");
  sprintf(tempname,"Prediction from #mu CS");
  catLeg1->AddEntry(hPre,tempname);
  catLeg1->Draw();

  sprintf(tempname,"CMS Preliminary, %.1f pb^{-1}, #sqrt{s} = 13 TeV",lumi);
  TLatex * ttext = new TLatex(xmin, ymax_top*1.3,tempname);
  ttext->SetTextFont(42);
  ttext->SetTextSize(0.050);
  ttext->SetTextAlign(11);
  ttext->Draw();

  //
  // Bottom ratio plot
  //
  // ----------

  //KH -- flip the numerator and denominator
  TH1D * hPreOverExp = (TH1D*) hPre->Clone();
  hPreOverExp->Divide(hExp);
  /*
    hPre->Print("all");
    hPreTT->Print("all");
    hPreWJ12->Print("all");
    hPreWJ24->Print("all");
    hPreWJ46->Print("all");
    hPreWJ6I->Print("all");
    hExp->Print("all");
  */
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

  if (normalize) sprintf(tempname,"Commissioning_hadtau_%s_%s_normalize_Plot.png",histname.c_str(),cutname.c_str());
  else           sprintf(tempname,"Commissioning_hadtau_%s_%s_Plot.png",histname.c_str(),cutname.c_str());
  canvas->Print(tempname);
  if (normalize) sprintf(tempname,"Commissioning_hadtau_%s_%s_normalize_Plot.pdf",histname.c_str(),cutname.c_str());
  else           sprintf(tempname,"Commissioning_hadtau_%s_%s_Plot.pdf",histname.c_str(),cutname.c_str());
  canvas->Print(tempname);
  
}
