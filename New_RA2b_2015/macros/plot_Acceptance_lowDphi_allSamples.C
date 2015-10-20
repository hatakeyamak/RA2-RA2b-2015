void plot_Acceptance_lowDphi_allSamples(){

  //
  ///////////////////////////////////////////////////////////////////////////////////////////
  ////Some cosmetic work for official documents. 
  gStyle->SetOptStat(0);   ///to avoid the stat. on the plots 
  gStyle->SetLineWidth(2); // Default:1 --- Line width of axis.
  gROOT->LoadMacro("tdrstyle.C");  
  //setTDRStyle();
  //gROOT->LoadMacro("CMS_lumi_v2.C");

  char tempname[200];
  char tempname2[200];
  int W = 800;
  int H = 600;
  int H_ref = 600;
  int W_ref = 800;
  float T = 0.08*H_ref;
  float B = 0.12*H_ref;
  float L = 0.12*W_ref;
  float R = 0.04*W_ref;

  TCanvas* c1 = new TCanvas("name","name",10,10,W,H);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin( L/W );
  c1->SetRightMargin( R/W );
  c1->SetTopMargin( T/H );
  c1->SetBottomMargin( B/H );
  c1->SetTickx(1);
  c1->SetTicky(1);
  
  Float_t legendX1 = .60; //.50;
  Float_t legendX2 = .90; //.70;
  Float_t legendY1 = .70; //.65;
  Float_t legendY2 = .82;
  TLegend* catLeg1 = new TLegend(legendX1,legendY1,legendX2,legendY2);
  catLeg1->SetTextSize(0.042);
  catLeg1->SetTextFont(42);
  catLeg1->SetFillColor(0);
  catLeg1->SetLineColor(0);
  catLeg1->SetBorderSize(0);

  sprintf(tempname,"TauHad/Stack/LostLepton2_MuonEfficienciesFromTTbar_stacked.root");
  TFile *file_TTbar   = new TFile(tempname,"R");
  sprintf(tempname,"TauHad/Stack/LostLepton2_MuonEfficienciesFromWJet_stacked.root");
  TFile *file_WJet   = new TFile(tempname,"R");
  sprintf(tempname,"TauHad/Stack/LostLepton2_MuonEfficienciesFromstacked.root");
  TFile *file_total   = new TFile(tempname,"R");
  


  TH1D * thist, * thist2 , *thist3;
  THStack * tempstack;
  //  catLeg1->SetHeader("Prob. of #mu from #tau ");


  //...........................................................................//
  // TTbar ....................................................................//
  //...........................................................................//
  double XUp = 10., maxVal=1.5, minVal=0.2;

  sprintf(tempname,"hAcc_lowDphi");
  
  thist3 = (TH1D*)file_total->Get(tempname)->Clone();
  thist3->SetLineColor(3);
  //    thist3->SetFillColor(0);
  thist3->SetLineStyle(2);
  thist3->SetLineWidth(2);
  thist3->SetMaximum(maxVal);
  thist3->SetMinimum(minVal);
  thist3->SetTitle("");
    
  thist3->GetXaxis()->SetLabelFont(40);
  thist3->GetXaxis()->SetLabelOffset(0.007);
  thist3->GetXaxis()->SetLabelSize(0.04);
  thist3->GetXaxis()->SetTitleSize(0.05);
  thist3->GetXaxis()->SetTitleOffset(1.0);
  thist3->GetXaxis()->SetTitleFont(42);
  thist3->GetYaxis()->SetLabelFont(42);
  thist3->GetYaxis()->SetLabelOffset(0.007);
  thist3->GetYaxis()->SetLabelSize(0.04);
  thist3->GetYaxis()->SetTitleSize(0.05);
  thist3->GetYaxis()->SetTitleOffset(1.0);
  thist3->GetYaxis()->SetTitleFont(40);
  thist3->GetXaxis()->SetTitle("bins(H_{T}^{miss},N_{jet})");
  thist3->GetYaxis()->SetTitle("Acceptance (low #Delta#phi)");
  thist3->GetXaxis()->SetRangeUser(1.,XUp);
  thist3->SetMaximum(maxVal);
  thist3->SetLineWidth(3);
  thist3->Draw();
	
  thist2 = (TH1D*)file_WJet->Get(tempname)->Clone();
	
  thist2->SetLineColor(2);
  thist2->SetLineWidth(3);
  thist2->Draw("same");
	
  thist = (TH1D*)file_TTbar->Get(tempname)->Clone();
  thist->SetLineColor(1);
  //    thist->SetFillColor(0);
  thist->SetLineWidth(3);
  thist->Draw("same");

  thist3->Draw("same");
	
  sprintf(tempname,"t#bar{t}");
  catLeg1->AddEntry(thist,tempname,"l");
  sprintf(tempname,"W+jets");
  catLeg1->AddEntry(thist2,tempname,"l");  
  catLeg1->AddEntry(thist3,"t#bar{t} & W+jets","l");
  catLeg1->Draw();
  
  //
  // Labels for binnings
  //

  double ymax=1.1;
  double ymin=0.2;
  double ytext=0.5;

  TLatex * ttext1 = new TLatex(2.5 , ytext , "4 #leq N_{jets} #leq 6");
  ttext1->SetTextFont(42);
  ttext1->SetTextSize(0.04);
  ttext1->SetTextAlign(22);
  ttext1->Draw();

  TLatex * ttext2 = new TLatex(5.5 , ytext , "7 #leq N_{jets} #leq 8");
  ttext2->SetTextFont(42);
  ttext2->SetTextSize(0.04);
  ttext2->SetTextAlign(22);
  ttext2->Draw();

  TLatex * ttext3 = new TLatex(8.5 , ytext , "N_{jets} #geq 9");
  ttext3->SetTextFont(42);
  ttext3->SetTextSize(0.04);
  ttext3->SetTextAlign(22);
  ttext3->Draw();

  TLine *tline_1 = new TLine(4.,ymin,4.,ymax);
  tline_1->SetLineStyle(2);
  tline_1->Draw();

  TLine *tline_2 = new TLine(7.,ymin,7.,ymax);
  tline_2->SetLineStyle(2);
  tline_2->Draw();

  //
  // Save output
  //
  sprintf(tempname,"Acceptance_lowDphi_allSamples.png");
  c1->Print(tempname);
  sprintf(tempname,"Acceptance_lowDphi_allSamples.pdf");
  c1->Print(tempname);

}
