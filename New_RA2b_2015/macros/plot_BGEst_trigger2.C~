using namespace std;

void plot_BGEst_trigger2(string cutname="delphi", string histname="MHT"){

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
  
  
  TFile *file_NoTrig = new TFile("InputRootFiles/HadTauEstimation_data_SingleMuon_v14c_.root","R");
  TFile *file_Mu15 = new TFile("InputRootFiles/HadTauEstimation_data_SingleMuon_v14c_HLT_Mu15_IsoVVVL_PFHT350_PFMET70_v_.root","R"); 
  TFile *file_Mu50   = new TFile("InputRootFiles/HadTauEstimation_data_SingleMuon_v14c_HLT_Mu50_v_.root","R");
  TFile *file_Mu15ORMu50 = new TFile("InputRootFiles/HadTauEstimation_data_SingleMuon_v14c_HLT_Mu50_v_OR_HLT_Mu15_IsoVVVL_PFHT350_PFMET70_v_.root","R"); 
  
  // set colors
  int Mu15Color =1;
  int Mu50Color =2;
  int Mu15ORMu50Color =4;
  sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname.c_str(),histname.c_str(),cutname.c_str());
  TH1D * NoTrigHist = (TH1D*)file_NoTrig->Get(tempname)->Clone();
  NoTrigHist->SetLineColor(41);
  NoTrigHist->SetLineWidth(2);
  TH1D * Mu15Hist = (TH1D*)file_Mu15->Get(tempname)->Clone();
  Mu15Hist->SetLineColor(Mu15Color);
  Mu15Hist->SetLineWidth(2);
  TH1D * Mu50Hist = (TH1D*)file_Mu50->Get(tempname)->Clone();
  Mu50Hist->SetLineColor(Mu50Color);
  Mu50Hist->SetLineWidth(2);
  TH1D * Mu15ORMu50Hist = (TH1D*)file_Mu15ORMu50->Get(tempname)->Clone();
  Mu15ORMu50Hist->SetLineColor(Mu15ORMu50Color);
  Mu15ORMu50Hist->SetLineWidth(2);
  
  NoTrigHist->SetMaximum(10.);
  double MaxX = 1000.;
  if(histname=="MHT"){
	  NoTrigHist->SetMaximum(10.);
	  NoTrigHist->GetXaxis()->SetRangeUser(0.0,1000.);
	  MaxX = 1000.;
  }
   if(histname=="origMHT" || histname=="origMET"){
	   MaxX = 500.;
	   NoTrigHist->SetMaximum(10.);
	   NoTrigHist->GetXaxis()->SetRangeUser(0.0,MaxX);
  }
  if(histname=="HT" || histname=="origHT"){
	  MaxX = 1500.;
	  NoTrigHist->SetMaximum(10.);
	  NoTrigHist->GetXaxis()->SetRangeUser(0.0,MaxX);
  }
  if(histname=="NJet"){
	  NoTrigHist->SetMaximum(10.);
	  NoTrigHist->GetXaxis()->SetRangeUser(3.0,10.);
	  MaxX = 10.;
  }
  if(histname=="NBtag"){
	  NoTrigHist->SetMaximum(15.);
	  NoTrigHist->GetXaxis()->SetRangeUser(0.0,4.);
	  MaxX = 4.;
  }
  NoTrigHist->SetTitle("");
  NoTrigHist->GetXaxis()->SetLabelFont(42);
  NoTrigHist->GetXaxis()->SetLabelOffset(0.007);
  NoTrigHist->GetXaxis()->SetLabelSize(0.032);
  NoTrigHist->GetXaxis()->SetTitleSize(0.036);
  NoTrigHist->GetXaxis()->SetTitleOffset(0.9);
  NoTrigHist->GetXaxis()->SetTitleFont(42);
  NoTrigHist->GetYaxis()->SetLabelFont(42);
  NoTrigHist->GetYaxis()->SetLabelOffset(0.007);
  NoTrigHist->GetYaxis()->SetLabelSize(0.032);
  NoTrigHist->GetYaxis()->SetTitleSize(0.036);
  NoTrigHist->GetYaxis()->SetTitleOffset(1.25);
  NoTrigHist->GetYaxis()->SetTitleFont(42);
  sprintf(tempname,"%s",histname.c_str());
  NoTrigHist->GetXaxis()->SetTitle(tempname);
  NoTrigHist->GetYaxis()->SetTitle("#event");

  // draw bottom figure 
  canvas_dw->cd();
  TH1D * nulH = new TH1D("nulH","",1,0,MaxX);
  // X axis
  nulH->GetXaxis()->SetTitle(tempname);
  nulH->GetXaxis()->SetTitleSize(0.15);
  nulH->GetXaxis()->SetLabelSize(0.15);
  // Y axis 
  nulH->GetYaxis()->SetLabelSize(0.15);
  nulH->GetYaxis()->SetTitleSize(0.15);
  nulH->GetYaxis()->SetTitleFont(42);
  nulH->GetYaxis()->SetTitleOffset(0.3);
  nulH->GetYaxis()->SetTitle("Efficiency");
  // Draw
  nulH->Draw();
  
  // Real efficiency plot
  TEfficiency * effMu15 = new TEfficiency(*Mu15Hist,*NoTrigHist);
  effMu15->SetLineColor(Mu15Color);
  effMu15->Draw("same");
  TEfficiency * effMu50 = new TEfficiency(*Mu50Hist,*NoTrigHist);
  effMu50->SetLineColor(Mu50Color);
  effMu50->Draw("same");
  TEfficiency * effMu15ORMu50 = new TEfficiency(*Mu15ORMu50Hist,*NoTrigHist);
  effMu15ORMu50->SetLineColor(Mu15ORMu50Color);
  effMu15ORMu50->Draw("same");
  
  // draw top figure
  canvas_up->cd();

 
    catLeg1->SetHeader("Triggers:");
  
    NoTrigHist->Draw("same,hist");	
	sprintf(tempname,"(a): No Trigger");
    catLeg1->AddEntry(NoTrigHist,tempname,"l");

    Mu15Hist->Draw("same,hist");
    sprintf(tempname,"(b): HLT_Mu15_IsoVVVL_PFHT350_PFMET70_v");
    catLeg1->AddEntry(Mu15Hist,tempname,"l");
	
	Mu50Hist->Draw("same,hist");
	sprintf(tempname,"(c): HLT_Mu50_v");
	catLeg1->AddEntry(Mu50Hist,tempname,"l");
	
    Mu15ORMu50Hist->Draw("same,hist");
	sprintf(tempname,"(d): (b) or (c)");
	catLeg1->AddEntry(Mu15ORMu50Hist,tempname,"l");
  
  catLeg1->Draw();

  
  sprintf(tempname,"BGEstWithTriggers_%s_%s.png",cutname.c_str(),histname.c_str());
  canvas->Print(tempname);














 
}
