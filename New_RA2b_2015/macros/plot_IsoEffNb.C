
void plot_IsoEffNb(){

  TFile *_file0 = TFile::Open("TauHad/Stack/IsoEfficiencies_stacked.root");

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

  //-----

  TCanvas* canvas = new TCanvas("canvas","canvas",10,10,W,H);
  canvas->SetFillColor(0);
  canvas->SetBorderMode(0);
  canvas->SetFrameFillStyle(0);
  canvas->SetFrameBorderMode(0);
  canvas->SetLeftMargin( L/W );
  canvas->SetRightMargin( R/W );
  canvas->SetTopMargin( T/H );
  canvas->SetBottomMargin( B/H );
  canvas->SetTickx(1);
  canvas->SetTicky(1);

  canvas->Divide(2,2);
  canvas->cd(1);
  gPad->SetTickx(1);
  gPad->SetTicky(1);
  IsoEff_NbNjet34->SetMaximum(1.5);
  IsoEff_NbNjet34->SetMinimum(0.7);
  IsoEff_NbNjet34->GetYaxis()->SetTitle("Isotrk Veto Nb Correction");
  IsoEff_NbNjet34->GetXaxis()->SetTitle("N_{b}");
  IsoEff_NbNjet34->Draw();
  
  canvas->cd(2);
  gPad->SetTickx(1);
  gPad->SetTicky(1);
  IsoEff_NbNjet56->SetMaximum(1.5);
  IsoEff_NbNjet56->SetMinimum(0.7);
  IsoEff_NbNjet56->GetYaxis()->SetTitle("Isotrk Veto Nb Correction");
  IsoEff_NbNjet56->GetXaxis()->SetTitle("N_{b}");
  IsoEff_NbNjet56->Draw();
  
  canvas->cd(3);
  gPad->SetTickx(1);
  gPad->SetTicky(1);
  IsoEff_NbNjet78->SetMaximum(1.5);
  IsoEff_NbNjet78->SetMinimum(0.7);
  IsoEff_NbNjet78->GetYaxis()->SetTitle("Isotrk Veto Nb Correction");
  IsoEff_NbNjet78->GetXaxis()->SetTitle("N_{b}");
  IsoEff_NbNjet78->Draw();
  
  canvas->cd(4);
  gPad->SetTickx(1);
  gPad->SetTicky(1);
  IsoEff_NbNjet9->SetMaximum(1.5);
  IsoEff_NbNjet9->SetMinimum(0.7);
  IsoEff_NbNjet9->GetYaxis()->SetTitle("Isotrk Veto Nb Correction");
  IsoEff_NbNjet9->GetXaxis()->SetTitle("N_{b}");
  IsoEff_NbNjet9->Draw();

  canvas->SaveAs("plot_IsoEffNb_HDP.png");
  canvas->SaveAs("plot_IsoEffNb_HDP.pdf");

  //-----
  
  TCanvas* canvas2 = new TCanvas("canvas2","canvas2",10,10,W,H);
  canvas2->SetFillColor(0);
  canvas2->SetBorderMode(0);
  canvas2->SetFrameFillStyle(0);
  canvas2->SetFrameBorderMode(0);
  canvas2->SetLeftMargin( L/W );
  canvas2->SetRightMargin( R/W );
  canvas2->SetTopMargin( T/H );
  canvas2->SetBottomMargin( B/H );
  canvas2->SetTickx(1);
  canvas2->SetTicky(1);

  canvas2->Divide(2,2);
  canvas2->cd(1);
  gPad->SetTickx(1);
  gPad->SetTicky(1);
  IsoEff_NbNjet34_lowDphi->SetMaximum(1.5);
  IsoEff_NbNjet34_lowDphi->SetMinimum(0.7);
  IsoEff_NbNjet34_lowDphi->GetYaxis()->SetTitle("Isotrk Veto Nb Correction");
  IsoEff_NbNjet34_lowDphi->GetXaxis()->SetTitle("N_{b}");
  IsoEff_NbNjet34_lowDphi->Draw();
  
  canvas2->cd(2);
  gPad->SetTickx(1);
  gPad->SetTicky(1);
  IsoEff_NbNjet56_lowDphi->SetMaximum(1.5);
  IsoEff_NbNjet56_lowDphi->SetMinimum(0.7);
  IsoEff_NbNjet56_lowDphi->GetYaxis()->SetTitle("Isotrk Veto Nb Correction");
  IsoEff_NbNjet56_lowDphi->GetXaxis()->SetTitle("N_{b}");
  IsoEff_NbNjet56_lowDphi->Draw();
  
  canvas2->cd(3);
  gPad->SetTickx(1);
  gPad->SetTicky(1);
  IsoEff_NbNjet78_lowDphi->SetMaximum(1.5);
  IsoEff_NbNjet78_lowDphi->SetMinimum(0.7);
  IsoEff_NbNjet78_lowDphi->GetYaxis()->SetTitle("Isotrk Veto Nb Correction");
  IsoEff_NbNjet78_lowDphi->GetXaxis()->SetTitle("N_{b}");
  IsoEff_NbNjet78_lowDphi->Draw();
  
  canvas2->cd(4);
  gPad->SetTickx(1);
  gPad->SetTicky(1);
  IsoEff_NbNjet9_lowDphi->SetMaximum(1.5);
  IsoEff_NbNjet9_lowDphi->SetMinimum(0.7);
  IsoEff_NbNjet9_lowDphi->GetYaxis()->SetTitle("Isotrk Veto Nb Correction");
  IsoEff_NbNjet9_lowDphi->GetXaxis()->SetTitle("N_{b}");
  IsoEff_NbNjet9_lowDphi->Draw();

  canvas2->SaveAs("plot_IsoEffNb_LDP.png");
  canvas2->SaveAs("plot_IsoEffNb_LDP.pdf");
  
}
