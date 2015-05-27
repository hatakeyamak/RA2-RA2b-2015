#include <TH1D.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TList.h>
#include <TStyle.h>
#include <vector>
#include <cstdio>

using namespace std;


Plot2(string cutname="nocut", string histname="MHT",string sample="TTbar_",int choice=0){

  //
  ///////////////////////////////////////////////////////////////////////////////////////////
  ////Some cosmetic work for official documents. 
  //
  // Set basic style
  //
//  gROOT->LoadMacro("tdrstyle.C");
//  setTDRStyle();
//  gROOT->LoadMacro("CMS_lumi_v2.C");

  int W = 600;
  int H = 600;
  int H_ref = 600;
  int W_ref = 800;
  float T = 0.08*H_ref;
  float B = 0.12*H_ref;
  float L = 0.12*W_ref;
  float R = 0.08*W_ref;

  ///////////////////////////////////////////////////////////////////////////////////////////
  //
  // More specific style set, opening input files etc
  //

  gStyle->SetOptStat(0);  ///to avoid the stat. on the plots 
  char tempname[200];
  char xtitlename[200];
  char ytitlename[200];
  
  vector<TFile *> filevec;
  
    
  sprintf(tempname,"TauHad/GenInfo_HadTauEstimation_%s.root",sample.c_str());
  filevec.push_back(TFile::Open(tempname,"R"));
  sprintf(tempname,"TauHad2/HadTauEstimation_%s.root",sample.c_str());
  // sprintf(tempname,"TauHad2/Storage/HadTauEstimation_TTbar_Feb_17_2015.root");
  filevec.push_back(TFile::Open(tempname,"R"));

  //
  // Define legend
  //
  Float_t legendX1 = .60; //.50;
  Float_t legendX2 = .90; //.70;
  Float_t legendY1 = .60; //.65;
  Float_t legendY2 = .80;

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
  canvas_dw->SetBottomMargin(0.25);
  
  // set top margin 0 for bottom figure
  canvas_dw->SetTopMargin(0);
  
  // draw top figure
  canvas_up->cd();

  THStack * tempstack;
  TH1D * GenHist, * EstHist,* thist;
  TH1D * histTemplate;

  double HT_x_max=2500.;
  double HT_x_min=400.;
  double MHT_x_max=1000.;
  double NJet_x_max=15.;
  double NBtag_x_max=4.;
  double search_x_max=19.;
  double search_x_min=0.;

  
  for(int i=0; i<filevec.size(); i++){

if(sample.find("stacked")!=string::npos){

    if(i==0){
      sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname.c_str(),histname.c_str(),cutname.c_str());
      tempstack = (THStack*)filevec.at(i)->Get(tempname)->Clone();
      GenHist=(TH1D*) tempstack->GetStack()->Last();
    }
    if(i==1){
      sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname.c_str(),histname.c_str(),cutname.c_str());
      tempstack = (THStack*)filevec.at(i)->Get(tempname)->Clone();
      EstHist=(TH1D*) tempstack->GetStack()->Last();
    }
    tempstack = (THStack*)filevec.at(i)->Get(tempname)->Clone();
    thist=(TH1D*) tempstack->GetStack()->Last();
    thist->SetLineColor(2*i+2);
    thist->SetFillColor(0);

}
else{

    if(i==0){
      if(histname=="search"){
        sprintf(tempname,"searchH");
        GenHist=(TH1D*) filevec.at(i)->Get(tempname)->Clone();
      }
      else{
        sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname.c_str(),histname.c_str(),cutname.c_str());
        GenHist=(TH1D*) filevec.at(i)->Get(tempname)->Clone();
      }
    }
    if(i==1){
//      if(histname=="NBtag")sprintf(tempname,"allEvents/%s/nB_new_%s_allEvents",cutname.c_str(),cutname.c_str());
//      else sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname.c_str(),histname.c_str(),cutname.c_str());
      if(histname=="search"){
        sprintf(tempname,"searchH");
        EstHist=(TH1D*) filevec.at(i)->Get(tempname)->Clone();
      }
      else{
        sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname.c_str(),histname.c_str(),cutname.c_str());
        EstHist=(TH1D*) filevec.at(i)->Get(tempname)->Clone();
      }
    }
