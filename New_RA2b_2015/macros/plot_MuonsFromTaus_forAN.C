

void plot_MuonsFromTaus_forAN(){

  //
  // icomp=0: only show own results
  //       1: show also Koushik's results
  //
  
  //
  ///////////////////////////////////////////////////////////////////////////////////////////
  ////Some cosmetic work for official documents. 
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();
  gROOT->LoadMacro("CMS_lumi_v2.C");
  
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
  
  double ymax=1.0;
  double ymin=0.0;
  double ytext=0.88;
  
  TCanvas* c1 = new TCanvas("name","name",10,10,W,H);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin( L/W );
  c1->SetRightMargin( R/W );
  c1->SetTopMargin( T/H );
  c1->SetBottomMargin( B/H );
  //c1->SetTickx(0);
  //c1->SetTicky(0);

  gStyle->SetOptStat(000000);
  gStyle->SetErrorX(0.5); 
  
  Float_t legendX1 = .60; //.50;
  Float_t legendX2 = .90; //.70;
  Float_t legendY1 = .60; //.65;
  Float_t legendY2 = .90;
  TLegend* catLeg1 = new TLegend(legendX1,legendY1,legendX2,legendY2);
  catLeg1->SetTextSize(0.042);
  catLeg1->SetTextFont(42);
  catLeg1->SetFillColor(0);
  catLeg1->SetLineColor(0);
  catLeg1->SetBorderSize(0);

  //
  
  sprintf(tempname,"TauHad2/Stack/Probability_Tau_mu_stacked.root");
  TFile *file   = new TFile(tempname,"R");

  sprintf(tempname,"hProb_Tau_mu");
  thist = (TH1D*)file->Get(tempname)->Clone();

  TH1F *thist_fixed = new TH1F("thist_fixed","thist_fixed",18,1.,19.);
  for (int ibin=0;ibin<18;ibin++){
    thist_fixed->SetBinContent(ibin+1,thist->GetBinContent(ibin+1));
    thist_fixed->SetBinError(ibin+1,thist->GetBinError(ibin+1));
  }
  
  thist_fixed->SetLineColor(1);
  thist_fixed->SetLineWidth(3);
  thist_fixed->SetStats(kFALSE);

  thist_fixed->SetTitle("");
  
  thist_fixed->SetMaximum(ymax);
  thist_fixed->GetXaxis()->SetLabelFont(42);
  thist_fixed->GetXaxis()->SetLabelOffset(0.007);
  thist_fixed->GetXaxis()->SetLabelSize(0.04);
  thist_fixed->GetXaxis()->SetTitleSize(0.05);
  thist_fixed->GetXaxis()->SetTitleOffset(1.0);
  thist_fixed->GetXaxis()->SetTitleFont(42);
  thist_fixed->GetYaxis()->SetLabelFont(42);
  thist_fixed->GetYaxis()->SetLabelOffset(0.007);
  thist_fixed->GetYaxis()->SetLabelSize(0.04);
  thist_fixed->GetYaxis()->SetTitleSize(0.05);
  thist_fixed->GetYaxis()->SetTitleOffset(1.20);
  thist_fixed->GetYaxis()->SetTitleFont(42);

  //KH adhoc
  thist_fixed->SetBinContent(18,0.2);
  
  thist_fixed->GetYaxis()->SetTitle("Fraction of muons from #tau decays");
  thist_fixed->GetXaxis()->SetTitle("Search bin");
  thist_fixed->SetMarkerStyle(20);
  thist_fixed->Draw();

  TLatex * ttext1 = new TLatex(4. , ytext , "4 #leq N_{jets} #leq 6");
  ttext1->SetTextFont(42);
  ttext1->SetTextSize(0.04);
  ttext1->SetTextAlign(22);
  ttext1->Draw();

  TLatex * ttext2 = new TLatex(10. , ytext , "7 #leq N_{jets} #leq 8");
  ttext2->SetTextFont(42);
  ttext2->SetTextSize(0.04);
  ttext2->SetTextAlign(22);
  ttext2->Draw();

  TLatex * ttext3 = new TLatex(16. , ytext , "N_{jets} #geq 9");
  ttext3->SetTextFont(42);
  ttext3->SetTextSize(0.04);
  ttext3->SetTextAlign(22);
  ttext3->Draw();

  TLine *tline_1 = new TLine(7.,ymin,7.,ymax);
  tline_1->SetLineStyle(2);
  tline_1->Draw();

  TLine *tline_2 = new TLine(13.,ymin,13.,ymax);
  tline_2->SetLineStyle(2);
  tline_2->Draw();
  
  c1->Print("plot_MuonsFromTaus.pdf");

}
