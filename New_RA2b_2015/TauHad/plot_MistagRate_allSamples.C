
void plot_MistagRate_allSamples(string sample="TTbar_"){

  //
  // icomp=0: only show own results
  //       1: show also Koushik's results
  //
  
  //
  ///////////////////////////////////////////////////////////////////////////////////////////
  ////Some cosmetic work for official documents. 
  gStyle->SetOptStat(0);  ///to avoid the stat. on the plots 
  gROOT->LoadMacro("tdrstyle.C");
//  setTDRStyle();
  gROOT->LoadMacro("CMS_lumi_v2.C");

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

  TCanvas* c1 = new TCanvas("name","name",10,10,W,H);
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
  
  Float_t legendX1 = .60; //.50;
  Float_t legendX2 = .90; //.70;
  Float_t legendY1 = .60; //.65;
  Float_t legendY2 = .70;
  TLegend* catLeg1 = new TLegend(legendX1,legendY1,legendX2,legendY2);
  catLeg1->SetTextSize(0.042);
  catLeg1->SetTextFont(42);
  catLeg1->SetFillColor(0);
  catLeg1->SetLineColor(0);
  catLeg1->SetBorderSize(0);

  TH1D * temp_tt_tauH, * temp_wj_tauH, *temp_tt_muH, * temp_wj_muH;
  

  TFile file_WJet("Stack/TauBtaggedRate_WJet_stacked.root","R");
  temp_wj_tauH = (TH1D*)file_WJet.Get("TauBtaggedRate")->Clone();
  TH1D * wj_tauH = new TH1D("wj_tauH","WJet -- Tau mistag",temp_wj_tauH->GetNbinsX(),temp_wj_tauH->GetXaxis()->GetXmin(),temp_wj_tauH->GetXaxis()->GetXmax());
  for(int ibin=0;ibin<wj_tauH->GetNbinsX()+2;ibin++){
    double con = (double)temp_wj_tauH->GetBinContent(ibin);
    double err = (double)temp_wj_tauH->GetBinError(ibin);
    cout << "con: " << con << " err: " << err << endl;
    wj_tauH->SetBinContent(ibin,con);
    wj_tauH->SetBinError(ibin,err);
  }



  TFile file_TTbar("Stack/TauBtaggedRate_TTbar_stacked.root","R");  
  temp_tt_tauH = (TH1D*)file_TTbar.Get("TauBtaggedRate")->Clone();
  TH1D * tt_tauH = new TH1D("tt_tauH","WJet -- Tau mistag",temp_tt_tauH->GetNbinsX(),temp_tt_tauH->GetXaxis()->GetXmin(),temp_tt_tauH->GetXaxis()->GetXmax());
  for(int ibin=0;ibin<tt_tauH->GetNbinsX()+2;ibin++){
    double con = (double)temp_tt_tauH->GetBinContent(ibin);
    double err = (double)temp_tt_tauH->GetBinError(ibin);
    cout << "con: " << con << " err: " << err << endl;
    tt_tauH->SetBinContent(ibin,con);
    tt_tauH->SetBinError(ibin,err);
  }


  TFile file_WJet_mu("../TauHad2/Stack/TauBtaggedRate_WJet_stacked.root","R");  
  temp_wj_muH = (TH1D*)file_WJet_mu.Get("TauBtaggedRate")->Clone();
  TH1D * wj_muH = new TH1D("wj_muH","WJet -- Tau mistag",temp_wj_muH->GetNbinsX(),temp_wj_muH->GetXaxis()->GetXmin(),temp_wj_muH->GetXaxis()->GetXmax());
  for(int ibin=0;ibin<wj_muH->GetNbinsX()+2;ibin++){
    double con = (double)temp_wj_muH->GetBinContent(ibin);
    double err = (double)temp_wj_muH->GetBinError(ibin);
    cout << "con: " << con << " err: " << err << endl;
    wj_muH->SetBinContent(ibin,con);
    wj_muH->SetBinError(ibin,err);
  }



  TFile file_TTbar_mu("../TauHad2/Stack/TauBtaggedRate_TTbar_stacked.root","R");
  temp_tt_muH = (TH1D*)file_TTbar_mu.Get("TauBtaggedRate")->Clone();
  TH1D * tt_muH = new TH1D("tt_muH","WJet -- Tau mistag",temp_tt_muH->GetNbinsX(),temp_tt_muH->GetXaxis()->GetXmin(),temp_tt_muH->GetXaxis()->GetXmax());
  for(int ibin=0;ibin<tt_muH->GetNbinsX()+2;ibin++){
    double con = (double)temp_tt_muH->GetBinContent(ibin);
    double err = (double)temp_tt_muH->GetBinError(ibin);
    cout << "con: " << con << " err: " << err << endl;
    tt_muH->SetBinContent(ibin,con);
    tt_muH->SetBinError(ibin,err);
  }




//  catLeg1->SetHeader("Prob. of #mu from #tau ");


//...........................................................................//
// TTbar ....................................................................//
//...........................................................................//
    double XUp = 500. , maxVal=1.;

    wj_tauH->GetXaxis()->SetRangeUser(0.,XUp);
    wj_tauH->SetMaximum(maxVal);
    wj_tauH->SetTitle("");
    
    wj_tauH->GetXaxis()->SetLabelFont(42);
    wj_tauH->GetXaxis()->SetLabelOffset(0.007);
    wj_tauH->GetXaxis()->SetLabelSize(0.04);
    wj_tauH->GetXaxis()->SetTitleSize(0.05);
    wj_tauH->GetXaxis()->SetTitleOffset(0.9);
    wj_tauH->GetXaxis()->SetTitleFont(42);
    wj_tauH->GetYaxis()->SetLabelFont(42);
    wj_tauH->GetYaxis()->SetLabelOffset(0.007);
    wj_tauH->GetYaxis()->SetLabelSize(0.04);
    wj_tauH->GetYaxis()->SetTitleSize(0.05);
    wj_tauH->GetYaxis()->SetTitleOffset(1.25);
    wj_tauH->GetYaxis()->SetTitleFont(42);
    wj_tauH->GetXaxis()->SetTitle("p_{T}(#tau jet)");
    wj_tauH->GetYaxis()->SetTitle("mistag rate");
    wj_tauH->GetXaxis()->SetRangeUser(0.,XUp);
    wj_tauH->SetMaximum(maxVal);
    wj_tauH->SetLineColor(2);
    wj_tauH->Draw();


    tt_tauH->SetLineColor(1);
//    thist.SetFillColor(0);
//    thist.SetLineWidth(3);
    tt_tauH->Draw("same");


    wj_muH->SetLineColor(3); 
//    wj_muH->SetMarkerStyle(20);
    wj_muH->Draw("same");

    tt_muH->SetLineColor(4);   
    tt_muH->Draw("same");


    sprintf(tempname,"T#bar{T}");
    catLeg1->AddEntry(tt_tauH,tempname,"l");
    sprintf(tempname,"WJet");
    catLeg1->AddEntry(wj_tauH,tempname,"l");    
    sprintf(tempname,"mu from T#bar{T}");
    catLeg1->AddEntry(tt_muH,tempname,"l");
    sprintf(tempname,"mu from WJet");
    catLeg1->AddEntry(wj_muH,tempname,"l");
    catLeg1->Draw();
  

    sprintf(tempname,"TauBtaggedRate_allSamples.png");
    c1->Print(tempname);
}