//    thist=(TH1D*) filevec.at(i)->Get(tempname)->Clone();
    thist=static_cast<TH1D*>(filevec.at(i)->Get(tempname)->Clone());
    thist->SetLineColor(2*i+2);

}
    // Setting style
    if(i==0){
      thist->SetMaximum(1.4);
      //thist->GetXaxis()->SetLabelFont(42);
      //thist->GetXaxis()->SetLabelOffset(0.007);
      //thist->GetXaxis()->SetLabelSize(0.04);
      thist->GetXaxis()->SetTitleSize(0.05);
      thist->GetXaxis()->SetTitleOffset(0.9);
      thist->GetXaxis()->SetTitleFont(42);
      //thist->GetYaxis()->SetLabelFont(42);
      //thist->GetYaxis()->SetLabelOffset(0.007);
      //thist->GetYaxis()->SetLabelSize(0.04);
      thist->GetYaxis()->SetTitleSize(0.05);
      thist->GetYaxis()->SetTitleOffset(1.0);
      thist->GetYaxis()->SetTitleFont(42);
    }
    if(histname=="search"){
      sprintf(xtitlename,"search bins");
      sprintf(ytitlename,"Events");
      thist->SetMaximum(2000);
      thist->SetMinimum(0.);
      thist->GetXaxis()->SetRangeUser(search_x_min,search_x_max);
    }
    if(histname=="HT"){
      sprintf(xtitlename,"H_{T} (GeV)");
      sprintf(ytitlename,"Events / 200 GeV");
      thist->SetMaximum(50000);
//      thist->SetMinimum(0.0001);
      thist->GetXaxis()->SetRangeUser(HT_x_min,HT_x_max);
      gPad->SetLogy();
      //thist->GetXaxis()->SetLimits(0.,HT_x_max);
    }
    if(histname=="MHT"){
      sprintf(xtitlename,"#slash{H}_{T} (GeV)");
      sprintf(ytitlename,"Events / 100 GeV");
      thist->SetMaximum(50000);
      thist->GetXaxis()->SetRangeUser(0.,MHT_x_max);
      gPad->SetLogy();
      //thist->GetXaxis()->SetLimits(0.,MHT_x_max);
    } 
    
    if(histname=="NBtag"){
      sprintf(xtitlename,"Number of b-tags");
      sprintf(ytitlename,"Events");
      thist->SetMaximum(10000);
      thist->GetXaxis()->SetRangeUser(0.,NBtag_x_max);
    }
    
    if(histname=="NJet"){
      sprintf(xtitlename,"Number of jets");
      sprintf(ytitlename,"Events");
      thist->SetMaximum(10000);
      thist->SetMinimum(1);
      thist->GetXaxis()->SetRangeUser(0.,NJet_x_max);
      gPad->SetLogy();
    }
    if(i==0){
//      thist->Draw();
      thist->SetFillStyle(3004);
      thist->SetFillColor(kGreen-3);
      thist->Draw("same e2");
      
    }
    else{
      thist->Draw("same ");
    }
    if(i==0){
      sprintf(tempname,"#tau_{hadronic} BG");
      catLeg1->AddEntry(thist,tempname,"f");
    }
    if(i==1){
      sprintf(tempname,"Data driven estimate");
      catLeg1->AddEntry(thist,tempname,"l");
    }
    thist->GetXaxis()->SetTitle(xtitlename);
    thist->GetYaxis()->SetTitle(ytitlename);
  }
  catLeg1->Draw();

  //
  // Bottom ratio plot
  //
  // ----------

  if(choice==0){
    /*  for(int j=0; j<=10; j++){
      printf("j: %d EstHist: %g GenHist: %g \n ",j,EstHist->GetBinContent(j),GenHist->GetBinContent(j) );
      }*/
      //KH -- flip the numerator and denominator
      EstHist->Divide(GenHist);
      //GenHist->Divide(EstHist);

    /*  for(int j=0; j<=10; j++){
      printf("j: %d Divide: %g \n ",j,EstHist->GetBinContent(j) );
      }
    */

      // draw bottom figure
      canvas_dw->cd();
      // font size
      EstHist->GetXaxis()->SetLabelSize(font_size_dw);
      EstHist->GetXaxis()->SetTitleSize(font_size_dw);
      EstHist->GetYaxis()->SetLabelSize(font_size_dw);
      EstHist->GetYaxis()->SetTitleSize(font_size_dw);
      
      //
      // Common to all bottom plots
      //
      sprintf(ytitlename,"Estimate / #tau_{had} BG");
      EstHist->SetMaximum(2.65);
      EstHist->SetMinimum(0.0);

      //
      // Specific to each bottom plot
      //
      if(histname=="search"){
        sprintf(xtitlename,"search bin");
        EstHist->GetXaxis()->SetRangeUser(search_x_min,search_x_max);
        TLine *tline = new TLine(search_x_min,1.,search_x_max,1.);
      }
      if(histname=="HT"){
        sprintf(xtitlename,"H_{T} (GeV)");
        EstHist->GetXaxis()->SetRangeUser(HT_x_min,HT_x_max);
        TLine *tline = new TLine(HT_x_min,1.,HT_x_max,1.);
      }
      if(histname=="MHT"){
        sprintf(xtitlename,"#slash{H}_{T} (GeV)");
        EstHist->GetXaxis()->SetRangeUser(0.,MHT_x_max);
        TLine *tline = new TLine(0.,1.,MHT_x_max,1.);
      }   
      if(histname=="NBtag"){
        sprintf(xtitlename,"Number of b-tags");
        EstHist->GetXaxis()->SetRangeUser(0.,NBtag_x_max);
        TLine *tline = new TLine(0.,1.,NBtag_x_max,1.);
      }    
      if(histname=="NJet"){
        sprintf(xtitlename,"Number of jets");
        EstHist->GetXaxis()->SetRangeUser(0.,NJet_x_max);
        TLine *tline = new TLine(0.,1.,NJet_x_max,1.);
      }

      // Setting style
      //EstHist->SetMaximum(1.4);
      //EstHist->GetXaxis()->SetLabelFont(42);
      //EstHist->GetXaxis()->SetLabelOffset(0.007);
      //EstHist->GetXaxis()->SetLabelSize(0.04);
      EstHist->GetXaxis()->SetTitleSize(0.12);
      EstHist->GetXaxis()->SetTitleOffset(0.9);
      EstHist->GetXaxis()->SetTitleFont(42);
      //EstHist->GetYaxis()->SetLabelFont(42);
      //EstHist->GetYaxis()->SetLabelOffset(0.007);
      //EstHist->GetYaxis()->SetLabelSize(0.04);
      EstHist->GetYaxis()->SetTitleSize(0.13);
      EstHist->GetYaxis()->SetTitleOffset(0.3);
      EstHist->GetYaxis()->SetTitleFont(42);

      EstHist->GetXaxis()->SetTitle(xtitlename);
      EstHist->GetYaxis()->SetTitle(ytitlename);

      EstHist->Draw();
      tline->SetLineStyle(2);
      tline->Draw();
  }

  if(choice==1){

      TH1D * denominator = static_cast<TH1D*>(EstHist->Clone("denominator"));
      EstHist->Add(GenHist,-1);
      denominator->Divide(EstHist,GenHist,1,1,"");
    
      // draw bottom figure
      canvas_dw->cd();
      // font size
      denominator->GetXaxis()->SetLabelSize(font_size_dw);
      denominator->GetXaxis()->SetTitleSize(font_size_dw);
      denominator->GetYaxis()->SetLabelSize(font_size_dw);
      denominator->GetYaxis()->SetTitleSize(font_size_dw);
      
      //
      // Common to all bottom plots
      //
//      sprintf(ytitlename,"#frac{Estimate - #tau_{had} BG}{#tau_{had} BG} ");
      sprintf(ytitlename,"#frac{Sim. - Pred.}{Pred.} ");
      denominator->SetMaximum(5);
      denominator->SetMinimum(-5);

      //
      // Specific to each bottom plot
      //
      if(histname=="HT"){
        sprintf(xtitlename,"H_{T} (GeV)");
        denominator->GetXaxis()->SetRangeUser(HT_x_min,HT_x_max);
        TLine *tline = new TLine(HT_x_min,-.1,HT_x_max,.1);
      }
      if(histname=="MHT"){
        sprintf(xtitlename,"#slash{H}_{T} (GeV)");
        denominator->GetXaxis()->SetRangeUser(0.,MHT_x_max);
        TLine *tline = new TLine(0.,-.1,MHT_x_max,.1);
      }   
      if(histname=="NBtag"){
        sprintf(xtitlename,"Number of b-tags");
        denominator->GetXaxis()->SetRangeUser(0.,NBtag_x_max);
        TLine *tline = new TLine(0.,-.1,NBtag_x_max,.1);
      }    
      if(histname=="NJet"){
        sprintf(xtitlename,"Number of jets");
        denominator->GetXaxis()->SetRangeUser(0.,NJet_x_max);
        TLine *tline = new TLine(0.,-.1,NJet_x_max,.1);
      }

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
//      denominator->GetYaxis()->SetTitleOffset(0.2);
      denominator->GetYaxis()->SetTitleFont(42);

      denominator->GetXaxis()->SetTitle(xtitlename);
      denominator->GetYaxis()->SetTitle(ytitlename);

      denominator->Draw();
      tline->SetLineStyle(2);
      tline->Draw();
  }


  sprintf(tempname,"%s_%s_%s_Plot.png",sample.c_str(),cutname.c_str(),histname.c_str());
  canvas->Print(tempname);

}
